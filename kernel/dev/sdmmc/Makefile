#	$OpenBSD: Makefile,v 1.1 2006/06/01 21:15:40 uwe Exp $

AWK=	awk

sdmmcdevs.h: sdmmcdevs devlist2h.lua
	/bin/rm -f sdmmcdevs.h
	xmake lua -q devlist2h.lua sdmmcdevs
