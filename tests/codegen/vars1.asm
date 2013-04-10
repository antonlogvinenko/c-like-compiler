include ..\..\include\start.inc

str0	db	37, 105, 0
v_jooh	dd	777


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_C	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	12
push	0
push	0
push	dword ptr [ eax ]
push	offset data:str0
call	_printf
add	esp,	16
xor	eax,	eax
return_C:
pop	ebp
ret	
f_C	endp






f_B	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	12
push	0
push	0
push	1
push	dword ptr [ eax ]
push	2
call	f_C
add	esp,	20
xor	eax,	eax
return_B:
pop	ebp
ret	
f_B	endp






f_A	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	12
push	0
push	0
push	1
push	dword ptr [ eax ]
push	2
call	f_B
add	esp,	20
xor	eax,	eax
return_A:
pop	ebp
ret	
f_A	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	1
push	1
push	v_jooh
push	2
call	f_A
add	esp,	16
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc