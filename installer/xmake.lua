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

-- Confirmed by testing: wprint/cprint are unavailable not just at
-- description scope, but also inside on_load/on_build during xmake f's
-- own internal target pre-check pass (_check_targets) on a project this
-- size -- a stricter environment than a normal `xmake build` invocation
-- of the same callback. Shimmed as LOCALS (not modifying the globals) so
-- every on_load/on_build closure later in this same file resolves them
-- via lexical scoping, which works regardless of which of the two
-- environments is actually active at call time -- falls through to the
-- real wprint/cprint when they do exist, so normal builds keep the
-- colored output.
local wprint = wprint or function(fmt, ...) print(string.format(fmt, ...)) end
local cprint = cprint or function(fmt, ...) print(string.format((fmt:gsub("%${[%w_]+}", "")), ...)) end

local unpack = table.unpack or unpack
local arch = get_config("target_arch") or "amd64"

-- ==============================================================================
-- Small utilities
-- ==============================================================================
local function read_file(filepath)
    if type(io) ~= "table" or not io.open then return nil end
    local f = io.open(filepath, "r")
    if not f then return nil end
    local c = f:read("*a")
    f:close()
    return c
end

local function list_subdirs(dir)
    local dirs = os.dirs(path.join(dir, "*"))
    table.sort(dirs)
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
    if type(io) ~= "table" or not io.open then
        wprint("eteleos-installer: io unavailable, cannot write %s", listfile)
        return
    end
    local f = io.open(listfile, "w")
    if not f then
        wprint("eteleos-installer: could not write %s", listfile)
        return
    end
    for _, e in ipairs(entries) do f:write(e, "\n") end
    f:close()

    import("lib.detect.find_tool")
    local pax = find_tool("pax")
    local sh = find_tool("sh")
    local ok
    if pax and sh then
        -- pax -w -d < list | gzip > outfile -- matches maketars exactly.
        ok = os.execv(sh.program, {"-c",
            string.format('cd "%s" && pax -w -d < "%s" | gzip > "%s"', destdir, listfile, outfile)},
            {try = true})
    else
        if not sh then
            wprint("eteleos-installer: no POSIX shell (sh) found -- falling back to tar "
                   .. "--files-from (not byte-identical to the real maketars, but produces "
                   .. "an equivalent .tgz). On Windows, install Git Bash, WSL, or MSYS2 for "
                   .. "the exact pax-based behavior.")
        else
            wprint("eteleos-installer: pax not found, falling back to tar --files-from "
                   .. "(not byte-identical to the real maketars, but produces an "
                   .. "equivalent .tgz for plain path lists)")
        end
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
        print(string.format("eteleos-installer: special/%s: no matching userland/ program found by name, skipping",
              name))
        return
    end
    local c_files = os.files(path.join(srcdir, "**.c"))
    if #c_files == 0 then
        print(string.format("eteleos-installer: special/%s: source dir %s has no .c files, skipping", name, srcdir))
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
        print("eteleos-installer: installer/special not found, skipping miniroot tools")
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
-- ==============================================================================
-- INSTALL IMAGE / ISO -- cross-platform rewrite (mtools + xorriso)
-- ==============================================================================
-- The real installer/amd64/iso/Makefile builds the install image using
-- vnconfig(8), fdisk(8), disklabel(8), newfs(8), mount(8) -- OpenBSD-only
-- privileged disk operations that cannot run on any other host, and were
-- never reimplemented here (see the previous revision's honest gap note,
-- and git history for that placeholder).
--
-- This revision builds a UEFI-bootable ISO a different way, using only
-- tools that are genuinely cross-platform and need no root/mount/vnd(4):
--   - mtools (mformat/mmd/mcopy) builds a small FAT "EFI System Partition"
--     image directly, as a plain file -- no loopback device, no root.
--   - xorriso authors the actual ISO9660 image and its El Torito boot
--     catalog, pointing at that FAT image for UEFI "no emulation" boot.
-- Every step below calls os.execv() with an explicit argv list -- never a
-- shell command string -- so none of this needs `sh`/bash at all, unlike
-- the pax/configure&&make paths elsewhere in this project that
-- necessarily do (confirmed: mtools and xorriso both take plain
-- command-line arguments, no shell features needed for any step here).
--
-- WHAT THIS DOES vs THE REAL installer(8)/release(8) -- read before relying
-- on this for anything beyond a boot-test image:
--   - Only UEFI boot is produced (matches kernel/xmake.lua: legacy BIOS
--     boot was explicitly never implemented there either). The ISO is
--     also isohybrid-GPT, so the same file can be dd'd to a USB stick.
--   - The kernel built by eteleos-kernel (GENERIC-equivalent) is placed at
--     the ISO9660 root as "/bsd" -- the real EFI bootloader's own libsa
--     includes a cd9660.c driver (verified in EFI_BOOTLOADERS' own
--     libsa_srcs list above), so it should be able to find and load a
--     kernel placed exactly this way on a real cd9660 filesystem, the
--     same as the genuine OpenBSD install CD's own layout.
--   - This is NOT the RAMDISK-based installer (see the still-open
--     BOOT IMAGE gap noted above) -- there is no interactive installer on
--     this ISO, just a bootable kernel. Booting it gets you as far as
--     whatever the GENERIC kernel does on its own (single-user-ish,
--     depending on init/rc availability), not a guided OpenBSD install.
--   - NOT verified by actually booting the result in a VM/hardware in
--     this delivery -- verified only that the pipeline runs and produces
--     a file of the expected shape (valid FAT image, valid ISO9660+El
--     Torito structure). Please boot-test it yourself before relying on it.
-- ==============================================================================

local EFI_PROG_NAMES = {amd64 = "BOOTX64.EFI", arm64 = "BOOTAA64.EFI", riscv64 = "BOOTRISCV64.EFI"}

target("eteleos-install-image")
    set_kind("phony")
    set_default(false)
    add_deps("eteleos-kernel")
    if ETELEOS_DECLARED_EFIBOOT and ETELEOS_DECLARED_EFIBOOT[arch] then
        add_deps("eteleos-kernel-efiboot-" .. arch)
    end

    on_build(function (target)
        import("lib.detect.find_tool")

        local mformat = find_tool("mformat")
        local mmd     = find_tool("mmd")
        local mcopy   = find_tool("mcopy")
        local xorriso = find_tool("xorriso")
        local missing = {}
        if not mformat then missing[#missing + 1] = "mformat" end
        if not mmd     then missing[#missing + 1] = "mmd" end
        if not mcopy   then missing[#missing + 1] = "mcopy" end
        if not xorriso then missing[#missing + 1] = "xorriso" end
        if #missing > 0 then
            wprint("eteleos-installer: install image needs mtools (mformat/mmd/mcopy) and "
                   .. "xorriso -- missing: %s. Install: Linux `apt install mtools xorriso`, "
                   .. "macOS `brew install mtools xorriso`, Windows via MSYS2 "
                   .. "`pacman -S mtools xorriso` (add MSYS2's usr/bin to PATH). Skipping.",
                   table.concat(missing, ", "))
            return
        end

        local prog_name = EFI_PROG_NAMES[arch]
        if not prog_name then
            wprint("eteleos-installer: no EFI bootloader filename known for arch '%s', "
                   .. "skipping install image", arch)
            return
        end
        local efi_bin = path.join(os.projectdir(), "build", "eteleos-kernel-gen", arch,
                                   "efiboot", prog_name)
        if not os.isfile(efi_bin) then
            wprint("eteleos-installer: %s not found -- build the EFI bootloader first "
                   .. "(xmake build eteleos-kernel-efiboot-%s). Skipping install image.",
                   efi_bin, arch)
            return
        end

        local kernel_dep = target:dep("eteleos-kernel")
        local kernel_bin = kernel_dep and kernel_dep:targetfile()
        if not kernel_bin or not os.isfile(kernel_bin) then
            wprint("eteleos-installer: kernel binary not found -- build eteleos-kernel "
                   .. "first. Skipping install image.")
            return
        end

        local gendir = path.join(os.projectdir(), "build", "eteleos-installer-gen", arch)
        local isoroot = path.join(gendir, "isoroot")
        os.tryrm(isoroot)
        os.mkdir(path.join(isoroot, "EFI", "BOOT"))

        -- --- 1. Build the FAT "EFI System Partition" image with mtools ------------
        -- 4 MiB is comfortably more than a single small bootloader binary needs;
        -- mtools defaults to FAT12/16 at this size, which is what UEFI firmware
        -- expects for a removable-media ESP this small.
        local esp_img = path.join(gendir, "efiboot.img")
        os.tryrm(esp_img)
        local esp_ok = os.execv(mformat.program,
            {"-i", esp_img, "-C", "-T", "8192", "-v", "ETELEOSESP", "::"}, {try = true})
        if esp_ok then
            esp_ok = os.execv(mmd.program, {"-i", esp_img, "::EFI"}, {try = true})
        end
        if esp_ok then
            esp_ok = os.execv(mmd.program, {"-i", esp_img, "::EFI/BOOT"}, {try = true})
        end
        if esp_ok then
            esp_ok = os.execv(mcopy.program,
                {"-i", esp_img, efi_bin, "::EFI/BOOT/" .. prog_name}, {try = true})
        end
        if not esp_ok or not os.isfile(esp_img) then
            wprint("eteleos-installer: building the FAT EFI System Partition image failed "
                   .. "(mformat/mmd/mcopy step) -- skipping install image")
            return
        end

        -- --- 2. Assemble the ISO9660 tree ------------------------------------------
        os.cp(esp_img, path.join(isoroot, "efiboot.img"))
        os.cp(efi_bin, path.join(isoroot, "EFI", "BOOT", prog_name))
        os.cp(kernel_bin, path.join(isoroot, "bsd"))

        -- --- 3. Author the ISO with xorriso -----------------------------------------
        -- -e/-no-emul-boot: El Torito "no emulation" boot pointing at the FAT
        -- image above -- this is what UEFI firmware looks for. -isohybrid-gpt-basdat
        -- additionally makes the same .iso file directly writable to a USB stick
        -- with dd and still bootable (isohybrid MBR + a GPT ESP entry).
        local outdir = path.join(os.projectdir(), "build", "release", arch)
        os.mkdir(outdir)
        local isopath = path.join(outdir, "install" .. arch .. ".iso")
        local iso_ok = os.execv(xorriso.program, {
            "-as", "mkisofs",
            "-o", isopath,
            "-V", "ETELEOS_INSTALL",
            "-R", "-J",
            "-e", "efiboot.img", "-no-emul-boot",
            "-isohybrid-gpt-basdat",
            isoroot,
        }, {try = true})
        if not iso_ok or not os.isfile(isopath) then
            wprint("eteleos-installer: xorriso failed to build the ISO -- see output above")
            return
        end
        cprint("${green}eteleos-installer${clear}: built %s (UEFI-bootable, arch=%s)", isopath, arch)
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

        local function write_file_safe(filepath, content)
            if type(io) ~= "table" or not io.open then
                wprint("eteleos-installer: io unavailable, could not write %s", filepath)
                return
            end
            local f = io.open(filepath, "w")
            if not f then
                wprint("eteleos-installer: could not write %s", filepath)
                return
            end
            f:write(content)
            f:close()
        end

        local buildinfo = string.format("BUILD: EteleOS 0.1 (%s)\nDATE: %s\n",
                                         arch, os.date("%Y-%m-%d %H:%M:%S"))
        write_file_safe(path.join(outdir, "BUILDINFO"), buildinfo)

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
                write_file_safe(path.join(outdir, "SHA256"), out or "")
            end
        else
            wprint("eteleos-installer: no sha256/sha256sum found, skipping SHA256 manifest")
        end

        cprint("${green}eteleos-installer${clear}: release metadata written to %s", outdir)
    end)
target_end()
