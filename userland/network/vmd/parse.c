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
#line 25 "parse.y"

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/socket.h>

#include <dev/vmm/vmm.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <agentx.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <util.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>

#include "vmd.h"

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

ssize_t		 parse_size(char *, int64_t);
int		 parse_disk(char *, enum vm_disk_fmt);
enum vm_disk_fmt parse_format(const char *);

static struct vmop_create_params vmc;
static struct vmd_switch	*vsw;
static char			*kernel = NULL;
static char			 vsw_type[IF_NAMESIZE];
static int			 vmc_disable;
static size_t			 vmc_nnics;
static int			 errors;
extern struct vmd		*env;
extern const char		*vmd_descsw[];

typedef struct {
	union {
		uint8_t		 lladdr[ETHER_ADDR_LEN];
		enum vm_disk_fmt disk_format;
		int64_t		 number;
		char		*string;
		struct {
			uid_t	 uid;
			int64_t	 gid;
		}		 owner;
	} v;
	int lineno;
} YYSTYPE;


#line 166 "y.tab.c"

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
    INCLUDE = 258,                 /* INCLUDE  */
    ERROR = 259,                   /* ERROR  */
    ADD = 260,                     /* ADD  */
    AGENTX = 261,                  /* AGENTX  */
    ALLOW = 262,                   /* ALLOW  */
    BOOT = 263,                    /* BOOT  */
    CDROM = 264,                   /* CDROM  */
    CONTEXT = 265,                 /* CONTEXT  */
    DEVICE = 266,                  /* DEVICE  */
    DISABLE = 267,                 /* DISABLE  */
    DISK = 268,                    /* DISK  */
    DOWN = 269,                    /* DOWN  */
    ENABLE = 270,                  /* ENABLE  */
    FORMAT = 271,                  /* FORMAT  */
    GROUP = 272,                   /* GROUP  */
    INET6 = 273,                   /* INET6  */
    INSTANCE = 274,                /* INSTANCE  */
    INTERFACE = 275,               /* INTERFACE  */
    LLADDR = 276,                  /* LLADDR  */
    LOCAL = 277,                   /* LOCAL  */
    LOCKED = 278,                  /* LOCKED  */
    MEMORY = 279,                  /* MEMORY  */
    NET = 280,                     /* NET  */
    NIFS = 281,                    /* NIFS  */
    OWNER = 282,                   /* OWNER  */
    PATH = 283,                    /* PATH  */
    PREFIX = 284,                  /* PREFIX  */
    RDOMAIN = 285,                 /* RDOMAIN  */
    SIZE = 286,                    /* SIZE  */
    SOCKET = 287,                  /* SOCKET  */
    SWITCH = 288,                  /* SWITCH  */
    UP = 289,                      /* UP  */
    VM = 290,                      /* VM  */
    VMID = 291,                    /* VMID  */
    STAGGERED = 292,               /* STAGGERED  */
    START = 293,                   /* START  */
    PARALLEL = 294,                /* PARALLEL  */
    DELAY = 295,                   /* DELAY  */
    SEV = 296,                     /* SEV  */
    SEVES = 297,                   /* SEVES  */
    NUMBER = 298,                  /* NUMBER  */
    STRING = 299                   /* STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INCLUDE 258
#define ERROR 259
#define ADD 260
#define AGENTX 261
#define ALLOW 262
#define BOOT 263
#define CDROM 264
#define CONTEXT 265
#define DEVICE 266
#define DISABLE 267
#define DISK 268
#define DOWN 269
#define ENABLE 270
#define FORMAT 271
#define GROUP 272
#define INET6 273
#define INSTANCE 274
#define INTERFACE 275
#define LLADDR 276
#define LOCAL 277
#define LOCKED 278
#define MEMORY 279
#define NET 280
#define NIFS 281
#define OWNER 282
#define PATH 283
#define PREFIX 284
#define RDOMAIN 285
#define SIZE 286
#define SOCKET 287
#define SWITCH 288
#define UP 289
#define VM 290
#define VMID 291
#define STAGGERED 292
#define START 293
#define PARALLEL 294
#define DELAY 295
#define SEV 296
#define SEVES 297
#define NUMBER 298
#define STRING 299

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
  YYSYMBOL_INCLUDE = 3,                    /* INCLUDE  */
  YYSYMBOL_ERROR = 4,                      /* ERROR  */
  YYSYMBOL_ADD = 5,                        /* ADD  */
  YYSYMBOL_AGENTX = 6,                     /* AGENTX  */
  YYSYMBOL_ALLOW = 7,                      /* ALLOW  */
  YYSYMBOL_BOOT = 8,                       /* BOOT  */
  YYSYMBOL_CDROM = 9,                      /* CDROM  */
  YYSYMBOL_CONTEXT = 10,                   /* CONTEXT  */
  YYSYMBOL_DEVICE = 11,                    /* DEVICE  */
  YYSYMBOL_DISABLE = 12,                   /* DISABLE  */
  YYSYMBOL_DISK = 13,                      /* DISK  */
  YYSYMBOL_DOWN = 14,                      /* DOWN  */
  YYSYMBOL_ENABLE = 15,                    /* ENABLE  */
  YYSYMBOL_FORMAT = 16,                    /* FORMAT  */
  YYSYMBOL_GROUP = 17,                     /* GROUP  */
  YYSYMBOL_INET6 = 18,                     /* INET6  */
  YYSYMBOL_INSTANCE = 19,                  /* INSTANCE  */
  YYSYMBOL_INTERFACE = 20,                 /* INTERFACE  */
  YYSYMBOL_LLADDR = 21,                    /* LLADDR  */
  YYSYMBOL_LOCAL = 22,                     /* LOCAL  */
  YYSYMBOL_LOCKED = 23,                    /* LOCKED  */
  YYSYMBOL_MEMORY = 24,                    /* MEMORY  */
  YYSYMBOL_NET = 25,                       /* NET  */
  YYSYMBOL_NIFS = 26,                      /* NIFS  */
  YYSYMBOL_OWNER = 27,                     /* OWNER  */
  YYSYMBOL_PATH = 28,                      /* PATH  */
  YYSYMBOL_PREFIX = 29,                    /* PREFIX  */
  YYSYMBOL_RDOMAIN = 30,                   /* RDOMAIN  */
  YYSYMBOL_SIZE = 31,                      /* SIZE  */
  YYSYMBOL_SOCKET = 32,                    /* SOCKET  */
  YYSYMBOL_SWITCH = 33,                    /* SWITCH  */
  YYSYMBOL_UP = 34,                        /* UP  */
  YYSYMBOL_VM = 35,                        /* VM  */
  YYSYMBOL_VMID = 36,                      /* VMID  */
  YYSYMBOL_STAGGERED = 37,                 /* STAGGERED  */
  YYSYMBOL_START = 38,                     /* START  */
  YYSYMBOL_PARALLEL = 39,                  /* PARALLEL  */
  YYSYMBOL_DELAY = 40,                     /* DELAY  */
  YYSYMBOL_SEV = 41,                       /* SEV  */
  YYSYMBOL_SEVES = 42,                     /* SEVES  */
  YYSYMBOL_NUMBER = 43,                    /* NUMBER  */
  YYSYMBOL_STRING = 44,                    /* STRING  */
  YYSYMBOL_45_n_ = 45,                     /* '\n'  */
  YYSYMBOL_46_ = 46,                       /* '='  */
  YYSYMBOL_47_ = 47,                       /* '{'  */
  YYSYMBOL_48_ = 48,                       /* '}'  */
  YYSYMBOL_49_ = 49,                       /* ','  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_grammar = 51,                   /* grammar  */
  YYSYMBOL_include = 52,                   /* include  */
  YYSYMBOL_varset = 53,                    /* varset  */
  YYSYMBOL_main = 54,                      /* main  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_switch = 56,                    /* switch  */
  YYSYMBOL_57_2 = 57,                      /* $@2  */
  YYSYMBOL_switch_opts_l = 58,             /* switch_opts_l  */
  YYSYMBOL_switch_opts = 59,               /* switch_opts  */
  YYSYMBOL_vm = 60,                        /* vm  */
  YYSYMBOL_61_3 = 61,                      /* $@3  */
  YYSYMBOL_vm_instance = 62,               /* vm_instance  */
  YYSYMBOL_vm_opts_l = 63,                 /* vm_opts_l  */
  YYSYMBOL_vm_opts = 64,                   /* vm_opts  */
  YYSYMBOL_instance = 65,                  /* instance  */
  YYSYMBOL_instance_l = 66,                /* instance_l  */
  YYSYMBOL_instance_flags = 67,            /* instance_flags  */
  YYSYMBOL_owner_id = 68,                  /* owner_id  */
  YYSYMBOL_agentxopt = 69,                 /* agentxopt  */
  YYSYMBOL_agentxopts = 70,                /* agentxopts  */
  YYSYMBOL_image_format = 71,              /* image_format  */
  YYSYMBOL_iface_opts_o = 72,              /* iface_opts_o  */
  YYSYMBOL_iface_opts_l = 73,              /* iface_opts_l  */
  YYSYMBOL_iface_opts_c = 74,              /* iface_opts_c  */
  YYSYMBOL_iface_opts = 75,                /* iface_opts  */
  YYSYMBOL_optstring = 76,                 /* optstring  */
  YYSYMBOL_string = 77,                    /* string  */
  YYSYMBOL_lladdr = 78,                    /* lladdr  */
  YYSYMBOL_local = 79,                     /* local  */
  YYSYMBOL_locked = 80,                    /* locked  */
  YYSYMBOL_updown = 81,                    /* updown  */
  YYSYMBOL_disable = 82,                   /* disable  */
  YYSYMBOL_sev = 83,                       /* sev  */
  YYSYMBOL_seves = 84,                     /* seves  */
  YYSYMBOL_bootdevice = 85,                /* bootdevice  */
  YYSYMBOL_optcomma = 86,                  /* optcomma  */
  YYSYMBOL_optnl = 87,                     /* optnl  */
  YYSYMBOL_optcommanl = 88,                /* optcommanl  */
  YYSYMBOL_nl = 89                         /* nl  */
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
#define YYLAST   199

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  173

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
      45,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   145,   145,   146,   147,   148,   149,   150,   151,   152,
     155,   170,   188,   191,   204,   214,   218,   218,   230,   237,
     237,   269,   270,   273,   276,   284,   300,   303,   311,   319,
     319,   404,   405,   408,   409,   412,   415,   418,   421,   430,
     464,   486,   489,   506,   518,   531,   546,   550,   553,   554,
     557,   558,   561,   562,   563,   564,   565,   566,   567,   573,
     577,   616,   626,   641,   642,   645,   648,   657,   658,   659,
     662,   663,   666,   667,   670,   683,   697,   702,   710,   718,
     719,   722,   728,   731,   743,   748,   749,   752,   753,   756,
     757,   760,   761,   764,   767,   770,   771,   772,   775,   776,
     779,   780,   783,   784,   787
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
  "\"end of file\"", "error", "\"invalid token\"", "INCLUDE", "ERROR",
  "ADD", "AGENTX", "ALLOW", "BOOT", "CDROM", "CONTEXT", "DEVICE",
  "DISABLE", "DISK", "DOWN", "ENABLE", "FORMAT", "GROUP", "INET6",
  "INSTANCE", "INTERFACE", "LLADDR", "LOCAL", "LOCKED", "MEMORY", "NET",
  "NIFS", "OWNER", "PATH", "PREFIX", "RDOMAIN", "SIZE", "SOCKET", "SWITCH",
  "UP", "VM", "VMID", "STAGGERED", "START", "PARALLEL", "DELAY", "SEV",
  "SEVES", "NUMBER", "STRING", "'\\n'", "'='", "'{'", "'}'", "','",
  "$accept", "grammar", "include", "varset", "main", "$@1", "switch",
  "$@2", "switch_opts_l", "switch_opts", "vm", "$@3", "vm_instance",
  "vm_opts_l", "vm_opts", "instance", "instance_l", "instance_flags",
  "owner_id", "agentxopt", "agentxopts", "image_format", "iface_opts_o",
  "iface_opts_l", "iface_opts_c", "iface_opts", "optstring", "string",
  "lladdr", "local", "locked", "updown", "disable", "sev", "seves",
  "bootdevice", "optcomma", "optnl", "optcommanl", "nl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-105)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-101)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -105,     9,  -105,   -39,   -16,  -105,    45,    40,   -16,   -16,
      35,     1,  -105,    33,    37,    42,    43,    44,  -105,   -16,
    -105,  -105,    51,    41,   -22,  -105,    71,    52,    60,  -105,
    -105,  -105,  -105,  -105,  -105,    20,    62,  -105,  -105,  -105,
    -105,    49,   -16,  -105,    65,  -105,    67,    68,  -105,  -105,
      64,  -105,    66,    75,  -105,  -105,    64,    80,    64,    74,
    -105,  -105,  -105,  -105,   -16,   -16,    97,    82,  -105,   107,
      64,  -105,  -105,   127,  -105,  -105,  -105,  -105,  -105,  -105,
      78,  -105,   110,    -6,   -16,   -16,  -105,    17,    83,   -22,
    -105,  -105,    57,    64,  -105,   112,  -105,  -105,  -105,    64,
    -105,     5,    46,  -105,  -105,   117,  -105,  -105,  -105,  -105,
    -105,    78,  -105,    94,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,   -22,    64,  -105,  -105,  -105,  -105,  -105,   -16,  -105,
    -105,  -105,   129,  -105,   172,  -105,   -16,  -105,   101,   -16,
      64,  -105,   144,  -105,   124,  -105,    99,   -26,  -105,  -105,
    -105,   156,   108,   104,  -105,    64,    64,  -105,   172,  -105,
       3,    64,  -105,  -105,  -105,  -105,   116,  -105,  -105,  -105,
      64,  -105,  -105
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,    16,     0,     0,     0,     0,
       0,     0,     4,     0,     0,     0,     0,     0,     9,    82,
      10,    63,    12,     0,     0,    19,    31,     0,     0,     3,
       5,     6,     7,     8,    81,    17,     0,    14,    59,    60,
      15,     0,     0,    29,     0,    11,     0,     0,    64,    13,
     101,    32,     0,     0,    61,    62,   101,     0,   101,     0,
     100,    92,    90,    91,     0,     0,     0,     0,    89,     0,
     101,    28,    23,    85,    18,    24,    25,    26,    27,    20,
       0,    22,     0,     0,     0,     0,    86,     0,     0,     0,
      93,    94,    85,   101,    47,     0,    35,    36,    37,   101,
      21,     0,     0,    40,    42,    65,    44,    45,    43,    46,
      30,     0,    34,    80,   104,    52,    56,    55,    57,    54,
      53,     0,   101,    49,    95,    96,    97,    41,     0,    38,
      33,    79,    69,    58,     0,    66,     0,    88,     0,     0,
     101,    39,    68,    73,     0,    78,     0,   101,    75,    77,
      74,    87,    99,    84,    48,   101,   101,    51,     0,   103,
      87,   101,    98,    72,    83,    76,   104,   102,    50,    67,
     101,    71,    70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,    87,
    -105,  -105,  -105,  -105,    79,  -105,     2,    81,   -86,  -105,
    -105,  -105,  -105,  -105,  -105,  -102,  -105,    -8,  -105,  -105,
    -105,    -7,   -65,  -105,  -105,  -105,  -105,   -54,  -105,  -104
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    13,    14,    15,    21,    16,    41,    69,    70,
      17,    52,    43,    92,    93,    94,   146,   147,    40,    48,
      35,   129,   141,   160,   142,   143,   132,    20,   165,    95,
     144,   145,    72,    97,    98,   127,   163,    57,   158,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,    26,    60,   109,    73,   102,    18,   130,    96,     2,
       3,    34,     4,   115,   116,     5,    81,    62,   117,   155,
     136,    38,    39,   156,   118,   119,   137,    96,    19,   120,
      46,     6,   121,   138,    51,   133,   139,    68,    19,   112,
     152,     7,     8,   159,     9,   114,    10,    28,    47,   161,
      71,   169,   122,    11,    12,   124,    75,    76,   170,   125,
     106,   107,    71,    22,    82,    83,    84,    24,   134,    61,
      85,   126,    63,    27,    23,   103,   104,   105,    29,    86,
      36,    87,    30,    88,    89,    37,   151,    31,    32,    33,
      42,    44,    61,   157,    62,    63,    50,    64,    90,    91,
      65,   166,   167,    66,    45,   110,    49,   171,    53,    56,
      67,    54,    55,    58,    68,    59,   172,    74,    77,    61,
     135,    62,    63,    99,    64,    78,   108,    65,   148,   101,
      66,   150,   113,   128,    82,    83,    84,    67,   131,    61,
      85,    68,    63,    62,   149,   153,   136,   154,   164,    86,
     -87,    87,   137,    88,    89,    79,    80,   162,    62,   138,
     168,   136,   139,    68,  -100,   -87,     0,   137,    90,    91,
      62,   111,     0,   136,   138,     0,   140,   139,    68,   137,
     115,   116,   123,     0,     0,   117,   138,     0,     0,   139,
      68,   118,   119,     0,     0,     0,   120,     0,     0,   121
};

static const yytype_int16 yycheck[] =
{
       8,     9,    56,    89,    58,    11,    45,   111,    73,     0,
       1,    19,     3,     8,     9,     6,    70,    14,    13,    45,
      17,    43,    44,    49,    19,    20,    23,    92,    44,    24,
      10,    22,    27,    30,    42,   121,    33,    34,    44,    93,
     142,    32,    33,   147,    35,    99,    37,    46,    28,   151,
      57,    48,    47,    44,    45,     9,    64,    65,   160,    13,
      43,    44,    69,    18,     7,     8,     9,    27,   122,    12,
      13,    25,    15,    38,    29,    83,    84,    85,    45,    22,
      29,    24,    45,    26,    27,    44,   140,    45,    45,    45,
      19,    39,    12,   147,    14,    15,    47,    17,    41,    42,
      20,   155,   156,    23,    44,    48,    44,   161,    43,    45,
      30,    44,    44,    47,    34,    40,   170,    43,    21,    12,
     128,    14,    15,    45,    17,    43,    43,    20,   136,    19,
      23,   139,    20,    16,     7,     8,     9,    30,    44,    12,
      13,    34,    15,    14,    43,    21,    17,    48,    44,    22,
      21,    24,    23,    26,    27,    48,    69,    49,    14,    30,
     158,    17,    33,    34,    48,    21,    -1,    23,    41,    42,
      14,    92,    -1,    17,    30,    -1,    47,    33,    34,    23,
       8,     9,   101,    -1,    -1,    13,    30,    -1,    -1,    33,
      34,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,     0,     1,     3,     6,    22,    32,    33,    35,
      37,    44,    45,    52,    53,    54,    56,    60,    45,    44,
      77,    55,    18,    29,    27,    77,    77,    38,    46,    45,
      45,    45,    45,    45,    77,    70,    29,    44,    43,    44,
      68,    57,    19,    62,    39,    44,    10,    28,    69,    44,
      47,    77,    61,    43,    44,    44,    45,    87,    47,    40,
      87,    12,    14,    15,    17,    20,    23,    30,    34,    58,
      59,    81,    82,    87,    43,    77,    77,    21,    43,    48,
      59,    87,     7,     8,     9,    13,    22,    24,    26,    27,
      41,    42,    63,    64,    65,    79,    82,    83,    84,    45,
      89,    19,    11,    77,    77,    77,    43,    44,    43,    68,
      48,    64,    87,    20,    87,     8,     9,    13,    19,    20,
      24,    27,    47,    67,     9,    13,    25,    85,    16,    71,
      89,    44,    76,    68,    87,    77,    17,    23,    30,    33,
      47,    72,    74,    75,    80,    81,    66,    67,    77,    43,
      77,    87,    75,    21,    48,    45,    49,    87,    88,    89,
      73,    75,    49,    86,    44,    78,    87,    87,    66,    48,
      75,    87,    87
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    53,    54,    54,    54,    54,    55,    54,    54,    57,
      56,    58,    58,    59,    59,    59,    59,    59,    59,    61,
      60,    62,    62,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      66,    66,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    72,
      73,    73,    74,    74,    75,    75,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    84,    85,    85,    85,    86,    86,
      87,    87,    88,    88,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     2,     3,     3,     3,     3,     3,
       2,     3,     2,     4,     3,     3,     0,     3,     6,     0,
       7,     3,     2,     1,     2,     2,     2,     2,     1,     0,
       8,     0,     2,     3,     2,     1,     1,     1,     3,     4,
       2,     3,     2,     2,     2,     2,     2,     1,     6,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     0,     2,     0,     2,     4,     1,     0,
       3,     2,     3,     1,     2,     2,     3,     2,     1,     1,
       0,     2,     1,     1,     0,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     0,     2,     1,     2
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
#line 152 "parse.y"
                                                { file->errors++; }
#line 1489 "y.tab.c"
    break;

  case 10: /* include: INCLUDE string  */
#line 155 "parse.y"
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
#line 1507 "y.tab.c"
    break;

  case 11: /* varset: STRING '=' STRING  */
#line 170 "parse.y"
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
				fatalx("cannot store variable");
			free((yyvsp[-2].v.string));
			free((yyvsp[0].v.string));
		}
#line 1528 "y.tab.c"
    break;

  case 12: /* main: LOCAL INET6  */
#line 188 "parse.y"
                              {
			env->vmd_cfg.cfg_flags |= VMD_CFG_INET6;
		}
#line 1536 "y.tab.c"
    break;

  case 13: /* main: LOCAL INET6 PREFIX STRING  */
#line 191 "parse.y"
                                            {
			const char	*err;

			if (parse_prefix6((yyvsp[0].v.string), &env->vmd_cfg.cfg_localprefix,
			    &err)) {
				yyerror("invalid local inet6 prefix: %s", err);
				YYERROR;
			} else {
				env->vmd_cfg.cfg_flags |= VMD_CFG_INET6;
				env->vmd_cfg.cfg_flags &= ~VMD_CFG_AUTOINET6;
			}
			free((yyvsp[0].v.string));
		}
#line 1554 "y.tab.c"
    break;

  case 14: /* main: LOCAL PREFIX STRING  */
#line 204 "parse.y"
                                      {
			const char	*err;

			if (parse_prefix4((yyvsp[0].v.string), &env->vmd_cfg.cfg_localprefix,
			    &err)) {
				yyerror("invalid local prefix: %s", err);
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 1569 "y.tab.c"
    break;

  case 15: /* main: SOCKET OWNER owner_id  */
#line 214 "parse.y"
                                        {
			env->vmd_ps.ps_csock.cs_uid = (yyvsp[0].v.owner).uid;
			env->vmd_ps.ps_csock.cs_gid = (yyvsp[0].v.owner).gid == -1 ? 0 : (yyvsp[0].v.owner).gid;
		}
#line 1578 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 218 "parse.y"
                         {
			env->vmd_cfg.cfg_agentx.ax_enabled = 1;
		}
#line 1586 "y.tab.c"
    break;

  case 17: /* main: AGENTX $@1 agentxopts  */
#line 220 "parse.y"
                             {
			if (env->vmd_cfg.cfg_agentx.ax_path[0] == '\0')
				if (strlcpy(env->vmd_cfg.cfg_agentx.ax_path,
				    AGENTX_MASTER_PATH,
				    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) >=
				    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) {
					yyerror("invalid agentx path");
					YYERROR;
				}
		}
#line 1601 "y.tab.c"
    break;

  case 18: /* main: STAGGERED START PARALLEL NUMBER DELAY NUMBER  */
#line 230 "parse.y"
                                                               {
			env->vmd_cfg.cfg_flags |= VMD_CFG_STAGGERED_START;
			env->vmd_cfg.delay.tv_sec = (yyvsp[0].v.number);
			env->vmd_cfg.parallelism = (yyvsp[-2].v.number);
		}
#line 1611 "y.tab.c"
    break;

  case 19: /* $@2: %empty  */
#line 237 "parse.y"
                                                {
			if ((vsw = calloc(1, sizeof(*vsw))) == NULL)
				fatal("could not allocate switch");

			vsw->sw_id = env->vmd_nswitches + 1;
			vsw->sw_name = (yyvsp[0].v.string);
			vsw->sw_flags = VMIFF_UP;

			vmc_disable = 0;
		}
#line 1626 "y.tab.c"
    break;

  case 20: /* switch: SWITCH string $@2 '{' optnl switch_opts_l '}'  */
#line 246 "parse.y"
                                                {
			if (strnlen(vsw->sw_ifname,
			    sizeof(vsw->sw_ifname)) == 0) {
				yyerror("switch \"%s\" "
				    "is missing interface name",
				    vsw->sw_name);
				YYERROR;
			}

			if (vmc_disable) {
				log_debug("%s:%d: switch \"%s\""
				    " skipped (disabled)",
				    file->name, yylval.lineno, vsw->sw_name);
			} else if (!env->vmd_noaction) {
				TAILQ_INSERT_TAIL(env->vmd_switches,
				    vsw, sw_entry);
				env->vmd_nswitches++;
				log_debug("%s:%d: switch \"%s\" registered",
				    file->name, yylval.lineno, vsw->sw_name);
			}
		}
#line 1652 "y.tab.c"
    break;

  case 23: /* switch_opts: disable  */
#line 273 "parse.y"
                                                {
			vmc_disable = (yyvsp[0].v.number);
		}
#line 1660 "y.tab.c"
    break;

  case 24: /* switch_opts: GROUP string  */
#line 276 "parse.y"
                                                {
			if (priv_validgroup((yyvsp[0].v.string)) == -1) {
				yyerror("invalid group name: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			vsw->sw_group = (yyvsp[0].v.string);
		}
#line 1673 "y.tab.c"
    break;

  case 25: /* switch_opts: INTERFACE string  */
#line 284 "parse.y"
                                                {
			if (priv_getiftype((yyvsp[0].v.string), vsw_type, NULL) == -1 ||
			    priv_findname(vsw_type, vmd_descsw) == -1) {
				yyerror("invalid switch interface: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}

			if (strlcpy(vsw->sw_ifname, (yyvsp[0].v.string),
			    sizeof(vsw->sw_ifname)) >= sizeof(vsw->sw_ifname)) {
				yyerror("switch interface too long: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 1694 "y.tab.c"
    break;

  case 26: /* switch_opts: LOCKED LLADDR  */
#line 300 "parse.y"
                                                {
			vsw->sw_flags |= VMIFF_LOCKED;
		}
#line 1702 "y.tab.c"
    break;

  case 27: /* switch_opts: RDOMAIN NUMBER  */
#line 303 "parse.y"
                                                {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > RT_TABLEID_MAX) {
				yyerror("invalid rdomain: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			vsw->sw_flags |= VMIFF_RDOMAIN;
			vsw->sw_rdomain = (yyvsp[0].v.number);
		}
#line 1715 "y.tab.c"
    break;

  case 28: /* switch_opts: updown  */
#line 311 "parse.y"
                                                {
			if ((yyvsp[0].v.number))
				vsw->sw_flags |= VMIFF_UP;
			else
				vsw->sw_flags &= ~VMIFF_UP;
		}
#line 1726 "y.tab.c"
    break;

  case 29: /* $@3: %empty  */
#line 319 "parse.y"
                                                {
			unsigned int	 i;
			char		*name;

			memset(&vmc, 0, sizeof(vmc));
			vmc.vmc_kernel = -1;

			vmc_disable = 0;
			vmc_nnics = 0;

			if ((yyvsp[0].v.string) != NULL) {
				/* This is an instance of a pre-configured VM */
				if (strlcpy(vmc.vmc_instance, (yyvsp[-1].v.string),
				    sizeof(vmc.vmc_instance)) >=
				    sizeof(vmc.vmc_instance)) {
					yyerror("vm %s name too long", (yyvsp[-1].v.string));
					free((yyvsp[-1].v.string));
					free((yyvsp[0].v.string));
					YYERROR;
				}

				free((yyvsp[-1].v.string));
				name = (yyvsp[0].v.string);
				vmc.vmc_flags |= VMOP_CREATE_INSTANCE;
			} else
				name = (yyvsp[-1].v.string);

			for (i = 0; i < VM_MAX_NICS_PER_VM; i++) {
				/* Set the interface to UP by default */
				vmc.vmc_ifflags[i] |= IFF_UP;
			}

			if (strlcpy(vmc.vmc_name, name,
			    sizeof(vmc.vmc_name)) >= sizeof(vmc.vmc_name)) {
				yyerror("vm name too long");
				free((yyvsp[-1].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}

			/* set default user/group permissions */
			vmc.vmc_owner.uid = 0;
			vmc.vmc_owner.gid = -1;
		}
#line 1775 "y.tab.c"
    break;

  case 30: /* vm: VM string vm_instance $@3 '{' optnl vm_opts_l '}'  */
#line 362 "parse.y"
                                                {
			struct vmd_vm	*vm;
			int		 ret;

			/* configured interfaces vs. number of interfaces */
			if (vmc_nnics > vmc.vmc_nnics)
				vmc.vmc_nnics = vmc_nnics;

			if (!env->vmd_noaction) {
				ret = vm_register(&env->vmd_ps, &vmc,
				    &vm, 0, 0);
				if (ret == -1 && errno == EALREADY) {
					log_debug("%s:%d: vm \"%s\""
					    " skipped (%s)",
					    file->name, yylval.lineno,
					    vmc.vmc_name,
					    (vm->vm_state & VM_STATE_RUNNING) ?
					    "running" : "already exists");
				} else if (ret == -1) {
					yyerror("vm \"%s\" failed: %s",
					    vmc.vmc_name, strerror(errno));
					YYERROR;
				} else {
					if (vmc_disable)
						vm->vm_state |= VM_STATE_DISABLED;
					else
						vm->vm_state |= VM_STATE_WAITING;
					log_debug("%s:%d: vm \"%s\" "
					    "registered (%s)",
					    file->name, yylval.lineno,
					    vmc.vmc_name,
					    vmc_disable ?
					    "disabled" : "enabled");
				}
				vm->vm_kernel_path = kernel;
				vm->vm_kernel = -1;
				vm->vm_from_config = 1;
			}
			kernel = NULL;
		}
#line 1820 "y.tab.c"
    break;

  case 31: /* vm_instance: %empty  */
#line 404 "parse.y"
                                                { (yyval.v.string) = NULL; }
#line 1826 "y.tab.c"
    break;

  case 32: /* vm_instance: INSTANCE string  */
#line 405 "parse.y"
                                                { (yyval.v.string) = (yyvsp[0].v.string); }
#line 1832 "y.tab.c"
    break;

  case 35: /* vm_opts: disable  */
#line 412 "parse.y"
                                                {
			vmc_disable = (yyvsp[0].v.number);
		}
#line 1840 "y.tab.c"
    break;

  case 36: /* vm_opts: sev  */
#line 415 "parse.y"
                                                {
			vmc.vmc_sev = 1;
		}
#line 1848 "y.tab.c"
    break;

  case 37: /* vm_opts: seves  */
#line 418 "parse.y"
                                                {
			vmc.vmc_sev = vmc.vmc_seves = 1;
		}
#line 1856 "y.tab.c"
    break;

  case 38: /* vm_opts: DISK string image_format  */
#line 421 "parse.y"
                                                {
			if (parse_disk((yyvsp[-1].v.string), (yyvsp[0].v.disk_format)) != 0) {
				yyerror("failed to parse disks: %s", (yyvsp[-1].v.string));
				free((yyvsp[-1].v.string));
				YYERROR;
			}
			free((yyvsp[-1].v.string));
			vmc.vmc_flags |= VMOP_CREATE_DISK;
		}
#line 1870 "y.tab.c"
    break;

  case 39: /* vm_opts: local INTERFACE optstring iface_opts_o  */
#line 430 "parse.y"
                                                         {
			unsigned int	i;
			char		type[IF_NAMESIZE];

			i = vmc_nnics;
			if (++vmc_nnics > VM_MAX_NICS_PER_VM) {
				yyerror("too many interfaces: %zu", vmc_nnics);
				free((yyvsp[-1].v.string));
				YYERROR;
			}

			if ((yyvsp[-3].v.number))
				vmc.vmc_ifflags[i] |= VMIFF_LOCAL;
			if ((yyvsp[-1].v.string) != NULL) {
				if (strcmp((yyvsp[-1].v.string), "tap") != 0 &&
				    (priv_getiftype((yyvsp[-1].v.string), type, NULL) == -1 ||
				    strcmp(type, "tap") != 0)) {
					yyerror("invalid interface: %s", (yyvsp[-1].v.string));
					free((yyvsp[-1].v.string));
					YYERROR;
				}

				if (strlcpy(vmc.vmc_ifnames[i], (yyvsp[-1].v.string),
				    sizeof(vmc.vmc_ifnames[i])) >=
				    sizeof(vmc.vmc_ifnames[i])) {
					yyerror("interface name too long: %s",
					    (yyvsp[-1].v.string));
					free((yyvsp[-1].v.string));
					YYERROR;
				}
			}
			free((yyvsp[-1].v.string));
			vmc.vmc_flags |= VMOP_CREATE_NETWORK;
		}
#line 1909 "y.tab.c"
    break;

  case 40: /* vm_opts: BOOT string  */
#line 464 "parse.y"
                                                {
			char	 path[PATH_MAX];

			if (kernel != NULL) {
				yyerror("kernel specified more than once");
				free((yyvsp[0].v.string));
				YYERROR;

			}
			if (realpath((yyvsp[0].v.string), path) == NULL) {
				yyerror("kernel path not found: %s",
				    strerror(errno));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			kernel = malloc(sizeof(path));
			if (kernel == NULL)
				yyerror("malloc");
			memcpy(kernel, &path, sizeof(path));
			vmc.vmc_flags |= VMOP_CREATE_KERNEL;
		}
#line 1936 "y.tab.c"
    break;

  case 41: /* vm_opts: BOOT DEVICE bootdevice  */
#line 486 "parse.y"
                                                {
			vmc.vmc_bootdevice = (yyvsp[0].v.number);
		}
#line 1944 "y.tab.c"
    break;

  case 42: /* vm_opts: CDROM string  */
#line 489 "parse.y"
                                                {
			if (vmc.vmc_cdrom[0] != '\0') {
				yyerror("cdrom specified more than once");
				free((yyvsp[0].v.string));
				YYERROR;

			}
			if (strlcpy(vmc.vmc_cdrom, (yyvsp[0].v.string),
			    sizeof(vmc.vmc_cdrom)) >=
			    sizeof(vmc.vmc_cdrom)) {
				yyerror("cdrom name too long");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			vmc.vmc_flags |= VMOP_CREATE_CDROM;
		}
#line 1966 "y.tab.c"
    break;

  case 43: /* vm_opts: NIFS NUMBER  */
#line 506 "parse.y"
                                                {
			if (vmc.vmc_nnics != 0) {
				yyerror("interfaces specified more than once");
				YYERROR;
			}
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > VM_MAX_NICS_PER_VM) {
				yyerror("too many interfaces: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			vmc.vmc_nnics = (size_t)(yyvsp[0].v.number);
			vmc.vmc_flags |= VMOP_CREATE_NETWORK;
		}
#line 1983 "y.tab.c"
    break;

  case 44: /* vm_opts: MEMORY NUMBER  */
#line 518 "parse.y"
                                                {
			ssize_t	 res;
			if (vmc.vmc_memranges[0].vmr_size != 0) {
				yyerror("memory specified more than once");
				YYERROR;
			}
			if ((res = parse_size(NULL, (yyvsp[0].v.number))) == -1) {
				yyerror("failed to parse size: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			vmc.vmc_memranges[0].vmr_size = (size_t)res;
			vmc.vmc_flags |= VMOP_CREATE_MEMORY;
		}
#line 2001 "y.tab.c"
    break;

  case 45: /* vm_opts: MEMORY STRING  */
#line 531 "parse.y"
                                                {
			ssize_t	 res;
			if (vmc.vmc_memranges[0].vmr_size != 0) {
				yyerror("argument specified more than once");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			if ((res = parse_size((yyvsp[0].v.string), 0)) == -1) {
				yyerror("failed to parse size: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			vmc.vmc_memranges[0].vmr_size = (size_t)res;
			vmc.vmc_flags |= VMOP_CREATE_MEMORY;
		}
#line 2021 "y.tab.c"
    break;

  case 46: /* vm_opts: OWNER owner_id  */
#line 546 "parse.y"
                                                {
			vmc.vmc_owner.uid = (yyvsp[0].v.owner).uid;
			vmc.vmc_owner.gid = (yyvsp[0].v.owner).gid;
		}
#line 2030 "y.tab.c"
    break;

  case 52: /* instance_flags: BOOT  */
#line 561 "parse.y"
                                { vmc.vmc_insflags |= VMOP_CREATE_KERNEL; }
#line 2036 "y.tab.c"
    break;

  case 53: /* instance_flags: MEMORY  */
#line 562 "parse.y"
                                { vmc.vmc_insflags |= VMOP_CREATE_MEMORY; }
#line 2042 "y.tab.c"
    break;

  case 54: /* instance_flags: INTERFACE  */
#line 563 "parse.y"
                                { vmc.vmc_insflags |= VMOP_CREATE_NETWORK; }
#line 2048 "y.tab.c"
    break;

  case 55: /* instance_flags: DISK  */
#line 564 "parse.y"
                                { vmc.vmc_insflags |= VMOP_CREATE_DISK; }
#line 2054 "y.tab.c"
    break;

  case 56: /* instance_flags: CDROM  */
#line 565 "parse.y"
                                { vmc.vmc_insflags |= VMOP_CREATE_CDROM; }
#line 2060 "y.tab.c"
    break;

  case 57: /* instance_flags: INSTANCE  */
#line 566 "parse.y"
                                { vmc.vmc_insflags |= VMOP_CREATE_INSTANCE; }
#line 2066 "y.tab.c"
    break;

  case 58: /* instance_flags: OWNER owner_id  */
#line 567 "parse.y"
                                 {
			vmc.vmc_insowner.uid = (yyvsp[0].v.owner).uid;
			vmc.vmc_insowner.gid = (yyvsp[0].v.owner).gid;
		}
#line 2075 "y.tab.c"
    break;

  case 59: /* owner_id: NUMBER  */
#line 573 "parse.y"
                                        {
			(yyval.v.owner).uid = (yyvsp[0].v.number);
			(yyval.v.owner).gid = -1;
		}
#line 2084 "y.tab.c"
    break;

  case 60: /* owner_id: STRING  */
#line 577 "parse.y"
                                        {
			char		*user, *group;
			struct passwd	*pw;
			struct group	*gr;

			(yyval.v.owner).uid = 0;
			(yyval.v.owner).gid = -1;

			user = (yyvsp[0].v.string);
			if ((group = strchr(user, ':')) != NULL) {
				if (group == user)
					user = NULL;
				*group++ = '\0';
			}

			if (user != NULL && *user) {
				if ((pw = getpwnam(user)) == NULL) {
					yyerror("failed to get user: %s",
					    user);
					free((yyvsp[0].v.string));
					YYERROR;
				}
				(yyval.v.owner).uid = pw->pw_uid;
			}

			if (group != NULL && *group) {
				if ((gr = getgrnam(group)) == NULL) {
					yyerror("failed to get group: %s",
					    group);
					free((yyvsp[0].v.string));
					YYERROR;
				}
				(yyval.v.owner).gid = gr->gr_gid;
			}

			free((yyvsp[0].v.string));
		}
#line 2126 "y.tab.c"
    break;

  case 61: /* agentxopt: CONTEXT STRING  */
#line 616 "parse.y"
                                 {
			if (strlcpy(env->vmd_cfg.cfg_agentx.ax_context, (yyvsp[0].v.string),
			    sizeof(env->vmd_cfg.cfg_agentx.ax_context)) >=
			    sizeof(env->vmd_cfg.cfg_agentx.ax_context)) {
				yyerror("agentx context too large");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2141 "y.tab.c"
    break;

  case 62: /* agentxopt: PATH STRING  */
#line 626 "parse.y"
                              {
			if (strlcpy(env->vmd_cfg.cfg_agentx.ax_path, (yyvsp[0].v.string),
			    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) >=
			    sizeof(env->vmd_cfg.cfg_agentx.ax_path)) {
				yyerror("agentx path too large");
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
			if (env->vmd_cfg.cfg_agentx.ax_path[0] != '/') {
				yyerror("agentx path is not absolute");
				YYERROR;
			}
		}
#line 2160 "y.tab.c"
    break;

  case 65: /* image_format: %empty  */
#line 645 "parse.y"
                                        {
			(yyval.v.disk_format) = VMDF_AUTO;
		}
#line 2168 "y.tab.c"
    break;

  case 66: /* image_format: FORMAT string  */
#line 648 "parse.y"
                                        {
			if (((yyval.v.disk_format) = parse_format((yyvsp[0].v.string))) == VMDF_INVALID) {
				yyerror("unrecognized disk format %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
		}
#line 2180 "y.tab.c"
    break;

  case 74: /* iface_opts: SWITCH string  */
#line 670 "parse.y"
                                                {
			unsigned int	i = vmc_nnics;

			/* No need to check if the switch exists */
			if (strlcpy(vmc.vmc_ifswitch[i], (yyvsp[0].v.string),
			    sizeof(vmc.vmc_ifswitch[i])) >=
			    sizeof(vmc.vmc_ifswitch[i])) {
				yyerror("switch name too long: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));
		}
#line 2198 "y.tab.c"
    break;

  case 75: /* iface_opts: GROUP string  */
#line 683 "parse.y"
                                                {
			unsigned int	i = vmc_nnics;

			if (priv_validgroup((yyvsp[0].v.string)) == -1) {
				yyerror("invalid group name: %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}

			/* No need to check if the group exists */
			(void)strlcpy(vmc.vmc_ifgroup[i], (yyvsp[0].v.string),
			    sizeof(vmc.vmc_ifgroup[i]));
			free((yyvsp[0].v.string));
		}
#line 2217 "y.tab.c"
    break;

  case 76: /* iface_opts: locked LLADDR lladdr  */
#line 697 "parse.y"
                                                {
			if ((yyvsp[-2].v.number))
				vmc.vmc_ifflags[vmc_nnics] |= VMIFF_LOCKED;
			memcpy(vmc.vmc_macs[vmc_nnics], (yyvsp[0].v.lladdr), ETHER_ADDR_LEN);
		}
#line 2227 "y.tab.c"
    break;

  case 77: /* iface_opts: RDOMAIN NUMBER  */
#line 702 "parse.y"
                                                {
			if ((yyvsp[0].v.number) < 0 || (yyvsp[0].v.number) > RT_TABLEID_MAX) {
				yyerror("invalid rdomain: %lld", (yyvsp[0].v.number));
				YYERROR;
			}
			vmc.vmc_ifflags[vmc_nnics] |= VMIFF_RDOMAIN;
			vmc.vmc_ifrdomain[vmc_nnics] = (yyvsp[0].v.number);
		}
#line 2240 "y.tab.c"
    break;

  case 78: /* iface_opts: updown  */
#line 710 "parse.y"
                                                {
			if ((yyvsp[0].v.number))
				vmc.vmc_ifflags[vmc_nnics] |= VMIFF_UP;
			else
				vmc.vmc_ifflags[vmc_nnics] &= ~VMIFF_UP;
		}
#line 2251 "y.tab.c"
    break;

  case 79: /* optstring: STRING  */
#line 718 "parse.y"
                                                { (yyval.v.string) = (yyvsp[0].v.string); }
#line 2257 "y.tab.c"
    break;

  case 80: /* optstring: %empty  */
#line 719 "parse.y"
                                                { (yyval.v.string) = NULL; }
#line 2263 "y.tab.c"
    break;

  case 81: /* string: STRING string  */
#line 722 "parse.y"
                                                {
			if (asprintf(&(yyval.v.string), "%s%s", (yyvsp[-1].v.string), (yyvsp[0].v.string)) == -1)
				fatal("asprintf string");
			free((yyvsp[-1].v.string));
			free((yyvsp[0].v.string));
		}
#line 2274 "y.tab.c"
    break;

  case 83: /* lladdr: STRING  */
#line 731 "parse.y"
                                                {
			struct ether_addr *ea;

			if ((ea = ether_aton((yyvsp[0].v.string))) == NULL) {
				yyerror("invalid address: %s\n", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			memcpy((yyval.v.lladdr), ea, ETHER_ADDR_LEN);
		}
#line 2291 "y.tab.c"
    break;

  case 84: /* lladdr: %empty  */
#line 743 "parse.y"
                              {
			memset((yyval.v.lladdr), 0, ETHER_ADDR_LEN);
		}
#line 2299 "y.tab.c"
    break;

  case 85: /* local: %empty  */
#line 748 "parse.y"
                                                { (yyval.v.number) = 0; }
#line 2305 "y.tab.c"
    break;

  case 86: /* local: LOCAL  */
#line 749 "parse.y"
                                                { (yyval.v.number) = 1; }
#line 2311 "y.tab.c"
    break;

  case 87: /* locked: %empty  */
#line 752 "parse.y"
                                                { (yyval.v.number) = 0; }
#line 2317 "y.tab.c"
    break;

  case 88: /* locked: LOCKED  */
#line 753 "parse.y"
                                                { (yyval.v.number) = 1; }
#line 2323 "y.tab.c"
    break;

  case 89: /* updown: UP  */
#line 756 "parse.y"
                                                { (yyval.v.number) = 1; }
#line 2329 "y.tab.c"
    break;

  case 90: /* updown: DOWN  */
#line 757 "parse.y"
                                                { (yyval.v.number) = 0; }
#line 2335 "y.tab.c"
    break;

  case 91: /* disable: ENABLE  */
#line 760 "parse.y"
                                                { (yyval.v.number) = 0; }
#line 2341 "y.tab.c"
    break;

  case 92: /* disable: DISABLE  */
#line 761 "parse.y"
                                                { (yyval.v.number) = 1; }
#line 2347 "y.tab.c"
    break;

  case 93: /* sev: SEV  */
#line 764 "parse.y"
                                                { (yyval.v.number) = 1; }
#line 2353 "y.tab.c"
    break;

  case 94: /* seves: SEVES  */
#line 767 "parse.y"
                                                { (yyval.v.number) = 1; }
#line 2359 "y.tab.c"
    break;

  case 95: /* bootdevice: CDROM  */
#line 770 "parse.y"
                                                { (yyval.v.number) = VMBOOTDEV_CDROM; }
#line 2365 "y.tab.c"
    break;

  case 96: /* bootdevice: DISK  */
#line 771 "parse.y"
                                                { (yyval.v.number) = VMBOOTDEV_DISK; }
#line 2371 "y.tab.c"
    break;

  case 97: /* bootdevice: NET  */
#line 772 "parse.y"
                                                { (yyval.v.number) = VMBOOTDEV_NET; }
#line 2377 "y.tab.c"
    break;


#line 2381 "y.tab.c"

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

#line 790 "parse.y"


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
		fatal("yyerror vasprintf");
	va_end(ap);
	log_warnx("%s:%d: %s", file->name, yylval.lineno, msg);
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
		{ "add",		ADD },
		{ "agentx",		AGENTX },
		{ "allow",		ALLOW },
		{ "boot",		BOOT },
		{ "cdrom",		CDROM },
		{ "context",		CONTEXT},
		{ "delay",		DELAY },
		{ "device",		DEVICE },
		{ "disable",		DISABLE },
		{ "disk",		DISK },
		{ "down",		DOWN },
		{ "enable",		ENABLE },
		{ "format",		FORMAT },
		{ "group",		GROUP },
		{ "id",			VMID },
		{ "include",		INCLUDE },
		{ "inet6",		INET6 },
		{ "instance",		INSTANCE },
		{ "interface",		INTERFACE },
		{ "interfaces",		NIFS },
		{ "lladdr",		LLADDR },
		{ "local",		LOCAL },
		{ "locked",		LOCKED },
		{ "memory",		MEMORY },
		{ "net",		NET },
		{ "owner",		OWNER },
		{ "parallel",		PARALLEL },
		{ "path",		PATH },
		{ "prefix",		PREFIX },
		{ "rdomain",		RDOMAIN },
		{ "sev",		SEV },
		{ "seves",		SEVES },
		{ "size",		SIZE },
		{ "socket",		SOCKET },
		{ "staggered",		STAGGERED },
		{ "start",		START  },
		{ "switch",		SWITCH },
		{ "up",			UP },
		{ "vm",			VM }
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
	if (c == '\t' || c == ' ') {
		/* Compress blanks to a single space. */
		do {
			c = getc(file->stream);
		} while (c == '\t' || c == ' ');
		ungetc(c, file->stream);
		c = ' ';
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
			fatal("yylex: strdup");
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
	x != '{' && x != '}' && \
	x != '!' && x != '=' && x != '#' && \
	x != ','))

	if (isalnum(c) || c == ':' || c == '_' || c == '/') {
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
				fatal("yylex: strdup");
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
parse_config(const char *filename)
{
	extern const char	 default_conffile[];
	struct sym		*sym, *next;

	if ((file = pushfile(filename, 0)) == NULL) {
		/* no default config file is fine */
		if (errno == ENOENT && filename == default_conffile) {
			log_debug("%s: missing", filename);
			return (0);
		}
		log_warn("failed to open %s", filename);
		if (errno == ENOENT)
			return (0);
		return (-1);
	}
	topfile = file;
	setservent(1);

	/* Set the default switch type */
	(void)strlcpy(vsw_type, VMD_SWITCH_TYPE, sizeof(vsw_type));

	env->vmd_cfg.cfg_agentx.ax_enabled = 0;
	env->vmd_cfg.cfg_agentx.ax_context[0] = '\0';
	env->vmd_cfg.cfg_agentx.ax_path[0] = '\0';

	yyparse();
	errors = file->errors;
	popfile();

	endservent();

	/* Free macros and check which have not been used. */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if (!sym->used)
			fprintf(stderr, "warning: macro '%s' not "
			    "used\n", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (errors)
		return (-1);

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
		fatal("%s: strndup", __func__);
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

ssize_t
parse_size(char *word, int64_t val)
{
	char		 result[FMT_SCALED_STRSIZE];
	ssize_t		 size;
	long long	 res;

	if (word != NULL) {
		if (scan_scaled(word, &res) != 0) {
			log_warn("invalid memory size: %s", word);
			return (-1);
		}
		val = (int64_t)res;
	}

	if (val < (1024 * 1024)) {
		log_warnx("memory size must be at least 1MB");
		return (-1);
	}

	if (val > VMM_MAX_VM_MEM_SIZE) {
		if (fmt_scaled(VMM_MAX_VM_MEM_SIZE, result) == 0)
			log_warnx("memory size too large (limit is %s)",
			    result);
		else
			log_warnx("memory size too large");
		return (-1);
	}

	/* Round down to the megabyte. */
	size = (val / (1024 * 1024)) * (1024 * 1024);

	if (size != val) {
		if (fmt_scaled(size, result) == 0)
			log_debug("memory size rounded to %s", result);
		else
			log_debug("memory size rounded to %zd bytes", size);
	}

	return ((ssize_t)size);
}

int
parse_disk(char *word, enum vm_disk_fmt type)
{
	char	 path[PATH_MAX];

	if (vmc.vmc_ndisks >= VM_MAX_DISKS_PER_VM) {
		log_warnx("too many disks");
		return (-1);
	}

	if (realpath(word, path) == NULL) {
		log_warn("disk %s", word);
		return (-1);
	}

	if (strlcpy(vmc.vmc_disks[vmc.vmc_ndisks], path,
	    sizeof(vmc.vmc_disks[vmc.vmc_ndisks])) >=
	    sizeof(vmc.vmc_disks[vmc.vmc_ndisks])) {
		log_warnx("disk path too long");
		return (-1);
	}
	vmc.vmc_disktypes[vmc.vmc_ndisks] = type;

	vmc.vmc_ndisks++;

	return (0);
}

enum vm_disk_fmt
parse_format(const char *word)
{
	if (strcasecmp(word, "raw") == 0)
		return (VMDF_RAW);
	else if (strcasecmp(word, "qcow2") == 0)
		return (VMDF_QCOW2);
	return (VMDF_INVALID);
}

/*
 * Parse an ipv4 address and prefix for local interfaces and validate
 * constraints for vmd networking.
 */
int
parse_prefix4(const char *str, struct local_prefix *out, const char **errstr)
{
	struct addrinfo		 hints, *res = NULL;
	struct sockaddr_storage	 ss;
	struct in_addr		 addr;
	int			 mask = 16;
	char			*p, *ps;

	if ((ps = strdup(str)) == NULL)
		fatal("%s: strdup", __func__);

	if ((p = strrchr(ps, '/')) != NULL) {
		mask = strtonum(p + 1, 1, 16, errstr);
		if (errstr != NULL && *errstr) {
			free(ps);
			return (1);
		}
		p[0] = '\0';
	}

	/* Attempt to construct an address from the user input. */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_NUMERICHOST;

	if (getaddrinfo(ps, NULL, &hints, &res) == 0) {
		memset(&ss, 0, sizeof(ss));
		memcpy(&ss, res->ai_addr, res->ai_addrlen);
		addr.s_addr = ss2sin(&ss)->sin_addr.s_addr;
		freeaddrinfo(res);
	} else { /* try 10/8 parsing */
		memset(&addr, 0, sizeof(addr));
		if (inet_net_pton(AF_INET, ps, &addr, sizeof(addr)) == -1) {
			if (errstr)
				*errstr = "invalid format";
			free(ps);
			return (1);
		}
	}
	free(ps);

	/*
	 * Validate the prefix by comparing it with the mask. Since we
	 * constrain the mask length to 16 above, this also validates
	 * we reserve the last 16 bits for use by vmd to assign vm id
	 * and interface id.
	 */
	if ((addr.s_addr & prefixlen2mask(mask)) != addr.s_addr) {
		if (errstr)
			*errstr = "bad mask";
		return (1);
	}

	/* Copy out the local prefix. */
	out->lp_in.s_addr = addr.s_addr;
	out->lp_mask.s_addr = prefixlen2mask(mask);
	return (0);
}

/*
 * Parse an ipv6 address and prefix for local interfaces and validate
 * constraints for vmd networking.
 */
int
parse_prefix6(const char *str, struct local_prefix *out, const char **errstr)
{
	struct addrinfo		 hints, *res = NULL;
	struct sockaddr_storage	 ss;
	struct in6_addr		 addr6, mask6;
	size_t			 i;
	int			 mask = 64, err;
	char			*p, *ps;

	if ((ps = strdup(str)) == NULL)
		fatal("%s: strdup", __func__);

	if ((p = strrchr(ps, '/')) != NULL) {
		mask = strtonum(p + 1, 0, 64, errstr);
		if (errstr != NULL && *errstr) {
			free(ps);
			return (1);
		}
		p[0] = '\0';
	}

	/* Attempt to construct an address from the user input. */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_NUMERICHOST;

	if ((err = getaddrinfo(ps, NULL, &hints, &res)) != 0) {
		if (errstr)
			*errstr = gai_strerror(err);
		free(ps);
		return (1);
	}
	free(ps);

	memset(&ss, 0, sizeof(ss));
	memcpy(&ss, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	memcpy(&addr6, (void*)&ss2sin6(&ss)->sin6_addr, sizeof(addr6));
	prefixlen2mask6(mask, &mask6);

	/*
	 * Validate the prefix by comparing it with the mask. Since we
	 * constrain the mask length to 64 above, this also validates
	 * that we're reserving bits for the encoding of the ipv4
	 * address, the vm id, and interface id. */
	for (i = 0; i < 16; i++) {
		if ((addr6.s6_addr[i] & mask6.s6_addr[i]) != addr6.s6_addr[i]) {
			if (errstr)
				*errstr = "bad mask";
			return (1);
		}
	}

	/* Copy out the local prefix. */
	memcpy(&out->lp_in6, &addr6, sizeof(out->lp_in6));
	memcpy(&out->lp_mask6, &mask6, sizeof(out->lp_mask6));
	return (0);
}
