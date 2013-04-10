include ..\..\include\start.inc

str0	db	37, 105, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_f	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	8
push	6
mov	eax,	dword ptr [ eax ]
pop	ebx
mov	dword ptr [ eax ],	ebx
xor	eax,	eax
return_f:
pop	ebp
ret	
f_f	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	288
mov	eax,	1
mov	ebx,	4
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	5
push	eax
mov	eax,	1
mov	ebx,	16
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	48
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	96
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
pop	ebx
sub	eax,	ebx
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	1
mov	ebx,	4
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	16
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	48
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	96
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
pop	ebx
sub	eax,	ebx
pop	ebx
sub	eax,	ebx
push	eax
call	f_f
add	esp,	4
mov	eax,	1
mov	ebx,	4
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	16
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	48
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	1
mov	ebx,	96
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
pop	ebx
sub	eax,	ebx
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	offset data:str0
call	_printf
add	esp,	296
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc