include ..\..\include\start.inc

str0	db	97, 32, 105, 115, 32, 55, 51, 10, 0
str1	db	97, 32, 105, 115, 110, 39, 116, 32, 55, 51, 10, 0
str2	db	98, 32, 105, 115, 32, 57, 0
str3	db	98, 32, 105, 115, 32, 110, 111, 116, 32, 57, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	73
push	8
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	73
xor	edx,	edx
cmp	eax,	ebx
jne	label1
mov	edx,	1
label1:
mov	eax,	edx
test	eax,	eax
jz	label0
push	offset data:str0
call	_printf
add	esp,	4
jmp	label2
label0:
push	offset data:str1
call	_printf
add	esp,	4
label2:
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	9
xor	edx,	edx
cmp	eax,	ebx
jne	label4
mov	edx,	1
label4:
mov	eax,	edx
test	eax,	eax
jz	label3
push	offset data:str2
call	_printf
add	esp,	4
jmp	label5
label3:
push	offset data:str3
call	_printf
add	esp,	4
label5:
add	esp,	8
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc