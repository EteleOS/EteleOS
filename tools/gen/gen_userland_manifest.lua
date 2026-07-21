--[[
================================================================================
 EteleOS: tools/gen/gen_userland_manifest.lua
 This file uses the Apache-2.0 license
================================================================================

WHY THIS FILE EXISTS
------------------------------------------------------
userland/xmake.lua needs to know, for ~900+ program directories, what each
one's own (still-unedited, pre-restructure-path) Makefile says: PROG=,
PROGS=, SUBDIR=, SRCS=, MAN=, LDADD=, MLINKS=, SCRIPTS=, BINOWN=/BINMODE=/
BINGRP=. Reading that requires io.open() and, for directory discovery,
either os.dirs() or a shell-out.

Confirmed against a real xmake v3.0.9 build (not just documentation): io,
import, pcall, dofile, require, os.iorun, os.exec and os.run are ALL nil at
xmake.lua description scope -- only a small read-only allowlist (os.getenv,
os.isfile, os.isdir, os.files, os.dirs, os.filedirs, ...) is available
there, matching docs.xmake.io/api/scripts/builtin-modules/import.html
("most module interfaces can only be used in the script domain"). This is
not a 3.0-specific regression -- it is xmake's long-standing scope model --
but it does mean this project's previous userland/xmake.lua (parsing
Makefiles with io.open() directly in its own top-level/description-scope
code) could never actually have loaded under a real xmake binary, at any
version.

The fix: parse everything HERE, in a plain script run via `xmake lua`
(confirmed: io/os.iorun/import are all real, working values in that
scope), and write the result out as a plain Lua data file --
userland/generated_manifest.lua -- containing nothing but a global table
assignment. userland/xmake.lua then does `includes("generated_manifest.lua")`
or `xmake lua` sees no other targets; only reads global table via includes.

Confirmed empirically: `includes("x.lua")` shares the caller's plain Lua
globals (a top-level `SOME_GLOBAL = {...}` assigned inside x.lua IS visible
in the includer afterwards), even though it does NOT propagate a `return`
value back to the caller.

REGENERATING
------------
Run this whenever userland/ Makefiles or directory layout change:
    xmake lua tools/gen/gen_userland_manifest.lua
(also wired up as the `eteleos-regen-userland` task in tools/tasks.lua, so
`xmake eteleos-regen-userland` works too once a project is configured).
The output, userland/generated_manifest.lua, is committed to the repo like
any other generated-but-tracked file (protobuf-generated code, `configure`
scripts, etc.) -- xmake.lua's description scope cannot regenerate it
itself, so it has to already be present and correct at `xmake f` time.

PARSING LOGIC
------------------
Ported as-is from the previous userland/xmake.lua (that logic was already
correct Lua -- only WHERE it ran was wrong). One real change:
list_subdirs() now uses os.dirs() instead of shelling out to `find` (os.dirs
is available in both script and description scope, is portable, and is the
same approach tests/xmake.lua's header already documented as correct for
exactly this reason -- this brings userland/ in line with that).
--------------------------------------------------------------------------------
--]]

local ROOT      = path.absolute(os.scriptdir() .. "/../..")     -- repo root, from tools/gen/
local USERLAND  = path.join(ROOT, "userland")

-- Programs that must additionally be built as HOST-native tools.
local HOST_TOOL_DIRS = {
    "system/config",
    "utilities/mklocale",
}

-- ==============================================================================
-- Small utilities (unchanged from the original userland/xmake.lua)
-- ==============================================================================
local function read_file(filepath)
    -- xmake's io.open raises a Lua error on a missing file instead of
    -- returning nil the way stock Lua's io.open does (confirmed by
    -- testing against the real tree: a plain missing Makefile is the
    -- overwhelmingly common case here, not an exceptional one). pcall
    -- itself turns out not to be available in this scope either
    -- (confirmed), so guard with os.isfile() first instead of catching
    -- the error after the fact.
    if not os.isfile(filepath) then return nil end
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

-- CHANGED: os.dirs() instead of os.iorun('find ...') -- portable, and
-- works in both script and description scope (matches tests/xmake.lua's
-- already-established convention).
local function list_subdirs(dir)
    local dirs = os.dirs(path.join(dir, "*"))
    table.sort(dirs)
    return dirs
end

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
-- Makefile parser -- unchanged from the original userland/xmake.lua
-- ==============================================================================
local function parse_program_makefile(dir)
    local info = {
        found = false, prog = nil, progs = {}, srcs = {}, man = {},
        ldadd_libs = {}, mlinks = {}, scripts = {}, subdirs = {},
        binown = nil, binmode = nil, bingrp = nil,
    }
    local content = read_file(path.join(dir, "Makefile"))
    if not content then return info end
    info.found = true

    for _, line in ipairs(logical_lines(content)) do
        local var, op, rest = line:match("^(%u[%u_]*)%s*([+:]?=)%s*(.*)$")
        if var then
            rest = rest:gsub("#.*$", "")
            if var == "PROG" then
                info.prog = rest:match("%S+")
            elseif var == "PROGS" then
                for name in rest:gmatch("%S+") do info.progs[#info.progs + 1] = name end
            elseif var == "SUBDIR" then
                for d in rest:gmatch("%S+") do info.subdirs[#info.subdirs + 1] = d end
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

local function resolve_prog_source(progdir, name)
    local local_path = path.join(progdir, name .. ".c")
    if os.isfile(local_path) then return local_path end
    local parent_path = path.join(progdir, "..", name .. ".c")
    if os.isfile(parent_path) then return parent_path end
    return nil
end

local TIC_DIR_REL    = "utilities/tic"                       -- relative to userland/
local CURSES_DIR_REL = "../libraries/extra/libcurses"        -- relative to userland/
local TIC_DIR    = path.join(USERLAND, TIC_DIR_REL)
local CURSES_DIR = path.join(USERLAND, CURSES_DIR_REL)
local MODULE_TIC_DEPS = {
    ["utilities/tic"]     = { termsort = false },
    ["utilities/tset"]    = { termsort = false },
    ["utilities/tput"]    = { termsort = true },
    ["utilities/infocmp"] = { termsort = true },
}

-- ==============================================================================
-- Discovery walk -- same shape as the original eteleos_walk_dir/
-- eteleos_category, but RECORDS build units into `UNITS` instead of calling
-- target()/target_end() (which are not available here -- and shouldn't be;
-- this script's only job is parsing, not declaring targets).
-- ==============================================================================
local UNITS = {}   -- flat list of build-unit descriptors, consumed by userland/xmake.lua
local stats = { programs = 0, script_only = 0, progs_groups = 0, subdir_dirs = 0, empty = 0 }

local function record_unit(target_name, progdir, opts, info)
    UNITS[#UNITS + 1] = {
        target_name = target_name,
        -- Relative to userland/ itself (NOT an absolute path, NOT
        -- relative to repo root) -- so userland/xmake.lua's consumer can
        -- resolve it with a plain path.join(os.scriptdir(), ...) on any
        -- machine, regardless of where the repo is checked out.
        progdir_rel = path.relative(progdir, USERLAND),
        opts = opts,
        info = info,
    }
    stats.programs = stats.programs + 1
end

local function walk_dir(dir, relpath, target_prefix, static)
    local info = parse_program_makefile(dir)

    if info.found and #info.subdirs > 0 and not info.prog and #info.progs == 0 then
        stats.subdir_dirs = stats.subdir_dirs + 1
        for _, sub in ipairs(info.subdirs) do
            local subdir = path.join(dir, sub)
            if os.isdir(subdir) then
                walk_dir(subdir, relpath .. "/" .. sub, target_prefix .. "-" .. sub, static)
            else
                print(string.format("eteleos-gen: %s: SUBDIR entry '%s' does not exist, skipping",
                      relpath, sub))
            end
        end
        return
    end

    if info.found and #info.progs > 0 and not info.prog then
        stats.progs_groups = stats.progs_groups + 1
        for _, name in ipairs(info.progs) do
            local src = resolve_prog_source(dir, name)
            if src then
                record_unit(target_prefix .. "-" .. name, dir, {
                    static = static,
                    explicit_srcs = { path.relative(src, USERLAND) },
                    prog_name = name,
                }, info)
            else
                print(string.format("eteleos-gen: %s: PROGS entry '%s' -- no %s.c found, skipping",
                      relpath, name, name))
            end
        end
        return
    end

    local tic_opts = MODULE_TIC_DEPS[relpath]
    local opts = { static = static }
    if tic_opts then
        opts.extra_includedirs = { TIC_DIR_REL, CURSES_DIR_REL }
        opts.extra_srcdirs = { TIC_DIR_REL }
        if tic_opts.termsort then
            opts.gen_termsort = { tic_dir = TIC_DIR_REL, curses_dir = CURSES_DIR_REL }
        end
    end

    -- Only record a unit if there is something to build or install (mirrors
    -- the original eteleos_program()'s own early-return for a genuinely
    -- empty directory -- script-only dirs ARE still recorded, since
    -- userland/xmake.lua's consumer still needs to install info.scripts).
    local has_content = (#info.srcs > 0) or info.found == false  -- no Makefile => glob fallback, still record
        or #info.scripts > 0 or info.prog ~= nil
    if has_content or not info.found then
        record_unit(target_prefix, dir, opts, info)
    else
        stats.empty = stats.empty + 1
    end

    for _, hostdir in ipairs(HOST_TOOL_DIRS) do
        if hostdir == relpath then
            record_unit("host-" .. target_prefix:gsub("^userland%-", ""), dir, { host = true },
                        parse_program_makefile(dir))
        end
    end
end

local function walk_category(category, label, static)
    local catdir = path.join(USERLAND, category)
    if not os.isdir(catdir) then
        print(string.format("eteleos-gen: userland/%s not found, skipping", category))
        return
    end
    for _, progdir in ipairs(list_subdirs(catdir)) do
        local name = path.filename(progdir)
        walk_dir(progdir, category .. "/" .. name, "userland-" .. label .. "-" .. name, static)
    end
end

walk_category("development", "development")
walk_category("games",       "games")
walk_category("libexec",     "libexec")
walk_category("multimedia",  "multimedia")
walk_category("network",     "network")
walk_category("package",     "package")
walk_category("security",    "security")
walk_category("system",      "system")
walk_category("utilities",   "utilities")
walk_category("essential/bin",  "bin",  true)
walk_category("essential/sbin", "sbin", true)

-- ==============================================================================
-- Serialize UNITS to a plain Lua data file
-- ==============================================================================
local function lua_quote(s)
    return string.format("%q", s)
end

local function serialize(value, indent)
    indent = indent or ""
    local t = type(value)
    if t == "string" then
        return lua_quote(value)
    elseif t == "number" or t == "boolean" then
        return tostring(value)
    elseif t == "nil" then
        return "nil"
    elseif t == "table" then
        local parts = {}
        local is_array = #value > 0
        local inner = indent .. "    "
        if is_array then
            for _, v in ipairs(value) do
                parts[#parts + 1] = inner .. serialize(v, inner) .. ","
            end
        else
            local keys = {}
            for k in pairs(value) do keys[#keys + 1] = k end
            table.sort(keys, function(a, b) return tostring(a) < tostring(b) end)
            for _, k in ipairs(keys) do
                local v = value[k]
                parts[#parts + 1] = inner .. "[" .. lua_quote(tostring(k)) .. "] = " .. serialize(v, inner) .. ","
            end
        end
        if #parts == 0 then return "{}" end
        return "{\n" .. table.concat(parts, "\n") .. "\n" .. indent .. "}"
    else
        raise("eteleos-gen: cannot serialize value of type " .. t)
    end
end

local out = {}
out[#out + 1] = "--[[ AUTO-GENERATED by tools/gen/gen_userland_manifest.lua -- DO NOT EDIT BY HAND."
out[#out + 1] = "     Regenerate with: xmake lua tools/gen/gen_userland_manifest.lua"
out[#out + 1] = "     (or: xmake eteleos-regen-userland, once a project is configured) ]]"
out[#out + 1] = ""
out[#out + 1] = "ETELEOS_USERLAND_MANIFEST = " .. serialize(UNITS)
out[#out + 1] = ""

local outpath = path.join(USERLAND, "generated_manifest.lua")
local f = io.open(outpath, "w")
f:write(table.concat(out, "\n"))
f:close()

print(string.format(
    "eteleos-gen: userland manifest written to %s\n" ..
    "  %d build units (%d PROGS= groups, %d pure-SUBDIR dirs, %d empty dirs skipped)",
    outpath, stats.programs, stats.progs_groups, stats.subdir_dirs, stats.empty))
