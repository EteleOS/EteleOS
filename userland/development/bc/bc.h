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

#ifndef YY_YY_BC_H_INCLUDED
# define YY_YY_BC_H_INCLUDED
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
    COMMA = 258,                   /* COMMA  */
    SEMICOLON = 259,               /* SEMICOLON  */
    LPAR = 260,                    /* LPAR  */
    RPAR = 261,                    /* RPAR  */
    LBRACE = 262,                  /* LBRACE  */
    RBRACE = 263,                  /* RBRACE  */
    LBRACKET = 264,                /* LBRACKET  */
    RBRACKET = 265,                /* RBRACKET  */
    DOT = 266,                     /* DOT  */
    NEWLINE = 267,                 /* NEWLINE  */
    LETTER = 268,                  /* LETTER  */
    NUMBER = 269,                  /* NUMBER  */
    STRING = 270,                  /* STRING  */
    DEFINE = 271,                  /* DEFINE  */
    BREAK = 272,                   /* BREAK  */
    QUIT = 273,                    /* QUIT  */
    LENGTH = 274,                  /* LENGTH  */
    RETURN = 275,                  /* RETURN  */
    FOR = 276,                     /* FOR  */
    IF = 277,                      /* IF  */
    WHILE = 278,                   /* WHILE  */
    SQRT = 279,                    /* SQRT  */
    SCALE = 280,                   /* SCALE  */
    IBASE = 281,                   /* IBASE  */
    OBASE = 282,                   /* OBASE  */
    AUTO = 283,                    /* AUTO  */
    CONTINUE = 284,                /* CONTINUE  */
    ELSE = 285,                    /* ELSE  */
    PRINT = 286,                   /* PRINT  */
    BOOL_OR = 287,                 /* BOOL_OR  */
    BOOL_AND = 288,                /* BOOL_AND  */
    BOOL_NOT = 289,                /* BOOL_NOT  */
    EQUALS = 290,                  /* EQUALS  */
    LESS_EQ = 291,                 /* LESS_EQ  */
    GREATER_EQ = 292,              /* GREATER_EQ  */
    UNEQUALS = 293,                /* UNEQUALS  */
    LESS = 294,                    /* LESS  */
    GREATER = 295,                 /* GREATER  */
    ASSIGN_OP = 296,               /* ASSIGN_OP  */
    PLUS = 297,                    /* PLUS  */
    MINUS = 298,                   /* MINUS  */
    MULTIPLY = 299,                /* MULTIPLY  */
    DIVIDE = 300,                  /* DIVIDE  */
    REMAINDER = 301,               /* REMAINDER  */
    EXPONENT = 302,                /* EXPONENT  */
    UMINUS = 303,                  /* UMINUS  */
    INCR = 304,                    /* INCR  */
    DECR = 305                     /* DECR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define COMMA 258
#define SEMICOLON 259
#define LPAR 260
#define RPAR 261
#define LBRACE 262
#define RBRACE 263
#define LBRACKET 264
#define RBRACKET 265
#define DOT 266
#define NEWLINE 267
#define LETTER 268
#define NUMBER 269
#define STRING 270
#define DEFINE 271
#define BREAK 272
#define QUIT 273
#define LENGTH 274
#define RETURN 275
#define FOR 276
#define IF 277
#define WHILE 278
#define SQRT 279
#define SCALE 280
#define IBASE 281
#define OBASE 282
#define AUTO 283
#define CONTINUE 284
#define ELSE 285
#define PRINT 286
#define BOOL_OR 287
#define BOOL_AND 288
#define BOOL_NOT 289
#define EQUALS 290
#define LESS_EQ 291
#define GREATER_EQ 292
#define UNEQUALS 293
#define LESS 294
#define GREATER 295
#define ASSIGN_OP 296
#define PLUS 297
#define MINUS 298
#define MULTIPLY 299
#define DIVIDE 300
#define REMAINDER 301
#define EXPONENT 302
#define UMINUS 303
#define INCR 304
#define DECR 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 124 "bc.y"

	ssize_t		node;
	struct lvalue	lvalue;
	const char	*str;
	char		*astr;

#line 174 "bc.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BC_H_INCLUDED  */
