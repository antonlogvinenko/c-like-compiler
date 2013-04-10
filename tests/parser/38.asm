include ..\..\include\start.inc



include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
mov	eax,	1
test	eax,	eax
jz	label0
jmp	label1
label0:
label1:
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc