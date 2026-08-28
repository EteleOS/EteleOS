#	$OpenBSD: Makefile,v 1.8 2017/08/24 09:00:50 otto Exp $

PROG =	rpc.lockd
SRCS =	nlm_prot_svc.c lockd.c lockd_lock.c procs.c
MAN =	rpc.lockd.8

DPADD=	${LIBRPCSVC}
LDADD=	-lrpcsvc

CFLAGS+= -I. -DSYSLOG -Wno-enum-conversion

test: test.c
	cc -o test test.c -lrpcsvc

.include <bsd.prog.mk>
