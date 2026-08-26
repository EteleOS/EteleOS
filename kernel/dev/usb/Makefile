#	$OpenBSD: Makefile,v 1.3 2007/06/04 10:34:04 mbalmer Exp $
#	$NetBSD: Makefile.usbdevs,v 1.2 1999/01/07 22:18:23 augustss Exp $

UNAME=	uname

PROG=	makemap.pl
MAP=	../pckbc/wskbdmap_mfii.c

all:	usbdevs.h ukbdmap.c

usbdevs.h usbdevs_data.h: usbdevs devlist2h.pl
	/bin/rm -f usbdevs.h usbdevs_data.h
	perl devlist2h.pl usbdevs

ukbdmap.c: ${MAP} ${PROG}
	/bin/rm -f $@
	perl ${PROG} ${MAP} > $@
