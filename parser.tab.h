
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 33 "parser.y"

    int int_val;
    float float_val;
    char* str_val;
    DataType type_val; // To hold type information
    struct ASTNode* ast; // AST node pointers



/* Line 1676 of yacc.c  */
#line 130 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


