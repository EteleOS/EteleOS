--[[
================================================================================
 EteleOS: libraries/xmake.lua, time write: 2026/07/16
 This file uses the Apache-2.0 license
================================================================================

Manages the whole libraries/ tree: libc, libm, libcrypto, libssl, libpthread,
librthread, libutil, libtls, libz, libedit, libelf, libevent, libexpat (all of
libraries/core/), plus every library under libraries/extra/, following the
current source layout (verified against github.com/EteleOS/EteleOS, NOT the
stale per-library Makefiles, which still reference pre-restructure paths).

Every library is built as a PAIR of targets -- "<name>-static" and
"<name>-shared" -- via the eteleos_bsd_library() helper below. This file does
not compile object/kernel/userland/driver/xenocara code; it only builds the
libraries/ tree, per the build spec.

WHAT CHANGED IN THIS REVISION
------------------------------------------------------
1. libc syscall stubs (previously missing -- only the one hand-written
   libc/sys/canceled.c was ever picked up by the generic glob). The real
   OpenBSD mechanism, confirmed against libc/sys/Makefile.inc, is NOT "parse
   syscalls.master and generate one .S per entry" -- it's simpler: the
   Makefile hand-maintains 5 name lists (ASM, ASM_NOERR, PSEUDO,
   PSEUDO_NOERR, HIDDEN) and, for each name, pipes a 2-line "source"
   (#include "SYS.h" + one of RSYSCALL()/RSYSCALL_NOERROR()/PSEUDO()/
   PSEUDO_NOERROR()/RSYSCALL_HIDDEN()) straight into the compiler, no file
   ever written to disk. This revision parses those 5 lists out of
   libc/sys/Makefile.inc (a small, constrained parse -- not a general
   Makefile parser) and materializes the same 2-line stub as a real file
   under a gendir instead of piping to stdin, since that fits this project's
   add_files()-based model much better; a handful of syscalls with real,
   hand-written .S files (Ovfork.S, brk.S, sigprocmask.S, ...) are picked up
   by the ordinary glob exactly as before, unaffected by this change.
2. All 19 libraries under libraries/extra/ (besides librthread, already
   wired) are now built. Most reuse eteleos_bsd_library() unchanged; four
   needed real per-library handling, documented at each call site:
   libkvm (arch-specific kvm_<arch>.c), libossaudio (sources shared with
   libsndio), libpcap (yacc/lex with a custom symbol prefix, plus one file
   from kernel/net/net/), and librpcsvc (every source is rpcgen-generated
   from a .x spec, not written by hand). Symbol-visibility control
   (Symbols.map / VERSION_SCRIPT, present in several of these Makefiles) is
   NOT implemented here -- every library still builds and links correctly
   without it, it only affects which symbols are exported as public ABI, so
   it is left as a follow-up rather than a build-correctness fix.
--------------------------------------------------------------------------------
--]]

local unpack = table.unpack or unpack

-- ==============================================================================
-- Helpers (local to this file -- library-build-specific, not project-wide
-- utilities, so these do not belong in tools/helpers.lua)
-- ==============================================================================

-- Read a small text file fully. Returns nil if it does not exist.
local function read_file(filepath)
    local f = io.open(filepath, "r")
    if not f then return nil end
    local content = f:read("*a")
    f:close()
    return content
end

local function write_file(filepath, content)
    local f = io.open(filepath, "w")
    if not f then raise("eteleos: could not write %s", filepath) end
    f:write(content)
    f:close()
end

-- "foo/bar/baz.c" -> "baz" (basename without extension). Pure Lua pattern
-- matching -- no dependency on any xmake-specific path.* helper.
local function basename_noext(filepath)
    local name = filepath:match("([^/]+)$") or filepath
    return (name:gsub("%.[^.]+$", ""))
end

-- Collect a library's source files, honoring the BSD machine-dependent (MD)
-- override convention used throughout OpenBSD's libc/libcrypto: a file
-- under arch/<MACHINE>/... REPLACES a machine-independent (MI) file of the
-- same basename anywhere else in the tree (e.g. arch/amd64/string/bcopy.S
-- overrides the generic string/bcopy.c). Returns two file lists: the
-- portable (MI) sources, and the active architecture's MD sources.
local function collect_sources(srcdir, arch)
    local overridden = {}   -- basename (no ext) -> true
    local md_files = {}
    local arch_dir = path.join(srcdir, "arch", arch)
    if os.isdir(arch_dir) then
        for _, f in ipairs(os.files(path.join(arch_dir, "**.c"))) do
            md_files[#md_files + 1] = f
            overridden[basename_noext(f)] = true
        end
        for _, f in ipairs(os.files(path.join(arch_dir, "**.S"))) do
            md_files[#md_files + 1] = f
            overridden[basename_noext(f)] = true
        end
    end

    local mi_files = {}
    local arch_root = path.join(srcdir, "arch") .. "/"
    for _, f in ipairs(os.files(path.join(srcdir, "**.c"))) do
        -- Skip anything under arch/ entirely (other architectures' MD code
        -- must never be compiled into this build).
        if f:sub(1, #arch_root) ~= arch_root then
            if not overridden[basename_noext(f)] then
                mi_files[#mi_files + 1] = f
            end
        end
    end
    return mi_files, md_files
end

-- Parse "major=N" / "minor=N" out of a BSD-style shlib_version file.
-- Returns 0, 0 if the file is missing or unparseable.
local function read_shlib_version(srcdir)
    local content = read_file(path.join(srcdir, "shlib_version"))
    if not content then return 0, 0 end
    local major = tonumber(content:match("major%s*=%s*(%d+)")) or 0
    local minor = tonumber(content:match("minor%s*=%s*(%d+)")) or 0
    return major, minor
end

-- ==============================================================================
-- libc syscall stubs -- see file header. Parses ASM/ASM_NOERR/PSEUDO/
-- PSEUDO_NOERR/HIDDEN out of libc/sys/Makefile.inc and materializes the
-- 2-line SYS.h-macro stub each name expands to, as a real file per name,
-- instead of piping to the compiler's stdin the way the real Makefile does
-- (add_files() needs real paths; this is the same content either way).
-- ==============================================================================
local SYSCALL_CLASS_MACRO = {
    ASM         = "RSYSCALL",
    ASM_NOERR   = "RSYSCALL_NOERROR",
    PSEUDO      = "PSEUDO",
    PSEUDO_NOERR= "PSEUDO_NOERROR",
    HIDDEN      = "RSYSCALL_HIDDEN",
}

-- Parse a handful of specific "NAME= tok1 tok2 \" continuation-style
-- variable assignments out of a Makefile.inc -- NOT a general Makefile
-- parser, just enough to read the 5 fixed list names above (each entry is
-- a bare object-file-like token, e.g. "access.o", ".o" stripped below).
-- Two-pass: (1) collect every "NAME= tok tok \" / "NAME+= tok tok \"
-- continuation-style variable in the file (not just the 5 syscall
-- classes), so a list can reference another one; (2) expand the two
-- BSD-make substitution forms actually used here when they appear as a
-- token inside one of the 5 tracked class lists:
--   ${VAR:=SUFFIX}     -- append SUFFIX to every word in VAR
--   ${VAR:%=PRE%POST}  -- %-pattern substitution over every word in VAR
-- Anything else shaped like "${...}" is a BSD-make construct this small,
-- deliberately-not-a-general-Makefile-parser does not understand -- it is
-- dropped with a warning rather than risk emitting a bogus generated file
-- name (confirmed necessary by testing: without this, the literal,
-- unexpanded "${CANCEL:=.o}" token leaked through as a garbage file name).
local function parse_syscall_lists(makefile_inc_path)
    local content = read_file(makefile_inc_path)
    if not content then return nil end

    local raw_vars = {}   -- every NAME= list, tokens as literally written (with .o kept)
    local current_var = nil
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local stripped = line:gsub("#.*$", "")
        local var, op, rest = stripped:match("^(%u+[%u_]*)%s*([:+]?=)%s*(.-)\\?%s*$")
        if var then
            if op == "+=" and raw_vars[var] then
                current_var = var
            else
                current_var = var
                raw_vars[var] = raw_vars[var] or {}
            end
            for tok in rest:gmatch("%S+") do
                raw_vars[current_var][#raw_vars[current_var] + 1] = tok
            end
            if not stripped:match("\\%s*$") then current_var = nil end
        elseif current_var and stripped:match("%S") then
            for tok in stripped:gmatch("%S+") do
                raw_vars[current_var][#raw_vars[current_var] + 1] = tok
            end
            if not stripped:match("\\%s*$") then current_var = nil end
        else
            current_var = nil
        end
    end

    local function expand_token(tok)
        local vname, suffix = tok:match("^%${(%u+):=(.-)}$")
        if vname and raw_vars[vname] then
            local out = {}
            for _, w in ipairs(raw_vars[vname]) do out[#out + 1] = w .. suffix end
            return out
        end
        local vname2, pre, post = tok:match("^%${(%u+):%%=(.-)%%(.-)}$")
        if vname2 and raw_vars[vname2] then
            local out = {}
            for _, w in ipairs(raw_vars[vname2]) do out[#out + 1] = pre .. w .. post end
            return out
        end
        if tok:find("%$") or tok:find("{") then
            wprint("eteleos: libc syscall list parser: don't know how to expand "
                   .. "\"%s\" -- skipping this token (see parse_syscall_lists)", tok)
            return {}
        end
        return { tok }
    end

    local lists = {}
    for class in pairs(SYSCALL_CLASS_MACRO) do
        lists[class] = {}
        for _, tok in ipairs(raw_vars[class] or {}) do
            for _, expanded in ipairs(expand_token(tok)) do
                lists[class][#lists[class] + 1] = (expanded:gsub("%.o$", ""))
            end
        end
    end

    -- Cancellation-point syscalls (CANCEL=) get their PUBLIC symbol from a
    -- hand-written w_<name>.c wrapper (already picked up by the ordinary
    -- source glob), which calls the raw syscall via HIDDEN(name) -- so the
    -- raw stub for these names must be HIDDEN-only, never also a plain
    -- ASM/ASM_NOERR/PSEUDO/PSEUDO_NOERR entry (that would either collide
    -- with w_<name>.c's own public symbol, or generate a stub nothing
    -- calls). The real Makefile does this subtraction with a ":N" filter
    -- this parser doesn't generically evaluate; the same result is applied
    -- directly here since the rule itself is simple and confirmed.
    local cancel_set = {}
    for _, tok in ipairs(raw_vars.CANCEL or {}) do cancel_set[tok] = true end
    for _, class in ipairs({"ASM", "ASM_NOERR", "PSEUDO", "PSEUDO_NOERR"}) do
        local filtered = {}
        for _, name in ipairs(lists[class]) do
            if not cancel_set[name] then filtered[#filtered + 1] = name end
        end
        lists[class] = filtered
    end

    return lists
end

-- Generate one gendir/<name>.S per entry in the 5 lists, materializing
-- exactly the 2-line stub the real Makefile pipes to the compiler
-- (#include "SYS.h" + the class macro). Returns the list of generated
-- file paths, or {} if libc/sys/Makefile.inc could not be parsed.
local function generate_syscall_stubs(libc_srcdir, gendir)
    local lists = parse_syscall_lists(path.join(libc_srcdir, "sys", "Makefile.inc"))
    if not lists then
        wprint("eteleos: libc/sys/Makefile.inc not found or unparseable -- syscall "
               .. "stubs will NOT be generated; libc will build but have no syscall "
               .. "entry points")
        return {}
    end
    os.mkdir(gendir)
    -- The public/hidden C symbol name usually matches the kernel syscall
    -- name exactly (RSYSCALL(x) et al above expand to the 2-arg PSEUDO
    -- family with x used for both) -- confirmed against
    -- kernel/core/kern/syscalls.master for the underscore-prefixed HIDDEN
    -- entries too (sys___realpath, sys___getcwd: the kernel's own names
    -- already carry the same underscores, so no translation is needed).
    -- _exit is the one confirmed exception: its public symbol is "_exit"
    -- but the kernel syscall it invokes is plain "sys_exit"/SYS_exit.
    local SYSCALL_NAME_OVERRIDE = { ["_exit"] = "exit" }
    local TWO_ARG_MACRO = {
        ASM = "PSEUDO", ASM_NOERR = "PSEUDO_NOERROR",
        PSEUDO = "PSEUDO", PSEUDO_NOERR = "PSEUDO_NOERROR",
        HIDDEN = "PSEUDO_HIDDEN",
    }
    local generated = {}
    for class, names in pairs(lists) do
        for _, name in ipairs(names) do
            local stub_path = path.join(gendir, name .. ".S")
            local underlying = SYSCALL_NAME_OVERRIDE[name]
            local body
            if underlying then
                body = string.format("%s(%s,%s)\n", TWO_ARG_MACRO[class], name, underlying)
            else
                body = string.format("%s(%s)\n", SYSCALL_CLASS_MACRO[class], name)
            end
            write_file(stub_path, '#include "SYS.h"\n' .. body)
            generated[#generated + 1] = stub_path
        end
    end
    if #generated == 0 then
        wprint("eteleos: parsed libc/sys/Makefile.inc but found zero syscall names "
               .. "in ASM/ASM_NOERR/PSEUDO/PSEUDO_NOERR/HIDDEN -- check the file's "
               .. "shape hasn't changed upstream")
    end
    return generated
end

-- Define a BSD-style library as a pair of targets: "<name>-static" (kind
-- "static") and "<name>-shared" (kind "shared"), both named libNAME on disk.
--   name:     library name without the "lib" prefix, e.g. "c" for libc
--   srcdir_rel: source directory, relative to this file (e.g. "core/libc")
--   opts:     { deps, defines, extra_includedirs, extra_srcdirs, extra_files,
--               arch_files, gen_files_fn }
--     extra_srcdirs: additional dirs (relative to this file, NOT to srcdir --
--       e.g. a sibling extra/ library, or kernel/net) to ALSO recursively
--       glob **.c from, for libraries whose real Makefile pulls sources
--       from outside their own directory via .PATH.
--     extra_files: absolute file paths to add as-is (for one-off cases not
--       worth a whole extra_srcdirs glob).
--     arch_files: { [arch] = "relative/file.c" } -- exactly one extra,
--       arch-specific file to add (e.g. libkvm's kvm_<arch>.c).
--     gen_files_fn: function(target_gendir) -> {list of generated file
--       paths}, called from on_load so generated sources are still added
--       to this same build's file list (matching this project's existing
--       generated-sources convention -- see kernel/xmake.lua's vers.c).
local function eteleos_bsd_library(name, srcdir_rel, opts)
    opts = opts or {}
    local srcdir = path.join(os.scriptdir(), srcdir_rel)

    if not os.isdir(srcdir) then
        wprint("eteleos: libraries/%s not found, skipping lib%s", srcdir_rel, name)
        return
    end

    local arch = get_config("target_arch") or "amd64"
    local mi_files, md_files = collect_sources(srcdir, arch)

    for _, extra_dir in ipairs(opts.extra_srcdirs or {}) do
        local d = path.join(os.scriptdir(), extra_dir)
        if os.isdir(d) then
            for _, f in ipairs(os.files(path.join(d, "**.c"))) do
                mi_files[#mi_files + 1] = f
            end
        else
            wprint("eteleos: lib%s: extra_srcdirs entry not found, skipping: %s", name, extra_dir)
        end
    end

    for _, f in ipairs(opts.extra_files or {}) do
        if os.isfile(f) then mi_files[#mi_files + 1] = f
        else wprint("eteleos: lib%s: extra_files entry not found, skipping: %s", name, f) end
    end

    if opts.arch_files and opts.arch_files[arch] then
        local f = path.join(srcdir, opts.arch_files[arch])
        if os.isfile(f) then mi_files[#mi_files + 1] = f
        else wprint("eteleos: lib%s: arch_files[%s] not found, skipping: %s", name, arch, f) end
    end

    if #mi_files == 0 and #md_files == 0 then
        wprint("eteleos: lib%s (%s) has no source files for arch '%s' yet, skipping",
               name, srcdir_rel, arch)
        return
    end

    local major, minor = read_shlib_version(srcdir)

    for _, kind in ipairs({"static", "shared"}) do
        target("lib" .. name .. "-" .. kind)
            set_kind(kind)
            set_basename("lib" .. name)
            set_default(false)   -- built explicitly by userland/kernel deps, not by a plain `xmake`

            add_rules("eteleos.base", "eteleos.library")

            if #mi_files > 0 then add_files(unpack(mi_files)) end
            if #md_files > 0 then add_files(unpack(md_files)) end

            add_includedirs(srcdir)
            add_includedirs(path.join(srcdir, "arch", arch))

            if opts.extra_includedirs then
                for _, d in ipairs(opts.extra_includedirs) do
                    add_includedirs(path.join(os.scriptdir(), d))
                end
            end

            if opts.defines then add_defines(unpack(opts.defines)) end

            -- Every EteleOS library builds against the exported headers.
            add_deps("eteleos-headers")
            if opts.deps then add_deps(unpack(opts.deps)) end

            -- Soname/version, shared build only.
            if kind == "shared" and (major > 0 or minor > 0) then
                set_version(string.format("%d.%d", major, minor))
            end

            if opts.gen_files_fn then
                on_load(function (target)
                    local gendir = path.join(config.builddir() or "build",
                                              "eteleos-libraries-gen", "lib" .. name, arch)
                    local files = opts.gen_files_fn(gendir)
                    for _, f in ipairs(files) do target:add("files", f) end
                    if #files > 0 then target:add("includedirs", gendir) end
                end)
            end
        target_end()
    end
end

-- ==============================================================================
-- libraries/core -- one entry per library, srcdir verified against the
-- current tree
-- ==============================================================================

-- libc: the C standard library. Syscall stubs (open.S, read.S, ...) are now
-- generated from libc/sys/Makefile.inc's own ASM/ASM_NOERR/PSEUDO/
-- PSEUDO_NOERR/HIDDEN lists -- see generate_syscall_stubs() above.
eteleos_bsd_library("c", "core/libc", {
    defines = {"__LIBC__"},
    -- DEFS.h (needed by the generated syscall stubs' "#include SYS.h",
    -- which itself does "#include DEFS.h") lives at core/libc/arch/DEFS.h,
    -- one level up from arch/<arch>/ -- confirmed necessary by testing.
    extra_includedirs = {"core/libc/arch"},
    gen_files_fn = function (gendir)
        local arch = get_config("target_arch") or "amd64"
        -- DEFS.h itself does "#include <machine/asm.h>" -- confirmed
        -- necessary by testing. kernel/arch/<arch>/include is the same
        -- real "machine" headers directory the kernel and (per
        -- include/xmake.lua's own "eteleos-headers" relink() logic) the
        -- installed userland headers both resolve <machine/...> against;
        -- materialized here as a real directory copy (not a symlink, same
        -- Windows-host-portability reasoning as kernel/xmake.lua) directly
        -- inside gendir, so the single includedirs(gendir) the generic
        -- helper already adds covers both the generated .S stubs AND this.
        local kernel_arch_include = path.join(os.scriptdir(), "..", "kernel", "arch", arch, "include")
        local machine_dir = path.join(gendir, "machine")
        if not os.isdir(machine_dir) and os.isdir(kernel_arch_include) then
            os.cp(kernel_arch_include, machine_dir)
        end
        return generate_syscall_stubs(path.join(os.scriptdir(), "core/libc"), gendir)
    end,
})

-- libm: math library. Portable C sources live under libm/src/, which the
-- recursive glob below picks up automatically.
eteleos_bsd_library("m", "core/libm")

-- libcrypto: OpenSSL's libcrypto, vendored. arch/ here covers many more
-- architectures than EteleOS supports (alpha, hppa, i386, m88k, ...); the
-- MD-override logic above only looks at arch/<target_arch>, so unrelated
-- architectures are never compiled in.
eteleos_bsd_library("crypto", "core/libcrypto")

-- libssl: TLS/SSL protocol implementation, layered on libcrypto.
eteleos_bsd_library("ssl", "core/libssl", {
    deps = {"libcrypto-shared"},
})

-- libtls: the higher-level libtls API, layered on libssl + libcrypto.
eteleos_bsd_library("tls", "core/libtls", {
    deps = {"libssl-shared", "libcrypto-shared"},
})

-- libpthread: expected to have ZERO source files on the current tree (only
-- a man/ directory) -- modern OpenBSD keeps libpthread as a thin
-- compatibility shim while the real implementation lives in librthread
-- (libraries/extra/librthread). eteleos_bsd_library() will simply skip it
-- with a warning until/unless real shim sources are added here; this is
-- expected, not a bug.
eteleos_bsd_library("pthread", "core/libpthread", {
    deps = {"librthread-shared"},
})

-- libutil: assorted system utility routines (bcrypt_pbkdf, fmt_scaled,
-- imsg, ...). Flat source layout, no arch/ overrides.
eteleos_bsd_library("util", "core/libutil")

-- libz: zlib, vendored.
eteleos_bsd_library("z", "core/libz")

-- libedit: line-editing library used by ksh, ftp, etc.
eteleos_bsd_library("edit", "core/libedit")

-- libelf: ELF object file access library.
eteleos_bsd_library("elf", "core/libelf")

-- libevent: event-notification library.
eteleos_bsd_library("event", "core/libevent")

-- libexpat: XML parser, vendored (sources under libexpat/lib/).
eteleos_bsd_library("expat", "core/libexpat")

-- ==============================================================================
-- libraries/extra -- librthread (already wired) plus the 19 libraries this
-- revision adds. Most are plain eteleos_bsd_library() calls; a few needed
-- real per-library handling, called out below.
-- ==============================================================================

-- librthread: the real pthread implementation (libpthread above is a thin
-- shim over this).
eteleos_bsd_library("rthread", "extra/librthread")

-- libagentx: SNMP AgentX protocol library. Plain flat source layout.
eteleos_bsd_library("agentx", "extra/libagentx")

-- libcbor: CBOR (RFC 8949) encoding library, vendored (needed by libfido2
-- below). Sources are nested under src/ and src/cbor/{,internal}/, all
-- picked up by the recursive glob; needs its own -I for "cbor/*.h"-style
-- internal includes plus the 3 malloc/realloc/free macro substitutions its
-- own Makefile always passes.
eteleos_bsd_library("cbor", "extra/libcbor", {
    extra_includedirs = {"extra/libcbor/src"},
    defines = {"HAVE_ENDIAN_H", "_cbor_malloc=malloc", "_cbor_realloc=realloc", "_cbor_free=free"},
})

-- libcurses: terminal-handling library (the base for libform/libmenu/
-- libpanel below). Sources nested under base/, tinfo/, trace/, tty/,
-- widechar/ -- all picked up by the recursive glob.
eteleos_bsd_library("curses", "extra/libcurses", {
    defines = {"_XOPEN_SOURCE_EXTENDED", "NDEBUG"},
})

-- libform, libmenu, libpanel: the 3 libcurses companion libraries, each
-- needing libcurses' own headers on their include path.
eteleos_bsd_library("form", "extra/libform", {
    extra_includedirs = {"extra/libcurses", "extra/libmenu"},
    defines = {"_XOPEN_SOURCE_EXTENDED", "NDEBUG"},
})
eteleos_bsd_library("menu", "extra/libmenu", {
    extra_includedirs = {"extra/libcurses"},
    defines = {"_XOPEN_SOURCE_EXTENDED", "NDEBUG"},
})
eteleos_bsd_library("panel", "extra/libpanel", {
    extra_includedirs = {"extra/libcurses"},
    defines = {"_XOPEN_SOURCE_EXTENDED", "NDEBUG"},
})

-- libfido2: FIDO2/U2F security-key library, layered on libcbor above.
eteleos_bsd_library("fido2", "extra/libfido2", {
    deps = {"libcbor-shared"},
    extra_includedirs = {"extra/libfido2/src"},
    defines = {"_FIDO_INTERNAL", "HAVE_UNISTD_H"},
})

-- libfuse: userspace filesystem library.
eteleos_bsd_library("fuse", "extra/libfuse", {
    extra_includedirs = {"extra/libfuse"},
})

-- libkeynote: trust-management library. Built NOPIC upstream (no shared
-- variant would normally be produced); this file still builds both
-- static/shared for consistency with every other library here, since a
-- shared build is not actually unsafe, just unnecessary upstream.
eteleos_bsd_library("keynote", "extra/libkeynote", {
    extra_includedirs = {"extra/libkeynote"},
})

-- libkvm: kernel-memory-access library. Real Makefile picks exactly one
-- machine-specific file (kvm_<arch>.c) -- verified present for all three
-- supported architectures (kvm_amd64.c, kvm_arm64.c, kvm_riscv64.c).
eteleos_bsd_library("kvm", "extra/libkvm", {
    defines = {"_LIBKVM"},
    arch_files = { amd64 = "kvm_amd64.c", arm64 = "kvm_arm64.c", riscv64 = "kvm_riscv64.c" },
})

-- libl: tiny lex/flex runtime support (libmain.c/libyywrap.c), needed by
-- programs built from plain lex output. NOPIC upstream (same reasoning as
-- libkeynote above). Its own directory has no sources at all -- the real
-- files live in userland/development/lex/ (confirmed on disk), pulled in
-- via the real Makefile's own .PATH.
eteleos_bsd_library("l", "extra/libl", {
    extra_srcdirs = {"../userland/development/lex"},
})

-- libossaudio: OSS audio-API compatibility shim, layered on libsndio's
-- sources (its real Makefile pulls them in via .PATH rather than linking
-- against libsndio itself).
eteleos_bsd_library("ossaudio", "extra/libossaudio", {
    extra_srcdirs = {"extra/libsndio"},
})

-- libpcap: packet-capture library. NOT handled through
-- eteleos_bsd_library() -- its real Makefile needs yacc/lex with a custom
-- symbol prefix (-ppcap_yy/-Ppcap_yy, so multiple libraries' generated
-- lexer/parser symbols don't collide at link time) and pulls
-- bpf_filter.c from kernel/net/net/ (verified present there) via .PATH,
-- neither of which the generic helper's opts support. Handled as its own
-- pair of targets below, reusing the same yacc/lex-with-prefix pattern
-- userland/xmake.lua already established for other programs.
do
    local pcap_srcdir = path.join(os.scriptdir(), "extra", "libpcap")
    if os.isdir(pcap_srcdir) then
        local arch = get_config("target_arch") or "amd64"
        for _, kind in ipairs({"static", "shared"}) do
            target("libpcap-" .. kind)
                set_kind(kind)
                set_basename("libpcap")
                set_default(false)
                add_rules("eteleos.base", "eteleos.library")

                local mi_files = select(1, collect_sources(pcap_srcdir, arch))
                if #mi_files > 0 then add_files(unpack(mi_files)) end
                local bpf_filter_c = path.join(os.scriptdir(), "..", "kernel", "net", "net", "bpf_filter.c")
                if os.isfile(bpf_filter_c) then add_files(bpf_filter_c)
                else wprint("eteleos: libpcap: kernel/net/net/bpf_filter.c not found, skipping") end

                add_includedirs(pcap_srcdir)
                add_defines("HAVE_SYS_IOCCOM_H", "HAVE_SYS_SOCKIO_H", "HAVE_ETHER_HOSTTON",
                            "yylval=pcap_yylval")
                add_deps("eteleos-headers")

                on_load(function (target)
                    import("lib.detect.find_tool")
                    local yacc = find_tool("bison") or find_tool("yacc")
                    local lex  = find_tool("flex") or find_tool("lex")
                    if not yacc or not lex then
                        wprint("eteleos: libpcap: no yacc/bison or lex/flex found -- "
                               .. "grammar.y/scanner.l will not be compiled, libpcap "
                               .. "will be missing its filter-expression parser")
                        return
                    end
                    local gendir = path.join(config.builddir() or "build",
                                              "eteleos-libraries-gen", "libpcap", arch)
                    os.mkdir(gendir)
                    local gram_c = path.join(gendir, "grammar.c")
                    local gram_h = path.join(gendir, "grammar.h")
                    if os.isfile(gram_c) then
                        target:add("files", gram_c)
                    elseif os.execv(yacc.program, {"-p", "pcap_yy", "-d", "-o", gram_c,
                                path.join(pcap_srcdir, "grammar.y")}, {try = true}) then
                        target:add("files", gram_c)
                    else
                        wprint("eteleos: libpcap: yacc/bison failed on grammar.y")
                    end
                    local scan_c = path.join(gendir, "scanner.c")
                    if os.isfile(scan_c) then
                        target:add("files", scan_c)
                    elseif os.execv(lex.program, {"-P", "pcap_yy", "-o", scan_c,
                                path.join(pcap_srcdir, "scanner.l")}, {try = true}) then
                        target:add("files", scan_c)
                    else
                        wprint("eteleos: libpcap: lex/flex failed on scanner.l")
                    end
                    target:add("includedirs", gendir)
                end)
            target_end()
        end
    else
        wprint("eteleos: libraries/extra/libpcap not found, skipping libpcap")
    end
end

-- libradius: RADIUS protocol client library.
eteleos_bsd_library("radius", "extra/libradius")

-- librpcsvc: NOT handled through eteleos_bsd_library() -- every single
-- source file is rpcgen-generated from a .x RPC protocol spec (confirmed:
-- the real Makefile's SRCS is entirely `${RPCSRCS:R:S/$/.c/g}`, i.e.
-- "take every .x name, swap the extension for .c" -- there are no
-- hand-written .c files here at all). Each spec generates exactly one .c
-- (rpcgen -c, XDR marshaling routines only -- this library never needed
-- generated client/server stubs, only the wire-format encoding).
do
    local rpcsvc_srcdir = path.join(os.scriptdir(), "extra", "librpcsvc")
    local RPCSVC_SPECS = { "bootparam_prot", "klm_prot", "mount", "nfs_prot",
                            "nlm_prot", "rnusers", "rquota", "rstat", "rusers", "rwall" }
    if os.isdir(rpcsvc_srcdir) then
        for _, kind in ipairs({"static", "shared"}) do
            target("librpcsvc-" .. kind)
                set_kind(kind)
                set_basename("librpcsvc")
                set_default(false)
                add_rules("eteleos.base", "eteleos.library")
                add_includedirs(rpcsvc_srcdir)
                add_deps("eteleos-headers")

                on_load(function (target)
                    import("lib.detect.find_tool")
                    local rpcgen = find_tool("rpcgen")
                    if not rpcgen then
                        wprint("eteleos: librpcsvc: rpcgen not found on host -- none of "
                               .. "the %d RPC spec(s) can be compiled, librpcsvc will "
                               .. "be an empty library", #RPCSVC_SPECS)
                        return
                    end
                    local gendir = path.join(config.builddir() or "build",
                                              "eteleos-libraries-gen", "librpcsvc")
                    os.mkdir(gendir)
                    local n = 0
                    for _, spec in ipairs(RPCSVC_SPECS) do
                        local x_file = path.join(rpcsvc_srcdir, spec .. ".x")
                        local c_file = path.join(gendir, spec .. ".c")
                        if os.isfile(c_file) then
                            -- Already generated (by this same run's static
                            -- target, or a previous invocation) -- rpcgen
                            -- prompts interactively on overwrite, which
                            -- hangs/fails non-interactively, so skip rather
                            -- than re-run (confirmed necessary by testing).
                            target:add("files", c_file)
                            n = n + 1
                        elseif os.isfile(x_file) then
                            if os.execv(rpcgen.program, {"-c", x_file, "-o", c_file}, {try = true}) then
                                target:add("files", c_file)
                                n = n + 1
                            else
                                wprint("eteleos: librpcsvc: rpcgen failed on %s.x", spec)
                            end
                        else
                            wprint("eteleos: librpcsvc: %s.x not found, skipping", spec)
                        end
                    end
                    target:add("includedirs", gendir)
                    cprint("${green}eteleos${clear}: librpcsvc: %d/%d RPC specs compiled",
                           n, #RPCSVC_SPECS)
                end)
            target_end()
        end
    else
        wprint("eteleos: libraries/extra/librpcsvc not found, skipping librpcsvc")
    end
end

-- libskey: S/Key one-time-password library.
eteleos_bsd_library("skey", "extra/libskey")

-- libsndio: sndio audio API. Also the source of libossaudio's sources
-- above (via extra_srcdirs), but built here as its own library too, since
-- libsndio is a normal, independently-linkable library in its own right.
eteleos_bsd_library("sndio", "extra/libsndio", {
    defines = {"DEBUG"},
})

-- libusbhid: USB HID report descriptor parsing library.
eteleos_bsd_library("usbhid", "extra/libusbhid", {
    extra_includedirs = {"extra/libusbhid"},
})

-- liby: tiny yacc/bison runtime support (main.c/yyerror.c), needed by
-- programs built from plain yacc output. NOPIC upstream (same reasoning as
-- libkeynote/libl above).
eteleos_bsd_library("y", "extra/liby")

-- ==============================================================================
-- Not yet wired up (out of scope for this revision -- see the readiness
-- notes this file's history is based on):
--   csu (C runtime startup objects: crt0.o, crtbegin.o, ...) and libarch
--   are NOT ordinary libNAME.a/.so libraries -- csu produces a handful of
--   standalone .o files linked directly into every executable rather than
--   an archive, and needs its own target shape; libarch is architecture
--   support code consumed directly by libc's own build, not a
--   separately-linked library. Both are real, additional gaps found while
--   auditing this file -- worth a dedicated pass, not folded into this one.
-- ==============================================================================
