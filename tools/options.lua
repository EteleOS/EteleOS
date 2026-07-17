--[[
================================================================================
 EteleOS: tools/options.lua, time write: 2026/07/16
 This file uses the Apache-2.0 license
================================================================================

All project-wide option() declarations.
Loaded by tools/xmake.lua (after helpers.lua).

option() declarations are project-global in xmake: once declared here, any
module's xmake.lua can interrogate them with has_config() / get_config()
regardless of where in the include tree it sits.

User interface:
  xmake f --target_arch=arm64
  xmake f --lto=y
  xmake f --asan=y --ubsan=y
  xmake f --werror=y
  xmake f --sysroot=/path/to/sysroot
  xmake f --eteleos_toolchain=eteleos-gcc
--------------------------------------------------------------------------------
--]]

-- ==============================================================================
-- Target architecture
-- ==============================================================================
-- The values listed here are the COMPLETE set of architectures still present
-- in the EteleOS source tree after the pruning described in the build spec.
-- Do not add back removed architectures here.
option("target_arch")
    set_default("amd64")
    set_showmenu(true)
    set_description("EteleOS target CPU architecture")
    set_values("amd64", "arm64", "riscv64")
option_end()

-- ==============================================================================
-- Toolchain preset
-- ==============================================================================
-- Selects which toolchain() declaration (from tools/toolchains.lua) is
-- activated as the project default. Setting this option also drives the
-- set_config("toolchain", ...) call in tools/compiler.lua.
option("eteleos_toolchain")
    set_default("eteleos-clang")
    set_showmenu(true)
    set_description("Build toolchain preset")
    set_values("eteleos-clang", "eteleos-gcc")
option_end()

-- ==============================================================================
-- Cross-build sysroot
-- ==============================================================================
-- When a dedicated OpenBSD sysroot is available on the host (e.g. a Linux
-- cross-build environment with a pre-built OpenBSD-amd64 sysroot extracted),
-- point to it here. Empty string means: let the toolchain use its own default
-- (works for native builds; for real cross-builds a sysroot is recommended).
option("sysroot")
    set_default("")
    set_showmenu(true)
    set_description("Sysroot for cross-compilation (empty = toolchain default)")
option_end()

-- ==============================================================================
-- Link-time optimization (LTO)
-- ==============================================================================
-- Off by default to keep iteration fast. Enable for official release builds.
-- Activate with: xmake f --lto=y
option("lto")
    set_default(false)
    set_showmenu(true)
    set_description("Enable link-time optimization (LTO)")
option_end()

-- ==============================================================================
-- Sanitizers
-- ==============================================================================
-- These are intentionally separate options so that, for example, a test build
-- can enable ubsan without asan. Both are ONLY valid for hosted targets
-- (userland tools, tests); the eteleos.kernel rule blocks them on the kernel.

option("asan")
    set_default(false)
    set_showmenu(true)
    set_description("Enable AddressSanitizer (hosted/userland targets only)")
option_end()

option("ubsan")
    set_default(false)
    set_showmenu(true)
    set_description("Enable UndefinedBehaviorSanitizer (hosted/userland targets only)")
option_end()

-- ==============================================================================
-- Warning / quality flags
-- ==============================================================================

-- Promotes every compiler warning to a hard error. Recommended for CI; off
-- by default so developers can iterate without a full-green build.
option("werror")
    set_default(false)
    set_showmenu(true)
    set_description("Treat all compiler warnings as errors (-Werror)")
option_end()

-- Emit the full compiler command line for every compilation unit. Useful
-- when debugging build-system or header-path problems.
option("verbose_build")
    set_default(false)
    set_showmenu(true)
    set_description("Show verbose compiler command lines during build (-v)")
option_end()

-- ==============================================================================
-- GUI: GLX / DRI
-- ==============================================================================
-- Real upstream Makefile.bsd-wrapper files (xserver's, and driver modules
-- like xf86-video-intel's) branch on XENOCARA_BUILD_GL / XENOCARA_BUILD_DRI
-- make variables to add --enable/--disable-glx and --enable/--disable-dri
-- configure flags. gui/xmake.lua reads these two options for that same
-- toggle. Off by default: a from-scratch OS bring-up (this project's own
-- notes point at VirtualBox/UEFI testing) gets a working, testable X server
-- faster without also having to bring up a GL/DRI-capable driver stack.
option("build_gl")
    set_default(false)
    set_showmenu(true)
    set_description("Build X.Org modules with GLX support")
option_end()

option("build_dri")
    set_default(false)
    set_showmenu(true)
    set_description("Build X.Org modules with DRI support")
option_end()
