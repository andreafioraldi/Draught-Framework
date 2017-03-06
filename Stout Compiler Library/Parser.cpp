/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 40 "Parser.y"


#include "Parser.h"
#include <sstream>

int yylex(YYSTYPE * lvalp, YYLTYPE * llocp, void * lexer);

void yyerror(YYLTYPE * locp, Compiler * compiler, const char * err) {
	throw CompilerErr(compiler->fileName, locp->first_line, err);
}

#define lexer compiler->lexer

bool isConst(Node * node) {
	if(node->type == NodeType::True ||
	node->type == NodeType::False ||
	node->type == NodeType::None ||
	node->type == NodeType::Char ||
	node->type == NodeType::Int ||
	node->type == NodeType::Float ||
	node->type == NodeType::Float64 ||
	node->type == NodeType::String)
		return true;
	if(node->type == NodeType::Array || node->type == NodeType::RefArray) {
		/*if(node->children[0] == nullptr)
			return true;
		for(size_t i = 0; i < node->children.size(); ++i)
			if(!isConst(node->children[i]))
				return false;*/
		return true;
	}
	return false;
}


/* Line 371 of yacc.c  */
#line 104 "Parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Parser.h".  */
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
/* Line 387 of yacc.c  */
#line 34 "Parser.y"


#include "StoutCompiler.h"



/* Line 387 of yacc.c  */
#line 143 "Parser.cpp"

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
/* Line 387 of yacc.c  */
#line 76 "Parser.y"

   string * text;
   Node * node;


/* Line 387 of yacc.c  */
#line 237 "Parser.cpp"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 277 "Parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  125
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1852

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  99
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNRULES -- Number of states.  */
#define YYNSTATES  275

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,     2,     2,    91,    84,     2,
      78,    79,    89,    87,    94,    88,    97,    90,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    76,
      85,    80,    86,    81,    98,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    95,     2,    96,    83,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    82,    75,    92,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    14,    17,    19,    22,
      26,    32,    40,    46,    53,    61,    69,    72,    77,    81,
      85,    90,    94,    98,   102,   106,   111,   115,   118,   121,
     124,   128,   131,   135,   137,   139,   141,   144,   146,   150,
     154,   158,   162,   166,   170,   174,   178,   182,   186,   190,
     194,   198,   202,   204,   210,   212,   216,   218,   222,   224,
     228,   230,   234,   236,   240,   242,   246,   250,   254,   256,
     260,   264,   268,   272,   274,   278,   282,   284,   288,   292,
     294,   298,   302,   306,   308,   311,   314,   317,   320,   323,
     326,   329,   332,   335,   338,   341,   344,   347,   350,   352,
     356,   358,   363,   369,   375,   377,   382,   386,   391,   396,
     400,   403,   406,   408,   410,   412,   414,   417,   419,   421,
     423,   425,   427,   429,   431,   433,   435,   437,   439,   446,
     453,   456,   462,   467,   471,   475,   478
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
     100,     0,    -1,   101,    -1,   104,    -1,   101,   104,    -1,
      74,   101,    75,    -1,    74,    75,    -1,    76,    -1,   105,
      76,    -1,    40,    77,   104,    -1,    14,    78,   105,    79,
     104,    -1,    14,    78,   105,    79,   104,    15,   104,    -1,
      16,    78,   105,    79,   104,    -1,    17,    78,   103,   103,
      79,   104,    -1,    17,    78,   103,   103,   105,    79,   104,
      -1,    17,    78,    40,    77,   105,    79,   104,    -1,    18,
     104,    -1,    18,   104,    19,   104,    -1,    26,   105,    76,
      -1,    31,    40,    76,    -1,    31,    40,   105,    76,    -1,
      28,   105,    76,    -1,    72,   105,    76,    -1,    29,   105,
      76,    -1,    30,    40,    76,    -1,    30,    40,   105,    76,
      -1,    22,    40,    76,    -1,    21,    76,    -1,    20,    76,
      -1,    23,    76,    -1,    23,   105,    76,    -1,    25,    76,
      -1,    25,   105,    76,    -1,   102,    -1,   103,    -1,   106,
      -1,    36,   105,    -1,   107,    -1,   118,    80,   105,    -1,
     118,    59,   105,    -1,   118,    60,   105,    -1,   118,    48,
     105,    -1,   118,    51,   105,    -1,   118,    52,   105,    -1,
     118,    53,   105,    -1,   118,    49,   105,    -1,   118,    50,
     105,    -1,   118,    47,   105,    -1,   118,    46,   105,    -1,
     118,    54,   105,    -1,   118,    55,   105,    -1,   118,    56,
     105,    -1,   108,    -1,   108,    81,   105,    77,   107,    -1,
     109,    -1,   108,    62,   109,    -1,   110,    -1,   109,    61,
     110,    -1,   111,    -1,   110,    82,   111,    -1,   112,    -1,
     111,    83,   112,    -1,   113,    -1,   112,    84,   113,    -1,
     114,    -1,   113,    65,   114,    -1,   113,    66,   114,    -1,
     113,    32,   114,    -1,   115,    -1,   114,    85,   115,    -1,
     114,    86,   115,    -1,   114,    63,   115,    -1,   114,    64,
     115,    -1,   116,    -1,   115,    58,   116,    -1,   115,    57,
     116,    -1,   117,    -1,   116,    87,   117,    -1,   116,    88,
     117,    -1,   118,    -1,   117,    89,   118,    -1,   117,    90,
     118,    -1,   117,    91,   118,    -1,   120,    -1,    87,   118,
      -1,    88,   118,    -1,    92,   118,    -1,    93,   118,    -1,
      67,   118,    -1,    68,   118,    -1,    38,   118,    -1,    39,
     118,    -1,    69,   118,    -1,    71,   118,    -1,    70,   118,
      -1,    33,   118,    -1,    34,   118,    -1,    13,   118,    -1,
     105,    -1,   119,    94,   105,    -1,   121,    -1,    12,   121,
      78,    79,    -1,    12,   121,    78,   119,    79,    -1,    12,
     121,    74,   105,    75,    -1,   122,    -1,   121,    95,   105,
      96,    -1,   121,    78,    79,    -1,   121,    74,   105,    75,
      -1,   121,    78,   119,    79,    -1,   121,    97,    40,    -1,
     121,    67,    -1,   121,    68,    -1,     3,    -1,     4,    -1,
       5,    -1,    40,    -1,    24,    40,    -1,    41,    -1,    42,
      -1,    43,    -1,    44,    -1,    45,    -1,     6,    -1,     7,
      -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,    37,
      78,   105,    94,   105,    79,    -1,    35,    78,   105,    94,
     105,    79,    -1,    27,   102,    -1,    27,    78,   105,    79,
     102,    -1,    98,    95,   119,    96,    -1,    98,    95,    96,
      -1,    95,   119,    96,    -1,    95,    96,    -1,    78,   105,
      79,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   171,   172,   176,   177,   181,   182,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   215,   216,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   238,   249,   265,   273,   285,   293,   305,   306,
     314,   315,   323,   324,   332,   333,   334,   335,   339,   340,
     345,   350,   355,   363,   364,   369,   377,   378,   383,   391,
     392,   397,   408,   422,   423,   428,   433,   438,   443,   448,
     453,   454,   459,   464,   465,   470,   475,   476,   480,   481,
     485,   486,   487,   488,   492,   493,   494,   495,   496,   497,
     498,   503,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"'true'\"", "\"'false'\"",
  "\"'none'\"", "\"'global'\"", "\"'main'\"", "\"'args'\"", "\"'me'\"",
  "\"'parent'\"", "\"'error'\"", "\"'new'\"", "\"'alloc'\"", "\"'if'\"",
  "\"'else'\"", "\"'while'\"", "\"'for'\"", "\"'try'\"", "\"'catch'\"",
  "\"'break'\"", "\"'continue'\"", "\"'goto'\"", "\"'return'\"",
  "\"'attach'\"", "\"'exit'\"", "\"'debug'\"", "\"'object'\"",
  "\"'extends'\"", "\"'delete'\"", "\"'library'\"", "\"'use'\"",
  "\"'like'\"", "\"'move'\"", "\"'copy'\"", "\"'swap'\"", "\"'readonly'\"",
  "\"'external'\"", "\"'addressof'\"", "\"'idof'\"", "\"identifier\"",
  "\"int\"", "\"float\"", "\"float64\"", "\"char\"", "\"string\"",
  "\"'>>='\"", "\"'<<='\"", "\"'@='\"", "\"'+='\"", "\"'-='\"", "\"'*='\"",
  "\"'/='\"", "\"'%='\"", "\"'&='\"", "\"'^='\"", "\"'|='\"", "\"'>>'\"",
  "\"'<<'\"", "\"'->'\"", "\"'<-'\"", "\"'&&'\"", "\"'||'\"", "\"'<='\"",
  "\"'>='\"", "\"'=='\"", "\"'!='\"", "\"'++'\"", "\"'--'\"",
  "\"'typeof'\"", "\"'typestr'\"", "\"'parentof'\"", "\"'throw'\"",
  "\"invalid character\"", "'{'", "'}'", "';'", "':'", "'('", "')'", "'='",
  "'?'", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'~'", "'!'", "','", "'['", "']'", "'.'", "'@'", "$accept",
  "start", "stmt_list", "compound_stmt", "expr_stmt", "stmt", "expr",
  "assign_expr", "cond_expr", "logic_or_expr", "logic_and_expr", "or_expr",
  "xor_expr", "and_expr", "equal_expr", "comparison_expr", "shift_expr",
  "add_expr", "mul_expr", "unary_expr", "expr_list", "new_expr",
  "postfix_expr", "primary_expr", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   123,   125,    59,    58,    40,    41,
      61,    63,   124,    94,    38,    60,    62,    43,    45,    42,
      47,    37,   126,    33,    44,    91,    93,    46,    64
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    99,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   113,   113,   113,   114,   114,
     114,   114,   114,   115,   115,   115,   116,   116,   116,   117,
     117,   117,   117,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   119,   119,
     120,   120,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     2,     1,     2,     3,
       5,     7,     5,     6,     7,     7,     2,     4,     3,     3,
       4,     3,     3,     3,     3,     4,     3,     2,     2,     2,
       3,     2,     3,     1,     1,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     5,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     4,     5,     5,     1,     4,     3,     4,     4,     3,
       2,     2,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     6,     6,
       2,     5,     4,     3,     3,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   112,   113,   114,   122,   123,   124,   125,   126,   127,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,     0,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     2,    33,    34,
       3,     0,    35,    37,    52,    54,    56,    58,    60,    62,
      64,    68,    73,    76,    79,    83,   100,   104,   115,     0,
      97,     0,     0,     0,    16,    28,    27,     0,    29,     0,
     116,    31,     0,     0,     0,   130,     0,     0,     0,     0,
      95,    96,     0,    36,     0,    90,    91,     0,    88,    89,
      92,    94,    93,     0,     6,     0,     0,    84,    85,    86,
      87,   135,    98,     0,     0,     1,     4,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,   115,     0,     0,    26,    30,    32,    18,     0,
      21,    23,    24,     0,    19,     0,     0,     0,     9,    22,
       5,   136,     0,   134,   133,     0,    55,    79,     0,    57,
      59,    61,    63,    67,    65,    66,    71,    72,    69,    70,
      75,    74,    77,    78,    80,    81,    82,    48,    47,    41,
      45,    46,    42,    43,    44,    49,    50,    51,    39,    40,
      38,     0,   106,     0,     0,   109,     0,   101,     0,     0,
       0,     0,     0,    17,     0,    25,    20,     0,     0,    99,
     132,     0,   107,   108,   105,   103,   102,    10,    12,     0,
       0,     0,   131,     0,     0,    53,     0,     0,    13,     0,
     129,   128,    11,    15,    14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     123,    75,    76,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -118
static const yytype_int16 yypact[] =
{
     506,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
      66,  1754,   -66,   -64,   -47,   506,   -43,   -35,    11,   602,
      28,   698,  1658,   -63,  1658,  1658,    42,    46,  1754,  1754,
     -31,  1658,    16,  1754,  1754,    36,  -118,  -118,  -118,  -118,
    -118,  1754,  1754,  1754,  1754,  1754,  1658,   314,  -118,  1658,
    1754,  1754,  1754,  1754,   794,    10,   115,   506,  -118,  -118,
    -118,    41,  -118,  -118,   -57,    61,    59,    64,    58,   -16,
     -46,   -29,   -68,    -6,     7,  -118,   -65,  -118,  -118,    21,
    -118,  1658,  1658,   890,   131,  -118,  -118,    77,  -118,    78,
    -118,  -118,    92,    93,  1658,  -118,    95,    99,   986,  1082,
    -118,  -118,  1658,  -118,  1658,  -118,  -118,   506,  -118,  -118,
    -118,  -118,  -118,   101,  -118,   410,    81,  -118,  -118,  -118,
    -118,  -118,  -118,     8,  1178,  -118,  -118,  -118,  1754,  1658,
    1754,  1754,  1754,  1754,  1754,  1754,  1754,  1754,  1754,  1754,
    1754,  1754,  1754,  1754,  1754,  1754,  1754,  1754,  1658,  1658,
    1658,  1658,  1658,  1658,  1658,  1658,  1658,  1658,  1658,  1658,
    1658,  1658,  -118,  -118,  1658,  1274,  1658,   134,  1658,  1370,
     103,   104,   108,  1466,   506,  -118,  -118,  -118,  -118,   109,
    -118,  -118,  -118,   111,  -118,   113,    86,    96,  -118,  -118,
    -118,  -118,  1658,  -118,  -118,    18,    61,  -118,   114,    59,
      64,    58,   -16,   -46,   -46,   -46,   -29,   -29,   -29,   -29,
     -68,   -68,    -6,    -6,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,   117,  -118,   -71,   100,  -118,   119,    84,   -69,   506,
     506,  1658,  1562,  -118,   123,  -118,  -118,  1658,  1658,  -118,
    -118,  1754,  -118,  -118,  -118,    89,    98,   183,  -118,   120,
     506,   121,  -118,   122,   125,  -118,   506,   506,  -118,   506,
    -118,  -118,  -118,  -118,  -118
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -118,  -118,   155,   -17,   -82,   -15,   124,  -118,   -48,  -118,
      79,    80,    82,    76,    83,   -38,   -59,   -77,   -24,    -7,
    -117,  -118,   199,  -118
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -109
static const yytype_int16 yytable[] =
{
      84,   173,   162,   163,    80,   128,    95,   195,   253,   164,
     256,    47,    81,   165,    82,    94,   134,   137,   138,   143,
     144,   100,   101,   192,   129,   192,   105,   106,   141,   142,
     166,    83,   167,    85,   108,   109,   110,   111,   112,   139,
     140,    86,   126,   117,   118,   119,   120,   102,   233,   135,
     136,    87,   238,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   210,   211,   159,   160,    90,     1,
       2,     3,     4,     5,     6,     7,     8,     9,   206,   207,
     208,   209,    98,   145,   146,   147,    99,   161,   162,   163,
      20,   242,   188,    23,   104,   168,   203,   204,   205,   169,
     126,    30,   192,    32,   193,   124,    78,    36,    37,    38,
      39,    40,   192,   107,   250,   125,   166,   127,   167,   212,
     213,   197,   130,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   214,   215,
     216,   131,   133,    89,    49,    92,    93,   132,    96,    97,
     174,  -106,  -106,   175,   176,   103,  -107,  -107,  -106,   243,
     191,    54,  -106,  -107,    55,  -108,  -108,  -107,   177,   178,
     113,   180,  -108,   116,   235,   181,  -108,   189,   122,  -106,
     247,  -106,   239,   240,  -107,   241,  -107,   245,   244,   246,
     248,   251,   252,  -108,   255,  -108,   254,    47,   266,   267,
     269,   270,   115,   265,   271,   170,   171,   196,   201,    79,
     199,     0,     0,   200,     0,     0,   202,     0,   179,     0,
       0,     0,   183,   185,   257,   258,   186,   262,   187,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   197,   268,     0,     0,   122,     0,
       0,   272,   273,   198,   274,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,     0,     0,   231,   122,
     234,     0,   236,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     0,
      13,    14,    15,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,     0,     0,     0,     0,   259,   261,     0,     0,     0,
       0,   263,   264,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,    46,     0,    47,   114,
      48,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,     0,     0,     0,    52,    53,     0,    54,
       0,     0,    55,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,    13,    14,    15,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,     0,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
      44,    45,    46,     0,    47,   190,    48,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    51,     0,
       0,     0,    52,    53,     0,    54,     0,     0,    55,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     0,    13,    14,    15,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     0,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    41,    42,    43,    44,    45,    46,     0,
      47,     0,    48,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,     0,     0,     0,    52,    53,
       0,    54,     0,     0,    55,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,    23,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    78,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    45,     0,     0,     0,     0,    88,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      51,     0,     0,     0,    52,    53,     0,    54,     0,     0,
      55,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,    23,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,    78,    36,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
       0,     0,     0,     0,    91,     0,    49,     0,     0,     0,
       0,     0,     0,     0,     0,    50,    51,     0,     0,     0,
      52,    53,     0,    54,     0,     0,    55,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,    23,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    78,    36,    37,    38,    39,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,     0,     0,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,     0,     0,     0,    52,    53,     0,    54,
     121,     0,    55,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,    23,     0,     0,
       0,     0,     0,    28,    29,    30,    31,    32,    33,    34,
     172,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
      44,    45,     0,     0,     0,     0,    48,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    51,     0,
       0,     0,    52,    53,     0,    54,     0,     0,    55,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,     0,     0,    23,     0,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    78,    36,    37,    38,
      39,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    41,    42,    43,    44,    45,     0,     0,
       0,     0,   182,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,     0,     0,     0,    52,    53,
       0,    54,     0,     0,    55,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,    23,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    78,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    45,     0,     0,     0,     0,   184,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      51,     0,     0,     0,    52,    53,     0,    54,     0,     0,
      55,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,    23,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,    78,    36,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,     0,     0,    50,    51,     0,     0,     0,
      52,    53,     0,    54,   194,     0,    55,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,    23,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    78,    36,    37,    38,    39,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,     0,     0,     0,     0,
       0,     0,    49,   232,     0,     0,     0,     0,     0,     0,
       0,    50,    51,     0,     0,     0,    52,    53,     0,    54,
       0,     0,    55,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,    23,     0,     0,
       0,     0,     0,    28,    29,    30,    31,    32,    33,    34,
      78,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
      44,    45,     0,     0,     0,     0,     0,     0,    49,   237,
       0,     0,     0,     0,     0,     0,     0,    50,    51,     0,
       0,     0,    52,    53,     0,    54,     0,     0,    55,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,     0,     0,    23,     0,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    78,    36,    37,    38,
      39,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    41,    42,    43,    44,    45,     0,     0,
       0,     0,    48,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,     0,     0,     0,    52,    53,
       0,    54,     0,     0,    55,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,    23,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    78,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    45,     0,     0,     0,     0,     0,     0,
      49,   260,     0,     0,     0,     0,     0,     0,     0,    50,
      51,     0,     0,     0,    52,    53,     0,    54,     0,     0,
      55,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,    23,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,    78,    36,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,     0,     0,    50,    51,     0,     0,     0,
      52,    53,     0,    54,     0,     0,    55,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,    23,     0,     0,     0,     0,     0,    28,    29,    30,
       0,    32,    33,    34,    78,    36,    37,    38,    39,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,     0,     0,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,     0,     0,     0,    52,    53,     0,    54,
       0,     0,    55
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-118)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      15,    83,    67,    68,    11,    62,    23,   124,    79,    74,
      79,    74,    78,    78,    78,    78,    32,    63,    64,    87,
      88,    28,    29,    94,    81,    94,    33,    34,    57,    58,
      95,    78,    97,    76,    41,    42,    43,    44,    45,    85,
      86,    76,    57,    50,    51,    52,    53,    78,   165,    65,
      66,    40,   169,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,   141,   142,    59,    60,    40,     3,
       4,     5,     6,     7,     8,     9,    10,    11,   137,   138,
     139,   140,    40,    89,    90,    91,    40,    80,    67,    68,
      24,   173,   107,    27,    78,    74,   134,   135,   136,    78,
     115,    35,    94,    37,    96,    95,    40,    41,    42,    43,
      44,    45,    94,    77,    96,     0,    95,    76,    97,   143,
     144,   128,    61,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,    82,    84,    19,    78,    21,    22,    83,    24,    25,
      19,    67,    68,    76,    76,    31,    67,    68,    74,   174,
      79,    95,    78,    74,    98,    67,    68,    78,    76,    76,
      46,    76,    74,    49,    40,    76,    78,    76,    54,    95,
      94,    97,    79,    79,    95,    77,    97,    76,    79,    76,
      94,    77,    75,    95,    75,    97,    96,    74,    15,    79,
      79,    79,    47,   251,    79,    81,    82,   128,   132,    10,
     130,    -1,    -1,   131,    -1,    -1,   133,    -1,    94,    -1,
      -1,    -1,    98,    99,   239,   240,   102,   244,   104,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   251,   260,    -1,    -1,   124,    -1,
      -1,   266,   267,   129,   269,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,    -1,    -1,   164,   165,
     166,    -1,   168,   169,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   192,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      16,    17,    18,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,   241,   242,    -1,    -1,    -1,
      -1,   247,   248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,    88,    -1,    -1,    -1,    92,    93,    -1,    95,
      -1,    -1,    98,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    16,    17,    18,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    -1,    74,    75,    76,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    -1,
      -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    16,    17,    18,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      74,    -1,    76,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    87,    88,    -1,    -1,    -1,    92,    93,
      -1,    95,    -1,    -1,    98,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    -1,    -1,    -1,    -1,    76,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      88,    -1,    -1,    -1,    92,    93,    -1,    95,    -1,    -1,
      98,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    -1,    76,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    -1,    -1,    -1,
      92,    93,    -1,    95,    -1,    -1,    98,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,    88,    -1,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    98,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    76,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    -1,
      -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    -1,    -1,
      -1,    -1,    76,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    87,    88,    -1,    -1,    -1,    92,    93,
      -1,    95,    -1,    -1,    98,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    -1,    -1,    -1,    -1,    76,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      88,    -1,    -1,    -1,    92,    93,    -1,    95,    -1,    -1,
      98,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    -1,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,    88,    -1,    -1,    -1,    92,    93,    -1,    95,
      -1,    -1,    98,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    -1,
      -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    -1,    -1,
      -1,    -1,    76,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    87,    88,    -1,    -1,    -1,    92,    93,
      -1,    95,    -1,    -1,    98,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      88,    -1,    -1,    -1,    92,    93,    -1,    95,    -1,    -1,
      98,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    -1,    -1,    -1,
      92,    93,    -1,    95,    -1,    -1,    98,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,    88,    -1,    -1,    -1,    92,    93,    -1,    95,
      -1,    -1,    98
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    16,    17,    18,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    67,    68,    69,    70,    71,    72,    74,    76,    78,
      87,    88,    92,    93,    95,    98,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   120,   121,   122,    40,   121,
     118,    78,    78,    78,   104,    76,    76,    40,    76,   105,
      40,    76,   105,   105,    78,   102,   105,   105,    40,    40,
     118,   118,    78,   105,    78,   118,   118,    77,   118,   118,
     118,   118,   118,   105,    75,   101,   105,   118,   118,   118,
     118,    96,   105,   119,    95,     0,   104,    76,    62,    81,
      61,    82,    83,    84,    32,    65,    66,    63,    64,    85,
      86,    57,    58,    87,    88,    89,    90,    91,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    59,
      60,    80,    67,    68,    74,    78,    95,    97,    74,    78,
     105,   105,    40,   103,    19,    76,    76,    76,    76,   105,
      76,    76,    76,   105,    76,   105,   105,   105,   104,    76,
      75,    79,    94,    96,    96,   119,   109,   118,   105,   110,
     111,   112,   113,   114,   114,   114,   115,   115,   115,   115,
     116,   116,   117,   117,   118,   118,   118,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,    79,   119,   105,    40,   105,    79,   119,    79,
      79,    77,   103,   104,    79,    76,    76,    94,    94,   105,
      96,    77,    75,    79,    96,    75,    79,   104,   104,   105,
      79,   105,   102,   105,   105,   107,    15,    79,   104,    79,
      79,    79,   104,   104,   104
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (&yylloc, compiler, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, lexer)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, compiler); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Compiler * compiler)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, compiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Compiler * compiler;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (compiler);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Compiler * compiler)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, compiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    Compiler * compiler;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, compiler);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, Compiler * compiler)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, compiler)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    Compiler * compiler;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , compiler);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, compiler); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Compiler * compiler)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, compiler)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    Compiler * compiler;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (compiler);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (Compiler * compiler)
#else
int
yyparse (compiler)
    Compiler * compiler;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc = yyloc_default;


    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 167 "Parser.y"
    { compiler->tree = (yyvsp[(1) - (1)].node); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 171 "Parser.y"
    { (yyval.node) = new StmtListNode((yyvsp[(1) - (1)].node), (yylsp[(1) - (1)]).first_line); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 172 "Parser.y"
    { (yyvsp[(1) - (2)].node)->children.push_back((yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 176 "Parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 177 "Parser.y"
    { (yyval.node) = new StmtListNode(nullptr, (yylsp[(1) - (2)]).first_line); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 181 "Parser.y"
    { (yyval.node) = new ExprStmtNode(nullptr, (yylsp[(1) - (1)]).first_line); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 182 "Parser.y"
    { (yyval.node) = new ExprStmtNode((yyvsp[(1) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 186 "Parser.y"
    { (yyval.node) = new LabelNode(*(yyvsp[(1) - (3)].text), (yyvsp[(3) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 187 "Parser.y"
    { (yyval.node) = new IfNode((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), (yylsp[(1) - (5)]).first_line); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 188 "Parser.y"
    { (yyval.node) = new IfElseNode((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), (yylsp[(1) - (7)]).first_line); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 189 "Parser.y"
    { (yyval.node) = new WhileNode((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), (yylsp[(1) - (5)]).first_line); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 190 "Parser.y"
    { (yyval.node) = new ForNode((yyvsp[(3) - (6)].node), (yyvsp[(4) - (6)].node), nullptr, (yyvsp[(6) - (6)].node), (yylsp[(1) - (6)]).first_line); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 191 "Parser.y"
    { (yyval.node) = new ForNode((yyvsp[(3) - (7)].node), (yyvsp[(4) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), (yylsp[(1) - (7)]).first_line); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 192 "Parser.y"
    { (yyval.node) = new ForEachNode(*(yyvsp[(3) - (7)].text), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), (yylsp[(1) - (7)]).first_line); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 193 "Parser.y"
    { (yyval.node) = new TryNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 194 "Parser.y"
    { (yyval.node) = new TryCatchNode((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node), (yylsp[(1) - (4)]).first_line); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 195 "Parser.y"
    { (yyval.node) = new DebugNode((yyvsp[(2) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 196 "Parser.y"
    { (yyval.node) = new UseNode(*(yyvsp[(2) - (3)].text), nullptr, (yylsp[(1) - (3)]).first_line); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 197 "Parser.y"
    { (yyval.node) = new UseNode(*(yyvsp[(2) - (4)].text), (yyvsp[(3) - (4)].node), (yylsp[(1) - (4)]).first_line); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 198 "Parser.y"
    { (yyval.node) = new ExtendsNode((yyvsp[(2) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 199 "Parser.y"
    { (yyval.node) = new ThrowNode((yyvsp[(2) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 200 "Parser.y"
    { (yyval.node) = new DeleteNode((yyvsp[(2) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 201 "Parser.y"
    { (yyval.node) = new LibraryNode(*(yyvsp[(2) - (3)].text), nullptr, (yylsp[(1) - (3)]).first_line); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 202 "Parser.y"
    { (yyval.node) = new LibraryNode(*(yyvsp[(2) - (4)].text), (yyvsp[(3) - (4)].node), (yylsp[(1) - (4)]).first_line); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 203 "Parser.y"
    { (yyval.node) = new GotoNode(*(yyvsp[(2) - (3)].text), (yylsp[(1) - (3)]).first_line); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 204 "Parser.y"
    { (yyval.node) = new ContinueNode((yylsp[(1) - (2)]).first_line); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 205 "Parser.y"
    { (yyval.node) = new BreakNode((yylsp[(1) - (2)]).first_line); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 206 "Parser.y"
    { (yyval.node) = new ReturnNode(nullptr, (yylsp[(1) - (2)]).first_line); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 207 "Parser.y"
    { (yyval.node) = new ReturnNode((yyvsp[(2) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 208 "Parser.y"
    { (yyval.node) = new ExitNode(nullptr, (yylsp[(1) - (2)]).first_line); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 209 "Parser.y"
    { (yyval.node) = new ExitNode((yyvsp[(2) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 210 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 211 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 215 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 216 "Parser.y"
    { (yyval.node) = new ReadOnlyNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 220 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 221 "Parser.y"
    { (yyval.node) = new AssignNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 222 "Parser.y"
    { (yyval.node) = new RBindNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 223 "Parser.y"
    { (yyval.node) = new LBindNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 224 "Parser.y"
    { (yyval.node) = new RefAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 225 "Parser.y"
    { (yyval.node) = new MulAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 226 "Parser.y"
    { (yyval.node) = new DivAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 227 "Parser.y"
    { (yyval.node) = new ModAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 228 "Parser.y"
    { (yyval.node) = new AddAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 229 "Parser.y"
    { (yyval.node) = new SubAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 230 "Parser.y"
    { (yyval.node) = new LShiftAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 231 "Parser.y"
    { (yyval.node) = new RShiftAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 232 "Parser.y"
    { (yyval.node) = new AndAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 233 "Parser.y"
    { (yyval.node) = new XorAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 234 "Parser.y"
    { (yyval.node) = new OrAsNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 238 "Parser.y"
    {
		if((yyvsp[(1) - (1)].node)->children.size() == 1) {
			Node * n = (yyvsp[(1) - (1)].node);
			(yyvsp[(1) - (1)].node) = n->children[0];
			delete n;
			if((yyvsp[(1) - (1)].node)->type == NodeType::LogicAnd)
				(yyval.node) = new LogicNode((yyvsp[(1) - (1)].node), (yyvsp[(1) - (1)].node)->line);
			else (yyval.node) = (yyvsp[(1) - (1)].node);
		}	
		else (yyval.node) = new LogicNode((yyvsp[(1) - (1)].node), (yyvsp[(1) - (1)].node)->line);
	}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 249 "Parser.y"
    {
		Node * tmp;
		if((yyvsp[(1) - (5)].node)->children.size() == 1) {
			Node * n = (yyvsp[(1) - (5)].node);
			(yyvsp[(1) - (5)].node) = n->children[0];
			delete n;
			if((yyvsp[(1) - (5)].node)->type == NodeType::LogicAnd)
				tmp = new LogicNode((yyvsp[(1) - (5)].node), (yyvsp[(1) - (5)].node)->line);
			else tmp = (yyvsp[(1) - (5)].node);
		}	
		else tmp = new LogicNode((yyvsp[(1) - (5)].node), (yyvsp[(1) - (5)].node)->line);
		(yyval.node) = new CondNode(tmp, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), (yylsp[(2) - (5)]).first_line);
	}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 265 "Parser.y"
    { 
		if((yyvsp[(1) - (1)].node)->children.size() == 1) {
			Node * n = (yyvsp[(1) - (1)].node);
			(yyvsp[(1) - (1)].node) = n->children[0];
			delete n;
		}	
		(yyval.node) = new LogicOrNode((yyvsp[(1) - (1)].node), (yylsp[(1) - (1)]).first_line);
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 273 "Parser.y"
    {
		if((yyvsp[(3) - (3)].node)->children.size() == 1) {
			Node * n = (yyvsp[(3) - (3)].node);
			(yyvsp[(3) - (3)].node) = n->children[0];
			delete n;
		}
		(yyvsp[(1) - (3)].node)->children.push_back((yyvsp[(3) - (3)].node)); 
		(yyval.node) = (yyvsp[(1) - (3)].node);
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 285 "Parser.y"
    {
		if((yyvsp[(1) - (1)].node)->type == NodeType::Logic) {
			Node * n = (yyvsp[(1) - (1)].node);
			(yyvsp[(1) - (1)].node) = n->children[0];
			delete n;
		}
		(yyval.node) = new LogicAndNode((yyvsp[(1) - (1)].node), (yylsp[(1) - (1)]).first_line);
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 293 "Parser.y"
    {
		if((yyvsp[(3) - (3)].node)->type == NodeType::Logic) {
			Node * n = (yyvsp[(3) - (3)].node);
			(yyvsp[(3) - (3)].node) = n->children[0];
			delete n;
		}
		(yyvsp[(1) - (3)].node)->children.push_back((yyvsp[(3) - (3)].node));
		(yyval.node) = (yyvsp[(1) - (3)].node);
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 305 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 306 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstOr((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new OrNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 314 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 315 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstXor((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new XorNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 323 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 324 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstAnd((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new AndNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 332 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 333 "Parser.y"
    { (yyval.node) = new EQNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 334 "Parser.y"
    { (yyval.node) = new NENode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 335 "Parser.y"
    { (yyval.node) = new LikeNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 339 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 340 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstLower((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new LowerNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 345 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstGreater((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new GreaterNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 350 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstLE((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new LENode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 355 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstGE((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new GENode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 363 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 364 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstLShift((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new LShiftNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 369 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstRShift((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new RShiftNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 377 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 378 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstAdd((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new AddNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 383 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstSub((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new SubNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 391 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 392 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize)
			(yyval.node) = ConstMul((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		else (yyval.node) = new MulNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 397 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize) {
			if((yyvsp[(3) - (3)].node)->type == NodeType::Int && Int(((IntNode*)(yyvsp[(3) - (3)].node))->text) == 0 ||
				(yyvsp[(3) - (3)].node)->type == NodeType::Float && ParseFloat(((IntNode*)(yyvsp[(3) - (3)].node))->text) == 0.0 ||
				(yyvsp[(3) - (3)].node)->type == NodeType::Float64 && Float(((IntNode*)(yyvsp[(3) - (3)].node))->text, 64) == 0.0 ||
				(yyvsp[(3) - (3)].node)->type == NodeType::Char && ParseChar(((IntNode*)(yyvsp[(3) - (3)].node))->text) == 0)
					(yyval.node) = new DivNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
			else (yyval.node) = ConstDiv((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		}
		else (yyval.node) = new DivNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 408 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (3)].node)) && isConst((yyvsp[(3) - (3)].node)) && compiler->optimize) {
			if((yyvsp[(3) - (3)].node)->type == NodeType::Int && Int(((IntNode*)(yyvsp[(3) - (3)].node))->text) == 0 ||
				(yyvsp[(3) - (3)].node)->type == NodeType::Float && ParseFloat(((IntNode*)(yyvsp[(3) - (3)].node))->text) == 0.0 ||
				(yyvsp[(3) - (3)].node)->type == NodeType::Float64 && Float(((IntNode*)(yyvsp[(3) - (3)].node))->text, 64) == 0.0 ||
				(yyvsp[(3) - (3)].node)->type == NodeType::Char && ParseChar(((IntNode*)(yyvsp[(3) - (3)].node))->text) == 0)
					(yyval.node) = new ModNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
			else (yyval.node) = ConstMod((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), compiler->fileName, (yylsp[(2) - (3)]).first_line);
		}
		else (yyval.node) = new ModNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line);
	}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 422 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 423 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstPlus((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new PlusNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 428 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstMinus((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new MinusNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 433 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstBitNot((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new BitNotNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 438 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstNot((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new NotNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 443 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstIncr((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new LIncrNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 448 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstDecr((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new LDecrNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 453 "Parser.y"
    { (yyval.node) = new AddrOfNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 454 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstTypeOf((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new IdOfNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 459 "Parser.y"
    {
		if(((yyvsp[(2) - (2)].node)->type == NodeType::Object || isConst((yyvsp[(2) - (2)].node))) && compiler->optimize)
			(yyval.node) = ConstTypeOf((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new TypeOfNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 464 "Parser.y"
    { (yyval.node) = new ParentOfNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 465 "Parser.y"
    {
		if(((yyvsp[(2) - (2)].node)->type == NodeType::Object || isConst((yyvsp[(2) - (2)].node))) && compiler->optimize)
			(yyval.node) = ConstTypeStr((yyvsp[(2) - (2)].node), compiler->fileName, (yylsp[(1) - (2)]).first_line);
		else (yyval.node) = new TypeStrNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 470 "Parser.y"
    {
		if(isConst((yyvsp[(2) - (2)].node)) && compiler->optimize)
			(yyval.node) = (yyvsp[(2) - (2)].node);
		else (yyval.node) = new MoveNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line);
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 475 "Parser.y"
    { (yyval.node) = new CopyNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 476 "Parser.y"
    { (yyval.node) = new AllocNode((yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 480 "Parser.y"
    { (yyval.node) = new ExprListNode((yyvsp[(1) - (1)].node), (yylsp[(1) - (1)]).first_line); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 481 "Parser.y"
    { (yyvsp[(1) - (3)].node)->children.push_back((yyvsp[(3) - (3)].node)); (yyval.node) = (yyvsp[(1) - (3)].node); }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 485 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 486 "Parser.y"
    { (yyval.node) = new NewNode((yyvsp[(2) - (4)].node), nullptr, (yylsp[(1) - (4)]).first_line); }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 487 "Parser.y"
    { (yyval.node) = new NewNode((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yylsp[(1) - (5)]).first_line); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 488 "Parser.y"
    { (yyval.node) = new NewArrNode((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yylsp[(1) - (5)]).first_line); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 492 "Parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 493 "Parser.y"
    { (yyval.node) = new AtNode((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), (yylsp[(2) - (4)]).first_line); }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 494 "Parser.y"
    { (yyval.node) = new CallNode((yyvsp[(1) - (3)].node), nullptr, (yylsp[(2) - (3)]).first_line); }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 495 "Parser.y"
    { (yyval.node) = new CallArrNode((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), (yylsp[(2) - (4)]).first_line); }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 496 "Parser.y"
    { (yyval.node) = new CallNode((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), (yylsp[(2) - (4)]).first_line); }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 497 "Parser.y"
    { (yyval.node) = new AttrNode(*(yyvsp[(3) - (3)].text), (yyvsp[(1) - (3)].node), (yylsp[(2) - (3)]).first_line); }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 498 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstIncr((yyvsp[(1) - (2)].node), compiler->fileName, (yylsp[(2) - (2)]).first_line);
		else (yyval.node) = new RIncrNode((yyvsp[(1) - (2)].node), (yylsp[(2) - (2)]).first_line);
	}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 503 "Parser.y"
    {
		if(isConst((yyvsp[(1) - (2)].node)) && compiler->optimize)
			(yyval.node) = ConstDecr((yyvsp[(1) - (2)].node), compiler->fileName, (yylsp[(2) - (2)]).first_line);
		else (yyval.node) = new RDecrNode((yyvsp[(1) - (2)].node), (yylsp[(2) - (2)]).first_line);
	}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 511 "Parser.y"
    { (yyval.node) = new TrueNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 512 "Parser.y"
    { (yyval.node) = new FalseNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 513 "Parser.y"
    { (yyval.node) = new NoneNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 514 "Parser.y"
    { (yyval.node) = new IdNode(*(yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 515 "Parser.y"
    { (yyval.node) = new AttachNode(*(yyvsp[(2) - (2)].text), (yylsp[(1) - (2)]).first_line); }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 516 "Parser.y"
    { (yyval.node) = new IntNode(*(yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line); }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 517 "Parser.y"
    { (yyval.node) = new FloatNode(*(yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line); }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 518 "Parser.y"
    { (yyval.node) = new Float64Node(*(yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line); }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 519 "Parser.y"
    { (yyval.node) = new CharNode(*(yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 520 "Parser.y"
    { (yyval.node) = new StringNode(*(yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 521 "Parser.y"
    { (yyval.node) = new GlobalNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 522 "Parser.y"
    { (yyval.node) = new MainNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 523 "Parser.y"
    { (yyval.node) = new ArgsNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 524 "Parser.y"
    { (yyval.node) = new MeNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 525 "Parser.y"
    { (yyval.node) = new ParentNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 526 "Parser.y"
    { (yyval.node) = new ErrorNode((yylsp[(1) - (1)]).first_line); }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 527 "Parser.y"
    { (yyval.node) = new ExternalNode((yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node), (yylsp[(1) - (6)]).first_line); }
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 528 "Parser.y"
    { (yyval.node) = new SwapNode((yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node), (yylsp[(1) - (6)]).first_line); }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 529 "Parser.y"
    { (yyval.node) = new ObjectNode(nullptr , (yyvsp[(2) - (2)].node), (yylsp[(1) - (2)]).first_line); }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 530 "Parser.y"
    { (yyval.node) = new ObjectNode((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), (yylsp[(1) - (5)]).first_line); }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 531 "Parser.y"
    { (yyval.node) = new RefArrayNode((yyvsp[(3) - (4)].node), (yylsp[(1) - (4)]).first_line); }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 532 "Parser.y"
    { (yyval.node) = new RefArrayNode(nullptr, (yylsp[(1) - (3)]).first_line); }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 533 "Parser.y"
    { (yyval.node) = new ArrayNode((yyvsp[(2) - (3)].node), (yylsp[(1) - (3)]).first_line); }
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 534 "Parser.y"
    { (yyval.node) = new ArrayNode(nullptr, (yylsp[(1) - (2)]).first_line); }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 535 "Parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;


/* Line 1792 of yacc.c  */
#line 3159 "Parser.cpp"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, compiler, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, compiler, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc, compiler);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, compiler);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, compiler, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, compiler);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, compiler);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 541 "Parser.y"








