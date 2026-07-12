/*
 EteleOS: xmake.lua, time wirte: 2026/07/10
 This file uses the Apache-2.0 license
*/

--[[
================================================================================
 EteleOS :: root xmake.lua -- pure orchestrator
================================================================================

This file does ONLY project-wide orchestration.

tools/xmake.lua is responsible for loading helpers.lua, options.lua,
compiler.lua, rules.lua and toolchains.lua and making everything they
declare available to every module included after it -- which is why
"tools" is always the first entry in the module list below.

NOTE ON LOCATION: this file lives at the repository ROOT. EteleOS calls the
whole source tree "src" (OpenBSD convention, as in /usr/src), but there is
no literal src/ subdirectory in this repository -- tools/, include/,
libraries/, kernel/, resources/, userland/, gui/, installer/, tests/,
ports/, configs/ and docs/ already live directly at the repo root.
--------------------------------------------------------------------------------
--]]

-- Require a reasonably recent xmake so every API used across this project
-- (custom toolchains, mode.releasedbg/minsizerel, LTO/sanitizer policies,
-- etc.) is guaranteed to exist. Bump this if you rely on something newer.
set_xmakever("2.8.5")

-- ==============================================================================
-- Project identity
-- ==============================================================================
set_project("EteleOS")

-- Placeholder version -- replace with EteleOS's real versioning scheme once
-- one is decided; this only needs to be *some* valid semver for now.
set_version("0.1.0", {build = "%Y%m%d"})

-- ==============================================================================
-- Global policies
-- ==============================================================================
-- We are cross-compiling an entire OS: a flag that xmake silently drops
-- because it "looks unsupported" is a much worse failure mode here than a
-- loud build error, so auto-ignoring is turned off project-wide.
set_policy("check.auto_ignore_flags", false)

-- Stream compiler/linker warnings as they happen instead of only at the end.
set_policy("build.warning", true)

-- Object-file build cache (ccache-style). EteleOS has no add_requires()
-- package dependencies, so the separate package-lock policies do not
-- apply here.
set_policy("build.ccache", true)

-- ==============================================================================
-- Build modes
-- ==============================================================================
-- Required: debug, release. Extended: releasedbg, minsizerel. Per-mode
-- optimize/symbols levels come from these built-in rules; nothing here
-- overrides them -- that stays out of the root file entirely.
add_rules("mode.debug", "mode.release", "mode.releasedbg", "mode.minsizerel")

-- ==============================================================================
-- Directories: build / install / package / cache
-- ==============================================================================
-- Keep every generated artifact under build/, never inside the source tree.
set_config("builddir", "$(projectdir)/build")

-- Configurable install root; override any time with `xmake f --installdir=`.
set_config("installdir", "$(projectdir)/build/install")

-- xmake's own package cache/install locations are normally read from the
-- XMAKE_PKG_CACHEDIR / XMAKE_PKG_INSTALLDIR environment variables at
-- process start-up. Point them at project-local folders so a full EteleOS
-- checkout stays self-contained -- but never clobber a value already set
-- (e.g. by CI). NOTE: because these are env vars, this only reliably
-- affects xmake processes launched *after* this script runs; export the
-- same variables in your shell/CI beforehand if you need it to apply to
-- the current invocation too.
local pkgroot = path.join(os.scriptdir(), "build", ".xmake-pkg")
if not os.getenv("XMAKE_PKG_CACHEDIR") then
    os.setenv("XMAKE_PKG_CACHEDIR", path.join(pkgroot, "cache"))
end
if not os.getenv("XMAKE_PKG_INSTALLDIR") then
    os.setenv("XMAKE_PKG_INSTALLDIR", path.join(pkgroot, "packages"))
end

-- ==============================================================================
-- Shared include path
-- ==============================================================================
-- include/ holds the headers shared across kernel, libraries and userland
-- (per README.md).
add_includedirs("$(projectdir)/include")

-- ==============================================================================
-- Submodules
-- ==============================================================================
-- Fixed dependency order mandated by the build spec -- do not reorder
-- without a clear technical reason. "tools" is loaded first because it now
-- owns every toolchain/option/compiler/rule declaration that every other
-- module depends on. Each module is only pulled in once its OWN xmake.lua
-- actually exists, so this file keeps working while modules are converted
-- from BSD Make one at a time instead of all at once.
local modules = {
    "tools",
    "include",
    "libraries",
    "kernel",
    "resources",
    "userland",
    "gui",
    "installer",
    "tests",
    "ports",
    "configs",
    "docs",
}

for _, mod in ipairs(modules) do
    local modfile = path.join(os.scriptdir(), mod, "xmake.lua")
    if os.isfile(modfile) then
        includes(mod)
    else
        wprint("eteleos: skipping '%s' (no xmake.lua there yet)", mod)
    end
end
