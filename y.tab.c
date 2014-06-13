
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
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 11 "parser.y"


/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine



/* Line 189 of yacc.c  */
#line 90 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
     T_Void = 258,
     T_Bool = 259,
     T_Int = 260,
     T_Double = 261,
     T_String = 262,
     T_Class = 263,
     T_This = 264,
     T_Interface = 265,
     T_Implements = 266,
     T_Extends = 267,
     T_New = 268,
     T_NewArray = 269,
     T_Print = 270,
     T_ReadInteger = 271,
     T_ReadLine = 272,
     T_Error = 273,
     T_LessEqual = 274,
     T_GreaterEqual = 275,
     T_Equal = 276,
     T_NotEqual = 277,
     T_Dims = 278,
     T_And = 279,
     T_Or = 280,
     T_Null = 281,
     T_While = 282,
     T_For = 283,
     T_If = 284,
     T_Else = 285,
     T_Return = 286,
     T_Break = 287,
     T_Switch = 288,
     T_Case = 289,
     T_Default = 290,
     T_Increment = 291,
     T_Decrement = 292,
     UMINUS = 293,
     T_Identifier = 294,
     T_StringConstant = 295,
     T_IntConstant = 296,
     T_DoubleConstant = 297,
     T_BoolConstant = 298
   };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_This 264
#define T_Interface 265
#define T_Implements 266
#define T_Extends 267
#define T_New 268
#define T_NewArray 269
#define T_Print 270
#define T_ReadInteger 271
#define T_ReadLine 272
#define T_Error 273
#define T_LessEqual 274
#define T_GreaterEqual 275
#define T_Equal 276
#define T_NotEqual 277
#define T_Dims 278
#define T_And 279
#define T_Or 280
#define T_Null 281
#define T_While 282
#define T_For 283
#define T_If 284
#define T_Else 285
#define T_Return 286
#define T_Break 287
#define T_Switch 288
#define T_Case 289
#define T_Default 290
#define T_Increment 291
#define T_Decrement 292
#define UMINUS 293
#define T_Identifier 294
#define T_StringConstant 295
#define T_IntConstant 296
#define T_DoubleConstant 297
#define T_BoolConstant 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 41 "parser.y"

		int integerConstant;
		bool boolConstant;
		char *stringConstant;
		double doubleConstant;
		char identifier[MaxIdentLen+1]; // +1 for terminating null
 
		// Decl
		Decl *decl;
		List<Decl*> *declList;
		Type* type;

		List<VarDecl*>*   funParaList;
		List<Decl*>*      classField;
		List<Decl*>*      interfaceField;
		List<NamedType*>* classImpList; 
		VarDecl*          varDecl;
		FnDecl*           funDecl;
		ClassDecl*        classDecl;
		InterfaceDecl*    interfaceDecl;
		NamedType*        namedType;

		// Exp  &  Statement 
		Expr*			expr;
		List<Expr*>*	exprList;
		Stmt*			statement;
		StmtBlock*		stmtBlockInner;
		StmtBlock*		stmtBlock;
		IfStmt*			ifStmt;
		WhileStmt*		whileStmt;
		ForStmt*		forStmt;
		BreakStmt*		breakStmt;
		ReturnStmt*		returnStmt;
		PrintStmt*		printStmt;


		LValue*			 lValue;
		List<Expr*>*	 actualPara;
		Call*			 call;
		Expr*            constant;



/* Line 214 of yacc.c  */
#line 256 "y.tab.c"
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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 281 "y.tab.c"

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
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   963

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNRULES -- Number of states.  */
#define YYNSTATES  215

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,     2,    51,     2,     2,
      56,    57,    49,    47,    55,    48,    53,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    54,
      46,    44,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    38,    41,
      45,    47,    48,    55,    62,    65,    67,    68,    74,    78,
      81,    84,    86,    87,    91,    93,   103,   111,   119,   125,
     129,   131,   134,   136,   138,   140,   142,   144,   146,   148,
     150,   154,   157,   160,   162,   166,   169,   175,   183,   189,
     199,   208,   217,   225,   228,   232,   235,   241,   245,   247,
     249,   251,   253,   257,   261,   265,   269,   273,   277,   280,
     283,   287,   291,   295,   299,   303,   307,   311,   315,   318,
     322,   326,   329,   336,   338,   342,   347,   352,   359,   363,
     365,   366,   368,   370,   372,   374
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      63,     0,    -1,    64,    -1,    64,    65,    -1,    65,    -1,
      67,    54,    -1,    69,    -1,    72,    -1,    75,    -1,     5,
      -1,     6,    -1,     4,    -1,     3,    -1,    26,    -1,     7,
      -1,    18,    -1,    39,    -1,    66,    23,    -1,    66,    39,
      -1,    68,    55,    67,    -1,    67,    -1,    -1,    66,    39,
      56,    68,    57,    79,    -1,    66,    39,    56,    68,    57,
      54,    -1,    71,    70,    -1,    70,    -1,    -1,    10,    39,
      58,    71,    59,    -1,    73,    67,    54,    -1,    73,    69,
      -1,    67,    54,    -1,    69,    -1,    -1,    74,    55,    39,
      -1,    39,    -1,     8,    39,    12,    39,    11,    74,    58,
      73,    59,    -1,     8,    39,    11,    74,    58,    73,    59,
      -1,     8,    39,    12,    39,    58,    73,    59,    -1,     8,
      39,    58,    73,    59,    -1,    76,    55,    86,    -1,    86,
      -1,    86,    54,    -1,    54,    -1,    80,    -1,    81,    -1,
      82,    -1,    83,    -1,    84,    -1,    85,    -1,    79,    -1,
      78,    67,    54,    -1,    78,    77,    -1,    67,    54,    -1,
      77,    -1,    58,    78,    59,    -1,    58,    59,    -1,    29,
      56,    86,    57,    77,    -1,    29,    56,    86,    57,    77,
      30,    77,    -1,    27,    56,    86,    57,    77,    -1,    28,
      56,    86,    54,    86,    54,    86,    57,    77,    -1,    28,
      56,    54,    86,    54,    86,    57,    77,    -1,    28,    56,
      86,    54,    86,    54,    57,    77,    -1,    28,    56,    54,
      86,    54,    57,    77,    -1,    32,    54,    -1,    31,    86,
      54,    -1,    31,    54,    -1,    15,    56,    76,    57,    54,
      -1,    87,    44,    86,    -1,    90,    -1,    87,    -1,     9,
      -1,    88,    -1,    56,    86,    57,    -1,    86,    47,    86,
      -1,    86,    48,    86,    -1,    86,    49,    86,    -1,    86,
      50,    86,    -1,    86,    51,    86,    -1,    48,    86,    -1,
      47,    86,    -1,    86,    19,    86,    -1,    86,    46,    86,
      -1,    86,    45,    86,    -1,    86,    20,    86,    -1,    86,
      21,    86,    -1,    86,    22,    86,    -1,    86,    24,    86,
      -1,    86,    25,    86,    -1,    52,    86,    -1,    16,    56,
      57,    -1,    17,    56,    57,    -1,    13,    39,    -1,    14,
      56,    86,    55,    66,    57,    -1,    39,    -1,    86,    53,
      39,    -1,    86,    60,    86,    61,    -1,    39,    56,    89,
      57,    -1,    86,    53,    39,    56,    89,    57,    -1,    89,
      55,    86,    -1,    86,    -1,    -1,    40,    -1,    41,    -1,
      42,    -1,    43,    -1,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   184,   184,   205,   206,   210,   211,   212,   213,   217,
     218,   219,   220,   221,   222,   223,   224,   228,   233,   240,
     241,   242,   245,   253,   260,   261,   262,   265,   272,   273,
     274,   275,   276,   280,   285,   293,   300,   306,   314,   321,
     322,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     336,   337,   338,   344,   352,   355,   362,   363,   367,   371,
     372,   376,   380,   387,   390,   391,   397,   403,   407,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   435,   441,   445,   449,   458,   465,   474,   475,
     476,   479,   480,   481,   482,   483
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_This", "T_Interface", "T_Implements",
  "T_Extends", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Error", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_While", "T_For",
  "T_If", "T_Else", "T_Return", "T_Break", "T_Switch", "T_Case",
  "T_Default", "T_Increment", "T_Decrement", "UMINUS", "T_Identifier",
  "T_StringConstant", "T_IntConstant", "T_DoubleConstant",
  "T_BoolConstant", "'='", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'!'", "'.'", "';'", "','", "'('", "')'", "'{'", "'}'", "'['", "']'",
  "$accept", "Program", "DeclList", "Decl", "Type", "VarDecl",
  "FunParaList", "FunDecl", "FunPrototype", "InterfaceField",
  "InterfaceDecl", "ClassField", "ClassImpleList", "ClassDecl", "ExprList",
  "Statement", "StmtBlockInner", "StmtBlock", "IfStmt", "WhileStmt",
  "ForStmt", "BreakStmt", "ReturnStmt", "PrintStmt", "Expr", "LValue",
  "Call", "Actuals", "Constant", 0
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
     295,   296,   297,   298,    61,    62,    60,    43,    45,    42,
      47,    37,    33,    46,    59,    44,    40,    41,   123,   125,
      91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    68,
      68,    68,    69,    70,    71,    71,    71,    72,    73,    73,
      73,    73,    73,    74,    74,    75,    75,    75,    75,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    82,
      82,    82,    82,    83,    84,    84,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    87,    88,    88,    89,    89,
      89,    90,    90,    90,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
       1,     0,     6,     6,     2,     1,     0,     5,     3,     2,
       2,     1,     0,     3,     1,     9,     7,     7,     5,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     1,     3,     2,     5,     7,     5,     9,
       8,     8,     7,     2,     3,     2,     5,     3,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     2,     6,     1,     3,     4,     4,     6,     3,     1,
       0,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    11,     9,    10,    14,     0,     0,    15,    13,
      16,     0,     2,     4,     0,     0,     6,     7,     8,     0,
       0,     1,     3,    17,    18,     5,     0,     0,    32,    26,
      21,    34,     0,     0,     0,    31,     0,     0,    25,     0,
       0,    20,     0,     0,    32,     0,    32,    30,    38,     0,
      29,     0,    27,    24,    18,     0,     0,    33,     0,     0,
       0,    28,    21,    19,     0,    22,    36,    32,    37,     0,
      70,     0,     0,     0,     0,     0,   105,     0,     0,     0,
       0,     0,    93,   101,   102,   103,   104,     0,     0,     0,
      42,     0,    55,     0,    53,     0,    49,    43,    44,    45,
      46,    47,    48,     0,    69,    71,    68,     0,     0,    91,
       0,     0,     0,     0,     0,     0,     0,   105,    93,    65,
       0,    63,   100,    79,    78,    88,     0,    52,    54,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,    35,    23,
       0,     0,    40,    89,    90,     0,     0,     0,     0,    64,
      99,     0,    72,    50,    80,    83,    84,    85,    86,    87,
      82,    81,    73,    74,    75,    76,    77,    94,     0,    67,
       0,     0,     0,     0,     0,     0,     0,     0,    96,   100,
      95,     0,    39,    66,    58,     0,     0,    56,    98,     0,
      92,     0,     0,     0,     0,    97,    62,     0,     0,     0,
      57,    60,    61,     0,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    34,    42,    35,    38,    39,
      17,    36,    32,    18,   151,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   161,   106
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int16 yypact[] =
{
     924,   -94,   -94,   -94,   -94,   -94,   -21,    -8,   -94,   -94,
     -94,    37,   924,   -94,   -18,   -20,   -94,   -94,   -94,    -5,
      -4,   -94,   -94,   -94,   -15,   -94,     9,    10,   340,   340,
     340,   -94,   -38,    -3,    11,   -94,   150,   -10,   -94,   231,
      -9,   -94,   -13,    25,   340,     9,   340,   -94,   -94,    26,
     -94,    28,   -94,   -94,   -94,   340,    23,   -94,   270,   -36,
     275,   -94,   340,   -94,   156,   -94,   -94,   340,   -94,     2,
     -94,    49,    38,    39,    40,    41,    17,    48,    53,    57,
     411,    64,   -11,   -94,   -94,   -94,   -94,   473,   473,   473,
     -94,   473,   -94,    65,   -94,   213,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   528,    80,   -94,   -94,   280,    72,   -94,
     473,   473,    70,    71,   473,   429,   473,   -94,    73,   -94,
     544,   -94,   473,   -17,   -17,   -17,   581,   -94,   -94,    76,
     -94,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   103,   -94,   473,   473,   -94,   -94,
     597,     5,   814,   -94,   -94,   634,   473,   650,   687,   -94,
     814,    30,   -94,   -94,    52,   873,    87,    87,   865,   849,
     873,    52,   141,   141,   -17,   -17,   -17,    89,   485,   814,
     340,   473,    95,   309,   703,   473,   309,   473,   -94,   473,
     -94,   -19,   814,   -94,   -94,   355,   740,   113,   814,    34,
     -94,   309,   756,   374,   309,   -94,   -94,   309,   309,   798,
     -94,   -94,   -94,   309,   -94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   -94,   140,   -29,    86,    96,     3,   125,   -94,
     -94,   -35,   121,   -94,   -94,   -93,   -94,   111,   -94,   -94,
     -94,   -94,   -94,   -94,   -64,   -94,   -94,   -14,   -94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -17
static const yytype_int16 yytable[] =
{
      37,    40,   130,    16,    23,    23,    26,    27,    45,    58,
      37,    60,   -16,    23,    23,    16,   120,    43,    19,    43,
      44,    24,    67,   123,   124,   125,    40,   126,   -16,    51,
      54,    20,   107,    40,    25,    40,   144,    21,   200,    50,
     -13,    30,    55,   146,    56,   122,   150,   152,    31,    33,
     155,   157,   158,    28,    29,    46,   -13,    55,   160,   108,
     181,    50,   182,    50,    57,    47,    40,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
      61,    64,   178,   179,    62,   187,    15,   188,   109,   187,
     194,   205,   184,   197,   110,   111,   112,   113,    15,   139,
     140,   141,   142,   143,   114,   144,   131,   132,   206,   115,
      50,   210,   146,   116,   211,   212,    41,   192,   121,   127,
     214,   196,    49,   198,   147,   160,   149,   153,   154,   122,
     163,   202,   137,   138,   139,   140,   141,   142,   143,   209,
     144,    63,   177,   204,    49,   189,    49,   146,    41,   193,
      93,   191,    22,     1,     2,     3,     4,     5,    69,     1,
       2,     3,     4,     5,    53,    70,    59,    65,     8,    71,
      72,    73,    74,    75,     8,   199,     9,     0,     0,     0,
       0,   129,    76,    77,    78,    79,     0,    80,    81,    10,
     141,   142,   143,    49,   144,    82,    83,    84,    85,    86,
       0,   146,     0,    87,    88,     0,     0,     0,    89,    48,
      90,     0,    91,     0,    64,    92,     1,     2,     3,     4,
       5,     0,    70,     0,     0,     0,    71,    72,    73,    74,
      75,     8,     0,     0,     1,     2,     3,     4,     5,    76,
      77,    78,    79,     0,    80,    81,     0,     0,     0,     8,
       0,     0,    82,    83,    84,    85,    86,     9,     0,     0,
      87,    88,     0,     0,     0,    89,     0,    90,     0,    91,
      10,    64,   128,     1,     2,     3,     4,     5,     1,     2,
       3,     4,     5,     1,     2,     3,     4,     5,     8,     0,
      52,     0,     0,     8,     0,     0,     9,     0,     8,     0,
       0,     9,     0,     0,     0,     0,     9,     0,     0,    10,
       0,     0,     0,     0,    10,     0,     0,     0,    70,    10,
       0,     0,    71,    72,    73,    74,    75,     0,     0,    66,
       0,     0,     0,     0,    68,   117,    77,    78,    79,   148,
      80,    81,     0,     1,     2,     3,     4,     5,   118,    83,
      84,    85,    86,     0,     0,     0,    87,    88,     8,     0,
       0,    89,     0,    90,    70,    91,     9,    64,    71,    72,
       0,    74,    75,     0,     0,     0,     0,     0,     0,    10,
       0,   117,     0,    70,     0,     0,     0,    71,    72,     0,
      74,    75,     0,     0,   118,    83,    84,    85,    86,     0,
     117,     0,    87,    88,     0,     0,     0,    89,     0,     0,
       0,    91,   201,   118,    83,    84,    85,    86,     0,     0,
      70,    87,    88,     0,    71,    72,    89,    74,    75,     0,
      91,   208,     0,     0,     0,     0,     0,   117,    70,     0,
       0,     0,    71,    72,     0,    74,    75,     0,     0,     0,
     118,    83,    84,    85,    86,   117,     0,     0,    87,    88,
       0,     0,     0,    89,     0,   119,     0,    91,   118,    83,
      84,    85,    86,     0,     0,     0,    87,    88,     0,     0,
       0,    89,    70,   156,     0,    91,    71,    72,     0,    74,
      75,     0,     0,     0,     0,     0,     0,     0,     0,   117,
       0,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     136,     0,   118,    83,    84,    85,    86,     0,     0,     0,
      87,    88,     0,     0,     0,    89,     0,     0,     0,    91,
     137,   138,   139,   140,   141,   142,   143,     0,   144,     0,
       0,     0,     0,     0,     0,   146,   190,   131,   132,   133,
     134,     0,   135,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,   133,   134,     0,   135,   136,
       0,     0,     0,   137,   138,   139,   140,   141,   142,   143,
       0,   144,   145,     0,     0,     0,     0,     0,   146,   137,
     138,   139,   140,   141,   142,   143,     0,   144,   159,     0,
     131,   132,   133,   134,   146,   135,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,   133,   134,
       0,   135,   136,     0,     0,     0,   137,   138,   139,   140,
     141,   142,   143,     0,   144,     0,     0,     0,   162,     0,
       0,   146,   137,   138,   139,   140,   141,   142,   143,     0,
     144,     0,   180,   131,   132,   133,   134,   146,   135,   136,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,   133,   134,     0,   135,   136,     0,     0,     0,   137,
     138,   139,   140,   141,   142,   143,     0,   144,     0,     0,
       0,   183,     0,     0,   146,   137,   138,   139,   140,   141,
     142,   143,     0,   144,   185,     0,   131,   132,   133,   134,
     146,   135,   136,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,   133,   134,     0,   135,   136,     0,
       0,     0,   137,   138,   139,   140,   141,   142,   143,     0,
     144,     0,     0,     0,   186,     0,     0,   146,   137,   138,
     139,   140,   141,   142,   143,     0,   144,   195,     0,   131,
     132,   133,   134,   146,   135,   136,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,   133,   134,     0,
     135,   136,     0,     0,     0,   137,   138,   139,   140,   141,
     142,   143,     0,   144,   203,     0,     0,     0,     0,     0,
     146,   137,   138,   139,   140,   141,   142,   143,     0,   144,
       0,     0,     0,   207,     0,     0,   146,   131,   132,   133,
     134,     0,   135,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,   133,   134,     0,   135,   136,
       0,     0,     0,   137,   138,   139,   140,   141,   142,   143,
       0,   144,     0,     0,     0,   213,     0,     0,   146,   137,
     138,   139,   140,   141,   142,   143,     0,   144,   131,   132,
     133,   134,     0,   135,   146,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,   132,   133,   134,     0,     0,
       0,     0,   131,     0,   137,   138,   139,   140,   141,   142,
     143,     0,   144,     0,     0,     0,     0,     0,     0,   146,
     137,   138,   139,   140,   141,   142,   143,     0,   144,   138,
     139,   140,   141,   142,   143,   146,   144,     1,     2,     3,
       4,     5,     6,   146,     7,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    10
};

static const yytype_int16 yycheck[] =
{
      29,    30,    95,     0,    23,    23,    11,    12,    11,    44,
      39,    46,    23,    23,    23,    12,    80,    55,    39,    55,
      58,    39,    58,    87,    88,    89,    55,    91,    39,    39,
      39,    39,    67,    62,    54,    64,    53,     0,    57,    36,
      23,    56,    55,    60,    57,    56,   110,   111,    39,    39,
     114,   115,   116,    58,    58,    58,    39,    55,   122,    57,
      55,    58,    57,    60,    39,    54,    95,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
      54,    58,   146,   147,    56,    55,     0,    57,    39,    55,
     183,    57,   156,   186,    56,    56,    56,    56,    12,    47,
      48,    49,    50,    51,    56,    53,    19,    20,   201,    56,
     107,   204,    60,    56,   207,   208,    30,   181,    54,    54,
     213,   185,    36,   187,    44,   189,    54,    57,    57,    56,
      54,   195,    45,    46,    47,    48,    49,    50,    51,   203,
      53,    55,    39,    30,    58,    56,    60,    60,    62,    54,
      64,   180,    12,     3,     4,     5,     6,     7,    62,     3,
       4,     5,     6,     7,    39,     9,    45,    56,    18,    13,
      14,    15,    16,    17,    18,   189,    26,    -1,    -1,    -1,
      -1,    95,    26,    27,    28,    29,    -1,    31,    32,    39,
      49,    50,    51,   107,    53,    39,    40,    41,    42,    43,
      -1,    60,    -1,    47,    48,    -1,    -1,    -1,    52,    59,
      54,    -1,    56,    -1,    58,    59,     3,     4,     5,     6,
       7,    -1,     9,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    18,    -1,    -1,     3,     4,     5,     6,     7,    26,
      27,    28,    29,    -1,    31,    32,    -1,    -1,    -1,    18,
      -1,    -1,    39,    40,    41,    42,    43,    26,    -1,    -1,
      47,    48,    -1,    -1,    -1,    52,    -1,    54,    -1,    56,
      39,    58,    59,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,    18,    -1,
      59,    -1,    -1,    18,    -1,    -1,    26,    -1,    18,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    26,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,     9,    39,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    -1,    59,
      -1,    -1,    -1,    -1,    59,    26,    27,    28,    29,    59,
      31,    32,    -1,     3,     4,     5,     6,     7,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    48,    18,    -1,
      -1,    52,    -1,    54,     9,    56,    26,    58,    13,    14,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    26,    -1,     9,    -1,    -1,    -1,    13,    14,    -1,
      16,    17,    -1,    -1,    39,    40,    41,    42,    43,    -1,
      26,    -1,    47,    48,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    56,    57,    39,    40,    41,    42,    43,    -1,    -1,
       9,    47,    48,    -1,    13,    14,    52,    16,    17,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    26,     9,    -1,
      -1,    -1,    13,    14,    -1,    16,    17,    -1,    -1,    -1,
      39,    40,    41,    42,    43,    26,    -1,    -1,    47,    48,
      -1,    -1,    -1,    52,    -1,    54,    -1,    56,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    52,     9,    54,    -1,    56,    13,    14,    -1,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    -1,    24,
      25,    -1,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    52,    -1,    -1,    -1,    56,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    19,    20,    21,
      22,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    -1,    24,    25,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    -1,
      19,    20,    21,    22,    60,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      -1,    24,    25,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    -1,    -1,    -1,    57,    -1,
      -1,    60,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    55,    19,    20,    21,    22,    60,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    -1,    24,    25,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    -1,    -1,
      -1,    57,    -1,    -1,    60,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    -1,    19,    20,    21,    22,
      60,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    -1,    24,    25,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    -1,    -1,    57,    -1,    -1,    60,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    -1,    19,
      20,    21,    22,    60,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    -1,
      24,    25,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
      60,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      -1,    -1,    -1,    57,    -1,    -1,    60,    19,    20,    21,
      22,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    -1,    24,    25,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    -1,    -1,    -1,    57,    -1,    -1,    60,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    19,    20,
      21,    22,    -1,    24,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    19,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    46,
      47,    48,    49,    50,    51,    60,    53,     3,     4,     5,
       6,     7,     8,    60,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    18,    26,
      39,    63,    64,    65,    66,    67,    69,    72,    75,    39,
      39,     0,    65,    23,    39,    54,    11,    12,    58,    58,
      56,    39,    74,    39,    67,    69,    73,    66,    70,    71,
      66,    67,    68,    55,    58,    11,    58,    54,    59,    67,
      69,    39,    59,    70,    39,    55,    57,    39,    73,    74,
      73,    54,    56,    67,    58,    79,    59,    58,    59,    68,
       9,    13,    14,    15,    16,    17,    26,    27,    28,    29,
      31,    32,    39,    40,    41,    42,    43,    47,    48,    52,
      54,    56,    59,    67,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    90,    73,    57,    39,
      56,    56,    56,    56,    56,    56,    56,    26,    39,    54,
      86,    54,    56,    86,    86,    86,    86,    54,    59,    67,
      77,    19,    20,    21,    22,    24,    25,    45,    46,    47,
      48,    49,    50,    51,    53,    54,    60,    44,    59,    54,
      86,    76,    86,    57,    57,    86,    54,    86,    86,    54,
      86,    89,    57,    54,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    39,    86,    86,
      55,    55,    57,    57,    86,    54,    57,    55,    57,    56,
      61,    66,    86,    54,    77,    54,    86,    77,    86,    89,
      57,    57,    86,    54,    30,    57,    77,    57,    57,    86,
      77,    77,    77,    57,    77
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

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
       `yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
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
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    { 
                                      (yylsp[(1) - (1)]); 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
									   List<Decl*> *p = (yyvsp[(1) - (1)].declList);

                                      Program *program = new Program((yyvsp[(1) - (1)].declList));

									  program->Check();
									 
									  freopen("out.asm","w",stdout);
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
									  {
											program->Emit();
									  }
                                          
                                    }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    { ((yyval.declList)=(yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].decl)); }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].decl)); }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (2)].varDecl);}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].funDecl);}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].interfaceDecl);}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 213 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].classDecl);}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    { (yyval.type) = new Type("int");    (yyval.type)->location = & (yylsp[(1) - (1)]);}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 218 "parser.y"
    { (yyval.type) = new Type("double"); (yyval.type)->location = & (yylsp[(1) - (1)]);}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 219 "parser.y"
    { (yyval.type) = new Type("bool");   (yyval.type)->location = & (yylsp[(1) - (1)]);}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 220 "parser.y"
    { (yyval.type) = new Type("void");   (yyval.type)->location = & (yylsp[(1) - (1)]);}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    { (yyval.type) = new Type("null");   (yyval.type)->location = & (yylsp[(1) - (1)]);}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 222 "parser.y"
    { (yyval.type) = new Type("string"); (yyval.type)->location = & (yylsp[(1) - (1)]);}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 223 "parser.y"
    { (yyval.type) = new Type("error");  (yyval.type)->location = & (yylsp[(1) - (1)]);}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    {  
		                     Identifier* pidentif = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
		                     (yyval.type) = new NamedType(pidentif);
					      }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    {
		                      (yyval.type) = new ArrayType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].type));
		                  }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    {
										  Identifier* pidentif = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
										  (yyval.varDecl) = new VarDecl(pidentif, (yyvsp[(1) - (2)].type));
							    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 240 "parser.y"
    { ((yyval.funParaList) = (yyvsp[(1) - (3)].funParaList))->Append((yyvsp[(3) - (3)].varDecl)); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 241 "parser.y"
    { ((yyval.funParaList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 242 "parser.y"
    {  (yyval.funParaList) = new List<VarDecl*>;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    {
														           Identifier* pidentif = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
														           FnDecl* pfunDecl = new FnDecl(pidentif,(yyvsp[(1) - (6)].type),(yyvsp[(4) - (6)].funParaList));
																   pfunDecl->SetFunctionBody((yyvsp[(6) - (6)].stmtBlock));
																   (yyval.funDecl) = pfunDecl;
													            }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    {
														           Identifier* pidentif = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
														           (yyval.funDecl) = new FnDecl(pidentif,(yyvsp[(1) - (6)].type),(yyvsp[(4) - (6)].funParaList));
													            }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 260 "parser.y"
    { ((yyval.interfaceField)=(yyvsp[(1) - (2)].interfaceField))->Append((yyvsp[(2) - (2)].funDecl));}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 261 "parser.y"
    { ((yyval.interfaceField)=new List<Decl*>)->Append((yyvsp[(1) - (1)].funDecl));}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 262 "parser.y"
    {  (yyval.interfaceField)=new List<Decl*>;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 265 "parser.y"
    {
																     Identifier* pident = new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier));  
																     (yyval.interfaceDecl) = new InterfaceDecl(pident, (yyvsp[(4) - (5)].interfaceField));
															       }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 272 "parser.y"
    {((yyval.classField) = ((yyvsp[(1) - (3)].classField)))->Append((yyvsp[(2) - (3)].varDecl));}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    {((yyval.classField) = ((yyvsp[(1) - (2)].classField)))->Append((yyvsp[(2) - (2)].funDecl));}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 274 "parser.y"
    {((yyval.classField) = new List<Decl*>)->Append((yyvsp[(1) - (2)].varDecl));}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 275 "parser.y"
    {((yyval.classField) = new List<Decl*>)->Append((yyvsp[(1) - (1)].funDecl));}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 276 "parser.y"
    { (yyval.classField) = new List<Decl*>;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 280 "parser.y"
    {   
                                                     Identifier * pident = new Identifier((yylsp[(3) - (3)]),(yyvsp[(3) - (3)].identifier));
                                                     NamedType* pNamedType = new NamedType(pident);
                                                     ((yyval.classImpList) = (yyvsp[(1) - (3)].classImpList))->Append(pNamedType);
												  }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 285 "parser.y"
    { 
			                                         Identifier * pident   = new Identifier((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].identifier));
													 NamedType* pNamedType = new NamedType(pident);
			                                         ((yyval.classImpList) = new List<NamedType*>)->Append(pNamedType);
												   }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 294 "parser.y"
    {
                                                              Identifier * pident     = new Identifier((yylsp[(2) - (9)]),(yyvsp[(2) - (9)].identifier));
															  Identifier * pextend    = new Identifier((yylsp[(4) - (9)]),(yyvsp[(4) - (9)].identifier));
															  NamedType *  pNamedType = new NamedType(pextend);
                                                              (yyval.classDecl) = new ClassDecl(pident,pNamedType,(yyvsp[(6) - (9)].classImpList),(yyvsp[(8) - (9)].classField));
														   }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {
                                                              Identifier * pident = new Identifier((yylsp[(2) - (7)]),(yyvsp[(2) - (7)].identifier));
                                                              (yyval.classDecl) = new ClassDecl(pident,NULL,(yyvsp[(4) - (7)].classImpList),(yyvsp[(6) - (7)].classField));
														   }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 307 "parser.y"
    {
														     Identifier * pident     = new Identifier((yylsp[(2) - (7)]),(yyvsp[(2) - (7)].identifier));
															 Identifier * pextend    = new Identifier((yylsp[(4) - (7)]),(yyvsp[(4) - (7)].identifier));
															 NamedType *  pNamedType = new NamedType(pextend);															 
															 (yyval.classDecl) = new ClassDecl(pident,pNamedType,new List<NamedType*>,(yyvsp[(6) - (7)].classField));
														   }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    {
															 Identifier * pident = new Identifier((yylsp[(2) - (5)]),(yyvsp[(2) - (5)].identifier));
															 (yyval.classDecl) = new ClassDecl(pident,NULL,new List<NamedType*>,(yyvsp[(4) - (5)].classField));
														   }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 321 "parser.y"
    { ((yyval.exprList) = (yyvsp[(1) - (3)].exprList))->Append((yyvsp[(3) - (3)].expr));}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 322 "parser.y"
    { ((yyval.exprList) = new List<Expr*>)->Append((yyvsp[(1) - (1)].expr));}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (2)].expr) ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 326 "parser.y"
    { (yyval.statement) = new EmptyExpr;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 327 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].ifStmt);}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 328 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].whileStmt);}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].forStmt);}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 330 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].breakStmt);}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].returnStmt);}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].printStmt);}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].stmtBlock);}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    {(((yyval.stmtBlockInner) = (yyvsp[(1) - (3)].stmtBlockInner))->decls)->Append((yyvsp[(2) - (3)].varDecl));}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 337 "parser.y"
    {(((yyval.stmtBlockInner) = (yyvsp[(1) - (2)].stmtBlockInner))->stmts)->Append((yyvsp[(2) - (2)].statement));}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 338 "parser.y"
    {
												 List<VarDecl*> *variableDeclarations = new List<VarDecl*> ;
												 variableDeclarations->Append((yyvsp[(1) - (2)].varDecl));										
												 List<Stmt*> *statements = new List<Stmt*>;
												 (yyval.stmtBlockInner) = new StmtBlock(variableDeclarations,statements);
										     }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 344 "parser.y"
    { 
												 List<VarDecl*> *variableDeclarations = new List<VarDecl*> ;									
												 List<Stmt*> *statements = new List<Stmt*>;
												 statements->Append((yyvsp[(1) - (1)].statement));
												 (yyval.stmtBlockInner) = new StmtBlock(variableDeclarations,statements);
											 }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 352 "parser.y"
    {    
												((yyval.stmtBlock) = (yyvsp[(2) - (3)].stmtBlockInner))->SetAllMembersParent() ;
										   }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 355 "parser.y"
    {
			                                  List<VarDecl*> *variableDeclarations = new List<VarDecl*> ;									
											  List<Stmt*> *statements = new List<Stmt*>;
											  (yyval.stmtBlock) = new StmtBlock(variableDeclarations,statements);
			                               }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 362 "parser.y"
    { (yyval.ifStmt) = new IfStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].statement), NULL);}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 363 "parser.y"
    { (yyval.ifStmt) = new IfStmt((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement));}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 367 "parser.y"
    { (yyval.whileStmt) = new  WhileStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].statement)) ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    { (yyval.forStmt)= new ForStmt((yyvsp[(3) - (9)].expr), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), (yyvsp[(9) - (9)].statement));}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 372 "parser.y"
    { 
		                                                           EmptyExpr* pempty = new EmptyExpr;
		                                                           (yyval.forStmt)= new ForStmt(pempty, (yyvsp[(4) - (8)].expr), (yyvsp[(6) - (8)].expr), (yyvsp[(8) - (8)].statement));
															     }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 376 "parser.y"
    { 
		                                                           EmptyExpr* pempty = new EmptyExpr;
		                                                           (yyval.forStmt)= new ForStmt((yyvsp[(3) - (8)].expr), (yyvsp[(5) - (8)].expr), pempty, (yyvsp[(8) - (8)].statement));
															     }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    { 
		                                                           EmptyExpr* pempty = new EmptyExpr;
		                                                           (yyval.forStmt)= new ForStmt(pempty, (yyvsp[(4) - (7)].expr), pempty, (yyvsp[(7) - (7)].statement));
															     }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    { (yyval.breakStmt) = new BreakStmt((yylsp[(1) - (2)]));}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 390 "parser.y"
    { (yyval.returnStmt) = new ReturnStmt((yylsp[(1) - (3)]), (yyvsp[(2) - (3)].expr));}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 391 "parser.y"
    {
		                          EmptyExpr* pempty = new EmptyExpr;
								  (yyval.returnStmt) = new ReturnStmt((yylsp[(1) - (2)]), pempty);
		                       }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 397 "parser.y"
    { (yyval.printStmt) = new PrintStmt((yyvsp[(3) - (5)].exprList));}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 403 "parser.y"
    { 
                                                  Operator *op = new Operator((yylsp[(2) - (3)]), "=");
                                                  (yyval.expr) = new AssignExpr((yyvsp[(1) - (3)].lValue), op, (yyvsp[(3) - (3)].expr));
										     }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 407 "parser.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].expr);}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 408 "parser.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].lValue);}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 409 "parser.y"
    {(yyval.expr) = new This((yylsp[(1) - (1)]));}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 410 "parser.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].call);}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 411 "parser.y"
    {(yyval.expr) = (yyvsp[(2) - (3)].expr);}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 412 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"+"), (yyvsp[(3) - (3)].expr));}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 413 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"-"), (yyvsp[(3) - (3)].expr));}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 414 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"*"), (yyvsp[(3) - (3)].expr));}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 415 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"/"), (yyvsp[(3) - (3)].expr));}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 416 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"%"), (yyvsp[(3) - (3)].expr));}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {(yyval.expr) = new ArithmeticExpr(new Operator((yylsp[(1) - (2)]),"-"), (yyvsp[(2) - (2)].expr));}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 418 "parser.y"
    {(yyval.expr) = new ArithmeticExpr(new Operator((yylsp[(1) - (2)]),"+"), (yyvsp[(2) - (2)].expr));}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 419 "parser.y"
    {(yyval.expr)  = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"<="), (yyvsp[(3) - (3)].expr));}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
    {(yyval.expr)  = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"<"), (yyvsp[(3) - (3)].expr));}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 421 "parser.y"
    {(yyval.expr)  = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),">"), (yyvsp[(3) - (3)].expr));}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 422 "parser.y"
    {(yyval.expr)  = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),">="), (yyvsp[(3) - (3)].expr));}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    {(yyval.expr)  = new EqualityExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"=="), (yyvsp[(3) - (3)].expr));}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 424 "parser.y"
    {(yyval.expr)  = new EqualityExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"!="), (yyvsp[(3) - (3)].expr));}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 425 "parser.y"
    {(yyval.expr) =  new LogicalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"&&"), (yyvsp[(3) - (3)].expr));}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 426 "parser.y"
    {(yyval.expr) =  new LogicalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]),"||"), (yyvsp[(3) - (3)].expr));}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 427 "parser.y"
    {(yyval.expr) =  new LogicalExpr( new Operator((yylsp[(1) - (2)]),"!"), (yyvsp[(2) - (2)].expr));}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 428 "parser.y"
    {(yyval.expr) = new ReadIntegerExpr((yylsp[(1) - (3)]));}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 429 "parser.y"
    {(yyval.expr) = new ReadLineExpr((yylsp[(1) - (3)]));}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 430 "parser.y"
    {
													Identifier *i = new Identifier((yylsp[(2) - (2)]),(yyvsp[(2) - (2)].identifier));
													NamedType *clsType = new  NamedType(i);
													(yyval.expr) = new NewExpr((yylsp[(1) - (2)]), clsType);
												 }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 435 "parser.y"
    {
												    (yyval.expr)= new NewArrayExpr((yylsp[(1) - (6)]),(yyvsp[(3) - (6)].expr), (yyvsp[(5) - (6)].type));
		                                         }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 441 "parser.y"
    { 
		                                                 Identifier *field = new Identifier((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].identifier));
		                                                 (yyval.lValue) = new FieldAccess(NULL, field);
													 }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 445 "parser.y"
    { 
		                                                 Identifier *field = new Identifier((yylsp[(3) - (3)]),(yyvsp[(3) - (3)].identifier));
		                                                 (yyval.lValue) = new FieldAccess((yyvsp[(1) - (3)].expr), field);
													 }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 449 "parser.y"
    {   
		                                                 yyltype loc = (yylsp[(1) - (4)]); 
                                                         loc.last_line   = ((yylsp[(4) - (4)])).last_line;
														 loc.last_column = ((yylsp[(4) - (4)])).last_column;
														 (yyval.lValue) = new  ArrayAccess( loc, (yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr));
			                                         }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    {    
                                                          yyltype loc = (yylsp[(1) - (4)]); 
                                                          loc.last_line   = ((yylsp[(4) - (4)])).last_line;
														  loc.last_column = ((yylsp[(4) - (4)])).last_column;
														  Identifier *field =  new Identifier((yylsp[(1) - (4)]),(yyvsp[(1) - (4)].identifier));
                                                          (yyval.call) = new Call(loc, NULL, field, (yyvsp[(3) - (4)].actualPara));
												     }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 465 "parser.y"
    {    
                                                          yyltype loc = (yylsp[(3) - (6)]); 
                                                          loc.last_line   = ((yylsp[(6) - (6)])).last_line;
														  loc.last_column = ((yylsp[(6) - (6)])).last_column;
														  Identifier *field =  new Identifier((yylsp[(3) - (6)]),(yyvsp[(3) - (6)].identifier));
                                                          (yyval.call) = new Call(loc, (yyvsp[(1) - (6)].expr), field, (yyvsp[(5) - (6)].actualPara));
												     }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 474 "parser.y"
    { ((yyval.actualPara) = (yyvsp[(1) - (3)].actualPara))->Append((yyvsp[(3) - (3)].expr)) ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    { ((yyval.actualPara) = new List<Expr*>)->Append((yyvsp[(1) - (1)].expr));}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 476 "parser.y"
    {  (yyval.actualPara) = new List<Expr*>; }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 479 "parser.y"
    {(yyval.expr) =  new StringConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].stringConstant));}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 480 "parser.y"
    {(yyval.expr) =  new IntConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].integerConstant));}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 481 "parser.y"
    {(yyval.expr) =  new DoubleConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].doubleConstant));}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 482 "parser.y"
    {(yyval.expr) =  new BoolConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].boolConstant));}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 483 "parser.y"
    {(yyval.expr) =  new NullConstant((yylsp[(1) - (1)]));}
    break;



/* Line 1455 of yacc.c  */
#line 2704 "y.tab.c"
      default: break;
    }
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

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
#line 486 "parser.y"

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}

