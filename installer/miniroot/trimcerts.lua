-- EteleOS: installer/miniroot/trimcerts.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: trimcerts.awk,v 1.2 2019/05/15 20:27:42 sthen Exp $
-- Copyright (c) 2018 Stuart Henderson <sthen@openbsd.org>
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

if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end

local argv = {...}; if #argv == 0 then argv = arg or {} end

if #argv < 2 then
    io.stderr:write("usage: xmake lua trimcerts.lua cert.pem outputfile\n")
    os.exit(1)
end

local infile  = argv[1]
local outfile = argv[2]

local inp = io.open(infile, "r")
if not inp then
    io.stderr:write(string.format("trimcerts.lua: cannot open %s\n", infile))
    os.exit(1)
end

local out = io.open(outfile, "w")
if not out then
    io.stderr:write(string.format("trimcerts.lua: cannot open %s for writing\n", outfile))
    inp:close()
    os.exit(1)
end

local incert = false

for line in inp:lines() do
    if line:match("^-----BEGIN CERTIFICATE-----") then
        incert = true
    end
    if line:match("^#") or incert then
        out:write(line .. "\n")
    end
    if line:match("^-----END CERTIFICATE-----") then
        incert = false
    end
end

inp:close()
out:close()

os.execute("chmod 444 " .. outfile)
os.execute("chown root:bin " .. outfile)
