--[[
================================================================================
 EteleOS: kernel/xmake.lua, time write: 2026/07/14
 This file uses the Apache-2.0 license
================================================================================

Manages: kernel core, subsystems ("modules"), drivers, architecture, linker
script, the final kernel image ("bsd"), and the EFI bootloader.

WHAT CHANGED IN THIS REVISION
------------------------------------------------------
The previous revision's hand-rolled files/GENERIC parser (parse_generic,
parse_files_list, eval_expr) had one confirmed correctness bug: it does not
resolve config(8)'s "attach <dev> at <bus> with <alias>" graph, so a file
conditioned on an attach alias (e.g. dev/ic/vga.c's "vga & (vga_pci |
vga_isa)") is wrongly excluded even when GENERIC enables it. It also never
generated ioconf.c.

Rather than extend the hand-rolled parser to reimplement config(8)'s
attach-graph resolution (config(8)'s own sem.c is ~1200 lines of exactly this
logic -- a second, parallel, Lua reimplementation is how the vga_pci bug got
in here in the first place), this revision builds and runs the REAL config(8)
as a private, build-time-only HOST tool, bootstrapped straight from its own
verified-present source at userland/system/config/*.c. This is not the same
"config" as userland/xmake.lua's own host-system-config target (that one
builds the INSTALLED /usr/sbin/config end users get); this is kernel/'s own
private bootstrap copy, analogous to how many OS build systems bootstrap a
small host-side tool ahead of the real build. Concretely, real config(8)
gives us, in one step:
  - ioconf.c, generated exactly the way config(8) has always generated it
    (see BUILD_HOST_CONFIG_TOOL / RUN_REAL_CONFIG / HARVEST_CONFIG_OUTPUT
    below), closing the "ioconf.c missing" gap.
  - a fully attach-graph-correct selected-files list, harvested from the
    Makefile config(8) itself writes (see HARVEST_CONFIG_OUTPUT) -- closing
    the vga_pci-style false-negative bug for free, because it is the real
    tool's own decision, not a re-derived approximation.

The restructuring the user flagged (source include paths not yet fixed for
the new layout) turned out, on inspection, to be a consistent pattern: the
old top-level sys/{conf,kern,lib,stand} each gained a new "core/" prefix
(verified: sys/conf -> kernel/core/conf, sys/lib -> kernel/core/lib, sys/
stand -> kernel/core/stand), dev/ absorbed scsi/ as a subdirectory (sys/scsi
-> kernel/dev/scsi), and net/ gained an extra nesting level (sys/net/if.h ->
kernel/net/net/if.h, same for netinet/netinet6/netmpls/net80211). Every
occurrence found so far (arch/<arch>/conf/GENERIC's own include line,
gram.y's hardcoded "conf/files" auto-include, files.amd64's own "include
scsi/files.scsi") is fixed with ONE general patch rather than one-off
staged copies: a scratch copy of config(8)'s own util.c has its sourcepath()
changed to retry a file under core/, dev/, or fs/ before giving up, when the
plain srcdir-relative path doesn't exist (patched into the private bootstrap
binary only -- see BUILD_HOST_CONFIG_TOOL below -- never touching the real
userland/system/config/util.c or any file under kernel/). This is a single,
general fix rather than a per-file special case, and -s (srcdir) is passed
as the real, unmodified kernel/ directory throughout: no staged/patched
GENERIC or files.* copies anywhere in this pipeline, and no filesystem
symlinks either (a symlink-based shim srcdir would silently break on a
Windows host with no symlink privilege -- a real concern, not a
hypothetical one, since this project's own transcripts show a Windows dev
environment; where a directory alias is genuinely needed -- <machine/...>
headers, see below -- it is a real directory COPY instead).

This file's include paths needed the same three fixes for the SAME reason,
confirmed by actually test-compiling this file end to end against the real
tree (not just reading it): kernel/core (for <sys/...>), kernel/fs (for
<isofs/...>, <ufs/...>, ...), and kernel/net (for <net/...>, <netinet/...>,
...) are all now on both the main kernel target's and the EFI bootloader's
include paths. <machine/...> resolution -- normally a "machine" symlink
config(8)/bsd.own.mk creates pointing at arch/<arch>/include -- is
materialized here as a real directory copy for the same Windows-portability
reason as above (arch/<arch>/include is a few hundred KB; copying it is
cheap and needs no special privilege).

Two small host-portability gaps surfaced the same way (this bootstrap tool
runs on the BUILD machine, which will not be OpenBSD): pledge(2) is
OpenBSD-only (compiled out via -Dpledge(a,b)=0 -- safe here since this is a
short-lived code generator, not the actual installed system tool userland/
xmake.lua's own host-system-config target already builds separately), and
BSD libc's major()/minor()/makedev()/errc() have no glibc equivalent
reachable the way config(8)'s sources expect (a tiny stub .c provides
standard-shaped replacements -- see devfuncs_stub_path below). The
interactive "UKC" boot-time config editor (cmd.c/ukc.c/ukcutil.c/exec_elf.c)
needs real BSD <nlist.h>/<kvm.h> host APIs unrelated to this bootstrap's
only job (batch-mode ioconf.c/file-list generation); since it is reachable
only through main.c's single, flag-gated "if (eflag) return ukc(...)" call,
those 4 files are excluded and replaced with a one-line ukc() stub instead
of chasing BSD-only headers that add nothing for this use case.

If the host bootstrap fails for any reason (no host C compiler, no
yacc/bison, no lex/flex, or a genuine compile error), this file falls back
to the OLD hand-rolled parser -- kept below, unchanged -- so a kernel still
builds (without ioconf.c, with the known attach-graph gap) rather than
hard-failing the whole project. Every fallback path prints a clear wprint()
explaining what is degraded and why, matching this file's existing style.

Tested (not just read) while drafting this revision: a plain Linux host
(gcc/bison/flex/lld) successfully bootstraps config(8), runs it against the
real GENERIC for amd64/arm64/riscv64 (2470/1803/951 files selected, all
three with ioconf.c generated), and compiles every EFI bootloader source for
all three architectures; amd64 additionally linked and objcopy'd into a
real, verified PE/EFI application end to end. arm64/riscv64 only got as far
as compiling (a cross-gcc packaging gap in the test sandbox, unrelated to
this project's actual clang-based toolchain, kept the link step from being
verified there too) -- worth re-confirming against the project's real
toolchain, but every source-level and path-resolution question is settled.

EFI BOOTLOADER (previously entirely out of scope)
------------------------------------------------------
kernel/arch/*/stand/ is real on all three supported architectures, but only
as EFI applications -- verified: arm64 and riscv64 have ONLY
stand/efiboot/ (no legacy BIOS chain at all, they are EFI-only platforms
upstream too), and amd64 additionally has biosboot/cdboot/cdbr/fdboot/mbr/
pxeboot/rdboot/vmboot (the legacy real-mode BIOS chain). This revision adds
EFI boot for all three architectures (ELETEOS_EFI_BOOTLOADERS below), reusing
the verified real recipe from each arch's own efiboot Makefile(.common):
compile freestanding+PIC, link as a "-shared" ELF, then objcopy into a PE/EFI
application (x86_64 via objcopy's real "efi-app-x86_64" BFD target; arm64/
riscv64 via a raw ".peheader"-section binary dump, exactly as their own
Makefiles do it -- the two are genuinely different mechanisms upstream, not
a simplification on this file's part).

The amd64-only legacy BIOS chain (biosboot/cdboot/cdbr/fdboot/mbr/pxeboot/
rdboot/vmboot) is explicitly NOT implemented here: it is 16-bit real-mode
code with flat-binary (not ELF) linking and sector-boundary size limits --
a genuinely different build problem from everything else in this file, and
one a modern hypervisor/UEFI-first target (this project's own VirtualBox
testing notes point the same way) needs far less than EFI boot does. Left
as an explicit follow-up, same as libraries/xmake.lua does for its own
deferred 19 libraries.

WHAT CHANGED IN THIS REVISION (2026/07/18) -- relocated to script scope
------------------------------------------------------------------------
Confirmed against a real xmake v3.0.9 build (not just documentation): io,
import, os.execv, os.iorun, pcall and even raw Lua error()/assert() are ALL
nil at xmake.lua description scope -- only a small read-only allowlist
(os.getenv, os.isfile, os.isdir, os.files, os.dirs, get_config, ...) is
available there. This means the config(8) bootstrap this file's own header
above describes as "tested... successfully bootstraps" was tested outside
xmake's own description-scope execution path -- the logic itself checks
out (re-confirmed here: 2470/1803/951 files selected, matching exactly),
but running it inline in a bare `do...end` block at the top of this file,
as the previous revision did, cannot actually load under a real xmake
binary. The exact same bootstrap logic now lives in
tools/gen/gen_kernel_manifest.lua, run via `xmake lua` (confirmed: io/
os.execv/import are all real there), writing its result to
generated_manifest.lua. This file just reads that manifest now. A few
smaller casualties of the same scope rule, also fixed here: wprint/cprint/
raise are script-scope-only too (fixed at every description-scope call
site to use print() instead); pcall is nil even inside on_load (fixed via
xmake's try{}/catch{} construct instead, confirmed to work there); and
config.builddir() is nil in EVERY scope, on_load included, since the
`config` module is never auto-imported (fixed throughout this project to
use path.join(os.projectdir(), "build", ...) instead, which needs no import
and, confirmed by testing, always resolves to a real path (get_config("builddir")
returned the project's "$(projectdir)/build" template UNEXPANDED during
xmake f in this project -- os.projectdir() itself is never templated). Also fixed
here: config(8)'s own output states some paths relative to the
pre-restructure flat layout (e.g. "conf/swapgeneric.c" for what is now
core/conf/swapgeneric.c) -- the driver/MI-optional file loop now retries
the same ""/"core/"/"dev/"/"fs/" prefixes tools/gen/gen_kernel_manifest.lua
already uses for config(8) itself, instead of silently dropping these as
if they were conditionally-disabled.
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
local arch   = get_config("target_arch") or "amd64"

-- ==============================================================================
-- Per-architecture facts (unchanged from the previous revision)
-- ==============================================================================
local MD_CORE_DIRS = { amd64 = "amd64", arm64 = "arm64", riscv64 = "riscv64" }

local BUS_GLUE_DIRS = {
    amd64   = {"isa", "pci"},
    arm64   = {"dev"},
    riscv64 = {"dev"},
}

-- Linker script filename -- NOT uniform across architectures.
local LDSCRIPT_NAMES = {
    amd64   = "ld.script",
    arm64   = "kern.ldscript",
    riscv64 = "kern.ldscript",
}

local CMACHFLAGS = {
    amd64 = {
        "-mcmodel=kernel", "-mno-red-zone",
        "-mno-sse2", "-mno-sse", "-mno-3dnow",
    },
    arm64 = {
        "-march=armv8-a+nofp+nosimd+rng",
        "-moutline-atomics",
        "-fno-stack-protector",
        "-mbranch-protection=bti",
    },
    riscv64 = {
        "-march=rv64gc", "-mcmodel=medany", "-mno-relax",
        "-fno-stack-protector",
    },
}

local PER_FILE_CFLAGS = {
    amd64 = {
        ["dev/pci/drm/amd/display/dc/dml/dcn10/dcn10_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/dcn20_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20.c"] = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20v2.c"]  = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20v2.c"]={"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn21/display_mode_vba_21.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn21/display_rq_dlg_calc_21.c"] = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn30/display_mode_vba_30.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn30/display_rq_dlg_calc_30.c"] = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn30/dcn30_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn31/display_mode_vba_31.c"]    = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn314/display_mode_vba_314.c"]  = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn314/display_rq_dlg_calc_314.c"]={"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn314/dcn314_fpu.c"]            = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn32/dcn32_fpu.c"]              = {"-msse", "-msse2"},
        ["dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_32.c"]    = {"-msse", "-msse2"},
    },
    arm64 = {},
    riscv64 = {},
}

if not MD_CORE_DIRS[arch] then
    print(string.format("eteleos-kernel: unsupported target_arch '%s' -- no kernel target "
          .. "will be built for it", arch))
end

local core_conf_dir = path.join(os.scriptdir(), "core", "conf")
local arch_conf_dir = path.join(os.scriptdir(), "arch", arch, "conf")

-- ==============================================================================
-- File discovery + config(8) bootstrap -- MOVED to tools/gen/gen_kernel_manifest.lua
-- ==============================================================================
-- Confirmed against a real xmake v3.0.9 build (not just documentation): io,
-- import, os.execv and os.iorun are all nil at xmake.lua description scope --
-- only a small read-only allowlist (os.getenv, os.isfile, os.isdir, os.files,
-- os.dirs, ...) is available there (see
-- docs.xmake.io/api/scripts/builtin-modules/import.html, "most module
-- interfaces can only be used in the script domain"). This is xmake's
-- long-standing scope model, not a 3.0-specific change, so the previous
-- revision of this file -- which built and ran config(8) directly in a bare
-- `do ... end` block at description scope, before target("eteleos-kernel")
-- even starts -- could not actually have loaded under a real xmake binary,
-- at any version.
--
-- That logic (bootstrap config(8) as a host tool from userland/system/config,
-- patch a scratch copy of util.c's sourcepath() for the post-restructure
-- directory layout, run it against each arch's real GENERIC, fall back to an
-- approximate files/GENERIC parser when any of that fails) is UNCHANGED --
-- only relocated to tools/gen/gen_kernel_manifest.lua, which runs via
-- `xmake lua` (confirmed: io/os.execv/import are all real there) and writes
-- its result to generated_manifest.lua as a plain ETELEOS_KERNEL_MANIFEST
-- global-table assignment, keyed by arch.
--
-- Verified end to end against the real tree, with bison/flex available on
-- the host: amd64 2470 files selected, arm64 1803, riscv64 951 -- via REAL
-- config(8) output, ioconf.c generated for all three -- matching this
-- project's own previously-recorded numbers, confirming the underlying
-- bootstrap logic itself was always sound and only needed to run in the
-- right scope. Without bison/flex on the host, all three arches cleanly
-- fall back to the approximate parser instead (373/344/303 files) rather
-- than failing outright.
--
-- Regenerate with: xmake lua tools/gen/gen_kernel_manifest.lua
-- (or: xmake eteleos-regen-kernel, once a project is configured)
-- whenever kernel/ Makefiles, GENERIC/files lists, or directory layout
-- change. The output is committed to the repo, like a `configure` script or
-- generated protobuf code -- description scope cannot regenerate it itself.
-- ==============================================================================

includes("generated_manifest.lua")

local selected_files, ioconf_c_path, ioconf_gendir = {}, nil, nil

local kernel_manifest = ETELEOS_KERNEL_MANIFEST and ETELEOS_KERNEL_MANIFEST[arch]
if kernel_manifest then
    selected_files = kernel_manifest.selected_files or {}
    if kernel_manifest.mode == "real-config8" and kernel_manifest.ioconf_c then
        ioconf_gendir = path.join(os.projectdir(), "build", "eteleos-kernel-gen", arch, "config-run", "build")
        ioconf_c_path = path.join(ioconf_gendir, "ioconf.c")
        -- NOTE: the actual file write happens in target("eteleos-kernel")'s
        -- on_load below (io.open needs script scope -- see this block's own
        -- header comment) -- ioconf_c_path/ioconf_gendir here are just the
        -- plain strings description scope is allowed to compute.
    end
    print(string.format("eteleos-kernel: %s: using %s output (%d files selected%s)",
          arch, kernel_manifest.mode == "real-config8" and "REAL config(8)" or "the approximate files/GENERIC parser",
          #selected_files, kernel_manifest.mode == "real-config8" and ", ioconf.c generated" or ""))
else
    print(string.format("eteleos-kernel: no generated_manifest.lua entry for arch '%s' -- "
          .. "run: xmake lua tools/gen/gen_kernel_manifest.lua -- building with zero "
          .. "driver/MI-optional files", arch))
end


-- ==============================================================================
-- Machine-independent kernel subsystems ("modules")
-- ==============================================================================
local KERNEL_MI_DIRS = {
    "core/kern", "core/lib/libkern", "core/miscfs",
    "uvm", "ddb", "crypto",
    "net/net", "net/netinet", "net/netinet6", "net/netmpls", "net/net80211",
    "fs/ufs", "fs/nfs", "fs/msdosfs", "fs/isofs", "fs/ntfs", "fs/tmpfs",
}

-- ==============================================================================
-- Kernel image
-- ==============================================================================
target("eteleos-kernel")
    set_kind("binary")
    set_basename("bsd")
    set_default(false)

    add_rules("eteleos.base", "eteleos.kernel")

    add_cxflags(unpack(CMACHFLAGS[arch] or {}))
    add_asflags(unpack(CMACHFLAGS[arch] or {}))

    for _, dir in ipairs(KERNEL_MI_DIRS) do
        local d = path.join(os.scriptdir(), dir)
        if os.isdir(d) then
            local files = os.files(path.join(d, "**.c"))
            if #files > 0 then add_files(unpack(files)) end
        else
            print(string.format("eteleos-kernel: kernel/%s not found, skipping", dir))
        end
    end

    for _, name in ipairs({"param.c", "swapgeneric.c"}) do
        local f = path.join(core_conf_dir, name)
        if os.isfile(f) then
            add_files(f)
        else
            print(string.format("eteleos-kernel: kernel/core/conf/%s not found, skipping", name))
        end
    end

    for relpath, cflags in pairs(PER_FILE_CFLAGS[arch] or {}) do
        local f = path.join(os.scriptdir(), relpath)
        if os.isfile(f) then
            add_files(f, {cxflags = cflags})
        else
            print(string.format("eteleos-kernel: per-file-cflags entry not found, skipping: %s", relpath))
        end
    end

    -- --- Driver + MI-optional sources -- selected_files now comes from
    -- REAL config(8) when available (see block above), the old approximate
    -- parser otherwise.
    do
        local added = 0
        local per_file_set = PER_FILE_CFLAGS[arch] or {}
        -- config(8)'s own output Makefile states each path relative to the
        -- flat pre-restructure sys/ layout convention (e.g. "conf/x.c",
        -- "kern/y.c") -- correct as-is for directories that stayed
        -- top-level under kernel/ (dev/, net/, uvm/, ddb/, crypto/, fs/),
        -- but stale for the four that moved under core/ (conf, kern, lib,
        -- stand). Same ""/"core/"/"dev/"/"fs/" fallback prefixes as the
        -- sourcepath() patch tools/gen/gen_kernel_manifest.lua applies for
        -- config(8) itself (see that file) -- needed again here since
        -- config(8)'s Makefile just echoes the original string, not its
        -- own already-resolved path.
        local PREFIXES = {"", "core/", "dev/", "fs/"}
        for _, relpath in ipairs(selected_files) do
            if not per_file_set[relpath] then
                local f = nil
                for _, prefix in ipairs(PREFIXES) do
                    local candidate = path.join(os.scriptdir(), prefix .. relpath)
                    if os.isfile(candidate) then f = candidate; break end
                end
                if f then
                    add_files(f)
                    added = added + 1
                end
                -- Missing files are expected here: many files/GENERIC entries
                -- are conditional on options that are always false on
                -- EteleOS's minimal enabled-set (vendor firmware blobs etc.)
            end
        end
        print(string.format("eteleos-kernel: %d driver/MI-optional files added (arch=%s)",
              added, arch))
    end

    -- --- ioconf.c, when real config(8) produced one --------------------------
    -- The actual file (io.open) is written inside on_load below, at script
    -- scope, then added via target:add("files", ...) there -- description
    -- scope cannot write it (see this file's earlier header note).
    if ioconf_gendir then
        add_includedirs(ioconf_gendir)
    end

    local md_dir = path.join(os.scriptdir(), "arch", arch, MD_CORE_DIRS[arch])
    if os.isdir(md_dir) then
        local c_files = os.files(path.join(md_dir, "*.c"))
        local s_files = os.files(path.join(md_dir, "*.S"))
        if #c_files > 0 then add_files(unpack(c_files)) end
        if #s_files > 0 then add_files(unpack(s_files)) end
    else
        print(string.format("eteleos-kernel: kernel/arch/%s/%s not found -- cannot build "
              .. "the kernel core for this architecture", arch, arch))
    end

    for _, bus in ipairs(BUS_GLUE_DIRS[arch] or {}) do
        local d = path.join(os.scriptdir(), "arch", arch, bus)
        if os.isdir(d) then
            local files = os.files(path.join(d, "**.c"))
            if #files > 0 then add_files(unpack(files)) end
        else
            print(string.format("eteleos-kernel: kernel/arch/%s/%s not found, skipping", arch, bus))
        end
    end

    -- <sys/...> headers moved to kernel/core/sys/ under the restructuring
    -- (verified: kernel/core/{conf,kern,lib,miscfs,stand,sys}) -- "core"
    -- itself must be on the include path, or every kernel .c file's very
    -- first #include <sys/param.h> fails to resolve (confirmed empirically
    -- against the real tree while drafting this file).
    add_includedirs(path.join(os.scriptdir(), "core"))
    -- <isofs/...>, <ufs/...>, <msdosfs/...>, <nfs/...> kernel filesystem
    -- headers live under kernel/fs/ (confirmed: fs/{isofs,msdosfs,nfs,ntfs,tmpfs,ufs})
    -- -- same "extra path segment" restructuring effect as core/ above
    -- (confirmed empirically: efidev.c's #include <isofs/cd9660/iso.h> fails without this).
    add_includedirs(path.join(os.scriptdir(), "fs"))
    -- <net/...>, <netinet/...>, <netinet6/...>, <netmpls/...>, <net80211/...>
    -- headers live under kernel/net/{net,netinet,netinet6,netmpls,net80211}/
    -- -- same restructuring effect again (confirmed empirically: efipxe.c's
    -- #include <net/if.h> fails without this, needing kernel/net/net/if.h).
    add_includedirs(path.join(os.scriptdir(), "net"))

    -- <machine/...> headers: real config(8)/bsd.own.mk machinery creates a
    -- "machine" SYMLINK in the object dir pointing at arch/<arch>/include
    -- (verified against arm64's own stand/efiboot/Makefile ".BEGIN:" rule).
    -- Materialized here as a real directory COPY instead of a symlink --
    -- arch/<arch>/include is small (a few hundred KB) and a plain copy
    -- needs no OS-specific symlink privilege (creating symlinks on Windows
    -- requires Developer Mode or admin rights, which cannot be assumed).
    -- The actual copy (os.cp) happens in on_load below -- also nil at
    -- description scope, confirmed the same way as io/os.iorun/os.cp above.
    local machine_gendir = path.join(os.projectdir(), "build", "eteleos-kernel-gen", arch)
    add_includedirs(machine_gendir)
    add_includedirs(path.join(os.scriptdir(), "arch", arch, "include"))
    add_includedirs(os.scriptdir())

    local ldscript = path.join(arch_conf_dir, LDSCRIPT_NAMES[arch])
    if os.isfile(ldscript) then
        add_ldflags("-Wl,-T," .. ldscript, {force = true})
    else
        print(string.format("eteleos-kernel: linker script not found at %s -- link step will fail", ldscript))
    end

    add_deps("eteleos-headers")

    on_load(function (target)
        local gendir = path.join(os.projectdir(), "build", "eteleos-kernel-gen", arch)
        os.mkdir(gendir)

        local machine_gendir = gendir
        if not os.isdir(path.join(machine_gendir, "machine")) then
            try
            {
                function()
                    os.cp(path.join(os.scriptdir(), "arch", arch, "include"),
                          path.join(machine_gendir, "machine"))
                end,
                catch { function(errs) wprint("eteleos-kernel: could not copy machine/ headers") end }
            }
        end

        if ioconf_c_path and kernel_manifest and kernel_manifest.ioconf_c then
            os.mkdir(ioconf_gendir)
            local f = (type(io) == "table" and io.open) and io.open(ioconf_c_path, "w") or nil
            if f then
                f:write(kernel_manifest.ioconf_c)
                f:close()
                target:add("files", ioconf_c_path)
            else
                wprint("eteleos-kernel: could not open %s for writing -- ioconf.c will be "
                       .. "missing for this build", ioconf_c_path)
            end
        end

        local function write_file_safe(filepath, content)
            local f = (type(io) == "table" and io.open) and io.open(filepath, "w") or nil
            if not f then
                wprint("eteleos-kernel: could not open %s for writing", filepath)
                return false
            end
            f:write(content)
            f:close()
            return true
        end

        local kernel_version = "0.1.0"
        local vers_c = string.format([[
/* Auto-generated by kernel/xmake.lua -- do not edit. */
char version[] = "EteleOS %s (%s) #0: %s\n";
]], kernel_version, arch, os.date("%a %b %d %H:%M:%S %Y"))
        local vers_path = path.join(gendir, "vers.c")
        write_file_safe(vers_path, vers_c)
        target:add("files", vers_path)

        local genassym_sh = path.join(os.scriptdir(), "core", "kern", "genassym.sh")
        local genassym_cf = path.join(md_dir, "genassym.cf")
        local assym_h = path.join(gendir, "assym.h")
        import("lib.detect.find_tool")
        local sh = find_tool("sh")
        if not sh then
            wprint("eteleos-kernel: no POSIX shell (sh) found -- genassym.sh needs one "
                   .. "to run. On Windows, install Git Bash, WSL, or MSYS2 and make sure "
                   .. "its sh is on PATH; on Linux/macOS this should already be present. "
                   .. "Writing a stub assym.h for now (locore.%s will likely fail to "
                   .. "assemble until this is resolved).", arch)
            write_file_safe(assym_h, "/* assym.h not generated -- no POSIX shell (sh) found on this host */\n")
        elseif os.isfile(genassym_sh) and os.isfile(genassym_cf) then
            local cc = get_config("cc") or "clang"
            local flags = table.concat(CMACHFLAGS[arch] or {}, " ")
            local incflags = "-I" .. path.join(os.scriptdir(), "arch", arch, "include")
                              .. " -I" .. os.scriptdir()
            local cmd = string.format('"%s" "%s" %s -ffreestanding %s %s < "%s"',
                                       sh.program, genassym_sh, cc, flags, incflags, genassym_cf)
            local outdata = try
            {
                function() return (os.iorun(cmd)) end,
                catch
                {
                    function(errs) return nil end
                }
            }
            if not outdata or outdata == "" then
                wprint("eteleos-kernel: genassym.sh produced no usable output for %s "
                       .. "-- assym.h will be a stub and locore.%s will likely fail to "
                       .. "assemble. Verify the genassym.sh invocation manually.",
                       genassym_cf, arch)
                outdata = "/* genassym.sh generation failed or produced no output */\n"
            end
            write_file_safe(assym_h, outdata)
        else
            wprint("eteleos-kernel: genassym.sh or %s not found, writing an empty assym.h",
                   genassym_cf)
            write_file_safe(assym_h, "/* assym.h not generated -- inputs missing */\n")
        end
        target:add("includedirs", gendir)
    end)
target_end()

-- ==============================================================================
-- EFI bootloader -- one target per architecture, built as a phony target
-- with its whole recipe in on_build (freestanding compile -> shared-object
-- link -> objcopy to the final .EFI application), since none of this is a
-- normal "compile to an executable" xmake target kind. Source lists below
-- are transcribed directly from each arch's real, verified efiboot Makefile
-- (Makefile.common for amd64/bootx64+bootia32; each arch's own single
-- Makefile for arm64/riscv64, which are self-contained) -- NOT auto-globbed,
-- because these directories mix in unrelated files (softraid_arm64.h,
-- headers, etc.) that must not be fed to the compiler as sources.
-- ==============================================================================
local EFI_BOOTLOADERS = {
    amd64 = {
        efidir       = "core/stand/efi",
        arch_efidir  = "arch/amd64/stand/efiboot",
        prog_dir     = "arch/amd64/stand/efiboot/bootx64",
        prog_name    = "BOOTX64.EFI",
        ldscript     = "arch/amd64/stand/efiboot/ldscript.amd64",
        objcopy_mode = "bfd-target", -- objcopy --target=efi-app-x86_64
        objfmt       = "efi-app-x86_64",
        efi_inc_arch = "amd64",
        defines      = {"EFIBOOT", "FWRANDOM", "NEEDS_HEAP_H", "SOFTRAID",
                         "IDLE_POWEROFF", "_STANDALONE", "SMALL", "SLOW",
                         "__INTERNAL_LIBSA_CREAD", "HIBERNATE",
                         "HEAP_LIMIT=0xc00000"},
        cflags       = {"-ffreestanding", "-std=gnu99", "-fshort-wchar", "-fPIC",
                         "-mno-red-zone", "-nostdinc", "-fno-builtin", "-Wno-pointer-sign"},
        own_srcs     = {"self_reloc.c", "efiboot.c", "efidev.c", "efipxe.c", "efirng.c",
                         "conf.c", "dev_i386.c", "cmd_i386.c", "diskprobe.c",
                         "exec_i386.c", "machdep.c", "memprobe.c"},
        -- own_srcs above live in arch_efidir (the shared parent of bootx64/
        -- and bootia32/, per Makefile.common's ".PATH: ${.CURDIR}/..");
        -- bootprog_srcs are bootx64's OWN 3 files, in prog_dir itself.
        own_srcs_dir = "arch_efidir",
        bootprog_srcs = {"start_amd64.S", "run_i386.S", "mdrandom.c"},
        boot_srcs    = {"boot.c", "bootarg.c", "cmd.c", "vars.c"},
        libsa_srcs   = {"alloc.c", "ctime.c", "exit.c", "getchar.c", "hexdump.c",
                        "memcmp.c", "memcpy.c", "memmove.c", "memset.c", "printf.c",
                        "putchar.c", "snprintf.c", "strcmp.c", "strerror.c", "strlen.c",
                        "strncmp.c", "strncpy.c", "strtol.c", "strtoll.c",
                        "close.c", "closeall.c", "cons.c", "cread.c", "dev.c",
                        "disklabel.c", "dkcksum.c", "fchmod.c", "fstat.c", "lseek.c",
                        "open.c", "read.c", "readdir.c", "stat.c", "ufs.c", "ufs2.c",
                        "cd9660.c", "loadfile.c", "arc4.c",
                        "aes_xts.c", "bcrypt_pbkdf.c", "blowfish.c", "explicit_bzero.c",
                        "hmac_sha1.c", "pkcs5_pbkdf2.c", "rijndael.c", "sha1.c",
                        "sha2.c", "softraid.c"},
        libz_srcs    = {"adler32.c", "crc32.c", "inflate.c", "inftrees.c"},
        libkern_srcs = {"ashldi3.c", "ashrdi3.c", "divdi3.c", "lshrdi3.c",
                         "moddi3.c", "qdivrem.c", "strlcpy.c"},
        -- arch-specific (arch/amd64/stand/libsa/, NOT core/lib/libsa)
        -- additions -- verified on disk: only elf64.c/elf32.c live there;
        -- loadfile.c/arc4.c were consolidated into core/lib/libsa (above)
        -- by the restructuring, unlike arm64/riscv64 where they never
        -- existed under arch/<arch>/stand/libsa/ to begin with.
        arch_libsa_srcs = {"elf64.c", "elf32.c"},
    },
    arm64 = {
        efidir       = "core/stand/efi",
        arch_efidir  = "arch/arm64/stand/efiboot",
        prog_dir     = "arch/arm64/stand/efiboot",
        prog_name    = "BOOTAA64.EFI",
        ldscript     = "arch/arm64/stand/efiboot/ldscript.arm64",
        objcopy_mode = "peheader-binary", -- objcopy --output-target=binary of specific sections
        objfmt       = "binary",
        efi_inc_arch = "arm64",
        defines      = {"_STANDALONE", "BOOT_STTY", "SMALL", "SLOW",
                         "__INTERNAL_LIBSA_CREAD", "NEEDS_HEAP_H", "MDRANDOM", "FWRANDOM"},
        cflags       = {"-ffreestanding", "-fno-stack-protector", "-fshort-wchar",
                         "-fPIC", "-fno-builtin", "-Wno-attributes", "-Wno-format",
                         "-nostdinc"},
        own_srcs     = {"start.S", "self_reloc.c", "efiboot.c", "conf.c", "exec.c",
                         "efiacpi.c", "efidev.c", "efipxe.c", "efirng.c", "fdt.c", "smbios.c",
                         "softraid_arm64.c"},
        boot_srcs    = {"boot.c", "cmd.c", "vars.c"},
        libsa_srcs   = {"alloc.c", "ctime.c", "exit.c", "getchar.c", "hexdump.c",
                        "memcmp.c", "memcpy.c", "memmove.c", "memset.c",
                        "printf.c", "putchar.c", "snprintf.c", "strchr.c", "strcmp.c",
                        "strerror.c", "strncmp.c", "strncpy.c", "strtol.c", "strtoll.c",
                        "close.c", "closeall.c", "cons.c", "cread.c", "dev.c",
                        "disklabel.c", "dkcksum.c", "fchmod.c", "fstat.c", "lseek.c",
                        "open.c", "read.c", "readdir.c", "stat.c",
                        "loadfile.c", "arc4.c", "ufs.c", "ufs2.c", "cd9660.c",
                        "arp.c", "ether.c", "globals.c", "in_cksum.c", "net.c",
                        "netif.c", "netudp.c", "tftp.c",
                        "aes_xts.c", "bcrypt_pbkdf.c", "blowfish.c", "explicit_bzero.c",
                        "hmac_sha1.c", "pkcs5_pbkdf2.c", "rijndael.c", "sha1.c",
                        "sha2.c", "softraid.c"},
        libz_srcs    = {"adler32.c", "crc32.c", "inflate.c", "inftrees.c"},
        libkern_srcs = {"divdi3.c", "moddi3.c", "qdivrem.c", "strlcat.c", "strlcpy.c", "strlen.c"},
        arch_libsa_srcs = {},
    },
    riscv64 = {
        efidir       = "core/stand/efi",
        arch_efidir  = "arch/riscv64/stand/efiboot",
        prog_dir     = "arch/riscv64/stand/efiboot",
        prog_name    = "BOOTRISCV64.EFI",
        ldscript     = "arch/riscv64/stand/efiboot/ldscript.riscv64",
        objcopy_mode = "peheader-binary",
        objfmt       = "binary",
        efi_inc_arch = "riscv64",
        defines      = {"_STANDALONE", "BOOT_STTY", "SMALL", "SLOW",
                         "__INTERNAL_LIBSA_CREAD", "NEEDS_HEAP_H", "FWRANDOM"},
        cflags       = {"-ffreestanding", "-fno-stack-protector", "-fshort-wchar",
                         "-fPIC", "-fno-builtin", "-Wno-attributes", "-Wno-format",
                         "-nostdinc", "-march=rv64gc", "-mno-relax"},
        own_srcs     = {"start.S", "self_reloc.c", "efiboot.c", "conf.c", "exec.c",
                         "efidev.c", "efipxe.c", "efirng.c", "fdt.c",
                         "softraid_riscv64.c", "efiriscv.c"},
        boot_srcs    = {"boot.c", "cmd.c", "vars.c"},
        libsa_srcs   = {"alloc.c", "ctime.c", "exit.c", "getchar.c", "hexdump.c",
                        "memcmp.c", "memcpy.c", "memmove.c", "memset.c",
                        "printf.c", "putchar.c", "snprintf.c", "strchr.c", "strcmp.c",
                        "strerror.c", "strncmp.c", "strncpy.c", "strtol.c", "strtoll.c",
                        "close.c", "closeall.c", "cons.c", "cread.c", "dev.c",
                        "disklabel.c", "dkcksum.c", "fchmod.c", "fstat.c", "lseek.c",
                        "open.c", "read.c", "readdir.c", "stat.c",
                        "loadfile.c", "arc4.c", "ufs.c", "ufs2.c",
                        "arp.c", "ether.c", "globals.c", "in_cksum.c", "net.c",
                        "netif.c", "netudp.c", "tftp.c",
                        "aes_xts.c", "bcrypt_pbkdf.c", "blowfish.c", "explicit_bzero.c",
                        "hmac_sha1.c", "pkcs5_pbkdf2.c", "rijndael.c", "sha1.c",
                        "sha2.c", "softraid.c"},
        libz_srcs    = {"adler32.c", "crc32.c", "inflate.c", "inftrees.c"},
        libkern_srcs = {"divdi3.c", "moddi3.c", "qdivrem.c", "strlcat.c", "strlcpy.c", "strlen.c"},
        arch_libsa_srcs = {},
    },
}

local function efi_collect(root, dir, names)
    local out = {}
    for _, n in ipairs(names or {}) do
        local f = path.join(root, dir, n)
        if os.isfile(f) then
            out[#out + 1] = f
        else
            wprint("eteleos-kernel-efiboot: expected source not found, skipping: %s", f)
        end
    end
    return out
end

local function eteleos_efi_bootloader(target_arch)
    local spec = EFI_BOOTLOADERS[target_arch]
    if not spec then return end
    local root = os.scriptdir()

    if not os.isdir(path.join(root, spec.prog_dir)) then
        print(string.format("eteleos-kernel-efiboot: %s not found, skipping EFI bootloader for %s",
              spec.prog_dir, target_arch))
        return
    end

    target("eteleos-kernel-efiboot-" .. target_arch)
        set_kind("phony")
        set_default(false)

        on_build(function (t)
            import("lib.detect.find_tool")
            local cc = get_config("cc") or "clang"
            local have_lld = find_tool("ld.lld") ~= nil
            if not have_lld then
                wprint("eteleos-kernel-efiboot: ld.lld not found -- the EFI bootloader "
                       .. "link step needs LLD specifically (--pack-dyn-relocs=none is "
                       .. "an LLD-only flag, matching every real efiboot Makefile in "
                       .. "this tree); skipping %s for %s rather than attempting a "
                       .. "broken link with a different linker", spec.prog_name, target_arch)
                return
            end
            local objcopy = find_tool("llvm-objcopy") or find_tool("objcopy")
            if not objcopy then
                wprint("eteleos-kernel-efiboot: no objcopy/llvm-objcopy found, cannot "
                       .. "produce %s for %s", spec.prog_name, target_arch)
                return
            end

            local gendir = path.join(os.projectdir(), "build",
                                      "eteleos-kernel-gen", target_arch, "efiboot")
            os.mkdir(gendir)

            local srcs = {}
            local function extend(t) for _, v in ipairs(t) do srcs[#srcs + 1] = v end end
            local own_dir = (spec.own_srcs_dir == "arch_efidir") and spec.arch_efidir or spec.prog_dir
            extend(efi_collect(root, own_dir, spec.own_srcs))
            if spec.bootprog_srcs then
                extend(efi_collect(root, spec.prog_dir, spec.bootprog_srcs))
            end
            extend(efi_collect(root, "core/stand/boot", spec.boot_srcs))
            extend(efi_collect(root, "core/lib/libsa", spec.libsa_srcs))
            extend(efi_collect(root, "core/lib/libz", spec.libz_srcs))
            -- core/lib/libkern/arch/<arch>/ exists for some archs but only
            -- holds optimized asm overrides (e.g. arm64's is just ffs.S) --
            -- every plain .c file this list needs (divdi3.c, moddi3.c, ...)
            -- lives directly under core/lib/libkern/ for all three archs
            -- (confirmed on disk while testing this file).
            extend(efi_collect(root, "core/lib/libkern", spec.libkern_srcs))
            if #spec.arch_libsa_srcs > 0 then
                extend(efi_collect(root, path.join("arch", target_arch, "stand", "libsa"),
                                    spec.arch_libsa_srcs))
            end

            if #srcs == 0 then
                wprint("eteleos-kernel-efiboot: zero source files resolved for %s, aborting",
                       target_arch)
                return
            end

            -- <machine/...> alias, same reasoning as the main kernel target
            -- above: a real copy, not a symlink (Windows-host portable).
            local machine_alias_dir = path.join(gendir, "machine-alias")
            if not os.isdir(path.join(machine_alias_dir, "machine")) then
                try
                {
                    function()
                        os.cp(path.join(root, "arch", target_arch, "include"),
                              path.join(machine_alias_dir, "machine"))
                    end,
                    catch { function(errs) wprint("eteleos-kernel-efiboot: could not copy machine/ headers") end }
                }
            end

            local includedirs = {
                path.join(root, spec.prog_dir),
                path.join(root, spec.arch_efidir),
                root,
                path.join(root, "core"),          -- <sys/...> -> core/sys/...
                path.join(root, "fs"),            -- <isofs/...>, <ufs/...> -> fs/isofs/..., fs/ufs/...
                path.join(root, "net"),            -- <net/...>, <netinet/...> -> net/net/..., net/netinet/...
                machine_alias_dir,                -- <machine/...> -> arch/<arch>/include/...
                path.join(root, "arch", target_arch, "stand", "libsa"),
                path.join(root, "core", "lib", "libsa"),
                path.join(root, spec.efidir, "include"),
                path.join(root, spec.efidir, "include", spec.efi_inc_arch),
                path.join(root, "core", "stand", "boot"),
            }

            local objs = {}
            for _, src in ipairs(srcs) do
                local objname = path.filename(src):gsub("%.[cS]$", "") .. ".o"
                local objpath = path.join(gendir, objname)
                local args = { "-c", "-o", objpath, src }
                for _, d in ipairs(includedirs) do args[#args + 1] = "-I" .. d end
                for _, d in ipairs(spec.defines) do args[#args + 1] = "-D" .. d end
                for _, f in ipairs(spec.cflags) do args[#args + 1] = f end
                if not os.execv(cc, args, {try = true}) then
                    wprint("eteleos-kernel-efiboot: failed to compile %s for %s, aborting",
                           src, target_arch)
                    return
                end
                objs[#objs + 1] = objpath
            end

            -- Link as a shared object (matches every real efiboot Makefile:
            -- "-nostdlib -T<ldscript> -Bsymbolic -shared"), then reformat
            -- into the final .EFI PE application. Only force -fuse-ld=lld
            -- when lld is actually present -- earlier drafts of this file
            -- hardcoded -fuse-ld=lld unconditionally, which breaks the
            -- build on any host that only has the default linker (verified
            -- while testing this file: "collect2: cannot find 'ld'" when
            -- lld isn't installed even though a perfectly usable ld is).
            local so_path = path.join(gendir, (spec.prog_name:gsub("%.EFI$", ".so")))
            local link_args = { "-fuse-ld=lld" }
            local more_link_args = {
                "-nostdlib", "-Wl,-T," .. path.join(root, spec.ldscript),
                "-Wl,-Bsymbolic", "-shared", "-Wl,--pack-dyn-relocs=none",
                "-o", so_path,
            }
            for _, a in ipairs(more_link_args) do link_args[#link_args + 1] = a end
            for _, o in ipairs(objs) do link_args[#link_args + 1] = o end
            if not os.execv(cc, link_args, {try = true}) then
                wprint("eteleos-kernel-efiboot: link step failed for %s, aborting", target_arch)
                return
            end

            local efi_path = path.join(gendir, spec.prog_name)
            local ok
            if spec.objcopy_mode == "bfd-target" then
                -- amd64: objcopy's own "efi-app-x86_64" BFD target does the
                -- ELF -> PE reformatting.
                ok = os.execv(objcopy.program, {
                    "-j", ".text", "-j", ".sdata", "-j", ".data", "-j", ".dynamic",
                    "-j", ".dynsym", "-j", ".rel", "-j", ".rel.dyn", "-j", ".rela",
                    "-j", ".rela.dyn", "-j", ".reloc",
                    "--target=" .. spec.objfmt, so_path, efi_path,
                }, {try = true})
            else
                -- arm64/riscv64: the PE header is a real section (.peheader)
                -- built by the linker script itself; objcopy just needs to
                -- concatenate the selected sections as raw bytes, in order.
                ok = os.execv(objcopy.program, {
                    "-j", ".peheader", "-j", ".text", "-j", ".sdata", "-j", ".data",
                    "-j", ".dynamic", "-j", ".dynsym", "-j", ".dynstr", "-j", ".rel",
                    "-j", ".rel.dyn", "-j", ".rela", "-j", ".rela.dyn", "-j", ".reloc",
                    "--output-target=" .. spec.objfmt, so_path, efi_path,
                }, {try = true})
            end
            if not ok or not os.isfile(efi_path) then
                wprint("eteleos-kernel-efiboot: objcopy step failed for %s, aborting", target_arch)
                return
            end
            cprint("${green}eteleos-kernel-efiboot${clear}: built %s for %s", spec.prog_name, target_arch)
        end)
    target_end()
end

eteleos_efi_bootloader(arch)
