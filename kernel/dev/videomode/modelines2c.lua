-- EteleOS: kernel/dev/videomode/modelines2c.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $NetBSD: modelines2c.awk,v 1.5 2011/03/21 19:32:26 jdc Exp $
-- $OpenBSD: modelines2c.awk,v 1.3 2024/11/06 09:34:10 miod Exp $
--
-- Copyright (c) 2006 Itronix Inc.
-- All rights reserved.
--
-- Written by Garrett D'Amore for Itronix Inc.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions
-- are met:
-- 1. Redistributions of source code must retain the above copyright
--    notice, this list of conditions and the following disclaimer.
-- 2. Redistributions in binary form must reproduce the above copyright
--    notice, this list of conditions and the following disclaimer in the
--    documentation and/or other materials provided with the distribution.
-- 3. The name of Itronix Inc. may not be used to endorse
--    or promote products derived from this software without specific
--    prior written permission.
--
-- THIS SOFTWARE IS PROVIDED BY ITRONIX INC. ``AS IS'' AND
-- ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
-- TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
-- PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL ITRONIX INC. BE LIABLE FOR ANY
-- DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
-- (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
-- LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
-- ON ANY THEORY OF LIABILITY, WHETHER IN
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
-- POSSIBILITY OF SUCH DAMAGE.

io.stdout:setvbuf("no")

local argv = arg or {}
local infile = argv[1]

local function split_fields(line)
    local fields = {}
    for f in line:gmatch("%S+") do
        fields[#fields + 1] = f
    end
    return fields
end

local nmodes = 0
local dmodes = {}

local inp = infile and io.open(infile, "r") or io.stdin
if not inp then
    io.stderr:write("modelines2c.lua: cannot open " .. tostring(infile) .. "\n")
    os.exit(1)
end

local nr = 0
for line in inp:lines() do
    nr = nr + 1
    local f = split_fields(line)
    local NF = #f

    if nr == 1 then
        local parts = {}
        for p in line:gmatch("[^$]+") do parts[#parts + 1] = p end
        local VERSION = parts[2] or ""

        io.write("/*\t$OpenBSD$\t*/\n\n")
        io.write("/*\n")
        io.write(" * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n")
        io.write(" *\n")
        io.write(" * generated from:\n")
        io.write(string.format(" *\t%s\n", VERSION))
        io.write(" */\n\n")
        io.write("#include <sys/types.h>\n")
        io.write("#include <dev/videomode/videomode.h>\n\n")
        io.write("/*\n")
        io.write(" * These macros help the modelines below fit on one line.\n")
        io.write(" */\n")
        io.write("#define HP VID_PHSYNC\n")
        io.write("#define HN VID_NHSYNC\n")
        io.write("#define VP VID_PVSYNC\n")
        io.write("#define VN VID_NVSYNC\n")
        io.write("#define I VID_INTERLACE\n")
        io.write("#define DS VID_DBLSCAN\n")
        io.write("\n")
        io.write("#define M(nm,hr,vr,clk,hs,he,ht,vs,ve,vt,f) \\\n")
        io.write("\t{ clk, hr, hs, he, ht, vr, vs, ve, vt, f, nm } \n\n")
        io.write("const struct videomode videomode_list[] = {\n")
        goto continue
    end

    if f[1] == "ModeLine" then
        local dotclock   = tonumber(f[3])  or 0
        local hdisplay   = tonumber(f[4])  or 0
        local hsyncstart = tonumber(f[5])  or 0
        local hsyncend   = tonumber(f[6])  or 0
        local htotal     = tonumber(f[7])  or 0
        local vdisplay   = tonumber(f[8])  or 0
        local vsyncstart = tonumber(f[9])  or 0
        local vsyncend   = tonumber(f[10]) or 0
        local vtotal     = tonumber(f[11]) or 0

        local hflags = "HP"
        local vflags = "VP"
        local iflag  = ""
        local iflags = ""
        local ifactor = 1.0

        if f[12] and f[12]:sub(1,1) == "-" then
            hflags = "HN"
        end
        if f[13] and f[13]:sub(1,1) == "-" then
            vflags = "VN"
        end
        if f[14] and f[14]:lower():match("interlace") then
            iflag   = "i"
            iflags  = "|I"
            ifactor = 2.0
        end

        local hrefresh = (dotclock * 1000000) / htotal
        local vrefresh = math.floor(((hrefresh * ifactor) / vtotal) + 0.1)

        local modestr = string.format("%dx%dx%d%s",
            hdisplay, vdisplay, vrefresh, iflag)

        io.write(string.format('M("%s",%d,%d,%d,%d,%d,%d,%d,%d,%d,%s),\n',
            modestr,
            hdisplay, vdisplay, math.floor(dotclock * 1000),
            hsyncstart, hsyncend, htotal,
            vsyncstart, vsyncend, vtotal,
            hflags .. "|" .. vflags .. iflags))

        local modestr2 = string.format("%dx%dx%d%s",
            math.floor(hdisplay/2), math.floor(vdisplay/2), vrefresh, iflag)
        dmodes[nmodes] = string.format(
            'M("%s",%d,%d,%d,%d,%d,%d,%d,%d,%d,%s),',
            modestr2,
            math.floor(hdisplay/2), math.floor(vdisplay/2),
            math.floor(dotclock * 1000 / 2),
            math.floor(hsyncstart/2), math.floor(hsyncend/2), math.floor(htotal/2),
            math.floor(vsyncstart/2), math.floor(vsyncend/2), math.floor(vtotal/2),
            hflags .. "|" .. vflags .. "|DS" .. iflags)

        nmodes = nmodes + 1
    end

    ::continue::
end

if infile then inp:close() end

io.write("\n/* Derived Double Scan Modes */\n\n")
for i = 0, nmodes - 1 do
    io.write(dmodes[i] .. "\n")
end
io.write("};\n\n")
io.write(string.format("const int videomode_count = %d;\n", nmodes))
