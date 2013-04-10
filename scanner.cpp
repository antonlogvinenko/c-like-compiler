#include "scanner.h"


Reserved::Reserved()
{
	reskeys["for"] = kfor;
	reskeys["if"] = kif;
	reskeys["while"] = kwhile;
	reskeys["switch"] = kswitch;
	reskeys["case"] = kcase;
	reskeys["default"] = kdefault;
	reskeys["float"] = kfloat;
	reskeys["else"] = kelse;
	reskeys["string"] = kstring;
	reskeys["int"] = kint;
	reskeys["struct"] = kstruct;
	reskeys["typedef"] = ktypedef;
	reskeys["return"] = kreturn;
	reskeys["break"] = kbreak;
	reskeys["continue"] = kcontinue;

	separs["("] = slbrace;
	separs[")"] = srbrace;
	separs["{"] = slfigbrace;
	separs["}"] = srfigbrace;
	separs[";"] = ssemic;
	separs["."] = sdot;
	separs[","] = scomma;
	separs[":"] = scolon;
	separs["["] = slsqbrace;
	separs["]"] = srsqbrace;

	opers["++"] = oincr;
	opers["--"] = odecr;
	opers["+"] = oplus;
	opers["-"] = ominus;
	opers["/"] = odiv;
	opers["*"] = omul;
	opers["="] = oassign;
	opers["+="] = oassignplus;
	opers["-="] = oassignmin;
	opers["/="] = oassigndiv;
	opers["*="] = oassignmul;
	opers[">"] = ogreat;
	opers["<"] = oless;
	opers[">="] = oegreat;
	opers["<="] = oeless;
	opers["=="] = oequal;
	opers["!="] = onequal;
	opers["!"] = onot;
	opers["&&"] = oand;
	opers["||"] = oor;
	opers["&"] = oamper;  			
} 
bool Reserved::IsInReskeys( string str )
{
	return ( reskeys.find( str ) != reskeys.end() );
}
bool Reserved::IsInReskeys( char ch )
{
	string str;
	str = ch;
	return reskeys.find( str ) != reskeys.end();
}
bool Reserved::IsInSepars( string str )
{
	return separs.find( str ) != separs.end();
}
bool Reserved::IsInSepars( char ch )
{
	string str;
	str = ch;
	return separs.find( str ) != separs.end();
}
bool Reserved::IsInOpers( string str )
{
	return opers.find( str ) != opers.end();
}
bool Reserved::IsInOpers( char ch )
{
	string str;
	str = ch;
	return opers.find( str ) != opers.end();
}


TokenString::TokenString()
{
	names[eof] = "EOF";
	names[name]	= "identifier";
	names[kfor]	= "keyword for";
	names[kif] = "keyword if";
	names[kelse] = "keyword else";
	names[kwhile] = "keyword while";
	names[kswitch] = "keyword switch";
	names[kcase] = "keyword case";
	names[kdefault] = "keyword default";
	names[kfloat] = "keyword float";
	names[kstring] = "keyword string";
	names[kint] = "keyword int";
	names[kstruct] = "keyword struct";
	names[ktypedef] = "keyword typedef";
	names[kreturn] = "keyword return";
	names[kbreak] = "keyword break";
	names[kcontinue] = "keyword continue";

	names[oincr] = "operator ++";
	names[odecr] = "operator --";
	names[oplus] = "operator +";
	names[ominus] = "operator -";
	names[odiv] = "operator /";
	names[omul] = "operator *";
	names[oassign] = "operator  = ";
	names[oassignplus] = "operator +=";
	names[oassignmin] = "operator -=";
	names[oassigndiv] = "operator /=";
	names[oassignmul] = "operator *=";
	names[ogreat] = "operator >";
	names[oless] = "operator <";
	names[oegreat] = "operator >=";
	names[oeless] = "operator <=";
	names[oequal] = "operator  ==";
	names[onequal] = "operator !=";
	names[onot] = "operator !";
	names[oand] = "operator &&";
	names[oor] = "operator ||";
	names[oamper] = "operator &";

	names[slbrace] = "separator (";
	names[srbrace] = "separator )";
	names[slfigbrace] = "separator {";
	names[srfigbrace] = "separator }";
	names[ssemic] = "separator ;";
	names[sdot] = "separator .";
	names[scomma] = "separator ,";
	names[scolon] = "separator :";
	names[slsqbrace] = "separator [";
	names[srsqbrace] = "separartor ]";	

	names[cint] = "int constant";
	names[cstr] = "string constant";
	names[cfloat] = "float constant"; 
};                 


Token::Token()
	:n_value( 0 ) , s_value() , type( name ) , source( "" )
{};
void Token::SetToken( Type  t, const string s , float v )
{
	source = s;
	type = t;
	n_value = v;
	s_value = "";
};
void Token::SetToken( Type t , const string s , string str )
{
	source = s;
	type = t;
	n_value = 0;
	s_value = str;
};
void Token::SetToken( Type t , const string s )
{
	source = s;
	type = t;
	n_value = 0;
	s_value = "";
}
const int Token::AsInteger() const
{
	return ( int ) n_value;		
}
string Token::AsString() const
{
	return s_value;
}
float Token::AsFloat()
{	
	return n_value;
}
const string& Token::GetSource() const
{
	return source;
}
Type Token::GetType() const
{
	return type;
}


Reader::Reader ( const char* filename )
	:ifstream( filename ) , curr( ' ' ) , numlast( 0 )
{}
char Reader::GetChar()
{
	if ( curr != '\n' )
		CurrPos.Column++;
	else
	{
		numlast = CurrPos.Column;
		CurrPos.Column = 1;
		CurrPos.Line++;
	}
	curr = get();
	return curr;
}
void Reader::PutBack( char ch )
{
	if ( CurrPos.Column > 1 )
	{
		putback( ch );
		CurrPos.Column--;
		curr = ' ';	
	}
	else
		if ( numlast )
		{
			putback( ch );
			CurrPos.Line--;
			CurrPos.Column = numlast;
			numlast = 0;
			curr = '\n';
		}
}


Scanner::Scanner( const char *filename )
	:reader( filename ), hidden( none )
{}
bool Scanner::OK()
{
	return reader;
}
void Scanner::EmulSemic()
{
	hidden = CurrToken.type;
	CurrToken.type = ssemic;
}
void Scanner::DeEmulSemic()
{
	if ( hidden != none )
	{
		CurrToken.type = hidden;
		hidden = none;
	}
}
void Scanner::Require( Type type )      
{
	if ( CurrToken.type != type )
		throw Required( GetCurrPos() , TypeToStr( type ) );
	Next();
}
string& Scanner::GetCurrSource()
{		
	return CurrToken.source;
}
Type Scanner::GetCurrType()
{
	return CurrToken.type;
}
int Scanner::GetCurrInt()
{
	return CurrToken.AsInteger();
}
float Scanner::GetCurrFloat()
{
	return CurrToken.AsFloat();
}
string Scanner::GetCurrStr()
{
	return CurrToken.AsString();
}
const Position& Scanner::GetCurrPos()
{
	return reader.CurrPos;
}
const Token& Scanner::GetToken() const
{
	return CurrToken;		
}
string Scanner::TypeToStr( Type type )
{
	return TokStr.names[type];
}
void Scanner::OutToken()
{
	cout << '\n' << TokStr.names[CurrToken.type] << '\t'; 

	cout << CurrToken.source;

	if ( CurrToken.type == cint )
		cout << "\t" << CurrToken.AsInteger();
	if ( CurrToken.type == cfloat )
		cout << "\t" << CurrToken.AsFloat();
	if ( CurrToken.type == cstr )
		cout << "\t" << CurrToken.AsString();
	return;
}
void Scanner::whileisdig( char &ch , string &source )
{
	while ( isdigit( ch ) )
	{
		source += ch;
		ch = reader.GetChar();
	}
}
void Scanner::Next()
{       
	string source; 	
	char ch = reader.GetChar();
	bool checked;

	//REPEATS UNTIL WE CATCH THE SYMBOL NOT OPENING COMMENTS OR SET OF SPACES
	do	
	{	
		checked = true;
		//IF COMMENTS, MISS THEM AND TAKE THE FOLLOWING SYMBOL
		if ( ch == '/' )
		{       
			ch = reader.GetChar();
			if ( ch=='/' )
			{
				checked = false;
				while ( ( ch != '\n' ) && ( ch != EOF ) )
					ch = reader.GetChar();
			}		
			else
				if ( ch == '*' )
				{
					Position PossibExcept = reader.CurrPos;
					checked = false;
					bool found = false;
					while( ( ch != EOF ) && ( !found ) )
					{       
						ch = reader.GetChar();
						if ( ch == '*' )
						{
							ch = reader.GetChar();
							if ( ch == '/' )
								found = true;
						}		
					}
					if ( found )
						ch = reader.GetChar();
					else  
					{       
						source = ch;
						throw Unterm( PossibExcept , "*/" );
						/*    exception unterminated comment    */
					} 
				}	
				else          
				{	
					reader.PutBack( ch );
					ch = '/';
				}
		}

		//IF SPACES, MISS THEM AND TAKE THE FOLLOWING SYMBOL
		if ( isspace( ch ) )
		{
			checked = false;
			while ( isspace( ch ) )
				ch = reader.GetChar();
		}
	}
	while ( !checked );    

	//END OF FILE
	if ( ch == EOF )
	{
		source = ch;
		CurrToken.SetToken( eof , source );
		return;		
	};


	//OPERATORS && SEPARATORS
	if ( ( ispunct( ch ) ) && ( ch!='\"' ) )
	{
		if ( coll.IsInSepars( ch ) )
		{
			if ( ch == '.' )
			{
				ch = reader.GetChar();
				reader.PutBack( ch );
				if ( !isdigit( ch ) )
				{
					source = '.';       
					CurrToken.SetToken( coll.separs[source] , source );
					return;
				}
				else
					ch = '.';
			}
			else
			{	
				source = ch;          
				CurrToken.SetToken( coll.separs[source] , source );
				return;
			}				
		}        

		if ( coll.IsInOpers( ch ) )             
		{  
			source = ch;
			ch = reader.GetChar();
			if ( ( source == "+" ) || ( source == "-" ) )
			{
				if ( ch == '=' )
					source += ch;
				else
					if ( ( ( ch == '+' ) || ( ch == '-' ) ) && ( source[0] == ch ) )
						source += ch;
					else
						reader.PutBack( ch );
			}
			else
				if ( ( source == "*" ) || ( source == "/" ) || (source==">") || (source=="<") || (source=="!") || (source=="=") )
				{
					if ( ch == '=' )
						source+=ch;
					else
						reader.PutBack( ch );
				}
				else
					if ( source == "&" )
					{
						if ( ch == '&' )
						{
							source += ch;
							CurrToken.SetToken( coll.opers[source] , source );
							return;	
						}
						else
							reader.PutBack( ch );				

					}
					CurrToken.SetToken( coll.opers[source] , source );
					return; 
		}   
		if ( ch == '|' )
		{     
			source = ch;
			ch = reader.GetChar();
			if ( ch == '|' )
			{
				source += ch;
				CurrToken.SetToken( coll.opers[source] , source );
				return;
			}
			reader.PutBack( ch );
		}
	}


	if ( isdigit( ch ) || ( ch =='.' ) )
	{
		bool real = false;
		if ( isdigit( ch ) )
			whileisdig( ch , source );

		if ( ch == '.' )
		{
			real = true;
			source += ch;              
			ch = reader.GetChar();  
			whileisdig( ch , source );
		}

		if ( ( ch == 'e' ) || ( ch == 'E' ) )
		{
			real = true;
			source += 'e';
			ch = reader.GetChar();
			if ( ( ch == '+' ) || ( ch == '-' ) )
			{
				source += ch;
				ch = reader.GetChar();
			}
			if ( !isdigit( ch ) )
				throw MissExp( reader.CurrPos , ch );
			whileisdig( ch , source );
		}
		if  (((isspace(ch))||(ch==EOF)||(coll.IsInOpers(ch))||coll.IsInSepars(ch)||(ch=='&')||(ch=='|') )&&(ch!='.'))
		{
			if ( real )
				CurrToken.SetToken( cfloat , source , atof( source.c_str() ) );
			else
				CurrToken.SetToken( cint , source , atof( source.c_str() ) ); 
			reader.PutBack( ch );
			return;	       
		}
		throw IllSymbConst( reader.CurrPos , ch );
	}



	//IDENTS: NAMES AND RESERVED KEYWORDS
	if ( ( isalpha( ch ) ) || ( ch == '_' ) )
	{
		//isalnum == isdigit||isalpha
		while ( isalnum( ch ) || ( ch=='_' ) )
		{
			source += ch;
			ch = reader.GetChar();
		}
		reader.PutBack( ch );
		//IS RESERVED KEYWORD
		if ( coll.reskeys.find( source ) != coll.reskeys.end() )
			CurrToken.SetToken( coll.reskeys[source] , source );
		//IS NAME
		else
			CurrToken.SetToken( name , source );
		return; 
	}  	       		

	//STRINGS...
	if ( ch == '\"' )
	{
		Position PossibExcept = reader.CurrPos;
		string str;
		source += ch;
		ch = reader.GetChar();
		//eof ; "" ; isgraph ; esc seq
		while ( ( ch != '\"' ) && ( ch != '\n' ) && ( ch != EOF ) ) 
		{
			if ( ch == '\\' )
			{
				source += ch;
				ch = reader.GetChar();
				if ( ( ch == '\"' ) || ( ch == '\\' ) )
				{
					source += ch;
					str+= ch;					
				}
				else
					if ( ch == 'n' )
					{
						source += ch;
						str += '\n';
					}
					else
						if ( ch == 't' )
						{
							source += ch;
							str += '\t';
						}
						else
							throw EscSeq( GetCurrPos() , ( string ) "\\" + ch );
			}
			else
				if ( isgraph( ch ) || ch == ' ' )
				{
					source += ch;
					str += ch;
				}
				else
					throw IllSymbConst( GetCurrPos() , ch );
			ch = reader.GetChar();
		}

		if ( ch == '\"' )
		{
			source += ch;
			CurrToken.SetToken( cstr , source , str );
			return;
		}
		source = ch;
		throw Unterm( PossibExcept , "\"" );
	}

	//IF UNKNOWN TYPE
	source = ch;
	throw Unknown ( GetCurrPos() , source );
	return;		
}

void Scanner::Scanning()
{
	do
	{
		try
		{
			Next();
			OutToken();
		}
		catch ( Error err )
		{
			err.ErrorPrint();
		}
	}
	while ( CurrToken.GetType() != eof );
}; 	     
