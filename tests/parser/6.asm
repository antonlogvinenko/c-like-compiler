include ..\..\include\start.inc



include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	0
mov	eax,	dword ptr [ ebp -4 ]
test	eax,	eax
jz	label0
mov	eax,	ebp
sub	eax,	4
mov	ebx,	1
mov	dword ptr [ eax ],	ebx
jmp	label1
label0:
label1:
add	esp,	4
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc