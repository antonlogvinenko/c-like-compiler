include ..\..\include\start.inc

v_b	dd	?
v_yyy	dd	?
v_i	dd	?


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
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc