-- EteleOS: installer/miniroot/list2sh.lua, time write: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Original AWK file license:
-- $OpenBSD: list2sh.awk,v 1.23 2021/02/13 18:46:52 semarie Exp $
--
-- Convert `list' spec to shell script.
-- Ported from list2sh.awk (OpenBSD)

io.stdout:setvbuf("no")

local function split_fields(line)
    local fields = {}
    for f in line:gmatch("%S+") do
        fields[#fields + 1] = f
    end
    return fields
end

io.write("cd ${OBJDIR}\n")
io.write("\n")

local exit_code = 0
local line_num = 0

for line in io.lines() do
    line_num = line_num + 1
    if line:match("^$") or line:match("^#") then
        io.write(line .. "\n")
        goto continue
    end

    local f = split_fields(line)
    local NF = #f
    local f1 = f[1] or ""

    if f1 == "COPY" then
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format("test -f ${TARGDIR}/%s && rm -fr ${TARGDIR}/%s\n", f[3], f[3]))
        io.write(string.format("cp %s ${TARGDIR}/%s\n", f[2], f[3]))

    elseif f1 == "REMOVE" then
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format("rm -f ${TARGDIR}/%s\n", f[2]))

    elseif f1 == "MKDIR" then
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format("mkdir -p ${TARGDIR}/%s\n", f[2]))

    elseif f1 == "STRIP" then
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format("test -f ${TARGDIR}/%s && rm -fr ${TARGDIR}/%s\n", f[3], f[3]))
        io.write(string.format("objcopy -S %s ${TARGDIR}/%s\n", f[2], f[3]))

    elseif f1 == "LINK" then
        io.write(string.format("echo '%s'\n", line))
        for i = 3, NF do
            io.write(string.format("test -f ${TARGDIR}/%s && rm -f ${TARGDIR}/%s\n", f[i], f[i]))
            io.write(string.format("(cd ${TARGDIR}; ln %s %s)\n", f[2], f[i]))
        end

    elseif f1 == "SYMLINK" then
        io.write(string.format("echo '%s'\n", line))
        for i = 3, NF do
            io.write(string.format("test -f ${TARGDIR}/%s && rm -f ${TARGDIR}/%s\n", f[i], f[i]))
            io.write(string.format("(cd ${TARGDIR}; ln -s %s %s)\n", f[2], f[i]))
        end

    elseif f1 == "ARGVLINK" or f1 == "SRCDIRS" or f1 == "LIBS" or f1 == "CRUNCHSPECIAL" then
        -- crunchgen directive; ignored here

    elseif f1 == "TZ" then
        io.write(string.format("echo '%s'\n", line))
        io.write("(cd ${TARGDIR}; sh $UTILS/maketz.sh $DESTDIR)\n")

    elseif f1 == "COPYDIR" then
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format("(cd ${TARGDIR}/%s && find . ! -name . | xargs /bin/rm -rf)\n", f[3]))
        io.write(string.format("(cd %s && pax -pe -rw . ${TARGDIR}/%s)\n", f[2], f[3]))

    elseif f1 == "SPECIAL" then
        local work = line
        work = work:gsub("\\", "\\\\")
        work = work:gsub('"', '\\"')
        work = work:gsub("%$", "\\$")
        work = work:gsub("`", "\\`")
        io.write(string.format('echo "%s"\n', work))

        local work2 = line:gsub("^[%s]*" .. f1 .. "[%s]*", "", 1)
        io.write(string.format("(cd ${TARGDIR}; %s)\n", work2))

    elseif f1 == "TERMCAP" then
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format(
            "(cd ${TARGDIR}; tic -C -x -r -e %s ${UTILS}/../../share/termtypes/termtypes.master | sed -e '/^#.*/d' -e '/^$/d' > %s)\n",
            f[2], f[3]))

    elseif f1 == "SCRIPT" then
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format(
            "sed -e '/^[ \\t]*#[ \\t].*$/d' -e '/^[ \\t]*#$/d' < %s > ${TARGDIR}/%s\n",
            f[2], f[3]))

    else
        io.write(string.format("echo '%s'\n", line))
        io.write(string.format('echo \'Unknown keyword "%s" at line %d of input.\'\n', f1, line_num))
        io.write("exit 1\n")
        exit_code = 1
        break
    end

    ::continue::
end

io.write("\n")
io.write("exit 0\n")
os.exit(exit_code)
