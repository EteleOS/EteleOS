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
#line 1 "gram.y"

/*	$OpenBSD: gram.y,v 1.25 2021/11/28 19:26:03 deraadt Exp $	*/
/*	$NetBSD: gram.y,v 1.14 1997/02/02 21:12:32 thorpej Exp $	*/

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)gram.y	8.1 (Berkeley) 6/6/93
 */

#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "config.h"
#include "sem.h"

#define	FORMAT(n) ((n) > -10 && (n) < 10 ? "%d" : "0x%x")

#define	stop(s)	error(s), exit(1)

int	include(const char *, int);
void	yyerror(const char *);
int	yylex(void);

static	struct	config conf;	/* at most one active at a time */

/* the following is used to recover nvlist space after errors */
static	struct	nvlist *alloc[1000];
static	int	adepth;
#define	new0(n,s,p,i,x)	(alloc[adepth++] = newnv(n, s, p, i, x))
#define	new_n(n)	new0(n, NULL, NULL, 0, NULL)
#define	new_nx(n, x)	new0(n, NULL, NULL, 0, x)
#define	new_ns(n, s)	new0(n, s, NULL, 0, NULL)
#define	new_si(s, i)	new0(NULL, s, NULL, i, NULL)
#define	new_nsi(n,s,i)	new0(n, s, NULL, i, NULL)
#define	new_np(n, p)	new0(n, NULL, p, 0, NULL)
#define	new_s(s)	new0(NULL, s, NULL, 0, NULL)
#define	new_p(p)	new0(NULL, NULL, p, 0, NULL)
#define	new_px(p, x)	new0(NULL, NULL, p, 0, x)

#define	fx_atom(s)	new0(s, NULL, NULL, FX_ATOM, NULL)
#define	fx_not(e)	new0(NULL, NULL, NULL, FX_NOT, e)
#define	fx_and(e1, e2)	new0(NULL, NULL, e1, FX_AND, e2)
#define	fx_or(e1, e2)	new0(NULL, NULL, e1, FX_OR, e2)

static	void	cleanup(void);
static	void	setmachine(const char *, const char *);
static	void	check_maxpart(void);


#line 160 "y.tab.c"

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
    AND = 258,                     /* AND  */
    AT = 259,                      /* AT  */
    ATTACH = 260,                  /* ATTACH  */
    BUILD = 261,                   /* BUILD  */
    COMPILE_WITH = 262,            /* COMPILE_WITH  */
    CONFIG = 263,                  /* CONFIG  */
    DEFINE = 264,                  /* DEFINE  */
    DEFOPT = 265,                  /* DEFOPT  */
    DEVICE = 266,                  /* DEVICE  */
    DISABLE = 267,                 /* DISABLE  */
    DUMPS = 268,                   /* DUMPS  */
    ENDFILE = 269,                 /* ENDFILE  */
    XFILE = 270,                   /* XFILE  */
    XOBJECT = 271,                 /* XOBJECT  */
    FLAGS = 272,                   /* FLAGS  */
    INCLUDE = 273,                 /* INCLUDE  */
    XMACHINE = 274,                /* XMACHINE  */
    MAJOR = 275,                   /* MAJOR  */
    MAKEOPTIONS = 276,             /* MAKEOPTIONS  */
    MAXUSERS = 277,                /* MAXUSERS  */
    MAXPARTITIONS = 278,           /* MAXPARTITIONS  */
    MINOR = 279,                   /* MINOR  */
    ON = 280,                      /* ON  */
    OPTIONS = 281,                 /* OPTIONS  */
    PSEUDO_DEVICE = 282,           /* PSEUDO_DEVICE  */
    ROOT = 283,                    /* ROOT  */
    SOURCE = 284,                  /* SOURCE  */
    SWAP = 285,                    /* SWAP  */
    WITH = 286,                    /* WITH  */
    NEEDS_COUNT = 287,             /* NEEDS_COUNT  */
    NEEDS_FLAG = 288,              /* NEEDS_FLAG  */
    RMOPTIONS = 289,               /* RMOPTIONS  */
    ENABLE = 290,                  /* ENABLE  */
    NUMBER = 291,                  /* NUMBER  */
    PATHNAME = 292,                /* PATHNAME  */
    WORD = 293,                    /* WORD  */
    EMPTY = 294                    /* EMPTY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define AND 258
#define AT 259
#define ATTACH 260
#define BUILD 261
#define COMPILE_WITH 262
#define CONFIG 263
#define DEFINE 264
#define DEFOPT 265
#define DEVICE 266
#define DISABLE 267
#define DUMPS 268
#define ENDFILE 269
#define XFILE 270
#define XOBJECT 271
#define FLAGS 272
#define INCLUDE 273
#define XMACHINE 274
#define MAJOR 275
#define MAKEOPTIONS 276
#define MAXUSERS 277
#define MAXPARTITIONS 278
#define MINOR 279
#define ON 280
#define OPTIONS 281
#define PSEUDO_DEVICE 282
#define ROOT 283
#define SOURCE 284
#define SWAP 285
#define WITH 286
#define NEEDS_COUNT 287
#define NEEDS_FLAG 288
#define RMOPTIONS 289
#define ENABLE 290
#define NUMBER 291
#define PATHNAME 292
#define WORD 293
#define EMPTY 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 90 "gram.y"

	struct	attr *attr;
	struct	devbase *devb;
	struct	deva *deva;
	struct	nvlist *list;
	const char *str;
	int	val;

#line 300 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


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
  YYSYMBOL_AND = 3,                        /* AND  */
  YYSYMBOL_AT = 4,                         /* AT  */
  YYSYMBOL_ATTACH = 5,                     /* ATTACH  */
  YYSYMBOL_BUILD = 6,                      /* BUILD  */
  YYSYMBOL_COMPILE_WITH = 7,               /* COMPILE_WITH  */
  YYSYMBOL_CONFIG = 8,                     /* CONFIG  */
  YYSYMBOL_DEFINE = 9,                     /* DEFINE  */
  YYSYMBOL_DEFOPT = 10,                    /* DEFOPT  */
  YYSYMBOL_DEVICE = 11,                    /* DEVICE  */
  YYSYMBOL_DISABLE = 12,                   /* DISABLE  */
  YYSYMBOL_DUMPS = 13,                     /* DUMPS  */
  YYSYMBOL_ENDFILE = 14,                   /* ENDFILE  */
  YYSYMBOL_XFILE = 15,                     /* XFILE  */
  YYSYMBOL_XOBJECT = 16,                   /* XOBJECT  */
  YYSYMBOL_FLAGS = 17,                     /* FLAGS  */
  YYSYMBOL_INCLUDE = 18,                   /* INCLUDE  */
  YYSYMBOL_XMACHINE = 19,                  /* XMACHINE  */
  YYSYMBOL_MAJOR = 20,                     /* MAJOR  */
  YYSYMBOL_MAKEOPTIONS = 21,               /* MAKEOPTIONS  */
  YYSYMBOL_MAXUSERS = 22,                  /* MAXUSERS  */
  YYSYMBOL_MAXPARTITIONS = 23,             /* MAXPARTITIONS  */
  YYSYMBOL_MINOR = 24,                     /* MINOR  */
  YYSYMBOL_ON = 25,                        /* ON  */
  YYSYMBOL_OPTIONS = 26,                   /* OPTIONS  */
  YYSYMBOL_PSEUDO_DEVICE = 27,             /* PSEUDO_DEVICE  */
  YYSYMBOL_ROOT = 28,                      /* ROOT  */
  YYSYMBOL_SOURCE = 29,                    /* SOURCE  */
  YYSYMBOL_SWAP = 30,                      /* SWAP  */
  YYSYMBOL_WITH = 31,                      /* WITH  */
  YYSYMBOL_NEEDS_COUNT = 32,               /* NEEDS_COUNT  */
  YYSYMBOL_NEEDS_FLAG = 33,                /* NEEDS_FLAG  */
  YYSYMBOL_RMOPTIONS = 34,                 /* RMOPTIONS  */
  YYSYMBOL_ENABLE = 35,                    /* ENABLE  */
  YYSYMBOL_NUMBER = 36,                    /* NUMBER  */
  YYSYMBOL_PATHNAME = 37,                  /* PATHNAME  */
  YYSYMBOL_WORD = 38,                      /* WORD  */
  YYSYMBOL_EMPTY = 39,                     /* EMPTY  */
  YYSYMBOL_40_ = 40,                       /* '|'  */
  YYSYMBOL_41_ = 41,                       /* '&'  */
  YYSYMBOL_42_n_ = 42,                     /* '\n'  */
  YYSYMBOL_43_ = 43,                       /* '!'  */
  YYSYMBOL_44_ = 44,                       /* '('  */
  YYSYMBOL_45_ = 45,                       /* ')'  */
  YYSYMBOL_46_ = 46,                       /* '{'  */
  YYSYMBOL_47_ = 47,                       /* '}'  */
  YYSYMBOL_48_ = 48,                       /* ','  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* '='  */
  YYSYMBOL_52_ = 52,                       /* '-'  */
  YYSYMBOL_53_ = 53,                       /* ':'  */
  YYSYMBOL_54_ = 54,                       /* '*'  */
  YYSYMBOL_55_ = 55,                       /* '?'  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_Configuration = 57,             /* Configuration  */
  YYSYMBOL_58_1 = 58,                      /* $@1  */
  YYSYMBOL_topthings = 59,                 /* topthings  */
  YYSYMBOL_topthing = 60,                  /* topthing  */
  YYSYMBOL_machine_spec = 61,              /* machine_spec  */
  YYSYMBOL_dev_eof = 62,                   /* dev_eof  */
  YYSYMBOL_pathnames = 63,                 /* pathnames  */
  YYSYMBOL_file = 64,                      /* file  */
  YYSYMBOL_object = 65,                    /* object  */
  YYSYMBOL_fopts = 66,                     /* fopts  */
  YYSYMBOL_fexpr = 67,                     /* fexpr  */
  YYSYMBOL_fatom = 68,                     /* fatom  */
  YYSYMBOL_fflgs = 69,                     /* fflgs  */
  YYSYMBOL_fflag = 70,                     /* fflag  */
  YYSYMBOL_oflgs = 71,                     /* oflgs  */
  YYSYMBOL_oflag = 72,                     /* oflag  */
  YYSYMBOL_rule = 73,                      /* rule  */
  YYSYMBOL_include = 74,                   /* include  */
  YYSYMBOL_dev_defs = 75,                  /* dev_defs  */
  YYSYMBOL_dev_def = 76,                   /* dev_def  */
  YYSYMBOL_one_def = 77,                   /* one_def  */
  YYSYMBOL_disable = 78,                   /* disable  */
  YYSYMBOL_atlist = 79,                    /* atlist  */
  YYSYMBOL_atname = 80,                    /* atname  */
  YYSYMBOL_devbase = 81,                   /* devbase  */
  YYSYMBOL_devattach_opt = 82,             /* devattach_opt  */
  YYSYMBOL_interface_opt = 83,             /* interface_opt  */
  YYSYMBOL_loclist_opt = 84,               /* loclist_opt  */
  YYSYMBOL_loclist = 85,                   /* loclist  */
  YYSYMBOL_locdef = 86,                    /* locdef  */
  YYSYMBOL_locdefault = 87,                /* locdefault  */
  YYSYMBOL_value = 88,                     /* value  */
  YYSYMBOL_signed_number = 89,             /* signed_number  */
  YYSYMBOL_attrs_opt = 90,                 /* attrs_opt  */
  YYSYMBOL_attrs = 91,                     /* attrs  */
  YYSYMBOL_attr = 92,                      /* attr  */
  YYSYMBOL_majorlist = 93,                 /* majorlist  */
  YYSYMBOL_majordef = 94,                  /* majordef  */
  YYSYMBOL_specs = 95,                     /* specs  */
  YYSYMBOL_spec = 96,                      /* spec  */
  YYSYMBOL_config_spec = 97,               /* config_spec  */
  YYSYMBOL_mkopt_list = 98,                /* mkopt_list  */
  YYSYMBOL_mkoption = 99,                  /* mkoption  */
  YYSYMBOL_opt_list = 100,                 /* opt_list  */
  YYSYMBOL_ropt_list = 101,                /* ropt_list  */
  YYSYMBOL_option = 102,                   /* option  */
  YYSYMBOL_conf = 103,                     /* conf  */
  YYSYMBOL_sysparam_list = 104,            /* sysparam_list  */
  YYSYMBOL_sysparam = 105,                 /* sysparam  */
  YYSYMBOL_swapdev_list = 106,             /* swapdev_list  */
  YYSYMBOL_dev_spec = 107,                 /* dev_spec  */
  YYSYMBOL_major_minor = 108,              /* major_minor  */
  YYSYMBOL_on_opt = 109,                   /* on_opt  */
  YYSYMBOL_npseudo = 110,                  /* npseudo  */
  YYSYMBOL_device_instance = 111,          /* device_instance  */
  YYSYMBOL_attachment = 112,               /* attachment  */
  YYSYMBOL_locators = 113,                 /* locators  */
  YYSYMBOL_locator = 114,                  /* locator  */
  YYSYMBOL_flags_opt = 115                 /* flags_opt  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  134
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  222

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      42,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,     2,     2,     2,    41,     2,
      44,    45,    54,     2,    48,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,     2,
       2,    51,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,    40,    47,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   143,   152,   152,   156,   157,   158,   159,
     162,   163,   164,   167,   170,   171,   177,   180,   184,   185,
     188,   189,   190,   191,   192,   195,   198,   199,   202,   203,
     206,   207,   210,   213,   214,   217,   224,   224,   228,   229,
     230,   233,   234,   235,   236,   237,   238,   240,   242,   243,
     244,   245,   248,   249,   252,   253,   256,   257,   260,   263,
     264,   267,   268,   271,   272,   276,   277,   281,   282,   283,
     286,   289,   290,   291,   300,   301,   304,   305,   308,   309,
     312,   315,   316,   319,   327,   327,   331,   332,   333,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     350,   351,   354,   357,   358,   361,   362,   365,   366,   369,
     376,   377,   380,   381,   382,   385,   386,   389,   390,   393,
     396,   396,   399,   400,   403,   404,   407,   408,   409,   412,
     413,   416,   417,   420,   421
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
  "\"end of file\"", "error", "\"invalid token\"", "AND", "AT", "ATTACH",
  "BUILD", "COMPILE_WITH", "CONFIG", "DEFINE", "DEFOPT", "DEVICE",
  "DISABLE", "DUMPS", "ENDFILE", "XFILE", "XOBJECT", "FLAGS", "INCLUDE",
  "XMACHINE", "MAJOR", "MAKEOPTIONS", "MAXUSERS", "MAXPARTITIONS", "MINOR",
  "ON", "OPTIONS", "PSEUDO_DEVICE", "ROOT", "SOURCE", "SWAP", "WITH",
  "NEEDS_COUNT", "NEEDS_FLAG", "RMOPTIONS", "ENABLE", "NUMBER", "PATHNAME",
  "WORD", "EMPTY", "'|'", "'&'", "'\\n'", "'!'", "'('", "')'", "'{'",
  "'}'", "','", "'['", "']'", "'='", "'-'", "':'", "'*'", "'?'", "$accept",
  "Configuration", "$@1", "topthings", "topthing", "machine_spec",
  "dev_eof", "pathnames", "file", "object", "fopts", "fexpr", "fatom",
  "fflgs", "fflag", "oflgs", "oflag", "rule", "include", "dev_defs",
  "dev_def", "one_def", "disable", "atlist", "atname", "devbase",
  "devattach_opt", "interface_opt", "loclist_opt", "loclist", "locdef",
  "locdefault", "value", "signed_number", "attrs_opt", "attrs", "attr",
  "majorlist", "majordef", "specs", "spec", "config_spec", "mkopt_list",
  "mkoption", "opt_list", "ropt_list", "option", "conf", "sysparam_list",
  "sysparam", "swapdev_list", "dev_spec", "major_minor", "on_opt",
  "npseudo", "device_instance", "attachment", "locators", "locator",
  "flags_opt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-150)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -150,     9,    23,  -150,  -150,   -34,   -20,    25,    34,  -150,
    -150,  -150,    26,    38,  -150,    59,    64,    39,  -150,  -150,
      65,  -150,  -150,    66,    71,    72,    73,    71,  -150,    52,
      75,    67,    78,    79,    71,  -150,  -150,  -150,  -150,  -150,
    -150,    74,  -150,  -150,  -150,   113,    76,  -150,    76,  -150,
      47,    50,    71,    82,  -150,    68,    39,  -150,    44,   -30,
    -150,    68,  -150,    83,    81,    50,  -150,   -24,  -150,  -150,
      77,    51,  -150,    87,    86,  -150,  -150,  -150,  -150,    29,
    -150,    80,    88,    85,  -150,    89,  -150,  -150,  -150,    55,
       3,    50,    50,    92,    91,  -150,    71,  -150,  -150,    93,
    -150,    39,    95,    44,    68,    40,  -150,    80,  -150,   -30,
    -150,    96,  -150,  -150,  -150,  -150,    94,  -150,  -150,  -150,
    -150,  -150,    86,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
     100,  -150,  -150,    90,  -150,  -150,  -150,  -150,  -150,  -150,
       5,    97,   104,   105,   108,   107,   109,   110,    98,  -150,
    -150,  -150,  -150,  -150,   111,   125,  -150,  -150,    45,    99,
     101,  -150,  -150,   103,   112,  -150,   115,  -150,   114,  -150,
    -150,    46,   121,   121,   121,    45,  -150,    40,   105,    40,
     107,  -150,   118,   117,  -150,   102,     2,  -150,    18,    18,
      18,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,   120,  -150,  -150,  -150,  -150,  -150,   155,   -13,
     135,    18,   127,    31,  -150,  -150,   128,  -150,  -150,  -150,
    -150,  -150
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     1,    12,     0,     0,     0,     0,     9,
       4,    37,     0,     0,    35,     0,     0,     0,     8,     7,
       0,    10,     6,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,     0,    39,    37,    41,    42,    43,
      36,     0,    11,    40,    58,     0,    62,    45,    62,    14,
      19,    19,     0,     0,    49,    77,     0,    38,     0,    64,
      44,    77,    25,     0,     0,     0,    27,    18,    20,    31,
       0,     0,    82,     0,     0,    50,    37,    57,    56,    60,
      55,    68,     0,     0,    63,    66,    46,    15,    21,     0,
      34,     0,     0,    17,     0,    51,     0,    48,    80,    76,
      79,     0,     0,     0,    77,     0,    67,     0,    61,     0,
      24,     0,    28,    29,    26,    16,    23,    22,    32,    30,
      83,    81,     0,     2,    59,    54,    47,    74,    71,    72,
       0,    70,    73,     0,    65,    33,    78,    85,    75,    69,
       0,     0,     0,     0,     0,     0,     0,     0,   125,    87,
      89,    90,    91,    84,     0,     0,    88,   109,     0,     0,
      94,   101,    95,   107,    92,   104,   123,   106,    93,   124,
      86,     0,   121,   121,   121,    96,   111,     0,     0,     0,
       0,   122,    53,     0,   126,   128,    53,   120,     0,     0,
       0,   110,   102,   100,   108,   103,    52,    97,   105,   127,
      98,   130,     0,   117,   114,   118,   112,   113,   116,   134,
       0,     0,     0,     0,   129,    99,     0,   115,   133,   132,
     131,   119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -150,  -150,  -150,  -150,  -150,  -150,   -55,  -150,    21,    27,
     119,   -58,   116,  -150,  -150,  -150,  -150,  -150,    -2,   -25,
    -150,  -150,   -21,  -150,    63,   -12,  -150,   123,  -150,    60,
    -150,    61,  -149,  -150,   -59,  -150,    53,  -150,   106,  -150,
    -150,  -150,  -150,    -6,  -150,  -150,    -7,  -150,  -150,    -1,
     -35,   -86,  -150,   -69,  -150,  -150,  -150,  -150,  -150,  -150
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,   137,     2,    10,    11,    36,    50,    37,    38,
      66,    67,    68,    90,   114,    93,   119,   115,    39,    17,
      40,    41,   197,    79,    80,    70,   104,    60,    83,    84,
      85,   106,   131,   132,    75,    99,   100,    71,    72,   140,
     153,   154,   160,   161,   164,   168,   165,   158,   175,   176,
     207,   208,   205,   188,   182,   155,   186,   209,   214,   215
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      12,    76,    86,    13,   212,    -3,   141,    89,    81,     3,
     111,    56,    45,   142,   196,    48,    91,    92,    14,    82,
      29,    30,    55,     6,     4,   213,   143,   144,   192,     5,
     194,   145,   146,   116,   117,   112,   113,   200,   202,   147,
      23,     6,     7,   148,    24,   126,   123,   149,    25,    26,
      27,   101,     8,    28,    29,    30,   203,     6,   172,    31,
     102,    32,    33,    15,   220,     9,    34,   127,    18,   128,
     129,    16,    77,   173,   184,   174,   127,   103,   128,   129,
      19,    35,    78,   130,   185,    62,   219,    63,    62,    49,
      64,    65,   130,    64,    65,    91,    92,    20,    95,    96,
     110,    21,   204,   206,   189,   190,    22,    42,    43,    44,
      46,    47,    51,    52,    53,    54,    57,    58,    73,    62,
      87,    74,    59,    97,    98,   118,   107,   120,    94,   171,
     196,   105,   108,   124,   135,    92,   138,   109,   152,   156,
     139,   122,   157,   159,   162,   163,   187,   166,   167,   178,
     177,   181,   169,   170,   179,   198,   210,   199,   211,   216,
     180,   150,   183,   218,   221,   201,   125,   151,   133,   134,
      69,    61,   193,   195,   191,   136,   217,     0,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121
};

static const yytype_int16 yycheck[] =
{
       2,    56,    61,    37,    17,     0,     1,    65,    38,     0,
       7,    36,    24,     8,    12,    27,    40,    41,    38,    49,
      15,    16,    34,    18,     1,    38,    21,    22,   177,     6,
     179,    26,    27,    91,    92,    32,    33,    35,    20,    34,
       1,    18,    19,    38,     5,   104,   101,    42,     9,    10,
      11,    76,    29,    14,    15,    16,    38,    18,    13,    20,
      31,    22,    23,    38,   213,    42,    27,    36,    42,    38,
      39,    37,    28,    28,    28,    30,    36,    48,    38,    39,
      42,    42,    38,    52,    38,    38,    55,    40,    38,    37,
      43,    44,    52,    43,    44,    40,    41,    38,    47,    48,
      45,    42,   188,   189,   173,   174,    42,    42,    42,    38,
      38,    38,    37,    46,    36,    36,    42,     4,    36,    38,
      37,    53,    46,    36,    38,    33,    38,    36,    51,     4,
      12,    51,    47,    38,    38,    41,    36,    48,   140,    42,
      50,    48,    38,    38,    36,    38,    25,    38,    38,    48,
      51,    36,    54,    42,    51,    38,    36,    55,     3,    24,
      48,   140,    48,    36,    36,   186,   103,   140,   107,   109,
      51,    48,   178,   180,   175,   122,   211,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    57,    59,     0,     1,     6,    18,    19,    29,    42,
      60,    61,    74,    37,    38,    38,    37,    75,    42,    42,
      38,    42,    42,     1,     5,     9,    10,    11,    14,    15,
      16,    20,    22,    23,    27,    42,    62,    64,    65,    74,
      76,    77,    42,    42,    38,    81,    38,    38,    81,    37,
      63,    37,    46,    36,    36,    81,    75,    42,     4,    46,
      83,    83,    38,    40,    43,    44,    66,    67,    68,    66,
      81,    93,    94,    36,    53,    90,    62,    28,    38,    79,
      80,    38,    49,    84,    85,    86,    90,    37,    68,    67,
      69,    40,    41,    71,    51,    47,    48,    36,    38,    91,
      92,    75,    31,    48,    82,    51,    87,    38,    47,    48,
      45,     7,    32,    33,    70,    73,    67,    67,    33,    72,
      36,    94,    48,    62,    38,    80,    90,    36,    38,    39,
      52,    88,    89,    87,    85,    38,    92,    58,    36,    50,
      95,     1,     8,    21,    22,    26,    27,    34,    38,    42,
      64,    65,    74,    96,    97,   111,    42,    38,   103,    38,
      98,    99,    36,    38,   100,   102,    38,    38,   101,    54,
      42,     4,    13,    28,    30,   104,   105,    51,    48,    51,
      48,    36,   110,    48,    28,    38,   112,    25,   109,   109,
     109,   105,    88,    99,    88,   102,    12,    78,    38,    55,
      35,    78,    20,    38,   107,   108,   107,   106,   107,   113,
      36,     3,    17,    38,   114,   115,    24,   106,    36,    55,
      88,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    58,    57,    59,    59,    60,    60,    60,    60,
      61,    61,    61,    62,    63,    63,    64,    65,    66,    66,
      67,    67,    67,    67,    67,    68,    69,    69,    70,    70,
      71,    71,    72,    73,    73,    74,    75,    75,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    78,    79,    79,    80,    80,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    86,
      87,    88,    88,    88,    89,    89,    90,    90,    91,    91,
      92,    93,    93,    94,    95,    95,    96,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      98,    98,    99,   100,   100,   101,   101,   102,   102,   103,
     104,   104,   105,   105,   105,   106,   106,   107,   107,   108,
     109,   109,   110,   110,   111,   111,   112,   112,   112,   113,
     113,   114,   114,   115,   115
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,    10,     2,     0,     3,     3,     2,     1,
       3,     4,     1,     1,     1,     3,     5,     4,     1,     0,
       1,     2,     3,     3,     3,     1,     2,     0,     1,     1,
       2,     0,     1,     2,     0,     2,     2,     0,     2,     1,
       2,     1,     1,     1,     3,     2,     4,     6,     4,     2,
       3,     4,     1,     0,     3,     1,     1,     1,     1,     2,
       0,     3,     0,     1,     0,     3,     1,     2,     1,     4,
       2,     1,     1,     1,     1,     2,     2,     0,     3,     1,
       1,     3,     1,     3,     2,     0,     2,     1,     2,     1,
       1,     1,     2,     2,     2,     2,     3,     4,     4,     6,
       3,     1,     3,     3,     1,     3,     1,     1,     3,     1,
       2,     1,     3,     3,     3,     3,     1,     1,     1,     4,
       1,     0,     1,     0,     2,     1,     1,     2,     1,     2,
       0,     2,     2,     2,     0
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
  case 2: /* $@1: %empty  */
#line 148 "gram.y"
                                        { check_maxpart(); }
#line 1556 "y.tab.c"
    break;

  case 6: /* topthing: SOURCE PATHNAME '\n'  */
#line 156 "gram.y"
                                        { if (!srcdir) srcdir = (yyvsp[-1].str); }
#line 1562 "y.tab.c"
    break;

  case 7: /* topthing: BUILD PATHNAME '\n'  */
#line 157 "gram.y"
                                        { if (!builddir) builddir = (yyvsp[-1].str); }
#line 1568 "y.tab.c"
    break;

  case 10: /* machine_spec: XMACHINE WORD '\n'  */
#line 162 "gram.y"
                                        { setmachine((yyvsp[-1].str),NULL); }
#line 1574 "y.tab.c"
    break;

  case 11: /* machine_spec: XMACHINE WORD WORD '\n'  */
#line 163 "gram.y"
                                        { setmachine((yyvsp[-2].str),(yyvsp[-1].str)); }
#line 1580 "y.tab.c"
    break;

  case 12: /* machine_spec: error  */
#line 164 "gram.y"
              { stop("cannot proceed without machine specifier"); }
#line 1586 "y.tab.c"
    break;

  case 13: /* dev_eof: ENDFILE  */
#line 167 "gram.y"
                                        { enddefs(); checkfiles(); }
#line 1592 "y.tab.c"
    break;

  case 14: /* pathnames: PATHNAME  */
#line 170 "gram.y"
                                        { (yyval.list) = new_nsi((yyvsp[0].str), NULL, 0); }
#line 1598 "y.tab.c"
    break;

  case 15: /* pathnames: pathnames '|' PATHNAME  */
#line 171 "gram.y"
                                        { ((yyval.list) = (yyvsp[-2].list))->nv_next = new_nsi((yyvsp[0].str), NULL, 0); }
#line 1604 "y.tab.c"
    break;

  case 16: /* file: XFILE pathnames fopts fflgs rule  */
#line 177 "gram.y"
                                         { addfile((yyvsp[-3].list), (yyvsp[-2].list), (yyvsp[-1].val), (yyvsp[0].str)); }
#line 1610 "y.tab.c"
    break;

  case 17: /* object: XOBJECT PATHNAME fopts oflgs  */
#line 180 "gram.y"
                                        { addobject((yyvsp[-2].str), (yyvsp[-1].list), (yyvsp[0].val)); }
#line 1616 "y.tab.c"
    break;

  case 18: /* fopts: fexpr  */
#line 184 "gram.y"
                                        { (yyval.list) = (yyvsp[0].list); }
#line 1622 "y.tab.c"
    break;

  case 19: /* fopts: %empty  */
#line 185 "gram.y"
                                        { (yyval.list) = NULL; }
#line 1628 "y.tab.c"
    break;

  case 20: /* fexpr: fatom  */
#line 188 "gram.y"
                                        { (yyval.list) = (yyvsp[0].list); }
#line 1634 "y.tab.c"
    break;

  case 21: /* fexpr: '!' fatom  */
#line 189 "gram.y"
                                        { (yyval.list) = fx_not((yyvsp[0].list)); }
#line 1640 "y.tab.c"
    break;

  case 22: /* fexpr: fexpr '&' fexpr  */
#line 190 "gram.y"
                                        { (yyval.list) = fx_and((yyvsp[-2].list), (yyvsp[0].list)); }
#line 1646 "y.tab.c"
    break;

  case 23: /* fexpr: fexpr '|' fexpr  */
#line 191 "gram.y"
                                        { (yyval.list) = fx_or((yyvsp[-2].list), (yyvsp[0].list)); }
#line 1652 "y.tab.c"
    break;

  case 24: /* fexpr: '(' fexpr ')'  */
#line 192 "gram.y"
                                        { (yyval.list) = (yyvsp[-1].list); }
#line 1658 "y.tab.c"
    break;

  case 25: /* fatom: WORD  */
#line 195 "gram.y"
                                        { (yyval.list) = fx_atom((yyvsp[0].str)); }
#line 1664 "y.tab.c"
    break;

  case 26: /* fflgs: fflgs fflag  */
#line 198 "gram.y"
                                        { (yyval.val) = (yyvsp[-1].val) | (yyvsp[0].val); }
#line 1670 "y.tab.c"
    break;

  case 27: /* fflgs: %empty  */
#line 199 "gram.y"
                                        { (yyval.val) = 0; }
#line 1676 "y.tab.c"
    break;

  case 28: /* fflag: NEEDS_COUNT  */
#line 202 "gram.y"
                                        { (yyval.val) = FI_NEEDSCOUNT; }
#line 1682 "y.tab.c"
    break;

  case 29: /* fflag: NEEDS_FLAG  */
#line 203 "gram.y"
                                        { (yyval.val) = FI_NEEDSFLAG; }
#line 1688 "y.tab.c"
    break;

  case 30: /* oflgs: oflgs oflag  */
#line 206 "gram.y"
                                        { (yyval.val) = (yyvsp[-1].val) | (yyvsp[0].val); }
#line 1694 "y.tab.c"
    break;

  case 31: /* oflgs: %empty  */
#line 207 "gram.y"
                                        { (yyval.val) = 0; }
#line 1700 "y.tab.c"
    break;

  case 32: /* oflag: NEEDS_FLAG  */
#line 210 "gram.y"
                                        { (yyval.val) = OI_NEEDSFLAG; }
#line 1706 "y.tab.c"
    break;

  case 33: /* rule: COMPILE_WITH WORD  */
#line 213 "gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 1712 "y.tab.c"
    break;

  case 34: /* rule: %empty  */
#line 214 "gram.y"
                                        { (yyval.str) = NULL; }
#line 1718 "y.tab.c"
    break;

  case 35: /* include: INCLUDE WORD  */
#line 217 "gram.y"
                                        { include((yyvsp[0].str), 0); }
#line 1724 "y.tab.c"
    break;

  case 38: /* dev_def: one_def '\n'  */
#line 228 "gram.y"
                                        { adepth = 0; }
#line 1730 "y.tab.c"
    break;

  case 40: /* dev_def: error '\n'  */
#line 230 "gram.y"
                                        { cleanup(); }
#line 1736 "y.tab.c"
    break;

  case 44: /* one_def: DEFINE WORD interface_opt  */
#line 236 "gram.y"
                                        { (void)defattr((yyvsp[-1].str), (yyvsp[0].list)); }
#line 1742 "y.tab.c"
    break;

  case 45: /* one_def: DEFOPT WORD  */
#line 237 "gram.y"
                                        { defoption((yyvsp[0].str)); }
#line 1748 "y.tab.c"
    break;

  case 46: /* one_def: DEVICE devbase interface_opt attrs_opt  */
#line 239 "gram.y"
                                        { defdev((yyvsp[-2].devb), 0, (yyvsp[-1].list), (yyvsp[0].list)); }
#line 1754 "y.tab.c"
    break;

  case 47: /* one_def: ATTACH devbase AT atlist devattach_opt attrs_opt  */
#line 241 "gram.y"
                                        { defdevattach((yyvsp[-1].deva), (yyvsp[-4].devb), (yyvsp[-2].list), (yyvsp[0].list)); }
#line 1760 "y.tab.c"
    break;

  case 48: /* one_def: MAXUSERS NUMBER NUMBER NUMBER  */
#line 242 "gram.y"
                                        { setdefmaxusers((yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1766 "y.tab.c"
    break;

  case 49: /* one_def: MAXPARTITIONS NUMBER  */
#line 243 "gram.y"
                                        { maxpartitions = (yyvsp[0].val); }
#line 1772 "y.tab.c"
    break;

  case 50: /* one_def: PSEUDO_DEVICE devbase attrs_opt  */
#line 244 "gram.y"
                                        { defdev((yyvsp[-1].devb),1,NULL,(yyvsp[0].list)); }
#line 1778 "y.tab.c"
    break;

  case 52: /* disable: DISABLE  */
#line 248 "gram.y"
                                        { (yyval.val) = 1; }
#line 1784 "y.tab.c"
    break;

  case 53: /* disable: %empty  */
#line 249 "gram.y"
                                        { (yyval.val) = 0; }
#line 1790 "y.tab.c"
    break;

  case 54: /* atlist: atlist ',' atname  */
#line 252 "gram.y"
                                        { (yyval.list) = new_nx((yyvsp[0].str), (yyvsp[-2].list)); }
#line 1796 "y.tab.c"
    break;

  case 55: /* atlist: atname  */
#line 253 "gram.y"
                                        { (yyval.list) = new_n((yyvsp[0].str)); }
#line 1802 "y.tab.c"
    break;

  case 56: /* atname: WORD  */
#line 256 "gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 1808 "y.tab.c"
    break;

  case 57: /* atname: ROOT  */
#line 257 "gram.y"
                                        { (yyval.str) = NULL; }
#line 1814 "y.tab.c"
    break;

  case 58: /* devbase: WORD  */
#line 260 "gram.y"
                                        { (yyval.devb) = getdevbase((char *)(yyvsp[0].str)); }
#line 1820 "y.tab.c"
    break;

  case 59: /* devattach_opt: WITH WORD  */
#line 263 "gram.y"
                                        { (yyval.deva) = getdevattach((yyvsp[0].str)); }
#line 1826 "y.tab.c"
    break;

  case 60: /* devattach_opt: %empty  */
#line 264 "gram.y"
                                        { (yyval.deva) = NULL; }
#line 1832 "y.tab.c"
    break;

  case 61: /* interface_opt: '{' loclist_opt '}'  */
#line 267 "gram.y"
                                        { (yyval.list) = new_nx("", (yyvsp[-1].list)); }
#line 1838 "y.tab.c"
    break;

  case 62: /* interface_opt: %empty  */
#line 268 "gram.y"
                                        { (yyval.list) = NULL; }
#line 1844 "y.tab.c"
    break;

  case 63: /* loclist_opt: loclist  */
#line 271 "gram.y"
                                        { (yyval.list) = (yyvsp[0].list); }
#line 1850 "y.tab.c"
    break;

  case 64: /* loclist_opt: %empty  */
#line 272 "gram.y"
                                        { (yyval.list) = NULL; }
#line 1856 "y.tab.c"
    break;

  case 65: /* loclist: locdef ',' loclist  */
#line 276 "gram.y"
                                        { ((yyval.list) = (yyvsp[-2].list))->nv_next = (yyvsp[0].list); }
#line 1862 "y.tab.c"
    break;

  case 66: /* loclist: locdef  */
#line 277 "gram.y"
                                        { (yyval.list) = (yyvsp[0].list); }
#line 1868 "y.tab.c"
    break;

  case 67: /* locdef: WORD locdefault  */
#line 281 "gram.y"
                                        { (yyval.list) = new_nsi((yyvsp[-1].str), (yyvsp[0].str), 0); }
#line 1874 "y.tab.c"
    break;

  case 68: /* locdef: WORD  */
#line 282 "gram.y"
                                        { (yyval.list) = new_nsi((yyvsp[0].str), NULL, 0); }
#line 1880 "y.tab.c"
    break;

  case 69: /* locdef: '[' WORD locdefault ']'  */
#line 283 "gram.y"
                                        { (yyval.list) = new_nsi((yyvsp[-2].str), (yyvsp[-1].str), 1); }
#line 1886 "y.tab.c"
    break;

  case 70: /* locdefault: '=' value  */
#line 286 "gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 1892 "y.tab.c"
    break;

  case 71: /* value: WORD  */
#line 289 "gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 1898 "y.tab.c"
    break;

  case 72: /* value: EMPTY  */
#line 290 "gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 1904 "y.tab.c"
    break;

  case 73: /* value: signed_number  */
#line 291 "gram.y"
                                        {
						char bf[40];

						(void)snprintf(bf, sizeof bf,
						    FORMAT((yyvsp[0].val)), (yyvsp[0].val));
						(yyval.str) = intern(bf);
					}
#line 1916 "y.tab.c"
    break;

  case 74: /* signed_number: NUMBER  */
#line 300 "gram.y"
                                        { (yyval.val) = (yyvsp[0].val); }
#line 1922 "y.tab.c"
    break;

  case 75: /* signed_number: '-' NUMBER  */
#line 301 "gram.y"
                                        { (yyval.val) = -(yyvsp[0].val); }
#line 1928 "y.tab.c"
    break;

  case 76: /* attrs_opt: ':' attrs  */
#line 304 "gram.y"
                                        { (yyval.list) = (yyvsp[0].list); }
#line 1934 "y.tab.c"
    break;

  case 77: /* attrs_opt: %empty  */
#line 305 "gram.y"
                                        { (yyval.list) = NULL; }
#line 1940 "y.tab.c"
    break;

  case 78: /* attrs: attrs ',' attr  */
#line 308 "gram.y"
                                        { (yyval.list) = new_px((yyvsp[0].attr), (yyvsp[-2].list)); }
#line 1946 "y.tab.c"
    break;

  case 79: /* attrs: attr  */
#line 309 "gram.y"
                                        { (yyval.list) = new_p((yyvsp[0].attr)); }
#line 1952 "y.tab.c"
    break;

  case 80: /* attr: WORD  */
#line 312 "gram.y"
                                        { (yyval.attr) = getattr((yyvsp[0].str)); }
#line 1958 "y.tab.c"
    break;

  case 83: /* majordef: devbase '=' NUMBER  */
#line 319 "gram.y"
                                        { setmajor((yyvsp[-2].devb), (yyvsp[0].val)); }
#line 1964 "y.tab.c"
    break;

  case 86: /* spec: config_spec '\n'  */
#line 331 "gram.y"
                                        { adepth = 0; }
#line 1970 "y.tab.c"
    break;

  case 88: /* spec: error '\n'  */
#line 333 "gram.y"
                                        { cleanup(); }
#line 1976 "y.tab.c"
    break;

  case 95: /* config_spec: MAXUSERS NUMBER  */
#line 342 "gram.y"
                                        { setmaxusers((yyvsp[0].val)); }
#line 1982 "y.tab.c"
    break;

  case 96: /* config_spec: CONFIG conf sysparam_list  */
#line 343 "gram.y"
                                        { addconf(&conf); }
#line 1988 "y.tab.c"
    break;

  case 97: /* config_spec: PSEUDO_DEVICE WORD npseudo disable  */
#line 344 "gram.y"
                                           { addpseudo((yyvsp[-2].str), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1994 "y.tab.c"
    break;

  case 98: /* config_spec: device_instance AT attachment ENABLE  */
#line 345 "gram.y"
                                             { enabledev((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 2000 "y.tab.c"
    break;

  case 99: /* config_spec: device_instance AT attachment disable locators flags_opt  */
#line 347 "gram.y"
                                        { adddev((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].list), (yyvsp[0].val), (yyvsp[-2].val)); }
#line 2006 "y.tab.c"
    break;

  case 102: /* mkoption: WORD '=' value  */
#line 354 "gram.y"
                                        { addmkoption((yyvsp[-2].str), (yyvsp[0].str)); }
#line 2012 "y.tab.c"
    break;

  case 105: /* ropt_list: ropt_list ',' WORD  */
#line 361 "gram.y"
                           { removeoption((yyvsp[0].str)); }
#line 2018 "y.tab.c"
    break;

  case 106: /* ropt_list: WORD  */
#line 362 "gram.y"
             { removeoption((yyvsp[0].str)); }
#line 2024 "y.tab.c"
    break;

  case 107: /* option: WORD  */
#line 365 "gram.y"
                                        { addoption((yyvsp[0].str), NULL); }
#line 2030 "y.tab.c"
    break;

  case 108: /* option: WORD '=' value  */
#line 366 "gram.y"
                                        { addoption((yyvsp[-2].str), (yyvsp[0].str)); }
#line 2036 "y.tab.c"
    break;

  case 109: /* conf: WORD  */
#line 369 "gram.y"
                                        { conf.cf_name = (yyvsp[0].str);
					    conf.cf_lineno = currentline();
					    conf.cf_root = NULL;
					    conf.cf_swap = NULL;
					    conf.cf_dump = NULL; }
#line 2046 "y.tab.c"
    break;

  case 112: /* sysparam: ROOT on_opt dev_spec  */
#line 380 "gram.y"
                                 { setconf(&conf.cf_root, "root", (yyvsp[0].list)); }
#line 2052 "y.tab.c"
    break;

  case 113: /* sysparam: SWAP on_opt swapdev_list  */
#line 381 "gram.y"
                                 { setconf(&conf.cf_swap, "swap", (yyvsp[0].list)); }
#line 2058 "y.tab.c"
    break;

  case 114: /* sysparam: DUMPS on_opt dev_spec  */
#line 382 "gram.y"
                                 { setconf(&conf.cf_dump, "dumps", (yyvsp[0].list)); }
#line 2064 "y.tab.c"
    break;

  case 115: /* swapdev_list: dev_spec AND swapdev_list  */
#line 385 "gram.y"
                                        { ((yyval.list) = (yyvsp[-2].list))->nv_next = (yyvsp[0].list); }
#line 2070 "y.tab.c"
    break;

  case 116: /* swapdev_list: dev_spec  */
#line 386 "gram.y"
                                        { (yyval.list) = (yyvsp[0].list); }
#line 2076 "y.tab.c"
    break;

  case 117: /* dev_spec: WORD  */
#line 389 "gram.y"
                                        { (yyval.list) = new_si((yyvsp[0].str), nodev); }
#line 2082 "y.tab.c"
    break;

  case 118: /* dev_spec: major_minor  */
#line 390 "gram.y"
                                        { (yyval.list) = new_si(NULL, (yyvsp[0].val)); }
#line 2088 "y.tab.c"
    break;

  case 119: /* major_minor: MAJOR NUMBER MINOR NUMBER  */
#line 393 "gram.y"
                                        { (yyval.val) = makedev((yyvsp[-2].val), (yyvsp[0].val)); }
#line 2094 "y.tab.c"
    break;

  case 122: /* npseudo: NUMBER  */
#line 399 "gram.y"
                                        { (yyval.val) = (yyvsp[0].val); }
#line 2100 "y.tab.c"
    break;

  case 123: /* npseudo: %empty  */
#line 400 "gram.y"
                                        { (yyval.val) = 1; }
#line 2106 "y.tab.c"
    break;

  case 124: /* device_instance: WORD '*'  */
#line 403 "gram.y"
                                        { (yyval.str) = starref((yyvsp[-1].str)); }
#line 2112 "y.tab.c"
    break;

  case 125: /* device_instance: WORD  */
#line 404 "gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 2118 "y.tab.c"
    break;

  case 126: /* attachment: ROOT  */
#line 407 "gram.y"
                                        { (yyval.str) = NULL; }
#line 2124 "y.tab.c"
    break;

  case 127: /* attachment: WORD '?'  */
#line 408 "gram.y"
                                        { (yyval.str) = wildref((yyvsp[-1].str)); }
#line 2130 "y.tab.c"
    break;

  case 128: /* attachment: WORD  */
#line 409 "gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 2136 "y.tab.c"
    break;

  case 129: /* locators: locators locator  */
#line 412 "gram.y"
                                        { ((yyval.list) = (yyvsp[0].list))->nv_next = (yyvsp[-1].list); }
#line 2142 "y.tab.c"
    break;

  case 130: /* locators: %empty  */
#line 413 "gram.y"
                                        { (yyval.list) = NULL; }
#line 2148 "y.tab.c"
    break;

  case 131: /* locator: WORD value  */
#line 416 "gram.y"
                                        { (yyval.list) = new_ns((yyvsp[-1].str), (yyvsp[0].str)); }
#line 2154 "y.tab.c"
    break;

  case 132: /* locator: WORD '?'  */
#line 417 "gram.y"
                                        { (yyval.list) = new_ns((yyvsp[-1].str), NULL); }
#line 2160 "y.tab.c"
    break;

  case 133: /* flags_opt: FLAGS NUMBER  */
#line 420 "gram.y"
                                        { (yyval.val) = (yyvsp[0].val); }
#line 2166 "y.tab.c"
    break;

  case 134: /* flags_opt: %empty  */
#line 421 "gram.y"
                                        { (yyval.val) = 0; }
#line 2172 "y.tab.c"
    break;


#line 2176 "y.tab.c"

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

#line 423 "gram.y"


void
yyerror(const char *s)
{

	error("%s", s);
}

/*
 * Cleanup procedure after syntax error: release any nvlists
 * allocated during parsing the current line.
 */
static void
cleanup(void)
{
	struct nvlist **np;
	int i;

	for (np = alloc, i = adepth; --i >= 0; np++)
		nvfree(*np);
	adepth = 0;
}

static void
setmachine(const char *mch, const char *mcharch)
{
	char buf[PATH_MAX];

	machine = mch;
	machinearch = mcharch;

	(void)snprintf(buf, sizeof buf, "arch/%s/conf/files.%s", machine, machine);
	if (include(buf, ENDFILE) != 0)
		exit(1);

	if (machinearch != NULL)
		(void)snprintf(buf, sizeof buf, "arch/%s/conf/files.%s",
		    machinearch, machinearch);
	else
		strlcpy(buf, _PATH_DEVNULL, sizeof buf);
	if (include(buf, ENDFILE) != 0)
		exit(1);

	if (include("conf/files", ENDFILE) != 0)
		exit(1);
}

static void
check_maxpart(void)
{
	if (maxpartitions <= 0) {
		stop("cannot proceed without maxpartitions specifier");
	}
}
