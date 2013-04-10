#pragma once
#include "stdafx.h"
#include "codegentools.h"
#include "tsymtable.h"


class CodeGen
{
	vector<int> *topop;
	bool optimizing, commenting;
	map< MnemCom, string > ComTable, NoChangeWith;
	map< MnemReg, string > RegTable;
	string asm_filename;
	vector< string > *continues, *breaks;
	ofstream *asm_file;
	vector< TAsmCommand * > *buffer;
	vector< TAsmCommand * >::iterator iter;
	int opt1, opt2;
	int label;
public:
	CodeGen( string  , bool  , bool  = false );
	string GenLabel();
	bool ComEnabled();
	void PushContinue( string  );
	void PopContinue();
	string GetContinueLabel();
	string GetBreakLabel();
	void PushBreak( string  );
	void PopBreak();
	void PushHaltPops();
	void PopHaltPops();
	void AddHaltPops( int  );
	void SubHaltPops( int  );
	int HaltPops();
	//visually shifts the asm code so it becomes easier to read
	void GenStart();//начинает .asm файл
	void GenMiddle();
	void GenFinish();//заканчивает .asm файл*/
	void Flush();//сбрасывает содержимое буфера в файл
	void FlushOp( Op *  );
	void FlushAddr( Op *  );
	string IntToString( int  );
	void FlushConst( Op *  );
	void Gen( MnemCom  , Op *  = NULL , Op *  = NULL , Op *  = NULL );	
	//these are for the "PeEp HoLe":
	void WatchPeepHole();
	void CreateOptPointers();	
	void NextOptPointers();
	bool Finished();
	void DelCom();
	bool NeedOptim();
	bool EqualOperands( Op *  , Op *  );
	void ReplaceCom( TAsmCommand *  );
	bool AllowedToExchange( TAsmCommand *  , TAsmCommand *  );
	bool SameMemOp( string  , Op *  );
	bool SameRegOp( MnemReg  , Op *  );
	bool StackOp( Op *  );
	Op *CopyOp( Op * );
	void Exchange();

	void FlushOpX( Op *  );
	void FlushAddrX( Op *  );
	void FlushConstX( Op *  );

	friend class Op;
};