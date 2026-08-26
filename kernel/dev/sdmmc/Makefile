#	$OpenBSD: Makefile,v 1.1 2006/06/01 21:15:40 uwe Exp $

AWK=	awk

sdmmcdevs.h: sdmmcdevs devlist2h.pl
	/bin/rm -f sdmmcdevs.h
	perl devlist2h.pl sdmmcdevs
