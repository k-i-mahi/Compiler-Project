
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 9 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
#include "symbol_table.h"
#include "ast.h"
#include "eval.h"
#include "tac_gen.h"
#include "c_gen.h"

// External declarations
extern int yylex();
extern int yylineno;
extern char* yytext;
void yyerror(const char *s);
static void insert_param_symbols(ASTNode *params);

ASTNode* root = NULL; // The root of the abstract syntax tree


/* Line 189 of yacc.c  */
#line 96 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_INT = 258,
     T_FLOAT = 259,
     T_BOOL = 260,
     T_CHAR = 261,
     T_STRING = 262,
     T_VOID = 263,
     T_GRAPH = 264,
     T_TREE = 265,
     T_RANGE_TREE = 266,
     T_DSU = 267,
     T_MATRIX = 268,
     T_ORDERED_SET = 269,
     T_STACK = 270,
     T_QUEUE = 271,
     T_IF = 272,
     T_ELSE = 273,
     T_FOR = 274,
     T_WHILE = 275,
     T_RETURN = 276,
     T_BREAK = 277,
     T_CONTINUE = 278,
     T_FUNCTION = 279,
     T_MAIN = 280,
     T_START = 281,
     T_END = 282,
     T_IDENTIFIER = 283,
     T_INT_LITERAL = 284,
     T_FLOAT_LITERAL = 285,
     T_STRING_LITERAL = 286,
     T_BOOL_LITERAL = 287,
     T_CHAR_LITERAL = 288,
     T_ASSIGN = 289,
     T_PLUS = 290,
     T_MINUS = 291,
     T_MULTIPLY = 292,
     T_DIVIDE = 293,
     T_MODULO = 294,
     T_PLUS_ASSIGN = 295,
     T_MINUS_ASSIGN = 296,
     T_STAR_ASSIGN = 297,
     T_SLASH_ASSIGN = 298,
     T_PERCENT_ASSIGN = 299,
     T_EQ = 300,
     T_NEQ = 301,
     T_LT = 302,
     T_GT = 303,
     T_LTE = 304,
     T_GTE = 305,
     T_AND = 306,
     T_OR = 307,
     T_NOT = 308,
     T_LPAREN = 309,
     T_RPAREN = 310,
     T_LBRACE = 311,
     T_RBRACE = 312,
     T_LBRACKET = 313,
     T_RBRACKET = 314,
     T_COMMA = 315,
     T_SEMICOLON = 316,
     T_MAHI_READ = 317,
     T_MAHI_WRITE = 318,
     T_MAHI_SORT = 319,
     T_MAHI_PUSH = 320,
     T_EOF = 321,
     UMINUS = 322,
     LOWER_THAN_ELSE = 323
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 33 "parser.y"

    int int_val;
    float float_val;
    char* str_val;
    DataType type_val; // To hold type information
    struct ASTNode* ast; // AST node pointers



/* Line 214 of yacc.c  */
#line 210 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 222 "parser.tab.c"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   553

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNRULES -- Number of states.  */
#define YYNSTATES  168

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      65,    66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    11,    12,    15,    16,    25,    28,
      30,    34,    35,    37,    38,    41,    43,    45,    47,    49,
      51,    53,    56,    59,    63,    65,    67,    71,    72,    74,
      75,    80,    84,    90,    92,    94,    96,    98,   100,   102,
     104,   106,   108,   110,   112,   114,   116,   118,   121,   127,
     135,   141,   150,   159,   163,   167,   171,   175,   179,   183,
     185,   187,   189,   191,   193,   198,   200,   204,   208,   212,
     216,   220,   224,   228,   232,   236,   240,   244,   248,   252,
     255,   258,   262,   267,   272,   277
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      70,     0,    -1,    -1,    71,    72,    26,    25,    82,    27,
      -1,    -1,    72,    73,    -1,    -1,    24,    85,    28,    54,
      77,    55,    74,    82,    -1,    85,    28,    -1,    75,    -1,
      76,    60,    75,    -1,    -1,    76,    -1,    -1,    79,    78,
      -1,    84,    -1,    86,    -1,    87,    -1,    88,    -1,    89,
      -1,    82,    -1,    22,    61,    -1,    23,    61,    -1,    21,
      90,    61,    -1,    61,    -1,    90,    -1,    80,    60,    90,
      -1,    -1,    80,    -1,    -1,    56,    83,    78,    57,    -1,
      85,    28,    61,    -1,    85,    28,    34,    90,    61,    -1,
       3,    -1,     4,    -1,     5,    -1,     6,    -1,     7,    -1,
       8,    -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,
      13,    -1,    14,    -1,    15,    -1,    16,    -1,    90,    61,
      -1,    17,    54,    90,    55,    79,    -1,    17,    54,    90,
      55,    79,    18,    79,    -1,    20,    54,    90,    55,    79,
      -1,    19,    54,    84,    90,    61,    90,    55,    79,    -1,
      19,    54,    86,    90,    61,    90,    55,    79,    -1,    28,
      34,    90,    -1,    28,    40,    90,    -1,    28,    41,    90,
      -1,    28,    42,    90,    -1,    28,    43,    90,    -1,    28,
      44,    90,    -1,    29,    -1,    30,    -1,    31,    -1,    32,
      -1,    33,    -1,    28,    54,    81,    55,    -1,    28,    -1,
      90,    35,    90,    -1,    90,    36,    90,    -1,    90,    37,
      90,    -1,    90,    38,    90,    -1,    90,    39,    90,    -1,
      90,    45,    90,    -1,    90,    46,    90,    -1,    90,    47,
      90,    -1,    90,    48,    90,    -1,    90,    49,    90,    -1,
      90,    50,    90,    -1,    90,    51,    90,    -1,    90,    52,
      90,    -1,    53,    90,    -1,    36,    90,    -1,    54,    90,
      55,    -1,    63,    54,    90,    55,    -1,    62,    54,    28,
      55,    -1,    64,    54,    90,    55,    -1,    65,    54,    90,
      60,    90,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,    99,   120,   121,   134,   133,   151,   161,
     162,   170,   171,   175,   176,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   201,   202,   206,   207,   212,
     211,   225,   233,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   262,   266,   272,
     282,   291,   299,   310,   320,   328,   336,   344,   352,   360,
     361,   362,   363,   364,   365,   369,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   396,   404,   408
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_INT", "T_FLOAT", "T_BOOL", "T_CHAR",
  "T_STRING", "T_VOID", "T_GRAPH", "T_TREE", "T_RANGE_TREE", "T_DSU",
  "T_MATRIX", "T_ORDERED_SET", "T_STACK", "T_QUEUE", "T_IF", "T_ELSE",
  "T_FOR", "T_WHILE", "T_RETURN", "T_BREAK", "T_CONTINUE", "T_FUNCTION",
  "T_MAIN", "T_START", "T_END", "T_IDENTIFIER", "T_INT_LITERAL",
  "T_FLOAT_LITERAL", "T_STRING_LITERAL", "T_BOOL_LITERAL",
  "T_CHAR_LITERAL", "T_ASSIGN", "T_PLUS", "T_MINUS", "T_MULTIPLY",
  "T_DIVIDE", "T_MODULO", "T_PLUS_ASSIGN", "T_MINUS_ASSIGN",
  "T_STAR_ASSIGN", "T_SLASH_ASSIGN", "T_PERCENT_ASSIGN", "T_EQ", "T_NEQ",
  "T_LT", "T_GT", "T_LTE", "T_GTE", "T_AND", "T_OR", "T_NOT", "T_LPAREN",
  "T_RPAREN", "T_LBRACE", "T_RBRACE", "T_LBRACKET", "T_RBRACKET",
  "T_COMMA", "T_SEMICOLON", "T_MAHI_READ", "T_MAHI_WRITE", "T_MAHI_SORT",
  "T_MAHI_PUSH", "T_EOF", "UMINUS", "LOWER_THAN_ELSE", "$accept",
  "program", "$@1", "function_declarations", "function_declaration", "$@2",
  "parameter_decl", "parameter_list", "opt_parameter_list", "statements",
  "statement", "argument_list", "opt_argument_list", "block_statement",
  "$@3", "declaration_statement", "type_specifier", "expression_statement",
  "if_statement", "while_statement", "for_statement", "expression", 0
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
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    71,    70,    72,    72,    74,    73,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    80,    80,    81,    81,    83,
      82,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    87,    87,
      88,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     0,     2,     0,     8,     2,     1,
       3,     0,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     1,     1,     3,     0,     1,     0,
       4,     3,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     5,     7,
       5,     8,     8,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     4,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     4,     4,     4,     6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     4,     1,     0,     0,     0,     5,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     0,     0,     0,    29,     0,    11,    13,     3,
       9,    12,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    59,    60,    61,    62,    63,     0,     0,     0,    24,
       0,     0,     0,     0,     0,    13,    20,    15,     0,    16,
      17,    18,    19,     0,     0,     6,     8,     0,     0,     0,
       0,    21,    22,     0,     0,     0,     0,     0,     0,    27,
      80,    79,     0,     0,     0,     0,     0,    30,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    47,    10,     0,     0,     0,     0,     0,
      23,    53,    54,    55,    56,    57,    58,    28,     0,    25,
      81,     0,     0,     0,     0,     0,    31,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       7,     0,     0,     0,     0,     0,    64,    83,    82,    84,
       0,     0,    48,     0,     0,    50,    26,     0,    32,     0,
       0,     0,    85,    49,     0,     0,    51,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     4,     7,   105,    30,    31,    32,    54,
      55,   117,   118,    56,    28,    57,    58,    59,    60,    61,
      62,    63
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -140
static const yytype_int16 yypact[] =
{
    -140,     3,  -140,  -140,     9,   537,   -19,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,   -15,   -44,   -35,  -140,    -3,   537,   115,  -140,
    -140,   -33,   -21,    15,   -10,    -9,    -8,   191,   -11,     6,
     -26,  -140,  -140,  -140,  -140,  -140,   191,   191,   191,  -140,
      -2,    14,    23,    24,    -6,   115,  -140,  -140,    41,  -140,
    -140,  -140,  -140,    54,   537,  -140,  -140,   191,   178,   191,
     212,  -140,  -140,   191,   191,   191,   191,   191,   191,   191,
     470,   470,   302,    51,   191,   191,   191,  -140,  -140,   -30,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,  -140,  -140,   -44,   323,   191,   191,   344,
    -140,   470,   470,   470,   470,   470,   470,    20,    26,   470,
    -140,    27,   365,   386,   284,   191,  -140,   -16,   -16,  -140,
    -140,  -140,    37,    37,    37,    37,    37,    37,   117,   488,
    -140,   115,   230,   248,   115,   191,  -140,  -140,  -140,  -140,
     191,   266,    66,   191,   191,  -140,   470,   407,  -140,   115,
     428,   449,  -140,  -140,   115,   115,  -140,  -140
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,  -140,  -140,  -140,    21,  -140,  -140,    31,
    -139,  -140,  -140,   -22,  -140,    19,     2,    28,  -140,  -140,
    -140,   -37
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      70,    26,   152,     3,   125,   155,    23,    22,    73,    80,
      81,    82,    25,    24,    74,    75,    76,    77,    78,    27,
     163,    92,    93,    94,    29,   166,   167,    64,    79,    33,
     106,   126,   109,     5,    65,     6,   111,   112,   113,   114,
     115,   116,   119,    66,    67,    68,    69,   122,   123,   124,
      71,    87,    83,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,    33,    72,    84,    89,
     142,   143,    90,    91,    92,    93,    94,    85,    86,   121,
     145,   146,   147,   140,   159,   104,    88,   107,   151,    90,
      91,    92,    93,    94,     0,     0,   108,     0,     0,    95,
      96,    97,    98,    99,   100,   101,   102,     0,   156,     0,
       0,     0,     0,   157,     0,   103,   160,   161,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    34,     0,    35,    36,    37,    38,    39,     0,
       0,     0,     0,    40,    41,    42,    43,    44,    45,     0,
       0,    46,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   100,    47,    48,
       0,    25,     0,     0,     0,     0,    49,    50,    51,    52,
      53,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,    41,    42,    43,
      44,    45,     0,     0,    46,     0,     0,     0,     0,    40,
      41,    42,    43,    44,    45,     0,     0,    46,     0,     0,
       0,    47,    48,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    47,    48,     0,    90,    91,    92,
      93,    94,     0,    50,    51,    52,    53,    95,    96,    97,
      98,    99,   100,   101,   102,    90,    91,    92,    93,    94,
       0,     0,     0,   110,     0,    95,    96,    97,    98,    99,
     100,   101,   102,    90,    91,    92,    93,    94,     0,     0,
       0,   153,     0,    95,    96,    97,    98,    99,   100,   101,
     102,    90,    91,    92,    93,    94,     0,     0,     0,   154,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    90,
      91,    92,    93,    94,     0,     0,     0,   158,     0,    95,
      96,    97,    98,    99,   100,   101,   102,    90,    91,    92,
      93,    94,     0,     0,   150,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,     0,     0,   120,    90,    91,
      92,    93,    94,     0,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   100,   101,   102,     0,     0,   141,    90,
      91,    92,    93,    94,     0,     0,     0,     0,     0,    95,
      96,    97,    98,    99,   100,   101,   102,     0,     0,   144,
      90,    91,    92,    93,    94,     0,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   100,   101,   102,     0,     0,
     148,    90,    91,    92,    93,    94,     0,     0,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,     0,
       0,   149,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
       0,     0,   162,    90,    91,    92,    93,    94,     0,     0,
       0,     0,     0,    95,    96,    97,    98,    99,   100,   101,
     102,     0,     0,   164,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   100,
     101,   102,     0,     0,   165,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,    90,    91,    92,    93,    94,     0,     0,
       0,     0,     0,    95,    96,    97,    98,    99,   100,   101,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21
};

static const yytype_int16 yycheck[] =
{
      37,    23,   141,     0,    34,   144,    25,     5,    34,    46,
      47,    48,    56,    28,    40,    41,    42,    43,    44,    54,
     159,    37,    38,    39,    27,   164,   165,    60,    54,    27,
      67,    61,    69,    24,    55,    26,    73,    74,    75,    76,
      77,    78,    79,    28,    54,    54,    54,    84,    85,    86,
      61,    57,    54,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    64,    61,    54,    28,
     107,   108,    35,    36,    37,    38,    39,    54,    54,    28,
      60,    55,    55,   105,    18,    64,    55,    68,   125,    35,
      36,    37,    38,    39,    -1,    -1,    68,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,   145,    -1,
      -1,    -1,    -1,   150,    -1,    61,   153,   154,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      -1,    36,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    53,    54,
      -1,    56,    -1,    -1,    -1,    -1,    61,    62,    63,    64,
      65,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    53,    54,    -1,    35,    36,    37,
      38,    39,    -1,    62,    63,    64,    65,    45,    46,    47,
      48,    49,    50,    51,    52,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    61,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    61,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    35,    36,    37,    38,    39,    -1,    -1,    -1,    61,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    61,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    35,    36,    37,
      38,    39,    -1,    -1,    60,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    -1,    55,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    55,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    55,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      55,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      -1,    55,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,    55,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    -1,    55,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    -1,    55,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,    71,     0,    72,    24,    26,    73,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    85,    25,    28,    56,    82,    54,    83,    27,
      75,    76,    77,    85,    17,    19,    20,    21,    22,    23,
      28,    29,    30,    31,    32,    33,    36,    53,    54,    61,
      62,    63,    64,    65,    78,    79,    82,    84,    85,    86,
      87,    88,    89,    90,    60,    55,    28,    54,    54,    54,
      90,    61,    61,    34,    40,    41,    42,    43,    44,    54,
      90,    90,    90,    54,    54,    54,    54,    57,    78,    28,
      35,    36,    37,    38,    39,    45,    46,    47,    48,    49,
      50,    51,    52,    61,    75,    74,    90,    84,    86,    90,
      61,    90,    90,    90,    90,    90,    90,    80,    81,    90,
      55,    28,    90,    90,    90,    34,    61,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      82,    55,    90,    90,    55,    60,    55,    55,    55,    55,
      60,    90,    79,    61,    61,    79,    90,    90,    61,    18,
      90,    90,    55,    79,    55,    55,    79,    79
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 99 "parser.y"
    {
        init_symbol_table();
        if (linear_verbose)
            printf("Program Start: Global scope initialized.\n");
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    {
        root = create_node(NODE_PROGRAM);
        root->middle = (yyvsp[(2) - (6)].ast); // function declarations
        root->left = (yyvsp[(5) - (6)].ast);   // main block
        if (linear_verbose) {
            printf("Parse successful: Program structure is valid.\n");
            print_ast(root, 0);
            print_all_scopes();
        }
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 122 "parser.y"
    {
        if ((yyvsp[(1) - (2)].ast)) {
            add_sibling((yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast));
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
        } else {
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        }
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    {
        enter_scope();
        insert_param_symbols((yyvsp[(5) - (6)].ast));
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    {
        (yyval.ast) = create_node(NODE_FUNC_DECL);
        (yyval.ast)->name = strdup((yyvsp[(3) - (8)].str_val));
        (yyval.ast)->int_val = (yyvsp[(2) - (8)].type_val); // return type
        (yyval.ast)->left = (yyvsp[(5) - (8)].ast);    // params
        (yyval.ast)->right = (yyvsp[(8) - (8)].ast);   // body
        exit_scope();
        free((yyvsp[(3) - (8)].str_val));
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    {
        (yyval.ast) = create_node(NODE_VAR_DECL);
        (yyval.ast)->name = strdup((yyvsp[(2) - (2)].str_val));
        (yyval.ast)->int_val = (yyvsp[(1) - (2)].type_val);
        free((yyvsp[(2) - (2)].str_val));
    ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    {
        add_sibling((yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
        (yyval.ast) = (yyvsp[(1) - (3)].ast);
    ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    {
        if ((yyvsp[(1) - (2)].ast) != NULL) {
            (yyval.ast) = (yyvsp[(1) - (2)].ast);
            add_sibling((yyval.ast), (yyvsp[(2) - (2)].ast));
        } else {
            (yyval.ast) = (yyvsp[(2) - (2)].ast);
        }
    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    { (yyval.ast) = create_node(NODE_BREAK); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { (yyval.ast) = create_node(NODE_CONTINUE); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    { (yyval.ast) = create_node(NODE_RETURN); (yyval.ast)->left = (yyvsp[(2) - (3)].ast); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    { (yyval.ast) = create_node(NODE_EMPTY); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 201 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    { add_sibling((yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); (yyval.ast) = (yyvsp[(1) - (3)].ast); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    { 
        enter_scope(); 
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    {
        (yyval.ast) = create_node(NODE_BLOCK);
        (yyval.ast)->left = (yyvsp[(3) - (4)].ast);
        exit_scope();
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 226 "parser.y"
    {
        insert_symbol((yyvsp[(2) - (3)].str_val), (yyvsp[(1) - (3)].type_val), yylineno);
        (yyval.ast) = create_node(NODE_VAR_DECL);
        (yyval.ast)->name = strdup((yyvsp[(2) - (3)].str_val));
        (yyval.ast)->int_val = (yyvsp[(1) - (3)].type_val);
        free((yyvsp[(2) - (3)].str_val)); 
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 234 "parser.y"
    {
        insert_symbol((yyvsp[(2) - (5)].str_val), (yyvsp[(1) - (5)].type_val), yylineno);
        (yyval.ast) = create_node(NODE_VAR_DECL);
        (yyval.ast)->name = strdup((yyvsp[(2) - (5)].str_val));
        (yyval.ast)->int_val = (yyvsp[(1) - (5)].type_val);
        (yyval.ast)->left = (yyvsp[(4) - (5)].ast);
        free((yyvsp[(2) - (5)].str_val));
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    { (yyval.type_val) = TYPE_INT; ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 246 "parser.y"
    { (yyval.type_val) = TYPE_FLOAT; ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    { (yyval.type_val) = TYPE_BOOL; ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 248 "parser.y"
    { (yyval.type_val) = TYPE_CHAR; ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    { (yyval.type_val) = TYPE_STRING; ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 250 "parser.y"
    { (yyval.type_val) = TYPE_VOID; ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    { (yyval.type_val) = TYPE_GRAPH; ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    { (yyval.type_val) = TYPE_TREE; ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    { (yyval.type_val) = TYPE_RANGE_TREE; ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 254 "parser.y"
    { (yyval.type_val) = TYPE_DSU; ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 255 "parser.y"
    { (yyval.type_val) = TYPE_MATRIX; ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 256 "parser.y"
    { (yyval.type_val) = TYPE_ORDERED_SET; ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 257 "parser.y"
    { (yyval.type_val) = TYPE_STACK; ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    { (yyval.type_val) = TYPE_QUEUE; ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 262 "parser.y"
    { (yyval.ast) = (yyvsp[(1) - (2)].ast); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    {
        (yyval.ast) = create_node(NODE_IF);
        (yyval.ast)->left = (yyvsp[(3) - (5)].ast);
        (yyval.ast)->right = (yyvsp[(5) - (5)].ast);
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    {
        (yyval.ast) = create_node(NODE_IF);
        (yyval.ast)->left = (yyvsp[(3) - (7)].ast);
        (yyval.ast)->middle = (yyvsp[(5) - (7)].ast);
        (yyval.ast)->right = (yyvsp[(7) - (7)].ast);
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    {
        (yyval.ast) = create_node(NODE_WHILE);
        (yyval.ast)->left = (yyvsp[(3) - (5)].ast);
        (yyval.ast)->right = (yyvsp[(5) - (5)].ast);
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    {
        (yyval.ast) = create_node(NODE_FOR);
        (yyval.ast)->left = (yyvsp[(3) - (8)].ast);   // init
        (yyval.ast)->middle = (yyvsp[(4) - (8)].ast); // cond
        (yyval.ast)->right = (yyvsp[(6) - (8)].ast);  // inc
        (yyval.ast)->body = (yyvsp[(8) - (8)].ast);   // body
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 300 "parser.y"
    {
        (yyval.ast) = create_node(NODE_FOR);
        (yyval.ast)->left = (yyvsp[(3) - (8)].ast);   // init
        (yyval.ast)->middle = (yyvsp[(4) - (8)].ast); // cond
        (yyval.ast)->right = (yyvsp[(6) - (8)].ast);  // inc
        (yyval.ast)->body = (yyvsp[(8) - (8)].ast);   // body
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 311 "parser.y"
    {
        if (lookup_symbol((yyvsp[(1) - (3)].str_val)) == NULL) {
            yyerror("Semantic Error: Assignment to undeclared identifier");
        }
        (yyval.ast) = create_node(NODE_ASSIGN);
        (yyval.ast)->left = create_identifier_node((yyvsp[(1) - (3)].str_val));
        (yyval.ast)->right = (yyvsp[(3) - (3)].ast);
        free((yyvsp[(1) - (3)].str_val));
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 321 "parser.y"
    {
        if (lookup_symbol((yyvsp[(1) - (3)].str_val)) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        (yyval.ast) = create_node(NODE_ASSIGN);
        (yyval.ast)->left = create_identifier_node((yyvsp[(1) - (3)].str_val));
        (yyval.ast)->right = create_binary_op_node("+", create_identifier_node(strdup((yyval.ast)->left->name)), (yyvsp[(3) - (3)].ast));
        free((yyvsp[(1) - (3)].str_val));
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {
        if (lookup_symbol((yyvsp[(1) - (3)].str_val)) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        (yyval.ast) = create_node(NODE_ASSIGN);
        (yyval.ast)->left = create_identifier_node((yyvsp[(1) - (3)].str_val));
        (yyval.ast)->right = create_binary_op_node("-", create_identifier_node(strdup((yyval.ast)->left->name)), (yyvsp[(3) - (3)].ast));
        free((yyvsp[(1) - (3)].str_val));
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 337 "parser.y"
    {
        if (lookup_symbol((yyvsp[(1) - (3)].str_val)) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        (yyval.ast) = create_node(NODE_ASSIGN);
        (yyval.ast)->left = create_identifier_node((yyvsp[(1) - (3)].str_val));
        (yyval.ast)->right = create_binary_op_node("*", create_identifier_node(strdup((yyval.ast)->left->name)), (yyvsp[(3) - (3)].ast));
        free((yyvsp[(1) - (3)].str_val));
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    {
        if (lookup_symbol((yyvsp[(1) - (3)].str_val)) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        (yyval.ast) = create_node(NODE_ASSIGN);
        (yyval.ast)->left = create_identifier_node((yyvsp[(1) - (3)].str_val));
        (yyval.ast)->right = create_binary_op_node("/", create_identifier_node(strdup((yyval.ast)->left->name)), (yyvsp[(3) - (3)].ast));
        free((yyvsp[(1) - (3)].str_val));
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    {
        if (lookup_symbol((yyvsp[(1) - (3)].str_val)) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        (yyval.ast) = create_node(NODE_ASSIGN);
        (yyval.ast)->left = create_identifier_node((yyvsp[(1) - (3)].str_val));
        (yyval.ast)->right = create_binary_op_node("%", create_identifier_node(strdup((yyval.ast)->left->name)), (yyvsp[(3) - (3)].ast));
        free((yyvsp[(1) - (3)].str_val));
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    { (yyval.ast) = create_int_literal_node((yyvsp[(1) - (1)].int_val)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 361 "parser.y"
    { (yyval.ast) = create_float_literal_node((yyvsp[(1) - (1)].float_val)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 362 "parser.y"
    { (yyval.ast) = create_string_literal_node((yyvsp[(1) - (1)].str_val)); free((yyvsp[(1) - (1)].str_val)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 363 "parser.y"
    { (yyval.ast) = create_node(NODE_LITERAL_BOOL); (yyval.ast)->int_val = (yyvsp[(1) - (1)].int_val); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 364 "parser.y"
    { (yyval.ast) = create_char_literal_node((yyvsp[(1) - (1)].str_val)); free((yyvsp[(1) - (1)].str_val)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 365 "parser.y"
    {
        (yyval.ast) = create_func_call_node((yyvsp[(1) - (4)].str_val), (yyvsp[(3) - (4)].ast));
        free((yyvsp[(1) - (4)].str_val));
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    {
        if (lookup_symbol((yyvsp[(1) - (1)].str_val)) == NULL) {
            yyerror("Semantic Error: Use of undeclared identifier");
        }
        (yyval.ast) = create_identifier_node((yyvsp[(1) - (1)].str_val));
        free((yyvsp[(1) - (1)].str_val));
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 376 "parser.y"
    { (yyval.ast) = create_binary_op_node("+", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 377 "parser.y"
    { (yyval.ast) = create_binary_op_node("-", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    { (yyval.ast) = create_binary_op_node("*", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    { (yyval.ast) = create_binary_op_node("/", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    { (yyval.ast) = create_binary_op_node("%", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 381 "parser.y"
    { (yyval.ast) = create_binary_op_node("==", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 382 "parser.y"
    { (yyval.ast) = create_binary_op_node("!=", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    { (yyval.ast) = create_binary_op_node("<", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 384 "parser.y"
    { (yyval.ast) = create_binary_op_node(">", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 385 "parser.y"
    { (yyval.ast) = create_binary_op_node("<=", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 386 "parser.y"
    { (yyval.ast) = create_binary_op_node(">=", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    { (yyval.ast) = create_binary_op_node("&&", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 388 "parser.y"
    { (yyval.ast) = create_binary_op_node("||", (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 389 "parser.y"
    { (yyval.ast) = create_unary_op_node("!", (yyvsp[(2) - (2)].ast)); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 390 "parser.y"
    { (yyval.ast) = create_unary_op_node("-", (yyvsp[(2) - (2)].ast)); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 391 "parser.y"
    { (yyval.ast) = (yyvsp[(2) - (3)].ast); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 393 "parser.y"
    {
        (yyval.ast) = create_func_call_node("MAHI_write", (yyvsp[(3) - (4)].ast));
    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 397 "parser.y"
    {
        if (lookup_symbol((yyvsp[(3) - (4)].str_val)) == NULL) {
            yyerror("Semantic Error: Use of undeclared identifier");
        }
        (yyval.ast) = create_func_call_node("MAHI_read", create_identifier_node((yyvsp[(3) - (4)].str_val)));
        free((yyvsp[(3) - (4)].str_val));
    ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 405 "parser.y"
    {
        (yyval.ast) = create_func_call_node("MAHI_sort", (yyvsp[(3) - (4)].ast));
    ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 409 "parser.y"
    {
        ASTNode *args = (yyvsp[(3) - (6)].ast);
        add_sibling(args, (yyvsp[(5) - (6)].ast));
        (yyval.ast) = create_func_call_node("MAHI_push", args);
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2389 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 1675 of yacc.c  */
#line 416 "parser.y"


/* === C Code Section === */

int main(int argc, char **argv) {
    const char *path = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
            linear_verbose = 1;
        else if (argv[i][0] != '-')
            path = argv[i];
    }

    FILE *file = NULL;
    if (path) {
        file = fopen(path, "r");
        if (!file) {
            perror(path);
            return 1;
        }
        yyin = file;
    }

    int ok = yyparse() == 0;
    if (ok && root) {
        char tac_path[1024];
        int tac_ok = generate_three_address_code(root, path, tac_path, sizeof(tac_path));
        if (tac_ok == 0) {
            printf("3AC generated: %s\n", tac_path);
        } else {
            fprintf(stderr, "Warning: failed to generate 3AC (code=%d).\n", tac_ok);
        }

        char c_path[1024];
        int c_ok = generate_c_code(root, path, c_path, sizeof(c_path));
        if (c_ok == 0) {
            printf("C generated: %s\n", c_path);
        } else {
            fprintf(stderr, "Warning: failed to generate C code (code=%d).\n", c_ok);
        }

        interpret(root);
        free_ast(root);
        root = NULL;
    } else if (!ok) {
        fprintf(stderr, "Compilation failed.\n");
    }

    destroy_symbol_table();

    if (file)
        fclose(file);

    return ok ? 0 : 1;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse Error at line %d: %s near '%s'\n", yylineno, s, yytext);
}

static void insert_param_symbols(ASTNode *params) {
    for (ASTNode *p = params; p; p = p->next) {
        if (p->name)
            insert_symbol(p->name, (DataType)p->int_val, yylineno);
    }
}

