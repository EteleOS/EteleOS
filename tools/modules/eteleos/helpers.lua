--[[
================================================================================
 EteleOS: tools/modules/eteleos/helpers.lua
 This file uses the Apache-2.0 license
================================================================================

WHY THIS FILE EXISTS, SEPARATELY FROM tools/helpers.lua
-------------------------------------------------------------
Confirmed by direct, isolated testing against a real xmake v3.0.9 build:
xmake.lua description scope and script scope (on_load/on_build/on_test/
after_install/...) have COMPLETELY SEPARATE Lua global environments --
this is true even for a bare global function defined and called within the
SAME FILE, not only across files. A plain `function eteleos_get_triple()
... end` written at the top level of tools/helpers.lua (description scope,
executed once when that file is includes()'d) is simply not visible from
inside `on_load(function (target) ... eteleos_get_triple() ... end)`
anywhere in the project, even though tools/helpers.lua's own header
comment claimed otherwise ("every symbol defined here is a Lua global...
so it remains accessible inside on_load()").

xmake's real, working mechanism for exactly this need (share logic between
project files and script-scope callbacks) is add_moduledirs() + import(),
confirmed working by isolated test. This file is that module -- the SAME
architecture data/logic as tools/helpers.lua, redefined here so it is
reachable via `import("eteleos.helpers")` from inside any on_load/on_build/
after_install/on_test callback in this project.

tools/helpers.lua ITSELF is UNCHANGED and still needed: it is still valid,
description-scope-to-description-scope global sharing (confirmed this
half genuinely does work -- e.g. tools/xmake.lua's own top-level call to
eteleos_check_arch() is descripton-scope calling description-scope,
which is fine), and a few description-scope call sites still use it
directly. The two files necessarily duplicate the same small data tables;
keep them in sync if this project's architecture list ever changes (the
canonical list is ETELEOS_SUPPORTED_ARCHS / ETELEOS_TARGET_TRIPLES in
tools/helpers.lua -- mirror any change here too).

Registered via add_moduledirs(path.join(os.scriptdir(), "modules")) in
tools/xmake.lua.
--------------------------------------------------------------------------------
--]]

local TARGET_TRIPLES = {
    amd64   = "x86_64-unknown-openbsd",
    arm64   = "aarch64-unknown-openbsd",
    riscv64 = "riscv64-unknown-openbsd",
}

local CROSS_PREFIXES = {
    amd64   = "x86_64-unknown-openbsd-",
    arm64   = "aarch64-unknown-openbsd-",
    riscv64 = "riscv64-unknown-openbsd-",
}

local ARCH_CFLAGS = {
    amd64   = {"-march=x86-64"},
    arm64   = {},
    riscv64 = {"-march=rv64gc"},
}

-- Return the arch-specific cflags list (or an empty table for unknown arch).
function eteleos_get_arch_cflags()
    local arch = get_config("target_arch") or "amd64"
    return ARCH_CFLAGS[arch] or {}
end

-- Return the LLVM target triple for the current target architecture.
function eteleos_get_triple()
    local arch = get_config("target_arch") or "amd64"
    return TARGET_TRIPLES[arch] or ("unknown-" .. arch .. "-unknown-openbsd")
end

-- Return the GCC-style cross-prefix for the current target architecture.
function eteleos_get_cross_prefix()
    local arch = get_config("target_arch") or "amd64"
    return CROSS_PREFIXES[arch] or ""
end

-- Return true when the target arch differs from the host arch (BSD naming
-- on both sides; os.arch() returns GNU/LLVM names).
function eteleos_is_cross()
    local target = get_config("target_arch") or "amd64"
    local gnu_to_bsd = { x86_64 = "amd64", aarch64 = "arm64", riscv64 = "riscv64" }
    local host = gnu_to_bsd[os.arch()] or os.arch()
    return target ~= host
end

-- Append multiple flags to a target (cxflags, ldflags, or asflags).
function eteleos_add_flags(target, kind, flags)
    if type(flags) == "table" then
        for _, f in ipairs(flags) do
            target:add(kind, f, {force = true})
        end
    elseif type(flags) == "string" then
        target:add(kind, flags, {force = true})
    end
end
