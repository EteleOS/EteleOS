#	$OpenBSD: Makefile,v 1.13 2016/03/30 06:38:46 jmc Exp $

.include <bsd.own.mk>

PROG=	rpc.bootparamd
SRCS=	bootparamd.c bootparam_prot_svc.c
MAN=	bootparams.5 rpc.bootparamd.8

DPADD=	${LIBRPCSVC}
LDADD=	-lrpcsvc

.include <bsd.prog.mk>
