include ..\..\include\start.inc



include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	100
mov	eax,	2
mov	ebx,	4
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	2
push	eax
mov	eax,	5
mov	ebx,	20
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	100
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc