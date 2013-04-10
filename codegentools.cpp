#include "codegentools.h"



Op::Op()
{}
bool Op::IsMem()
{
	return type == "mem";
}
bool Op::IsReg()
{
	return type == "reg";
}
bool Op::IsImm()
{
	return type == "imm";
}
bool Op::IsAddr()
{
	return ( ( type == "daddr" ) || ( type == "qaddr" ) );
}
bool Op::IsDaddr()
{
	return type == "daddr";
}

bool Op::IsStr()
{
	return type == "str";
}
string Op::GetMem()
{
	return "";
}
bool Op::IsInt()
{
	return 0;
}
MnemReg Op::GetReg()
{
	return notreg;
}
int Op::GetInt()
{
	return 0;
}
int Op::GetOffset()
{
	return 0;
}
float Op::GetFloat()
{
	return 0;
}
string Op::GetStr()
{
	return "";
}


Mem::Mem( string s )
	:memname( s )
{
	type = "mem";
}
string Mem::GetMem()
{
	return memname;
}

Imm::Imm( int val )
	:i_val( val ), isint( 1 )
{
	type = "imm";
}
Imm::Imm( float val )
	:f_val( val ), isint( 0 )
{
	type = "imm";
}
bool Imm::IsInt()
{
	return isint;
}
int Imm::GetInt()
{
	return i_val;
}
float Imm::GetFloat()
{
	return f_val;
}


Reg::Reg( MnemReg mnem )
	:reg( mnem )
{
	type = "reg";
}
MnemReg Reg::GetReg()
{
	return reg;
}


Str::Str( string s )
	:str( s )
{
	type = "str";
}
string Str::GetStr()
{
	return str;
}
Addr::Addr( MnemReg r , int off , bool qword )
	:reg( r ) , offset( off )
{
	if ( !qword )
		type = "daddr";
	else
		type = "qaddr";
}
MnemReg Addr::GetReg()
{
	return reg;
}
int Addr::GetOffset()
{
	return offset;
}

Mem *mem( string str )
{
	return new Mem( str );
}
Imm *imm( int i_val )
{
	return new Imm( i_val );
}
Imm *imm( float f_val )
{
	return new Imm( f_val );
}
Reg *reg( MnemReg r )
{
	return new Reg( r ) ;
}
Str *str( string s )
{
	return new Str( s );
}
Addr *addr( MnemReg r , int off , bool qword )
{
	return new Addr( r , off , qword );
}


string v_( string str )
{
	return "v_" + str;
}
string f_( string str )
{
	return "f_" + str;
}

Mem *memv_( string s )
{
	return mem( v_( s ) );
}
Str *strf_( string s )
{
	return str( f_( s ) );
}
Str *strv_( string s )
{
	return str( v_( s ) );
}

Str *Begin( string s )
{
	return str( "\t-->> " + s );
}

Str *End( string s )
{
	return str( "\t<<-- " + s );
}

TAsmCommand::TAsmCommand( MnemCom m , Op *oper1 , Op *oper2 , Op *oper3 )
	:mnem( m ), op1( oper1 ), op2( oper2 ), op3( oper3 )
{}
MnemCom TAsmCommand::GetMnem()
{
	return mnem;
}
Op *TAsmCommand::GetOp1()
{
	return op1;
}
Op *TAsmCommand::GetOp2()
{
	return op2;
}
Op *TAsmCommand::GetOp3()
{
	return op3;
}
bool TAsmCommand::IsPush()
{
	return mnem == PUSH;
}
bool TAsmCommand::IsPop()
{
	return mnem == POP;
}
bool TAsmCommand::ChangesEsp()
{
	if ( op1 )
		if ( op1->IsReg() )
			return op1->GetReg() == esp;
	return 0;
}