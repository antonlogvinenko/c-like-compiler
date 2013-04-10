include ..\..\include\start.inc

v_a	dd	?


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	600
mov	eax,	2
mov	ebx,	4
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	3
mov	ebx,	20
mul	ebx
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	2
mov	ebx,	120
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
xor	eax,	eax
add	esp,	604
jmp	return_main
add	esp,	604
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc