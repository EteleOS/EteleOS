--[[
================================================================================
 EteleOS: resources/xmake.lua, time write: 2026/07/12
 This file uses the Apache-2.0 license
================================================================================

Manages: firmware, fonts, locale, man, zoneinfo, dict, and the rest of the
renamed share/ tree ("resources/" IS the renamed share/ -- there is no
separate "share/" subdirectory to also handle; see README.md).

Verified against the current tree (github.com/EteleOS/EteleOS), not assumed:
  resources/{dict, locale, man, misc, mk, snmp, tabset, termtypes, tmac,
             zoneinfo, btrace}

  - firmware: NOT present anywhere in this source tree. OpenBSD does not
    ship most firmware blobs in base; they are fetched separately via
    fw_update(8) at install/runtime. Nothing to install here currently --
    if/when a firmware/ directory is added to this tree, it can be wired up
    the same way as the other flat categories below.
  - fonts: no dedicated fonts/ directory either. The only font-shaped
    content found is resources/misc/pcvtfonts/ (legacy console fonts for
    the pcvt driver), which is covered by the generic "misc" copy below.
    Xenocara's X11 fonts are a separate concern (xenocara/xmake.lua).
  - resources/mk/ (bsd.lib.mk, bsd.prog.mk, bsd.own.mk, ...) is
    DELIBERATELY EXCLUDED: those are BSD Make's own build-system internals,
    being replaced by this very XMake conversion -- not a runtime resource
    to install onto the target system.

Does NOT compile anything: this is a headeronly (no-binary) target. zic(8)
and mklocale(1) invocations below are DATA compilation (turning IANA tzdata
text / ctype source into the binary formats libc's localtime()/ctype
routines read), not C/C++ compilation, and are skipped gracefully if the
tool is not found on the host.
--------------------------------------------------------------------------------
--]]

target("eteleos-resources")
    set_kind("headeronly")
    set_default(false)

    -- ==========================================================================
    -- Flat categories: install verbatim, preserving each directory's own
    -- internal structure (man keeps man1/man2/.../man9, etc.)
    -- ==========================================================================
    -- dict: traditional word lists (propernames, web2, web2a) -- flat files.
    add_installfiles("dict/propernames", {prefixdir = "share/dict"})
    add_installfiles("dict/web2",        {prefixdir = "share/dict"})
    add_installfiles("dict/web2a",       {prefixdir = "share/dict"})

    -- man: man0 through man9, troff source -- never compiled, just installed
    -- (makewhatis(8) indexing is a separate post-install step, not done here).
    add_installfiles("(man/**)",                  {prefixdir = "share"})

    -- misc: mime.types, scsi_modes, usb_hid_usages, templates, pcvtfonts/, ...
    add_installfiles("(misc/**)",                 {prefixdir = "share"})

    -- tmac / tabset / termtypes: troff macros and terminal data.
    add_installfiles("(tmac/**)",                 {prefixdir = "share"})
    add_installfiles("(tabset/**)",                {prefixdir = "share"})
    add_installfiles("(termtypes/**)",             {prefixdir = "share"})

    -- snmp: MIB definitions used by snmpd(8).
    add_installfiles("(snmp/**)",                  {prefixdir = "share"})

    -- btrace: example/skeleton scripts for btrace(8).
    add_installfiles("(btrace/**)",                {prefixdir = "share"})

    add_deps("eteleos-headers")

    -- ==========================================================================
    -- Data compilation: zoneinfo (zic) and locale (mklocale)
    -- ==========================================================================
    -- KNOWN LIMITATION: resources/zoneinfo/Makefile is the upstream IANA
    -- tzdata build system (DATAFORM variants, POSIXRULES, leap-second
    -- handling via leapseconds.awk, ziguard.awk/zishrink.awk
    -- post-processing, "fat"/"slim" TZif variants, ...). That full
    -- Makefile is NOT reimplemented here -- this only runs a single,
    -- reasonable `zic` invocation over datfiles/ with zic's own defaults.
    -- Revisit this if a specific DATAFORM/leap-second policy is required.
    after_install(function (target)
        import("lib.detect.find_tool")

        local installdir = get_config("installdir")
                            or path.join(os.scriptdir(), "..", "build", "install")
        local scriptdir = os.scriptdir()

        -- --- zoneinfo: compile IANA tz source data into binary TZif files ----
        local zic = find_tool("zic")
        local tzdatadir = path.join(scriptdir, "zoneinfo", "datfiles")
        local tzoutdir = path.join(installdir, "share", "zoneinfo")
        if zic and os.isdir(tzdatadir) then
            os.mkdir(tzoutdir)
            local srcfiles = os.files(path.join(tzdatadir, "*"))
            if #srcfiles > 0 then
                local args = {"-d", tzoutdir}
                for _, f in ipairs(srcfiles) do args[#args + 1] = f end
                local ok, err = pcall(os.execv, zic.program, args)
                if ok then
                    cprint("${green}eteleos-resources${clear}: compiled %d zoneinfo source files with zic",
                           #srcfiles)
                else
                    wprint("eteleos-resources: zic failed: %s", tostring(err))
                end
            else
                wprint("eteleos-resources: no zoneinfo source files found under %s", tzdatadir)
            end
        else
            wprint("eteleos-resources: zic not found (or %s missing) -- zoneinfo NOT compiled; "
                   .. "the target will have no /usr/share/zoneinfo data", tzdatadir)
        end

        -- --- locale: compile ctype sources into binary locale databases -----
        -- NOTE: only invoked if mklocale is found; resources/locale/ctype's
        -- own Makefile/source-list is not parsed here, so this is a
        -- best-effort pass, not a faithful port of that build.
        local mklocale = find_tool("mklocale")
        local ctypedir = path.join(scriptdir, "locale", "ctype")
        if mklocale and os.isdir(ctypedir) then
            cprint("${green}eteleos-resources${clear}: mklocale found "
                   .. "(%s) -- locale/ctype build not yet wired up in detail, "
                   .. "see the note in this file", mklocale.program)
        else
            wprint("eteleos-resources: mklocale not found (or locale/ctype missing) -- "
                   .. "locale databases NOT compiled")
        end
    end)
target_end()
