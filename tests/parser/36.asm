include ..\..\include\start.inc



include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_f	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
return_f:
pop	ebp
ret	
f_f	endp






f_h	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
return_h:
pop	ebp
ret	
f_h	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	72
mov	eax,	ebp
sub	eax,	76
push	eax
call	f_h
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
push	040666666h
call	f_f
add	esp,	80
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc