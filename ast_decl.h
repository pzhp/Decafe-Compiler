/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp3: You will need to extend the Decl classes to implement 
 * semantic processing including detection of declaration conflicts 
 * and managing scoping issues.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "list.h"
#include "hashtable.h"
#include "errors.h"

#include "ast_type.h"
#include "ast_stmt.h"
#include "tac.h"
#include "codegen.h"

class Type;
class NamedType;
class Identifier;
class Stmt;

class Scope;
class VarDecl;
class FnDecl;

class Decl : public Node 
{
public:
	Identifier *id;
	Scope* scope; 
	int memsize;

public:
	Decl(Identifier *name);
	~Decl();
	friend ostream& operator<<(ostream& out, Decl *d) { return out << d->id; }
	

	virtual void BuildScope(Scope* parent);  //at same time check the same name
	virtual void Check()=0; 
	
	virtual bool isNameEqual(char* name){
		return strcmp(id->name,name)==0;
	}
	char* GetName(){
		return id->name;
	}

	virtual VarDecl* LookupVarDeclInNamedClass(char* varName){
		return NULL;
	}
	virtual FnDecl* LookupFnInNamedType(char* fnname){
		return NULL;
	}	

	int GetMemSize(){return memsize;}
	virtual void Emit(CodeGenerator* cg){}
};

//string, array, class only occupy 4 bytes, which point to its object
class VarDecl : public Decl 
{
public:
	Type *type;

	Location* memloc;  //its content pointer to alloc address 
	int offsetVar;     //bytes, mainly use in stack ,class 

	void SetVarOffset(int off){ 
		offsetVar = off;
	}
	int GetVarOffset(){ 
		return offsetVar;
	}

public:
	VarDecl(Identifier *name, Type *type);
	
	void Check();
	VarDecl* LookupVarDeclInNamedClass(char* varName)
	{ 
		return isNameEqual(varName)? this : NULL;
	}
	void Emit(CodeGenerator* cg) //use in stack
	{
		memloc = cg->GenLocalVar(GetName(),CodeGenerator::VarSize);
	}

	void Emit_GlobalVar(CodeGenerator* cg) // use for global Var
	{
		memloc = cg->GenGlobalVar(GetName(),CodeGenerator::VarSize); 
	}
};

class ClassDecl : public Decl 
{
public:
	List<Decl*> *members;
	NamedType *extends;
	List<NamedType*> *implements; 
	
	List<FnDecl*>* VTableList;     // manage virtual function by order
	List<VarDecl*>* VarOffsetList; // record the var offset,keep the order from parent to here
	bool hadPreHandle;   
	string VTableLabel;           //use when "new express", not use in call (there ,just lookup first 4bytes in object)

public:
	ClassDecl(Identifier *name, NamedType *extends, List<NamedType*> *implements, List<Decl*> *members);
	
	void BuildScope(Scope* parent);
	void Check();		
	VarDecl* LookupVarDeclInNamedClass(char* varName);
	FnDecl* LookupFnInNamedType(char* fnname);

	// emit function and VTable
	void Emit(CodeGenerator* cg);	
	//generate in VTable order and variable offset
	void PreEmitOnOrderOfMembers();

private:
	void EmitFunctionAndVTable(CodeGenerator* cg);
};

class InterfaceDecl : public Decl 
{
  public:
    List<Decl*> *members;	
	List<FnDecl*> virtualTable; //use for VTable
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
	
	void BuildScope(Scope* parent);
	void Check();
	FnDecl* LookupFnInNamedType(char* fnname);

	void Emit(CodeGenerator* cg) 
	{
		return; // to add 
	}
};

class FnDecl : public Decl 
{
public:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;

	string typeName; 
	string funLabel;  // assigne in check()	
	int methodOffset; //offset use in virtual,nth not bytes, assign in class PreEmitOnOrderOfMembers
    
public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
	bool IsInterfaceEqual(Decl* fnDecl); // all the same 
	bool IsCallEqual(Decl* fnDecl);      // every para is A<=B
	
	void BuildScope(Scope* parent);
	void Check();
	FnDecl* LookupFnInNamedType(char* fnname){
		return isNameEqual(fnname)? this : NULL;
	}

	bool isMethod();	
	void Emit(CodeGenerator* cg);
	
	void SetMethodOffset(int index){
		methodOffset = index;
	}
	int GetMethodOffset(){
		return methodOffset;
	}
};

class Scope
{	
public:
	Scope* Parent;	
	Hashtable<Decl*>  SymTable;

	ClassDecl* includedByClass;          //used for this ,class's scope != NULL 
	InterfaceDecl* includedByInterface;  //

	Scope() {Parent = NULL;includedByClass=NULL; includedByInterface = NULL;}
	Scope(Scope* pS) {Parent = pS;includedByClass = NULL; includedByInterface =NULL;}
	~Scope(){}
	void MergeScope( Scope** sp );

	void SetParentScope(Scope* sp)
	{  Parent = sp;  }

	void AddToCurSymTable(char* key,Decl* pVar)
	{
		Decl* pDecl = SymTable.Lookup(key);
		if (pDecl!=NULL)
			ReportError::DeclConflict(pVar,pDecl);

		SymTable.Enter(key,pVar,0);
	}

	void RemoveFromCurSymTable(char* key, Decl* pValue)
	{
		SymTable.Remove(key,pValue);
	}


	/******** functions for lookup********/
	Decl* LookupInCurTable(char* key);	
	Decl* LookupInAllTable(char* key);  //scope link

	VarDecl* LookupVarInTable(char* key);
	ClassDecl* LookupClassInTable(char* key);
	FnDecl* LookupFunInTable(char* key);
	InterfaceDecl* LookupInterfaceInTable(char* key);
	Decl* LookupTypeDeclInTable(char* key);// include class and interface

	ClassDecl* LookupNearestClassofThis();//lookup nearest classDecl including current Node in scope
//	InterfaceDecl* LookupInterfaceofThis();//lookup nearest interfaceDecl including current Node in scope
};

#endif
