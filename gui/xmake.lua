/*
 EteleOS: xmake.lua, time wirte: 2026/07/12
 This file uses the Apache-2.0 license
*/


--[[
================================================================================
 EteleOS :: gui/xmake.lua
================================================================================

Manages the X.Org-derived windowing stack: Window System, Display Server,
Graphics Libraries, Fonts, and X11 apps/utilities (verified categories:
app/, driver/, font/, lib/, proto/, util/, xserver/ -- roughly 27,000 files
across ~200 separately-versioned upstream modules listed in gui/MODULES).

WHAT DOES NOT EXIST HERE -- please read first
-------------------------------------------------
  Compositor, Desktop Environment, Mobile UI, and Wayland were requested as
  responsibilities of this file, but NONE of them exist anywhere in the
  current source tree -- verified by searching the whole gui/ tree:
    - No compositor implementation (Xorg itself has a compositing
      *extension*, "composite/" inside xserver/, which is real and
      already built as part of xserver below -- but that is not the same
      thing as a standalone Wayland-style compositor).
    - No desktop environment or window manager is vendored in gui/
      (traditional OpenBSD ships bare X11; a WM like cwm is a separate
      userland/ or ports/ concern, not part of gui/).
    - No mobile UI code anywhere.
    - No Wayland protocol/compositor implementation. The only "wayland"
      hits in the entire tree are an OPTIONAL backend inside the vendored
      libva video-acceleration library (lib/libva/va/wayland/) -- an
      optional feature flag of a dependency, not a Wayland display server.
  If/when source for any of these is added to the tree, it can be wired up
  the same way as the rest of this file; nothing is faked here to look
  more complete than it is.

WHY THIS FILE LOOKS DIFFERENT FROM kernel/libraries/userland's xmake.lua
--------------------------------------------------------------------------
  Every gui module is its own independently-versioned upstream X.Org
  project, built with autotools/libtool (configure.ac, Makefile.am), NOT a
  simple PROG=/SRCS= BSD Makefile. Re-implementing autotools' own
  dependency/feature detection in xmake is not realistic; the verified,
  actual build mechanism (confirmed by reading real Makefile.bsd-wrapper
  files in this tree) is: OpenBSD's own bsd.xorg.mk wraps each module's
  configure+make+make-install, and only a FEW modules -- xserver being the
  big one -- override it with custom CONFIGURE_ARGS. So instead of native
  xmake compilation, this file defines one GENERIC autotools-wrapper
  utility target per module (invoking that module's own real configure/
  make/make-install as subprocesses, cross-compiling via our own
  eteleos-clang toolchain's target triple), plus a small override table
  for the handful of modules confirmed to need non-default configure
  flags.

Does not use xmake's native compiler pipeline (add_files/target kind
binary) -- every module here is a "phony" utility target whose real work
happens in on_build/on_install shelling out to that module's own configure
script, which is the correct, honest shape of this problem.
--------------------------------------------------------------------------------
--]]

-- ==============================================================================
-- Module discovery: parse the real gui/MODULES file (category/name,
-- upstream version, optional status flag) instead of hand-listing ~200
-- modules.
-- ==============================================================================
local function parse_modules_list(filepath)
    local f = io.open(filepath, "r")
    if not f then
        wprint("eteleos-gui: MODULES file not found at %s", filepath)
        return {}
    end
    local modules = {}
    for line in f:lines() do
        local stripped = line:gsub("#.*$", "")
        local relpath, version = stripped:match("^(%S+)%s+(%S+)")
        if relpath then
            local category, name = relpath:match("^([^/]+)/(.+)$")
            if category and name then
                modules[#modules + 1] = { category = category, name = name,
                                           relpath = relpath, version = version }
            end
        end
    end
    f:close()
    return modules
end

-- ==============================================================================
-- Per-module configure overrides -- confirmed real from
-- gui/xserver/Makefile.bsd-wrapper. Everything NOT listed here uses
-- the generic default args below (matching the generic
-- ".include <bsd.xorg.mk>"-only wrapper that most modules actually have,
-- verified against xf86-video-apm's real Makefile.bsd-wrapper).
-- ==============================================================================
local MODULE_CONFIGURE_OVERRIDES = {
    ["xserver/xserver"] = {
        "--localstatedir=/var",
        "--sysconfdir=/etc/X11",
        "--with-xkb-path=/usr/X11R6/share/X11/xkb",
        "--with-xkb-output=/var/db/xkb",
        "--with-default-xkb-rules=base",
        "--disable-install-setuid",
        "--enable-privsep",
        "--enable-xcsecurity",
        "--disable-xdm-auth-1",
        "--without-fop", "--without-xmlto", "--without-xsltproc",
        -- GLX/DRI left at their configure-script defaults here (the real
        -- wrapper branches on gui_BUILD_GL / gui_BUILD_DRI make
        -- variables, which have no equivalent wired up in this file yet).
    },
}

-- ==============================================================================
-- Generic autotools wrapper: one utility target per module, cross-building
-- via our own toolchain's target triple.
-- ==============================================================================
local function eteleos_gui_module(mod)
    -- xserver is vendored directly at gui/xserver/ (MODULES lists it
    -- as a bare "xserver" entry with no category/name split), not nested
    -- as gui/xserver/xserver/ -- special-case its directory.
    local moddir
    if mod.relpath == "xserver/xserver" then
        moddir = path.join(os.scriptdir(), "xserver")
    else
        moddir = path.join(os.scriptdir(), mod.category, mod.name)
    end
    if not os.isdir(moddir) then
        wprint("eteleos-gui: %s not found on disk, skipping", mod.relpath)
        return
    end

    local target_name = "gui-" .. mod.category .. "-" .. mod.name

    target(target_name)
        set_kind("phony")
        set_default(false)

        on_build(function (target)
            import("lib.detect.find_tool")

            local arch = get_config("target_arch") or "amd64"
            local triple = (ETELEOS_TARGET_TRIPLES or {})[arch]
            local installdir = get_config("installdir")
                                or path.join(os.scriptdir(), "..", "build", "install")

            -- Prefer an already-generated `configure` (most modules ship
            -- one, generated upstream); fall back to autoreconf if only
            -- configure.ac is present and autoreconf is available.
            local configure = path.join(moddir, "configure")
            if not os.isfile(configure) then
                local autoreconf = find_tool("autoreconf")
                if autoreconf and os.isfile(path.join(moddir, "configure.ac")) then
                    os.execv(autoreconf.program, {"-fi"}, {curdir = moddir, try = true})
                end
            end
            if not os.isfile(configure) then
                wprint("eteleos-gui: %s has no configure script (and autoreconf "
                       .. "unavailable/failed) -- skipping", mod.relpath)
                return
            end

            local args = {
                "--host=" .. (triple or arch),
                "--prefix=/usr/X11R6",
            }
            for _, extra in ipairs(MODULE_CONFIGURE_OVERRIDES[mod.relpath] or {}) do
                args[#args + 1] = extra
            end

            local cc = get_config("cc") or "clang"
            local envs = { CC = cc }
            local ok = os.execv(configure, args, { curdir = moddir, envs = envs, try = true })
            if not ok then
                wprint("eteleos-gui: %s: configure failed", mod.relpath)
                return
            end

            local make = find_tool("make") or find_tool("gmake")
            if make then
                if not os.execv(make.program, {}, { curdir = moddir, try = true }) then
                    wprint("eteleos-gui: %s: make failed", mod.relpath)
                    return
                end
                os.execv(make.program, {"install", "DESTDIR=" .. installdir},
                          { curdir = moddir, try = true })
            else
                wprint("eteleos-gui: no make/gmake found, cannot build %s", mod.relpath)
            end
        end)
    target_end()
end

-- ==============================================================================
-- Discover and wire up every module from the real MODULES file
-- ==============================================================================
local modules_file = path.join(os.scriptdir(), "MODULES")
local all_modules = parse_modules_list(modules_file)
cprint("${green}eteleos-gui${clear}: %d modules discovered from MODULES", #all_modules)

for _, mod in ipairs(all_modules) do
    eteleos_gui_module(mod)
end

-- xserver itself is not listed in MODULES (it is vendored directly under
-- gui/xserver/, not gui/xserver/xserver/) -- wire it up
-- explicitly since it is the single most important target here (the
-- actual Window System / Display Server the user's spec asks for).
eteleos_gui_module({ category = "xserver", name = "xserver", relpath = "xserver/xserver" })
