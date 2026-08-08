-- EteleOS: kernel/dev/onewire/devlist2h.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: devlist2h.awk,v 1.4 2007/02/28 22:31:32 deraadt Exp $
--
-- Copyright (c) 2006 Alexander Yurchenko <grange@openbsd.org>
--
-- Permission to use, copy, modify, and distribute this software for any
-- purpose with or without fee is hereby granted, provided that the above
-- copyright notice and this permission notice appear in all copies.
--
-- THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
-- WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
-- MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
-- ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
-- WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
-- ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
-- OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

io.stdout:setvbuf("no")

local argv = arg or {}
local infile = argv[1] or "onewiredevs"

local function split_fields(line)
    local fields = {}
    for f in line:gmatch("%S+") do
        fields[#fields + 1] = f
    end
    return fields
end

local hfile_path = "onewiredevs.h"
local dfile_path = "onewiredevs_data.h"

local hf = io.open(hfile_path, "w")
local df = io.open(dfile_path, "w")
if not hf or not df then
    io.stderr:write("devlist2h.lua: cannot open output files\n")
    os.exit(1)
end

local inp = io.open(infile, "r")
if not inp then
    io.stderr:write("devlist2h.lua: cannot open " .. infile .. "\n")
    os.exit(1)
end

local nr = 0
for line in inp:lines() do
    nr = nr + 1
    local f = split_fields(line)
    local NF = #f

    if nr == 1 then
        local VERSION = line:gsub("%$", "")
        local header = string.format(
            "/*\t\\$OpenBSD\\$\t*/\n\n" ..
            "/*\n * THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT.\n" ..
            " *\n * Generated from:\n *\t%s\n */\n\n", VERSION)
        hf:write(header)
        df:write(header)

        df:write("struct onewire_family {\n")
        df:write("\tint\t\tof_type;\n")
        df:write("\tconst char\t*of_name;\n")
        df:write("};\n\n")
        df:write("static const struct onewire_family onewire_famtab[] = {\n")
        goto continue
    end

    if NF > 0 and f[1] == "family" then
        local fname = f[2]:upper()
        local ftype = f[3]

        hf:write(string.format("#define ONEWIRE_FAMILY_%s\t%s\n", fname, ftype))
        df:write(string.format('\t{ ONEWIRE_FAMILY_%s, "', fname))

        local fid = 4
        local first = true
        while fid <= NF do
            if not first then df:write(" ") end
            df:write(f[fid])
            first = false
            fid = fid + 1
        end
        df:write('" },\n')
        goto continue
    end

    ::continue::
end

inp:close()

df:write("\t{ 0, NULL }\n};\n")

hf:close()
df:close()
