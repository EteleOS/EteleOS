#	$OpenBSD: Makefile,v 1.3 2017/07/10 21:30:37 espie Exp $

PROG=	rpc.statd
SRCS=	procs.c sm_inter_svc.c statd.c
MAN=	rpc.statd.8

DPADD=	${LIBRPCSVC}
LDADD=	-lrpcsvc

CFLAGS+= -I.

test: ${.CURDIR}/test.c
	cc -o test ${.CURDIR}/test.c -lrpcsvc

.include <bsd.prog.mk>
