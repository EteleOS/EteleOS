-- EteleOS: userland/development/vi/docs/USD.doc/vi.ref/merge.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: merge.awk,v 1.3 2001/01/29 01:58:35 niklas Exp $
-- @(#)merge.awk 8.3 (Berkeley) 5/25/94

if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end

local argv = {...}; if #argv == 0 then argv = arg or {} end
local infile = argv[1]

local inp = infile and io.open(infile, "r") or io.stdin
if not inp then
    io.stderr:write("merge.lua: cannot open " .. tostring(infile) .. "\n")
    os.exit(1)
end

local prev = nil
local nr   = 0

for line in inp:lines() do
    nr = nr + 1
    local f = {}
    for tok in line:gmatch("%S+") do f[#f+1] = tok end
    local f1 = f[1] or ""
    local f2 = f[2] or ""

    if f1 == prev then
        io.write(string.format(", %s", f2))
    else
        if nr ~= 1 then
            io.write("\n")
        end
        io.write(string.format("%s \t%s", f1, f2))
        prev = f1
    end
end

if infile then inp:close() end

io.write("\n")
