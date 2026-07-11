/*
 EteleOS: xmake.lua, time wirte: 2026/07/11
 This file uses the Apache-2.0 license
*/

--[[
================================================================================
 EteleOS :: libraries/xmake.lua
================================================================================

Manages the whole libraries/ tree: libc, libm, libcrypto, libssl, libpthread,
librthread, libutil, libtls, libz, libedit, libelf, libevent, libexpat (all of
libraries/core/), following the current source layout (verified against
github.com/EteleOS/EteleOS, NOT the stale per-library Makefiles, which still
reference pre-restructure paths like ../include or ../gnu).

Every library is built as a PAIR of targets -- "<name>-static" and
"<name>-shared" -- via the eteleos_bsd_library() helper below. This file does
not compile object/kernel/userland/driver/xenocara code; it only builds the
libraries/ tree, per the build spec.

libraries/extra/ (librthread plus 19 other libraries) is intentionally NOT
wired up yet -- see the note at the bottom of this file.
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

-- Define a BSD-style library as a pair of targets: "<name>-static" (kind
-- "static") and "<name>-shared" (kind "shared"), both named libNAME on disk.
--   name:     library name without the "lib" prefix, e.g. "c" for libc
--   srcdir_rel: source directory, relative to this file (e.g. "core/libc")
--   opts:     { deps = {...}, defines = {...}, extra_includedirs = {...} }
local function eteleos_bsd_library(name, srcdir_rel, opts)
    opts = opts or {}
    local srcdir = path.join(os.scriptdir(), srcdir_rel)

    if not os.isdir(srcdir) then
        wprint("eteleos: libraries/%s not found, skipping lib%s", srcdir_rel, name)
        return
    end

    local arch = get_config("target_arch") or "amd64"
    local mi_files, md_files = collect_sources(srcdir, arch)

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
                    add_includedirs(path.join(srcdir, d))
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
        target_end()
    end
end

-- ==============================================================================
-- libraries/core -- one entry per library, srcdir verified against the
-- current tree
-- ==============================================================================

-- libc: the C standard library. NOTE -- known gap: OpenBSD generates each
-- syscall's userland stub (open.S, read.S, write.S, ...) from
-- kernel/core/kern/syscalls.master via a script; that generation step is
-- NOT wired up here yet (only the one hand-written libc/sys/canceled.c is
-- picked up by the generic glob below). Until that pipeline exists, this
-- target will build but the resulting libc will be missing its syscall
-- entry points.
eteleos_bsd_library("c", "core/libc", {
    defines = {"__LIBC__"},
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

-- librthread lives under libraries/extra/, but libpthread above depends on
-- it, so it is wired up here rather than left silently broken. The rest of
-- libraries/extra/ (19 more libraries) is intentionally deferred -- see the
-- note below.
eteleos_bsd_library("rthread", "extra/librthread")

-- ==============================================================================
-- Deferred: libraries/extra/
-- ==============================================================================
-- libagentx, libcbor, libcurses, libfido2, libform, libfuse, libkeynote,
-- libkvm, libl, libmenu, libossaudio, libpanel, libpcap, libradius,
-- librpcsvc, libskey, libsndio, libusbhid, liby are not wired up yet. They
-- can reuse eteleos_bsd_library() exactly as above once their build order
-- relative to userland/xenocara is decided -- ask for these explicitly when
-- ready.
