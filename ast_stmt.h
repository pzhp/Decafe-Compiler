/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp3: You will need to extend the Stmt classes to implement
 * semantic analysis for rules pertaining to statements.
 */

#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"
#include "codegen.h"


class Decl;
class VarDecl;
class FnDecl;
class InterfaceDecl;
class ClassDecl;
class Expr;
  
class Program : public Node
{
private:
	List<Decl*> *decls;
    Scope* g_scope; 
	CodeGenerator* g_code_gene;

public:    
	Program(List<Decl*> *declList);
	void BuildScope();	
	void Check();
	void Emit();
};

class Stmt : public Node
{
  public:
	 Scope*   scope;
     Stmt();
     Stmt(yyltype loc);
	 
	 virtual void BuildScope(Scope* sp);
	 virtual void Check(){};

	 virtual void Emit(CodeGenerator* cg){ return ;}

	 int memsize;
	 int GetMemSize(){return memsize;}  // use for function
};

class StmtBlock : public Stmt 
{
  public:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
    
  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
	
	void SetAllMembersParent()
	{
		if(decls!=NULL) decls->SetParentAll(this);
		if(stmts!=NULL) stmts->SetParentAll(this);
	}

	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};


class ConditionalStmt : public Stmt
{
protected:
	Expr *test;
	Stmt *body;

public:
	ConditionalStmt(Expr *testExpr, Stmt *body);
};

class LoopStmt : public ConditionalStmt 
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) { LoopBeginLabel =NULL; LoopEndLabel = NULL;}

	char* LoopBeginLabel;
	char* LoopEndLabel;
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
	
	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

class WhileStmt : public LoopStmt 
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}

	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

class IfStmt : public ConditionalStmt 
{
  protected:	
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);


	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

class BreakStmt : public Stmt 
{
public:
	BreakStmt(yyltype loc) : Stmt(loc) {}

	LoopStmt* OutLooper; // assign in check()

	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

class ReturnStmt : public Stmt  
{
protected:
	Expr *expr;  //maybe EmptyExpr

public:
	ReturnStmt(yyltype loc, Expr *expr);
	
	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

class PrintStmt : public Stmt
{
protected:
	List<Expr*> *args;

public:
	PrintStmt(List<Expr*> *arguments);

	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

#endif
