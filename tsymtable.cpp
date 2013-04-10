#include "tsymtable.h"
#include "tsymbol.h"
#include "codegen.h"
#include "tsyntobj.h"


int TSymTable::GetSize()
{
	return size;
}
int TSymTable::GetOffset()
{
	return offset;
}
int TSymTable::GetNumElems()
{
	return Table->size();
}
TSymbol *TSymTable::Find( string name )
{
	for( int i = 0 ; i < Table->size() ; ++i )
		if ( ((*Table)[i]->funcname == name)||((*Table)[i]->varname == name)||
			((*Table)[i]->simpletypename == name)||((*Table)[i]->StrucTypename == name) ||
			((*Table)[i]->aliastypename == name) )
			return (*Table)[i];

	return NULL;
}
void TSymTable::Init()
{
	Table->push_back( new TypeInteger() );
	Table->push_back( new TypeFloat() );
	Table->push_back( new TypeString() );

	Table->push_back( new TSymFunc( string( "printf" ) , (*Table)[0] ) );
	(*Table)[3]->PutBody( new TBlockStmt() );
	Table->push_back( new TSymFunc( string( "scanf" ) , (*Table)[0] ) );
	(*Table)[4]->PutBody( new TBlockStmt() );
}
void TSymTable::Output( int level )
{
	cout << "String Constants:\n";
	for ( int i = 0 ; i < StringTable->size() ; ++i )
	{
		cout << "str" << i << "  is  ";
		cout << *(*StringTable)[i] << "\n";
	}
	for ( int i = 5 ; i < Table->size() ; ++i )
		(*Table)[i]->FullPrint( level );
}
TSymbol *TSymTable::FindType( string &name )
{
	for ( int i = 0 ; i < Table->size() ; ++i )
		if (   ( (*Table)[i]->simpletypename == name ) ||
			( (*Table)[i]->StrucTypename == name ) ||
			( (*Table)[i]->aliastypename == name)   )
			return (*Table)[i];
	return NULL;
}
TSymbol *TSymTable::FindVar( string &name )
{
	for ( int i = 0 ; i < Table->size(); ++i )
		if ( (*Table)[i]->varname == name )
			return (*Table)[i];
	return NULL;
}
void TSymTable::Add( TSymbol* add )
{
	Table->push_back( add );
}
int TSymTable::AddString( string *str )
{
	StringTable->push_back( str );
	return StringTable->size() - 1;
	return 0;
}
vector< TSymbol * > *TSymTable::ShowTable()
{
	return Table;
}
void TSymTable::Print( int level = 0 )
{
	cout << "\n";
	Tab( level );
	cout << "Size of table: " << size << "\n";
	Tab( level );
	cout << "Offset of table: " << offset << "\n";

	for ( int i = 0 ; i<Table->size() ; ++i )
		(*Table)[i]->FullPrint( level );
}
TSymbol *TSymTable::GetElemN( int level )
{
	return (*Table)[level];
}
TSymbol *TSymTable::GetLastSym()
{
	return (*Table)[Table->size()-1];
}
void TSymTable::Gen( CodeGen *cg )
{
	for ( int i = 0 ; i < Table->size() ; ++i )
		(*Table)[i]->Gen( cg );
}
//GLOBAL TABLE THAT IS BEING GENERATED
void TSymTable::GenGlobal( CodeGen *cg )
{
	cg->GenStart();
	GenGlobVarDecls( cg );
	cg->Flush();
	cg->GenMiddle();

	cg->Gen( PROC , str( "_main" ) );
	GenGlobVarInits( cg );
	if ( cg->NeedOptim() )
		cg->WatchPeepHole();
	cg->Gen( CALL , str( "f_main" ) );
	cg->Gen( RET );
	cg->Gen( ENDP , str( "_main" ) );
	cg->Flush();

	//generating only functions, not global variables
	for ( int i = 5 ; i < Table->size() ; ++i )
		if ( (*Table)[i]->IsFunc() )
		{
			(*Table)[i]->Gen( cg );
			if ( cg->NeedOptim() )
				cg->WatchPeepHole();
			cg->Flush();
		}
	cg->GenFinish();
}
void TSymTable::GenStringConst( CodeGen *cg , string *convert , int index )
{
	string s( "" );
	for ( int i = 0 ; i < convert->length() ; ++i )
		s += cg->IntToString( (*convert)[i] ) + ", ";
	s += "0";
	cg->Gen( DB , mem( "str" + cg->IntToString( index ) ) , str( s ) );
}
void TSymTable::GenGlobVarDecls( CodeGen *cg )
{
	/*generate variables for met string constants*/
	cg->Gen( Com, str( "STRING CONSTANTS:" ) );
	for ( int i = 0 ; i < StringTable->size() ; ++i )
		GenStringConst( cg , (*StringTable)[i] , i );
	
	cg->Gen( Com , str( "GLOBAL VARIABLES:" ) );
	/*Generate global variables*/
	for ( int i = 0 ; i < Table->size() ; ++i )
		if ( (*Table)[i]->IsVar() )
			(*Table)[i]->Gen( cg );
}
void TSymTable::GenGlobVarInits( CodeGen *cg )
{
	for ( int i = 0 ; i < Table->size() ; ++i )
		if ( (*Table)[i]->IsVar() )
			if ( (*Table)[i]->GetRealType()->IsSimpleType() )
			(*Table)[i]->GenGlobVarInit( cg );
}
void  TSymTable::CalcSize()
{
	size = 0;
	for ( int i = 0 ; i < Table->size() ; ++i )
		if ( (*Table)[i]->IsVar() )
		{
			(*Table)[i]->InitOffset( size );
			size += (*Table)[i]->GetSize();
		}
}
void TSymTable::InitOffset( int off )
{
	offset = off;
}
void TSymTable::InitSize( int s )
{
    size = s;
}
void TSymTable::InverseOffset()
{
	if ( !Table->size() )
		return;

	int counter = 0;
	//8 is selected because there are returning value
	//and saved ebp between arguments and where new ebp references
	for ( int i = Table->size() - 1; i >= 0 ; --i )
		if ( (*Table)[i]->IsVar() )
		{
			counter += (*Table)[i]->GetSize();
            (*Table)[i]->InitOffset( counter );
		}
}
void TSymTable::AddTableElems( TSymTable *tbl )
{
	for( int i = 0 ; i < tbl->GetNumElems() ; ++i )
		Table->push_back( tbl->GetElemN( i ) );
}
void TSymTable::ThrowBackElems( int number )
{
    if ( Table->size() )
		Table->erase( Table->begin() , Table->begin() + number );
}


TSymTableStack::TSymTableStack( TSymTable *Tab )
{
	Table = new vector<TSymTable*>();
	Table->push_back( Tab );
}
void TSymTableStack::AddSymTable( TSymTable *Tab )
{
	Table->push_back( Tab );
}
TSymbol *TSymTableStack::FindGlobal( string &name )
{
	TSymbol *found;
	for ( int i = Table->size()-1; i>-1; --i )
		if (  ( found = (*Table)[i]->Find( name ) ) != NULL  )
			return found;
	return NULL;                
}
TSymbol *TSymTableStack::FindLocal( string &name )
{
	return (*Table)[Table->size()-1]->Find( name );
}
TSymbol *TSymTableStack::FindTypeGlobal( string &name )
{
	TSymbol *found;
	for( int i = Table->size() - 1 ; i > -1 ; --i )
		if (  ( found = ( *Table )[i]->FindType( name ) ) != NULL  )
			return found;
	return NULL;
}
TSymbol *TSymTableStack::FindTypeLocal( string &name )
{
	return (*Table)[Table->size()-1]->FindType( name );
}
TSymbol *TSymTableStack::FindVarGlobal( string &name )
{
	TSymbol *found;
	for( int i = Table->size()-1 ; i > -1 ; --i )
		if (   ( found=(*Table)[i]->FindVar( name ) ) != NULL   )
			return found;
	return NULL;
}
void TSymTableStack::Add( TSymbol *add )
{
	(*Table)[Table->size()-1]->Add( add );
}

	
TSymTable *TSymTableStack::ShowLocalTable()
{
	return (*Table)[Table->size() - 1];
}
void TSymTableStack::Push( TSymTable *newtop )
{
	Table->push_back( newtop );
}
void TSymTableStack::Pop()
{	
	Table->pop_back();
}
TSymbol *TSymTableStack::GetLastSym()
{
	return (*Table)[Table->size() - 1]->GetLastSym();
}
bool TSymTableStack::GlobalSpace()
{
	return ( Table->size() == 1 );
}