#include "parsetools.h"
#include "tsymbol.h"
#include "tsyntobj.h"


void Tab( int level )
{
	for( int i = 0 ; i < level ; ++i )
		cout << '\t';
}
LoopInfo::LoopInfo()
	:loops( 0 )
{}
void LoopInfo::LoopIn()
{
	++loops;	
}
void LoopInfo::LoopOut()
{
	if ( loops )
		--loops;
}
bool LoopInfo::IsInLoop()
{
	return loops;
}


Operations::Operations()
{
	Binary[0].push_back( oor );
	Binary[1].push_back( oand );

	Binary[2].push_back( oequal );
	Binary[2].push_back( onequal );

	Binary[3].push_back( ogreat );
	Binary[3].push_back( oless );	
	Binary[3].push_back( oegreat );
	Binary[3].push_back( oeless );

	Binary[4].push_back( oplus );
	Binary[4].push_back( ominus );

	Binary[5].push_back( omul );
	Binary[5].push_back( odiv );

	Unary[0] = onot;
	Unary[1] = oincr;	
	Unary[2] = odecr;
	Unary[3] = oplus;
	Unary[4] = ominus; 
}
bool Operations::IsBinOnLev( Type type , int level )
{
	level %= 6;

	for ( int i = 0 ; i < Binary[level].size() ; ++i )
		if ( type == Binary[level][i] )
			return 1;
	return 0;
}
bool Operations::IsUnary( Type type )
{
	for ( int i = 0 ; i < 5 ; ++i )
		if ( Unary[i] == type )
			return 1;
	return 0;
}


bool EqualArrays( TSymbol *a1 , TSymbol *a2 )
{            
	if ( !a1->IsArray() || !a2->IsArray() )
	{
		if ( a1->IsArray() || a2->IsArray() )
			return 0;
		if ( a1->GetRealType() != a2->GetRealType() )
			return 0;
		return 1;
	}
	if ( a1->GetSizeExpr()->GetInt() != a2->GetSizeExpr()->GetInt() )
		return 0;
	return EqualArrays( a1->type , a2->type );
}
