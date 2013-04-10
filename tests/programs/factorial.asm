include ..\..\include\start.inc

str0	db	78, 117, 109, 98, 101, 114, 58, 32, 0
str1	db	37, 105, 0
str2	db	70, 97, 99, 116, 111, 114, 105, 97, 108, 32, 105, 115, 58, 32, 37, 105, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_factorial	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
pop	eax
test	eax,	eax
jz	label0
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
push	1
pop	ebx
pop	eax
sub	eax,	ebx
push	eax
call	f_factorial
add	esp,	4
push	eax
pop	ebx
pop	eax
imul	ebx
push	eax
pop	eax
add	esp,	0
jmp	return_factorial
label0:
push	1
pop	eax
add	esp,	0
jmp	return_factorial
xor	eax,	eax
return_factorial:
pop	ebp
ret	
f_factorial	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	0
push	offset data:str0
call	_printf
add	esp,	4
push	eax
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
push	offset data:str1
call	_scanf
add	esp,	8
push	eax
add	esp,	4
push	dword ptr [ ebp -4 ]
call	f_factorial
add	esp,	4
push	eax
mov	eax,	ebp
sub	eax,	4
push	eax
pop	eax
pop	ebx
mov	dword ptr [ eax ],	ebx
push	ebx
add	esp,	4
push	dword ptr [ ebp -4 ]
push	offset data:str2
call	_printf
add	esp,	8
push	eax
add	esp,	4
add	esp,	4
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc