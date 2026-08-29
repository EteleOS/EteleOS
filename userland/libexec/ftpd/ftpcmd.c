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
#line 40 "ftpcmd.y"


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <netinet/in.h>
#include <arpa/ftp.h>

#include <ctype.h>
#include <errno.h>
#include <glob.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <limits.h>

#include "monitor.h"
#include "extern.h"

extern	union sockunion data_dest;
extern	int logged_in;
extern	struct passwd *pw;
extern	int guest;
extern	int logging;
extern	int type;
extern	int form;
extern	int debug;
extern	int timeout;
extern	int maxtimeout;
extern  int pdata;
extern	char hostname[], remotehost[];
extern	char proctitle[];
extern	int usedefault;
extern  int transflag;
extern  char tmpline[];
extern	int portcheck;
extern	union sockunion his_addr;
extern	int umaskchange;

off_t	restart_point;

static	int cmd_type;
static	int cmd_form;
static	int cmd_bytesz;
static	int state;
static	int quit;
char	cbuf[512];
char	*fromname;


#line 129 "y.tab.c"

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
    A = 258,                       /* A  */
    B = 259,                       /* B  */
    C = 260,                       /* C  */
    E = 261,                       /* E  */
    F = 262,                       /* F  */
    I = 263,                       /* I  */
    L = 264,                       /* L  */
    N = 265,                       /* N  */
    P = 266,                       /* P  */
    R = 267,                       /* R  */
    S = 268,                       /* S  */
    T = 269,                       /* T  */
    SP = 270,                      /* SP  */
    CRLF = 271,                    /* CRLF  */
    COMMA = 272,                   /* COMMA  */
    ALL = 273,                     /* ALL  */
    USER = 274,                    /* USER  */
    PASS = 275,                    /* PASS  */
    ACCT = 276,                    /* ACCT  */
    REIN = 277,                    /* REIN  */
    QUIT = 278,                    /* QUIT  */
    PORT = 279,                    /* PORT  */
    PASV = 280,                    /* PASV  */
    TYPE = 281,                    /* TYPE  */
    STRU = 282,                    /* STRU  */
    MODE = 283,                    /* MODE  */
    RETR = 284,                    /* RETR  */
    STOR = 285,                    /* STOR  */
    APPE = 286,                    /* APPE  */
    MLFL = 287,                    /* MLFL  */
    MAIL = 288,                    /* MAIL  */
    MSND = 289,                    /* MSND  */
    MSOM = 290,                    /* MSOM  */
    MSAM = 291,                    /* MSAM  */
    MRSQ = 292,                    /* MRSQ  */
    MRCP = 293,                    /* MRCP  */
    ALLO = 294,                    /* ALLO  */
    REST = 295,                    /* REST  */
    RNFR = 296,                    /* RNFR  */
    RNTO = 297,                    /* RNTO  */
    ABOR = 298,                    /* ABOR  */
    DELE = 299,                    /* DELE  */
    CWD = 300,                     /* CWD  */
    LIST = 301,                    /* LIST  */
    NLST = 302,                    /* NLST  */
    SITE = 303,                    /* SITE  */
    STAT = 304,                    /* STAT  */
    HELP = 305,                    /* HELP  */
    NOOP = 306,                    /* NOOP  */
    MKD = 307,                     /* MKD  */
    RMD = 308,                     /* RMD  */
    PWD = 309,                     /* PWD  */
    CDUP = 310,                    /* CDUP  */
    STOU = 311,                    /* STOU  */
    SMNT = 312,                    /* SMNT  */
    SYST = 313,                    /* SYST  */
    SIZE = 314,                    /* SIZE  */
    MDTM = 315,                    /* MDTM  */
    LPRT = 316,                    /* LPRT  */
    LPSV = 317,                    /* LPSV  */
    EPRT = 318,                    /* EPRT  */
    EPSV = 319,                    /* EPSV  */
    UMASK = 320,                   /* UMASK  */
    IDLE = 321,                    /* IDLE  */
    CHMOD = 322,                   /* CHMOD  */
    LEXERR = 323,                  /* LEXERR  */
    STRING = 324,                  /* STRING  */
    NUMBER = 325,                  /* NUMBER  */
    BIGNUM = 326                   /* BIGNUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define A 258
#define B 259
#define C 260
#define E 261
#define F 262
#define I 263
#define L 264
#define N 265
#define P 266
#define R 267
#define S 268
#define T 269
#define SP 270
#define CRLF 271
#define COMMA 272
#define ALL 273
#define USER 274
#define PASS 275
#define ACCT 276
#define REIN 277
#define QUIT 278
#define PORT 279
#define PASV 280
#define TYPE 281
#define STRU 282
#define MODE 283
#define RETR 284
#define STOR 285
#define APPE 286
#define MLFL 287
#define MAIL 288
#define MSND 289
#define MSOM 290
#define MSAM 291
#define MRSQ 292
#define MRCP 293
#define ALLO 294
#define REST 295
#define RNFR 296
#define RNTO 297
#define ABOR 298
#define DELE 299
#define CWD 300
#define LIST 301
#define NLST 302
#define SITE 303
#define STAT 304
#define HELP 305
#define NOOP 306
#define MKD 307
#define RMD 308
#define PWD 309
#define CDUP 310
#define STOU 311
#define SMNT 312
#define SYST 313
#define SIZE 314
#define MDTM 315
#define LPRT 316
#define LPSV 317
#define EPRT 318
#define EPSV 319
#define UMASK 320
#define IDLE 321
#define CHMOD 322
#define LEXERR 323
#define STRING 324
#define NUMBER 325
#define BIGNUM 326

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 98 "ftpcmd.y"

	int	i;
	off_t	o;
	char   *s;

#line 327 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_A = 3,                          /* A  */
  YYSYMBOL_B = 4,                          /* B  */
  YYSYMBOL_C = 5,                          /* C  */
  YYSYMBOL_E = 6,                          /* E  */
  YYSYMBOL_F = 7,                          /* F  */
  YYSYMBOL_I = 8,                          /* I  */
  YYSYMBOL_L = 9,                          /* L  */
  YYSYMBOL_N = 10,                         /* N  */
  YYSYMBOL_P = 11,                         /* P  */
  YYSYMBOL_R = 12,                         /* R  */
  YYSYMBOL_S = 13,                         /* S  */
  YYSYMBOL_T = 14,                         /* T  */
  YYSYMBOL_SP = 15,                        /* SP  */
  YYSYMBOL_CRLF = 16,                      /* CRLF  */
  YYSYMBOL_COMMA = 17,                     /* COMMA  */
  YYSYMBOL_ALL = 18,                       /* ALL  */
  YYSYMBOL_USER = 19,                      /* USER  */
  YYSYMBOL_PASS = 20,                      /* PASS  */
  YYSYMBOL_ACCT = 21,                      /* ACCT  */
  YYSYMBOL_REIN = 22,                      /* REIN  */
  YYSYMBOL_QUIT = 23,                      /* QUIT  */
  YYSYMBOL_PORT = 24,                      /* PORT  */
  YYSYMBOL_PASV = 25,                      /* PASV  */
  YYSYMBOL_TYPE = 26,                      /* TYPE  */
  YYSYMBOL_STRU = 27,                      /* STRU  */
  YYSYMBOL_MODE = 28,                      /* MODE  */
  YYSYMBOL_RETR = 29,                      /* RETR  */
  YYSYMBOL_STOR = 30,                      /* STOR  */
  YYSYMBOL_APPE = 31,                      /* APPE  */
  YYSYMBOL_MLFL = 32,                      /* MLFL  */
  YYSYMBOL_MAIL = 33,                      /* MAIL  */
  YYSYMBOL_MSND = 34,                      /* MSND  */
  YYSYMBOL_MSOM = 35,                      /* MSOM  */
  YYSYMBOL_MSAM = 36,                      /* MSAM  */
  YYSYMBOL_MRSQ = 37,                      /* MRSQ  */
  YYSYMBOL_MRCP = 38,                      /* MRCP  */
  YYSYMBOL_ALLO = 39,                      /* ALLO  */
  YYSYMBOL_REST = 40,                      /* REST  */
  YYSYMBOL_RNFR = 41,                      /* RNFR  */
  YYSYMBOL_RNTO = 42,                      /* RNTO  */
  YYSYMBOL_ABOR = 43,                      /* ABOR  */
  YYSYMBOL_DELE = 44,                      /* DELE  */
  YYSYMBOL_CWD = 45,                       /* CWD  */
  YYSYMBOL_LIST = 46,                      /* LIST  */
  YYSYMBOL_NLST = 47,                      /* NLST  */
  YYSYMBOL_SITE = 48,                      /* SITE  */
  YYSYMBOL_STAT = 49,                      /* STAT  */
  YYSYMBOL_HELP = 50,                      /* HELP  */
  YYSYMBOL_NOOP = 51,                      /* NOOP  */
  YYSYMBOL_MKD = 52,                       /* MKD  */
  YYSYMBOL_RMD = 53,                       /* RMD  */
  YYSYMBOL_PWD = 54,                       /* PWD  */
  YYSYMBOL_CDUP = 55,                      /* CDUP  */
  YYSYMBOL_STOU = 56,                      /* STOU  */
  YYSYMBOL_SMNT = 57,                      /* SMNT  */
  YYSYMBOL_SYST = 58,                      /* SYST  */
  YYSYMBOL_SIZE = 59,                      /* SIZE  */
  YYSYMBOL_MDTM = 60,                      /* MDTM  */
  YYSYMBOL_LPRT = 61,                      /* LPRT  */
  YYSYMBOL_LPSV = 62,                      /* LPSV  */
  YYSYMBOL_EPRT = 63,                      /* EPRT  */
  YYSYMBOL_EPSV = 64,                      /* EPSV  */
  YYSYMBOL_UMASK = 65,                     /* UMASK  */
  YYSYMBOL_IDLE = 66,                      /* IDLE  */
  YYSYMBOL_CHMOD = 67,                     /* CHMOD  */
  YYSYMBOL_LEXERR = 68,                    /* LEXERR  */
  YYSYMBOL_STRING = 69,                    /* STRING  */
  YYSYMBOL_NUMBER = 70,                    /* NUMBER  */
  YYSYMBOL_BIGNUM = 71,                    /* BIGNUM  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_cmd_list = 73,                  /* cmd_list  */
  YYSYMBOL_cmd = 74,                       /* cmd  */
  YYSYMBOL_rcmd = 75,                      /* rcmd  */
  YYSYMBOL_username = 76,                  /* username  */
  YYSYMBOL_password = 77,                  /* password  */
  YYSYMBOL_byte_size = 78,                 /* byte_size  */
  YYSYMBOL_file_size = 79,                 /* file_size  */
  YYSYMBOL_host_port = 80,                 /* host_port  */
  YYSYMBOL_host_long_port4 = 81,           /* host_long_port4  */
  YYSYMBOL_host_long_port6 = 82,           /* host_long_port6  */
  YYSYMBOL_form_code = 83,                 /* form_code  */
  YYSYMBOL_type_code = 84,                 /* type_code  */
  YYSYMBOL_struct_code = 85,               /* struct_code  */
  YYSYMBOL_mode_code = 86,                 /* mode_code  */
  YYSYMBOL_pathname = 87,                  /* pathname  */
  YYSYMBOL_pathstring = 88,                /* pathstring  */
  YYSYMBOL_octal_number = 89,              /* octal_number  */
  YYSYMBOL_check_login = 90,               /* check_login  */
  YYSYMBOL_check_login_epsvall = 91        /* check_login_epsvall  */
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
#define YYLAST   304

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  281

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   139,   139,   140,   148,   152,   157,   167,   196,   215,
     234,   241,   246,   251,   256,   263,   268,   302,   316,   330,
     336,   342,   349,   356,   363,   368,   374,   379,   386,   393,
     398,   405,   420,   425,   430,   437,   441,   457,   461,   468,
     475,   480,   485,   489,   494,   504,   522,   542,   550,   567,
     574,   587,   604,   631,   636,   644,   658,   674,   679,   682,
     686,   690,   694,   701,   723,   750,   799,   803,   807,   814,
     819,   824,   829,   834,   838,   843,   849,   857,   861,   865,
     872,   876,   880,   887,   926,   930,   958,   972
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
  "\"end of file\"", "error", "\"invalid token\"", "A", "B", "C", "E",
  "F", "I", "L", "N", "P", "R", "S", "T", "SP", "CRLF", "COMMA", "ALL",
  "USER", "PASS", "ACCT", "REIN", "QUIT", "PORT", "PASV", "TYPE", "STRU",
  "MODE", "RETR", "STOR", "APPE", "MLFL", "MAIL", "MSND", "MSOM", "MSAM",
  "MRSQ", "MRCP", "ALLO", "REST", "RNFR", "RNTO", "ABOR", "DELE", "CWD",
  "LIST", "NLST", "SITE", "STAT", "HELP", "NOOP", "MKD", "RMD", "PWD",
  "CDUP", "STOU", "SMNT", "SYST", "SIZE", "MDTM", "LPRT", "LPSV", "EPRT",
  "EPSV", "UMASK", "IDLE", "CHMOD", "LEXERR", "STRING", "NUMBER", "BIGNUM",
  "$accept", "cmd_list", "cmd", "rcmd", "username", "password",
  "byte_size", "file_size", "host_port", "host_long_port4",
  "host_long_port6", "form_code", "type_code", "struct_code", "mode_code",
  "pathname", "pathstring", "octal_number", "check_login",
  "check_login_epsvall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-90)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -90,    45,   -90,   -90,    -9,    -2,     1,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,    28,   -90,     0,    44,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,    -6,    14,   -90,    87,   100,   107,   120,   121,
     122,   123,   124,   125,   127,   128,   129,   105,   130,    51,
      62,    64,   -41,    99,    77,   -90,   -90,   132,   133,   134,
     135,   137,   138,   140,   141,   142,   143,   145,   104,   -90,
     146,   -90,   147,    79,   -90,    53,   106,     7,    84,    84,
      84,    88,    55,    84,    84,   -90,    84,    84,   -90,    84,
     -90,    92,   -90,   112,   -90,   -90,    98,    84,   -90,   149,
      84,    84,   -90,   -90,    84,   -90,    84,    84,    96,   -90,
     101,   -15,   -90,   -90,   -90,   150,   152,   154,   156,   -90,
     -13,   157,   -90,   -90,   -90,   158,   -90,   -90,   -90,   159,
     -90,   160,   -90,   161,   162,   114,   -90,   -90,   163,   164,
     165,   166,   167,   168,   169,   103,   -90,   116,   171,   118,
     172,   -90,   173,   174,   175,   176,   177,   170,   178,   179,
     180,   181,   182,   131,   -90,     9,     9,   136,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   187,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   184,   139,   -90,   139,   144,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   148,   -90,   -90,
     -90,   -90,   -90,   185,   -90,   -90,   -90,   -90,   -90,   -90,
     188,   -90,   -90,   189,   192,   194,   191,   151,   153,   -90,
      84,   -90,   155,   195,   197,   199,   200,   183,   -90,   -90,
     186,   202,   203,   190,   193,   205,   207,   196,   198,   -90,
     209,   201,   210,   204,   211,   206,   212,   208,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     -90
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    54,     0,     0,     0,    87,    87,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,     0,    86,     0,     0,    86,    86,
      86,    86,    86,    86,    86,    86,    87,    87,    87,    86,
       3,     4,     0,    58,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,    35,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,     0,     0,    33,     0,
      26,     0,    24,     0,    86,    86,     0,     0,    29,     0,
       0,     0,    40,    41,     0,    50,     0,     0,     0,    12,
       0,     0,    15,     5,     6,     0,     0,    69,    71,    73,
      74,     0,    77,    79,    78,     0,    81,    82,    80,     0,
      84,     0,    83,     0,     0,     0,    61,    62,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     0,     0,     0,    60,    76,
      16,    17,    18,    21,    22,    23,     0,    19,    56,    55,
      31,    30,    34,    27,    25,     0,     0,    44,     0,     0,
      47,    28,    38,    39,    49,    51,    52,     0,     8,     9,
      10,    14,    13,     0,    68,    66,    67,    70,    72,    75,
       0,    43,    85,     0,     0,     0,     0,     0,     0,    45,
       0,    48,     0,     0,     0,     0,     0,     0,    20,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -90,   -90,   -90,   -90,   -90,   -90,    27,   -90,   -90,   -90,
     -90,    35,   -90,   -90,   -90,   -89,   -90,    18,    19,    74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    40,    41,    80,    82,   179,   148,   126,   168,
     169,   217,   131,   135,   139,   141,   142,   223,    47,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     143,   144,   177,   171,   149,   150,    42,   151,   152,   103,
     153,   136,   137,    43,   214,    64,    65,    44,   160,   215,
     138,   162,   163,   216,   104,   164,   105,   165,   166,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     2,     3,    67,    68,    69,
      70,    71,    72,    73,    74,   172,   127,   178,    78,   128,
      66,   129,   130,    79,     4,     5,    97,    98,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    99,   100,   101,
     102,   106,    46,    81,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    83,    33,    34,    35,    36,    37,    38,    39,
      75,    76,    77,   132,   107,   108,    84,   133,   134,   121,
     122,    95,    85,   157,   158,   146,   147,   155,   156,   186,
     187,   196,   197,   199,   200,    86,    87,    88,    89,    90,
      91,   235,    92,    93,    94,    96,   109,   110,   111,   125,
     112,   113,   114,   140,   115,   116,   117,   118,   145,   119,
     120,   154,   123,   124,   159,   161,   167,   173,   174,   175,
     170,   176,   195,   180,   181,   182,   183,   184,   185,   188,
     189,   190,   191,   192,   193,   194,   198,   207,   201,   202,
     203,   204,   205,   206,   208,   209,   210,   211,   212,   220,
     221,   213,   227,   228,   219,   229,   178,   230,   232,   222,
     231,   218,   237,   238,   225,   239,   224,   240,   226,   243,
     244,   233,   247,   234,   248,   236,   251,   253,   255,   257,
     259,     0,   261,     0,   263,     0,   265,     0,   267,     0,
     269,     0,   271,     0,   273,     0,   275,     0,   277,     0,
     279,     0,     0,   241,     0,     0,   242,     0,     0,     0,
     245,     0,     0,   246,     0,     0,   249,     0,   250,     0,
       0,   252,     0,     0,   254,     0,   256,     0,   258,     0,
       0,     0,     0,     0,   260,     0,   262,     0,   264,     0,
     266,     0,   268,     0,   270,     0,   272,     0,   274,     0,
     276,     0,   278,     0,   280
};

static const yytype_int16 yycheck[] =
{
      89,    90,    15,    18,    93,    94,    15,    96,    97,    50,
      99,     4,     5,    15,     5,    15,    16,    16,   107,    10,
      13,   110,   111,    14,    65,   114,    67,   116,   117,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    15,    25,     0,     1,    28,    29,    30,
      31,    32,    33,    34,    35,    70,     3,    70,    39,     6,
      16,     8,     9,    69,    19,    20,    15,    16,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    15,    16,    15,
      16,    62,     8,    69,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    15,    58,    59,    60,    61,    62,    63,    64,
      36,    37,    38,     7,    15,    16,    16,    11,    12,    15,
      16,    16,    15,   104,   105,    70,    71,    15,    16,    15,
      16,    15,    16,    15,    16,    15,    15,    15,    15,    15,
      15,   230,    15,    15,    15,    15,    69,    15,    15,    70,
      16,    16,    15,    69,    16,    15,    15,    15,    70,    16,
      15,    69,    16,    16,    66,    16,    70,    17,    16,    15,
      69,    15,    69,    16,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    15,    17,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    12,
      16,    70,    17,    15,   177,    16,    70,    15,    17,    70,
      16,   176,    17,    16,    70,    16,   198,    17,    70,    17,
      17,    70,    17,    70,    17,    70,    17,    17,    17,    17,
      17,    -1,    17,    -1,    17,    -1,    17,    -1,    17,    -1,
      17,    -1,    17,    -1,    17,    -1,    17,    -1,    17,    -1,
      17,    -1,    -1,    70,    -1,    -1,    70,    -1,    -1,    -1,
      70,    -1,    -1,    70,    -1,    -1,    70,    -1,    70,    -1,
      -1,    70,    -1,    -1,    70,    -1,    70,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    70,    -1,    70,    -1,
      70,    -1,    70,    -1,    70,    -1,    70,    -1,    70,    -1,
      70,    -1,    70,    -1,    70
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    73,     0,     1,    19,    20,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    58,    59,    60,    61,    62,    63,    64,
      74,    75,    15,    15,    16,    91,    91,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    15,    90,    15,    16,    16,    90,    90,    90,
      90,    90,    90,    90,    90,    91,    91,    91,    90,    69,
      76,    69,    77,    15,    16,    15,    15,    15,    15,    15,
      15,    15,    15,    15,    15,    16,    15,    15,    16,    15,
      16,    15,    16,    50,    65,    67,    90,    15,    16,    69,
      15,    15,    16,    16,    15,    16,    15,    15,    15,    16,
      15,    15,    16,    16,    16,    70,    80,     3,     6,     8,
       9,    84,     7,    11,    12,    85,     4,     5,    13,    86,
      69,    87,    88,    87,    87,    70,    70,    71,    79,    87,
      87,    87,    87,    87,    69,    15,    16,    90,    90,    66,
      87,    16,    87,    87,    87,    87,    87,    70,    81,    82,
      69,    18,    70,    17,    16,    15,    15,    15,    70,    78,
      16,    16,    16,    16,    16,    16,    15,    16,    16,    16,
      16,    16,    16,    16,    16,    69,    15,    16,    15,    15,
      16,    16,    16,    16,    16,    16,    16,    17,    16,    16,
      16,    16,    16,    70,     5,    10,    14,    83,    83,    78,
      12,    16,    70,    89,    89,    70,    70,    17,    15,    16,
      15,    16,    17,    70,    70,    87,    70,    17,    16,    16,
      17,    70,    70,    17,    17,    70,    70,    17,    17,    70,
      70,    17,    70,    17,    70,    17,    70,    17,    70,    17,
      70,    17,    70,    17,    70,    17,    70,    17,    70,    17,
      70,    17,    70,    17,    70,    17,    70,    17,    70,    17,
      70
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    75,    76,    77,    77,
      78,    79,    79,    80,    81,    82,    83,    83,    83,    84,
      84,    84,    84,    84,    84,    84,    84,    85,    85,    85,
      86,    86,    86,    87,    88,    89,    90,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     4,     5,     5,     5,
       5,     3,     3,     5,     5,     3,     5,     5,     5,     5,
       9,     5,     5,     5,     3,     5,     3,     5,     5,     3,
       5,     5,     3,     3,     5,     2,     4,     2,     5,     5,
       3,     3,     4,     6,     5,     7,     9,     5,     7,     5,
       3,     5,     5,     2,     1,     5,     5,     1,     0,     1,
       1,     1,     1,    11,    17,    41,     1,     1,     1,     1,
       3,     1,     3,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     0
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
  case 3: /* cmd_list: cmd_list cmd  */
#line 141 "ftpcmd.y"
                {
			if (fromname) {
				free(fromname);
				fromname = NULL;
			}
			restart_point = 0;
		}
#line 1577 "y.tab.c"
    break;

  case 5: /* cmd: USER SP username CRLF  */
#line 153 "ftpcmd.y"
                {
			monitor_user((yyvsp[-1].s));
			free((yyvsp[-1].s));
		}
#line 1586 "y.tab.c"
    break;

  case 6: /* cmd: PASS SP password CRLF  */
#line 158 "ftpcmd.y"
                {
			quit = monitor_pass((yyvsp[-1].s));
			explicit_bzero((yyvsp[-1].s), strlen((yyvsp[-1].s)));
			free((yyvsp[-1].s));

			/* Terminate unprivileged pre-auth slave */
			if (quit)
				_exit(0);
		}
#line 1600 "y.tab.c"
    break;

  case 7: /* cmd: PORT check_login_epsvall SP host_port CRLF  */
#line 168 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				if ((yyvsp[-1].i)) {
					usedefault = 1;
					reply(500,
					    "Illegal PORT rejected (range errors).");
				} else if (portcheck &&
				    ntohs(data_dest.su_sin.sin_port) < IPPORT_RESERVED) {
					usedefault = 1;
					reply(500,
					    "Illegal PORT rejected (reserved port).");
				} else if (portcheck &&
				    memcmp(&data_dest.su_sin.sin_addr,
				    &his_addr.su_sin.sin_addr,
				    sizeof data_dest.su_sin.sin_addr)) {
					usedefault = 1;
					reply(500,
					    "Illegal PORT rejected (address wrong).");
				} else {
					usedefault = 0;
					if (pdata >= 0) {
						(void) close(pdata);
						pdata = -1;
					}
					reply(200, "PORT command successful.");
				}
			}
		}
#line 1633 "y.tab.c"
    break;

  case 8: /* cmd: LPRT check_login_epsvall SP host_long_port4 CRLF  */
#line 197 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				/* reject invalid host_long_port4 */
				if ((yyvsp[-1].i)) {
					reply(500,
					    "Illegal LPRT command rejected");
					usedefault = 1;
				} else {
					usedefault = 0;
					if (pdata >= 0) {
						(void) close(pdata);
						pdata = -1;
					}
					reply(200, "LPRT command successful.");
				}
			}
		}
#line 1655 "y.tab.c"
    break;

  case 9: /* cmd: LPRT check_login_epsvall SP host_long_port6 CRLF  */
#line 216 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				/* reject invalid host_long_port6 */
				if ((yyvsp[-1].i)) {
					reply(500,
					    "Illegal LPRT command rejected");
					usedefault = 1;
				} else {
					usedefault = 0;
					if (pdata >= 0) {
						(void) close(pdata);
						pdata = -1;
					}
					reply(200, "LPRT command successful.");
				}
			}
		}
#line 1677 "y.tab.c"
    break;

  case 10: /* cmd: EPRT check_login_epsvall SP STRING CRLF  */
#line 235 "ftpcmd.y"
                {
			if ((yyvsp[-3].i))
				extended_port((yyvsp[-1].s));
			free((yyvsp[-1].s));
		}
#line 1687 "y.tab.c"
    break;

  case 11: /* cmd: PASV check_login_epsvall CRLF  */
#line 242 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				passive();
		}
#line 1696 "y.tab.c"
    break;

  case 12: /* cmd: LPSV check_login_epsvall CRLF  */
#line 247 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				long_passive("LPSV", PF_UNSPEC);
		}
#line 1705 "y.tab.c"
    break;

  case 13: /* cmd: EPSV check_login SP NUMBER CRLF  */
#line 252 "ftpcmd.y"
                {
			if ((yyvsp[-3].i))
				long_passive("EPSV", epsvproto2af((yyvsp[-1].i)));
		}
#line 1714 "y.tab.c"
    break;

  case 14: /* cmd: EPSV check_login SP ALL CRLF  */
#line 257 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				reply(200, "EPSV ALL command successful.");
				epsvall++;
			}
		}
#line 1725 "y.tab.c"
    break;

  case 15: /* cmd: EPSV check_login CRLF  */
#line 264 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				long_passive("EPSV", PF_UNSPEC);
		}
#line 1734 "y.tab.c"
    break;

  case 16: /* cmd: TYPE check_login SP type_code CRLF  */
#line 269 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				switch (cmd_type) {

				case TYPE_A:
					if (cmd_form == FORM_N) {
						reply(200, "Type set to A.");
						type = cmd_type;
						form = cmd_form;
					} else
						reply(504, "Form must be N.");
					break;

				case TYPE_E:
					reply(504, "Type E not implemented.");
					break;

				case TYPE_I:
					reply(200, "Type set to I.");
					type = cmd_type;
					break;

				case TYPE_L:
					if (cmd_bytesz == 8) {
						reply(200,
						    "Type set to L (byte size 8).");
						    type = cmd_type;
					} else
						reply(504, "Byte size must be 8.");

				}
			}
		}
#line 1772 "y.tab.c"
    break;

  case 17: /* cmd: STRU check_login SP struct_code CRLF  */
#line 303 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				switch ((yyvsp[-1].i)) {

				case STRU_F:
					reply(200, "STRU F ok.");
					break;

				default:
					reply(504, "Unimplemented STRU type.");
				}
			}
		}
#line 1790 "y.tab.c"
    break;

  case 18: /* cmd: MODE check_login SP mode_code CRLF  */
#line 317 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				switch ((yyvsp[-1].i)) {

				case MODE_S:
					reply(200, "MODE S ok.");
					break;

				default:
					reply(502, "Unimplemented MODE type.");
				}
			}
		}
#line 1808 "y.tab.c"
    break;

  case 19: /* cmd: ALLO check_login SP NUMBER CRLF  */
#line 331 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				reply(202, "ALLO command ignored.");
			}
		}
#line 1818 "y.tab.c"
    break;

  case 20: /* cmd: ALLO check_login SP NUMBER SP R SP NUMBER CRLF  */
#line 337 "ftpcmd.y"
                {
			if ((yyvsp[-7].i)) {
				reply(202, "ALLO command ignored.");
			}
		}
#line 1828 "y.tab.c"
    break;

  case 21: /* cmd: RETR check_login SP pathname CRLF  */
#line 343 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				retrieve(RET_FILE, (yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1839 "y.tab.c"
    break;

  case 22: /* cmd: STOR check_login SP pathname CRLF  */
#line 350 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				store((yyvsp[-1].s), "w", 0);
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1850 "y.tab.c"
    break;

  case 23: /* cmd: APPE check_login SP pathname CRLF  */
#line 357 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				store((yyvsp[-1].s), "a", 0);
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1861 "y.tab.c"
    break;

  case 24: /* cmd: NLST check_login CRLF  */
#line 364 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				send_file_list(".");
		}
#line 1870 "y.tab.c"
    break;

  case 25: /* cmd: NLST check_login SP STRING CRLF  */
#line 369 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				send_file_list((yyvsp[-1].s));
			free((yyvsp[-1].s));
		}
#line 1880 "y.tab.c"
    break;

  case 26: /* cmd: LIST check_login CRLF  */
#line 375 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				retrieve(RET_LIST, ".");
		}
#line 1889 "y.tab.c"
    break;

  case 27: /* cmd: LIST check_login SP pathname CRLF  */
#line 380 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				retrieve(RET_LIST, (yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1900 "y.tab.c"
    break;

  case 28: /* cmd: STAT check_login SP pathname CRLF  */
#line 387 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				statfilecmd((yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1911 "y.tab.c"
    break;

  case 29: /* cmd: STAT check_login CRLF  */
#line 394 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				statcmd();
		}
#line 1920 "y.tab.c"
    break;

  case 30: /* cmd: DELE check_login SP pathname CRLF  */
#line 399 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				delete((yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1931 "y.tab.c"
    break;

  case 31: /* cmd: RNTO check_login SP pathname CRLF  */
#line 406 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL) {
				if (fromname) {
					renamecmd(fromname, (yyvsp[-1].s));
					free(fromname);
					fromname = NULL;
				} else {
					reply(503,
					  "Bad sequence of commands.");
				}
			}
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1950 "y.tab.c"
    break;

  case 32: /* cmd: ABOR check_login CRLF  */
#line 421 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				reply(225, "ABOR command successful.");
		}
#line 1959 "y.tab.c"
    break;

  case 33: /* cmd: CWD check_login CRLF  */
#line 426 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				cwd(pw->pw_dir);
		}
#line 1968 "y.tab.c"
    break;

  case 34: /* cmd: CWD check_login SP pathname CRLF  */
#line 431 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				cwd((yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 1979 "y.tab.c"
    break;

  case 35: /* cmd: HELP CRLF  */
#line 438 "ftpcmd.y"
                {
			help(cmdtab, NULL);
		}
#line 1987 "y.tab.c"
    break;

  case 36: /* cmd: HELP SP STRING CRLF  */
#line 442 "ftpcmd.y"
                {
			char *cp = (yyvsp[-1].s);

			if (strncasecmp(cp, "SITE", 4) == 0) {
				cp = (yyvsp[-1].s) + 4;
				if (*cp == ' ')
					cp++;
				if (*cp)
					help(sitetab, cp);
				else
					help(sitetab, NULL);
			} else
				help(cmdtab, (yyvsp[-1].s));
			free ((yyvsp[-1].s));
		}
#line 2007 "y.tab.c"
    break;

  case 37: /* cmd: NOOP CRLF  */
#line 458 "ftpcmd.y"
                {
			reply(200, "NOOP command successful.");
		}
#line 2015 "y.tab.c"
    break;

  case 38: /* cmd: MKD check_login SP pathname CRLF  */
#line 462 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				makedir((yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 2026 "y.tab.c"
    break;

  case 39: /* cmd: RMD check_login SP pathname CRLF  */
#line 469 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				removedir((yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 2037 "y.tab.c"
    break;

  case 40: /* cmd: PWD check_login CRLF  */
#line 476 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				pwd();
		}
#line 2046 "y.tab.c"
    break;

  case 41: /* cmd: CDUP check_login CRLF  */
#line 481 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
				cwd("..");
		}
#line 2055 "y.tab.c"
    break;

  case 42: /* cmd: SITE SP HELP CRLF  */
#line 486 "ftpcmd.y"
                {
			help(sitetab, NULL);
		}
#line 2063 "y.tab.c"
    break;

  case 43: /* cmd: SITE SP HELP SP STRING CRLF  */
#line 490 "ftpcmd.y"
                {
			help(sitetab, (yyvsp[-1].s));
			free ((yyvsp[-1].s));
		}
#line 2072 "y.tab.c"
    break;

  case 44: /* cmd: SITE SP UMASK check_login CRLF  */
#line 495 "ftpcmd.y"
                {
			mode_t oldmask;

			if ((yyvsp[-1].i)) {
				oldmask = umask(0);
				(void) umask(oldmask);
				reply(200, "Current UMASK is %03o", oldmask);
			}
		}
#line 2086 "y.tab.c"
    break;

  case 45: /* cmd: SITE SP UMASK check_login SP octal_number CRLF  */
#line 505 "ftpcmd.y"
                {
			mode_t oldmask;

			if ((yyvsp[-3].i)) {
				if (((yyvsp[-1].i) == -1) || ((yyvsp[-1].i) > 0777)) {
					reply(501, "Bad UMASK value");
				} else if (!umaskchange) {
					reply(550,
					    "No permission to change umask.");
				} else {
					oldmask = umask((yyvsp[-1].i));
					reply(200,
					    "UMASK set to %03o (was %03o)",
					    (yyvsp[-1].i), oldmask);
				}
			}
		}
#line 2108 "y.tab.c"
    break;

  case 46: /* cmd: SITE SP CHMOD check_login SP octal_number SP pathname CRLF  */
#line 523 "ftpcmd.y"
                {
			if ((yyvsp[-5].i) && ((yyvsp[-1].s) != NULL)) {
				if (((yyvsp[-3].i) == -1) || ((yyvsp[-3].i) > 0777))
					reply(501,
					    "CHMOD: Mode value must be between "
					    "0 and 0777");
				else if (!umaskchange)
					reply(550,
					    "No permission to change mode of %s.",
					    (yyvsp[-1].s));
				else if (chmod((yyvsp[-1].s), (yyvsp[-3].i)) == -1)
					perror_reply(550, (yyvsp[-1].s));
				else
					reply(200,
					    "CHMOD command successful.");
			}
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 2132 "y.tab.c"
    break;

  case 47: /* cmd: SITE SP check_login IDLE CRLF  */
#line 543 "ftpcmd.y"
                {
			if ((yyvsp[-2].i))
				reply(200,
				    "Current IDLE time limit is %d "
				    "seconds; max %d",
				    timeout, maxtimeout);
		}
#line 2144 "y.tab.c"
    break;

  case 48: /* cmd: SITE SP check_login IDLE SP NUMBER CRLF  */
#line 551 "ftpcmd.y"
                {
			if ((yyvsp[-4].i)) {
				if ((yyvsp[-1].i) < 30 || (yyvsp[-1].i) > maxtimeout) {
					reply(501,
					    "Maximum IDLE time must be between "
					    "30 and %d seconds",
					    maxtimeout);
				} else {
					timeout = (yyvsp[-1].i);
					(void) alarm((unsigned) timeout);
					reply(200,
					    "Maximum IDLE time set to %d seconds",
					    timeout);
				}
			}
		}
#line 2165 "y.tab.c"
    break;

  case 49: /* cmd: STOU check_login SP pathname CRLF  */
#line 568 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				store((yyvsp[-1].s), "w", 1);
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 2176 "y.tab.c"
    break;

  case 50: /* cmd: SYST check_login CRLF  */
#line 575 "ftpcmd.y"
                {
			if ((yyvsp[-1].i))
			reply(215, "UNIX Type: L8");
		}
#line 2185 "y.tab.c"
    break;

  case 51: /* cmd: SIZE check_login SP pathname CRLF  */
#line 588 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL)
				sizecmd((yyvsp[-1].s));
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 2196 "y.tab.c"
    break;

  case 52: /* cmd: MDTM check_login SP pathname CRLF  */
#line 605 "ftpcmd.y"
                {
			if ((yyvsp[-3].i) && (yyvsp[-1].s) != NULL) {
				struct stat stbuf;
				if (stat((yyvsp[-1].s), &stbuf) == -1)
					reply(550, "%s: %s",
					    (yyvsp[-1].s), strerror(errno));
				else if (!S_ISREG(stbuf.st_mode)) {
					reply(550, "%s: not a plain file.", (yyvsp[-1].s));
				} else {
					struct tm *t;
					t = gmtime(&stbuf.st_mtime);
					if (t == NULL) {
						/* invalid time, use epoch */
						stbuf.st_mtime = 0;
						t = gmtime(&stbuf.st_mtime);
					}
					reply(213,
					    "%04d%02d%02d%02d%02d%02d",
					    1900 + t->tm_year,
					    t->tm_mon+1, t->tm_mday,
					    t->tm_hour, t->tm_min, t->tm_sec);
				}
			}
			if ((yyvsp[-1].s) != NULL)
				free((yyvsp[-1].s));
		}
#line 2227 "y.tab.c"
    break;

  case 53: /* cmd: QUIT CRLF  */
#line 632 "ftpcmd.y"
                {
			reply(221, "Goodbye.");
			dologout(0);
		}
#line 2236 "y.tab.c"
    break;

  case 54: /* cmd: error  */
#line 637 "ftpcmd.y"
                {
			yyclearin;		/* discard lookahead data */
			yyerrok;		/* clear error condition */
			state = 0;		/* reset lexer state */
		}
#line 2246 "y.tab.c"
    break;

  case 55: /* rcmd: RNFR check_login SP pathname CRLF  */
#line 645 "ftpcmd.y"
                {
			restart_point = 0;
			if ((yyvsp[-3].i) && (yyvsp[-1].s)) {
				if (fromname)
					free(fromname);
				fromname = renamefrom((yyvsp[-1].s));
				if (fromname == NULL)
					free((yyvsp[-1].s));
			} else if ((yyvsp[-1].s)) {
				free ((yyvsp[-1].s));
			}
		}
#line 2263 "y.tab.c"
    break;

  case 56: /* rcmd: REST check_login SP file_size CRLF  */
#line 659 "ftpcmd.y"
                {
			if ((yyvsp[-3].i)) {
				if (fromname) {
					free(fromname);
					fromname = NULL;
				}
				restart_point = (yyvsp[-1].o);
				reply(350, "Restarting at %lld. %s",
				    (long long)restart_point,
				    "Send STORE or RETRIEVE to initiate transfer.");
			}
		}
#line 2280 "y.tab.c"
    break;

  case 58: /* password: %empty  */
#line 679 "ftpcmd.y"
                {
			(yyval.s) = calloc(1, sizeof(char));
		}
#line 2288 "y.tab.c"
    break;

  case 61: /* file_size: NUMBER  */
#line 691 "ftpcmd.y"
                {
			(yyval.o) = (yyvsp[0].i);
		}
#line 2296 "y.tab.c"
    break;

  case 62: /* file_size: BIGNUM  */
#line 695 "ftpcmd.y"
                {
			(yyval.o) = (yyvsp[0].o);
		}
#line 2304 "y.tab.c"
    break;

  case 63: /* host_port: NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER  */
#line 703 "ftpcmd.y"
                {
			char *a, *p;

			if ((yyvsp[-10].i) < 0 || (yyvsp[-10].i) > 255 || (yyvsp[-8].i) < 0 || (yyvsp[-8].i) > 255 ||
			    (yyvsp[-6].i) < 0 || (yyvsp[-6].i) > 255 || (yyvsp[-4].i) < 0 || (yyvsp[-4].i) > 255 ||
			    (yyvsp[-2].i) < 0 || (yyvsp[-2].i) > 255 || (yyvsp[0].i) < 0 || (yyvsp[0].i) > 255) {
				(yyval.i) = 1;
			} else {
				data_dest.su_sin.sin_len = sizeof(struct sockaddr_in);
				data_dest.su_sin.sin_family = AF_INET;
				p = (char *)&data_dest.su_sin.sin_port;
				p[0] = (yyvsp[-2].i); p[1] = (yyvsp[0].i);
				a = (char *)&data_dest.su_sin.sin_addr;
				a[0] = (yyvsp[-10].i); a[1] = (yyvsp[-8].i); a[2] = (yyvsp[-6].i); a[3] = (yyvsp[-4].i);
				(yyval.i) = 0;
			}
		}
#line 2326 "y.tab.c"
    break;

  case 64: /* host_long_port4: NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER  */
#line 726 "ftpcmd.y"
                {
			char *a, *p;

			/* reject invalid LPRT command */
			if ((yyvsp[-16].i) != 4 || (yyvsp[-14].i) != 4 ||
			    (yyvsp[-12].i) < 0 || (yyvsp[-12].i) > 255 || (yyvsp[-10].i) < 0 || (yyvsp[-10].i) > 255 ||
			    (yyvsp[-8].i) < 0 || (yyvsp[-8].i) > 255 || (yyvsp[-6].i) < 0 || (yyvsp[-6].i) > 255 ||
			    (yyvsp[-4].i) != 2 ||
			    (yyvsp[-2].i) < 0 || (yyvsp[-2].i) > 255 || (yyvsp[0].i) < 0 || (yyvsp[0].i) > 255) {
				(yyval.i) = 1;
			} else {
				data_dest.su_sin.sin_len =
					sizeof(struct sockaddr_in);
				data_dest.su_family = AF_INET;
				p = (char *)&data_dest.su_port;
				p[0] = (yyvsp[-2].i); p[1] = (yyvsp[0].i);
				a = (char *)&data_dest.su_sin.sin_addr;
				a[0] = (yyvsp[-12].i); a[1] = (yyvsp[-10].i); a[2] = (yyvsp[-8].i); a[3] = (yyvsp[-6].i);
				(yyval.i) = 0;
			}
		}
#line 2352 "y.tab.c"
    break;

  case 65: /* host_long_port6: NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER COMMA NUMBER  */
#line 756 "ftpcmd.y"
                {
			char *a, *p;

			/* reject invalid LPRT command */
			if ((yyvsp[-40].i) != 6 || (yyvsp[-38].i) != 16 ||
			    (yyvsp[-36].i) < 0 || (yyvsp[-36].i) > 255 || (yyvsp[-34].i) < 0 || (yyvsp[-34].i) > 255 ||
			    (yyvsp[-32].i) < 0 || (yyvsp[-32].i) > 255 || (yyvsp[-30].i) < 0 || (yyvsp[-30].i) > 255 ||
			    (yyvsp[-28].i) < 0 || (yyvsp[-28].i) > 255 || (yyvsp[-26].i) < 0 || (yyvsp[-26].i) > 255 ||
			    (yyvsp[-24].i) < 0 || (yyvsp[-24].i) > 255 || (yyvsp[-22].i) < 0 || (yyvsp[-22].i) > 255 ||
			    (yyvsp[-20].i) < 0 || (yyvsp[-20].i) > 255 || (yyvsp[-18].i) < 0 || (yyvsp[-18].i) > 255 ||
			    (yyvsp[-16].i) < 0 || (yyvsp[-16].i) > 255 || (yyvsp[-14].i) < 0 || (yyvsp[-14].i) > 255 ||
			    (yyvsp[-12].i) < 0 || (yyvsp[-12].i) > 255 || (yyvsp[-10].i) < 0 || (yyvsp[-10].i) > 255 ||
			    (yyvsp[-8].i) < 0 || (yyvsp[-8].i) > 255 || (yyvsp[-6].i) < 0 || (yyvsp[-6].i) > 255 ||
			    (yyvsp[-4].i) != 2 ||
			    (yyvsp[-2].i) < 0 || (yyvsp[-2].i) > 255 || (yyvsp[0].i) < 0 || (yyvsp[0].i) > 255) {
				(yyval.i) = 1;
			} else {
				data_dest.su_sin6.sin6_len =
					sizeof(struct sockaddr_in6);
				data_dest.su_family = AF_INET6;
				p = (char *)&data_dest.su_port;
				p[0] = (yyvsp[-2].i); p[1] = (yyvsp[0].i);
				a = (char *)&data_dest.su_sin6.sin6_addr;
				 a[0] =  (yyvsp[-36].i);  a[1] =  (yyvsp[-34].i);
				 a[2] =  (yyvsp[-32].i);  a[3] = (yyvsp[-30].i);
				 a[4] = (yyvsp[-28].i);  a[5] = (yyvsp[-26].i);
				 a[6] = (yyvsp[-24].i);  a[7] = (yyvsp[-22].i);
				 a[8] = (yyvsp[-20].i);  a[9] = (yyvsp[-18].i);
				a[10] = (yyvsp[-16].i); a[11] = (yyvsp[-14].i);
				a[12] = (yyvsp[-12].i); a[13] = (yyvsp[-10].i);
				a[14] = (yyvsp[-8].i); a[15] = (yyvsp[-6].i);
				if (his_addr.su_family == AF_INET6) {
					/* XXX more sanity checks! */
					data_dest.su_sin6.sin6_scope_id =
					    his_addr.su_sin6.sin6_scope_id;
				}

				(yyval.i) = 0;
			}
		}
#line 2397 "y.tab.c"
    break;

  case 66: /* form_code: N  */
#line 800 "ftpcmd.y"
                {
			(yyval.i) = FORM_N;
		}
#line 2405 "y.tab.c"
    break;

  case 67: /* form_code: T  */
#line 804 "ftpcmd.y"
                {
			(yyval.i) = FORM_T;
		}
#line 2413 "y.tab.c"
    break;

  case 68: /* form_code: C  */
#line 808 "ftpcmd.y"
                {
			(yyval.i) = FORM_C;
		}
#line 2421 "y.tab.c"
    break;

  case 69: /* type_code: A  */
#line 815 "ftpcmd.y"
                {
			cmd_type = TYPE_A;
			cmd_form = FORM_N;
		}
#line 2430 "y.tab.c"
    break;

  case 70: /* type_code: A SP form_code  */
#line 820 "ftpcmd.y"
                {
			cmd_type = TYPE_A;
			cmd_form = (yyvsp[0].i);
		}
#line 2439 "y.tab.c"
    break;

  case 71: /* type_code: E  */
#line 825 "ftpcmd.y"
                {
			cmd_type = TYPE_E;
			cmd_form = FORM_N;
		}
#line 2448 "y.tab.c"
    break;

  case 72: /* type_code: E SP form_code  */
#line 830 "ftpcmd.y"
                {
			cmd_type = TYPE_E;
			cmd_form = (yyvsp[0].i);
		}
#line 2457 "y.tab.c"
    break;

  case 73: /* type_code: I  */
#line 835 "ftpcmd.y"
                {
			cmd_type = TYPE_I;
		}
#line 2465 "y.tab.c"
    break;

  case 74: /* type_code: L  */
#line 839 "ftpcmd.y"
                {
			cmd_type = TYPE_L;
			cmd_bytesz = 8;
		}
#line 2474 "y.tab.c"
    break;

  case 75: /* type_code: L SP byte_size  */
#line 844 "ftpcmd.y"
                {
			cmd_type = TYPE_L;
			cmd_bytesz = (yyvsp[0].i);
		}
#line 2483 "y.tab.c"
    break;

  case 76: /* type_code: L byte_size  */
#line 850 "ftpcmd.y"
                {
			cmd_type = TYPE_L;
			cmd_bytesz = (yyvsp[0].i);
		}
#line 2492 "y.tab.c"
    break;

  case 77: /* struct_code: F  */
#line 858 "ftpcmd.y"
                {
			(yyval.i) = STRU_F;
		}
#line 2500 "y.tab.c"
    break;

  case 78: /* struct_code: R  */
#line 862 "ftpcmd.y"
                {
			(yyval.i) = STRU_R;
		}
#line 2508 "y.tab.c"
    break;

  case 79: /* struct_code: P  */
#line 866 "ftpcmd.y"
                {
			(yyval.i) = STRU_P;
		}
#line 2516 "y.tab.c"
    break;

  case 80: /* mode_code: S  */
#line 873 "ftpcmd.y"
                {
			(yyval.i) = MODE_S;
		}
#line 2524 "y.tab.c"
    break;

  case 81: /* mode_code: B  */
#line 877 "ftpcmd.y"
                {
			(yyval.i) = MODE_B;
		}
#line 2532 "y.tab.c"
    break;

  case 82: /* mode_code: C  */
#line 881 "ftpcmd.y"
                {
			(yyval.i) = MODE_C;
		}
#line 2540 "y.tab.c"
    break;

  case 83: /* pathname: pathstring  */
#line 888 "ftpcmd.y"
                {
			/*
			 * Problem: this production is used for all pathname
			 * processing, but only gives a 550 error reply.
			 * This is a valid reply in some cases but not in others.
			 */
			if (logged_in && (yyvsp[0].s) && strchr((yyvsp[0].s), '~') != NULL) {
				glob_t gl;
				int flags =
				 GLOB_BRACE|GLOB_NOCHECK|GLOB_QUOTE|GLOB_TILDE;
				char *pptr = (yyvsp[0].s);

				/*
				 * glob() will only find a leading ~, but
				 * Netscape kindly puts a slash in front of
				 * it for publish URLs.  There needs to be
				 * a flag for glob() that expands tildes
				 * anywhere in the string.
				 */
				if ((pptr[0] == '/') && (pptr[1] == '~'))
					pptr++;

				memset(&gl, 0, sizeof(gl));
				if (glob(pptr, flags, NULL, &gl) ||
				    gl.gl_pathc == 0) {
					reply(550, "not found");
					(yyval.s) = NULL;
				} else {
					(yyval.s) = strdup(gl.gl_pathv[0]);
				}
				globfree(&gl);
				free((yyvsp[0].s));
			} else
				(yyval.s) = (yyvsp[0].s);
		}
#line 2580 "y.tab.c"
    break;

  case 85: /* octal_number: NUMBER  */
#line 931 "ftpcmd.y"
                {
			int ret, dec, multby, digit;

			/*
			 * Convert a number that was read as decimal number
			 * to what it would be if it had been read as octal.
			 */
			dec = (yyvsp[0].i);
			multby = 1;
			ret = 0;
			while (dec) {
				digit = dec%10;
				if (digit > 7) {
					ret = -1;
					break;
				}
				ret += digit * multby;
				multby *= 8;
				dec /= 10;
			}
			(yyval.i) = ret;
		}
#line 2607 "y.tab.c"
    break;

  case 86: /* check_login: %empty  */
#line 958 "ftpcmd.y"
                {
			if (logged_in)
				(yyval.i) = 1;
			else {
				reply(530, "Please login with USER and PASS.");
				(yyval.i) = 0;
				state = 0;
				YYABORT;
			}
		}
#line 2622 "y.tab.c"
    break;

  case 87: /* check_login_epsvall: %empty  */
#line 972 "ftpcmd.y"
                {
			if (!logged_in) {
				reply(530, "Please login with USER and PASS.");
				(yyval.i) = 0;
				state = 0;
				YYABORT;
			} else if (epsvall) {
				reply(501, "the command is disallowed "
				    "after EPSV ALL");
				usedefault = 1;
				(yyval.i) = 0;
			} else
				(yyval.i) = 1;
		}
#line 2641 "y.tab.c"
    break;


#line 2645 "y.tab.c"

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

#line 988 "ftpcmd.y"


#define	CMD	0	/* beginning of command */
#define	ARGS	1	/* expect miscellaneous arguments */
#define	STR1	2	/* expect SP followed by STRING */
#define	STR2	3	/* expect STRING */
#define	OSTR	4	/* optional SP then STRING */
#define	ZSTR1	5	/* SP then optional STRING */
#define	ZSTR2	6	/* optional STRING after SP */
#define	SITECMD	7	/* SITE command */
#define	NSTR	8	/* Number followed by a string */

struct tab {
	char	*name;
	short	token;
	short	state;
	short	implemented;	/* 1 if command is implemented */
	char	*help;
};

struct tab cmdtab[] = {		/* In order defined in RFC 765 */
	{ "USER", USER, STR1, 1,	"<sp> username" },
	{ "PASS", PASS, ZSTR1, 1,	"<sp> password" },
	{ "ACCT", ACCT, STR1, 0,	"(specify account)" },
	{ "SMNT", SMNT, ARGS, 0,	"(structure mount)" },
	{ "REIN", REIN, ARGS, 0,	"(reinitialize server state)" },
	{ "QUIT", QUIT, ARGS, 1,	"(terminate service)", },
	{ "PORT", PORT, ARGS, 1,	"<sp> b0, b1, b2, b3, b4" },
	{ "LPRT", LPRT, ARGS, 1,	"<sp> af, hal, h1, h2, h3,..., pal, p1, p2..." },
	{ "EPRT", EPRT, STR1, 1,	"<sp> |af|addr|port|" },
	{ "PASV", PASV, ARGS, 1,	"(set server in passive mode)" },
	{ "LPSV", LPSV, ARGS, 1,	"(set server in passive mode)" },
	{ "EPSV", EPSV, ARGS, 1,	"[<sp> af|ALL]" },
	{ "TYPE", TYPE, ARGS, 1,	"<sp> [ A | E | I | L ]" },
	{ "STRU", STRU, ARGS, 1,	"(specify file structure)" },
	{ "MODE", MODE, ARGS, 1,	"(specify transfer mode)" },
	{ "RETR", RETR, STR1, 1,	"<sp> file-name" },
	{ "STOR", STOR, STR1, 1,	"<sp> file-name" },
	{ "APPE", APPE, STR1, 1,	"<sp> file-name" },
	{ "MLFL", MLFL, OSTR, 0,	"(mail file)" },
	{ "MAIL", MAIL, OSTR, 0,	"(mail to user)" },
	{ "MSND", MSND, OSTR, 0,	"(mail send to terminal)" },
	{ "MSOM", MSOM, OSTR, 0,	"(mail send to terminal or mailbox)" },
	{ "MSAM", MSAM, OSTR, 0,	"(mail send to terminal and mailbox)" },
	{ "MRSQ", MRSQ, OSTR, 0,	"(mail recipient scheme question)" },
	{ "MRCP", MRCP, STR1, 0,	"(mail recipient)" },
	{ "ALLO", ALLO, ARGS, 1,	"allocate storage (vacuously)" },
	{ "REST", REST, ARGS, 1,	"<sp> offset (restart command)" },
	{ "RNFR", RNFR, STR1, 1,	"<sp> file-name" },
	{ "RNTO", RNTO, STR1, 1,	"<sp> file-name" },
	{ "ABOR", ABOR, ARGS, 1,	"(abort operation)" },
	{ "DELE", DELE, STR1, 1,	"<sp> file-name" },
	{ "CWD",  CWD,  OSTR, 1,	"[ <sp> directory-name ]" },
	{ "XCWD", CWD,	OSTR, 1,	"[ <sp> directory-name ]" },
	{ "LIST", LIST, OSTR, 1,	"[ <sp> path-name ]" },
	{ "NLST", NLST, OSTR, 1,	"[ <sp> path-name ]" },
	{ "SITE", SITE, SITECMD, 1,	"site-cmd [ <sp> arguments ]" },
	{ "SYST", SYST, ARGS, 1,	"(get type of operating system)" },
	{ "STAT", STAT, OSTR, 1,	"[ <sp> path-name ]" },
	{ "HELP", HELP, OSTR, 1,	"[ <sp> <string> ]" },
	{ "NOOP", NOOP, ARGS, 1,	"" },
	{ "MKD",  MKD,  STR1, 1,	"<sp> path-name" },
	{ "XMKD", MKD,  STR1, 1,	"<sp> path-name" },
	{ "RMD",  RMD,  STR1, 1,	"<sp> path-name" },
	{ "XRMD", RMD,  STR1, 1,	"<sp> path-name" },
	{ "PWD",  PWD,  ARGS, 1,	"(return current directory)" },
	{ "XPWD", PWD,  ARGS, 1,	"(return current directory)" },
	{ "CDUP", CDUP, ARGS, 1,	"(change to parent directory)" },
	{ "XCUP", CDUP, ARGS, 1,	"(change to parent directory)" },
	{ "STOU", STOU, STR1, 1,	"<sp> file-name" },
	{ "SIZE", SIZE, OSTR, 1,	"<sp> path-name" },
	{ "MDTM", MDTM, OSTR, 1,	"<sp> path-name" },
	{ NULL,   0,    0,    0,	0 }
};

struct tab sitetab[] = {
	{ "UMASK", UMASK, ARGS, 1,	"[ <sp> umask ]" },
	{ "IDLE", IDLE, ARGS, 1,	"[ <sp> maximum-idle-time ]" },
	{ "CHMOD", CHMOD, NSTR, 1,	"<sp> mode <sp> file-name" },
	{ "HELP", HELP, OSTR, 1,	"[ <sp> <string> ]" },
	{ NULL,   0,    0,    0,	0 }
};

static void	 help(struct tab *, char *);
static struct tab *
		 lookup(struct tab *, const char *);
static void	 sizecmd(const char *);
static int	 yylex(void);

extern int epsvall;

static struct tab *
lookup(struct tab *p, const char *cmd)
{

	for (; p->name != NULL; p++)
		if (strcmp(cmd, p->name) == 0)
			return (p);
	return (NULL);
}

#include <arpa/telnet.h>

/*
 * get_line - a hacked up version of fgets to ignore TELNET escape codes.
 */
int
get_line(char *s, int n)
{
	int c;
	char *cs;

	cs = s;
/* tmpline may contain saved command from urgent mode interruption */
	for (c = 0; tmpline[c] != '\0' && --n > 0; ++c) {
		*cs++ = tmpline[c];
		if (tmpline[c] == '\n') {
			*cs++ = '\0';
			if (debug)
				syslog(LOG_DEBUG, "command: %s", s);
			tmpline[0] = '\0';
			return(0);
		}
		if (c == 0)
			tmpline[0] = '\0';
	}
	while ((c = getc(stdin)) != EOF) {
		c &= 0377;
		if (c == IAC) {
		    if ((c = getc(stdin)) != EOF) {
			c &= 0377;
			switch (c) {
			case WILL:
			case WONT:
				c = getc(stdin);
				printf("%c%c%c", IAC, DONT, 0377&c);
				(void) fflush(stdout);
				continue;
			case DO:
			case DONT:
				c = getc(stdin);
				printf("%c%c%c", IAC, WONT, 0377&c);
				(void) fflush(stdout);
				continue;
			case IAC:
				break;
			default:
				continue;	/* ignore command */
			}
		    }
		}
		*cs++ = c;
		if (--n <= 0) {
			/*
			 * If command doesn't fit into buffer, discard the
			 * rest of the command and indicate truncation.
			 * This prevents the command to be split up into
			 * multiple commands.
			 */
			while (c != '\n' && (c = getc(stdin)) != EOF)
				;
			return (-2);
		}
		if (c == '\n')
			break;
	}
	if (c == EOF && cs == s)
		return (-1);
	*cs++ = '\0';
	if (debug) {
		if (!guest && strncasecmp("pass ", s, 5) == 0) {
			/* Don't syslog passwords */
			syslog(LOG_DEBUG, "command: %.5s ???", s);
		} else {
			char *cp;
			int len;

			/* Don't syslog trailing CR-LF */
			len = strlen(s);
			cp = s + len - 1;
			while (cp >= s && (*cp == '\n' || *cp == '\r')) {
				--cp;
				--len;
			}
			syslog(LOG_DEBUG, "command: %.*s", len, s);
		}
	}
	return (0);
}

void
toolong(int signo)
{
	struct syslog_data sdata = SYSLOG_DATA_INIT;

	reply_r(421,
	    "Timeout (%d seconds): closing control connection.", timeout);
	if (logging)
		syslog_r(LOG_INFO, &sdata, "User %s timed out after %d seconds",
		    (pw ? pw -> pw_name : "unknown"), timeout);
	dologout(1);
}

static int
yylex(void)
{
	static int cpos;
	char *cp, *cp2;
	struct tab *p;
	int n;
	char c;

	for (;;) {
		switch (state) {

		case CMD:
			(void) alarm((unsigned) timeout);
			n = get_line(cbuf, sizeof(cbuf)-1);
			if (n == -1) {
				reply(221, "You could at least say goodbye.");
				dologout(0);
			} else if (n == -2) {
				reply(500, "Command too long.");
				alarm(0);
				continue;
			}
			(void) alarm(0);
			if ((cp = strchr(cbuf, '\r'))) {
				*cp++ = '\n';
				*cp = '\0';
			}
			if (strncasecmp(cbuf, "PASS", 4) != 0) {
				if ((cp = strpbrk(cbuf, "\n"))) {
					c = *cp;
					*cp = '\0';
					setproctitle("%s: %s", proctitle, cbuf);
					*cp = c;
				}
			}
			if ((cp = strpbrk(cbuf, " \n")))
				cpos = cp - cbuf;
			if (cpos == 0)
				cpos = 4;
			c = cbuf[cpos];
			cbuf[cpos] = '\0';
			upper(cbuf);
			p = lookup(cmdtab, cbuf);
			cbuf[cpos] = c;
			if (p != NULL) {
				if (p->implemented == 0) {
					nack(p->name);
					return (LEXERR);
				}
				state = p->state;
				yylval.s = p->name;
				return (p->token);
			}
			break;

		case SITECMD:
			if (cbuf[cpos] == ' ') {
				cpos++;
				return (SP);
			}
			cp = &cbuf[cpos];
			if ((cp2 = strpbrk(cp, " \n")))
				cpos = cp2 - cbuf;
			c = cbuf[cpos];
			cbuf[cpos] = '\0';
			upper(cp);
			p = lookup(sitetab, cp);
			cbuf[cpos] = c;
			if (p != NULL) {
				if (p->implemented == 0) {
					state = CMD;
					nack(p->name);
					return (LEXERR);
				}
				state = p->state;
				yylval.s = p->name;
				return (p->token);
			}
			state = CMD;
			break;

		case OSTR:
			if (cbuf[cpos] == '\n') {
				state = CMD;
				return (CRLF);
			}
			/* FALLTHROUGH */

		case STR1:
		case ZSTR1:
		dostr1:
			if (cbuf[cpos] == ' ') {
				cpos++;
				state = state == OSTR ? STR2 : state+1;
				return (SP);
			}
			break;

		case ZSTR2:
			if (cbuf[cpos] == '\n') {
				state = CMD;
				return (CRLF);
			}
			/* FALLTHROUGH */

		case STR2:
			cp = &cbuf[cpos];
			n = strlen(cp);
			cpos += n - 1;
			/*
			 * Make sure the string is nonempty and \n terminated.
			 */
			if (n > 1 && cbuf[cpos] == '\n') {
				cbuf[cpos] = '\0';
				yylval.s = strdup(cp);
				if (yylval.s == NULL)
					fatal("Ran out of memory.");
				cbuf[cpos] = '\n';
				state = ARGS;
				return (STRING);
			}
			break;

		case NSTR:
			if (cbuf[cpos] == ' ') {
				cpos++;
				return (SP);
			}
			if (isdigit((unsigned char)cbuf[cpos])) {
				cp = &cbuf[cpos];
				while (isdigit((unsigned char)cbuf[++cpos]))
					;
				c = cbuf[cpos];
				cbuf[cpos] = '\0';
				yylval.i = atoi(cp);
				cbuf[cpos] = c;
				state = STR1;
				return (NUMBER);
			}
			state = STR1;
			goto dostr1;

		case ARGS:
			if (isdigit((unsigned char)cbuf[cpos])) {
				long long llval;

				cp = &cbuf[cpos];
				errno = 0;
				llval = strtoll(cp, &cp2, 10);
				if (llval < 0 ||
				    (errno == ERANGE && llval == LLONG_MAX))
					break;

				cpos = (int)(cp2 - cbuf);
				if (llval > INT_MAX) {
					yylval.o = llval;
					return (BIGNUM);
				} else {
					yylval.i = (int)llval;
					return (NUMBER);
				}
			}
			if (strncasecmp(&cbuf[cpos], "ALL", 3) == 0 &&
			    !isalnum((unsigned char)cbuf[cpos + 3])) {
				cpos += 3;
				return ALL;
			}
			switch (cbuf[cpos++]) {

			case '\n':
				state = CMD;
				return (CRLF);

			case ' ':
				return (SP);

			case ',':
				return (COMMA);

			case 'A':
			case 'a':
				return (A);

			case 'B':
			case 'b':
				return (B);

			case 'C':
			case 'c':
				return (C);

			case 'E':
			case 'e':
				return (E);

			case 'F':
			case 'f':
				return (F);

			case 'I':
			case 'i':
				return (I);

			case 'L':
			case 'l':
				return (L);

			case 'N':
			case 'n':
				return (N);

			case 'P':
			case 'p':
				return (P);

			case 'R':
			case 'r':
				return (R);

			case 'S':
			case 's':
				return (S);

			case 'T':
			case 't':
				return (T);

			}
			break;

		default:
			fatal("Unknown state in scanner.");
		}
		state = CMD;
		return (LEXERR);
	}
}

void
upper(char *s)
{
	char *p;

	for (p = s; *p; p++)
		*p = (char)toupper((unsigned char)*p);
}

static void
help(struct tab *ctab, char *s)
{
	struct tab *c;
	int width, NCMDS;
	char *type;

	if (ctab == sitetab)
		type = "SITE ";
	else
		type = "";
	width = 0, NCMDS = 0;
	for (c = ctab; c->name != NULL; c++) {
		int len = strlen(c->name);

		if (len > width)
			width = len;
		NCMDS++;
	}
	width = (width + 8) &~ 7;
	if (s == NULL) {
		int i, j, w;
		int columns, lines;

		lreply(214, "The following %scommands are recognized %s.",
		    type, "(* =>'s unimplemented)");
		columns = 76 / width;
		if (columns == 0)
			columns = 1;
		lines = (NCMDS + columns - 1) / columns;
		for (i = 0; i < lines; i++) {
			printf("   ");
			for (j = 0; j < columns; j++) {
				c = ctab + j * lines + i;
				printf("%s%c", c->name,
					c->implemented ? ' ' : '*');
				if (c + lines >= &ctab[NCMDS])
					break;
				w = strlen(c->name) + 1;
				while (w < width) {
					putchar(' ');
					w++;
				}
			}
			printf("\r\n");
		}
		(void) fflush(stdout);
		reply(214, "Direct comments to ftp-bugs@%s.", hostname);
		return;
	}
	upper(s);
	c = lookup(ctab, s);
	if (c == NULL) {
		reply(502, "Unknown command %s.", s);
		return;
	}
	if (c->implemented)
		reply(214, "Syntax: %s%s %s", type, c->name, c->help);
	else
		reply(214, "%s%-*s\t%s; unimplemented.", type, width,
		    c->name, c->help);
}

static void
sizecmd(const char *filename)
{
	switch (type) {
	case TYPE_L:
	case TYPE_I: {
		struct stat stbuf;
		if (stat(filename, &stbuf) == -1 || !S_ISREG(stbuf.st_mode))
			reply(550, "%s: not a plain file.", filename);
		else
			reply(213, "%lld", (long long)stbuf.st_size);
		break; }
	case TYPE_A: {
		FILE *fin;
		int c;
		off_t count;
		struct stat stbuf;
		fin = fopen(filename, "r");
		if (fin == NULL) {
			perror_reply(550, filename);
			return;
		}
		if (fstat(fileno(fin), &stbuf) == -1 || !S_ISREG(stbuf.st_mode)) {
			reply(550, "%s: not a plain file.", filename);
			(void) fclose(fin);
			return;
		}
		if (stbuf.st_size > 10240) {
			reply(550, "%s: file too large for SIZE.", filename);
			(void) fclose(fin);
			return;
		}

		count = 0;
		while((c = getc(fin)) != EOF) {
			if (c == '\n')	/* will get expanded to \r\n */
				count++;
			count++;
		}
		(void) fclose(fin);

		reply(213, "%lld", (long long)count);
		break; }
	default:
		reply(504, "SIZE not implemented for Type %c.", "?AEIL"[type]);
	}
}
