#include "tsyntobj.h"
#include "tsymbol.h"
#include "tsymtable.h"
#include "scantools.h"
#include "error.h"
#include "codegen.h"



bool TExpr::IsExpr()
{
	return 1;
}
TSymbol *TExpr::GetType()
{
	return exprtype;
}
TSymbol *TExpr::GetRealType()
{
	return exprtype->GetRealType();
}
TSymbol *TExpr::GetRefdObjType()
{
	return exprtype->GetRealType();
}


TConstExpr::TConstExpr( const string &s , float v , TSymbol *t )
	:f_value( v )
{
	source = s;
	type = cfloat;
	exprtype = t;
	islvalue = false;
}
TConstExpr::TConstExpr( const string &s , int v , TSymbol *t )
	:i_value( v )
{
	source = s;
	type = cint;
	exprtype = t;
	islvalue = false;
}
TConstExpr::TConstExpr( const string &s , string v , TSymbol *t )
	:s_value( v )
{
	exprtype = NULL;
	source = s;
	type = cstr;
	exprtype = t;
	islvalue = false;
}
int TConstExpr::GetInt()
{
	return i_value;
}
float TConstExpr::GetFloat()
{
	return f_value;
}
string *TConstExpr::GetString()
{
	return &s_value;
}
bool TConstExpr::IsStringConst()
{
	return s_value != "";
}
void TConstExpr::PutStringNum( int num )
{
	i_value = num;
}
void TConstExpr::Gen( CodeGen *cg )
{
	cg->Gen( Com , Begin( Comment() ) );
	if ( type == cint )
		cg->Gen( PUSH, imm( i_value ) );
	else
		cg->Gen( PUSH , imm( f_value ) );
	cg->Gen( Com , End( Comment() ) );
}

string TConstExpr::Comment()
{
	return source;
}
void TConstExpr::Print( int level )
{
	Tab( level );
	cout << "````";
	/*if ( type == cstr )
		cout << s_value;
	else
		if ( type == cint )
			cout << i_value;
		else
			cout << f_value;*/
	cout << source;
	cout << '\n';
}
bool TConstExpr::IsConstExpr()
{
	return 1;
}


TVarExpr::TVarExpr( string s , TSymbol *t )
{ 
	source = s;
	type = name;
	exprtype = t;
	islvalue = true;
}
void TVarExpr::Print( int level )
{
	Tab( level );
	cout << "````";
	cout << source << '\n';
}
void TVarExpr::Gen( CodeGen *cg )
{
	if ( exprtype->IsGlobal() )
		cg->Gen( PUSH , strv_( source ) );
	else
		if ( exprtype->IsLocal() )
		{
			cg->Gen( Com , Begin( source ) );
			cg->Gen( PUSH , addr( ebp , -exprtype->GetFullOffset() ) );
			cg->Gen( Com , End( source ) );
		}
		else
		{
			if ( exprtype->GetType()->IsReference() )
			{
				cg->Gen( MOV , reg( eax ) , addr( ebp , exprtype->GetFullOffset() ) );
				cg->Gen( MOV , reg( eax ) , addr( eax ) );
				cg->Gen( PUSH , reg( eax ) );
			}
			else
			{
				cg->Gen( MOV , reg( eax ) , reg( ebp ) );
				cg->Gen( ADD , reg( eax ) , imm( exprtype->GetRelOffset() ) );
				cg->Gen( PUSH , addr( eax ) );
			}
		}
}
void TVarExpr::GenAddr( CodeGen *cg )
{
	if ( exprtype->IsGlobal() )
		cg->Gen( PUSH , str( "offset data:" + v_( source ) ) );
	else
		if ( exprtype->IsLocal() )
		{
			cg->Gen( MOV , reg( eax ) , reg( ebp ) );
			cg->Gen( SUB , reg( eax ) , imm( exprtype->GetFullOffset() ) );
			cg->Gen( PUSH , reg( eax ) );
		}
		else
		{
			if ( exprtype->GetType()->IsReference() )
			{
				cg->Gen( MOV , reg( eax ) , reg( ebp ) );
				cg->Gen( ADD , reg( eax ) , imm( exprtype->GetRelOffset() ) );
				cg->Gen( PUSH , addr( eax ) );
			}
			else
			{
				cg->Gen( MOV , reg( eax ) , reg( ebp ) );
				cg->Gen( ADD , reg( eax ) , imm( exprtype->GetRelOffset() ) );
				cg->Gen( PUSH , reg( eax ) );				
			}
		}
}
string TVarExpr::Comment()
{
	return source;
}

TTypeCast::TTypeCast( TSymbol *to , TExpr *s )
	:expression( s )
{
	exprtype = to;
}
void TTypeCast::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	TSymbol *typ;
	if( expression->IsFunccallOp() )
		typ = expression->GetFuncType();
	else
		typ = expression->GetRealType();
	if ( !typ->IsSimpleType() )
		throw TypeCastNotAvail( pos );
	islvalue = false;
}
bool TTypeCast::CastNeeded()
{
	return expression->GetType() != exprtype;
}
bool TTypeCast::IsAlive()
{
	return expression->IsAlive();
}
int TTypeCast::GetInt()
{
	return expression->GetInt();
}
float TTypeCast::GetFloat()
{
	return expression->GetFloat();
}
void TTypeCast::Print( int level )
{
	expression->Print( level+1 );
	Tab( level );
	cout << "````";
	exprtype->FullPrint();
	cout << "()\n";
}
void TTypeCast::Gen( CodeGen *cg )
{
	TSymbol *typ = exprtype->GetRealType();
	cg->Gen( Com , Begin( Comment() ) );
	expression->Gen( cg );
	if ( typ->IsInt() && expression->GetRefdObjType()->IsFloat() )
	{
		cg->Gen( FLD , addr( esp ) );
		cg->Gen( FISTP , addr( esp ) );
	}
	else
		if ( typ->IsFloat() && expression->GetRefdObjType()->IsInt() )
		{
			cg->Gen( FILD , addr( esp ) );
			cg->Gen( FSTP , addr( esp ) );
		}
	cg->Gen( Com , End( Comment() ) );
}
string TTypeCast::Comment()
{
	return exprtype->simpletypename + "(" + expression->Comment() + ")";
}


TEmptyExpr::TEmptyExpr()
{ 
	source = "?";
	exprtype = NULL;
}
void TEmptyExpr::Gen( CodeGen *cg )
{
	if ( cg->ComEnabled() )
		cg->Gen( LABEL , str( ";WARNING: TEmptyExpr has been generated; possibly mistake" ) );
}
void TEmptyExpr::Print( int  )
{}
bool TEmptyExpr::IsEmptyExpr()
{
	return 1;
}

bool TFunccallOp::IsAlive()
{
	return true;
}
TFunccallOp::TFunccallOp( TExpr *name , TExpr *list )
	:funcname( name ), arglist( list )
{
	source = "()";
	ListExpr = new vector< TExpr * >();
	islvalue = false;
}
string TFunccallOp::Comment()
{
	return funcname->source + "()";
}
void TFunccallOp::GenPrintf( CodeGen *cg )
{
	vector< TExpr * > *list = arglist->ListExpr;
	int size = list->size();
	int floats = 0;
	for ( int i = size - 1 ; i > 0 ; --i )
	{
		(*list)[i]->Gen( cg );
		if ( (*list)[i]->GetRefdObjType()->GetRealType()->IsFloat() )
		{
			++floats;
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( SUB , reg( esp ) , imm( 4 ) );
			cg->Gen( FSTP , addr( esp , 0 , 1 ) );
		}
	}
	cg->Gen( PUSH , str( "offset data:str" + cg->IntToString( (*list)[0]->GetInt() ) ) );
	cg->Gen( CALL , str( "_printf" ) );	
	cg->Gen( ADD , reg( esp ) , imm( ( size + floats )* 4  ) );
	cg->Gen( PUSH , reg( eax ) );
}
void TFunccallOp::GenScanf( CodeGen *cg )
{
	vector< TExpr * > *list = arglist->ListExpr;
	int size = list->size();
	for ( int i = size - 1 ; i > 0 ; --i )
		(*list)[i]->GenAddr( cg );
	cg->Gen( PUSH , str( "offset data:str" + cg->IntToString( (*list)[0]->GetInt() ) ) );
	cg->Gen( CALL , str( "_scanf" ) );
	cg->Gen( ADD , reg( esp ) , imm( size * 4 ) );
	cg->Gen( PUSH , reg( eax ) );
}
void TFunccallOp::Gen( CodeGen *cg )
{
	cg->Gen( Com , Begin( "call " + Comment() ) );
	if ( funcname->source == "printf" )
	{
		GenPrintf( cg );
		cg->Gen( Com , End( "call " + Comment() ) );
		return;
	}
	if ( funcname->source == "scanf" )
	{
		GenScanf( cg );
		cg->Gen( Com , End( "call " + Comment() ) );
		return;
	}
	//push all arguments
	PushArgs( cg );
	//call function ;)
	cg->Gen( CALL , strf_( funcname->source ) );
	PopArgs( cg );
	cg->Gen( PUSH , reg( eax ) );
	cg->Gen( Com , End( "call " + Comment() ) );
}
void TFunccallOp::PushArgs( CodeGen *cg )
{
	cg->Gen( Com , Begin( "PUSHing arguments" ) );
	vector< TExpr * > *list = arglist->ListExpr;
	vector< TSymbol * > *argtable = funcname->exprtype->argtable->ShowTable();

	for ( int i = 0 ; i < list->size() ; ++i )
	{
		if ( (*argtable)[i]->GetType()->IsReference() )
			(*list)[i]->GenAddr( cg );
		else
			(*list)[i]->Gen( cg );
	}
	cg->Gen( Com , End( "PUSHing arguments" ) );	
}
void TFunccallOp::PopArgs( CodeGen *cg )
{
	cg->Gen( Com , Begin( "POPing arguments" ) );
	int size = arglist->ListExpr->size();
	if ( size )
		cg->Gen( ADD , reg( esp ) , imm( size * 4 ) );
	cg->Gen( Com , End( "POPing arguments" ) );	
}
void TFunccallOp::CheckPrintf( TSymTable *GlobSymTable , Position pos )
{
	vector< TExpr * > *list = arglist->ListExpr;
	if ( (*list)[0]->IsStringConst() )
		(*list)[0]->PutStringNum( GlobSymTable->AddString( (*list)[0]->GetString() ) );
	else
		throw StringConstExp( pos );
	TSymbol *type;
	for ( int i = 1 ; i < list->size() ; ++i )
	{ 
		if ( (*list)[i]->IsStringConst() )
			throw ArgMismatch( pos );
		type = (*list)[i]->GetRefdObjType();
		if ( !type->IsSimpleType() )
			throw ArgMismatch( pos );
	}
}
void TFunccallOp::CheckScanf( TSymTable *GlobSymTable , Position pos )
{
	vector< TExpr * > *list = arglist->ListExpr;
	if ( (*list)[0]->IsStringConst() )
		(*list)[0]->PutStringNum( GlobSymTable->AddString( (*list)[0]->GetString() ) );
	else
		throw StringConstExp( pos );
	TSymbol *type;
	for ( int i = 1 ; i < list->size() ; ++i )
	{ 
		if ( (*list)[i]->IsStringConst() )
			throw ArgMismatch( pos );
		type = (*list)[i]->GetRefdObjType();
		if ( !type->IsSimpleType() )
			throw ArgMismatch( pos );
	}
}
void TFunccallOp::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	if ( funcname->source == "printf" )
	{
		CheckPrintf( GlobSymTable , pos );
		return;
	}
	if ( funcname->source == "scanf" )
	{
		CheckScanf( GlobSymTable , pos );
		return;
	}
	//funcname's type contains nothing - identifier was left for structs fields
	if ( !funcname->exprtype )
		throw FuncNameExp( pos );
	//funcnames's type doesn't contain pointer to TSymFunc in the GlobSymTable that is it's var
	if ( !funcname->exprtype->IsFunc( ) )
		throw FuncNameExp( pos );
	exprtype = funcname->exprtype;
	//forbidden to call main()
	if ( funcname->exprtype->funcname == "main" )
		throw MainCall( pos );
	if ( arglist->ListExpr->size() != funcname->exprtype->argtable->GetNumElems() )
		throw ArgNumMismatch( pos );
	
	vector< TExpr*  > *l1;
	TSymTable *l2;
	l1 = arglist->ListExpr;
	l2 = funcname->exprtype->argtable;

	TSymbol *a1, *a2;
	bool lval;
	for ( int i = 0 ; i < l1->size() ; ++i )
	{
		lval = (*l1)[i]->islvalue;
		if ( (*l1)[i]->IsFunccallOp() )
		{
			//lval = false;
			a1 = (*l1)[i]->GetFuncType();
		}
		else
			a1 = (*l1)[i]->GetRealType();

		/*if ( (*l1)[i]->IsConstExpr() )
			lval = false;*/
		a2 = l2->GetElemN( i )->GetRealType();

		if ( a1->IsArray() && a2->IsArray() )
		{
			if ( !EqualArrays( a1 , a2 ) )
				throw ArgMismatch( pos );
		}
		else
			if ( !a1->IsArray() && !a2->IsArray() )
			{
				if ( !lval && l2->GetElemN( i )->GetType()->IsReference() )
					throw ConstNLval( pos );
				if ( a1 != a2 )
					throw ArgMismatch( pos );
			}
			else
				throw ArgMismatch( pos );
	}
}
bool TFunccallOp::IsFunccallOp()
{
	return 1;
}
TSymbol *TFunccallOp::GetFuncType()
{
	return funcname->exprtype->type;
}
string TFunccallOp::GetFuncName()
{
	return funcname->source;
}
void TFunccallOp::Print( int level )
{
	arglist->Print( level + 1 );
	Tab( level );
	cout << "````" << source << '\n';
	funcname->Print( level + 1 );
}

TExtractOp::TExtractOp( TExpr *left , TExpr *i )
	:leftpart( left ), index( i )
{}
bool TExtractOp::IsExtractOp()
{
	return 1;
}
void TExtractOp::Gen( CodeGen *cg )
{
	GenAddr( cg );
	cg->Gen( POP , reg( eax ) );
	cg->Gen( MOV , reg( eax ) , addr( eax ) );
	cg->Gen( PUSH , reg( eax) );
}

//!!adds the address of extracting element to the top double word of the stack
//hence zero value at the stack's top is needed when begining computation
void TExtractStructOp::GenAddr( CodeGen *cg )
{
	cg->Gen( PUSH , imm( 0 ) );
	GenAddrHelper( cg );
}
bool TExtractArrayOp::IsAlive()
{
	return leftpart->IsAlive() || index->IsAlive();
}
bool TExtractStructOp::IsAlive()
{
	return leftpart->IsAlive();
}
void TExtractStructOp::GenAddrHelper( CodeGen *cg )
{
	//generate offset of the member in the struct
	cg->Gen( MOV , reg( eax ) , imm( leftpart->GetRefdObjType()->FindMember( index->source )->GetRelOffset() ) );
	//adding previous value of offset from stack
	cg->Gen( POP , reg( ebx ) );
	cg->Gen( ADD , reg( eax ) , reg( ebx ) );
	//put new offset back to stack
	cg->Gen( PUSH , reg( eax ) );

	if ( leftpart->IsExtractStructOp() )
		leftpart->GenAddrHelper( cg );
	else
	{
		leftpart->GenAddr( cg );
		cg->Gen( POP , reg( eax ) );
		cg->Gen( POP , reg( ebx ) );
		cg->Gen( SUB , reg( eax ) , reg( ebx ) );
		cg->Gen( PUSH , reg( eax ) );
	}
}
void TExtractArrayOp::GenAddr( CodeGen *cg )
{
	cg->Gen( PUSH , imm( 0 ) );
	GenAddrHelper( cg );
}
void TExtractArrayOp::GenAddrHelper( CodeGen *cg )
{	
	//generate value of index
	index->Gen( cg );
	cg->Gen( POP , reg( eax ) );
	//generate value of size of embbded array
	cg->Gen( MOV , reg( ebx ) , imm( GetType()->GetSize() ) );
	//getting offset
	cg->Gen( MUL , reg( ebx ) );
	//adding previous value from stack
	cg->Gen( POP , reg( ebx ) );
	cg->Gen( ADD , reg( eax ) , reg( ebx ) );
	//put new offset back to stack
	cg->Gen( PUSH , reg( eax ) );

	//if next level is struct or array extracting
	//then gen its offset like above,
	//but if it is the name of some object (array or struct), then generate it's base address
	if ( leftpart->IsExtractArrayOp() )
		leftpart->GenAddrHelper( cg );
	else
	{
		leftpart->GenAddr( cg );
		cg->Gen( POP , reg( eax ) );
		cg->Gen( POP , reg( ebx ) );
		cg->Gen( SUB , reg( eax ) , reg( ebx ) );
		cg->Gen( PUSH , reg( eax ) );
	}
}

/*EXTRACTING OPERATION*/
TExtractArrayOp::TExtractArrayOp( TExpr *left , TExpr *i )
	:TExtractOp( left , i )
{}
TExtractStructOp::TExtractStructOp( TExpr *left , TExpr *i )
	:TExtractOp( left , i )
{}
void TExtractArrayOp::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	if ( !leftpart->exprtype )
		throw StructArrayExp( pos );
	if ( !index->exprtype )
		throw IllegIndex( pos );
	if ( !leftpart->GetRefdObjType() )
		throw StructArrayExp( pos );

	TSymbol *l = leftpart->GetRealType();
	if ( !l->IsArray() )
		throw ArrayExp( pos );
	TSymbol *i;
	if ( index->IsFunccallOp() )
		i = index->GetFuncType();
	else
		i = index->GetRealType();
	if ( !i->IsInt() )
		throw NonIntIndex( pos );
	exprtype = l->type;
	if ( exprtype->IsSimpleType() )
		islvalue = true;
	else
		islvalue = false;
	exprtype = leftpart->GetRefdObjType()->GetArrayElemType();
}

void TExtractStructOp::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	if ( !leftpart->exprtype )
		throw StructArrayExp( pos );
	if ( !leftpart->GetRefdObjType()->IsStrucType() )
		throw StructArrayExp( pos );

	TSymbol *l = leftpart->GetRealType();
	if ( !l->IsStrucType() )
		throw StructExp( pos );
	if ( index->type != name )
		throw IdStructExp( pos );
	if (  l->FindMember( index->source ) == NULL  )
		throw NonStructField( pos );
	exprtype = l->FindMember( index->source )->GetRealType();
	if ( exprtype->IsSimpleType() )
		islvalue = true;
	else
		islvalue = false;
	exprtype = leftpart->GetRefdObjType()->FindMember( index->source );
}

TExpr *TExtractOp::GetIndex()
{
	return index;
}
TExpr *TExtractOp::GetLeftPart()
{
	return leftpart;
}
bool TExtractStructOp::IsExtractStructOp()
{
	return 1;
}
bool TExtractArrayOp::IsExtractArrayOp()
{
	return 1;
}

string TExtractArrayOp::Comment()
{
	return leftpart->Comment() + '[' + index->Comment() + ']';
}

string TExtractStructOp::Comment()
{
	return leftpart->Comment() + '.' + index->source;
}



/*extract op generation*/
void TExtractOp::Print( int level )
{
	index->Print( level+1 );
	Tab( level );
	cout << "````" << ( IsExtractStructOp() ? "." : "[]" ) << source << '\n';
	leftpart->Print( level+1 );
}


TAssignOp::TAssignOp ( Type t , string s , TExpr *l , TExpr *r )
	:left( l ), right( r )
{
	type = t;
	source = s;
}
bool TAssignOp::IsAlive()
{
	return true;
}
void TAssignOp::Gen( CodeGen *cg )
{
	cg->Gen( Com , Begin( Comment() ) );
	right->Gen( cg );
	left->GenAddr( cg );
	if ( oassign == type )
	{
		cg->Gen( POP , reg( eax ) );
		cg->Gen( POP , reg( ebx ) );
		cg->Gen( MOV , addr( eax ) , reg( ebx ) );
		cg->Gen( PUSH , reg( ebx ) );

		cg->Gen( Com , End( Comment() ) );
		return;		
	}

	TSymbol *typ = exprtype->GetRealType();
	if ( typ->IsInt() )
	{
		if ( oassignplus == type )
		{
			cg->Gen( POP , reg( eax ) );
			cg->Gen( POP , reg( ebx ) );
			cg->Gen( ADD , addr( eax ) , reg( ebx ) );
			cg->Gen( PUSH , addr( eax ) );
		}
		else
			if ( oassignmin == type )
			{
				cg->Gen( POP , reg( eax ) );
				cg->Gen( POP , reg( ebx ) );
				cg->Gen( SUB , addr( eax ) , reg( ebx ) );
				cg->Gen( PUSH , addr( eax ) );
			}
			else
				if ( oassignmul == type )
				{
					cg->Gen( POP , reg( ebx ) );
					cg->Gen( POP , reg( eax ) );
					cg->Gen( MUL , addr( ebx ) );
					cg->Gen( PUSH , reg( eax ) );
					cg->Gen( MOV , addr( ebx ) , reg( eax ) );
				}
				else
					if ( oassigndiv == type )
					{
						cg->Gen( POP , reg( ecx ) );
						cg->Gen( POP , reg( ebx ) );
						cg->Gen( MOV , reg( eax ) , addr( ecx ) );
						cg->Gen( XOR , reg( edx ) , reg( edx ) );
						cg->Gen( IDIV , reg( ebx ) );
						cg->Gen( MOV , addr( ecx ) , reg( eax ) );
						cg->Gen( PUSH , reg( eax ) );
					};
	}
	else
	{
		cg->Gen( POP , reg( eax ) );
		cg->Gen( FLD , addr( eax ) );
		cg->Gen( FLD , addr( esp ) );
		if ( oassignplus == type )
			cg->Gen( FADDP , reg( st1 ) , reg( st0 ) );
		else
			if ( oassignmin == type )
				cg->Gen( FSUBP , reg( st1 ) , reg( st0 ) );
			else
				if ( oassignmul == type )
					cg->Gen( FMULP , reg( st1 ) , reg( st0 ) );
				else
					if ( oassigndiv == type )
						cg->Gen( FDIVP , reg( st1 ) , reg( st0 ) );
		cg->Gen( FST , addr( eax ) );
		cg->Gen( FSTP , addr( esp ) );
	}
	cg->Gen( Com , End( Comment() ) );
	return;
}
string TAssignOp::Comment()
{
	return "(" + left->Comment() + ")" + source + "(" + right->Comment() + ")";
}
void TAssignOp::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	if ( !left->exprtype || !right->exprtype )
		throw LeftAssignUnknown( pos );

	if ( left->GetType()->IsFunc() )
		throw NoFuncExp( pos );
	if ( !left->islvalue )
		throw LeftAssignMustBeLvalue( pos );

	islvalue = false;
	TSymbol *l = left->GetRealType();
	TSymbol *r;
	if ( right->IsFunccallOp() )
		r = right->GetFuncType();
	else
		r = right->GetRealType();

	if ( !l->IsSimpleType() || !r->IsSimpleType() )
		throw AssignNonSimple( pos );
	if ( l != r )
		CreateTypeCast( right , l , opt );
	exprtype = l;
}
void TAssignOp::Print( int level )
{
	if ( right != NULL )
		right->Print( level+1 );

	Tab( level );
	cout << "````" << source << '\n';

	if ( left != NULL )
		left->Print( level+1 );
}


TBinaryOp::TBinaryOp( Type t , string s , TExpr *l , TExpr *r )
	:left( l ) , right( r )
{
	type = t;
	source = s;
}
bool TBinaryOp::IsAlive()
{
	return left->IsAlive() || right->IsAlive();
}
TExpr *TBinaryOp::GetRightPart()
{
	return right;
}
TExpr *TBinaryOp::GetLeftPart()
{
	return left;
}
void TBinaryOp::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	//unknwon type
	if ( !left->exprtype || !right->exprtype )
		throw BinOpersUnknown( pos );
	//binary operation is not lvalue
	islvalue = false;
	//if Op - ident and names a function

	//take types of Ops
	TSymbol *l, *r;

	if ( left->IsFunccallOp() )
		l = left->GetFuncType();
	else
		l = left->GetType()->GetRealType();

	if ( right->IsFunccallOp() )
		r = right->GetFuncType();
	else
		r = right->GetRealType();

	//Ops must be int or float
	if ( !l->IsSimpleType() || !r->IsSimpleType() )
		throw BinOpSimpType( pos );
	//if logical operations or comparsion
	if ( ( type > 26 ) && ( type < 37 ) )
	{
		exprtype = GlobSymTable->GetElemN( 0 );		
		TSymbol *flt = GlobSymTable->GetElemN( 1 );
		if ( l != r )
		{
			if ( l->IsFloat() )
				CreateTypeCast( right , flt , opt );
			if ( r->IsFloat() )
				CreateTypeCast( left , flt , opt );
		}
	}
	else
		if ( l != r )
		{
			if ( r->IsFloat() )
			{
				exprtype = r;
				CreateTypeCast( left , r , opt );
			}
			else
			{
				exprtype = l;
				CreateTypeCast( right , l , opt );
			}
		}
		else
			exprtype = l;
	//type of expression matches the type of each argument	
}
string TBinaryOp::Comment()
{
	return "(" + left->Comment() + ")" + source + "(" + right->Comment() + ")";
}
//		<<<<<<<		<<<<<<<		CODE	GENERATION		>>>>>>>		>>>>>>>
void TBinaryOp::Gen( CodeGen *cg )
{
	TSymbol *typ = exprtype->GetRealType();
	cg->Gen( Com , Begin( Comment() ) );

	//together: + - / *
	if ( ( type > 19 ) && ( type < 24 ) )
	{
		left->Gen( cg );
		right->Gen( cg );
		if ( typ->IsInt() )
		{
			cg->Gen( POP , reg( ebx ) );
			cg->Gen( POP , reg( eax ) );
			if ( oplus == type )
				cg->Gen( ADD , reg( eax ) , reg( ebx ) );
			else
				if ( ominus == type )
					cg->Gen( SUB , reg( eax ) , reg( ebx ) );
				else
					if ( omul == type )					
						cg->Gen( IMUL , reg( ebx ) );
					else
						if ( odiv == type )
						{
							cg->Gen( XOR , reg( edx ) , reg( edx ) );						
							cg->Gen( DIV , reg( ebx ) );						
						}
			cg->Gen( PUSH , reg( eax ) );
		}
		//the same fo floats
		else
		{
			cg->Gen( FLD , addr( esp , 4 ) );
			cg->Gen( FLD , addr( esp ) );
			if ( oplus == type )
				cg->Gen( FADDP , reg( st1 ) , reg( st0 ) );
			else
				if ( ominus == type )
					cg->Gen( FSUBP , reg( st1 ) , reg( st0 ) );
				else
					if ( omul == type )
						cg->Gen( FMULP , reg( st1 ) , reg( st0 ) );
					else
						if ( odiv == type )
							cg->Gen( FDIVP , reg( st1 ) , reg( st0 ) );
			cg->Gen( ADD , reg( esp ) , imm( 4 ) );
			cg->Gen( FSTP , addr( esp ) );
		}
		cg->Gen( Com , End( Comment() ) );
		return;
	}


	TSymbol *argstype = left->GetRealType();
	//together: == != >= <= > <
	if ( ( type > 28 ) && ( type < 35 ) )
	{		
		string label = cg->GenLabel();
		left->Gen( cg );
		right->Gen( cg );
		if ( argstype->IsInt() )
		{
			cg->Gen( POP , reg( ebx ) );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( XOR , reg( edx ) , reg( edx ) );
			cg->Gen( CMP , reg( eax ) , reg( ebx ) );
			if ( oequal == type )				
				cg->Gen( JNE , str( label ) );
			else
				if ( onequal == type )				
					cg->Gen( JE , str( label ) );
				else
					if ( oegreat == type )						
						cg->Gen( JL , str( label ) );
					else
						if ( oeless == type )						
							cg->Gen( JG , str( label ) );
						else
							if ( ogreat == type )							
								cg->Gen( JNG , str( label ) );
							else
								if ( oless == type  )
									cg->Gen( JNL , str( label ) );
			cg->Gen( MOV , reg( edx ) , imm( 1 ) );
			cg->Gen( LABEL , str( label ) );
			cg->Gen( PUSH , reg( edx ) );
		}
		else
		{
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( FLD , addr( esp , 4 ) );			
			cg->Gen( ADD , reg( esp ) , imm( 8 ) );
			cg->Gen( XOR , reg( eax ) , reg( eax ) );
			cg->Gen( FCOMIP , reg( st ) , reg( st1 ) );
			if ( oequal == type )
				cg->Gen( JNZ , str( label ) );
			else
				if ( onequal == type )
					cg->Gen( JZ , str( label ) );
				else
					if ( oegreat == type )
						cg->Gen( JC , str( label ) );
					else
						if ( oeless == type )							
							cg->Gen( JA , str( label ) );
						else
							if ( ogreat == type )
							{								
								cg->Gen( JZ , str( label ) );
								cg->Gen( JC , str( label ) );								
							}
							else
								if ( oless == type  )
								{									
									cg->Gen( JZ , str( label ) );
									cg->Gen( JNC , str( label ) );									
								};
			
			cg->Gen( MOV , reg( eax ) , imm( 1 ) );
			cg->Gen( LABEL , str( label ) );
			
			cg->Gen( FFREE , reg ( st0 ) );
			cg->Gen( FINCSTP );
			cg->Gen( PUSH , reg( eax ) );
		}
		cg->Gen( Com , End( Comment() ) );
		return;
	}

	//&& and ||, couldn't group the code...
	if ( oand == type )
	{
		string label = cg->GenLabel();
		left->Gen( cg );
		if ( argstype->IsInt() )
		{
			
			cg->Gen( POP , reg( eax ) );
			cg->Gen( CMP , reg( eax ) , imm( 0 ) );
			cg->Gen( JE , str( label ) );
			right->Gen( cg );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( CMP , reg( eax ) , imm( 0 ) );
			cg->Gen( JE , str( label ) );
			cg->Gen( MOV , reg( eax ) , imm( 1 ) );
			cg->Gen( LABEL , str( label ) );
			cg->Gen( PUSH , reg( eax ) );
		}
		else
		{			
			cg->Gen( XOR , reg( eax ) , reg( eax ) );
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( ADD , reg( esp ) , imm( 4 ) );
			cg->Gen( FLDZ );
			cg->Gen( FCOMIP , reg( st ) , reg( st1 ) );
			cg->Gen( JZ , str( label ) );
			right->Gen( cg );
			cg->Gen( XOR , reg( eax ) , reg( eax ) );
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( ADD , reg( esp ) , imm( 4 ) );
			cg->Gen( FLDZ );
			cg->Gen( FCOMI , reg( st ) , reg( st1 ) );
			cg->Gen( JZ , str( label ) );
			cg->Gen( MOV , reg( eax ) ,imm( 1 ) );
			cg->Gen( LABEL , str( label ) );
			cg->Gen( PUSH , reg( eax ) );
		}

		cg->Gen( Com , End( Comment() ) );
		return;
	}
	if ( oor == type )
	{
		string label = cg->GenLabel();
		left->Gen( cg );
		if ( argstype->IsInt() )
		{
			cg->Gen( MOV , reg( edx ) , imm( 1 ) );			
			cg->Gen( POP , reg( eax ) );
			cg->Gen( CMP , reg( eax ) , imm( 0 ) );
			cg->Gen( JNE , str( label ) );
			right->Gen( cg );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( CMP , reg( eax ) , imm( 0 ) );
			cg->Gen( JNE , str( label ) );
			cg->Gen( XOR , reg( edx ) , reg( edx ) );
			cg->Gen( LABEL , str( label ) );
			cg->Gen( PUSH , reg( edx ) );
		}
		else
		{
			cg->Gen( MOV , reg( eax ) , imm( 1 ) );
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( ADD , reg( esp ) , imm( 4 ) );
			cg->Gen( FLDZ );
			cg->Gen( FCOMIP , reg( st ) , reg( st1 ) );
			cg->Gen( JNZ , str( label ) );
			right->Gen( cg );
			cg->Gen( MOV , reg( eax ) , imm( 1 ) );
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( ADD , reg( esp ) , imm( 4 ) );
			cg->Gen( FLDZ );
			cg->Gen( FCOMI , reg( st ) , reg( st1 ) );
			cg->Gen( JNZ , str( label ) );
			cg->Gen( XOR , reg( eax ) , reg( eax ) );
			cg->Gen( LABEL , str( label ) );
			cg->Gen( PUSH , reg( eax ) );
		}
		cg->Gen( Com, End( Comment() ) );
		return;
	}
}
void TBinaryOp::Print( int level )
{
	if ( right != NULL )
		right->Print( level+1 );
	Tab( level );
	cout << "````";
	cout << source << '\n';
	if ( left != NULL )
		left->Print( level+1 );
}


TUnaryOp::TUnaryOp( string s , Type t , TExpr *r )
	:right( r ), left ( NULL )
{  
	type = t;
	source = s;
	left = NULL;
}
TUnaryOp::TUnaryOp( string s , TExpr *l , Type t )
	:left( l ), right( NULL )
{ 
	type = t;
	source = s;
	right = NULL;
}
bool TUnaryOp::IsAlive()
{
	if ( right && ( oincr == type ) || ( odecr == type ) )
		return true;
	if ( right )
		return right->IsAlive();
	return left->IsAlive();
}
int TUnaryOp::GetInt()
{
	if ( left )
		return left->GetInt();
	return right->GetInt();
}
float TUnaryOp::GetFloat()
{
	if ( left )
		return left->GetFloat();
	return right->GetFloat();
}
TExpr *TUnaryOp::GetLeftPart()
{
	return left;
}
TExpr *TUnaryOp::GetRightPart()
{
	return right;
}

void TUnaryOp::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	if ( right != NULL )
	{
		if ( !right->exprtype )
			throw UnknownUnOp( pos );
		TSymbol *r;
		if ( right->IsFunccallOp() )
			r = right->GetFuncType();
		else
			r = right->GetRealType();
		
		if ( !r->IsSimpleType() )
			throw UnOpSymType( pos );
		islvalue = false;
		if ( ( type == oplus ) || ( type == ominus ) )
			exprtype = r;
		else
			if ( ( type == oincr ) || ( type == odecr ) )
			{
				if ( !right->islvalue )
					throw LvalueExp( pos );
				exprtype = r;
				islvalue = true;
			}
			else
				exprtype = GlobSymTable->GetElemN( 0 );
	}
	else
	{
		if ( !left->exprtype )
			throw UnknownUnOp( pos );
		if ( !left->islvalue )
			throw LvalueExp( pos );
		TSymbol *l = left->GetRealType();
		if ( !l->IsSimpleType() )
			throw UnOpSymType( pos );
		islvalue = false;
		exprtype = l;
	}
}
string TUnaryOp::Comment()
{
	if ( right )
		return source + "(" + right->Comment() + ")";
	return "(" + left->Comment() + ")" + source;
}
//		<<<<<<<		<<<<<<<		CODE	GENERATION		>>>>>>>		>>>>>>>
void TUnaryOp::Gen( CodeGen *cg )
{	
	cg->Gen( Com , Begin( Comment() ) );
	if ( type == oplus )
	{
		right->Gen( cg );
		cg->Gen( Com , End( Comment() ) );
		return;
	}

	TSymbol *typ = exprtype->GetRealType();
	if ( type == ominus )
	{
		if ( typ->IsInt() )
		{
			right->Gen( cg );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( NEG , reg( eax ) );
			cg->Gen( PUSH , reg( eax ) );
		}
		else
		{
			right->Gen( cg );
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( FCHS );
			cg->Gen( FSTP , addr( esp ) );
		}
		cg->Gen( Com , End( Comment() ) );
		return;
	}
	
	if ( onot == type )
	{
		TSymbol *argtype = right->GetRealType();
		string label = cg->GenLabel();
		right->Gen( cg );
		if ( argtype->IsInt() )
		{
			cg->Gen( POP , reg( eax ) );
			cg->Gen( XOR , reg( edx ) , reg( edx ) );
			cg->Gen( CMP , reg( eax ) , imm( 0 ) );
			cg->Gen( JNE , str( label ) );
			cg->Gen( MOV , reg( edx ) , imm( 1 ) );
			cg->Gen( LABEL , str( label ) );
			cg->Gen( PUSH , reg( edx ) );
		}
		else
		{
			cg->Gen( XOR , reg( eax ) , reg( eax ) );
			cg->Gen( FLD , addr( esp ) );
			cg->Gen( FLDZ );
			cg->Gen( FCOMIP , reg( st ) , reg( st1 ) );
			cg->Gen( JNZ , str( label ) );			
			cg->Gen( MOV , reg( eax ) , imm( 1 ) );
			cg->Gen( LABEL , str( label ) );

			cg->Gen( MOV , addr( esp ) , reg ( eax ) );
		}
		cg->Gen( Com , End( Comment() ) );
		return;
	}

	//for all increments and decrements
	if ( left )
	{
		if ( typ->IsInt() )
		{
			left->GenAddr( cg );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( MOV , reg( ebx ) , addr( eax ) );
			cg->Gen( PUSH , reg( ebx ) );
			if ( oincr == type )
				cg->Gen( INC , reg( ebx ) );
			else
				//odecr
				cg->Gen( DEC , reg( ebx ) );
			cg->Gen( MOV , addr( eax ) , reg( ebx ) );
		}
		else
		{
			left->GenAddr( cg );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( PUSH , addr( eax ) );
			cg->Gen( FLD , addr( eax ) );
			cg->Gen( FLD1 );
			if ( oincr == type )
				cg->Gen( FADDP , reg( st1 ) , reg( st0 ) );
			else
				//odecr
				cg->Gen( FSUBP , reg( st1 ) , reg( st0 ) );
			cg->Gen( FSTP , addr( eax ) );
		}
	}
	//if right
	else
	{
		if ( typ->IsInt() )
		{
			right->GenAddr( cg );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( MOV , reg( ebx ) , addr( eax ) );
			if ( oincr == type )
				cg->Gen( INC , reg( ebx ) );
			else
				//odecr
				cg->Gen( DEC , reg( ebx ) );
			cg->Gen( MOV , addr( eax ) , reg( ebx ) );
			cg->Gen( PUSH , reg( ebx ) );
		}
		else
		{
			right->GenAddr( cg );
				cg->Gen( MOV , reg( eax ) , addr( esp ) );
				cg->Gen( FLD , addr( eax ) );
				cg->Gen( FLD1 );
			if ( oincr == type )				
				cg->Gen( FADDP , reg( st1 ) , reg( st0 ) );
			else
				//odecr
				cg->Gen( FSUBP , reg( st1 ) , reg( st0 ) );
			cg->Gen( FST , addr( esp ) );
			cg->Gen( FSTP , addr( eax ) );
		}
	};
	cg->Gen( Com , End( Comment() ) );
	return;
}
void TUnaryOp::GenAddr( CodeGen *cg )
{
	//can only be called for generating smth like "++some = (...)" or "--some = (...)"
	//both for floats and for ints
	TSymbol *typ = exprtype->GetRealType();
	cg->Gen( Com , Begin( Comment() ) );

	//if ++some or --some asked to generate the address expression
	if ( typ->IsInt() )
	{
		right->GenAddr( cg );
		cg->Gen( POP , reg( eax ) );
		if ( oincr == type )			
			cg->Gen( INC , addr( eax ) );
		//decr
		else
			cg->Gen( DEC , addr( eax ) );
		cg->Gen( PUSH , reg( eax ) );
	}
	else
	{
		right->GenAddr( cg );
		cg->Gen( MOV , reg( eax ) , addr( esp ) );
		cg->Gen( FLD , addr( eax ) );
		cg->Gen( FLD1 );
		if ( oincr == type )
			cg->Gen( FADDP , reg( st1 ) , reg( st0 ) );
		//decr
		else
			cg->Gen( FSUBP , reg( st1 ) , reg( st0 ) );
		cg->Gen( FSTP , addr( eax ) );
	}
	cg->Gen( Com , End( Comment() ) );
	return;
}
void TUnaryOp::Print( int level )
{
	if ( right != NULL )
		right->Print( level+1 );
	Tab( level );
	cout << "````";
	cout << source << '\n';
	if ( left != NULL )
		left->Print( level+1 );
}


TListExpr::TListExpr()
{
	ListExpr = new vector<TExpr*>();
}
TListExpr::TListExpr( TExpr *n )
{
	ListExpr = new vector<TExpr*>();
	ListExpr->push_back( n );
	type = none;
}
TListExpr::TListExpr( TExpr *n1 , TExpr *n2 )
{
	ListExpr = new vector<TExpr*>();
	ListExpr->push_back( n1 );
	ListExpr->push_back( n2 );
	type = none;
}
bool TListExpr::IsAlive()
{
	for ( int i = 0; i < ListExpr->size() ; ++i )
		if ( (*ListExpr)[i]->IsAlive() )
			return true;
	return false;
}
void TListExpr::Gen( CodeGen *cg )
{
	cg->Gen( Com , Begin( Comment() ) );
	GenHelper( cg );
	cg->Gen( Com , str( "lists's final element" ) );
	(*ListExpr)[ ListExpr->size() - 1 ]->Gen( cg );
	cg->Gen( Com , End( Comment() ) );
}
void TListExpr::GenAddr( CodeGen *cg )
{
	cg->Gen( Com , Begin( Comment() ) );
	GenHelper( cg );
	cg->Gen( Com , str( "lists's final element" ) );
	(*ListExpr)[ ListExpr->size() - 1 ]->GenAddr( cg );
	cg->Gen( Com , End( Comment() ) );
}
void TListExpr::GenHelper( CodeGen *cg )
{
	cg->Gen( Com , Begin( "ALL ELEMENTs BUT THE LAST" ) ); 
	int togen = ListExpr->size() - 1;
	for ( int i = 0 ; i < togen ; ++i )
	{
		(*ListExpr)[i]->Gen( cg );
		cg->Gen( ADD , reg( esp ) , imm( 4 ) );
	}
	cg->Gen( Com , End( "ALL ELEMENTs BUT THE LAST" ) );
}
string TListExpr::Comment()
{
	string comment;
	for ( int i = 0 ; i < ListExpr->size() ; ++i )
		comment += (*ListExpr)[i]->Comment() + " , ";
	return comment;
}
bool TListExpr::IsListExpr()
{
	return true;
}
void TListExpr::AddExpr( TExpr *add )
{
	ListExpr->push_back( add );
}
void TListExpr::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{        
	islvalue = (*ListExpr)[ ListExpr->size() - 1 ]->islvalue;
	exprtype = (*ListExpr)[ ListExpr->size() - 1 ]->exprtype;
}
void TListExpr::Print( int level )
{
	for ( int i = ListExpr->size()-1 ; i > -1 ; --i )
	{
		(*ListExpr)[i]->Print( level + 1 );
		if ( i )
		{
			Tab( level );
			cout << "````" << ',' << '\n';
		}
	}
}


bool TStatement::IsExpr()
{
	return 0;
}


TBlockStmt::TBlockStmt()
{
	breaks = continues = false;
	source = "block";
	blocktable = new TSymTable();
}
TSymTable *TBlockStmt::ShowTable()
{
	return blocktable;
}
void TBlockStmt::AddStmt( TSyntaxObject *synt )
{
	syntlist.push_back( synt );
	if ( synt->HasBreaks() )
		breaks = true;
	if ( synt->HasContinues() )
		continues = true;
}
void TBlockStmt::Gen( CodeGen *cg )
{
	if ( HasBreaks() || HasContinues() )
		cg->AddHaltPops( blocktable->GetSize() );
	cg->Gen( Com , Begin( "BLOCK STATEMENT" ) );
	//PUSHing local vars
	PushLocalVars( cg );
	//generating nested statements,
	//may be block statements or "if" or "while" including a block
	for ( int i = 0 ; i < syntlist.size() ; ++i )
	{
		syntlist[i]->Gen( cg );
		if ( syntlist[i]->CleanupNeeded() )
		{
			cg->Gen( Com , str( "...cleaning..." ) );
			cg->Gen( ADD , reg( esp ) , imm( 4 ) );
		}
	}
	//POPing local vars
	PopLocalVars( cg );	
	cg->Gen( Com , End( "BLOCK STATEMENT" ) );
	if ( HasBreaks() || HasContinues() )
		cg->SubHaltPops( blocktable->GetSize() );
}
void TBlockStmt::PushLocalVars( CodeGen *cg )
{
	cg->Gen( Com , Begin( "PUSHing local variables" ) );
	blocktable->Gen( cg );
	cg->Gen( Com , End( "PUSHing local variables" ) );
}
void TBlockStmt::PopLocalVars( CodeGen *cg )
{
	cg->Gen( Com , Begin( "POPing local variables" ) );
	int size = blocktable->GetSize();
	if ( size )
		cg->Gen( ADD , reg( esp ) , imm( size ) );
	cg->Gen( Com , End( "POPing local variables" ) );
}
void TBlockStmt::Print( int level )
{
	Tab( level );
	cout << "{\n";
	Tab( level + 1 );
	cout << "declarations:\n";
	blocktable->Print( level + 1 );
	Tab( level + 1 );
	cout << "statements:\n";
	for ( int i = 0 ; i < syntlist.size() ; ++i )
		syntlist[i]->Print( level + 1 );
	Tab( level );
	cout << "}\n";
}
void TBlockStmt::CalcTableSizes( int offset )
{
	blocktable->CalcSize();
	blocktable->InitOffset( offset );

	vector<TSyntaxObject *> *list = &syntlist;
	int size = syntlist.size();
	for ( int i = 0 ; i<size ; ++i )
		if ( (*list)[i]->HasBlock() || (*list)[i]->IsBlock() )
			(*list)[i]->CalcTableSizes( blocktable->GetSize() + blocktable->GetOffset() );
}


TEmptyStmt::TEmptyStmt()
{
	source = "empty";
}
void TEmptyStmt::Print( int  )
{}
void TEmptyStmt::Gen( CodeGen *cg )
{
	if ( cg->ComEnabled() )
		cg->Gen( LABEL , str( ";WARNING: TEmptyStmt has been generated; possibly mistake" ) );
}

TIfStmt::TIfStmt( TExpr *c )
	:condition( c ), trueblock( new TEmptyStmt() ), falseblock( new TEmptyStmt() )
{
	breaks = false;
	continues = false;
	source = "if";
}
void TIfStmt::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	TSymbol *typ;
	if( condition->IsFunccallOp() )
		typ = condition->GetFuncType();
	else
		typ = condition->GetRealType();
	if ( !typ->IsInt() && !typ->IsFloat() )
		throw NumTypExp( pos , condition->source );
	if ( condition->GetType()->IsFloat() )
		CreateTypeCast( condition , GlobSymTable->GetElemN( 0 ) , opt );
}
string TIfStmt::Comment()
{
	return "IF STATEMENT";
}
void TIfStmt::AddTrueBlock( TStatement *stmt )
{
	if ( stmt->HasContinues() )
		continues = true;
	if ( stmt->HasBreaks() )
		breaks = true;
	trueblock = stmt;
}
void TIfStmt::AddFalseBlock( TStatement *stmt )
{
	if ( stmt->HasContinues() )
		continues = true;
	if ( stmt->HasBreaks() )
		breaks = true;
	falseblock = stmt;
}
void TIfStmt::Gen( CodeGen *cg )
{
	cg->Gen( Com , Begin( Comment() ) );
	string label1 = cg->GenLabel();

	cg->Gen( Com , Begin( "CONDITION" ) );
	condition->Gen( cg );
	cg->Gen( Com , End( "CONDITION" ) );
	
	cg->Gen( POP , reg( eax ) );
	cg->Gen( TEST , reg( eax ) , reg( eax ) );
	cg->Gen( JZ , str( label1 ) );
	cg->Gen( Com , Begin( "TRUE BLOCK" ) );
	trueblock->Gen( cg );
	cg->Gen( Com , End( "TRUE BLOCK" ) );

	if ( !falseblock->IsEmptyStmt() )
	{
		string label2 = cg->GenLabel();
		cg->Gen( JMP , str( label2 ) );
		cg->Gen( LABEL , str( label1 ) );
		cg->Gen( Com , Begin( "FALSE BLOCK" ) );
		falseblock->Gen( cg );
		cg->Gen( Com , End( "FALSE BLOCK" ) );
		cg->Gen( LABEL , str( label2 ) );	
	}
	else
		cg->Gen( LABEL , str( label1 ) );
	cg->Gen( Com , End( Comment() ) );
}

void TIfStmt::Print( int level )
{
	Tab( level );
	cout << "if-statement.  condition:\n";
	condition->Print( level + 1 );
	Tab( level );
	cout << "trueblock:\n";
	trueblock->Print( level );
	Tab( level );
	cout << "falseblock:\n";
	falseblock->Print( level );
	Tab( level );
	cout << "end if-statement\n";
}
void TIfStmt::CalcTableSizes( int offset )
{
	if ( trueblock )
		trueblock->CalcTableSizes( offset );
	if ( falseblock )
		falseblock->CalcTableSizes( offset );
}

TForStmt::TForStmt( TExpr *c )
	:condition( c )
{}
void TForStmt::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	TSymbol *typ;
	if( condition->IsFunccallOp() )
		typ = condition->GetFuncType();
	else
		typ = condition->GetRealType();
	if ( !typ->IsInt() && !typ->IsFloat() )
		throw NumTypExp( pos , condition->source );
	if ( condition->GetType()->IsFloat() )
		CreateTypeCast( condition , GlobSymTable->GetElemN( 0 ) , opt );
}
void TForStmt::AddBlock( TStatement *stmt )
{
	block = stmt;
}
void TForStmt::Gen( CodeGen *cg )
{
	string label1 = cg->GenLabel();
	string label2 = cg->GenLabel();
	//if breaks will appear
	if ( block->HasBreaks() || block->HasContinues() )
	{
		cg->PushHaltPops();
		if ( block->HasBreaks() )
			cg->PushBreak( cg->GenLabel() );
		if ( block->HasContinues() )
			cg->PushContinue( label1 );
	}
	
	//if continue instruction will appear:	
	cg->Gen( Com , Begin( Comment() ) );
	cg->Gen( JMP , str( label1 ) );
	cg->Gen( LABEL , str( label2 ) );
	block->Gen( cg );
	cg->Gen( LABEL , str( label1 ) );
	cg->Gen( Com , Begin( "CONDITION" ) );
	condition->Gen( cg );
	cg->Gen( Com , End( "CONDITION" ) );
	cg->Gen( POP , reg( eax ) );
	cg->Gen( TEST , reg( eax ) , reg( eax ) );
	cg->Gen( JNZ , str( label2 ) );
	//exit for break
	if ( block->HasBreaks() )
		cg->Gen( LABEL , str( cg->GetBreakLabel() ) );
	cg->Gen( Com , End( Comment() ) );
	//if there were breaks...
	if ( block->HasBreaks() || block->HasContinues() )
	{
		cg->PopHaltPops();
		if ( block->HasBreaks() )
			cg->PopBreak();
		if ( block->HasContinues() )
			cg->PopContinue();
	}
}
void TForStmt::CalcTableSizes( int offset )
{
	if ( block )
		block->CalcTableSizes( offset );
}
void TForStmt::Print( int level )
{
	Tab( level );
	cout << "for-statement. condition:\n";
	condition->Print( level + 1 );
	Tab( level );
	cout << "block:\n";
	block->Print( level );
	Tab( level );
	cout << "end for-statement\n";
}
string TForStmt::Comment()
{
	return "FOR STATEMENT";
}

TWhileStmt::TWhileStmt( TExpr *c )
	:condition( c )
{
	continues = false;
	breaks = false;
	source = "while";
	block = new TBlockStmt();
}
void TWhileStmt::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	TSymbol *typ;
	if( condition->IsFunccallOp() )
		typ = condition->GetFuncType();
	else
		typ = condition->GetRealType();
	if ( !typ->IsInt() && !typ->IsFloat() )
		throw NumTypExp( pos , condition->source );
	if ( condition->GetType()->IsFloat() )
		CreateTypeCast( condition , GlobSymTable->GetElemN( 0 ) , opt );
}
void TWhileStmt::Print( int level )
{
	Tab( level );
	cout << "while-statement. condition:\n";
	condition->Print( level + 1 );
	Tab( level );
	cout <<"block:\n";
	block->Print( level );
	Tab( level );
	cout << "end while-statement\n";
}
void TWhileStmt::AddBlock( TStatement *stmt )
{
	block = stmt;
}
string TWhileStmt::Comment()
{
	return "WHILE STATEMENT";
}
void TWhileStmt::Gen( CodeGen *cg )
{
	string label1 = cg->GenLabel();
	string label2 = cg->GenLabel();
	if ( block->HasBreaks() || block->HasContinues() )
	{
		if ( block->HasBreaks() )
			cg->PushBreak( cg->GenLabel() );
		if ( block->HasContinues() )
			cg->PushContinue( cg->GenLabel() );
		cg->PushHaltPops();
	}	
	cg->PushContinue( label1 );
	cg->Gen( Com , Begin( Comment() ) );
	cg->Gen( JMP , str( label1 ) );
	cg->Gen( LABEL , str( label2 ) );
	block->Gen( cg );
	cg->Gen( LABEL , str( label1 ) );
	cg->Gen( Com , Begin( "CONDITION" ) );
	condition->Gen( cg );
	cg->Gen( Com , End( "CONDITION" ) );
	cg->Gen( POP , reg( eax ) );
	cg->Gen( TEST , reg( eax ) , reg( eax ) );
	cg->Gen( JNZ , str( label2 ) );
	//exit for break
	if ( block->HasBreaks() )
		cg->Gen( LABEL , str( cg->GetBreakLabel() ) );
	cg->Gen( Com , End( Comment() ) );
	if ( block->HasBreaks() || block->HasContinues() )
	{
		cg->PopHaltPops();
		if ( block->HasBreaks() )
			cg->PopBreak();
		if ( block->HasContinues() )
			cg->PopContinue();
	}
}
void TWhileStmt::CalcTableSizes( int offset )
{
	if ( block )
		block->CalcTableSizes( offset );
}


TJumpStmt::TJumpStmt( string jmp , TSymTable *GlobSymTable , TSymTableStack *stack , TExpr *retval )
	:value( retval )
{
	source = jmp;
	if ( source == "return" )
	{
		localtable = stack->ShowLocalTable();
		funcname = GlobSymTable->GetLastSym()->funcname;
	}
}
void TJumpStmt::Gen( CodeGen *cg )
{
	if ( "return" == source )
	{
		cg->Gen( Com , Begin( "RETURN" ) );
		if ( value->IsEmptyExpr() )
			cg->Gen( XOR , reg( eax ) , reg( eax ) );
		else
		{
			value->Gen( cg );
			cg->Gen( POP , reg( eax ) );
		}
		int topop = localtable->GetSize() + localtable->GetOffset();
		cg->Gen( ADD , reg( esp ) , imm( topop ) );
		cg->Gen( JMP , str( "return_" + funcname ) );
		cg->Gen( Com , End( "RETURN" ) );
	}
	else
		if ( "continue" == source )
		{
			cg->Gen( Com , Begin( "CONTINUE" ) );
			cg->Gen( ADD , reg( esp ) , imm( cg->HaltPops() ) );
			cg->Gen( JMP , str( cg->GetContinueLabel() ) );
			cg->Gen( Com , End( "CONTINUE" ) );
		}
		else
		{
			cg->Gen( Com , Begin( "BREAK" ) );
			cg->Gen( ADD , reg( esp ) , imm( cg->HaltPops() ) );
			cg->Gen( JMP , str( cg->GetBreakLabel() ) );
			cg->Gen( Com , End( "BREAK" ) );
		}
}
void TJumpStmt::Print( int level )
{
	Tab( level );
	cout << "jump statement:   " << source << "\n";
	if ( "return" == source )
		value->Print( level + 1 );
	cout << "\n";            
}
TSwitchStmt::TSwitchStmt( TExpr *e )
	:switchexpr( e )
{
	continues = false;
	breaks = false;
}
void TSwitchStmt::Gen( CodeGen *cg )
{
	vector < string > *labels = new vector< string >();
	string temp, deflab, exitlab = "";
	if ( breaks )
		cg->PushBreak( cg->GenLabel() );
	//gen expression
	cg->Gen( Com , Begin( "switch expression" ) );
	switchexpr->Gen( cg );
	cg->Gen( Com , End( "switch expression" ) );

	//gen conditions
	cg->Gen( Com , Begin( "switch conditions" ) );
	//generating conditions, jumps
	//have to generate label to default block
	//cause won't be able to do this in the next loop
	//but i add it to the labelstack
	if ( defaultN != -1 )
		deflab = cg->GenLabel();
	for ( int i = 0 ; i < caselist->size() ; ++i )
	{
		if ( i != defaultN )
		{
			(*caselist)[i]->expr->Gen( cg );
			cg->Gen( POP , reg( eax ) );
			cg->Gen( POP , reg( ebx ) );
			cg->Gen( CMP , reg( eax ) , reg( ebx ) );
			temp = cg->GenLabel();
			cg->Gen( JE , str( temp ) );
			labels->push_back( temp );
			cg->Gen( PUSH , reg( ebx ) );
		}
		else
			labels->push_back( deflab );
	}
	cg->Gen( ADD , reg( esp ) , imm( 4 ) );
	//if all conditions were false:
	//if there was default, jump to it
	if ( defaultN != -1 )
		cg->Gen( JMP , str( deflab ) );
	//if no default
	else
	{
		//if we have breaks then use their label
		if ( breaks )
			cg->Gen( JMP, str( cg->GetBreakLabel() ) );
		//else make new label to exit
		else
		{	
			exitlab = cg->GenLabel();
			cg->Gen( JMP, str( exitlab ) );
		}
	}
	cg->Gen( Com , End( "switch conditions" ) );


	//generating bodies
	cg->Gen( Com , End( "switch bodies" ) );
	//we have caselist and label stack, they are mapped
	//one into another
	for ( int i = 0 ; i < caselist->size() ; ++i )
	{
		if ( (*caselist)[i]->block->HasBreaks() )		
			cg->PushHaltPops();
		if ( i != defaultN )
			cg->Gen( LABEL , str( (*labels)[i] ) );
		else
			cg->Gen( LABEL , str( deflab ) );
		(*caselist)[i]->block->Gen( cg );
		if ( (*caselist)[i]->block->HasBreaks() )
			cg->PopHaltPops();
	}
	cg->Gen( Com , End( "switch bodies" ) );
	
	//putting labels...
	if ( breaks )
	{
		cg->Gen( Com , str( "for breaks" ) );
		cg->Gen( LABEL , str( cg->GetBreakLabel() ) );
	}
	else
		if ( exitlab != "" )
		{
			cg->Gen( Com , str( "for exit" ) );
			cg->Gen( LABEL , str( exitlab ) );
		}

	//kill break label for this switch
	if ( breaks )
		cg->PopBreak();
}
void TSwitchStmt::Print( int level )
{
	Tab( level );
	cout << "SWITCH statement\n";
	Tab( level );
	cout << "expression:\n";
	Tab( level );
	switchexpr->Print( level + 1 );
	for ( int i = 0 ; i < caselist->size() ; ++i )
	{
		Tab( level );
		if ( (*caselist)[i]->expr->IsEmptyExpr() )
			cout << "default:\n";
		else
		{
			cout << "case:\n";
			(*caselist)[i]->expr->Print( level + 1 );
		}
		Tab( level );
		cout << "tied body:\n";
		(*caselist)[i]->block->Print( level + 1 );
	}
	Tab( level );
	cout << "END SWITCH statement\n";
}
void TSwitchStmt::Init( vector< CaseStruct * > *list , int num )
{
	caselist = list;
	for ( int i = 0; i < list->size() ; ++i )
		if ( (*list)[i]->block->HasBreaks() )
			breaks = true;
	defaultN = num;
}
void TSwitchStmt::TypeCheck( TSymTable *GlobSymTable , Position pos , bool opt )
{
	map<int,bool> *cases;
	cases = new map<int,bool>();
	if ( caselist->size() )
	{
		for ( int i = 0 ; i < caselist->size() ; ++i )
		{
			if ( i == defaultN )
			{
				++i;
				continue;
			}
			if ( cases->find( (*caselist)[i]->expr->GetInt() ) != cases->end() )
				throw RepCases( pos );
			else
				(*cases)[ (*caselist)[i]->expr->GetInt() ] = 1;
		}
	}
}
void TSwitchStmt::CalcTableSizes( int offset )
{
	for ( int i = 0 ; i < caselist->size() ; ++i )
		(*caselist)[i]->block->CalcTableSizes( offset );
}
//is used when TypeCast objects are created IN TypeCheck()
void CreateTypeCast( TExpr *&val , TSymbol *totype , bool opt )
{
	if ( opt && val->IsConstExpr() && ( totype != val->GetType() ) )
	{
		TExpr *copy = val;
		if ( totype->IsFloat() )
			val = new TConstExpr( "float( " + val->source + " ) " , float( val->GetInt() ), totype );
		else
			val = new TConstExpr( "int( " + val->source + " ) " , int( val->GetFloat() ), totype );
		delete( copy );
	}
	else
		val = new TTypeCast( totype , val );
}