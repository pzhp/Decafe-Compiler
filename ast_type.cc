/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */

#include <string.h>
#include "ast_type.h"
#include "ast_decl.h"
 
/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error"); 



Type::Type(const char *n) {
    Assert(n);
    typeName = _strdup(n);
}

bool Type::IsCompatibleTo( Type *other,Scope* sp )
{
	bool iserror = strcmp(typeName,"error")==0 || strcmp(other->typeName,"error")==0;
	if( (strcmp(typeName,"null")==0) || (strcmp(typeName,other->typeName)==0) || iserror )
		return 1;
	return 0;
}

bool Type::IsEquivalentTo( Type *other )
{
	if(strcmp(typeName,"error")==0 || strcmp(other->typeName,"error")==0 )
		return 1;
	else	
		return strcmp(typeName,other->typeName) == 0;
}


NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
	typeName = _strdup(i->name);
	namedTypeDecl = NULL;
	hasChecked = 0;
} 

bool NamedType::IsEquivalentTo( Type *other )
{
	if((dynamic_cast<NamedType*>(other) != NULL) && (strcmp(id->name,other->typeName)==0))
		return 1;
	return 0;
}

bool NamedType::IsCompatibleTo( Type *other,Scope* sp )
{
	// include the same type compare & interface compare : recursion end condition 
	if (IsEquivalentTo(other))
		return 1;

	Decl* pd  = sp->LookupInAllTable(id->name);		
	ClassDecl* cd = dynamic_cast<ClassDecl*>(pd);
	if(cd==NULL)
		return 0;

	//search in extends
	if(cd->extends != NULL)
		if(cd->extends->IsCompatibleTo(other,sp) == 1)
			return 1;

	//search in implements
	for (int i=0;i<cd->implements->NumElements();i++)
	{
		if(cd->implements->Nth(i)->IsCompatibleTo(other,sp) == 1)
			return 1;
	}

	return 0 ;
}

bool NamedType::Check( Scope* sp )
{
	if(hasChecked)
		return (namedTypeDecl==NULL)? 0:1;
	else
	{
		hasChecked = 1;
		namedTypeDecl = sp->LookupTypeDeclInTable(id->name);	
		if (namedTypeDecl==NULL)
		{
			ReportError::IdentifierNotDeclared(id,LookingForType);
			return 0;
		}
		return 1;
	}
}

void NamedType::CheckisClass( Scope*sp )
{
	Decl* pd = sp->LookupInAllTable(id->name);		
	ClassDecl* pnt = dynamic_cast<ClassDecl*>(pd);		
	if (pnt == NULL)
		ReportError::IdentifierNotDeclared(id,LookingForClass);
}

void NamedType::CheckisInterface( Scope*sp )
{
	Decl* pd = sp->LookupInAllTable(id->name);		
	InterfaceDecl* pnt = dynamic_cast<InterfaceDecl*>(pd);		
	if (pnt == NULL)
		ReportError::IdentifierNotDeclared(id,LookingForInterface);
}

Decl* NamedType::GetNamedTypeDecl(Scope* sp)
{
	if(!hasChecked)
		Check(sp);
	return namedTypeDecl;
}

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
     Assert(et != NULL);
	 newArrayExpr = NULL;
    (elemType=et)->SetParent(this);

	//system length funciton
	Identifier* pid = new Identifier(loc,"length");
	sysLengthFun = new FnDecl(pid,Type::intType,new List<VarDecl*>); 
}

bool ArrayType::IsEquivalentTo( Type *other )
{
	ArrayType* pA = dynamic_cast<ArrayType*>(other);

	if((pA != NULL) && elemType->IsEquivalentTo(pA->elemType))
		return 1;
	return 0;
}

bool ArrayType::IsCompatibleTo( Type *other,Scope* sp )
{
	ArrayType* pA = dynamic_cast<ArrayType*>(other);
	if((pA != NULL) && elemType->IsEquivalentTo(pA->elemType))
		return 1;
	return 0;
}

bool ArrayType::isSystemLengthFun( char* funName,int actualsNum )
{
	if( funName ==NULL) 
		return 0;
	else
		return strcmp(funName,"length")==0 && actualsNum==0;
}


