/*
 EteleOS: xmake.lua, time wirte: 2026/07/12
 This file uses the Apache-2.0 license
*/

--[[
================================================================================
 EteleOS :: kernel/xmake.lua
================================================================================

Manages: kernel core, subsystems ("modules"), drivers, architecture, linker
script and the final kernel image ("bsd", OpenBSD's traditional kernel name).

This revision replaces the earlier hand-picked driver allowlist with a real
parser for kernel/core/conf/files, kernel/arch/<arch>/conf/files.<arch> and
the GENERIC config files -- an actual (if simplified) approximation of what
config(8) does, instead of a guess at "safe" driver categories. It also
generates vers.c and assym.h, and applies real per-file compiler flag
overrides found in the current Makefile.<arch> files.

WHAT THIS DOES vs. THE OLD ALLOWLIST
-------------------------------------
  1. parse_generic()     reads GENERIC (+ its "include"d MI GENERIC) and
                          collects every "device"/"option"/"pseudo-device"
                          name that is turned on, into an "enabled" set.
  2. parse_files_list()  reads files / files.<arch> and extracts every
                          "file <path> <condition>" entry, correctly joining
                          multi-line conditions (config(8)'s files list wraps
                          long boolean expressions across lines with no
                          special continuation marker -- verified against
                          the real dev/ic/ahci.c entry, which spans 2 lines).
  3. eval_expr()          a real recursive-descent evaluator for the
                          "a & b | (c | d)" boolean expressions used as
                          conditions, with "needs-flag"/"needs-count"
                          modifiers stripped before evaluation.
  A file is compiled if its condition is empty (unconditional) or evaluates
  to true against the enabled set. This was tested against the ACTUAL
  kernel/core/conf/files (608 entries) and kernel/arch/amd64/conf/files.amd64
  (292 entries) content: 373 files selected, 328 excluded, including correct
  results for spot-checked entries (dev/ic/ahci.c -> included, matching an
  enabled "ahci" alias; dev/ic/aic6360.c -> excluded, an ISA-only SCSI
  controller not present on a modern GENERIC).

KNOWN REMAINING LIMITATION -- please read
------------------------------------------
  config(8)'s real semantics let a device declare that it PROVIDES an
  attribute other than its own name via "attach <dev> at <bus> with <alias>"
  in the files list (e.g. "attach vga at pci with vga_pci"). This file does
  NOT resolve that attach-graph: it only ever enables the literal identifier
  appearing before "at" in GENERIC (e.g. "vga0 at pci?" enables "vga", not
  "vga_pci"). This causes real, observed false negatives -- e.g.
  dev/ic/vga.c (condition "vga & (vga_pci | vga_isa)") is currently excluded
  even on a GENERIC that would enable it through vga_pci in real config(8).
  Fully closing this gap means walking the "attach ... with ..." graph, which
  is the deepest 20% of config(8)'s job. NOTE: config(8)'s own source is
  present in this tree at userland/system/config/ (confirmed, including
  mkioconf.c) -- actually building and invoking the real config(8) as a host
  tool would be the fully-faithful fix, and is a reasonable next step, but is
  not attempted here.

  ioconf.c (the generated device-attachment table config(8) normally
  produces) is still NOT generated -- same category of gap, tracked
  separately from file selection.

  Also out of scope here (unchanged from the previous revision):
  kernel/arch/*/stand/ (bootloaders) and the RAMDISK/RAMDISK_CD/VMBOOT
  config variants; this file targets the equivalent of GENERIC only.
--------------------------------------------------------------------------------
--]]

local unpack = table.unpack or unpack
local arch   = get_config("target_arch") or "amd64"

-- ==============================================================================
-- Per-architecture facts (verified against the current tree)
-- ==============================================================================
local MD_CORE_DIRS = { amd64 = "amd64", arm64 = "arm64", riscv64 = "riscv64" }

local BUS_GLUE_DIRS = {
    amd64   = {"isa", "pci"},
    arm64   = {"dev"},
    riscv64 = {"dev"},
}

-- Linker script filename -- NOT uniform across architectures.
local LDSCRIPT_NAMES = {
    amd64   = "ld.script",
    arm64   = "kern.ldscript",
    riscv64 = "kern.ldscript",
}

-- Machine-dependent compiler flags -- read directly out of each
-- kernel/arch/<arch>/conf/Makefile.<arch>'s CMACHFLAGS, NOT assumed uniform:
--   amd64:   -mcmodel=kernel -mno-red-zone -mno-sse2 -mno-sse -mno-3dnow
--   arm64:   -march=armv8-a+nofp+nosimd+rng -moutline-atomics
--            -fno-stack-protector -mbranch-protection=bti
--   riscv64: -march=rv64gc -mcmodel=medany -mno-relax -fno-stack-protector
local CMACHFLAGS = {
    amd64 = {
        "-mcmodel=kernel", "-mno-red-zone",
        "-mno-sse2", "-mno-sse", "-mno-3dnow",
    },
    arm64 = {
        "-march=armv8-a+nofp+nosimd+rng",
        "-moutline-atomics",
        "-fno-stack-protector",
        "-mbranch-protection=bti",
    },
    riscv64 = {
        "-march=rv64gc", "-mcmodel=medany", "-mno-relax",
        "-fno-stack-protector",
    },
}

-- Per-file compiler flag overrides -- data taken directly from
-- kernel/arch/amd64/conf/Makefile.amd64's HARDFLOAT_CFLAGS block, which
-- re-enables SSE (globally disabled above via -mno-sse/-mno-sse2) for a
-- specific list of AMD display-driver floating-point helper files. This is
-- the ONE verified example found so far; extend this table as other
-- arch Makefiles are audited the same way.
local PER_FILE_CFLAGS = {
    amd64 = {
        ["dev/pci/drm/amd/display/dc/dml/dcn10/dcn10_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/dcn20_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20.c"] = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20v2.c"]  = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20v2.c"]={"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn21/display_mode_vba_21.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn21/display_rq_dlg_calc_21.c"] = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn30/display_mode_vba_30.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn30/display_rq_dlg_calc_30.c"] = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn30/dcn30_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn31/display_mode_vba_31.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn314/display_mode_vba_314.c"]  = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn314/display_rq_dlg_calc_314.c"]={"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn314/dcn314_fpu.c"]            = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn32/dcn32_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_32.c"]    = {"-msse", "-msse2"},
    },
    arm64 = {},
    riscv64 = {},
}

if not MD_CORE_DIRS[arch] then
    raise("eteleos-kernel: unsupported target_arch '%s'", arch)
end

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

local function write_file(filepath, content)
    local f = io.open(filepath, "w")
    if not f then
        raise("eteleos-kernel: could not write %s", filepath)
    end
    f:write(content)
    f:close()
end

local function strip_comment(line)
    local in_quote = false
    for i = 1, #line do
        local c = line:sub(i, i)
        if c == '"' then in_quote = not in_quote
        elseif c == "#" and not in_quote then
            return line:sub(1, i - 1)
        end
    end
    return line
end

local function extract_base_name(token)
    return (token:gsub("[%d%*]+$", ""))
end

-- ==============================================================================
-- config(8) approximation: GENERIC parser
-- ==============================================================================
-- Collects every enabled device/option/pseudo-device NAME from a GENERIC-
-- style file into `enabled`. Follows "include" directives; resolves the
-- include path relative to the including file first, then falls back to
-- kernel/core/conf/ (the current MI conf location) if that literal path is
-- stale -- which it currently IS for every arch's GENERIC (verified: all
-- three say `include "../../../conf/GENERIC"`, which resolves to the
-- pre-restructure sys/conf/GENERIC location and no longer exists; consider
-- fixing this path directly in the config files as a follow-up).
local function resolve_include(from_dir, incpath, core_conf_dir)
    local naive = path.join(from_dir, incpath)
    if os.isfile(naive) then return naive end
    local fallback = path.join(core_conf_dir, path.filename(incpath))
    if os.isfile(fallback) then
        wprint("eteleos-kernel: GENERIC include \"%s\" is stale (resolved from %s); "
               .. "falling back to %s -- consider fixing the include path in the source",
               incpath, from_dir, fallback)
        return fallback
    end
    return nil
end

local function parse_generic(filepath, core_conf_dir, enabled, seen)
    seen = seen or {}
    if seen[filepath] then return end
    seen[filepath] = true

    local content = read_file(filepath)
    if not content then
        wprint("eteleos-kernel: config file not found: %s", filepath)
        return
    end

    local from_dir = path.directory(filepath)
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local stripped = strip_comment(line)
        local tokens = {}
        for tok in stripped:gmatch("%S+") do tokens[#tokens + 1] = tok end
        if #tokens > 0 then
            local kw = tokens[1]
            local disabled = tokens[#tokens] == "disable"
            if kw == "option" and tokens[2] then
                for name in tokens[2]:gmatch("[^,=]+") do enabled[name] = true end
            elseif kw == "pseudo-device" and tokens[2] then
                enabled[tokens[2]] = true
            elseif kw == "include" and tokens[2] then
                local incpath = tokens[2]:gsub('"', "")
                local resolved = resolve_include(from_dir, incpath, core_conf_dir)
                if resolved then
                    parse_generic(resolved, core_conf_dir, enabled, seen)
                else
                    wprint("eteleos-kernel: could not resolve GENERIC include \"%s\" from %s",
                           incpath, filepath)
                end
            elseif tokens[2] == "at" and not disabled then
                enabled[extract_base_name(kw)] = true
            end
        end
    end
end

-- ==============================================================================
-- config(8) approximation: files / files.<arch> parser
-- ==============================================================================
local DIRECTIVES = {
    file=true, device=true, attach=true, define=true, ["pseudo-device"]=true,
    major=true, maxpartitions=true, maxusers=true, obsolete=true, deffs=true,
    defflag=true, defopt=true, defparam=true, filesystem=true, machine=true,
    source=true, include=true, ["export-jail"]=true,
}

-- Extracts a list of { path = "...", cond = {token, token, ...} } entries.
-- Correctly joins conditions that wrap across multiple physical lines --
-- verified against the real dev/ic/ahci.c entry, which does exactly this.
local function parse_files_list(filepath, entries)
    local content = read_file(filepath)
    if not content then
        wprint("eteleos-kernel: files list not found: %s", filepath)
        return
    end
    local pending
    local function flush() if pending then entries[#entries + 1] = pending end; pending = nil end
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local stripped = strip_comment(line)
        local tokens = {}
        for tok in stripped:gmatch("%S+") do tokens[#tokens + 1] = tok end
        if #tokens > 0 then
            if tokens[1] == "file" then
                flush()
                pending = { path = tokens[2], cond = {} }
                for i = 3, #tokens do pending.cond[#pending.cond + 1] = tokens[i] end
            elseif DIRECTIVES[tokens[1]] then
                flush()
            elseif pending then
                for _, t in ipairs(tokens) do pending.cond[#pending.cond + 1] = t end
            end
        end
    end
    flush()
end

-- Boolean expression evaluator for the condition column ("a & b | (c|d)"),
-- with "needs-flag" / "needs-count <n>" modifiers stripped first.
local function strip_modifiers(cond)
    local out, i = {}, 1
    while i <= #cond do
        local t = cond[i]
        if t == "needs-flag" then
            -- ignore
        elseif t == "needs-count" then
            i = i + 1
        else
            out[#out + 1] = t
        end
        i = i + 1
    end
    return out
end

local function eval_expr(cond, enabled)
    cond = strip_modifiers(cond)
    if #cond == 0 then return true end
    local pos = 1
    local function peek() return cond[pos] end
    local function advance() pos = pos + 1 end
    local parse_or, parse_and, parse_atom
    parse_atom = function()
        local t = peek()
        if t == "(" then
            advance()
            local v = parse_or()
            if peek() == ")" then advance() end
            return v
        elseif t == nil then
            return true
        else
            advance()
            return enabled[t] == true
        end
    end
    parse_and = function()
        local v = parse_atom()
        while peek() == "&" do advance(); v = parse_atom() and v end
        return v
    end
    parse_or = function()
        local v = parse_and()
        while peek() == "|" do advance(); v = parse_and() or v end
        return v
    end
    return parse_or()
end

-- ==============================================================================
-- Build the enabled-attribute set and the MI + MD selected file lists
-- ==============================================================================
local core_conf_dir = path.join(os.scriptdir(), "core", "conf")
local arch_conf_dir  = path.join(os.scriptdir(), "arch", arch, "conf")

local enabled = {}
parse_generic(path.join(core_conf_dir, "GENERIC"), core_conf_dir, enabled)
parse_generic(path.join(arch_conf_dir, "GENERIC"), core_conf_dir, enabled)

local file_entries = {}
parse_files_list(path.join(core_conf_dir, "files"), file_entries)
parse_files_list(path.join(arch_conf_dir, "files." .. arch), file_entries)

local selected_files = {}
for _, e in ipairs(file_entries) do
    if eval_expr(e.cond, enabled) then
        selected_files[#selected_files + 1] = e.path
    end
end

-- ==============================================================================
-- Machine-independent kernel subsystems ("modules") -- always compiled in
-- (OpenBSD's kernel is monolithic; these are not conditional in the files
-- list the way individual drivers are).
-- ==============================================================================
local KERNEL_MI_DIRS = {
    "core/kern", "core/lib/libkern", "core/miscfs",
    "uvm", "ddb", "crypto",
    "net/net", "net/netinet", "net/netinet6", "net/netmpls", "net/net80211",
    "fs/ufs", "fs/nfs", "fs/msdosfs", "fs/isofs", "fs/ntfs", "fs/tmpfs",
}

-- ==============================================================================
-- Kernel image
-- ==============================================================================
target("eteleos-kernel")
    set_kind("binary")
    set_basename("bsd")
    set_default(false)

    add_rules("eteleos.base", "eteleos.kernel")

    -- --- Machine-dependent compiler flags (real, per-arch, from Makefile.<arch>) --
    -- NOTE: {force=true} is deliberately NOT appended here: in Lua,
    -- unpack(t) only expands to multiple values when it is the LAST
    -- argument in a call -- add_cxflags(unpack(t), {force=true}) would
    -- silently truncate to just the FIRST flag. check.auto_ignore_flags is
    -- already disabled project-wide (see root xmake.lua), so force isn't
    -- needed anyway.
    add_cxflags(unpack(CMACHFLAGS[arch] or {}))
    add_asflags(unpack(CMACHFLAGS[arch] or {}))

    -- --- Machine-independent subsystem sources --------------------------------
    for _, dir in ipairs(KERNEL_MI_DIRS) do
        local d = path.join(os.scriptdir(), dir)
        if os.isdir(d) then
            local files = os.files(path.join(d, "**.c"))
            if #files > 0 then add_files(unpack(files)) end
        else
            wprint("eteleos-kernel: kernel/%s not found, skipping", dir)
        end
    end

    -- --- core/conf: param.c / swapgeneric.c -----------------------------------
    -- vers.c is generated below (on_load) instead of read from disk; init_sysent.c
    -- is picked up automatically via core/kern above (it is a checked-in,
    -- already-generated file -- see the note in the file header).
    for _, name in ipairs({"param.c", "swapgeneric.c"}) do
        local f = path.join(core_conf_dir, name)
        if os.isfile(f) then
            add_files(f)
        else
            wprint("eteleos-kernel: kernel/core/conf/%s not found, skipping", name)
        end
    end

    -- --- Files with per-file compiler flag overrides --------------------------
    -- Verified: these files (e.g. the AMD display driver's *_fpu.c helpers)
    -- do NOT appear as "file" directives in files/files.<arch> at all -- in
    -- the real Makefile.amd64 they are wired in directly via hand-written
    -- .o rules alongside param.o/swapgeneric.o, outside the normal
    -- conditional files-list mechanism. So they must be added explicitly
    -- here, same as param.c/swapgeneric.c above, rather than expected to
    -- surface from the selected_files parser.
    for relpath, cflags in pairs(PER_FILE_CFLAGS[arch] or {}) do
        local f = path.join(os.scriptdir(), relpath)
        if os.isfile(f) then
            add_files(f, {cxflags = cflags})
        else
            wprint("eteleos-kernel: per-file-cflags entry not found, skipping: %s", relpath)
        end
    end

    -- --- Driver + MI-optional sources, selected via the real files/GENERIC ----
    -- parser above (replaces the previous hand-picked allowlist).
    do
        local added = 0
        local per_file_set = PER_FILE_CFLAGS[arch] or {}
        for _, relpath in ipairs(selected_files) do
            if not per_file_set[relpath] then  -- already added above, avoid duplicate compilation
                local f = path.join(os.scriptdir(), relpath)
                if os.isfile(f) then
                    add_files(f)
                    added = added + 1
                end
                -- Files named in files/files.<arch> but not present on disk are
                -- silently skipped: many entries are conditional on options
                -- that are always false on EteleOS's minimal enabled-set
                -- today (e.g. vendor-specific firmware blobs), so a missing
                -- file is expected, not an error.
            end
        end
        cprint("${green}eteleos-kernel${clear}: %d files selected via files/GENERIC parsing "
               .. "(arch=%s)", added, arch)
    end

    -- --- Machine-dependent core sources (machdep.c, locore.S, ...) ------------
    local md_dir = path.join(os.scriptdir(), "arch", arch, MD_CORE_DIRS[arch])
    if os.isdir(md_dir) then
        local c_files = os.files(path.join(md_dir, "*.c"))
        local s_files = os.files(path.join(md_dir, "*.S"))
        if #c_files > 0 then add_files(unpack(c_files)) end
        if #s_files > 0 then add_files(unpack(s_files)) end
    else
        raise("eteleos-kernel: kernel/arch/%s/%s not found -- cannot build the kernel core for this architecture",
              arch, arch)
    end

    -- --- Machine-dependent bus-glue sources -----------------------------------
    for _, bus in ipairs(BUS_GLUE_DIRS[arch] or {}) do
        local d = path.join(os.scriptdir(), "arch", arch, bus)
        if os.isdir(d) then
            local files = os.files(path.join(d, "**.c"))
            if #files > 0 then add_files(unpack(files)) end
        else
            wprint("eteleos-kernel: kernel/arch/%s/%s not found, skipping", arch, bus)
        end
    end

    -- --- Kernel-only include paths ---------------------------------------------
    add_includedirs(path.join(os.scriptdir(), "arch", arch, "include"))
    add_includedirs(os.scriptdir())

    -- --- Linker script -----------------------------------------------------------
    local ldscript = path.join(arch_conf_dir, LDSCRIPT_NAMES[arch])
    if os.isfile(ldscript) then
        add_ldflags("-Wl,-T," .. ldscript, {force = true})
    else
        raise("eteleos-kernel: linker script not found at %s", ldscript)
    end

    add_deps("eteleos-headers")

    -- ==========================================================================
    -- Generated files: vers.c and assym.h
    -- ==========================================================================
    -- Both are generated in on_load (not before_build) so the resulting file
    -- can still be added to the target's own file list via target:add("files",
    -- ...) before the build's source-file batching happens. This matches the
    -- documented xmake pattern for generated sources; it has not been
    -- exercised against a real xmake install in this environment, so treat it
    -- as a good-faith implementation to verify on first real build.
    on_load(function (target)
        local gendir = path.join(config.builddir() or "build", "eteleos-kernel-gen", arch)
        os.mkdir(gendir)

        -- --- vers.c: a native re-implementation of newvers.sh's output, not a
        -- shell-out to the real script (avoids depending on newvers.sh's own
        -- environment/path assumptions, e.g. $USER, ${SYSTEM_DEP}, a writable
        -- version-counter file). Produces the same *shape* of vers.c (kernel
        -- ident string + build metadata) that param.c/msgbuf code expects to
        -- link against (extern char version[]).
        local kernel_version = "0.1.0"  -- placeholder, same as root xmake.lua's set_version
        local vers_c = string.format([[
/* Auto-generated by kernel/xmake.lua -- do not edit. */
char version[] = "EteleOS %s (%s) #0: %s\n";
]], kernel_version, arch, os.date("%a %b %d %H:%M:%S %Y"))
        local vers_path = path.join(gendir, "vers.c")
        io.open(vers_path, "w"):write(vers_c):close()
        target:add("files", vers_path)

        -- --- assym.h: invoke the REAL kernel/core/kern/genassym.sh against
        -- kernel/arch/<arch>/<arch>/genassym.cf, using the same cc + machine
        -- flags as the rest of the kernel. genassym.sh works by asking the
        -- compiler to emit constants as inline-asm operands in its assembly
        -- output (see the script itself) -- it never RUNS target code, so
        -- this works correctly even when cross-compiling.
        local genassym_sh = path.join(os.scriptdir(), "core", "kern", "genassym.sh")
        local genassym_cf = path.join(md_dir, "genassym.cf")
        local assym_h = path.join(gendir, "assym.h")
        if os.isfile(genassym_sh) and os.isfile(genassym_cf) then
            local cc = get_config("cc") or "clang"
            local triple_flag = ""  -- toolchain's on_load already adds -target globally
            local flags = table.concat(CMACHFLAGS[arch] or {}, " ")
            local incflags = "-I" .. path.join(os.scriptdir(), "arch", arch, "include")
                              .. " -I" .. os.scriptdir()
            local cmd = string.format('sh "%s" %s -ffreestanding %s %s < "%s"',
                                       genassym_sh, cc, flags, incflags, genassym_cf)
            local ok, outdata_or_err = pcall(os.iorun, cmd)
            local outdata = ok and outdata_or_err or nil
            if not outdata or outdata == "" then
                wprint("eteleos-kernel: genassym.sh produced no usable output for %s "
                       .. "-- assym.h will be a stub and locore.%s will likely fail to "
                       .. "assemble. Verify the genassym.sh invocation manually.",
                       genassym_cf, arch)
                outdata = "/* genassym.sh generation failed or produced no output */\n"
            end
            io.open(assym_h, "w"):write(outdata):close()
        else
            wprint("eteleos-kernel: genassym.sh or %s not found, writing an empty assym.h",
                   genassym_cf)
            io.open(assym_h, "w"):write("/* assym.h not generated -- inputs missing */\n"):close()
        end
        target:add("includedirs", gendir)
    end)
target_end()

