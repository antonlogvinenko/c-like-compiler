include ..\..\include\start.inc

str0	db	101, 110, 116, 101, 114, 32, 97, 32, 110, 117, 109, 98, 101, 114, 58, 0
str1	db	37, 105, 0


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
push	offset data:str0
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
push	offset data:str1
call	_scanf
add	esp,	8
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	7
xor	edx,	edx
cmp	eax,	ebx
jne	label4
mov	edx,	1
label4:
mov	eax,	edx
test	eax,	eax
jz	label3
jmp	label2
label3:
label0:
mov	eax,	1
test	eax,	eax
jnz	label1
label2:
add	esp,	4
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc