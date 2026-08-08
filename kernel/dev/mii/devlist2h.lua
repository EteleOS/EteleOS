-- EteleOS: kernel/dev/mii/devlist2h.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: devlist2h.awk,v 1.3 2023/01/04 14:42:46 jsg Exp $
-- $NetBSD: devlist2h.awk,v 1.2 1998/09/05 14:42:06 christos Exp $
--
-- Copyright (c) 1998 The NetBSD Foundation, Inc.
-- All rights reserved.
--
-- This code is derived from software contributed to The NetBSD Foundation
-- by Christos Zoulas.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions
-- are met:
-- 1. Redistributions of source code must retain the above copyright
--    notice, this list of conditions and the following disclaimer.
-- 2. Redistributions in binary form must reproduce the above copyright
--    notice, this list of conditions and the following disclaimer in the
--    documentation and/or other materials provided with the distribution.
--
-- THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
-- ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
-- TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
-- PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
-- BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
-- POSSIBILITY OF SUCH DAMAGE.
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
--      This model includes software developed by Christopher G. Demetriou.
-- 4. The name of the author(s) may not be used to endorse or promote models
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

if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end

local argv = {...}; if #argv == 0 then argv = arg or {} end
local infile = argv[1] or "miidevs"

local function split_fields(line)
    local fields = {}
    for f in line:gmatch("%S+") do
        fields[#fields + 1] = f
    end
    return fields
end

local function collectline(fields, fstart)
    local oparen = false
    local parts  = {}
    local NF     = #fields
    local f      = fstart
    while f <= NF do
        if fields[f] == "#" then
            parts[#parts + 1] = "("
            oparen = true
            f = f + 1
        elseif oparen then
            parts[#parts + 1] = fields[f]
            if f < NF then parts[#parts + 1] = " " end
            f = f + 1
        else
            parts[#parts + 1] = fields[f]
            if f < NF then parts[#parts + 1] = " " end
            f = f + 1
        end
    end
    if oparen then parts[#parts + 1] = ")" end
    return table.concat(parts)
end

local hfile_path = "miidevs.h"
local hf = io.open(hfile_path, "w")
if not hf then
    io.stderr:write("devlist2h.lua: cannot open " .. hfile_path .. "\n")
    os.exit(1)
end

local nmodels  = 0
local nouis    = 0
local ouis     = {}
local models   = {}
local ouiindex = {}

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
        hf:write("/*\t\\$OpenBSD\\$\t*/\n\n")
        hf:write("/*\n")
        hf:write(" * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n")
        hf:write(" *\n")
        hf:write(" * generated from:\n")
        hf:write(string.format(" *\t%s\n", VERSION))
        hf:write(" */\n")
        goto continue
    end

    if NF > 0 and f[1] == "oui" then
        nouis = nouis + 1
        local oname   = f[2]
        local oid     = f[3]
        local ocomment = collectline(f, 4)
        ouiindex[oname] = nouis
        ouis[nouis] = {name=oname, id=oid, comment=ocomment}
        hf:write(string.format("#define\tMII_OUI_%s\t%s\t/* %s */\n",
            oname, oid, ocomment))
        goto continue
    end

    if NF > 0 and f[1] == "model" then
        nmodels = nmodels + 1
        local moui     = f[2]
        local mmodel   = f[3]
        local mid      = f[4]
        local mcomment = collectline(f, 5)
        models[nmodels] = {oui=moui, model=mmodel, id=mid, comment=mcomment}

        hf:write(string.format("#define\tMII_MODEL_%s_%s\t%s\n",
            moui, mmodel, mid))
        hf:write(string.format('#define\tMII_STR_%s_%s\t"%s"\n',
            moui, mmodel, mcomment))
        goto continue
    end

    hf:write(line .. "\n")

    ::continue::
end

inp:close()
hf:close()
