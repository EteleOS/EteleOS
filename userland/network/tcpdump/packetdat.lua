-- EteleOS: userland/network/tcpdump/packetdat.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- Summarize TCP packets in an FTP trace.  Ported from packetdat.awk.
if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end
local argv = {...}; if #argv == 0 then argv = arg or {} end; local packetsize = tonumber(argv[1]) or 512
local filename = tonumber(argv[1]) and argv[2] or argv[1]
local input = filename and assert(io.open(filename, "r")) or io.stdin
local function fields(line) local r = {}; for x in line:gmatch("%S+") do r[#r+1] = x end; return r end
local function stamp(s) local h,m,sec = s:match("^(%d+):(%d+):([%d.]+)"); return h*3600 + m*60 + sec end
local firstSend, lastSend, firstAck, lastAck, seqNo, timesSent, timesAcked = {}, {}, {}, {}, {}, {}, {}
local maxId, totalPackets, totalAcks = 0, 0, 0
for line in input:lines() do
    local f = fields(line)
    if not (f[5] or ""):match("[SR]") then
        local time = stamp(f[1])
        if f[6] ~= "ack" then
            local seq = tonumber((f[6] or ""):match("^(.-):")) or 0
            local id = math.floor(1.5 + (seq - 1) / packetsize)
            maxId = math.max(maxId, id)
            if not firstSend[id] then firstSend[id], seqNo[id] = time, seq end
            lastSend[id] = time; timesSent[id] = (timesSent[id] or 0) + 1; totalPackets = totalPackets + 1
        else
            local id = math.floor(1 + ((tonumber(f[7]) or 0) - 2) / packetsize)
            timesAcked[id] = (timesAcked[id] or 0) + 1
            if not firstAck[id] then firstAck[id] = time end
            lastAck[id] = time; totalAcks = totalAcks + 1
        end
    end
end
if input ~= io.stdin then input:close() end
print(string.format("# %s chunks.  %s packets sent.  %s acks.", maxId, totalPackets, totalAcks))
for i = maxId - 1, 1, -1 do
    while i > 0 and not firstAck[i] do firstAck[i], lastAck[i], i = firstAck[i + 1], firstAck[i + 1], i - 1 end
end
local tzero = firstSend[1] or 0
for i = 1, maxId do
    io.write(string.format("%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t%d\t%d\n", i, seqNo[i] or 0,
        (firstSend[i] or 0) - tzero, (lastSend[i] or 0) - tzero,
        (firstAck[i] or 0) - tzero, (lastAck[i] or 0) - tzero,
        timesSent[i] or 0, timesAcked[i] or 0))
end
