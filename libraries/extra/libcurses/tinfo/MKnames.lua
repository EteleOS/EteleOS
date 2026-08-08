-- EteleOS: libraries/extra/libcurses/tinfo/MKnames.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: MKnames.awk,v 1.4 2023/10/17 09:52:09 nicm Exp $
-- Copyright 2019,2020 Thomas E. Dickey
-- Copyright 1998-2008,2009 Free Software Foundation, Inc.
--
-- Permission is hereby granted, free of charge, to any person obtaining a
-- copy of this software and associated documentation files (the "Software"),
-- to deal in the Software without restriction, including without limitation
-- the rights to use, copy, modify, merge, publish, distribute, distribute
-- with modifications, sublicense, and/or sell copies of the Software, and to
-- permit persons to whom the Software is furnished to do so, subject to the
-- following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
-- THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
-- FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
-- DEALINGS IN THE SOFTWARE.

io.stdout:setvbuf("no")

local argv = arg or {}

local bigstrings = argv[1] or "0"
local inputfiles = {}
for i = 2, #argv do
    inputfiles[#inputfiles + 1] = argv[i]
end

local awk_script = (debug.getinfo(1, "S").source or "@MKnames.lua"):sub(2)
    :gsub("%.lua$", ".awk")

local input_str = #inputfiles > 0 and table.concat(inputfiles, " ") or ""

local cmd = string.format(
    'awk -v bigstrings=%s -f "%s" %s',
    bigstrings, awk_script, input_str)

local ok, how, code = os.execute(cmd)
if not ok then
    io.stderr:write(string.format("MKnames.lua: awk failed (exit %s)\n", tostring(code)))
    os.exit(1)
end
