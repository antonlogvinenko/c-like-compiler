include ..\..\include\start.inc



include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
jmp	label0
label1:
mov	eax,	1
test	eax,	eax
jz	label3
label3:
jmp	label2
label0:
mov	eax,	1
test	eax,	eax
jnz	label1
label2:
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc