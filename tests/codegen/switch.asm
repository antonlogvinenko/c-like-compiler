include ..\..\include\start.inc

str0	db	98, 108, 97, 10, 0
str1	db	66, 76, 65, 10, 0
str2	db	110, 111, 98, 108, 97, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	2
mov	ebx,	dword ptr [ ebp -4 ]
mov	eax,	2
cmp	eax,	ebx
je	label1
mov	eax,	1
cmp	eax,	ebx
je	label2
xor	eax,	eax
cmp	eax,	ebx
je	label3
jmp	label0
label1:
push	offset data:str0
call	_printf
add	esp,	4
label2:
push	offset data:str1
call	_printf
add	esp,	4
jmp	label0
label3:
push	offset data:str2
call	_printf
add	esp,	4
label0:
add	esp,	4
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc