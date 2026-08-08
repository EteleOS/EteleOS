-- EteleOS: kernel/dev/isa/devlist2h.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: devlist2h.awk,v 1.6 2001/01/29 06:16:14 mickey Exp $
-- $NetBSD: devlist2h.awk,v 1.2 1996/01/22 21:08:09 cgd Exp $
--
-- Copyright (c) 1995, 1996 Christopher G. Demetriou
-- All rights reserved.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions
-- are met:
-- 1. Redistributions of source code must retain the above copyright
--    notice, this list of conditions and the following disclaimer.
-- 2. Redistributions in binary form must reproduce the above copyright
--    notice, this list of conditions and the following disclaimer in the
--    documentation and/or other materials provided with the distribution.
-- 3. All advertising materials mentioning features or use of this software
--    must display the following acknowledgement:
--      This product includes software developed by Christopher G. Demetriou.
-- 4. The name of the author may not be used to endorse or promote products
--    derived from this software without specific prior written permission
--
-- THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
-- IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
-- OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
-- IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
-- INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
-- NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
-- DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
-- THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
-- (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
-- THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

io.stdout:setvbuf("no")

local argv = arg or {}
local infile = argv[1] or "pnpdevs"

local function split_fields(line)
    local fields = {}
    for f in line:gmatch("%S+") do
        fields[#fields + 1] = f
    end
    return fields
end

local dfile_path = "pnpdevs.h"
local df = io.open(dfile_path, "w")
if not df then
    io.stderr:write("devlist2h.lua: cannot open " .. dfile_path .. "\n")
    os.exit(1)
end

local nproducts = 0
local products  = {}

local inp = io.open(infile, "r")
if not inp then
    io.stderr:write("devlist2h.lua: cannot open " .. infile .. "\n")
    os.exit(1)
end

local nr = 0
for line in inp:lines() do
    nr = nr + 1
    local f  = split_fields(line)
    local NF = #f

    if nr == 1 then
        local VERSION = line:gsub("%$", "")
        df:write("/*\n")
        df:write(" * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n")
        df:write(" *\n")
        df:write(" * generated from:\n")
        df:write(string.format(" *\t%s\n", VERSION))
        df:write(" */\n")
        goto continue
    end

    if NF == 0 then goto continue end
    if f[1]:sub(1,1) == "#" then goto continue end
    if f[2] and f[2]:sub(1,1) == "#" then goto continue end

    local field1 = f[1]
    local field2 = f[2] or ""

    repeat
        nproducts = nproducts + 1
        local driver
        local slash_pos = field1:find("/", 1, true)
        if slash_pos then
            driver = field1:sub(1, slash_pos - 1)
            field1 = field1:sub(slash_pos + 1)
        else
            driver = field1
            field1 = nil
        end
        products[nproducts] = {driver=driver, pnpid=field2}
    until not field1

    ::continue::
end

inp:close()

df:write("\n")
df:write("const struct isapnp_knowndev isapnp_knowndevs[] = {\n")
for i = 1, nproducts do
    local p = products[i]
    df:write(string.format('\t{ {"%s"}, {"%s"} },', p.pnpid, p.driver))
    df:write("\n")
end
df:write("};\n")

df:close()
