include ..\..\include\start.inc

str0	db	104, 111, 111, 111, 111, 104, 46, 46, 46, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	0
push	0
jmp	label0
label1:
sub	esp,	840
push	0
push	0
push	0
push	0
mov	eax,	dword ptr [ ebp -4 ]
test	eax,	eax
jz	label2
push	offset data:str0
call	_printf
add	esp,	4
xor	eax,	eax
add	esp,	864
jmp	return_main
label2:
sub	esp,	200
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	1056
jmp	label0
add	esp,	216
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	840
label0:
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	20
xor	edx,	edx
cmp	eax,	ebx
jnl	label3
mov	edx,	1
label3:
mov	eax,	edx
test	eax,	eax
jnz	label1
add	esp,	8
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc