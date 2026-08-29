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

#line 154 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
