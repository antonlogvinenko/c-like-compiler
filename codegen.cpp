#include "codegen.h"
#include "codegentools.h"


CodeGen::CodeGen( string filename , bool opt , bool com )
	:label( 0 ), optimizing( opt )
{
	topop = new vector<int>();
	//checking
	if ( !opt )
		commenting = com;
	else
		commenting = false;	
	buffer = new vector<TAsmCommand*>();
	continues = new vector< string >();
	breaks = new vector< string >();
	asm_filename = filename.substr( 0 , filename.size() - 3) + "asm";

	ComTable[DD] = "dd";
	ComTable[DB] = "db";
	ComTable[DUP] = "dup";

	ComTable[PUSH] = "push";
	ComTable[POP] = "pop";

	ComTable[MOV] = "mov";
	ComTable[CMOVNZ] = "cmovnz";
	ComTable[CMOVNZ] = "cmovz";
	ComTable[INC] = "inc";
	ComTable[DEC] = "dec";
	ComTable[ADD] = "add";
	ComTable[ADC] = "adc";
	ComTable[SUB] = "sub";
	ComTable[SBB] = "sbb";
	ComTable[MUL] = "mul";
	ComTable[IMUL] = "imul";
	ComTable[IDIV] = "idiv";
	ComTable[DIV] = "div";
	ComTable[NEG] = "neg";

	ComTable[XOR] = "xor";
	ComTable[OR] = "or";
	ComTable[AND] = "and";

	ComTable[Com] = ";";

	ComTable[JNE]  =  "jne";
	ComTable[JNG] = "jng";
	ComTable[JNL] = "jnl";
	ComTable[JA] = "ja";
	ComTable[JNA] = "jna";
	ComTable[JB] = "jb";
	ComTable[JG] = "jg";
	ComTable[JGE] = "jge";
	ComTable[JL] = "jl";
	ComTable[JLE] = "jle";
	ComTable[JNB] = "jnb";
	ComTable[JNC] = "jnc";
	ComTable[JE] = "je";
	ComTable[JNZ] = "jnz";
	ComTable[JZ] = "jz";
	ComTable[JC] = "jc";
	ComTable[JMP] = "jmp";
	ComTable[CMP] = "cmp";
	ComTable[TEST] = "test";

	ComTable[PROC] = "proc";
	ComTable[ENDP] = "endp";
	ComTable[CALL] = "call";
	ComTable[RET] = "ret";

	ComTable[FLDZ] = "fldz";
	ComTable[FSUB] = "fsub";
	ComTable[FSUBP] = "fsubp";
	ComTable[FADD] = "fadd";
	ComTable[FADDP] = "faddp";
	ComTable[FILD] = "fild";
	ComTable[FIST] = "fist";
	ComTable[FISTP] = "fistp";
	ComTable[FLD] = "fld";
	ComTable[FLD1] = "fld1";
	ComTable[FST] = "fst";
	ComTable[FSTP] = "fstp";
	ComTable[FMUL] = "fmul";
	ComTable[FMULP] = "fmulp";
	ComTable[FDIV] = "fdiv";
	ComTable[FDIVP] = "fdivp";
	ComTable[FCHS] = "fchs";
	ComTable[FCOMI] = "fcomi";
	ComTable[FCOMIP] = "fcomip";
	ComTable[FINCSTP] = "FINCSTP";
	ComTable[FFREE] = "FFREE";


	RegTable[eax] = "eax";
	RegTable[ebx] = "ebx";
	RegTable[ecx] = "ecx";
	RegTable[edx] = "edx";
	RegTable[st0] = "st(0)";
	RegTable[st1] = "st(1)";
	RegTable[st] = "st";

	RegTable[esp] = "esp";
	RegTable[ebp] = "ebp";	


	//"NO Change with" table - for optimizing
	

	NoChangeWith[PROC] = "proc";
	NoChangeWith[ENDP] = "endp";
	NoChangeWith[CALL] = "call";
	NoChangeWith[RET] = "ret";
	NoChangeWith[JNE]  =  "jne";
	NoChangeWith[JNG] = "jng";
	NoChangeWith[JNL] = "jnl";
	NoChangeWith[JA] = "ja";
	NoChangeWith[JNA] = "jna";
	NoChangeWith[JB] = "jb";
	NoChangeWith[JG] = "jg";
	NoChangeWith[JGE] = "jge";
	NoChangeWith[JL] = "jl";
	NoChangeWith[JLE] = "jle";
	NoChangeWith[JNB] = "jnb";
	NoChangeWith[JNC] = "jnc";
	NoChangeWith[JE] = "je";
	NoChangeWith[JNZ] = "jnz";
	NoChangeWith[JZ] = "jz";
	NoChangeWith[JC] = "jc";
	NoChangeWith[JMP] = "jmp";
	NoChangeWith[FINCSTP] = "FINCSTP";
	NoChangeWith[FFREE] = "FFREE";

//	NoChangeWith[MOV] = "mov";
	/*NoChangeWith[XOR] = "xor";
	NoChangeWith[OR] = "or";
	NoChangeWith[AND] = "and";
	NoChangeWith[CMP] = "cmp";
	NoChangeWith[TEST] = "test";	
	NoChangeWith[FILD] = "fild";
	NoChangeWith[FIST] = "fist";
	NoChangeWith[FISTP] = "fistp";
	NoChangeWith[FLD] = "fld";	
	NoChangeWith[FST] = "fst";
	NoChangeWith[FSTP] = "fstp";*/	
}

void CodeGen::GenStart()
{	
	asm_file = new ofstream( asm_filename.c_str() );
	*asm_file << "include ..\\..\\include\\start.inc\n";
}

void CodeGen::GenMiddle()
{
	*asm_file << "\ninclude ..\\..\\include\\code.inc\n";
}

void CodeGen::GenFinish()
{
	*asm_file << "\ninclude ..\\..\\include\\end.inc";
	asm_file->close();
}

string CodeGen::IntToString( int convert )
{
	char *t = new char[5];
	itoa( convert , t , 10 );
	return string( t );
}
bool CodeGen::ComEnabled()
{
	return commenting;
}
string CodeGen::GenLabel()
{
	return "label" + IntToString( label++ );
}
void CodeGen::PushContinue( string label )
{
	continues->push_back( label );
}
void CodeGen::PopContinue()
{
	continues->pop_back();
}
string CodeGen::GetContinueLabel()
{
	return (*continues)[continues->size() - 1];
}
string CodeGen::GetBreakLabel()
{
	return (*breaks)[breaks->size() - 1];
}
void CodeGen::PushHaltPops()
{
	topop->push_back( 0 );
}
void CodeGen::PopHaltPops()
{
	topop->pop_back();
}
void CodeGen::PushBreak( string label )
{
	breaks->push_back( label );
}
void CodeGen::PopBreak()
{
	breaks->pop_back();
}
void CodeGen::AddHaltPops( int a )
{
	(*topop)[topop->size()-1] += a;
}
void CodeGen::SubHaltPops( int s )
{
	(*topop)[topop->size()-1] -= s;
}
int CodeGen::HaltPops()
{
	return (*topop)[topop->size()-1];
}
void CodeGen::FlushOp( Op *op )
{
	if ( op->IsReg() )
		*asm_file << RegTable[op->GetReg()];
	else
		if ( op->IsImm() )
			FlushConst( op );
		else
			if ( op->IsMem() )
				*asm_file << op->GetMem();
			else
				if ( op->IsAddr() )
					FlushAddr( op );
				else
				*asm_file << op->GetStr();
}
void CodeGen::FlushOpX( Op *op )
{
	if ( op->IsReg() )
		cout << RegTable[op->GetReg()];
	else
		if ( op->IsImm() )
			FlushConstX( op );
		else
			if ( op->IsMem() )
				cout << op->GetMem();
			else
				if ( op->IsAddr() )
					FlushAddrX( op );
				else
				cout << op->GetStr();
}

void CodeGen::FlushConstX( Op *op )
{
	float conv;
	if ( op->IsInt() )
		cout << op->GetInt();
	else
	{
		conv = op->GetFloat();
		cout << hex << 0 << *(int*)&conv << "h" << dec;
	}
}
void CodeGen::FlushConst( Op *op )
{
	float conv;
	if ( op->IsInt() )
		*asm_file << op->GetInt();
	else
	{
		conv = op->GetFloat();
		*asm_file << hex << 0 << *(int*)&conv << "h" << dec;
	}
}
void CodeGen::FlushAddrX( Op *op )
{
	if ( op->IsDaddr() )
		cout << "dword ptr [ ";
	else
		cout << "qword ptr [ ";
	cout << RegTable[ op->GetReg() ];
	if ( op->GetOffset() > 0 )
		cout << " + " + IntToString( op->GetOffset() );
	else
		if ( op->GetOffset() < 0 )
			cout << " " + IntToString( op->GetOffset() );
	cout << " ]";
}
void CodeGen::FlushAddr( Op *op )
{
	if ( op->IsDaddr() )
		*asm_file << "dword ptr [ ";
	else
		*asm_file << "qword ptr [ ";
	*asm_file << RegTable[ op->GetReg() ];
	if ( op->GetOffset() > 0 )
		*asm_file << " + " + IntToString( op->GetOffset() );
	else
		if ( op->GetOffset() < 0 )
			*asm_file << " " + IntToString( op->GetOffset() );
	*asm_file << " ]";
}
void CodeGen::Flush()
{
	*asm_file << "\n";
	MnemCom mnem;
	TAsmCommand *fl;
	Op *op1, *op2, *op3;
	while ( buffer->size() )
	{
		fl = buffer->front();
		mnem = fl->GetMnem();
		op1 = fl->GetOp1();
		op2 = fl->GetOp2();
		op3 = fl->GetOp3();
		//mnem = (*buffer)[0]->GetMnem();
		
		//var declaration, f.e. "v_a dd 4"
		//op1 is memory(f.e. "v_a"), op2 is immediate (value) or string ("?")
		if ( mnem < 2 )
		{
			*asm_file << op1->GetMem() << "\t";
			*asm_file << ComTable[ mnem ];

			*asm_file << "\t";

			if ( op2->IsStr() )
				*asm_file << op2->GetStr();
			else
				FlushConst( op2 );
		}
		else
			if ( mnem == LABEL )
				*asm_file << op1->GetStr() << ":";
			else
				if ( mnem == DUP )
				{
					*asm_file << op1->GetMem();
					*asm_file << "\tdb\t";
					*asm_file << op2->GetInt();
					*asm_file << " dup (?)";
				}
				else
					if (  ( mnem == PROC ) || ( mnem == ENDP )  )
					{
						if ( mnem == PROC )
							*asm_file << "\n\n";
						*asm_file << op1->GetStr();
						*asm_file << "\t" << ComTable[mnem];
						if ( mnem == ENDP )
							*asm_file << "\n\n";
					}
					else
					{
						*asm_file << ComTable[mnem] << "\t";

						if ( op1 )
						{
							FlushOp( op1 );
							if ( op2 )
							{
								*asm_file << ",\t";
								FlushOp( op2 );
                                if ( op3 )
								{
									*asm_file << ",\t";
									FlushOp( op3 );
								}
							}
						}
					};
		buffer->erase( buffer->begin() );
		*asm_file << "\n";
	}
	*asm_file << "\n";
}


//генерирует 1 команду ассемблера и добавляет её в буфер
void CodeGen::Gen( MnemCom mnem , Op *op1 , Op *op2 , Op *op3 )
{
	if ( commenting || ( Com != mnem ) )
		buffer->push_back( new TAsmCommand( mnem , op1 , op2 , op3 ) );
}

bool CodeGen::NeedOptim()
{
	return optimizing;
}

bool CodeGen::EqualOperands( Op *op1 , Op *op2 )
{
	if ( op1 && op2 )
	{
		if ( op1->IsAddr() && op2->IsAddr() )
		{
			if ( op1->IsDaddr() != op2->IsDaddr() )
				return 0;
			return ( ( op1->GetReg() == op2->GetReg() )
				&& ( op1->GetOffset() == op2->GetOffset() ) );
		}
		else
			if ( op1->IsMem() && op2->IsMem() )
				return op1->GetMem() == op2->GetMem();
			else
				if ( op1->IsReg() && op2->IsReg() )
					return op1->GetReg() == op2->GetReg();
	}
	return 0;
}
Op *CodeGen::CopyOp( Op *op )
{
	Op *newop;
	if ( op->IsReg() )
		newop = new Reg( op->GetReg() );
	else
		if ( op->IsMem() )
			newop = new Mem( op->GetMem() );
		else
			if ( op->IsImm() )
			{
				if ( op->IsInt() )
					newop = new Imm( op->GetInt() );
				else
					newop = new Imm( op->GetFloat() );
			}
			else
				if ( op->IsAddr() )
					newop = new Addr( op->GetReg() , op->GetOffset() , !op->IsDaddr() );
	return newop;
}
//if the command can change stack in some way 
//throught this operand
bool CodeGen::StackOp( Op *op )
{
	if ( op )
	{
		if ( op->IsReg() )
			if ( op->GetReg() == esp )
				return 1;
		if ( op->IsAddr() )	
			return 1;
		if ( op->IsStr() )
			return 1;
	}
	return 0;
}
bool CodeGen::SameRegOp( MnemReg reg , Op *tocheck )
{
	if ( tocheck )
		if ( tocheck->IsReg() )
			if ( tocheck->GetReg() == reg )
				return 1;
	return 0;
}
bool CodeGen::SameMemOp( string mem , Op *tocheck )
{
	if ( tocheck )
		if ( tocheck->IsMem() )
			if ( tocheck->GetMem() == mem )
				return 1;
	return 0;
}
bool CodeGen::AllowedToExchange( TAsmCommand *p , TAsmCommand *com )
{
	MnemCom mcom = com->GetMnem();
	if ( NoChangeWith[mcom] != "" )
		return 0;	

	if (  StackOp( p->GetOp1() ) ||
		StackOp( com->GetOp1() ) ||
		StackOp( com->GetOp2() ) ||
		StackOp( com->GetOp3() )  )
	return 0;
	
	if ( p->GetOp1()->IsReg() )
	{
		MnemReg reg = p->GetOp1()->GetReg();
		if (  SameRegOp( reg , com->GetOp1() ) ||
			SameRegOp( reg , com->GetOp2() ) ||
			SameRegOp( reg , com->GetOp3() )  )
			return 0;		
	}
	//if mem
	else
		if ( p->GetOp1()->IsMem() )
		{
			string mem = p->GetOp1()->GetMem();
			if (  SameMemOp( mem , com->GetOp1() ) ||
				SameMemOp( mem , com->GetOp2() ) ||
				SameMemOp( mem , com->GetOp3() )  )
				return 0;
		}
	return 1;
}
void CodeGen::ReplaceCom( TAsmCommand *newcom )
{
	iter = buffer->begin() + opt1;
	delete( *iter );
	*iter = newcom;
}
void CodeGen::Exchange()
{
	TAsmCommand *temp = (*buffer)[opt1];
	(*buffer)[opt1] = (*buffer)[opt2];
	(*buffer)[opt2] = temp;
}
//deletes the opt1
void CodeGen::DelCom()
{
	buffer->erase( buffer->begin() + opt1 );
}
void CodeGen::CreateOptPointers()
{
	opt1 = 0;
	opt2 = 1;
}
void CodeGen::NextOptPointers()
{
	++opt1;
	++opt2;
}
bool CodeGen::Finished()
{
	return opt2 >= buffer->size();
}
void CodeGen::WatchPeepHole()
{
	bool optim_done = false;
	TAsmCommand *a, *b, *temp;	
	for ( int i = 0 ; ( i < 500 ) && !optim_done ; ++i )
	{	
		CreateOptPointers();
		optim_done = true;
		while ( !Finished() )
		{
			a = (*buffer)[opt1];
			b = (*buffer)[opt2];	
			Op *aop1 = a->GetOp1(), *aop2 = a->GetOp2(),
				*bop1 = b->GetOp1(), *bop2 = b->GetOp2();

			//push eax, pop eax; pop eax, push eax
			if (  a->IsPush() && b->IsPop() &&
				EqualOperands( aop1 , bop1 ) )
			{
				optim_done = false;
				DelCom();
				DelCom();
				continue;
			}

			if ( a->IsPush() && ( b->GetMnem() == ADD ) )
				if ( bop1->GetReg() == esp )
				{
					optim_done = false;
					if ( bop2->GetInt() == 4 )
					{
						DelCom();
						DelCom();
					}
					if ( bop2->GetInt() > 4 )
					{
						temp = new TAsmCommand( ADD , reg( esp ) , imm( bop2->GetInt() - 4 ) );
						DelCom();
						ReplaceCom( temp );
					}
					continue;
				};


			//push x, pop y, x or y is register
			if ( a->IsPush() && b->IsPop() && 
				( aop1->IsReg() || bop1->IsReg() ) )
			{
				optim_done = false;
				temp = new TAsmCommand( MOV , CopyOp( bop1 ) , CopyOp( aop1 ) );
				DelCom();
				ReplaceCom( temp );
				continue;
			}

			///grouping togehter such adds and subs:
			//add reg, imm; sub reg, imm
			//add mem, imm; sub mem, imm		
			if (  ( ( a->GetMnem() == ADD ) || ( a->GetMnem() == SUB ) ) &&	( ( b->GetMnem() == ADD ) || ( b->GetMnem() == SUB ) )  )
			{
				if ( aop2->IsImm() && bop2->IsImm() )
				{
					if (   ( aop1->IsReg() && bop1->IsReg() && ( aop1->GetReg() == bop1->GetReg() ) ) ||
						( aop1->IsMem() && bop1->IsMem() && ( aop1->GetMem() == bop1->GetMem() ) )   )
					{
						optim_done = false;
						int toadd = 0;
						if ( a->GetMnem() == ADD )
							toadd += aop2->GetInt();
						else
							toadd -= aop2->GetInt();
						if ( b->GetMnem() == ADD )
							toadd += bop2->GetInt();
						else
							toadd -= bop2->GetInt();

						if ( toadd < 0 )
							temp = new TAsmCommand( SUB , CopyOp( aop1 ) , imm( -toadd ) );
						else
							if ( toadd > 0 )
								temp = new TAsmCommand( ADD , CopyOp( aop1 ) , imm( toadd ) );
							else
								DelCom();
						DelCom();
						if ( toadd )
							ReplaceCom( temp );
						continue;
					}
				}
			}

			//add smth, 0
			if ( a->GetMnem() == ADD )
				if ( aop2->IsImm() )
					if ( !aop2->GetInt() )
					{
						DelCom();
						continue;
					}
			//cmp smth, 0
			if ( a->GetMnem() == CMP )
				if ( aop2->IsImm() )
					if ( !aop2->GetInt() )
					{
						temp = new TAsmCommand( TEST , CopyOp( a->GetOp1() ) , CopyOp( a->GetOp1() ) );
						ReplaceCom( temp );
						continue;
					}
			//mov smth, 0
			if ( a->GetMnem() == MOV )
				if ( aop2->IsImm() && !aop2->GetInt() )
					if ( aop1->IsReg() || aop1->IsMem() )
					{
						temp = new TAsmCommand( XOR , CopyOp( a->GetOp1() ) , CopyOp( a->GetOp1() ) );
						ReplaceCom( temp );
						continue;
					}

			//try to exchange
			if ( i < 250 )
			{
				if (   ( a->IsPop() && !b->IsPush() && !b->IsPop() ) ||
					( b->IsPush() && !a->IsPush() && !a->IsPop() )   )
				{
					optim_done = false;
					//optim_done = false;
					if ( a->IsPop() )
					{
						if ( AllowedToExchange( a , b ) )
						{
							Exchange();
							continue;
						}					
					}
					else
						if ( AllowedToExchange( b , a ) )
						{
							Exchange();
							continue;
						}
				}
			}
			else
			{
				if (   ( a->IsPush() && !b->IsPush() && !b->IsPop() ) ||
					( b->IsPop() && !a->IsPush() && !a->IsPop() )   )
				{
					optim_done = false;
					//optim_done = false;
					if ( a->IsPush() )
					{
						if ( AllowedToExchange( a , b ) )
						{
							Exchange();
							continue;
						}					
					}
					else
						if ( AllowedToExchange( b , a ) )
						{
							Exchange();
							continue;
						}
				}
			}
			NextOptPointers();
			//see if not shorted
		}
	}
}