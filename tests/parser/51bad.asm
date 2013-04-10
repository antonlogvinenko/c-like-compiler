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






f_main	proc
push	ebp
mov	ebp,	esp
push	0
call	f_f
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
mov	dword ptr [ eax ],	ebx
add	esp,	4
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc