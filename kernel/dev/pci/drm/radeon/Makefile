#	$OpenBSD: Makefile,v 1.2 2020/06/08 04:48:15 jsg Exp $

radeon_devlist.h: ../include/drm/drm_pciids.h devlist.pl
	/bin/rm -f radeon_devlist.h
	perl devlist.pl ../include/drm/drm_pciids.h > radeon_devlist.h
