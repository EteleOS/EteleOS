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

-- Confirmed by testing: wprint/cprint are unavailable not just at
-- description scope, but also inside on_load/on_build during xmake f's
-- own internal target pre-check pass (_check_targets) on a project this
-- size -- a stricter environment than a normal `xmake build` invocation
-- of the same callback. Shimmed as LOCALS (not modifying the globals) so
-- every on_load/on_build closure later in this same file resolves them
-- via lexical scoping, which works regardless of which of the two
-- environments is actually active at call time -- falls through to the
-- real wprint/cprint when they do exist, so normal builds keep the
-- colored output.
local wprint = wprint or function(fmt, ...) print(string.format(fmt, ...)) end
local cprint = cprint or function(fmt, ...) print(string.format((fmt:gsub("%${[%w_]+}", "")), ...)) end

-- ==============================================================================
-- Load build framework sub-modules in dependency order
-- ==============================================================================

-- 1. Helper tables and functions (ETELEOS_* globals, eteleos_* functions).
--    Everything else depends on this. Description-scope-to-description-
--    scope only (confirmed: this genuinely works) -- for script-scope
--    (on_load/on_build/...) use, see tools/modules/eteleos/helpers.lua
--    and the add_moduledirs()/import() pair right below instead; a plain
--    global here is NOT visible from inside any callback, confirmed by
--    isolated testing against a real xmake v3.0.9 build.
includes("helpers.lua")

-- Registers tools/modules/ as an import() search path, so any on_load/
-- on_build/after_install/on_test callback anywhere in this project can do
-- `import("eteleos.helpers")` to reach the script-scope twin of the table
-- above (tools/modules/eteleos/helpers.lua).
add_moduledirs(path.join(os.scriptdir(), "modules"))

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
        import("eteleos.helpers")
        local arch   = get_config("target_arch") or "amd64"
        local triple = helpers.eteleos_get_triple()
        local tc     = get_config("toolchain") or "unknown"
        cprint("${green}EteleOS build framework${clear}")
        cprint("  target arch : %s  ->  %s", arch, triple)
        cprint("  toolchain   : %s", tc)
        cprint("  build mode  : %s", get_config("mode") or "debug")
        cprint("  lto         : %s", tostring(has_config("lto")))
        cprint("  asan        : %s", tostring(has_config("asan")))
        cprint("  ubsan       : %s", tostring(has_config("ubsan")))
        cprint("  werror      : %s", tostring(has_config("werror")))
        cprint("  cross build : %s", tostring(helpers.eteleos_is_cross()))
    end)
target_end()
