/*
EteleOS: xmake.lua, time wirte: 2026/07/10
This file uses the Apache-2.0 license
*/

--[[
================================================================================
 EteleOS :: tools/toolchains.lua
================================================================================

Clang/LLVM and GCC toolchain declarations for EteleOS.
Loaded by tools/xmake.lua (after rules.lua, which means helpers.lua is
already in scope and ETELEOS_TARGET_TRIPLES etc. are accessible).

toolchain() declarations are project-global in xmake: once declared here,
any module can reference these toolchains, and the default set in
compiler.lua (via set_config("toolchain", ...)) applies to all targets
that do not override it explicitly.

Architecture → triple mapping:
  amd64   → x86_64-unknown-openbsd
  arm64   → aarch64-unknown-openbsd
  riscv64 → riscv64-unknown-openbsd

Design:
  - A single Clang binary is retargeted via the -target <triple> flag so that
    the SAME toolchain declaration works for both native and cross builds.
    Switching target_arch only changes a flag, not the toolchain binary.
  - GCC is secondary/best-effort. Plain gcc cannot retarget with a single
    flag; eteleos-gcc works for native builds out of the box. For real
    cross-builds, the user must supply a properly-prefixed cross-gcc via
    `xmake f --sdk=/path/to/cross-gcc-sysroot`.

Nothing in this file compiles any source file or declares any target.
--------------------------------------------------------------------------------
--]]

-- ==============================================================================
-- Primary toolchain: Clang/LLVM
-- ==============================================================================
toolchain("eteleos-clang")
    set_kind("standalone")
    set_homepage("https://github.com/EteleOS/EteleOS")
    set_description("Clang/LLVM toolchain for EteleOS (default)")

    -- --- Tool binaries --------------------------------------------------------
    -- No hard-coded paths: xmake searches PATH for these names.
    -- Users can override any binary via: xmake f --cc=/usr/bin/clang-17 etc.
    set_toolset("cc",     "clang")
    set_toolset("cxx",    "clang",   "clang++")
    set_toolset("ld",     "clang++", "clang")
    set_toolset("sh",     "clang++", "clang")   -- shared lib linker
    set_toolset("as",     "clang")
    set_toolset("ar",     "llvm-ar", "ar")
    set_toolset("strip",  "llvm-strip", "strip")
    set_toolset("ranlib", "llvm-ranlib", "ranlib")
    set_toolset("objcopy","llvm-objcopy", "objcopy")
    set_toolset("objdump","llvm-objdump", "objdump")
    set_toolset("nm",     "llvm-nm", "nm")
    set_toolset("size",   "llvm-size", "size")

    -- --- Dynamic configuration via on_load ------------------------------------
    -- on_load fires once per toolchain instance (i.e. once when xmake f runs).
    -- We use the closure over ETELEOS_TARGET_TRIPLES (from helpers.lua) to
    -- resolve the triple without requiring a target object.
    on_load(function (toolchain)
        local arch   = get_config("target_arch") or "amd64"
        local triple = ETELEOS_TARGET_TRIPLES[arch]
                       or ("unknown-" .. arch .. "-unknown-openbsd")

        -- Retarget compiler, assembler and linker to the chosen architecture.
        -- This is what allows a single Clang installation to cross-compile
        -- without a separate cross-prefixed binary per target arch.
        toolchain:add("cxflags", "-target", triple)
        toolchain:add("asflags", "-target", triple)
        toolchain:add("ldflags", "-target", triple)

        -- When an explicit sysroot is configured, pass it to every tool.
        local sysroot = get_config("sysroot")
        if sysroot and sysroot ~= "" then
            toolchain:add("cxflags", "--sysroot=" .. sysroot)
            toolchain:add("asflags", "--sysroot=" .. sysroot)
            toolchain:add("ldflags", "--sysroot=" .. sysroot)
        end
    end)
toolchain_end()

-- ==============================================================================
-- Secondary toolchain: GCC (best-effort)
-- ==============================================================================
-- Plain `gcc` only targets the host. For cross-builds, the user must either:
--   (a) supply a cross-prefixed gcc in their PATH and tell xmake about it, or
--   (b) set the --sdk option to the root of a cross-gcc installation.
-- This toolchain is intentionally simpler than eteleos-clang; advanced
-- cross-build wiring is left as an extension point in tools/cross/.
toolchain("eteleos-gcc")
    set_kind("standalone")
    set_description("GCC toolchain for EteleOS (secondary / best-effort)")

    on_check(function (toolchain)
        -- Confirm that gcc is actually available before marking this
        -- toolchain as usable. xmake's detect.find_tool() is available in
        -- on_check's script scope.
        import("detect.find_tool")
        local gcc = find_tool("gcc")
        if not gcc then
            cprint("${yellow}warning${clear}: gcc not found; "
                   .. "eteleos-gcc toolchain will not be usable")
            return false
        end
        return true
    end)

    set_toolset("cc",     "gcc")
    set_toolset("cxx",    "gcc",   "g++")
    set_toolset("ld",     "g++",   "gcc")
    set_toolset("sh",     "g++",   "gcc")
    set_toolset("as",     "gcc")
    set_toolset("ar",     "ar")
    set_toolset("strip",  "strip")
    set_toolset("ranlib", "ranlib")
    set_toolset("objcopy","objcopy")
    set_toolset("objdump","objdump")
    set_toolset("nm",     "nm")
    set_toolset("size",   "size")

    on_load(function (toolchain)
        -- GCC cannot retarget via a single flag like Clang's -target.
        -- For native builds, no special flag is needed. For cross-builds,
        -- the cross-prefix approach (x86_64-unknown-openbsd-gcc) is expected
        -- to be set up externally (toolchain in PATH or via --sdk).
        --
        -- We still pass the sysroot if configured, as even native GCC can
        -- benefit from an explicit sysroot in some setups.
        local sysroot = get_config("sysroot")
        if sysroot and sysroot ~= "" then
            toolchain:add("cxflags", "--sysroot=" .. sysroot)
            toolchain:add("ldflags", "--sysroot=" .. sysroot)
        end
    end)
toolchain_end()
