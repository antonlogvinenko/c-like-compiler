#pragma once

#include <vector>
#include <map>
#include <string>
#include "scantools.h"

using namespace std;

class TSymbol;

void Tab( int level = 0 );

class LoopInfo
{  
	int loops;
    public:
        LoopInfo();
        void LoopIn();
        void LoopOut();
        bool IsInLoop();
};

class Operations
{
	vector<Type> Binary[6];
	Type Unary[5];
public:
	Operations();
	bool IsBinOnLev( Type  , int  );
	bool IsUnary( Type  );
};

bool EqualArrays( TSymbol *  , TSymbol *  );