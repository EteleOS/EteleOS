--[[
PeteleOS: tools/tasks.lua, time write: 2026/07/26
This file uses the Apache-2.0 license
--]]

--[[
Long-referenced but, until this revision, never actually implemented:
userland/xmake.lua, kernel/xmake.lua, and three of the tools/gen/gen_*.lua
generator scripts themselves all say regeneration is "also wired up as the
`os-regen-<module>` task in tools/tasks.lua" -- this file is that
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

    xmake os-regen-userland
    xmake os-regen-kernel
    xmake os-regen-libraries
    xmake os-regen-tests
    xmake os-regen-gui
    xmake os-regen-all        -- runs all five, in one command
--]]

-- Shared by every os-regen-* task below. Confirmed safe to call from a
-- plain helper function (unlike import()/find_tool()/os.execv() -- see the
-- long comment above): only touches path.join/os.isfile/os.projectdir.
local function os_resolve_script(name, script_rel)
    local scriptpath = path.join(os.projectdir(), script_rel)
    if not os.isfile(scriptpath) then
        print(string.format("os-regen-%s: generator script not found at %s", name, scriptpath))
        return nil
    end
    return scriptpath
end

task("os-regen-userland")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("os-regen-userland: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_userland_manifest.lua` by hand instead")
            return
        end
        local scriptpath = os_resolve_script("userland", "tools/gen/gen_userland_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake os-regen-userland",
        description = "Regenerate userland/generated_manifest.lua from userland/ Makefiles",
    })
task_end()

task("os-regen-kernel")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("os-regen-kernel: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_kernel_manifest.lua` by hand instead")
            return
        end
        local scriptpath = os_resolve_script("kernel", "tools/gen/gen_kernel_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake os-regen-kernel",
        description = "Regenerate kernel/generated_manifest.lua by running real config(8) per arch",
    })
task_end()

task("os-regen-libraries")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("os-regen-libraries: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_libraries_manifest.lua` by hand instead")
            return
        end
        local scriptpath = os_resolve_script("libraries", "tools/gen/gen_libraries_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake os-regen-libraries",
        description = "Regenerate libraries/generated_manifest.lua (shlib_version lookup table)",
    })
task_end()

task("os-regen-tests")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("os-regen-tests: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_tests_manifest.lua` by hand instead")
            return
        end
        local scriptpath = os_resolve_script("tests", "tools/gen/gen_tests_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake os-regen-tests",
        description = "Regenerate tests/generated_manifest.lua from tests/ Makefiles",
    })
task_end()

task("os-regen-gui")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("os-regen-gui: could not find the xmake binary on PATH -- "
                  .. "run `xmake lua tools/gen/gen_gui_manifest.lua` by hand instead")
            return
        end
        local scriptpath = os_resolve_script("gui", "tools/gen/gen_gui_manifest.lua")
        if scriptpath then
            os.execv(xm.program, {"lua", scriptpath})
        end
    end)
    set_menu({
        usage = "xmake os-regen-gui",
        description = "Regenerate gui/generated_manifest.lua from gui/MODULES",
    })
task_end()

task("os-regen-all")
    on_run(function ()
        import("lib.detect.find_tool")
        local xm = find_tool("xmake")
        if not xm then
            print("os-regen-all: could not find the xmake binary on PATH -- "
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
            local scriptpath = os_resolve_script(spec[1], spec[2])
            if scriptpath then
                os.execv(xm.program, {"lua", scriptpath})
            end
        end
    end)
    set_menu({
        usage = "xmake os-regen-all",
        description = "Regenerate every module's generated_manifest.lua",
    })
task_end()

task("os-verify-rpcgen-output")
    on_run(function ()
        import("lib.detect.find_tool")
        local sh = find_tool("sh")
        local scriptpath = os_resolve_script("rpcgen-output", "tools/verify-rpcgen-output.sh")
        if not sh then
            print("os-verify-rpcgen-output: could not find sh on PATH")
        elseif scriptpath then
            os.execv(sh.program, {scriptpath})
        end
    end)
    set_menu({
        usage = "xmake os-verify-rpcgen-output",
        description = "Verify committed RPC generated C/header output using pinned rpcgen",
    })
task_end()
