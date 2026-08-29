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
#line 23 "parse.y"

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/queue.h>
#include <sys/stat.h>

#include <net/if.h>
#include <net/if_media.h>
#include <net/if_arp.h>
#include <net/if_llc.h>
#include <net/bpf.h>

#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>

#include <net80211/ieee80211.h>
#include <net80211/ieee80211_radiotap.h>

#include <ctype.h>
#include <errno.h>
#include <event.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <err.h>

#include "hostapd.h"

TAILQ_HEAD(files, file)		 files = TAILQ_HEAD_INITIALIZER(files);
static struct file {
	TAILQ_ENTRY(file)	 entry;
	FILE			*stream;
	char			*name;
	size_t	 		 ungetpos;
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

extern struct hostapd_config hostapd_cfg;

typedef struct {
	union {
		struct {
			u_int8_t		lladdr[IEEE80211_ADDR_LEN];
			struct hostapd_table	*table;
			u_int32_t		flags;
		} reflladdr;
		struct {
			u_int16_t		alg;
			u_int16_t		transaction;
		} authalg;
		struct in_addr		in;
		char			*string;
		int64_t			number;
		u_int16_t		reason;
		enum hostapd_op		op;
		struct timeval		timeout;
	} v;
	int lineno;
} YYSTYPE;

struct hostapd_apme *apme;
struct hostapd_table *table;
struct hostapd_entry *entry;
struct hostapd_frame frame, *frame_ptr;
struct hostapd_ieee80211_frame *frame_ieee80211;

#define HOSTAPD_MATCH(_m, _not)	{					\
	frame.f_flags |= (_not) ?					\
	    HOSTAPD_FRAME_F_##_m##_N : HOSTAPD_FRAME_F_##_m;		\
}
#define HOSTAPD_MATCH_TABLE(_m, _not)	{				\
	frame.f_flags |= HOSTAPD_FRAME_F_##_m##_TABLE | ((_not) ?	\
	    HOSTAPD_FRAME_F_##_m##_N : HOSTAPD_FRAME_F_##_m);		\
}
#define HOSTAPD_MATCH_RADIOTAP(_x) {					\
	if (hostapd_cfg.c_apme_dlt == DLT_IEEE802_11 ||			\
	    (hostapd_cfg.c_apme_dlt == 0 &&				\
	    HOSTAPD_DLT == DLT_IEEE802_11)) {				\
		yyerror("option %s requires radiotap headers", #_x);	\
		YYERROR;						\
	}								\
	frame.f_radiotap |= HOSTAPD_RADIOTAP_F(RSSI);			\
	frame.f_flags |= HOSTAPD_FRAME_F_##_x;				\
}
#define HOSTAPD_IAPP_FLAG(_f, _not) {					\
	if (_not)							\
		hostapd_cfg.c_iapp.i_flags &= ~(HOSTAPD_IAPP_F_##_f);	\
	else								\
		hostapd_cfg.c_iapp.i_flags |= (HOSTAPD_IAPP_F_##_f);	\
}


#line 201 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    MODE = 258,                    /* MODE  */
    INTERFACE = 259,               /* INTERFACE  */
    IAPP = 260,                    /* IAPP  */
    HOSTAP = 261,                  /* HOSTAP  */
    MULTICAST = 262,               /* MULTICAST  */
    BROADCAST = 263,               /* BROADCAST  */
    SET = 264,                     /* SET  */
    SEC = 265,                     /* SEC  */
    USEC = 266,                    /* USEC  */
    HANDLE = 267,                  /* HANDLE  */
    TYPE = 268,                    /* TYPE  */
    SUBTYPE = 269,                 /* SUBTYPE  */
    FROM = 270,                    /* FROM  */
    TO = 271,                      /* TO  */
    BSSID = 272,                   /* BSSID  */
    WITH = 273,                    /* WITH  */
    FRAME = 274,                   /* FRAME  */
    RADIOTAP = 275,                /* RADIOTAP  */
    NWID = 276,                    /* NWID  */
    PASSIVE = 277,                 /* PASSIVE  */
    MANAGEMENT = 278,              /* MANAGEMENT  */
    DATA = 279,                    /* DATA  */
    PROBE = 280,                   /* PROBE  */
    BEACON = 281,                  /* BEACON  */
    ATIM = 282,                    /* ATIM  */
    ANY = 283,                     /* ANY  */
    DS = 284,                      /* DS  */
    NO = 285,                      /* NO  */
    DIR = 286,                     /* DIR  */
    RESEND = 287,                  /* RESEND  */
    RANDOM = 288,                  /* RANDOM  */
    AUTH = 289,                    /* AUTH  */
    DEAUTH = 290,                  /* DEAUTH  */
    ASSOC = 291,                   /* ASSOC  */
    DISASSOC = 292,                /* DISASSOC  */
    REASSOC = 293,                 /* REASSOC  */
    REQUEST = 294,                 /* REQUEST  */
    RESPONSE = 295,                /* RESPONSE  */
    PCAP = 296,                    /* PCAP  */
    RATE = 297,                    /* RATE  */
    ERROR = 298,                   /* ERROR  */
    CONST = 299,                   /* CONST  */
    TABLE = 300,                   /* TABLE  */
    NODE = 301,                    /* NODE  */
    DELETE = 302,                  /* DELETE  */
    ADD = 303,                     /* ADD  */
    LOG = 304,                     /* LOG  */
    VERBOSE = 305,                 /* VERBOSE  */
    LIMIT = 306,                   /* LIMIT  */
    QUICK = 307,                   /* QUICK  */
    SKIP = 308,                    /* SKIP  */
    REASON = 309,                  /* REASON  */
    UNSPECIFIED = 310,             /* UNSPECIFIED  */
    EXPIRE = 311,                  /* EXPIRE  */
    LEAVE = 312,                   /* LEAVE  */
    TOOMANY = 313,                 /* TOOMANY  */
    NOT = 314,                     /* NOT  */
    AUTHED = 315,                  /* AUTHED  */
    ASSOCED = 316,                 /* ASSOCED  */
    RESERVED = 317,                /* RESERVED  */
    RSN = 318,                     /* RSN  */
    REQUIRED = 319,                /* REQUIRED  */
    INCONSISTENT = 320,            /* INCONSISTENT  */
    IE = 321,                      /* IE  */
    INVALID = 322,                 /* INVALID  */
    MIC = 323,                     /* MIC  */
    FAILURE = 324,                 /* FAILURE  */
    OPEN = 325,                    /* OPEN  */
    ADDRESS = 326,                 /* ADDRESS  */
    PORT = 327,                    /* PORT  */
    ON = 328,                      /* ON  */
    NOTIFY = 329,                  /* NOTIFY  */
    TTL = 330,                     /* TTL  */
    INCLUDE = 331,                 /* INCLUDE  */
    ROUTE = 332,                   /* ROUTE  */
    ROAMING = 333,                 /* ROAMING  */
    RSSI = 334,                    /* RSSI  */
    TXRATE = 335,                  /* TXRATE  */
    FREQ = 336,                    /* FREQ  */
    HOPPER = 337,                  /* HOPPER  */
    DELAY = 338,                   /* DELAY  */
    NE = 339,                      /* NE  */
    LE = 340,                      /* LE  */
    GE = 341,                      /* GE  */
    ARROW = 342,                   /* ARROW  */
    STRING = 343,                  /* STRING  */
    NUMBER = 344                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define MODE 258
#define INTERFACE 259
#define IAPP 260
#define HOSTAP 261
#define MULTICAST 262
#define BROADCAST 263
#define SET 264
#define SEC 265
#define USEC 266
#define HANDLE 267
#define TYPE 268
#define SUBTYPE 269
#define FROM 270
#define TO 271
#define BSSID 272
#define WITH 273
#define FRAME 274
#define RADIOTAP 275
#define NWID 276
#define PASSIVE 277
#define MANAGEMENT 278
#define DATA 279
#define PROBE 280
#define BEACON 281
#define ATIM 282
#define ANY 283
#define DS 284
#define NO 285
#define DIR 286
#define RESEND 287
#define RANDOM 288
#define AUTH 289
#define DEAUTH 290
#define ASSOC 291
#define DISASSOC 292
#define REASSOC 293
#define REQUEST 294
#define RESPONSE 295
#define PCAP 296
#define RATE 297
#define ERROR 298
#define CONST 299
#define TABLE 300
#define NODE 301
#define DELETE 302
#define ADD 303
#define LOG 304
#define VERBOSE 305
#define LIMIT 306
#define QUICK 307
#define SKIP 308
#define REASON 309
#define UNSPECIFIED 310
#define EXPIRE 311
#define LEAVE 312
#define TOOMANY 313
#define NOT 314
#define AUTHED 315
#define ASSOCED 316
#define RESERVED 317
#define RSN 318
#define REQUIRED 319
#define INCONSISTENT 320
#define IE 321
#define INVALID 322
#define MIC 323
#define FAILURE 324
#define OPEN 325
#define ADDRESS 326
#define PORT 327
#define ON 328
#define NOTIFY 329
#define TTL 330
#define INCLUDE 331
#define ROUTE 332
#define ROAMING 333
#define RSSI 334
#define TXRATE 335
#define FREQ 336
#define HOPPER 337
#define DELAY 338
#define NE 339
#define LE 340
#define GE 341
#define ARROW 342
#define STRING 343
#define NUMBER 344

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MODE = 3,                       /* MODE  */
  YYSYMBOL_INTERFACE = 4,                  /* INTERFACE  */
  YYSYMBOL_IAPP = 5,                       /* IAPP  */
  YYSYMBOL_HOSTAP = 6,                     /* HOSTAP  */
  YYSYMBOL_MULTICAST = 7,                  /* MULTICAST  */
  YYSYMBOL_BROADCAST = 8,                  /* BROADCAST  */
  YYSYMBOL_SET = 9,                        /* SET  */
  YYSYMBOL_SEC = 10,                       /* SEC  */
  YYSYMBOL_USEC = 11,                      /* USEC  */
  YYSYMBOL_HANDLE = 12,                    /* HANDLE  */
  YYSYMBOL_TYPE = 13,                      /* TYPE  */
  YYSYMBOL_SUBTYPE = 14,                   /* SUBTYPE  */
  YYSYMBOL_FROM = 15,                      /* FROM  */
  YYSYMBOL_TO = 16,                        /* TO  */
  YYSYMBOL_BSSID = 17,                     /* BSSID  */
  YYSYMBOL_WITH = 18,                      /* WITH  */
  YYSYMBOL_FRAME = 19,                     /* FRAME  */
  YYSYMBOL_RADIOTAP = 20,                  /* RADIOTAP  */
  YYSYMBOL_NWID = 21,                      /* NWID  */
  YYSYMBOL_PASSIVE = 22,                   /* PASSIVE  */
  YYSYMBOL_MANAGEMENT = 23,                /* MANAGEMENT  */
  YYSYMBOL_DATA = 24,                      /* DATA  */
  YYSYMBOL_PROBE = 25,                     /* PROBE  */
  YYSYMBOL_BEACON = 26,                    /* BEACON  */
  YYSYMBOL_ATIM = 27,                      /* ATIM  */
  YYSYMBOL_ANY = 28,                       /* ANY  */
  YYSYMBOL_DS = 29,                        /* DS  */
  YYSYMBOL_NO = 30,                        /* NO  */
  YYSYMBOL_DIR = 31,                       /* DIR  */
  YYSYMBOL_RESEND = 32,                    /* RESEND  */
  YYSYMBOL_RANDOM = 33,                    /* RANDOM  */
  YYSYMBOL_AUTH = 34,                      /* AUTH  */
  YYSYMBOL_DEAUTH = 35,                    /* DEAUTH  */
  YYSYMBOL_ASSOC = 36,                     /* ASSOC  */
  YYSYMBOL_DISASSOC = 37,                  /* DISASSOC  */
  YYSYMBOL_REASSOC = 38,                   /* REASSOC  */
  YYSYMBOL_REQUEST = 39,                   /* REQUEST  */
  YYSYMBOL_RESPONSE = 40,                  /* RESPONSE  */
  YYSYMBOL_PCAP = 41,                      /* PCAP  */
  YYSYMBOL_RATE = 42,                      /* RATE  */
  YYSYMBOL_ERROR = 43,                     /* ERROR  */
  YYSYMBOL_CONST = 44,                     /* CONST  */
  YYSYMBOL_TABLE = 45,                     /* TABLE  */
  YYSYMBOL_NODE = 46,                      /* NODE  */
  YYSYMBOL_DELETE = 47,                    /* DELETE  */
  YYSYMBOL_ADD = 48,                       /* ADD  */
  YYSYMBOL_LOG = 49,                       /* LOG  */
  YYSYMBOL_VERBOSE = 50,                   /* VERBOSE  */
  YYSYMBOL_LIMIT = 51,                     /* LIMIT  */
  YYSYMBOL_QUICK = 52,                     /* QUICK  */
  YYSYMBOL_SKIP = 53,                      /* SKIP  */
  YYSYMBOL_REASON = 54,                    /* REASON  */
  YYSYMBOL_UNSPECIFIED = 55,               /* UNSPECIFIED  */
  YYSYMBOL_EXPIRE = 56,                    /* EXPIRE  */
  YYSYMBOL_LEAVE = 57,                     /* LEAVE  */
  YYSYMBOL_TOOMANY = 58,                   /* TOOMANY  */
  YYSYMBOL_NOT = 59,                       /* NOT  */
  YYSYMBOL_AUTHED = 60,                    /* AUTHED  */
  YYSYMBOL_ASSOCED = 61,                   /* ASSOCED  */
  YYSYMBOL_RESERVED = 62,                  /* RESERVED  */
  YYSYMBOL_RSN = 63,                       /* RSN  */
  YYSYMBOL_REQUIRED = 64,                  /* REQUIRED  */
  YYSYMBOL_INCONSISTENT = 65,              /* INCONSISTENT  */
  YYSYMBOL_IE = 66,                        /* IE  */
  YYSYMBOL_INVALID = 67,                   /* INVALID  */
  YYSYMBOL_MIC = 68,                       /* MIC  */
  YYSYMBOL_FAILURE = 69,                   /* FAILURE  */
  YYSYMBOL_OPEN = 70,                      /* OPEN  */
  YYSYMBOL_ADDRESS = 71,                   /* ADDRESS  */
  YYSYMBOL_PORT = 72,                      /* PORT  */
  YYSYMBOL_ON = 73,                        /* ON  */
  YYSYMBOL_NOTIFY = 74,                    /* NOTIFY  */
  YYSYMBOL_TTL = 75,                       /* TTL  */
  YYSYMBOL_INCLUDE = 76,                   /* INCLUDE  */
  YYSYMBOL_ROUTE = 77,                     /* ROUTE  */
  YYSYMBOL_ROAMING = 78,                   /* ROAMING  */
  YYSYMBOL_RSSI = 79,                      /* RSSI  */
  YYSYMBOL_TXRATE = 80,                    /* TXRATE  */
  YYSYMBOL_FREQ = 81,                      /* FREQ  */
  YYSYMBOL_HOPPER = 82,                    /* HOPPER  */
  YYSYMBOL_DELAY = 83,                     /* DELAY  */
  YYSYMBOL_NE = 84,                        /* NE  */
  YYSYMBOL_LE = 85,                        /* LE  */
  YYSYMBOL_GE = 86,                        /* GE  */
  YYSYMBOL_ARROW = 87,                     /* ARROW  */
  YYSYMBOL_STRING = 88,                    /* STRING  */
  YYSYMBOL_NUMBER = 89,                    /* NUMBER  */
  YYSYMBOL_90_n_ = 90,                     /* '\n'  */
  YYSYMBOL_91_ = 91,                       /* '{'  */
  YYSYMBOL_92_ = 92,                       /* '}'  */
  YYSYMBOL_93_ = 93,                       /* '/'  */
  YYSYMBOL_94_ = 94,                       /* '<'  */
  YYSYMBOL_95_ = 95,                       /* '>'  */
  YYSYMBOL_96_ = 96,                       /* '='  */
  YYSYMBOL_97_ = 97,                       /* '&'  */
  YYSYMBOL_98_ = 98,                       /* ','  */
  YYSYMBOL_99_ = 99,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 100,                 /* $accept  */
  YYSYMBOL_grammar = 101,                  /* grammar  */
  YYSYMBOL_include = 102,                  /* include  */
  YYSYMBOL_option = 103,                   /* option  */
  YYSYMBOL_iappmode = 104,                 /* iappmode  */
  YYSYMBOL_iappmodeaddr = 105,             /* iappmodeaddr  */
  YYSYMBOL_iappmodeport = 106,             /* iappmodeport  */
  YYSYMBOL_iappmodettl = 107,              /* iappmodettl  */
  YYSYMBOL_hostapmode = 108,               /* hostapmode  */
  YYSYMBOL_hostapifaces = 109,             /* hostapifaces  */
  YYSYMBOL_hostapifacelist = 110,          /* hostapifacelist  */
  YYSYMBOL_hostapiface = 111,              /* hostapiface  */
  YYSYMBOL_hopperifaces = 112,             /* hopperifaces  */
  YYSYMBOL_hopperifacelist = 113,          /* hopperifacelist  */
  YYSYMBOL_hopperiface = 114,              /* hopperiface  */
  YYSYMBOL_hostapmatch = 115,              /* hostapmatch  */
  YYSYMBOL_event = 116,                    /* event  */
  YYSYMBOL_117_1 = 117,                    /* $@1  */
  YYSYMBOL_118_2 = 118,                    /* $@2  */
  YYSYMBOL_iappsubtypes = 119,             /* iappsubtypes  */
  YYSYMBOL_iappsubtypelist = 120,          /* iappsubtypelist  */
  YYSYMBOL_iappsubtype = 121,              /* iappsubtype  */
  YYSYMBOL_eventopt = 122,                 /* eventopt  */
  YYSYMBOL_action = 123,                   /* action  */
  YYSYMBOL_verbose = 124,                  /* verbose  */
  YYSYMBOL_iapp = 125,                     /* iapp  */
  YYSYMBOL_nodeopt = 126,                  /* nodeopt  */
  YYSYMBOL_frmmatch = 127,                 /* frmmatch  */
  YYSYMBOL_frm = 128,                      /* frm  */
  YYSYMBOL_frmaction = 129,                /* frmaction  */
  YYSYMBOL_limit = 130,                    /* limit  */
  YYSYMBOL_rate = 131,                     /* rate  */
  YYSYMBOL_frmmatchtype = 132,             /* frmmatchtype  */
  YYSYMBOL_frmmatchmgmt = 133,             /* frmmatchmgmt  */
  YYSYMBOL_frmsubtype = 134,               /* frmsubtype  */
  YYSYMBOL_frmelems = 135,                 /* frmelems  */
  YYSYMBOL_frmelems_l = 136,               /* frmelems_l  */
  YYSYMBOL_frmelem = 137,                  /* frmelem  */
  YYSYMBOL_frmauth = 138,                  /* frmauth  */
  YYSYMBOL_authalg = 139,                  /* authalg  */
  YYSYMBOL_frmreason = 140,                /* frmreason  */
  YYSYMBOL_frmreason_l = 141,              /* frmreason_l  */
  YYSYMBOL_frmmatchdir = 142,              /* frmmatchdir  */
  YYSYMBOL_frmdir = 143,                   /* frmdir  */
  YYSYMBOL_frmmatchfrom = 144,             /* frmmatchfrom  */
  YYSYMBOL_frmmatchto = 145,               /* frmmatchto  */
  YYSYMBOL_frmmatchbssid = 146,            /* frmmatchbssid  */
  YYSYMBOL_frmmatchrtap = 147,             /* frmmatchrtap  */
  YYSYMBOL_frmmatchrtap_l = 148,           /* frmmatchrtap_l  */
  YYSYMBOL_frmmatchrtapopt = 149,          /* frmmatchrtapopt  */
  YYSYMBOL_frmmatchaddr = 150,             /* frmmatchaddr  */
  YYSYMBOL_frmactiontype = 151,            /* frmactiontype  */
  YYSYMBOL_frmactionmgmt = 152,            /* frmactionmgmt  */
  YYSYMBOL_frmactiondir = 153,             /* frmactiondir  */
  YYSYMBOL_frmactionfrom = 154,            /* frmactionfrom  */
  YYSYMBOL_frmactionto = 155,              /* frmactionto  */
  YYSYMBOL_frmactionbssid = 156,           /* frmactionbssid  */
  YYSYMBOL_frmactionaddr = 157,            /* frmactionaddr  */
  YYSYMBOL_table = 158,                    /* table  */
  YYSYMBOL_tabledef = 159,                 /* tabledef  */
  YYSYMBOL_160_3 = 160,                    /* $@3  */
  YYSYMBOL_tableopts = 161,                /* tableopts  */
  YYSYMBOL_tableopts_l = 162,              /* tableopts_l  */
  YYSYMBOL_tableopt = 163,                 /* tableopt  */
  YYSYMBOL_string = 164,                   /* string  */
  YYSYMBOL_varset = 165,                   /* varset  */
  YYSYMBOL_refaddr = 166,                  /* refaddr  */
  YYSYMBOL_tableaddrlist = 167,            /* tableaddrlist  */
  YYSYMBOL_tableaddrentry = 168,           /* tableaddrentry  */
  YYSYMBOL_169_4 = 169,                    /* $@4  */
  YYSYMBOL_tableaddropt = 170,             /* tableaddropt  */
  YYSYMBOL_ipv4addr = 171,                 /* ipv4addr  */
  YYSYMBOL_ipv4netmask = 172,              /* ipv4netmask  */
  YYSYMBOL_lladdr = 173,                   /* lladdr  */
  YYSYMBOL_randaddr = 174,                 /* randaddr  */
  YYSYMBOL_passive = 175,                  /* passive  */
  YYSYMBOL_assign = 176,                   /* assign  */
  YYSYMBOL_mask = 177,                     /* mask  */
  YYSYMBOL_comma = 178,                    /* comma  */
  YYSYMBOL_optnl = 179,                    /* optnl  */
  YYSYMBOL_not = 180,                      /* not  */
  YYSYMBOL_unaryop = 181,                  /* unaryop  */
  YYSYMBOL_percent = 182,                  /* percent  */
  YYSYMBOL_txrate = 183,                   /* txrate  */
  YYSYMBOL_freq = 184,                     /* freq  */
  YYSYMBOL_timeout = 185                   /* timeout  */
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
#define YYLAST   288

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  206
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  332

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   344


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
      90,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    99,     2,     2,     2,     2,    97,     2,
       2,     2,     2,     2,    98,     2,     2,    93,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      94,    96,    95,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,     2,    92,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   183,   183,   184,   185,   186,   187,   188,   189,   190,
     193,   208,   213,   214,   219,   220,   237,   238,   248,   258,
     261,   265,   271,   272,   279,   280,   290,   291,   301,   305,
     311,   312,   315,   316,   319,   329,   330,   333,   334,   337,
     349,   350,   365,   369,   364,   389,   390,   393,   394,   397,
     401,   405,   409,   416,   419,   423,   430,   433,   437,   441,
     442,   450,   456,   457,   463,   469,   473,   479,   480,   484,
     485,   488,   491,   492,   500,   511,   512,   531,   532,   533,
     539,   547,   548,   549,   555,   560,   565,   570,   575,   580,
     585,   590,   595,   600,   605,   612,   613,   616,   617,   620,
     623,   624,   639,   644,   651,   668,   671,   675,   679,   683,
     687,   691,   695,   699,   703,   707,   711,   715,   719,   723,
     729,   730,   731,   737,   741,   745,   749,   755,   756,   757,
     770,   771,   772,   785,   786,   787,   800,   801,   804,   805,
     808,   822,   828,   836,   847,   854,   858,   864,   868,   872,
     875,   886,   897,   908,   913,   917,   923,   934,   934,   947,
     948,   951,   952,   955,   962,   963,   966,   973,   976,   995,
     999,  1003,  1009,  1010,  1014,  1013,  1026,  1027,  1034,  1044,
    1056,  1059,  1069,  1085,  1091,  1092,  1098,  1101,  1104,  1105,
    1108,  1109,  1113,  1116,  1120,  1127,  1130,  1134,  1138,  1142,
    1146,  1150,  1154,  1160,  1177,  1194,  1217
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
  "\"end of file\"", "error", "\"invalid token\"", "MODE", "INTERFACE",
  "IAPP", "HOSTAP", "MULTICAST", "BROADCAST", "SET", "SEC", "USEC",
  "HANDLE", "TYPE", "SUBTYPE", "FROM", "TO", "BSSID", "WITH", "FRAME",
  "RADIOTAP", "NWID", "PASSIVE", "MANAGEMENT", "DATA", "PROBE", "BEACON",
  "ATIM", "ANY", "DS", "NO", "DIR", "RESEND", "RANDOM", "AUTH", "DEAUTH",
  "ASSOC", "DISASSOC", "REASSOC", "REQUEST", "RESPONSE", "PCAP", "RATE",
  "ERROR", "CONST", "TABLE", "NODE", "DELETE", "ADD", "LOG", "VERBOSE",
  "LIMIT", "QUICK", "SKIP", "REASON", "UNSPECIFIED", "EXPIRE", "LEAVE",
  "TOOMANY", "NOT", "AUTHED", "ASSOCED", "RESERVED", "RSN", "REQUIRED",
  "INCONSISTENT", "IE", "INVALID", "MIC", "FAILURE", "OPEN", "ADDRESS",
  "PORT", "ON", "NOTIFY", "TTL", "INCLUDE", "ROUTE", "ROAMING", "RSSI",
  "TXRATE", "FREQ", "HOPPER", "DELAY", "NE", "LE", "GE", "ARROW", "STRING",
  "NUMBER", "'\\n'", "'{'", "'}'", "'/'", "'<'", "'>'", "'='", "'&'",
  "','", "'!'", "$accept", "grammar", "include", "option", "iappmode",
  "iappmodeaddr", "iappmodeport", "iappmodettl", "hostapmode",
  "hostapifaces", "hostapifacelist", "hostapiface", "hopperifaces",
  "hopperifacelist", "hopperiface", "hostapmatch", "event", "$@1", "$@2",
  "iappsubtypes", "iappsubtypelist", "iappsubtype", "eventopt", "action",
  "verbose", "iapp", "nodeopt", "frmmatch", "frm", "frmaction", "limit",
  "rate", "frmmatchtype", "frmmatchmgmt", "frmsubtype", "frmelems",
  "frmelems_l", "frmelem", "frmauth", "authalg", "frmreason",
  "frmreason_l", "frmmatchdir", "frmdir", "frmmatchfrom", "frmmatchto",
  "frmmatchbssid", "frmmatchrtap", "frmmatchrtap_l", "frmmatchrtapopt",
  "frmmatchaddr", "frmactiontype", "frmactionmgmt", "frmactiondir",
  "frmactionfrom", "frmactionto", "frmactionbssid", "frmactionaddr",
  "table", "tabledef", "$@3", "tableopts", "tableopts_l", "tableopt",
  "string", "varset", "refaddr", "tableaddrlist", "tableaddrentry", "$@4",
  "tableaddropt", "ipv4addr", "ipv4netmask", "lladdr", "randaddr",
  "passive", "assign", "mask", "comma", "optnl", "not", "unaryop",
  "percent", "txrate", "freq", "timeout", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-225)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-191)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -225,     2,  -225,   -49,    21,    25,   -36,   -43,   -25,  -225,
     -11,    13,    18,    27,    35,  -225,  -225,    14,     1,    10,
    -225,  -225,    46,  -225,  -225,  -225,  -225,  -225,    86,   135,
      57,   101,    74,    83,    22,   -16,     3,    79,   -30,  -225,
      89,  -225,  -225,   110,   125,   129,  -225,   178,   -40,   157,
     158,  -225,  -225,  -225,  -225,   114,  -225,  -225,    44,   116,
    -225,  -225,   114,  -225,   -30,  -225,  -225,   -31,     8,   118,
     129,   119,  -225,  -225,  -225,  -225,   114,  -225,  -225,  -225,
      29,   -36,   -36,  -225,   121,  -225,   114,  -225,  -225,  -225,
    -225,   -54,  -225,   122,  -225,  -225,  -225,   194,  -225,  -225,
     137,  -225,   -31,  -225,   139,   138,   140,  -225,  -225,    28,
    -225,   123,  -225,  -225,    28,  -225,  -225,  -225,   196,   -19,
     184,   131,  -225,    28,  -225,  -225,  -225,  -225,   114,   121,
     134,    28,  -225,   141,   142,   -58,    16,   166,  -225,   127,
     -15,   204,  -225,   -31,   146,  -225,  -225,  -225,   123,   149,
    -225,  -225,  -225,  -225,  -225,   118,   141,   208,   209,  -225,
     109,   173,   150,   182,   211,  -225,  -225,    94,    -6,   212,
    -225,  -225,  -225,  -225,   151,  -225,   207,  -225,   143,  -225,
     199,  -225,  -225,   -21,  -225,  -225,   148,   153,  -225,    -5,
    -225,   202,   203,   217,   206,  -225,  -225,    11,    -4,   219,
     154,  -225,   173,   223,  -225,    94,   225,  -225,    72,  -225,
    -225,  -225,  -225,  -225,  -225,   152,  -225,   144,  -225,  -225,
     218,  -225,  -225,  -225,  -225,  -225,    11,    -3,    68,  -225,
    -225,   144,  -225,  -225,   -21,   230,  -225,  -225,  -225,   159,
     133,   228,  -225,   180,   197,   136,   197,   145,  -225,  -225,
    -225,  -225,    11,    69,    69,    69,  -225,    68,  -225,  -225,
    -225,   -21,   235,   243,   228,   228,   -31,  -225,   228,  -225,
     147,  -225,  -225,    78,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,   167,
     168,   169,  -225,  -225,   -21,  -225,  -225,  -225,  -225,   170,
    -225,  -225,  -225,   132,    71,  -225,   130,  -225,   128,   187,
     190,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,   200,  -225,  -225,  -225,  -225,  -225,
    -225,  -225
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     9,    42,     0,     0,     0,
     157,    10,     0,     4,     6,     7,     5,     8,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   159,   167,
     168,    54,    55,    40,    22,    24,    16,   184,   192,     0,
       0,    28,    29,    14,    34,   190,    11,    31,     0,     0,
     156,   163,   190,   158,   160,   162,   166,   192,    69,     0,
      24,     0,    21,   185,    15,   194,   190,   193,    19,    46,
       0,     0,     0,   191,     0,    39,   190,    12,    36,   206,
      13,     0,   161,     0,    70,    67,    43,    77,   179,    23,
      26,    25,   192,    50,     0,     0,     0,    17,    18,   188,
      32,     0,   182,   164,   188,   172,   174,    41,    56,   192,
     120,     0,    20,   188,    47,    49,    52,    51,   190,     0,
       0,   188,    37,     0,     0,   176,     0,    72,    78,     0,
     192,   127,    27,   192,     0,   189,    33,    30,     0,     0,
     173,   165,   186,   187,   175,     0,     0,     0,     0,    61,
       0,    62,     0,    75,    81,    79,   121,     0,   192,   130,
      48,    45,    38,    35,   180,   178,     0,    59,     0,    58,
     148,    65,    66,     0,    63,    57,     0,     0,    44,   192,
      80,     0,     0,     0,     0,   122,   128,     0,   192,   133,
       0,   177,    62,     0,   145,     0,     0,   183,     0,    60,
     155,   153,   154,    73,    74,     0,    82,     0,   125,   124,
       0,   123,   129,   143,   144,   131,     0,   192,   136,   181,
      64,     0,   146,   149,     0,     0,   169,   170,   171,     0,
       0,    95,    87,   100,   105,     0,   105,     0,    83,   126,
     132,   134,     0,   195,   195,   195,    68,   137,   139,   147,
     150,     0,     0,     0,    95,    95,   192,    86,    96,    98,
       0,    88,   101,     0,    89,   104,    90,    92,    91,    93,
      94,   135,   198,   199,   201,   200,   202,   196,   197,     0,
       0,     0,   138,   151,     0,    71,    76,    84,    85,     0,
      97,   102,   103,     0,     0,   106,     0,   115,     0,     0,
       0,   203,   140,   204,   141,   205,   142,   152,    99,   107,
     108,   109,   113,   110,     0,   111,   112,   116,   117,   118,
     119,   114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,  -225,  -225,  -225,  -225,   191,  -225,  -225,  -225,
    -225,   -69,  -225,  -225,   -79,  -225,  -225,  -225,  -225,  -225,
    -225,   -86,  -225,  -225,    60,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,    32,   -70,  -225,    -2,  -225,  -225,
      19,  -225,  -225,    59,  -225,  -225,  -225,  -225,  -225,    12,
    -206,  -225,  -225,  -225,  -225,  -225,  -225,  -224,     0,  -225,
    -225,  -225,  -225,   210,  -225,  -225,  -225,  -225,   155,  -225,
    -225,   112,  -225,   -90,  -225,  -225,  -225,  -225,   -10,   -12,
     -67,   -57,  -225,  -225,  -225,  -225
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    10,    11,    46,    70,    72,   122,    53,    56,
     109,    57,    87,   131,    88,    68,    12,    28,   118,    78,
     123,    79,    43,   137,   185,   177,   183,    96,    97,   179,
     163,   188,   120,   190,   248,   267,   268,   269,   271,   272,
     274,   275,   141,   195,   169,   199,   228,   256,   257,   258,
     222,   180,   232,   206,   235,   262,   295,   209,   223,    13,
      38,    63,    64,    65,    40,    14,   210,   114,   115,   135,
     154,    99,   201,   211,   212,    74,   155,   156,   129,    84,
      80,   289,   312,   314,   316,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      93,   116,     2,     3,    34,    35,    20,    58,     4,   138,
     260,     5,   207,   166,    61,   110,   124,    29,    30,    75,
     250,   157,   196,   216,   225,   251,    31,    94,    75,   152,
      17,    18,   132,    16,   112,   158,    95,   293,   113,   153,
      75,    15,    51,   116,    75,    21,   281,     6,   159,   103,
      91,    76,   139,    75,    75,    75,    75,   170,    19,    77,
     146,    62,   160,    52,   102,   161,   175,   112,    77,   172,
     317,    22,    54,   167,   111,    55,   208,   104,     7,    23,
      77,   107,   108,    36,    77,    32,    59,   236,   237,   238,
       8,    33,     9,    77,    77,    77,    77,   130,    37,   112,
     105,   197,   134,    24,   133,    19,   106,   224,    25,   191,
     192,   144,   303,   143,   304,    48,   145,    26,    83,   149,
    -190,   148,   217,   193,   194,    27,   128,   321,   322,   323,
     324,   226,    85,   305,    39,    86,   224,   306,    41,    42,
     307,   308,    44,    45,   309,    47,   310,   253,   254,   255,
     164,   165,    49,   282,   283,   284,   181,   182,   213,   214,
     252,    50,   224,   285,   286,   287,   203,   204,   288,   240,
     241,   242,   264,   265,    60,   276,   277,    66,   243,   244,
     245,   246,   247,    67,   279,   280,   301,   302,   319,   320,
     325,   326,   327,   328,   297,   298,    69,   290,   291,   299,
      73,    71,    81,    82,    83,    89,    98,   119,   101,    54,
     117,    85,   121,   125,   136,   140,   126,   162,   127,   168,
     142,   176,   178,   184,   187,   189,   147,   202,   198,   112,
     205,   218,   219,   220,   151,   221,   227,   231,   171,   186,
     234,   173,   215,   229,   200,   239,   261,   249,   263,   266,
     270,   273,   294,   296,   329,   311,   313,   315,   318,   330,
     331,   100,   230,   259,   233,   278,   300,   174,     0,   292,
       0,     0,     0,     0,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150
};

static const yytype_int16 yycheck[] =
{
      67,    91,     0,     1,     3,     4,     6,     4,     6,    28,
     234,     9,    33,    28,    44,    84,   102,     3,     4,    59,
     226,     5,    28,    28,    28,    28,    12,    19,    59,    87,
       5,     6,   111,    12,    88,    19,    28,   261,    92,    97,
      59,    90,    20,   133,    59,    88,   252,    45,    32,    20,
      62,    91,   119,    59,    59,    59,    59,   143,    94,    99,
     129,    91,    46,    41,    76,    49,   156,    88,    99,   148,
     294,    96,    88,   140,    86,    91,    97,    48,    76,    90,
      99,    81,    82,    82,    99,    71,    83,    15,    16,    17,
      88,    77,    90,    99,    99,    99,    99,   109,    88,    88,
      71,   168,   114,    90,   114,    94,    77,   197,    90,    15,
      16,   123,    34,   123,    36,    14,   128,    90,    90,   131,
      92,   131,   189,    29,    30,    90,    98,    56,    57,    58,
      59,   198,    88,    55,    88,    91,   226,    59,    52,    53,
      62,    63,     7,     8,    66,    88,    68,    79,    80,    81,
      23,    24,    78,    84,    85,    86,    47,    48,    10,    11,
     227,    78,   252,    94,    95,    96,    23,    24,    99,    25,
      26,    27,    39,    40,    95,    39,    40,    88,    34,    35,
      36,    37,    38,    73,    39,    40,    39,    40,    56,    57,
      60,    61,    64,    65,   264,   265,    71,   254,   255,   266,
      22,    72,    45,    45,    90,    89,    88,    13,    89,    88,
      88,    88,    75,    74,    18,    31,    78,    51,    78,    15,
      89,    13,    13,    50,    42,    14,    92,    20,    16,    88,
      31,    29,    29,    16,    92,    29,    17,    14,    92,    89,
      15,    92,    89,    89,    93,    93,    16,    29,    89,    21,
      70,    54,    17,    10,    67,    88,    88,    88,    88,    69,
      60,    70,   202,   231,   205,   246,   268,   155,    -1,   257,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   133
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   101,     0,     1,     6,     9,    45,    76,    88,    90,
     102,   103,   116,   159,   165,    90,    12,     5,     6,    94,
     158,    88,    96,    90,    90,    90,    90,    90,   117,     3,
       4,    12,    71,    77,     3,     4,    82,    88,   160,    88,
     164,    52,    53,   122,     7,     8,   104,    88,    14,    78,
      78,    20,    41,   108,    88,    91,   109,   111,     4,    83,
      95,    44,    91,   161,   162,   163,    88,    73,   115,    71,
     105,    72,   106,    22,   175,    59,    91,    99,   119,   121,
     180,    45,    45,    90,   179,    88,    91,   112,   114,    89,
     185,   179,   163,   180,    19,    28,   127,   128,    88,   171,
     106,    89,   179,    20,    48,    71,    77,   158,   158,   110,
     111,   179,    88,    92,   167,   168,   173,    88,   118,    13,
     132,    75,   107,   120,   121,    74,    78,    78,    98,   178,
     179,   113,   114,   178,   179,   169,    18,   123,    28,   180,
      31,   142,    89,   178,   179,   179,   111,    92,   178,   179,
     168,    92,    87,    97,   170,   176,   177,     5,    19,    32,
      46,    49,    51,   130,    23,    24,    28,   180,    15,   144,
     121,    92,   114,    92,   171,   173,    13,   125,    13,   129,
     151,    47,    48,   126,    50,   124,    89,    42,   131,    14,
     133,    15,    16,    29,    30,   143,    28,   180,    16,   145,
      93,   172,    20,    23,    24,    31,   153,    33,    97,   157,
     166,   173,   174,    10,    11,    89,    28,   180,    29,    29,
      16,    29,   150,   158,   173,    28,   180,    17,   146,    89,
     124,    14,   152,   143,    15,   154,    15,    16,    17,    93,
      25,    26,    27,    34,    35,    36,    37,    38,   134,    29,
     150,    28,   180,    79,    80,    81,   147,   148,   149,   134,
     157,    16,   155,    89,    39,    40,    21,   135,   136,   137,
      70,   138,   139,    54,   140,   141,    39,    40,   140,    39,
      40,   150,    84,    85,    86,    94,    95,    96,    99,   181,
     181,   181,   149,   157,    17,   156,    10,   135,   135,   180,
     137,    39,    40,    34,    36,    55,    59,    62,    63,    66,
      68,    88,   182,    88,   183,    88,   184,   157,    88,    56,
      57,    56,    57,    58,    59,    60,    61,    64,    65,    67,
      69,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   101,   101,   101,   101,   101,   101,   101,
     102,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   111,   112,   112,   113,   113,   114,
     115,   115,   117,   118,   116,   119,   119,   120,   120,   121,
     121,   121,   121,   122,   122,   122,   123,   123,   123,   123,
     123,   123,   124,   124,   125,   126,   126,   127,   127,   128,
     128,   129,   130,   130,   130,   131,   131,   132,   132,   132,
     132,   133,   133,   133,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   135,   135,   136,   136,   137,
     138,   138,   139,   139,   140,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     142,   142,   142,   143,   143,   143,   143,   144,   144,   144,
     145,   145,   145,   146,   146,   146,   147,   147,   148,   148,
     149,   149,   149,   150,   150,   151,   151,   152,   153,   153,
     154,   155,   156,   157,   157,   157,   158,   160,   159,   161,
     161,   162,   162,   163,   163,   163,   164,   164,   165,   166,
     166,   166,   167,   167,   169,   168,   170,   170,   170,   171,
     172,   172,   173,   174,   175,   175,   176,   177,   178,   178,
     179,   179,   180,   180,   180,   181,   181,   181,   181,   181,
     181,   181,   181,   182,   183,   184,   185
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     3,     3,     3,     3,     3,     3,
       2,     4,     5,     5,     4,     5,     4,     6,     6,     5,
       4,     2,     0,     2,     0,     2,     0,     2,     1,     1,
       5,     1,     1,     3,     1,     5,     1,     1,     3,     1,
       0,     3,     0,     0,    10,     5,     1,     1,     3,     3,
       2,     3,     3,     0,     1,     1,     0,     3,     3,     3,
       4,     2,     0,     1,     3,     1,     1,     1,     7,     0,
       1,     5,     0,     3,     3,     0,     5,     0,     2,     3,
       4,     0,     2,     3,     3,     3,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     0,     1,     2,     1,     3,
       0,     1,     2,     2,     1,     0,     2,     3,     3,     3,
       3,     3,     3,     3,     4,     2,     3,     3,     3,     3,
       0,     2,     3,     2,     2,     2,     3,     0,     2,     3,
       0,     2,     3,     0,     2,     3,     0,     1,     2,     1,
       3,     3,     3,     1,     1,     2,     3,     2,     0,     2,
       2,     2,     2,     1,     1,     1,     3,     0,     4,     0,
       1,     2,     1,     1,     3,     5,     2,     1,     3,     2,
       2,     2,     1,     3,     0,     3,     0,     3,     2,     1,
       0,     2,     1,     1,     0,     1,     1,     1,     0,     2,
       0,     1,     0,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
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
#line 190 "parse.y"
                                                { file->errors++; }
#line 1840 "y.tab.c"
    break;

  case 10: /* include: INCLUDE STRING  */
#line 194 "parse.y"
                {
			struct file *nfile;

			if ((nfile = pushfile((yyvsp[0].v.string), 1)) == NULL) {
				yyerror("failed to include file %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			file = nfile;
			lungetc('\n');
		}
#line 1858 "y.tab.c"
    break;

  case 11: /* option: SET HOSTAP INTERFACE hostapifaces  */
#line 209 "parse.y"
                {
			if (!TAILQ_EMPTY(&hostapd_cfg.c_apmes))
				hostapd_cfg.c_flags |= HOSTAPD_CFG_F_APME;
		}
#line 1867 "y.tab.c"
    break;

  case 13: /* option: SET HOSTAP HOPPER DELAY timeout  */
#line 215 "parse.y"
                {
			bcopy(&(yyvsp[0].v.timeout), &hostapd_cfg.c_apme_hopdelay,
			    sizeof(struct timeval));
		}
#line 1876 "y.tab.c"
    break;

  case 15: /* option: SET IAPP INTERFACE STRING passive  */
#line 221 "parse.y"
                {
			if (strlcpy(hostapd_cfg.c_iapp.i_iface, (yyvsp[-1].v.string),
			    sizeof(hostapd_cfg.c_iapp.i_iface)) >=
			    sizeof(hostapd_cfg.c_iapp.i_iface)) {
				yyerror("invalid interface %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}

			hostapd_cfg.c_flags |= HOSTAPD_CFG_F_IAPP;

			hostapd_log(HOSTAPD_LOG_DEBUG,
			    "%s: IAPP interface added", (yyvsp[-1].v.string));

			free((yyvsp[-1].v.string));
		}
#line 1897 "y.tab.c"
    break;

  case 17: /* option: SET IAPP ADDRESS ROAMING TABLE table  */
#line 239 "parse.y"
                {
			if ((hostapd_cfg.c_iapp.i_addr_tbl =
			    hostapd_table_lookup(&hostapd_cfg, (yyvsp[0].v.string))) == NULL) {
				yyerror("undefined table <%s>", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 1911 "y.tab.c"
    break;

  case 18: /* option: SET IAPP ROUTE ROAMING TABLE table  */
#line 249 "parse.y"
                {
			if ((hostapd_cfg.c_iapp.i_route_tbl =
			    hostapd_table_lookup(&hostapd_cfg, (yyvsp[0].v.string))) == NULL) {
				yyerror("undefined table <%s>", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 1925 "y.tab.c"
    break;

  case 20: /* iappmode: MULTICAST iappmodeaddr iappmodeport iappmodettl  */
#line 262 "parse.y"
                {
			hostapd_cfg.c_flags &= ~HOSTAPD_CFG_F_BRDCAST;
		}
#line 1933 "y.tab.c"
    break;

  case 21: /* iappmode: BROADCAST iappmodeport  */
#line 266 "parse.y"
                {
			hostapd_cfg.c_flags |= HOSTAPD_CFG_F_BRDCAST;
		}
#line 1941 "y.tab.c"
    break;

  case 23: /* iappmodeaddr: ADDRESS ipv4addr  */
#line 273 "parse.y"
                {
			bcopy(&(yyvsp[0].v.in), &hostapd_cfg.c_iapp.i_multicast.sin_addr,
			    sizeof(struct in_addr));
		}
#line 1950 "y.tab.c"
    break;

  case 25: /* iappmodeport: PORT NUMBER  */
#line 281 "parse.y"
                {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > UINT16_MAX) {
				yyerror("port out of range: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			hostapd_cfg.c_iapp.i_addr.sin_port = htons((yyvsp[0].v.number));
		}
#line 1962 "y.tab.c"
    break;

  case 27: /* iappmodettl: TTL NUMBER  */
#line 292 "parse.y"
                {
			if ((yyvsp[0].v.number) < 1 || (yyvsp[0].v.number) > UINT8_MAX) {
				yyerror("ttl out of range: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			hostapd_cfg.c_iapp.i_ttl = (yyvsp[0].v.number);
		}
#line 1974 "y.tab.c"
    break;

  case 28: /* hostapmode: RADIOTAP  */
#line 302 "parse.y"
                {
			hostapd_cfg.c_apme_dlt = DLT_IEEE802_11_RADIO;
		}
#line 1982 "y.tab.c"
    break;

  case 29: /* hostapmode: PCAP  */
#line 306 "parse.y"
                {
			hostapd_cfg.c_apme_dlt = DLT_IEEE802_11;
		}
#line 1990 "y.tab.c"
    break;

  case 34: /* hostapiface: STRING  */
#line 320 "parse.y"
                {
			if (hostapd_apme_add(&hostapd_cfg, (yyvsp[0].v.string)) != 0) {
				yyerror("failed to add hostap interface");
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2002 "y.tab.c"
    break;

  case 39: /* hopperiface: STRING  */
#line 338 "parse.y"
                {
			if ((apme = hostapd_apme_addhopper(&hostapd_cfg,
			    (yyvsp[0].v.string))) == NULL) {
				yyerror("failed to add hopper %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2016 "y.tab.c"
    break;

  case 41: /* hostapmatch: ON not STRING  */
#line 351 "parse.y"
                {
			if ((frame.f_apme =
			    hostapd_apme_lookup(&hostapd_cfg, (yyvsp[0].v.string))) == NULL) {
				yyerror("undefined hostap interface");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			HOSTAPD_MATCH(APME, (yyvsp[-1].v.number));
		}
#line 2032 "y.tab.c"
    break;

  case 42: /* $@1: %empty  */
#line 365 "parse.y"
                {
			bzero(&frame, sizeof(struct hostapd_frame));
			/* IEEE 802.11 frame to match */
			frame_ieee80211 = &frame.f_frame;
		}
#line 2042 "y.tab.c"
    break;

  case 43: /* $@2: %empty  */
#line 369 "parse.y"
                                                {
			/* IEEE 802.11 raw frame to send as an action */
			frame_ieee80211 = &frame.f_action_data.a_frame;
		}
#line 2051 "y.tab.c"
    break;

  case 44: /* event: HOSTAP HANDLE $@1 eventopt hostapmatch frmmatch $@2 action limit rate  */
#line 372 "parse.y"
                                    {
			if ((frame_ptr = calloc(1, sizeof(struct hostapd_frame)))
			    == NULL) {
				yyerror("calloc");
				YYERROR;
			}

			if (gettimeofday(&frame.f_last, NULL) == -1)
				hostapd_fatal("gettimeofday");
			timeradd(&frame.f_last, &frame.f_limit, &frame.f_then);

			bcopy(&frame, frame_ptr, sizeof(struct hostapd_frame));
			TAILQ_INSERT_TAIL(&hostapd_cfg.c_frames,
			    frame_ptr, f_entries);
		}
#line 2071 "y.tab.c"
    break;

  case 49: /* iappsubtype: not ADD NOTIFY  */
#line 398 "parse.y"
                {
			HOSTAPD_IAPP_FLAG(ADD_NOTIFY, (yyvsp[-2].v.number));
		}
#line 2079 "y.tab.c"
    break;

  case 50: /* iappsubtype: not RADIOTAP  */
#line 402 "parse.y"
                {
			HOSTAPD_IAPP_FLAG(RADIOTAP, (yyvsp[-1].v.number));
		}
#line 2087 "y.tab.c"
    break;

  case 51: /* iappsubtype: not ROUTE ROAMING  */
#line 406 "parse.y"
                {
			HOSTAPD_IAPP_FLAG(ROAMING_ROUTE, (yyvsp[-2].v.number));
		}
#line 2095 "y.tab.c"
    break;

  case 52: /* iappsubtype: not ADDRESS ROAMING  */
#line 410 "parse.y"
                {
			HOSTAPD_IAPP_FLAG(ROAMING_ADDRESS, (yyvsp[-2].v.number));
		}
#line 2103 "y.tab.c"
    break;

  case 53: /* eventopt: %empty  */
#line 416 "parse.y"
                {
			frame.f_flags |= HOSTAPD_FRAME_F_RET_OK;
		}
#line 2111 "y.tab.c"
    break;

  case 54: /* eventopt: QUICK  */
#line 420 "parse.y"
                {
			frame.f_flags |= HOSTAPD_FRAME_F_RET_QUICK;
		}
#line 2119 "y.tab.c"
    break;

  case 55: /* eventopt: SKIP  */
#line 424 "parse.y"
                {
			frame.f_flags |= HOSTAPD_FRAME_F_RET_SKIP;
		}
#line 2127 "y.tab.c"
    break;

  case 56: /* action: %empty  */
#line 430 "parse.y"
                {
			frame.f_action = HOSTAPD_ACTION_NONE;
		}
#line 2135 "y.tab.c"
    break;

  case 57: /* action: WITH LOG verbose  */
#line 434 "parse.y"
                {
			frame.f_action = HOSTAPD_ACTION_LOG;
		}
#line 2143 "y.tab.c"
    break;

  case 58: /* action: WITH FRAME frmaction  */
#line 438 "parse.y"
                {
			frame.f_action = HOSTAPD_ACTION_FRAME;
		}
#line 2151 "y.tab.c"
    break;

  case 60: /* action: WITH NODE nodeopt frmactionaddr  */
#line 443 "parse.y"
                {
			if (((yyvsp[0].v.reflladdr).flags & HOSTAPD_ACTION_F_REF_M) == 0) {
				bcopy((yyvsp[0].v.reflladdr).lladdr, frame.f_action_data.a_lladdr,
				    IEEE80211_ADDR_LEN);
			} else
				frame.f_action_data.a_flags |= (yyvsp[0].v.reflladdr).flags;
		}
#line 2163 "y.tab.c"
    break;

  case 61: /* action: WITH RESEND  */
#line 451 "parse.y"
                {
			frame.f_action = HOSTAPD_ACTION_RESEND;
		}
#line 2171 "y.tab.c"
    break;

  case 63: /* verbose: VERBOSE  */
#line 458 "parse.y"
                {
			frame.f_action_flags |= HOSTAPD_ACTION_VERBOSE;
		}
#line 2179 "y.tab.c"
    break;

  case 64: /* iapp: TYPE RADIOTAP verbose  */
#line 464 "parse.y"
                {
			frame.f_action = HOSTAPD_ACTION_RADIOTAP;
		}
#line 2187 "y.tab.c"
    break;

  case 65: /* nodeopt: DELETE  */
#line 470 "parse.y"
                {
			frame.f_action = HOSTAPD_ACTION_DELNODE;
		}
#line 2195 "y.tab.c"
    break;

  case 66: /* nodeopt: ADD  */
#line 474 "parse.y"
                {
			frame.f_action = HOSTAPD_ACTION_ADDNODE;
		}
#line 2203 "y.tab.c"
    break;

  case 73: /* limit: LIMIT NUMBER SEC  */
#line 493 "parse.y"
                {
			if ((yyvsp[-1].v.number) < 0 || (yyvsp[-1].v.number) > LONG_MAX) {
				yyerror("limit out of range: %lld sec", (yyvsp[-1].v.number));
				YYERROR;
			}
			frame.f_limit.tv_sec = (yyvsp[-1].v.number);
		}
#line 2215 "y.tab.c"
    break;

  case 74: /* limit: LIMIT NUMBER USEC  */
#line 501 "parse.y"
                {
			if ((yyvsp[-1].v.number) < 0 || (yyvsp[-1].v.number) > LONG_MAX) {
				yyerror("limit out of range: %lld usec", (yyvsp[-1].v.number));
				YYERROR;
			}
			frame.f_limit.tv_sec = (yyvsp[-1].v.number) / 1000000;
			frame.f_limit.tv_usec = (yyvsp[-1].v.number) % 1000000;
		}
#line 2228 "y.tab.c"
    break;

  case 76: /* rate: RATE NUMBER '/' NUMBER SEC  */
#line 513 "parse.y"
                {
			if (((yyvsp[-3].v.number) < 1 || (yyvsp[-3].v.number) > LONG_MAX) ||
			    ((yyvsp[-1].v.number) < 1 || (yyvsp[-1].v.number) > LONG_MAX)) {
				yyerror("rate out of range: %lld/%lld sec",
				    (yyvsp[-3].v.number), (yyvsp[-1].v.number));
				YYERROR;
			}

			if (!((yyvsp[-3].v.number) && (yyvsp[-1].v.number))) {
				yyerror("invalid rate");
				YYERROR;
			}

			frame.f_rate = (yyvsp[-3].v.number);
			frame.f_rate_intval = (yyvsp[-1].v.number);
		}
#line 2249 "y.tab.c"
    break;

  case 79: /* frmmatchtype: TYPE not DATA  */
#line 534 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_TYPE_DATA;
			HOSTAPD_MATCH(TYPE, (yyvsp[-1].v.number));
		}
#line 2259 "y.tab.c"
    break;

  case 80: /* frmmatchtype: TYPE not MANAGEMENT frmmatchmgmt  */
#line 540 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_TYPE_MGT;
			HOSTAPD_MATCH(TYPE, (yyvsp[-2].v.number));
		}
#line 2269 "y.tab.c"
    break;

  case 83: /* frmmatchmgmt: SUBTYPE not frmsubtype  */
#line 550 "parse.y"
                {
			HOSTAPD_MATCH(SUBTYPE, (yyvsp[-1].v.number));
		}
#line 2277 "y.tab.c"
    break;

  case 84: /* frmsubtype: PROBE REQUEST frmelems  */
#line 556 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_PROBE_REQ;
		}
#line 2286 "y.tab.c"
    break;

  case 85: /* frmsubtype: PROBE RESPONSE frmelems  */
#line 561 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_PROBE_RESP;
		}
#line 2295 "y.tab.c"
    break;

  case 86: /* frmsubtype: BEACON frmelems  */
#line 566 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_BEACON;
		}
#line 2304 "y.tab.c"
    break;

  case 87: /* frmsubtype: ATIM  */
#line 571 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_ATIM;
		}
#line 2313 "y.tab.c"
    break;

  case 88: /* frmsubtype: AUTH frmauth  */
#line 576 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_AUTH;
		}
#line 2322 "y.tab.c"
    break;

  case 89: /* frmsubtype: DEAUTH frmreason  */
#line 581 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_DEAUTH;
		}
#line 2331 "y.tab.c"
    break;

  case 90: /* frmsubtype: ASSOC REQUEST  */
#line 586 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_ASSOC_REQ;
		}
#line 2340 "y.tab.c"
    break;

  case 91: /* frmsubtype: DISASSOC frmreason  */
#line 591 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_DISASSOC;
		}
#line 2349 "y.tab.c"
    break;

  case 92: /* frmsubtype: ASSOC RESPONSE  */
#line 596 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_ASSOC_RESP;
		}
#line 2358 "y.tab.c"
    break;

  case 93: /* frmsubtype: REASSOC REQUEST  */
#line 601 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_REASSOC_REQ;
		}
#line 2367 "y.tab.c"
    break;

  case 94: /* frmsubtype: REASSOC RESPONSE  */
#line 606 "parse.y"
                {
			frame_ieee80211->i_fc[0] |=
			    IEEE80211_FC0_SUBTYPE_REASSOC_RESP;
		}
#line 2376 "y.tab.c"
    break;

  case 101: /* frmauth: authalg  */
#line 625 "parse.y"
                {
			if ((frame_ieee80211->i_data = malloc(6)) == NULL) {
				yyerror("failed to allocate auth");
				YYERROR;
			}
			((u_int16_t *)frame_ieee80211->i_data)[0] =
				(yyvsp[0].v.authalg).alg;
			((u_int16_t *)frame_ieee80211->i_data)[1] =
				(yyvsp[0].v.authalg).transaction;
			((u_int16_t *)frame_ieee80211->i_data)[0] = 0;
			frame_ieee80211->i_data_len = 6;
		}
#line 2393 "y.tab.c"
    break;

  case 102: /* authalg: OPEN REQUEST  */
#line 640 "parse.y"
                {
			(yyval.v.authalg).alg = htole16(IEEE80211_AUTH_ALG_OPEN);
			(yyval.v.authalg).transaction = htole16(IEEE80211_AUTH_OPEN_REQUEST);
		}
#line 2402 "y.tab.c"
    break;

  case 103: /* authalg: OPEN RESPONSE  */
#line 645 "parse.y"
                {
			(yyval.v.authalg).alg = htole16(IEEE80211_AUTH_ALG_OPEN);
			(yyval.v.authalg).transaction = htole16(IEEE80211_AUTH_OPEN_RESPONSE);
		}
#line 2411 "y.tab.c"
    break;

  case 104: /* frmreason: frmreason_l  */
#line 652 "parse.y"
                {
			if ((yyvsp[0].v.reason) != 0) {
				if ((frame_ieee80211->i_data =
				    malloc(sizeof(u_int16_t))) == NULL) {
					yyerror("failed to allocate "
					    "reason code %u", (yyvsp[0].v.reason));
					YYERROR;
				}
				*(u_int16_t *)frame_ieee80211->i_data =
				    htole16((yyvsp[0].v.reason));
				frame_ieee80211->i_data_len = sizeof(u_int16_t);
			}
		}
#line 2429 "y.tab.c"
    break;

  case 105: /* frmreason_l: %empty  */
#line 668 "parse.y"
                {
			(yyval.v.reason) = 0;
		}
#line 2437 "y.tab.c"
    break;

  case 106: /* frmreason_l: REASON UNSPECIFIED  */
#line 672 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_UNSPECIFIED;
		}
#line 2445 "y.tab.c"
    break;

  case 107: /* frmreason_l: REASON AUTH EXPIRE  */
#line 676 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_AUTH_EXPIRE;
		}
#line 2453 "y.tab.c"
    break;

  case 108: /* frmreason_l: REASON AUTH LEAVE  */
#line 680 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_AUTH_LEAVE;
		}
#line 2461 "y.tab.c"
    break;

  case 109: /* frmreason_l: REASON ASSOC EXPIRE  */
#line 684 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_ASSOC_EXPIRE;
		}
#line 2469 "y.tab.c"
    break;

  case 110: /* frmreason_l: REASON ASSOC TOOMANY  */
#line 688 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_ASSOC_TOOMANY;
		}
#line 2477 "y.tab.c"
    break;

  case 111: /* frmreason_l: REASON NOT AUTHED  */
#line 692 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_NOT_AUTHED;
		}
#line 2485 "y.tab.c"
    break;

  case 112: /* frmreason_l: REASON NOT ASSOCED  */
#line 696 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_NOT_ASSOCED;
		}
#line 2493 "y.tab.c"
    break;

  case 113: /* frmreason_l: REASON ASSOC LEAVE  */
#line 700 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_ASSOC_LEAVE;
		}
#line 2501 "y.tab.c"
    break;

  case 114: /* frmreason_l: REASON ASSOC NOT AUTHED  */
#line 704 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_NOT_AUTHED;
		}
#line 2509 "y.tab.c"
    break;

  case 115: /* frmreason_l: REASON RESERVED  */
#line 708 "parse.y"
                {
			(yyval.v.reason) = 10;	/* XXX unknown */
		}
#line 2517 "y.tab.c"
    break;

  case 116: /* frmreason_l: REASON RSN REQUIRED  */
#line 712 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_RSN_REQUIRED;
		}
#line 2525 "y.tab.c"
    break;

  case 117: /* frmreason_l: REASON RSN INCONSISTENT  */
#line 716 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_RSN_INCONSISTENT;
		}
#line 2533 "y.tab.c"
    break;

  case 118: /* frmreason_l: REASON IE INVALID  */
#line 720 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_IE_INVALID;
		}
#line 2541 "y.tab.c"
    break;

  case 119: /* frmreason_l: REASON MIC FAILURE  */
#line 724 "parse.y"
                {
			(yyval.v.reason) = IEEE80211_REASON_MIC_FAILURE;
		}
#line 2549 "y.tab.c"
    break;

  case 122: /* frmmatchdir: DIR not frmdir  */
#line 732 "parse.y"
                {
			HOSTAPD_MATCH(DIR, (yyvsp[-1].v.number));
		}
#line 2557 "y.tab.c"
    break;

  case 123: /* frmdir: NO DS  */
#line 738 "parse.y"
                {
			frame_ieee80211->i_fc[1] |= IEEE80211_FC1_DIR_NODS;
		}
#line 2565 "y.tab.c"
    break;

  case 124: /* frmdir: TO DS  */
#line 742 "parse.y"
                {
			frame_ieee80211->i_fc[1] |= IEEE80211_FC1_DIR_TODS;
		}
#line 2573 "y.tab.c"
    break;

  case 125: /* frmdir: FROM DS  */
#line 746 "parse.y"
                {
			frame_ieee80211->i_fc[1] |= IEEE80211_FC1_DIR_FROMDS;
		}
#line 2581 "y.tab.c"
    break;

  case 126: /* frmdir: DS TO DS  */
#line 750 "parse.y"
                {
			frame_ieee80211->i_fc[1] |= IEEE80211_FC1_DIR_DSTODS;
		}
#line 2589 "y.tab.c"
    break;

  case 129: /* frmmatchfrom: FROM not frmmatchaddr  */
#line 758 "parse.y"
                {
			if (((yyvsp[0].v.reflladdr).flags & HOSTAPD_ACTION_F_OPT_TABLE) == 0) {
				bcopy((yyvsp[0].v.reflladdr).lladdr, &frame_ieee80211->i_from,
				    IEEE80211_ADDR_LEN);
				HOSTAPD_MATCH(FROM, (yyvsp[-1].v.number));
			} else {
				frame.f_from = (yyvsp[0].v.reflladdr).table;
				HOSTAPD_MATCH_TABLE(FROM, (yyvsp[-1].v.number));
			}
		}
#line 2604 "y.tab.c"
    break;

  case 132: /* frmmatchto: TO not frmmatchaddr  */
#line 773 "parse.y"
                {
			if (((yyvsp[0].v.reflladdr).flags & HOSTAPD_ACTION_F_OPT_TABLE) == 0) {
				bcopy((yyvsp[0].v.reflladdr).lladdr, &frame_ieee80211->i_to,
				    IEEE80211_ADDR_LEN);
				HOSTAPD_MATCH(TO, (yyvsp[-1].v.number));
			} else {
				frame.f_to = (yyvsp[0].v.reflladdr).table;
				HOSTAPD_MATCH_TABLE(TO, (yyvsp[-1].v.number));
			}
		}
#line 2619 "y.tab.c"
    break;

  case 135: /* frmmatchbssid: BSSID not frmmatchaddr  */
#line 788 "parse.y"
                {
			if (((yyvsp[0].v.reflladdr).flags & HOSTAPD_ACTION_F_OPT_TABLE) == 0) {
				bcopy((yyvsp[0].v.reflladdr).lladdr, &frame_ieee80211->i_bssid,
				    IEEE80211_ADDR_LEN);
				HOSTAPD_MATCH(BSSID, (yyvsp[-1].v.number));
			} else {
				frame.f_bssid = (yyvsp[0].v.reflladdr).table;
				HOSTAPD_MATCH_TABLE(BSSID, (yyvsp[-1].v.number));
			}
		}
#line 2634 "y.tab.c"
    break;

  case 140: /* frmmatchrtapopt: RSSI unaryop percent  */
#line 809 "parse.y"
                {
			if (((yyvsp[-1].v.op) == HOSTAPD_OP_GT && (yyvsp[0].v.number) == 100) ||
			    ((yyvsp[-1].v.op) == HOSTAPD_OP_LE && (yyvsp[0].v.number) == 100) ||
			    ((yyvsp[-1].v.op) == HOSTAPD_OP_LT && (yyvsp[0].v.number) == 0) ||
			    ((yyvsp[-1].v.op) == HOSTAPD_OP_GE && (yyvsp[0].v.number) == 0)) {
				yyerror("absurd unary comparison");
				YYERROR;
			}

			frame.f_rssi_op = (yyvsp[-1].v.op);
			frame.f_rssi = (yyvsp[0].v.number);
			HOSTAPD_MATCH_RADIOTAP(RSSI);
		}
#line 2652 "y.tab.c"
    break;

  case 141: /* frmmatchrtapopt: TXRATE unaryop txrate  */
#line 823 "parse.y"
                {
			frame.f_txrate_op = (yyvsp[-1].v.op);
			frame.f_txrate = (yyvsp[0].v.number);
			HOSTAPD_MATCH_RADIOTAP(RATE);
		}
#line 2662 "y.tab.c"
    break;

  case 142: /* frmmatchrtapopt: FREQ unaryop freq  */
#line 829 "parse.y"
                {
			frame.f_chan_op = (yyvsp[-1].v.op);
			frame.f_chan = (yyvsp[0].v.number);
			HOSTAPD_MATCH_RADIOTAP(CHANNEL);
		}
#line 2672 "y.tab.c"
    break;

  case 143: /* frmmatchaddr: table  */
#line 837 "parse.y"
                {
			if (((yyval.v.reflladdr).table =
			    hostapd_table_lookup(&hostapd_cfg, (yyvsp[0].v.string))) == NULL) {
				yyerror("undefined table <%s>", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			(yyval.v.reflladdr).flags = HOSTAPD_ACTION_F_OPT_TABLE;
			free((yyvsp[0].v.string));
		}
#line 2687 "y.tab.c"
    break;

  case 144: /* frmmatchaddr: lladdr  */
#line 848 "parse.y"
                {
			bcopy((yyvsp[0].v.reflladdr).lladdr, (yyval.v.reflladdr).lladdr, IEEE80211_ADDR_LEN);
			(yyval.v.reflladdr).flags = HOSTAPD_ACTION_F_OPT_LLADDR;
		}
#line 2696 "y.tab.c"
    break;

  case 145: /* frmactiontype: TYPE DATA  */
#line 855 "parse.y"
                {
			frame_ieee80211->i_fc[0] |= IEEE80211_FC0_TYPE_DATA;
		}
#line 2704 "y.tab.c"
    break;

  case 146: /* frmactiontype: TYPE MANAGEMENT frmactionmgmt  */
#line 859 "parse.y"
                {
			frame_ieee80211->i_fc[0] |= IEEE80211_FC0_TYPE_MGT;
		}
#line 2712 "y.tab.c"
    break;

  case 148: /* frmactiondir: %empty  */
#line 868 "parse.y"
                {
			frame.f_action_data.a_flags |=
			    HOSTAPD_ACTION_F_OPT_DIR_AUTO;
		}
#line 2721 "y.tab.c"
    break;

  case 150: /* frmactionfrom: FROM frmactionaddr  */
#line 876 "parse.y"
                {
			if (((yyvsp[0].v.reflladdr).flags & HOSTAPD_ACTION_F_REF_M) == 0) {
				bcopy((yyvsp[0].v.reflladdr).lladdr, frame_ieee80211->i_from,
				    IEEE80211_ADDR_LEN);
			} else
				frame.f_action_data.a_flags |=
				    ((yyvsp[0].v.reflladdr).flags << HOSTAPD_ACTION_F_REF_FROM_S);
		}
#line 2734 "y.tab.c"
    break;

  case 151: /* frmactionto: TO frmactionaddr  */
#line 887 "parse.y"
                {
			if (((yyvsp[0].v.reflladdr).flags & HOSTAPD_ACTION_F_REF_M) == 0) {
				bcopy((yyvsp[0].v.reflladdr).lladdr, frame_ieee80211->i_to,
				    IEEE80211_ADDR_LEN);
			} else
				frame.f_action_data.a_flags |=
				    ((yyvsp[0].v.reflladdr).flags << HOSTAPD_ACTION_F_REF_TO_S);
		}
#line 2747 "y.tab.c"
    break;

  case 152: /* frmactionbssid: BSSID frmactionaddr  */
#line 898 "parse.y"
                {
			if (((yyvsp[0].v.reflladdr).flags & HOSTAPD_ACTION_F_REF_M) == 0) {
				bcopy((yyvsp[0].v.reflladdr).lladdr, frame_ieee80211->i_bssid,
				    IEEE80211_ADDR_LEN);
			} else
				frame.f_action_data.a_flags |=
				    ((yyvsp[0].v.reflladdr).flags << HOSTAPD_ACTION_F_REF_BSSID_S);
		}
#line 2760 "y.tab.c"
    break;

  case 153: /* frmactionaddr: lladdr  */
#line 909 "parse.y"
                {
			bcopy((yyvsp[0].v.reflladdr).lladdr, (yyval.v.reflladdr).lladdr, IEEE80211_ADDR_LEN);
			(yyval.v.reflladdr).flags = (yyvsp[0].v.reflladdr).flags;
		}
#line 2769 "y.tab.c"
    break;

  case 154: /* frmactionaddr: randaddr  */
#line 914 "parse.y"
                {
			(yyval.v.reflladdr).flags = (yyvsp[0].v.reflladdr).flags;
		}
#line 2777 "y.tab.c"
    break;

  case 155: /* frmactionaddr: refaddr  */
#line 918 "parse.y"
                {
			(yyval.v.reflladdr).flags = (yyvsp[0].v.reflladdr).flags;
		}
#line 2785 "y.tab.c"
    break;

  case 156: /* table: '<' STRING '>'  */
#line 923 "parse.y"
                                 {
			if (strlen((yyvsp[-1].v.string)) >= HOSTAPD_TABLE_NAMELEN) {
				yyerror("table name %s too long, max %u",
				    (yyvsp[-1].v.string), HOSTAPD_TABLE_NAMELEN - 1);
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			(yyval.v.string) = (yyvsp[-1].v.string);
		}
#line 2799 "y.tab.c"
    break;

  case 157: /* $@3: %empty  */
#line 934 "parse.y"
                              {
			if ((table =
			    hostapd_table_add(&hostapd_cfg, (yyvsp[0].v.string))) == NULL) {
				yyerror("failed to add table: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2813 "y.tab.c"
    break;

  case 158: /* tabledef: TABLE table $@3 tableopts  */
#line 942 "parse.y"
                            {
			table = NULL;
		}
#line 2821 "y.tab.c"
    break;

  case 163: /* tableopt: CONST  */
#line 955 "parse.y"
                        {
			if (table->t_flags & HOSTAPD_TABLE_F_CONST) {
				yyerror("option already specified");
				YYERROR;
			}
			table->t_flags |= HOSTAPD_TABLE_F_CONST;
		}
#line 2833 "y.tab.c"
    break;

  case 166: /* string: string STRING  */
#line 967 "parse.y"
                {
			if (asprintf(&(yyval.v.string), "%s %s", (yyvsp[-1].v.string), (yyvsp[0].v.string)) == -1)
				hostapd_fatal("string: asprintf");
			free((yyvsp[-1].v.string));
			free((yyvsp[0].v.string));
		}
#line 2844 "y.tab.c"
    break;

  case 168: /* varset: STRING '=' string  */
#line 977 "parse.y"
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
				hostapd_fatal("cannot store variable");
			free((yyvsp[-2].v.string));
			free((yyvsp[0].v.string));
		}
#line 2865 "y.tab.c"
    break;

  case 169: /* refaddr: '&' FROM  */
#line 996 "parse.y"
                {
			(yyval.v.reflladdr).flags |= HOSTAPD_ACTION_F_REF_FROM;
		}
#line 2873 "y.tab.c"
    break;

  case 170: /* refaddr: '&' TO  */
#line 1000 "parse.y"
                {
			(yyval.v.reflladdr).flags |= HOSTAPD_ACTION_F_REF_TO;
		}
#line 2881 "y.tab.c"
    break;

  case 171: /* refaddr: '&' BSSID  */
#line 1004 "parse.y"
                {
			(yyval.v.reflladdr).flags |= HOSTAPD_ACTION_F_REF_BSSID;
		}
#line 2889 "y.tab.c"
    break;

  case 174: /* $@4: %empty  */
#line 1014 "parse.y"
                {
			if ((entry = hostapd_entry_add(table,
			    (yyvsp[0].v.reflladdr).lladdr)) == NULL) {
				yyerror("failed to add entry: %s",
				    etheraddr_string((yyvsp[0].v.reflladdr).lladdr));
				YYERROR;
			}
		}
#line 2902 "y.tab.c"
    break;

  case 175: /* tableaddrentry: lladdr $@4 tableaddropt  */
#line 1021 "parse.y"
                               {
			entry = NULL;
		}
#line 2910 "y.tab.c"
    break;

  case 177: /* tableaddropt: assign ipv4addr ipv4netmask  */
#line 1028 "parse.y"
                {
			entry->e_flags |= HOSTAPD_ENTRY_F_INADDR;
			entry->e_inaddr.in_af = AF_INET;
			bcopy(&(yyvsp[-1].v.in), &entry->e_inaddr.in_v4,
			    sizeof(struct in_addr));
		}
#line 2921 "y.tab.c"
    break;

  case 178: /* tableaddropt: mask lladdr  */
#line 1035 "parse.y"
                {
			entry->e_flags |= HOSTAPD_ENTRY_F_MASK;
			bcopy((yyvsp[0].v.reflladdr).lladdr, entry->e_mask, IEEE80211_ADDR_LEN);

			/* Update entry position in the table */
			hostapd_entry_update(table, entry);
		}
#line 2933 "y.tab.c"
    break;

  case 179: /* ipv4addr: STRING  */
#line 1045 "parse.y"
                {
			if (inet_net_pton(AF_INET, (yyvsp[0].v.string), &(yyval.v.in), sizeof((yyval.v.in))) == -1) {
				yyerror("invalid address: %s\n", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2946 "y.tab.c"
    break;

  case 180: /* ipv4netmask: %empty  */
#line 1056 "parse.y"
                {
			entry->e_inaddr.in_netmask = -1;
		}
#line 2954 "y.tab.c"
    break;

  case 181: /* ipv4netmask: '/' NUMBER  */
#line 1060 "parse.y"
                {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > 32) {
				yyerror("netmask out of range: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			entry->e_inaddr.in_netmask = (yyvsp[0].v.number);
		}
#line 2966 "y.tab.c"
    break;

  case 182: /* lladdr: STRING  */
#line 1070 "parse.y"
                {
			struct ether_addr *ea;

			if ((ea = ether_aton((yyvsp[0].v.string))) == NULL) {
				yyerror("invalid address: %s\n", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			bcopy(ea, (yyval.v.reflladdr).lladdr, IEEE80211_ADDR_LEN);
			(yyval.v.reflladdr).flags = HOSTAPD_ACTION_F_OPT_LLADDR;
		}
#line 2984 "y.tab.c"
    break;

  case 183: /* randaddr: RANDOM  */
#line 1086 "parse.y"
                {
			(yyval.v.reflladdr).flags |= HOSTAPD_ACTION_F_REF_RANDOM;
		}
#line 2992 "y.tab.c"
    break;

  case 185: /* passive: PASSIVE  */
#line 1093 "parse.y"
                {
			hostapd_cfg.c_flags |= HOSTAPD_CFG_F_IAPP_PASSIVE;
		}
#line 3000 "y.tab.c"
    break;

  case 192: /* not: %empty  */
#line 1113 "parse.y"
                {
			(yyval.v.number) = 0;
		}
#line 3008 "y.tab.c"
    break;

  case 193: /* not: '!'  */
#line 1117 "parse.y"
                {
			(yyval.v.number) = 1;
		}
#line 3016 "y.tab.c"
    break;

  case 194: /* not: NOT  */
#line 1121 "parse.y"
                {
			(yyval.v.number) = 1;
		}
#line 3024 "y.tab.c"
    break;

  case 195: /* unaryop: %empty  */
#line 1127 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_EQ;
		}
#line 3032 "y.tab.c"
    break;

  case 196: /* unaryop: '='  */
#line 1131 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_EQ;
		}
#line 3040 "y.tab.c"
    break;

  case 197: /* unaryop: '!'  */
#line 1135 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_NE;
		}
#line 3048 "y.tab.c"
    break;

  case 198: /* unaryop: NE  */
#line 1139 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_NE;
		}
#line 3056 "y.tab.c"
    break;

  case 199: /* unaryop: LE  */
#line 1143 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_LE;
		}
#line 3064 "y.tab.c"
    break;

  case 200: /* unaryop: '<'  */
#line 1147 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_LT;
		}
#line 3072 "y.tab.c"
    break;

  case 201: /* unaryop: GE  */
#line 1151 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_GE;
		}
#line 3080 "y.tab.c"
    break;

  case 202: /* unaryop: '>'  */
#line 1155 "parse.y"
                {
			(yyval.v.op) = HOSTAPD_OP_GT;
		}
#line 3088 "y.tab.c"
    break;

  case 203: /* percent: STRING  */
#line 1161 "parse.y"
                {
			double val;
			char *cp;

			val = strtod((yyvsp[0].v.string), &cp);
			if (cp == NULL || strcmp(cp, "%") != 0 ||
			    val < 0 || val > 100) {
				yyerror("invalid percentage: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			(yyval.v.number) = val;
		}
#line 3107 "y.tab.c"
    break;

  case 204: /* txrate: STRING  */
#line 1178 "parse.y"
                {
			double val;
			char *cp;

			val = strtod((yyvsp[0].v.string), &cp) * 2;
			if (cp == NULL || strcasecmp(cp, "mb") != 0 ||
			    val != (int)val) {
				yyerror("invalid rate: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			(yyval.v.number) = val;
		}
#line 3126 "y.tab.c"
    break;

  case 205: /* freq: STRING  */
#line 1195 "parse.y"
                {
			double val;
			char *cp;

			val = strtod((yyvsp[0].v.string), &cp);
			if (cp != NULL) {
				if (strcasecmp(cp, "ghz") == 0) {
					(yyval.v.number) = val * 1000;
				} else if (strcasecmp(cp, "mhz") == 0) {
					(yyval.v.number) = val;
				} else
					cp = NULL;
			}
			if (cp == NULL) {
				yyerror("invalid frequency: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 3151 "y.tab.c"
    break;

  case 206: /* timeout: NUMBER  */
#line 1218 "parse.y"
                {
			if ((yyvsp[0].v.number) < 1 || (yyvsp[0].v.number) > LONG_MAX) {
				yyerror("timeout out of range: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			(yyval.v.timeout).tv_sec = (yyvsp[0].v.number) / 1000;
			(yyval.v.timeout).tv_usec = ((yyvsp[0].v.number) % 1000) * 1000;
		}
#line 3164 "y.tab.c"
    break;


#line 3168 "y.tab.c"

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

#line 1227 "parse.y"


/*
 * Parser and lexer
 */

struct keywords {
	char *k_name;
	int k_val;
};

int
kw_cmp(const void *a, const void *b)
{
	return strcmp(a, ((const struct keywords *)b)->k_name);
}

int
lookup(char *token)
{
	/* Keep this list sorted */
	static const struct keywords keywords[] = {
		{ "add",		ADD },
		{ "address",		ADDRESS },
		{ "any",		ANY },
		{ "assoc",		ASSOC },
		{ "assoced",		ASSOCED },
		{ "atim",		ATIM },
		{ "auth",		AUTH },
		{ "authed",		AUTHED },
		{ "beacon",		BEACON },
		{ "broadcast",		BROADCAST },
		{ "bssid",		BSSID },
		{ "const",		CONST },
		{ "data",		DATA },
		{ "deauth",		DEAUTH },
		{ "delay",		DELAY },
		{ "delete",		DELETE },
		{ "dir",		DIR },
		{ "disassoc",		DISASSOC },
		{ "ds",			DS },
		{ "expire",		EXPIRE },
		{ "failure",		FAILURE },
		{ "frame",		FRAME },
		{ "freq",		FREQ },
		{ "from",		FROM },
		{ "handle",		HANDLE },
		{ "hopper",		HOPPER },
		{ "hostap",		HOSTAP },
		{ "iapp",		IAPP },
		{ "ie",			IE },
		{ "include",		INCLUDE },
		{ "inconsistent",	INCONSISTENT },
		{ "interface",		INTERFACE },
		{ "invalid",		INVALID },
		{ "leave",		LEAVE },
		{ "limit",		LIMIT },
		{ "log",		LOG },
		{ "management",		MANAGEMENT },
		{ "mic",		MIC },
		{ "mode",		MODE },
		{ "multicast",		MULTICAST },
		{ "no",			NO },
		{ "node",		NODE },
		{ "not",		NOT },
		{ "notify",		NOTIFY },
		{ "nwid",		NWID },
		{ "on",			ON },
		{ "open",		OPEN },
		{ "passive",		PASSIVE },
		{ "pcap",		PCAP },
		{ "port",		PORT },
		{ "probe",		PROBE },
		{ "quick",		QUICK },
		{ "radiotap",		RADIOTAP },
		{ "random",		RANDOM },
		{ "rate",		RATE },
		{ "reason",		REASON },
		{ "reassoc",		REASSOC },
		{ "request",		REQUEST },
		{ "required",		REQUIRED },
		{ "resend",		RESEND },
		{ "reserved",		RESERVED },
		{ "response",		RESPONSE },
		{ "roaming",		ROAMING },
		{ "route",		ROUTE },
		{ "rsn",		RSN },
		{ "sec",		SEC },
		{ "set",		SET },
		{ "signal",		RSSI },
		{ "skip",		SKIP },
		{ "subtype",		SUBTYPE },
		{ "table",		TABLE },
		{ "to",			TO },
		{ "toomany",		TOOMANY },
		{ "ttl",		TTL },
		{ "txrate",		TXRATE },
		{ "type",		TYPE },
		{ "unspecified",	UNSPECIFIED },
		{ "usec",		USEC },
		{ "verbose",		VERBOSE },
		{ "with",		WITH }
	};
	const struct keywords *p;

	p = bsearch(token, keywords, sizeof(keywords) / sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	return (p == NULL ? STRING : p->k_val);
}

#define	START_EXPAND	1
#define	DONE_EXPAND	2

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
			yyerror("macro \"%s\" not defined", buf);
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
			hostapd_fatal("yylex: strdup");
		return (STRING);
	case '-':
		next = lgetc(0);
		if (next == '>')
			return (ARROW);
		lungetc(next);
		break;
	case '!':
		next = lgetc(0);
		if (next == '=')
			return (NE);
		lungetc(next);
		break;		
	case '<':
		next = lgetc(0);
		if (next == '=')
			return (LE);
		lungetc(next);
		break;
	case '>':
		next = lgetc(0);
		if (next == '=')
			return (GE);
		lungetc(next);
		break;
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
	x != '!' && x != '=' && x != '/' && x != '#' && \
	x != ','))

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
				hostapd_fatal("yylex: strdup");
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

	hostapd_log(HOSTAPD_LOG_DEBUG, "%s = \"%s\"", sym->nam, sym->val);

	return (0);
}

int
hostapd_parse_symset(char *s)
{
	char	*sym, *val;
	int	ret;
	size_t	len;

	if ((val = strrchr(s, '=')) == NULL)
		return (-1);

	len = strlen(s) - strlen(val) + 1;
	if ((sym = malloc(len)) == NULL)
		hostapd_fatal("cmdline_symset: malloc");

	(void)strlcpy(sym, s, len);

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

int
check_file_secrecy(int fd, const char *fname)
{
	struct stat	st;

	if (fstat(fd, &st)) {
		warn("cannot stat %s", fname);
		return (-1);
	}
	if (st.st_uid != 0 && st.st_uid != getuid()) {
		warnx("%s: owner not root or current user", fname);
		return (-1);
	}
	if (st.st_mode & (S_IWGRP | S_IXGRP | S_IRWXO)) {
		warnx("%s: group writable or world read/writable", fname);
		return (-1);
	}
	return (0);
}

struct file *
pushfile(const char *name, int secret)
{
	struct file	*nfile;

	if ((nfile = calloc(1, sizeof(struct file))) == NULL) {
		warn("%s", __func__);
		return (NULL);
	}
	if ((nfile->name = strdup(name)) == NULL) {
		warn("%s", __func__);
		free(nfile);
		return (NULL);
	}
	if ((nfile->stream = fopen(nfile->name, "r")) == NULL) {
		warn("%s: %s", __func__, nfile->name);
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
		warn("%s", __func__);
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
hostapd_parse_file(struct hostapd_config *cfg)
{
	struct sym *sym, *next;
	int errors = 0;
	int ret;

	if ((file = pushfile(cfg->c_config, 1)) == NULL)
		hostapd_fatal("failed to open the main config file: %s\n",
		    cfg->c_config);
	topfile = file;

	/* Init tables and data structures */
	TAILQ_INIT(&cfg->c_apmes);
	TAILQ_INIT(&cfg->c_tables);
	TAILQ_INIT(&cfg->c_frames);
	cfg->c_iapp.i_multicast.sin_addr.s_addr = INADDR_ANY;
	cfg->c_iapp.i_flags = HOSTAPD_IAPP_F_DEFAULT;
	cfg->c_iapp.i_ttl = IP_DEFAULT_MULTICAST_TTL;
	cfg->c_apme_hopdelay.tv_sec = HOSTAPD_HOPPER_MDELAY / 1000;
	cfg->c_apme_hopdelay.tv_usec = (HOSTAPD_HOPPER_MDELAY % 1000) * 1000;

	ret = yyparse();
	errors = file->errors;
	popfile();

	/* Free macros and check which have not been used. */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if (!sym->used)
			hostapd_log(HOSTAPD_LOG_VERBOSE,
			    "warning: macro '%s' not used", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	return (errors ? EINVAL : ret);
}

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*msg;

	file->errors++;

	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap) == -1)
		hostapd_fatal("yyerror vasprintf");
	va_end(ap);
	fprintf(stderr, "%s:%d: %s\n", file->name, yylval.lineno, msg);
	fflush(stderr);
	free(msg);

	return (0);
}
