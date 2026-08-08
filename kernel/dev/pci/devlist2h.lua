-- EteleOS: kernel/dev/pci/devlist2h.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: devlist2h.awk,v 1.8 2007/02/21 13:17:28 deraadt Exp $
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

if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end

local argv = {...}; if #argv == 0 then argv = arg or {} end
local infile = argv[1] or "pcidevs"

local function split_fields(line)
    local fields = {}
    for f in line:gmatch("%S+") do
        fields[#fields + 1] = f
    end
    return fields
end

local dfile_path = "pcidevs_data.h"
local hfile_path = "pcidevs.h"

local df = io.open(dfile_path, "w")
local hf = io.open(hfile_path, "w")
if not df or not hf then
    io.stderr:write("devlist2h.lua: cannot open output files\n")
    os.exit(1)
end

local nproducts   = 0
local nvendors    = 0
local nvendor_dup = 0
local blanklines  = 0
local vendors     = {}
local products    = {}
local vendorindex = {}

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
        df:write(" */\n\n")

        hf:write("/*\n")
        hf:write(" * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n")
        hf:write(" *\n")
        hf:write(" * generated from:\n")
        hf:write(string.format(" *\t%s\n", VERSION))
        hf:write(" */\n")
        goto continue
    end

    if NF > 0 and f[1] == "vendor" then
        nvendors = nvendors + 1
        local vname = f[2]
        local vid   = f[3]

        if vendorindex[vname] then
            io.write(string.format("duplicate vendor name %s\n", vname))
            nvendor_dup = nvendor_dup + 1
        end
        vendorindex[vname] = nvendors

        hf:write(string.format("#define\tPCI_VENDOR_%s\t%s\t", vname, vid))

        local oparen   = false
        local ocomment = false
        local fid      = 4
        local str_parts = {}
        if fid <= NF then
            hf:write("\t/* ")
            ocomment = true
        end
        while fid <= NF do
            if f[fid] == "#" then
                hf:write("(")
                oparen = true
                fid = fid + 1
            elseif oparen then
                hf:write(f[fid])
                if fid < NF then hf:write(" ") end
                fid = fid + 1
            else
                str_parts[#str_parts + 1] = f[fid]
                hf:write(f[fid])
                if fid < NF then hf:write(" ") end
                fid = fid + 1
            end
        end
        if oparen   then hf:write(")") end
        if ocomment then hf:write(" */") end
        hf:write("\n")

        vendors[nvendors] = {name=vname, id=vid, parts=str_parts}
        goto continue
    end

    if NF > 0 and f[1] == "product" then
        nproducts = nproducts + 1
        local pvendor  = f[2]
        local pproduct = f[3]
        local pid      = f[4]

        hf:write(string.format("#define\tPCI_PRODUCT_%s_%s\t%s\t",
            pvendor, pproduct, pid))

        local oparen   = false
        local ocomment = false
        local fid      = 5
        local desc_parts = {}
        if fid <= NF then
            hf:write("\t/* ")
            ocomment = true
        end
        while fid <= NF do
            if f[fid] == "#" then
                hf:write("(")
                oparen = true
                fid = fid + 1
            elseif oparen then
                hf:write(f[fid])
                if fid < NF then hf:write(" ") end
                fid = fid + 1
            else
                desc_parts[#desc_parts + 1] = f[fid]
                hf:write(f[fid])
                if fid < NF then hf:write(" ") end
                fid = fid + 1
            end
        end
        if oparen   then hf:write(")") end
        if ocomment then hf:write(" */") end
        hf:write("\n")

        products[nproducts] = {
            vendor  = pvendor,
            product = pproduct,
            id      = pid,
            desc    = desc_parts,
        }
        goto continue
    end

    if line == "" then blanklines = blanklines + 1 end
    hf:write(line .. "\n")
    if blanklines < 2 then
        df:write(line .. "\n")
    end

    ::continue::
end

inp:close()

df:write("\n")

if nvendor_dup > 0 then
    df:close()
    hf:close()
    os.exit(1)
end

df:write("/* Descriptions of known vendors and devices. */\n")
df:write("struct pci_known_vendor {\n")
df:write("\tpci_vendor_id_t vendor;\n")
df:write("\tconst char *vendorname;\n")
df:write("};\n\n")

df:write("struct pci_known_product {\n")
df:write("\tpci_vendor_id_t vendor;\n")
df:write("\tpci_product_id_t product;\n")
df:write("\tconst char *productname;\n")
df:write("};\n\n")

df:write("static const struct pci_known_product pci_known_products[] = {\n")
for i = 1, nproducts do
    local p = products[i]
    df:write("\t{\n")
    df:write(string.format("\t    PCI_VENDOR_%s, PCI_PRODUCT_%s_%s,\n",
        p.vendor, p.vendor, p.product))
    df:write('\t    "')
    local needspace = false
    for _, part in ipairs(p.desc) do
        if needspace then df:write(" ") end
        df:write(part)
        needspace = true
    end
    df:write('",\n')
    df:write("\t},\n")
end
df:write("\t{ 0, 0, NULL, }\n")
df:write("};\n\n")

df:write("static const struct pci_known_vendor pci_known_vendors[] = {\n")
for i = 1, nvendors do
    local v = vendors[i]
    df:write("\t{\n")
    df:write(string.format("\t    PCI_VENDOR_%s,\n", v.name))
    df:write('\t    "')
    local needspace = false
    for _, part in ipairs(v.parts) do
        if needspace then df:write(" ") end
        df:write(part)
        needspace = true
    end
    df:write('",\n')
    df:write("\t},\n")
end
df:write("\t{ 0, NULL, }\n")
df:write("};\n")

df:close()
hf:close()
