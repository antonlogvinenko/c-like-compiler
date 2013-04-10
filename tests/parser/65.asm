include ..\..\include\start.inc

v_h	dd	?


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
jmp	return_main
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc