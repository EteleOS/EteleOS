-- EteleOS: userland/network/tcpdump/atime.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- Extract ACK timestamps from a tcpdump FTP trace.  Ported from atime.awk.
if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end
local input = io.stdin; if (arg or {})[1] then input = assert(io.open(arg[1], "r")) end
local tzero
for line in input:lines() do
    local f = {}; for x in line:gmatch("%S+") do f[#f+1] = x end
    if (f[6] or ""):match("ack$") and not (f[5] or ""):match("[SFR]") then
        local h,m,s = f[1]:match("^(%d+):(%d+):([%d.]+)"); local time = h*3600 + m*60 + s
        tzero = tzero or time; io.write(string.format("%7.2f\t%g\n", time - tzero, (tonumber(f[7]) or 0) / 1024))
    end
end
if input ~= io.stdin then input:close() end
