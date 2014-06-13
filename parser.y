/* File: parser.y
 * --------------
 * Bison input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

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

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
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
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Bison will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */

 

%token   T_Void T_Bool T_Int T_Double T_String 
%token   T_Class  T_This T_Interface T_Implements T_Extends

%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine T_Error

%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null 

%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_Switch T_Case T_Default

%token   T_Increment T_Decrement
%token   UMINUS

%token   <identifier>      T_Identifier
%token   <stringConstant>  T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant>  T_DoubleConstant
%token   <boolConstant>    T_BoolConstant


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <declList>       DeclList 
%type <decl>           Decl
%type <type>           Type



%type <varDecl>        VarDecl
%type <funParaList>    FunParaList
%type <funDecl>        FunDecl;
%type <funDecl>        FunPrototype
%type <classField>     ClassField
%type <interfaceField> InterfaceField
%type <classDecl>      ClassDecl
%type <classImpList>   ClassImpleList
%type <interfaceDecl>  InterfaceDecl




%type <expr>              Expr
%type <exprList>          ExprList
%type <statement>         Statement
%type <stmtBlockInner>    StmtBlockInner
%type <stmtBlock>         StmtBlock    
%type <ifStmt>            IfStmt
%type <whileStmt>         WhileStmt
%type <forStmt>           ForStmt   
%type <breakStmt>         BreakStmt
%type <returnStmt>        ReturnStmt
%type <printStmt>         PrintStmt


%type<expr>               Constant
%type<lValue>             LValue
%type<call>               Call
%type<actualPara>         Actuals



%right  '='
%left   T_Or
%left   T_And
%left   T_Equal  T_NotEqual
%left   '>' T_GreaterEqual
%left   '<' T_LessEqual 
%left   '+' '-'
%left   '*' '/' '%'
%right  T_New  T_NewArray
%right  '!'
%nonassoc   UMINUS
%left       '.'

%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program   :    DeclList            { 
                                      @1; 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
									   List<Decl*> *p = $1;

                                      Program *program = new Program($1);

									  program->Check();
									 
									  freopen("out.asm","w",stdout);
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
									  {
											program->Emit();
									  }
                                          
                                    }
          ;

DeclList  :    DeclList Decl        { ($$=$1)->Append($2); }
          |    Decl                 { ($$ = new List<Decl*>)->Append($1); }
          ;


Decl      :    VarDecl ';'      { $$ = $1;}
		  |    FunDecl          { $$ = $1;}
		  |    InterfaceDecl    { $$ = $1;}
		  |    ClassDecl        { $$ = $1;}
		  ;


Type    :    T_Int        { $$ = new Type("int");    $$->location = & @1;}
		|    T_Double     { $$ = new Type("double"); $$->location = & @1;}
		|    T_Bool       { $$ = new Type("bool");   $$->location = & @1;}
		|    T_Void       { $$ = new Type("void");   $$->location = & @1;}
		|    T_Null       { $$ = new Type("null");   $$->location = & @1;}
		|    T_String     { $$ = new Type("string"); $$->location = & @1;}
		|    T_Error      { $$ = new Type("error");  $$->location = & @1;}
		|    T_Identifier {  
		                     Identifier* pidentif = new Identifier(@1, $1);
		                     $$ = new NamedType(pidentif);
					      }
		|    Type T_Dims  {
		                      $$ = new ArrayType(@1, $1);
		                  }
        ;
//////Variable
VarDecl : Type T_Identifier     {
										  Identifier* pidentif = new Identifier(@2, $2);
										  $$ = new VarDecl(pidentif, $1);
							    }
		;

////////Function
FunParaList : FunParaList ',' VarDecl  { ($$ = $1)->Append($3); }
			| VarDecl                  { ($$ = new List<VarDecl*>)->Append($1); }
			|                          {  $$ = new List<VarDecl*>;}
			;

FunDecl     : Type T_Identifier '(' FunParaList ')' StmtBlock  {
														           Identifier* pidentif = new Identifier(@2, $2);
														           FnDecl* pfunDecl = new FnDecl(pidentif,$1,$4);
																   pfunDecl->SetFunctionBody($6);
																   $$ = pfunDecl;
													            }
		    ;

FunPrototype : Type T_Identifier '(' FunParaList ')' ';'       {
														           Identifier* pidentif = new Identifier(@2, $2);
														           $$ = new FnDecl(pidentif,$1,$4);
													            }
		    ;

//// INTERFACE
InterfaceField : InterfaceField FunPrototype  { ($$=$1)->Append($2);}
               | FunPrototype                 { ($$=new List<Decl*>)->Append($1);}
			   |                              {  $$=new List<Decl*>;}
			   ;

InterfaceDecl : T_Interface T_Identifier '{'InterfaceField '}'     {
																     Identifier* pident = new Identifier(@2, $2);  
																     $$ = new InterfaceDecl(pident, $4);
															       }
              ;

////CLASS
ClassField  : ClassField VarDecl ';' {($$ = ($1))->Append($2);}
            | ClassField FunDecl     {($$ = ($1))->Append($2);}
			| VarDecl ';'            {($$ = new List<Decl*>)->Append($1);}
			| FunDecl                {($$ = new List<Decl*>)->Append($1);}
			|                        { $$ = new List<Decl*>;}
			;


ClassImpleList : ClassImpleList ',' T_Identifier  {   
                                                     Identifier * pident = new Identifier(@3,$3);
                                                     NamedType* pNamedType = new NamedType(pident);
                                                     ($$ = $1)->Append(pNamedType);
												  }
               | T_Identifier                     { 
			                                         Identifier * pident   = new Identifier(@1,$1);
													 NamedType* pNamedType = new NamedType(pident);
			                                         ($$ = new List<NamedType*>)->Append(pNamedType);
												   }
			   ;
 
			    
ClassDecl   : T_Class T_Identifier T_Extends T_Identifier T_Implements ClassImpleList '{' ClassField '}'  
                                                           {
                                                              Identifier * pident     = new Identifier(@2,$2);
															  Identifier * pextend    = new Identifier(@4,$4);
															  NamedType *  pNamedType = new NamedType(pextend);
                                                              $$ = new ClassDecl(pident,pNamedType,$6,$8);
														   }
		    | T_Class T_Identifier T_Implements ClassImpleList '{' ClassField '}' 
                                                           {
                                                              Identifier * pident = new Identifier(@2,$2);
                                                              $$ = new ClassDecl(pident,NULL,$4,$6);
														   }

			| T_Class T_Identifier T_Extends T_Identifier '{' ClassField '}'
			                                               {
														     Identifier * pident     = new Identifier(@2,$2);
															 Identifier * pextend    = new Identifier(@4,$4);
															 NamedType *  pNamedType = new NamedType(pextend);															 
															 $$ = new ClassDecl(pident,pNamedType,new List<NamedType*>,$6);
														   }

			| T_Class T_Identifier '{' ClassField '}'      {
															 Identifier * pident = new Identifier(@2,$2);
															 $$ = new ClassDecl(pident,NULL,new List<NamedType*>,$4);
														   }
            ;
////////////////////////////////////////////////////////////////////////////////////////

ExprList   : ExprList ',' Expr { ($$ = $1)->Append($3);}
           | Expr              { ($$ = new List<Expr*>)->Append($1);}
           ;

Statement  : Expr ';'       { $$ = $1 ;}
           | ';'            { $$ = new EmptyExpr;}
		   | IfStmt         { $$ = $1;} 
		   | WhileStmt      { $$ = $1;} 
		   | ForStmt	    { $$ = $1;} 
		   | BreakStmt	    { $$ = $1;} 
		   | ReturnStmt	    { $$ = $1;} 
		   | PrintStmt	    { $$ = $1;} 
		   | StmtBlock 	    { $$ = $1;} 
		   ;

StmtBlockInner : StmtBlockInner VarDecl ';'  {(($$ = $1)->decls)->Append($2);}
               | StmtBlockInner Statement    {(($$ = $1)->stmts)->Append($2);}
			   | VarDecl ';'                 {
												 List<VarDecl*> *variableDeclarations = new List<VarDecl*> ;
												 variableDeclarations->Append($1);										
												 List<Stmt*> *statements = new List<Stmt*>;
												 $$ = new StmtBlock(variableDeclarations,statements);
										     }
			   | Statement                   { 
												 List<VarDecl*> *variableDeclarations = new List<VarDecl*> ;									
												 List<Stmt*> *statements = new List<Stmt*>;
												 statements->Append($1);
												 $$ = new StmtBlock(variableDeclarations,statements);
											 }
			   ;

StmtBlock      : '{' StmtBlockInner '}'    {    
												($$ = $2)->SetAllMembersParent() ;
										   }
               | '{' '}'                   {
			                                  List<VarDecl*> *variableDeclarations = new List<VarDecl*> ;									
											  List<Stmt*> *statements = new List<Stmt*>;
											  $$ = new StmtBlock(variableDeclarations,statements);
			                               }
               ;

IfStmt    : T_If '(' Expr ')' Statement                    { $$ = new IfStmt($3, $5, NULL);}
          | T_If '(' Expr ')' Statement T_Else Statement   { $$ = new IfStmt($3, $5, $7);}
		  ;


WhileStmt :   T_While '(' Expr ')' Statement           { $$ = new  WhileStmt($3, $5) ;}
          ;


ForStmt   : T_For '('  Expr  ';'  Expr  ';'  Expr  ')' Statement { $$= new ForStmt($3, $5, $7, $9);}
          | T_For '('   ';'  Expr  ';'  Expr  ')' Statement      { 
		                                                           EmptyExpr* pempty = new EmptyExpr;
		                                                           $$= new ForStmt(pempty, $4, $6, $8);
															     }
          | T_For '('  Expr  ';' Expr   ';'  ')' Statement       { 
		                                                           EmptyExpr* pempty = new EmptyExpr;
		                                                           $$= new ForStmt($3, $5, pempty, $8);
															     }
          | T_For '('   ';'  Expr ';'  ')' Statement             { 
		                                                           EmptyExpr* pempty = new EmptyExpr;
		                                                           $$= new ForStmt(pempty, $4, pempty, $7);
															     }
		  ;

 
BreakStmt  : T_Break ';' { $$ = new BreakStmt(@1);}
           ;

ReturnStmt : T_Return Expr ';' { $$ = new ReturnStmt(@1, $2);}
           | T_Return ';'      {
		                          EmptyExpr* pempty = new EmptyExpr;
								  $$ = new ReturnStmt(@1, pempty);
		                       }
           ;

PrintStmt  : T_Print '(' ExprList ')' ';' { $$ = new PrintStmt($3);}



/////////////////////////////////// Express

Expr       :  LValue '=' Expr                { 
                                                  Operator *op = new Operator(@2, "=");
                                                  $$ = new AssignExpr($1, op, $3);
										     }
           |  Constant                       {$$ = $1;}
		   |  LValue                         {$$ = $1;}
		   |  T_This                         {$$ = new This(@1);}
		   |  Call                           {$$ = $1;}
		   |  '(' Expr ')'                   {$$ = $2;}
		   |  Expr '+' Expr			         {$$ = new ArithmeticExpr($1, new Operator(@2,"+"), $3);}
		   |  Expr '-' Expr			         {$$ = new ArithmeticExpr($1, new Operator(@2,"-"), $3);}
		   |  Expr '*' Expr			         {$$ = new ArithmeticExpr($1, new Operator(@2,"*"), $3);}
		   |  Expr '/' Expr			         {$$ = new ArithmeticExpr($1, new Operator(@2,"/"), $3);}
		   |  Expr '%' Expr			         {$$ = new ArithmeticExpr($1, new Operator(@2,"%"), $3);}
		   |       '-' Expr	 %prec UMINUS    {$$ = new ArithmeticExpr(new Operator(@1,"-"), $2);}
		   |       '+' Expr	 %prec UMINUS    {$$ = new ArithmeticExpr(new Operator(@1,"+"), $2);}
		   |  Expr T_LessEqual Expr			         {$$  = new RelationalExpr($1, new Operator(@2,"<="), $3);}
		   |  Expr '<' Expr			                 {$$  = new RelationalExpr($1, new Operator(@2,"<"), $3);}
		   |  Expr '>' Expr			                 {$$  = new RelationalExpr($1, new Operator(@2,">"), $3);}
		   |  Expr T_GreaterEqual Expr			     {$$  = new RelationalExpr($1, new Operator(@2,">="), $3);}
		   |  Expr T_Equal Expr			             {$$  = new EqualityExpr($1, new Operator(@2,"=="), $3);}
		   |  Expr T_NotEqual Expr                   {$$  = new EqualityExpr($1, new Operator(@2,"!="), $3);}
		   |  Expr T_And Expr			             {$$ =  new LogicalExpr($1, new Operator(@2,"&&"), $3);}
		   |  Expr T_Or Expr			             {$$ =  new LogicalExpr($1, new Operator(@2,"||"), $3);}
		   |        '!' Expr			             {$$ =  new LogicalExpr( new Operator(@1,"!"), $2);} 
		   |  T_ReadInteger '(' ')'				 {$$ = new ReadIntegerExpr(@1);}
		   |  T_ReadLine '(' ')'			     {$$ = new ReadLineExpr(@1);}
		   |  T_New T_Identifier                 {
													Identifier *i = new Identifier(@2,$2);
													NamedType *clsType = new  NamedType(i);
													$$ = new NewExpr(@1, clsType);
												 }
		   |  T_NewArray '(' Expr ',' Type ')'   {
												    $$= new NewArrayExpr(@1,$3, $5);
		                                         }
		   ;


LValue     :  T_Identifier                           { 
		                                                 Identifier *field = new Identifier(@1,$1);
		                                                 $$ = new FieldAccess(NULL, field);
													 }
           |  Expr '.' T_Identifier                  { 
		                                                 Identifier *field = new Identifier(@3,$3);
		                                                 $$ = new FieldAccess($1, field);
													 }
		   |  Expr '['  Expr  ']'                    {   
		                                                 yyltype loc = @1; 
                                                         loc.last_line   = (@4).last_line;
														 loc.last_column = (@4).last_column;
														 $$ = new  ArrayAccess( loc, $1, $3);
			                                         }		                                        
		   ;
		   

Call       : T_Identifier '(' Actuals ')'            {    
                                                          yyltype loc = @1; 
                                                          loc.last_line   = (@4).last_line;
														  loc.last_column = (@4).last_column;
														  Identifier *field =  new Identifier(@1,$1);
                                                          $$ = new Call(loc, NULL, field, $3);
												     }
           | Expr '.' T_Identifier '(' Actuals ')'   {    
                                                          yyltype loc = @3; 
                                                          loc.last_line   = (@6).last_line;
														  loc.last_column = (@6).last_column;
														  Identifier *field =  new Identifier(@3,$3);
                                                          $$ = new Call(loc, $1, field, $5);
												     }
		   ;

Actuals    : Actuals ',' Expr  { ($$ = $1)->Append($3) ;}
           | Expr              { ($$ = new List<Expr*>)->Append($1);}
		   |                   {  $$ = new List<Expr*>; }
		   ;

Constant   : T_StringConstant  {$$ =  new StringConstant(@1, $1);}
		   | T_IntConstant     {$$ =  new IntConstant(@1, $1);}
		   | T_DoubleConstant  {$$ =  new DoubleConstant(@1, $1);}
		   | T_BoolConstant    {$$ =  new BoolConstant(@1, $1);}
		   | T_Null            {$$ =  new NullConstant(@1);}
		   ;

%%
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
