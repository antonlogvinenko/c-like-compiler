include ..\..\include\start.inc

str0	db	101, 110, 116, 101, 114, 32, 118, 97, 108, 117, 101, 32, 78, 32, 37, 105, 32, 10, 0
str1	db	37, 105, 0
str2	db	101, 110, 116, 101, 114, 101, 100, 58, 0
str3	db	37, 105, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	40
push	0
jmp	label0
label1:
push	dword ptr [ ebp -44 ]
push	offset data:str0
call	_printf
add	esp,	8
push	0
mov	eax,	dword ptr [ ebp -44 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
push	eax
push	offset data:str1
call	_scanf
add	esp,	8
push	0
mov	eax,	dword ptr [ ebp -44 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
xor	edx,	edx
test	eax,	eax
jne	label3
mov	edx,	1
label3:
mov	eax,	edx
test	eax,	eax
jz	label2
jmp	label0
label2:
mov	eax,	ebp
sub	eax,	44
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label0:
mov	eax,	dword ptr [ ebp -44 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label4
mov	edx,	1
label4:
mov	eax,	edx
test	eax,	eax
jnz	label1
push	offset data:str2
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	44
xor	ebx,	ebx
mov	dword ptr [ eax ],	ebx
jmp	label5
label6:
push	0
mov	eax,	dword ptr [ ebp -44 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	offset data:str3
call	_printf
add	esp,	8
mov	eax,	ebp
sub	eax,	44
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label5:
mov	eax,	dword ptr [ ebp -44 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label7
mov	edx,	1
label7:
mov	eax,	edx
test	eax,	eax
jnz	label6
add	esp,	44
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc