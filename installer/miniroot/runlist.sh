#	$OpenBSD: runlist.sh,v 1.6 2014/02/21 19:14:23 deraadt Exp $

if [ "X$1" = "X-d" ]; then
	SHELLCMD=cat
	shift
else
	SHELLCMD="sh -e"
fi

( while [ "X$1" != "X" ]; do
	cat $1
	shift
done ) | xmake lua -q ${UTILS:-${CURDIR}}/list2sh.lua | ${SHELLCMD}
