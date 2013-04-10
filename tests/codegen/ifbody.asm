include ..\..\include\start.inc

str0	db	97, 32, 105, 115, 32, 50, 10, 0
str1	db	97, 32, 105, 115, 32, 110, 111, 116, 32, 50, 10, 0
str2	db	46, 46, 46, 98, 97, 100, 32, 98, 114, 97, 110, 99, 104, 0
str3	db	103, 111, 111, 100, 32, 98, 114, 97, 110, 99, 104, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	2
push	040e00000h
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	2
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
push	dword ptr [ ebp -8 ]
push	666
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
jnz	label4
mov	eax,	1
label4:
FFREE	st(0)
FINCSTP	
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