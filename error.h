#pragma once
#include "stdafx.h"
#include "scantools.h"


class Error
{
public:
	int Line;
	Position Pos;
	string matter;
	string message;

	Position GetPos();
	const string& GetMatter();
	void ErrorPrint();
};

class UnexpLex:public Error
{
public:
	UnexpLex( Position , string );				
};

class Required:public Error
{
public:
	Required( Position , string );				
};

class EscSeq:public Error
{
public:
	EscSeq( Position , string );				
};

class MissExp:public Error
{
public:
	MissExp( Position , char );	
};
class IllSymbConst:public Error
{
public:
	IllSymbConst( Position , char );	
};

class Unterm:public Error
{
public:
	Unterm( Position , string );
};

class Unknown:public Error
{
public:
	Unknown( Position , string );	
};

class MissIdent:public Error
{
public:
	MissIdent( Position , string );	
};

class Redif:public Error
{
public:
	Redif( Position , string );	
};

class UndefVar:public Error
{
public:
	UndefVar( Position , string );	
};

class ArgRedif:public Error
{
public:
	ArgRedif( Position , string );
};
class NotLoop:public Error
{
public:
	NotLoop( Position , string );
};

class NotLoopOrSwitch:public Error
{
public:
	NotLoopOrSwitch( Position , string );
};

class FuncDefined:public Error
{
public:
	FuncDefined( Position , string );
};

class WrongFuncRedecl:public Error
{
public:
	WrongFuncRedecl( Position , string );
};

class EmbeddedFunc:public Error
{
public:
	EmbeddedFunc( Position , string );
};

class IdentRedif:public Error
{
public:
	IdentRedif( Position , string );
};

class IllegDeclIdent:public Error
{
public:
	IllegDeclIdent( Position , string );
};

class UnknownType:public Error
{
public:
	UnknownType( Position , string );
};
class NumTypExp:public Error
{
public:
	NumTypExp( Position , string );
};
class NonStructType:public Error
{
public:
	NonStructType( Position , string );
};

class OldMissed:public Error
{
public:
	OldMissed( Position , string );
};

class OldNotType:public Error
{
public:
	OldNotType( Position , string );
};

class MembRedecl:public Error
{
public:
	MembRedecl( Position , string );
};

class WrongStructEnd:public Error
{
public:
	WrongStructEnd( Position , string );
};

class ErrStructBegin:public Error
{
public:
	ErrStructBegin( Position , string );
};

class ForbidArgType:public Error
{
public:
	ForbidArgType( Position , string );
};

class ForbidReturnType:public Error
{
public:
	ForbidReturnType( Position , string );
};

class UserInit:public Error
{
public:
	UserInit( Position , string );
};

class SimpStrucTypExp:public Error
{
public:
	SimpStrucTypExp( Position , string );
};

class SimpArrTypExp:public Error
{
public:
	SimpArrTypExp( Position , string );	
};

class IntMain:public Error
{
public:
	IntMain( Position , string );
};

class MainNoArgs:public Error
{
public:
	MainNoArgs( Position , string );
};

class IllegIndexType:public Error
{
public:
	IllegIndexType( Position , string );
};

class MainDeclForbid:public Error
{
public:
	MainDeclForbid( Position , string );
};

class MainNotDefined:public Error
{
public:
	MainNotDefined( Position , string );
};

class UndefinedFunc:public Error
{
public:
	UndefinedFunc( Position , string );
};

class IdNotFuncOrVar:public Error
{
public:
	IdNotFuncOrVar( Position , string );
};

class TypeCastNotAvail:public Error
{
public:
	TypeCastNotAvail( Position , string = "" );
};

class FuncNameExp:public Error
{
public:
	FuncNameExp( Position , string = "" );
};

class MainCall:public Error
{
public:
	MainCall( Position , string = "" );
};

class ArgMismatch:public Error
{
public:
	ArgMismatch( Position , string = "" );
};

class StringConstExp:public Error
{
public:
	StringConstExp( Position , string = "" );
};

class ArgNumMismatch:public Error
{
public:
	ArgNumMismatch( Position , string = "" );
};

class StructArrayExp:public Error
{
public:
	StructArrayExp( Position , string = "" );
};

class ArrayExp:public Error
{
public:
	ArrayExp( Position , string = "" );
};

class StructExp:public Error
{
public:
	StructExp( Position , string = "" );
};

class IdStructExp:public Error
{
public:
	IdStructExp( Position , string = "" );
};

class IllegIndex:public Error
{
public:
	IllegIndex( Position , string = "" );
};

class NonIntIndex:public Error
{
public:
	NonIntIndex( Position , string = "" );
};

class NonStructField:public Error
{
public:
	NonStructField( Position , string = "" );
};

class LeftAssignUnknown:public Error
{
public:
	LeftAssignUnknown( Position , string = "" );
};

class LeftAssignMustBeLvalue:public Error
{
public:
	LeftAssignMustBeLvalue( Position , string = "" );
};

class NoFuncExp:public Error
{
public:
	NoFuncExp( Position , string = "" );
};

class AssignNonSimple:public Error
{
public:
	AssignNonSimple( Position , string = "" );
};

class AssignTypeMismatch:public Error
{
public:
	AssignTypeMismatch( Position , string = "" );
};

class BinOpersUnknown:public Error
{
public:
	BinOpersUnknown( Position , string = "" );
};

class BinOpSimpType:public Error
{
public:
	BinOpSimpType( Position , string = "" );
};

class BinTypeMismatch:public Error
{
public:
	BinTypeMismatch( Position , string = "" );
};

class LogAndCompOpsType:public Error
{
public:
	LogAndCompOpsType( Position , string = "" );
};

class UnknownUnOp:public Error
{
public:
	UnknownUnOp( Position , string = "" );
};

class UnOpSymType:public Error
{
public:
	UnOpSymType( Position , string = "" );
};

class LvalueExp:public Error
{
public:
	LvalueExp( Position , string = "" );
};
class ConstNLval:public Error
{
public:
	ConstNLval( Position , string = "" );
};
class ConditionMissed:public Error
{
public:
	ConditionMissed( Position , string = "" );
};
class DefaultOrCase:public Error
{
public:
	DefaultOrCase( Position , string = "" );
};
class DefaultTwice:public Error
{
public:
	DefaultTwice( Position , string = "" );
};
class RepCases:public Error
{
public:
	RepCases( Position , string = "" );
};
class IntExpSwitch:public Error
{
public:
	IntExpSwitch( Position , string = "" );
};
class NonConstInSwitch:public Error
{
public:
	NonConstInSwitch( Position , string = "" );
};