
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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 182 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;

