#include "parser.h"


Parser::Parser( Scanner &s , TSymTable *glob , bool opt )
	:scanner( s ), GlobSymTable( glob ), optimizing( opt )
{
	scanner.Next();
	stack = new TSymTableStack( GlobSymTable );
}


bool Parser::EqualSignats( TSymbol* func1 , TSymbol* func2 )
{
	if ( func1->GetRealType() != func2->GetRealType() )
		return 0;  
	if ( func1->argtable->GetNumElems() != func2->argtable->GetNumElems() )
		return 0;
	TSymbol *s1, *s2;

	for ( int i = 0 , size = func1->argtable->GetNumElems() ; i < size ; ++i )
	{
		s1 = func1->argtable->GetElemN( i );
		s2 = func2->argtable->GetElemN( i );
		if ( s1->varname != s2->varname )
			return 0;

		if ( s1->GetType()->aliastypename != s2->GetType()->aliastypename )
			return 0;

		if ( !s1->GetRealType()->IsArray() && !s2->GetRealType()->IsArray() )
		{
			if ( s1->GetRealType() != s2->GetRealType() )
				return 0;
		}
		else
			if ( s1->GetRealType()->IsArray() && s2->GetRealType()->IsArray() )
			{
				if ( !EqualArrays( s1->GetRealType() , s2->GetRealType()) )
					return 0;
			}
			else
				return 0;
	}
	return 1;
}


//PARSING STATEMENTS
void Parser::ParseJumpStmt( TBlockStmt *block )
{
	Type jumptype = scanner.GetCurrType();
	string jumpstr = scanner.GetCurrSource();

	if ( jumptype == kreturn )
	{
		TSymbol *curr_func_type = GlobSymTable->GetLastSym()->GetType()->GetRealType();
		scanner.Next();
		//if there is smth to return
		if ( scanner.GetCurrType() != ssemic )
		{
			TExpr *retval = ParseExpr();
			TSymbol *rettype;
			if ( retval->IsFunccallOp() )
				rettype = retval->GetFuncType();
			else
				rettype = retval->GetRealType();

			if ( !rettype->IsSimpleType() )
				throw ForbidReturnType( scanner.GetCurrPos() , "" );
			if ( rettype != curr_func_type )
				CreateTypeCast( retval , curr_func_type , optimizing );
			scanner.Require( ssemic );
			block->AddStmt( new TJumpStmt( jumpstr , GlobSymTable , stack , retval ) );
			return;
		}
		//if nothing was returned
		if ( curr_func_type->IsInt() )
			block->AddStmt( new TJumpStmt( jumpstr , GlobSymTable , stack , new TConstExpr( "0" , 0 , curr_func_type ) ) );
		else
			block->AddStmt( new TJumpStmt( jumpstr , GlobSymTable , stack , new TConstExpr( "0.0" , float(0) , curr_func_type ) ) );
		scanner.Require( ssemic );
		return;
	}
	if ( ( jumptype == kbreak ) || ( jumptype == kcontinue ) )
	{
		bool l = loop.IsInLoop(),
			s = cases.IsInLoop();
		if (  ( kbreak == jumptype ) && !l && !s  )
			throw NotLoopOrSwitch( scanner.GetCurrPos() , scanner.GetCurrSource() );
		if ( ( kcontinue == jumptype ) && !l )
			throw NotLoop( scanner.GetCurrPos() , scanner.GetCurrSource() );
		scanner.Next();
		scanner.Require( ssemic );
		block->AddStmt( new TJumpStmt( jumpstr , GlobSymTable , stack ) );
	}
}


void Parser::ParseForStmt( TBlockStmt *block )
{
	loop.LoopIn();
	scanner.Next();
	scanner.Require( slbrace );

	//if we have smth to do before "for"
	if ( scanner.GetCurrType() != ssemic )
	{
		string str = scanner.GetCurrSource();
		TSymbol *typ = stack->FindTypeGlobal( str );
		if ( !typ )
			block->AddStmt( ParseExpr() );
		else
		{
			scanner.Next();
			ParseDecl( typ );
			while ( scanner.GetCurrType() != ssemic )  
			{
				scanner.Require( scomma );
				ParseDecl( typ );
			}
		}
	}
	scanner.Require( ssemic );

	//parsing condition
	TExpr *condition;
	if ( scanner.GetCurrType() == ssemic )
		condition = new TConstExpr( ""  , 1 , GlobSymTable->GetElemN(0) );
	else
		condition = ParseExpr();
	scanner.Require( ssemic );

	//parsing afterward
	TExpr *afterward = ParseExpr();
	scanner.Require( srbrace );

	//creating for-object
	TForStmt *stfor = new TForStmt( condition );

	TBlockStmt *forblock;
	//parsing block or statement tied with for
	if ( scanner.GetCurrType() != ssemic )
	{		
		if ( scanner.GetCurrType() == slfigbrace )
		{
			scanner.Next();
			forblock = ParseBlock();
		}
		else
		{
			forblock = new TBlockStmt();
			stack->Push( forblock->ShowTable() );
			ParseStmt( forblock );
			stack->Pop();
		}
	}
	else
	{
		forblock = new TBlockStmt();
		scanner.Next();
	}
	forblock->AddStmt( afterward );
	stfor->AddBlock( forblock );
	stfor->TypeCheck( GlobSymTable , scanner.GetCurrPos() , optimizing );
	if ( optimizing && stfor->condition->IsConstExpr() && !stfor->condition->GetInt() )
		delete( stfor );
	else
		block->AddStmt( stfor );
	loop.LoopOut();
}
void Parser::ParseWhileStmt( TBlockStmt *block )
{
	loop.LoopIn();
	scanner.Next();
	scanner.Require( slbrace );
	TExpr *condition = ParseExpr();
	if ( condition->IsEmptyExpr() )
		throw ConditionMissed( scanner.GetCurrPos() );
	scanner.Require( srbrace );

	TWhileStmt *stwhile = new TWhileStmt( condition );
	TStatement *WBlock;
	if ( scanner.GetCurrType() != ssemic )
	{
		if ( scanner.GetCurrType() == slfigbrace )
		{
			scanner.Next();
			WBlock = ParseBlock();
		}
		else
		{
			TBlockStmt *temp = new TBlockStmt();
			ParseStmt( temp );
			WBlock = temp;
		}
	}
	else
	{
		WBlock = new TEmptyStmt();
		scanner.Next();
	}
	stwhile->AddBlock( WBlock );
	stwhile->TypeCheck( GlobSymTable , scanner.GetCurrPos() , optimizing );
	if ( optimizing && stwhile->condition->IsConstExpr() && !stwhile->condition->GetInt() )
		delete( stwhile );
	else
		block->AddStmt( stwhile );
	loop.LoopOut();	
}

void Parser::ParseIfStmt( TBlockStmt *block )
{
	scanner.Next();
	scanner.Require( slbrace );
	TExpr *condition = ParseExpr();
	if ( condition->IsEmptyExpr() )
		throw ConditionMissed( scanner.GetCurrPos() );
	scanner.Require( srbrace );
	TIfStmt *stif = new TIfStmt( condition );
	TStatement *TBlock, *FBlock;

	if ( scanner.GetCurrType() != ssemic )
	{
		if ( scanner.GetCurrType() == slfigbrace )
		{
			scanner.Next();
			TBlock = ParseBlock();
		}
		else
		{
			TBlockStmt *temp = new TBlockStmt();
			ParseStmt( temp );
			TBlock = temp;
		}
		if ( scanner.GetCurrType() == kelse )
		{
			scanner.Next();
			if ( scanner.GetCurrType() == slfigbrace )
			{
				scanner.Next();
				FBlock = ParseBlock();
			}
			else
			{
				TBlockStmt *temp = new TBlockStmt();
				ParseStmt( temp );
				FBlock = temp;
			}
		}
		else
			FBlock = new TEmptyStmt();
	}
	else
	{
		TBlock = FBlock = new TEmptyStmt();
		scanner.Next();
	}
	
	stif->TypeCheck( GlobSymTable , scanner.GetCurrPos() , optimizing );
	//optimizing
	if ( optimizing && stif->condition->IsConstExpr() )
	{
		delete( stif );
		if ( stif->condition->GetInt() )
		{
			delete( FBlock );
			block->AddStmt( TBlock );
		}
		else
		{
			delete( TBlock );
			block->AddStmt( FBlock );			
		}
	}
	else
	{
		stif->AddTrueBlock( TBlock );
		stif->AddFalseBlock( FBlock );
		block->AddStmt( stif );
	}
	
}
void Parser::ParseSwitchStmt( TBlockStmt *block )
{
	cases.LoopIn();
	scanner.Next();
	scanner.Require( slbrace );
	TExpr *switchexpr = ParseExpr();
	if ( !switchexpr->GetRefdObjType()->IsInt() )
		throw IntExpSwitch( scanner.GetCurrPos() );
	if ( switchexpr->IsEmptyExpr() )
		throw ConditionMissed( scanner.GetCurrPos() );
	scanner.Require( srbrace );
	scanner.Require( slfigbrace );

	TSwitchStmt *swstmt = new TSwitchStmt( switchexpr );
	TExpr *temp;
	vector < CaseStruct * > *caselist = new vector< CaseStruct * >();
	bool deffound = false;
	int firstnotinited = 0, defnum = -1;
	Type tok;
	TBlockStmt *caseblock;
	
	while ( srfigbrace != scanner.GetCurrType() )
	{
		//parse "default:" or "case const:"
		tok = scanner.GetCurrType();		
		if ( ( kcase != tok ) && ( kdefault != tok ) )
			throw DefaultOrCase( scanner.GetCurrPos() , scanner.GetCurrSource() );
		if ( ( kdefault == tok ) && deffound )
			throw DefaultTwice( scanner.GetCurrPos() );
		scanner.Next();
		if ( kcase == tok )
		{
			temp = ParseExpr();
			if ( !temp->GetRefdObjType()->IsInt() )
				throw IntExpSwitch( scanner.GetCurrPos() );
			if ( !temp->IsConstExpr() )
				throw NonConstInSwitch( scanner.GetCurrPos() );
		}
		scanner.Require( scolon );
		
		if ( kcase == tok )
			caselist->push_back( new CaseStruct( temp ) );
		else
		{
			caselist->push_back( new CaseStruct( new TEmptyExpr() ) );
			defnum = caselist->size() - 1;
			deffound = true;
		}

		//if block or statement found then use it to initialize everything met before
		if ( ( kcase != scanner.GetCurrType() ) && ( kdefault != scanner.GetCurrType() ) )
		{			
			if ( slfigbrace == scanner.GetCurrType() )
			{
				scanner.Next();
				caseblock = ParseBlock();
			}
			else
			{
				caseblock = new TBlockStmt();
				ParseStmt( caseblock );
			}

			if ( caseblock->HasBreaks() )
				swstmt->breaks = true;
			//standing after all semicolons
			while ( ssemic == scanner.GetCurrType() )
				scanner.Next();
			for ( int i = firstnotinited ; i < caselist->size() ; ++i )
				(*caselist)[i]->block = caseblock;
			firstnotinited = caselist->size();
		}
	}
	scanner.Next();
	swstmt->Init( caselist , defnum );
	swstmt->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
	block->AddStmt( swstmt );
	cases.LoopOut();
}


void Parser::ParseStmt( TBlockStmt *block )
{
	switch ( scanner.GetCurrType() )
	{
	case ssemic:
		{
			scanner.Next();
			break;
		}
	case slfigbrace:
		{
			scanner.Next();
			block->AddStmt( ParseBlock() );
			break;
		}
	case ktypedef:
		{
			ParseTypedefDecl();
			break;
		}
	case kbreak:
	case kreturn:
	case kcontinue:
		{
			ParseJumpStmt( block );
			break;
		}
	case kswitch:
		{
			ParseSwitchStmt( block );
			break;
		}
	case kstruct:
	case kint:
	case kfloat:
		{
			ParseListDecl(); 
			break;
		}
	case kif:
		{
			ParseIfStmt( block );
			break;
		}
	case kwhile:
		{
			ParseWhileStmt( block );
			break;
		}
	case kfor:
		{
			ParseForStmt( block );
			break;
		}
	case name:
		{
			TSymbol *typedecl;
			if (  ( typedecl = stack->FindTypeGlobal( scanner.GetCurrSource() ) ) != NULL  )
			{
				ParseListDecl();
				break; 
			}
		}
	default:
		{
			TExpr *temp = ParseExpr();
			//if ! optimizing or optimizing and object is not alive
			//a*b+!b == !(!a*b)
			//cout << temp->IsAlive();
			if ( !( !temp->IsAlive() && optimizing ) )
				block->AddStmt( temp );
			else
				delete( temp );
			scanner.Require( ssemic );
		}
	}
}


//PARSING DECLARATIONS
TBlockStmt *Parser::ParseBlock( TSymTable *argtable )
{
	TBlockStmt *block = new TBlockStmt();
	if ( argtable )
		block->blocktable->AddTableElems( argtable );
	stack->Push( block->ShowTable() );
	//standing right after "{"
	while ( scanner.GetCurrType() != srfigbrace )
		ParseStmt( block );
	//let's stand right after "}"
	scanner.Next();
	stack->Pop();
	return block;
}


void Parser::ParseListArgs( TSymFunc *funcdecl )
{
	TSymbol *type;
	string typname, argname;
	bool ref, isstruct;
	TSymVar *newvar;
	while ( scanner.GetCurrType() != srbrace )
	{
		ref = isstruct = false;
		Position postype=scanner.GetCurrPos();
		if ( scanner.GetCurrType() == kstruct )
		{
			isstruct = true;
			scanner.Next();
		}
		typname = scanner.GetCurrSource();

		if ( ( type = stack->FindTypeGlobal( typname ) ) == NULL )
			throw UnknownType( scanner.GetCurrPos() , scanner.GetCurrSource() );            

		scanner.Next();
		if ( scanner.GetCurrType() == oamper )
		{
			ref = true;
			scanner.Next();
		}
		argname = scanner.GetCurrSource();
		scanner.Require( name );
		if ( funcdecl->FindArg( argname ) )
			throw ArgRedif( scanner.GetCurrPos() , argname );

		if ( ref )
		{
			if ( !type->IsAlSimpleType() && !type->IsAlStrucType()
				&& !type->IsSimpleType() && !type->IsStrucType() )
				throw SimpStrucTypExp(postype, typname);
			TypeRefer *reftype = new TypeRefer( type );
			newvar = new TSymVar( argname , reftype , stack );
		}
		else
		{
			if ( !type->IsAlSimpleType() && !type->IsAlStrucType() )
				throw SimpArrTypExp( postype , typname );
			if ( scanner.GetCurrType() == slsqbrace )
				newvar = new TSymVar( argname , new TypeRefer( ParseArrayType( type ) ) , stack );
			else
				if ( type->IsAlStrucType() )
					newvar = new TSymVar( argname , new TypeRefer( type ) , stack );
				else
					newvar = new TSymVar( argname , type , stack );                
		}
		newvar->SetArgument();
		funcdecl->AddArg( newvar );

		if ( scanner.GetCurrType() != srbrace )
			scanner.Require( scomma );
	}
	scanner.Next();
}


TSymbol *Parser::ParseFuncDecl( string declname , TSymbol *decltype )
{
	if ( declname == "main" )
		if ( decltype->GetRealType()->simpletypename != "int" )
			throw IntMain( scanner.GetCurrPos() , "" );
	bool repdecl = false;
	TSymbol *redeclared;
	if ( ( redeclared = GlobSymTable->Find( declname ) ) != NULL )
	{
		if ( !redeclared->IsFunc() )
			throw IdentRedif( scanner.GetCurrPos() , declname );
		if ( redeclared->HasBody() )
			throw FuncDefined( scanner.GetCurrPos() , declname );
		repdecl = true;
	}

	TSymFunc *funcdecl = new TSymFunc( declname , decltype );

	stack->Push( funcdecl->argtable );//args have ref to argtable, they take it in TSymVar() through stack
	ParseListArgs( funcdecl );
	stack->Pop();

	//args must be empty if main
	if ( declname == "main" )
		if ( funcdecl->argtable->GetNumElems() )
			throw MainNoArgs( scanner.GetCurrPos() , "" );

	if ( repdecl )
	{
		if (  !EqualSignats( funcdecl , redeclared )  )
			throw WrongFuncRedecl( scanner.GetCurrPos() , declname );
		delete( funcdecl );//!delete this
		return redeclared;//!and this  if you want to make decls and definition as different blocks
	}
	GlobSymTable->Add( funcdecl );//!and this & in Parse Decl too
	return funcdecl;
}


TSymbol *Parser::ParseArrayType( TSymbol *decltype )
{
	if ( scanner.GetCurrType() != slsqbrace )
		return decltype;
	scanner.Next();
	TExpr *e = ParsePrimExpr();
	if ( e->type != cint )
		throw IllegIndexType( scanner.GetCurrPos() , "" );
	scanner.Require( srsqbrace );
	return new TypeArray( e , ParseArrayType( decltype ) );
}


void Parser::ParseVarDecl( TSymbol *decltype , string &declname )
{
	if ( stack->FindLocal( declname ) != NULL )
		throw IdentRedif( scanner.GetCurrPos() , declname );
	TSymVar *newvar;
	if ( scanner.GetCurrType() == oassign )
	{            
		if ( !decltype->GetRealType()->IsSimpleType() )
			throw UserInit( scanner.GetCurrPos() , declname );
		newvar = new TSymVar( declname , decltype , stack );
		scanner.Next();
		TExpr *init = ParseAssignExpr();
		if ( decltype->GetRealType() != init->GetRealType() )
			CreateTypeCast( init , decltype , optimizing );
		newvar->PutValue( init );
	}
	else
		if ( scanner.GetCurrType() == slsqbrace )
		{
			TSymbol *typearray = ParseArrayType( decltype );
			newvar = new TSymVar( declname , typearray , stack );
		}
		else
			newvar = new TSymVar( declname , decltype , stack );
	stack->Add( newvar );
}


void Parser::ParseDecl( TSymbol *decltype )
{
	string declname = scanner.GetCurrSource();
	if ( scanner.GetCurrType() != name )
		throw IllegDeclIdent( scanner.GetCurrPos() , declname );
	scanner.Next();
	switch ( scanner.GetCurrType() )
	{
	case slbrace:
		{
			if ( stack->ShowLocalTable() != GlobSymTable )
				throw EmbeddedFunc( scanner.GetCurrPos() , declname );
			if ( !decltype->IsAlSimpleType() )
				throw ForbidReturnType( scanner.GetCurrPos() , "" );
			scanner.Next();
			TSymbol *funcdecl = ParseFuncDecl( declname , decltype );

			//GlobSymTable->Add(funcdecl); !!!and uncomment this (see ParseFuncDecl())
			if ( ( scanner.GetCurrType() == scomma ) || ( scanner.GetCurrType() == ssemic ) )
			{
				if ( declname == "main" )
					throw MainDeclForbid( scanner.GetCurrPos() , "" );
				return;
			}
			if ( scanner.GetCurrType() == slfigbrace )//if definition
			{		
				scanner.Next();
				//include arguments into the table of block
				TBlockStmt *block = ParseBlock( funcdecl->argtable );				
				block->blocktable->ThrowBackElems( funcdecl->argtable->GetNumElems() );
				//exclude arguments from the block

				//adds return, no matter if it exists

				/*TSymbol *curr_func_type=decltype->GetRealType();

				if (curr_func_type->simpletypename=="int")
				block->AddStmt(new TJumpStmt("return", new TConstExpr("0", 0, curr_func_type)));
				else
				block->AddStmt(new TJumpStmt("return", new TConstExpr("0.0", float(0), curr_func_type)));
				*/
				funcdecl->PutBody( block );
				scanner.EmulSemic();
				return;
			}
			throw UnexpLex( scanner.GetCurrPos() , scanner.GetCurrSource() );
		}
	case slsqbrace:
	case oassign:
	case scomma:
	case ssemic:
		{
			ParseVarDecl( decltype , declname );
			break;
		}
	default:
		throw IllegDeclIdent( scanner.GetCurrPos() , declname );
	}
}


void Parser::ParseTypedefDecl()
{
	scanner.Next();
	Type first = scanner.GetCurrType();
	TSymbol *old_t;

	if ( first == kstruct )
	{
		scanner.Next();
		string old_s = scanner.GetCurrSource();
		scanner.Require( name );
		old_t = stack->FindTypeGlobal( old_s );
		if ( old_t == NULL )
			throw UnknownType( scanner.GetCurrPos() , old_s );
		if ( !old_t->IsStrucType() )
			throw NonStructType( scanner.GetCurrPos() , old_s );
	}
	else
		if ( ( first == name ) || ( first == kint ) || ( first == kfloat ) )
		{
			old_t = stack->FindGlobal( scanner.GetCurrSource() );
			if ( old_t == NULL )
				throw OldMissed( scanner.GetCurrPos() , scanner.GetCurrSource() );
			if ( !old_t->IsType() )
				throw OldNotType( scanner.GetCurrPos() , scanner.GetCurrSource() );
			scanner.Next();
		}
		else
			throw OldNotType( scanner.GetCurrPos() , scanner.GetCurrSource() );
	string new_s = scanner.GetCurrSource();

	if ( stack->FindLocal( new_s ) != NULL )
		throw IdentRedif( scanner.GetCurrPos() , new_s );
	scanner.Require( name );
	stack->Add( new TypeAlias( old_t , new_s ) );
	scanner.Require( ssemic );
}


TSymTable *Parser::ParseStructBody()
{
    TSymTable *members = new TSymTable();
    TSymVar *currvar;
    int currsize = 0;
	TSymbol *membtype;
	string membname, membtypestr;
	while ( scanner.GetCurrType() != srfigbrace )
	{
		membtypestr = scanner.GetCurrSource();
		if ( ( membtype = stack->FindTypeGlobal( membtypestr ) ) == NULL )
			throw UnknownType( scanner.GetCurrPos() , membtypestr );
		do
		{
			scanner.Next();
			membname = scanner.GetCurrSource();
			scanner.Require( name );
			if ( members->FindVar( membname ) )
				throw MembRedecl( scanner.GetCurrPos() , membname );
			if ( scanner.GetCurrType() == slsqbrace )
				membtype = ParseArrayType( membtype );

			currvar = new TSymVar( membname , membtype , stack );
			//very important ( about - 4 ):
			currvar->InitOffset( currsize - 4 );
			currsize += currvar->GetSize();        
			members->Add( currvar );
		}
		while ( scanner.GetCurrType() == scomma );
		scanner.Require( ssemic );
	}	
    members->InitSize( currsize );
	scanner.Next();
	return members;
}


void Parser::ParseStructDecl( string structname )
{
	TSymTable *body = ParseStructBody();
	TypeStruct *newstruct = new TypeStruct( body , structname );
    newstruct->size = body->GetSize();
   	Type tok = scanner.GetCurrType();
	if ( tok == name )
	{
		if ( stack->FindLocal( scanner.GetCurrSource() ) != NULL )
			throw IdentRedif( scanner.GetCurrPos() , scanner.GetCurrSource() );
		if ( structname != "" )
			stack->Add( newstruct );
		stack->Add( new TSymVar( scanner.GetCurrSource() , newstruct , stack ) );
		scanner.Next();
		scanner.Require( ssemic );
		return;
	}
	if ( tok == ssemic )
	{
		if ( structname != "" )
			stack->Add( newstruct );
		else
			delete( body );
		scanner.Next();
		return;
	}
	throw WrongStructEnd( scanner.GetCurrPos() , scanner.GetCurrSource() );
}


void Parser::ParseListDecl()
{	
	if ( scanner.GetCurrType() == ktypedef )
	{
		ParseTypedefDecl();
		return;
	}

	TSymbol *typedecl;
	if ( scanner.GetCurrType() == kstruct )
	{
		scanner.Next();
		if ( scanner.GetCurrType() == slfigbrace )
		{
			scanner.Next();
			ParseStructDecl();
			return;
		}

		if ( scanner.GetCurrType() == name )
		{
			string stypename = scanner.GetCurrSource();
			Position p = scanner.GetCurrPos();
			scanner.Next();
			if ( scanner.GetCurrType() == slfigbrace )
			{
				if ( stack->FindLocal( stypename ) != NULL )
					throw IdentRedif( p , stypename );
				scanner.Next();
				ParseStructDecl( stypename );
				return;
			}

			if ( scanner.GetCurrType() == name )
			{
				typedecl = stack->FindTypeGlobal( stypename );
				if ( typedecl == NULL )
					throw UnknownType( scanner.GetCurrPos() , stypename );
				if ( !typedecl->IsStrucType() )
					throw NonStructType( scanner.GetCurrPos() , stypename );
			}
			else
				throw ErrStructBegin( scanner.GetCurrPos() , scanner.GetCurrSource() );
		}
	}
	else
		if ( scanner.GetCurrType() == name )
		{
			typedecl = stack->FindGlobal( scanner.GetCurrSource() );
			if ( typedecl == NULL )
				throw Unknown( scanner.GetCurrPos() , scanner.GetCurrSource() );
			if ( !typedecl->IsType() )
				throw UnknownType( scanner.GetCurrPos() , scanner.GetCurrSource() );
			scanner.Next();
		}
		else
			if ( (scanner.GetCurrType() == kint ) || ( scanner.GetCurrType() == kfloat ) )
			{
				typedecl = stack->FindGlobal( scanner.GetCurrSource() );
				scanner.Next();
			}
			else
				if ( scanner.GetCurrType()==ssemic )
				{
					scanner.Next();
					return;
				}
				else
					throw UnexpLex( scanner.GetCurrPos() , scanner.GetCurrSource() );

	ParseDecl( typedecl );
	while ( scanner.GetCurrType() != ssemic )
	{
		scanner.Require( scomma );
		ParseDecl( typedecl );
	}
	scanner.DeEmulSemic();
	//stand after all semicolons
	while ( scanner.GetCurrType() == ssemic )
		scanner.Next();
}


void Parser::ParseProgram()
{
	while ( scanner.GetCurrType() != eof )
		ParseListDecl();

	//let's see if every function is defined <=> has body, and if main is defined
	int top = GlobSymTable->ShowTable()->size();
	vector< TSymbol * > *Table = GlobSymTable->ShowTable();
	bool main_defined = false;
	for ( int i = 0 ; i < top ; ++i )
	{
		if ( (*Table)[i]->IsFunc() )
		{
			if ( !(*Table)[i]->HasBody() )
				throw UndefinedFunc( scanner.GetCurrPos() , (*Table)[i]->funcname );
			if ( (*Table)[i]->funcname == "main" )
				main_defined = true;
			(*Table)[i]->CalcTableSizes();
		}
	}
	if ( !main_defined )
		throw MainNotDefined( scanner.GetCurrPos() , "" );
}


//PARSING EXPRESSIONS
TExpr *Parser::ParseExpr()
{
	TExpr *e = ParseAssignExpr();
	if ( e->type == name )
		if ( !e->exprtype )
			throw Unknown( scanner.GetCurrPos() , e->source );

	if ( scanner.GetCurrType() != scomma )
		return e;

	e = new TListExpr( e );	
	TExpr *temp;

	while ( 1 )
	{
		if ( scanner.GetCurrType() != scomma )
		{
			e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );			
			return e;
		}
		scanner.Next();
		temp = ParseAssignExpr();
		if ( temp->type == name )
		{
			if ( !temp->exprtype )
				throw Unknown( scanner.GetCurrPos() , temp->source );
		}
		e->AddExpr( temp );
	}	
}


TExpr *Parser::ParseAssignExpr()
{
	TExpr *e = ParseBinExpr();
	
	//if assignment expression; prepare exception
	Type tok = scanner.GetCurrType();

	if ( ( tok == oassign ) || ( tok == oassignplus ) || ( tok == oassignmin )||
		( tok == oassigndiv ) || ( tok == oassignmul ) )
	{
		string source = scanner.GetCurrSource();
		scanner.Next();
		e = new TAssignOp( tok , source , e , ParseAssignExpr() );
		e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
	}
	return e;
}

TExpr *Parser::ParseBinExpr( int level )
{
	//stops ParseBinExpr recursion
	if ( level == 6 )
		return ParseUnaryExpr();
	TExpr *e = ParseBinExpr( level + 1 );
	while ( 1 )
	{
		Type tok = scanner.GetCurrType();
		string source = scanner.GetCurrSource();
		if ( !ops.IsBinOnLev( tok , level ) )
			return e;
		scanner.Next();
		e = new TBinaryOp( tok , source , e , ParseBinExpr( level + 1 ) );
		e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
		if ( optimizing )
			FoldBinaryOp( e );
	}			
}


TExpr *Parser::ParseUnaryExpr()
{
	if ( ops.IsUnary( scanner.GetCurrType() ) )
	{
		Type tok = scanner.GetCurrType();
		string source = scanner.GetCurrSource();
		scanner.Next();
		TExpr *e = new TUnaryOp( source , tok , ParseUnaryExpr() );
		e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
		if ( optimizing )
			FoldUnaryOp( e );
		return e;
	}
	return ParsePostfExpr();
}


TExpr *Parser::ParsePostfExpr()
{
	TExpr *e = ParsePrimExpr();	
	if ( scanner.GetCurrType() == slbrace )
	{
		scanner.Next();//
		TExpr *temp = ParseExpr();//Prim
		if ( temp->IsEmptyExpr() )
		{
			delete( temp );
			temp = new TListExpr();
		}
		else
			if( !temp->IsListExpr() )
				temp = new TListExpr( temp );
		scanner.Next();//
		e = new TFunccallOp( e , temp );
		e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
		return e;
	}
	while  ( 1 )
	{
		Type tok = scanner.GetCurrType();
		string source = scanner.GetCurrSource();
		if ( tok == slsqbrace )
		{
			scanner.Next();
			e = new TExtractArrayOp( e , ParseExpr() );
			e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
			scanner.Require( srsqbrace );
		}
		else
			if ( ( tok == oincr ) || ( tok == odecr ) )
			{
				scanner.Next();
				e = new TUnaryOp( source , e , tok );
				e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
				if ( optimizing )
					FoldUnaryOp( e );
			}
			else
					if ( tok == sdot )
					{
						scanner.Next();
						TExpr *s = ParsePrimExpr();
						e = new TExtractStructOp( e , s );
						e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
					}
					else
						return e;
	}
}


TExpr *Parser::ParsePrimExpr()
{
	TExpr *e;
	Type tok = scanner.GetCurrType();

	switch ( tok )
	{
	case name:
		{
			TSymbol *def = stack->FindGlobal( scanner.GetCurrSource() );
			if ( def )
				if ( !def->IsVar() && !def->IsFunc() )
					throw IdNotFuncOrVar( scanner.GetCurrPos() , scanner.GetCurrSource() );
			string var = scanner.GetCurrSource();
			scanner.Next();
			//leave undefined name - it may be used in structures
			//but it must be caught in the other cases;
			if ( !def )
				return new TVarExpr( var , NULL );
			//if is varname, TVarExpr contains the pointer to TSymVar
			if ( def->IsVar() )
				return new TVarExpr( var , def );//def->GetType()
			//if is function name, TVarExpr contains pointer to TSymFunc
			return new TVarExpr( var , def ); //IsFunc
		}
	case slbrace:
		{
			scanner.Next();
			e = ParseExpr();
			scanner.Require( srbrace );
			return e;
		}
	case cint:
		{
			e = new TConstExpr( scanner.GetCurrSource() , scanner.GetCurrInt() , GlobSymTable->GetElemN( 0 ) );						
			scanner.Next();
			return e;
		}
	case cfloat:
		{
			e = new TConstExpr( scanner.GetCurrSource() , scanner.GetCurrFloat() , GlobSymTable->GetElemN( 1 ) );						
			scanner.Next();
			return e;
		}
	case cstr:
		{
			e = new TConstExpr( scanner.GetCurrSource() , scanner.GetCurrStr() , GlobSymTable->GetElemN( 2 ) );
			scanner.Next();
			return e;
		}
	case kint:
		{
			scanner.Next();
			scanner.Require( slbrace );
			e = new TTypeCast( GlobSymTable->GetElemN( 0 ) , ParseExpr() );
			e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
			if ( optimizing )
				FoldTypeCast( e );
			scanner.Require( srbrace );
			return e;
		}
	case kfloat:
		{
			scanner.Next();
			scanner.Require( slbrace );
			e = new TTypeCast( GlobSymTable->GetElemN( 1 ) , ParseExpr() );
			e->TypeCheck( GlobSymTable , scanner.GetCurrPos() );
			if ( optimizing )
				FoldTypeCast( e );
			scanner.Require( srbrace );
			return e;
		}
		case srbrace:
			return new TEmptyExpr();
	}
	throw UnexpLex( scanner.GetCurrPos() , scanner.TypeToStr( scanner.GetCurrType() ) );
}

void Parser::FoldBinaryOp( TExpr *&bin )
{
	if ( bin->ArgsAreConsts() )
	{
		TExpr *copy = bin;
		TExpr *left = bin->GetLeftPart(),
			*right = bin->GetRightPart();
		TSymbol *opvaluetype = bin->GetType();

		Type optype = bin->type,
			argtype = left->type;
		string source = left->GetSource();
		int i_val;
		float f_val;
		//operations: + - * /
		if ( ( optype > 19 ) && ( optype < 24 ) )
		{//redo TConstExpr () constructor
			if ( oplus == optype )
			{
				source += " + ";
				if ( cint == argtype )
					i_val = left->GetInt() + right->GetInt();
				else
					f_val = left->GetFloat() + right->GetFloat();
			}
			else
				if ( ominus == optype )
				{
					source += " - ";
					if ( cint == argtype )
						i_val = left->GetInt() - right->GetInt();
					else
						f_val = left->GetFloat() - right->GetFloat();
				}
				else
					if ( odiv == optype )
					{
						source += " / ";
						if ( cint == argtype )
							i_val = left->GetInt() / right->GetInt();
						else
							f_val = left->GetFloat() / right->GetFloat();
					}
					else
						if ( omul == optype )
						{
							source += " * ";
							if ( cint == argtype )
								i_val = left->GetInt() * right->GetInt();
							else
								f_val = left->GetFloat() * right->GetFloat();
						}
						source += bin->GetRightPart()->GetSource();
						if ( cint == argtype )
							bin = new TConstExpr( source , i_val , opvaluetype );
						else
							bin = new TConstExpr( source , f_val , opvaluetype );
		}
		else
			//> < == != >= <=
			if ( ( optype > 28 ) && ( optype < 37 ) )
			{
				if ( ogreat == optype )
				{
					source += " > ";
					if ( cint == argtype )
						i_val = left->GetInt() > right->GetInt();
					else
						i_val = left->GetFloat() > right->GetFloat();
				}
				else
					if ( oless == optype )
					{
						source += " < ";
						if ( cint == argtype )
							i_val = left->GetInt() < right->GetInt();
						else
							i_val = left->GetFloat() < right->GetFloat();
					}
					else
						if ( oegreat == optype )
						{
							source += " >= ";
							if ( cint == argtype )
								i_val = left->GetInt() >= right->GetInt();
							else
								i_val = left->GetFloat() >= right->GetFloat();

						}
						else
							if ( oeless == optype )
							{
								source += " <= ";
								if ( cint == argtype )
									i_val = left->GetInt() <= right->GetInt();
								else
									i_val = left->GetFloat() <= right->GetFloat();
							}
							else
								if ( oequal == optype )
								{
									source += " == ";
									if ( cint == argtype )
										i_val = left->GetInt() == right->GetInt();
									else
										i_val = left->GetFloat() == right->GetFloat();
								}
								else
									if( onequal == optype )
									{
										source += " != ";
										if ( cint == argtype )
											i_val = left->GetInt() != right->GetInt();
										else
											i_val = left->GetFloat() != right->GetFloat();
									}
									else
										if ( oor == optype )
										{
											source += " || ";
											if ( cint == argtype )
												i_val = left->GetInt() || right->GetInt();
											else
												i_val = left->GetFloat() || right->GetFloat();
										}
										else
											if ( oand == optype )
											{
												source += " && ";
												if ( cint == argtype )
													i_val = left->GetInt() && right->GetInt();
												else
													i_val = left->GetFloat() && right->GetFloat();
											};
				source += bin->GetRightPart()->GetSource();
				bin = new TConstExpr( source , i_val , opvaluetype );
			}
			delete( copy );
	}

}
void Parser::FoldUnaryOp( TExpr *&un )
{
	if ( un->ArgsAreConsts() )
	{
		TExpr *rpart = un->GetRightPart();
		TExpr *copy = un;
		if ( onot == un->type )
		{
			if ( rpart->GetInt() || rpart->GetFloat() )
				un = new TConstExpr( "0" , 0 , un->GetType() );
			else
				un = new TConstExpr( "1" , 1 , un->GetType() );
		}
		else
			if ( oplus == un->type )
			{
				if ( cint == rpart->type )
					un = new TConstExpr( "+" + rpart->source , rpart->GetInt() , un->GetType() );
				else
					un = new TConstExpr( "+" + rpart->source , rpart->GetFloat() , un->GetType() );
			}
			else
				if ( ominus == un->type )
				{
					if ( cint == rpart->type )
						un = new TConstExpr( "-" + rpart->source , -rpart->GetInt() , un->GetType() );
					else
						un = new TConstExpr( "-" + rpart->source , -rpart->GetFloat() , un->GetType() );
				}
		delete( copy );
	}
}
void Parser::FoldTypeCast( TExpr *&e )
{
	if ( e->ArgsAreConsts() && ( e->CastNeeded() ) )
	{
		TExpr *temp = e;
		//float to int
		if ( e->exprtype->IsInt() )
			e = new TConstExpr( e->source , int( e->GetFloat() ), e->exprtype );
		//int to float
		else
			e = new TConstExpr( e->source , float( e->GetInt() ), e->exprtype );
		delete( temp );
	}
}