/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 24 "parse.y"

#include <sys/stat.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <ifaddrs.h>
#include <inttypes.h>
#include <libgen.h>
#include <resolv.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <util.h>

#include "smtpd.h"
#include "ssl.h"
#include "log.h"

TAILQ_HEAD(files, file)		 files = TAILQ_HEAD_INITIALIZER(files);
static struct file {
	TAILQ_ENTRY(file)	 entry;
	FILE			*stream;
	char			*name;
	size_t			 ungetpos;
	size_t			 ungetsize;
	u_char			*ungetbuf;
	int			 eof_reached;
	int			 lineno;
	int			 errors;
} *file, *topfile;
struct file	*pushfile(const char *, int);
int		 popfile(void);
int		 check_file_secrecy(int, const char *);
int		 yyparse(void);
int		 yylex(void);
int		 kw_cmp(const void *, const void *);
int		 lookup(char *);
int		 igetc(void);
int		 lgetc(int);
void		 lungetc(int);
int		 findeol(void);
int		 yyerror(const char *, ...)
    __attribute__((__format__ (printf, 1, 2)))
    __attribute__((__nonnull__ (1)));

TAILQ_HEAD(symhead, sym)	 symhead = TAILQ_HEAD_INITIALIZER(symhead);
struct sym {
	TAILQ_ENTRY(sym)	 entry;
	int			 used;
	int			 persist;
	char			*nam;
	char			*val;
};
int		 symset(const char *, const char *, int);
char		*symget(const char *);

struct smtpd		*conf = NULL;
static int		 errors = 0;

struct table		*table = NULL;
struct mta_limits	*limits;
static struct pki	*pki;
static struct ca	*sca;

struct dispatcher	*dsp;
struct rule		*rule;
struct filter_proc	*processor;
struct filter_config	*filter_config;
static uint32_t		 last_dynchain_id = 1;

enum listen_options {
	LO_FAMILY	= 0x000001,
	LO_PORT		= 0x000002,
	LO_SSL		= 0x000004,
	LO_FILTER      	= 0x000008,
	LO_PKI      	= 0x000010,
	LO_AUTH      	= 0x000020,
	LO_TAG      	= 0x000040,
	LO_HOSTNAME   	= 0x000080,
	LO_HOSTNAMES   	= 0x000100,
	LO_MASKSOURCE  	= 0x000200,
	LO_NODSN	= 0x000400,
	LO_SENDERS	= 0x000800,
	LO_RECEIVEDAUTH = 0x001000,
	LO_MASQUERADE	= 0x002000,
	LO_CA		= 0x004000,
	LO_PROXY       	= 0x008000,
};

#define PKI_MAX	32
static struct listen_opts {
	char	       *ifx;
	int		family;
	in_port_t	port;
	uint16_t	ssl;
	char	       *filtername;
	char	       *pki[PKI_MAX];
	int		pkicount;
	char	       *tls_ciphers;
	char	       *tls_protocols;
	char	       *ca;
	uint16_t       	auth;
	struct table   *authtable;
	char	       *tag;
	char	       *hostname;
	struct table   *hostnametable;
	struct table   *sendertable;
	uint16_t	flags;

	uint32_t       	options;
} listen_opts;

static void	create_sock_listener(struct listen_opts *);
static void	create_if_listener(struct listen_opts *);
static void	config_listener(struct listener *, struct listen_opts *);
static int	host_v4(struct listen_opts *);
static int	host_v6(struct listen_opts *);
static int	host_dns(struct listen_opts *);
static int	interface(struct listen_opts *);
#define TAG_MAX	32
static const char *processor_maketag(const char *);

int		 delaytonum(char *);
int		 is_if_in_group(const char *, const char *);

static int config_lo_mask_source(struct listen_opts *);

typedef struct {
	union {
		int64_t		 number;
		struct table	*table;
		char		*string;
		struct host	*host;
		struct mailaddr	*maddr;
	} v;
	int lineno;
} YYSTYPE;


#line 217 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ACTION = 258,                  /* ACTION  */
    ADMD = 259,                    /* ADMD  */
    ALIAS = 260,                   /* ALIAS  */
    ANY = 261,                     /* ANY  */
    ARROW = 262,                   /* ARROW  */
    AUTH = 263,                    /* AUTH  */
    AUTH_OPTIONAL = 264,           /* AUTH_OPTIONAL  */
    BACKUP = 265,                  /* BACKUP  */
    BOUNCE = 266,                  /* BOUNCE  */
    BYPASS = 267,                  /* BYPASS  */
    CA = 268,                      /* CA  */
    CERT = 269,                    /* CERT  */
    CHAIN = 270,                   /* CHAIN  */
    CHROOT = 271,                  /* CHROOT  */
    CIPHERS = 272,                 /* CIPHERS  */
    COMMIT = 273,                  /* COMMIT  */
    COMPRESSION = 274,             /* COMPRESSION  */
    CONNECT = 275,                 /* CONNECT  */
    DATA = 276,                    /* DATA  */
    DATA_LINE = 277,               /* DATA_LINE  */
    DHE = 278,                     /* DHE  */
    DISCONNECT = 279,              /* DISCONNECT  */
    DOMAIN = 280,                  /* DOMAIN  */
    EHLO = 281,                    /* EHLO  */
    ENABLE = 282,                  /* ENABLE  */
    ENCRYPTION = 283,              /* ENCRYPTION  */
    ERROR = 284,                   /* ERROR  */
    EXPAND_ONLY = 285,             /* EXPAND_ONLY  */
    FCRDNS = 286,                  /* FCRDNS  */
    FILTER = 287,                  /* FILTER  */
    FOR = 288,                     /* FOR  */
    FORWARD_ONLY = 289,            /* FORWARD_ONLY  */
    FROM = 290,                    /* FROM  */
    GROUP = 291,                   /* GROUP  */
    HELO = 292,                    /* HELO  */
    HELO_SRC = 293,                /* HELO_SRC  */
    HOST = 294,                    /* HOST  */
    HOSTNAME = 295,                /* HOSTNAME  */
    HOSTNAMES = 296,               /* HOSTNAMES  */
    INCLUDE = 297,                 /* INCLUDE  */
    INET4 = 298,                   /* INET4  */
    INET6 = 299,                   /* INET6  */
    JUNK = 300,                    /* JUNK  */
    KEY = 301,                     /* KEY  */
    LIMIT = 302,                   /* LIMIT  */
    LISTEN = 303,                  /* LISTEN  */
    LMTP = 304,                    /* LMTP  */
    LOCAL = 305,                   /* LOCAL  */
    MAIL_FROM = 306,               /* MAIL_FROM  */
    MAILDIR = 307,                 /* MAILDIR  */
    MASK_SRC = 308,                /* MASK_SRC  */
    MASQUERADE = 309,              /* MASQUERADE  */
    MATCH = 310,                   /* MATCH  */
    MAX_MESSAGE_SIZE = 311,        /* MAX_MESSAGE_SIZE  */
    MAX_DEFERRED = 312,            /* MAX_DEFERRED  */
    MBOX = 313,                    /* MBOX  */
    MDA = 314,                     /* MDA  */
    MTA = 315,                     /* MTA  */
    MX = 316,                      /* MX  */
    NO_DSN = 317,                  /* NO_DSN  */
    NO_VERIFY = 318,               /* NO_VERIFY  */
    NOOP = 319,                    /* NOOP  */
    ON = 320,                      /* ON  */
    PHASE = 321,                   /* PHASE  */
    PKI = 322,                     /* PKI  */
    PORT = 323,                    /* PORT  */
    PROC = 324,                    /* PROC  */
    PROC_EXEC = 325,               /* PROC_EXEC  */
    PROTOCOLS = 326,               /* PROTOCOLS  */
    PROXY_V2 = 327,                /* PROXY_V2  */
    QUEUE = 328,                   /* QUEUE  */
    QUIT = 329,                    /* QUIT  */
    RCPT_TO = 330,                 /* RCPT_TO  */
    RDNS = 331,                    /* RDNS  */
    RECIPIENT = 332,               /* RECIPIENT  */
    RECEIVEDAUTH = 333,            /* RECEIVEDAUTH  */
    REGEX = 334,                   /* REGEX  */
    RELAY = 335,                   /* RELAY  */
    REJECT = 336,                  /* REJECT  */
    REPORT = 337,                  /* REPORT  */
    REWRITE = 338,                 /* REWRITE  */
    RSET = 339,                    /* RSET  */
    SCHEDULER = 340,               /* SCHEDULER  */
    SENDER = 341,                  /* SENDER  */
    SENDERS = 342,                 /* SENDERS  */
    SMTP = 343,                    /* SMTP  */
    SMTP_IN = 344,                 /* SMTP_IN  */
    SMTP_OUT = 345,                /* SMTP_OUT  */
    SMTPS = 346,                   /* SMTPS  */
    SOCKET = 347,                  /* SOCKET  */
    SRC = 348,                     /* SRC  */
    SRS = 349,                     /* SRS  */
    SUB_ADDR_DELIM = 350,          /* SUB_ADDR_DELIM  */
    TABLE = 351,                   /* TABLE  */
    TAG = 352,                     /* TAG  */
    TAGGED = 353,                  /* TAGGED  */
    TLS = 354,                     /* TLS  */
    TLS_REQUIRE = 355,             /* TLS_REQUIRE  */
    TTL = 356,                     /* TTL  */
    USER = 357,                    /* USER  */
    USERBASE = 358,                /* USERBASE  */
    VERIFY = 359,                  /* VERIFY  */
    VIRTUAL = 360,                 /* VIRTUAL  */
    WARN_INTERVAL = 361,           /* WARN_INTERVAL  */
    WRAPPER = 362,                 /* WRAPPER  */
    STRING = 363,                  /* STRING  */
    NUMBER = 364                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ACTION 258
#define ADMD 259
#define ALIAS 260
#define ANY 261
#define ARROW 262
#define AUTH 263
#define AUTH_OPTIONAL 264
#define BACKUP 265
#define BOUNCE 266
#define BYPASS 267
#define CA 268
#define CERT 269
#define CHAIN 270
#define CHROOT 271
#define CIPHERS 272
#define COMMIT 273
#define COMPRESSION 274
#define CONNECT 275
#define DATA 276
#define DATA_LINE 277
#define DHE 278
#define DISCONNECT 279
#define DOMAIN 280
#define EHLO 281
#define ENABLE 282
#define ENCRYPTION 283
#define ERROR 284
#define EXPAND_ONLY 285
#define FCRDNS 286
#define FILTER 287
#define FOR 288
#define FORWARD_ONLY 289
#define FROM 290
#define GROUP 291
#define HELO 292
#define HELO_SRC 293
#define HOST 294
#define HOSTNAME 295
#define HOSTNAMES 296
#define INCLUDE 297
#define INET4 298
#define INET6 299
#define JUNK 300
#define KEY 301
#define LIMIT 302
#define LISTEN 303
#define LMTP 304
#define LOCAL 305
#define MAIL_FROM 306
#define MAILDIR 307
#define MASK_SRC 308
#define MASQUERADE 309
#define MATCH 310
#define MAX_MESSAGE_SIZE 311
#define MAX_DEFERRED 312
#define MBOX 313
#define MDA 314
#define MTA 315
#define MX 316
#define NO_DSN 317
#define NO_VERIFY 318
#define NOOP 319
#define ON 320
#define PHASE 321
#define PKI 322
#define PORT 323
#define PROC 324
#define PROC_EXEC 325
#define PROTOCOLS 326
#define PROXY_V2 327
#define QUEUE 328
#define QUIT 329
#define RCPT_TO 330
#define RDNS 331
#define RECIPIENT 332
#define RECEIVEDAUTH 333
#define REGEX 334
#define RELAY 335
#define REJECT 336
#define REPORT 337
#define REWRITE 338
#define RSET 339
#define SCHEDULER 340
#define SENDER 341
#define SENDERS 342
#define SMTP 343
#define SMTP_IN 344
#define SMTP_OUT 345
#define SMTPS 346
#define SOCKET 347
#define SRC 348
#define SRS 349
#define SUB_ADDR_DELIM 350
#define TABLE 351
#define TAG 352
#define TAGGED 353
#define TLS 354
#define TLS_REQUIRE 355
#define TTL 356
#define USER 357
#define USERBASE 358
#define VERIFY 359
#define VIRTUAL 360
#define WARN_INTERVAL 361
#define WRAPPER 362
#define STRING 363
#define NUMBER 364

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ACTION = 3,                     /* ACTION  */
  YYSYMBOL_ADMD = 4,                       /* ADMD  */
  YYSYMBOL_ALIAS = 5,                      /* ALIAS  */
  YYSYMBOL_ANY = 6,                        /* ANY  */
  YYSYMBOL_ARROW = 7,                      /* ARROW  */
  YYSYMBOL_AUTH = 8,                       /* AUTH  */
  YYSYMBOL_AUTH_OPTIONAL = 9,              /* AUTH_OPTIONAL  */
  YYSYMBOL_BACKUP = 10,                    /* BACKUP  */
  YYSYMBOL_BOUNCE = 11,                    /* BOUNCE  */
  YYSYMBOL_BYPASS = 12,                    /* BYPASS  */
  YYSYMBOL_CA = 13,                        /* CA  */
  YYSYMBOL_CERT = 14,                      /* CERT  */
  YYSYMBOL_CHAIN = 15,                     /* CHAIN  */
  YYSYMBOL_CHROOT = 16,                    /* CHROOT  */
  YYSYMBOL_CIPHERS = 17,                   /* CIPHERS  */
  YYSYMBOL_COMMIT = 18,                    /* COMMIT  */
  YYSYMBOL_COMPRESSION = 19,               /* COMPRESSION  */
  YYSYMBOL_CONNECT = 20,                   /* CONNECT  */
  YYSYMBOL_DATA = 21,                      /* DATA  */
  YYSYMBOL_DATA_LINE = 22,                 /* DATA_LINE  */
  YYSYMBOL_DHE = 23,                       /* DHE  */
  YYSYMBOL_DISCONNECT = 24,                /* DISCONNECT  */
  YYSYMBOL_DOMAIN = 25,                    /* DOMAIN  */
  YYSYMBOL_EHLO = 26,                      /* EHLO  */
  YYSYMBOL_ENABLE = 27,                    /* ENABLE  */
  YYSYMBOL_ENCRYPTION = 28,                /* ENCRYPTION  */
  YYSYMBOL_ERROR = 29,                     /* ERROR  */
  YYSYMBOL_EXPAND_ONLY = 30,               /* EXPAND_ONLY  */
  YYSYMBOL_FCRDNS = 31,                    /* FCRDNS  */
  YYSYMBOL_FILTER = 32,                    /* FILTER  */
  YYSYMBOL_FOR = 33,                       /* FOR  */
  YYSYMBOL_FORWARD_ONLY = 34,              /* FORWARD_ONLY  */
  YYSYMBOL_FROM = 35,                      /* FROM  */
  YYSYMBOL_GROUP = 36,                     /* GROUP  */
  YYSYMBOL_HELO = 37,                      /* HELO  */
  YYSYMBOL_HELO_SRC = 38,                  /* HELO_SRC  */
  YYSYMBOL_HOST = 39,                      /* HOST  */
  YYSYMBOL_HOSTNAME = 40,                  /* HOSTNAME  */
  YYSYMBOL_HOSTNAMES = 41,                 /* HOSTNAMES  */
  YYSYMBOL_INCLUDE = 42,                   /* INCLUDE  */
  YYSYMBOL_INET4 = 43,                     /* INET4  */
  YYSYMBOL_INET6 = 44,                     /* INET6  */
  YYSYMBOL_JUNK = 45,                      /* JUNK  */
  YYSYMBOL_KEY = 46,                       /* KEY  */
  YYSYMBOL_LIMIT = 47,                     /* LIMIT  */
  YYSYMBOL_LISTEN = 48,                    /* LISTEN  */
  YYSYMBOL_LMTP = 49,                      /* LMTP  */
  YYSYMBOL_LOCAL = 50,                     /* LOCAL  */
  YYSYMBOL_MAIL_FROM = 51,                 /* MAIL_FROM  */
  YYSYMBOL_MAILDIR = 52,                   /* MAILDIR  */
  YYSYMBOL_MASK_SRC = 53,                  /* MASK_SRC  */
  YYSYMBOL_MASQUERADE = 54,                /* MASQUERADE  */
  YYSYMBOL_MATCH = 55,                     /* MATCH  */
  YYSYMBOL_MAX_MESSAGE_SIZE = 56,          /* MAX_MESSAGE_SIZE  */
  YYSYMBOL_MAX_DEFERRED = 57,              /* MAX_DEFERRED  */
  YYSYMBOL_MBOX = 58,                      /* MBOX  */
  YYSYMBOL_MDA = 59,                       /* MDA  */
  YYSYMBOL_MTA = 60,                       /* MTA  */
  YYSYMBOL_MX = 61,                        /* MX  */
  YYSYMBOL_NO_DSN = 62,                    /* NO_DSN  */
  YYSYMBOL_NO_VERIFY = 63,                 /* NO_VERIFY  */
  YYSYMBOL_NOOP = 64,                      /* NOOP  */
  YYSYMBOL_ON = 65,                        /* ON  */
  YYSYMBOL_PHASE = 66,                     /* PHASE  */
  YYSYMBOL_PKI = 67,                       /* PKI  */
  YYSYMBOL_PORT = 68,                      /* PORT  */
  YYSYMBOL_PROC = 69,                      /* PROC  */
  YYSYMBOL_PROC_EXEC = 70,                 /* PROC_EXEC  */
  YYSYMBOL_PROTOCOLS = 71,                 /* PROTOCOLS  */
  YYSYMBOL_PROXY_V2 = 72,                  /* PROXY_V2  */
  YYSYMBOL_QUEUE = 73,                     /* QUEUE  */
  YYSYMBOL_QUIT = 74,                      /* QUIT  */
  YYSYMBOL_RCPT_TO = 75,                   /* RCPT_TO  */
  YYSYMBOL_RDNS = 76,                      /* RDNS  */
  YYSYMBOL_RECIPIENT = 77,                 /* RECIPIENT  */
  YYSYMBOL_RECEIVEDAUTH = 78,              /* RECEIVEDAUTH  */
  YYSYMBOL_REGEX = 79,                     /* REGEX  */
  YYSYMBOL_RELAY = 80,                     /* RELAY  */
  YYSYMBOL_REJECT = 81,                    /* REJECT  */
  YYSYMBOL_REPORT = 82,                    /* REPORT  */
  YYSYMBOL_REWRITE = 83,                   /* REWRITE  */
  YYSYMBOL_RSET = 84,                      /* RSET  */
  YYSYMBOL_SCHEDULER = 85,                 /* SCHEDULER  */
  YYSYMBOL_SENDER = 86,                    /* SENDER  */
  YYSYMBOL_SENDERS = 87,                   /* SENDERS  */
  YYSYMBOL_SMTP = 88,                      /* SMTP  */
  YYSYMBOL_SMTP_IN = 89,                   /* SMTP_IN  */
  YYSYMBOL_SMTP_OUT = 90,                  /* SMTP_OUT  */
  YYSYMBOL_SMTPS = 91,                     /* SMTPS  */
  YYSYMBOL_SOCKET = 92,                    /* SOCKET  */
  YYSYMBOL_SRC = 93,                       /* SRC  */
  YYSYMBOL_SRS = 94,                       /* SRS  */
  YYSYMBOL_SUB_ADDR_DELIM = 95,            /* SUB_ADDR_DELIM  */
  YYSYMBOL_TABLE = 96,                     /* TABLE  */
  YYSYMBOL_TAG = 97,                       /* TAG  */
  YYSYMBOL_TAGGED = 98,                    /* TAGGED  */
  YYSYMBOL_TLS = 99,                       /* TLS  */
  YYSYMBOL_TLS_REQUIRE = 100,              /* TLS_REQUIRE  */
  YYSYMBOL_TTL = 101,                      /* TTL  */
  YYSYMBOL_USER = 102,                     /* USER  */
  YYSYMBOL_USERBASE = 103,                 /* USERBASE  */
  YYSYMBOL_VERIFY = 104,                   /* VERIFY  */
  YYSYMBOL_VIRTUAL = 105,                  /* VIRTUAL  */
  YYSYMBOL_WARN_INTERVAL = 106,            /* WARN_INTERVAL  */
  YYSYMBOL_WRAPPER = 107,                  /* WRAPPER  */
  YYSYMBOL_STRING = 108,                   /* STRING  */
  YYSYMBOL_NUMBER = 109,                   /* NUMBER  */
  YYSYMBOL_110_n_ = 110,                   /* '\n'  */
  YYSYMBOL_111_ = 111,                     /* '='  */
  YYSYMBOL_112_ = 112,                     /* ','  */
  YYSYMBOL_113_ = 113,                     /* '!'  */
  YYSYMBOL_114_ = 114,                     /* '{'  */
  YYSYMBOL_115_ = 115,                     /* '}'  */
  YYSYMBOL_116_ = 116,                     /* '<'  */
  YYSYMBOL_117_ = 117,                     /* '>'  */
  YYSYMBOL_YYACCEPT = 118,                 /* $accept  */
  YYSYMBOL_grammar = 119,                  /* grammar  */
  YYSYMBOL_include = 120,                  /* include  */
  YYSYMBOL_varset = 121,                   /* varset  */
  YYSYMBOL_comma = 122,                    /* comma  */
  YYSYMBOL_optnl = 123,                    /* optnl  */
  YYSYMBOL_nl = 124,                       /* nl  */
  YYSYMBOL_negation = 125,                 /* negation  */
  YYSYMBOL_assign = 126,                   /* assign  */
  YYSYMBOL_keyval = 127,                   /* keyval  */
  YYSYMBOL_keyval_list = 128,              /* keyval_list  */
  YYSYMBOL_stringel = 129,                 /* stringel  */
  YYSYMBOL_string_list = 130,              /* string_list  */
  YYSYMBOL_tableval_list = 131,            /* tableval_list  */
  YYSYMBOL_bounce = 132,                   /* bounce  */
  YYSYMBOL_133_1 = 133,                    /* $@1  */
  YYSYMBOL_admd = 134,                     /* admd  */
  YYSYMBOL_ca = 135,                       /* ca  */
  YYSYMBOL_136_2 = 136,                    /* $@2  */
  YYSYMBOL_ca_params_opt = 137,            /* ca_params_opt  */
  YYSYMBOL_ca_params = 138,                /* ca_params  */
  YYSYMBOL_mda = 139,                      /* mda  */
  YYSYMBOL_mta = 140,                      /* mta  */
  YYSYMBOL_141_3 = 141,                    /* $@3  */
  YYSYMBOL_142_4 = 142,                    /* $@4  */
  YYSYMBOL_pki = 143,                      /* pki  */
  YYSYMBOL_144_5 = 144,                    /* $@5  */
  YYSYMBOL_pki_params_opt = 145,           /* pki_params_opt  */
  YYSYMBOL_pki_params = 146,               /* pki_params  */
  YYSYMBOL_proc = 147,                     /* proc  */
  YYSYMBOL_148_6 = 148,                    /* $@6  */
  YYSYMBOL_proc_params_opt = 149,          /* proc_params_opt  */
  YYSYMBOL_proc_params = 150,              /* proc_params  */
  YYSYMBOL_queue = 151,                    /* queue  */
  YYSYMBOL_scheduler = 152,                /* scheduler  */
  YYSYMBOL_smtp = 153,                     /* smtp  */
  YYSYMBOL_srs = 154,                      /* srs  */
  YYSYMBOL_dispatcher_local_option = 155,  /* dispatcher_local_option  */
  YYSYMBOL_dispatcher_local_options = 156, /* dispatcher_local_options  */
  YYSYMBOL_dispatcher_local = 157,         /* dispatcher_local  */
  YYSYMBOL_158_7 = 158,                    /* $@7  */
  YYSYMBOL_159_8 = 159,                    /* $@8  */
  YYSYMBOL_160_9 = 160,                    /* $@9  */
  YYSYMBOL_161_10 = 161,                   /* $@10  */
  YYSYMBOL_162_11 = 162,                   /* $@11  */
  YYSYMBOL_163_12 = 163,                   /* $@12  */
  YYSYMBOL_164_13 = 164,                   /* $@13  */
  YYSYMBOL_165_14 = 165,                   /* $@14  */
  YYSYMBOL_166_15 = 166,                   /* $@15  */
  YYSYMBOL_167_16 = 167,                   /* $@16  */
  YYSYMBOL_dispatcher_remote_option = 168, /* dispatcher_remote_option  */
  YYSYMBOL_169_17 = 169,                   /* $@17  */
  YYSYMBOL_dispatcher_remote_options = 170, /* dispatcher_remote_options  */
  YYSYMBOL_dispatcher_remote = 171,        /* dispatcher_remote  */
  YYSYMBOL_dispatcher_type = 172,          /* dispatcher_type  */
  YYSYMBOL_dispatcher_option = 173,        /* dispatcher_option  */
  YYSYMBOL_dispatcher_options = 174,       /* dispatcher_options  */
  YYSYMBOL_dispatcher = 175,               /* dispatcher  */
  YYSYMBOL_176_18 = 176,                   /* $@18  */
  YYSYMBOL_match_option = 177,             /* match_option  */
  YYSYMBOL_match_options = 178,            /* match_options  */
  YYSYMBOL_match_dispatcher = 179,         /* match_dispatcher  */
  YYSYMBOL_action = 180,                   /* action  */
  YYSYMBOL_match = 181,                    /* match  */
  YYSYMBOL_182_19 = 182,                   /* $@19  */
  YYSYMBOL_filter_action_builtin = 183,    /* filter_action_builtin  */
  YYSYMBOL_filter_action_builtin_nojunk = 184, /* filter_action_builtin_nojunk  */
  YYSYMBOL_filter_phase_check_fcrdns = 185, /* filter_phase_check_fcrdns  */
  YYSYMBOL_filter_phase_check_rdns = 186,  /* filter_phase_check_rdns  */
  YYSYMBOL_filter_phase_check_rdns_table = 187, /* filter_phase_check_rdns_table  */
  YYSYMBOL_filter_phase_check_rdns_regex = 188, /* filter_phase_check_rdns_regex  */
  YYSYMBOL_filter_phase_check_src_table = 189, /* filter_phase_check_src_table  */
  YYSYMBOL_filter_phase_check_src_regex = 190, /* filter_phase_check_src_regex  */
  YYSYMBOL_filter_phase_check_helo_table = 191, /* filter_phase_check_helo_table  */
  YYSYMBOL_filter_phase_check_helo_regex = 192, /* filter_phase_check_helo_regex  */
  YYSYMBOL_filter_phase_check_auth = 193,  /* filter_phase_check_auth  */
  YYSYMBOL_filter_phase_check_auth_table = 194, /* filter_phase_check_auth_table  */
  YYSYMBOL_filter_phase_check_auth_regex = 195, /* filter_phase_check_auth_regex  */
  YYSYMBOL_filter_phase_check_mail_from_table = 196, /* filter_phase_check_mail_from_table  */
  YYSYMBOL_filter_phase_check_mail_from_regex = 197, /* filter_phase_check_mail_from_regex  */
  YYSYMBOL_filter_phase_check_rcpt_to_table = 198, /* filter_phase_check_rcpt_to_table  */
  YYSYMBOL_filter_phase_check_rcpt_to_regex = 199, /* filter_phase_check_rcpt_to_regex  */
  YYSYMBOL_filter_phase_global_options = 200, /* filter_phase_global_options  */
  YYSYMBOL_filter_phase_connect_options = 201, /* filter_phase_connect_options  */
  YYSYMBOL_filter_phase_helo_options = 202, /* filter_phase_helo_options  */
  YYSYMBOL_filter_phase_auth_options = 203, /* filter_phase_auth_options  */
  YYSYMBOL_filter_phase_mail_from_options = 204, /* filter_phase_mail_from_options  */
  YYSYMBOL_filter_phase_rcpt_to_options = 205, /* filter_phase_rcpt_to_options  */
  YYSYMBOL_filter_phase_data_options = 206, /* filter_phase_data_options  */
  YYSYMBOL_filter_phase_commit_options = 207, /* filter_phase_commit_options  */
  YYSYMBOL_filter_phase_connect = 208,     /* filter_phase_connect  */
  YYSYMBOL_209_20 = 209,                   /* $@20  */
  YYSYMBOL_filter_phase_helo = 210,        /* filter_phase_helo  */
  YYSYMBOL_211_21 = 211,                   /* $@21  */
  YYSYMBOL_filter_phase_ehlo = 212,        /* filter_phase_ehlo  */
  YYSYMBOL_213_22 = 213,                   /* $@22  */
  YYSYMBOL_filter_phase_auth = 214,        /* filter_phase_auth  */
  YYSYMBOL_215_23 = 215,                   /* $@23  */
  YYSYMBOL_filter_phase_mail_from = 216,   /* filter_phase_mail_from  */
  YYSYMBOL_217_24 = 217,                   /* $@24  */
  YYSYMBOL_filter_phase_rcpt_to = 218,     /* filter_phase_rcpt_to  */
  YYSYMBOL_219_25 = 219,                   /* $@25  */
  YYSYMBOL_filter_phase_data = 220,        /* filter_phase_data  */
  YYSYMBOL_221_26 = 221,                   /* $@26  */
  YYSYMBOL_filter_phase_commit = 222,      /* filter_phase_commit  */
  YYSYMBOL_223_27 = 223,                   /* $@27  */
  YYSYMBOL_filter_phase = 224,             /* filter_phase  */
  YYSYMBOL_filterel = 225,                 /* filterel  */
  YYSYMBOL_filter_list = 226,              /* filter_list  */
  YYSYMBOL_filter = 227,                   /* filter  */
  YYSYMBOL_228_28 = 228,                   /* $@28  */
  YYSYMBOL_229_29 = 229,                   /* $@29  */
  YYSYMBOL_230_30 = 230,                   /* $@30  */
  YYSYMBOL_size = 231,                     /* size  */
  YYSYMBOL_bouncedelay = 232,              /* bouncedelay  */
  YYSYMBOL_bouncedelays = 233,             /* bouncedelays  */
  YYSYMBOL_opt_limit_mda = 234,            /* opt_limit_mda  */
  YYSYMBOL_limits_smtp = 235,              /* limits_smtp  */
  YYSYMBOL_opt_limit_smtp = 236,           /* opt_limit_smtp  */
  YYSYMBOL_limits_mda = 237,               /* limits_mda  */
  YYSYMBOL_opt_limit_mta = 238,            /* opt_limit_mta  */
  YYSYMBOL_limits_mta = 239,               /* limits_mta  */
  YYSYMBOL_opt_limit_scheduler = 240,      /* opt_limit_scheduler  */
  YYSYMBOL_limits_scheduler = 241,         /* limits_scheduler  */
  YYSYMBOL_opt_sock_listen = 242,          /* opt_sock_listen  */
  YYSYMBOL_243_31 = 243,                   /* $@31  */
  YYSYMBOL_opt_if_listen = 244,            /* opt_if_listen  */
  YYSYMBOL_245_32 = 245,                   /* $@32  */
  YYSYMBOL_listener_type = 246,            /* listener_type  */
  YYSYMBOL_socket_listener = 247,          /* socket_listener  */
  YYSYMBOL_if_listener = 248,              /* if_listener  */
  YYSYMBOL_sock_listen = 249,              /* sock_listen  */
  YYSYMBOL_if_listen = 250,                /* if_listen  */
  YYSYMBOL_listen = 251,                   /* listen  */
  YYSYMBOL_252_33 = 252,                   /* $@33  */
  YYSYMBOL_table = 253,                    /* table  */
  YYSYMBOL_254_34 = 254,                   /* $@34  */
  YYSYMBOL_tablenew = 255,                 /* tablenew  */
  YYSYMBOL_256_35 = 256,                   /* $@35  */
  YYSYMBOL_tableref = 257,                 /* tableref  */
  YYSYMBOL_tables = 258                    /* tables  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   522

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  141
/* YYNRULES -- Number of rules.  */
#define YYNRULES  358
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  584

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   364


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     110,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   113,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   112,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     116,   111,   117,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   114,     2,   115,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   201,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   224,   239,   257,   258,   259,   262,   263,
     266,   269,   270,   273,   273,   276,   283,   284,   287,   293,
     294,   297,   298,   302,   302,   309,   324,   324,   348,   354,
     359,   360,   371,   374,   374,   386,   386,   393,   393,   416,
     419,   422,   440,   441,   446,   446,   465,   473,   481,   489,
     514,   515,   520,   523,   526,   535,   548,   553,   554,   557,
     560,   576,   579,   582,   602,   625,   646,   667,   683,   693,
     694,   698,   698,   701,   701,   704,   704,   707,   707,   715,
     715,   723,   723,   727,   727,   731,   731,   735,   735,   738,
     738,   745,   753,   768,   776,   784,   792,   800,   816,   824,
     837,   849,   869,   890,   899,   907,   928,   944,   944,   967,
     982,   983,   987,   991,   994,  1000,  1017,  1018,  1022,  1022,
    1038,  1056,  1075,  1092,  1110,  1117,  1124,  1141,  1159,  1176,
    1194,  1211,  1230,  1238,  1248,  1258,  1275,  1293,  1301,  1319,
    1339,  1351,  1371,  1393,  1413,  1435,  1445,  1455,  1472,  1490,
    1510,  1534,  1535,  1539,  1549,  1552,  1556,  1556,  1573,  1574,
    1577,  1583,  1586,  1589,  1592,  1598,  1605,  1612,  1618,  1625,
    1631,  1638,  1644,  1651,  1657,  1663,  1670,  1676,  1683,  1689,
    1696,  1697,  1698,  1699,  1700,  1701,  1704,  1707,  1708,  1709,
    1712,  1713,  1714,  1715,  1716,  1717,  1720,  1721,  1722,  1723,
    1724,  1725,  1726,  1727,  1730,  1731,  1732,  1733,  1734,  1735,
    1736,  1737,  1738,  1739,  1742,  1743,  1744,  1745,  1746,  1747,
    1748,  1749,  1769,  1770,  1771,  1772,  1773,  1774,  1775,  1776,
    1780,  1780,  1787,  1787,  1793,  1793,  1799,  1799,  1804,  1804,
    1810,  1810,  1816,  1816,  1848,  1848,  1856,  1857,  1858,  1859,
    1860,  1861,  1862,  1867,  1872,  1914,  1915,  1919,  1941,  1941,
    1965,  1965,  1979,  1979,  1994,  2001,  2014,  2034,  2035,  2038,
    2063,  2064,  2067,  2089,  2090,  2093,  2096,  2099,  2109,  2110,
    2113,  2135,  2136,  2140,  2157,  2157,  2179,  2184,  2192,  2208,
    2216,  2224,  2242,  2258,  2274,  2287,  2303,  2303,  2325,  2333,
    2341,  2349,  2357,  2365,  2372,  2379,  2386,  2394,  2402,  2410,
    2419,  2428,  2442,  2451,  2467,  2472,  2480,  2488,  2496,  2512,
    2530,  2531,  2534,  2543,  2549,  2550,  2553,  2554,  2558,  2558,
    2569,  2607,  2607,  2615,  2623,  2623,  2631,  2644,  2645
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ACTION", "ADMD",
  "ALIAS", "ANY", "ARROW", "AUTH", "AUTH_OPTIONAL", "BACKUP", "BOUNCE",
  "BYPASS", "CA", "CERT", "CHAIN", "CHROOT", "CIPHERS", "COMMIT",
  "COMPRESSION", "CONNECT", "DATA", "DATA_LINE", "DHE", "DISCONNECT",
  "DOMAIN", "EHLO", "ENABLE", "ENCRYPTION", "ERROR", "EXPAND_ONLY",
  "FCRDNS", "FILTER", "FOR", "FORWARD_ONLY", "FROM", "GROUP", "HELO",
  "HELO_SRC", "HOST", "HOSTNAME", "HOSTNAMES", "INCLUDE", "INET4", "INET6",
  "JUNK", "KEY", "LIMIT", "LISTEN", "LMTP", "LOCAL", "MAIL_FROM",
  "MAILDIR", "MASK_SRC", "MASQUERADE", "MATCH", "MAX_MESSAGE_SIZE",
  "MAX_DEFERRED", "MBOX", "MDA", "MTA", "MX", "NO_DSN", "NO_VERIFY",
  "NOOP", "ON", "PHASE", "PKI", "PORT", "PROC", "PROC_EXEC", "PROTOCOLS",
  "PROXY_V2", "QUEUE", "QUIT", "RCPT_TO", "RDNS", "RECIPIENT",
  "RECEIVEDAUTH", "REGEX", "RELAY", "REJECT", "REPORT", "REWRITE", "RSET",
  "SCHEDULER", "SENDER", "SENDERS", "SMTP", "SMTP_IN", "SMTP_OUT", "SMTPS",
  "SOCKET", "SRC", "SRS", "SUB_ADDR_DELIM", "TABLE", "TAG", "TAGGED",
  "TLS", "TLS_REQUIRE", "TTL", "USER", "USERBASE", "VERIFY", "VIRTUAL",
  "WARN_INTERVAL", "WRAPPER", "STRING", "NUMBER", "'\\n'", "'='", "','",
  "'!'", "'{'", "'}'", "'<'", "'>'", "$accept", "grammar", "include",
  "varset", "comma", "optnl", "nl", "negation", "assign", "keyval",
  "keyval_list", "stringel", "string_list", "tableval_list", "bounce",
  "$@1", "admd", "ca", "$@2", "ca_params_opt", "ca_params", "mda", "mta",
  "$@3", "$@4", "pki", "$@5", "pki_params_opt", "pki_params", "proc",
  "$@6", "proc_params_opt", "proc_params", "queue", "scheduler", "smtp",
  "srs", "dispatcher_local_option", "dispatcher_local_options",
  "dispatcher_local", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13",
  "$@14", "$@15", "$@16", "dispatcher_remote_option", "$@17",
  "dispatcher_remote_options", "dispatcher_remote", "dispatcher_type",
  "dispatcher_option", "dispatcher_options", "dispatcher", "$@18",
  "match_option", "match_options", "match_dispatcher", "action", "match",
  "$@19", "filter_action_builtin", "filter_action_builtin_nojunk",
  "filter_phase_check_fcrdns", "filter_phase_check_rdns",
  "filter_phase_check_rdns_table", "filter_phase_check_rdns_regex",
  "filter_phase_check_src_table", "filter_phase_check_src_regex",
  "filter_phase_check_helo_table", "filter_phase_check_helo_regex",
  "filter_phase_check_auth", "filter_phase_check_auth_table",
  "filter_phase_check_auth_regex", "filter_phase_check_mail_from_table",
  "filter_phase_check_mail_from_regex", "filter_phase_check_rcpt_to_table",
  "filter_phase_check_rcpt_to_regex", "filter_phase_global_options",
  "filter_phase_connect_options", "filter_phase_helo_options",
  "filter_phase_auth_options", "filter_phase_mail_from_options",
  "filter_phase_rcpt_to_options", "filter_phase_data_options",
  "filter_phase_commit_options", "filter_phase_connect", "$@20",
  "filter_phase_helo", "$@21", "filter_phase_ehlo", "$@22",
  "filter_phase_auth", "$@23", "filter_phase_mail_from", "$@24",
  "filter_phase_rcpt_to", "$@25", "filter_phase_data", "$@26",
  "filter_phase_commit", "$@27", "filter_phase", "filterel", "filter_list",
  "filter", "$@28", "$@29", "$@30", "size", "bouncedelay", "bouncedelays",
  "opt_limit_mda", "limits_smtp", "opt_limit_smtp", "limits_mda",
  "opt_limit_mta", "limits_mta", "opt_limit_scheduler", "limits_scheduler",
  "opt_sock_listen", "$@31", "opt_if_listen", "$@32", "listener_type",
  "socket_listener", "if_listener", "sock_listen", "if_listen", "listen",
  "$@33", "table", "$@34", "tablenew", "$@35", "tableref", "tables", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-385)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-173)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -385,    21,  -385,   -83,   -73,   -68,   -58,   -57,   -53,   -43,
    -385,  -385,   -34,    10,   -42,   -38,    -9,    25,     0,    56,
     -19,    50,  -385,    57,    59,    70,    72,    74,    76,    94,
      95,   101,   106,   107,   108,   124,   129,   132,   138,   150,
     152,  -385,  -385,  -385,  -385,  -385,   137,  -385,   199,     6,
     159,   171,   250,   182,  -385,   184,  -385,   193,   203,   207,
     209,   220,   -48,   226,    -3,   231,   234,   240,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,   255,   244,   339,  -385,
    -385,   246,   252,   -64,  -385,    63,     6,    23,   263,   159,
    -385,   256,   277,   104,  -385,    29,  -385,  -385,  -385,   265,
     207,  -385,  -385,   269,  -385,   220,  -385,  -385,  -385,  -385,
     271,  -385,  -385,  -385,   267,  -385,  -385,  -385,   278,     4,
    -385,   280,   162,  -385,  -385,   290,  -385,  -385,   295,   291,
    -385,  -385,   300,   245,  -385,  -385,   112,   206,  -385,  -385,
    -385,   172,     8,   105,   202,   211,   215,   216,  -385,  -385,
     301,  -385,  -385,  -385,  -385,  -385,   307,  -385,  -385,   308,
     104,  -385,   311,   313,   314,    29,  -385,    48,  -385,  -385,
    -385,  -385,  -385,   306,    32,    32,   352,  -385,   383,    32,
      32,  -385,   -85,   372,   327,   328,   -85,   333,   335,   -85,
     -85,   336,   340,   342,   -85,  -385,   388,   162,  -385,   346,
     290,  -385,   244,  -385,   306,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,    48,   347,  -385,  -385,   349,   112,  -385,   -85,
     -85,   351,   355,   356,   357,   -85,  -385,  -385,  -385,  -385,
     358,    80,   359,  -385,  -385,   -85,   364,   361,  -385,   366,
     206,  -385,   -85,  -385,   306,   363,  -385,  -385,  -385,  -385,
     229,  -385,   230,  -385,   233,  -385,   242,   243,  -385,   247,
     -85,  -385,   -85,  -385,   -85,  -385,   -85,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,   365,   367,   368,
     369,    48,  -385,   306,   370,   -85,   371,   -85,   -85,   373,
      32,  -385,  -385,  -385,    32,    32,  -385,    32,  -385,  -385,
      32,  -385,   374,  -385,  -385,  -385,  -385,   360,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
     375,   405,   417,   425,   429,   430,   431,   432,   433,  -385,
    -385,   376,  -385,  -385,  -385,  -385,  -385,  -385,  -385,   377,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,   435,  -385,
    -385,  -385,  -385,  -385,  -385,   378,   -85,  -385,   -85,  -385,
     -85,  -385,   -85,  -385,   -85,  -385,   -85,  -385,  -385,  -385,
    -385,  -385,   104,  -385,  -385,  -385,  -385,  -385,  -385,    -1,
      81,  -385,    81,  -385,   379,  -385,  -385,  -385,  -385,  -385,
    -385,    32,  -385,  -385,    32,  -385,  -385,  -385,   306,  -385,
      81,   381,   380,   380,   380,   380,   380,   380,   380,   380,
     306,   306,  -385,   370,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,   384,   306,   306,   389,  -385,  -385,
     390,  -385,  -385,  -385,  -385,   375,   375,  -385,  -385,    66,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,    -4,    31,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,   217,   102,  -385,    -4,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,    -4,    90,  -385,  -385,  -385,    -4,
      -4,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,    -4,
     194,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,    -4,   375,   375,   385,  -385,   391,  -385,    -1,  -385,
    -385,  -385,   386,  -385,   254,  -385,   257,   261,   287,  -385,
     394,  -385,   395,   396,   397,  -385,  -385,   288,  -385,  -385,
    -385,  -385,  -385,  -385,   297,  -385,   392,   393,  -385,  -385,
     -85,  -385,   -85,  -385,   -85,  -385,   -85,  -385,  -385,  -385,
    -385,  -385,   -85,  -385,   -85,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
     348,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,   138,    45,    43,    46,     0,    23,     0,    32,
     294,     0,    55,     0,    57,     0,    72,    73,     0,   302,
       0,   291,     0,     0,     0,     0,   351,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    19,    20,    21,    17,    18,     0,     0,     0,   282,
     280,     0,     0,     0,    31,     0,    32,     0,     0,   294,
      50,     0,     0,   299,    52,    63,    64,    74,    75,     0,
     302,    76,    78,     0,    77,   291,   285,   284,    79,    80,
       0,    81,    83,   350,     0,    24,   109,   107,     0,    93,
      91,     0,   131,   133,   134,   137,   286,   288,    44,     0,
      49,    47,     0,     0,   277,   278,   345,   347,   349,   340,
     341,   145,     0,     0,     0,     0,     0,     0,   144,   171,
       0,   174,   177,   289,   293,    51,     0,   295,   296,     0,
     299,    56,     0,     0,     0,    63,    58,    71,   300,   301,
     292,   290,    82,    29,    90,    90,   101,    95,    97,    90,
      90,   105,     0,   120,     0,     0,     0,   127,     0,     0,
       0,     0,     0,     0,     0,   129,   123,   131,   132,     0,
     137,   139,     0,    48,    29,   256,   264,   250,   262,   254,
     252,   258,   260,   266,   267,   268,   269,   270,   271,   272,
     273,   281,    71,   304,   306,   307,     0,   345,   342,   327,
     328,     0,     0,   316,     0,     0,   309,   310,   334,   336,
       0,     0,     0,   337,   335,     0,   318,     0,   320,   321,
     347,   343,     0,   353,    29,     0,   357,   358,   146,   166,
       0,   165,     0,   154,   160,   153,     0,   157,   152,     0,
       0,   142,     0,   148,     0,   150,     0,   140,   173,   175,
      53,   297,   298,    59,    61,    60,    62,     0,     0,     0,
       0,    71,    65,    29,     0,     0,     0,     0,     0,     0,
      90,   110,   108,   103,    90,    90,    99,    90,    94,    92,
      90,   125,     0,   114,   115,   122,   126,     0,   111,   112,
     121,   118,   113,   116,   117,   124,   130,   135,   136,   287,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   279,
     303,     0,   308,   344,   329,   330,   326,   323,   315,     0,
     332,   333,   325,   312,   313,   311,   314,   324,   338,   319,
     331,   322,   346,   147,   354,     0,     0,   167,     0,   169,
       0,   161,     0,   163,     0,   158,     0,   155,   143,   149,
     151,   141,   299,    68,    67,    69,    66,    70,    28,    38,
      27,    42,    27,    41,     0,    85,    84,    87,    86,    88,
      89,    90,   102,    96,    90,    98,   106,   119,    29,   274,
      27,     0,    32,    32,    32,    32,    32,    32,    32,    32,
      29,    29,   339,     0,   356,   168,   170,   162,   164,   159,
     156,    54,    34,    33,     0,    29,    29,     0,    36,    26,
       0,    39,   352,   104,   100,     0,     0,   275,   283,     0,
     200,   201,   203,   202,   205,   204,   210,   211,   212,   213,
     214,   215,     0,     0,   242,   243,   244,   245,   246,   247,
     248,   249,     0,     0,   206,     0,   234,   235,   236,   237,
     238,   239,   240,   241,     0,     0,   207,   208,   209,     0,
       0,   216,   217,   218,   219,   220,   221,   222,   223,     0,
       0,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,     0,     0,     0,     0,    35,    28,    25,     0,    37,
      38,    40,     0,   276,   193,   185,     0,   186,     0,   180,
       0,   179,     0,     0,     0,   257,   178,     0,   265,   251,
     263,   255,   253,   259,     0,   261,     0,     0,   355,   128,
       0,   194,     0,   191,     0,   187,     0,   189,   182,   181,
     184,   183,     0,   196,     0,   198,   305,   317,   195,   192,
     188,   190,   197,   199
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -385,  -385,  -385,  -385,  -384,  -210,  -385,   -37,  -385,  -385,
      62,  -385,    60,    73,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,   337,  -385,
    -385,  -385,  -202,  -385,  -385,  -385,  -385,  -385,  -174,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,   304,  -385,  -385,  -385,   303,  -385,  -385,  -385,
     418,  -385,  -385,  -385,  -385,  -336,    34,  -385,  -385,  -385,
    -385,  -385,  -385,     9,    17,  -171,    24,    33,  -153,   -31,
    -385,  -385,     1,  -385,    88,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,  -385,  -385,  -385,  -385,  -385,  -385,  -385,  -279,  -385,
    -385,  -385,  -385,  -385,   305,  -385,  -385,   403,  -385,   420,
    -385,  -165,  -385,   410,  -385,  -385,  -385,  -385,  -385,  -385,
    -385,   284,   262,  -385,  -385,  -385,  -385,  -385,  -385,  -385,
    -154
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    23,    24,   447,   304,   449,   473,   444,   400,
     401,   402,   403,   404,    25,    87,    26,    27,    88,   140,
     141,    28,    29,   392,   103,    30,   105,   175,   176,    31,
     177,   301,   302,    32,    33,    34,    35,   310,   311,   133,
     190,   189,   315,   317,   414,   314,   411,   320,   185,   184,
     207,   327,   208,   134,   135,   210,   211,    36,    86,    96,
      97,   289,   162,    37,    49,   545,   546,   460,   461,   462,
     463,   464,   465,   496,   497,   468,   469,   470,   479,   480,
     518,   519,   498,   485,   499,   472,   509,   521,   494,   482,
     223,   343,   224,   346,   225,   345,   226,   341,   227,   347,
     228,   348,   229,   344,   230,   342,   231,   420,   421,    38,
     232,   143,   142,   118,   137,   138,    99,   114,   115,   100,
     170,   171,   110,   111,   237,   351,   260,   359,   148,   149,
     150,   238,   261,    39,    48,    40,   124,   266,   433,   267,
     268
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     281,   283,   285,   287,   340,   292,   442,   120,   539,  -172,
      56,   312,    95,    50,   269,   318,   319,    60,   450,    57,
     540,     2,     3,   263,     4,     5,   160,    41,   146,   264,
     349,   265,     6,   270,     7,    42,   456,   305,   321,   534,
      43,   541,   325,   172,   147,   329,   330,    61,    44,   187,
     334,    45,   173,     8,   374,    46,    62,    52,   271,    95,
     116,   117,   535,     9,   297,    47,    54,    53,   536,    10,
      55,   151,    59,    51,   534,   174,    11,   542,   543,   544,
      12,    13,   547,   272,   298,   354,   355,  -172,    14,    66,
      15,   361,    58,   398,    16,    63,   152,   535,   153,   397,
     154,   368,    64,   536,   161,   121,    17,   537,   373,    18,
     443,   273,   188,   274,   155,    19,   377,    20,   379,    94,
     381,   535,   383,   385,   538,   387,   388,   536,   389,    21,
     390,    22,   391,   535,   306,   307,   410,   308,   156,   309,
     412,   413,   537,   415,   233,   299,   416,   167,   168,   549,
     300,   405,    89,   407,   408,   275,   276,    65,   550,   538,
     157,    67,   158,   551,   552,   234,   537,    68,   363,    69,
     192,   364,   193,   553,   235,   194,   532,   533,   537,   195,
      70,   277,    71,   538,    72,   555,    73,   196,   365,   366,
     448,   445,   451,   446,   197,   538,   -29,   278,   279,   198,
     199,   200,   534,    90,    74,    75,    91,    92,   455,   236,
     457,    76,   169,   201,   239,   240,    77,    78,    79,   241,
     522,   523,   435,   242,   436,   535,   437,   441,   438,   202,
     439,   536,   440,   203,    80,   526,   527,   453,   243,    81,
     454,   540,    82,   556,   557,   547,   244,   245,    83,   246,
     247,   262,   476,   215,   488,   204,   205,   503,   513,   248,
      84,   206,    85,   216,    93,   217,   218,    98,   249,   554,
     537,   219,   491,   250,   251,   506,   516,   252,   253,   101,
     263,   280,   220,   102,   254,   126,   264,   538,   265,   127,
     282,   104,   106,   255,   284,   286,   221,   256,   542,   543,
     544,   107,   166,   257,   128,   258,   259,   129,   376,   378,
     263,   108,   380,   130,   131,   109,   264,   112,   265,   263,
     222,   382,   384,   263,   263,   264,   386,   265,   113,   264,
     264,   265,   265,   560,   119,   132,   562,   263,   263,   122,
     564,   263,   123,   264,   264,   265,   265,   264,   125,   265,
     263,   263,   136,   139,   144,   263,   264,   264,   265,   265,
     145,   264,   263,   265,   165,   263,   566,   572,   264,   263,
     265,   264,   163,   265,   178,   264,   574,   265,   180,   182,
     561,   183,   563,   565,   567,   459,   186,   483,   191,   495,
     495,   209,   510,   573,   492,   263,   263,   507,   517,   213,
     575,   264,   264,   265,   265,   263,   578,   212,   579,   288,
     580,   264,   581,   265,   214,   290,   303,   291,   582,   293,
     583,   294,   295,   471,   481,   484,   493,   313,   316,   508,
     520,   466,   474,   322,   486,   323,   324,   501,   511,   467,
     475,   326,   487,   328,   331,   502,   512,   477,   332,   489,
     333,   335,   504,   514,   337,   350,   478,   352,   490,   356,
     422,   505,   515,   357,   358,   360,   362,   367,   369,   370,
     371,   375,   423,   393,   418,   394,   395,   396,   399,   406,
     424,   409,   417,   419,   425,   426,   427,   428,   429,   432,
     430,   431,   525,    94,   452,   434,   458,   528,   530,   -30,
     558,   559,   568,   569,   570,   571,   524,   576,   577,   529,
     531,   336,   296,   338,   159,   500,   548,   339,   181,   164,
     179,   353,   372
};

static const yytype_int16 yycheck[] =
{
     154,   155,   156,   157,   214,   170,     7,    10,    12,     3,
      19,   185,    49,    47,     6,   189,   190,    17,   402,    28,
      24,     0,     1,   108,     3,     4,     3,   110,    92,   114,
     232,   116,    11,    25,    13,   108,   420,     5,   192,     8,
     108,    45,   196,    14,   108,   199,   200,    47,   106,    45,
     204,   108,    23,    32,   264,   108,    56,    47,    50,    96,
     108,   109,    31,    42,    16,   108,   108,    57,    37,    48,
     108,     8,    47,   107,     8,    46,    55,    81,    82,    83,
      59,    60,    51,    75,    36,   239,   240,    81,    67,   108,
      69,   245,   101,   303,    73,    95,    33,    31,    35,   301,
      37,   255,    46,    37,    81,   108,    85,    76,   262,    88,
     111,     6,   108,     8,    51,    94,   270,    96,   272,   113,
     274,    31,   276,   277,    93,   279,   280,    37,   282,   108,
     284,   110,   286,    31,   102,   103,   310,   105,    75,   107,
     314,   315,    76,   317,    32,    97,   320,    43,    44,   485,
     102,   305,    15,   307,   308,    50,    51,   101,   494,    93,
      97,   111,    99,   499,   500,    53,    76,   110,    88,   110,
       8,    91,    10,   509,    62,    13,   455,   456,    76,    17,
     110,    76,   110,    93,   110,   521,   110,    25,   108,   109,
     400,   110,   402,   112,    32,    93,   115,    92,    93,    37,
      38,    39,     8,    66,   110,   110,    69,    70,   418,    97,
     420,   110,   108,    51,     8,     9,   110,   110,   110,    13,
     430,   431,   376,    17,   378,    31,   380,   392,   382,    67,
     384,    37,   386,    71,   110,   445,   446,   411,    32,   110,
     414,    24,   110,   522,   523,    51,    40,    41,   110,    43,
      44,    79,   423,     8,   425,    93,    94,   428,   429,    53,
     110,    99,   110,    18,    65,    20,    21,   108,    62,    75,
      76,    26,   425,    67,    68,   428,   429,    71,    72,   108,
     108,    79,    37,    33,    78,    30,   114,    93,   116,    34,
      79,   109,   108,    87,    79,    79,    51,    91,    81,    82,
      83,   108,    25,    97,    49,    99,   100,    52,    79,    79,
     108,   108,    79,    58,    59,   108,   114,   108,   116,   108,
      75,    79,    79,   108,   108,   114,    79,   116,   108,   114,
     114,   116,   116,    79,   108,    80,    79,   108,   108,   108,
      79,   108,   108,   114,   114,   116,   116,   114,   108,   116,
     108,   108,   108,    14,   108,   108,   114,   114,   116,   116,
     108,   114,   108,   116,   108,   108,    79,    79,   114,   108,
     116,   114,   109,   116,   109,   114,    79,   116,   109,   108,
     534,   114,   536,   537,   538,   422,   108,   424,   108,   426,
     427,   101,   429,   547,   425,   108,   108,   428,   429,   108,
     554,   114,   114,   116,   116,   108,   560,   112,   562,   108,
     564,   114,   566,   116,   114,   108,   110,   109,   572,   108,
     574,   108,   108,   422,   423,   424,   425,    75,    45,   428,
     429,   422,   423,    61,   425,   108,   108,   428,   429,   422,
     423,   108,   425,   108,   108,   428,   429,   423,   108,   425,
     108,    63,   428,   429,   108,   108,   423,   108,   425,   108,
      55,   428,   429,   108,   108,   108,   108,   108,   104,   108,
     104,   108,    55,   108,   114,   108,   108,   108,   108,   108,
      55,   108,   108,   108,    55,    55,    55,    55,    55,    54,
     114,   114,   108,   113,   115,   117,   115,   108,   108,   108,
     115,   115,   108,   108,   108,   108,   433,   115,   115,   447,
     450,   207,   175,   210,    96,   427,   482,   212,   115,    99,
     110,   237,   260
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   119,     0,     1,     3,     4,    11,    13,    32,    42,
      48,    55,    59,    60,    67,    69,    73,    85,    88,    94,
      96,   108,   110,   120,   121,   132,   134,   135,   139,   140,
     143,   147,   151,   152,   153,   154,   175,   181,   227,   251,
     253,   110,   108,   108,   106,   108,   108,   108,   252,   182,
      47,   107,    47,    57,   108,   108,    19,    28,   101,    47,
      17,    47,    56,    95,    46,   101,   108,   111,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   176,   133,   136,    15,
      66,    69,    70,    65,   113,   125,   177,   178,   108,   234,
     237,   108,    33,   142,   109,   144,   108,   108,   108,   108,
     240,   241,   108,   108,   235,   236,   108,   109,   231,   108,
      10,   108,   108,   108,   254,   108,    30,    34,    49,    52,
      58,    59,    80,   157,   171,   172,   108,   232,   233,    14,
     137,   138,   230,   229,   108,   108,    92,   108,   246,   247,
     248,     8,    33,    35,    37,    51,    75,    97,    99,   178,
       3,    81,   180,   109,   237,   108,    25,    43,    44,   108,
     238,   239,    14,    23,    46,   145,   146,   148,   109,   241,
     109,   235,   108,   114,   167,   166,   108,    45,   108,   159,
     158,   108,     8,    10,    13,    17,    25,    32,    37,    38,
      39,    51,    67,    71,    93,    94,    99,   168,   170,   101,
     173,   174,   112,   108,   114,     8,    18,    20,    21,    26,
      37,    51,    75,   208,   210,   212,   214,   216,   218,   220,
     222,   224,   228,    32,    53,    62,    97,   242,   249,     8,
       9,    13,    17,    32,    40,    41,    43,    44,    53,    62,
      67,    68,    71,    72,    78,    87,    91,    97,    99,   100,
     244,   250,    79,   108,   114,   116,   255,   257,   258,     6,
      25,    50,    75,     6,     8,    50,    51,    76,    92,    93,
      79,   258,    79,   258,    79,   258,    79,   258,   108,   179,
     108,   109,   239,   108,   108,   108,   146,    16,    36,    97,
     102,   149,   150,   110,   123,     5,   102,   103,   105,   107,
     155,   156,   156,    75,   163,   160,    45,   161,   156,   156,
     165,   258,    61,   108,   108,   258,   108,   169,   108,   258,
     258,   108,   108,   108,   258,    63,   170,   108,   174,   232,
     123,   215,   223,   209,   221,   213,   211,   217,   219,   150,
     108,   243,   108,   249,   258,   258,   108,   108,   108,   245,
     108,   258,   108,    88,    91,   108,   109,   108,   258,   104,
     108,   104,   250,   258,   123,   108,    79,   258,    79,   258,
      79,   258,    79,   258,    79,   258,    79,   258,   258,   258,
     258,   258,   141,   108,   108,   108,   108,   150,   123,   108,
     127,   128,   129,   130,   131,   258,   108,   258,   258,   108,
     156,   164,   156,   156,   162,   156,   156,   108,   114,   108,
     225,   226,    55,    55,    55,    55,    55,    55,    55,    55,
     114,   114,    54,   256,   117,   258,   258,   258,   258,   258,
     258,   239,     7,   111,   126,   110,   112,   122,   123,   124,
     122,   123,   115,   156,   156,   123,   122,   123,   115,   125,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   200,   203,   125,   191,   192,   193,   194,   195,   196,
     197,   200,   207,   125,   200,   201,   191,   192,   193,   194,
     195,   196,   197,   200,   206,   125,   191,   192,   200,   202,
     202,   191,   192,   193,   194,   195,   196,   197,   200,   204,
     125,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   205,   123,   123,   131,   108,   123,   123,   108,   128,
     108,   130,   226,   226,     8,    31,    37,    76,    93,    12,
      24,    45,    81,    82,    83,   183,   184,    51,   184,   183,
     183,   183,   183,   183,    75,   183,   226,   226,   115,   115,
      79,   258,    79,   258,    79,   258,    79,   258,   108,   108,
     108,   108,    79,   258,    79,   258,   115,   115,   258,   258,
     258,   258,   258,   258
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   118,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   121,   122,   122,   122,   123,   123,
     124,   125,   125,   126,   126,   127,   128,   128,   129,   130,
     130,   131,   131,   133,   132,   134,   136,   135,   137,   138,
     139,   139,   140,   141,   140,   142,   140,   144,   143,   145,
     145,   145,   146,   146,   148,   147,   149,   149,   149,   149,
     150,   150,   151,   151,   151,   151,   152,   153,   153,   153,
     153,   154,   154,   154,   155,   155,   155,   155,   155,   156,
     156,   158,   157,   159,   157,   160,   157,   161,   157,   162,
     157,   163,   157,   164,   157,   165,   157,   166,   157,   167,
     157,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   169,   168,   168,
     170,   170,   171,   172,   172,   173,   174,   174,   176,   175,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   178,   178,   179,   180,   180,   182,   181,   183,   183,
     183,   184,   184,   184,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   200,   200,   200,   200,   200,   201,   202,   202,   202,
     203,   203,   203,   203,   203,   203,   204,   204,   204,   204,
     204,   204,   204,   204,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   206,   206,   206,   206,   206,   206,
     206,   206,   207,   207,   207,   207,   207,   207,   207,   207,
     209,   208,   211,   210,   213,   212,   215,   214,   217,   216,
     219,   218,   221,   220,   223,   222,   224,   224,   224,   224,
     224,   224,   224,   224,   225,   226,   226,   227,   228,   227,
     229,   227,   230,   227,   231,   231,   232,   233,   233,   234,
     235,   235,   236,   237,   237,   238,   238,   238,   239,   239,
     240,   241,   241,   242,   243,   242,   242,   242,   242,   244,
     244,   244,   244,   244,   244,   244,   245,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     246,   246,   247,   248,   249,   249,   250,   250,   252,   251,
     253,   254,   253,   255,   256,   255,   257,   258,   258
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     2,     1,     0,     2,     0,
       2,     1,     0,     1,     1,     3,     2,     3,     1,     2,
       3,     1,     1,     0,     4,     2,     0,     4,     2,     1,
       3,     4,     3,     0,     7,     0,     4,     0,     4,     2,
       2,     2,     2,     0,     0,     5,     2,     2,     2,     2,
       2,     0,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     2,     2,     2,     2,     2,     2,
       0,     0,     3,     0,     3,     0,     4,     0,     4,     0,
       5,     0,     4,     0,     5,     0,     4,     0,     3,     0,
       3,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       1,     2,     2,     1,     2,     2,     2,     0,     6,     1,
       2,     0,     2,     1,     1,     2,     2,     0,     0,     5,
       3,     4,     3,     4,     2,     2,     3,     4,     3,     4,
       3,     4,     3,     3,     3,     4,     5,     3,     4,     5,
       3,     4,     5,     4,     5,     3,     3,     4,     5,     4,
       5,     2,     0,     1,     1,     2,     0,     4,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     3,     4,     3,
       4,     3,     4,     2,     3,     4,     3,     4,     3,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     5,     0,     5,     0,     5,     0,     5,     0,     5,
       0,     5,     0,     5,     0,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     4,     0,     6,
       0,     5,     0,     8,     1,     1,     1,     3,     1,     2,
       2,     0,     2,     2,     0,     1,     1,     2,     2,     0,
       2,     2,     0,     2,     0,     6,     1,     1,     2,     1,
       1,     2,     2,     2,     2,     2,     0,     6,     1,     2,
       1,     1,     2,     2,     2,     2,     2,     1,     1,     2,
       2,     2,     2,     2,     1,     1,     1,     1,     2,     3,
       1,     1,     2,     2,     2,     0,     2,     0,     0,     4,
       3,     0,     7,     1,     0,     5,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 22: /* grammar: grammar error '\n'  */
#line 221 "parse.y"
                                                { file->errors++; }
#line 2170 "y.tab.c"
    break;

  case 23: /* include: INCLUDE STRING  */
#line 224 "parse.y"
                                                {
			struct file	*nfile;

			if ((nfile = pushfile((yyvsp[0].v.string), 0)) == NULL) {
				yyerror("failed to include file %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			file = nfile;
			lungetc('\n');
		}
#line 2188 "y.tab.c"
    break;

  case 24: /* varset: STRING '=' STRING  */
#line 239 "parse.y"
                                                {
			char *s = (yyvsp[-2].v.string);
			while (*s++) {
				if (isspace((unsigned char)*s)) {
					yyerror("macro name cannot contain "
					    "whitespace");
					free((yyvsp[-2].v.string));
					free((yyvsp[0].v.string));
					YYERROR;
				}
			}
			if (symset((yyvsp[-2].v.string), (yyvsp[0].v.string), 0) == -1)
				fatal("cannot store variable");
			free((yyvsp[-2].v.string));
			free((yyvsp[0].v.string));
		}
#line 2209 "y.tab.c"
    break;

  case 31: /* negation: '!'  */
#line 269 "parse.y"
                                { (yyval.v.number) = 1; }
#line 2215 "y.tab.c"
    break;

  case 32: /* negation: %empty  */
#line 270 "parse.y"
                                { (yyval.v.number) = 0; }
#line 2221 "y.tab.c"
    break;

  case 35: /* keyval: STRING assign STRING  */
#line 276 "parse.y"
                                                {
			table_add(table, (yyvsp[-2].v.string), (yyvsp[0].v.string));
			free((yyvsp[-2].v.string));
			free((yyvsp[0].v.string));
		}
#line 2231 "y.tab.c"
    break;

  case 38: /* stringel: STRING  */
#line 287 "parse.y"
                                                {
			table_add(table, (yyvsp[0].v.string), NULL);
			free((yyvsp[0].v.string));
		}
#line 2240 "y.tab.c"
    break;

  case 41: /* tableval_list: string_list  */
#line 297 "parse.y"
                                                { }
#line 2246 "y.tab.c"
    break;

  case 42: /* tableval_list: keyval_list  */
#line 298 "parse.y"
                                                { }
#line 2252 "y.tab.c"
    break;

  case 43: /* $@1: %empty  */
#line 302 "parse.y"
                     {
	memset(conf->sc_bounce_warn, 0, sizeof conf->sc_bounce_warn);
}
#line 2260 "y.tab.c"
    break;

  case 45: /* admd: ADMD STRING  */
#line 309 "parse.y"
            {
	size_t i;

	for (i = 0; (yyvsp[0].v.string)[i] != '\0'; i++) {
		if (!isprint((yyvsp[0].v.string)[i])) {
			yyerror("not a valid admd");
			free((yyvsp[0].v.string));
			YYERROR;
		}
	}
	conf->sc_admd = (yyvsp[0].v.string);
}
#line 2277 "y.tab.c"
    break;

  case 46: /* $@2: %empty  */
#line 324 "parse.y"
          {
	char buf[HOST_NAME_MAX+1];

	/* if not catchall, check that it is a valid domain */
	if (strcmp((yyvsp[0].v.string), "*") != 0) {
		if (!res_hnok((yyvsp[0].v.string))) {
			yyerror("not a valid domain name: %s", (yyvsp[0].v.string));
			free((yyvsp[0].v.string));
			YYERROR;
		}
	}
	xlowercase(buf, (yyvsp[0].v.string), sizeof(buf));
	free((yyvsp[0].v.string));
	sca = dict_get(conf->sc_ca_dict, buf);
	if (sca == NULL) {
		sca = xcalloc(1, sizeof *sca);
		(void)strlcpy(sca->ca_name, buf, sizeof(sca->ca_name));
		dict_set(conf->sc_ca_dict, sca->ca_name, sca);
	}
}
#line 2302 "y.tab.c"
    break;

  case 48: /* ca_params_opt: CERT STRING  */
#line 348 "parse.y"
            {
	sca->ca_cert_file = (yyvsp[0].v.string);
}
#line 2310 "y.tab.c"
    break;

  case 51: /* mda: MDA WRAPPER STRING STRING  */
#line 360 "parse.y"
                            {
	if (dict_get(conf->sc_mda_wrappers, (yyvsp[-1].v.string))) {
		yyerror("mda wrapper already declared with that name: %s", (yyvsp[-1].v.string));
		YYERROR;
	}
	dict_set(conf->sc_mda_wrappers, (yyvsp[-1].v.string), (yyvsp[0].v.string));
}
#line 2322 "y.tab.c"
    break;

  case 52: /* mta: MTA MAX_DEFERRED NUMBER  */
#line 371 "parse.y"
                         {
	conf->sc_mta_max_deferred = (yyvsp[0].v.number);
}
#line 2330 "y.tab.c"
    break;

  case 53: /* $@3: %empty  */
#line 374 "parse.y"
                              {
	struct mta_limits	*d;

	limits = dict_get(conf->sc_limits_dict, (yyvsp[0].v.string));
	if (limits == NULL) {
		limits = xcalloc(1, sizeof(*limits));
		dict_xset(conf->sc_limits_dict, (yyvsp[0].v.string), limits);
		d = dict_xget(conf->sc_limits_dict, "default");
		memmove(limits, d, sizeof(*limits));
	}
	free((yyvsp[0].v.string));
}
#line 2347 "y.tab.c"
    break;

  case 55: /* $@4: %empty  */
#line 386 "parse.y"
            {
	limits = dict_get(conf->sc_limits_dict, "default");
}
#line 2355 "y.tab.c"
    break;

  case 57: /* $@5: %empty  */
#line 393 "parse.y"
           {
	char buf[HOST_NAME_MAX+1];

	/* if not catchall, check that it is a valid domain */
	if (strcmp((yyvsp[0].v.string), "*") != 0) {
		if (!res_hnok((yyvsp[0].v.string))) {
			yyerror("not a valid domain name: %s", (yyvsp[0].v.string));
			free((yyvsp[0].v.string));
			YYERROR;
		}
	}
	xlowercase(buf, (yyvsp[0].v.string), sizeof(buf));
	free((yyvsp[0].v.string));
	pki = dict_get(conf->sc_pki_dict, buf);
	if (pki == NULL) {
		pki = xcalloc(1, sizeof *pki);
		(void)strlcpy(pki->pki_name, buf, sizeof(pki->pki_name));
		dict_set(conf->sc_pki_dict, pki->pki_name, pki);
	}
}
#line 2380 "y.tab.c"
    break;

  case 59: /* pki_params_opt: CERT STRING  */
#line 416 "parse.y"
            {
	pki->pki_cert_file = (yyvsp[0].v.string);
}
#line 2388 "y.tab.c"
    break;

  case 60: /* pki_params_opt: KEY STRING  */
#line 419 "parse.y"
             {
	pki->pki_key_file = (yyvsp[0].v.string);
}
#line 2396 "y.tab.c"
    break;

  case 61: /* pki_params_opt: DHE STRING  */
#line 422 "parse.y"
             {
	if (strcasecmp((yyvsp[0].v.string), "none") == 0)
		pki->pki_dhe = 0;
	else if (strcasecmp((yyvsp[0].v.string), "auto") == 0)
		pki->pki_dhe = 1;
	else if (strcasecmp((yyvsp[0].v.string), "legacy") == 0)
		pki->pki_dhe = 2;
	else {
		yyerror("invalid DHE keyword: %s", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	free((yyvsp[0].v.string));
}
#line 2415 "y.tab.c"
    break;

  case 64: /* $@6: %empty  */
#line 446 "parse.y"
                   {
	if (dict_get(conf->sc_filter_processes_dict, (yyvsp[-1].v.string))) {
		yyerror("processor already exists with that name: %s", (yyvsp[-1].v.string));
		free((yyvsp[-1].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	processor = xcalloc(1, sizeof *processor);
	processor->command = (yyvsp[0].v.string);
}
#line 2430 "y.tab.c"
    break;

  case 65: /* proc: PROC STRING STRING $@6 proc_params  */
#line 455 "parse.y"
              {
	if (!processor->tag)
		processor->tag = processor_maketag((yyvsp[-3].v.string));
	dict_set(conf->sc_filter_processes_dict, (yyvsp[-3].v.string), processor);
	processor = NULL;
}
#line 2441 "y.tab.c"
    break;

  case 66: /* proc_params_opt: USER STRING  */
#line 465 "parse.y"
            {
	if (processor->user) {
		yyerror("user already specified for this processor");
		free((yyvsp[0].v.string));
		YYERROR;
	}
	processor->user = (yyvsp[0].v.string);
}
#line 2454 "y.tab.c"
    break;

  case 67: /* proc_params_opt: GROUP STRING  */
#line 473 "parse.y"
               {
	if (processor->group) {
		yyerror("group already specified for this processor");
		free((yyvsp[0].v.string));
		YYERROR;
	}
	processor->group = (yyvsp[0].v.string);
}
#line 2467 "y.tab.c"
    break;

  case 68: /* proc_params_opt: CHROOT STRING  */
#line 481 "parse.y"
                {
	if (processor->chroot) {
		yyerror("chroot already specified for this processor");
		free((yyvsp[0].v.string));
		YYERROR;
	}
	processor->chroot = (yyvsp[0].v.string);
}
#line 2480 "y.tab.c"
    break;

  case 69: /* proc_params_opt: TAG STRING  */
#line 489 "parse.y"
             {
	size_t i;

	if (processor->tag) {
		yyerror("tag already specified for this processor");
		free((yyvsp[0].v.string));
		YYERROR;
	}
	for (i = 0; (yyvsp[0].v.string)[i] != '\0'; i++) {
		if (!isalpha((yyvsp[0].v.string)[i])) {
			yyerror("tag can only contain letters");
			free((yyvsp[0].v.string));
			YYERROR;
		}
	}
	if (i > TAG_MAX) {
		yyerror("tag can only be %d characters", TAG_MAX);
		free((yyvsp[0].v.string));
		YYERROR;
	}
	processor->tag = (yyvsp[0].v.string);
}
#line 2507 "y.tab.c"
    break;

  case 72: /* queue: QUEUE COMPRESSION  */
#line 520 "parse.y"
                  {
	conf->sc_queue_flags |= QUEUE_COMPRESSION;
}
#line 2515 "y.tab.c"
    break;

  case 73: /* queue: QUEUE ENCRYPTION  */
#line 523 "parse.y"
                   {
	conf->sc_queue_flags |= QUEUE_ENCRYPTION;
}
#line 2523 "y.tab.c"
    break;

  case 74: /* queue: QUEUE ENCRYPTION STRING  */
#line 526 "parse.y"
                          {
	if (strcasecmp((yyvsp[0].v.string), "stdin") == 0 || strcasecmp((yyvsp[0].v.string), "-") == 0) {
		conf->sc_queue_key = "stdin";
		free((yyvsp[0].v.string));
	}
	else
		conf->sc_queue_key = (yyvsp[0].v.string);
	conf->sc_queue_flags |= QUEUE_ENCRYPTION;
}
#line 2537 "y.tab.c"
    break;

  case 75: /* queue: QUEUE TTL STRING  */
#line 535 "parse.y"
                   {
	conf->sc_ttl = delaytonum((yyvsp[0].v.string));
	if (conf->sc_ttl == -1) {
		yyerror("invalid ttl delay: %s", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	free((yyvsp[0].v.string));
}
#line 2551 "y.tab.c"
    break;

  case 78: /* smtp: SMTP CIPHERS STRING  */
#line 554 "parse.y"
                      {
	conf->sc_tls_ciphers = (yyvsp[0].v.string);
}
#line 2559 "y.tab.c"
    break;

  case 79: /* smtp: SMTP MAX_MESSAGE_SIZE size  */
#line 557 "parse.y"
                             {
	conf->sc_maxsize = (yyvsp[0].v.number);
}
#line 2567 "y.tab.c"
    break;

  case 80: /* smtp: SMTP SUB_ADDR_DELIM STRING  */
#line 560 "parse.y"
                             {
	if (strlen((yyvsp[0].v.string)) != 1) {
		yyerror("subaddressing-delimiter must be one character");
		free((yyvsp[0].v.string));
		YYERROR;
	}
	if (isspace((unsigned char)*(yyvsp[0].v.string)) || !isprint((unsigned char)*(yyvsp[0].v.string)) || *(yyvsp[0].v.string) == '@') {
		yyerror("sub-addr-delim uses invalid character");
		free((yyvsp[0].v.string));
		YYERROR;
	}
	conf->sc_subaddressing_delim = (yyvsp[0].v.string);
}
#line 2585 "y.tab.c"
    break;

  case 81: /* srs: SRS KEY STRING  */
#line 576 "parse.y"
               {
	conf->sc_srs_key = (yyvsp[0].v.string);
}
#line 2593 "y.tab.c"
    break;

  case 82: /* srs: SRS KEY BACKUP STRING  */
#line 579 "parse.y"
                        {
	conf->sc_srs_key_backup = (yyvsp[0].v.string);
}
#line 2601 "y.tab.c"
    break;

  case 83: /* srs: SRS TTL STRING  */
#line 582 "parse.y"
                 {
	conf->sc_srs_ttl = delaytonum((yyvsp[0].v.string));
	if (conf->sc_srs_ttl == -1) {
		yyerror("ttl delay \"%s\" is invalid", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}

	conf->sc_srs_ttl /= 86400;
	if (conf->sc_srs_ttl == 0) {
		yyerror("ttl delay \"%s\" is too short", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	free((yyvsp[0].v.string));
}
#line 2622 "y.tab.c"
    break;

  case 84: /* dispatcher_local_option: USER STRING  */
#line 602 "parse.y"
            {
	if (dsp->u.local.is_mbox) {
		yyerror("user may not be specified for this dispatcher");
		YYERROR;
	}

	if (dsp->u.local.forward_only) {
		yyerror("user may not be specified for forward-only");
		YYERROR;
	}

	if (dsp->u.local.expand_only) {
		yyerror("user may not be specified for expand-only");
		YYERROR;
	}

	if (dsp->u.local.user) {
		yyerror("user already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.local.user = (yyvsp[0].v.string);
}
#line 2650 "y.tab.c"
    break;

  case 85: /* dispatcher_local_option: ALIAS tables  */
#line 625 "parse.y"
               {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.local.table_alias) {
		yyerror("alias mapping already specified for this dispatcher");
		YYERROR;
	}

	if (dsp->u.local.table_virtual) {
		yyerror("virtual mapping already specified for this dispatcher");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_HASH, K_ALIAS)) {
		yyerror("table \"%s\" may not be used for alias lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.local.table_alias = strdup(t->t_name);
}
#line 2676 "y.tab.c"
    break;

  case 86: /* dispatcher_local_option: VIRTUAL tables  */
#line 646 "parse.y"
                 {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.local.table_virtual) {
		yyerror("virtual mapping already specified for this dispatcher");
		YYERROR;
	}

	if (dsp->u.local.table_alias) {
		yyerror("alias mapping already specified for this dispatcher");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_HASH, K_ALIAS)) {
		yyerror("table \"%s\" may not be used for virtual lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.local.table_virtual = strdup(t->t_name);
}
#line 2702 "y.tab.c"
    break;

  case 87: /* dispatcher_local_option: USERBASE tables  */
#line 667 "parse.y"
                  {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.local.table_userbase) {
		yyerror("userbase mapping already specified for this dispatcher");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_HASH, K_USERINFO)) {
		yyerror("table \"%s\" may not be used for userbase lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.local.table_userbase = strdup(t->t_name);
}
#line 2723 "y.tab.c"
    break;

  case 88: /* dispatcher_local_option: WRAPPER STRING  */
#line 683 "parse.y"
                 {
	if (! dict_get(conf->sc_mda_wrappers, (yyvsp[0].v.string))) {
		yyerror("no mda wrapper with that name: %s", (yyvsp[0].v.string));
		YYERROR;
	}
	dsp->u.local.mda_wrapper = (yyvsp[0].v.string);
}
#line 2735 "y.tab.c"
    break;

  case 91: /* $@7: %empty  */
#line 698 "parse.y"
     {
	dsp->u.local.is_mbox = 1;
}
#line 2743 "y.tab.c"
    break;

  case 93: /* $@8: %empty  */
#line 701 "parse.y"
          {
	asprintf(&dsp->u.local.command, "/usr/libexec/mail.maildir");
}
#line 2751 "y.tab.c"
    break;

  case 95: /* $@9: %empty  */
#line 704 "parse.y"
               {
	asprintf(&dsp->u.local.command, "/usr/libexec/mail.maildir -j");
}
#line 2759 "y.tab.c"
    break;

  case 97: /* $@10: %empty  */
#line 707 "parse.y"
                 {
	if (strncmp((yyvsp[0].v.string), "~/", 2) == 0)
		asprintf(&dsp->u.local.command,
		    "/usr/libexec/mail.maildir \"%%{user.directory}/%s\"", (yyvsp[0].v.string)+2);
	else
		asprintf(&dsp->u.local.command,
		    "/usr/libexec/mail.maildir \"%s\"", (yyvsp[0].v.string));
}
#line 2772 "y.tab.c"
    break;

  case 99: /* $@11: %empty  */
#line 715 "parse.y"
                      {
	if (strncmp((yyvsp[-1].v.string), "~/", 2) == 0)
		asprintf(&dsp->u.local.command,
		    "/usr/libexec/mail.maildir -j \"%%{user.directory}/%s\"", (yyvsp[-1].v.string)+2);
	else
		asprintf(&dsp->u.local.command,
		    "/usr/libexec/mail.maildir -j \"%s\"", (yyvsp[-1].v.string));
}
#line 2785 "y.tab.c"
    break;

  case 101: /* $@12: %empty  */
#line 723 "parse.y"
              {
	asprintf(&dsp->u.local.command,
	    "/usr/libexec/mail.lmtp -d %s -u", (yyvsp[0].v.string));
}
#line 2794 "y.tab.c"
    break;

  case 103: /* $@13: %empty  */
#line 727 "parse.y"
                      {
	asprintf(&dsp->u.local.command,
	    "/usr/libexec/mail.lmtp -d %s -r", (yyvsp[-1].v.string));
}
#line 2803 "y.tab.c"
    break;

  case 105: /* $@14: %empty  */
#line 731 "parse.y"
             {
	asprintf(&dsp->u.local.command,
	    "/usr/libexec/mail.mda \"%s\"", (yyvsp[0].v.string));
}
#line 2812 "y.tab.c"
    break;

  case 107: /* $@15: %empty  */
#line 735 "parse.y"
               {
	dsp->u.local.forward_only = 1;
}
#line 2820 "y.tab.c"
    break;

  case 109: /* $@16: %empty  */
#line 738 "parse.y"
              {
	dsp->u.local.expand_only = 1;
}
#line 2828 "y.tab.c"
    break;

  case 111: /* dispatcher_remote_option: HELO STRING  */
#line 745 "parse.y"
            {
	if (dsp->u.remote.helo) {
		yyerror("helo already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.helo = (yyvsp[0].v.string);
}
#line 2841 "y.tab.c"
    break;

  case 112: /* dispatcher_remote_option: HELO_SRC tables  */
#line 753 "parse.y"
                  {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.remote.helo_source) {
		yyerror("helo-source mapping already specified for this dispatcher");
		YYERROR;
	}
	if (!table_check_use(t, T_DYNAMIC|T_HASH, K_ADDRNAME)) {
		yyerror("table \"%s\" may not be used for helo-source lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.remote.helo_source = strdup(t->t_name);
}
#line 2861 "y.tab.c"
    break;

  case 113: /* dispatcher_remote_option: PKI STRING  */
#line 768 "parse.y"
             {
	if (dsp->u.remote.pki) {
		yyerror("pki already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.pki = (yyvsp[0].v.string);
}
#line 2874 "y.tab.c"
    break;

  case 114: /* dispatcher_remote_option: CA STRING  */
#line 776 "parse.y"
            {
	if (dsp->u.remote.ca) {
		yyerror("ca already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.ca = (yyvsp[0].v.string);
}
#line 2887 "y.tab.c"
    break;

  case 115: /* dispatcher_remote_option: CIPHERS STRING  */
#line 784 "parse.y"
                 {
	if (dsp->u.remote.tls_ciphers) {
		yyerror("ciphers already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.tls_ciphers = (yyvsp[0].v.string);
}
#line 2900 "y.tab.c"
    break;

  case 116: /* dispatcher_remote_option: PROTOCOLS STRING  */
#line 792 "parse.y"
                   {
	if (dsp->u.remote.tls_protocols) {
		yyerror("protocols already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.tls_protocols = (yyvsp[0].v.string);
}
#line 2913 "y.tab.c"
    break;

  case 117: /* dispatcher_remote_option: SRC tables  */
#line 800 "parse.y"
             {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.remote.source) {
		yyerror("source mapping already specified for this dispatcher");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST|T_HASH, K_SOURCE)) {
		yyerror("table \"%s\" may not be used for source lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.remote.source = strdup(t->t_name);
}
#line 2934 "y.tab.c"
    break;

  case 118: /* dispatcher_remote_option: MAIL_FROM STRING  */
#line 816 "parse.y"
                   {
	if (dsp->u.remote.mail_from) {
		yyerror("mail-from already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.mail_from = (yyvsp[0].v.string);
}
#line 2947 "y.tab.c"
    break;

  case 119: /* dispatcher_remote_option: BACKUP MX STRING  */
#line 824 "parse.y"
                   {
	if (dsp->u.remote.backup) {
		yyerror("backup already specified for this dispatcher");
		YYERROR;
	}
	if (dsp->u.remote.smarthost) {
		yyerror("backup and host are mutually exclusive");
		YYERROR;
	}

	dsp->u.remote.backup = 1;
	dsp->u.remote.backupmx = (yyvsp[0].v.string);
}
#line 2965 "y.tab.c"
    break;

  case 120: /* dispatcher_remote_option: BACKUP  */
#line 837 "parse.y"
         {
	if (dsp->u.remote.backup) {
		yyerror("backup already specified for this dispatcher");
		YYERROR;
	}
	if (dsp->u.remote.smarthost) {
		yyerror("backup and host are mutually exclusive");
		YYERROR;
	}

	dsp->u.remote.backup = 1;
}
#line 2982 "y.tab.c"
    break;

  case 121: /* dispatcher_remote_option: HOST tables  */
#line 849 "parse.y"
              {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.remote.smarthost) {
		yyerror("host mapping already specified for this dispatcher");
		YYERROR;
	}
	if (dsp->u.remote.backup) {
		yyerror("backup and host are mutually exclusive");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_RELAYHOST)) {
		yyerror("table \"%s\" may not be used for host lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.remote.smarthost = strdup(t->t_name);
}
#line 3007 "y.tab.c"
    break;

  case 122: /* dispatcher_remote_option: DOMAIN tables  */
#line 869 "parse.y"
                {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.remote.smarthost) {
		yyerror("host mapping already specified for this dispatcher");
		YYERROR;
	}
	if (dsp->u.remote.backup) {
		yyerror("backup and domain are mutually exclusive");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_HASH, K_RELAYHOST)) {
		yyerror("table \"%s\" may not be used for host lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.remote.smarthost = strdup(t->t_name);
	dsp->u.remote.smarthost_domain = 1;
}
#line 3033 "y.tab.c"
    break;

  case 123: /* dispatcher_remote_option: TLS  */
#line 890 "parse.y"
      {
	if (dsp->u.remote.tls_required == 1) {
		yyerror("tls already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.tls_required = 1;
	dsp->u.remote.tls_verify = 1;
}
#line 3047 "y.tab.c"
    break;

  case 124: /* dispatcher_remote_option: TLS NO_VERIFY  */
#line 899 "parse.y"
                {
	if (dsp->u.remote.tls_required == 1) {
		yyerror("tls already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.tls_required = 1;
}
#line 3060 "y.tab.c"
    break;

  case 125: /* dispatcher_remote_option: AUTH tables  */
#line 907 "parse.y"
              {
	struct table   *t = (yyvsp[0].v.table);

	if (dsp->u.remote.smarthost == NULL) {
		yyerror("auth may not be specified without host on a dispatcher");
		YYERROR;
	}

	if (dsp->u.remote.auth) {
		yyerror("auth mapping already specified for this dispatcher");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_HASH, K_CREDENTIALS)) {
		yyerror("table \"%s\" may not be used for auth lookups",
		    t->t_name);
		YYERROR;
	}

	dsp->u.remote.auth = strdup(t->t_name);
}
#line 3086 "y.tab.c"
    break;

  case 126: /* dispatcher_remote_option: FILTER STRING  */
#line 928 "parse.y"
                {
	struct filter_config *fc;

	if (dsp->u.remote.filtername) {
		yyerror("filter already specified for this dispatcher");
		YYERROR;
	}

	if ((fc = dict_get(conf->sc_filters_dict, (yyvsp[0].v.string))) == NULL) {
		yyerror("no filter exist with that name: %s", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	fc->filter_subsystem |= FILTER_SUBSYSTEM_SMTP_OUT;
	dsp->u.remote.filtername = (yyvsp[0].v.string);
}
#line 3107 "y.tab.c"
    break;

  case 127: /* $@17: %empty  */
#line 944 "parse.y"
         {
	char	buffer[128];
	char	*filtername;

	if (dsp->u.remote.filtername) {
		yyerror("filter already specified for this dispatcher");
		YYERROR;
	}

	do {
		(void)snprintf(buffer, sizeof buffer, "<dynchain:%08x>", last_dynchain_id++);
	} while (dict_check(conf->sc_filters_dict, buffer));

	filtername = xstrdup(buffer);
	filter_config = xcalloc(1, sizeof *filter_config);
	filter_config->filter_type = FILTER_TYPE_CHAIN;
	filter_config->filter_subsystem |= FILTER_SUBSYSTEM_SMTP_OUT;
	dict_init(&filter_config->chain_procs);
	dsp->u.remote.filtername = filtername;
}
#line 3132 "y.tab.c"
    break;

  case 128: /* dispatcher_remote_option: FILTER $@17 '{' optnl filter_list '}'  */
#line 963 "parse.y"
                            {
	dict_set(conf->sc_filters_dict, dsp->u.remote.filtername, filter_config);
	filter_config = NULL;
}
#line 3141 "y.tab.c"
    break;

  case 129: /* dispatcher_remote_option: SRS  */
#line 967 "parse.y"
      {
	if (conf->sc_srs_key == NULL) {
		yyerror("an srs key is required for srs to be specified in an action");
		YYERROR;
	}
	if (dsp->u.remote.srs == 1) {
		yyerror("srs already specified for this dispatcher");
		YYERROR;
	}

	dsp->u.remote.srs = 1;
}
#line 3158 "y.tab.c"
    break;

  case 133: /* dispatcher_type: dispatcher_local  */
#line 991 "parse.y"
                 {
	dsp->type = DISPATCHER_LOCAL;
}
#line 3166 "y.tab.c"
    break;

  case 134: /* dispatcher_type: dispatcher_remote  */
#line 994 "parse.y"
                    {
	dsp->type = DISPATCHER_REMOTE;
}
#line 3174 "y.tab.c"
    break;

  case 135: /* dispatcher_option: TTL STRING  */
#line 1000 "parse.y"
           {
	if (dsp->ttl) {
		yyerror("ttl already specified for this dispatcher");
		YYERROR;
	}

	dsp->ttl = delaytonum((yyvsp[0].v.string));
	if (dsp->ttl == -1) {
		yyerror("ttl delay \"%s\" is invalid", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	free((yyvsp[0].v.string));
}
#line 3193 "y.tab.c"
    break;

  case 138: /* $@18: %empty  */
#line 1022 "parse.y"
              {
	if (dict_get(conf->sc_dispatchers, (yyvsp[0].v.string))) {
		yyerror("dispatcher already declared with that name: %s", (yyvsp[0].v.string));
		YYERROR;
	}
	dsp = xcalloc(1, sizeof *dsp);
}
#line 3205 "y.tab.c"
    break;

  case 139: /* dispatcher: ACTION STRING $@18 dispatcher_type dispatcher_options  */
#line 1028 "parse.y"
                                     {
	if (dsp->type == DISPATCHER_LOCAL)
		if (dsp->u.local.table_userbase == NULL)
			dsp->u.local.table_userbase = "<getpwnam>";
	dict_set(conf->sc_dispatchers, (yyvsp[-3].v.string), dsp);
	dsp = NULL;
}
#line 3217 "y.tab.c"
    break;

  case 140: /* match_option: negation TAG tables  */
#line 1038 "parse.y"
                    {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_tag) {
		yyerror("tag already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_STRING)) {
		yyerror("table \"%s\" may not be used for tag lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_tag = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_tag = strdup(t->t_name);
}
#line 3239 "y.tab.c"
    break;

  case 141: /* match_option: negation TAG REGEX tables  */
#line 1056 "parse.y"
                          {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_tag) {
		yyerror("tag already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for tag lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_tag = (yyvsp[-3].v.number) ? -1 : 1;
	rule->flag_tag_regex = 1;
	rule->table_tag = strdup(t->t_name);
}
#line 3262 "y.tab.c"
    break;

  case 142: /* match_option: negation HELO tables  */
#line 1075 "parse.y"
                       {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_helo) {
		yyerror("helo already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_DOMAIN)) {
		yyerror("table \"%s\" may not be used for helo lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_helo = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_smtp_helo = strdup(t->t_name);
}
#line 3284 "y.tab.c"
    break;

  case 143: /* match_option: negation HELO REGEX tables  */
#line 1092 "parse.y"
                             {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_helo) {
		yyerror("helo already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for helo lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_helo = (yyvsp[-3].v.number) ? -1 : 1;
	rule->flag_smtp_helo_regex = 1;
	rule->table_smtp_helo = strdup(t->t_name);
}
#line 3307 "y.tab.c"
    break;

  case 144: /* match_option: negation TLS  */
#line 1110 "parse.y"
               {
	if (rule->flag_smtp_starttls) {
		yyerror("tls already specified for this rule");
		YYERROR;
	}
	rule->flag_smtp_starttls = (yyvsp[-1].v.number) ? -1 : 1;
}
#line 3319 "y.tab.c"
    break;

  case 145: /* match_option: negation AUTH  */
#line 1117 "parse.y"
                {
	if (rule->flag_smtp_auth) {
		yyerror("auth already specified for this rule");
		YYERROR;
	}
	rule->flag_smtp_auth = (yyvsp[-1].v.number) ? -1 : 1;
}
#line 3331 "y.tab.c"
    break;

  case 146: /* match_option: negation AUTH tables  */
#line 1124 "parse.y"
                       {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_auth) {
		yyerror("auth already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST|T_HASH, K_STRING|K_CREDENTIALS)) {
		yyerror("table \"%s\" may not be used for auth lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_auth = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_smtp_auth = strdup(t->t_name);
}
#line 3353 "y.tab.c"
    break;

  case 147: /* match_option: negation AUTH REGEX tables  */
#line 1141 "parse.y"
                             {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_auth) {
		yyerror("auth already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for auth lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_auth = (yyvsp[-3].v.number) ? -1 : 1;
	rule->flag_smtp_auth_regex = 1;
	rule->table_smtp_auth = strdup(t->t_name);
}
#line 3376 "y.tab.c"
    break;

  case 148: /* match_option: negation MAIL_FROM tables  */
#line 1159 "parse.y"
                            {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_mail_from) {
		yyerror("mail-from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST|T_HASH, K_MAILADDR)) {
		yyerror("table \"%s\" may not be used for mail-from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_mail_from = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_smtp_mail_from = strdup(t->t_name);
}
#line 3398 "y.tab.c"
    break;

  case 149: /* match_option: negation MAIL_FROM REGEX tables  */
#line 1176 "parse.y"
                                  {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_mail_from) {
		yyerror("mail-from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for mail-from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_mail_from = (yyvsp[-3].v.number) ? -1 : 1;
	rule->flag_smtp_mail_from_regex = 1;
	rule->table_smtp_mail_from = strdup(t->t_name);
}
#line 3421 "y.tab.c"
    break;

  case 150: /* match_option: negation RCPT_TO tables  */
#line 1194 "parse.y"
                          {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_rcpt_to) {
		yyerror("rcpt-to already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST|T_HASH, K_MAILADDR)) {
		yyerror("table \"%s\" may not be used for rcpt-to lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_rcpt_to = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_smtp_rcpt_to = strdup(t->t_name);
}
#line 3443 "y.tab.c"
    break;

  case 151: /* match_option: negation RCPT_TO REGEX tables  */
#line 1211 "parse.y"
                                {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_smtp_rcpt_to) {
		yyerror("rcpt-to already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for rcpt-to lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_smtp_rcpt_to = (yyvsp[-3].v.number) ? -1 : 1;
	rule->flag_smtp_rcpt_to_regex = 1;
	rule->table_smtp_rcpt_to = strdup(t->t_name);
}
#line 3466 "y.tab.c"
    break;

  case 152: /* match_option: negation FROM SOCKET  */
#line 1230 "parse.y"
                       {
	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}
	rule->flag_from = (yyvsp[-2].v.number) ? -1 : 1;
	rule->flag_from_socket = 1;
}
#line 3479 "y.tab.c"
    break;

  case 153: /* match_option: negation FROM LOCAL  */
#line 1238 "parse.y"
                      {
	struct table	*t = table_find(conf, "<localhost>");

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}
	rule->flag_from = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_from = strdup(t->t_name);
}
#line 3494 "y.tab.c"
    break;

  case 154: /* match_option: negation FROM ANY  */
#line 1248 "parse.y"
                    {
	struct table	*t = table_find(conf, "<anyhost>");

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}
	rule->flag_from = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_from = strdup(t->t_name);
}
#line 3509 "y.tab.c"
    break;

  case 155: /* match_option: negation FROM SRC tables  */
#line 1258 "parse.y"
                           {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_NETADDR)) {
		yyerror("table \"%s\" may not be used for from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = (yyvsp[-3].v.number) ? -1 : 1;
	rule->table_from = strdup(t->t_name);
}
#line 3531 "y.tab.c"
    break;

  case 156: /* match_option: negation FROM SRC REGEX tables  */
#line 1275 "parse.y"
                                 {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = (yyvsp[-4].v.number) ? -1 : 1;
	rule->flag_from_regex = 1;
	rule->table_from = strdup(t->t_name);
}
#line 3554 "y.tab.c"
    break;

  case 157: /* match_option: negation FROM RDNS  */
#line 1293 "parse.y"
                     {
	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}
	rule->flag_from = (yyvsp[-2].v.number) ? -1 : 1;
	rule->flag_from_rdns = 1;
}
#line 3567 "y.tab.c"
    break;

  case 158: /* match_option: negation FROM RDNS tables  */
#line 1301 "parse.y"
                            {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_DOMAIN)) {
		yyerror("table \"%s\" may not be used for rdns lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = (yyvsp[-3].v.number) ? -1 : 1;
	rule->flag_from_rdns = 1;
	rule->table_from = strdup(t->t_name);
}
#line 3590 "y.tab.c"
    break;

  case 159: /* match_option: negation FROM RDNS REGEX tables  */
#line 1319 "parse.y"
                                  {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_DOMAIN)) {
		yyerror("table \"%s\" may not be used for rdns lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = (yyvsp[-4].v.number) ? -1 : 1;
	rule->flag_from_regex = 1;
	rule->flag_from_rdns = 1;
	rule->table_from = strdup(t->t_name);
}
#line 3614 "y.tab.c"
    break;

  case 160: /* match_option: negation FROM AUTH  */
#line 1339 "parse.y"
                     {
	struct table	*anyhost = table_find(conf, "<anyhost>");

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	rule->flag_from = 1;
	rule->table_from = strdup(anyhost->t_name);
	rule->flag_smtp_auth = (yyvsp[-2].v.number) ? -1 : 1;
}
#line 3631 "y.tab.c"
    break;

  case 161: /* match_option: negation FROM AUTH tables  */
#line 1351 "parse.y"
                            {
	struct table	*anyhost = table_find(conf, "<anyhost>");
	struct table	*t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_STRING|K_CREDENTIALS)) {
		yyerror("table \"%s\" may not be used for from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = 1;
	rule->table_from = strdup(anyhost->t_name);
	rule->flag_smtp_auth = (yyvsp[-3].v.number) ? -1 : 1;
	rule->table_smtp_auth = strdup(t->t_name);
}
#line 3656 "y.tab.c"
    break;

  case 162: /* match_option: negation FROM AUTH REGEX tables  */
#line 1371 "parse.y"
                                  {
	struct table	*anyhost = table_find(conf, "<anyhost>");
	struct table	*t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
        	yyerror("table \"%s\" may not be used for from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = 1;
	rule->table_from = strdup(anyhost->t_name);
	rule->flag_smtp_auth = (yyvsp[-4].v.number) ? -1 : 1;
	rule->flag_smtp_auth_regex = 1;
	rule->table_smtp_auth = strdup(t->t_name);
}
#line 3682 "y.tab.c"
    break;

  case 163: /* match_option: negation FROM MAIL_FROM tables  */
#line 1393 "parse.y"
                                 {
	struct table	*anyhost = table_find(conf, "<anyhost>");
	struct table	*t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST|T_HASH, K_MAILADDR)) {
		yyerror("table \"%s\" may not be used for from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = 1;
	rule->table_from = strdup(anyhost->t_name);
	rule->flag_smtp_mail_from = (yyvsp[-3].v.number) ? -1 : 1;
	rule->table_smtp_mail_from = strdup(t->t_name);
}
#line 3707 "y.tab.c"
    break;

  case 164: /* match_option: negation FROM MAIL_FROM REGEX tables  */
#line 1413 "parse.y"
                                       {
	struct table	*anyhost = table_find(conf, "<anyhost>");
	struct table	*t = (yyvsp[0].v.table);

	if (rule->flag_from) {
		yyerror("from already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for from lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_from = 1;
	rule->table_from = strdup(anyhost->t_name);
	rule->flag_smtp_mail_from = (yyvsp[-4].v.number) ? -1 : 1;
	rule->flag_smtp_mail_from_regex = 1;
	rule->table_smtp_mail_from = strdup(t->t_name);
}
#line 3733 "y.tab.c"
    break;

  case 165: /* match_option: negation FOR LOCAL  */
#line 1435 "parse.y"
                     {
	struct table   *t = table_find(conf, "<localnames>");

	if (rule->flag_for) {
		yyerror("for already specified for this rule");
		YYERROR;
	}
	rule->flag_for = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_for = strdup(t->t_name);
}
#line 3748 "y.tab.c"
    break;

  case 166: /* match_option: negation FOR ANY  */
#line 1445 "parse.y"
                   {
	struct table   *t = table_find(conf, "<anydestination>");

	if (rule->flag_for) {
		yyerror("for already specified for this rule");
		YYERROR;
	}
	rule->flag_for = (yyvsp[-2].v.number) ? -1 : 1;
	rule->table_for = strdup(t->t_name);
}
#line 3763 "y.tab.c"
    break;

  case 167: /* match_option: negation FOR DOMAIN tables  */
#line 1455 "parse.y"
                             {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_for) {
		yyerror("for already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_DOMAIN)) {
		yyerror("table \"%s\" may not be used for 'for' lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_for = (yyvsp[-3].v.number) ? -1 : 1;
	rule->table_for = strdup(t->t_name);
}
#line 3785 "y.tab.c"
    break;

  case 168: /* match_option: negation FOR DOMAIN REGEX tables  */
#line 1472 "parse.y"
                                   {
	struct table   *t = (yyvsp[0].v.table);

	if (rule->flag_for) {
		yyerror("for already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for 'for' lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_for = (yyvsp[-4].v.number) ? -1 : 1;
	rule->flag_for_regex = 1;
	rule->table_for = strdup(t->t_name);
}
#line 3808 "y.tab.c"
    break;

  case 169: /* match_option: negation FOR RCPT_TO tables  */
#line 1490 "parse.y"
                              {
	struct table	*anyhost = table_find(conf, "<anydestination>");
	struct table	*t = (yyvsp[0].v.table);

	if (rule->flag_for) {
		yyerror("for already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST|T_HASH, K_MAILADDR)) {
		yyerror("table \"%s\" may not be used for for lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_for = 1;
	rule->table_for = strdup(anyhost->t_name);
	rule->flag_smtp_rcpt_to = (yyvsp[-3].v.number) ? -1 : 1;
	rule->table_smtp_rcpt_to = strdup(t->t_name);
}
#line 3833 "y.tab.c"
    break;

  case 170: /* match_option: negation FOR RCPT_TO REGEX tables  */
#line 1510 "parse.y"
                                    {
	struct table	*anyhost = table_find(conf, "<anydestination>");
	struct table	*t = (yyvsp[0].v.table);

	if (rule->flag_for) {
		yyerror("for already specified for this rule");
		YYERROR;
	}

	if (!table_check_use(t, T_DYNAMIC|T_LIST, K_REGEX)) {
		yyerror("table \"%s\" may not be used for for lookups",
		    t->t_name);
		YYERROR;
	}

	rule->flag_for = 1;
	rule->table_for = strdup(anyhost->t_name);
	rule->flag_smtp_rcpt_to = (yyvsp[-4].v.number) ? -1 : 1;
	rule->flag_smtp_rcpt_to_regex = 1;
	rule->table_smtp_rcpt_to = strdup(t->t_name);
}
#line 3859 "y.tab.c"
    break;

  case 173: /* match_dispatcher: STRING  */
#line 1539 "parse.y"
       {
	if (dict_get(conf->sc_dispatchers, (yyvsp[0].v.string)) == NULL) {
		yyerror("no such dispatcher: %s", (yyvsp[0].v.string));
		YYERROR;
	}
	rule->dispatcher = (yyvsp[0].v.string);
}
#line 3871 "y.tab.c"
    break;

  case 174: /* action: REJECT  */
#line 1549 "parse.y"
       {
	rule->reject = 1;
}
#line 3879 "y.tab.c"
    break;

  case 176: /* $@19: %empty  */
#line 1556 "parse.y"
      {
	rule = xcalloc(1, sizeof *rule);
}
#line 3887 "y.tab.c"
    break;

  case 177: /* match: MATCH $@19 match_options action  */
#line 1558 "parse.y"
                       {
	if (!rule->flag_from) {
		rule->table_from = strdup("<localhost>");
		rule->flag_from = 1;
	}
	if (!rule->flag_for) {
		rule->table_for = strdup("<localnames>");
		rule->flag_for = 1;
	}
	TAILQ_INSERT_TAIL(conf->sc_rules, rule, r_entry);
	rule = NULL;
}
#line 3904 "y.tab.c"
    break;

  case 179: /* filter_action_builtin: JUNK  */
#line 1574 "parse.y"
       {
	filter_config->junk = 1;
}
#line 3912 "y.tab.c"
    break;

  case 180: /* filter_action_builtin: BYPASS  */
#line 1577 "parse.y"
         {
	filter_config->bypass = 1;
}
#line 3920 "y.tab.c"
    break;

  case 181: /* filter_action_builtin_nojunk: REJECT STRING  */
#line 1583 "parse.y"
              {
	filter_config->reject = (yyvsp[0].v.string);
}
#line 3928 "y.tab.c"
    break;

  case 182: /* filter_action_builtin_nojunk: DISCONNECT STRING  */
#line 1586 "parse.y"
                    {
	filter_config->disconnect = (yyvsp[0].v.string);
}
#line 3936 "y.tab.c"
    break;

  case 183: /* filter_action_builtin_nojunk: REWRITE STRING  */
#line 1589 "parse.y"
                 {
	filter_config->rewrite = (yyvsp[0].v.string);
}
#line 3944 "y.tab.c"
    break;

  case 184: /* filter_action_builtin_nojunk: REPORT STRING  */
#line 1592 "parse.y"
                {
	filter_config->report = (yyvsp[0].v.string);
}
#line 3952 "y.tab.c"
    break;

  case 185: /* filter_phase_check_fcrdns: negation FCRDNS  */
#line 1598 "parse.y"
                {
	filter_config->not_fcrdns = (yyvsp[-1].v.number) ? -1 : 1;
	filter_config->fcrdns = 1;
}
#line 3961 "y.tab.c"
    break;

  case 186: /* filter_phase_check_rdns: negation RDNS  */
#line 1605 "parse.y"
              {
	filter_config->not_rdns = (yyvsp[-1].v.number) ? -1 : 1;
	filter_config->rdns = 1;
}
#line 3970 "y.tab.c"
    break;

  case 187: /* filter_phase_check_rdns_table: negation RDNS tables  */
#line 1612 "parse.y"
                     {
	filter_config->not_rdns_table = (yyvsp[-2].v.number) ? -1 : 1;
	filter_config->rdns_table = (yyvsp[0].v.table);
}
#line 3979 "y.tab.c"
    break;

  case 188: /* filter_phase_check_rdns_regex: negation RDNS REGEX tables  */
#line 1618 "parse.y"
                           {
	filter_config->not_rdns_regex = (yyvsp[-3].v.number) ? -1 : 1;
	filter_config->rdns_regex = (yyvsp[0].v.table);
}
#line 3988 "y.tab.c"
    break;

  case 189: /* filter_phase_check_src_table: negation SRC tables  */
#line 1625 "parse.y"
                    {
	filter_config->not_src_table = (yyvsp[-2].v.number) ? -1 : 1;
	filter_config->src_table = (yyvsp[0].v.table);
}
#line 3997 "y.tab.c"
    break;

  case 190: /* filter_phase_check_src_regex: negation SRC REGEX tables  */
#line 1631 "parse.y"
                          {
	filter_config->not_src_regex = (yyvsp[-3].v.number) ? -1 : 1;
	filter_config->src_regex = (yyvsp[0].v.table);
}
#line 4006 "y.tab.c"
    break;

  case 191: /* filter_phase_check_helo_table: negation HELO tables  */
#line 1638 "parse.y"
                     {
	filter_config->not_helo_table = (yyvsp[-2].v.number) ? -1 : 1;
	filter_config->helo_table = (yyvsp[0].v.table);
}
#line 4015 "y.tab.c"
    break;

  case 192: /* filter_phase_check_helo_regex: negation HELO REGEX tables  */
#line 1644 "parse.y"
                           {
	filter_config->not_helo_regex = (yyvsp[-3].v.number) ? -1 : 1;
	filter_config->helo_regex = (yyvsp[0].v.table);
}
#line 4024 "y.tab.c"
    break;

  case 193: /* filter_phase_check_auth: negation AUTH  */
#line 1651 "parse.y"
              {
	filter_config->not_auth = (yyvsp[-1].v.number) ? -1 : 1;
	filter_config->auth = 1;
}
#line 4033 "y.tab.c"
    break;

  case 194: /* filter_phase_check_auth_table: negation AUTH tables  */
#line 1657 "parse.y"
                     {
	filter_config->not_auth_table = (yyvsp[-2].v.number) ? -1 : 1;
	filter_config->auth_table = (yyvsp[0].v.table);
}
#line 4042 "y.tab.c"
    break;

  case 195: /* filter_phase_check_auth_regex: negation AUTH REGEX tables  */
#line 1663 "parse.y"
                           {
	filter_config->not_auth_regex = (yyvsp[-3].v.number) ? -1 : 1;
	filter_config->auth_regex = (yyvsp[0].v.table);
}
#line 4051 "y.tab.c"
    break;

  case 196: /* filter_phase_check_mail_from_table: negation MAIL_FROM tables  */
#line 1670 "parse.y"
                          {
	filter_config->not_mail_from_table = (yyvsp[-2].v.number) ? -1 : 1;
	filter_config->mail_from_table = (yyvsp[0].v.table);
}
#line 4060 "y.tab.c"
    break;

  case 197: /* filter_phase_check_mail_from_regex: negation MAIL_FROM REGEX tables  */
#line 1676 "parse.y"
                                {
	filter_config->not_mail_from_regex = (yyvsp[-3].v.number) ? -1 : 1;
	filter_config->mail_from_regex = (yyvsp[0].v.table);
}
#line 4069 "y.tab.c"
    break;

  case 198: /* filter_phase_check_rcpt_to_table: negation RCPT_TO tables  */
#line 1683 "parse.y"
                        {
	filter_config->not_rcpt_to_table = (yyvsp[-2].v.number) ? -1 : 1;
	filter_config->rcpt_to_table = (yyvsp[0].v.table);
}
#line 4078 "y.tab.c"
    break;

  case 199: /* filter_phase_check_rcpt_to_regex: negation RCPT_TO REGEX tables  */
#line 1689 "parse.y"
                              {
	filter_config->not_rcpt_to_regex = (yyvsp[-3].v.number) ? -1 : 1;
	filter_config->rcpt_to_regex = (yyvsp[0].v.table);
}
#line 4087 "y.tab.c"
    break;

  case 250: /* $@20: %empty  */
#line 1780 "parse.y"
        {
	filter_config->phase = FILTER_CONNECT;
}
#line 4095 "y.tab.c"
    break;

  case 252: /* $@21: %empty  */
#line 1787 "parse.y"
     {
	filter_config->phase = FILTER_HELO;
}
#line 4103 "y.tab.c"
    break;

  case 254: /* $@22: %empty  */
#line 1793 "parse.y"
     {
	filter_config->phase = FILTER_EHLO;
}
#line 4111 "y.tab.c"
    break;

  case 256: /* $@23: %empty  */
#line 1799 "parse.y"
     {
}
#line 4118 "y.tab.c"
    break;

  case 258: /* $@24: %empty  */
#line 1804 "parse.y"
          {
	filter_config->phase = FILTER_MAIL_FROM;
}
#line 4126 "y.tab.c"
    break;

  case 260: /* $@25: %empty  */
#line 1810 "parse.y"
        {
	filter_config->phase = FILTER_RCPT_TO;
}
#line 4134 "y.tab.c"
    break;

  case 262: /* $@26: %empty  */
#line 1816 "parse.y"
     {
	filter_config->phase = FILTER_DATA;
}
#line 4142 "y.tab.c"
    break;

  case 264: /* $@27: %empty  */
#line 1848 "parse.y"
       {
	filter_config->phase = FILTER_COMMIT;
}
#line 4150 "y.tab.c"
    break;

  case 274: /* filterel: STRING  */
#line 1872 "parse.y"
        {
	struct filter_config   *fr;
	size_t			i;

	if ((fr = dict_get(conf->sc_filters_dict, (yyvsp[0].v.string))) == NULL) {
		yyerror("no filter exist with that name: %s", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	if (fr->filter_type == FILTER_TYPE_CHAIN) {
		yyerror("no filter chain allowed within a filter chain: %s", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}

	for (i = 0; i < filter_config->chain_size; i++) {
		if (strcmp(filter_config->chain[i], (yyvsp[0].v.string)) == 0) {
			yyerror("no filter allowed twice within a filter chain: %s", (yyvsp[0].v.string));
			free((yyvsp[0].v.string));
			YYERROR;
		}
	}

	if (fr->proc) {
		if (dict_get(&filter_config->chain_procs, fr->proc)) {
			yyerror("no proc allowed twice within a filter chain: %s", fr->proc);
			free((yyvsp[0].v.string));
			YYERROR;
		}
		dict_set(&filter_config->chain_procs, fr->proc, NULL);
	}

	fr->filter_subsystem |= filter_config->filter_subsystem;
	filter_config->chain_size += 1;
	filter_config->chain = reallocarray(filter_config->chain, filter_config->chain_size, sizeof(char *));
	if (filter_config->chain == NULL)
		fatal("reallocarray");
	filter_config->chain[filter_config->chain_size - 1] = (yyvsp[0].v.string);
}
#line 4194 "y.tab.c"
    break;

  case 277: /* filter: FILTER STRING PROC STRING  */
#line 1919 "parse.y"
                          {

	if (dict_get(conf->sc_filters_dict, (yyvsp[-2].v.string))) {
		yyerror("filter already exists with that name: %s", (yyvsp[-2].v.string));
		free((yyvsp[-2].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}
	if (dict_get(conf->sc_filter_processes_dict, (yyvsp[0].v.string)) == NULL) {
		yyerror("no processor exist with that name: %s", (yyvsp[0].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}

	filter_config = xcalloc(1, sizeof *filter_config);
	filter_config->filter_type = FILTER_TYPE_PROC;
	filter_config->name = (yyvsp[-2].v.string);
	filter_config->proc = (yyvsp[0].v.string);
	dict_set(conf->sc_filters_dict, (yyvsp[-2].v.string), filter_config);
	filter_config = NULL;
}
#line 4220 "y.tab.c"
    break;

  case 278: /* $@28: %empty  */
#line 1941 "parse.y"
                               {
	if (dict_get(conf->sc_filters_dict, (yyvsp[-2].v.string))) {
		yyerror("filter already exists with that name: %s", (yyvsp[-2].v.string));
		free((yyvsp[-2].v.string));
		free((yyvsp[0].v.string));
		YYERROR;
	}

	processor = xcalloc(1, sizeof *processor);
	processor->command = (yyvsp[0].v.string);

	filter_config = xcalloc(1, sizeof *filter_config);
	filter_config->filter_type = FILTER_TYPE_PROC;
	filter_config->name = (yyvsp[-2].v.string);
	filter_config->proc = xstrdup((yyvsp[-2].v.string));
	dict_set(conf->sc_filters_dict, (yyvsp[-2].v.string), filter_config);
}
#line 4242 "y.tab.c"
    break;

  case 279: /* filter: FILTER STRING PROC_EXEC STRING $@28 proc_params  */
#line 1957 "parse.y"
              {
	if (!processor->tag)
		processor->tag = processor_maketag(filter_config->proc);
	dict_set(conf->sc_filter_processes_dict, filter_config->proc, processor);
	processor = NULL;
	filter_config = NULL;
}
#line 4254 "y.tab.c"
    break;

  case 280: /* $@29: %empty  */
#line 1965 "parse.y"
                    {
	if (dict_get(conf->sc_filters_dict, (yyvsp[-1].v.string))) {
		yyerror("filter already exists with that name: %s", (yyvsp[-1].v.string));
		free((yyvsp[-1].v.string));
		YYERROR;
	}
	filter_config = xcalloc(1, sizeof *filter_config);
	filter_config->name = (yyvsp[-1].v.string);
	filter_config->filter_type = FILTER_TYPE_BUILTIN;
	dict_set(conf->sc_filters_dict, (yyvsp[-1].v.string), filter_config);
}
#line 4270 "y.tab.c"
    break;

  case 281: /* filter: FILTER STRING PHASE $@29 filter_phase  */
#line 1975 "parse.y"
               {
	filter_config = NULL;
}
#line 4278 "y.tab.c"
    break;

  case 282: /* $@30: %empty  */
#line 1979 "parse.y"
                    {
	if (dict_get(conf->sc_filters_dict, (yyvsp[-1].v.string))) {
		yyerror("filter already exists with that name: %s", (yyvsp[-1].v.string));
		free((yyvsp[-1].v.string));
		YYERROR;
	}
	filter_config = xcalloc(1, sizeof *filter_config);
	filter_config->filter_type = FILTER_TYPE_CHAIN;
	dict_init(&filter_config->chain_procs);
}
#line 4293 "y.tab.c"
    break;

  case 283: /* filter: FILTER STRING CHAIN $@30 '{' optnl filter_list '}'  */
#line 1988 "parse.y"
                            {
	dict_set(conf->sc_filters_dict, (yyvsp[-6].v.string), filter_config);
	filter_config = NULL;
}
#line 4302 "y.tab.c"
    break;

  case 284: /* size: NUMBER  */
#line 1994 "parse.y"
                                        {
			if ((yyvsp[0].v.number) < 0) {
				yyerror("invalid size: %" PRId64, (yyvsp[0].v.number));
				YYERROR;
			}
			(yyval.v.number) = (yyvsp[0].v.number);
		}
#line 4314 "y.tab.c"
    break;

  case 285: /* size: STRING  */
#line 2001 "parse.y"
                                                {
			long long result;

			if (scan_scaled((yyvsp[0].v.string), &result) == -1 || result < 0) {
				yyerror("invalid size: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			(yyval.v.number) = result;
		}
#line 4330 "y.tab.c"
    break;

  case 286: /* bouncedelay: STRING  */
#line 2014 "parse.y"
                         {
			time_t	d;
			int	i;

			d = delaytonum((yyvsp[0].v.string));
			if (d < 0) {
				yyerror("invalid bounce delay: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			for (i = 0; i < MAX_BOUNCE_WARN; i++) {
				if (conf->sc_bounce_warn[i] != 0)
					continue;
				conf->sc_bounce_warn[i] = d;
				break;
			}
		}
#line 4353 "y.tab.c"
    break;

  case 289: /* opt_limit_mda: STRING NUMBER  */
#line 2038 "parse.y"
                                {
			if (!strcmp((yyvsp[-1].v.string), "max-session")) {
				conf->sc_mda_max_session = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "max-session-per-user")) {
				conf->sc_mda_max_user_session = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "task-lowat")) {
				conf->sc_mda_task_lowat = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "task-hiwat")) {
				conf->sc_mda_task_hiwat = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "task-release")) {
				conf->sc_mda_task_release = (yyvsp[0].v.number);
			}
			else {
				yyerror("invalid scheduler limit keyword: %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
		}
#line 4381 "y.tab.c"
    break;

  case 292: /* opt_limit_smtp: STRING NUMBER  */
#line 2067 "parse.y"
                               {
			if (!strcmp((yyvsp[-1].v.string), "max-rcpt")) {
				if ((yyvsp[0].v.number) < 100) {
					yyerror("RFC5321 requires "
					    "max-rcpt >= 100");
					free((yyvsp[-1].v.string));
					YYERROR;
				}
				conf->sc_session_max_rcpt = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "max-mails")) {
				conf->sc_session_max_mails = (yyvsp[0].v.number);
			}
			else {
				yyerror("invalid session limit keyword: %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
		}
#line 4406 "y.tab.c"
    break;

  case 295: /* opt_limit_mta: INET4  */
#line 2093 "parse.y"
                        {
			limits->family = AF_INET;
		}
#line 4414 "y.tab.c"
    break;

  case 296: /* opt_limit_mta: INET6  */
#line 2096 "parse.y"
                        {
			limits->family = AF_INET6;
		}
#line 4422 "y.tab.c"
    break;

  case 297: /* opt_limit_mta: STRING NUMBER  */
#line 2099 "parse.y"
                                {
			if (!limit_mta_set(limits, (yyvsp[-1].v.string), (yyvsp[0].v.number))) {
				yyerror("invalid mta limit keyword: %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
		}
#line 4435 "y.tab.c"
    break;

  case 300: /* opt_limit_scheduler: STRING NUMBER  */
#line 2113 "parse.y"
                                    {
			if (!strcmp((yyvsp[-1].v.string), "max-inflight")) {
				conf->sc_scheduler_max_inflight = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "max-evp-batch-size")) {
				conf->sc_scheduler_max_evp_batch_size = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "max-msg-batch-size")) {
				conf->sc_scheduler_max_msg_batch_size = (yyvsp[0].v.number);
			}
			else if (!strcmp((yyvsp[-1].v.string), "max-schedule")) {
				conf->sc_scheduler_max_schedule = (yyvsp[0].v.number);
			}
			else {
				yyerror("invalid scheduler limit keyword: %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
		}
#line 4460 "y.tab.c"
    break;

  case 303: /* opt_sock_listen: FILTER STRING  */
#line 2140 "parse.y"
                                {
			struct filter_config *fc;

			if (listen_opts.options & LO_FILTER) {
				yyerror("filter already specified");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			if ((fc = dict_get(conf->sc_filters_dict, (yyvsp[0].v.string))) == NULL) {
				yyerror("no filter exist with that name: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			fc->filter_subsystem |= FILTER_SUBSYSTEM_SMTP_IN;
			listen_opts.options |= LO_FILTER;
			listen_opts.filtername = (yyvsp[0].v.string);
		}
#line 4482 "y.tab.c"
    break;

  case 304: /* $@31: %empty  */
#line 2157 "parse.y"
                         {
			char	buffer[128];

			if (listen_opts.options & LO_FILTER) {
				yyerror("filter already specified");
				YYERROR;
			}

			do {
				(void)snprintf(buffer, sizeof buffer, "<dynchain:%08x>", last_dynchain_id++);
			} while (dict_check(conf->sc_filters_dict, buffer));

			listen_opts.options |= LO_FILTER;
			listen_opts.filtername = xstrdup(buffer);
			filter_config = xcalloc(1, sizeof *filter_config);
			filter_config->filter_type = FILTER_TYPE_CHAIN;
			filter_config->filter_subsystem |= FILTER_SUBSYSTEM_SMTP_IN;
			dict_init(&filter_config->chain_procs);
		}
#line 4506 "y.tab.c"
    break;

  case 305: /* opt_sock_listen: FILTER $@31 '{' optnl filter_list '}'  */
#line 2175 "parse.y"
                                            {
			dict_set(conf->sc_filters_dict, listen_opts.filtername, filter_config);
			filter_config = NULL;
		}
#line 4515 "y.tab.c"
    break;

  case 306: /* opt_sock_listen: MASK_SRC  */
#line 2179 "parse.y"
                           {
			if (config_lo_mask_source(&listen_opts)) {
				YYERROR;
			}
		}
#line 4525 "y.tab.c"
    break;

  case 307: /* opt_sock_listen: NO_DSN  */
#line 2184 "parse.y"
                                {
			if (listen_opts.options & LO_NODSN) {
				yyerror("no-dsn already specified");
				YYERROR;
			}
			listen_opts.options |= LO_NODSN;
			listen_opts.flags &= ~F_EXT_DSN;
		}
#line 4538 "y.tab.c"
    break;

  case 308: /* opt_sock_listen: TAG STRING  */
#line 2192 "parse.y"
                                                {
			if (listen_opts.options & LO_TAG) {
				yyerror("tag already specified");
				YYERROR;
			}
			listen_opts.options |= LO_TAG;

			if (strlen((yyvsp[0].v.string)) >= SMTPD_TAG_SIZE) {
				yyerror("tag name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			listen_opts.tag = (yyvsp[0].v.string);
		}
#line 4557 "y.tab.c"
    break;

  case 309: /* opt_if_listen: INET4  */
#line 2208 "parse.y"
                      {
			if (listen_opts.options & LO_FAMILY) {
				yyerror("address family already specified");
				YYERROR;
			}
			listen_opts.options |= LO_FAMILY;
			listen_opts.family = AF_INET;
		}
#line 4570 "y.tab.c"
    break;

  case 310: /* opt_if_listen: INET6  */
#line 2216 "parse.y"
                                        {
			if (listen_opts.options & LO_FAMILY) {
				yyerror("address family already specified");
				YYERROR;
			}
			listen_opts.options |= LO_FAMILY;
			listen_opts.family = AF_INET6;
		}
#line 4583 "y.tab.c"
    break;

  case 311: /* opt_if_listen: PORT STRING  */
#line 2224 "parse.y"
                                                {
			struct servent	*servent;

			if (listen_opts.options & LO_PORT) {
				yyerror("port already specified");
				YYERROR;
			}
			listen_opts.options |= LO_PORT;

			servent = getservbyname((yyvsp[0].v.string), "tcp");
			if (servent == NULL) {
				yyerror("invalid port: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			listen_opts.port = ntohs(servent->s_port);
		}
#line 4606 "y.tab.c"
    break;

  case 312: /* opt_if_listen: PORT SMTP  */
#line 2242 "parse.y"
                                                {
			struct servent *servent;

			if (listen_opts.options & LO_PORT) {
				yyerror("port already specified");
				YYERROR;
			}
			listen_opts.options |= LO_PORT;

			servent = getservbyname("smtp", "tcp");
			if (servent == NULL) {
				yyerror("invalid port: smtp");
				YYERROR;
			}
			listen_opts.port = ntohs(servent->s_port);
		}
#line 4627 "y.tab.c"
    break;

  case 313: /* opt_if_listen: PORT SMTPS  */
#line 2258 "parse.y"
                                                {
			struct servent *servent;

			if (listen_opts.options & LO_PORT) {
				yyerror("port already specified");
				YYERROR;
			}
			listen_opts.options |= LO_PORT;

			servent = getservbyname("smtps", "tcp");
			if (servent == NULL) {
				yyerror("invalid port: smtps");
				YYERROR;
			}
			listen_opts.port = ntohs(servent->s_port);
		}
#line 4648 "y.tab.c"
    break;

  case 314: /* opt_if_listen: PORT NUMBER  */
#line 2274 "parse.y"
                                                {
			if (listen_opts.options & LO_PORT) {
				yyerror("port already specified");
				YYERROR;
			}
			listen_opts.options |= LO_PORT;

			if ((yyvsp[0].v.number) <= 0 || (yyvsp[0].v.number) > (int)USHRT_MAX) {
				yyerror("invalid port: %" PRId64, (yyvsp[0].v.number));
				YYERROR;
			}
			listen_opts.port = (yyvsp[0].v.number);
		}
#line 4666 "y.tab.c"
    break;

  case 315: /* opt_if_listen: FILTER STRING  */
#line 2287 "parse.y"
                                                {
			struct filter_config *fc;

			if (listen_opts.options & LO_FILTER) {
				yyerror("filter already specified");
				YYERROR;
			}
			if ((fc = dict_get(conf->sc_filters_dict, (yyvsp[0].v.string))) == NULL) {
				yyerror("no filter exist with that name: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			fc->filter_subsystem |= FILTER_SUBSYSTEM_SMTP_IN;
			listen_opts.options |= LO_FILTER;
			listen_opts.filtername = (yyvsp[0].v.string);
		}
#line 4687 "y.tab.c"
    break;

  case 316: /* $@32: %empty  */
#line 2303 "parse.y"
                         {
			char	buffer[128];

			if (listen_opts.options & LO_FILTER) {
				yyerror("filter already specified");
				YYERROR;
			}

			do {
				(void)snprintf(buffer, sizeof buffer, "<dynchain:%08x>", last_dynchain_id++);
			} while (dict_check(conf->sc_filters_dict, buffer));

			listen_opts.options |= LO_FILTER;
			listen_opts.filtername = xstrdup(buffer);
			filter_config = xcalloc(1, sizeof *filter_config);
			filter_config->filter_type = FILTER_TYPE_CHAIN;
			filter_config->filter_subsystem |= FILTER_SUBSYSTEM_SMTP_IN;
			dict_init(&filter_config->chain_procs);
		}
#line 4711 "y.tab.c"
    break;

  case 317: /* opt_if_listen: FILTER $@32 '{' optnl filter_list '}'  */
#line 2321 "parse.y"
                                            {
			dict_set(conf->sc_filters_dict, listen_opts.filtername, filter_config);
			filter_config = NULL;
		}
#line 4720 "y.tab.c"
    break;

  case 318: /* opt_if_listen: SMTPS  */
#line 2325 "parse.y"
                                                {
			if (listen_opts.options & LO_SSL) {
				yyerror("TLS mode already specified");
				YYERROR;
			}
			listen_opts.options |= LO_SSL;
			listen_opts.ssl = F_SMTPS;
		}
#line 4733 "y.tab.c"
    break;

  case 319: /* opt_if_listen: SMTPS VERIFY  */
#line 2333 "parse.y"
                                                {
			if (listen_opts.options & LO_SSL) {
				yyerror("TLS mode already specified");
				YYERROR;
			}
			listen_opts.options |= LO_SSL;
			listen_opts.ssl = F_SMTPS|F_TLS_VERIFY;
		}
#line 4746 "y.tab.c"
    break;

  case 320: /* opt_if_listen: TLS  */
#line 2341 "parse.y"
                                                {
			if (listen_opts.options & LO_SSL) {
				yyerror("TLS mode already specified");
				YYERROR;
			}
			listen_opts.options |= LO_SSL;
			listen_opts.ssl = F_STARTTLS;
		}
#line 4759 "y.tab.c"
    break;

  case 321: /* opt_if_listen: TLS_REQUIRE  */
#line 2349 "parse.y"
                                                {
			if (listen_opts.options & LO_SSL) {
				yyerror("TLS mode already specified");
				YYERROR;
			}
			listen_opts.options |= LO_SSL;
			listen_opts.ssl = F_STARTTLS|F_STARTTLS_REQUIRE;
		}
#line 4772 "y.tab.c"
    break;

  case 322: /* opt_if_listen: TLS_REQUIRE VERIFY  */
#line 2357 "parse.y"
                                                {
			if (listen_opts.options & LO_SSL) {
				yyerror("TLS mode already specified");
				YYERROR;
			}
			listen_opts.options |= LO_SSL;
			listen_opts.ssl = F_STARTTLS|F_STARTTLS_REQUIRE|F_TLS_VERIFY;
		}
#line 4785 "y.tab.c"
    break;

  case 323: /* opt_if_listen: CIPHERS STRING  */
#line 2365 "parse.y"
                                 {
			if (listen_opts.tls_ciphers) {
				yyerror("ciphers already specified");
				YYERROR;
			}
			listen_opts.tls_ciphers = (yyvsp[0].v.string);
		}
#line 4797 "y.tab.c"
    break;

  case 324: /* opt_if_listen: PROTOCOLS STRING  */
#line 2372 "parse.y"
                                   {
			if (listen_opts.tls_protocols) {
				yyerror("protocols already specified");
				YYERROR;
			}
			listen_opts.tls_protocols = (yyvsp[0].v.string);
		}
#line 4809 "y.tab.c"
    break;

  case 325: /* opt_if_listen: PKI STRING  */
#line 2379 "parse.y"
                                                {
			if (listen_opts.pkicount == PKI_MAX) {
				yyerror("too many pki specified");
				YYERROR;
			}
			listen_opts.pki[listen_opts.pkicount++] = (yyvsp[0].v.string);
		}
#line 4821 "y.tab.c"
    break;

  case 326: /* opt_if_listen: CA STRING  */
#line 2386 "parse.y"
                                                {
			if (listen_opts.options & LO_CA) {
				yyerror("ca already specified");
				YYERROR;
			}
			listen_opts.options |= LO_CA;
			listen_opts.ca = (yyvsp[0].v.string);
		}
#line 4834 "y.tab.c"
    break;

  case 327: /* opt_if_listen: AUTH  */
#line 2394 "parse.y"
                                                {
			if (listen_opts.options & LO_AUTH) {
				yyerror("auth already specified");
				YYERROR;
			}
			listen_opts.options |= LO_AUTH;
			listen_opts.auth = F_AUTH|F_AUTH_REQUIRE;
		}
#line 4847 "y.tab.c"
    break;

  case 328: /* opt_if_listen: AUTH_OPTIONAL  */
#line 2402 "parse.y"
                                                {
			if (listen_opts.options & LO_AUTH) {
				yyerror("auth already specified");
				YYERROR;
			}
			listen_opts.options |= LO_AUTH;
			listen_opts.auth = F_AUTH;
		}
#line 4860 "y.tab.c"
    break;

  case 329: /* opt_if_listen: AUTH tables  */
#line 2410 "parse.y"
                                                {
			if (listen_opts.options & LO_AUTH) {
				yyerror("auth already specified");
				YYERROR;
			}
			listen_opts.options |= LO_AUTH;
			listen_opts.authtable = (yyvsp[0].v.table);
			listen_opts.auth = F_AUTH|F_AUTH_REQUIRE;
		}
#line 4874 "y.tab.c"
    break;

  case 330: /* opt_if_listen: AUTH_OPTIONAL tables  */
#line 2419 "parse.y"
                                                {
			if (listen_opts.options & LO_AUTH) {
				yyerror("auth already specified");
				YYERROR;
			}
			listen_opts.options |= LO_AUTH;
			listen_opts.authtable = (yyvsp[0].v.table);
			listen_opts.auth = F_AUTH;
		}
#line 4888 "y.tab.c"
    break;

  case 331: /* opt_if_listen: TAG STRING  */
#line 2428 "parse.y"
                                                {
			if (listen_opts.options & LO_TAG) {
				yyerror("tag already specified");
				YYERROR;
			}
			listen_opts.options |= LO_TAG;

			if (strlen((yyvsp[0].v.string)) >= SMTPD_TAG_SIZE) {
       				yyerror("tag name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			listen_opts.tag = (yyvsp[0].v.string);
		}
#line 4907 "y.tab.c"
    break;

  case 332: /* opt_if_listen: HOSTNAME STRING  */
#line 2442 "parse.y"
                                        {
			if (listen_opts.options & LO_HOSTNAME) {
				yyerror("hostname already specified");
				YYERROR;
			}
			listen_opts.options |= LO_HOSTNAME;

			listen_opts.hostname = (yyvsp[0].v.string);
		}
#line 4921 "y.tab.c"
    break;

  case 333: /* opt_if_listen: HOSTNAMES tables  */
#line 2451 "parse.y"
                                        {
			struct table	*t = (yyvsp[0].v.table);

			if (listen_opts.options & LO_HOSTNAMES) {
				yyerror("hostnames already specified");
				YYERROR;
			}
			listen_opts.options |= LO_HOSTNAMES;

			if (!table_check_use(t, T_DYNAMIC|T_HASH, K_ADDRNAME)) {
				yyerror("invalid use of table \"%s\" as "
				    "HOSTNAMES parameter", t->t_name);
				YYERROR;
			}
			listen_opts.hostnametable = t;
		}
#line 4942 "y.tab.c"
    break;

  case 334: /* opt_if_listen: MASK_SRC  */
#line 2467 "parse.y"
                                {
			if (config_lo_mask_source(&listen_opts)) {
				YYERROR;
			}
		}
#line 4952 "y.tab.c"
    break;

  case 335: /* opt_if_listen: RECEIVEDAUTH  */
#line 2472 "parse.y"
                                {
			if (listen_opts.options & LO_RECEIVEDAUTH) {
				yyerror("received-auth already specified");
				YYERROR;
			}
			listen_opts.options |= LO_RECEIVEDAUTH;
			listen_opts.flags |= F_RECEIVEDAUTH;
		}
#line 4965 "y.tab.c"
    break;

  case 336: /* opt_if_listen: NO_DSN  */
#line 2480 "parse.y"
                                {
			if (listen_opts.options & LO_NODSN) {
				yyerror("no-dsn already specified");
				YYERROR;
			}
			listen_opts.options |= LO_NODSN;
			listen_opts.flags &= ~F_EXT_DSN;
		}
#line 4978 "y.tab.c"
    break;

  case 337: /* opt_if_listen: PROXY_V2  */
#line 2488 "parse.y"
                                {
			if (listen_opts.options & LO_PROXY) {
				yyerror("proxy-v2 already specified");
				YYERROR;
			}
			listen_opts.options |= LO_PROXY;
			listen_opts.flags |= F_PROXY;
		}
#line 4991 "y.tab.c"
    break;

  case 338: /* opt_if_listen: SENDERS tables  */
#line 2496 "parse.y"
                                        {
			struct table	*t = (yyvsp[0].v.table);

			if (listen_opts.options & LO_SENDERS) {
				yyerror("senders already specified");
				YYERROR;
			}
			listen_opts.options |= LO_SENDERS;

			if (!table_check_use(t, T_DYNAMIC|T_HASH, K_MAILADDRMAP)) {
				yyerror("invalid use of table \"%s\" as "
				    "SENDERS parameter", t->t_name);
				YYERROR;
			}
			listen_opts.sendertable = t;
		}
#line 5012 "y.tab.c"
    break;

  case 339: /* opt_if_listen: SENDERS tables MASQUERADE  */
#line 2512 "parse.y"
                                                {
			struct table	*t = (yyvsp[-1].v.table);

			if (listen_opts.options & LO_SENDERS) {
				yyerror("senders already specified");
				YYERROR;
			}
			listen_opts.options |= LO_SENDERS|LO_MASQUERADE;

			if (!table_check_use(t, T_DYNAMIC|T_HASH, K_MAILADDRMAP)) {
				yyerror("invalid use of table \"%s\" as "
				    "SENDERS parameter", t->t_name);
				YYERROR;
			}
			listen_opts.sendertable = t;
		}
#line 5033 "y.tab.c"
    break;

  case 342: /* socket_listener: SOCKET sock_listen  */
#line 2534 "parse.y"
                                     {
			if (conf->sc_sock_listener) {
				yyerror("socket listener already configured");
				YYERROR;
			}
			create_sock_listener(&listen_opts);
		}
#line 5045 "y.tab.c"
    break;

  case 343: /* if_listener: STRING if_listen  */
#line 2543 "parse.y"
                                   {
			listen_opts.ifx = (yyvsp[-1].v.string);
			create_if_listener(&listen_opts);
		}
#line 5054 "y.tab.c"
    break;

  case 348: /* $@33: %empty  */
#line 2558 "parse.y"
                         {
			memset(&listen_opts, 0, sizeof listen_opts);
			listen_opts.family = AF_UNSPEC;
			listen_opts.flags |= F_EXT_DSN;
		}
#line 5064 "y.tab.c"
    break;

  case 349: /* listen: LISTEN $@33 ON listener_type  */
#line 2562 "parse.y"
                                   {
			free(listen_opts.tls_protocols);
			free(listen_opts.tls_ciphers);
			memset(&listen_opts, 0, sizeof listen_opts);
		}
#line 5074 "y.tab.c"
    break;

  case 350: /* table: TABLE STRING STRING  */
#line 2569 "parse.y"
                                        {
			char *p, *backend, *config;

			p = (yyvsp[0].v.string);
			if (*p == '/') {
				backend = "static";
				config = (yyvsp[0].v.string);
			}
			else {
				backend = (yyvsp[0].v.string);
				config = NULL;
				for (p = (yyvsp[0].v.string); *p && *p != ':'; p++)
					;
				if (*p == ':') {
					*p = '\0';
					backend = (yyvsp[0].v.string);
					config  = p+1;
				}
			}
			if (config != NULL && *config != '/') {
				yyerror("invalid backend parameter for table: %s",
				    (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			table = table_create(conf, backend, (yyvsp[-1].v.string), config);
			if (!table_config(table)) {
				yyerror("invalid configuration file %s for table %s",
				    config, table->t_name);
				free((yyvsp[-1].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			table = NULL;
			free((yyvsp[-1].v.string));
			free((yyvsp[0].v.string));
		}
#line 5117 "y.tab.c"
    break;

  case 351: /* $@34: %empty  */
#line 2607 "parse.y"
                               {
			table = table_create(conf, "static", (yyvsp[0].v.string), NULL);
			free((yyvsp[0].v.string));
		}
#line 5126 "y.tab.c"
    break;

  case 352: /* table: TABLE STRING $@34 '{' optnl tableval_list '}'  */
#line 2610 "parse.y"
                                              {
			table = NULL;
		}
#line 5134 "y.tab.c"
    break;

  case 353: /* tablenew: STRING  */
#line 2615 "parse.y"
                                                {
			struct table	*t;

			t = table_create(conf, "static", NULL, NULL);
			table_add(t, (yyvsp[0].v.string), NULL);
			free((yyvsp[0].v.string));
			(yyval.v.table) = t;
		}
#line 5147 "y.tab.c"
    break;

  case 354: /* $@35: %empty  */
#line 2623 "parse.y"
                                                {
			table = table_create(conf, "static", NULL, NULL);
		}
#line 5155 "y.tab.c"
    break;

  case 355: /* tablenew: '{' optnl $@35 tableval_list '}'  */
#line 2625 "parse.y"
                                                {
			(yyval.v.table) = table;
			table = NULL;
		}
#line 5164 "y.tab.c"
    break;

  case 356: /* tableref: '<' STRING '>'  */
#line 2631 "parse.y"
                                                {
			struct table	*t;

			if ((t = table_find(conf, (yyvsp[-1].v.string))) == NULL) {
				yyerror("no such table: %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
			(yyval.v.table) = t;
		}
#line 5180 "y.tab.c"
    break;

  case 357: /* tables: tablenew  */
#line 2644 "parse.y"
                                                { (yyval.v.table) = (yyvsp[0].v.table); }
#line 5186 "y.tab.c"
    break;

  case 358: /* tables: tableref  */
#line 2645 "parse.y"
                                                { (yyval.v.table) = (yyvsp[0].v.table); }
#line 5192 "y.tab.c"
    break;


#line 5196 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2649 "parse.y"


struct keywords {
	const char	*k_name;
	int		 k_val;
};

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*msg;

	file->errors++;
	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap) == -1)
		fatalx("yyerror vasprintf");
	va_end(ap);
	logit(LOG_CRIT, "%s:%d: %s", file->name, yylval.lineno, msg);
	free(msg);
	return (0);
}

int
kw_cmp(const void *k, const void *e)
{
	return (strcmp(k, ((const struct keywords *)e)->k_name));
}

int
lookup(char *s)
{
	/* this has to be sorted always */
	static const struct keywords keywords[] = {
		{ "action",		ACTION },
		{ "admd",		ADMD },
		{ "alias",		ALIAS },
		{ "any",		ANY },
		{ "auth",		AUTH },
		{ "auth-optional",     	AUTH_OPTIONAL },
		{ "backup",		BACKUP },
		{ "bounce",		BOUNCE },
		{ "bypass",		BYPASS },
		{ "ca",			CA },
		{ "cert",		CERT },
		{ "chain",		CHAIN },
		{ "chroot",		CHROOT },
		{ "ciphers",		CIPHERS },
		{ "commit",		COMMIT },
		{ "compression",	COMPRESSION },
		{ "connect",		CONNECT },
		{ "data",		DATA },
		{ "data-line",		DATA_LINE },
		{ "dhe",		DHE },
		{ "disconnect",		DISCONNECT },
		{ "domain",		DOMAIN },
		{ "ehlo",		EHLO },
		{ "encryption",		ENCRYPTION },
		{ "expand-only",      	EXPAND_ONLY },
		{ "fcrdns",		FCRDNS },
		{ "filter",		FILTER },
		{ "for",		FOR },
		{ "forward-only",      	FORWARD_ONLY },
		{ "from",		FROM },
		{ "group",		GROUP },
		{ "helo",		HELO },
		{ "helo-src",       	HELO_SRC },
		{ "host",		HOST },
		{ "hostname",		HOSTNAME },
		{ "hostnames",		HOSTNAMES },
		{ "include",		INCLUDE },
		{ "inet4",		INET4 },
		{ "inet6",		INET6 },
		{ "junk",		JUNK },
		{ "key",		KEY },
		{ "limit",		LIMIT },
		{ "listen",		LISTEN },
		{ "lmtp",		LMTP },
		{ "local",		LOCAL },
		{ "mail-from",		MAIL_FROM },
		{ "maildir",		MAILDIR },
		{ "mask-src",		MASK_SRC },
		{ "masquerade",		MASQUERADE },
		{ "match",		MATCH },
		{ "max-deferred",  	MAX_DEFERRED },
		{ "max-message-size",  	MAX_MESSAGE_SIZE },
		{ "mbox",		MBOX },
		{ "mda",		MDA },
		{ "mta",		MTA },
		{ "mx",			MX },
		{ "no-dsn",		NO_DSN },
		{ "no-verify",		NO_VERIFY },
		{ "noop",		NOOP },
		{ "on",			ON },
		{ "phase",		PHASE },
		{ "pki",		PKI },
		{ "port",		PORT },
		{ "proc",		PROC },
		{ "proc-exec",		PROC_EXEC },
		{ "protocols",		PROTOCOLS },
		{ "proxy-v2",		PROXY_V2 },
		{ "queue",		QUEUE },
		{ "quit",		QUIT },
		{ "rcpt-to",		RCPT_TO },
		{ "rdns",		RDNS },
		{ "received-auth",     	RECEIVEDAUTH },
		{ "recipient",		RECIPIENT },
		{ "regex",		REGEX },
		{ "reject",		REJECT },
		{ "relay",		RELAY },
		{ "report",		REPORT },
		{ "rewrite",		REWRITE },
		{ "rset",		RSET },
		{ "scheduler",		SCHEDULER },
		{ "senders",   		SENDERS },
		{ "smtp",		SMTP },
		{ "smtp-in",		SMTP_IN },
		{ "smtp-out",		SMTP_OUT },
		{ "smtps",		SMTPS },
		{ "socket",		SOCKET },
		{ "src",		SRC },
		{ "srs",		SRS },
		{ "sub-addr-delim",	SUB_ADDR_DELIM },
		{ "table",		TABLE },
		{ "tag",		TAG },
		{ "tagged",		TAGGED },
		{ "tls",		TLS },
		{ "tls-require",       	TLS_REQUIRE },
		{ "ttl",		TTL },
		{ "user",		USER },
		{ "userbase",		USERBASE },
		{ "verify",		VERIFY },
		{ "virtual",		VIRTUAL },
		{ "warn-interval",	WARN_INTERVAL },
		{ "wrapper",		WRAPPER },
	};
	const struct keywords	*p;

	p = bsearch(s, keywords, sizeof(keywords)/sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	if (p)
		return (p->k_val);
	else
		return (STRING);
}

#define START_EXPAND	1
#define DONE_EXPAND	2

static int	expanding;

int
igetc(void)
{
	int	c;

	while (1) {
		if (file->ungetpos > 0)
			c = file->ungetbuf[--file->ungetpos];
		else
			c = getc(file->stream);

		if (c == START_EXPAND)
			expanding = 1;
		else if (c == DONE_EXPAND)
			expanding = 0;
		else
			break;
	}
	return (c);
}

int
lgetc(int quotec)
{
	int		c, next;

	if (quotec) {
		if ((c = igetc()) == EOF) {
			yyerror("reached end of file while parsing "
			    "quoted string");
			if (file == topfile || popfile() == EOF)
				return (EOF);
			return (quotec);
		}
		return (c);
	}

	while ((c = igetc()) == '\\') {
		next = igetc();
		if (next != '\n') {
			c = next;
			break;
		}
		yylval.lineno = file->lineno;
		file->lineno++;
	}

	if (c == EOF) {
		/*
		 * Fake EOL when hit EOF for the first time. This gets line
		 * count right if last line in included file is syntactically
		 * invalid and has no newline.
		 */
		if (file->eof_reached == 0) {
			file->eof_reached = 1;
			return ('\n');
		}
		while (c == EOF) {
			if (file == topfile || popfile() == EOF)
				return (EOF);
			c = igetc();
		}
	}
	return (c);
}

void
lungetc(int c)
{
	if (c == EOF)
		return;

	if (file->ungetpos >= file->ungetsize) {
		void *p = reallocarray(file->ungetbuf, file->ungetsize, 2);
		if (p == NULL)
			fatal("%s", __func__);
		file->ungetbuf = p;
		file->ungetsize *= 2;
	}
	file->ungetbuf[file->ungetpos++] = c;
}

int
findeol(void)
{
	int	c;

	/* skip to either EOF or the first real EOL */
	while (1) {
		c = lgetc(0);
		if (c == '\n') {
			file->lineno++;
			break;
		}
		if (c == EOF)
			break;
	}
	return (ERROR);
}

int
yylex(void)
{
	char	 buf[8096];
	char	*p, *val;
	int	 quotec, next, c;
	int	 token;

top:
	p = buf;
	while ((c = lgetc(0)) == ' ' || c == '\t')
		; /* nothing */

	yylval.lineno = file->lineno;
	if (c == '#')
		while ((c = lgetc(0)) != '\n' && c != EOF)
			; /* nothing */
	if (c == '$' && !expanding) {
		while (1) {
			if ((c = lgetc(0)) == EOF)
				return (0);

			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			if (isalnum(c) || c == '_') {
				*p++ = c;
				continue;
			}
			*p = '\0';
			lungetc(c);
			break;
		}
		val = symget(buf);
		if (val == NULL) {
			yyerror("macro '%s' not defined", buf);
			return (findeol());
		}
		p = val + strlen(val) - 1;
		lungetc(DONE_EXPAND);
		while (p >= val) {
			lungetc((unsigned char)*p);
			p--;
		}
		lungetc(START_EXPAND);
		goto top;
	}

	switch (c) {
	case '\'':
	case '"':
		quotec = c;
		while (1) {
			if ((c = lgetc(quotec)) == EOF)
				return (0);
			if (c == '\n') {
				file->lineno++;
				continue;
			} else if (c == '\\') {
				if ((next = lgetc(quotec)) == EOF)
					return (0);
				if (next == quotec || next == ' ' ||
				    next == '\t')
					c = next;
				else if (next == '\n') {
					file->lineno++;
					continue;
				} else
					lungetc(next);
			} else if (c == quotec) {
				*p = '\0';
				break;
			} else if (c == '\0') {
				yyerror("syntax error");
				return (findeol());
			}
			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			*p++ = c;
		}
		yylval.v.string = strdup(buf);
		if (yylval.v.string == NULL)
			fatal("%s", __func__);
		return (STRING);
	}

#define allowed_to_end_number(x) \
	(isspace(x) || x == ')' || x ==',' || x == '/' || x == '}' || x == '=')

	if (c == '-' || isdigit(c)) {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && isdigit(c));
		lungetc(c);
		if (p == buf + 1 && buf[0] == '-')
			goto nodigits;
		if (c == EOF || allowed_to_end_number(c)) {
			const char *errstr = NULL;

			*p = '\0';
			yylval.v.number = strtonum(buf, LLONG_MIN,
			    LLONG_MAX, &errstr);
			if (errstr) {
				yyerror("\"%s\" invalid number: %s",
				    buf, errstr);
				return (findeol());
			}
			return (NUMBER);
		} else {
nodigits:
			while (p > buf + 1)
				lungetc((unsigned char)*--p);
			c = (unsigned char)*--p;
			if (c == '-')
				return (c);
		}
	}

	if (c == '=') {
		if ((c = lgetc(0)) != EOF && c == '>')
			return (ARROW);
		lungetc(c);
		c = '=';
	}

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && x != '<' && x != '>' && \
	x != '!' && x != '=' && x != '#' && \
	x != ','))

	if (isalnum(c) || c == ':' || c == '_') {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && (allowed_in_string(c)));
		lungetc(c);
		*p = '\0';
		if ((token = lookup(buf)) == STRING)
			if ((yylval.v.string = strdup(buf)) == NULL)
				fatal("%s", __func__);
		return (token);
	}
	if (c == '\n') {
		yylval.lineno = file->lineno;
		file->lineno++;
	}
	if (c == EOF)
		return (0);
	return (c);
}

int
check_file_secrecy(int fd, const char *fname)
{
	struct stat	st;

	if (fstat(fd, &st)) {
		log_warn("warn: cannot stat %s", fname);
		return (-1);
	}
	if (st.st_uid != 0 && st.st_uid != getuid()) {
		log_warnx("warn: %s: owner not root or current user", fname);
		return (-1);
	}
	if (st.st_mode & (S_IWGRP | S_IXGRP | S_IRWXO)) {
		log_warnx("warn: %s: group/world readable/writeable", fname);
		return (-1);
	}
	return (0);
}

struct file *
pushfile(const char *name, int secret)
{
	struct file	*nfile;

	if ((nfile = calloc(1, sizeof(struct file))) == NULL) {
		log_warn("%s", __func__);
		return (NULL);
	}
	if ((nfile->name = strdup(name)) == NULL) {
		log_warn("%s", __func__);
		free(nfile);
		return (NULL);
	}
	if ((nfile->stream = fopen(nfile->name, "r")) == NULL) {
		log_warn("%s: %s", __func__, nfile->name);
		free(nfile->name);
		free(nfile);
		return (NULL);
	} else if (secret &&
	    check_file_secrecy(fileno(nfile->stream), nfile->name)) {
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return (NULL);
	}
	nfile->lineno = TAILQ_EMPTY(&files) ? 1 : 0;
	nfile->ungetsize = 16;
	nfile->ungetbuf = malloc(nfile->ungetsize);
	if (nfile->ungetbuf == NULL) {
		log_warn("%s", __func__);
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return (NULL);
	}
	TAILQ_INSERT_TAIL(&files, nfile, entry);
	return (nfile);
}

int
popfile(void)
{
	struct file	*prev;

	if ((prev = TAILQ_PREV(file, files, entry)) != NULL)
		prev->errors += file->errors;

	TAILQ_REMOVE(&files, file, entry);
	fclose(file->stream);
	free(file->name);
	free(file->ungetbuf);
	free(file);
	file = prev;
	return (file ? 0 : EOF);
}

int
parse_config(struct smtpd *x_conf, const char *filename, int opts)
{
	struct sym     *sym, *next;

	conf = x_conf;
	errors = 0;

	if ((file = pushfile(filename, 0)) == NULL) {
		purge_config(PURGE_EVERYTHING);
		return (-1);
	}
	topfile = file;

	/*
	 * parse configuration
	 */
	setservent(1);
	yyparse();
	errors = file->errors;
	popfile();
	endservent();

	/* If the socket listener was not configured, create a default one. */
	if (!conf->sc_sock_listener) {
		memset(&listen_opts, 0, sizeof listen_opts);
		listen_opts.family = AF_UNSPEC;
		listen_opts.flags |= F_EXT_DSN;
		create_sock_listener(&listen_opts);
	}

	/* Free macros and check which have not been used. */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if ((conf->sc_opts & SMTPD_OPT_VERBOSE) && !sym->used)
			fprintf(stderr, "warning: macro '%s' not "
			    "used\n", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (TAILQ_EMPTY(conf->sc_rules)) {
		log_warnx("warn: no rules, nothing to do");
		errors++;
	}

	if (errors) {
		purge_config(PURGE_EVERYTHING);
		return (-1);
	}

	return (0);
}

int
symset(const char *nam, const char *val, int persist)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0)
			break;
	}

	if (sym != NULL) {
		if (sym->persist == 1)
			return (0);
		else {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}
	if ((sym = calloc(1, sizeof(*sym))) == NULL)
		return (-1);

	sym->nam = strdup(nam);
	if (sym->nam == NULL) {
		free(sym);
		return (-1);
	}
	sym->val = strdup(val);
	if (sym->val == NULL) {
		free(sym->nam);
		free(sym);
		return (-1);
	}
	sym->used = 0;
	sym->persist = persist;
	TAILQ_INSERT_TAIL(&symhead, sym, entry);
	return (0);
}

int
cmdline_symset(char *s)
{
	char	*sym, *val;
	int	ret;

	if ((val = strrchr(s, '=')) == NULL)
		return (-1);
	sym = strndup(s, val - s);
	if (sym == NULL)
		fatalx("%s: strndup", __func__);
	ret = symset(sym, val + 1, 1);
	free(sym);

	return (ret);
}

char *
symget(const char *nam)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0) {
			sym->used = 1;
			return (sym->val);
		}
	}
	return (NULL);
}

static void
create_sock_listener(struct listen_opts *lo)
{
	struct listener *l = xcalloc(1, sizeof(*l));
	lo->hostname = conf->sc_hostname;
	l->ss.ss_family = AF_LOCAL;
	l->ss.ss_len = sizeof(struct sockaddr *);
	l->local = 1;
	conf->sc_sock_listener = l;
	config_listener(l, lo);
}

static void
create_if_listener(struct listen_opts *lo)
{
	uint16_t	flags;

	if (lo->port != 0 && lo->ssl == F_SSL)
		fatalx("invalid listen option: tls/smtps on same port");

	if (lo->auth != 0 && !lo->ssl)
		fatalx("invalid listen option: auth requires tls/smtps");

	if (lo->pkicount && !lo->ssl)
		fatalx("invalid listen option: pki requires tls/smtps");
	if (lo->pkicount == 0 && lo->ssl)
		fatalx("invalid listen option: pki required for tls/smtps");

	flags = lo->flags;

	if (lo->port) {
		lo->flags = lo->ssl|lo->auth|flags;
		lo->port = htons(lo->port);
	}
	else {
		if (lo->ssl & F_SMTPS) {
			lo->port = htons(465);
			lo->flags = F_SMTPS|lo->auth|flags;
		}

		if (!lo->ssl || (lo->ssl & F_STARTTLS)) {
			lo->port = htons(25);
			lo->flags = lo->auth|flags;
			if (lo->ssl & F_STARTTLS)
				lo->flags |= F_STARTTLS;
		}
	}

	if (interface(lo))
		return;
	if (host_v4(lo))
		return;
	if (host_v6(lo))
		return;
	if (host_dns(lo))
		return;

	fatalx("invalid virtual ip or interface: %s", lo->ifx);
}

static void
config_listener(struct listener *h,  struct listen_opts *lo)
{
	int i;

	h->fd = -1;
	h->port = lo->port;
	h->flags = lo->flags;

	if (lo->hostname == NULL)
		lo->hostname = conf->sc_hostname;

	if (lo->options & LO_FILTER) {
		h->flags |= F_FILTERED;
		(void)strlcpy(h->filter_name,
		    lo->filtername,
		    sizeof(h->filter_name));
	}

	if (lo->authtable != NULL)
		(void)strlcpy(h->authtable, lo->authtable->t_name, sizeof(h->authtable));

	h->pkicount = lo->pkicount;
	if (h->pkicount) {
		h->pki = calloc(h->pkicount, sizeof(*h->pki));
		if (h->pki == NULL)
			fatal("calloc");
	}
	for (i = 0; i < lo->pkicount; i++) {
		h->pki[i] = dict_get(conf->sc_pki_dict, lo->pki[i]);
		if (h->pki[i] == NULL) {
			log_warnx("pki name not found: %s", lo->pki[i]);
			fatalx(NULL);
		}
	}

	if (lo->tls_ciphers != NULL &&
	    (h->tls_ciphers = strdup(lo->tls_ciphers)) == NULL) {
		fatal("strdup");
	}

	if (lo->tls_protocols != NULL &&
	    (h->tls_protocols = strdup(lo->tls_protocols)) == NULL) {
		fatal("strdup");
	}

	if (lo->ca != NULL) {
		if (!lowercase(h->ca_name, lo->ca, sizeof(h->ca_name))) {
			log_warnx("ca name too long: %s", lo->ca);
			fatalx(NULL);
		}
		if (dict_get(conf->sc_ca_dict, h->ca_name) == NULL) {
			log_warnx("ca name not found: %s", lo->ca);
			fatalx(NULL);
		}
	}
	if (lo->tag != NULL)
		(void)strlcpy(h->tag, lo->tag, sizeof(h->tag));

	(void)strlcpy(h->hostname, lo->hostname, sizeof(h->hostname));
	if (lo->hostnametable)
		(void)strlcpy(h->hostnametable, lo->hostnametable->t_name, sizeof(h->hostnametable));
	if (lo->sendertable) {
		(void)strlcpy(h->sendertable, lo->sendertable->t_name, sizeof(h->sendertable));
		if (lo->options & LO_MASQUERADE)
			h->flags |= F_MASQUERADE;
	}

	if (lo->ssl & F_TLS_VERIFY)
		h->flags |= F_TLS_VERIFY;

	if (lo->ssl & F_STARTTLS_REQUIRE)
		h->flags |= F_STARTTLS_REQUIRE;
	
	if (h != conf->sc_sock_listener)
		TAILQ_INSERT_TAIL(conf->sc_listeners, h, entry);
}

static int
host_v4(struct listen_opts *lo)
{
	struct in_addr		 ina;
	struct sockaddr_in	*sain;
	struct listener		*h;

	if (lo->family != AF_UNSPEC && lo->family != AF_INET)
		return (0);

	memset(&ina, 0, sizeof(ina));
	if (inet_pton(AF_INET, lo->ifx, &ina) != 1)
		return (0);

	h = xcalloc(1, sizeof(*h));
	sain = (struct sockaddr_in *)&h->ss;
	sain->sin_len = sizeof(struct sockaddr_in);
	sain->sin_family = AF_INET;
	sain->sin_addr.s_addr = ina.s_addr;
	sain->sin_port = lo->port;

	if (sain->sin_addr.s_addr == htonl(INADDR_LOOPBACK))
		h->local = 1;
	config_listener(h,  lo);

	return (1);
}

static int
host_v6(struct listen_opts *lo)
{
	struct in6_addr		 ina6;
	struct sockaddr_in6	*sin6;
	struct listener		*h;

	if (lo->family != AF_UNSPEC && lo->family != AF_INET6)
		return (0);

	memset(&ina6, 0, sizeof(ina6));
	if (inet_pton(AF_INET6, lo->ifx, &ina6) != 1)
		return (0);

	h = xcalloc(1, sizeof(*h));
	sin6 = (struct sockaddr_in6 *)&h->ss;
	sin6->sin6_len = sizeof(struct sockaddr_in6);
	sin6->sin6_family = AF_INET6;
	sin6->sin6_port = lo->port;
	memcpy(&sin6->sin6_addr, &ina6, sizeof(ina6));

	if (IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr))
		h->local = 1;
	config_listener(h,  lo);

	return (1);
}

static int
host_dns(struct listen_opts *lo)
{
	struct addrinfo		 hints, *res0, *res;
	int			 error, cnt = 0;
	struct sockaddr_in	*sain;
	struct sockaddr_in6	*sin6;
	struct listener		*h;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = lo->family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_ADDRCONFIG;
	error = getaddrinfo(lo->ifx, NULL, &hints, &res0);
	if (error == EAI_AGAIN || error == EAI_NODATA || error == EAI_NONAME)
		return (0);
	if (error) {
		log_warnx("warn: host_dns: could not parse \"%s\": %s", lo->ifx,
		    gai_strerror(error));
		return (-1);
	}

	for (res = res0; res; res = res->ai_next) {
		if (res->ai_family != AF_INET &&
		    res->ai_family != AF_INET6)
			continue;
		h = xcalloc(1, sizeof(*h));

		h->ss.ss_family = res->ai_family;
		if (res->ai_family == AF_INET) {
			sain = (struct sockaddr_in *)&h->ss;
			sain->sin_len = sizeof(struct sockaddr_in);
			sain->sin_addr.s_addr = ((struct sockaddr_in *)
			    res->ai_addr)->sin_addr.s_addr;
			sain->sin_port = lo->port;
			if (sain->sin_addr.s_addr == htonl(INADDR_LOOPBACK))
				h->local = 1;
		} else {
			sin6 = (struct sockaddr_in6 *)&h->ss;
			sin6->sin6_len = sizeof(struct sockaddr_in6);
			memcpy(&sin6->sin6_addr, &((struct sockaddr_in6 *)
			    res->ai_addr)->sin6_addr, sizeof(struct in6_addr));
			sin6->sin6_port = lo->port;
			if (IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr))
				h->local = 1;
		}

		config_listener(h, lo);

		cnt++;
	}

	freeaddrinfo(res0);
	return (cnt);
}

static int
interface(struct listen_opts *lo)
{
	struct ifaddrs *ifap, *p;
	struct sockaddr_in	*sain;
	struct sockaddr_in6	*sin6;
	struct listener		*h;
	int			ret = 0;

	if (getifaddrs(&ifap) == -1)
		fatal("getifaddrs");

	for (p = ifap; p != NULL; p = p->ifa_next) {
		if (p->ifa_addr == NULL)
			continue;
		if (strcmp(p->ifa_name, lo->ifx) != 0 &&
		    !is_if_in_group(p->ifa_name, lo->ifx))
			continue;
		if (lo->family != AF_UNSPEC && lo->family != p->ifa_addr->sa_family)
			continue;

		h = xcalloc(1, sizeof(*h));

		switch (p->ifa_addr->sa_family) {
		case AF_INET:
			sain = (struct sockaddr_in *)&h->ss;
			*sain = *(struct sockaddr_in *)p->ifa_addr;
			sain->sin_len = sizeof(struct sockaddr_in);
			sain->sin_port = lo->port;
			if (sain->sin_addr.s_addr == htonl(INADDR_LOOPBACK))
				h->local = 1;
			break;

		case AF_INET6:
			sin6 = (struct sockaddr_in6 *)&h->ss;
			*sin6 = *(struct sockaddr_in6 *)p->ifa_addr;
			sin6->sin6_len = sizeof(struct sockaddr_in6);
			sin6->sin6_port = lo->port;
#ifdef __KAME__
			if ((IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr) ||
			    IN6_IS_ADDR_MC_LINKLOCAL(&sin6->sin6_addr) ||
			    IN6_IS_ADDR_MC_INTFACELOCAL(&sin6->sin6_addr)) &&
			    sin6->sin6_scope_id == 0) {
				sin6->sin6_scope_id = ntohs(
				    *(u_int16_t *)&sin6->sin6_addr.s6_addr[2]);
				sin6->sin6_addr.s6_addr[2] = 0;
				sin6->sin6_addr.s6_addr[3] = 0;
			}
#endif
			if (IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr))
				h->local = 1;
			break;

		default:
			free(h);
			continue;
		}

		config_listener(h, lo);
		ret = 1;
	}

	freeifaddrs(ifap);

	return ret;
}

int
delaytonum(char *str)
{
	unsigned int     factor;
	size_t           len;
	const char      *errstr = NULL;
	int              delay;

	/* we need at least 1 digit and 1 unit */
	len = strlen(str);
	if (len < 2)
		goto bad;

	switch(str[len - 1]) {

	case 's':
		factor = 1;
		break;

	case 'm':
		factor = 60;
		break;

	case 'h':
		factor = 60 * 60;
		break;

	case 'd':
		factor = 24 * 60 * 60;
		break;

	default:
		goto bad;
	}

	str[len - 1] = '\0';
	delay = strtonum(str, 1, INT_MAX / factor, &errstr);
	if (errstr)
		goto bad;

	return (delay * factor);

bad:
	return (-1);
}

int
is_if_in_group(const char *ifname, const char *groupname)
{
        unsigned int		 len;
        struct ifgroupreq        ifgr;
        struct ifg_req          *ifg;
	int			 s;
	int			 ret = 0;

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		fatal("socket");

        memset(&ifgr, 0, sizeof(ifgr));
        if (strlcpy(ifgr.ifgr_name, ifname, IFNAMSIZ) >= IFNAMSIZ)
		fatalx("interface name too large");

        if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1) {
                if (errno == EINVAL || errno == ENOTTY)
			goto end;
		fatal("SIOCGIFGROUP");
        }

        len = ifgr.ifgr_len;
        ifgr.ifgr_groups = xcalloc(len/sizeof(struct ifg_req),
		sizeof(struct ifg_req));
        if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1)
                fatal("SIOCGIFGROUP");

        ifg = ifgr.ifgr_groups;
        for (; ifg && len >= sizeof(struct ifg_req); ifg++) {
                len -= sizeof(struct ifg_req);
		if (strcmp(ifg->ifgrq_group, groupname) == 0) {
			ret = 1;
			break;
		}
        }
        free(ifgr.ifgr_groups);

end:
	close(s);
	return ret;
}

static int
config_lo_mask_source(struct listen_opts *lo) {
	if (lo->options & LO_MASKSOURCE) {
		yyerror("mask-source already specified");
		return -1;
	}
	lo->options |= LO_MASKSOURCE;
	lo->flags |= F_MASK_SOURCE;

	return 0;
}

/* Best effort. If it's ugly: use the tag parameter */
static const char *
processor_maketag(const char *name)
{
	char tag[TAG_MAX + 1];
	size_t i, j;

	for (i = j = 0; name[i] != '\0' && j < sizeof(tag) - 1; i++) {
		if (isalnum(name[i]))
			tag[j++] = name[i];
	}
	tag[j] = '\0';

	return xstrdup(tag);
}
