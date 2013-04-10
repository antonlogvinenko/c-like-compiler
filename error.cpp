#include "error.h"


Position Error::GetPos()
{
	return Pos;
}

const string& Error::GetMatter()
{
	return matter;
}

void Error::ErrorPrint()
{
	cout << "\nerror at " << Pos.Line << ":" << Pos.Column << "\t" << message << matter;
}

UnexpLex::UnexpLex( Position p , string s )
{       
	Pos = p; matter = s;
	message = " unexpected lexem: ";
};

Required::Required( Position p , string s )
{       
	Pos = p; matter = s;
	message = " another lexem expected: ";
};

RepCases::RepCases( Position p , string s )
{       
	Pos = p; matter = s;
	message = " repeating cases are forbidden ";
};
EscSeq::EscSeq( Position p , string s )
{       
	Pos = p; matter = s;
	message = " unknown escape sequence ";
};

MissExp::MissExp( Position p, char s )
{
	Pos = p; matter = s;
	message = " missing exponent - illegal symbol ";
};

IllSymbConst::IllSymbConst( Position p, char s )
{ 
	Pos = p; matter = s;
	message = " illegal symbol in constant ";
};

Unterm::Unterm( Position p , string s )
{
	Pos = p; matter = s;
	message = " missing terminating character ";
};

Unknown::Unknown( Position p , string s )
{
	Pos = p; matter = s;
	message = " unknown identificator ";
};

MissIdent::MissIdent( Position p , string s )
{
	Pos = p; matter = s;
	message = " identifier expected instead of ";
}

Redif::Redif( Position p , string s )
{
	Pos = p; matter = s;
	message = " redefenition is forbiden ";
}

UndefVar::UndefVar( Position p , string s )
{
	Pos = p; matter = s;
	message = " variable is used without being defined";
}

ArgRedif::ArgRedif( Position p , string s )
{
	Pos = p; matter = s;
	message = " argument with such a name has already been declared: ";
}

NotLoop::NotLoop( Position p , string s )
{
	Pos = p; matter = s;
	message = " jump statement not within a loop: ";
}
NotLoopOrSwitch::NotLoopOrSwitch( Position p , string s )
{
	Pos = p; matter = s;
	message = " jump statement not within a loop or a switch: ";
}

FuncDefined::FuncDefined( Position p , string s )
{
	Pos = p; matter = s;
	message = " function with such a name has already been defined: ";
}

WrongFuncRedecl::WrongFuncRedecl( Position p , string s )
{
	Pos = p; matter = s;
	message = " new declaration of function differs from previous one: ";
}

EmbeddedFunc::EmbeddedFunc( Position p , string s )
{
	Pos = p; matter = s;
	message = " embedded functions are forbidden: ";
}

IdentRedif::IdentRedif( Position p , string s )
{
	Pos = p; matter = s;
	message = " identifier has already been declared: ";
}

IllegDeclIdent::IllegDeclIdent( Position p , string s )
{
	Pos = p; matter = s;
	message = " illegal lexem in declaration: ";
}

UnknownType::UnknownType( Position p , string s )
{
	Pos = p; matter = s;
	message = " type expected: ";
}
NumTypExp::NumTypExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " numerical type expected: ";
}

NonStructType::NonStructType( Position p , string s )
{
	Pos = p; matter = s;
	message = " non-struct type: ";
}

OldMissed::OldMissed( Position p , string s )
{
	Pos = p; matter = s;
	message = " is not a type to be given new name: ";
}

OldNotType::OldNotType( Position p , string s )
{
	Pos = p; matter = s;
	message = " meant to be a type: ";
}

MembRedecl::MembRedecl( Position p , string s )
{
	Pos = p; matter = s;
	message = " member redeclaraton is forbidden: ";
}

WrongStructEnd::WrongStructEnd( Position p , string s )
{
	Pos = p; matter = s;
	message = " identifier or semicolon expected: ";
}

ErrStructBegin::ErrStructBegin( Position p , string s )
{
	Pos = p; matter = s;
	message = " struct body or an identifier expected: ";
}

ForbidArgType::ForbidArgType( Position p , string s )
{
	Pos = p; matter = s;
	message = " struct arguments are forbiden: ";
}

ForbidReturnType::ForbidReturnType( Position p , string s )
{
	Pos = p; matter = s;
	message = " function can only return int and float values ";
}

UserInit::UserInit( Position p , string s )
{
	Pos = p; matter = s;
	message = " initialization of user types is forbidden: ";
}

SimpStrucTypExp::SimpStrucTypExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " simple or struct type expected: ";
}

SimpArrTypExp::SimpArrTypExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " simple or array type expected: ";
}

IntMain::IntMain( Position p , string s )
{
	Pos = p; matter = s;
	message = " main() must return int value ";
}

MainNoArgs::MainNoArgs( Position p , string s )
{
	Pos = p; matter = s;
	message = " main() must have no arguments ";
}

IllegIndexType::IllegIndexType( Position p , string s )
{
	Pos = p; matter = s;
	message = " index must have integer type ";
}
MainDeclForbid::MainDeclForbid( Position p , string s )
{
	Pos = p; matter = s;
	message = " main() declarations are forbidden ";
}

MainNotDefined::MainNotDefined( Position p , string s )
{
	Pos = p; matter = s;
	message = " main() must be defined ";
}

UndefinedFunc::UndefinedFunc( Position p , string s )
{
	Pos = p; matter = s;
	message = " function must be defined: ";
}

IdNotFuncOrVar::IdNotFuncOrVar( Position p , string s )
{
	Pos = p; matter = s;
	message = " variable or function name expected: ";
}

TypeCastNotAvail::TypeCastNotAvail( Position p , string s )
{
	Pos = p; matter = s;
	message = " type cast is available only for int and float types";
}

FuncNameExp::FuncNameExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " used identifier must name a function ";
}

MainCall::MainCall( Position p , string s )
{
	Pos = p; matter = s;
	message = " forbidden to call main() ";
}

ArgMismatch::ArgMismatch( Position p , string s )
{
	Pos = p; matter = s;
	message = " invalid argument(s) ";
}

StringConstExp::StringConstExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " string constant expected as the first argument ";
}

ArgNumMismatch::ArgNumMismatch( Position p , string s )
{
	Pos = p; matter = s;
	message = " number of arguments is wrong";
}

StructArrayExp::StructArrayExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " array or struct variable expected ";
}

ArrayExp::ArrayExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " variable of array type expected ";
}

StructExp::StructExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " variable of struct type expected ";
}

IdStructExp::IdStructExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " : ";
}

IllegIndex::IllegIndex( Position p , string s )
{
	message = " index has unknown type ";
}

NonIntIndex::NonIntIndex( Position p , string s )
{
	Pos = p; matter = s;
	message = " index must have int type ";
}

NonStructField::NonStructField( Position p , string s )
{
	Pos = p; matter = s;
	message = " no such field in structure ";
}

LeftAssignUnknown::LeftAssignUnknown( Position p , string s )
{
	Pos = p; matter = s;
	message = " left part of the assignment has unknown type ";
}

LeftAssignMustBeLvalue::LeftAssignMustBeLvalue( Position p , string s )
{
	Pos = p; matter = s;
	message = " left part of the assignment must be lvalue ";
}

NoFuncExp::NoFuncExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " function call is not expected ";
}

AssignNonSimple::AssignNonSimple( Position p , string s )
{
	Pos = p; matter = s;
	message = " only int and float types are allowed to assign ";
}

AssignTypeMismatch::AssignTypeMismatch( Position p , string s )
{
	Pos = p; matter = s;
	message = " assignment type mismatch ";
}

BinOpersUnknown::BinOpersUnknown( Position p , string s )
{
	Pos = p; matter = s;
	message = " Operand(s) of binary operation with no type ";
}

BinOpSimpType::BinOpSimpType( Position p , string s )
{
	Pos = p; matter = s;
	message = " binary operation's operands must have int or float type ";
}

BinTypeMismatch::BinTypeMismatch( Position p , string s )
{
	Pos = p; matter = s;
	message = " type mismatch: binary operation's operands must have same types ";
}

LogAndCompOpsType::LogAndCompOpsType( Position p , string s )
{
	Pos = p; matter = s;
	message = " logic and comparsion operation must have integer operands ";
}

UnknownUnOp::UnknownUnOp( Position p , string s )
{
	Pos = p; matter = s;
	message = " unknown type of unary operand ";
}

UnOpSymType::UnOpSymType( Position p , string s )
{
	Pos = p; matter = s;
	message = " unary operation's operand must have int or float type ";
}

LvalueExp::LvalueExp( Position p , string s )
{
	Pos = p; matter = s;
	message = " lvalue expected as the operand of unary operation ";
}
ConstNLval::ConstNLval( Position p , string s )
{
	Pos = p; matter = s;
	message = " constant value cannot be given to a function by reference ";
}
ConditionMissed::ConditionMissed( Position p , string s )
{
	Pos = p; matter = s;
	message = " condition missed ";
}
DefaultOrCase::DefaultOrCase( Position p , string s )
{
	Pos = p; matter = s;
	message = " default or case keyword expected: ";
}
DefaultTwice::DefaultTwice( Position p , string s )
{
	Pos = p; matter = s;
	message = " only one default case is allowed ";
}
IntExpSwitch::IntExpSwitch( Position p , string s )
{
	Pos = p; matter = s;
	message = " only int expression is allowed ";
}
NonConstInSwitch::NonConstInSwitch( Position p , string s )
{
	Pos = p; matter = s;
	message = " some non constant expression is used as a case ";
}