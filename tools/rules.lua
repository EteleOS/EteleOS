--[[
================================================================================
 EteleOS: tools/rules.lua, time write: 2026/07/10
 This file uses the Apache-2.0 license
================================================================================

Project-wide rule() declarations for EteleOS.
Loaded by tools/xmake.lua (after compiler.lua).

rule() declarations are project-global in xmake: once declared here, any
module can opt in with add_rules("eteleos.*").

Rule catalogue
--------------
  eteleos.base          Common flags for every EteleOS target (hosted or not).
                        Every target in every module should add this rule.

  eteleos.kernel        Freestanding flags for the kernel. Builds that add
                        this rule MUST also add eteleos.base first.

  eteleos.userland      Hardening flags for userland executables.
  eteleos.userland_static Static-link variant, for /bin and /sbin.

  eteleos.library       Flags for shared/static libraries.

  eteleos.asm           Preprocessed assembler (.S) support.

  eteleos.strip_release Strip all symbols in release/minsizerel mode.

  eteleos.lto           Explicit per-target LTO (for modules that do not rely
                        on the global policy set in compiler.lua).

  eteleos.asan          AddressSanitizer for hosted targets.

  eteleos.ubsan         UndefinedBehaviorSanitizer for hosted targets.

Nothing in this file compiles any source file or declares any target.
--------------------------------------------------------------------------------
--]]

-- ==============================================================================
-- eteleos.base
-- ==============================================================================
-- Common flags that apply to every EteleOS target (hosted or freestanding).
-- Think of this as EteleOS's global "baseline" build configuration.
-- Usage (in any module's xmake.lua):
--   target("foo")
--       add_rules("eteleos.base")
-- ==============================================================================
rule("eteleos.base")
    on_load(function (target)
        -- --- Preprocessor -------------------------------------------------------
        -- __EteleOS__ identifies EteleOS-specific code paths.
        -- __OpenBSD__ is NOT added here: clang/gcc predefine it automatically
        -- when the target triple ends in "-openbsd" (see toolchains.lua).
        target:add("defines", "__EteleOS__")

        -- --- Warning flags -------------------------------------------------------
        -- Equivalent to -Wall -Wextra. Specific modules can tune this locally
        -- by adding more warning flags or by using add_cxflags({"-Wno-..."}).
        target:add("cxflags",
            "-Wall",
            "-Wextra",
            "-Wno-unused-parameter",    -- too noisy across ported BSD code
            "-Wno-sign-compare",        -- widespread in OpenBSD-derived code
            {force = true})

        -- Treat warnings as errors when --werror is active.
        if has_config("werror") then
            target:add("cxflags", "-Werror", {force = true})
        end

        -- --- Architecture-specific flags ----------------------------------------
        -- These come from tools/modules/eteleos/helpers.lua (NOT the plain
        -- global of the same name in tools/helpers.lua -- confirmed by
        -- testing that a description-scope global, even one defined in
        -- this exact project, is invisible from on_load; see that
        -- module's header for the full explanation).
        import("eteleos.helpers")
        local arch_flags = helpers.eteleos_get_arch_cflags()
        if #arch_flags > 0 then
            helpers.eteleos_add_flags(target, "cxflags", arch_flags)
            helpers.eteleos_add_flags(target, "asflags", arch_flags)
        end

        -- --- Cross-build sysroot ------------------------------------------------
        local sysroot = get_config("sysroot")
        if sysroot and sysroot ~= "" then
            target:add("cxflags",  "--sysroot=" .. sysroot, {force = true})
            target:add("asflags",  "--sysroot=" .. sysroot, {force = true})
            target:add("ldflags",  "--sysroot=" .. sysroot, {force = true})
        end

        -- --- Verbose build flag -------------------------------------------------
        if has_config("verbose_build") then
            target:add("cxflags", "-v", {force = true})
            target:add("ldflags", "-v", {force = true})
        end

        -- --- Reproducible builds ------------------------------------------------
        -- These eliminate timestamps and host paths from object files so the
        -- same source always produces the same binary.
        target:add("cxflags",
            "-fmacro-prefix-map=$(projectdir)/=./",
            {force = true})
    end)
rule_end()

-- ==============================================================================
-- eteleos.kernel
-- ==============================================================================
-- Freestanding flags for the kernel. MUST be combined with eteleos.base.
-- Explicitly blocks sanitizers (which require a hosted runtime library).
-- Usage (in kernel/xmake.lua):
--   target("eteleos-kernel")
--       add_rules("eteleos.base", "eteleos.kernel")
-- ==============================================================================
rule("eteleos.kernel")
    on_load(function (target)
        -- Freestanding environment: no libc, no hosted ABI assumptions.
        target:add("cxflags",
            "-ffreestanding",
            "-fno-builtin",
            "-fno-stack-protector",     -- kernel manages its own stack
            "-fno-pic",
            "-fno-pie",
            "-fno-common",
            "-fno-asynchronous-unwind-tables",   -- saves size; kernel handles own unwind
            {force = true})

        -- Assembler: enable CPP so .S files can use #include / #define.
        target:add("asflags",
            "-D__ASSEMBLER__",
            "-x", "assembler-with-cpp",
            {force = true})

        -- Linker: no default libs; link with a custom linker script supplied
        -- by kernel/xmake.lua via add_ldflags("-T", "kernel/arch/amd64/ld.script").
        target:add("ldflags",
            "-nostdlib",
            "-static",
            {force = true})

        -- Block sanitizers unconditionally on freestanding targets.
        -- They require a hosted runtime (libasan / libubsan) that does not
        -- exist in a freestanding environment.
        target:add("cxflags",
            "-fno-sanitize=all",
            {force = true})
    end)
rule_end()

-- ==============================================================================
-- eteleos.userland
-- ==============================================================================
-- Security hardening flags for EteleOS userland executables.
-- MUST be combined with eteleos.base.
-- Usage:
--   target("sh")
--       add_rules("eteleos.base", "eteleos.userland")
-- ==============================================================================
rule("eteleos.userland")
    on_load(function (target)
        -- Position-independent executable.
        target:add("cxflags",  "-fpie",  {force = true})
        target:add("ldflags",  "-pie",   {force = true})

        -- Stack protector: use the "strong" variant (gcc >= 4.9 / clang >= 3.5).
        target:add("cxflags",  "-fstack-protector-strong", {force = true})

        -- RELRO + BIND_NOW: make the PLT/GOT read-only after start-up.
        target:add("ldflags",
            "-Wl,-z,relro",
            "-Wl,-z,now",
            {force = true})

        -- No executable stack.
        target:add("ldflags", "-Wl,-z,noexecstack", {force = true})
    end)
rule_end()

-- ==============================================================================
-- eteleos.userland_static
-- ==============================================================================
-- Same hardening as eteleos.userland, for the long-standing BSD convention
-- that /bin and /sbin link statically so they still work if /usr (and
-- whatever shared libraries live there) isn't mounted yet during early
-- boot/single-user recovery. Not combined with -fpie/-pie: a static PIE
-- executable is a real but much less common mode (-static-pie) with its
-- own runtime-relocation requirements, and isn't what "so it works before
-- /usr is mounted" is actually asking for here.
-- MUST be combined with eteleos.base.
-- Usage:
--   target("mount")
--       add_rules("eteleos.base", "eteleos.userland_static")
-- ==============================================================================
rule("eteleos.userland_static")
    on_load(function (target)
        target:add("ldflags", "-static", {force = true})
        target:add("cxflags", "-fstack-protector-strong", {force = true})
        target:add("ldflags", "-Wl,-z,noexecstack", {force = true})
    end)
rule_end()

-- ==============================================================================
-- eteleos.library
-- ==============================================================================
-- Flags for shared libraries (and static libraries intended for later dynamic
-- linking). MUST be combined with eteleos.base.
-- Usage:
--   target("libcrypto")
--       add_rules("eteleos.base", "eteleos.library")
-- ==============================================================================
rule("eteleos.library")
    on_load(function (target)
        -- Position-independent code.
        target:add("cxflags", "-fpic", {force = true})
        -- No executable stack in shared libraries either.
        target:add("ldflags", "-Wl,-z,noexecstack", {force = true})
    end)
rule_end()

-- ==============================================================================
-- eteleos.asm
-- ==============================================================================
-- Support rule for pure-assembly source modules (.S / .s).
-- Can be combined with eteleos.base or eteleos.kernel as needed.
-- Usage:
--   target("boot")
--       add_rules("eteleos.base", "eteleos.kernel", "eteleos.asm")
-- ==============================================================================
rule("eteleos.asm")
    on_load(function (target)
        target:add("asflags",
            "-D__ASSEMBLER__",
            "-x", "assembler-with-cpp",
            {force = true})
    end)
rule_end()

-- ==============================================================================
-- eteleos.strip_release
-- ==============================================================================
-- Strip all debug symbols from the installed binary in release / minsizerel
-- modes. Optional: only add this rule to targets where stripping is desired.
-- Usage:
--   target("sh")
--       add_rules("eteleos.base", "eteleos.userland", "eteleos.strip_release")
-- ==============================================================================
rule("eteleos.strip_release")
    on_load(function (target)
        if is_mode("release") or is_mode("minsizerel") then
            target:set("strip", "all")
        end
    end)
rule_end()

-- ==============================================================================
-- eteleos.lto
-- ==============================================================================
-- Explicit per-target LTO, for modules that prefer to opt in target-by-target
-- rather than rely on the global policy set in compiler.lua.
-- Usage:
--   target("libssl")
--       add_rules("eteleos.base", "eteleos.library", "eteleos.lto")
-- ==============================================================================
rule("eteleos.lto")
    on_load(function (target)
        -- Raw -flto flag, not the xmake policy; this ensures the flag appears
        -- whether or not set_policy("build.optimization.lto") is active.
        target:add("cxflags", "-flto=thin", {force = true})
        target:add("ldflags", "-flto=thin", {force = true})
    end)
rule_end()

-- ==============================================================================
-- eteleos.asan
-- ==============================================================================
-- AddressSanitizer for hosted targets (userland tools, tests).
-- NEVER add this rule to the kernel or any freestanding target.
-- Usage:
--   target("my-tool")
--       add_rules("eteleos.base", "eteleos.userland", "eteleos.asan")
-- ==============================================================================
rule("eteleos.asan")
    on_load(function (target)
        if has_config("asan") then
            target:add("cxflags", "-fsanitize=address", {force = true})
            target:add("ldflags", "-fsanitize=address", {force = true})
        end
    end)
rule_end()

-- ==============================================================================
-- eteleos.ubsan
-- ==============================================================================
-- UndefinedBehaviorSanitizer for hosted targets.
-- NEVER add this rule to the kernel or any freestanding target.
-- Usage:
--   target("my-tool")
--       add_rules("eteleos.base", "eteleos.userland", "eteleos.ubsan")
-- ==============================================================================
rule("eteleos.ubsan")
    on_load(function (target)
        if has_config("ubsan") then
            target:add("cxflags", "-fsanitize=undefined", {force = true})
            target:add("ldflags", "-fsanitize=undefined", {force = true})
        end
    end)
rule_end()
