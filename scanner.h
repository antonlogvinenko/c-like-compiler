#pragma once
#include "stdafx.h"
#include "scantools.h"
#include "error.h"


class Reserved
{
public:
	map<string, enum Type> reskeys, opers, separs;
	Reserved();
	bool IsInReskeys( string  );
	bool IsInReskeys( char  );
	bool IsInSepars( string  );
	bool IsInSepars( char  );
	bool IsInOpers( string  );
	bool IsInOpers( char  );	                    
};

class TokenString
{
	map<enum Type, string> names;
public:
	TokenString();
	friend class Scanner;
};

class Token
{
	float n_value;
	string s_value;
	Type type;
	string source;

	void SetToken( Type  , const string  , float  );
	void SetToken( Type  , const string  , string  );
	void SetToken( Type  , const string  );

public:
	Token();
	const int AsInteger()const;
	string AsString()const;
	float AsFloat(); 	     
	const string& GetSource()const;
	Type GetType()const;
	friend class Scanner;		        
};

class Reader:private ifstream
{
	Position CurrPos;
	int numlast;
	char curr;
	char GetChar();
	void PutBack( char  );
public:
	Reader ( const char *  );
	friend class Scanner;
};

class Scanner
{
	Reader reader;
	Token CurrToken;
	Reserved coll;
	TokenString TokStr;
	Type hidden;

public:
	Scanner( const char *  );

	void EmulSemic();
	void DeEmulSemic();
	void Require( Type  );
	bool OK();

	string& GetCurrSource();
	Type GetCurrType();
	int GetCurrInt();
	float GetCurrFloat();
	string GetCurrStr();	
	const Position& GetCurrPos();
	const Token& GetToken()const;

	string TypeToStr(Type );	
	void whileisdig( char &  , string &  );

	void Next();
	void Scanning();
	void OutToken();
};