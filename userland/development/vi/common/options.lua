-- EteleOS: userland/development/vi/common/options.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: options.awk,v 1.4 2017/12/14 10:02:53 martijn Exp $
-- @(#)options.awk 10.1 (Berkeley) 6/8/95

io.stdout:setvbuf("no")

local argv = arg or {}
local infile = argv[1]

local inp = infile and io.open(infile, "r") or io.stdin
if not inp then
    io.stderr:write("options.lua: cannot open " .. tostring(infile) .. "\n")
    os.exit(1)
end

io.write("enum {\n")
local first = true

for line in inp:lines() do
    local opt = line:match("^/[*] (O_[0-9A-Z_]*)")
    if opt then
        if first then
            io.write(string.format("\t%s = 0,\n", opt))
        else
            io.write(string.format("\t%s,\n", opt))
        end
        first = false
    end
end

if infile then inp:close() end

io.write("\tO_OPTIONCOUNT\n};\n")
