include ..\..\include\start.inc



include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_kill	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
return_kill:
pop	ebp
ret	
f_kill	endp






f_main	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc