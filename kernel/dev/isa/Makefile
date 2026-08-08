#	$OpenBSD: Makefile,v 1.1 1997/07/12 23:22:00 weingart Exp $
#	$NetBSD: Makefile,v 1.1 1995/06/18 01:07:04 cgd Exp $

AWK=	awk

pnpdevs.h: pnpdevs devlist2h.lua
	/bin/rm -f pnpdevs.h
	xmake lua -q devlist2h.lua pnpdevs
