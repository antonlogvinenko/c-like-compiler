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
call	f_f
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc