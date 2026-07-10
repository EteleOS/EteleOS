/*
EteleOS: xmake.lua, time wirte: 2026/07/10
This file uses the Apache-2.0 license
*/

--[[
================================================================================
 EteleOS :: tools/compiler.lua
================================================================================

Project-global compiler, linker and assembler default configuration.
Loaded by tools/xmake.lua (after options.lua).

Key points about xmake scoping that drive the design of this file:
  - set_config() writes to the project-wide config cache -- equivalent to
    the user running `xmake f --key=value` -- so it takes effect globally
    across ALL modules regardless of where in the include tree this file sits.
  - set_policy() at the root scope of a sub-file is scope-limited to that
    sub-file and its children. Policies that must apply to ALL modules (e.g.
    build.warning, build.ccache) are therefore set in the ROOT xmake.lua.
    Policies set here only affect targets defined within the tools/ subtree,
    which is intentional for sanitizer activation (kernel must NOT inherit
    hosted sanitizer policies).

Nothing in this file compiles any source file or declares any target.
--------------------------------------------------------------------------------
--]]

-- ==============================================================================
-- Default toolchain
-- ==============================================================================
-- Drive the default toolchain from the eteleos_toolchain option. This is
-- equivalent to `xmake f --toolchain=eteleos-clang` but persisted in
-- xmake.lua so fresh checkouts get the right default automatically.
-- The toolchain() declarations themselves live in tools/toolchains.lua.
local _tc = get_config("eteleos_toolchain") or "eteleos-clang"
set_config("toolchain", _tc)

-- ==============================================================================
-- Compiler / linker / assembler binary defaults
-- ==============================================================================
-- These act as fallbacks when no custom toolchain is active, and also drive
-- the `xmake f --cc / --cxx / --ld ...` CLI defaults for the Clang preset.
-- Switch to GCC equivalents when the eteleos-gcc preset is selected.
if _tc == "eteleos-gcc" then
    set_config("cc",     "gcc")
    set_config("cxx",    "g++")
    set_config("ld",     "g++")
    set_config("ar",     "ar")
    set_config("as",     "gcc")
    set_config("strip",  "strip")
    set_config("ranlib", "ranlib")
else
    -- Default: Clang/LLVM
    set_config("cc",     "clang")
    set_config("cxx",    "clang++")
    set_config("ld",     "clang++")
    set_config("ar",     "llvm-ar")
    set_config("as",     "clang")
    set_config("strip",  "llvm-strip")
    set_config("ranlib", "llvm-ranlib")
end

-- ==============================================================================
-- LTO policy (tools/ scope)
-- ==============================================================================
-- Activating LTO via a policy lets XMake coordinate the compiler, linker and
-- archiver flags automatically. This policy is scope-limited to the tools/
-- subtree here; other modules (libraries/, kernel/, userland/, ...) that want
-- LTO should either add the eteleos.lto rule (declared in rules.lua) to their
-- targets, or add their own set_policy("build.optimization.lto", true).
if has_config("lto") then
    set_policy("build.optimization.lto", true)
end

-- ==============================================================================
-- Sanitizer policies (tools/ scope)
-- ==============================================================================
-- Scope-limited to tools/ intentionally: the kernel must NOT inherit hosted
-- sanitizer runtime dependencies. Other modules that want sanitizers should
-- add the eteleos.asan / eteleos.ubsan rules (declared in rules.lua) to
-- their specific targets, which injects the raw -fsanitize=... flags without
-- relying on xmake's global policy mechanism.
if has_config("asan") then
    set_policy("build.sanitizer.address", true)
end
if has_config("ubsan") then
    set_policy("build.sanitizer.undefined", true)
end
