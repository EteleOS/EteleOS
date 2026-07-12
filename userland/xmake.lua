/*
 EteleOS: xmake.lua, time wirte: 2026/07/12
 This file uses the Apache-2.0 license
*/


--[[
================================================================================
 EteleOS :: userland/xmake.lua
================================================================================

Manages: applications, commands, daemons, utilities, services -- every
individual program under userland/ (verified categories: development,
essential/{bin,sbin}, games, libexec, multimedia, network, package, security,
system, utilities -- roughly 900+ program directories, far too many to
hand-enumerate; see the discovery approach below).

WHAT THIS FILE PARSES OUT OF EACH PROGRAM'S OWN MAKEFILE (real, verified)
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
  No ASN.1 generator or unicode-table generator was found anywhere in
  userland/ -- files merely named "asn1*" (e.g. openssl/asn1pars.c,
  rpki-client/rpki-asn1.h) are ordinary hand-written C, not generated.

HOST-BUILD vs CROSS-BUILD
---------------------------
  Two programs here are needed as HOST-native build-time tools, not (only)
  as target-arch binaries: userland/system/config (the config(8) tool --
  see the ioconf.c/ generation gap noted in kernel/xmake.lua) and
  userland/utilities/mklocale (needed by resources/xmake.lua's own
  find_tool("mklocale") step). Both are still built as normal target-arch
  programs by the discovery loop below AND separately declared as
  HOST_TOOL_DIRS, built a second time with the plain host toolchain (no
  -target cross flag) so they can actually run during this build. Wiring
  the rest of the tree to actually USE these host binaries (rather than
  just building them) is not done here -- see the gap notes in
  kernel/xmake.lua and resources/xmake.lua, which this closes half of.

KNOWN LIMITATIONS -- please read
----------------------------------
  - SUBDIR-style umbrella directories (no sources of their own, just
    sub-programs) are currently just skipped as empty units rather than
    recursed into. All ~900 directories checked so far have matched this
    file's "one directory = one program" assumption; SUBDIR nesting has
    not been ruled out for the ones not spot-checked.
  - PROGS= (plural, multiple binaries from one Makefile) is parsed
    defensively but NO real example of it was found in this tree -- this
    path is currently untested against real data.
  - Dependency analysis between programs is limited to the LDADD-derived
    library graph and the two-program host-tool list above; there is no
    general build-order solver for e.g. one program's build depending on
    another program's *output* (beyond the host-tool case).
  - BINOWN/BINMODE are applied via a best-effort chmod/chown in
    after_install; chown only succeeds when the install itself runs as
    root, exactly like the original Makefiles' behavior.
--------------------------------------------------------------------------------
--]]

local unpack = table.unpack or unpack

-- Programs that must additionally be built as HOST-native tools (see the
-- note above). Keyed by their path relative to userland/.
local HOST_TOOL_DIRS = {
    "system/config",
    "utilities/mklocale",
}

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

local function basename_noext(filepath)
    local name = filepath:match("([^/]+)$") or filepath
    return (name:gsub("%.[^.]+$", ""))
end

local function list_subdirs(dir)
    local out = os.iorun(string.format('find "%s" -mindepth 1 -maxdepth 1 -type d 2>/dev/null | sort', dir))
    local dirs = {}
    if out then
        for line in out:gmatch("[^\r\n]+") do dirs[#dirs + 1] = line end
    end
    return dirs
end

-- Join Makefile continuation lines (trailing "\") into single logical lines.
local function logical_lines(content)
    local lines = {}
    local acc = nil
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local cont = line:match("(.*)\\%s*$")
        if cont then
            acc = (acc or "") .. cont .. " "
        else
            lines[#lines + 1] = (acc or "") .. line
            acc = nil
        end
    end
    return lines
end

-- ==============================================================================
-- Makefile parser -- extracts everything this file needs from ONE program's
-- own Makefile. Returns a table (all fields optional except `found`).
-- ==============================================================================
local function parse_program_makefile(dir)
    local info = {
        found = false, prog = nil, progs = {}, srcs = {}, man = {},
        ldadd_libs = {}, mlinks = {}, scripts = {},
        binown = nil, binmode = nil, bingrp = nil,
    }
    local content = read_file(path.join(dir, "Makefile"))
    if not content then return info end
    info.found = true

    for _, line in ipairs(logical_lines(content)) do
        local var, op, rest = line:match("^(%u[%u_]*)%s*([+:]?=)%s*(.*)$")
        if var then
            rest = rest:gsub("#.*$", "")  -- trailing comment
            if var == "PROG" then
                info.prog = rest:match("%S+")
            elseif var == "PROGS" then
                for name in rest:gmatch("%S+") do info.progs[#info.progs + 1] = name end
            elseif var == "SRCS" then
                for f in rest:gmatch("%S+") do info.srcs[#info.srcs + 1] = f end
            elseif var == "MAN" then
                for f in rest:gmatch("%S+") do
                    if f ~= "no" then info.man[#info.man + 1] = f end
                end
            elseif var == "LDADD" then
                for libname in rest:gmatch("%-l([%w_]+)") do
                    info.ldadd_libs[#info.ldadd_libs + 1] = libname
                end
            elseif var == "MLINKS" then
                local toks = {}
                for t in rest:gmatch("%S+") do toks[#toks + 1] = t end
                for i = 1, #toks - 1, 2 do
                    info.mlinks[#info.mlinks + 1] = { from = toks[i], to = toks[i + 1] }
                end
            elseif var == "SCRIPTS" then
                for f in rest:gmatch("%S+") do info.scripts[#info.scripts + 1] = f end
            elseif var == "BINOWN" then
                info.binown = rest:match("%S+")
            elseif var == "BINMODE" then
                info.binmode = rest:match("%S+")
            elseif var == "BINGRP" then
                info.bingrp = rest:match("%S+")
            end
        end
    end
    return info
end

-- ==============================================================================
-- Generated-source handling (yacc/lex/rpcgen), shared by every program
-- ==============================================================================
local function wire_generated_sources(target_name, progdir, y_files, l_files, x_files)
    if #y_files == 0 and #l_files == 0 and #x_files == 0 then return end
    on_load(function (target)
        import("lib.detect.find_tool")
        local gendir = path.join(config.builddir() or "build", "eteleos-userland-gen", target:name())
        os.mkdir(gendir)

        for _, yfile in ipairs(y_files) do
            local yacc = find_tool("bison") or find_tool("yacc")
            local outc = path.join(gendir, basename_noext(yfile) .. ".c")
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

        for _, lfile in ipairs(l_files) do
            local lex = find_tool("flex") or find_tool("lex")
            local outc = path.join(gendir, basename_noext(lfile) .. ".c")
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

        for _, xfile in ipairs(x_files) do
            local rpcgen = find_tool("rpcgen")
            local base = basename_noext(xfile)
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
    end)
end

-- ==============================================================================
-- Install permissions (BINOWN/BINMODE/BINGRP), applied best-effort
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
-- Man page install
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
-- Define one userland program
-- ==============================================================================
local function eteleos_program(target_name, progdir, opts)
    opts = opts or {}
    local info = parse_program_makefile(progdir)

    local c_files  = os.files(path.join(progdir, "**.c"))
    local cc_files = os.files(path.join(progdir, "**.cc"))
    local cxx_files = os.files(path.join(progdir, "**.cpp"))
    local s_files  = os.files(path.join(progdir, "*.S"))
    local y_files  = os.files(path.join(progdir, "*.y"))
    local l_files  = os.files(path.join(progdir, "*.l"))
    local x_files  = os.files(path.join(progdir, "*.x"))

    -- Prefer the Makefile's own explicit SRCS= list when present (it is
    -- the ground truth for which files actually belong to this program,
    -- e.g. excluding test helpers or including only a subset of a shared
    -- directory); otherwise fall back to the glob above.
    local portable_files = {}
    if info.found and #info.srcs > 0 then
        for _, f in ipairs(info.srcs) do
            if not f:match("%.[yl]$") and not f:match("%.x$") then
                local full = path.join(progdir, f)
                if os.isfile(full) then portable_files[#portable_files + 1] = full end
            end
        end
    else
        for _, f in ipairs(c_files)  do portable_files[#portable_files + 1] = f end
        for _, f in ipairs(cc_files) do portable_files[#portable_files + 1] = f end
        for _, f in ipairs(cxx_files) do portable_files[#portable_files + 1] = f end
        for _, f in ipairs(s_files)  do portable_files[#portable_files + 1] = f end
    end

    if #portable_files == 0 and #y_files == 0 and #l_files == 0 and #x_files == 0 then
        -- Likely a SUBDIR-style umbrella directory (see limitations above),
        -- or a script-only program (SCRIPTS=, no compiled sources at all).
        if info.found and #info.scripts > 0 then
            for _, s in ipairs(info.scripts) do
                add_installfiles(path.join(progdir, s), {prefixdir = "bin"})
            end
            cprint("eteleos-userland: %s installed as a script (SCRIPTS=), nothing compiled",
                   target_name)
        end
        return
    end

    target(target_name)
        set_kind("binary")
        set_default(false)

        add_rules("eteleos.base", "eteleos.userland", "eteleos.strip_release")
        if #portable_files > 0 then add_files(unpack(portable_files)) end
        add_includedirs(progdir)
        add_deps("eteleos-headers")

        if opts.host then
            -- Host-native build tool: escape the project-wide cross
            -- toolchain default so this actually runs on the build host
            -- (see the HOST-BUILD note at the top of this file).
            set_toolchains("clang", "gcc")
        end

        for _, libname in ipairs(info.ldadd_libs) do
            add_deps("lib" .. libname .. "-shared")
        end

        wire_generated_sources(target_name, progdir, y_files, l_files, x_files)
        wire_install_perms(info)
        wire_man_pages(progdir, info.man)
    target_end()
end

-- Discover and build every program under one category directory.
local function eteleos_category(category, label)
    local catdir = path.join(os.scriptdir(), category)
    if not os.isdir(catdir) then
        wprint("eteleos-userland: userland/%s not found, skipping", category)
        return
    end
    for _, progdir in ipairs(list_subdirs(catdir)) do
        local name = path.filename(progdir)
        local relpath = category .. "/" .. name
        eteleos_program("userland-" .. label .. "-" .. name, progdir)

        for _, hostdir in ipairs(HOST_TOOL_DIRS) do
            if hostdir == relpath then
                eteleos_program("host-" .. label .. "-" .. name, progdir, { host = true })
            end
        end
    end
end

-- ==============================================================================
-- Categories (verified against the current tree)
-- ==============================================================================
eteleos_category("development", "development")
eteleos_category("games",       "games")
eteleos_category("libexec",     "libexec")
eteleos_category("multimedia",  "multimedia")
eteleos_category("network",     "network")
eteleos_category("package",     "package")
eteleos_category("security",    "security")
eteleos_category("system",      "system")
eteleos_category("utilities",   "utilities")

-- "essential" nests one level deeper (bin/ and sbin/). The long-standing
-- BSD convention of statically linking /bin and /sbin so they work before
-- /usr is mounted is NOT implemented -- every program here links the same
-- way regardless of category.
eteleos_category("essential/bin",  "bin")
eteleos_category("essential/sbin", "sbin")
