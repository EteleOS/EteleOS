-- EteleOS: tests/sys/kern/extent/extest.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- $OpenBSD: extest.awk,v 1.3 2019/09/11 12:30:34 kettenis Exp $
-- $NetBSD: extest.awk,v 1.6 2002/02/21 03:59:25 mrg Exp $
-- Generate the extent regression C program.  Ported from extest.awk.
if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end
local input = io.stdin
if (arg or {})[1] then input = assert(io.open(arg[1], "r")) end
local first, align, boundary = true, "EX_NOALIGN", "EX_NOBOUNDARY"
io.write("#include <sys/types.h>\n#include <sys/extent.h>\n\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\nint main(void) {\nstruct extent *ex; int error; long result;\n")
for line in input:lines() do
    local f = {}; for word in line:gmatch("%S+") do f[#f + 1] = word end
    if f[1] == "extent" then
        if not first then io.write("extent_destroy(ex);\n") end
        align, boundary = "EX_NOALIGN", "EX_NOBOUNDARY"
        io.write(string.format("printf(\"output for %s\\n\");\n", f[2]))
        io.write(string.format("ex = extent_create(\"%s\", %s, %s, 0, 0, 0, %s);\n", f[2], f[3], f[4], f[5] or "0")); first = false
    elseif f[1] == "align" then align = f[2]
    elseif f[1] == "boundary" then boundary = f[2]
    elseif f[1] == "alloc_region" then
        io.write(string.format("error = extent_alloc_region(ex, %s, %s, %s);\nif (error)\n\tprintf(\"error: %%s\\n\", strerror(error));\n", f[2], f[3], f[4] or "0"))
    elseif f[1] == "alloc_subregion" then
        io.write(string.format("error = extent_alloc_subregion(ex, %s, %s, %s,\n\t%s, 0, %s, 0, &result);\nif (error)\n\tprintf(\"error: %%s\\n\", strerror(error));\nelse\n\tprintf(\"result: 0x%%lx\\n\", result);\n", f[2], f[3], f[4], align, boundary))
    elseif f[1] == "free" then
        io.write(string.format("error = extent_free(ex, %s, %s, %s);\nif (error)\n\tprintf(\"error: %%s\\n\", strerror(error));\n", f[2], f[3], f[4] or "0"))
    elseif f[1] == "print" then io.write("extent_print(ex);\n") end
end
if input ~= io.stdin then input:close() end
io.write("exit (0);\n}\n")
