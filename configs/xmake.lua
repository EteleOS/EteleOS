/*
 EteleOS: xmake.lua, time wirte: 2026/07/13
 This file uses the Apache-2.0 license
*/


--[[
================================================================================
 EteleOS :: configs/xmake.lua
================================================================================

Manages: etc, rc, passwd, group, login.conf, sysctl.conf, and the rest of
the system configuration tree (configs/ is OpenBSD's /etc, reorganized
thematically). Does NOT compile anything -- pure file installation, same
model as resources/xmake.lua (headeronly target + after_install copy
logic).

Verified against the current tree (github.com/EteleOS/EteleOS):
  configs/{etc, filesystem, logging, mail, network, security, system,
           templates, Makefile, Makefile.inc}
  configs/etc/{etc.amd64, etc.arm64, etc.riscv64}/ -- per-architecture
    /etc files: disktab, fbtab, login.conf, sysctl.conf, ttys, MAKEDEV(.md)
    -- confirming the user's login.conf/sysctl.conf are architecture-
    specific here, not flat top-level files.

THE DESTINATION MAPPING BELOW IS A RECONSTRUCTION, NOT A VERIFIED CURRENT
SOURCE -- please read
--------------------------------------------------------------------------------
The only Makefile that states install destinations explicitly and is NOT
stale is configs/mail/Makefile (still correct: aliases/smtpd.conf ->
${DESTDIR}/etc/mail/, mode 644 root:wheel -- verified and used directly
below). The top-level configs/Makefile ALSO exists, but it is stale in the
exact same way other legacy Makefiles found throughout this project are:
it references the pre-restructure flat etc/ layout (a MUTABLE= list of
bare filenames like "group", "gettytab", "moduli", "pf.os") and the old
kernel path (../sys/arch/${MACHINE}/compile/...), neither of which match
the current thematic configs/{system,security,network,...} split or the
kernel/ tree kernel/xmake.lua now builds. It is also NOT this file's job to
build kernels for a release -- that overlap in the legacy Makefile belongs
to kernel/xmake.lua and installer/xmake.lua respectively.

So: every category-to-destination mapping below other than mail/ is this
file's own reconstruction from the directory names and standard OpenBSD
/etc conventions, not read from a current authoritative source. Treat it
as a starting point to correct against a real installed system if any
mapping turns out wrong.

  filesystem/mtree/*      -> /etc/mtree/*     (mtree(8) specs -- ALSO used
                                                by installer/ to construct
                                                the base directory tree,
                                                not just passive data; that
                                                usage is not wired up here)
  filesystem/{MAKEDEV,fbtab.*,minfree} -> /etc/
  logging/*               -> /etc/
  mail/*                  -> /etc/mail/       (verified, see above)
  network/*               -> /etc/
  security/*              -> /etc/
  system/*                -> /etc/
  templates/skel/*        -> /etc/skel/
  templates/root/*        -> /root/
  templates/examples/*    -> /etc/examples/
  templates/ksh.kshrc     -> /etc/
  etc/etc.<target_arch>/* -> /etc/            (flattened; Makefile/
                                                Makefile.inc excluded, see
                                                below)

Build-system artifacts (Makefile, Makefile.inc) found inside these
directories are deliberately EXCLUDED from installation -- they configure
the legacy BSD Make install step, not runtime files.

PERMISSIONS
--------------
Only one file gets a non-default mode here: system/master.passwd at 600
(well-established OpenBSD convention -- it contains password hashes).
Everything else installs at the standard 644, root:wheel. This is a
smaller, more conservative permissions pass than userland/xmake.lua's
BINMODE parsing (there is no per-file BINMODE metadata to read here, since
the one Makefile that had it -- the top-level configs/Makefile -- is the
stale one described above).
--------------------------------------------------------------------------------
--]]

local arch = get_config("target_arch") or "amd64"

local EXCLUDE_NAMES = { Makefile = true, ["Makefile.inc"] = true }

local SENSITIVE_MODES = {
    ["master.passwd"] = "600",
}

-- ==============================================================================
-- Small utilities
-- ==============================================================================
local function copy_dir_flat(srcdir, dstdir)
    if not os.isdir(srcdir) then return 0 end
    os.mkdir(dstdir)
    local count = 0
    for _, f in ipairs(os.files(path.join(srcdir, "*"))) do
        local name = path.filename(f)
        if not EXCLUDE_NAMES[name] then
            local dst = path.join(dstdir, name)
            os.cp(f, dst)
            local mode = SENSITIVE_MODES[name]
            if mode then os.execv("chmod", {mode, dst}, {try = true}) end
            count = count + 1
        end
    end
    return count
end

local function copy_dir_recursive(srcdir, dstdir)
    if not os.isdir(srcdir) then return 0 end
    os.mkdir(dstdir)
    local count = 0
    for _, f in ipairs(os.files(path.join(srcdir, "**"))) do
        if not EXCLUDE_NAMES[path.filename(f)] then
            local rel = f:sub(#srcdir + 2)
            local dst = path.join(dstdir, rel)
            os.mkdir(path.directory(dst))
            os.cp(f, dst)
            count = count + 1
        end
    end
    return count
end

-- ==============================================================================
-- Target
-- ==============================================================================
target("eteleos-configs")
    set_kind("headeronly")
    set_default(false)

    after_install(function (target)
        local installdir = get_config("installdir")
                            or path.join(os.scriptdir(), "..", "build", "install")
        local etcdir = path.join(installdir, "etc")
        local scriptdir = os.scriptdir()
        local total = 0

        -- --- Flat categories: install directly under /etc -----------------------
        for _, category in ipairs({"logging", "network", "security", "system"}) do
            local n = copy_dir_flat(path.join(scriptdir, category), etcdir)
            if n == 0 then
                wprint("eteleos-configs: configs/%s not found or empty, skipping", category)
            end
            total = total + n
        end

        -- --- filesystem: mtree/ goes to /etc/mtree, the rest flat to /etc -------
        total = total + copy_dir_flat(path.join(scriptdir, "filesystem", "mtree"),
                                        path.join(etcdir, "mtree"))
        do
            local fsdir = path.join(scriptdir, "filesystem")
            if os.isdir(fsdir) then
                for _, f in ipairs(os.files(path.join(fsdir, "*"))) do
                    local name = path.filename(f)
                    if name ~= "mtree" and not EXCLUDE_NAMES[name] then
                        os.cp(f, path.join(etcdir, name))
                        total = total + 1
                    end
                end
            end
        end

        -- --- mail: verified real destination, /etc/mail ---------------------------
        total = total + copy_dir_flat(path.join(scriptdir, "mail"), path.join(etcdir, "mail"))

        -- --- templates: skel/root/examples go to distinct destinations ----------
        total = total + copy_dir_recursive(path.join(scriptdir, "templates", "skel"),
                                             path.join(etcdir, "skel"))
        total = total + copy_dir_recursive(path.join(scriptdir, "templates", "root"),
                                             path.join(installdir, "root"))
        total = total + copy_dir_flat(path.join(scriptdir, "templates", "examples"),
                                        path.join(etcdir, "examples"))
        do
            local kshrc = path.join(scriptdir, "templates", "ksh.kshrc")
            if os.isfile(kshrc) then
                os.cp(kshrc, path.join(etcdir, "ksh.kshrc"))
                total = total + 1
            end
        end

        -- --- etc/etc.<arch>: architecture-specific /etc files, flattened --------
        local archdir = path.join(scriptdir, "etc", "etc." .. arch)
        if os.isdir(archdir) then
            total = total + copy_dir_flat(archdir, etcdir)
        else
            wprint("eteleos-configs: configs/etc/etc.%s not found, skipping "
                   .. "architecture-specific /etc files (login.conf, sysctl.conf, "
                   .. "disktab, ttys, ...)", arch)
        end

        cprint("${green}eteleos-configs${clear}: installed %d files to %s (arch=%s)",
               total, etcdir, arch)
    end)
target_end()
