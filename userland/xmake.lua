--[[
================================================================================
 EteleOS: userland/xmake.lua, time write: 2026/07/18
 This file uses the Apache-2.0 license
================================================================================

Manages: applications, commands, daemons, utilities, services -- every
individual program under userland/ (verified categories: development,
essential/{bin,sbin}, games, libexec, multimedia, network, package, security,
system, utilities -- 565 build units as of the current tree; see
tools/gen/gen_userland_manifest.lua for how that number is produced).

ARCHITECTURE CHANGE IN THIS REVISION -- discovery moved out of this file
-------------------------------------------------------------------------
Confirmed against a real xmake v3.0.9 build (not just documentation): io,
import, pcall, os.iorun and os.exec are ALL nil at xmake.lua description
scope -- only a small read-only allowlist (os.getenv, os.isfile, os.isdir,
os.files, os.dirs, os.filedirs, ...) is available there. See
docs.xmake.io/api/scripts/builtin-modules/import.html ("most module
interfaces can only be used in the script domain") -- this is xmake's
long-standing scope model, not a 3.0-specific change, so the previous
revision of this file (which called io.open() and os.iorun() directly at
top level to parse each program's Makefile and to walk SUBDIR= chains)
could not actually have loaded under a real xmake binary, at any version.

The Makefile-parsing and directory-walking logic itself was already
correct -- only WHERE it ran was the problem. It has been relocated,
essentially unchanged, to tools/gen/gen_userland_manifest.lua, which runs
via `xmake lua` (confirmed: io/os.iorun/import are all real there) and
writes its result to generated_manifest.lua as a plain
ETELEOS_USERLAND_MANIFEST global-table assignment -- no xmake API calls in
that file, so `includes()` (confirmed: shares plain Lua globals with its
caller, though it does not propagate a `return` value) can hand it back
here safely. This file then does nothing but iterate that table and call
eteleos_program(), which is otherwise the exact same function as before
(target()/add_files()/add_installfiles()/on_load()/after_install() were
never the problem -- they are all real description- and script-scope APIs).

Regenerate generated_manifest.lua with:
    xmake lua tools/gen/gen_userland_manifest.lua
whenever userland/ Makefiles or directory layout change (also wired up as
the `eteleos-regen-userland` task in tools/tasks.lua). The output is
committed to the repo, the same way a `configure` script or generated
protobuf code would be -- description scope cannot regenerate it itself,
so it has to already be correct at `xmake f` time.

WHAT THIS FILE (VIA THE GENERATOR) PARSES OUT OF EACH PROGRAM'S OWN
MAKEFILE (real, verified; unchanged from the previous revision)
--------------------------------------------------------------------------
  PROG=            program name (falls back to the directory name if absent)
  SRCS=            explicit source list, when given (falls back to a
                    recursive *.c/*.S/*.cc glob otherwise)
  LDADD(+)?=       "-lxxx" tokens -> add_deps("lib<xxx>-shared")
                    (verified: httpd, bgpd, openssl)
  MAN=             man page files -> installed under share/man/manN,
                    section taken from each file's own extension
  BINOWN= / BINMODE=  install owner + mode, including setuid (verified:
                    doas BINMODE=4555, ping BINMODE=4555 -- both real
                    setuid-root programs, flagged loudly, not silently
                    applied)
  MLINKS=          extra install hardlinks (parsed defensively; NO real
                    usage of this variable was found anywhere in the
                    current userland/ tree, so this path is exercised by
                    nothing today)

GENERATED SOURCES (best-effort, tool-checked)
----------------------------------------------
  *.y (yacc/bison), *.l (lex/flex): verified real, 53 + 8 files across
    userland (e.g. httpd/parse.y, security/doas/parse.y,
    utilities/mklocale/{lex.l,yacc.y}).
  *.x (rpcgen): verified real but rare -- only 3 files found
    (system/amd/rpcx/{amq,nfs_prot}.x, system/ypserv/ypserv/ypv1.x).
    rpcgen conventionally emits MULTIPLE files per .x (_clnt.c, _svc.c,
    _xdr.c, a header); this implementation is a reasonable best-effort
    invocation, not a byte-verified replica of every rpcgen flag each of
    those 3 Makefiles actually uses.

HOST-BUILD vs CROSS-BUILD
---------------------------
  Two programs here are needed as HOST-native build-time tools, not (only)
  as target-arch binaries: userland/system/config (the config(8) tool --
  see the ioconf.c/ generation gap noted in kernel/xmake.lua) and
  userland/utilities/mklocale (needed by resources/xmake.lua's own
  find_tool("mklocale") step). Both are still built as normal target-arch
  programs by the discovery loop below AND separately declared as
  HOST_TOOL_DIRS (in the generator), built a second time with the plain
  host toolchain (no -target cross flag) so they can actually run during
  this build. Wiring the rest of the tree to actually USE these host
  binaries (rather than just building them) is not done here -- see the
  gap notes in kernel/xmake.lua and resources/xmake.lua.

REMAINING KNOWN LIMITATIONS
----------------------------------
  - BINOWN/BINMODE are applied via a best-effort chmod/chown in
    after_install; chown only succeeds when the install itself runs as
    root, exactly like the original Makefiles' behavior.
  - The cross-program tic/tset/tput/infocmp dependency and PROGS= handling
    (network/smtpd/mail/Makefile) are unchanged in behavior from the
    previous revision -- only relocated into the generator. See
    tools/gen/gen_userland_manifest.lua for the up-to-date verification
    notes on those.
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

-- ==============================================================================
-- Small utilities still needed HERE (build-time, not discovery-time)
-- ==============================================================================
local function basename_noext(filepath)
    local name = filepath:match("([^/]+)$") or filepath
    return (name:gsub("%.[^.]+$", ""))
end

-- Resolve a path the generator stored relative to userland/ back to an
-- absolute one for this machine's actual checkout.
local function abspath(rel)
    return path.join(os.scriptdir(), rel)
end

-- ==============================================================================
-- Generated-source handling (yacc/lex/rpcgen), shared by every program --
-- unchanged: this was already entirely on_load-scoped (script scope), where
-- import()/os.execv() genuinely do work.
-- ==============================================================================
local function is_fresh(outc, srcfile)
    return os.isfile(outc) and os.isfile(srcfile) and os.mtime(outc) >= os.mtime(srcfile)
end

local function wire_generated_sources(target_name, progdir, y_files, l_files, x_files)
    if #y_files == 0 and #l_files == 0 and #x_files == 0 then return end
    on_load(function (target)
        import("lib.detect.find_tool")
        local gendir = path.join(os.projectdir(), "build", "eteleos-userland-gen", target:name())
        os.mkdir(gendir)

        for _, yfile in ipairs(y_files) do
            local outc = path.join(gendir, basename_noext(yfile) .. ".c")
            if is_fresh(outc, yfile) then
                target:add("files", outc)
            else
                local yacc = find_tool("bison") or find_tool("yacc")
                if yacc then
                    if os.execv(yacc.program, {"-o", outc, yfile}, {try = true}) then
                        target:add("files", outc)
                    else
                        wprint("eteleos-userland: %s: bison/yacc failed on %s", target:name(), yfile)
                    end
                else
                    wprint("eteleos-userland: %s: no bison/yacc found, skipping %s", target:name(), yfile)
                end
            end
        end

        for _, lfile in ipairs(l_files) do
            local outc = path.join(gendir, basename_noext(lfile) .. ".c")
            if is_fresh(outc, lfile) then
                target:add("files", outc)
            else
                local lex = find_tool("flex") or find_tool("lex")
                if lex then
                    if os.execv(lex.program, {"-o", outc, lfile}, {try = true}) then
                        target:add("files", outc)
                    else
                        wprint("eteleos-userland: %s: flex/lex failed on %s", target:name(), lfile)
                    end
                else
                    wprint("eteleos-userland: %s: no flex/lex found, skipping %s", target:name(), lfile)
                end
            end
        end

        for _, xfile in ipairs(x_files) do
            local base = basename_noext(xfile)
            local all_cached = is_fresh(path.join(gendir, base .. "_clnt.c"), xfile)
                and is_fresh(path.join(gendir, base .. "_svc.c"), xfile)
                and is_fresh(path.join(gendir, base .. "_xdr.c"), xfile)
            if all_cached then
                for _, suffix in ipairs({"_clnt.c", "_svc.c", "_xdr.c"}) do
                    target:add("files", path.join(gendir, base .. suffix))
                end
                target:add("includedirs", gendir)
            else
                local rpcgen = find_tool("rpcgen")
                if rpcgen then
                    -- rpcgen's usual output set: <base>_clnt.c, <base>_svc.c,
                    -- <base>_xdr.c and <base>.h -- generated into gendir and
                    -- added if rpcgen actually produced them (best-effort: not
                    -- every .x file uses all four, e.g. header-only .x files).
                    os.execv(rpcgen.program, {"-h", "-o", path.join(gendir, base .. ".h"), xfile}, {try = true})
                    for _, suffix in ipairs({"_clnt.c", "_svc.c", "_xdr.c"}) do
                        local outc = path.join(gendir, base .. suffix)
                        local flag = (suffix == "_clnt.c" and "-l") or (suffix == "_svc.c" and "-m") or "-c"
                        if os.execv(rpcgen.program, {flag, "-o", outc, xfile}, {try = true}) then
                            target:add("files", outc)
                        end
                    end
                    target:add("includedirs", gendir)
                else
                    wprint("eteleos-userland: %s: rpcgen not found, skipping %s", target:name(), xfile)
                end
            end
        end
    end)
end

-- ==============================================================================
-- Install permissions (BINOWN/BINMODE/BINGRP), applied best-effort --
-- unchanged: already entirely after_install-scoped.
-- ==============================================================================
local function wire_install_perms(info)
    if not (info.binmode or info.binown or info.bingrp) then return end
    after_install(function (target)
        local installed = path.join(get_config("installdir") or "build/install",
                                     "bin", target:basename() or target:name())
        if info.binmode then
            local is_setuid = info.binmode:match("^[24]") ~= nil
            if is_setuid then
                cprint("${yellow}eteleos-userland${clear}: %s installs SETUID (mode %s, owner %s) -- "
                       .. "review before shipping", target:name(), info.binmode, info.binown or "?")
            end
            os.execv("chmod", {info.binmode, installed}, {try = true})
        end
        if info.binown then
            -- Only succeeds when the install itself runs as root, exactly
            -- like the original BSD Makefiles' own chown behavior.
            os.execv("chown", {info.bingrp and (info.binown .. ":" .. info.bingrp) or info.binown, installed},
                      {try = true})
        end
    end)
end

-- ==============================================================================
-- Man page install -- unchanged: add_installfiles() is description-scope-safe.
-- ==============================================================================
local function wire_man_pages(progdir, man_files)
    if #man_files == 0 then return end
    for _, m in ipairs(man_files) do
        local section = m:match("%.(%d%w*)$")
        if section then
            add_installfiles(path.join(progdir, m), {prefixdir = "share/man/man" .. section:sub(1, 1)})
        end
    end
end

-- ==============================================================================
-- Define one userland program. UNCHANGED from the previous revision except:
-- `info` is now a parameter (pre-parsed by the generator) instead of being
-- computed here via parse_program_makefile(progdir); and opts.extra_includedirs
-- / opts.extra_srcdirs / opts.gen_termsort now hold paths relative to
-- userland/ (resolved here via abspath()) instead of pre-resolved absolutes,
-- since the generator cannot know this machine's checkout path.
-- ==============================================================================
local function eteleos_program(target_name, progdir, opts, info)
    opts = opts or {}

    local portable_files, y_files, l_files, x_files

    if opts.explicit_srcs then
        -- PROGS= caller: exactly one source file, already resolved (path
        -- relative to userland/, from the generator).
        portable_files = {}
        for _, f in ipairs(opts.explicit_srcs) do portable_files[#portable_files + 1] = abspath(f) end
        y_files, l_files, x_files = {}, {}, {}
    else
        local c_files  = os.files(path.join(progdir, "**.c"))
        local cc_files = os.files(path.join(progdir, "**.cc"))
        local cxx_files = os.files(path.join(progdir, "**.cpp"))
        local s_files  = os.files(path.join(progdir, "*.S"))
        y_files  = os.files(path.join(progdir, "*.y"))
        l_files  = os.files(path.join(progdir, "*.l"))
        x_files  = os.files(path.join(progdir, "*.x"))

        -- Prefer the Makefile's own explicit SRCS= list when present (it is
        -- the ground truth for which files actually belong to this program,
        -- e.g. excluding test helpers or including only a subset of a shared
        -- directory); otherwise fall back to the glob above.
        portable_files = {}
        if info.found and #info.srcs > 0 then
            for _, f in ipairs(info.srcs) do
                if not f:match("%.[yl]$") and not f:match("%.x$") then
                    local full = path.join(progdir, f)
                    if not os.isfile(full) then
                        -- Fall back to the parent directory (".PATH:
                        -- ${.CURDIR}/.." is a common real pattern for
                        -- small wrapper directories whose own sources
                        -- actually live one level up), then any caller-
                        -- supplied extra directories (a handful of
                        -- programs pull one file from a specific sibling
                        -- directory instead -- see MODULE_TIC_DEPS in the
                        -- generator).
                        local parent_full = path.join(progdir, "..", f)
                        if os.isfile(parent_full) then
                            full = parent_full
                        else
                            for _, extra_dir in ipairs(opts.extra_srcdirs or {}) do
                                local candidate = path.join(abspath(extra_dir), f)
                                if os.isfile(candidate) then full = candidate; break end
                            end
                        end
                    end
                    if os.isfile(full) then portable_files[#portable_files + 1] = full end
                end
            end
        else
            for _, f in ipairs(c_files)  do portable_files[#portable_files + 1] = f end
            for _, f in ipairs(cc_files) do portable_files[#portable_files + 1] = f end
            for _, f in ipairs(cxx_files) do portable_files[#portable_files + 1] = f end
            for _, f in ipairs(s_files)  do portable_files[#portable_files + 1] = f end
        end
    end

    if #portable_files == 0 and #y_files == 0 and #l_files == 0 and #x_files == 0 then
        -- Script-only program (SCRIPTS=, no compiled sources at all).
        if info.found and #info.scripts > 0 then
            for _, s in ipairs(info.scripts) do
                add_installfiles(path.join(progdir, s), {prefixdir = "bin"})
            end
            print(string.format("eteleos-userland: %s installed as a script (SCRIPTS=), nothing compiled",
                  target_name))
        end
        return
    end

    ETELEOS_DECLARED_USERLAND = ETELEOS_DECLARED_USERLAND or {}
    ETELEOS_DECLARED_USERLAND[target_name] = true

    target(target_name)
        set_kind("binary")
        set_default(false)

        add_rules("eteleos.base", opts.static and "eteleos.userland_static" or "eteleos.userland",
                   "eteleos.strip_release")
        if #portable_files > 0 then add_files(unpack(portable_files)) end
        add_includedirs(progdir)
        if info.found then add_includedirs(path.join(progdir, "..")) end
        for _, d in ipairs(opts.extra_includedirs or {}) do add_includedirs(abspath(d)) end
        add_deps("eteleos-headers")

        if opts.host then
            -- Host-native build tool: escape the project-wide cross
            -- toolchain default so this actually runs on the build host.
            set_toolchains("clang", "gcc")
        end

        for _, libname in ipairs(info.ldadd_libs) do
            if ETELEOS_DECLARED_LIBRARIES and ETELEOS_DECLARED_LIBRARIES[libname] then
                add_deps("lib" .. libname .. "-shared")
            else
                print(string.format("eteleos-userland: %s: LDADD -l%s has no matching library "
                      .. "target (not yet built for this arch), linking without it",
                      target_name, libname))
            end
        end

        wire_generated_sources(target_name, progdir, y_files, l_files, x_files)
        wire_install_perms(info)

        -- In PROGS= mode (opts.prog_name set), a shared MAN= list covers
        -- every binary in the directory (e.g. "mail.lmtp.8 mail.maildir.8
        -- ..." for PROGS="mail.lmtp mail.maildir ..." -- confirmed real:
        -- network/smtpd/mail/Makefile) -- only install the page(s) whose
        -- name actually matches this one binary.
        if opts.prog_name then
            local mine = {}
            for _, m in ipairs(info.man) do
                if m == opts.prog_name or m:match("^" .. opts.prog_name:gsub("%p", "%%%1") .. "%.%d+$") then
                    mine[#mine + 1] = m
                end
            end
            wire_man_pages(opts.man_dir or progdir, mine)
        else
            wire_man_pages(progdir, info.man)
        end

        if opts.gen_termsort then
            -- tic/tset/tput/infocmp cross-dependency (see the generator's
            -- MODULE_TIC_DEPS). Confirmed real (infocmp/Makefile,
            -- tput/Makefile):
            --   termsort.h: ${TIC}/MKtermsort.sh
            --       sh ${TIC}/MKtermsort.sh awk ${CURSES}/Caps > ${.TARGET}
            local tic_dir = abspath(opts.gen_termsort.tic_dir)
            local curses_dir = abspath(opts.gen_termsort.curses_dir)
            on_load(function (target)
                import("lib.detect.find_tool")
                local gendir = path.join(os.projectdir(), "build",
                                          "eteleos-userland-gen", target_name)
                os.mkdir(gendir)
                local termsort_h = path.join(gendir, "termsort.h")
                local mkscript = path.join(tic_dir, "MKtermsort.sh")
                local caps = path.join(curses_dir, "Caps")
                local sh = find_tool("sh")
                if not sh then
                    wprint("eteleos-userland: %s: no POSIX shell (sh) found -- "
                           .. "MKtermsort.sh needs one to run. On Windows, install "
                           .. "Git Bash, WSL, or MSYS2 and make sure its sh is on PATH; "
                           .. "on Linux/macOS this should already be present. "
                           .. "Skipping termsort.h for now.", target_name)
                elseif os.isfile(mkscript) and os.isfile(caps) then
                    local out = os.iorun(string.format('"%s" "%s" awk "%s"', sh.program, mkscript, caps))
                    if out and out ~= "" then
                    if type(io) == "table" and io.open then
                        local f = io.open(termsort_h, "w")
                        if f then f:write(out); f:close(); target:add("includedirs", gendir)
                        else wprint("eteleos-userland: %s: could not write termsort.h", target_name) end
                    else
                        wprint("eteleos-userland: %s: io unavailable, skipping termsort.h", target_name)
                    end
                    else
                        wprint("eteleos-userland: %s: MKtermsort.sh produced no output, "
                               .. "termsort.h will be missing", target_name)
                    end
                else
                    wprint("eteleos-userland: %s: MKtermsort.sh or Caps not found, "
                           .. "skipping termsort.h generation", target_name)
                end
            end)
        end
    target_end()
end

-- ==============================================================================
-- Consume the generated manifest (see file header). This is the ONLY thing
-- that replaces the previous eteleos_walk_dir()/eteleos_category() calls --
-- everything about WHICH programs exist and WHAT their Makefiles say was
-- already decided by tools/gen/gen_userland_manifest.lua.
-- ==============================================================================
includes("generated_manifest.lua")

if type(ETELEOS_USERLAND_MANIFEST) == "table" then
    for _, unit in ipairs(ETELEOS_USERLAND_MANIFEST) do
        eteleos_program(unit.target_name, abspath(unit.progdir_rel), unit.opts, unit.info)
    end
else
    print("eteleos-userland: generated_manifest.lua did not define ETELEOS_USERLAND_MANIFEST -- "
          .. "no userland programs will be built. Run: xmake lua tools/gen/gen_userland_manifest.lua")
end
