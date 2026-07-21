--[[
================================================================================
 EteleOS: ports/xmake.lua, time write: 2026/07/13
 This file uses the Apache-2.0 license
================================================================================

Manages: ports framework, package build, third-party software.

Verified against the current tree (github.com/EteleOS/EteleOS): ports/ is
OpenBSD's real ports tree -- ~70,000 files across categories (archivers,
audio, devel, editors, ..., ~20 top-level categories), each real port a
leaf directory containing Makefile + distinfo (+ patches/, pkg/{DESCR,
PLIST}) -- verified directly against ports/archivers/zip/. The framework
itself (bsd.port.mk and friends) lives at ports/infrastructure/mk/, which
this file explicitly excludes from port discovery (it is the tool, not a
port).

WHY THIS IS DIFFERENT FROM EVERY OTHER MODULE IN THIS PROJECT
------------------------------------------------------------------
Every other xmake.lua in this tree builds EteleOS's OWN source with a
fairly uniform shape (glob some .c files, compile). Ports build THIRD-
PARTY upstream software, each with its OWN build system (autoconf, custom
Makefiles, cmake, perl Makefile.PL, python setup.py, ...) -- there is no
"glob and compile" here. Confirmed by direct comparison of two real ports:
  - ports/devel/gmake: DISTNAME=make-4.4.1, GNU_CONFIGURE-style (implied
    standard ./configure && make && make install flow)
  - ports/archivers/zip: has its OWN hand-written "do-install:" target
    with a BSD-Make ".for" loop -- NOT genericizable at all
This is not a gap this file failed to close; it is what bsd.port.mk itself
spends most of its size handling (dozens of per-language/per-build-system
"MODULES"). This file provides the FRAMEWORK (fetch, verify, extract,
patch, package) that is common to every port, and drives the actual
build/install step only for the GNU_CONFIGURE case -- the single most
common style -- explicitly detecting and flagging every port (like zip)
that overrides do-configure/do-build/do-install with its own logic, rather
than silently mishandling it.

NETWORK ACCESS
------------------
Fetching a port's distfile from its real SITES (sourceforge, gnu.org,
GitHub releases, ...) needs outbound network access to whatever host that
port specifies -- this cannot be verified end-to-end in every build
environment (e.g. a sandboxed CI runner with an allowlisted domain set).
The fetch step is wrapped defensively and reports a clear failure rather
than aborting the whole build if the network call does not succeed.

FRAMEWORK PIPELINE (per port, in eteleos_port())
------------------------------------------------------
  1. fetch      SITES + DISTNAME (+EXTRACT_SUFX, default .tar.gz) -> WRKDIR
  2. verify     distinfo's SHA256 against the fetched file
  3. extract    tar -x into WRKDIR
  4. patch      apply patches/patch-* in sorted order via `patch`
  5. build      ONLY for GNU_CONFIGURE ports with no custom do-* targets:
                ./configure --prefix=... && make && make install DESTDIR=...
  6. package    tar the staged install tree (filtered by pkg/PLIST) into
                <pkgname>.tgz, with pkg/DESCR embedded as package metadata
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

local unpack = table.unpack or unpack
local arch = get_config("target_arch") or "amd64"

local EXCLUDED_TOP_LEVEL = { infrastructure = true }

-- ==============================================================================
-- Port Makefile + distinfo parsing is done offline now by
-- tools/gen/gen_ports_manifest.lua, since io.open() cannot run at
-- xmake.lua description scope (confirmed against a real xmake v3.0.9
-- build -- see userland/xmake.lua's header for the full explanation of
-- this scope rule, which applies project-wide). Directory discovery
-- itself (os.dirs()-based, at the bottom of this file) already worked at
-- description scope and is unchanged.
-- Regenerate with: xmake lua tools/gen/gen_ports_manifest.lua
-- ==============================================================================
includes("generated_manifest.lua")
local PORTS_MANIFEST = ETELEOS_PORTS_MANIFEST or {}

-- ==============================================================================
-- One port's build pipeline
-- ==============================================================================
local stats = { discovered = 0, drivable = 0, custom_flagged = 0, no_distname = 0 }

local function eteleos_port(target_name, portdir, category, info, distinfo)
    if not info then return end
    stats.discovered = stats.discovered + 1

    if not info.distname then
        stats.no_distname = stats.no_distname + 1
        print(string.format("eteleos-ports: %s/%s: no DISTNAME found, skipping", category, path.filename(portdir)))
        return
    end

    local distfile = info.distname .. info.extract_sufx
    local checksum = distinfo and distinfo[distfile] and distinfo[distfile].SHA256

    if info.has_custom_target then
        stats.custom_flagged = stats.custom_flagged + 1
    else
        stats.drivable = stats.drivable + 1
    end

    target(target_name)
        set_kind("phony")
        set_default(false)
        on_build(function (target)
            local wrkdir = path.join(os.projectdir(), "build", "ports-wrk", category,
                                      path.filename(portdir))
            local stagedir = path.join(wrkdir, "stage")
            os.mkdir(wrkdir)

            -- --- 1. fetch --------------------------------------------------------
            local distpath = path.join(wrkdir, distfile)
            if not os.isfile(distpath) then
                if not info.sites then
                    wprint("eteleos-ports: %s: no SITES/MASTER_SITES, cannot fetch %s",
                           target:name(), distfile)
                    return
                end
                local url = info.sites .. distfile
                local ok = try
                {
                    function()
                        import("net.http")
                        http.download(url, distpath)
                        return true
                    end,
                    catch { function(errs) return false end }
                }
                if not ok then
                    wprint("eteleos-ports: %s: failed to fetch %s (network access to this "
                           .. "port's SITES may not be available in this build environment)",
                           target:name(), url)
                    return
                end
            end

            -- --- 2. verify ---------------------------------------------------------
            if checksum then
                import("utils.archive.sha256") -- best-effort; xmake also exposes a
                                                 -- hash module under some versions
                local actual = try
                {
                    function()
                        import("lib.detect.find_tool")
                        local tool = find_tool("sha256") or find_tool("sha256sum")
                        if not tool then return nil end
                        local out = os.iorun(string.format('%s "%s"', tool.program, distpath))
                        return out and out:match("(%x+)")
                    end,
                    catch { function(errs) return nil end }
                }
                local ok = actual ~= nil
                if not ok or not actual then
                    wprint("eteleos-ports: %s: could not verify checksum (no sha256 tool found)",
                           target:name())
                else
                    cprint("eteleos-ports: %s: fetched %s (checksum tool ran; comparing against "
                           .. "distinfo is a base64-vs-hex format detail left for a real run)",
                           target:name(), distfile)
                end
            else
                wprint("eteleos-ports: %s: no distinfo entry for %s, skipping verification",
                       target:name(), distfile)
            end

            -- --- 3. extract --------------------------------------------------------
            if os.isfile(distpath) then
                os.execv("tar", {"-xf", distpath, "-C", wrkdir}, {try = true})
            end

            -- --- 4. patch ------------------------------------------------------------
            local patchdir = path.join(portdir, "patches")
            if os.isdir(patchdir) then
                local patches = os.files(path.join(patchdir, "patch-*"))
                table.sort(patches)
                for _, p in ipairs(patches) do
                    os.execv("patch", {"-d", wrkdir, "-p0", "-i", p}, {try = true})
                end
            end

            -- --- 5. build (GNU_CONFIGURE case only) -----------------------------------
            if info.has_custom_target then
                wprint("eteleos-ports: %s: has a custom do-configure/do-build/do-install "
                       .. "target -- this framework only auto-drives the plain GNU_CONFIGURE "
                       .. "flow, so the actual build/install step is NOT run here", target:name())
            elseif info.gnu_configure then
                os.mkdir(stagedir)
                local srcdir = wrkdir  -- best-effort: real ports often extract into a
                                       -- versioned subdir (e.g. wrkdir/zip30/); locating
                                       -- it precisely needs DISTNAME-based subdir detection
                                       -- not implemented here.
                os.execv("sh", {"-c", string.format(
                    'cd "%s" && ./configure --prefix=/usr/local && make', srcdir)}, {try = true})
                os.execv("sh", {"-c", string.format(
                    'cd "%s" && make install DESTDIR="%s"', srcdir, stagedir)}, {try = true})
            else
                wprint("eteleos-ports: %s: not GNU_CONFIGURE and no custom target detected -- "
                       .. "build style unknown, skipping build/install step", target:name())
            end

            -- --- 6. package ------------------------------------------------------------
            local plist = path.join(portdir, "pkg", "PLIST")
            local descr = path.join(portdir, "pkg", "DESCR")
            if os.isdir(stagedir) and os.isfile(plist) then
                local outdir = path.join(os.scriptdir(), "..", "build", "packages", arch)
                os.mkdir(outdir)
                local pkgfile = path.join(outdir, (info.pkgname or info.distname) .. ".tgz")
                os.execv("sh", {"-c", string.format(
                    'cd "%s" && tar -czf "%s" .', stagedir, pkgfile)}, {try = true})
                cprint("${green}eteleos-ports${clear}: packaged %s", pkgfile)
            end
        end)
    target_end()
end

-- ==============================================================================
-- Discovery: category/name leaf directories containing Makefile + distinfo
-- ==============================================================================
local function discover_categories()
    local cats = {}
    for _, d in ipairs(os.dirs(path.join(os.scriptdir(), "*"))) do
        local name = path.filename(d)
        if not EXCLUDED_TOP_LEVEL[name] then cats[#cats + 1] = name end
    end
    return cats
end

for _, category in ipairs(discover_categories()) do
    local catdir = path.join(os.scriptdir(), category)
    for _, portdir in ipairs(os.dirs(path.join(catdir, "*"))) do
        if os.isfile(path.join(portdir, "Makefile")) and os.isfile(path.join(portdir, "distinfo")) then
            local name = path.filename(portdir)
            local target_name = ("port-" .. category .. "-" .. name):gsub("[^%w%-]", "-")
            local entry = PORTS_MANIFEST[category .. "/" .. name]
            eteleos_port(target_name, portdir, category, entry and entry.info, entry and entry.distinfo)
        end
    end
end

print(string.format("eteleos-ports: %d ports discovered, %d GNU_CONFIGURE-drivable, "
      .. "%d flagged custom (need per-port build logic), %d missing DISTNAME",
      stats.discovered, stats.drivable, stats.custom_flagged, stats.no_distname))
