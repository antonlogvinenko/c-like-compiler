#pragma once
#include "stdafx.h"


class CodeGen;
class TSymbol;
class TJumpStmt;

class TSymTable
{
	vector< TSymbol * > *Table;
	vector< string * > *StringTable;
public:
	int offset, size;
	TSymTable::TSymTable()
	{
		offset = size = 0;
		Table = new vector< TSymbol * >();
		StringTable = new vector< string * >();
	}
	TSymbol* Find( string );
	TSymbol* FindType( string &  );
	TSymbol* FindVar( string &  );
	vector<TSymbol*> *ShowTable();
	TSymbol *GetLastSym();
	void Add( TSymbol * );
	int AddString( string *  );
	void Print( int  );
	void Init();
	void Output( int = 0 );
	TSymbol* GetElemN( int  );
	void AddTableElems( TSymTable *  );
	void ThrowBackElems( int  );
	void Gen( CodeGen *  );
	void GenGlobal( CodeGen *  );
	void GenStringConst( CodeGen *  , string *  , int  );
	void GenGlobVarDecls( CodeGen *  );
	void GenGlobVarInits( CodeGen *  );
	void CalcSize();
    void InitSize( int  );
	void InitOffset( int  );
	int GetSize();
	int GetOffset();
	int GetNumElems();
	void InverseOffset();
};


class TSymTableStack
{
	vector<TSymTable*> *Table;
public:
	TSymTableStack( TSymTable*  );
	void AddSymTable( TSymTable *  );
	TSymbol* FindGlobal( string &  );
	TSymbol* FindLocal( string &  );
	TSymbol* FindTypeGlobal( string &  );
	TSymbol* FindTypeLocal( string &  );
	TSymbol* FindVarGlobal( string &  );
	TSymTable* ShowLocalTable();
	TSymbol* GetLastSym();
	void Add( TSymbol *  );
	void Push( TSymTable *  );
	void Pop();
	bool GlobalSpace();
};

