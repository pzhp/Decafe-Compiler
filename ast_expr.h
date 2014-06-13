/* File: ast_expr.h
* ----------------
* The Expr class and its subclasses are used to represent
* expressions in the parse tree.  For each expression in the
* language (add, call, New, etc.) there is a corresponding
* node class for that construct. 
*
* pp3: You will need to extend the Expr classes to implement 
* semantic analysis for rules pertaining to expressions.
*/

#ifndef _H_ast_expr
#define _H_ast_expr

#include "ast.h"
#include "ast_stmt.h"
#include "list.h"
#include "ast_type.h"

class Expr : public Stmt 
{
public:
	Expr(yyltype loc) : Stmt(loc),typeflag(NULL) { 
		memlocation =NULL;
	}
	Expr() : Stmt() {
		memlocation = NULL;
		typeflag = NULL;
	}
	ClassDecl* GetCurMostNearClass();

	Type* typeflag;
	Location* memlocation;
};

/* This node type is used for those places where an expression is optional.
* We could use a NULL pointer, but then it adds a lot of checking for
* NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr
{
public:
};

class IntConstant : public Expr 
{
protected:
	int value;

public:
	IntConstant(yyltype loc, int val);
	void Check()
	{
		typeflag = Type::intType;
	}
	void Emit(CodeGenerator* cg)
	{
		memlocation = cg->GenLoadConstant(value);
	}
};

class DoubleConstant : public Expr 
{
protected:
	double value;

public:
	DoubleConstant(yyltype loc, double val);
	void Check()
	{
		typeflag = Type::doubleType;
	}
};

class BoolConstant : public Expr 
{
protected:
	bool value;

public:
	BoolConstant(yyltype loc, bool val);
	void Check()
	{
		typeflag = Type::boolType;
	}
	void Emit(CodeGenerator* cg)
	{
		memlocation = cg->GenLoadConstant(value);
	}
};

class StringConstant : public Expr 
{ 
protected:
	char *value;

public:
	StringConstant(yyltype loc, const char *val);
	void Check()
	{
		typeflag = Type::stringType;
	}

	void Emit(CodeGenerator* cg)
	{
		memlocation = cg->GenLoadConstant(value);
	}
};

class NullConstant: public Expr 
{
public: 
	NullConstant(yyltype loc) : Expr(loc) {  }

	void Check()
	{
		typeflag = Type::nullType;
	}

	void Emit(CodeGenerator* cg)
	{
		memlocation = cg->GenLoadConstant(0);
	}
};

class Operator : public Node 
{
protected:
	char tokenString[4];

public:
	Operator(yyltype loc, const char *tok);
	friend ostream& operator<<(ostream& out, Operator *o) { return out << o->tokenString; }
	char* GetOpName(){return tokenString;}
};

class CompoundExpr : public Expr
{
protected:
	Operator *op;
	Expr *left, *right; // left will be NULL if unary

public:
	CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
	CompoundExpr(Operator *op, Expr *rhs);             // for unary
};

class ArithmeticExpr : public CompoundExpr 
{
public:
	ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
	ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}

	void BuildScope(Scope* sp);
	void Check();

	void Emit(CodeGenerator* cg);
};

class RelationalExpr : public CompoundExpr 
{
public:
	RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}

	void BuildScope(Scope* sp);
	void Check();

	void Emit(CodeGenerator* cg);
};

class EqualityExpr : public CompoundExpr 
{
public:
	EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
	const char *GetPrintNameForNode() { return "EqualityExpr"; }

	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

class LogicalExpr : public CompoundExpr 
{
public:
	LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
	LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
	const char *GetPrintNameForNode() { return "LogicalExpr"; }

	void BuildScope(Scope* sp);
	void Check();
	void Emit(CodeGenerator* cg);
};

class LValue : public Expr 
{
public:
	LValue(yyltype loc) : Expr(loc) {}

};



class AssignExpr : public CompoundExpr 
{
public:
	AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
	const char *GetPrintNameForNode() { return "AssignExpr"; }

	void BuildScope(Scope* sp);
	void Check();

	void Emit(CodeGenerator* cg);
};

class This : public Expr 
{
public:
	This(yyltype loc) : Expr(loc) {}

	void BuildScope(Scope* sp);	
	void Check();
	void Emit(CodeGenerator*cg)
	{
		memlocation = new Location(fpRelative,CodeGenerator::OffsetToFirstParam,"this");
	}
};

class ArrayAccess : public LValue 
{
protected:
	Expr *base, *subscript;
	//memlocation         // when it as left value,it pointer to element,while it as right value, it contain the dereference value in tmp
public:
	ArrayAccess(yyltype loc, Expr *base, Expr *subscript);

	void BuildScope(Scope* sp);
	void Check();

	void Emit(CodeGenerator* cg); //value
	void Emit_StoreProc(CodeGenerator* cg,Location* val); // for write back in assign express
	void Emit_RunTime_RangeCheck(CodeGenerator* cg);
};

class FieldAccess : public LValue 
{
protected:
	Expr *base;	// will be NULL if no explicit base
	Identifier *field;

	VarDecl* fieldDecl; // assign in check()
	bool isMemberVar;   //assign in check()
	//memlocation  the same as in array access
public:
	FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base

	void BuildScope(Scope* sp);
	void Check();
	VarDecl* LookupVarDeclFromCurToClass();// local declare > parent class > global declare

	void Emit(CodeGenerator* cg);// default get value for read
	void Emit_StoreProc(CodeGenerator* cg,Location* val) ; // for write;
	bool GetFieldisMemberVar()
	{
		return isMemberVar;
	}
};

class Call : public Expr 
{
protected:
	Expr *base;	// will be NULL if no explicit base
	Identifier *field;
	List<Expr*> *actuals;
	FnDecl* fieldFnDecl;  //assign in check()

public:
	Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);

	void BuildScope(Scope* sp);
	void Check();
	FnDecl* LookupFnDeclFromCurToClass();

	int Emit_PushPara(CodeGenerator* cg);
	void Emit(CodeGenerator* cg);// because function label or offset is known at compiler time
};

class NewExpr : public Expr
{
protected:
	NamedType *cType;

public:
	NewExpr(yyltype loc, NamedType *clsType);

	//use statement's BuildScope
	void Check();
	
	void Emit(CodeGenerator* cg);
};

class NewArrayExpr : public Expr
{
protected:
	Expr *size;
	Type *elemType;
	//memlocation has the alloc address
public:
	NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);

	void BuildScope(Scope* sp);
	void Check();

	void Emit(CodeGenerator* cg);
};

class ReadIntegerExpr : public Expr
{
public:
	ReadIntegerExpr(yyltype loc) : Expr(loc) {}

	void Check()
	{
		typeflag = Type::intType;
	}

	void Emit(CodeGenerator* cg)
	{
		memlocation = cg->GenBuiltInCall(ReadInteger,NULL,NULL);
	}
};

class ReadLineExpr : public Expr
{
public:
	ReadLineExpr(yyltype loc) : Expr (loc) {}

	void Check()
	{
		typeflag = Type::stringType;	
	}

	void Emit(CodeGenerator* cg)
	{
		memlocation = cg->GenBuiltInCall(ReadLine,NULL,NULL);
	}
};


#endif
