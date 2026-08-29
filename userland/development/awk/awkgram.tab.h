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

#ifndef YY_YY_AWKGRAM_TAB_H_INCLUDED
# define YY_YY_AWKGRAM_TAB_H_INCLUDED
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
    FIRSTTOKEN = 258,              /* FIRSTTOKEN  */
    PROGRAM = 259,                 /* PROGRAM  */
    PASTAT = 260,                  /* PASTAT  */
    PASTAT2 = 261,                 /* PASTAT2  */
    XBEGIN = 262,                  /* XBEGIN  */
    XEND = 263,                    /* XEND  */
    NL = 264,                      /* NL  */
    ARRAY = 265,                   /* ARRAY  */
    MATCH = 266,                   /* MATCH  */
    NOTMATCH = 267,                /* NOTMATCH  */
    MATCHOP = 268,                 /* MATCHOP  */
    FINAL = 269,                   /* FINAL  */
    DOT = 270,                     /* DOT  */
    ALL = 271,                     /* ALL  */
    CCL = 272,                     /* CCL  */
    NCCL = 273,                    /* NCCL  */
    CHAR = 274,                    /* CHAR  */
    OR = 275,                      /* OR  */
    STAR = 276,                    /* STAR  */
    QUEST = 277,                   /* QUEST  */
    PLUS = 278,                    /* PLUS  */
    EMPTYRE = 279,                 /* EMPTYRE  */
    ZERO = 280,                    /* ZERO  */
    AND = 281,                     /* AND  */
    BOR = 282,                     /* BOR  */
    APPEND = 283,                  /* APPEND  */
    EQ = 284,                      /* EQ  */
    GE = 285,                      /* GE  */
    GT = 286,                      /* GT  */
    LE = 287,                      /* LE  */
    LT = 288,                      /* LT  */
    NE = 289,                      /* NE  */
    IN = 290,                      /* IN  */
    ARG = 291,                     /* ARG  */
    BLTIN = 292,                   /* BLTIN  */
    BREAK = 293,                   /* BREAK  */
    CLOSE = 294,                   /* CLOSE  */
    CONTINUE = 295,                /* CONTINUE  */
    DELETE = 296,                  /* DELETE  */
    DO = 297,                      /* DO  */
    EXIT = 298,                    /* EXIT  */
    FOR = 299,                     /* FOR  */
    FUNC = 300,                    /* FUNC  */
    GENSUB = 301,                  /* GENSUB  */
    SUB = 302,                     /* SUB  */
    GSUB = 303,                    /* GSUB  */
    IF = 304,                      /* IF  */
    INDEX = 305,                   /* INDEX  */
    LSUBSTR = 306,                 /* LSUBSTR  */
    MATCHFCN = 307,                /* MATCHFCN  */
    NEXT = 308,                    /* NEXT  */
    NEXTFILE = 309,                /* NEXTFILE  */
    ADD = 310,                     /* ADD  */
    MINUS = 311,                   /* MINUS  */
    MULT = 312,                    /* MULT  */
    DIVIDE = 313,                  /* DIVIDE  */
    MOD = 314,                     /* MOD  */
    ASSIGN = 315,                  /* ASSIGN  */
    ASGNOP = 316,                  /* ASGNOP  */
    ADDEQ = 317,                   /* ADDEQ  */
    SUBEQ = 318,                   /* SUBEQ  */
    MULTEQ = 319,                  /* MULTEQ  */
    DIVEQ = 320,                   /* DIVEQ  */
    MODEQ = 321,                   /* MODEQ  */
    POWEQ = 322,                   /* POWEQ  */
    PRINT = 323,                   /* PRINT  */
    PRINTF = 324,                  /* PRINTF  */
    SPRINTF = 325,                 /* SPRINTF  */
    ELSE = 326,                    /* ELSE  */
    INTEST = 327,                  /* INTEST  */
    CONDEXPR = 328,                /* CONDEXPR  */
    POSTINCR = 329,                /* POSTINCR  */
    PREINCR = 330,                 /* PREINCR  */
    POSTDECR = 331,                /* POSTDECR  */
    PREDECR = 332,                 /* PREDECR  */
    VAR = 333,                     /* VAR  */
    IVAR = 334,                    /* IVAR  */
    VARNF = 335,                   /* VARNF  */
    CALL = 336,                    /* CALL  */
    NUMBER = 337,                  /* NUMBER  */
    STRING = 338,                  /* STRING  */
    REGEXPR = 339,                 /* REGEXPR  */
    GETLINE = 340,                 /* GETLINE  */
    RETURN = 341,                  /* RETURN  */
    SPLIT = 342,                   /* SPLIT  */
    SUBSTR = 343,                  /* SUBSTR  */
    WHILE = 344,                   /* WHILE  */
    CAT = 345,                     /* CAT  */
    NOT = 346,                     /* NOT  */
    UMINUS = 347,                  /* UMINUS  */
    UPLUS = 348,                   /* UPLUS  */
    POWER = 349,                   /* POWER  */
    DECR = 350,                    /* DECR  */
    INCR = 351,                    /* INCR  */
    INDIRECT = 352,                /* INDIRECT  */
    LASTTOKEN = 353                /* LASTTOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define FIRSTTOKEN 258
#define PROGRAM 259
#define PASTAT 260
#define PASTAT2 261
#define XBEGIN 262
#define XEND 263
#define NL 264
#define ARRAY 265
#define MATCH 266
#define NOTMATCH 267
#define MATCHOP 268
#define FINAL 269
#define DOT 270
#define ALL 271
#define CCL 272
#define NCCL 273
#define CHAR 274
#define OR 275
#define STAR 276
#define QUEST 277
#define PLUS 278
#define EMPTYRE 279
#define ZERO 280
#define AND 281
#define BOR 282
#define APPEND 283
#define EQ 284
#define GE 285
#define GT 286
#define LE 287
#define LT 288
#define NE 289
#define IN 290
#define ARG 291
#define BLTIN 292
#define BREAK 293
#define CLOSE 294
#define CONTINUE 295
#define DELETE 296
#define DO 297
#define EXIT 298
#define FOR 299
#define FUNC 300
#define GENSUB 301
#define SUB 302
#define GSUB 303
#define IF 304
#define INDEX 305
#define LSUBSTR 306
#define MATCHFCN 307
#define NEXT 308
#define NEXTFILE 309
#define ADD 310
#define MINUS 311
#define MULT 312
#define DIVIDE 313
#define MOD 314
#define ASSIGN 315
#define ASGNOP 316
#define ADDEQ 317
#define SUBEQ 318
#define MULTEQ 319
#define DIVEQ 320
#define MODEQ 321
#define POWEQ 322
#define PRINT 323
#define PRINTF 324
#define SPRINTF 325
#define ELSE 326
#define INTEST 327
#define CONDEXPR 328
#define POSTINCR 329
#define PREINCR 330
#define POSTDECR 331
#define PREDECR 332
#define VAR 333
#define IVAR 334
#define VARNF 335
#define CALL 336
#define NUMBER 337
#define STRING 338
#define REGEXPR 339
#define GETLINE 340
#define RETURN 341
#define SPLIT 342
#define SUBSTR 343
#define WHILE 344
#define CAT 345
#define NOT 346
#define UMINUS 347
#define UPLUS 348
#define POWER 349
#define DECR 350
#define INCR 351
#define INDIRECT 352
#define LASTTOKEN 353

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 42 "awkgram.y"

	Node	*p;
	Cell	*cp;
	int	i;
	char	*s;

#line 270 "awkgram.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_AWKGRAM_TAB_H_INCLUDED  */
