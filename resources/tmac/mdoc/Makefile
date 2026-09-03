#	$OpenBSD: Makefile,v 1.6 2019/12/21 21:40:01 espie Exp $
#	@(#)Makefile	8.1 (Berkeley) 6/8/93

MSRCS=	doc doc-ditroff doc-common doc-nroff doc-syms
BINDIR=	/usr/share/tmac/mdoc
LINKS=	${BINDIR}/doc ${BINDIR}/../tmac.doc

STRIP_PL = ${.CURDIR}/../strip.pl
NOOBJ=	noobj

all clean cleandir tags:

beforeinstall:
	for i in ${MSRCS}; do \
		perl ${STRIP_PL} < $$i > ${DESTDIR}${BINDIR}/$$i; \
		chown ${BINOWN}:${BINGRP} ${DESTDIR}${BINDIR}/$$i; \
		chmod 444 ${DESTDIR}${BINDIR}/$$i; \
	done

.include <bsd.prog.mk>
