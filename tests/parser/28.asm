include ..\..\include\start.inc



include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp






f_g	proc
push	ebp
mov	ebp,	esp
mov	eax,	8
mov	ebx,	4
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	2
push	eax
mov	eax,	6
mov	ebx,	24
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
xor	eax,	eax
return_g:
pop	ebp
ret	
f_g	endp




include ..\..\include\end.inc