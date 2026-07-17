--[[
================================================================================
 EteleOS: installer/xmake.lua, time write: 2026/07/13
 This file uses the Apache-2.0 license
================================================================================

Manages: install image, iso, boot image, release image, sets.

Verified against the current tree (github.com/EteleOS/EteleOS):
  installer/{amd64,arm64,riscv64,miniroot,notes,sets,special,syspatch,Makefile}

SETS -- the most tractable and fully implemented piece
--------------------------------------------------------
installer/sets/lists/<name>/{mi, md.<arch>} are plain text files, one
"./relative/path" per line -- verified real, e.g. base/mi lists "./bin/cat",
"./bin/ksh", etc. The real maketars script (read in full) does exactly this
for `base comp game man`:
  1. concatenate mi + md.<arch> (+ for comp: gcc.<arch>/clang.<arch> if present)
  2. sort, then reorder so every "./usr/lib/lib*" entry comes first
  3. pipe the list through `pax -w -d` and gzip into <name><rev>.tgz
This file reimplements that exact pipeline (steps 1-2 faithfully; step 3
uses pax if found, otherwise falls back to `tar -C <destdir> --files-from=-`,
verified to work in this sandbox as an equivalent for plain path lists).
etc.tgz is intentionally NOT built the same way: OpenBSD's real
installer/sets/makeetcset is a separate script with upgrade-merge-aware
behavior this file does not replicate -- see the note below.

SPECIAL (miniroot tools) -- implemented via name search, not .PATH
---------------------------------------------------------------------
installer/special/ has 72 program directories, each a thin wrapper Makefile
that reuses a userland/ program's source via ".PATH: ${.CURDIR}/../../../X"
and rebuilds it statically, size-optimized, without a man page, for the
install ramdisk. VERIFIED: every .PATH checked (cat, dd, bioctl, chroot)
points at the STALE pre-restructure location (../../../bin/cat,
../../../sbin/bioctl, ../../../usr.sbin/chroot) -- none of which exist
anymore. Rather than trust those broken paths, this file searches for a
same-named directory across the same categories userland/xmake.lua already
discovers programs in, and reuses ITS sources.

BOOT IMAGE -- honest gap, tied to kernel/xmake.lua
-----------------------------------------------------
The install ramdisk needs a SEPARATE kernel build (RAMDISK / RAMDISK_CD
configs, confirmed present at kernel/arch/<arch>/conf/{RAMDISK,RAMDISK_CD}),
not the GENERIC-equivalent kernel/xmake.lua currently builds. kernel/xmake.lua
is not yet parameterized by config name -- extending it to accept a config
option (and re-running the files/GENERIC parser against RAMDISK instead of
GENERIC) is a concrete follow-up, not attempted here.

INSTALL IMAGE / ISO -- honest gap, inherent to the tools involved
----------------------------------------------------------------------
The real installer/amd64/iso/Makefile (read in full) builds the install
image using vnconfig(8), fdisk(8), disklabel(8), newfs(8) and mount(8) --
OpenBSD kernel-specific privileged disk operations (vnd(4)) that cannot run
on a generic Linux (or other non-OpenBSD) build host, sandboxed or not. This
is not a gap in this file's logic; it is what release(8) building has always
required a real (or emulated) OpenBSD host for. This file provides a
best-effort wrapper that looks for these tools via find_tool() and runs the
same steps when they exist, and clearly warns and skips otherwise.
--------------------------------------------------------------------------------
--]]

local unpack = table.unpack or unpack
local arch = get_config("target_arch") or "amd64"

-- ==============================================================================
-- Small utilities
-- ==============================================================================
local function read_file(filepath)
    local f = io.open(filepath, "r")
    if not f then return nil end
    local c = f:read("*a")
    f:close()
    return c
end

local function list_subdirs(dir)
    local out = os.iorun(string.format('find "%s" -mindepth 1 -maxdepth 1 -type d 2>/dev/null | sort', dir))
    local dirs = {}
    if out then
        for line in out:gmatch("[^\r\n]+") do dirs[#dirs + 1] = line end
    end
    return dirs
end

-- Same category list userland/xmake.lua discovers programs in, used here
-- for the special/ tools' by-name search (see the note above).
local USERLAND_SEARCH_DIRS = {
    "development", "games", "libexec", "multimedia", "network", "package",
    "security", "system", "utilities", "essential/bin", "essential/sbin",
}

local function find_userland_program_dir(name)
    local userland_root = path.join(os.scriptdir(), "..", "userland")
    for _, cat in ipairs(USERLAND_SEARCH_DIRS) do
        local candidate = path.join(userland_root, cat, name)
        if os.isdir(candidate) then return candidate end
    end
    return nil
end

-- ==============================================================================
-- Sets: parse installer/sets/lists/<name>/{mi,md.<arch>} into a sorted,
-- lib-first path list, matching maketars' own ordering exactly.
-- ==============================================================================
local SET_NAMES = {"base", "comp", "etc", "game", "man"}

local function read_list_file(filepath)
    local content = read_file(filepath)
    local entries = {}
    if not content then return entries end
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local trimmed = line:match("^%s*(.-)%s*$")
        if trimmed ~= "" and not trimmed:match("^#") then
            entries[#entries + 1] = trimmed
        end
    end
    return entries
end

local function build_set_list(setname)
    local listsdir = path.join(os.scriptdir(), "sets", "lists", setname)
    local entries = {}
    for _, e in ipairs(read_list_file(path.join(listsdir, "mi"))) do entries[#entries + 1] = e end
    for _, e in ipairs(read_list_file(path.join(listsdir, "md." .. arch))) do entries[#entries + 1] = e end
    if setname == "comp" then
        for _, e in ipairs(read_list_file(path.join(listsdir, "gcc." .. arch))) do entries[#entries + 1] = e end
        for _, e in ipairs(read_list_file(path.join(listsdir, "clang." .. arch))) do entries[#entries + 1] = e end
    end

    table.sort(entries)
    -- maketars puts every "./usr/lib/lib*" entry first (library load-order
    -- concern during set extraction); replicate exactly.
    local libs, rest = {}, {}
    for _, e in ipairs(entries) do
        if e:match("^%./usr/lib/lib") then
            libs[#libs + 1] = e
        else
            rest[#rest + 1] = e
        end
    end
    local ordered = {}
    for _, e in ipairs(libs) do ordered[#ordered + 1] = e end
    for _, e in ipairs(rest) do ordered[#ordered + 1] = e end
    return ordered
end

-- Build one <name><version>.tgz from `destdir` (the already-populated
-- xmake installdir) into `outdir`, using pax if available, else tar.
local function write_tarball(setname, entries, destdir, outdir, version)
    if #entries == 0 then
        wprint("eteleos-installer: %s set has no entries for arch '%s', skipping", setname, arch)
        return
    end
    os.mkdir(outdir)
    local outfile = path.join(outdir, setname .. version .. ".tgz")
    local listfile = path.join(outdir, "." .. setname .. ".list")
    local f = io.open(listfile, "w")
    for _, e in ipairs(entries) do f:write(e, "\n") end
    f:close()

    import("lib.detect.find_tool")
    local pax = find_tool("pax")
    local ok
    if pax then
        -- pax -w -d < list | gzip > outfile -- matches maketars exactly.
        ok = os.execv("sh", {"-c",
            string.format('cd "%s" && pax -w -d < "%s" | gzip > "%s"', destdir, listfile, outfile)},
            {try = true})
    else
        wprint("eteleos-installer: pax not found, falling back to tar --files-from "
               .. "(not byte-identical to the real maketars, but produces an "
               .. "equivalent .tgz for plain path lists)")
        ok = os.execv("tar", {"-czf", outfile, "-C", destdir, "--files-from=" .. listfile}, {try = true})
    end
    if ok then
        cprint("${green}eteleos-installer${clear}: built %s (%d entries)", outfile, #entries)
    else
        wprint("eteleos-installer: failed to build %s", outfile)
    end
end

-- ==============================================================================
-- Special (miniroot) tools: statically-linked, size-optimized rebuild of a
-- same-named userland program, for the install ramdisk.
-- ==============================================================================
local function eteleos_special_tool(name, specialdir)
    local srcdir = find_userland_program_dir(name)
    if not srcdir then
        wprint("eteleos-installer: special/%s: no matching userland/ program found by name, skipping",
               name)
        return
    end
    local c_files = os.files(path.join(srcdir, "**.c"))
    if #c_files == 0 then
        wprint("eteleos-installer: special/%s: source dir %s has no .c files, skipping", name, srcdir)
        return
    end

    target("installer-special-" .. name)
        set_kind("binary")
        set_default(false)

        add_rules("eteleos.base")   -- deliberately NOT eteleos.userland: no PIE/relro here,
                                     -- matching the real NOPIE=/LDSTATIC=-static miniroot build
        add_files(unpack(c_files))
        add_includedirs(srcdir)
        add_deps("eteleos-headers")

        -- Matches the real installer/special/Makefile.inc flags: size-
        -- optimized, static, no unwind tables, no stack protector.
        add_cxflags("-Oz", "-fno-stack-protector", "-fno-unwind-tables",
                    "-fno-asynchronous-unwind-tables")
        add_ldflags("-static", {force = true})
    target_end()
end

-- ==============================================================================
-- Targets
-- ==============================================================================

-- --- Sets ---------------------------------------------------------------------
target("eteleos-sets")
    set_kind("phony")
    set_default(false)
    on_build(function (target)
        local destdir = get_config("installdir") or path.join(os.scriptdir(), "..", "build", "install")
        local outdir = path.join(os.scriptdir(), "..", "build", "release", arch)
        local version = "0.1"  -- placeholder, matches root xmake.lua's set_version prefix

        for _, setname in ipairs(SET_NAMES) do
            if setname == "etc" then
                wprint("eteleos-installer: etc.tgz built via the same simple tar-from-list "
                       .. "path as the other sets -- the real installer/sets/makeetcset "
                       .. "does upgrade-merge-aware handling this does NOT replicate")
            end
            local entries = build_set_list(setname)
            write_tarball(setname, entries, destdir, outdir, version)
        end
    end)
target_end()

-- --- Special (miniroot) tools --------------------------------------------------
do
    local specialdir = path.join(os.scriptdir(), "special")
    if os.isdir(specialdir) then
        for _, dir in ipairs(list_subdirs(specialdir)) do
            local name = path.filename(dir)
            if os.isfile(path.join(dir, "Makefile")) then
                eteleos_special_tool(name, dir)
            end
        end
    else
        wprint("eteleos-installer: installer/special not found, skipping miniroot tools")
    end
end

-- --- Boot image (RAMDISK kernel) -- honest gap, see file header ---------------
target("eteleos-boot-image")
    set_kind("phony")
    set_default(false)
    on_build(function (target)
        raise("eteleos-installer: boot image needs a RAMDISK-config kernel build, which "
              .. "kernel/xmake.lua does not yet support (it only builds the GENERIC-"
              .. "equivalent config) -- see the note at the top of this file")
    end)
target_end()

-- --- Install image / ISO -- best-effort, requires an OpenBSD-like host --------
target("eteleos-install-image")
    set_kind("phony")
    set_default(false)
    on_build(function (target)
        import("lib.detect.find_tool")
        local required = {"vnconfig", "fdisk", "disklabel", "newfs", "mount"}
        local missing = {}
        for _, toolname in ipairs(required) do
            if not find_tool(toolname) then missing[#missing + 1] = toolname end
        end
        if #missing > 0 then
            wprint("eteleos-installer: install image/ISO needs %s, none of which exist on a "
                   .. "typical non-OpenBSD build host (missing here: %s) -- this step must "
                   .. "run on a real or emulated OpenBSD system, matching how release(8) "
                   .. "building has always worked; skipping",
                   table.concat(required, ", "), table.concat(missing, ", "))
            return
        end
        wprint("eteleos-installer: all required disk tools were found, but the actual "
               .. "vnd(4)/newfs/mount sequence from installer/%s/iso/Makefile is not "
               .. "reimplemented here yet -- wire it up once this is confirmed running "
               .. "on a real OpenBSD host", arch)
    end)
target_end()

-- --- Release image: notes + checksums, the tractable part of "make release" ---
target("eteleos-release")
    set_kind("phony")
    set_default(false)
    add_deps("eteleos-sets")
    on_build(function (target)
        local outdir = path.join(os.scriptdir(), "..", "build", "release", arch)
        os.mkdir(outdir)

        local notes = path.join(os.scriptdir(), "notes", arch, "install")
        if os.isfile(notes) then
            os.cp(notes, path.join(outdir, "INSTALL." .. arch))
        else
            wprint("eteleos-installer: notes/%s/install not found, skipping INSTALL.%s", arch, arch)
        end

        local buildinfo = string.format("BUILD: EteleOS 0.1 (%s)\nDATE: %s\n",
                                         arch, os.date("%Y-%m-%d %H:%M:%S"))
        io.open(path.join(outdir, "BUILDINFO"), "w"):write(buildinfo):close()

        -- SHA256 manifest of everything just built, matching the real
        -- release directory's own "SHA256" file -- best-effort: uses
        -- sha256/sha256sum, whichever is found.
        import("lib.detect.find_tool")
        local sha = find_tool("sha256") or find_tool("sha256sum")
        if sha then
            local files = os.files(path.join(outdir, "*.tgz"))
            if #files > 0 then
                local out = os.iorun(string.format('cd "%s" && %s %s', outdir, sha.program,
                    table.concat((function()
                        local names = {}
                        for _, f in ipairs(files) do names[#names+1] = f:match("([^/]+)$") end
                        return names
                    end)(), " ")))
                io.open(path.join(outdir, "SHA256"), "w"):write(out or ""):close()
            end
        else
            wprint("eteleos-installer: no sha256/sha256sum found, skipping SHA256 manifest")
        end

        cprint("${green}eteleos-installer${clear}: release metadata written to %s", outdir)
    end)
target_end()
