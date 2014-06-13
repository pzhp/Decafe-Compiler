/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"

ClassDecl* Expr::GetCurMostNearClass()
{
	Scope* sp = scope;
	while (sp!=NULL)
	{
		if (sp->includedByClass!=NULL)
		{
			return sp->includedByClass;
		}
		sp =sp->Parent;
	}
	return NULL;
}

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;

}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = _strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}
CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}
 

void ArithmeticExpr::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	if (left!=NULL)
		left->BuildScope(sp);

	right->BuildScope(sp);
}

void ArithmeticExpr::Check()
{
	//binary check
	if (left != NULL)
	{
		left->Check();
		right->Check();

		Type* ll =  left->typeflag;
		Type* rr =  right->typeflag;
		bool sameInt    = ll->IsEquivalentTo(Type::intType) && rr->IsEquivalentTo(Type::intType);
		bool sameDouble = ll->IsEquivalentTo(Type::doubleType) && rr->IsEquivalentTo(Type::doubleType);

		if (sameDouble)
			typeflag = Type::doubleType;
		else if(sameInt)
			typeflag = Type::intType;
		else
		{
			ReportError::IncompatibleOperands(op,ll,rr);			
			typeflag = Type::errorType; //avoid error Cascade
		}
	}
	else //unary check
	{
		right->Check();
		typeflag = right->typeflag;
	}
}

void ArithmeticExpr::Emit( CodeGenerator* cg )
{
	right->Emit(cg);
	if(left)
	{
		left->Emit(cg);
		memlocation=cg->GenBinaryOp(op->GetOpName(),left->memlocation,right->memlocation);
	}
	else//-7
	{
		Location* zero = cg->GenLoadConstant(0);
		memlocation=cg->GenBinaryOp(op->GetOpName(),zero,right->memlocation);
	}
}


void RelationalExpr::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	left->BuildScope(sp);
	right->BuildScope(sp);
}

void RelationalExpr::Check()
{
	//binary check
	if (left != NULL)
	{
		left->Check();
		right->Check();

		Type* ll =  left->typeflag;
		Type* rr =  right->typeflag;
		bool sameInt    = ll->IsEquivalentTo(Type::intType) && rr->IsEquivalentTo(Type::intType);
		bool sameDouble = ll->IsEquivalentTo(Type::doubleType) && rr->IsEquivalentTo(Type::doubleType);

		if(sameDouble != true && sameInt != true)
			ReportError::IncompatibleOperands(op,ll,rr);				
		typeflag = Type::boolType; 
	}
	else //unary check
	{
		right->Check();
		if(!right->typeflag->IsEquivalentTo(Type::intType) && !right->typeflag->IsEquivalentTo(Type::doubleType))
			ReportError::IncompatibleOperand(op,right->typeflag);
		typeflag = Type::boolType;
	}
}

void RelationalExpr::Emit( CodeGenerator* cg )
{
	right->Emit(cg);
	left->Emit(cg);
	if(strcmp(op->GetOpName(),">")==0) // only have "<",need to transform
		memlocation=cg->GenBinaryOp("<",right->memlocation,left->memlocation);
	else if(strcmp(op->GetOpName(),"<")==0)
		memlocation=cg->GenBinaryOp(op->GetOpName(),left->memlocation,right->memlocation);
	else if (strcmp(op->GetOpName(),">=")==0)
	{
		memlocation = cg->GenBinaryOp("<",left->memlocation,right->memlocation); // <
		memlocation = cg->GenBinaryOp("==",memlocation,cg->GenLoadConstant(0));//reverse
	}
	else //<=
	{
		memlocation = cg->GenBinaryOp(">",right->memlocation,left->memlocation); // >
		memlocation = cg->GenBinaryOp("==",memlocation,cg->GenLoadConstant(0));//reverse
	}
}

void EqualityExpr::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	left->BuildScope(sp);
	right->BuildScope(sp);
}

void EqualityExpr::Check()
{
	left->Check();
	right->Check();
	if(!left->typeflag->IsCompatibleTo(right->typeflag,scope) && !right->typeflag->IsCompatibleTo(left->typeflag,scope))
		ReportError::IncompatibleOperands(op,left->typeflag,right->typeflag);		
	typeflag = Type::boolType;
}

void EqualityExpr::Emit( CodeGenerator* cg )
{
	right->Emit(cg);
	left->Emit(cg);

	if (strcmp(op->GetOpName(),"==")==0)// for array class ,reference equal
	{
		if (left->typeflag->IsEquivalentTo(Type::stringType))
			memlocation = cg->GenBuiltInCall(StringEqual,left->memlocation,right->memlocation);
		else
			memlocation=cg->GenBinaryOp(op->GetOpName(),left->memlocation,right->memlocation);
	}
	else // !=
	{
		Location* tmp;
		if (left->typeflag->IsEquivalentTo(Type::stringType))
			tmp = cg->GenBuiltInCall(StringEqual,left->memlocation,right->memlocation);
		else
			tmp = cg->GenBinaryOp("==",left->memlocation,right->memlocation);

		//just 	!	
		memlocation = cg->GenBinaryOp("==",tmp,cg->GenLoadConstant(0));
	}
}

void LogicalExpr::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	if (left!=NULL)
		left->BuildScope(sp);

	right->BuildScope(sp);
}

void LogicalExpr::Check()
{
	//binary check
	if (left != NULL)
	{
		left->Check();
		right->Check();

		Type* ll =  left->typeflag;
		Type* rr =  right->typeflag;

		if(!ll->IsEquivalentTo(Type::boolType) || !rr->IsEquivalentTo(Type::boolType))
			ReportError::IncompatibleOperands(op,ll,rr);				
		typeflag = Type::boolType; 
	}
	else //unary check
	{
		right->Check();
		if(!right->typeflag->IsEquivalentTo(Type::boolType))
			ReportError::IncompatibleOperand(op,right->typeflag);
		typeflag = Type::boolType;
	}
}

void LogicalExpr::Emit( CodeGenerator* cg )
{
	right->Emit(cg);
	if(left)
	{
		left->Emit(cg);
		memlocation=cg->GenBinaryOp(op->GetOpName(),left->memlocation,right->memlocation);
	}
	else
	{
		// ! a 
		memlocation = cg->GenBinaryOp("==",right->memlocation,cg->GenLoadConstant(0));
	}
}

void AssignExpr::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	left->BuildScope(sp);
	right->BuildScope(sp);
}

void AssignExpr::Check()
{
	left->Check();
	right->Check();

	if (!right->typeflag->IsCompatibleTo(left->typeflag,scope))
		ReportError::IncompatibleOperands(op,left->typeflag,right->typeflag);

	typeflag = left->typeflag;
}

void AssignExpr::Emit( CodeGenerator* cg )
{
	right->Emit(cg);
	//array 
	ArrayAccess* arr = NULL;
	FieldAccess* field =NULL;
	if (arr = dynamic_cast<ArrayAccess*>(left))
	{
		arr->Emit_StoreProc(cg,right->memlocation);
	}else if ((field = dynamic_cast<FieldAccess*>(left)) && field->GetFieldisMemberVar())//field
	{
		field->Emit_StoreProc(cg,right->memlocation);
	}
	else
	{
		left->Emit(cg);
		cg->GenAssign(left->memlocation,right->memlocation);
	}
	
	memlocation = right->memlocation; // to rethink
}



void This::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
}

void This::Check()
{
	ClassDecl* pClass = scope->LookupNearestClassofThis();
	if (pClass==NULL)
	{
		ReportError::ThisOutsideClassScope(this);
		typeflag = Type::errorType;
	}
	else
		typeflag = new NamedType(pClass->id);
}


ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

void ArrayAccess::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	if (base!=NULL)
		base->BuildScope(sp);

	subscript->BuildScope(sp);
}

void ArrayAccess::Check()
{
	base->Check();
	ArrayType* pArray = dynamic_cast<ArrayType*>(base->typeflag);

	if (pArray == NULL)
	{
		ReportError::BracketsOnNonArray(base);
		typeflag = Type::errorType;
	}
	else
	{
		subscript->Check();
		if (! subscript->typeflag->IsEquivalentTo(Type::intType))
			ReportError::SubscriptNotInteger(subscript);

		typeflag = pArray->elemType;
	}
}

void ArrayAccess::Emit( CodeGenerator* cg )
{
	base->Emit(cg);
	subscript->Emit(cg);
	
	// Runtime Check
	Emit_RunTime_RangeCheck(cg);

	//offset= infoheader+subscript*TypeSize
	int infoheader = 4;
	Location* pheaderConst = cg->GenLoadConstant(4);	
	Location* pHeaderOffset = cg->GenBinaryOp("+",base->memlocation,pheaderConst);

	int typeSize = 4; 
	Location* pTypeSize = cg->GenLoadConstant(typeSize);
	Location* indexOffset = cg->GenBinaryOp("*",subscript->memlocation,pTypeSize);

	Location* memAddress  = cg->GenBinaryOp("+",pHeaderOffset,indexOffset);  
	memlocation = cg->GenLoad(memAddress); //dereference
}

void ArrayAccess::Emit_StoreProc( CodeGenerator* cg,Location* val ) /* for write back */
{
	base->Emit(cg);
	subscript->Emit(cg);

	//runtime check
	Emit_RunTime_RangeCheck(cg);

	//offset= infoheader+subscript*TypeSize
	int infoheader = 4;
	Location* pheaderConst = cg->GenLoadConstant(4);
	Location* pHeaderOffset = cg->GenBinaryOp("+",base->memlocation,pheaderConst);

	int typeSize = 4; 
	Location* pTypeSize = cg->GenLoadConstant(typeSize);
	Location* indexOffset = cg->GenBinaryOp("*",subscript->memlocation,pTypeSize);

	memlocation  = cg->GenBinaryOp("+",pHeaderOffset,indexOffset);  
	
	cg->GenStore(memlocation,val);
}

void ArrayAccess::Emit_RunTime_RangeCheck(CodeGenerator* cg)
{
	char* NormalLabel = cg->NewLabel();

	Location* len = cg->GenLoad(base->memlocation,0);
	Location* one = cg->GenLoadConstant(1);
	len = cg->GenBinaryOp("-",len,one);

	//overflow
	Location* tup  = cg->GenBinaryOp("<",len,subscript->memlocation);	//0-normal
	//underflow
	Location* under =cg->GenBinaryOp("<",subscript->memlocation,cg->GenLoadConstant(0));//0-normal
	
	Location* result = cg->GenBinaryOp("||",tup,under);
	result = cg->GenBinaryOp("==",result,one);
	cg->GenIfZ(result,NormalLabel);
	//Except
	Location* ptips = cg->GenLoadLabel("ArrayBoundary");// this store in defs.asm
	cg->GenBuiltInCall(PrintString,ptips,NULL);
	cg->GenBuiltInCall(Halt,NULL,NULL);

	// Normal
	cg->GenLabel(NormalLabel);
}


FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);

	isMemberVar = 1;
}

void FieldAccess::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	if (base!=NULL)
		base->BuildScope(sp);
}

void FieldAccess::Check()
{
	VarDecl* varD = NULL ;
	if (base == NULL)//
	{
		//first ,current scope to nearest class scope
		varD = LookupVarDeclFromCurToClass();
		isMemberVar = 0;
		//second, in class inherit; third,from class to up level scope
		if (!varD)
		{
			ClassDecl* pCD = GetCurMostNearClass();
			if (pCD!=NULL)
			{
				varD = pCD->LookupVarDeclInNamedClass(field->name);
				isMemberVar = 1;
				if (!varD && pCD->scope->Parent!=NULL)
				{
					pCD->scope->Parent->LookupVarInTable(field->name);
					isMemberVar = 0;
				}
			}
		}
	    
		//find over		
		if (varD == NULL) // variable not declare
		{
			ReportError::IdentifierNotDeclared(field,LookingForVariable);
			typeflag = Type::errorType;
		}
		else		
		{				
			typeflag = varD->type;
			fieldDecl = varD;
		}
	}
	else //b.a
	{
		base->Check();// check base was declared
		Decl* pD = base->typeflag->GetNamedTypeDecl(scope);
		if (pD == NULL)
		{
			typeflag = Type::errorType;
			ReportError::FieldNotFoundInBase(field,base->typeflag);
		}
		else
		{
			ClassDecl* pCDecl =dynamic_cast<ClassDecl*>(pD);
			if (pCDecl == NULL)
				typeflag = Type::errorType;
			else
			{
				VarDecl*  pVar = pCDecl->LookupVarDeclInNamedClass(field->name);
				if(pVar==NULL)
				{
					typeflag = Type::errorType;
					ReportError::FieldNotFoundInBase(field,base->typeflag);
				}
				else				
				{
					typeflag = pVar->type;
					//if (dynamic_cast<This*>(base)==NULL) // if not this.a form, error
						//ReportError::InaccessibleField(field,base->typeflag);

					fieldDecl = pVar;
				}
			}		
		}				
	}
}

VarDecl* FieldAccess::LookupVarDeclFromCurToClass()
{
	Scope* sp = scope;
	while (sp!=NULL && sp->includedByClass==NULL)
	{
		VarDecl* pVar = dynamic_cast<VarDecl*>(sp->LookupInCurTable(field->name));
		if (pVar)
			return pVar;
		sp = sp->Parent;
	}

	return NULL;
}

void FieldAccess::Emit( CodeGenerator* cg )
{
	if (!base) // a is free Var or member Var
	{
		Assert(fieldDecl!=NULL);
		if(!isMemberVar)
			memlocation = fieldDecl->memloc;
		else
		{
			Location* this_loc = new Location(fpRelative,4,"this");
			Location* t1 = cg->GenLoadConstant(fieldDecl->GetVarOffset());
			Location* memAddress = cg->GenBinaryOp("+",this_loc,t1);
			memlocation = cg->GenLoad(memAddress,0);
		}

	}else //a.b, use offset 
	{
		base->Emit(cg); //Get pointer to alloc address
		int offset = fieldDecl->GetVarOffset();
		Location* t1 = cg->GenLoadConstant(offset);
		Location* memAddress = cg->GenBinaryOp("+",base->memlocation,t1);
		memlocation = cg->GenLoad(memAddress,0);
	}
}

void FieldAccess::Emit_StoreProc( CodeGenerator* cg,Location* val ) /* for write */
{
	if (!base) // a is free Var or member Var
	{
		Assert(fieldDecl!=NULL);
		if(!isMemberVar)
			memlocation = fieldDecl->memloc; // Not in
		else
		{
			Location* this_loc = new Location(fpRelative,4,"this");
			Location* t1 = cg->GenLoadConstant(fieldDecl->GetVarOffset());
			memlocation = cg->GenBinaryOp("+",this_loc,t1);
		}

	}else //a.b, use offset 
	{
		base->Emit(cg); //Get pointer to alloc address
		int offset = fieldDecl->GetVarOffset();
		Location* t1 = cg->GenLoadConstant(offset);
		memlocation = cg->GenBinaryOp("+",base->memlocation,t1);
	}	

	cg->GenStore(memlocation,val);
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

void Call::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	if(base!=NULL) base->BuildScope(sp);

	for (int i=0,n=actuals->NumElements();i<n;i++)
		actuals->Nth(i)->BuildScope(sp);
}

void Call::Check()
{
	bool isSucceed =0;
	FnDecl* pFn = NULL;
	if (base == NULL )
	{
		//first,from current to class
		pFn = LookupFnDeclFromCurToClass();
		if(pFn==NULL)
		{
			ClassDecl* pCd = GetCurMostNearClass();
			if(pCd!=NULL)
			{
				pFn = pCd->LookupFnInNamedType(field->name); //second, in class inherit
				if (pFn==NULL && pCd->scope->Parent!=NULL)
					pFn = pCd->scope->Parent->LookupFunInTable(field->name); //third,in up level scope
			}
		}

		if (pFn == NULL)
			ReportError::IdentifierNotDeclared(field,LookingForFunction);
	}
	else//b.fun();
	{
		base->Check();
		Decl* pDecl = scope->LookupTypeDeclInTable(base->typeflag->typeName);
		ArrayType* pArrayT =NULL;
		if(pDecl!=NULL) //type
		{
			pFn  = pDecl->LookupFnInNamedType(field->name);			
			if (pFn ==NULL)
				ReportError::FieldNotFoundInBase(field,base->typeflag);
		}
		else if( (pArrayT = dynamic_cast<ArrayType*>(base->typeflag))!=NULL) //array type
		{
			pFn = pArrayT->sysLengthFun;			
		}
		else// primitive type
			ReportError::FieldNotFoundInBase(field,base->typeflag);
	}

	// for TAC
	fieldFnDecl = pFn;
	
	// pass para verify
	int wrongsums = -1;
	if(pFn != NULL)
	{
		//check fun para nums
		int expected = pFn->formals->NumElements();
		int given = actuals->NumElements();
		if (expected != given)
			ReportError::NumArgsMismatch(field,expected,given);
		else 	//check fun para type
		{			
			wrongsums = 0;
			for (int i=0;i<expected;i++)
			{
				actuals->Nth(i)->Check();
				Type* pGiven = actuals->Nth(i)->typeflag;
				Type* pForms = pFn->formals->Nth(i)->type;
				if (! pGiven->IsCompatibleTo(pForms,scope))
				{ 
					ReportError::ArgMismatch(actuals->Nth(i),i+1,pGiven,pForms);
					wrongsums++;
				}
			}
		}
	}
	else
	{
		for (int i=0,n=actuals->NumElements();i<n;i++)
		{
			actuals->Nth(i)->Check();
		}
	}

	if (wrongsums==0)
		typeflag = pFn->returnType;
	else
		typeflag = Type::errorType;
}

FnDecl* Call::LookupFnDeclFromCurToClass()
{
	Scope* sp = scope;
	while (sp!=NULL && sp->includedByClass==NULL)
	{
		FnDecl* pFn = dynamic_cast<FnDecl*>(sp->LookupInCurTable(field->name));
		if (pFn!=NULL)
			return pFn;
		sp = sp->Parent;
	}

	return NULL;
}

int Call::Emit_PushPara( CodeGenerator* cg )
{
	List<Location*>* paraList = new List<Location*>;
	for (int i=actuals->NumElements()-1;i>=0;i--)
	{
		actuals->Nth(i)->Emit(cg);
		paraList->Append(actuals->Nth(i)->memlocation);
	}
	int ParaNum =0;
	for (int i=0,n=paraList->NumElements();i<n;i++)
	{
		cg->GenPushParam(paraList->Nth(i));
		ParaNum++;
	}

	return ParaNum;
}

/* because function label or offset is known at compiler time ;
  find offset from class, but get VTable from base address*/
void Call::Emit( CodeGenerator* cg ) 
{
	Assert(fieldFnDecl!=NULL);

	//deal with Array legnth() call
	if(base)
	{
		ArrayType* pAt = dynamic_cast<ArrayType*>(base->typeflag);
		if (pAt && fieldFnDecl->IsInterfaceEqual(pAt->GetSysLengthFn()))
		{
			base->Emit(cg); // base address
			memlocation = cg->GenLoad(base->memlocation,0); // get the size
			return;
		}
	}

	//deal with method
	if (fieldFnDecl->isMethod())
	{
		Location* this_loc = NULL;

		if(!base)  //fun()
		{
			this_loc = new Location(fpRelative,4,"this");
		}
		else // a.fun()
		{
			//just for unorder declare
			ClassDecl* pcd = dynamic_cast<ClassDecl*>(base->typeflag->GetNamedTypeDecl(scope));
			Assert(pcd!=NULL);
			pcd->PreEmitOnOrderOfMembers();
			
			base->Emit(cg);
			this_loc = base->memlocation;
		}

		Location* VtableAddr = cg->GenLoad(this_loc,0); 
		int offset = fieldFnDecl->GetMethodOffset()*4; // function occupy 4 bytes
		Location* jumploc = cg->GenLoad(VtableAddr,offset); // lookup vtable for fun address

		//Para
		int ParaNum=Emit_PushPara(cg);
		cg->GenPushParam(this_loc);
		ParaNum++;
		bool hasReturn = fieldFnDecl->returnType->IsEquivalentTo(Type::voidType) ? 0:1;

		//call
		memlocation = cg->GenACall(jumploc,hasReturn);

		cg->GenPopParams(ParaNum*CodeGenerator::VarSize);
	}
	else // only fun(),fun() is global
	{			
		List<Location*>* paraList = new List<Location*>;
		for (int i=actuals->NumElements()-1;i>=0;i--)
		{
			actuals->Nth(i)->Emit(cg);
			paraList->Append(actuals->Nth(i)->memlocation);
		}
		int ParaNum =0;
		for (int i=0,n=paraList->NumElements();i<n;i++)
		{
			cg->GenPushParam(paraList->Nth(i));
			ParaNum++;
		}

		bool HasReturn = fieldFnDecl->returnType->IsEquivalentTo(Type::voidType) ? 0:1;

		memlocation = cg->GenLCall(fieldFnDecl->funLabel.c_str(),HasReturn);

		cg->GenPopParams(ParaNum*CodeGenerator::VarSize);
	}
}



NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::Check()
{
	if(cType->Check(scope))// NamedType exist
		typeflag = cType;
	else
		typeflag = Type::errorType;
}

void NewExpr::Emit( CodeGenerator* cg )
{
	ClassDecl* pcd = dynamic_cast<ClassDecl*>(cType->GetNamedTypeDecl(scope));
	Assert(pcd!=NULL);
	Location* psize = cg->GenLoadConstant(pcd->GetMemSize());
	memlocation = cg->GenBuiltInCall(Alloc,psize,NULL);
	
	//move VTable
	Location* t1 = cg->GenLoadLabel(pcd->VTableLabel.c_str());
	cg->GenStore(memlocation,t1,0);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

void NewArrayExpr::BuildScope( Scope* sp )
{
	scope->SetParentScope(sp);
	size->BuildScope(sp);
}

void NewArrayExpr::Check()
{
	//check elemType
	elemType->Check(scope);	
	if (elemType->IsEquivalentTo(Type::voidType))
		ReportError::NewArrayTypeWrong(elemType);

	//check size
	size->Check();		
	if (!size->typeflag->IsEquivalentTo(Type::intType))
		ReportError::NewArraySizeNotInteger(size);

	ArrayType* pArray = new ArrayType(*GetLocation(),elemType);
	pArray->newArrayExpr = this;
	typeflag = pArray;
}

void NewArrayExpr::Emit( CodeGenerator* cg )
{
	size->Emit(cg);

	//runtime check
	char* normallabel = cg->NewLabel();
	Location* zero = cg->GenLoadConstant(0);
	Location* test = cg->GenBinaryOp("<",size->memlocation,zero);
	cg->GenIfZ(test,normallabel);
	Location* err_str = cg->GenLoadLabel("ArrayCreateError");// assign in defs.asm
	cg->GenBuiltInCall(PrintString,err_str,NULL);
	cg->GenBuiltInCall(Halt,NULL,NULL);

	cg->GenLabel(normallabel);
	//find size 4, different from "new class"
	Location* type_sz = cg->GenLoadConstant(CodeGenerator::VarSize);
	Location* total_sz = cg->GenBinaryOp("*",size->memlocation,type_sz);
	Location* header = cg->GenLoadConstant(CodeGenerator::VarSize);
	Location* total_header_sz = cg->GenBinaryOp("+",total_sz,header);

	//alloc memory
	memlocation = cg->GenBuiltInCall(Alloc,total_header_sz,NULL);

	// set array header 
	cg->GenStore(memlocation,size->memlocation,0);
}

       




