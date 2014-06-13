/* File: ast_decl.cc
* -----------------
* Implementation of Decl node classes.
*/
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"

/***************************Decl****************************/

Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
	Assert(n != NULL);
	(id=n)->SetParent(this); 	
	scope = new Scope(NULL);
	memsize = 0;
}

Decl::~Decl()
{
	if (id!= NULL)
	{
		delete id;
	}

	if (scope!=NULL)
	{
		delete scope;
	}
}

void Decl::BuildScope( Scope* parent )
{
	scope->SetParentScope(parent);
}

/***************************VarDecl****************************/
VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
	Assert(n != NULL && t != NULL);
	(type=t)->SetParent(this);

	offsetVar = 0;
	memsize = CodeGenerator::VarSize;
}

void VarDecl::Check()
{
   //check type
	type->Check(scope);

   // id check had done in BuildScope
}

/***************************ClassDecl****************************/
ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
	// extends can be NULL, impl & mem may be empty lists but cannot be NULL
	Assert(n != NULL && imp != NULL && m != NULL);     
	extends = ex;
	if (extends) extends->SetParent(this);
	(implements=imp)->SetParentAll(this);
	(members=m)->SetParentAll(this);

	VTableList    = new List<FnDecl*>;
	VarOffsetList = new List<VarDecl*>;

	VTableLabel+= n->name ;
	VTableLabel+="_Class_VTable";
	hadPreHandle = 0;
}

void ClassDecl::Check()
{
	//check class name had done in BuildScope

	//check extends
	if (extends!=NULL)
		extends->CheckisClass(scope);

	//check implements
	for(int i=0; i<implements->NumElements();i++)
		implements->Nth(i)->CheckisInterface(scope);

	//check class block
	scope->includedByClass = this;
	for (int i=0;i<members->NumElements();i++)
		members->Nth(i)->Check();
	
	//check it's function agreement with it's extend class if function name is equal
	if (extends !=NULL)
	{
		ClassDecl* pExtendC = scope->LookupClassInTable(extends->typeName);
		if(pExtendC!=NULL)
		{
			for (int i=0;i<members->NumElements();i++)
			{
				FnDecl* pLocal = dynamic_cast<FnDecl*>(members->Nth(i));
				if (pLocal!=NULL)// funciton
				{
					FnDecl* pExtendFun = pExtendC->LookupFnInNamedType(pLocal->id->name);
					if (pExtendFun!=NULL)// the same function name
					{
						if(!pLocal->IsInterfaceEqual(pExtendFun))
							ReportError::OverrideMismatch(pLocal);
					}
				}
			}
		}
	}

	//check it has implemented all the interface function?
	for(int i=0; i<implements->NumElements();i++)
	{
		NamedType* pType = implements->Nth(i);
		InterfaceDecl* pInter = scope->LookupInterfaceInTable(pType->typeName);
		if (pInter==NULL)
			ReportError::ImplementIsNotInterface(this,pType);
		else
		{
			for (int j=0;j<pInter->members->NumElements();j++)
			{
				Decl* pDecl = scope->LookupInCurTable(pInter->members->Nth(j)->id->name);
				FnDecl* pfunInClass = dynamic_cast<FnDecl*>(pDecl);
				if(pfunInClass==NULL)
					ReportError::InterfaceNotImplemented(this,pType);
				else if (pfunInClass!=NULL && !pfunInClass->IsInterfaceEqual(pInter->members->Nth(j)))
					ReportError::OverrideMismatch(pInter->members->Nth(j));
			}
		}

	}
}

VarDecl* ClassDecl::LookupVarDeclInNamedClass(char* varName)
{
	//current 
	for (int i=0;i<members->NumElements();i++)
	{
		VarDecl* pvarDecl = members->Nth(i)->LookupVarDeclInNamedClass(varName);
		if(pvarDecl!=NULL)
			return pvarDecl;
	}

	//parent class
	if (extends!=NULL)
	{
		ClassDecl* pextendC = scope->LookupClassInTable(extends->typeName);
		if (pextendC!=NULL)
		{
			return pextendC->LookupVarDeclInNamedClass(varName);
		}
	}
	return NULL;
}

FnDecl* ClassDecl::LookupFnInNamedType(char* fnname)
{
	//current 
	for (int i=0;i<members->NumElements();i++)
	{
		FnDecl* pfnDecl = members->Nth(i)->LookupFnInNamedType(fnname);
		if(pfnDecl!=NULL)
			return pfnDecl;
	}

	//parent class
	if (extends!=NULL)
	{
		ClassDecl* pextendC = scope->LookupClassInTable(extends->typeName);
		if (pextendC!=NULL)
		{
			FnDecl* pFn =  pextendC->LookupFnInNamedType(fnname);
			if(pFn != NULL)
				return pFn;
		}
	}

	//parent interface
	for (int i=0;i<implements->NumElements();i++)
	{
		InterfaceDecl* pInDecl = scope->LookupInterfaceInTable(implements->Nth(i)->typeName);
		if (pInDecl!=NULL)
		{
			FnDecl* pResult = pInDecl->LookupFnInNamedType(fnname);
			if (pResult!=NULL)
				return pResult;
		}
	}

	return NULL;
}

void ClassDecl::BuildScope( Scope* parent )
{
	scope->SetParentScope(parent);
	for (int i=0,n=members->NumElements(); i<n; i++)
	{
		scope->AddToCurSymTable(members->Nth(i)->id->name,members->Nth(i));
		members->Nth(i)->BuildScope(scope);
	}
}

void ClassDecl::PreEmitOnOrderOfMembers()
{
	if (hadPreHandle)
		return;
	ClassDecl* pCD;

	//the parent
	if(extends!=NULL && (pCD = dynamic_cast<ClassDecl*>(extends->GetNamedTypeDecl(scope)))!=NULL)
	{
		pCD->PreEmitOnOrderOfMembers();	
		
		for (int i=0,n=pCD->VarOffsetList->NumElements();i<n;i++)
		{
			VarOffsetList->Append(pCD->VarOffsetList->Nth(i));
		}
		
		for (int i=0,n=pCD->VTableList->NumElements();i<n;i++)
		{
			VTableList->Append(pCD->VTableList->Nth(i));
		}
	}

	//local
	for (int i=0,n=members->NumElements();i<n;i++)
	{
		VarDecl* plocalVar = NULL;
		FnDecl* plocalFn=NULL;
		
		//variable
		bool hasReDeclare = 0;
		if (plocalVar=dynamic_cast<VarDecl*>(members->Nth(i)))
		{
			for (int j=0,m=VarOffsetList->NumElements();j<m;j++)
			{
				if (strcmp(plocalVar->GetName(),VarOffsetList->Nth(j)->GetName())==0)
				{
					VarOffsetList->RemoveAt(j);
					VarOffsetList->InsertAt(plocalVar,j);
					hasReDeclare = 1;
					break;
				}
			}
			if(!hasReDeclare)
				VarOffsetList->Append(plocalVar);
		}

		//function
		bool hasOverrided = 0;
		if (plocalFn = dynamic_cast<FnDecl*>(members->Nth(i)))
		{
			for (int j=0,m=VTableList->NumElements();j<m;j++)
			{
				//handle override
				if (strcmp(plocalFn->GetName(),VTableList->Nth(j)->GetName())==0)
				{
					VTableList->RemoveAt(j);
					VTableList->InsertAt(plocalFn,j);
					hasOverrided = 1;
					break;
				}
			}
			if(!hasOverrided)
				VTableList->Append(plocalFn);
		}
	}


	//  variable offset 
	int voffset = CodeGenerator::OffsetToFirstField;
	for (int i=0,n=VarOffsetList->NumElements();i<n;i++)
	{
		VarOffsetList->Nth(i)->SetVarOffset(voffset);
		voffset+=VarOffsetList->Nth(i)->GetMemSize();
	}
	memsize = voffset;
	

	// function offset
	for (int i=0,n=VTableList->NumElements();i<n;i++)
	{
		VTableList->Nth(i)->SetMethodOffset(i);
	}
	hadPreHandle = 1;
}

void ClassDecl::EmitFunctionAndVTable( CodeGenerator* cg )
{
	//insert function into VTable;
	PreEmitOnOrderOfMembers();

	// emit every function
	for (int i=0,n=members->NumElements();i<n;i++)
	{
		FnDecl* pFn=NULL;
		if (pFn=dynamic_cast<FnDecl*>(members->Nth(i)))
		{
			pFn->Emit(cg);
		}
	}

	//emit VTable
	List<const char*>* vTableFunLabel = new List< const char*>;
	for (int i=0,n=VTableList->NumElements();i<n;i++)
	{
		vTableFunLabel->Append(VTableList->Nth(i)->funLabel.c_str());
	}
	cg->GenVTable(VTableLabel.c_str(),vTableFunLabel);
}

void ClassDecl::Emit( CodeGenerator* cg )
{
	EmitFunctionAndVTable(cg);
}

/***************************InterfaceDecl****************************/

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
	Assert(n != NULL && m != NULL);
	(members=m)->SetParentAll(this);
}

void InterfaceDecl::Check()
{
	//check interface block
	for (int i=0;i<members->NumElements();i++)
		members->Nth(i)->Check();
	scope->includedByInterface = this;
}

FnDecl* InterfaceDecl::LookupFnInNamedType(char* fnname )
{
	for (int i=0;i<members->NumElements();i++)
	{
		FnDecl* pFn = members->Nth(i)->LookupFnInNamedType(fnname);
		if(pFn!=NULL)
			return pFn;
	}
	return NULL;
}

void InterfaceDecl::BuildScope( Scope* parent )
{
	scope->SetParentScope(parent);
	for (int i=0,n=members->NumElements(); i<n; i++)
	{
		scope->AddToCurSymTable(members->Nth(i)->id->name,members->Nth(i));
		members->Nth(i)->BuildScope(scope);
	}
}

/***************************FnDecl****************************/

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
	Assert(n != NULL && r!= NULL && d != NULL);
	(returnType=r)->SetParent(this);
	(formals=d)->SetParentAll(this);
	body = NULL;
	methodOffset = 0;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
	(body=b)->SetParent(this);
}


void FnDecl::Check()
{
	//check function name

	//check function parameters
	for (int i=0; i< formals->NumElements();i++)
		formals->Nth(i)->Check();

	//check body
	if(body!=NULL)
		body->Check();

	//check function return type
	returnType->Check(scope);

	//generate function label for TAC
	isMethod();
	funLabel = typeName;
	funLabel+=GetName();
}

bool FnDecl::IsInterfaceEqual( Decl* fnDecl )
{
	FnDecl* pfn = dynamic_cast<FnDecl*>(fnDecl);
	if(pfn == NULL) return 0;

	//check id
	if (strcmp(id->name,pfn->id->name) != 0)
		return 0;

	//check formals
	int localParaNums = formals->NumElements();
	int interParaNums = pfn->formals->NumElements();

	if (localParaNums != interParaNums)
		return 0;
	else
	{
		for (int i=0;i<localParaNums;i++)
		{
			if(!formals->Nth(i)->type->IsEquivalentTo(pfn->formals->Nth(i)->type))
				return 0;
		}
	}

	//check return type
	if (!returnType->IsEquivalentTo(pfn->returnType))
		return 0;

	// had finish checked 
	return 1;
}

void FnDecl::BuildScope( Scope* parent )
{
	scope->SetParentScope(parent);
	//because the formals must been putted in the block scope
	if (body!=NULL)
		scope->MergeScope(& body->scope); // let body's scope pointer to the FnDecl's scope;

	for (int i=0,n=formals->NumElements(); i<n; i++)
	{
		scope->AddToCurSymTable(formals->Nth(i)->id->name,formals->Nth(i));
		formals->Nth(i)->BuildScope(scope);
	}

	if (body!=NULL)
		body->BuildScope(scope);
}

bool FnDecl::isMethod()
{
	if(scope->Parent == NULL)
		return 0;

	if (scope->Parent->includedByClass!=NULL)
	{
		typeName = scope->Parent->includedByClass->GetName();
		return 1;
	}

	if (scope->Parent->includedByInterface!=NULL)
	{
		typeName = scope->Parent->includedByInterface->GetName();
		return 1;
	}

	return 0;
}

void FnDecl::Emit( CodeGenerator* cg )
{
	//Parameters bind to memory location 
	int offset = CodeGenerator::OffsetToFirstParam;
	if (isMethod())  //this 
	{
		offset+=CodeGenerator::OffsetToFirstField;
	}

	//link para to location
	for (int i =0,n=formals->NumElements(); i<n; i++)
	{
		VarDecl* pVD = formals->Nth(i);
		pVD->memloc = new Location(fpRelative,offset,pVD->GetName());
		offset+=pVD->GetMemSize();
		pVD->SetVarOffset(offset);
	}

	//function body
	int funInnerOffset = CodeGenerator::OffsetToFirstLocal;
	if (body!=NULL)
	{
		//generate function Label
		cg->GenLabel(funLabel.c_str());

		//begin fun
		BeginFunc* begtemp = cg->GenBeginFunc(); //reset localoffset in cg
		body->Emit(cg);
		memsize = body->GetMemSize();   //local and temp variable, exclude fp,ra
		begtemp->SetFrameSize(memsize); //backpatch
		// end fun
		cg->GenEndFunc();
	}
}

/***************************Scope****************************/

Decl* Scope::LookupInAllTable( char* key )
{
	if(key==NULL) 
		return NULL;

	Scope* tmp = this;
	Decl* pDecl = NULL;
	while (tmp!=NULL)
	{
		pDecl = (tmp->SymTable).Lookup(key);
		if (pDecl != NULL)
		{
			return pDecl;
		}
		tmp = tmp->Parent;
	}		
	return NULL;
}

Decl* Scope::LookupInCurTable( char* key )
{
	if(key==NULL) 
		return NULL;
	else
		return SymTable.Lookup(key);
}

VarDecl* Scope::LookupVarInTable( char* key )
{
	Decl* dc = LookupInAllTable(key);
	VarDecl* varDc = dynamic_cast<VarDecl*>(dc);
	if (varDc!=NULL)
		return varDc;
	else
		return NULL;
}

ClassDecl* Scope::LookupClassInTable( char* key )
{
	Decl* dc = LookupInAllTable(key);

	ClassDecl* classDc = dynamic_cast<ClassDecl*>(dc);
	if (classDc!=NULL)
		return classDc;
	else
		return NULL;
}

FnDecl* Scope::LookupFunInTable( char* key )
{
	Decl* pFn = LookupInAllTable(key);
	return dynamic_cast<FnDecl*>(pFn);
}

InterfaceDecl* Scope::LookupInterfaceInTable( char* key )
{
	Decl* pIn = LookupInAllTable(key);
	return dynamic_cast<InterfaceDecl*>(pIn);
}

Decl* Scope::LookupTypeDeclInTable( char* key )
{
	Decl* pDecl = LookupInAllTable(key);
	if (dynamic_cast<ClassDecl*>(pDecl)!=NULL  ||  dynamic_cast<InterfaceDecl*>(pDecl)!=NULL)
	{
		return pDecl;
	}
	return NULL;
}

ClassDecl* Scope::LookupNearestClassofThis()
{
	Scope* tmp = this;
	while (tmp != NULL)
	{
		if (tmp->includedByClass!=NULL)
		{
			return tmp->includedByClass;
		}
		tmp = tmp->Parent;
	}

	return NULL;
}

void Scope::MergeScope( Scope** sp )
{
	if (*sp!=NULL)
	{
		delete *sp;
		*sp = this; 
	}
}






