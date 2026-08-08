-- EteleOS: userland/development/vi/ex/ex.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: ex.awk,v 1.3 2017/12/14 10:02:53 martijn Exp $
-- @(#)ex.awk 10.1 (Berkeley) 6/8/95

io.stdout:setvbuf("no")

local argv = arg or {}
local infile = argv[1]

local inp = infile and io.open(infile, "r") or io.stdin
if not inp then
    io.stderr:write("ex.lua: cannot open " .. tostring(infile) .. "\n")
    os.exit(1)
end

io.write("enum {")
local first = true

for line in inp:lines() do
    local cmd = line:match("^/[*] (C_[0-9A-Z_]*) [*]/$")
    if cmd then
        if first then
            io.write(string.format("\n\t%s = 0", cmd))
        else
            io.write(string.format(",\n\t%s", cmd))
        end
        first = false
    end
end

if infile then inp:close() end

io.write("\n};\n")
