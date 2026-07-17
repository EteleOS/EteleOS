--[[
================================================================================
 EteleOS: tools/xmake.lua, time write: 2026/07/10
 This file uses the Apache-2.0 license
================================================================================

This file is the Build Framework of EteleOS. It owns every project-wide
piece of build infrastructure:
  - helper tables and utility functions        (helpers.lua)
  - all option() declarations                  (options.lua)
  - compiler / linker / assembler defaults     (compiler.lua)
  - all rule() declarations                    (rules.lua)
  - all toolchain() declarations               (toolchains.lua)

Loading order matters:
  helpers.lua     → must be first; toolchains.lua and rules.lua close over
                    the ETELEOS_* globals it defines.
  options.lua     → must be before compiler.lua (has_config() checks options).
  compiler.lua    → must be before rules.lua (rules check has_config too).
  rules.lua       → must be before toolchains.lua (rules reference helpers).
  toolchains.lua  → last, after all helpers and options are in scope.

Constraints (build spec, section 3):
  - This file MUST NOT build any target.
  - It must not compile, link or install any binary.

Usage in sibling modules (after tools/ is loaded first by root xmake.lua):
  Every module's xmake.lua gains access to the project-global entities
  declared here (option(), rule(), toolchain()) because xmake registers them
  at project level, not at file scope. Modules apply them like so:

      target("sh")
          set_kind("binary")
          add_rules("eteleos.base", "eteleos.userland", "eteleos.strip_release")
          add_files("src/*.c")
--------------------------------------------------------------------------------
--]]

-- ==============================================================================
-- Load build framework sub-modules in dependency order
-- ==============================================================================

-- 1. Helper tables and functions (ETELEOS_* globals, eteleos_* functions).
--    Everything else depends on this.
includes("helpers.lua")

-- 2. All option() declarations. Must precede compiler.lua (which calls
--    has_config() / get_config() on those options).
includes("options.lua")

-- 3. Compiler / linker / assembler defaults (set_config + set_policy calls).
--    Must follow options.lua; must precede rules.lua and toolchains.lua.
includes("compiler.lua")

-- 4. All rule() declarations. Must follow compiler.lua and helpers.lua;
--    on_load callbacks call eteleos_* helpers and has_config().
includes("rules.lua")

-- 5. All toolchain() declarations. Must follow helpers.lua (uses
--    ETELEOS_TARGET_TRIPLES) and options.lua (reads target_arch / sysroot).
includes("toolchains.lua")

-- ==============================================================================
-- Architecture validation
-- ==============================================================================
-- Raise a hard error now if the user passed an unsupported --target_arch
-- so the failure is immediate and obvious rather than a confusing
-- compiler error later.
eteleos_check_arch()

-- ==============================================================================
-- Phony diagnostic target
-- ==============================================================================
-- Builds nothing. Run with: xmake build eteleos-framework
-- Prints a summary of the active build configuration.
target("eteleos-framework")
    set_kind("phony")
    set_default(false)
    on_build(function (target)
        local arch   = get_config("target_arch") or "amd64"
        local triple = ETELEOS_TARGET_TRIPLES[arch] or "unknown"
        local tc     = get_config("toolchain") or "unknown"
        cprint("${green}EteleOS build framework${clear}")
        cprint("  target arch : %s  ->  %s", arch, triple)
        cprint("  toolchain   : %s", tc)
        cprint("  build mode  : %s", get_config("mode") or "debug")
        cprint("  lto         : %s", tostring(has_config("lto")))
        cprint("  asan        : %s", tostring(has_config("asan")))
        cprint("  ubsan       : %s", tostring(has_config("ubsan")))
        cprint("  werror      : %s", tostring(has_config("werror")))
        cprint("  cross build : %s", tostring(eteleos_is_cross()))
    end)
target_end()
