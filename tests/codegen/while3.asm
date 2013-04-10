include ..\..\include\start.inc

str0	db	72, 111, 111, 111, 111, 104, 46, 46, 46, 46, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	48
jmp	label0
label1:
jmp	label2
add	esp,	228
label0:
mov	eax,	1
test	eax,	eax
jnz	label1
label2:
push	offset data:str0
call	_printf
add	esp,	52
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc