include ..\..\include\start.inc

v_a	dd	8


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_g	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
return_g:
pop	ebp
ret	
f_g	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	72
mov	eax,	ebp
sub	eax,	4
push	040666666h
push	0
push	eax
call	f_g
add	esp,	84
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc