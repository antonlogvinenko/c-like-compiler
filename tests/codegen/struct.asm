include ..\..\include\start.inc

str0	db	108, 101, 102, 116, 58, 37, 105, 32, 44, 32, 114, 105, 103, 104, 116, 58, 37, 105, 10, 10, 0
str1	db	37, 105, 37, 105, 10, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	16
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	4
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	ebx,	777
mov	dword ptr [ eax ],	ebx
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	4
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	ebx,	888
mov	dword ptr [ eax ],	ebx
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	ebx,	7
mov	dword ptr [ eax ],	ebx
mov	eax,	12
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	ebx,	8
mov	dword ptr [ eax ],	ebx
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	4
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	4
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	offset data:str0
call	_printf
add	esp,	12
mov	eax,	12
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	offset data:str1
call	_printf
add	esp,	28
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc