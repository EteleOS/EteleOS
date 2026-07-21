--[[
================================================================================
 EteleOS: tools/gen/gen_ports_manifest.lua
 This file uses the Apache-2.0 license
================================================================================

Same reasoning as tools/gen/gen_userland_manifest.lua. ports/xmake.lua's own
parse_port_makefile()/parse_distinfo() used io.open() directly, called from
description scope -- confirmed nil there in a real xmake v3.0.9 run.
Directory discovery itself (os.dirs()-based) already worked at description
scope and is unchanged, still in ports/xmake.lua; only the Makefile/distinfo
content parse is relocated here.

Regenerate with: xmake lua tools/gen/gen_ports_manifest.lua
whenever ports/ Makefiles, distinfo files, or the category/port list change.
--------------------------------------------------------------------------------
--]]

local ROOT  = path.absolute(os.scriptdir() .. "/../..")
local PORTS = path.join(ROOT, "ports")
local EXCLUDED_TOP_LEVEL = { infrastructure = true }

-- ==============================================================================
-- Unchanged from the previous revision of ports/xmake.lua
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

local function expand_vars(value, vars)
    return (value:gsub("%$[{(]([%w_.:=]+)[})]", function (name)
        local base = name:match("^([%w_]+)")
        return vars[base] or ("${" .. name .. "}")
    end))
end

local function parse_port_makefile(dir)
    local content = read_file(path.join(dir, "Makefile"))
    if not content then return nil end

    local info = {
        distname = nil, version = nil, pkgname = nil, categories = {},
        sites = nil, wantlib = {}, gnu_configure = false, has_custom_target = false,
        extract_sufx = ".tar.gz",
    }
    local vars = {}

    for _, line in ipairs(logical_lines(content)) do
        local stripped = line:gsub("#.*$", ""):match("^%s*(.-)%s*$")
        if stripped ~= "" then
            local var, op, rest = stripped:match("^(%u[%u_]*)%s*([+?:!]?=)%s*(.*)$")
            if var and op ~= "!=" then
                local expanded = expand_vars(rest, vars)
                if op == "+=" and vars[var] then
                    vars[var] = vars[var] .. " " .. expanded
                elseif op == "?=" and vars[var] then
                    -- no override
                else
                    vars[var] = expanded
                end
            elseif stripped:match("^do%-configure%s*:") or stripped:match("^do%-build%s*:")
                   or stripped:match("^do%-install%s*:") or stripped:match("^post%-")
                   or stripped:match("^pre%-") then
                info.has_custom_target = true
            end
        end
    end

    info.distname = vars.DISTNAME
    info.version = vars.VERSION
    info.pkgname = vars.PKGNAME or info.distname
    info.sites = vars.SITES or vars.MASTER_SITES
    info.extract_sufx = vars.EXTRACT_SUFX or ".tar.gz"
    info.gnu_configure = (vars.GNU_CONFIGURE == "Yes" or vars.GNU_CONFIGURE == "yes")
    if vars.CATEGORIES then
        for c in vars.CATEGORIES:gmatch("%S+") do info.categories[#info.categories + 1] = c end
    end
    if vars.WANTLIB then
        for l in vars.WANTLIB:gmatch("%S+") do info.wantlib[#info.wantlib + 1] = l end
    end
    return info
end

local function parse_distinfo(dir)
    local content = read_file(path.join(dir, "distinfo"))
    local entries = {}
    if not content then return entries end
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local algo, fname, value = line:match("^([%u%d]+)%s*%(([^)]+)%)%s*=%s*(.+)$")
        if algo and fname then
            entries[fname] = entries[fname] or {}
            entries[fname][algo] = value
        end
    end
    return entries
end

-- ==============================================================================
-- Discovery (unchanged: os.dirs() already works at description scope) +
-- parse each port found.
-- ==============================================================================
local MANIFEST = {}   -- "category/name" -> { info = ..., distinfo = ... }
local stats = { discovered = 0, no_makefile = 0 }

for _, catdir in ipairs(os.dirs(path.join(PORTS, "*"))) do
    local category = path.filename(catdir)
    if not EXCLUDED_TOP_LEVEL[category] then
        for _, portdir in ipairs(os.dirs(path.join(catdir, "*"))) do
            if os.isfile(path.join(portdir, "Makefile")) and os.isfile(path.join(portdir, "distinfo")) then
                local name = path.filename(portdir)
                local info = parse_port_makefile(portdir)
                if info then
                    MANIFEST[category .. "/" .. name] = {
                        info = info,
                        distinfo = parse_distinfo(portdir),
                    }
                    stats.discovered = stats.discovered + 1
                else
                    stats.no_makefile = stats.no_makefile + 1
                end
            end
        end
    end
end

print(string.format("eteleos-gen-ports: %d ports parsed, %d skipped (no Makefile)",
      stats.discovered, stats.no_makefile))

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
out[#out + 1] = "--[[ AUTO-GENERATED by tools/gen/gen_ports_manifest.lua -- DO NOT EDIT BY HAND."
out[#out + 1] = "     Regenerate with: xmake lua tools/gen/gen_ports_manifest.lua ]]"
out[#out + 1] = ""
out[#out + 1] = "ETELEOS_PORTS_MANIFEST = " .. serialize(MANIFEST)
out[#out + 1] = ""

local outpath = path.join(PORTS, "generated_manifest.lua")
local f = io.open(outpath, "w")
f:write(table.concat(out, "\n"))
f:close()
print(string.format("eteleos-gen-ports: manifest written to %s", outpath))
