/*
 EteleOS: xmake.lua, time wirte: 2026/07/11
 This file uses the Apache-2.0 license
*/

--[[
================================================================================
 EteleOS :: include/xmake.lua
================================================================================

Manages:
  - header installation        (plain headers under include/*.h and the
                                 arpa/, protocols/, rpc/, rpcsvc/ subdirs)
  - exported include path       (public add_includedirs so any module can
                                 add_deps("eteleos-headers") and inherit it)
  - generated headers           (per-architecture "machine" headers and the
                                 kernel-exported directories -- crypto/, dev/,
                                 net/, sys/, uvm/, etc. -- copied from kernel/
                                 at install time, mirroring the "copies"
                                 target of the old include/Makefile)
  - compatibility headers       (endian.h, fcntl.h, syslog.h, termios.h,
                                 stdarg.h, stdint.h, varargs.h -- thin
                                 symlinks to sys/<name>.h, exactly like the
                                 old include/Makefile's LFILES/MFILES logic)

Does NOT compile anything: set_kind("headeronly") builds no binary, and every
side effect below is a pure file operation (copy / symlink) that only runs
when `xmake install` runs, exactly like the old Makefile's includes/copies/
symlinks targets did.

Source of truth for the mapping below: the CURRENT kernel/ tree (verified
against github.com/EteleOS/EteleOS), not the stale include/Makefile, which
still refers to pre-restructure paths (../sys, ../lib, ../gnu) and has not
been converted yet.
--------------------------------------------------------------------------------
--]]

target("eteleos-headers")
    set_kind("headeronly")

    -- ==========================================================================
    -- 1. Header installation -- plain public headers
    -- ==========================================================================
    -- The old Makefile hand-listed every filename in FILES=; here a glob is
    -- used instead so a new header dropped into include/ is picked up
    -- automatically (single "*.h" is non-recursive, so this only matches
    -- the flat files directly in include/, not the subdirectories below).
    add_headerfiles("*.h")

    -- DIRS= arpa protocols rpc rpcsvc in the old Makefile. The "(...)"
    -- capture preserves the subdirectory in the installed path, so these
    -- land at $(includedir)/arpa/*.h, $(includedir)/rpc/*.h, etc. The old
    -- Makefile also accepted *.i files here; kept for fidelity even though
    -- none currently exist.
    add_headerfiles("(arpa/*.h)",     "(arpa/*.i)")
    add_headerfiles("(protocols/*.h)","(protocols/*.i)")
    add_headerfiles("(rpc/*.h)",      "(rpc/*.i)")
    add_headerfiles("(rpcsvc/*.h)",   "(rpcsvc/*.i)")

    -- ==========================================================================
    -- 2. Exported include path
    -- ==========================================================================
    -- Public: any target that does add_deps("eteleos-headers") inherits this
    -- include directory automatically. Root's own add_includedirs("include")
    -- still covers modules that do not use add_deps; both are harmless
    -- together since they point at the same directory.
    add_includedirs("$(projectdir)/include", {public = true})

    -- ==========================================================================
    -- 3 & 4. Generated + compatibility headers (install-time only)
    -- ==========================================================================
    -- Runs AFTER the default header install above (after_install, not
    -- on_install, so add_headerfiles's own install step still happens).
    after_install(function (target)
        local installdir = get_config("installdir")
                            or path.join(os.scriptdir(), "..", "build", "install")
        local includedir = path.join(installdir, "include")
        local kernel_root = path.join(os.scriptdir(), "..", "kernel")

        -- Defensive: add_headerfiles's own install step normally creates
        -- $(installdir)/include already, but do not rely on that ordering
        -- implicitly -- make sure it exists before anything below tries to
        -- create a symlink inside it.
        if not os.isdir(includedir) then
            os.mkdir(includedir)
        end

        -- Replace a stale file/symlink at dst, then point it at "target_path".
        local function relink(dst, target_path)
            if os.isfile(dst) or os.islink(dst) then
                os.rm(dst)
            end
            os.ln(target_path, dst)
        end

        -- ---------------------------------------------------------------------
        -- Compatibility headers (old LFILES): the canonical definition lives
        -- in kernel/core/sys/<name>.h, exported below as
        -- $(includedir)/sys/<name>.h. Userland keeps including the
        -- traditional bare name (<fcntl.h>, <termios.h>, ...), which is just
        -- a symlink redirecting into sys/.
        -- ---------------------------------------------------------------------
        local compat_headers = {
            "endian.h", "fcntl.h", "syslog.h", "termios.h",
            "stdarg.h", "stdint.h", "varargs.h",
        }
        for _, name in ipairs(compat_headers) do
            relink(path.join(includedir, name), path.join("sys", name))
        end

        -- ---------------------------------------------------------------------
        -- Machine-dependent compatibility header (old MFILES): frame.h is a
        -- symlink to machine/frame.h, where "machine" (below) is itself a
        -- symlink to the currently selected architecture's header directory.
        -- ---------------------------------------------------------------------
        relink(path.join(includedir, "frame.h"), path.join("machine", "frame.h"))

        -- ---------------------------------------------------------------------
        -- Generated headers: kernel-exported directories (old LDIRS/"copies"
        -- target). Each entry maps the historical exported name to its new
        -- location under kernel/, confirmed against the current tree:
        --   old name  -> new kernel/ subpath
        -- ---------------------------------------------------------------------
        local kernel_exports = {
            crypto   = "crypto",
            ddb      = "ddb",
            dev      = "dev",
            isofs    = "fs/isofs",
            miscfs   = "core/miscfs",
            msdosfs  = "fs/msdosfs",
            net      = "net/net",
            netinet  = "net/netinet",
            netinet6 = "net/netinet6",
            netmpls  = "net/netmpls",
            net80211 = "net/net80211",
            nfs      = "fs/nfs",
            ntfs     = "fs/ntfs",
            scsi     = "dev/scsi",
            sys      = "core/sys",
            ufs      = "fs/ufs",
            uvm      = "uvm",
        }
        -- Sort keys for deterministic, easy-to-read install log output.
        local export_names = {}
        for name in pairs(kernel_exports) do
            export_names[#export_names + 1] = name
        end
        table.sort(export_names)

        for _, exported_name in ipairs(export_names) do
            local kernel_subpath = kernel_exports[exported_name]
            local src = path.join(kernel_root, kernel_subpath)
            local dst = path.join(includedir, exported_name)
            if os.isdir(src) then
                os.rm(dst)
                os.mkdir(dst)
                -- Recursive copy: some of these (e.g. dev/) have their own
                -- subdirectories (scsi/, pci/, usb/, ...) with public headers.
                os.cp(path.join(src, "**.h"), dst, {rootdir = src})
            else
                wprint("eteleos: kernel/%s not found, skipping include/%s export",
                       kernel_subpath, exported_name)
            end
        end

        -- ---------------------------------------------------------------------
        -- Per-architecture "machine" headers (also old "copies" target):
        -- kernel/arch/<target_arch>/include/*.h is exported as
        -- $(includedir)/<target_arch>/*.h, and "machine" is a symlink that
        -- always points at whichever architecture is currently selected.
        -- ---------------------------------------------------------------------
        local arch = get_config("target_arch") or "amd64"
        local arch_src = path.join(kernel_root, "arch", arch, "include")
        if os.isdir(arch_src) then
            local arch_dst = path.join(includedir, arch)
            os.rm(arch_dst)
            os.mkdir(arch_dst)
            os.cp(path.join(arch_src, "*.h"), arch_dst)
            relink(path.join(includedir, "machine"), arch)
        else
            wprint("eteleos: kernel/arch/%s/include not found, skipping machine headers",
                   arch)
        end

        cprint("${green}eteleos-headers${clear}: installed to %s", includedir)
    end)
target_end()
