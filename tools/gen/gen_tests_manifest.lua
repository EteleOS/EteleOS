--[[
================================================================================
 EteleOS: tools/gen/gen_tests_manifest.lua
 This file uses the Apache-2.0 license
================================================================================

Same reasoning as tools/gen/gen_userland_manifest.lua. tests/xmake.lua's own
parse_makefile() used io.open() directly, called from description scope --
confirmed nil there in a real xmake v3.0.9 run. The directory *discovery*
itself (find_test_dirs) already used os.files()/os.dirs(), which genuinely
do work at description scope, so that part is untouched and still lives in
tests/xmake.lua; only the Makefile-content parse is relocated here.

Regenerate with: xmake lua tools/gen/gen_tests_manifest.lua
whenever tests/ Makefiles or directory layout change.
--------------------------------------------------------------------------------
--]]

local ROOT  = path.absolute(os.scriptdir() .. "/../..")
local TESTS = path.join(ROOT, "tests")
local arch  = get_config("target_arch") or "amd64"

local TEST_CATEGORIES = {
    "bin", "sbin", "usr.bin", "usr.sbin", "lib", "libexec", "gnu",
    "include", "misc", "sys",
}
local KNOWN_INCLUDES = { ["bsd.regress.mk"] = true, ["bsd.subdir.mk"] = true }
local INTERPRETER_BY_EXT = { sh = "sh", py = "python3", pl = "perl", lua = "lua" }

-- ==============================================================================
-- Unchanged from the previous revision of tests/xmake.lua
-- ==============================================================================
local function read_file(filepath)
    if not os.isfile(filepath) then return nil end
    local f = io.open(filepath, "r")
    if not f then return nil end
    local c = f:read("*a")
    f:close()
    return c
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

local function find_test_dirs(dir)
    local seen, dirs = {}, {}
    local function add(d)
        if not seen[d] then seen[d] = true; dirs[#dirs + 1] = d end
    end
    for _, mf in ipairs(os.files(path.join(dir, "**", "Makefile"))) do
        add(path.directory(mf))
    end
    for ext in pairs(INTERPRETER_BY_EXT) do
        for _, sf in ipairs(os.files(path.join(dir, "**", "*." .. ext))) do
            add(path.directory(sf))
        end
    end
    table.sort(dirs)
    return dirs
end

local function expand_vars(value, vars)
    local unresolved = {}
    local result = value:gsub("%$[{(]([%w_.]+)[})]", function (name)
        if vars[name] ~= nil then return vars[name] end
        unresolved[#unresolved + 1] = name
        return "${" .. name .. "}"
    end)
    return result, unresolved
end

local function parse_makefile(dir)
    local content = read_file(path.join(dir, "Makefile"))
    if not content then return nil end

    local info = {
        prog = nil, progs = {}, srcs = {}, ldadd_libs = {},
        custom = false, dynamic_vars = {}, unknown_includes = {},
        targets = {},
        has_regress_targets_var = false,
    }
    local vars = {}

    for _, line in ipairs(logical_lines(content)) do
        local stripped = line:gsub("#.*$", ""):match("^%s*(.-)%s*$")
        if stripped ~= "" then
            local var, op, rest = stripped:match("^(%u[%u_]*)%s*([+?:!]?=)%s*(.*)$")
            if var and op ~= "!=" then
                if op == "+=" and vars[var] then
                    vars[var] = vars[var] .. " " .. rest
                elseif op == "?=" and vars[var] then
                    -- already set
                else
                    vars[var] = rest
                end
            elseif var and op == "!=" then
                info.dynamic_vars[#info.dynamic_vars + 1] = var
                vars[var] = vars[var] or ""
            end
        end
    end

    local if_stack = {}
    local function block_active()
        for _, v in ipairs(if_stack) do if not v then return false end end
        return true
    end

    local current_target = nil
    for _, line in ipairs(logical_lines(content)) do
        local stripped = line:gsub("#.*$", ""):match("^%s*(.-)%s*$")
        if stripped ~= "" then
            local ifcond = stripped:match("^%.%s*if%s+(.*)$")
            local var, op, rest = stripped:match("^(%u[%u_]*)%s*([+?:!]?=)%s*(.*)$")

            if ifcond then
                local machvar, cmpval = ifcond:match('%${(MACHINE_?A?R?C?H?)}%s*==%s*"([%w_]+)"')
                if machvar then
                    if_stack[#if_stack + 1] = (cmpval == arch)
                else
                    if_stack[#if_stack + 1] = true
                end
            elseif stripped:match("^%.%s*else") then
                if #if_stack > 0 then if_stack[#if_stack] = not if_stack[#if_stack] end
            elseif stripped:match("^%.%s*endif") then
                if #if_stack > 0 then table.remove(if_stack) end
            elseif stripped:match("^%.%s*include") then
                local inc = stripped:match("[<\"]([^>\"]+)[>\"]")
                if inc and not KNOWN_INCLUDES[path.filename(inc)] then
                    info.unknown_includes[#info.unknown_includes + 1] = inc
                end
            elseif block_active() and var and op ~= "!=" then
                local expanded, unresolved = expand_vars(rest, vars)
                if var == "PROG" then info.prog = expanded:match("%S+")
                elseif var == "PROGS" then
                    for n in expanded:gmatch("%S+") do info.progs[#info.progs + 1] = n end
                elseif var == "SRCS" then
                    for f in expanded:gmatch("%S+") do info.srcs[#info.srcs + 1] = f end
                elseif var == "LDADD" then
                    for lib in expanded:gmatch("%-l([%w_]+)") do
                        info.ldadd_libs[#info.ldadd_libs + 1] = lib
                    end
                elseif var == "REGRESS_TARGETS" then
                    info.has_regress_targets_var = true
                end
                current_target = nil
            elseif block_active() then
                local tname = stripped:match("^([%w_%-]+)%s*:")
                if tname then
                    current_target = tname
                    info.targets[tname] = info.targets[tname] or { recipe_lines = {} }
                    info.custom = true
                elseif current_target and stripped:match("^@?[%w./${}%-]") then
                    table.insert(info.targets[current_target].recipe_lines, stripped)
                else
                    info.custom = true
                end
            end
        end
    end

    return info
end

-- ==============================================================================
-- Walk every category, parse every discovered testdir's Makefile (if any)
-- ==============================================================================
local MANIFEST = {}   -- testdir_rel (relative to tests/) -> info table, or a
                       -- table with has_makefile=false for script-only dirs
local stats = { with_makefile = 0, script_only = 0 }

for _, category in ipairs(TEST_CATEGORIES) do
    local catdir = path.join(TESTS, category)
    if os.isdir(catdir) then
        for _, testdir in ipairs(find_test_dirs(catdir)) do
            local rel = path.relative(testdir, TESTS)
            local info = parse_makefile(testdir)
            if info then
                info.has_makefile = true
                MANIFEST[rel] = info
                stats.with_makefile = stats.with_makefile + 1
            else
                MANIFEST[rel] = { has_makefile = false }
                stats.script_only = stats.script_only + 1
            end
        end
    else
        print(string.format("eteleos-gen-tests: tests/%s not found, skipping", category))
    end
end

print(string.format("eteleos-gen-tests: %d dirs with a Makefile, %d script-only (arch=%s)",
      stats.with_makefile, stats.script_only, arch))

-- ==============================================================================
-- Serialize
-- ==============================================================================
local function lua_quote(s) return string.format("%q", s) end

local function serialize(value, indent)
    indent = indent or ""
    local t = type(value)
    if t == "string" then return lua_quote(value)
    elseif t == "number" or t == "boolean" then return tostring(value)
    elseif t == "nil" then return "nil"
    elseif t == "table" then
        local parts = {}
        local is_array = #value > 0
        local inner = indent .. "    "
        if is_array then
            for _, v in ipairs(value) do parts[#parts + 1] = inner .. serialize(v, inner) .. "," end
        else
            local keys = {}
            for k in pairs(value) do keys[#keys + 1] = k end
            table.sort(keys, function(a, b) return tostring(a) < tostring(b) end)
            for _, k in ipairs(keys) do
                parts[#parts + 1] = inner .. "[" .. lua_quote(tostring(k)) .. "] = "
                    .. serialize(value[k], inner) .. ","
            end
        end
        if #parts == 0 then return "{}" end
        return "{\n" .. table.concat(parts, "\n") .. "\n" .. indent .. "}"
    else
        return "nil"
    end
end

local out = {}
out[#out + 1] = "--[[ AUTO-GENERATED by tools/gen/gen_tests_manifest.lua -- DO NOT EDIT BY HAND."
out[#out + 1] = "     Regenerate with: xmake lua tools/gen/gen_tests_manifest.lua ]]"
out[#out + 1] = ""
out[#out + 1] = "ETELEOS_TESTS_MANIFEST = " .. serialize(MANIFEST)
out[#out + 1] = ""

local outpath = path.join(TESTS, "generated_manifest.lua")
local f = io.open(outpath, "w")
f:write(table.concat(out, "\n"))
f:close()
print(string.format("eteleos-gen-tests: manifest written to %s", outpath))
