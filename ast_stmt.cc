/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"



Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::BuildScope()
{
	g_scope = new Scope(NULL);

	for (int i=0,n=decls->NumElements();i<n;i++)
	{
		g_scope->AddToCurSymTable(decls->Nth(i)->id->name,decls->Nth(i));
		decls->Nth(i)->BuildScope(g_scope);
	}
}

void Program::Check()
{
	BuildScope();
	for (int i=0;i<decls->NumElements();i++)
		decls->Nth(i)->Check();
}

void Program::Emit()
{
	g_code_gene = new CodeGenerator;

	//just no need for using after define
	for (int i=0,n=decls->NumElements();i<n;i++)
	{
		if(VarDecl* pg = dynamic_cast<VarDecl*>(decls->Nth(i)))
			pg->Emit_GlobalVar(g_code_gene);
	}

	// interface
	for (int i=0,n=decls->NumElements();i<n;i++)
	{
		if(InterfaceDecl* pg = dynamic_cast<InterfaceDecl*>(decls->Nth(i)))
			pg->Emit(g_code_gene);
	}

	//class
	for (int i=0,n=decls->NumElements();i<n;i++)
	{
		if(ClassDecl* pg = dynamic_cast<ClassDecl*>(decls->Nth(i)))
			pg->Emit(g_code_gene);
	}

	//function
	for (int i=0,n=decls->NumElements();i<n;i++)
	{
		if(FnDecl* pg = dynamic_cast<FnDecl*>(decls->Nth(i)))
			pg->Emit(g_code_gene);
	}

	g_code_gene->DoFinalCodeGen();
	//g_code_gene->PrintAllInstrutions();
}

Stmt::Stmt( yyltype loc ) : Node(loc)
{
	scope = new Scope(NULL);
	memsize = 0;
}
Stmt::Stmt()
{
	scope = new Scope(NULL);
	memsize = 0;
}

void Stmt::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
}




StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}


void StmtBlock::BuildScope( Scope* sp )
{
	//Link
	if (sp!=scope) // when sp==scope, it included by function
		scope->SetParentScope(sp);  

	//decls
	for (int i=0,n=decls->NumElements(); i<n; i++)
	{
		VarDecl* pVar =decls->Nth(i); 
		scope->AddToCurSymTable(pVar->GetName(),pVar);
		pVar->BuildScope(scope);
	}

	//statements
	for (int i=0,n=stmts->NumElements();i<n;i++)
		stmts->Nth(i)->BuildScope(scope);
}

void StmtBlock::Check()
{
	for (int i=0; i<decls->NumElements(); i++)
		decls->Nth(i)->Check();

	for (int i=0; i<stmts->NumElements(); i++)
		stmts->Nth(i)->Check();
}

void StmtBlock::Emit( CodeGenerator* cg )
{
	int begin_offset = cg->GetLocalOffset();
	for (int i=0,n=decls->NumElements();i<n;i++)
		decls->Nth(i)->Emit(cg);

	for (int i=0,n=stmts->NumElements();i<n;i++)
		stmts->Nth(i)->Emit(cg);

	memsize = begin_offset - cg->GetLocalOffset();
}


ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
	Assert(i != NULL && t != NULL && s != NULL && b != NULL);
	(init=i)->SetParent(this);
	(step=s)->SetParent(this);
}

void ForStmt::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	init->BuildScope(scope);
	step->BuildScope(scope);
	test->BuildScope(scope);
	body->BuildScope(scope);
}

void ForStmt::Check()
{
	init->Check();
	step->Check();
	
	test->Check();
	if (!test->typeflag->IsEquivalentTo(Type::boolType))
	{
		ReportError::TestNotBoolean(test);
	}
	
	body->Check();
}

void ForStmt::Emit( CodeGenerator* cg )
{
	LoopBeginLabel = cg->NewLabel();
	LoopEndLabel = cg->NewLabel();

	init->Emit(cg);
	cg->GenLabel(LoopBeginLabel);
	Assert(test!=NULL);
	test->Emit(cg);
	cg->GenIfZ(test->memlocation,LoopEndLabel);
	body->Emit(cg);
	step->Emit(cg);
	cg->GenGoto(LoopBeginLabel);
	cg->GenLabel(LoopEndLabel);
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);

	test->BuildScope(scope);
	body->BuildScope(scope);
	if(elseBody!=NULL)
		elseBody->BuildScope(scope);
}

void IfStmt::Check()
{
	test->Check();
	if (!test->typeflag->IsEquivalentTo(Type::boolType))
	{
		ReportError::TestNotBoolean(test);
	}

	body->Check();

	if(elseBody!=NULL)
		elseBody->Check();
}

void IfStmt::Emit( CodeGenerator* cg )
{
	if(elseBody)
	{
		char* elseLabel = cg->NewLabel();
		char* endLabel  = cg->NewLabel();
		test->Emit(cg);
		cg->GenIfZ(test->memlocation,elseLabel);  //if
			body->Emit(cg);
			cg->GenGoto(endLabel);
		cg->GenLabel(elseLabel);  //else
			elseBody->Emit(cg);
		cg->GenLabel(endLabel);
	}else
	{
		char* endLabel = cg->NewLabel();
		test->Emit(cg);
		cg->GenIfZ(test->memlocation,endLabel);  //if
			body->Emit(cg);
		cg->GenLabel(endLabel);
	}
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
	Assert(e != NULL);
	(expr=e)->SetParent(this);
}

void ReturnStmt::Check()
{
	//check expr;
	expr->Check();

	//check "return" is in function
	Node* ptmp = this->parent;
	FnDecl* pFn ;
	while (ptmp != NULL)
	{
		if ((pFn = dynamic_cast<FnDecl*>(ptmp))!= NULL)
		{
			// check return type is compatible	
			if(!expr->typeflag) //no return
			{
				if(!pFn->returnType->IsEquivalentTo(Type::voidType))
					ReportError::ReturnMismatch(this,Type::voidType,pFn->returnType);
			}
			else
			{
				if (!expr->typeflag->IsCompatibleTo(pFn->returnType,scope))
					ReportError::ReturnMismatch(this,expr->typeflag,pFn->returnType);
			}
			return ;
		}
		ptmp = ptmp->GetParent();
	}
	
	ReportError::ReturnOutFunction(this);
}

void ReturnStmt::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	expr->BuildScope(scope);
}

void ReturnStmt::Emit( CodeGenerator* cg )
{
	if(expr)
	{
		expr->Emit(cg);
		cg->GenReturn(expr->memlocation);
	}
	else
		cg->GenReturn(NULL);
}


PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);		
	for (int i=0,n=args->NumElements(); i<n ;i++)
		args->Nth(i)->BuildScope(sp);
}

void PrintStmt::Check()
{
	for (int i=0,n=args->NumElements();i<n;i++)
	{
		Expr* pexp = args->Nth(i);
		pexp->Check();
		bool isstring = pexp->typeflag->IsEquivalentTo(Type::stringType);
		bool isint    = pexp->typeflag->IsEquivalentTo(Type::intType);
		bool isbool   = pexp->typeflag->IsEquivalentTo(Type::boolType);
		if (!isstring && !isint && !isbool)
			ReportError::PrintArgMismatch(pexp,i+1,pexp->typeflag);
	}
}

void PrintStmt::Emit( CodeGenerator* cg )
{
	Expr* expr =NULL;
	for (int i=0,n=args->NumElements();i<n;i++)
	{

		(expr=args->Nth(i))->Emit(cg);			
		if (expr->typeflag->IsEquivalentTo(Type::stringType))
		{
			cg->GenBuiltInCall(PrintString,expr->memlocation);
		}else if(expr->typeflag->IsEquivalentTo(Type::intType))
		{
			cg->GenBuiltInCall(PrintInt,expr->memlocation);
		}
		else
		{
			cg->GenBuiltInCall(PrintBool,expr->memlocation);
		}		
	}
}




void WhileStmt::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	test->BuildScope(scope);
	body->BuildScope(scope);
}

void WhileStmt::Check()
{
	test->Check();
	if (!test->typeflag->IsEquivalentTo(Type::boolType))
	{
		ReportError::TestNotBoolean(test);
	}
	body->Check();
}

void WhileStmt::Emit( CodeGenerator* cg )
{
	LoopBeginLabel = cg->NewLabel();
	LoopEndLabel = cg->NewLabel();

	cg->GenLabel(LoopBeginLabel);
	test->Emit(cg);
	cg->GenIfZ(test->memlocation,LoopEndLabel);
	body->Emit(cg);
	cg->GenGoto(LoopBeginLabel);
	cg->GenLabel(LoopEndLabel);
}

void BreakStmt::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
}

void BreakStmt::Check()
{
	//check "break" is in while OR for
	Node* ptmp = this->parent;
	while (ptmp != NULL)
	{
		if (OutLooper = dynamic_cast<LoopStmt*>(ptmp))
			return ;
		ptmp = ptmp->parent;
	}
	ReportError::BreakOutsideLoop(this);
}

void BreakStmt::Emit( CodeGenerator* cg )
{
	Assert(OutLooper!=NULL);
	cg->GenGoto(OutLooper->LoopEndLabel);
}
