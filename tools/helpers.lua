--[[
================================================================================
 EteleOS: tools/helpers.lua, time write: 2026/07/10
 This file uses the Apache-2.0 license
================================================================================

Global helper tables and utility functions for the EteleOS build framework.
Loaded FIRST by tools/xmake.lua; every symbol defined here is a Lua global
(ETELEOS_ prefix) so it remains accessible inside on_load() / on_build()
callbacks defined in the files that follow.

Nothing here calls any xmake description-scope API that declares a project
entity (no option(), no toolchain(), no rule(), no target()).
--------------------------------------------------------------------------------
--]]

-- ==============================================================================
-- Architecture → LLVM target triple
-- ==============================================================================
-- Only the three architectures that remain in the EteleOS tree after pruning.
-- Keep this table in sync with option("target_arch") in options.lua.
ETELEOS_TARGET_TRIPLES = {
    amd64   = "x86_64-unknown-openbsd",
    arm64   = "aarch64-unknown-openbsd",
    riscv64 = "riscv64-unknown-openbsd",
}

-- Canonical list of supported architectures.
-- Used for validation and for the option values list.
ETELEOS_SUPPORTED_ARCHS = { "amd64", "arm64", "riscv64" }

-- ==============================================================================
-- Architecture → GCC cross-prefix
-- ==============================================================================
-- Only meaningful for eteleos-gcc / external cross-toolchains.
ETELEOS_CROSS_PREFIXES = {
    amd64   = "x86_64-unknown-openbsd-",
    arm64   = "aarch64-unknown-openbsd-",
    riscv64 = "riscv64-unknown-openbsd-",
}

-- ==============================================================================
-- Architecture-specific compiler flags
-- ==============================================================================
-- Flags required for correctness on a given ISA, beyond the -target triple.
-- Used in rules.lua (eteleos.base on_load) and toolchains.lua (on_load).
ETELEOS_ARCH_CFLAGS = {
    amd64 = {
        "-m64",
        -- No red zone below RSP -- required for kernel interrupt handlers.
        -- Userland targets can override/drop this via their own flags.
        "-mno-red-zone",
    },
    arm64 = {
        "-march=armv8-a",
    },
    riscv64 = {
        "-march=rv64imafdc",
        "-mabi=lp64d",
    },
}

-- ==============================================================================
-- Helper functions
-- ==============================================================================

-- Return the LLVM target triple for the currently configured architecture.
-- Safe to call from both description scope (loading phase) and script-scope
-- callbacks (build phase).
function eteleos_get_triple()
    local arch = get_config("target_arch") or "amd64"
    return ETELEOS_TARGET_TRIPLES[arch]
        or ("unknown-" .. arch .. "-unknown-openbsd")
end

-- Return the arch-specific cflags list (or an empty table for unknown arch).
-- Used inside on_load() callbacks where the target object is available.
function eteleos_get_arch_cflags()
    local arch = get_config("target_arch") or "amd64"
    return ETELEOS_ARCH_CFLAGS[arch] or {}
end

-- Return the GCC cross-prefix for the current target architecture.
-- Returns an empty string when the arch is unknown (native build assumed).
function eteleos_get_cross_prefix()
    local arch = get_config("target_arch") or "amd64"
    return ETELEOS_CROSS_PREFIXES[arch] or ""
end

-- Return true when the target arch differs from the host arch.
-- Uses BSD naming on both sides for comparison.
-- NOTE: os.arch() returns GNU/LLVM names (x86_64, aarch64, riscv64).
-- This function is called from script-scope callbacks (on_load, on_build)
-- where os.arch() is always available.
function eteleos_is_cross()
    local target = get_config("target_arch") or "amd64"
    local gnu_to_bsd = {
        x86_64  = "amd64",
        aarch64 = "arm64",
        riscv64 = "riscv64",
    }
    local host_bsd = gnu_to_bsd[os.arch()] or os.arch()
    return host_bsd ~= target
end

-- Raise a hard error if target_arch is set to a value we no longer support.
-- Called from tools/xmake.lua after options.lua is loaded.
function eteleos_check_arch()
    local arch = get_config("target_arch")
    if not arch then return end
    if not ETELEOS_TARGET_TRIPLES[arch] then
        local supported = table.concat(ETELEOS_SUPPORTED_ARCHS, ", ")
        raise("EteleOS: unsupported target_arch '%s'. Supported: %s",
              arch, supported)
    end
end

-- Append multiple flags to a target (cxflags, ldflags, or asflags).
-- Convenience wrapper so callers do not have to unpack tables manually.
--   eteleos_add_flags(target, "cxflags", {"-Wall", "-Wextra"})
function eteleos_add_flags(target, kind, flags)
    if type(flags) == "table" then
        for _, f in ipairs(flags) do
            target:add(kind, f, {force = true})
        end
    elseif type(flags) == "string" then
        target:add(kind, flags, {force = true})
    end
end
