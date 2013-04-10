#pragma once
#include "stdafx.h"


struct Position
{
	int Line, Column;
	Position( int l = 1 , int c = 0 );
};

enum Type
{
none, eof, name,
kfor, kif, kelse, kwhile, kswitch, kcase, kdefault, kfloat, kstring, kint, kstruct, ktypedef, kreturn, kbreak, kcontinue,
oincr, odecr, oplus, ominus, odiv, omul, oassign,
oassignplus, oassignmin, oassigndiv, oassignmul,
ogreat, oless, oegreat, oeless, oequal, onequal, oand, oor, onot, oamper,
slbrace, srbrace, slfigbrace, srfigbrace, slsqbrace, srsqbrace, ssemic, sdot, scomma, scolon,
cint, cstr, cfloat
};