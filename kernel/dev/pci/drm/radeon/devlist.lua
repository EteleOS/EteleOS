-- EteleOS: kernel/dev/pci/drm/radeon/devlist.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- Generate the Radeon PCI ID table from pciids.
-- Ported from devlist.awk.
if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end
local input = io.stdin
if (arg or {})[1] and arg[1] ~= "-" then input = assert(io.open(arg[1], "r")) end
print("/* THIS FILE AUTOMATICALLY GENERATED.  DO NOT EDIT. */")
print("static const struct pci_matchid radeon_devices[] = {")
for line in input:lines() do
    if line:match("^0, CHIP") then
        -- AWK's substr($0, 3, 14): Lua strings use a one-based index.
        io.write("\t{ " .. line:sub(3, 16) .. " },\n")
    end
end
if input ~= io.stdin then input:close() end
print("};")
