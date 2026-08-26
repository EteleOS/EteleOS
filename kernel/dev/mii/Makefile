#	$OpenBSD: Makefile,v 1.1 1998/09/10 17:17:32 jason Exp $
#	$NetBSD: Makefile.miidevs,v 1.1 1998/08/10 23:55:17 thorpej Exp $

AWK=	awk

miidevs.h: miidevs devlist2h.pl
	/bin/rm -f miidevs.h
	perl devlist2h.pl miidevs
