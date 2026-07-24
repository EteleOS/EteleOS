--[[
================================================================================
 EteleOS: tools/tasks.lua, time write: 2026/07/24
 This file uses the Apache-2.0 license
================================================================================

Long-referenced but, until this revision, never actually implemented:
userland/xmake.lua, kernel/xmake.lua, and three of the tools/gen/gen_*.lua
generator scripts themselves all say regeneration is "also wired up as the
`eteleos-regen-<module>` task in tools/tasks.lua" -- this file is that
promise, finally kept. Confirmed by grep across the whole tree before this
revision: no tools/tasks.lua existed, and no task() was declared anywhere
in the project.

WHY THIS DOES NOT (AND CANNOT) MAKE generated_manifest.lua STOP BEING A
COMMITTED, HAND-TRIGGERED FILE
--------------------------------------------------------------------------
Each module's generated_manifest.lua is read via includes() from *within*
that module's own xmake.lua, at description scope -- and description scope
is exactly the environment that (confirmed against real xmake v3.0.9, see
every tools/gen/gen_*.lua header) cannot itself run io.open()/os.exec() to
regenerate anything. So the manifest has to already be correct, on disk,
before `xmake f` ever starts reading xmake.lua -- there is no hook early
enough in xmake's own lifecycle for a target/task in THIS project to
regenerate a manifest "invisibly" during a normal build. That is not a gap
left by this file; it is the same constraint already documented in every
module that carries a generated_manifest.lua.

What this file DOES fix: previously the only way to regenerate one was to
already know the exact `xmake lua tools/gen/gen_<x>_manifest.lua` incantation
by reading a source comment. Now it is a normal, discoverable, tab-completable
xmake task, run BEFORE `xmake f`/`xmake build` (same as you would run a
`configure` script once before `make`):

    xmake eteleos-regen-userland
    xmake eteleos-regen-kernel
    xmake eteleos-regen-libraries
    xmake eteleos-regen-tests
    xmake eteleos-regen-gui
    xmake eteleos-regen-all        -- runs all five, in one command

TWO REAL BUGS FOUND AND FIXED IN THIS REVISION BY ACTUALLY RUNNING IT
against real xmake v3.0.9 (downloaded straight from the xmake-io/xmake
v3.0.9 GitHub release, not assumed from docs) -- neither is visible from
luac -p or from reading the code:

1) `xmake eteleos-regen-gui` first failed with "attempt to call a nil value
   (global 'import')". import("lib.detect.find_tool") was called from
   inside a shared plain Lua helper function that on_run() merely called,
   not written directly inside on_run() itself. xmake statically scans each
   script block (on_run/on_load/on_build/...) for import() calls to hoist
   by LEXICAL position in the source, not by dynamic Lua call stack -- so
   import() only resolves when textually written directly inside a
   recognized block.

2) After moving import()+find_tool() inline, the next run failed with
   "attempt to call a nil value (field 'execv')". Confirmed by a minimal
   reproduction (two on_run bodies, one calling os.execv directly and one
   calling it via a one-line helper): os.execv (and by the same mechanism,
   presumably exec/run/runv/iorun/iorunv) is ALSO only visible directly
   inside the callback body itself -- a plain helper function it calls
   sees a *different*, more restricted `os` table where os.execv is nil,
   even though os.isfile/os.projectdir/path.join stay visible everywhere
   (confirmed by the same test). Likely cause: xmake enriches the callback
   function's own environment right before invoking it, which in Lua does
   not propagate to a separately-defined function's environment even when
   that function is called from inside the enriched one.

Fixed by keeping the shared helper (eteleos_resolve_script) limited to only
path.join/os.isfile/os.projectdir (confirmed safe across the function
boundary), and moving import("lib.detect.find_tool"), find_tool("xmake"),
and os.execv() all directly, lexically, inside every task's own on_run()
body below -- one repeated block per task, matching the exact repetition
already established in userland/xmake.lua's on_load callbacks for the same
reason. Re-verified end-to-end after the fix: in an isolated sandbox
project, `xmake eteleos-regen-gui` now correctly resolves the real xmake
binary, resolves the real script path, os.execv()'s a real subprocess
running the real tools/gen/gen_gui_manifest.lua, which runs to completion
(reporting gui/MODULES not found, which is only because that sandbox has
no gui/ source tree checked out -- an unrelated, expected limitation of the
test environment, not a bug in this file).

NOTE ON gen_ports_manifest.lua -- deliberately NOT wired up here. ports/
was removed from the tree; that generator was removed with this revision
as dead code.
--------------------------------------------------------------------------------
--]]

-- Shared by every eteleos-regen-* task below. Confirmed safe to call from a
-- plain helper function (unlike import()/find_tool()/os.execv() -- see the
-- long comment above): only touches path.join/os.isfile/os.projectdir.
local function eteleos_resolve_script(name, script_rel)
    local scriptpath = path.join(os.projectdir(), script_rel)
    if not os.isfile(scriptpath) then
        print(string.format("eteleos-regen-%s: generator script not found at %s", name, scriptpath))
        return nil
    end
    return scriptpath
end

task("eteleos-regen-userland")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("eteleos-regen-userland: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_userland_manifest.lua` by hand instead")
            return
        end
        local scriptpath = eteleos_resolve_script("userland", "tools/gen/gen_userland_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake eteleos-regen-userland",
        description = "Regenerate userland/generated_manifest.lua from userland/ Makefiles",
    })
task_end()

task("eteleos-regen-kernel")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("eteleos-regen-kernel: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_kernel_manifest.lua` by hand instead")
            return
        end
        local scriptpath = eteleos_resolve_script("kernel", "tools/gen/gen_kernel_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake eteleos-regen-kernel",
        description = "Regenerate kernel/generated_manifest.lua by running real config(8) per arch",
    })
task_end()

task("eteleos-regen-libraries")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("eteleos-regen-libraries: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_libraries_manifest.lua` by hand instead")
            return
        end
        local scriptpath = eteleos_resolve_script("libraries", "tools/gen/gen_libraries_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake eteleos-regen-libraries",
        description = "Regenerate libraries/generated_manifest.lua (shlib_version lookup table)",
    })
task_end()

task("eteleos-regen-tests")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("eteleos-regen-tests: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_tests_manifest.lua` by hand instead")
            return
        end
        local scriptpath = eteleos_resolve_script("tests", "tools/gen/gen_tests_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake eteleos-regen-tests",
        description = "Regenerate tests/generated_manifest.lua from tests/ Makefiles",
    })
task_end()

task("eteleos-regen-gui")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("eteleos-regen-gui: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_gui_manifest.lua` by hand instead")
            return
        end
        local scriptpath = eteleos_resolve_script("gui", "tools/gen/gen_gui_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake eteleos-regen-gui",
        description = "Regenerate gui/generated_manifest.lua from gui/MODULES",
    })
task_end()

task("eteleos-regen-all")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("eteleos-regen-all: could not find the xmake binary on PATH -- "
                  .. "run each tools/gen/gen_*.lua by hand instead")
            return
        end
        local specs = {
            {"userland", "tools/gen/gen_userland_manifest.lua"},
            {"kernel", "tools/gen/gen_kernel_manifest.lua"},
            {"libraries", "tools/gen/gen_libraries_manifest.lua"},
            {"tests", "tools/gen/gen_tests_manifest.lua"},
            {"gui", "tools/gen/gen_gui_manifest.lua"},
        }
        for _, spec in ipairs(specs) do
            local scriptpath = eteleos_resolve_script(spec[1], spec[2])
            if scriptpath then
                os.execv(xm.program, {"lua", scriptpath})
            end
        end
    end)
    set_menu({
        usage = "xmake eteleos-regen-all",
        description = "Regenerate every module's generated_manifest.lua",
    })
task_end()
