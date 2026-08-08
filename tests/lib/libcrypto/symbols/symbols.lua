-- EteleOS: tests/lib/libcrypto/symbols/symbols.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- $OpenBSD: symbols.awk,v 1.15 2025/08/22 15:52:34 tb Exp $
-- Copyright (c) 2018,2020 Theo Buehler <tb@openbsd.org>
-- Permission to use, copy, modify, and distribute this software for any purpose with or without fee is hereby granted.
-- Generate the LibreSSL symbol probe.  Ported from symbols.awk.
if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end
local input = io.stdin
if (arg or {})[1] then input = assert(io.open(arg[1], "r")) end
local symbols = {}
io.write('#include "include_headers.c"\n\n')
for name in input:lines() do
    symbols[name] = name
    io.write(string.format("#ifdef %s\n#undef %s\n#endif\n", name, name))
    io.write(string.format("extern typeof(%s) *_libre_%s;\n", name, name))
end
if input ~= io.stdin then input:close() end
io.write("\nint\nmain(void)\n{\n\tsize_t i;\n\n\tstruct {\n\t\tconst char *const name;\n\t\tconst void *addr;\n\t\tconst void *libre_addr;\n\t} symbols[] = {\n")
for name in pairs(symbols) do
    io.write(string.format("\t\t{\n\t\t\t.name = \"%s\",\n\t\t\t.addr = &%s,\n#if defined(USE_LIBRESSL_NAMESPACE)\n\t\t\t.libre_addr = &_libre_%s,\n#endif\n\t\t},\n", name, name, name))
end
io.write("\t};\n\n\tfor (i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++) {\n\t\tfprintf(stderr, \"%s: %p\\n\", symbols[i].name, symbols[i].addr);\n#if defined(USE_LIBRESSL_NAMESPACE)\n\t\tfprintf(stderr, \"_libre_%s: %p\\n\", symbols[i].name, symbols[i].libre_addr);\n#endif\n\t}\n\n\tprintf(\"OK\\n\");\n\n\treturn 0;\n}\n")
