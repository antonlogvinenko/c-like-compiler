include ..\..\include\start.inc

str0	db	97, 32, 97, 110, 100, 32, 98, 58, 32, 49, 32, 97, 110, 100, 32, 50, 0
str1	db	115, 111, 109, 101, 116, 104, 105, 110, 103, 32, 115, 116, 114, 97, 110, 103, 101, 32, 104, 97, 115, 32, 104, 97, 112, 112, 101, 110, 101, 100, 46, 46, 46, 0
str2	db	115, 116, 114, 97, 110, 103, 101, 32, 97, 103, 97, 105, 110, 46, 46, 46, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	1
push	2
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	1
xor	edx,	edx
cmp	eax,	ebx
jne	label1
mov	edx,	1
label1:
mov	eax,	edx
test	eax,	eax
jz	label0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	2
xor	edx,	edx
cmp	eax,	ebx
jne	label3
mov	edx,	1
label3:
mov	eax,	edx
test	eax,	eax
jz	label2
push	offset data:str0
call	_printf
add	esp,	4
jmp	label4
label2:
push	offset data:str1
call	_printf
add	esp,	4
label4:
jmp	label5
label0:
push	offset data:str2
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