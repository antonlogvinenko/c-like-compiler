#pragma once
#include "stdafx.h"
#include "tsymtable.h"
#include "codegen.h"

class TExpr;
class TStatement;
class TBlockStmt;


class TSymbol
{
public:
	string
		varname,
		funcname,
		simpletypename,
		StrucTypename,
		aliastypename;
	TSymTable *argtable;
	TSymbol *type;
	TStatement *body;
	
	bool IsVar();
	bool IsArray();
	bool IsReference();
	bool IsStrucType();
	bool IsAliasType();
	bool IsSimpleType();
	bool IsAlSimpleType();
	bool IsAlStrucType();
	bool IsFunc();
	bool IsType();
	bool IsFloat();
	bool IsString();
	bool IsInt();
	bool HasBody();
	virtual TExpr* GetSizeExpr();
	virtual bool operator!=( TSymbol  );
	virtual void ShortPrint();
	virtual void FullPrint( int = 0 );
	virtual bool FindArg( string , TSymbol *  );
	virtual void AddArg( TSymbol *  );
	virtual void PutBody( TBlockStmt *  );
	virtual TSymbol* GetArrayElemType();
	virtual TSymbol* GetReferType();
	virtual TSymbol* TypeByName( string &  );
	TSymbol* GetRealType();
	TSymbol* GetType();
	virtual void Gen( CodeGen * ){}
	virtual void CalcTableSizes();
	virtual void InitOffset( int  ){}
	virtual void GenGlobVarDecl( CodeGen *  ){};
	virtual void GenGlobVarInit( CodeGen *  ){};
	virtual TSymbol *FindMember( string  )
	{
		return NULL;
	}
	virtual int GetSize()
	{
		return 0;
	}
	virtual void SetGlobal(){}
	virtual void SetLocal(){}
	virtual void SetArgument(){}
	virtual bool IsGlobal()
	{
		return 0;
	}
	virtual bool IsLocal()
	{
		return 0;
	}
	virtual bool IsArgument()
	{
		return 0;
	}
	virtual int GetRelOffset()
	{
		return 0;
	}
	virtual int GetFullOffset()
	{
		return 0;
	}
};

typedef map < string , TSymbol* > enumer;

class TSymVar:public TSymbol
{
	TExpr *value;
	string scope;
	int offset;
	TSymTable *reftotable;
public:
	TSymVar( string &  , TSymbol * , TSymTableStack * , TExpr*  = NULL );
	void FullPrint( int  );
	bool operator!=( TSymbol  );
	void PutValue( TExpr *  );
	void Gen( CodeGen *  );
	void GenGlobVarDecl( CodeGen *  );	
	void GenLocVarDecl( CodeGen *  );
	void GenGlobVarInit( CodeGen *  );
	void InitOffset( int  );
	int GetSize();
	int GetRelOffset();
	int GetFullOffset();
	string Comment();

	void SetArgument();
	void SetGlobal();
	void SetLocal();
	bool IsGlobal();
	bool IsLocal();
	bool IsArgument();
};

class TSymFunc:public TSymbol
{
public:
	TSymFunc( string &  , TSymbol *   );
	void PutBody( TBlockStmt *  );
	void FullPrint( int  );
	bool FindArg( string  );
	void AddArg( TSymbol *  );
	int CalcArgSize();
	void CalcTableSizes();
	void Gen( CodeGen *  );
};

class TSymType:public TSymbol
{
public:
	int size;
	int GetSize();
};

class TypeInteger:public TSymType
{
public:
	TypeInteger();
	void ShortPrint();
	void FullPrint( int  );	
};

class TypeFloat:public TSymType
{
public:
	TypeFloat();
	void ShortPrint();
	void FullPrint( int  );
	
};

class TypeString:public TSymType
{
public:
	TypeString();
};

class TypeArray:public TSymType
{    
	TExpr *sizeexpr;
public:
	TypeArray( TExpr *  , TSymbol *  );
	TSymbol* GetType();
	void FullPrint( int  );
	void ShortPrint();
	TSymbol* GetArrayElemType();
	TExpr* GetSizeExpr();
	bool IsArray();
};

class TypeStruct:public TSymType
{
public:
	TSymTable *memtable;
	TypeStruct( TSymTable *  , string &  );
	void ShortPrint();
	void FullPrint( int  );
	TSymbol *FindMember( string  );
};

class TypeRefer:public TSymType
{
public:
	TypeRefer( TSymbol *  );
	TSymbol* GetReferType();
	void ShortPrint();
	void FullPrint( int  );
};

class TypeAlias:public TSymType
{
public:
	TypeAlias( TSymbol *  , string  );

	void ShortPrint();
	void FullPrint( int  );
	int GetSize();
};