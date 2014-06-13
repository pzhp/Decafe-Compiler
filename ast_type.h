/* File: ast_type.h
* ----------------
* In our parse tree, Type nodes are used to represent and
* store type information. The base Type class is used
* for built-in types, the NamedType for classes and interfaces,
* and the ArrayType for arrays of other types.  
*
* pp3: You will need to extend the Type classes to implement
* the type system and rules for type equivalency and compatibility.
*/

#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"

#include <iostream>
using namespace std;

class NewArrayExpr;
class Decl;
class FnDecl;

class Type : public Node 
{
public:
	char *typeName;

public :
	static Type *intType, *doubleType, *boolType, *voidType,
		*nullType, *stringType, *errorType;  // null<= ***<= error

	Type(yyltype loc) : Node(loc) { typeName = NULL;}
	Type(const char *str);

	virtual void PrintToStream(ostream& out) { out << typeName; }
	friend ostream& operator<<(ostream& out, Type *t) { t->PrintToStream(out); return out; }

	virtual bool IsEquivalentTo(Type *other);
	virtual bool IsCompatibleTo(Type *other,Scope* sp);//this<=other
	virtual bool Check(Scope* sp){ return 1;}

	virtual Decl* GetNamedTypeDecl(Scope* sp){return NULL;}
};

class NamedType : public Type 
{
protected:
	Identifier *id;
	Decl * namedTypeDecl;   // class or interface
	bool   hasChecked;

public:
	NamedType(Identifier *i);
	void PrintToStream(ostream& out) { out << id; }

	bool IsEquivalentTo(Type *other);
	bool IsCompatibleTo(Type *other,Scope* sp);
	bool Check(Scope* sp);
	void CheckisClass(Scope*sp);     //used for class extend
	void CheckisInterface(Scope*sp); // used for class implements	

	Decl* GetNamedTypeDecl(Scope* sp);
};

class ArrayType : public Type 
{
public:
	Type *elemType;
	NewArrayExpr* newArrayExpr;
	FnDecl* sysLengthFun; // in fact,just complement in assembly by simple instrusions, not call

public:
	ArrayType(yyltype loc, Type *elemType);

	void PrintToStream(ostream& out) { out << elemType << "[]"; }

	bool IsEquivalentTo(Type *other);
	bool IsCompatibleTo(Type *other,Scope* sp);
	bool isSystemLengthFun(char* funName,int actualsNum);

	bool Check(Scope* sp) { return elemType->Check(sp);}
	FnDecl* GetSysLengthFn(){ return sysLengthFun;}
};

#endif
