#include "tsymbol.h"
#include "tsyntobj.h"
#include "tsymtable.h"


bool TSymbol::HasBody()
{
	if ( body )
		return body->source != "empty";
	return NULL;
}
TExpr *TSymbol::GetSizeExpr()
{
	return NULL;
}
bool TSymbol::operator!=(TSymbol )
{
	return 0;
}
void TSymbol::ShortPrint()
{}
void TSymbol::FullPrint( int  )
{}
bool TSymbol::FindArg( string , TSymbol *  )
{
	return NULL;
}
void TSymbol::AddArg( TSymbol *  )
{}
void TSymbol::PutBody( TBlockStmt *  )
{}
TSymbol *TSymbol::GetArrayElemType()
{
	return NULL;
}
TSymbol *TSymbol::GetReferType()
{
	return NULL;
}
TSymbol *TSymbol::TypeByName( string &  )
{
	return NULL;
}
bool TSymbol::IsVar()
{
	return varname != "";
}
bool TSymbol::IsArray()
{
	return aliastypename == "0array";
}
bool TSymbol::IsReference()
{
	return aliastypename == "0reference";
}
bool TSymbol::IsStrucType()
{
	return StrucTypename != "";
}
bool TSymbol::IsAliasType()
{
	return ( aliastypename != "" ) && !IsArray() && !IsReference();
}
bool TSymbol::IsSimpleType()
{
	return ( simpletypename != "" );
}
bool TSymbol::IsAlSimpleType()
{
	if ( IsAliasType() )
		return GetRealType()->IsSimpleType();
	return IsSimpleType();
}
bool TSymbol::IsAlStrucType()
{
	if ( IsAliasType() )
		return GetRealType()->IsStrucType();
	return IsStrucType();
}
bool TSymbol::IsFunc()
{
	return ( funcname != "" );
}
bool TSymbol::IsType()
{
	return ( ( varname == "" ) && ( funcname == "" ) );
}
bool TSymbol::IsFloat()
{
	return simpletypename == "float";
}
bool TSymbol::IsInt()
{
	return simpletypename == "int";
}
bool TSymbol::IsString()
{
	return simpletypename == "string";
}
TSymbol *TSymbol::GetRealType()
{
	if ( !IsVar() && !IsAliasType() && !IsFunc() && !IsReference() )
		return this;
	return type->GetRealType();
};
TSymbol *TSymbol::GetType()
{
	return type;
}
void TSymbol::CalcTableSizes()
{}


TSymVar::TSymVar( string &id , TSymbol *t , TSymTableStack *stack  , TExpr *v )
{
	offset = 0;
	type = t;
	varname = id;
	if ( v )
		value = v;
	else
		value = new TEmptyExpr();
	if ( stack->GlobalSpace() )
		SetGlobal();
	else
		SetLocal();
	reftotable = stack->ShowLocalTable();
}
void TSymVar::FullPrint( int level = 0 )
{
	Tab( level );
	cout << "varname = " << varname << "\ttype = ";
	type->ShortPrint();
	cout << "\tsize = " << type->GetSize();
	cout << "\tscope = " << scope << "\toffset = " << offset;
	if ( !value->IsEmptyExpr() )
	{
		cout << "\tvalue:\n";
		value->Print( level + 1 );
	}
	cout << "\n";
}
bool TSymVar::operator!=( TSymbol s )
{
	return ( s.varname != varname )
		|| ( s.GetRealType()->simpletypename != GetRealType()->simpletypename );         
}
void TSymVar::PutValue( TExpr *val )
{
	value = val;
}
string TSymVar::Comment()
{
	return " variable " + varname + " definition ";
}
void TSymVar::Gen( CodeGen *cg )
{
	if ( IsGlobal() )
		GenGlobVarDecl( cg );
	else//if local
		GenLocVarDecl( cg );
}
void TSymVar::GenLocVarDecl( CodeGen *cg )
{
	//if has an expression as value
	//then generate it and leave in the stack
	cg->Gen( Com , Begin( varname ) );
	if ( value->IsEmptyExpr() )
	{
		if ( GetRealType()->IsStrucType() || GetRealType()->IsArray() )
			cg->Gen( SUB , reg( esp ) , imm( GetRealType()->GetSize() ) );
		else
			cg->Gen( PUSH , imm( 0 ) );
	}
	else
		value->Gen( cg );
	cg->Gen( Com , End( varname ) );
}
void TSymVar::GenGlobVarDecl( CodeGen *cg )
{
	cg->Gen( Com , Begin( varname ) );
	TSymbol *t = type->GetRealType();
	if ( t->IsStrucType() )
		cg->Gen( DUP , memv_( varname ) , imm( t->GetSize() ) );
	else
		if ( value->IsConstExpr() )
		{
			if ( t->IsFloat() )
				cg->Gen( DD , memv_( varname ) , imm( value->GetFloat() ) );
			else
				if ( t->IsInt() )
					cg->Gen( DD , memv_( varname ) , imm( value->GetInt() ) );
		}
		else
			if ( t->IsFloat() )
				cg->Gen( DD , memv_( varname ) , str( "?" ) );
			else
				if ( t->IsInt() )
					cg->Gen( DD , memv_( varname ) , str( "?" ) );
	cg->Gen( Com , End( varname ) );
}
void TSymVar::GenGlobVarInit( CodeGen *cg )
{
	if ( !value->IsEmptyExpr() && !value->IsConstExpr() )
	{
		value->Gen( cg );
		if ( type->GetRealType()->IsInt() )
		{
			cg->Gen( POP , reg( eax ) );
			cg->Gen( MOV , memv_( varname ) , reg( eax ) );
		}
		else
		{
            cg->Gen( FLD , mem( "DD ptr [esp]" ) );
			cg->Gen( ADD , reg( esp ) , imm( 4 ) );
			cg->Gen( FST , memv_( varname ) );
		}
	}
}
void TSymVar::InitOffset( int off )
{
	offset = off + 4;
}
int TSymVar::GetSize()
{
	return type->GetSize();
}
void TSymVar::SetArgument()
{
	scope = "argument";
}
void TSymVar::SetGlobal()
{
	scope = "global";
}
void TSymVar::SetLocal()
{
	scope = "local";
}
bool TSymVar::IsGlobal()
{
	return scope == "global";
}
bool TSymVar::IsLocal()
{
	return scope == "local";
}
bool TSymVar::IsArgument()
{
	return scope == "argument";
}
int TSymVar::GetRelOffset()
{
	return offset;
}
int TSymVar::GetFullOffset()
{
	return offset + reftotable->GetOffset();
}


TSymFunc::TSymFunc( string &id , TSymbol *t )
{
	type = t;
	funcname = id;
	body = new TEmptyStmt();
	argtable = new TSymTable();
}
void TSymFunc::Gen( CodeGen *cg )
{
	//generate "function	proc"
	cg->Gen( PROC , strf_( funcname ) );
	cg->Gen( PUSH , reg( ebp ) );
	cg->Gen( MOV , reg( ebp ) , reg( esp ) );
	body->Gen( cg );

	cg->Gen( XOR , reg( eax ) , reg( eax ) );
	cg->Gen( LABEL , str( "return_" + funcname ) );
	cg->Gen( POP , reg( ebp ) );
	cg->Gen( RET );
	//generate "function	endp"
	cg->Gen( ENDP , strf_( funcname ) );
}
void TSymFunc::PutBody( TBlockStmt *b )
{
	delete( body );
	body = b;
}
void TSymFunc::FullPrint( int level = 0 )
{
	Tab( level );
	if ( HasBody() )
		cout << "func definition:   ";
	else
		cout << "func declaration:   ";
	if ( type->IsSimpleType() )
		cout << type->simpletypename;
	if ( type->IsAliasType() )
		cout << type->aliastypename;
	cout << " " << funcname << "   \n";
	if ( argtable->GetNumElems() )
	{
		Tab( level );
		cout << "arguments: \n";
		argtable->Print( level + 1 );
	}
	else
	{
		Tab( level );
		cout << "has no arguments\n";
	}
	body->Print( level+1 );
	Tab( level );
	cout << "end function\n\n\n\n\n";
}
bool TSymFunc::FindArg( string s )
{
	return argtable->FindVar( s );
}
void TSymFunc::AddArg( TSymbol *add )
{
	argtable->Add( add );
}
void TSymFunc::CalcTableSizes()
{
	argtable->CalcSize();
	argtable->InverseOffset();
	body->CalcTableSizes( 0 );
}
int TSymFunc::CalcArgSize()
{
	int counter = 0;
	for ( int i = 0 ; i<argtable->GetSize() ; ++i )
		counter += argtable->GetElemN( i )->GetSize();
	return counter;
}


int TSymType::GetSize()
{
	return size;
}


void TypeInteger::ShortPrint()
{
	cout << simpletypename;
}
void TypeInteger::FullPrint( int level = 0 )
{
	ShortPrint();
}
TypeInteger::TypeInteger()
{
	size = 4;
	simpletypename = "int";
}


void TypeFloat::ShortPrint()
{
	cout << simpletypename;
}
TypeFloat::TypeFloat()
{
	size = 4;
	simpletypename = "float";
}
void TypeFloat::FullPrint( int level = 0 )
{
	ShortPrint();
}
TypeString::TypeString()
{
	simpletypename == "string";
}

TypeArray::TypeArray( TExpr *e , TSymbol *t )
	:sizeexpr( e )
{
	aliastypename = "0array";
	type = t;
	size = t->GetSize() * e->GetInt();
}
TSymbol *TypeArray::GetType()
{
	return type;
}
void TypeArray::FullPrint( int level = 0 )
{
	ShortPrint();
}
void TypeArray::ShortPrint()
{
	cout << "\narray\n[\n";
	sizeexpr->Print( 0 );
	cout << "] of : ";
	type->ShortPrint();
}
TSymbol *TypeArray::GetArrayElemType()
{
	return type;
}
TExpr *TypeArray::GetSizeExpr()
{
	return sizeexpr;
}
bool TypeArray::IsArray()
{
	return 1;
}


TypeStruct::TypeStruct( TSymTable *mems , string &name )
{
	memtable = mems;
	size = mems->GetSize();
	StrucTypename = ( name == "" ? "0anonymous" : name );
}
void TypeStruct::ShortPrint()
{
	if ( StrucTypename == "0anonymous" )
		FullPrint( 0 );
	else
		cout << "struct " << StrucTypename;
}
void TypeStruct::FullPrint( int level = 0 )
{
	Tab( level );
	cout << "struct " << StrucTypename;
	Tab( level );
	cout << "\n{\n";
	Tab( level );
	cout << "size of struct type: " << size;
	Tab( level );
	memtable->Print( level );
	cout << "}";
	if ( StrucTypename != "0anonymous" )
		cout << "\n";
}
TSymbol *TypeStruct::FindMember( string str )
{
	return memtable->Find( str );
}


TypeRefer::TypeRefer( TSymbol *oldt )
{
	type = oldt;
	aliastypename = "0reference";
	size = 4;
}
TSymbol *TypeRefer::GetReferType()
{
	return type;
}
void TypeRefer::ShortPrint()
{    
	cout << "reference to ";
	type->ShortPrint();            
}
void TypeRefer::FullPrint( int level = 0 )
{
	Tab( level );
	cout << "reference to data of type: ";
	type->ShortPrint();
	cout << "\n";
}


TypeAlias::TypeAlias( TSymbol *oldt , string newname )
{
	type = oldt;
	aliastypename = newname;
}
void TypeAlias::ShortPrint()
{ 
	cout << aliastypename;
}
void TypeAlias::FullPrint( int level = 0 )
{
	Tab( level );
	cout << "typedef   previous name: ";
	type->ShortPrint();
	cout << "   new name: " << aliastypename << "\n";        
}
int TypeAlias::GetSize()
{
	return GetRealType()->GetSize();
}