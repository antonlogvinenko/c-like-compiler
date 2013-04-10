#pragma once
#include "stdafx.h"
#include "scantools.h"
#include "tsymTable.h"
#include "parsetools.h"
#include "tsymbol.h"


class TSymbol;
class TSymTable;
class CodeGen;

void Tab( int  );

class TSyntaxObject
{
public:
	string source;
	virtual void Print( int  ) = 0;
	virtual bool IsExpr() = 0;
	virtual void Gen( CodeGen *  ) = 0;
	virtual bool HasBlock() = 0;
	virtual bool HasBreaks() = 0;
	virtual bool HasContinues() = 0;
	virtual bool IsBlock() = 0;
	virtual bool CleanupNeeded() = 0;
	virtual void CalcTableSizes( int  ) = 0;
	virtual void TypeCheck( TSymTable *  , Position  , bool = 0 ) = 0;
	virtual string Comment() = 0;
};

class TExpr:public TSyntaxObject
{
public:
	vector< TExpr * > *ListExpr;
	bool islvalue;
	TSymbol *exprtype;

	Type type;
	bool IsExpr();

	virtual void AddExpr( TExpr *  ){}
	virtual void TypeCheck( TSymTable *  , Position  , bool  = 0 ){}
	virtual void Gen( CodeGen *  ){}
	virtual void GenAddr( CodeGen *  ){}
	virtual void GenAddrHelper( CodeGen *  ){}
	TSymbol* GetType();
	TSymbol* GetRealType();
	TSymbol* GetRefdObjType();
	string GetSource()
	{
		return source;
	}
	virtual bool IsListExpr()
	{
		return 0;
	}
	virtual TSymbol *GetFuncType()
	{
		return NULL;
	}
	virtual string GetFuncName()
	{
		return "";
	}
	virtual TExpr *GetIndex()
	{
		return NULL;
	}
	virtual bool CastNeeded()
	{
		return 0;
	}
	virtual TExpr *GetLeftPart()
	{
		return NULL;
	}
	virtual TExpr *GetRightPart()
	{
		return NULL;
	}
	virtual void PutStringNum( int  )
	{
	}
	virtual string *GetString()
	{
		return NULL;
	}
	virtual bool IsStringConst()
	{
		return 0;
	}
	virtual string Comment()
	{
		return "";
	}
	virtual bool IsConstExpr()
	{
		return 0;
	}
	virtual bool IsEmptyExpr()
	{
		return 0;
	}
	virtual bool IsFunccallOp()
	{
		return 0;
	}
	virtual bool IsExtractArrayOp()
	{
		return 0;
	}
	virtual bool IsExtractStructOp()
	{
		return 0;
	}
	virtual bool IsExtractOp()
	{
		return 0;
	}
	virtual bool IsTypeCast()
	{
		return 0;
	}
	virtual bool IsBinaryOp()
	{
		return 0;
	}
	virtual bool IsUnaryOp()
	{
		return 0;
	}
	virtual int GetInt()
	{
		return 0;
	}
	virtual float GetFloat()
	{
		return 0;
	}
	virtual bool IsAlive()
	{
		return 0;
	}
	bool HasBlock()
	{
		return 0;
	}
	bool HasBreaks()
	{
		return 0;
	}
	bool HasContinues()
	{
		return 0;
	}
	bool IsBlock()
	{
		return 0;
	}
	virtual bool ArgsAreConsts()
	{
		return 0;
	}
	virtual bool CleanupNeeded()
	{
		return 1;
	}
	virtual void CalcTableSizes( int  )
	{}
};

class TConstExpr:public TExpr
{
public:
	float f_value;
	int i_value;
	string s_value;

	void Gen( CodeGen *  );
	TConstExpr( const string &  , float  , TSymbol *   );
	TConstExpr( const string &  , int  , TSymbol *  );
	TConstExpr( const string &  , string  , TSymbol *  );

	int GetInt();
	float GetFloat();
	string *GetString();
	bool IsStringConst();
	void PutStringNum( int  );
	string Comment();

	void Print( int = 0 );
	bool IsConstExpr();
};

class TVarExpr:public TExpr
{
public:
	TVarExpr( string  , TSymbol *  );
	void Print( int = 0 );
	string Comment();
	void Gen( CodeGen *  );
	void GenAddr( CodeGen *  );
};

class TTypeCast:public TExpr
{
public:
	TExpr *expression;
	TTypeCast( TSymbol *  , TExpr  * );
	void TypeCheck( TSymTable *  , Position  , bool = 0 );
	void Print( int = 0 );
	void Gen( CodeGen *  );
	bool CastNeeded();
	bool ArgsAreConsts()
	{
		return expression->IsConstExpr();
	}
	bool IsConstExpr()
	{
		return 0;
	}
	bool IsAlive();
	bool IsTypeCast()
	{
		return 1;
	}
	int GetInt();
	float GetFloat();
	string Comment();
};

class TEmptyExpr:public TExpr
{
public:
	TEmptyExpr();
	void Print( int  );
	bool IsEmptyExpr();
	void Gen( CodeGen *  );
};

class TFunccallOp:public TExpr
{
	TExpr
		*arglist,
		*funcname;
public:
	TFunccallOp( TExpr *  , TExpr *  );
	bool IsFunccallOp();
	string GetFuncName();
	TSymbol *GetFuncType();
	void TypeCheck( TSymTable *  , Position  , bool = 0 );
	void CheckPrintf( TSymTable *  , Position  );
	void CheckScanf( TSymTable *  , Position  );
	void Print( int = 0 );
	void Gen( CodeGen *  );
	void PushArgs( CodeGen *  );
	void PopArgs( CodeGen *  );
	void GenPrintf( CodeGen *  );
	void GenScanf( CodeGen *  );
	bool IsAlive();
	string Comment();
};

class TExtractOp:public TExpr
{
public:
	TExpr
		*index,
		*leftpart;

	TExtractOp( TExpr *  , TExpr *  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 ){}
	void Print( int = 0 );
	bool IsExtractOp();
	void Gen( CodeGen *  );
	TExpr* GetIndex();
	TExpr* GetLeftPart();
};

class TExtractArrayOp:public TExtractOp
{
public:
	TExtractArrayOp( TExpr *  , TExpr *  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 );
	bool IsExtractArrayOp();
	string Comment();
	bool IsAlive();
	void GenAddr( CodeGen *  );
	void GenAddrHelper( CodeGen *  );
};

class TExtractStructOp:public TExtractOp
{
public:
	TExtractStructOp( TExpr *  , TExpr *  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 );
	bool IsExtractStructOp();
	string Comment();
	bool IsAlive();
	void GenAddr( CodeGen * );
	void GenAddrHelper( CodeGen *  );
};

class TAssignOp:public TExpr
{
	TExpr
		*left,
		*right;

public:
	TAssignOp( Type  , string  , TExpr *  , TExpr *  );
	void TypeCheck( TSymTable *  , Position  , bool  );
	bool IsAlive();
	void Print( int = 0 );
	void Gen( CodeGen *  );
	string Comment();
};

class TBinaryOp:public TExpr
{
	TExpr
		*left,
		*right;
public:
	TBinaryOp( Type  , string  , TExpr *  , TExpr *  );
	void TypeCheck( TSymTable *  , Position  , bool  );
	void Print( int = 0 );
	void Gen( CodeGen *  );
	TExpr *GetLeftPart();
	TExpr *GetRightPart();
	bool IsAlive();
	bool IsBinaryOp()
	{
		return 1;
	}
	bool ArgsAreConsts()
	{
		return left->IsConstExpr() && right->IsConstExpr();
	}
	string Comment();
};

class TUnaryOp:public TExpr
{
	TExpr
		*right,
		*left;
public:
	TUnaryOp( string  , Type  , TExpr *  );
	TUnaryOp( string  , TExpr * , Type  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 );
	void Gen( CodeGen *  );
	void GenAddr( CodeGen *  );
	void Print( int = 0 );
	bool IsAlive();
	bool ArgsAreConsts()
	{
		if ( right )
			return right->IsConstExpr();
		return left->IsConstExpr();
	}
	bool IsUnaryOp()
	{
		return 1;
	}
	int GetInt();
	float GetFloat();
	string Comment();
	TExpr *GetLeftPart();
	TExpr *GetRightPart();
};

class TListExpr:public TExpr
{
public:
	TListExpr( TExpr *  , TExpr *  );
	TListExpr( TExpr *  );
	TListExpr();
	void TypeCheck( TSymTable *  , Position  , bool = 0 );
	void Gen( CodeGen *  );
	void GenAddr( CodeGen *  );
	void GenHelper( CodeGen *  );
	string Comment();
	bool IsListExpr();
	void AddExpr( TExpr * );
	void Print( int = 0 );
	bool IsAlive();
};

class TStatement:public TSyntaxObject
{
	public:
	bool breaks, continues;
	vector<TSyntaxObject*> syntlist;
	TSymTable *blocktable;
	virtual void Gen( CodeGen *  ){}
	bool IsExpr();
	virtual string Comment()
	{
		return "";
	}
	virtual bool IsEmptyStmt()
	{
		return 0;
	}
	bool HasBlock()
	{
		return 0;
	}
	virtual bool HasBreaks()
	{
		return false;
	}
	virtual bool HasContinues()
	{
		return false;
	}
	bool IsBlock()
	{
		return 0;
	}
	virtual void CalcTableSizes( int  )
	{}
	virtual bool CleanupNeeded()
	{
		return 0;
	}
	virtual void TypeCheck( TSymTable *  , Position  , bool = 0 ){}
};

class TBlockStmt:public TStatement
{
public:	
	TBlockStmt();
	TSymTable *ShowTable();
	void AddStmt( TSyntaxObject *  );
	void Print( int  );
	void Gen( CodeGen *  );
	void PushLocalVars( CodeGen *  );
	void PopLocalVars( CodeGen *  );
	virtual bool HasBreaks()
	{
		return breaks;
	}
	virtual bool HasContinues()
	{
		return continues;
	}
	bool IsBlock()
	{
		return 1;
	}
	void CalcTableSizes( int  );
};

class TEmptyStmt:public TStatement
{
public:
	TEmptyStmt();
	bool IsEmptyStmt()
	{
		return 1;
	}
	void Print( int  );
	void Gen( CodeGen *  );
};

class TIfStmt:public TStatement
{
public:
	TStatement
		*trueblock,
		*falseblock;

	TExpr *condition;
	TIfStmt( TExpr *  );
	void AddTrueBlock( TStatement *  );
	void AddFalseBlock( TStatement *  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 ) ;
	string Comment();
	virtual bool HasBreaks()
	{
		return breaks;
	}
	virtual bool HasContinues()
	{
		return continues;
	}
	bool HasBlock()
	{
		return 1;
	}
	void Gen( CodeGen *  );
	void Print( int = 0 );
	void CalcTableSizes( int  );
};

class TWhileStmt:public TStatement
{
public:
	TExpr *condition;
	TStatement *block;
	TWhileStmt( TExpr *  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 ) ;
	void Gen( CodeGen *  );
	string Comment();
	void Print( int = 0 );
	void AddBlock( TStatement *  );
	bool HasBlock()
	{
		return 1;
	}
	void CalcTableSizes( int  );
};

class TForStmt:public TStatement
{
public:
	TExpr *condition;
	TStatement *block;
	TForStmt( TExpr *  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 ) ;
	string Comment();
	void AddBlock( TStatement *  );
	bool HasBlock()
	{
		return 1;
	}
	void Print( int = 0 );
	void Gen( CodeGen *  );
	void CalcTableSizes( int  );
};

class TJumpStmt:public TStatement
{
	int poponbreak;
public:
	string funcname;
	TSymTable *localtable;
	TExpr *value;
	TJumpStmt( string  , TSymTable *  , TSymTableStack *  , TExpr * = NULL );
	bool HasBreaks()
	{
		return "break" == source;
	}
	bool HasContinues()
	{
		return "continue" == source;
	}
	void Gen( CodeGen *  );
	void Print( int = 0 );
};
struct CaseStruct
{
	CaseStruct( TExpr * e, TBlockStmt * b = NULL )
		:expr( e ), block( b )
	{}
	TExpr *expr;
	TBlockStmt *block;
};
class TSwitchStmt:public TStatement
{
public:
	int defaultN;
	TExpr *switchexpr;
	vector< CaseStruct * > *caselist;
	TSwitchStmt( TExpr *  );
	void Gen( CodeGen *  );
	void Print( int = 0 );
	void Init( vector< CaseStruct * > *  , int  );
	void CalcTableSizes( int  );
	void TypeCheck( TSymTable *  , Position  , bool = 0 );
	bool HasBlock()
	{
		return caselist->size();
	}
};
void CreateTypeCast( TExpr *&  , TSymbol *  , bool  );
