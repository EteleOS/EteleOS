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
#line 31 "bt_parse.y"

#include <sys/queue.h>

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "bt_parser.h"

/* Name for the default map @[], hopefully nobody will use this one ;) */
#define UNNAMED_MAP	"___unnamed_map_doesnt_have_any_name"

/* Number of rules to evaluate. */
struct bt_ruleq		g_rules = TAILQ_HEAD_INITIALIZER(g_rules);

/* Number of probes except BEGIN/END. */
int		 	g_nprobes;

/* List of global variables, including maps. */
SLIST_HEAD(, bt_var)	 g_variables;

/* List of local variables, cleaned for each new rule. */
SLIST_HEAD(, bt_var)	l_variables;

struct bt_arg 		g_nullba = BA_INITIALIZER(0, B_AT_LONG);
struct bt_arg		g_maxba = BA_INITIALIZER(LONG_MAX, B_AT_LONG);

struct bt_rule	*br_new(struct bt_probe *, struct bt_filter *,
		     struct bt_stmt *);
struct bt_probe	*bp_new(const char *, const char *, const char *, long);
struct bt_arg	*ba_append(struct bt_arg *, struct bt_arg *);
struct bt_arg	*ba_op(enum bt_argtype, struct bt_arg *, struct bt_arg *);
struct bt_stmt	*bs_new(enum bt_action, struct bt_arg *, struct bt_var *);
struct bt_stmt	*bs_append(struct bt_stmt *, struct bt_stmt *);

struct bt_var	*bg_lookup(const char *);
struct bt_stmt	*bg_store(const char *, struct bt_arg *);
struct bt_arg	*bg_find(const char *);
struct bt_var	*bg_get(const char *);

struct bt_arg	*bi_find(struct bt_arg *, unsigned long);

struct bt_var	*bl_lookup(const char *);
struct bt_stmt	*bl_store(const char *, struct bt_arg *);
struct bt_arg	*bl_find(const char *);

struct bt_arg	*bm_find(const char *, struct bt_arg *);
struct bt_stmt	*bm_insert(const char *, struct bt_arg *, struct bt_arg *);
struct bt_stmt	*bm_op(enum bt_action, struct bt_arg *, struct bt_arg *);

struct bt_stmt	*bh_inc(const char *, struct bt_arg *, struct bt_arg *);

/*
 * Lexer
 */
const char	*pbuf;
size_t		 plen;
size_t		 pindex;
int		 perrors = 0;

typedef struct {
	union {
		long			 number;
		int			 i;
		const char		*string;
		struct bt_probe		*probe;
		struct bt_filter	*filter;
		struct bt_stmt		*stmt;
		struct bt_arg		*arg;
	} v;
	const char			*filename;
	int				 lineno;
	int				 colno;
} yystype;
#define YYSTYPE yystype

static void	 yyerror(const char *, ...);
static int	 yylex(void);

static int 	 pflag = 0;		/* probe parsing context flag */
static int 	 beflag = 0;		/* BEGIN/END parsing context flag */

#line 159 "y.tab.c"

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
    ERROR = 258,                   /* ERROR  */
    ENDFILT = 259,                 /* ENDFILT  */
    OP_EQ = 260,                   /* OP_EQ  */
    OP_NE = 261,                   /* OP_NE  */
    OP_LE = 262,                   /* OP_LE  */
    OP_LT = 263,                   /* OP_LT  */
    OP_GE = 264,                   /* OP_GE  */
    OP_GT = 265,                   /* OP_GT  */
    OP_LAND = 266,                 /* OP_LAND  */
    OP_LOR = 267,                  /* OP_LOR  */
    BUILTIN = 268,                 /* BUILTIN  */
    BEGIN = 269,                   /* BEGIN  */
    ELSE = 270,                    /* ELSE  */
    END = 271,                     /* END  */
    IF = 272,                      /* IF  */
    STR = 273,                     /* STR  */
    F_DELETE = 274,                /* F_DELETE  */
    F_PRINT = 275,                 /* F_PRINT  */
    MFUNC = 276,                   /* MFUNC  */
    FUNC0 = 277,                   /* FUNC0  */
    FUNC1 = 278,                   /* FUNC1  */
    FUNCN = 279,                   /* FUNCN  */
    OP1 = 280,                     /* OP1  */
    OP2 = 281,                     /* OP2  */
    OP4 = 282,                     /* OP4  */
    MOP0 = 283,                    /* MOP0  */
    MOP1 = 284,                    /* MOP1  */
    STRING = 285,                  /* STRING  */
    CSTRING = 286,                 /* CSTRING  */
    GVAR = 287,                    /* GVAR  */
    LVAR = 288,                    /* LVAR  */
    PVAR = 289,                    /* PVAR  */
    PNUM = 290,                    /* PNUM  */
    NUMBER = 291                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ERROR 258
#define ENDFILT 259
#define OP_EQ 260
#define OP_NE 261
#define OP_LE 262
#define OP_LT 263
#define OP_GE 264
#define OP_GT 265
#define OP_LAND 266
#define OP_LOR 267
#define BUILTIN 268
#define BEGIN 269
#define ELSE 270
#define END 271
#define IF 272
#define STR 273
#define F_DELETE 274
#define F_PRINT 275
#define MFUNC 276
#define FUNC0 277
#define FUNC1 278
#define FUNCN 279
#define OP1 280
#define OP2 281
#define OP4 282
#define MOP0 283
#define MOP1 284
#define STRING 285
#define CSTRING 286
#define GVAR 287
#define LVAR 288
#define PVAR 289
#define PNUM 290
#define NUMBER 291

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
  YYSYMBOL_ERROR = 3,                      /* ERROR  */
  YYSYMBOL_ENDFILT = 4,                    /* ENDFILT  */
  YYSYMBOL_OP_EQ = 5,                      /* OP_EQ  */
  YYSYMBOL_OP_NE = 6,                      /* OP_NE  */
  YYSYMBOL_OP_LE = 7,                      /* OP_LE  */
  YYSYMBOL_OP_LT = 8,                      /* OP_LT  */
  YYSYMBOL_OP_GE = 9,                      /* OP_GE  */
  YYSYMBOL_OP_GT = 10,                     /* OP_GT  */
  YYSYMBOL_OP_LAND = 11,                   /* OP_LAND  */
  YYSYMBOL_OP_LOR = 12,                    /* OP_LOR  */
  YYSYMBOL_BUILTIN = 13,                   /* BUILTIN  */
  YYSYMBOL_BEGIN = 14,                     /* BEGIN  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_END = 16,                       /* END  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_STR = 18,                       /* STR  */
  YYSYMBOL_F_DELETE = 19,                  /* F_DELETE  */
  YYSYMBOL_F_PRINT = 20,                   /* F_PRINT  */
  YYSYMBOL_MFUNC = 21,                     /* MFUNC  */
  YYSYMBOL_FUNC0 = 22,                     /* FUNC0  */
  YYSYMBOL_FUNC1 = 23,                     /* FUNC1  */
  YYSYMBOL_FUNCN = 24,                     /* FUNCN  */
  YYSYMBOL_OP1 = 25,                       /* OP1  */
  YYSYMBOL_OP2 = 26,                       /* OP2  */
  YYSYMBOL_OP4 = 27,                       /* OP4  */
  YYSYMBOL_MOP0 = 28,                      /* MOP0  */
  YYSYMBOL_MOP1 = 29,                      /* MOP1  */
  YYSYMBOL_STRING = 30,                    /* STRING  */
  YYSYMBOL_CSTRING = 31,                   /* CSTRING  */
  YYSYMBOL_GVAR = 32,                      /* GVAR  */
  YYSYMBOL_LVAR = 33,                      /* LVAR  */
  YYSYMBOL_PVAR = 34,                      /* PVAR  */
  YYSYMBOL_PNUM = 35,                      /* PNUM  */
  YYSYMBOL_NUMBER = 36,                    /* NUMBER  */
  YYSYMBOL_37_n_ = 37,                     /* '\n'  */
  YYSYMBOL_38_ = 38,                       /* ','  */
  YYSYMBOL_39_ = 39,                       /* ':'  */
  YYSYMBOL_40_ = 40,                       /* '['  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* '/'  */
  YYSYMBOL_45_ = 45,                       /* '+'  */
  YYSYMBOL_46_ = 46,                       /* '-'  */
  YYSYMBOL_47_ = 47,                       /* '&'  */
  YYSYMBOL_48_ = 48,                       /* '^'  */
  YYSYMBOL_49_ = 49,                       /* '|'  */
  YYSYMBOL_50_ = 50,                       /* '*'  */
  YYSYMBOL_51_ = 51,                       /* '%'  */
  YYSYMBOL_52_ = 52,                       /* '.'  */
  YYSYMBOL_53_ = 53,                       /* ';'  */
  YYSYMBOL_54_ = 54,                       /* '='  */
  YYSYMBOL_55_ = 55,                       /* '{'  */
  YYSYMBOL_56_ = 56,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_grammar = 58,                   /* grammar  */
  YYSYMBOL_rule = 59,                      /* rule  */
  YYSYMBOL_beginend = 60,                  /* beginend  */
  YYSYMBOL_plist = 61,                     /* plist  */
  YYSYMBOL_probe = 62,                     /* probe  */
  YYSYMBOL_63_1 = 63,                      /* $@1  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_pname = 65,                     /* pname  */
  YYSYMBOL_mentry = 66,                    /* mentry  */
  YYSYMBOL_mpat = 67,                      /* mpat  */
  YYSYMBOL_filter = 68,                    /* filter  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_term = 70,                      /* term  */
  YYSYMBOL_fterm = 71,                     /* fterm  */
  YYSYMBOL_variable = 72,                  /* variable  */
  YYSYMBOL_factor = 73,                    /* factor  */
  YYSYMBOL_func = 74,                      /* func  */
  YYSYMBOL_vargs = 75,                     /* vargs  */
  YYSYMBOL_pargs = 76,                     /* pargs  */
  YYSYMBOL_NL = 77,                        /* NL  */
  YYSYMBOL_stmt = 78,                      /* stmt  */
  YYSYMBOL_stmtblck = 79,                  /* stmtblck  */
  YYSYMBOL_stmtlist = 80,                  /* stmtlist  */
  YYSYMBOL_block = 81,                     /* block  */
  YYSYMBOL_action = 82                     /* action  */
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


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
      37,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    51,    47,     2,
      42,    43,    50,    45,    38,    46,    52,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    53,
       2,    54,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,    49,    56,     2,     2,     2,     2,
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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   138,   138,   139,   140,   141,   144,   147,   147,   149,
     150,   153,   153,   154,   154,   157,   158,   161,   164,   165,
     166,   169,   170,   179,   180,   181,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   198,   199,
     200,   201,   204,   205,   206,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   221,   222,   225,   226,   229,
     230,   233,   234,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   251,   252,   253,   256,   257,
     258,   259,   262,   263,   266,   267
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
  "\"end of file\"", "error", "\"invalid token\"", "ERROR", "ENDFILT",
  "OP_EQ", "OP_NE", "OP_LE", "OP_LT", "OP_GE", "OP_GT", "OP_LAND",
  "OP_LOR", "BUILTIN", "BEGIN", "ELSE", "END", "IF", "STR", "F_DELETE",
  "F_PRINT", "MFUNC", "FUNC0", "FUNC1", "FUNCN", "OP1", "OP2", "OP4",
  "MOP0", "MOP1", "STRING", "CSTRING", "GVAR", "LVAR", "PVAR", "PNUM",
  "NUMBER", "'\\n'", "','", "':'", "'['", "']'", "'('", "')'", "'/'",
  "'+'", "'-'", "'&'", "'^'", "'|'", "'*'", "'%'", "'.'", "';'", "'='",
  "'{'", "'}'", "$accept", "grammar", "rule", "beginend", "plist", "probe",
  "$@1", "$@2", "pname", "mentry", "mpat", "filter", "expr", "term",
  "fterm", "variable", "factor", "func", "vargs", "pargs", "NL", "stmt",
  "stmtblck", "stmtlist", "block", "action", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-14)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -72,    83,   -72,   -72,   -72,   -72,    20,   -72,   -17,   115,
       1,   157,   -20,     3,   -72,   -72,   -72,   -72,   -72,   -72,
      25,   -72,    35,   -72,   -72,   -72,   -72,   157,   -72,    94,
      -2,    90,    33,   -72,   -72,     0,   -72,    52,    62,   157,
      14,    87,   -72,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,    85,
      93,   100,   102,   104,   127,   129,   130,    15,   131,   149,
     -72,   -72,   -72,    17,   155,   121,    40,   -27,   -72,   157,
      -2,    -2,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,   -72,   -72,   -72,   -72,   157,   164,   182,
      30,   154,   157,   157,   157,   120,   157,   -72,   -72,   -72,
     -72,   -72,    24,   157,   -72,   157,   -72,    16,    18,    35,
     169,    71,    40,   176,   -72,   -34,   -72,    60,   122,   -26,
     178,   179,    40,    40,   -72,   -72,    81,    40,   -72,    95,
     -72,   157,   -72,   -72,   -72,   -72,   144,   157,   157,   -72,
     170,   207,   -72,    40,   145,    89,   111,   -72,    57,   183,
     184,   -72,    40,   -72,   157,   -72,   -72,   185,   157,   123,
     -72,    96,   -72,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     5,     3,     4,    21,    10,     0,     0,
      13,     0,     0,     0,    12,     7,     8,    14,     9,    48,
       0,    49,    43,    42,    50,    51,    47,     0,    53,     0,
      25,    37,    52,    41,    54,     0,     6,     0,     0,     0,
      57,     0,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      85,    81,    80,     0,     0,     0,    57,     0,    45,     0,
      23,    24,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    39,    38,    40,    44,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,    63,    84,
      79,    78,     0,     0,    55,     0,    17,    58,     0,     0,
       0,    43,    59,     0,    43,     0,    70,     0,     0,     0,
       0,     0,    64,    65,    15,    16,     0,    58,    46,     0,
      71,     0,    72,    69,    68,    67,     0,     0,     0,    56,
       0,    75,    82,    60,     0,     0,     0,    83,     0,     0,
       0,    66,    20,    73,     0,    77,    76,     0,     0,     0,
      18,     0,    74,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   -72,   -72,   217,   -72,   -72,   -72,   132,
     -72,   -72,   -11,   124,   156,   133,   126,   -72,   -38,   -72,
     -72,   -25,   -71,   -72,    73,   220
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     5,    17,     6,     7,     8,     9,    14,    28,
     161,    12,    76,    30,    31,    32,    33,    34,    41,   123,
     108,   150,    72,    73,   151,   152
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    77,   111,    45,    46,    47,    48,    49,    50,   143,
      71,   115,   115,    13,   116,   146,    40,    60,    59,    61,
      62,    63,    64,    65,    66,    43,    44,    43,    44,    43,
      44,   -11,    67,    68,    60,    35,    61,    62,    63,    64,
      65,    66,    37,    51,    52,    53,    54,    55,   110,    67,
      68,    43,    44,    69,   134,   104,    70,    78,    10,   138,
     135,   139,   124,    23,    11,   128,   129,    38,   117,   105,
      69,    43,    44,   109,    60,    39,    61,    62,    63,    64,
      65,    66,    74,     2,     3,    59,   118,   165,   122,    67,
      68,   127,    43,    44,   132,   133,    75,   -13,    42,   -13,
      43,    44,   136,   144,   137,    43,    44,    43,    44,   141,
      69,    39,    35,   -11,    61,    62,    63,    64,    65,    66,
       4,    96,    43,    44,   149,    79,   169,    67,    68,    15,
     153,    16,   163,    19,    56,    97,   155,   156,    20,   173,
      57,    58,    98,   162,    99,   130,   100,   131,    69,   164,
      35,    21,    22,    23,    24,    25,    26,   171,    19,   113,
     115,   115,    27,    20,   114,   145,   172,    80,    81,   101,
      19,   102,   103,   159,   160,    20,    21,    22,    23,    24,
      25,    26,    93,    94,    95,   106,   107,    27,    21,    22,
      23,    24,    25,    26,   112,    19,   119,   126,   154,    27,
      20,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   140,    21,   121,    23,    24,    25,    26,   142,
     147,   148,   158,   157,    27,   167,   168,    18,   170,     0,
     120,   166,    36,   125
};

static const yytype_int16 yycheck[] =
{
      11,    39,    73,     5,     6,     7,     8,     9,    10,    43,
      35,    38,    38,    30,    41,    41,    27,    17,    52,    19,
      20,    21,    22,    23,    24,    11,    12,    11,    12,    11,
      12,    30,    32,    33,    17,    55,    19,    20,    21,    22,
      23,    24,    39,    45,    46,    47,    48,    49,    73,    32,
      33,    11,    12,    53,    30,    40,    56,    43,    38,    43,
      36,    43,    32,    33,    44,   103,   104,    42,    79,    54,
      53,    11,    12,    56,    17,    40,    19,    20,    21,    22,
      23,    24,    30,     0,     1,    52,    97,   158,    99,    32,
      33,   102,    11,    12,   105,   106,    34,    14,     4,    16,
      11,    12,   113,    43,   115,    11,    12,    11,    12,    38,
      53,    40,    55,    30,    19,    20,    21,    22,    23,    24,
      37,    36,    11,    12,    43,    38,   164,    32,    33,    14,
     141,    16,    43,    13,    44,    42,   147,   148,    18,    43,
      50,    51,    42,   154,    42,    25,    42,    27,    53,    38,
      55,    31,    32,    33,    34,    35,    36,   168,    13,    38,
      38,    38,    42,    18,    43,    43,    43,    43,    44,    42,
      13,    42,    42,    28,    29,    18,    31,    32,    33,    34,
      35,    36,    56,    57,    58,    54,    37,    42,    31,    32,
      33,    34,    35,    36,    39,    13,    32,    43,    54,    42,
      18,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    43,    31,    32,    33,    34,    35,    36,    43,
      42,    42,    15,    53,    42,    42,    42,    10,    43,    -1,
      98,   158,    12,   100
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    58,     0,     1,    37,    59,    61,    62,    63,    64,
      38,    44,    68,    30,    65,    14,    16,    60,    62,    13,
      18,    31,    32,    33,    34,    35,    36,    42,    66,    69,
      70,    71,    72,    73,    74,    55,    82,    39,    42,    40,
      69,    75,     4,    11,    12,     5,     6,     7,     8,     9,
      10,    45,    46,    47,    48,    49,    44,    50,    51,    52,
      17,    19,    20,    21,    22,    23,    24,    32,    33,    53,
      56,    78,    79,    80,    30,    34,    69,    75,    43,    38,
      70,    70,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    73,    73,    73,    36,    42,    42,    42,
      42,    42,    42,    42,    40,    54,    54,    37,    77,    56,
      78,    79,    39,    38,    43,    38,    41,    69,    69,    32,
      66,    32,    69,    76,    32,    72,    43,    69,    75,    75,
      25,    27,    69,    69,    30,    36,    69,    69,    43,    43,
      43,    38,    43,    43,    43,    43,    41,    42,    42,    43,
      78,    81,    82,    69,    54,    69,    69,    53,    15,    28,
      29,    67,    69,    43,    38,    79,    81,    42,    42,    75,
      43,    69,    43,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    58,    58,    58,    59,    60,    60,    61,
      61,    63,    62,    64,    62,    65,    65,    66,    67,    67,
      67,    68,    68,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      71,    71,    72,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    74,    74,    75,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    79,    79,    79,    80,    80,
      80,    80,    81,    81,    82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     3,     1,     1,     3,
       1,     0,     2,     0,     2,     5,     5,     4,     3,     4,
       1,     0,     3,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     1,     1,     1,     3,     3,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     6,     1,     3,     1,
       3,     0,     1,     2,     3,     3,     6,     4,     4,     4,
       3,     4,     4,     6,     8,     5,     7,     7,     2,     2,
       1,     1,     1,     2,     3,     2
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
  case 6: /* rule: plist filter action  */
#line 144 "bt_parse.y"
                                        { br_new((yyvsp[-2].v.probe), (yyvsp[-1].v.filter), (yyvsp[0].v.stmt)); beflag = 0; }
#line 1456 "y.tab.c"
    break;

  case 9: /* plist: plist ',' probe  */
#line 149 "bt_parse.y"
                                        { (yyval.v.probe) = bp_append((yyvsp[-2].v.probe), (yyvsp[0].v.probe)); }
#line 1462 "y.tab.c"
    break;

  case 11: /* $@1: %empty  */
#line 153 "bt_parse.y"
          { pflag = 1; }
#line 1468 "y.tab.c"
    break;

  case 12: /* probe: $@1 pname  */
#line 153 "bt_parse.y"
                                        { (yyval.v.probe) = (yyvsp[0].v.probe); pflag = 0; }
#line 1474 "y.tab.c"
    break;

  case 13: /* $@2: %empty  */
#line 154 "bt_parse.y"
          { beflag = 1; }
#line 1480 "y.tab.c"
    break;

  case 14: /* probe: $@2 beginend  */
#line 154 "bt_parse.y"
                                        { (yyval.v.probe) = bp_new(NULL, NULL, NULL, (yyvsp[0].v.i)); }
#line 1486 "y.tab.c"
    break;

  case 15: /* pname: STRING ':' STRING ':' STRING  */
#line 157 "bt_parse.y"
                                        { (yyval.v.probe) = bp_new((yyvsp[-4].v.string), (yyvsp[-2].v.string), (yyvsp[0].v.string), 0); }
#line 1492 "y.tab.c"
    break;

  case 16: /* pname: STRING ':' STRING ':' NUMBER  */
#line 158 "bt_parse.y"
                                        { (yyval.v.probe) = bp_new((yyvsp[-4].v.string), (yyvsp[-2].v.string), NULL, (yyvsp[0].v.number)); }
#line 1498 "y.tab.c"
    break;

  case 17: /* mentry: GVAR '[' vargs ']'  */
#line 161 "bt_parse.y"
                                        { (yyval.v.arg) = bm_find((yyvsp[-3].v.string), (yyvsp[-1].v.arg)); }
#line 1504 "y.tab.c"
    break;

  case 18: /* mpat: MOP0 '(' ')'  */
#line 164 "bt_parse.y"
                                        { (yyval.v.arg) = ba_new(NULL, (yyvsp[-2].v.i)); }
#line 1510 "y.tab.c"
    break;

  case 19: /* mpat: MOP1 '(' expr ')'  */
#line 165 "bt_parse.y"
                                        { (yyval.v.arg) = ba_new((yyvsp[-1].v.arg), (yyvsp[-3].v.i)); }
#line 1516 "y.tab.c"
    break;

  case 21: /* filter: %empty  */
#line 169 "bt_parse.y"
                                        { (yyval.v.filter) = NULL; }
#line 1522 "y.tab.c"
    break;

  case 22: /* filter: '/' expr ENDFILT  */
#line 170 "bt_parse.y"
                                        { (yyval.v.filter) = bc_new(NULL, B_AT_OP_NE, (yyvsp[-1].v.arg)); }
#line 1528 "y.tab.c"
    break;

  case 23: /* expr: expr OP_LAND term  */
#line 179 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_LAND, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1534 "y.tab.c"
    break;

  case 24: /* expr: expr OP_LOR term  */
#line 180 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_LOR, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1540 "y.tab.c"
    break;

  case 26: /* term: term OP_EQ fterm  */
#line 184 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_EQ, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1546 "y.tab.c"
    break;

  case 27: /* term: term OP_NE fterm  */
#line 185 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_NE, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1552 "y.tab.c"
    break;

  case 28: /* term: term OP_LE fterm  */
#line 186 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_LE, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1558 "y.tab.c"
    break;

  case 29: /* term: term OP_LT fterm  */
#line 187 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_LT, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1564 "y.tab.c"
    break;

  case 30: /* term: term OP_GE fterm  */
#line 188 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_GE, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1570 "y.tab.c"
    break;

  case 31: /* term: term OP_GT fterm  */
#line 189 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_GT, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1576 "y.tab.c"
    break;

  case 32: /* term: term '+' fterm  */
#line 190 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_PLUS, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1582 "y.tab.c"
    break;

  case 33: /* term: term '-' fterm  */
#line 191 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_MINUS, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1588 "y.tab.c"
    break;

  case 34: /* term: term '&' fterm  */
#line 192 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_BAND, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1594 "y.tab.c"
    break;

  case 35: /* term: term '^' fterm  */
#line 193 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_XOR, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1600 "y.tab.c"
    break;

  case 36: /* term: term '|' fterm  */
#line 194 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_BOR, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1606 "y.tab.c"
    break;

  case 38: /* fterm: fterm '*' factor  */
#line 198 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_MULT, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1612 "y.tab.c"
    break;

  case 39: /* fterm: fterm '/' factor  */
#line 199 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_DIVIDE, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1618 "y.tab.c"
    break;

  case 40: /* fterm: fterm '%' factor  */
#line 200 "bt_parse.y"
                                { (yyval.v.arg) = ba_op(B_AT_OP_MODULO, (yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1624 "y.tab.c"
    break;

  case 42: /* variable: LVAR  */
#line 204 "bt_parse.y"
                                { (yyval.v.arg) = bl_find((yyvsp[0].v.string)); }
#line 1630 "y.tab.c"
    break;

  case 43: /* variable: GVAR  */
#line 205 "bt_parse.y"
                                { (yyval.v.arg) = bg_find((yyvsp[0].v.string)); }
#line 1636 "y.tab.c"
    break;

  case 44: /* variable: variable '.' NUMBER  */
#line 206 "bt_parse.y"
                                { (yyval.v.arg) = bi_find((yyvsp[-2].v.arg), (yyvsp[0].v.number)); }
#line 1642 "y.tab.c"
    break;

  case 45: /* factor: '(' expr ')'  */
#line 209 "bt_parse.y"
                                { (yyval.v.arg) = (yyvsp[-1].v.arg); }
#line 1648 "y.tab.c"
    break;

  case 46: /* factor: '(' vargs ',' expr ')'  */
#line 210 "bt_parse.y"
                                { (yyval.v.arg) = ba_new(ba_append((yyvsp[-3].v.arg), (yyvsp[-1].v.arg)), B_AT_TUPLE); }
#line 1654 "y.tab.c"
    break;

  case 47: /* factor: NUMBER  */
#line 211 "bt_parse.y"
                                { (yyval.v.arg) = ba_new((yyvsp[0].v.number), B_AT_LONG); }
#line 1660 "y.tab.c"
    break;

  case 48: /* factor: BUILTIN  */
#line 212 "bt_parse.y"
                                { (yyval.v.arg) = ba_new(NULL, (yyvsp[0].v.i)); }
#line 1666 "y.tab.c"
    break;

  case 49: /* factor: CSTRING  */
#line 213 "bt_parse.y"
                                { (yyval.v.arg) = ba_new((yyvsp[0].v.string), B_AT_STR); }
#line 1672 "y.tab.c"
    break;

  case 55: /* func: STR '(' PVAR ')'  */
#line 221 "bt_parse.y"
                                        { (yyval.v.arg) = ba_new((yyvsp[-1].v.arg), B_AT_FN_STR); }
#line 1678 "y.tab.c"
    break;

  case 56: /* func: STR '(' PVAR ',' expr ')'  */
#line 222 "bt_parse.y"
                                        { (yyval.v.arg) = ba_op(B_AT_FN_STR, (yyvsp[-3].v.arg), (yyvsp[-1].v.arg)); }
#line 1684 "y.tab.c"
    break;

  case 58: /* vargs: vargs ',' expr  */
#line 226 "bt_parse.y"
                                        { (yyval.v.arg) = ba_append((yyvsp[-2].v.arg), (yyvsp[0].v.arg)); }
#line 1690 "y.tab.c"
    break;

  case 60: /* pargs: GVAR ',' expr  */
#line 230 "bt_parse.y"
                                        { (yyval.v.arg) = ba_append(bg_find((yyvsp[-2].v.string)), (yyvsp[0].v.arg)); }
#line 1696 "y.tab.c"
    break;

  case 63: /* stmt: ';' NL  */
#line 237 "bt_parse.y"
                                        { (yyval.v.stmt) = NULL; }
#line 1702 "y.tab.c"
    break;

  case 64: /* stmt: GVAR '=' expr  */
#line 238 "bt_parse.y"
                                        { (yyval.v.stmt) = bg_store((yyvsp[-2].v.string), (yyvsp[0].v.arg)); }
#line 1708 "y.tab.c"
    break;

  case 65: /* stmt: LVAR '=' expr  */
#line 239 "bt_parse.y"
                                        { (yyval.v.stmt) = bl_store((yyvsp[-2].v.string), (yyvsp[0].v.arg)); }
#line 1714 "y.tab.c"
    break;

  case 66: /* stmt: GVAR '[' vargs ']' '=' mpat  */
#line 240 "bt_parse.y"
                                        { (yyval.v.stmt) = bm_insert((yyvsp[-5].v.string), (yyvsp[-3].v.arg), (yyvsp[0].v.arg)); }
#line 1720 "y.tab.c"
    break;

  case 67: /* stmt: FUNCN '(' vargs ')'  */
#line 241 "bt_parse.y"
                                        { (yyval.v.stmt) = bs_new((yyvsp[-3].v.i), (yyvsp[-1].v.arg), NULL); }
#line 1726 "y.tab.c"
    break;

  case 68: /* stmt: FUNC1 '(' expr ')'  */
#line 242 "bt_parse.y"
                                        { (yyval.v.stmt) = bs_new((yyvsp[-3].v.i), (yyvsp[-1].v.arg), NULL); }
#line 1732 "y.tab.c"
    break;

  case 69: /* stmt: MFUNC '(' variable ')'  */
#line 243 "bt_parse.y"
                                        { (yyval.v.stmt) = bs_new((yyvsp[-3].v.i), (yyvsp[-1].v.arg), NULL); }
#line 1738 "y.tab.c"
    break;

  case 70: /* stmt: FUNC0 '(' ')'  */
#line 244 "bt_parse.y"
                                        { (yyval.v.stmt) = bs_new((yyvsp[-2].v.i), NULL, NULL); }
#line 1744 "y.tab.c"
    break;

  case 71: /* stmt: F_DELETE '(' mentry ')'  */
#line 245 "bt_parse.y"
                                        { (yyval.v.stmt) = bm_op((yyvsp[-3].v.i), (yyvsp[-1].v.arg), NULL); }
#line 1750 "y.tab.c"
    break;

  case 72: /* stmt: F_PRINT '(' pargs ')'  */
#line 246 "bt_parse.y"
                                        { (yyval.v.stmt) = bs_new((yyvsp[-3].v.i), (yyvsp[-1].v.arg), NULL); }
#line 1756 "y.tab.c"
    break;

  case 73: /* stmt: GVAR '=' OP1 '(' expr ')'  */
#line 247 "bt_parse.y"
                                        { (yyval.v.stmt) = bh_inc((yyvsp[-5].v.string), (yyvsp[-1].v.arg), NULL); }
#line 1762 "y.tab.c"
    break;

  case 74: /* stmt: GVAR '=' OP4 '(' expr ',' vargs ')'  */
#line 248 "bt_parse.y"
                                                { (yyval.v.stmt) = bh_inc((yyvsp[-7].v.string), (yyvsp[-3].v.arg), (yyvsp[-1].v.arg)); }
#line 1768 "y.tab.c"
    break;

  case 75: /* stmtblck: IF '(' expr ')' block  */
#line 251 "bt_parse.y"
                                                { (yyval.v.stmt) = bt_new((yyvsp[-2].v.arg), (yyvsp[0].v.stmt), NULL); }
#line 1774 "y.tab.c"
    break;

  case 76: /* stmtblck: IF '(' expr ')' block ELSE block  */
#line 252 "bt_parse.y"
                                                { (yyval.v.stmt) = bt_new((yyvsp[-4].v.arg), (yyvsp[-2].v.stmt), (yyvsp[0].v.stmt)); }
#line 1780 "y.tab.c"
    break;

  case 77: /* stmtblck: IF '(' expr ')' block ELSE stmtblck  */
#line 253 "bt_parse.y"
                                                { (yyval.v.stmt) = bt_new((yyvsp[-4].v.arg), (yyvsp[-2].v.stmt), (yyvsp[0].v.stmt)); }
#line 1786 "y.tab.c"
    break;

  case 78: /* stmtlist: stmtlist stmtblck  */
#line 256 "bt_parse.y"
                                        { (yyval.v.stmt) = bs_append((yyvsp[-1].v.stmt), (yyvsp[0].v.stmt)); }
#line 1792 "y.tab.c"
    break;

  case 79: /* stmtlist: stmtlist stmt  */
#line 257 "bt_parse.y"
                                        { (yyval.v.stmt) = bs_append((yyvsp[-1].v.stmt), (yyvsp[0].v.stmt)); }
#line 1798 "y.tab.c"
    break;

  case 84: /* action: '{' stmtlist '}'  */
#line 266 "bt_parse.y"
                                        { (yyval.v.stmt) = (yyvsp[-1].v.stmt); }
#line 1804 "y.tab.c"
    break;

  case 85: /* action: '{' '}'  */
#line 267 "bt_parse.y"
                                        { (yyval.v.stmt) = NULL; }
#line 1810 "y.tab.c"
    break;


#line 1814 "y.tab.c"

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

#line 270 "bt_parse.y"


struct bt_arg*
get_varg(int index)
{
	extern int nargs;
	extern char **vargs;
	const char *errstr = NULL;
	long val;

	if (1 <= index && index <= nargs) {
		val = (long)strtonum(vargs[index-1], LONG_MIN, LONG_MAX,
		    &errstr);
		if (errstr == NULL)
			return ba_new(val, B_AT_LONG);
		return ba_new(vargs[index-1], B_AT_STR);
	}

	return ba_new(0L, B_AT_NIL);
}

struct bt_arg*
get_nargs(void)
{
	extern int nargs;

	return ba_new((long) nargs, B_AT_LONG);
}

/* Create a new rule, representing  "probe / filter / { action }" */
struct bt_rule *
br_new(struct bt_probe *probe, struct bt_filter *filter, struct bt_stmt *head)
{
	struct bt_rule *br;

	br = calloc(1, sizeof(*br));
	if (br == NULL)
		err(1, "bt_rule: calloc");
	/* SLIST_INSERT_HEAD() nullify the next pointer. */
	SLIST_FIRST(&br->br_probes) = probe;
	br->br_filter = filter;
	/* SLIST_INSERT_HEAD() nullify the next pointer. */
	SLIST_FIRST(&br->br_action) = head;

	SLIST_FIRST(&br->br_variables) = SLIST_FIRST(&l_variables);
	SLIST_INIT(&l_variables);

	do {
		if (probe->bp_type != B_PT_PROBE)
			continue;
		g_nprobes++;
	} while ((probe = SLIST_NEXT(probe, bp_next)) != NULL);

	TAILQ_INSERT_TAIL(&g_rules, br, br_next);

	return br;
}

/* Create a new condition */
struct bt_filter *
bc_new(struct bt_arg *term, enum bt_argtype op, struct bt_arg *ba)
{
	struct bt_filter *bf;

	bf = calloc(1, sizeof(*bf));
	if (bf == NULL)
		err(1, "bt_filter: calloc");

	bf->bf_condition = bs_new(B_AC_TEST, ba_op(op, term, ba), NULL);

	return bf;
}

/* Create a new if/else test */
struct bt_stmt *
bt_new(struct bt_arg *ba, struct bt_stmt *condbs, struct bt_stmt *elsebs)
{
	struct bt_arg *bop;
	struct bt_cond *bc;

	bop = ba_op(B_AT_OP_NE, NULL, ba);

	bc = calloc(1, sizeof(*bc));
	if (bc == NULL)
		err(1, "bt_cond: calloc");
	bc->bc_condbs = condbs;
	bc->bc_elsebs = elsebs;

	return bs_new(B_AC_TEST, bop, (struct bt_var *)bc);
}

/*
 * interval and profile support the same units.
 */
static uint64_t
bp_unit_to_nsec(const char *unit, long value)
{
	static const struct {
		const char *name;
		enum { UNIT_HZ, UNIT_US, UNIT_MS, UNIT_S } id;
		long long max;
	} units[] = {
		{ .name = "hz", .id = UNIT_HZ, .max = 1000000LL },
		{ .name = "us", .id = UNIT_US, .max = LLONG_MAX / 1000 },
		{ .name = "ms", .id = UNIT_MS, .max = LLONG_MAX / 1000000 },
		{ .name = "s", .id = UNIT_S, .max = LLONG_MAX / 1000000000 },
	};
	size_t i;

	for (i = 0; i < nitems(units); i++) {
		if (strcmp(units[i].name, unit) == 0) {
			if (value < 1)
				yyerror("Number is invalid: %ld", value);
			if (value > units[i].max)
				yyerror("Number is too large: %ld", value);
			switch (units[i].id) {
			case UNIT_HZ:
				return (1000000000LLU / value);
			case UNIT_US:
				return (value * 1000LLU);
			case UNIT_MS:
				return (value * 1000000LLU);
			case UNIT_S:
				return (value * 1000000000LLU);
			}
		}
	}
	yyerror("Invalid unit: %s", unit);
	return 0;
}

/* Create a new probe */
struct bt_probe *
bp_new(const char *prov, const char *func, const char *name, long number)
{
	struct bt_probe *bp;
	enum bt_ptype ptype;

	if (prov == NULL && func == NULL && name == NULL)
		ptype = number; /* BEGIN or END */
	else
		ptype = B_PT_PROBE;

	bp = calloc(1, sizeof(*bp));
	if (bp == NULL)
		err(1, "bt_probe: calloc");
	bp->bp_prov = prov;
	bp->bp_func = func;
	bp->bp_name = name;
	if (ptype == B_PT_PROBE && name == NULL)
		bp->bp_nsecs = bp_unit_to_nsec(func, number);
	bp->bp_type = ptype;

	return bp;
}

/*
 * Link two probes together, to build a probe list attached to
 * a single action.
 */
struct bt_probe *
bp_append(struct bt_probe *bp0, struct bt_probe *bp1)
{
	struct bt_probe *bp = bp0;

	assert(bp1 != NULL);

	if (bp0 == NULL)
		return bp1;

	while (SLIST_NEXT(bp, bp_next) != NULL)
		bp = SLIST_NEXT(bp, bp_next);

	SLIST_INSERT_AFTER(bp, bp1, bp_next);

	return bp0;
}

/* Create a new argument */
struct bt_arg *
ba_new0(void *val, enum bt_argtype type)
{
	struct bt_arg *ba;

	ba = calloc(1, sizeof(*ba));
	if (ba == NULL)
		err(1, "bt_arg: calloc");
	ba->ba_value = val;
	ba->ba_type = type;

	return ba;
}

/*
 * Link two arguments together, to build an argument list used in
 * operators, tuples and function calls.
 */
struct bt_arg *
ba_append(struct bt_arg *da0, struct bt_arg *da1)
{
	struct bt_arg *ba = da0;

	assert(da1 != NULL);

	if (da0 == NULL)
		return da1;

	while (SLIST_NEXT(ba, ba_next) != NULL)
		ba = SLIST_NEXT(ba, ba_next);

	SLIST_INSERT_AFTER(ba, da1, ba_next);

	return da0;
}

/* Create an operator argument */
struct bt_arg *
ba_op(enum bt_argtype op, struct bt_arg *da0, struct bt_arg *da1)
{
	return ba_new(ba_append(da0, da1), op);
}

/* Create a new statement: function call or assignment. */
struct bt_stmt *
bs_new(enum bt_action act, struct bt_arg *head, struct bt_var *var)
{
	struct bt_stmt *bs;

	bs = calloc(1, sizeof(*bs));
	if (bs == NULL)
		err(1, "bt_stmt: calloc");
	bs->bs_act = act;
	bs->bs_var = var;
	/* SLIST_INSERT_HEAD() nullify the next pointer. */
	SLIST_FIRST(&bs->bs_args) = head;

	return bs;
}

/* Link two statements together, to build an 'action'. */
struct bt_stmt *
bs_append(struct bt_stmt *ds0, struct bt_stmt *ds1)
{
	struct bt_stmt *bs = ds0;

	if (ds0 == NULL)
		return ds1;

	if (ds1 == NULL)
		return ds0;

	while (SLIST_NEXT(bs, bs_next) != NULL)
		bs = SLIST_NEXT(bs, bs_next);

	SLIST_INSERT_AFTER(bs, ds1, bs_next);

	return ds0;
}

const char *
bv_name(struct bt_var *bv)
{
	if (strncmp(bv->bv_name, UNNAMED_MAP, strlen(UNNAMED_MAP)) == 0)
		return "";
	return bv->bv_name;
}

/* Allocate a variable. */
struct bt_var *
bv_new(const char *vname)
{
	struct bt_var *bv;

	bv = calloc(1, sizeof(*bv));
	if (bv == NULL)
		err(1, "bt_var: calloc");
	bv->bv_name = vname;

	return bv;
}

/* Return the global variable corresponding to `vname'. */
struct bt_var *
bg_lookup(const char *vname)
{
	struct bt_var *bv;

	SLIST_FOREACH(bv, &g_variables, bv_next) {
		if (strcmp(vname, bv->bv_name) == 0)
			break;
	}

	return bv;
}

/* Find or allocate a global variable corresponding to `vname' */
struct bt_var *
bg_get(const char *vname)
{
	struct bt_var *bv;

	bv = bg_lookup(vname);
	if (bv == NULL) {
		bv = bv_new(vname);
		SLIST_INSERT_HEAD(&g_variables, bv, bv_next);
	}

	return bv;
}

/* Create an "argument" that points to an existing untyped variable. */
struct bt_arg *
bg_find(const char *vname)
{
	return ba_new(bg_get(vname), B_AT_VAR);
}

/* Create a 'store' statement to assign a value to a global variable. */
struct bt_stmt *
bg_store(const char *vname, struct bt_arg *vval)
{
	return bs_new(B_AC_STORE, vval, bg_get(vname));
}

/* Return the local variable corresponding to `vname'. */
struct bt_var *
bl_lookup(const char *vname)
{
	struct bt_var *bv;

	SLIST_FOREACH(bv, &l_variables, bv_next) {
		if (strcmp(vname, bv->bv_name) == 0)
			break;
	}

	return bv;
}

/* Find or create a local variable corresponding to `vname' */
struct bt_arg *
bl_find(const char *vname)
{
	struct bt_var *bv;

	bv = bl_lookup(vname);
	if (bv == NULL) {
		bv = bv_new(vname);
		SLIST_INSERT_HEAD(&l_variables, bv, bv_next);
	}

	return ba_new(bv, B_AT_VAR);
}

/* Create a 'store' statement to assign a value to a local variable. */
struct bt_stmt *
bl_store(const char *vname, struct bt_arg *vval)
{
	struct bt_var *bv;

	bv = bl_lookup(vname);
	if (bv == NULL) {
		bv = bv_new(vname);
		SLIST_INSERT_HEAD(&l_variables, bv, bv_next);
	}

	return bs_new(B_AC_STORE, vval, bv);
}

/* Create an argument that points to a tuple variable and a given index */
struct bt_arg *
bi_find(struct bt_arg *ba, unsigned long index)
{
	struct bt_var *bv = ba->ba_value;

	ba = ba_new(bv, B_AT_TMEMBER);
	ba->ba_key = (void *)index;
	return ba;
}

struct bt_stmt *
bm_op(enum bt_action mact, struct bt_arg *ba, struct bt_arg *mval)
{
	return bs_new(mact, ba, (struct bt_var *)mval);
}

/* Create a 'map store' statement to assign a value to a map entry. */
struct bt_stmt *
bm_insert(const char *mname, struct bt_arg *mkey, struct bt_arg *mval)
{
	struct bt_arg *ba;

	if (mkey->ba_type == B_AT_TUPLE)
		yyerror("tuple cannot be used as map key");

	ba = ba_new(bg_get(mname), B_AT_MAP);
	ba->ba_key = mkey;

	return bs_new(B_AC_INSERT, ba, (struct bt_var *)mval);
}

/* Create an argument that points to a map variable and attach a key to it. */
struct bt_arg *
bm_find(const char *vname, struct bt_arg *mkey)
{
	struct bt_arg *ba;

	ba = ba_new(bg_get(vname), B_AT_MAP);
	ba->ba_key = mkey;
	return ba;
}

/*
 * Histograms implemented using associative arrays (maps).  In the case
 * of linear histograms `ba_key' points to a list of (min, max, step)
 * necessary to "bucketize" any value.
 */
struct bt_stmt *
bh_inc(const char *hname, struct bt_arg *hval, struct bt_arg *hrange)
{
	struct bt_arg *ba;

	if (hrange == NULL) {
		/* Power-of-2 histogram */
	} else {
		long min = 0, max;
		int count = 0;

		/* Linear histogram */
		for (ba = hrange; ba != NULL; ba = SLIST_NEXT(ba, ba_next)) {
			if (++count > 3)
				yyerror("too many arguments");
			if (ba->ba_type != B_AT_LONG)
				yyerror("type invalid");

			switch (count) {
			case 1:
				min = (long)ba->ba_value;
				if (min >= 0)
					break;
				yyerror("negative minimum");
			case 2:
				max = (long)ba->ba_value;
				if (max > min)
					break;
				yyerror("maximum smaller than minimum (%d < %d)",
				    max,  min);
			case 3:
				break;
			default:
				assert(0);
			}
		}
		if (count < 3)
			yyerror("%d missing arguments", 3 - count);
	}

	ba = ba_new(bg_get(hname), B_AT_HIST);
	ba->ba_key = hrange;
	return bs_new(B_AC_BUCKETIZE, ba, (struct bt_var *)hval);
}

struct keyword {
	const char	*word;
	int		 token;
	int		 type;
};

int
kw_cmp(const void *str, const void *xkw)
{
	return (strcmp(str, ((const struct keyword *)xkw)->word));
}

struct keyword *
lookup(char *s)
{
	static const struct keyword kws[] = {
		{ "BEGIN",	BEGIN,		B_PT_BEGIN },
		{ "END",	END,		B_PT_END },
		{ "arg0",	BUILTIN,	B_AT_BI_ARG0 },
		{ "arg1",	BUILTIN,	B_AT_BI_ARG1 },
		{ "arg2",	BUILTIN,	B_AT_BI_ARG2 },
		{ "arg3",	BUILTIN,	B_AT_BI_ARG3 },
		{ "arg4",	BUILTIN,	B_AT_BI_ARG4 },
		{ "arg5",	BUILTIN,	B_AT_BI_ARG5 },
		{ "arg6",	BUILTIN,	B_AT_BI_ARG6 },
		{ "arg7",	BUILTIN,	B_AT_BI_ARG7 },
		{ "arg8",	BUILTIN,	B_AT_BI_ARG8 },
		{ "arg9",	BUILTIN,	B_AT_BI_ARG9 },
		{ "clear",	MFUNC,		B_AC_CLEAR },
		{ "comm",	BUILTIN,	B_AT_BI_COMM },
		{ "count",	MOP0, 		B_AT_MF_COUNT },
		{ "cpu",	BUILTIN,	B_AT_BI_CPU },
		{ "delete",	F_DELETE,	B_AC_DELETE },
		{ "else",	ELSE,		0 },
		{ "exit",	FUNC0,		B_AC_EXIT },
		{ "hist",	OP1,		0 },
		{ "if",		IF,		0 },
		{ "kstack",	BUILTIN,	B_AT_BI_KSTACK },
		{ "lhist",	OP4,		0 },
		{ "max",	MOP1,		B_AT_MF_MAX },
		{ "min",	MOP1,		B_AT_MF_MIN },
		{ "nsecs",	BUILTIN,	B_AT_BI_NSECS },
		{ "pid",	BUILTIN,	B_AT_BI_PID },
		{ "print",	F_PRINT,	B_AC_PRINT },
		{ "printf",	FUNCN,		B_AC_PRINTF },
		{ "probe",	BUILTIN,	B_AT_BI_PROBE },
		{ "retval",	BUILTIN,	B_AT_BI_RETVAL },
		{ "str",	STR,		B_AT_FN_STR },
		{ "sum",	MOP1,		B_AT_MF_SUM },
		{ "tid",	BUILTIN,	B_AT_BI_TID },
		{ "time",	FUNC1,		B_AC_TIME },
		{ "ustack",	BUILTIN,	B_AT_BI_USTACK },
		{ "zero",	MFUNC,		B_AC_ZERO },
	};

	return bsearch(s, kws, nitems(kws), sizeof(kws[0]), kw_cmp);
}

int
peek(void)
{
	if (pbuf != NULL) {
		if (pindex < plen)
			return pbuf[pindex];
	}
	return EOF;
}

int
lgetc(void)
{
	if (pbuf != NULL) {
		if (pindex < plen) {
			yylval.colno++;
			return pbuf[pindex++];
		}
	}
	return EOF;
}

void
lungetc(void)
{
	if (pbuf != NULL && pindex > 0) {
		yylval.colno--;
		pindex--;
	}
}

static inline int
allowed_to_end_number(int x)
{
	return (isspace(x) || x == ')' || x == '/' || x == '{' || x == ';' ||
	    x == ']' || x == ',' || x == '=');
}

static inline int
allowed_in_string(int x)
{
	return (isalnum(x) || x == '_');
}

static int
skip(void)
{
	int c;

again:
	/* skip whitespaces */
	for (c = lgetc(); isspace(c); c = lgetc()) {
		if (c == '\n') {
			yylval.lineno++;
			yylval.colno = 0;
		}
	}

	/* skip single line comments and shell magic */
	if ((c == '/' && peek() == '/') ||
	    (yylval.lineno == 1 && yylval.colno == 1 && c == '#' &&
	     peek() == '!')) {
		for (c = lgetc(); c != EOF; c = lgetc()) {
			if (c == '\n') {
				yylval.lineno++;
				yylval.colno = 0;
				goto again;
			}
		}
	}

	/* skip multi line comments */
	if (c == '/' && peek() == '*') {
		int pc;

		for (pc = 0, c = lgetc(); c != EOF; c = lgetc()) {
			if (pc == '*' && c == '/')
				goto again;
			else if (c == '\n')
				yylval.lineno++;
			pc = c;
		}
	}

	return c;
}

int
yylex(void)
{
	unsigned char	 buf[1024];
	unsigned char	*ebuf, *p, *str;
	int		 c;

	ebuf = buf + sizeof(buf);
	p = buf;

again:
	c = skip();

	switch (c) {
	case '!':
	case '=':
		if (peek() == '=') {
			lgetc();
			return (c == '=') ? OP_EQ : OP_NE;
		}
		return c;
	case '<':
		if (peek() == '=') {
			lgetc();
			return OP_LE;
		}
		return OP_LT;
	case '>':
		if (peek() == '=') {
			lgetc();
			return OP_GE;
		}
		return OP_GT;
	case '&':
		if (peek() == '&') {
			lgetc();
			return OP_LAND;
		}
		return c;
	case '|':
		if (peek() == '|') {
			lgetc();
			return OP_LOR;
		}
		return c;
	case '/':
		while (isspace(peek())) {
			if (lgetc() == '\n') {
				yylval.lineno++;
				yylval.colno = 0;
			}
		}
		if (peek() == '{' || peek() == '/' || peek() == '\n')
			return ENDFILT;
		/* FALLTHROUGH */
	case ',':
	case '(':
	case ')':
	case '{':
	case '}':
	case ':':
	case ';':
		return c;
	case '$':
		c = lgetc();
		if (c == '#') {
			yylval.v.arg = get_nargs();
			return PNUM;
		} else if (isdigit(c)) {
			do {
				*p++ = c;
				if (p == ebuf) {
					yyerror("line too long");
					return ERROR;
				}
			} while ((c = lgetc()) != EOF && isdigit(c));
			lungetc();
			*p = '\0';
			if (c == EOF || allowed_to_end_number(c)) {
				const char *errstr = NULL;
				int num;

				num = strtonum(buf, 1, INT_MAX, &errstr);
				if (errstr) {
					yyerror("'$%s' is %s", buf, errstr);
					return ERROR;
				}

				yylval.v.arg = get_varg(num);
				return PVAR;
			}
		} else if (isalpha(c)) {
			do {
				*p++ = c;
				if (p == ebuf) {
					yyerror("line too long");
					return ERROR;
				}
			} while ((c = lgetc()) != EOF && allowed_in_string(c));
			lungetc();
			*p = '\0';
			if ((yylval.v.string = strdup(buf)) == NULL)
				err(1, "%s", __func__);
			return LVAR;
		}
		yyerror("'$%s%c' is an invalid variable name", buf, c);
		return ERROR;
		break;
	case '@':
		c = lgetc();
		/* check for unnamed map '@' */
		if (isalpha(c)) {
			do {
				*p++ = c;
				if (p == ebuf) {
					yyerror("line too long");
					return ERROR;
				}
			} while ((c = lgetc()) != EOF && allowed_in_string(c));
			lungetc();
			*p = '\0';
			if ((yylval.v.string = strdup(buf)) == NULL)
				err(1, "%s", __func__);
			return GVAR;
		} else if (allowed_to_end_number(c) || c == '[') {
			lungetc();
			*p = '\0';
			yylval.v.string = UNNAMED_MAP;
			return GVAR;
		}
		yyerror("'@%s%c' is an invalid variable name", buf, c);
		return ERROR;
		break;
	case EOF:
		return 0;
	case '"':
		/* parse C-like string */
		while ((c = lgetc()) != EOF) {
			if (c == '"') {
				/* handle multi-line strings */
				c = skip();
				if (c == '"')
					continue;
				else
					lungetc();
				break;
			}
			if (c == '\\') {
				c = lgetc();
				switch (c) {
				case '\\':	c = '\\';	break;
				case '\'':	c = '\'';	break;
				case '"':	c = '"';	break;
				case 'a':	c = '\a';	break;
				case 'b':	c = '\b';	break;
				case 'e':	c = 033;	break;
				case 'f':	c = '\f';	break;
				case 'n':	c = '\n';	break;
				case 'r':	c = '\r';	break;
				case 't':	c = '\t';	break;
				case 'v':	c = '\v';	break;
				default:
					yyerror("'%c' unsupported escape", c);
					return ERROR;
				}
			}
			*p++ = c;
			if (p == ebuf) {
				yyerror("line too long");
				return ERROR;
			}
		}
		if (c == EOF) {
			yyerror("\"%s\" invalid EOF", buf);
			return ERROR;
		}
		*p++ = '\0';
		if ((str = strdup(buf)) == NULL)
			err(1, "%s", __func__);
		yylval.v.string = str;
		return CSTRING;
	default:
		break;
	}

	/* parsing number */
	if (isdigit(c)) {
		do {
			*p++ = c;
			if (p == ebuf) {
				yyerror("line too long");
				return ERROR;
			}
		} while ((c = lgetc()) != EOF &&
		    (isxdigit(c) || c == 'x' || c == 'X'));
		lungetc();
		if (c == EOF || allowed_to_end_number(c)) {
			*p = '\0';
			errno = 0;
			yylval.v.number = strtol(buf, NULL, 0);
			if (errno == ERANGE) {
				/*
				 * Characters are already validated, so only
				 * check ERANGE.
				 */
				yyerror("%sflow", (yylval.v.number == LONG_MIN)
				    ? "under" : "over");
				return ERROR;
			}
			return NUMBER;
		} else {
			while (p > buf + 1) {
				--p;
				lungetc();
			}
			c = *--p;
		}
	}

	/* parsing next word */
	if (allowed_in_string(c)) {
		struct keyword *kwp;
		do {
			*p++ = c;
			if (p == ebuf) {
				yyerror("line too long");
				return ERROR;
			}
		} while ((c = lgetc()) != EOF && (allowed_in_string(c)));
		lungetc();
		*p = '\0';
		kwp = lookup(buf);
		if (kwp == NULL) {
			if ((yylval.v.string = strdup(buf)) == NULL)
				err(1, "%s", __func__);
			return STRING;
		}
		if (pflag) {
			/*
			 * Probe lexer backdoor, interpret the token as a string
			 * rather than a keyword. Otherwise, reserved keywords
			 * would conflict with syscall names.
			 */
			yylval.v.string = kwp->word;
			return STRING;
		} else if (beflag) {
			/* Interpret tokens in a BEGIN/END context. */
			if (kwp->type >= B_AT_BI_ARG0 &&
			    kwp->type <= B_AT_BI_ARG9)
				yyerror("the %s builtin cannot be used with "
				    "BEGIN or END probes", kwp->word);
		}
		yylval.v.i = kwp->type;
		return kwp->token;
	}

	if (c == '\n') {
		yylval.lineno++;
		yylval.colno = 0;
	}
	if (c == EOF)
		return 0;
	return c;
}

void
pprint_syntax_error(void)
{
	char line[BUFSIZ];
	int c, indent = yylval.colno;
	size_t i;

	strlcpy(line, &pbuf[pindex - yylval.colno], sizeof(line));

	for (i = 0; line[i] != '\0' && (c = line[i]) != '\n'; i++) {
		if (c == '\t')
			indent += (8 - 1);
		fputc(c, stderr);
	}

	fprintf(stderr, "\n%*c\n", indent, '^');
}

void
yyerror(const char *fmt, ...)
{
	const char *prefix;
	va_list	va;

	prefix = (yylval.filename != NULL) ? yylval.filename : getprogname();

	fprintf(stderr, "%s:%d:%d: ", prefix, yylval.lineno, yylval.colno);
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
	fprintf(stderr, ":\n");

	pprint_syntax_error();

	perrors++;
}

int
btparse(const char *str, size_t len, const char *filename, int debug)
{
	if (debug > 0)
		yydebug = 1;
	pbuf = str;
	plen = len;
	pindex = 0;
	yylval.filename = filename;
	yylval.lineno = 1;

	yyparse();
	if (perrors)
		return perrors;

	assert(SLIST_EMPTY(&l_variables));

	return 0;
}
