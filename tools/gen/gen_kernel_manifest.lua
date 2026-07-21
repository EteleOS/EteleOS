--[[
================================================================================
 EteleOS: tools/gen/gen_kernel_manifest.lua
 This file uses the Apache-2.0 license
================================================================================

Same reasoning as tools/gen/gen_userland_manifest.lua (see that file's
header for the full explanation of why io.open()/os.execv() cannot run at
xmake.lua description scope, confirmed against a real xmake v3.0.9 build).

kernel/xmake.lua's own "REAL config(8), bootstrapped as a private host
tool" section previously ran this entire pipeline directly at description
scope (a bare `do ... end` block, before target("eteleos-kernel") even
starts) -- which cannot work, for the same reason. The logic itself
(building config(8) from userland/system/config/ with a host compiler,
patching a scratch copy of util.c's sourcepath() for the post-restructure
directory layout, running it against each arch's real GENERIC, and falling
back to an approximate files/GENERIC parser when any of that fails) is
UNCHANGED from the previous revision -- only relocated here, to run via
`xmake lua`, and parameterized by arch (looped over all three) instead of
closing over kernel/xmake.lua's single `arch` local.

Regenerate with: xmake lua tools/gen/gen_kernel_manifest.lua
(or: xmake eteleos-regen-kernel, once a project is configured)

Output: kernel/generated_manifest.lua, containing
ETELEOS_KERNEL_MANIFEST[arch] = { selected_files = {...}, ioconf_c = <string
or nil>, mode = "real-config8" | "approximate" } for each of amd64, arm64,
riscv64.
--------------------------------------------------------------------------------
--]]

local ROOT   = path.absolute(os.scriptdir() .. "/../..")
local KERNEL = path.join(ROOT, "kernel")
local GEN_ROOT = path.join(ROOT, "build", "eteleos-kernel-gen")

local ARCHES = {"amd64", "arm64", "riscv64"}

-- ==============================================================================
-- Small utilities (unchanged)
-- ==============================================================================
local function read_file(filepath)
    if not os.isfile(filepath) then return nil end
    local f = io.open(filepath, "r")
    if not f then return nil end
    local c = f:read("*a")
    f:close()
    return c
end

local function write_file(filepath, content)
    local f = io.open(filepath, "w")
    if not f then
        print(string.format("eteleos-gen-kernel: could not write %s", filepath))
        return false
    end
    f:write(content)
    f:close()
    return true
end

local function strip_comment(line)
    local in_quote = false
    for i = 1, #line do
        local c = line:sub(i, i)
        if c == '"' then in_quote = not in_quote
        elseif c == "#" and not in_quote then
            return line:sub(1, i - 1)
        end
    end
    return line
end

local function extract_base_name(token)
    return (token:gsub("[%d%*]+$", ""))
end

local function newest_mtime(files)
    local newest = 0
    for _, f in ipairs(files) do
        if os.isfile(f) then
            local mt = os.mtime(f)
            if mt and mt > newest then newest = mt end
        end
    end
    return newest
end

-- ==============================================================================
-- REAL config(8), bootstrapped as a private host tool. Arch-independent --
-- built once, reused for all three arches below.
-- ==============================================================================
local function build_host_config_tool()
    import("lib.detect.find_tool")

    local config_srcdir = path.join(ROOT, "userland", "system", "config")
    if not os.isdir(config_srcdir) then
        print("eteleos-gen-kernel: userland/system/config not found -- cannot bootstrap "
              .. "real config(8), falling back to the approximate parser")
        return nil
    end

    local bootstrap_dir = path.join(GEN_ROOT, "host-config-bootstrap")
    os.mkdir(bootstrap_dir)
    local out_bin = path.join(bootstrap_dir, is_host("windows") and "config.exe" or "config")

    local UKC_EXCLUDED = { ["cmd.c"]=true, ["ukc.c"]=true, ["ukcutil.c"]=true, ["exec_elf.c"]=true,
                           ["util.c"]=true }
    local c_srcs = {}
    for _, f in ipairs(os.files(path.join(config_srcdir, "*.c"))) do
        if not UKC_EXCLUDED[path.filename(f)] then c_srcs[#c_srcs + 1] = f end
    end
    local ukc_stub_path = path.join(bootstrap_dir, "ukc_stub.c")
    write_file(ukc_stub_path, [[
/* Stub for tools/gen/gen_kernel_manifest.lua's private config(8) bootstrap:
 * the real ukc() (interactive UKC boot-config editor, normally in ukc.c)
 * needs BSD-only <nlist.h>/<kvm.h> host APIs unrelated to batch-mode
 * ioconf.c generation, which is all this bootstrap tool is ever used for. */
int ukc(char *file, char *outfile, int uflag, int force);
int ukc(char *file, char *outfile, int uflag, int force) {
    (void)file; (void)outfile; (void)uflag; (void)force;
    return (1);
}
]])
    c_srcs[#c_srcs + 1] = ukc_stub_path

    local devfuncs_stub_path = path.join(bootstrap_dir, "devfuncs_stub.c")
    write_file(devfuncs_stub_path, [[
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int major(int dev) { return (dev >> 8) & 0xff; }
int minor(int dev) { return dev & 0xff; }
int makedev(int maj, int min) { return ((maj & 0xff) << 8) | (min & 0xff); }
void errc(int eval, int code, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, ": %s\n", strerror(code));
    exit(eval);
}
]])
    c_srcs[#c_srcs + 1] = devfuncs_stub_path

    local newest_src = newest_mtime(c_srcs)
    newest_src = math.max(newest_src, newest_mtime({
        path.join(config_srcdir, "gram.y"), path.join(config_srcdir, "scan.l"),
    }))
    if os.isfile(out_bin) and os.mtime(out_bin) >= newest_src then
        return out_bin
    end

    local cc = find_tool("clang") or find_tool("cc") or find_tool("gcc")
    if not cc then
        print("eteleos-gen-kernel: no host C compiler (clang/cc/gcc) found -- cannot "
              .. "bootstrap real config(8), falling back to the approximate parser")
        return nil
    end

    local yacc = find_tool("bison") or find_tool("yacc")
    local lex  = find_tool("flex") or find_tool("lex")
    if not yacc or not lex then
        print("eteleos-gen-kernel: no yacc/bison or lex/flex found on host -- cannot "
              .. "bootstrap real config(8), falling back to the approximate parser")
        return nil
    end

    local util_c_src = read_file(path.join(config_srcdir, "util.c"))
    if not util_c_src then
        print("eteleos-gen-kernel: could not read util.c, falling back to the approximate parser")
        return nil
    end
    local old_sourcepath = [[
sourcepath(const char *file)
{
	char *cp;

	if (asprintf(&cp, "%s/%s", srcdir, file) == -1)
		err(1, NULL);

	return cp;
}]]
    local new_sourcepath = [[
sourcepath(const char *file)
{
	char *cp;
	/* eteleos: fall back to a handful of known-relocated prefixes when
	 * the plain srcdir-relative path doesn't exist -- see
	 * tools/gen/gen_kernel_manifest.lua. */
	static const char *eteleos_prefixes[] = { "", "core/", "dev/", "fs/" };
	struct stat eteleos_sb;
	size_t eteleos_i;

	for (eteleos_i = 0; eteleos_i < 4; eteleos_i++) {
		if (asprintf(&cp, "%s/%s%s", srcdir, eteleos_prefixes[eteleos_i], file) == -1)
			err(1, NULL);
		if (stat(cp, &eteleos_sb) == 0)
			return cp;
		free(cp);
	}
	if (asprintf(&cp, "%s/%s", srcdir, file) == -1)
		err(1, NULL);
	return cp;
}]]
    local patched_util_c, n = util_c_src:gsub(old_sourcepath:gsub("%p", "%%%1"), (new_sourcepath:gsub("%%", "%%%%")))
    if n == 0 then
        print("eteleos-gen-kernel: util.c's sourcepath() was not found in the expected "
              .. "shape -- proceeding unpatched; real config(8) may fail to resolve "
              .. "some relocated include paths")
        patched_util_c = util_c_src
    end
    patched_util_c = patched_util_c:gsub('(#include <sys/types%.h>)', "%1\n#include <sys/stat.h>", 1)
    local staged_util_c = path.join(bootstrap_dir, "util.c")
    write_file(staged_util_c, patched_util_c)
    c_srcs[#c_srcs + 1] = staged_util_c

    local gram_c = path.join(bootstrap_dir, "gram.c")
    local gram_h = path.join(bootstrap_dir, "gram.h")
    local yacc_ok = os.execv(yacc.program,
        {"-d", "-o", gram_c, path.join(config_srcdir, "gram.y")}, {curdir = bootstrap_dir, try = true})
    if not yacc_ok or not os.isfile(gram_c) then
        print("eteleos-gen-kernel: yacc/bison failed on gram.y, falling back to the approximate parser")
        return nil
    end
    if not os.isfile(gram_h) then
        local alt = path.join(bootstrap_dir, "y.tab.h")
        if os.isfile(alt) then os.cp(alt, gram_h) end
    end

    local scan_c = path.join(bootstrap_dir, "scan.c")
    local lex_ok = os.execv(lex.program,
        {"-o", scan_c, path.join(config_srcdir, "scan.l")},
        {curdir = bootstrap_dir, try = true})
    if not lex_ok or not os.isfile(scan_c) then
        print("eteleos-gen-kernel: lex/flex failed on scan.l, falling back to the approximate parser")
        return nil
    end

    local all_srcs = {gram_c, scan_c}
    for _, f in ipairs(c_srcs) do all_srcs[#all_srcs + 1] = f end

    local cflags = {
        "-O1", "-w", "-I", bootstrap_dir, "-I", config_srcdir,
        "-Dpledge(a,b)=0",
        "-o", out_bin,
    }
    for _, f in ipairs(all_srcs) do cflags[#cflags + 1] = f end

    local compile_ok = os.execv(cc.program, cflags, {curdir = bootstrap_dir, try = true})
    if not compile_ok or not os.isfile(out_bin) then
        print("eteleos-gen-kernel: host compile of config(8) failed, falling back to "
              .. "the approximate parser")
        return nil
    end
    return out_bin
end

local function run_real_config(config_bin, arch, arch_conf_dir)
    local real_generic = path.join(arch_conf_dir, "GENERIC")
    if not os.isfile(real_generic) then
        print(string.format("eteleos-gen-kernel: %s not found, falling back to the approximate parser", real_generic))
        return nil
    end

    local run_dir = path.join(GEN_ROOT, arch, "config-run")
    os.mkdir(run_dir)
    local builddir = path.join(run_dir, "build")

    local ok = os.execv(config_bin,
        {"-s", KERNEL, "-b", builddir, real_generic},
        {curdir = run_dir, try = true})
    if not ok then
        print(string.format("eteleos-gen-kernel: real config(8) run failed for arch '%s', "
              .. "falling back to the approximate parser", arch))
        return nil
    end
    if not os.isfile(path.join(builddir, "ioconf.c")) then
        print("eteleos-gen-kernel: config(8) ran but did not produce ioconf.c, falling "
              .. "back to the approximate parser")
        return nil
    end
    return builddir
end

local function harvest_selected_files(builddir)
    local makefile_path = path.join(builddir, "Makefile")
    local content = read_file(makefile_path)
    if not content then
        print(string.format("eteleos-gen-kernel: config(8) did not write a Makefile at %s, "
              .. "falling back to the approximate parser", makefile_path))
        return nil
    end
    local files, seen = {}, {}
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local relpath = line:match("^%S+%.o:%s+%$S/(%S+)%s*$")
        if relpath and not seen[relpath] then
            seen[relpath] = true
            files[#files + 1] = relpath
        end
    end
    if #files == 0 then
        print("eteleos-gen-kernel: parsed config(8)'s Makefile but found zero selected "
              .. "files, falling back to the approximate parser")
        return nil
    end
    return files
end

-- ==============================================================================
-- Approximate files/GENERIC parser -- fallback path, unchanged logic.
-- ==============================================================================
local function resolve_include(from_dir, incpath, conf_dir)
    local naive = path.join(from_dir, incpath)
    if os.isfile(naive) then return naive end
    local fallback = path.join(conf_dir, path.filename(incpath))
    if os.isfile(fallback) then return fallback end
    return nil
end

local function parse_generic(filepath, conf_dir, enabled, seen)
    seen = seen or {}
    if seen[filepath] then return end
    seen[filepath] = true
    local content = read_file(filepath)
    if not content then
        print(string.format("eteleos-gen-kernel: config file not found: %s", filepath))
        return
    end
    local from_dir = path.directory(filepath)
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local stripped = strip_comment(line)
        local tokens = {}
        for tok in stripped:gmatch("%S+") do tokens[#tokens + 1] = tok end
        if #tokens > 0 then
            local kw = tokens[1]
            local disabled = tokens[#tokens] == "disable"
            if kw == "option" and tokens[2] then
                for name in tokens[2]:gmatch("[^,=]+") do enabled[name] = true end
            elseif kw == "pseudo-device" and tokens[2] then
                enabled[tokens[2]] = true
            elseif kw == "include" and tokens[2] then
                local incpath = tokens[2]:gsub('"', "")
                local resolved = resolve_include(from_dir, incpath, conf_dir)
                if resolved then
                    parse_generic(resolved, conf_dir, enabled, seen)
                else
                    print(string.format("eteleos-gen-kernel: could not resolve GENERIC include \"%s\" from %s",
                          incpath, filepath))
                end
            elseif tokens[2] == "at" and not disabled then
                enabled[extract_base_name(kw)] = true
            end
        end
    end
end

local DIRECTIVES = {
    file=true, device=true, attach=true, define=true, ["pseudo-device"]=true,
    major=true, maxpartitions=true, maxusers=true, obsolete=true, deffs=true,
    defflag=true, defopt=true, defparam=true, filesystem=true, machine=true,
    source=true, include=true, ["export-jail"]=true,
}

local function parse_files_list(filepath, entries)
    local content = read_file(filepath)
    if not content then
        print(string.format("eteleos-gen-kernel: files list not found: %s", filepath))
        return
    end
    local pending
    local function flush() if pending then entries[#entries + 1] = pending end; pending = nil end
    for line in (content .. "\n"):gmatch("(.-)\n") do
        local stripped = strip_comment(line)
        local tokens = {}
        for tok in stripped:gmatch("%S+") do tokens[#tokens + 1] = tok end
        if #tokens > 0 then
            if tokens[1] == "file" then
                flush()
                pending = { path = tokens[2], cond = {} }
                for i = 3, #tokens do pending.cond[#pending.cond + 1] = tokens[i] end
            elseif DIRECTIVES[tokens[1]] then
                flush()
            elseif pending then
                for _, t in ipairs(tokens) do pending.cond[#pending.cond + 1] = t end
            end
        end
    end
    flush()
end

local function strip_modifiers(cond)
    local out, i = {}, 1
    while i <= #cond do
        local t = cond[i]
        if t == "needs-flag" then
        elseif t == "needs-count" then i = i + 1
        else out[#out + 1] = t end
        i = i + 1
    end
    return out
end

local function eval_expr(cond, enabled)
    cond = strip_modifiers(cond)
    if #cond == 0 then return true end
    local pos = 1
    local function peek() return cond[pos] end
    local function advance() pos = pos + 1 end
    local parse_or, parse_and, parse_atom
    parse_atom = function()
        local t = peek()
        if t == "(" then
            advance()
            local v = parse_or()
            if peek() == ")" then advance() end
            return v
        elseif t == nil then return true
        else advance(); return enabled[t] == true end
    end
    parse_and = function()
        local v = parse_atom()
        while peek() == "&" do advance(); v = parse_atom() and v end
        return v
    end
    parse_or = function()
        local v = parse_and()
        while peek() == "|" do advance(); v = parse_and() or v end
        return v
    end
    return parse_or()
end

local function approximate_parser_selected_files(arch, core_conf_dir, arch_conf_dir)
    local enabled = {}
    parse_generic(path.join(core_conf_dir, "GENERIC"), core_conf_dir, enabled)
    parse_generic(path.join(arch_conf_dir, "GENERIC"), core_conf_dir, enabled)

    local file_entries = {}
    parse_files_list(path.join(core_conf_dir, "files"), file_entries)
    parse_files_list(path.join(arch_conf_dir, "files." .. arch), file_entries)

    local selected = {}
    for _, e in ipairs(file_entries) do
        if eval_expr(e.cond, enabled) then
            selected[#selected + 1] = e.path
        end
    end
    return selected
end

-- ==============================================================================
-- Drive it for all three arches. config(8) itself is arch-independent, so
-- it is only built once and reused.
-- ==============================================================================
local config_bin = build_host_config_tool()

local MANIFEST = {}
for _, arch in ipairs(ARCHES) do
    local core_conf_dir = path.join(KERNEL, "core", "conf")
    local arch_conf_dir = path.join(KERNEL, "arch", arch, "conf")

    local builddir = config_bin and run_real_config(config_bin, arch, arch_conf_dir) or nil
    local harvested = builddir and harvest_selected_files(builddir) or nil

    if harvested then
        MANIFEST[arch] = {
            selected_files = harvested,
            ioconf_c = read_file(path.join(builddir, "ioconf.c")),
            mode = "real-config8",
        }
        print(string.format("eteleos-gen-kernel: %s: using REAL config(8) output "
              .. "(%d files selected, ioconf.c generated)", arch, #harvested))
    else
        local approx = approximate_parser_selected_files(arch, core_conf_dir, arch_conf_dir)
        MANIFEST[arch] = {
            selected_files = approx,
            ioconf_c = nil,
            mode = "approximate",
        }
        print(string.format("eteleos-gen-kernel: %s: using the approximate files/GENERIC "
              .. "parser (%d files selected) -- no ioconf.c, attach-graph gap still applies",
              arch, #approx))
    end
end

-- ==============================================================================
-- Serialize
-- ==============================================================================
local function lua_quote(s) return string.format("%q", s) end

local function serialize_list(list, indent)
    local parts = {}
    for _, v in ipairs(list) do parts[#parts + 1] = indent .. "    " .. lua_quote(v) .. "," end
    if #parts == 0 then return "{}" end
    return "{\n" .. table.concat(parts, "\n") .. "\n" .. indent .. "}"
end

local out = {}
out[#out + 1] = "--[[ AUTO-GENERATED by tools/gen/gen_kernel_manifest.lua -- DO NOT EDIT BY HAND."
out[#out + 1] = "     Regenerate with: xmake lua tools/gen/gen_kernel_manifest.lua ]]"
out[#out + 1] = ""
out[#out + 1] = "ETELEOS_KERNEL_MANIFEST = {}"
for _, arch in ipairs(ARCHES) do
    local m = MANIFEST[arch]
    out[#out + 1] = string.format("ETELEOS_KERNEL_MANIFEST[%q] = {", arch)
    out[#out + 1] = string.format("    mode = %q,", m.mode)
    out[#out + 1] = "    selected_files = " .. serialize_list(m.selected_files, "    ") .. ","
    out[#out + 1] = "    ioconf_c = " .. (m.ioconf_c and lua_quote(m.ioconf_c) or "nil") .. ","
    out[#out + 1] = "}"
end
out[#out + 1] = ""

local outpath = path.join(KERNEL, "generated_manifest.lua")
write_file(outpath, table.concat(out, "\n"))
print(string.format("eteleos-gen-kernel: manifest written to %s", outpath))
