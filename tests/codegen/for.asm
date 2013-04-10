include ..\..\include\start.inc

str0	db	37, 105, 10, 0


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
push	dword ptr [ ebp -4 ]
mov	ebx,	dword ptr [ ebp -4 ]
pop	eax
imul	ebx
push	eax
push	offset data:str0
call	_printf
add	esp,	8
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label0:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	16
xor	edx,	edx
cmp	eax,	ebx
jnl	label2
mov	edx,	1
label2:
mov	eax,	edx
test	eax,	eax
jnz	label1
add	esp,	4
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc