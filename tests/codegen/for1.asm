include ..\..\include\start.inc

str0	db	104, 111, 111, 111, 111, 111, 104, 46, 46, 46, 46, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	0
jmp	label0
label1:
jmp	label2
add	esp,	216
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	840
label0:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	20
xor	edx,	edx
cmp	eax,	ebx
jnl	label3
mov	edx,	1
label3:
mov	eax,	edx
test	eax,	eax
jnz	label1
label2:
push	offset data:str0
call	_printf
add	esp,	8
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc