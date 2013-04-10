#pragma once
#include "stdafx.h"
#include "scantools.h"
#include "tsymbol.h"
#include "tsyntobj.h"
#include "tsymtable.h"
#include "scanner.h"
#include "parsetools.h"


class Parser
{
	bool optimizing;
	Scanner &scanner;
	Operations ops;
	LoopInfo loop, cases;
	TSymTableStack *stack;
	TSymTable *GlobSymTable;
public:
	Parser( Scanner& s , TSymTable *  , bool  );
    bool EqualSignats( TSymbol *  , TSymbol *  );

	void ParseJumpStmt( TBlockStmt *  );
    void ParseWhileStmt( TBlockStmt *  );
	void ParseForStmt( TBlockStmt *  );
    void ParseIfStmt( TBlockStmt *  );
	void ParseSwitchStmt( TBlockStmt *  );
    void ParseStmt( TBlockStmt *  );

	TBlockStmt* ParseBlock( TSymTable * = NULL );
	void ParseListArgs( TSymFunc *  );
	TSymbol* ParseFuncDecl( string  , TSymbol *  );
    TSymbol* ParseArrayType( TSymbol *  );
    void ParseVarDecl( TSymbol *  , string &  );
	void ParseDecl( TSymbol *  );
	void ParseTypedefDecl();
	TSymTable* ParseStructBody();
	void ParseStructDecl( string = "" );
	void ParseListDecl();
	void ParseProgram();

	void FoldTypeCast( TExpr *&  );
	void FoldUnaryOp( TExpr *&  );
	void FoldBinaryOp( TExpr *&  );

	TExpr* ParseExpr();
	TExpr* ParseAssignExpr();
	TExpr* ParseBinExpr( int level = 0 );
	TExpr* ParseUnaryExpr();
	TExpr* ParsePostfExpr();
	TExpr* ParsePrimExpr();
};