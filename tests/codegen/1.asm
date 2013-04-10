include ..\..\include\start.inc

str0	db	37, 102, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	10
push	04039999ah
push	dword ptr [ ebp -4 ]
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
push	dword ptr [ ebp -8 ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
push	offset data:str0
call	_printf
add	esp,	20
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc