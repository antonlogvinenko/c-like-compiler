include ..\..\include\start.inc

str0	db	72, 111, 111, 111, 111, 111, 104, 46, 46, 46, 0
v_i	dd	0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	48
jmp	label0
label1:
push	0
push	0
push	0
push	0
sub	esp,	212
mov	eax,	v_i
test	eax,	eax
jz	label3
push	offset data:str0
call	_printf
add	esp,	4
xor	eax,	eax
add	esp,	276
jmp	return_main
label3:
mov	eax,	offset data:v_i
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	228
jmp	label0
add	esp,	228
label0:
mov	eax,	1
test	eax,	eax
jnz	label1
add	esp,	48
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc