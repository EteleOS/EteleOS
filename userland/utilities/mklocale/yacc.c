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
#line 4 "yacc.y"

/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
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
 */

#include <sys/types.h>
#include <netinet/in.h>	/* Needed by <arpa/inet.h> on NetBSD 1.5. */
#include <arpa/inet.h>	/* Needed for htonl on POSIX systems. */

#include <err.h>
#include "locale/runetype.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "ldef.h"

const char	*locale_file = "<stdout>";

rune_map	maplower = { { 0, }, };
rune_map	mapupper = { { 0, }, };
rune_map	types = { { 0, }, };

_RuneLocale	new_locale = { { 0, }, };

rune_t	charsetbits = (rune_t)0x00000000;
#if 0
rune_t	charsetmask = (rune_t)0x0000007f;
#endif
rune_t	charsetmask = (rune_t)0xffffffff;

void set_map(rune_map *, rune_list *, u_int32_t);
void add_map(rune_map *, rune_list *, u_int32_t);

int		main(int, char *[]);
int		yyerror(const char *s);
void		*xmalloc(size_t sz);
u_int32_t	*xlalloc(size_t sz);
u_int32_t	*xrelalloc(u_int32_t *old, size_t sz);
void		dump_tables(void);
int		yyparse(void);
extern int	yylex(void);

#line 146 "y.tab.c"

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
    RUNE = 258,                    /* RUNE  */
    LBRK = 259,                    /* LBRK  */
    RBRK = 260,                    /* RBRK  */
    THRU = 261,                    /* THRU  */
    MAPLOWER = 262,                /* MAPLOWER  */
    MAPUPPER = 263,                /* MAPUPPER  */
    DIGITMAP = 264,                /* DIGITMAP  */
    LIST = 265,                    /* LIST  */
    VARIABLE = 266,                /* VARIABLE  */
    CHARSET = 267,                 /* CHARSET  */
    ENCODING = 268,                /* ENCODING  */
    INVALID = 269,                 /* INVALID  */
    STRING = 270                   /* STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define RUNE 258
#define LBRK 259
#define RBRK 260
#define THRU 261
#define MAPLOWER 262
#define MAPUPPER 263
#define DIGITMAP 264
#define LIST 265
#define VARIABLE 266
#define CHARSET 267
#define ENCODING 268
#define INVALID 269
#define STRING 270

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 79 "yacc.y"

    rune_t	rune;
    int		i;
    char	*str;

    rune_list	*list;

#line 237 "y.tab.c"

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
  YYSYMBOL_RUNE = 3,                       /* RUNE  */
  YYSYMBOL_LBRK = 4,                       /* LBRK  */
  YYSYMBOL_RBRK = 5,                       /* RBRK  */
  YYSYMBOL_THRU = 6,                       /* THRU  */
  YYSYMBOL_MAPLOWER = 7,                   /* MAPLOWER  */
  YYSYMBOL_MAPUPPER = 8,                   /* MAPUPPER  */
  YYSYMBOL_DIGITMAP = 9,                   /* DIGITMAP  */
  YYSYMBOL_LIST = 10,                      /* LIST  */
  YYSYMBOL_VARIABLE = 11,                  /* VARIABLE  */
  YYSYMBOL_CHARSET = 12,                   /* CHARSET  */
  YYSYMBOL_ENCODING = 13,                  /* ENCODING  */
  YYSYMBOL_INVALID = 14,                   /* INVALID  */
  YYSYMBOL_STRING = 15,                    /* STRING  */
  YYSYMBOL_16_ = 16,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 17,                  /* $accept  */
  YYSYMBOL_locale = 18,                    /* locale  */
  YYSYMBOL_table = 19,                     /* table  */
  YYSYMBOL_entry = 20,                     /* entry  */
  YYSYMBOL_list = 21,                      /* list  */
  YYSYMBOL_map = 22,                       /* map  */
  YYSYMBOL_mapignore = 23                  /* mapignore  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   70

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  17
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  27
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  66

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   270


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    16,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   107,   107,   108,   112,   113,   116,   118,   122,   124,
     126,   158,   160,   162,   164,   166,   170,   178,   186,   194,
     204,   212,   220,   228,   238,   239,   240,   241
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
  "\"end of file\"", "error", "\"invalid token\"", "RUNE", "LBRK", "RBRK",
  "THRU", "MAPLOWER", "MAPUPPER", "DIGITMAP", "LIST", "VARIABLE",
  "CHARSET", "ENCODING", "INVALID", "STRING", "':'", "$accept", "locale",
  "table", "entry", "list", "map", "mapignore", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-7)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-24)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -6,     5,     5,    19,    14,    -7,    -3,     9,    22,    26,
      -6,    -7,    24,    25,    25,    27,    28,    -7,    16,    30,
      31,    -7,    -7,    -7,    -7,    -7,     7,    32,     8,    33,
      34,    35,    -7,    23,    36,    12,    37,    40,    13,    -7,
      41,    -7,    15,    42,    43,    44,    29,    45,    46,    -7,
      48,    -7,    38,    49,    51,    47,    52,    50,    53,    56,
      -7,    55,    57,    59,    -7,    58
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     0,     0,     7,     0,     0,     0,     0,
       3,     4,     0,    13,    14,     0,     0,    15,    16,    12,
       8,    10,     6,    11,     1,     5,     0,     0,     0,     0,
       0,    18,     9,     0,     0,     0,     0,     0,     0,    17,
       0,    20,     0,     0,     0,    24,     0,     0,     0,    19,
       0,    21,     0,     0,    25,     0,     0,     0,     0,     0,
      22,     0,    26,     0,    23,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -7,    -7,    -7,    60,    -7,    18,    -7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     9,    10,    11,    19,    13,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      20,     1,     2,     3,     4,     5,     6,     7,     8,    12,
      33,    36,    21,    34,    37,    43,    47,    18,    44,    48,
      14,    16,    30,    15,    22,    23,    24,    26,    41,    27,
      28,    50,    29,    31,    32,    35,    38,    39,     0,    42,
       0,    40,    45,    46,    49,    53,    52,    51,   -20,    55,
      54,    56,    58,    61,    57,   -21,     0,    60,    62,    63,
      64,   -22,   -23,    59,    65,     0,     0,     0,     0,     0,
      25
};

static const yytype_int8 yycheck[] =
{
       3,     7,     8,     9,    10,    11,    12,    13,    14,     4,
       3,     3,    15,     6,     6,     3,     3,     3,     6,     6,
       2,     3,     6,     4,    15,     3,     0,     3,     5,     4,
       3,    16,     4,     3,     3,     3,     3,     3,    -1,     3,
      -1,     6,     5,     3,     3,    16,     3,     5,     4,     3,
       5,     3,     3,     3,    16,     4,    -1,     5,     5,     3,
       5,     4,     4,    16,     5,    -1,    -1,    -1,    -1,    -1,
      10
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    10,    11,    12,    13,    14,    18,
      19,    20,     4,    22,    22,     4,    22,    23,     3,    21,
       3,    15,    15,     3,     0,    20,     3,     4,     3,     4,
       6,     3,     3,     3,     6,     3,     3,     6,     3,     3,
       6,     5,     3,     3,     6,     5,     3,     3,     6,     3,
      16,     5,     3,    16,     5,     3,     3,    16,     3,    16,
       5,     3,     5,     3,     5,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    17,    18,    18,    19,    19,    20,    20,    20,    20,
      20,    20,    20,    20,    20,    20,    21,    21,    21,    21,
      22,    22,    22,    22,    23,    23,    23,    23
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     2,     1,     2,     3,
       2,     2,     2,     2,     2,     2,     1,     3,     2,     4,
       4,     5,     7,     8,     4,     5,     7,     8
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
  case 3: /* locale: table  */
#line 109 "yacc.y"
                { dump_tables(); }
#line 1267 "y.tab.c"
    break;

  case 6: /* entry: ENCODING STRING  */
#line 117 "yacc.y"
                { strncpy(new_locale.rl_encoding, (yyvsp[0].str), sizeof(new_locale.rl_encoding)); }
#line 1273 "y.tab.c"
    break;

  case 7: /* entry: VARIABLE  */
#line 119 "yacc.y"
                { new_locale.rl_variable_len = strlen((yyvsp[0].str)) + 1;
		  new_locale.rl_variable = strdup((yyvsp[0].str));
		}
#line 1281 "y.tab.c"
    break;

  case 8: /* entry: CHARSET RUNE  */
#line 123 "yacc.y"
                { charsetbits = (yyvsp[0].rune); charsetmask = 0x0000007f; }
#line 1287 "y.tab.c"
    break;

  case 9: /* entry: CHARSET RUNE RUNE  */
#line 125 "yacc.y"
                { charsetbits = (yyvsp[-1].rune); charsetmask = (yyvsp[0].rune); }
#line 1293 "y.tab.c"
    break;

  case 10: /* entry: CHARSET STRING  */
#line 127 "yacc.y"
                { int final = (yyvsp[0].str)[strlen((yyvsp[0].str)) - 1] & 0x7f;
		  charsetbits = final << 24;
		  if ((yyvsp[0].str)[0] == '$') {
			charsetmask = 0x00007f7f;
			if (strchr(",-./", (yyvsp[0].str)[1]))
				charsetbits |= 0x80;
			if (0xd0 <= final && final <= 0xdf)
				charsetmask |= 0x007f0000;
		  } else {
			charsetmask = 0x0000007f;
			if (strchr(",-./", (yyvsp[0].str)[0]))
				charsetbits |= 0x80;
			if (strlen((yyvsp[0].str)) == 2 && (yyvsp[0].str)[0] == '!')
				charsetbits |= ((0x80 | (yyvsp[0].str)[0]) << 16);
		  }

		  /*
		   * special rules
		   */
		  if (charsetbits == ('B' << 24)
		   && charsetmask == 0x0000007f) {
			/*ASCII: 94B*/
			charsetbits = 0;
			charsetmask = 0x0000007f;
		  } else if (charsetbits == (('A' << 24) | 0x80)
		  	  && charsetmask == 0x0000007f) {
		  	/*Latin1: 96A*/
			charsetbits = 0x80;
			charsetmask = 0x0000007f;
		  }
		}
#line 1329 "y.tab.c"
    break;

  case 11: /* entry: INVALID RUNE  */
#line 159 "yacc.y"
                { new_locale.rl_invalid_rune = (yyvsp[0].rune); }
#line 1335 "y.tab.c"
    break;

  case 12: /* entry: LIST list  */
#line 161 "yacc.y"
                { set_map(&types, (yyvsp[0].list), (yyvsp[-1].i)); }
#line 1341 "y.tab.c"
    break;

  case 13: /* entry: MAPLOWER map  */
#line 163 "yacc.y"
                { set_map(&maplower, (yyvsp[0].list), 0); }
#line 1347 "y.tab.c"
    break;

  case 14: /* entry: MAPUPPER map  */
#line 165 "yacc.y"
                { set_map(&mapupper, (yyvsp[0].list), 0); }
#line 1353 "y.tab.c"
    break;

  case 15: /* entry: DIGITMAP mapignore  */
#line 167 "yacc.y"
                { }
#line 1359 "y.tab.c"
    break;

  case 16: /* list: RUNE  */
#line 171 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[0].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[0].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = 0;
		    (yyval.list)->next = 0;
		}
#line 1371 "y.tab.c"
    break;

  case 17: /* list: RUNE THRU RUNE  */
#line 179 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[-2].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[0].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = 0;
		    (yyval.list)->next = 0;
		}
#line 1383 "y.tab.c"
    break;

  case 18: /* list: list RUNE  */
#line 187 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[0].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[0].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = 0;
		    (yyval.list)->next = (yyvsp[-1].list);
		}
#line 1395 "y.tab.c"
    break;

  case 19: /* list: list RUNE THRU RUNE  */
#line 195 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[-2].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[0].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = 0;
		    (yyval.list)->next = (yyvsp[-3].list);
		}
#line 1407 "y.tab.c"
    break;

  case 20: /* map: LBRK RUNE RUNE RBRK  */
#line 205 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[-2].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[-2].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = (yyvsp[-1].rune);
		    (yyval.list)->next = 0;
		}
#line 1419 "y.tab.c"
    break;

  case 21: /* map: map LBRK RUNE RUNE RBRK  */
#line 213 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[-2].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[-2].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = (yyvsp[-1].rune);
		    (yyval.list)->next = (yyvsp[-4].list);
		}
#line 1431 "y.tab.c"
    break;

  case 22: /* map: LBRK RUNE THRU RUNE ':' RUNE RBRK  */
#line 221 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[-5].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[-3].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = (yyvsp[-1].rune);
		    (yyval.list)->next = 0;
		}
#line 1443 "y.tab.c"
    break;

  case 23: /* map: map LBRK RUNE THRU RUNE ':' RUNE RBRK  */
#line 229 "yacc.y"
                {
		    (yyval.list) = xmalloc(sizeof(rune_list));
		    (yyval.list)->min = ((yyvsp[-5].rune) & charsetmask) | charsetbits;
		    (yyval.list)->max = ((yyvsp[-3].rune) & charsetmask) | charsetbits;
		    (yyval.list)->map = (yyvsp[-1].rune);
		    (yyval.list)->next = (yyvsp[-7].list);
		}
#line 1455 "y.tab.c"
    break;

  case 24: /* mapignore: LBRK RUNE RUNE RBRK  */
#line 238 "yacc.y"
                                    { }
#line 1461 "y.tab.c"
    break;

  case 25: /* mapignore: map LBRK RUNE RUNE RBRK  */
#line 239 "yacc.y"
                                        { }
#line 1467 "y.tab.c"
    break;

  case 26: /* mapignore: LBRK RUNE THRU RUNE ':' RUNE RBRK  */
#line 240 "yacc.y"
                                                  { }
#line 1473 "y.tab.c"
    break;

  case 27: /* mapignore: map LBRK RUNE THRU RUNE ':' RUNE RBRK  */
#line 241 "yacc.y"
                                                      { }
#line 1479 "y.tab.c"
    break;


#line 1483 "y.tab.c"

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

#line 243 "yacc.y"


int debug = 0;
FILE *ofile;

int
main(int ac, char *av[])
{
    int x;

    extern char *optarg;
    extern int optind;

    if (pledge("stdio rpath wpath cpath", NULL) == -1) {
	perror("pledge");
	exit(1);
    }

    while ((x = getopt(ac, av, "do:")) != -1) {
	switch(x) {
	case 'd':
	    debug = 1;
	    break;
	case 'o':
	    locale_file = optarg;
	    if ((ofile = fopen(locale_file, "w")) == 0)
		err(1, "unable to open output file %s", locale_file);
	    break;
	default:
	usage:
	    fprintf(stderr,
		"usage: mklocale [-d] [src-file] language/LC_CTYPE\n"
		"       mklocale [-d] -o language/LC_CTYPE src-file\n");
	    exit(1);
	}
    }

    switch (ac - optind) {
    case 0:
	break;
    case 1:
	if (freopen(av[optind], "r", stdin) == 0)
	    err(1, "unable to open input file %s", av[optind]);
	break;
    default:
	goto usage;
    }
    for (x = 0; x < _CACHED_RUNES; ++x) {
	mapupper.map[x] = x;
	maplower.map[x] = x;
    }
    new_locale.rl_invalid_rune = _DEFAULT_INVALID_RUNE;
    memcpy(new_locale.rl_magic, _RUNE_MAGIC_1, sizeof(new_locale.rl_magic));

    yyparse();

    return 0;
}

int
yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);

    return 0;
}

void *
xmalloc(size_t sz)
{
    void *r = malloc(sz);
    if (!r) {
	perror("xmalloc");
	abort();
    }
    return(r);
}

u_int32_t *
xlalloc(size_t sz)
{
    u_int32_t *r = reallocarray(NULL, sz, sizeof(u_int32_t));
    if (!r) {
	perror("xlalloc");
	abort();
    }
    return(r);
}

u_int32_t *
xrelalloc(u_int32_t *old, size_t sz)
{
    u_int32_t *r = reallocarray(old, sz, sizeof(u_int32_t));
    if (!r) {
	perror("xrelalloc");
	abort();
    }
    return(r);
}

void
set_map(rune_map *map, rune_list *list, u_int32_t flag)
{
    list->map &= charsetmask;
    list->map |= charsetbits;
    while (list) {
	rune_list *nlist = list->next;
	add_map(map, list, flag);
	list = nlist;
    }
}

void
add_map(rune_map *map, rune_list *list, u_int32_t flag)
{
    rune_t i;
    rune_list *lr = 0;
    rune_list *r;
    rune_t run;

    while (list->min < _CACHED_RUNES && list->min <= list->max) {
	if (flag)
	    map->map[list->min++] |= flag;
	else
	    map->map[list->min++] = list->map++;
    }

    if (list->min > list->max) {
	free(list);
	return;
    }

    run = list->max - list->min + 1;

    if (!(r = map->root) || (list->max < r->min - 1)
			 || (!flag && list->max == r->min - 1)) {
	if (flag) {
	    list->types = xlalloc(run);
	    for (i = 0; i < run; ++i)
		list->types[i] = flag;
	}
	list->next = map->root;
	map->root = list;
	return;
    }

    for (r = map->root; r && r->max + 1 < list->min; r = r->next)
	lr = r;

    if (!r) {
	/*
	 * We are off the end.
	 */
	if (flag) {
	    list->types = xlalloc(run);
	    for (i = 0; i < run; ++i)
		list->types[i] = flag;
	}
	list->next = 0;
	lr->next = list;
	return;
    }

    if (list->max < r->min - 1) {
	/*
	 * We come before this range and we do not intersect it.
	 * We are not before the root node, it was checked before the loop
	 */
	if (flag) {
	    list->types = xlalloc(run);
	    for (i = 0; i < run; ++i)
		list->types[i] = flag;
	}
	list->next = lr->next;
	lr->next = list;
	return;
    }

    /*
     * At this point we have found that we at least intersect with
     * the range pointed to by `r', we might intersect with one or
     * more ranges beyond `r' as well.
     */

    if (!flag && list->map - list->min != r->map - r->min) {
	/*
	 * There are only two cases when we are doing case maps and
	 * our maps needn't have the same offset.  When we are adjoining
	 * but not intersecting.
	 */
	if (list->max + 1 == r->min) {
	    lr->next = list;
	    list->next = r;
	    return;
	}
	if (list->min - 1 == r->max) {
	    list->next = r->next;
	    r->next = list;
	    return;
	}
	fprintf(stderr, "Error: conflicting map entries\n");
	exit(1);
    }

    if (list->min >= r->min && list->max <= r->max) {
	/*
	 * Subset case.
	 */

	if (flag) {
	    for (i = list->min; i <= list->max; ++i)
		r->types[i - r->min] |= flag;
	}
	free(list);
	return;
    }
    if (list->min <= r->min && list->max >= r->max) {
	/*
	 * Superset case.  Make him big enough to hold us.
	 * We might need to merge with the guy after him.
	 */
	if (flag) {
	    list->types = xlalloc(list->max - list->min + 1);

	    for (i = list->min; i <= list->max; ++i)
		list->types[i - list->min] = flag;

	    for (i = r->min; i <= r->max; ++i)
		list->types[i - list->min] |= r->types[i - r->min];

	    free(r->types);
	    r->types = list->types;
	} else {
	    r->map = list->map;
	}
	r->min = list->min;
	r->max = list->max;
	free(list);
    } else if (list->min < r->min) {
	/*
	 * Our tail intersects his head.
	 */
	if (flag) {
	    list->types = xlalloc(r->max - list->min + 1);

	    for (i = r->min; i <= r->max; ++i)
		list->types[i - list->min] = r->types[i - r->min];

	    for (i = list->min; i < r->min; ++i)
		list->types[i - list->min] = flag;

	    for (i = r->min; i <= list->max; ++i)
		list->types[i - list->min] |= flag;

	    free(r->types);
	    r->types = list->types;
	} else {
	    r->map = list->map;
	}
	r->min = list->min;
	free(list);
	return;
    } else {
	/*
	 * Our head intersects his tail.
	 * We might need to merge with the guy after him.
	 */
	if (flag) {
	    r->types = xrelalloc(r->types, list->max - r->min + 1);

	    for (i = list->min; i <= r->max; ++i)
		r->types[i - r->min] |= flag;

	    for (i = r->max+1; i <= list->max; ++i)
		r->types[i - r->min] = flag;
	}
	r->max = list->max;
	free(list);
    }

    /*
     * Okay, check to see if we grew into the next guy(s)
     */
    while ((lr = r->next) && r->max >= lr->min) {
	if (flag) {
	    if (r->max >= lr->max) {
		/*
		 * Good, we consumed all of him.
		 */
		for (i = lr->min; i <= lr->max; ++i)
		    r->types[i - r->min] |= lr->types[i - lr->min];
	    } else {
		/*
		 * "append" him on to the end of us.
		 */
		r->types = xrelalloc(r->types, lr->max - r->min + 1);

		for (i = lr->min; i <= r->max; ++i)
		    r->types[i - r->min] |= lr->types[i - lr->min];

		for (i = r->max+1; i <= lr->max; ++i)
		    r->types[i - r->min] = lr->types[i - lr->min];

		r->max = lr->max;
	    }
	} else {
	    if (lr->max > r->max)
		r->max = lr->max;
	}

	r->next = lr->next;

	if (flag)
	    free(lr->types);
	free(lr);
    }
}

void
dump_tables()
{
    int x, n;
    rune_list *list;
    _FileRuneLocale file_new_locale;
    FILE *fp = (ofile ? ofile : stdout);

    memset(&file_new_locale, 0, sizeof(file_new_locale));

    /*
     * See if we can compress some of the istype arrays
     */
    for(list = types.root; list; list = list->next) {
	list->map = list->types[0];
	for (x = 1; x < list->max - list->min + 1; ++x) {
	    if (list->types[x] != list->map) {
		list->map = 0;
		break;
	    }
	}
    }

    memcpy(&file_new_locale.frl_magic, new_locale.rl_magic,
	sizeof(file_new_locale.frl_magic));
    memcpy(&file_new_locale.frl_encoding, new_locale.rl_encoding,
	sizeof(file_new_locale.frl_encoding));

    file_new_locale.frl_invalid_rune = htonl(new_locale.rl_invalid_rune);

    /*
     * Fill in our tables.  Do this in network order so that
     * diverse machines have a chance of sharing data.
     * (Machines like Crays cannot share with little machines due to
     *  word size.  Sigh.  We tried.)
     */
    for (x = 0; x < _CACHED_RUNES; ++x) {
	file_new_locale.frl_runetype[x] = htonl(types.map[x]);
	file_new_locale.frl_maplower[x] = htonl(maplower.map[x]);
	file_new_locale.frl_mapupper[x] = htonl(mapupper.map[x]);
    }

    /*
     * Count up how many ranges we will need for each of the extents.
     */
    list = types.root;

    while (list) {
	new_locale.rl_runetype_ext.rr_nranges++;
	list = list->next;
    }
    file_new_locale.frl_runetype_ext.frr_nranges =
	htonl(new_locale.rl_runetype_ext.rr_nranges);

    list = maplower.root;

    while (list) {
	new_locale.rl_maplower_ext.rr_nranges++;
	list = list->next;
    }
    file_new_locale.frl_maplower_ext.frr_nranges =
	htonl(new_locale.rl_maplower_ext.rr_nranges);

    list = mapupper.root;

    while (list) {
	new_locale.rl_mapupper_ext.rr_nranges++;
	list = list->next;
    }
    file_new_locale.frl_mapupper_ext.frr_nranges =
	htonl(new_locale.rl_mapupper_ext.rr_nranges);

    file_new_locale.frl_variable_len = htonl(new_locale.rl_variable_len);

    /*
     * Okay, we are now ready to write the new locale file.
     */

    /*
     * PART 1: The _RuneLocale structure
     */
    if (fwrite((char *)&file_new_locale, sizeof(file_new_locale), 1, fp) != 1)
	err(1, "writing _RuneLocale to %s", locale_file);
    /*
     * PART 2: The runetype_ext structures (not the actual tables)
     */
    for (list = types.root, n = 0; list != NULL; list = list->next, n++) {
	_FileRuneEntry re;

	memset(&re, 0, sizeof(re));
	re.fre_min = htonl(list->min);
	re.fre_max = htonl(list->max);
	re.fre_map = htonl(list->map);

	if (fwrite((char *)&re, sizeof(re), 1, fp) != 1)
	    err(1, "writing runetype_ext #%d to %s", n, locale_file);
    }
    /*
     * PART 3: The maplower_ext structures
     */
    for (list = maplower.root, n = 0; list != NULL; list = list->next, n++) {
	_FileRuneEntry re;

	memset(&re, 0, sizeof(re));
	re.fre_min = htonl(list->min);
	re.fre_max = htonl(list->max);
	re.fre_map = htonl(list->map);

	if (fwrite((char *)&re, sizeof(re), 1, fp) != 1)
	    err(1, "writing maplower_ext #%d to %s", n, locale_file);
    }
    /*
     * PART 4: The mapupper_ext structures
     */
    for (list = mapupper.root, n = 0; list != NULL; list = list->next, n++) {
	_FileRuneEntry re;

	memset(&re, 0, sizeof(re));
	re.fre_min = htonl(list->min);
	re.fre_max = htonl(list->max);
	re.fre_map = htonl(list->map);

	if (fwrite((char *)&re, sizeof(re), 1, fp) != 1)
	    err(1, "writing mapupper_ext #%d to %s", n, locale_file);
    }
    /*
     * PART 5: The runetype_ext tables
     */
    for (list = types.root, n = 0; list != NULL; list = list->next, n++) {
	for (x = 0; x < list->max - list->min + 1; ++x)
	    list->types[x] = htonl(list->types[x]);

	if (!list->map) {
	    if (fwrite((char *)list->types,
		       (list->max - list->min + 1) * sizeof(u_int32_t),
		       1, fp) != 1)
		err(1, "writing runetype_ext table #%d to %s", n, locale_file);
	}
    }
    /*
     * PART 5: And finally the variable data
     */
    if (new_locale.rl_variable_len != 0 &&
	fwrite((char *)new_locale.rl_variable,
	       new_locale.rl_variable_len, 1, fp) != 1)
	err(1, "writing variable data to %s", locale_file);
    fclose(fp);

    if (!debug)
	return;

    if (new_locale.rl_encoding[0])
	fprintf(stderr, "ENCODING	%s\n", new_locale.rl_encoding);
    if (new_locale.rl_variable)
	fprintf(stderr, "VARIABLE	%s\n",
		(char *)new_locale.rl_variable);

    fprintf(stderr, "\nMAPLOWER:\n\n");

    for (x = 0; x < _CACHED_RUNES; ++x) {
	if (isprint(maplower.map[x]))
	    fprintf(stderr, " '%c'", (int)maplower.map[x]);
	else if (maplower.map[x])
	    fprintf(stderr, "%04x", maplower.map[x]);
	else
	    fprintf(stderr, "%4x", 0);
	if ((x & 0xf) == 0xf)
	    fprintf(stderr, "\n");
	else
	    fprintf(stderr, " ");
    }
    fprintf(stderr, "\n");

    for (list = maplower.root; list; list = list->next)
	fprintf(stderr, "\t%04x - %04x : %04x\n", list->min, list->max, list->map);

    fprintf(stderr, "\nMAPUPPER:\n\n");

    for (x = 0; x < _CACHED_RUNES; ++x) {
	if (isprint(mapupper.map[x]))
	    fprintf(stderr, " '%c'", (int)mapupper.map[x]);
	else if (mapupper.map[x])
	    fprintf(stderr, "%04x", mapupper.map[x]);
	else
	    fprintf(stderr, "%4x", 0);
	if ((x & 0xf) == 0xf)
	    fprintf(stderr, "\n");
	else
	    fprintf(stderr, " ");
    }
    fprintf(stderr, "\n");

    for (list = mapupper.root; list; list = list->next)
	fprintf(stderr, "\t%04x - %04x : %04x\n", list->min, list->max, list->map);


    fprintf(stderr, "\nTYPES:\n\n");

    for (x = 0; x < _CACHED_RUNES; ++x) {
	u_int32_t r = types.map[x];

	if (r) {
	    if (isprint(x))
		fprintf(stderr, " '%c':%2d", x, (int)(r & 0xff));
	    else
		fprintf(stderr, "%04x:%2d", x, (int)(r & 0xff));

	    fprintf(stderr, " %4s", (r & _RUNETYPE_A) ? "alph" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_C) ? "ctrl" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_D) ? "dig" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_G) ? "graf" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_L) ? "low" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_P) ? "punc" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_S) ? "spac" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_U) ? "upp" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_X) ? "xdig" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_B) ? "blnk" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_R) ? "prnt" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_I) ? "ideo" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_T) ? "spec" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_Q) ? "phon" : "");
	    fprintf(stderr, "\n");
	}
    }

    for (list = types.root; list; list = list->next) {
	if (list->map && list->min + 3 < list->max) {
	    u_int32_t r = list->map;

	    fprintf(stderr, "%04x:%2d", list->min, r & 0xff);

	    fprintf(stderr, " %4s", (r & _RUNETYPE_A) ? "alph" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_C) ? "ctrl" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_D) ? "dig" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_G) ? "graf" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_L) ? "low" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_P) ? "punc" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_S) ? "spac" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_U) ? "upp" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_X) ? "xdig" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_B) ? "blnk" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_R) ? "prnt" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_I) ? "ideo" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_T) ? "spec" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_Q) ? "phon" : "");
	    fprintf(stderr, "\n...\n");

	    fprintf(stderr, "%04x:%2d", list->max, r & 0xff);

	    fprintf(stderr, " %4s", (r & _RUNETYPE_A) ? "alph" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_C) ? "ctrl" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_D) ? "dig" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_G) ? "graf" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_L) ? "low" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_P) ? "punc" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_S) ? "spac" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_U) ? "upp" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_X) ? "xdig" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_B) ? "blnk" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_R) ? "prnt" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_I) ? "ideo" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_T) ? "spec" : "");
	    fprintf(stderr, " %4s", (r & _RUNETYPE_Q) ? "phon" : "");
            fprintf(stderr, " %1u", (unsigned)((r & _RUNETYPE_SWM)>>_RUNETYPE_SWS));
	    fprintf(stderr, "\n");
	} else 
	for (x = list->min; x <= list->max; ++x) {
	    u_int32_t r = ntohl(list->types[x - list->min]);

	    if (r) {
		fprintf(stderr, "%04x:%2d", x, (int)(r & 0xff));

		fprintf(stderr, " %4s", (r & _RUNETYPE_A) ? "alph" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_C) ? "ctrl" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_D) ? "dig" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_G) ? "graf" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_L) ? "low" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_P) ? "punc" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_S) ? "spac" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_U) ? "upp" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_X) ? "xdig" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_B) ? "blnk" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_R) ? "prnt" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_I) ? "ideo" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_T) ? "spec" : "");
		fprintf(stderr, " %4s", (r & _RUNETYPE_Q) ? "phon" : "");
                fprintf(stderr, " %1u", (unsigned)((r & _RUNETYPE_SWM)>>_RUNETYPE_SWS));
		fprintf(stderr, "\n");
	    }
	}
    }
}
