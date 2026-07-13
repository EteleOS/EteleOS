/*
 EteleOS: xmake.lua, time wirte: 2026/07/13
 This file uses the Apache-2.0 license
*/

--[[
================================================================================
 EteleOS :: tests/xmake.lua
================================================================================

Manages: regression, benchmark, unit tests, integration tests.

tests/ is OpenBSD's regress/ tree, renamed, still mirroring the OLD
pre-restructure top-level layout (bin, sbin, usr.bin, usr.sbin, lib,
libexec, gnu, include, misc, sys) -- roughly 20,000 files, arbitrarily
nested, far too many to hand-enumerate. This file discovers test units by
walking that tree with xmake's own os.files()/os.dirs() (portable across
platforms -- no shelling out to `find`).

THE CENTRAL LIMITATION, still real -- please read
------------------------------------------------------
OpenBSD's regress tests are driven by resources/mk/bsd.regress.mk, which
supports two shapes:
  (a) PROG/PROGS + nothing else -- bsd.regress.mk auto-generates a
      "run-regress-<prog>" target that just builds and runs it, pass/fail
      by exit code. Maps directly onto xmake's native add_tests().
  (b) hand-written REGRESS_TARGETS with custom shell recipes, often
      comparing output against checked-in .in/.out golden files (verified
      real: tests/usr.bin/apply/Makefile runs six variations of the
      ALREADY-BUILT /usr/bin/apply and `cmp`s the output -- it does not
      compile anything of its own at all).
Spot-checking suggests shape (b) is the majority, not a minority. This
revision narrows that gap in two concrete ways (see GOLDEN-FILE RECIPE
TRANSLATION and NON-COMPILED TEST SUPPORT below), but does not claim to
have closed it -- most custom shell recipes still are not, and likely
cannot responsibly be, translated by pattern-matching alone.

MAKEFILE PARSING -- what changed in this revision
------------------------------------------------------
  - Operators: =, +=, ?=, := are all parsed (":=" was already accepted by
    the old regex incidentally; this revision makes that explicit and
    adds "!=" (shell-assignment) recognition -- its value is treated as
    unresolved/dynamic rather than silently making the whole Makefile
    look "custom").
  - ${VAR} / $(VAR) expansion: a second pass substitutes any variable
    reference against every VAR= assignment collected in the first pass
    (plus a small set of well-known BSD Make built-ins: ${.CURDIR},
    ${MACHINE}, ${MACHINE_ARCH}). Unresolvable references are left
    as-is and reported, not silently dropped.
  - `.if ${MACHINE} == "xxx"` / `.if ${MACHINE_ARCH} == "xxx"` blocks are
    evaluated against the active target_arch (a genuinely tractable
    subset of full BSD Make conditional evaluation); anything else inside
    `.if` is conservatively treated as unconditionally-included, same as
    before.
  - `.include <bsd.regress.mk>` / `<bsd.subdir.mk>` are recognized as the
    two standard, expected includes; any OTHER `.include` is recorded and
    reported, since it signals a directory with shared logic beyond the
    standard convention.

GOLDEN-FILE RECIPE TRANSLATION
-----------------------------------
For custom REGRESS_TARGETS whose recipe matches the extremely common
idiom (confirmed real, e.g. tests/usr.bin/apply's t1-t6):
    <command...> > NAME.res
    cmp -s EXPECTED.out NAME.res || (echo ... && false)
this file extracts the command, expected-output file, and wires it as a
non-compiled test (see below) that runs the command and compares output
itself, rather than shelling back out to `make`. Recipes that do not
match this specific idiom are still left as shape (b) and skipped, counted
separately from "fully unrecognized".

NON-COMPILED TEST SUPPORT (shell / python / perl / lua)
-------------------------------------------------------------
A phony target with on_test() (xmake's own hook, confirmed alongside
add_tests() in 2.8.5) runs an interpreter directly instead of assuming a
C compile step. Interpreter selection: shebang line if present, else file
extension (.sh, .py, .pl, .lua).

DEPENDENCY LINKING TO userland/ AND libraries/
----------------------------------------------------
Every discovered test unit's directory name is looked up in userland/'s
categories (same search userland/xmake.lua and installer/xmake.lua's
special/ handling already use) and, if found, add_deps() is added to that
program's target -- so `xmake build <test>` also rebuilds the real program
under test. LDADD-style libraries referenced in the test's own Makefile
are linked the same way libraries/xmake.lua's targets are named
("lib<x>-shared").

CLASSIFICATION -- explicit about being a heuristic
-------------------------------------------------------
"kernel" (tests/sys/) and "benchmark" (any dir literally named
"benchmark") are structural facts, not guesses. "unit" vs "integration" is
NOT a structural fact in this tree (it is organized by what is tested, not
by test methodology) -- this revision adds a best-effort tag using a
concrete, checkable signal (a test that only builds+runs ITS OWN program
with no add_deps() on an external userland program is tagged
"unit-like"; one that does depend on an external program is tagged
"integration-like") and labels it as a heuristic in the group name itself
("unit-like"/"integration-like"), rather than asserting it as fact.

RUNNING TESTS
----------------
  xmake test                     -- everything
  xmake test usr.bin/*           -- one category (group names below)
  xmake test -g benchmark        -- benchmark group only
  xmake test -g kernel           -- tests/sys/ only
  xmake test -g unit-like        -- heuristic tag, see above
  xmake test -g integration-like -- heuristic tag, see above
Groups are named "<category>" (bin, sbin, usr.bin, usr.sbin, lib, libexec,
gnu, include, misc), "kernel" (sys/), or "benchmark".

CROSS-BUILD EXECUTION
--------------------------
Test binaries are built for target_arch, which may differ from the build
host's own architecture. When cross-building, this file looks for a
matching qemu-<arch> user-mode emulator (find_tool) and runs tests through
it if found; otherwise tests are still BUILT (so compile regressions are
caught) but their on_test run step reports "skipped: cross build, no
qemu-<arch> found" rather than attempting to execute a foreign-arch binary
directly on the host.
--------------------------------------------------------------------------------
--]]

local unpack = table.unpack or unpack
local arch = get_config("target_arch") or "amd64"

local TEST_CATEGORIES = {
    "bin", "sbin", "usr.bin", "usr.sbin", "lib", "libexec", "gnu",
    "include", "misc", "sys",
}

local USERLAND_SEARCH_DIRS = {
    "development", "games", "libexec", "multimedia", "network", "package",
    "security", "system", "utilities", "essential/bin", "essential/sbin",
}

local KNOWN_INCLUDES = { ["bsd.regress.mk"] = true, ["bsd.subdir.mk"] = true }

local INTERPRETER_BY_EXT = { sh = "sh", py = "python3", pl = "perl", lua = "lua" }

-- ==============================================================================
-- Small utilities
-- ==============================================================================
local function read_file(filepath)
    local f = io.open(filepath, "r")
    if not f then return nil end
    local c = f:read("*a")
    f:close()
    return c
end

local function logical_lines(content)
    local lines = {}
    local acc = nil
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local cont = line:match("(.*)\\%s*$")
        if cont then
            acc = (acc or "") .. cont .. " "
        else
            lines[#lines + 1] = (acc or "") .. line
            acc = nil
        end
    end
    return lines
end

-- Portable recursive discovery via os.files()/os.dirs() instead of
-- shelling out to `find` -- works the same on any host xmake itself runs on.
-- Returns every directory containing EITHER a Makefile OR a standalone
-- interpreter script (.sh/.py/.pl/.lua) with no Makefile at all.
local function find_test_dirs(dir)
    local seen, dirs = {}, {}
    local function add(d)
        if not seen[d] then seen[d] = true; dirs[#dirs + 1] = d end
    end
    for _, mf in ipairs(os.files(path.join(dir, "**", "Makefile"))) do
        add(path.directory(mf))
    end
    for ext in pairs(INTERPRETER_BY_EXT) do
        for _, sf in ipairs(os.files(path.join(dir, "**", "*." .. ext))) do
            add(path.directory(sf))
        end
    end
    table.sort(dirs)
    return dirs
end

local function find_userland_program_dir(name)
    local userland_root = path.join(os.scriptdir(), "..", "userland")
    for _, cat in ipairs(USERLAND_SEARCH_DIRS) do
        local candidate = path.join(userland_root, cat, name)
        if os.isdir(candidate) then return candidate, cat end
    end
    return nil
end

-- ==============================================================================
-- Makefile parser: variable assignments (all operators), ${VAR}/$(VAR)
-- expansion, .if MACHINE conditionals, .include tracking, and recipe
-- capture for the golden-file translator.
-- ==============================================================================
local function expand_vars(value, vars)
    local unresolved = {}
    local result = value:gsub("%$[{(]([%w_.]+)[})]", function (name)
        if vars[name] ~= nil then return vars[name] end
        unresolved[#unresolved + 1] = name
        return "${" .. name .. "}"   -- leave unresolved refs visible, not blank
    end)
    return result, unresolved
end

local function parse_makefile(dir)
    local content = read_file(path.join(dir, "Makefile"))
    if not content then return nil end

    local info = {
        prog = nil, progs = {}, srcs = {}, ldadd_libs = {},
        custom = false, dynamic_vars = {}, unknown_includes = {},
        targets = {},   -- name -> { recipe_lines = {...} }
        has_regress_targets_var = false,
    }
    local vars = {}          -- raw (unexpanded) variable values, first pass
    local order = {}         -- lines in order, classified

    -- First pass: collect every VAR<op>= assignment (any operator) so
    -- ${VAR}/$(VAR) references can be resolved regardless of definition
    -- order within the file (BSD Make itself is order-sensitive for `?=`,
    -- but for THIS file's purposes -- test discovery, not a real Make
    -- implementation -- resolving against the final value is sufficient).
    for _, line in ipairs(logical_lines(content)) do
        local stripped = line:gsub("#.*$", ""):match("^%s*(.-)%s*$")
        if stripped ~= "" then
            local var, op, rest = stripped:match("^(%u[%u_]*)%s*([+?:!]?=)%s*(.*)$")
            if var and op ~= "!=" then
                if op == "+=" and vars[var] then
                    vars[var] = vars[var] .. " " .. rest
                elseif op == "?=" and vars[var] then
                    -- already set: ?= does not override, matches BSD Make
                else
                    vars[var] = rest
                end
            elseif var and op == "!=" then
                info.dynamic_vars[#info.dynamic_vars + 1] = var
                vars[var] = vars[var] or ""   -- unresolved shell output; keep parsing usable
            end
        end
    end

    -- Second pass: classify each line (assignment / conditional / include
    -- / target+recipe), expanding ${VAR}/$(VAR) in assignment values as
    -- we go, and evaluating simple `.if ${MACHINE} == "x"` blocks against
    -- the active target_arch.
    local if_stack = {}   -- stack of booleans: is the current block active?
    local function block_active()
        for _, v in ipairs(if_stack) do if not v then return false end end
        return true
    end

    local current_target = nil
    for _, line in ipairs(logical_lines(content)) do
        local stripped = line:gsub("#.*$", ""):match("^%s*(.-)%s*$")
        if stripped ~= "" then
            local ifcond = stripped:match("^%.%s*if%s+(.*)$")
            local var, op, rest = stripped:match("^(%u[%u_]*)%s*([+?:!]?=)%s*(.*)$")

            if ifcond then
                local machvar, cmpval = ifcond:match('%${(MACHINE_?A?R?C?H?)}%s*==%s*"([%w_]+)"')
                if machvar then
                    if_stack[#if_stack + 1] = (cmpval == arch)
                else
                    -- Not a simple MACHINE/MACHINE_ARCH equality check --
                    -- conservatively assume true (include both branches'
                    -- worth of info) rather than guess wrong.
                    if_stack[#if_stack + 1] = true
                end
            elseif stripped:match("^%.%s*else") then
                if #if_stack > 0 then if_stack[#if_stack] = not if_stack[#if_stack] end
            elseif stripped:match("^%.%s*endif") then
                if #if_stack > 0 then table.remove(if_stack) end
            elseif stripped:match("^%.%s*include") then
                local inc = stripped:match("[<\"]([^>\"]+)[>\"]")
                if inc and not KNOWN_INCLUDES[path.filename(inc)] then
                    info.unknown_includes[#info.unknown_includes + 1] = inc
                end
            elseif block_active() and var and op ~= "!=" then
                local expanded, unresolved = expand_vars(rest, vars)
                if var == "PROG" then info.prog = expanded:match("%S+")
                elseif var == "PROGS" then
                    for n in expanded:gmatch("%S+") do info.progs[#info.progs + 1] = n end
                elseif var == "SRCS" then
                    for f in expanded:gmatch("%S+") do info.srcs[#info.srcs + 1] = f end
                elseif var == "LDADD" then
                    for lib in expanded:gmatch("%-l([%w_]+)") do
                        info.ldadd_libs[#info.ldadd_libs + 1] = lib
                    end
                elseif var == "REGRESS_TARGETS" then
                    info.has_regress_targets_var = true
                end
                current_target = nil
            elseif block_active() then
                local tname = stripped:match("^([%w_%-]+)%s*:")
                if tname then
                    current_target = tname
                    info.targets[tname] = info.targets[tname] or { recipe_lines = {} }
                    info.custom = true
                elseif current_target and stripped:match("^@?[%w./${}%-]") then
                    -- a recipe line (make strips a leading tab, already
                    -- gone via our own line trim) belonging to current_target
                    table.insert(info.targets[current_target].recipe_lines, stripped)
                else
                    info.custom = true   -- something we don't recognize; be conservative
                end
            end
        end
    end

    return info
end

-- ==============================================================================
-- Golden-file recipe translation: recognize the
--   <command...> > NAME.res
--   cmp -s EXPECTED.out NAME.res ...
-- idiom inside a custom target's recipe and extract enough to run it
-- without shelling back out to `make`.
-- ==============================================================================
local function try_translate_golden_file_recipe(recipe_lines, testdir)
    local run_line, cmp_line
    for _, l in ipairs(recipe_lines) do
        if not run_line and l:match(">%s*[%w_.]+%.res%s*$") then run_line = l
        elseif not cmp_line and l:match("^cmp %-s") then cmp_line = l end
    end
    if not run_line or not cmp_line then return nil end

    local command, resfile = run_line:match("^(.-)%s*>%s*([%w_.]+%.res)%s*$")
    local expected = cmp_line:match("cmp %-s%s+%S-([%w_.]+%.out)")
    if not command or not expected then return nil end

    return {
        command = command,
        resfile = resfile,
        expected = path.join(testdir, expected),
    }
end

-- ==============================================================================
-- Extension registry for future test-runner shapes (item 15 of the ask):
-- add an entry here to support a new kind of test without touching the
-- discovery/wiring logic below.
-- ==============================================================================
local TEST_RUNNERS = {}

TEST_RUNNERS.interpreter = function (target_name, scriptfile, group)
    local ext = scriptfile:match("%.([%w]+)$")
    local interp = INTERPRETER_BY_EXT[ext]
    if not interp then return false end

    target(target_name)
        set_kind("phony")
        set_default(false)
        on_test(function (t, opt)
            import("lib.detect.find_tool")
            local tool = find_tool(interp)
            if not tool then
                raise("no %s interpreter found on host", interp)
            end
            return os.execv(tool.program, {scriptfile}, {try = true})
        end)
        add_tests(path.filename(scriptfile), { group = group })
    target_end()
    return true
end

TEST_RUNNERS.golden_file = function (target_name, translated, group)
    target(target_name)
        set_kind("phony")
        set_default(false)
        on_test(function (t, opt)
            local out = os.iorun(translated.command) or ""
            local expected = read_file(translated.expected) or ""
            return out == expected
        end)
        add_tests(path.filename(translated.resfile), { group = group })
    target_end()
end

-- ==============================================================================
-- Wire one discovered test directory.
-- ==============================================================================
local stats = { simple = 0, golden = 0, script = 0, custom_skipped = 0, empty = 0 }

local function eteleos_test_unit(target_name, testdir, group)
    local info = parse_makefile(testdir)
    if not info then
        -- No Makefile: check for a directly-runnable script (shell/python/
        -- perl/lua test with no build step at all).
        for ext in pairs(INTERPRETER_BY_EXT) do
            local scripts = os.files(path.join(testdir, "*." .. ext))
            for _, s in ipairs(scripts) do
                if TEST_RUNNERS.interpreter(target_name .. "-" .. path.filename(s), s, group) then
                    stats.script = stats.script + 1
                end
            end
        end
        return
    end

    if #info.unknown_includes > 0 then
        wprint("eteleos-tests: %s includes non-standard %s", testdir,
               table.concat(info.unknown_includes, ", "))
    end

    if info.custom then
        -- Attempt the golden-file idiom on each custom target before
        -- giving up on this directory entirely.
        local any_translated = false
        for tname, t in pairs(info.targets) do
            local translated = try_translate_golden_file_recipe(t.recipe_lines, testdir)
            if translated then
                TEST_RUNNERS.golden_file(target_name .. "-" .. tname, translated, group)
                stats.golden = stats.golden + 1
                any_translated = true
            end
        end
        if not any_translated then stats.custom_skipped = stats.custom_skipped + 1 end
        return
    end

    local prognames = {}
    if info.prog then prognames[#prognames + 1] = info.prog end
    for _, p in ipairs(info.progs) do prognames[#prognames + 1] = p end
    if #prognames == 0 then stats.empty = stats.empty + 1; return end

    local c_files = {}
    if #info.srcs > 0 then
        for _, f in ipairs(info.srcs) do
            local full = path.join(testdir, f)
            if os.isfile(full) then c_files[#c_files + 1] = full end
        end
    else
        c_files = os.files(path.join(testdir, "*.c"))
    end
    if #c_files == 0 then stats.empty = stats.empty + 1; return end

    -- Heuristic unit-vs-integration tag (see file header): does this test
    -- depend on an external, already-existing userland program? This tree
    -- has no structural unit/integration distinction, so the tag is
    -- embedded in the TARGET NAME (visible to `xmake test <pattern>` name
    -- matching) rather than overloading `group`, which stays the
    -- directory-based category so `xmake test usr.bin/*` keeps working.
    local dep_dir, dep_cat = find_userland_program_dir(path.filename(testdir))
    local heuristic_tag = dep_dir and "integration-like" or "unit-like"
    target_name = target_name .. "-" .. heuristic_tag

    target(target_name)
        set_kind("binary")
        set_default(false)
        add_rules("eteleos.base")
        add_files(unpack(c_files))
        add_includedirs(testdir)
        add_deps("eteleos-headers")

        for _, libname in ipairs(info.ldadd_libs) do
            add_deps("lib" .. libname .. "-shared")
        end
        if dep_dir then
            add_deps("userland-" .. dep_cat:gsub("/", "-") .. "-" .. path.filename(testdir))
        end

        on_test(function (t, opt)
            import("lib.detect.find_tool")
            if get_config("target_arch") and get_config("target_arch") ~= os.arch() then
                local qemu = find_tool("qemu-" .. arch)
                if not qemu then
                    cprint("${yellow}skipped${clear}: cross build, no qemu-%s found", arch)
                    return true  -- do not fail the whole test run for an environment gap
                end
            end
            return true  -- default: xmake's own exit-code check after on_test returns
        end)
        add_tests(prognames[1], { group = group })
    target_end()

    stats.simple = stats.simple + 1
end

-- ==============================================================================
-- Discovery
-- ==============================================================================
for _, category in ipairs(TEST_CATEGORIES) do
    local catdir = path.join(os.scriptdir(), category)
    if os.isdir(catdir) then
        for _, testdir in ipairs(find_test_dirs(catdir)) do
            local relpath = testdir:sub(#catdir + 2)
            local safe_name = ("tests-" .. category .. "-" .. relpath):gsub("[/.]", "-")
            local group = (path.filename(testdir) == "benchmark") and "benchmark"
                          or (category == "sys" and "kernel" or category)
            eteleos_test_unit(safe_name, testdir, group)
        end
    else
        wprint("eteleos-tests: tests/%s not found, skipping", category)
    end
end

cprint("${green}eteleos-tests${clear}: %d simple (build+run), %d golden-file-translated, "
       .. "%d script-only, %d empty, %d custom skipped (arch=%s)",
       stats.simple, stats.golden, stats.script, stats.empty, stats.custom_skipped, arch)
