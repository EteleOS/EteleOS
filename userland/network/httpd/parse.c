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
#line 28 "parse.y"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <sys/tree.h>
#include <sys/ioctl.h>
#include <sys/sockio.h>
#include <sys/time.h>

#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ctype.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <ifaddrs.h>
#include <syslog.h>

#include "httpd.h"
#include "http.h"
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
int		 yyerror(const char *, ...)
    __attribute__((__format__ (printf, 1, 2)))
    __attribute__((__nonnull__ (1)));
int		 kw_cmp(const void *, const void *);
int		 lookup(char *);
int		 igetc(void);
int		 lgetc(int);
void		 lungetc(int);
int		 findeol(void);

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

struct httpd		*conf = NULL;
static int		 errors = 0;
static int		 loadcfg = 0;
uint32_t		 last_server_id = 0;
uint32_t		 last_auth_id = 0;

static struct server	*srv = NULL, *parentsrv = NULL;
static struct server_config *srv_conf = NULL;
struct serverlist	 servers;
struct media_type	 media;

struct address	*host_v4(const char *);
struct address	*host_v6(const char *);
int		 host_dns(const char *, struct addresslist *,
		    int, struct portrange *, const char *, int);
int		 host_if(const char *, struct addresslist *,
		    int, struct portrange *, const char *, int);
int		 host(const char *, struct addresslist *,
		    int, struct portrange *, const char *, int);
struct server	*server_inherit(struct server *, struct server_config *,
		    struct server_config *);
int		 listen_on(const char *, int, struct portrange *);
int		 getservice(char *);
int		 is_if_in_group(const char *, const char *);
int		 get_fastcgi_dest(struct server_config *, const char *, char *);
void		 remove_locations(struct server_config *);

typedef struct {
	union {
		int64_t			 number;
		char			*string;
		struct timeval		 tv;
		struct portrange	 port;
		struct auth		 auth;
	} v;
	int lineno;
} YYSTYPE;


#line 181 "y.tab.c"

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
    ACCESS = 258,                  /* ACCESS  */
    ALIAS = 259,                   /* ALIAS  */
    AUTO = 260,                    /* AUTO  */
    BACKLOG = 261,                 /* BACKLOG  */
    BODY = 262,                    /* BODY  */
    BUFFER = 263,                  /* BUFFER  */
    CERTIFICATE = 264,             /* CERTIFICATE  */
    CHROOT = 265,                  /* CHROOT  */
    CIPHERS = 266,                 /* CIPHERS  */
    COMMON = 267,                  /* COMMON  */
    COMBINED = 268,                /* COMBINED  */
    CONNECTION = 269,              /* CONNECTION  */
    DHE = 270,                     /* DHE  */
    DIRECTORY = 271,               /* DIRECTORY  */
    ECDHE = 272,                   /* ECDHE  */
    ERR = 273,                     /* ERR  */
    FCGI = 274,                    /* FCGI  */
    INDEX = 275,                   /* INDEX  */
    IP = 276,                      /* IP  */
    KEY = 277,                     /* KEY  */
    LIFETIME = 278,                /* LIFETIME  */
    LISTEN = 279,                  /* LISTEN  */
    LOCATION = 280,                /* LOCATION  */
    LOG = 281,                     /* LOG  */
    LOGDIR = 282,                  /* LOGDIR  */
    MATCH = 283,                   /* MATCH  */
    MAXIMUM = 284,                 /* MAXIMUM  */
    NO = 285,                      /* NO  */
    NODELAY = 286,                 /* NODELAY  */
    OCSP = 287,                    /* OCSP  */
    ON = 288,                      /* ON  */
    PORT = 289,                    /* PORT  */
    PREFORK = 290,                 /* PREFORK  */
    PROTOCOLS = 291,               /* PROTOCOLS  */
    REQUESTS = 292,                /* REQUESTS  */
    ROOT = 293,                    /* ROOT  */
    SACK = 294,                    /* SACK  */
    SERVER = 295,                  /* SERVER  */
    SOCKET = 296,                  /* SOCKET  */
    STRIP = 297,                   /* STRIP  */
    STYLE = 298,                   /* STYLE  */
    SYSLOG = 299,                  /* SYSLOG  */
    TCP = 300,                     /* TCP  */
    TICKET = 301,                  /* TICKET  */
    TIMEOUT = 302,                 /* TIMEOUT  */
    TLS = 303,                     /* TLS  */
    TYPE = 304,                    /* TYPE  */
    TYPES = 305,                   /* TYPES  */
    HSTS = 306,                    /* HSTS  */
    MAXAGE = 307,                  /* MAXAGE  */
    SUBDOMAINS = 308,              /* SUBDOMAINS  */
    DEFAULT = 309,                 /* DEFAULT  */
    PRELOAD = 310,                 /* PRELOAD  */
    REQUEST = 311,                 /* REQUEST  */
    ERROR = 312,                   /* ERROR  */
    INCLUDE = 313,                 /* INCLUDE  */
    AUTHENTICATE = 314,            /* AUTHENTICATE  */
    WITH = 315,                    /* WITH  */
    BLOCK = 316,                   /* BLOCK  */
    DROP = 317,                    /* DROP  */
    RETURN = 318,                  /* RETURN  */
    PASS = 319,                    /* PASS  */
    REWRITE = 320,                 /* REWRITE  */
    CA = 321,                      /* CA  */
    CLIENT = 322,                  /* CLIENT  */
    CRL = 323,                     /* CRL  */
    OPTIONAL = 324,                /* OPTIONAL  */
    PARAM = 325,                   /* PARAM  */
    FORWARDED = 326,               /* FORWARDED  */
    FOUND = 327,                   /* FOUND  */
    NOT = 328,                     /* NOT  */
    ERRDOCS = 329,                 /* ERRDOCS  */
    GZIPSTATIC = 330,              /* GZIPSTATIC  */
    BANNER = 331,                  /* BANNER  */
    STRING = 332,                  /* STRING  */
    NUMBER = 333                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ACCESS 258
#define ALIAS 259
#define AUTO 260
#define BACKLOG 261
#define BODY 262
#define BUFFER 263
#define CERTIFICATE 264
#define CHROOT 265
#define CIPHERS 266
#define COMMON 267
#define COMBINED 268
#define CONNECTION 269
#define DHE 270
#define DIRECTORY 271
#define ECDHE 272
#define ERR 273
#define FCGI 274
#define INDEX 275
#define IP 276
#define KEY 277
#define LIFETIME 278
#define LISTEN 279
#define LOCATION 280
#define LOG 281
#define LOGDIR 282
#define MATCH 283
#define MAXIMUM 284
#define NO 285
#define NODELAY 286
#define OCSP 287
#define ON 288
#define PORT 289
#define PREFORK 290
#define PROTOCOLS 291
#define REQUESTS 292
#define ROOT 293
#define SACK 294
#define SERVER 295
#define SOCKET 296
#define STRIP 297
#define STYLE 298
#define SYSLOG 299
#define TCP 300
#define TICKET 301
#define TIMEOUT 302
#define TLS 303
#define TYPE 304
#define TYPES 305
#define HSTS 306
#define MAXAGE 307
#define SUBDOMAINS 308
#define DEFAULT 309
#define PRELOAD 310
#define REQUEST 311
#define ERROR 312
#define INCLUDE 313
#define AUTHENTICATE 314
#define WITH 315
#define BLOCK 316
#define DROP 317
#define RETURN 318
#define PASS 319
#define REWRITE 320
#define CA 321
#define CLIENT 322
#define CRL 323
#define OPTIONAL 324
#define PARAM 325
#define FORWARDED 326
#define FOUND 327
#define NOT 328
#define ERRDOCS 329
#define GZIPSTATIC 330
#define BANNER 331
#define STRING 332
#define NUMBER 333

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
  YYSYMBOL_ACCESS = 3,                     /* ACCESS  */
  YYSYMBOL_ALIAS = 4,                      /* ALIAS  */
  YYSYMBOL_AUTO = 5,                       /* AUTO  */
  YYSYMBOL_BACKLOG = 6,                    /* BACKLOG  */
  YYSYMBOL_BODY = 7,                       /* BODY  */
  YYSYMBOL_BUFFER = 8,                     /* BUFFER  */
  YYSYMBOL_CERTIFICATE = 9,                /* CERTIFICATE  */
  YYSYMBOL_CHROOT = 10,                    /* CHROOT  */
  YYSYMBOL_CIPHERS = 11,                   /* CIPHERS  */
  YYSYMBOL_COMMON = 12,                    /* COMMON  */
  YYSYMBOL_COMBINED = 13,                  /* COMBINED  */
  YYSYMBOL_CONNECTION = 14,                /* CONNECTION  */
  YYSYMBOL_DHE = 15,                       /* DHE  */
  YYSYMBOL_DIRECTORY = 16,                 /* DIRECTORY  */
  YYSYMBOL_ECDHE = 17,                     /* ECDHE  */
  YYSYMBOL_ERR = 18,                       /* ERR  */
  YYSYMBOL_FCGI = 19,                      /* FCGI  */
  YYSYMBOL_INDEX = 20,                     /* INDEX  */
  YYSYMBOL_IP = 21,                        /* IP  */
  YYSYMBOL_KEY = 22,                       /* KEY  */
  YYSYMBOL_LIFETIME = 23,                  /* LIFETIME  */
  YYSYMBOL_LISTEN = 24,                    /* LISTEN  */
  YYSYMBOL_LOCATION = 25,                  /* LOCATION  */
  YYSYMBOL_LOG = 26,                       /* LOG  */
  YYSYMBOL_LOGDIR = 27,                    /* LOGDIR  */
  YYSYMBOL_MATCH = 28,                     /* MATCH  */
  YYSYMBOL_MAXIMUM = 29,                   /* MAXIMUM  */
  YYSYMBOL_NO = 30,                        /* NO  */
  YYSYMBOL_NODELAY = 31,                   /* NODELAY  */
  YYSYMBOL_OCSP = 32,                      /* OCSP  */
  YYSYMBOL_ON = 33,                        /* ON  */
  YYSYMBOL_PORT = 34,                      /* PORT  */
  YYSYMBOL_PREFORK = 35,                   /* PREFORK  */
  YYSYMBOL_PROTOCOLS = 36,                 /* PROTOCOLS  */
  YYSYMBOL_REQUESTS = 37,                  /* REQUESTS  */
  YYSYMBOL_ROOT = 38,                      /* ROOT  */
  YYSYMBOL_SACK = 39,                      /* SACK  */
  YYSYMBOL_SERVER = 40,                    /* SERVER  */
  YYSYMBOL_SOCKET = 41,                    /* SOCKET  */
  YYSYMBOL_STRIP = 42,                     /* STRIP  */
  YYSYMBOL_STYLE = 43,                     /* STYLE  */
  YYSYMBOL_SYSLOG = 44,                    /* SYSLOG  */
  YYSYMBOL_TCP = 45,                       /* TCP  */
  YYSYMBOL_TICKET = 46,                    /* TICKET  */
  YYSYMBOL_TIMEOUT = 47,                   /* TIMEOUT  */
  YYSYMBOL_TLS = 48,                       /* TLS  */
  YYSYMBOL_TYPE = 49,                      /* TYPE  */
  YYSYMBOL_TYPES = 50,                     /* TYPES  */
  YYSYMBOL_HSTS = 51,                      /* HSTS  */
  YYSYMBOL_MAXAGE = 52,                    /* MAXAGE  */
  YYSYMBOL_SUBDOMAINS = 53,                /* SUBDOMAINS  */
  YYSYMBOL_DEFAULT = 54,                   /* DEFAULT  */
  YYSYMBOL_PRELOAD = 55,                   /* PRELOAD  */
  YYSYMBOL_REQUEST = 56,                   /* REQUEST  */
  YYSYMBOL_ERROR = 57,                     /* ERROR  */
  YYSYMBOL_INCLUDE = 58,                   /* INCLUDE  */
  YYSYMBOL_AUTHENTICATE = 59,              /* AUTHENTICATE  */
  YYSYMBOL_WITH = 60,                      /* WITH  */
  YYSYMBOL_BLOCK = 61,                     /* BLOCK  */
  YYSYMBOL_DROP = 62,                      /* DROP  */
  YYSYMBOL_RETURN = 63,                    /* RETURN  */
  YYSYMBOL_PASS = 64,                      /* PASS  */
  YYSYMBOL_REWRITE = 65,                   /* REWRITE  */
  YYSYMBOL_CA = 66,                        /* CA  */
  YYSYMBOL_CLIENT = 67,                    /* CLIENT  */
  YYSYMBOL_CRL = 68,                       /* CRL  */
  YYSYMBOL_OPTIONAL = 69,                  /* OPTIONAL  */
  YYSYMBOL_PARAM = 70,                     /* PARAM  */
  YYSYMBOL_FORWARDED = 71,                 /* FORWARDED  */
  YYSYMBOL_FOUND = 72,                     /* FOUND  */
  YYSYMBOL_NOT = 73,                       /* NOT  */
  YYSYMBOL_ERRDOCS = 74,                   /* ERRDOCS  */
  YYSYMBOL_GZIPSTATIC = 75,                /* GZIPSTATIC  */
  YYSYMBOL_BANNER = 76,                    /* BANNER  */
  YYSYMBOL_STRING = 77,                    /* STRING  */
  YYSYMBOL_NUMBER = 78,                    /* NUMBER  */
  YYSYMBOL_79_n_ = 79,                     /* '\n'  */
  YYSYMBOL_80_ = 80,                       /* '='  */
  YYSYMBOL_81_ = 81,                       /* '{'  */
  YYSYMBOL_82_ = 82,                       /* '}'  */
  YYSYMBOL_83_ = 83,                       /* '/'  */
  YYSYMBOL_84_ = 84,                       /* ';'  */
  YYSYMBOL_85_ = 85,                       /* ','  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_grammar = 87,                   /* grammar  */
  YYSYMBOL_include = 88,                   /* include  */
  YYSYMBOL_varset = 89,                    /* varset  */
  YYSYMBOL_opttls = 90,                    /* opttls  */
  YYSYMBOL_main = 91,                      /* main  */
  YYSYMBOL_server = 92,                    /* server  */
  YYSYMBOL_93_1 = 93,                      /* $@1  */
  YYSYMBOL_serveropts_l = 94,              /* serveropts_l  */
  YYSYMBOL_serveroptsl = 95,               /* serveroptsl  */
  YYSYMBOL_96_2 = 96,                      /* $@2  */
  YYSYMBOL_banner = 97,                    /* banner  */
  YYSYMBOL_optfound = 98,                  /* optfound  */
  YYSYMBOL_hsts = 99,                      /* hsts  */
  YYSYMBOL_hstsflags_l = 100,              /* hstsflags_l  */
  YYSYMBOL_hstsflags = 101,                /* hstsflags  */
  YYSYMBOL_fastcgi = 102,                  /* fastcgi  */
  YYSYMBOL_103_3 = 103,                    /* $@3  */
  YYSYMBOL_104_4 = 104,                    /* $@4  */
  YYSYMBOL_fcgiflags_l = 105,              /* fcgiflags_l  */
  YYSYMBOL_fcgiflags = 106,                /* fcgiflags  */
  YYSYMBOL_connection = 107,               /* connection  */
  YYSYMBOL_conflags_l = 108,               /* conflags_l  */
  YYSYMBOL_conflags = 109,                 /* conflags  */
  YYSYMBOL_tls = 110,                      /* tls  */
  YYSYMBOL_tlsopts_l = 111,                /* tlsopts_l  */
  YYSYMBOL_tlsopts = 112,                  /* tlsopts  */
  YYSYMBOL_tlsclientopt = 113,             /* tlsclientopt  */
  YYSYMBOL_root = 114,                     /* root  */
  YYSYMBOL_rootflags_l = 115,              /* rootflags_l  */
  YYSYMBOL_rootflags = 116,                /* rootflags  */
  YYSYMBOL_request = 117,                  /* request  */
  YYSYMBOL_requestflags_l = 118,           /* requestflags_l  */
  YYSYMBOL_requestflags = 119,             /* requestflags  */
  YYSYMBOL_authenticate = 120,             /* authenticate  */
  YYSYMBOL_authopts = 121,                 /* authopts  */
  YYSYMBOL_directory = 122,                /* directory  */
  YYSYMBOL_dirflags_l = 123,               /* dirflags_l  */
  YYSYMBOL_dirflags = 124,                 /* dirflags  */
  YYSYMBOL_logformat = 125,                /* logformat  */
  YYSYMBOL_logflags_l = 126,               /* logflags_l  */
  YYSYMBOL_logflags = 127,                 /* logflags  */
  YYSYMBOL_logstyle = 128,                 /* logstyle  */
  YYSYMBOL_filter = 129,                   /* filter  */
  YYSYMBOL_block = 130,                    /* block  */
  YYSYMBOL_optmatch = 131,                 /* optmatch  */
  YYSYMBOL_optstring = 132,                /* optstring  */
  YYSYMBOL_fcgiport = 133,                 /* fcgiport  */
  YYSYMBOL_gzip_static = 134,              /* gzip_static  */
  YYSYMBOL_tcpip = 135,                    /* tcpip  */
  YYSYMBOL_tcpflags_l = 136,               /* tcpflags_l  */
  YYSYMBOL_tcpflags = 137,                 /* tcpflags  */
  YYSYMBOL_types = 138,                    /* types  */
  YYSYMBOL_mediaopts_l = 139,              /* mediaopts_l  */
  YYSYMBOL_mediaoptsl = 140,               /* mediaoptsl  */
  YYSYMBOL_mediastring = 141,              /* mediastring  */
  YYSYMBOL_medianames_l = 142,             /* medianames_l  */
  YYSYMBOL_medianamesl = 143,              /* medianamesl  */
  YYSYMBOL_port = 144,                     /* port  */
  YYSYMBOL_timeout = 145,                  /* timeout  */
  YYSYMBOL_numberstring = 146,             /* numberstring  */
  YYSYMBOL_optsemicolon = 147,             /* optsemicolon  */
  YYSYMBOL_optnl = 148,                    /* optnl  */
  YYSYMBOL_optcommanl = 149,               /* optcommanl  */
  YYSYMBOL_nl = 150                        /* nl  */
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
#define YYLAST   364

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  333

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   333


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
      79,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    85,     2,     2,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    84,
       2,    80,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,     2,    82,     2,     2,     2,     2,
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
      75,    76,    77,    78
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   157,   157,   158,   159,   160,   161,   162,   163,   164,
     167,   182,   200,   201,   204,   214,   217,   228,   231,   234,
     240,   240,   468,   469,   472,   479,   505,   520,   527,   533,
     539,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   566,   683,   688,   689,   698,   705,   714,   715,   716,
     719,   720,   721,   724,   725,   728,   735,   738,   743,   747,
     751,   751,   755,   755,   761,   762,   765,   780,   788,   797,
     827,   836,   837,   840,   841,   844,   848,   852,   855,   860,
     861,   864,   865,   868,   874,   880,   887,   897,   904,   914,
     924,   933,   936,   947,   952,   953,   960,   964,   965,   968,
     969,   972,   985,   986,   989,   990,   993,  1005,  1009,  1018,
    1021,  1044,  1063,  1074,  1075,  1078,  1079,  1082,  1094,  1098,
    1102,  1109,  1110,  1111,  1117,  1118,  1121,  1122,  1126,  1130,
    1141,  1154,  1159,  1164,  1169,  1176,  1196,  1200,  1204,  1210,
    1216,  1217,  1220,  1221,  1224,  1234,  1245,  1248,  1253,  1254,
    1257,  1258,  1261,  1262,  1263,  1266,  1269,  1276,  1283,  1304,
    1307,  1308,  1311,  1312,  1315,  1332,  1333,  1336,  1356,  1364,
    1379,  1390,  1398,  1401,  1402,  1405,  1406,  1409,  1410,  1413
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
  "\"end of file\"", "error", "\"invalid token\"", "ACCESS", "ALIAS",
  "AUTO", "BACKLOG", "BODY", "BUFFER", "CERTIFICATE", "CHROOT", "CIPHERS",
  "COMMON", "COMBINED", "CONNECTION", "DHE", "DIRECTORY", "ECDHE", "ERR",
  "FCGI", "INDEX", "IP", "KEY", "LIFETIME", "LISTEN", "LOCATION", "LOG",
  "LOGDIR", "MATCH", "MAXIMUM", "NO", "NODELAY", "OCSP", "ON", "PORT",
  "PREFORK", "PROTOCOLS", "REQUESTS", "ROOT", "SACK", "SERVER", "SOCKET",
  "STRIP", "STYLE", "SYSLOG", "TCP", "TICKET", "TIMEOUT", "TLS", "TYPE",
  "TYPES", "HSTS", "MAXAGE", "SUBDOMAINS", "DEFAULT", "PRELOAD", "REQUEST",
  "ERROR", "INCLUDE", "AUTHENTICATE", "WITH", "BLOCK", "DROP", "RETURN",
  "PASS", "REWRITE", "CA", "CLIENT", "CRL", "OPTIONAL", "PARAM",
  "FORWARDED", "FOUND", "NOT", "ERRDOCS", "GZIPSTATIC", "BANNER", "STRING",
  "NUMBER", "'\\n'", "'='", "'{'", "'}'", "'/'", "';'", "','", "$accept",
  "grammar", "include", "varset", "opttls", "main", "server", "$@1",
  "serveropts_l", "serveroptsl", "$@2", "banner", "optfound", "hsts",
  "hstsflags_l", "hstsflags", "fastcgi", "$@3", "$@4", "fcgiflags_l",
  "fcgiflags", "connection", "conflags_l", "conflags", "tls", "tlsopts_l",
  "tlsopts", "tlsclientopt", "root", "rootflags_l", "rootflags", "request",
  "requestflags_l", "requestflags", "authenticate", "authopts",
  "directory", "dirflags_l", "dirflags", "logformat", "logflags_l",
  "logflags", "logstyle", "filter", "block", "optmatch", "optstring",
  "fcgiport", "gzip_static", "tcpip", "tcpflags_l", "tcpflags", "types",
  "mediaopts_l", "mediaoptsl", "mediastring", "medianames_l",
  "medianamesl", "port", "timeout", "numberstring", "optsemicolon",
  "optnl", "optcommanl", "nl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-176)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -87,     4,   -87,   -70,   -14,   -12,    -3,    15,    91,    40,
      74,    57,    68,    87,   -87,    70,    75,    92,    98,   101,
     -87,   -87,   -87,   -87,   -87,   -87,    97,   107,   113,   -87,
     -87,   115,   -87,   -87,   -87,   -87,   -87,   -87,   107,    27,
     120,   -87,   -87,   124,   -87,   -87,   125,   117,   -59,   138,
     107,   -87,   117,   107,   -87,   -87,   -87,    84,   -87,   -87,
     -87,   288,   -87,   -87,   -87,   -87,   -87,    91,    35,     6,
      -4,   161,   126,     3,    50,   -61,    11,    13,    58,   170,
      37,   -50,   -87,   -87,   149,   -87,   -87,   -87,    82,   107,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   150,   -87,   -87,   153,    34,   132,   184,   107,   -87,
     212,   157,    95,   107,   -87,   152,   111,   160,   -87,   167,
      91,   164,   165,   202,    43,   -87,   107,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   107,   -87,   169,   174,    64,
     -87,   -87,   244,   107,   -87,   176,   178,   179,   180,   181,
     213,   183,   186,   238,   198,   107,   -87,   187,   -87,   -87,
     107,   -87,   113,   201,   189,   191,   107,   -87,   193,   211,
     -87,   -87,   -87,   117,   -87,   -87,   195,   -87,   196,   269,
     -87,   -87,   132,   141,   -87,   -87,   257,   -87,    69,   107,
      -5,   206,   209,   -87,   231,   -87,   210,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   129,   214,   -87,   215,   -87,
     -87,   216,   154,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -25,   218,   133,   -87,   156,   -87,   -87,   -87,   -87,
     -17,   -87,   219,   -87,   220,   -87,   223,   -87,   207,    52,
     -87,   208,    52,   111,   226,   -87,   -87,   228,   -87,   274,
     -87,   227,    52,   229,    52,   -87,   -87,   233,    52,   -87,
     -87,   -87,   234,    52,   235,    52,   237,    52,   -87,   -87,
     -87,   -87,   -87,   107,   107,   -87,   141,   -87,   -87,   -87,
      69,   239,    52,   140,   -87,   144,   -87,   241,   -87,   -87,
     129,   -87,   -87,   214,   -87,   -87,   154,   155,   -87,   -87,
     133,   -87,   -87,   156,   -87,   -87,   -17,   242,   -87,   -87,
     -87,   -87,   -87,   111,   -87,   -87,   -87,   -87,   -87,   107,
     -87,   -87,   -87,   243,   -87,   -87,   -87,   -87,   -87,   288,
     -87,   224,   -87
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,   140,     0,
       0,     0,     0,     0,     4,     0,     0,     0,     0,     0,
       9,    15,    17,    18,    14,   141,     0,   176,     0,    10,
      16,     0,     3,     5,     6,     7,     8,    20,   176,     0,
       0,    19,    11,     0,   175,   163,     0,     0,     0,     0,
     176,   159,     0,   176,   161,   172,   171,   174,   166,   167,
     164,     0,   160,   179,   173,   165,   162,   140,     0,     0,
      59,     0,    47,     0,     0,     0,     0,     0,    52,     0,
       0,     0,   139,   138,     0,   147,    45,    43,     0,   176,
      34,    44,    36,    29,    30,    32,    31,    37,    33,    35,
      39,   137,    38,    28,     0,     0,     0,     0,   176,    72,
       0,     0,     0,   176,   113,     0,     0,     0,    48,     0,
     140,     0,     0,     0,     0,   127,   176,   121,    58,   123,
     109,    27,   146,    46,   101,   176,    97,     0,     0,     0,
     154,   152,     0,   176,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   176,    80,     0,    56,    57,
     176,    51,     0,     0,     0,     0,   176,   102,     0,     0,
     110,    26,    21,     0,    23,   136,     0,    25,     0,     0,
     170,    75,     0,     0,   119,   117,     0,   118,     0,   176,
       0,     0,     0,    63,    12,    49,     0,   129,   130,   128,
     131,   132,   133,   134,   126,     0,     0,   156,     0,   155,
     153,     0,     0,    83,    86,    88,    89,    84,    93,    85,
      90,     0,     0,     0,    55,     0,    42,   107,   108,   106,
       0,   112,     0,    22,   142,    77,     0,    76,     0,   176,
     120,     0,   176,     0,     0,    66,    70,     0,    13,     0,
      40,     0,   176,     0,   176,   158,   157,     0,   176,    91,
      92,    94,     0,   176,     0,   176,     0,   176,   111,   143,
     135,    78,    71,   176,   176,    74,     0,   178,   114,   116,
       0,     0,   176,    67,    69,     0,    24,     0,   122,   125,
       0,    98,   100,     0,   148,   151,     0,    87,    79,    82,
       0,    50,    54,     0,   103,   105,     0,   179,   177,    73,
     115,    61,    65,     0,   145,   144,    68,   169,   168,   176,
     124,    99,   150,     0,    96,    81,    53,   104,    64,     0,
      95,     0,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,    22,   -87,   -87,   -87,   -87,   -87,   -19,   -86,
     -87,   -87,   -87,   -87,    20,   247,   -87,   -87,   -87,    14,
     221,   -87,    53,   260,   -87,    30,   254,   -87,   -87,    39,
     259,   -87,    29,   258,   -87,   -87,   -87,    60,   272,   -87,
      55,   270,   -87,   -87,   -87,   -60,   -87,   -87,   -87,   -87,
      54,   275,   -87,   -87,   302,   -27,   -87,   296,   -87,   172,
     -87,   -87,   -38,   -76,   -44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    87,    16,   249,    17,    18,    43,    88,    89,
     287,    90,   120,    91,   264,   265,    92,   115,   116,   281,
     282,    93,   238,   239,    94,   262,   263,   297,    95,   253,
     254,    96,   266,   267,    97,   170,    98,   241,   242,    99,
     251,   252,   204,   100,   101,    26,   270,   316,   102,   103,
     257,   258,    19,    46,    47,    48,    57,    58,   286,   181,
      59,    66,    39,   276,   277
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,    41,   173,    54,     2,     3,   121,   104,    62,    20,
     168,   110,    61,   163,     4,    63,   134,   137,    55,    56,
     135,   122,   145,    15,   146,   164,   111,   169,   147,   259,
     148,     5,   138,   123,     6,   149,   112,   -62,   -62,     7,
     244,   139,   140,   150,     8,   151,   124,   125,   165,   152,
     141,   174,   142,   260,     9,   200,   201,   202,    10,   153,
     196,    45,    11,    21,   105,    22,   -62,   163,    45,   128,
     183,   178,   245,    23,   110,   188,   129,   -60,    12,   164,
     154,    13,   106,    14,   126,    11,    67,   113,   205,   111,
     179,   107,   143,    24,   155,   209,    68,   206,    69,   112,
     186,    70,   165,   210,    40,   212,    71,    72,    73,   130,
     157,   158,    74,   159,   203,   187,   108,   223,   166,    25,
      75,    27,   225,    28,   131,   132,   133,    76,   230,   233,
      77,   273,   121,    78,    29,   226,    79,   274,    80,   160,
      11,    81,   145,    82,   146,    30,    83,   122,   147,    32,
     148,   243,   190,   191,    33,   149,    84,    85,    86,   123,
     137,    55,    56,   150,   172,   151,   280,    31,    64,   152,
     105,    34,   124,   125,    37,   138,   290,    35,   293,   153,
      36,   192,   296,    11,   139,   140,    38,   300,   106,   303,
      40,   306,    42,   141,   117,   142,    53,   107,   118,   119,
     154,   275,    40,    49,   279,    50,   313,    51,   157,   158,
     180,   159,   175,   176,   289,    60,   292,   314,   315,   162,
     295,   317,   318,   323,   324,   299,   171,   302,    67,   305,
     177,   182,   184,   189,   185,   307,   308,   194,    68,   195,
      69,   197,   198,    70,   312,   173,   199,   207,    71,    72,
      73,   208,   211,   213,    74,   214,   215,   216,   217,   218,
     219,   221,    75,   220,   222,   224,   227,   228,   229,    76,
     231,   232,    77,   234,   235,    78,   236,   240,    79,   248,
      80,   329,    11,    81,   246,    82,   247,   250,    83,   272,
     278,   134,    67,   255,   256,   261,   268,   269,    84,    85,
      86,   271,    68,   283,    69,   284,   332,    70,   285,   288,
     331,   291,    71,    72,    73,   294,   298,   301,    74,   304,
     330,   311,   319,   326,  -175,   161,    75,   328,   109,   309,
     325,   156,   321,    76,   136,   327,    77,   193,   167,    78,
     310,   114,    79,   127,    80,   320,    11,    81,    52,    82,
     322,   144,    83,    65,   237,     0,     0,     0,     0,     0,
       0,     0,    84,    85,    86
};

static const yytype_int16 yycheck[] =
{
      38,    28,    88,    47,     0,     1,     3,    67,    52,    79,
      60,     5,    50,    30,    10,    53,    77,     6,    77,    78,
      81,    18,     9,     1,    11,    42,    20,    77,    15,    54,
      17,    27,    21,    30,    30,    22,    30,    41,    42,    35,
      45,    30,    31,    30,    40,    32,    43,    44,    65,    36,
      39,    89,    41,    78,    50,    12,    13,    14,    54,    46,
     120,    39,    58,    77,    29,    77,    70,    30,    46,    19,
     108,    37,    77,    76,     5,   113,    26,    81,    74,    42,
      67,    77,    47,    79,    81,    58,     4,    81,   126,    20,
      56,    56,    81,    78,    81,    31,    14,   135,    16,    30,
       5,    19,    65,    39,    77,   143,    24,    25,    26,    59,
      52,    53,    30,    55,    71,    20,    81,   155,    81,    28,
      38,    81,   160,    49,    74,    75,    76,    45,   166,   173,
      48,    79,     3,    51,    77,   162,    54,    85,    56,    81,
      58,    59,     9,    61,    11,    77,    64,    18,    15,    79,
      17,   189,    41,    42,    79,    22,    74,    75,    76,    30,
       6,    77,    78,    30,    82,    32,   242,    80,    84,    36,
      29,    79,    43,    44,    77,    21,   252,    79,   254,    46,
      79,    70,   258,    58,    30,    31,    79,   263,    47,   265,
      77,   267,    77,    39,    33,    41,    79,    56,    72,    73,
      67,   239,    77,    83,   242,    81,   282,    82,    52,    53,
      78,    55,    62,    63,   252,    77,   254,    77,    78,    49,
     258,    77,    78,    68,    69,   263,    77,   265,     4,   267,
      77,    47,    20,    81,    77,   273,   274,    77,    14,    72,
      16,    77,    77,    19,   282,   331,    44,    78,    24,    25,
      26,    77,     8,    77,    30,    77,    77,    77,    77,    46,
      77,    23,    38,    77,    66,    78,    65,    78,    77,    45,
      77,    60,    48,    78,    78,    51,     7,    20,    54,    48,
      56,   319,    58,    59,    78,    61,    77,    77,    64,    82,
      82,    77,     4,    78,    78,    77,    77,    77,    74,    75,
      76,    78,    14,    77,    16,    77,    82,    19,    34,    82,
     329,    82,    24,    25,    26,    82,    82,    82,    30,    82,
      77,    82,    81,   303,    82,    78,    38,   313,    68,   276,
     300,    77,   293,    45,    75,   306,    48,   116,    80,    51,
     280,    69,    54,    73,    56,   290,    58,    59,    46,    61,
     296,    76,    64,    57,   182,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    87,     0,     1,    10,    27,    30,    35,    40,    50,
      54,    58,    74,    77,    79,    88,    89,    91,    92,   138,
      79,    77,    77,    76,    78,    28,   131,    81,    49,    77,
      77,    80,    79,    79,    79,    79,    79,    77,    79,   148,
      77,   141,    77,    93,   148,    88,   139,   140,   141,    83,
      81,    82,   140,    79,   150,    77,    78,   142,   143,   146,
      77,   148,   150,   148,    84,   143,   147,     4,    14,    16,
      19,    24,    25,    26,    30,    38,    45,    48,    51,    54,
      56,    59,    61,    64,    74,    75,    76,    88,    94,    95,
      97,    99,   102,   107,   110,   114,   117,   120,   122,   125,
     129,   130,   134,   135,   131,    29,    47,    56,    81,   109,
       5,    20,    30,    81,   124,   103,   104,    33,    72,    73,
      98,     3,    18,    30,    43,    44,    81,   127,    19,    26,
      59,    74,    75,    76,    77,    81,   116,     6,    21,    30,
      31,    39,    41,    81,   137,     9,    11,    15,    17,    22,
      30,    32,    36,    46,    67,    81,   112,    52,    53,    55,
      81,   101,    49,    30,    42,    65,    81,   119,    60,    77,
     121,    77,    82,    95,   148,    62,    63,    77,    37,    56,
      78,   145,    47,   148,    20,    77,     5,    20,   148,    81,
      41,    42,    70,   106,    77,    72,   131,    77,    77,    44,
      12,    13,    14,    71,   128,   148,   148,    78,    77,    31,
      39,     8,   148,    77,    77,    77,    77,    77,    46,    77,
      77,    23,    66,   148,    78,   148,   141,    65,    78,    77,
     148,    77,    60,   150,    78,    78,     7,   145,   108,   109,
      20,   123,   124,   148,    45,    77,    78,    77,    48,    90,
      77,   126,   127,   115,   116,    78,    78,   136,   137,    54,
      78,    77,   111,   112,   100,   101,   118,   119,    77,    77,
     132,    78,    82,    79,    85,   148,   149,   150,    82,   148,
     149,   105,   106,    77,    77,    34,   144,    96,    82,   148,
     149,    82,   148,   149,    82,   148,   149,   113,    82,   148,
     149,    82,   148,   149,    82,   148,   149,   148,   148,   108,
     123,    82,   148,   149,    77,    78,   133,    77,    78,    81,
     126,   115,   136,    68,    69,   111,   100,   118,   105,   148,
      77,    94,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      88,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      93,    92,    94,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      96,    95,    95,    95,    95,    97,    97,    98,    98,    98,
      99,    99,    99,   100,   100,   101,   101,   101,   102,   102,
     103,   102,   104,   102,   105,   105,   106,   106,   106,   106,
     106,   107,   107,   108,   108,   109,   109,   109,   109,   110,
     110,   111,   111,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   113,   113,   113,   114,   114,   115,
     115,   116,   117,   117,   118,   118,   119,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   124,
     124,   125,   125,   125,   126,   126,   127,   127,   127,   127,
     127,   128,   128,   128,   128,   129,   129,   129,   129,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   137,   137,   137,   137,   137,   138,
     139,   139,   140,   140,   141,   142,   142,   143,   144,   144,
     145,   146,   146,   147,   147,   148,   148,   149,   149,   150
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     2,     3,     3,     3,     3,     3,
       2,     3,     0,     1,     2,     2,     2,     2,     2,     3,
       0,     8,     3,     2,     5,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     9,     3,     1,     1,     1,     2,     0,     1,     2,
       5,     2,     1,     3,     2,     2,     1,     1,     2,     1,
       0,     6,     0,     3,     3,     2,     2,     3,     4,     3,
       2,     5,     2,     3,     2,     2,     3,     3,     4,     5,
       2,     3,     2,     2,     2,     2,     2,     4,     2,     2,
       2,     3,     3,     2,     0,     3,     2,     2,     5,     3,
       2,     1,     2,     5,     3,     2,     2,     2,     2,     2,
       2,     3,     2,     2,     5,     3,     2,     2,     2,     2,
       3,     2,     5,     2,     3,     2,     2,     1,     2,     2,
       2,     1,     1,     1,     1,     4,     2,     1,     1,     1,
       0,     1,     0,     1,     1,     1,     2,     1,     5,     2,
       3,     2,     1,     2,     1,     2,     2,     3,     3,     5,
       3,     2,     3,     1,     3,     2,     1,     1,     2,     2,
       1,     1,     1,     1,     0,     2,     0,     2,     1,     2
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
  case 9: /* grammar: grammar error '\n'  */
#line 164 "parse.y"
                                                { file->errors++; }
#line 1756 "y.tab.c"
    break;

  case 10: /* include: INCLUDE STRING  */
#line 167 "parse.y"
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
#line 1774 "y.tab.c"
    break;

  case 11: /* varset: STRING '=' STRING  */
#line 182 "parse.y"
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
#line 1795 "y.tab.c"
    break;

  case 12: /* opttls: %empty  */
#line 200 "parse.y"
                                { (yyval.v.number) = 0; }
#line 1801 "y.tab.c"
    break;

  case 13: /* opttls: TLS  */
#line 201 "parse.y"
                                { (yyval.v.number) = 1; }
#line 1807 "y.tab.c"
    break;

  case 14: /* main: PREFORK NUMBER  */
#line 204 "parse.y"
                                        {
			if (loadcfg)
				break;
			if ((yyvsp[0].v.number) <= 0 || (yyvsp[0].v.number) > PROC_MAX_INSTANCES) {
				yyerror("invalid number of preforked "
				    "servers: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			conf->sc_prefork_server = (yyvsp[0].v.number);
		}
#line 1822 "y.tab.c"
    break;

  case 15: /* main: CHROOT STRING  */
#line 214 "parse.y"
                                        {
			conf->sc_chroot = (yyvsp[0].v.string);
		}
#line 1830 "y.tab.c"
    break;

  case 16: /* main: ERRDOCS STRING  */
#line 217 "parse.y"
                                        {
			if ((yyvsp[0].v.string) != NULL && strlcpy(conf->sc_errdocroot, (yyvsp[0].v.string),
			    sizeof(conf->sc_errdocroot)) >=
			    sizeof(conf->sc_errdocroot)) {
				yyerror("errdoc root path too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			conf->sc_custom_errdocs = 1;
		}
#line 1846 "y.tab.c"
    break;

  case 17: /* main: LOGDIR STRING  */
#line 228 "parse.y"
                                        {
			conf->sc_logdir = (yyvsp[0].v.string);
		}
#line 1854 "y.tab.c"
    break;

  case 18: /* main: NO BANNER  */
#line 231 "parse.y"
                                        {
			conf->sc_flags |= SRVFLAG_NO_BANNER;
		}
#line 1862 "y.tab.c"
    break;

  case 19: /* main: DEFAULT TYPE mediastring  */
#line 234 "parse.y"
                                                {
			memcpy(&conf->sc_default_type, &media,
			    sizeof(struct media_type));
		}
#line 1871 "y.tab.c"
    break;

  case 20: /* $@1: %empty  */
#line 240 "parse.y"
                                                {
			struct server		*s;
			struct sockaddr_un	*sun;

			if (!loadcfg) {
				free((yyvsp[0].v.string));
				YYACCEPT;
			}

			if ((s = calloc(1, sizeof (*s))) == NULL)
				fatal("out of memory");

			if (strlcpy(s->srv_conf.name, (yyvsp[0].v.string),
			    sizeof(s->srv_conf.name)) >=
			    sizeof(s->srv_conf.name)) {
				yyerror("server name truncated");
				free((yyvsp[0].v.string));
				free(s);
				YYERROR;
			}
			free((yyvsp[0].v.string));

			strlcpy(s->srv_conf.root, HTTPD_DOCROOT,
			    sizeof(s->srv_conf.root));
			strlcpy(s->srv_conf.index, HTTPD_INDEX,
			    sizeof(s->srv_conf.index));
			strlcpy(s->srv_conf.accesslog, HTTPD_ACCESS_LOG,
			    sizeof(s->srv_conf.accesslog));
			strlcpy(s->srv_conf.errorlog, HTTPD_ERROR_LOG,
			    sizeof(s->srv_conf.errorlog));
			s->srv_conf.id = ++last_server_id;
			s->srv_conf.parent_id = s->srv_conf.id;
			s->srv_s = -1;
			s->srv_conf.timeout.tv_sec = SERVER_TIMEOUT;
			s->srv_conf.requesttimeout.tv_sec =
			    SERVER_REQUESTTIMEOUT;
			s->srv_conf.maxrequests = SERVER_MAXREQUESTS;
			s->srv_conf.maxrequestbody = SERVER_MAXREQUESTBODY;
			s->srv_conf.flags = SRVFLAG_LOG;
			if ((yyvsp[-1].v.number))
				s->srv_conf.flags |= SRVFLAG_SERVER_MATCH;
			s->srv_conf.logformat = LOG_FORMAT_COMMON;
			s->srv_conf.tls_protocols = TLS_PROTOCOLS_DEFAULT;
			if ((s->srv_conf.tls_cert_file =
			    strdup(HTTPD_TLS_CERT)) == NULL)
				fatal("out of memory");
			if ((s->srv_conf.tls_key_file =
			    strdup(HTTPD_TLS_KEY)) == NULL)
				fatal("out of memory");
			strlcpy(s->srv_conf.tls_ciphers,
			    HTTPD_TLS_CIPHERS,
			    sizeof(s->srv_conf.tls_ciphers));
			strlcpy(s->srv_conf.tls_dhe_params,
			    HTTPD_TLS_DHE_PARAMS,
			    sizeof(s->srv_conf.tls_dhe_params));
			strlcpy(s->srv_conf.tls_ecdhe_curves,
			    HTTPD_TLS_ECDHE_CURVES,
			    sizeof(s->srv_conf.tls_ecdhe_curves));

			sun = (struct sockaddr_un *)&s->srv_conf.fastcgi_ss;
			sun->sun_family = AF_UNIX;
			(void)strlcpy(sun->sun_path, HTTPD_FCGI_SOCKET,
			    sizeof(sun->sun_path));
			sun->sun_len = sizeof(struct sockaddr_un);

			s->srv_conf.hsts_max_age = SERVER_HSTS_DEFAULT_AGE;

			if (conf->sc_flags & SRVFLAG_NO_BANNER)
				s->srv_conf.flags |= SRVFLAG_NO_BANNER;

			(void)strlcpy(s->srv_conf.errdocroot,
			    conf->sc_errdocroot,
			    sizeof(s->srv_conf.errdocroot));
			if (conf->sc_custom_errdocs)
				s->srv_conf.flags |= SRVFLAG_ERRDOCS;

			if (last_server_id == INT_MAX) {
				yyerror("too many servers defined");
				free(s);
				YYERROR;
			}
			srv = s;
			srv_conf = &srv->srv_conf;

			SPLAY_INIT(&srv->srv_clients);
			TAILQ_INIT(&srv->srv_hosts);
			TAILQ_INIT(&srv_conf->fcgiparams);

			TAILQ_INSERT_TAIL(&srv->srv_hosts, srv_conf, entry);
		}
#line 1966 "y.tab.c"
    break;

  case 21: /* server: SERVER optmatch STRING $@1 '{' optnl serveropts_l '}'  */
#line 329 "parse.y"
                                                {
			struct server		*s, *sn;
			struct server_config	*a, *b;

			srv_conf = &srv->srv_conf;

			/* Check if the new server already exists. */
			if (server_match(srv, 1) != NULL) {
				yyerror("server \"%s\" defined twice",
				    srv->srv_conf.name);
				serverconfig_free(srv_conf);
				free(srv);
				YYABORT;
			}

			if (srv->srv_conf.ss.ss_family == AF_UNSPEC) {
				yyerror("listen address not specified");
				serverconfig_free(srv_conf);
				free(srv);
				YYERROR;
			}

			if ((s = server_match(srv, 0)) != NULL) {
				if ((s->srv_conf.flags & SRVFLAG_TLS) !=
				    (srv->srv_conf.flags & SRVFLAG_TLS)) {
					yyerror("server \"%s\": tls and "
					    "non-tls on same address/port",
					    srv->srv_conf.name);
					serverconfig_free(srv_conf);
					free(srv);
					YYERROR;
				}
				if (srv->srv_conf.flags & SRVFLAG_TLS &&
				    server_tls_cmp(s, srv) != 0) {
					yyerror("server \"%s\": tls "
					    "configuration mismatch on same "
					    "address/port",
					    srv->srv_conf.name);
					serverconfig_free(srv_conf);
					free(srv);
					YYERROR;
				}
			}

			if ((srv->srv_conf.flags & SRVFLAG_TLS) &&
			    srv->srv_conf.tls_protocols == 0) {
				yyerror("server \"%s\": no tls protocols",
				    srv->srv_conf.name);
				serverconfig_free(srv_conf);
				free(srv);
				YYERROR;
			}

			if (server_tls_load_keypair(srv) == -1) {
				/* Soft fail as there may be no certificate. */
				log_warnx("%s:%d: server \"%s\": failed to "
				    "load public/private keys", file->name,
				    yylval.lineno, srv->srv_conf.name);

				remove_locations(srv_conf);
				serverconfig_free(srv_conf);
				srv_conf = NULL;
				free(srv);
				srv = NULL;
				break;
			}

			if (server_tls_load_ca(srv) == -1) {
				yyerror("server \"%s\": failed to load "
				    "ca cert(s)", srv->srv_conf.name);
				serverconfig_free(srv_conf);
				free(srv);
				YYERROR;
			}

			if (server_tls_load_crl(srv) == -1) {
				yyerror("server \"%s\": failed to load crl(s)",
				    srv->srv_conf.name);
				serverconfig_free(srv_conf);
				free(srv);
				YYERROR;
			}

			if (server_tls_load_ocsp(srv) == -1) {
				yyerror("server \"%s\": failed to load "
				    "ocsp staple", srv->srv_conf.name);
				serverconfig_free(srv_conf);
				free(srv);
				YYERROR;
			}

			DPRINTF("adding server \"%s[%u]\"",
			    srv->srv_conf.name, srv->srv_conf.id);

			TAILQ_INSERT_TAIL(conf->sc_servers, srv, srv_entry);

			/*
			 * Add aliases and additional listen addresses as
			 * individual servers.
			 */
			TAILQ_FOREACH(a, &srv->srv_hosts, entry) {
				/* listen address */
				if (a->ss.ss_family == AF_UNSPEC)
					continue;
				TAILQ_FOREACH(b, &srv->srv_hosts, entry) {
					/* alias name */
					if (*b->name == '\0' ||
					    (b == &srv->srv_conf && b == a))
						continue;

					if ((sn = server_inherit(srv,
					    b, a)) == NULL) {
						serverconfig_free(srv_conf);
						free(srv);
						YYABORT;
					}

					DPRINTF("adding server \"%s[%u]\"",
					    sn->srv_conf.name, sn->srv_conf.id);

					TAILQ_INSERT_TAIL(conf->sc_servers,
					    sn, srv_entry);
				}
			}

			/* Remove temporary aliases */
			TAILQ_FOREACH_SAFE(a, &srv->srv_hosts, entry, b) {
				TAILQ_REMOVE(&srv->srv_hosts, a, entry);
				if (a == &srv->srv_conf)
					continue;
				serverconfig_free(a);
				free(a);
			}

			srv = NULL;
			srv_conf = NULL;
		}
#line 2108 "y.tab.c"
    break;

  case 24: /* serveroptsl: LISTEN ON STRING opttls port  */
#line 472 "parse.y"
                                                {
			if (listen_on((yyvsp[-2].v.string), (yyvsp[-1].v.number), &(yyvsp[0].v.port)) == -1) {
				free((yyvsp[-2].v.string));
				YYERROR;
			}
			free((yyvsp[-2].v.string));
		}
#line 2120 "y.tab.c"
    break;

  case 25: /* serveroptsl: ALIAS optmatch STRING  */
#line 479 "parse.y"
                                                {
			struct server_config	*alias;

			if (parentsrv != NULL) {
				yyerror("alias inside location");
				free((yyvsp[0].v.string));
				YYERROR;
			}

			if ((alias = calloc(1, sizeof(*alias))) == NULL)
				fatal("out of memory");

			if (strlcpy(alias->name, (yyvsp[0].v.string), sizeof(alias->name)) >=
			    sizeof(alias->name)) {
				yyerror("server alias truncated");
				free((yyvsp[0].v.string));
				free(alias);
				YYERROR;
			}
			free((yyvsp[0].v.string));

			if ((yyvsp[-1].v.number))
				alias->flags |= SRVFLAG_SERVER_MATCH;

			TAILQ_INSERT_TAIL(&srv->srv_hosts, alias, entry);
		}
#line 2151 "y.tab.c"
    break;

  case 26: /* serveroptsl: ERRDOCS STRING  */
#line 505 "parse.y"
                                        {
			if (parentsrv != NULL) {
				yyerror("errdocs inside location");
				YYERROR;
			}
			if ((yyvsp[0].v.string) != NULL && strlcpy(srv->srv_conf.errdocroot, (yyvsp[0].v.string),
			    sizeof(srv->srv_conf.errdocroot)) >=
			    sizeof(srv->srv_conf.errdocroot)) {
				yyerror("errdoc root path too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			srv->srv_conf.flags |= SRVFLAG_ERRDOCS;
		}
#line 2171 "y.tab.c"
    break;

  case 27: /* serveroptsl: NO ERRDOCS  */
#line 520 "parse.y"
                                        {
			if (parentsrv != NULL) {
				yyerror("errdocs inside location");
				YYERROR;
			}
			srv->srv_conf.flags &= ~SRVFLAG_ERRDOCS;
		}
#line 2183 "y.tab.c"
    break;

  case 28: /* serveroptsl: tcpip  */
#line 527 "parse.y"
                                        {
			if (parentsrv != NULL) {
				yyerror("tcp flags inside location");
				YYERROR;
			}
		}
#line 2194 "y.tab.c"
    break;

  case 29: /* serveroptsl: connection  */
#line 533 "parse.y"
                                        {
			if (parentsrv != NULL) {
				yyerror("connection options inside location");
				YYERROR;
			}
		}
#line 2205 "y.tab.c"
    break;

  case 30: /* serveroptsl: tls  */
#line 539 "parse.y"
                                        {
			struct server_config	*sc;
			int			 tls_flag = 0;

			if (parentsrv != NULL) {
				yyerror("tls configuration inside location");
				YYERROR;
			}

			/* Ensure that at least one server has TLS enabled. */
			TAILQ_FOREACH(sc, &srv->srv_hosts, entry) {
				tls_flag |= (sc->flags & SRVFLAG_TLS);
			}
			if (tls_flag == 0) {
				yyerror("tls options without tls listener");
				YYERROR;
			}
		}
#line 2228 "y.tab.c"
    break;

  case 40: /* $@2: %empty  */
#line 566 "parse.y"
                                                        {
			struct server		*s;
			struct sockaddr_un	*sun;

			if (srv->srv_conf.ss.ss_family == AF_UNSPEC) {
				yyerror("listen address not specified");
				free((yyvsp[0].v.string));
				YYERROR;
			}

			if (parentsrv != NULL) {
				yyerror("location %s inside location", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}

			if (!loadcfg) {
				free((yyvsp[0].v.string));
				YYACCEPT;
			}

			if ((s = calloc(1, sizeof (*s))) == NULL)
				fatal("out of memory");

			if (strlcpy(s->srv_conf.location, (yyvsp[0].v.string),
			    sizeof(s->srv_conf.location)) >=
			    sizeof(s->srv_conf.location)) {
				yyerror("server location truncated");
				free((yyvsp[0].v.string));
				free(s);
				YYERROR;
			}
			free((yyvsp[0].v.string));

			if (strlcpy(s->srv_conf.name, srv->srv_conf.name,
			    sizeof(s->srv_conf.name)) >=
			    sizeof(s->srv_conf.name)) {
				yyerror("server name truncated");
				free(s);
				YYERROR;
			}

			sun = (struct sockaddr_un *)&s->srv_conf.fastcgi_ss;
			sun->sun_family = AF_UNIX;
			(void)strlcpy(sun->sun_path, HTTPD_FCGI_SOCKET,
			    sizeof(sun->sun_path));
			sun->sun_len = sizeof(struct sockaddr_un);

			s->srv_conf.id = ++last_server_id;
			/* A location entry uses the parent id */
			s->srv_conf.parent_id = srv->srv_conf.id;
			s->srv_conf.flags = SRVFLAG_LOCATION;
			if ((yyvsp[-2].v.number) == 1) {
				s->srv_conf.flags &=
				    ~SRVFLAG_LOCATION_NOT_FOUND;
				s->srv_conf.flags |=
				    SRVFLAG_LOCATION_FOUND;
			} else if ((yyvsp[-2].v.number) == -1) {
				s->srv_conf.flags &=
				    ~SRVFLAG_LOCATION_FOUND;
				s->srv_conf.flags |=
				    SRVFLAG_LOCATION_NOT_FOUND;
			}
			if ((yyvsp[-1].v.number))
				s->srv_conf.flags |= SRVFLAG_LOCATION_MATCH;
			s->srv_s = -1;
			memcpy(&s->srv_conf.ss, &srv->srv_conf.ss,
			    sizeof(s->srv_conf.ss));
			s->srv_conf.port = srv->srv_conf.port;
			s->srv_conf.prefixlen = srv->srv_conf.prefixlen;
			s->srv_conf.tls_flags = srv->srv_conf.tls_flags;

			if (last_server_id == INT_MAX) {
				yyerror("too many servers/locations defined");
				free(s);
				YYERROR;
			}
			parentsrv = srv;
			srv = s;
			srv_conf = &srv->srv_conf;
			SPLAY_INIT(&srv->srv_clients);
		}
#line 2315 "y.tab.c"
    break;

  case 41: /* serveroptsl: LOCATION optfound optmatch STRING $@2 '{' optnl serveropts_l '}'  */
#line 647 "parse.y"
                                                {
			struct server	*s = NULL;
			uint32_t	 f;

			f = SRVFLAG_LOCATION_FOUND |
			    SRVFLAG_LOCATION_NOT_FOUND;

			TAILQ_FOREACH(s, conf->sc_servers, srv_entry) {
				/* Compare locations of same parent server */
				if ((s->srv_conf.flags & SRVFLAG_LOCATION) &&
				    s->srv_conf.parent_id ==
				    srv_conf->parent_id &&
				    (s->srv_conf.flags & f) ==
				    (srv_conf->flags & f) &&
				    strcmp(s->srv_conf.location,
				    srv_conf->location) == 0)
					break;
			}
			if (s != NULL) {
				yyerror("location \"%s\" defined twice",
				    srv->srv_conf.location);
				serverconfig_free(srv_conf);
				free(srv);
				YYABORT;
			}

			DPRINTF("adding location \"%s\" for \"%s[%u]\"",
			    srv->srv_conf.location,
			    srv->srv_conf.name, srv->srv_conf.id);

			TAILQ_INSERT_TAIL(conf->sc_servers, srv, srv_entry);

			srv = parentsrv;
			srv_conf = &parentsrv->srv_conf;
			parentsrv = NULL;
		}
#line 2356 "y.tab.c"
    break;

  case 42: /* serveroptsl: DEFAULT TYPE mediastring  */
#line 683 "parse.y"
                                                {
			srv_conf->flags |= SRVFLAG_DEFAULT_TYPE;
			memcpy(&srv_conf->default_type, &media,
			    sizeof(struct media_type));
		}
#line 2366 "y.tab.c"
    break;

  case 44: /* serveroptsl: hsts  */
#line 689 "parse.y"
                                                {
			if (parentsrv != NULL) {
				yyerror("hsts inside location");
				YYERROR;
			}
			srv->srv_conf.flags |= SRVFLAG_SERVER_HSTS;
		}
#line 2378 "y.tab.c"
    break;

  case 45: /* banner: BANNER  */
#line 698 "parse.y"
                                        {
			if (parentsrv != NULL) {
				yyerror("banner inside location");
				YYERROR;
			}
			srv->srv_conf.flags &= ~SRVFLAG_NO_BANNER;
		}
#line 2390 "y.tab.c"
    break;

  case 46: /* banner: NO BANNER  */
#line 705 "parse.y"
                                        {
			if (parentsrv != NULL) {
				yyerror("no banner inside location");
				YYERROR;
			}
			srv->srv_conf.flags |= SRVFLAG_NO_BANNER;
		}
#line 2402 "y.tab.c"
    break;

  case 47: /* optfound: %empty  */
#line 714 "parse.y"
                                { (yyval.v.number) = 0; }
#line 2408 "y.tab.c"
    break;

  case 48: /* optfound: FOUND  */
#line 715 "parse.y"
                                { (yyval.v.number) = 1; }
#line 2414 "y.tab.c"
    break;

  case 49: /* optfound: NOT FOUND  */
#line 716 "parse.y"
                                { (yyval.v.number) = -1; }
#line 2420 "y.tab.c"
    break;

  case 55: /* hstsflags: MAXAGE NUMBER  */
#line 728 "parse.y"
                                        {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > INT_MAX) {
				yyerror("invalid number of seconds: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			srv_conf->hsts_max_age = (yyvsp[0].v.number);
		}
#line 2432 "y.tab.c"
    break;

  case 56: /* hstsflags: SUBDOMAINS  */
#line 735 "parse.y"
                                        {
			srv->srv_conf.hsts_flags |= HSTSFLAG_SUBDOMAINS;
		}
#line 2440 "y.tab.c"
    break;

  case 57: /* hstsflags: PRELOAD  */
#line 738 "parse.y"
                                        {
			srv->srv_conf.hsts_flags |= HSTSFLAG_PRELOAD;
		}
#line 2448 "y.tab.c"
    break;

  case 58: /* fastcgi: NO FCGI  */
#line 743 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_FCGI;
			srv_conf->flags |= SRVFLAG_NO_FCGI;
		}
#line 2457 "y.tab.c"
    break;

  case 59: /* fastcgi: FCGI  */
#line 747 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_FCGI;
			srv_conf->flags |= SRVFLAG_FCGI;
		}
#line 2466 "y.tab.c"
    break;

  case 60: /* $@3: %empty  */
#line 751 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_FCGI;
			srv_conf->flags |= SRVFLAG_FCGI;
		}
#line 2475 "y.tab.c"
    break;

  case 62: /* $@4: %empty  */
#line 755 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_FCGI;
			srv_conf->flags |= SRVFLAG_FCGI;
		}
#line 2484 "y.tab.c"
    break;

  case 66: /* fcgiflags: SOCKET STRING  */
#line 765 "parse.y"
                                {
			struct sockaddr_un *sun;
			sun = (struct sockaddr_un *)&srv_conf->fastcgi_ss;
			memset(sun, 0, sizeof(*sun));
			sun->sun_family = AF_UNIX;
			if (strlcpy(sun->sun_path, (yyvsp[0].v.string), sizeof(sun->sun_path))
			    >= sizeof(sun->sun_path)) {
				yyerror("socket path too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			srv_conf->fastcgi_ss.ss_len =
			    sizeof(struct sockaddr_un);
			free((yyvsp[0].v.string));
		}
#line 2504 "y.tab.c"
    break;

  case 67: /* fcgiflags: SOCKET TCP STRING  */
#line 780 "parse.y"
                                    {
			if (get_fastcgi_dest(srv_conf, (yyvsp[0].v.string), FCGI_DEFAULT_PORT)
			    == -1) {
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2517 "y.tab.c"
    break;

  case 68: /* fcgiflags: SOCKET TCP STRING fcgiport  */
#line 788 "parse.y"
                                             {
			if (get_fastcgi_dest(srv_conf, (yyvsp[-1].v.string), (yyvsp[0].v.string)) == -1) {
				free((yyvsp[-1].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
			free((yyvsp[0].v.string));
		}
#line 2531 "y.tab.c"
    break;

  case 69: /* fcgiflags: PARAM STRING STRING  */
#line 797 "parse.y"
                                        {
			struct fastcgi_param	*param;

			if ((param = calloc(1, sizeof(*param))) == NULL)
				fatal("out of memory");

			if (strlcpy(param->name, (yyvsp[-1].v.string), sizeof(param->name)) >=
			    sizeof(param->name)) {
				yyerror("fastcgi_param name truncated");
				free((yyvsp[-1].v.string));
				free((yyvsp[0].v.string));
				free(param);
				YYERROR;
			}
			if (strlcpy(param->value, (yyvsp[0].v.string), sizeof(param->value)) >=
			    sizeof(param->value)) {
				yyerror("fastcgi_param value truncated");
				free((yyvsp[-1].v.string));
				free((yyvsp[0].v.string));
				free(param);
				YYERROR;
			}
			free((yyvsp[-1].v.string));
			free((yyvsp[0].v.string));

			DPRINTF("[%s,%s,%d]: adding param \"%s\" value \"%s\"",
			    srv_conf->location, srv_conf->name, srv_conf->id,
			    param->name, param->value);
			TAILQ_INSERT_HEAD(&srv_conf->fcgiparams, param, entry);
		}
#line 2566 "y.tab.c"
    break;

  case 70: /* fcgiflags: STRIP NUMBER  */
#line 827 "parse.y"
                                                {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > INT_MAX) {
				yyerror("invalid fastcgi strip number");
				YYERROR;
			}
			srv_conf->fcgistrip = (yyvsp[0].v.number);
		}
#line 2578 "y.tab.c"
    break;

  case 75: /* conflags: TIMEOUT timeout  */
#line 844 "parse.y"
                                                {
			memcpy(&srv_conf->timeout, &(yyvsp[0].v.tv),
			    sizeof(struct timeval));
		}
#line 2587 "y.tab.c"
    break;

  case 76: /* conflags: REQUEST TIMEOUT timeout  */
#line 848 "parse.y"
                                                {
			memcpy(&srv_conf->requesttimeout, &(yyvsp[0].v.tv),
			    sizeof(struct timeval));
		}
#line 2596 "y.tab.c"
    break;

  case 77: /* conflags: MAXIMUM REQUESTS NUMBER  */
#line 852 "parse.y"
                                                {
			srv_conf->maxrequests = (yyvsp[0].v.number);
		}
#line 2604 "y.tab.c"
    break;

  case 78: /* conflags: MAXIMUM REQUEST BODY NUMBER  */
#line 855 "parse.y"
                                                {
			srv_conf->maxrequestbody = (yyvsp[0].v.number);
		}
#line 2612 "y.tab.c"
    break;

  case 83: /* tlsopts: CERTIFICATE STRING  */
#line 868 "parse.y"
                                                {
			free(srv_conf->tls_cert_file);
			if ((srv_conf->tls_cert_file = strdup((yyvsp[0].v.string))) == NULL)
				fatal("out of memory");
			free((yyvsp[0].v.string));
		}
#line 2623 "y.tab.c"
    break;

  case 84: /* tlsopts: KEY STRING  */
#line 874 "parse.y"
                                                {
			free(srv_conf->tls_key_file);
			if ((srv_conf->tls_key_file = strdup((yyvsp[0].v.string))) == NULL)
				fatal("out of memory");
			free((yyvsp[0].v.string));
		}
#line 2634 "y.tab.c"
    break;

  case 85: /* tlsopts: OCSP STRING  */
#line 880 "parse.y"
                                                {
			free(srv_conf->tls_ocsp_staple_file);
			if ((srv_conf->tls_ocsp_staple_file = strdup((yyvsp[0].v.string)))
			    == NULL)
				fatal("out of memory");
			free((yyvsp[0].v.string));
		}
#line 2646 "y.tab.c"
    break;

  case 86: /* tlsopts: CIPHERS STRING  */
#line 887 "parse.y"
                                                {
			if (strlcpy(srv_conf->tls_ciphers, (yyvsp[0].v.string),
			    sizeof(srv_conf->tls_ciphers)) >=
			    sizeof(srv_conf->tls_ciphers)) {
				yyerror("ciphers too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2661 "y.tab.c"
    break;

  case 87: /* tlsopts: CLIENT CA STRING tlsclientopt  */
#line 897 "parse.y"
                                                {
			srv_conf->tls_flags |= TLSFLAG_CA;
			free(srv_conf->tls_ca_file);
			if ((srv_conf->tls_ca_file = strdup((yyvsp[-1].v.string))) == NULL)
				fatal("out of memory");
			free((yyvsp[-1].v.string));
		}
#line 2673 "y.tab.c"
    break;

  case 88: /* tlsopts: DHE STRING  */
#line 904 "parse.y"
                                                {
			if (strlcpy(srv_conf->tls_dhe_params, (yyvsp[0].v.string),
			    sizeof(srv_conf->tls_dhe_params)) >=
			    sizeof(srv_conf->tls_dhe_params)) {
				yyerror("dhe too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2688 "y.tab.c"
    break;

  case 89: /* tlsopts: ECDHE STRING  */
#line 914 "parse.y"
                                                {
			if (strlcpy(srv_conf->tls_ecdhe_curves, (yyvsp[0].v.string),
			    sizeof(srv_conf->tls_ecdhe_curves)) >=
			    sizeof(srv_conf->tls_ecdhe_curves)) {
				yyerror("ecdhe too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2703 "y.tab.c"
    break;

  case 90: /* tlsopts: PROTOCOLS STRING  */
#line 924 "parse.y"
                                                {
			if (tls_config_parse_protocols(
			    &srv_conf->tls_protocols, (yyvsp[0].v.string)) != 0) {
				yyerror("invalid tls protocols");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2717 "y.tab.c"
    break;

  case 91: /* tlsopts: TICKET LIFETIME DEFAULT  */
#line 933 "parse.y"
                                                {
			srv_conf->tls_ticket_lifetime = SERVER_DEF_TLS_LIFETIME;
		}
#line 2725 "y.tab.c"
    break;

  case 92: /* tlsopts: TICKET LIFETIME NUMBER  */
#line 936 "parse.y"
                                                {
			if ((yyvsp[0].v.number) != 0 && (yyvsp[0].v.number) < SERVER_MIN_TLS_LIFETIME) {
				yyerror("ticket lifetime too small");
				YYERROR;
			}
			if ((yyvsp[0].v.number) > SERVER_MAX_TLS_LIFETIME) {
				yyerror("ticket lifetime too large");
				YYERROR;
			}
			srv_conf->tls_ticket_lifetime = (yyvsp[0].v.number);
		}
#line 2741 "y.tab.c"
    break;

  case 93: /* tlsopts: NO TICKET  */
#line 947 "parse.y"
                                                {
			srv_conf->tls_ticket_lifetime = 0;
		}
#line 2749 "y.tab.c"
    break;

  case 95: /* tlsclientopt: tlsclientopt CRL STRING  */
#line 953 "parse.y"
                                                {
			srv_conf->tls_flags = TLSFLAG_CRL;
			free(srv_conf->tls_crl_file);
			if ((srv_conf->tls_crl_file = strdup((yyvsp[0].v.string))) == NULL)
				fatal("out of memory");
			free((yyvsp[0].v.string));
		}
#line 2761 "y.tab.c"
    break;

  case 96: /* tlsclientopt: tlsclientopt OPTIONAL  */
#line 960 "parse.y"
                                                {
			srv_conf->tls_flags |= TLSFLAG_OPTIONAL;
		}
#line 2769 "y.tab.c"
    break;

  case 101: /* rootflags: STRING  */
#line 972 "parse.y"
                                        {
			if (strlcpy(srv->srv_conf.root, (yyvsp[0].v.string),
			    sizeof(srv->srv_conf.root)) >=
			    sizeof(srv->srv_conf.root)) {
				yyerror("document root too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			srv->srv_conf.flags |= SRVFLAG_ROOT;
		}
#line 2785 "y.tab.c"
    break;

  case 106: /* requestflags: REWRITE STRING  */
#line 993 "parse.y"
                                                {
			if (strlcpy(srv->srv_conf.path, (yyvsp[0].v.string),
			    sizeof(srv->srv_conf.path)) >=
			    sizeof(srv->srv_conf.path)) {
				yyerror("request path too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			srv->srv_conf.flags |= SRVFLAG_PATH_REWRITE;
			srv->srv_conf.flags &= ~SRVFLAG_NO_PATH_REWRITE;
		}
#line 2802 "y.tab.c"
    break;

  case 107: /* requestflags: NO REWRITE  */
#line 1005 "parse.y"
                                                {
			srv->srv_conf.flags |= SRVFLAG_NO_PATH_REWRITE;
			srv->srv_conf.flags &= ~SRVFLAG_PATH_REWRITE;
		}
#line 2811 "y.tab.c"
    break;

  case 108: /* requestflags: STRIP NUMBER  */
#line 1009 "parse.y"
                                                {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > INT_MAX) {
				yyerror("invalid strip number");
				YYERROR;
			}
			srv->srv_conf.strip = (yyvsp[0].v.number);
		}
#line 2823 "y.tab.c"
    break;

  case 109: /* authenticate: NO AUTHENTICATE  */
#line 1018 "parse.y"
                                                {
			srv->srv_conf.flags |= SRVFLAG_NO_AUTH;
		}
#line 2831 "y.tab.c"
    break;

  case 110: /* authenticate: AUTHENTICATE authopts  */
#line 1021 "parse.y"
                                                {
			struct auth	*auth;

			if ((auth = auth_add(conf->sc_auth, &(yyvsp[0].v.auth))) == NULL) {
				yyerror("failed to add auth");
				YYERROR;
			}

			if (auth->auth_id == 0) {
				/* New htpasswd, get new Id */
				auth->auth_id = ++last_auth_id;
				if (last_auth_id == INT_MAX) {
					yyerror("too many auth ids defined");
					auth_free(conf->sc_auth, auth);
					YYERROR;
				}
			}

			srv->srv_conf.auth_id = auth->auth_id;
			srv->srv_conf.flags |= SRVFLAG_AUTH;
		}
#line 2857 "y.tab.c"
    break;

  case 111: /* authopts: STRING WITH STRING  */
#line 1044 "parse.y"
                                        {
			if (strlcpy(srv->srv_conf.auth_realm, (yyvsp[-2].v.string),
			    sizeof(srv->srv_conf.auth_realm)) >=
			    sizeof(srv->srv_conf.auth_realm)) {
				yyerror("basic auth realm name too long");
				free((yyvsp[-2].v.string));
				YYERROR;
			}
			free((yyvsp[-2].v.string));
			if (strlcpy((yyval.v.auth).auth_htpasswd, (yyvsp[0].v.string),
			    sizeof((yyval.v.auth).auth_htpasswd)) >=
			    sizeof((yyval.v.auth).auth_htpasswd)) {
				yyerror("password file name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

		}
#line 2881 "y.tab.c"
    break;

  case 112: /* authopts: WITH STRING  */
#line 1063 "parse.y"
                                        {
			if (strlcpy((yyval.v.auth).auth_htpasswd, (yyvsp[0].v.string),
			    sizeof((yyval.v.auth).auth_htpasswd)) >=
			    sizeof((yyval.v.auth).auth_htpasswd)) {
				yyerror("password file name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2896 "y.tab.c"
    break;

  case 117: /* dirflags: INDEX STRING  */
#line 1082 "parse.y"
                                        {
			if (strlcpy(srv_conf->index, (yyvsp[0].v.string),
			    sizeof(srv_conf->index)) >=
			    sizeof(srv_conf->index)) {
				yyerror("index file too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			srv_conf->flags &= ~SRVFLAG_NO_INDEX;
			srv_conf->flags |= SRVFLAG_INDEX;
			free((yyvsp[0].v.string));
		}
#line 2913 "y.tab.c"
    break;

  case 118: /* dirflags: NO INDEX  */
#line 1094 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_INDEX;
			srv_conf->flags |= SRVFLAG_NO_INDEX;
		}
#line 2922 "y.tab.c"
    break;

  case 119: /* dirflags: AUTO INDEX  */
#line 1098 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_AUTO_INDEX;
			srv_conf->flags |= SRVFLAG_AUTO_INDEX;
		}
#line 2931 "y.tab.c"
    break;

  case 120: /* dirflags: NO AUTO INDEX  */
#line 1102 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_AUTO_INDEX;
			srv_conf->flags |= SRVFLAG_NO_AUTO_INDEX;
		}
#line 2940 "y.tab.c"
    break;

  case 123: /* logformat: NO LOG  */
#line 1111 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_LOG;
			srv_conf->flags |= SRVFLAG_NO_LOG;
		}
#line 2949 "y.tab.c"
    break;

  case 127: /* logflags: SYSLOG  */
#line 1122 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_SYSLOG;
			srv_conf->flags |= SRVFLAG_SYSLOG;
		}
#line 2958 "y.tab.c"
    break;

  case 128: /* logflags: NO SYSLOG  */
#line 1126 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_SYSLOG;
			srv_conf->flags |= SRVFLAG_NO_SYSLOG;
		}
#line 2967 "y.tab.c"
    break;

  case 129: /* logflags: ACCESS STRING  */
#line 1130 "parse.y"
                                        {
			if (strlcpy(srv_conf->accesslog, (yyvsp[0].v.string),
			    sizeof(srv_conf->accesslog)) >=
			    sizeof(srv_conf->accesslog)) {
				yyerror("access log name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			srv_conf->flags |= SRVFLAG_ACCESS_LOG;
		}
#line 2983 "y.tab.c"
    break;

  case 130: /* logflags: ERR STRING  */
#line 1141 "parse.y"
                                        {
			if (strlcpy(srv_conf->errorlog, (yyvsp[0].v.string),
			    sizeof(srv_conf->errorlog)) >=
			    sizeof(srv_conf->errorlog)) {
				yyerror("error log name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			srv_conf->flags |= SRVFLAG_ERROR_LOG;
		}
#line 2999 "y.tab.c"
    break;

  case 131: /* logstyle: COMMON  */
#line 1154 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_LOG;
			srv_conf->flags |= SRVFLAG_LOG;
			srv_conf->logformat = LOG_FORMAT_COMMON;
		}
#line 3009 "y.tab.c"
    break;

  case 132: /* logstyle: COMBINED  */
#line 1159 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_LOG;
			srv_conf->flags |= SRVFLAG_LOG;
			srv_conf->logformat = LOG_FORMAT_COMBINED;
		}
#line 3019 "y.tab.c"
    break;

  case 133: /* logstyle: CONNECTION  */
#line 1164 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_LOG;
			srv_conf->flags |= SRVFLAG_LOG;
			srv_conf->logformat = LOG_FORMAT_CONNECTION;
		}
#line 3029 "y.tab.c"
    break;

  case 134: /* logstyle: FORWARDED  */
#line 1169 "parse.y"
                                        {
			srv_conf->flags &= ~SRVFLAG_NO_LOG;
			srv_conf->flags |= SRVFLAG_LOG;
			srv_conf->logformat = LOG_FORMAT_FORWARDED;
		}
#line 3039 "y.tab.c"
    break;

  case 135: /* filter: block RETURN NUMBER optstring  */
#line 1176 "parse.y"
                                                {
			if ((yyvsp[-1].v.number) <= 0 || server_httperror_byid((yyvsp[-1].v.number)) == NULL) {
				yyerror("invalid return code: %lld", (yyvsp[-1].v.number));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			srv_conf->return_code = (yyvsp[-1].v.number);

			if ((yyvsp[0].v.string) != NULL) {
				/* Only for 3xx redirection headers */
				if ((yyvsp[-1].v.number) < 300 || (yyvsp[-1].v.number) > 399) {
					yyerror("invalid return code for "
					    "location URI");
					free((yyvsp[0].v.string));
					YYERROR;
				}
				srv_conf->return_uri = (yyvsp[0].v.string);
				srv_conf->return_uri_len = strlen((yyvsp[0].v.string)) + 1;
			}
		}
#line 3064 "y.tab.c"
    break;

  case 136: /* filter: block DROP  */
#line 1196 "parse.y"
                                                {
			/* No return code, silently drop the connection */
			srv_conf->return_code = 0;
		}
#line 3073 "y.tab.c"
    break;

  case 137: /* filter: block  */
#line 1200 "parse.y"
                                                {
			/* Forbidden */
			srv_conf->return_code = 403;
		}
#line 3082 "y.tab.c"
    break;

  case 138: /* filter: PASS  */
#line 1204 "parse.y"
                                                {
			srv_conf->flags &= ~SRVFLAG_BLOCK;
			srv_conf->flags |= SRVFLAG_NO_BLOCK;
		}
#line 3091 "y.tab.c"
    break;

  case 139: /* block: BLOCK  */
#line 1210 "parse.y"
                                                {
			srv_conf->flags &= ~SRVFLAG_NO_BLOCK;
			srv_conf->flags |= SRVFLAG_BLOCK;
		}
#line 3100 "y.tab.c"
    break;

  case 140: /* optmatch: %empty  */
#line 1216 "parse.y"
                                        { (yyval.v.number) = 0; }
#line 3106 "y.tab.c"
    break;

  case 141: /* optmatch: MATCH  */
#line 1217 "parse.y"
                                        { (yyval.v.number) = 1; }
#line 3112 "y.tab.c"
    break;

  case 142: /* optstring: %empty  */
#line 1220 "parse.y"
                                        { (yyval.v.string) = NULL; }
#line 3118 "y.tab.c"
    break;

  case 143: /* optstring: STRING  */
#line 1221 "parse.y"
                                        { (yyval.v.string) = (yyvsp[0].v.string); }
#line 3124 "y.tab.c"
    break;

  case 144: /* fcgiport: NUMBER  */
#line 1224 "parse.y"
                                        {
			if ((yyvsp[0].v.number) <= 0 || (yyvsp[0].v.number) > (int)USHRT_MAX) {
				yyerror("invalid port: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			if (asprintf(&(yyval.v.string), "%lld", (yyvsp[0].v.number)) == -1) {
				yyerror("out of memory");
				YYERROR;
			}
		}
#line 3139 "y.tab.c"
    break;

  case 145: /* fcgiport: STRING  */
#line 1234 "parse.y"
                                        {
			if (getservice((yyvsp[0].v.string)) <= 0) {
				yyerror("invalid port: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}

			(yyval.v.string) = (yyvsp[0].v.string);
		}
#line 3153 "y.tab.c"
    break;

  case 146: /* gzip_static: NO GZIPSTATIC  */
#line 1245 "parse.y"
                                        {
			srv->srv_conf.flags &= ~SRVFLAG_GZIP_STATIC;
		}
#line 3161 "y.tab.c"
    break;

  case 147: /* gzip_static: GZIPSTATIC  */
#line 1248 "parse.y"
                                        {
			srv->srv_conf.flags |= SRVFLAG_GZIP_STATIC;
		}
#line 3169 "y.tab.c"
    break;

  case 152: /* tcpflags: SACK  */
#line 1261 "parse.y"
                                        { srv_conf->tcpflags |= TCPFLAG_SACK; }
#line 3175 "y.tab.c"
    break;

  case 153: /* tcpflags: NO SACK  */
#line 1262 "parse.y"
                                        { srv_conf->tcpflags |= TCPFLAG_NSACK; }
#line 3181 "y.tab.c"
    break;

  case 154: /* tcpflags: NODELAY  */
#line 1263 "parse.y"
                                        {
			srv_conf->tcpflags |= TCPFLAG_NODELAY;
		}
#line 3189 "y.tab.c"
    break;

  case 155: /* tcpflags: NO NODELAY  */
#line 1266 "parse.y"
                                        {
			srv_conf->tcpflags |= TCPFLAG_NNODELAY;
		}
#line 3197 "y.tab.c"
    break;

  case 156: /* tcpflags: BACKLOG NUMBER  */
#line 1269 "parse.y"
                                        {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > SERVER_MAX_CLIENTS) {
				yyerror("invalid backlog: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			srv_conf->tcpbacklog = (yyvsp[0].v.number);
		}
#line 3209 "y.tab.c"
    break;

  case 157: /* tcpflags: SOCKET BUFFER NUMBER  */
#line 1276 "parse.y"
                                        {
			srv_conf->tcpflags |= TCPFLAG_BUFSIZ;
			if ((srv_conf->tcpbufsiz = (yyvsp[0].v.number)) < 0) {
				yyerror("invalid socket buffer size: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
		}
#line 3221 "y.tab.c"
    break;

  case 158: /* tcpflags: IP STRING NUMBER  */
#line 1283 "parse.y"
                                        {
			if ((yyvsp[0].v.number) < 0) {
				yyerror("invalid ttl: %lld", (yyvsp[0].v.number));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			if (strcasecmp("ttl", (yyvsp[-1].v.string)) == 0) {
				srv_conf->tcpflags |= TCPFLAG_IPTTL;
				srv_conf->tcpipttl = (yyvsp[0].v.number);
			} else if (strcasecmp("minttl", (yyvsp[-1].v.string)) == 0) {
				srv_conf->tcpflags |= TCPFLAG_IPMINTTL;
				srv_conf->tcpipminttl = (yyvsp[0].v.number);
			} else {
				yyerror("invalid TCP/IP flag: %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
		}
#line 3245 "y.tab.c"
    break;

  case 164: /* mediastring: STRING '/' STRING  */
#line 1315 "parse.y"
                                        {
			if (strlcpy(media.media_type, (yyvsp[-2].v.string),
			    sizeof(media.media_type)) >=
			    sizeof(media.media_type) ||
			    strlcpy(media.media_subtype, (yyvsp[0].v.string),
			    sizeof(media.media_subtype)) >=
			    sizeof(media.media_subtype)) {
				yyerror("media type too long");
				free((yyvsp[-2].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[-2].v.string));
			free((yyvsp[0].v.string));
		}
#line 3265 "y.tab.c"
    break;

  case 167: /* medianamesl: numberstring  */
#line 1336 "parse.y"
                                                        {
			if (strlcpy(media.media_name, (yyvsp[0].v.string),
			    sizeof(media.media_name)) >=
			    sizeof(media.media_name)) {
				yyerror("media name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			if (!loadcfg)
				break;

			if (media_add(conf->sc_mediatypes, &media) == NULL) {
				yyerror("failed to add media type");
				YYERROR;
			}
		}
#line 3288 "y.tab.c"
    break;

  case 168: /* port: PORT NUMBER  */
#line 1356 "parse.y"
                              {
			if ((yyvsp[0].v.number) <= 0 || (yyvsp[0].v.number) > (int)USHRT_MAX) {
				yyerror("invalid port: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			(yyval.v.port).val[0] = htons((yyvsp[0].v.number));
			(yyval.v.port).op = 1;
		}
#line 3301 "y.tab.c"
    break;

  case 169: /* port: PORT STRING  */
#line 1364 "parse.y"
                              {
			int	 val;

			if ((val = getservice((yyvsp[0].v.string))) == -1) {
				yyerror("invalid port: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			(yyval.v.port).val[0] = val;
			(yyval.v.port).op = 1;
		}
#line 3319 "y.tab.c"
    break;

  case 170: /* timeout: NUMBER  */
#line 1380 "parse.y"
                {
			if ((yyvsp[0].v.number) < 0) {
				yyerror("invalid timeout: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			(yyval.v.tv).tv_sec = (yyvsp[0].v.number);
			(yyval.v.tv).tv_usec = 0;
		}
#line 3332 "y.tab.c"
    break;

  case 171: /* numberstring: NUMBER  */
#line 1390 "parse.y"
                                        {
			char *s;
			if (asprintf(&s, "%lld", (yyvsp[0].v.number)) == -1) {
				yyerror("asprintf: number");
				YYERROR;
			}
			(yyval.v.string) = s;
		}
#line 3345 "y.tab.c"
    break;


#line 3349 "y.tab.c"

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

#line 1416 "parse.y"


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
		{ "access",		ACCESS },
		{ "alias",		ALIAS },
		{ "authenticate",	AUTHENTICATE},
		{ "auto",		AUTO },
		{ "backlog",		BACKLOG },
		{ "banner",		BANNER },
		{ "block",		BLOCK },
		{ "body",		BODY },
		{ "buffer",		BUFFER },
		{ "ca",			CA },
		{ "certificate",	CERTIFICATE },
		{ "chroot",		CHROOT },
		{ "ciphers",		CIPHERS },
		{ "client",		CLIENT },
		{ "combined",		COMBINED },
		{ "common",		COMMON },
		{ "connection",		CONNECTION },
		{ "crl",		CRL },
		{ "default",		DEFAULT },
		{ "dhe",		DHE },
		{ "directory",		DIRECTORY },
		{ "drop",		DROP },
		{ "ecdhe",		ECDHE },
		{ "errdocs",		ERRDOCS },
		{ "error",		ERR },
		{ "fastcgi",		FCGI },
		{ "forwarded",		FORWARDED },
		{ "found",		FOUND },
		{ "gzip-static",	GZIPSTATIC },
		{ "hsts",		HSTS },
		{ "include",		INCLUDE },
		{ "index",		INDEX },
		{ "ip",			IP },
		{ "key",		KEY },
		{ "lifetime",		LIFETIME },
		{ "listen",		LISTEN },
		{ "location",		LOCATION },
		{ "log",		LOG },
		{ "logdir",		LOGDIR },
		{ "match",		MATCH },
		{ "max",		MAXIMUM },
		{ "max-age",		MAXAGE },
		{ "no",			NO },
		{ "nodelay",		NODELAY },
		{ "not",		NOT },
		{ "ocsp",		OCSP },
		{ "on",			ON },
		{ "optional",		OPTIONAL },
		{ "param",		PARAM },
		{ "pass",		PASS },
		{ "port",		PORT },
		{ "prefork",		PREFORK },
		{ "preload",		PRELOAD },
		{ "protocols",		PROTOCOLS },
		{ "request",		REQUEST },
		{ "requests",		REQUESTS },
		{ "return",		RETURN },
		{ "rewrite",		REWRITE },
		{ "root",		ROOT },
		{ "sack",		SACK },
		{ "server",		SERVER },
		{ "socket",		SOCKET },
		{ "strip",		STRIP },
		{ "style",		STYLE },
		{ "subdomains",		SUBDOMAINS },
		{ "syslog",		SYSLOG },
		{ "tcp",		TCP },
		{ "ticket",		TICKET },
		{ "timeout",		TIMEOUT },
		{ "tls",		TLS },
		{ "type",		TYPE },
		{ "types",		TYPES },
		{ "with",		WITH }
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
			err(1, "%s", __func__);
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
			err(1, "%s", __func__);
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

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && x != '<' && x != '>' && \
	x != '!' && x != '=' && x != '#' && \
	x != ',' && x != ';' && x != '/'))

	if (isalnum(c) || c == ':' || c == '_' || c == '*') {
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
				err(1, "%s", __func__);
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
		log_warn("cannot stat %s", fname);
		return (-1);
	}
	if (st.st_uid != 0 && st.st_uid != getuid()) {
		log_warnx("%s: owner not root or current user", fname);
		return (-1);
	}
	if (st.st_mode & (S_IWGRP | S_IXGRP | S_IRWXO)) {
		log_warnx("%s: group writable or world read/writable", fname);
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
parse_config(const char *filename, struct httpd *x_conf)
{
	struct sym		*sym, *next;
	struct media_type	 dflt = HTTPD_DEFAULT_TYPE;

	conf = x_conf;
	if (config_init(conf) == -1) {
		log_warn("%s: cannot initialize configuration", __func__);
		return (-1);
	}

	/* Set default media type */
	memcpy(&conf->sc_default_type, &dflt, sizeof(struct media_type));

	errors = 0;

	if ((file = pushfile(filename, 0)) == NULL)
		return (-1);

	topfile = file;
	setservent(1);

	yyparse();
	errors = file->errors;
	while (popfile() != EOF)
		;

	endservent();
	endprotoent();

	/* Free macros */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	return (errors ? -1 : 0);
}

int
load_config(const char *filename, struct httpd *x_conf)
{
	struct sym		*sym, *next;
	struct http_mediatype	 mediatypes[] = MEDIA_TYPES;
	struct media_type	 m;
	int			 i;

	memset(&m, 0, sizeof(m));
	conf = x_conf;
	conf->sc_flags = 0;

	loadcfg = 1;
	errors = 0;
	last_server_id = 0;
	last_auth_id = 0;

	srv = NULL;

	if ((file = pushfile(filename, 0)) == NULL)
		return (-1);

	topfile = file;
	setservent(1);

	yyparse();
	errors = file->errors;
	popfile();

	endservent();
	endprotoent();

	/* Free macros and check which have not been used. */
	for (sym = TAILQ_FIRST(&symhead); sym != NULL; sym = next) {
		next = TAILQ_NEXT(sym, entry);
		if ((conf->sc_opts & HTTPD_OPT_VERBOSE) && !sym->used)
			fprintf(stderr, "warning: macro '%s' not "
			    "used\n", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (TAILQ_EMPTY(conf->sc_servers)) {
		log_warnx("no actions, nothing to do");
		errors++;
	}

	if (RB_EMPTY(conf->sc_mediatypes)) {
		/* Add default media types */
		for (i = 0; mediatypes[i].media_name != NULL; i++) {
			(void)strlcpy(m.media_name, mediatypes[i].media_name,
			    sizeof(m.media_name));
			(void)strlcpy(m.media_type, mediatypes[i].media_type,
			    sizeof(m.media_type));
			(void)strlcpy(m.media_subtype,
			    mediatypes[i].media_subtype,
			    sizeof(m.media_subtype));
			m.media_encoding = NULL;

			if (media_add(conf->sc_mediatypes, &m) == NULL) {
				log_warnx("failed to add default media \"%s\"",
				    m.media_name);
				errors++;
			}
		}
	}

	return (errors ? -1 : 0);
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
		errx(1, "%s: strndup", __func__);
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

struct address *
host_v4(const char *s)
{
	struct in_addr		 ina;
	struct sockaddr_in	*sain;
	struct address		*h;

	memset(&ina, 0, sizeof(ina));
	if (inet_pton(AF_INET, s, &ina) != 1)
		return (NULL);

	if ((h = calloc(1, sizeof(*h))) == NULL)
		fatal(__func__);
	sain = (struct sockaddr_in *)&h->ss;
	sain->sin_len = sizeof(struct sockaddr_in);
	sain->sin_family = AF_INET;
	sain->sin_addr.s_addr = ina.s_addr;
	if (sain->sin_addr.s_addr == INADDR_ANY)
		h->prefixlen = 0; /* 0.0.0.0 address */
	else
		h->prefixlen = -1; /* host address */
	return (h);
}

struct address *
host_v6(const char *s)
{
	struct addrinfo		 hints, *res;
	struct sockaddr_in6	*sa_in6;
	struct address		*h = NULL;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM; /* dummy */
	hints.ai_flags = AI_NUMERICHOST;
	if (getaddrinfo(s, "0", &hints, &res) == 0) {
		if ((h = calloc(1, sizeof(*h))) == NULL)
			fatal(__func__);
		sa_in6 = (struct sockaddr_in6 *)&h->ss;
		sa_in6->sin6_len = sizeof(struct sockaddr_in6);
		sa_in6->sin6_family = AF_INET6;
		memcpy(&sa_in6->sin6_addr,
		    &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr,
		    sizeof(sa_in6->sin6_addr));
		sa_in6->sin6_scope_id =
		    ((struct sockaddr_in6 *)res->ai_addr)->sin6_scope_id;
		if (memcmp(&sa_in6->sin6_addr, &in6addr_any,
		    sizeof(sa_in6->sin6_addr)) == 0)
			h->prefixlen = 0; /* any address */
		else
			h->prefixlen = -1; /* host address */
		freeaddrinfo(res);
	}

	return (h);
}

int
host_dns(const char *s, struct addresslist *al, int max,
    struct portrange *port, const char *ifname, int ipproto)
{
	struct addrinfo		 hints, *res0, *res;
	int			 error, cnt = 0;
	struct sockaddr_in	*sain;
	struct sockaddr_in6	*sin6;
	struct address		*h;

	if ((cnt = host_if(s, al, max, port, ifname, ipproto)) != 0)
		return (cnt);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; /* DUMMY */
	hints.ai_flags = AI_ADDRCONFIG;
	error = getaddrinfo(s, NULL, &hints, &res0);
	if (error == EAI_AGAIN || error == EAI_NODATA || error == EAI_NONAME)
		return (0);
	if (error) {
		log_warnx("%s: could not parse \"%s\": %s", __func__, s,
		    gai_strerror(error));
		return (-1);
	}

	for (res = res0; res && cnt < max; res = res->ai_next) {
		if (res->ai_family != AF_INET &&
		    res->ai_family != AF_INET6)
			continue;
		if ((h = calloc(1, sizeof(*h))) == NULL)
			fatal(__func__);

		if (port != NULL)
			memcpy(&h->port, port, sizeof(h->port));
		if (ifname != NULL) {
			if (strlcpy(h->ifname, ifname, sizeof(h->ifname)) >=
			    sizeof(h->ifname))
				log_warnx("%s: interface name truncated",
				    __func__);
			freeaddrinfo(res0);
			free(h);
			return (-1);
		}
		if (ipproto != -1)
			h->ipproto = ipproto;
		h->ss.ss_family = res->ai_family;
		h->prefixlen = -1; /* host address */

		if (res->ai_family == AF_INET) {
			sain = (struct sockaddr_in *)&h->ss;
			sain->sin_len = sizeof(struct sockaddr_in);
			sain->sin_addr.s_addr = ((struct sockaddr_in *)
			    res->ai_addr)->sin_addr.s_addr;
		} else {
			sin6 = (struct sockaddr_in6 *)&h->ss;
			sin6->sin6_len = sizeof(struct sockaddr_in6);
			memcpy(&sin6->sin6_addr, &((struct sockaddr_in6 *)
			    res->ai_addr)->sin6_addr, sizeof(struct in6_addr));
		}

		TAILQ_INSERT_HEAD(al, h, entry);
		cnt++;
	}
	if (cnt == max && res) {
		log_warnx("%s: %s resolves to more than %d hosts", __func__,
		    s, max);
	}
	freeaddrinfo(res0);
	return (cnt);
}

int
host_if(const char *s, struct addresslist *al, int max,
    struct portrange *port, const char *ifname, int ipproto)
{
	struct ifaddrs		*ifap, *p;
	struct sockaddr_in	*sain;
	struct sockaddr_in6	*sin6;
	struct address		*h;
	int			 cnt = 0, af;

	if (getifaddrs(&ifap) == -1)
		fatal("getifaddrs");

	/* First search for IPv4 addresses */
	af = AF_INET;

 nextaf:
	for (p = ifap; p != NULL && cnt < max; p = p->ifa_next) {
		if (p->ifa_addr == NULL ||
		    p->ifa_addr->sa_family != af ||
		    (strcmp(s, p->ifa_name) != 0 &&
		    !is_if_in_group(p->ifa_name, s)))
			continue;
		if ((h = calloc(1, sizeof(*h))) == NULL)
			fatal("calloc");

		if (port != NULL)
			memcpy(&h->port, port, sizeof(h->port));
		if (ifname != NULL) {
			if (strlcpy(h->ifname, ifname, sizeof(h->ifname)) >=
			    sizeof(h->ifname))
				log_warnx("%s: interface name truncated",
				    __func__);
			freeifaddrs(ifap);
			free(h);
			return (-1);
		}
		if (ipproto != -1)
			h->ipproto = ipproto;
		h->ss.ss_family = af;
		h->prefixlen = -1; /* host address */

		if (af == AF_INET) {
			sain = (struct sockaddr_in *)&h->ss;
			sain->sin_len = sizeof(struct sockaddr_in);
			sain->sin_addr.s_addr = ((struct sockaddr_in *)
			    p->ifa_addr)->sin_addr.s_addr;
		} else {
			sin6 = (struct sockaddr_in6 *)&h->ss;
			sin6->sin6_len = sizeof(struct sockaddr_in6);
			memcpy(&sin6->sin6_addr, &((struct sockaddr_in6 *)
			    p->ifa_addr)->sin6_addr, sizeof(struct in6_addr));
			sin6->sin6_scope_id = ((struct sockaddr_in6 *)
			    p->ifa_addr)->sin6_scope_id;
		}

		TAILQ_INSERT_HEAD(al, h, entry);
		cnt++;
	}
	if (af == AF_INET) {
		/* Next search for IPv6 addresses */
		af = AF_INET6;
		goto nextaf;
	}

	if (cnt > max) {
		log_warnx("%s: %s resolves to more than %d hosts", __func__,
		    s, max);
	}
	freeifaddrs(ifap);
	return (cnt);
}

int
host(const char *s, struct addresslist *al, int max,
    struct portrange *port, const char *ifname, int ipproto)
{
	struct address *h;

	h = host_v4(s);

	/* IPv6 address? */
	if (h == NULL)
		h = host_v6(s);

	if (h != NULL) {
		if (port != NULL)
			memcpy(&h->port, port, sizeof(h->port));
		if (ifname != NULL) {
			if (strlcpy(h->ifname, ifname, sizeof(h->ifname)) >=
			    sizeof(h->ifname)) {
				log_warnx("%s: interface name truncated",
				    __func__);
				free(h);
				return (-1);
			}
		}
		if (ipproto != -1)
			h->ipproto = ipproto;

		TAILQ_INSERT_HEAD(al, h, entry);
		return (1);
	}

	return (host_dns(s, al, max, port, ifname, ipproto));
}

struct server *
server_inherit(struct server *src, struct server_config *alias,
    struct server_config *addr)
{
	struct server	*dst, *s, *dstl;

	if ((dst = calloc(1, sizeof(*dst))) == NULL)
		fatal("out of memory");

	/* Copy the source server and assign a new Id */
	memcpy(&dst->srv_conf, &src->srv_conf, sizeof(dst->srv_conf));
	if ((dst->srv_conf.tls_cert_file =
	    strdup(src->srv_conf.tls_cert_file)) == NULL)
		fatal("out of memory");
	if ((dst->srv_conf.tls_key_file =
	    strdup(src->srv_conf.tls_key_file)) == NULL)
		fatal("out of memory");
	if (src->srv_conf.tls_ocsp_staple_file != NULL) {
		if ((dst->srv_conf.tls_ocsp_staple_file =
		    strdup(src->srv_conf.tls_ocsp_staple_file)) == NULL)
			fatal("out of memory");
	}

	if (src->srv_conf.return_uri != NULL &&
	    (dst->srv_conf.return_uri =
	    strdup(src->srv_conf.return_uri)) == NULL)
		fatal("out of memory");

	dst->srv_conf.id = ++last_server_id;
	dst->srv_conf.parent_id = dst->srv_conf.id;
	dst->srv_s = -1;

	if (last_server_id == INT_MAX) {
		yyerror("too many servers defined");
		serverconfig_free(&dst->srv_conf);
		free(dst);
		return (NULL);
	}

	/* Now set alias and listen address */
	strlcpy(dst->srv_conf.name, alias->name, sizeof(dst->srv_conf.name));
	memcpy(&dst->srv_conf.ss, &addr->ss, sizeof(dst->srv_conf.ss));
	dst->srv_conf.port = addr->port;
	dst->srv_conf.prefixlen = addr->prefixlen;
	if (addr->flags & SRVFLAG_TLS)
		dst->srv_conf.flags |= SRVFLAG_TLS;
	else
		dst->srv_conf.flags &= ~SRVFLAG_TLS;

	/* Don't inherit the "match" option, use it from the alias */
	dst->srv_conf.flags &= ~SRVFLAG_SERVER_MATCH;
	dst->srv_conf.flags |= (alias->flags & SRVFLAG_SERVER_MATCH);

	if (server_tls_load_keypair(dst) == -1)
		log_warnx("%s:%d: server \"%s\": failed to "
		    "load public/private keys", file->name,
		    yylval.lineno, dst->srv_conf.name);

	if (server_tls_load_ca(dst) == -1) {
		yyerror("failed to load ca cert(s) for server %s",
		    dst->srv_conf.name);
		serverconfig_free(&dst->srv_conf);
		return NULL;
	}

	if (server_tls_load_crl(dst) == -1) {
		yyerror("failed to load crl(s) for server %s",
		    dst->srv_conf.name);
		serverconfig_free(&dst->srv_conf);
		free(dst);
		return NULL;
	}

	if (server_tls_load_ocsp(dst) == -1) {
		yyerror("failed to load ocsp staple "
		    "for server %s", dst->srv_conf.name);
		serverconfig_free(&dst->srv_conf);
		free(dst);
		return (NULL);
	}

	/* Check if the new server already exists */
	if (server_match(dst, 1) != NULL) {
		yyerror("server \"%s\" defined twice",
		    dst->srv_conf.name);
		serverconfig_free(&dst->srv_conf);
		free(dst);
		return (NULL);
	}

	/* Copy all the locations of the source server */
	TAILQ_FOREACH(s, conf->sc_servers, srv_entry) {
		if (!(s->srv_conf.flags & SRVFLAG_LOCATION &&
		    s->srv_conf.parent_id == src->srv_conf.parent_id))
			continue;

		if ((dstl = calloc(1, sizeof(*dstl))) == NULL)
			fatal("out of memory");

		memcpy(&dstl->srv_conf, &s->srv_conf, sizeof(dstl->srv_conf));
		strlcpy(dstl->srv_conf.name, alias->name,
		    sizeof(dstl->srv_conf.name));

		/* Copy the new Id and listen address */
		dstl->srv_conf.id = ++last_server_id;
		dstl->srv_conf.parent_id = dst->srv_conf.id;
		memcpy(&dstl->srv_conf.ss, &addr->ss,
		    sizeof(dstl->srv_conf.ss));
		dstl->srv_conf.port = addr->port;
		dstl->srv_conf.prefixlen = addr->prefixlen;
		dstl->srv_s = -1;

		DPRINTF("adding location \"%s\" for \"%s[%u]\"",
		    dstl->srv_conf.location,
		    dstl->srv_conf.name, dstl->srv_conf.id);

		TAILQ_INSERT_TAIL(conf->sc_servers, dstl, srv_entry);
	}

	return (dst);
}

int
listen_on(const char *addr, int tls, struct portrange *port)
{
	struct addresslist	 al;
	struct address		*h;
	struct server_config	*s_conf, *alias = NULL;

	if (parentsrv != NULL) {
		yyerror("listen %s inside location", addr);
		return (-1);
	}

	TAILQ_INIT(&al);
	if (strcmp("*", addr) == 0) {
		if (host("0.0.0.0", &al, 1, port, NULL, -1) <= 0) {
			yyerror("invalid listen ip: %s",
			    "0.0.0.0");
			return (-1);
		}
		if (host("::", &al, 1, port, NULL, -1) <= 0) {
			yyerror("invalid listen ip: %s", "::");
			return (-1);
		}
	} else {
		if (host(addr, &al, HTTPD_MAX_ALIAS_IP, port, NULL,
		    -1) <= 0) {
			yyerror("invalid listen ip: %s", addr);
			return (-1);
		}
	}

	while ((h = TAILQ_FIRST(&al)) != NULL) {
		if (srv->srv_conf.ss.ss_family != AF_UNSPEC) {
			if ((alias = calloc(1,
			    sizeof(*alias))) == NULL)
				fatal("out of memory");
				/* Add as an IP-based alias. */
			s_conf = alias;
		} else
			s_conf = &srv->srv_conf;
		memcpy(&s_conf->ss, &h->ss, sizeof(s_conf->ss));
		s_conf->prefixlen = h->prefixlen;
		/* Set the default port to 80 or 443 */
		if (!h->port.op)
			s_conf->port = htons(tls ?
			    HTTPS_PORT : HTTP_PORT);
		else
			s_conf->port = h->port.val[0];

		if (tls)
			s_conf->flags |= SRVFLAG_TLS;

		if (alias != NULL) {
			/*
			 * IP-based; use name match flags from
			 * parent
			 */
			alias->flags &= ~SRVFLAG_SERVER_MATCH;
			alias->flags |= srv->srv_conf.flags &
			    SRVFLAG_SERVER_MATCH;
			TAILQ_INSERT_TAIL(&srv->srv_hosts,
			    alias, entry);
		}
		TAILQ_REMOVE(&al, h, entry);
		free(h);
	}

	return (0);
}

int
getservice(char *n)
{
	struct servent	*s;
	const char	*errstr;
	long long	 llval;

	llval = strtonum(n, 0, UINT16_MAX, &errstr);
	if (errstr) {
		s = getservbyname(n, "tcp");
		if (s == NULL)
			s = getservbyname(n, "udp");
		if (s == NULL)
			return (-1);
		return (s->s_port);
	}

	return (htons((unsigned short)llval));
}

int
is_if_in_group(const char *ifname, const char *groupname)
{
	unsigned int		 len;
	struct ifgroupreq	 ifgr;
	struct ifg_req		*ifg;
	int			 s;
	int			 ret = 0;

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		err(1, "socket");

	memset(&ifgr, 0, sizeof(ifgr));
	if (strlcpy(ifgr.ifgr_name, ifname, IFNAMSIZ) >= IFNAMSIZ)
		err(1, "IFNAMSIZ");
	if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1) {
		if (errno == EINVAL || errno == ENOTTY)
			goto end;
		err(1, "SIOCGIFGROUP");
	}

	len = ifgr.ifgr_len;
	ifgr.ifgr_groups = calloc(len / sizeof(struct ifg_req),
	    sizeof(struct ifg_req));
	if (ifgr.ifgr_groups == NULL)
		err(1, "getifgroups");
	if (ioctl(s, SIOCGIFGROUP, (caddr_t)&ifgr) == -1)
		err(1, "SIOCGIFGROUP");

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
	return (ret);
}

int
get_fastcgi_dest(struct server_config *xsrv_conf, const char *node, char *port)
{
	struct addrinfo		 hints, *res;
	int			 s;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((s = getaddrinfo(node, port, &hints, &res)) != 0) {
		yyerror("getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	memset(&(xsrv_conf)->fastcgi_ss, 0, sizeof(xsrv_conf->fastcgi_ss));
	memcpy(&(xsrv_conf)->fastcgi_ss, res->ai_addr, res->ai_addrlen);

	freeaddrinfo(res);

	return (0);
}

void
remove_locations(struct server_config *xsrv_conf)
{
	struct server *s, *next;

	TAILQ_FOREACH_SAFE(s, conf->sc_servers, srv_entry, next) {
		if (!(s->srv_conf.flags & SRVFLAG_LOCATION &&
		    s->srv_conf.parent_id == xsrv_conf->parent_id))
			continue;
		TAILQ_REMOVE(conf->sc_servers, s, srv_entry);
		serverconfig_free(&s->srv_conf);
		free(s);
	}
}
