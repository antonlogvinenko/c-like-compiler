#pragma once
#include "stdafx.h"


enum MnemCom
{
	DB, DD, CALL, PUSH, POP, MOV, INC, DEC, ADD, ADC, SUB, SBB, MUL, IMUL, DIV, IDIV, NEG, XOR, OR, AND, Com,
	CMP, LABEL, FLD, FILD, FST, FSTP, FIST, FISTP, FLD1,
	FADD, FADDP, FLDZ, FSUB, FSUBP, FMUL, FMULP, FDIV, FDIVP, FCOMIP, FINCSTP, FFREE,
	DUP, RET, PROC, ENDP,
	CMOVNZ, CMOVZ, FCHS, FCOMI, JE, JNE, JNG, JNL, JMP, JA, JB, JG, JC, JGE, JL, JLE, JNB, JNZ, JZ, JNC, JNA, TEST,
};
enum MnemReg
{
	 notreg , eax , ebx , ecx , edx , st0, st1 , esp , ebp, st,
};




class Op
{	
public:
	string type;
	Op();

	bool IsMem();
	bool IsReg();
	bool IsImm();
	bool IsStr();
	bool IsAddr();
	bool IsDaddr();

	virtual MnemReg GetReg();
	virtual int GetInt();
	virtual float GetFloat();
	virtual string GetStr();
	virtual string GetMem();
	virtual int GetOffset();

	virtual bool IsInt();
};
class Mem:public Op
{
	string memname;
public:
	Mem ( string  );
	string GetMem();
};
class Imm:public Op
{
	int i_val;
	float f_val;
	bool isint;
public:
	Imm( int  );
	Imm( float  );
	bool IsInt();
	int GetInt();
	float GetFloat();
};
class Reg:public Op
{
	MnemReg reg;
public:
	Reg( MnemReg  );
	MnemReg GetReg();
};
class Str:public Op
{
	string str;
public:
	Str( string  );
	string GetStr();
};
class Addr:public Op
{
	MnemReg reg;
	int offset;
public:
	Addr( MnemReg  , int  , bool  );
	MnemReg GetReg();
	int GetOffset();
};


Mem *mem( string  );
Imm *imm( int  );
Imm *imm( float  );
Reg *reg( MnemReg  );
Str *str( string  );
Addr *addr( MnemReg  , int  = 0 , bool  = false );
Mem *memv_( string  );
Str *strf_( string  );
Str *strv_( string  );

string v_( string  );
string f_( string  );

Str *Begin( string  );
Str *End( string  );


class TAsmCommand
{
	MnemCom mnem;
	Op *op1, *op2, *op3;
public:
	TAsmCommand( MnemCom , Op *oper1 = NULL , Op *oper2 = NULL , Op *oper3 = NULL );
	bool IsPush();
	bool IsPop();
	bool ChangesEsp();
	
	MnemCom GetMnem();
	Op *GetOp1();
	Op *GetOp2();
	Op *GetOp3();
};
