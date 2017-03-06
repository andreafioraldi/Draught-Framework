/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 2058 of yacc.c  */
#line 34 "Parser.y"


#include "StoutCompiler.h"



/* Line 2058 of yacc.c  */
#line 53 "Parser.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_TRUE = 258,
     TK_FALSE = 259,
     TK_NONE = 260,
     TK_GLOBAL = 261,
     TK_MAIN = 262,
     TK_ARGS = 263,
     TK_ME = 264,
     TK_PARENT = 265,
     TK_ERROR = 266,
     TK_NEW = 267,
     TK_ALLOC = 268,
     TK_IF = 269,
     TK_ELSE = 270,
     TK_WHILE = 271,
     TK_FOR = 272,
     TK_TRY = 273,
     TK_CATCH = 274,
     TK_BREAK = 275,
     TK_CONTINUE = 276,
     TK_GOTO = 277,
     TK_RETURN = 278,
     TK_ATTACH = 279,
     TK_EXIT = 280,
     TK_DEBUG = 281,
     TK_OBJECT = 282,
     TK_EXTENDS = 283,
     TK_DELETE = 284,
     TK_LIBRARY = 285,
     TK_USE = 286,
     TK_LIKE = 287,
     TK_MOVE = 288,
     TK_COPY = 289,
     TK_SWAP = 290,
     TK_READONLY = 291,
     TK_EXTERNAL = 292,
     TK_ADDRESSOF = 293,
     TK_IDOF = 294,
     TK_ID = 295,
     TK_INT = 296,
     TK_FLOAT = 297,
     TK_FLOAT64 = 298,
     TK_CHAR = 299,
     TK_STRING = 300,
     TK_RSHIFT_AS = 301,
     TK_LSHIFT_AS = 302,
     TK_REF_AS = 303,
     TK_ADD_AS = 304,
     TK_SUB_AS = 305,
     TK_MUL_AS = 306,
     TK_DIV_AS = 307,
     TK_MOD_AS = 308,
     TK_AND_AS = 309,
     TK_XOR_AS = 310,
     TK_OR_AS = 311,
     TK_RSHIFT = 312,
     TK_LSHIFT = 313,
     TK_RBIND = 314,
     TK_LBIND = 315,
     TK_AND = 316,
     TK_OR = 317,
     TK_LE = 318,
     TK_GE = 319,
     TK_EQ = 320,
     TK_NE = 321,
     TK_INCR = 322,
     TK_DECR = 323,
     TK_TYPEOF = 324,
     TK_TYPESTR = 325,
     TK_PARENTOF = 326,
     TK_THROW = 327,
     TK_NOT_RECOGNIZED = 328
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 76 "Parser.y"

   string * text;
   Node * node;


/* Line 2058 of yacc.c  */
#line 147 "Parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (Compiler * compiler);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */
