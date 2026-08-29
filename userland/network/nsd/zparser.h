/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ZPARSER_H_INCLUDED
# define YY_YY_ZPARSER_H_INCLUDED
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
    T_A = 258,                     /* T_A  */
    T_NS = 259,                    /* T_NS  */
    T_MX = 260,                    /* T_MX  */
    T_TXT = 261,                   /* T_TXT  */
    T_CNAME = 262,                 /* T_CNAME  */
    T_AAAA = 263,                  /* T_AAAA  */
    T_PTR = 264,                   /* T_PTR  */
    T_NXT = 265,                   /* T_NXT  */
    T_KEY = 266,                   /* T_KEY  */
    T_SOA = 267,                   /* T_SOA  */
    T_SIG = 268,                   /* T_SIG  */
    T_SRV = 269,                   /* T_SRV  */
    T_CERT = 270,                  /* T_CERT  */
    T_LOC = 271,                   /* T_LOC  */
    T_MD = 272,                    /* T_MD  */
    T_MF = 273,                    /* T_MF  */
    T_MB = 274,                    /* T_MB  */
    T_MG = 275,                    /* T_MG  */
    T_MR = 276,                    /* T_MR  */
    T_NULL = 277,                  /* T_NULL  */
    T_WKS = 278,                   /* T_WKS  */
    T_HINFO = 279,                 /* T_HINFO  */
    T_MINFO = 280,                 /* T_MINFO  */
    T_RP = 281,                    /* T_RP  */
    T_AFSDB = 282,                 /* T_AFSDB  */
    T_X25 = 283,                   /* T_X25  */
    T_ISDN = 284,                  /* T_ISDN  */
    T_RT = 285,                    /* T_RT  */
    T_NSAP = 286,                  /* T_NSAP  */
    T_NSAP_PTR = 287,              /* T_NSAP_PTR  */
    T_PX = 288,                    /* T_PX  */
    T_GPOS = 289,                  /* T_GPOS  */
    T_EID = 290,                   /* T_EID  */
    T_NIMLOC = 291,                /* T_NIMLOC  */
    T_ATMA = 292,                  /* T_ATMA  */
    T_NAPTR = 293,                 /* T_NAPTR  */
    T_KX = 294,                    /* T_KX  */
    T_A6 = 295,                    /* T_A6  */
    T_DNAME = 296,                 /* T_DNAME  */
    T_SINK = 297,                  /* T_SINK  */
    T_OPT = 298,                   /* T_OPT  */
    T_APL = 299,                   /* T_APL  */
    T_UINFO = 300,                 /* T_UINFO  */
    T_UID = 301,                   /* T_UID  */
    T_GID = 302,                   /* T_GID  */
    T_UNSPEC = 303,                /* T_UNSPEC  */
    T_TKEY = 304,                  /* T_TKEY  */
    T_TSIG = 305,                  /* T_TSIG  */
    T_IXFR = 306,                  /* T_IXFR  */
    T_AXFR = 307,                  /* T_AXFR  */
    T_MAILB = 308,                 /* T_MAILB  */
    T_MAILA = 309,                 /* T_MAILA  */
    T_DS = 310,                    /* T_DS  */
    T_DLV = 311,                   /* T_DLV  */
    T_SSHFP = 312,                 /* T_SSHFP  */
    T_RRSIG = 313,                 /* T_RRSIG  */
    T_NSEC = 314,                  /* T_NSEC  */
    T_DNSKEY = 315,                /* T_DNSKEY  */
    T_SPF = 316,                   /* T_SPF  */
    T_NSEC3 = 317,                 /* T_NSEC3  */
    T_IPSECKEY = 318,              /* T_IPSECKEY  */
    T_DHCID = 319,                 /* T_DHCID  */
    T_NSEC3PARAM = 320,            /* T_NSEC3PARAM  */
    T_TLSA = 321,                  /* T_TLSA  */
    T_URI = 322,                   /* T_URI  */
    T_NID = 323,                   /* T_NID  */
    T_L32 = 324,                   /* T_L32  */
    T_L64 = 325,                   /* T_L64  */
    T_LP = 326,                    /* T_LP  */
    T_EUI48 = 327,                 /* T_EUI48  */
    T_EUI64 = 328,                 /* T_EUI64  */
    T_CAA = 329,                   /* T_CAA  */
    T_CDS = 330,                   /* T_CDS  */
    T_CDNSKEY = 331,               /* T_CDNSKEY  */
    T_OPENPGPKEY = 332,            /* T_OPENPGPKEY  */
    T_CSYNC = 333,                 /* T_CSYNC  */
    T_ZONEMD = 334,                /* T_ZONEMD  */
    T_AVC = 335,                   /* T_AVC  */
    T_SMIMEA = 336,                /* T_SMIMEA  */
    T_SVCB = 337,                  /* T_SVCB  */
    T_HTTPS = 338,                 /* T_HTTPS  */
    DOLLAR_TTL = 339,              /* DOLLAR_TTL  */
    DOLLAR_ORIGIN = 340,           /* DOLLAR_ORIGIN  */
    NL = 341,                      /* NL  */
    SP = 342,                      /* SP  */
    QSTR = 343,                    /* QSTR  */
    STR = 344,                     /* STR  */
    PREV = 345,                    /* PREV  */
    BITLAB = 346,                  /* BITLAB  */
    T_TTL = 347,                   /* T_TTL  */
    T_RRCLASS = 348,               /* T_RRCLASS  */
    URR = 349,                     /* URR  */
    T_UTYPE = 350                  /* T_UTYPE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "zparser.y"

	domain_type	 *domain;
	const dname_type *dname;
	struct lex_data	  data;
	uint32_t	  ttl;
	uint16_t	  klass;
	uint16_t	  type;
	uint16_t	 *unknown;

#line 169 "zparser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ZPARSER_H_INCLUDED  */
