include ..\..\include\start.inc

str0	db	69, 110, 116, 101, 114, 32, 116, 104, 101, 32, 110, 117, 109, 98, 101, 114, 58, 10, 0
str1	db	37, 102, 0
str2	db	69, 110, 116, 101, 114, 32, 116, 104, 101, 32, 97, 99, 99, 117, 114, 97, 99, 121, 58, 10, 0
str3	db	37, 102, 0
str4	db	37, 102, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_abs	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
push	0
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
jz	label1
jnc	label1
mov	eax,	1
label1:
FFREE	st(0)
FINCSTP	
test	eax,	eax
jz	label0
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
fld	dword ptr [ esp ]
fchs	
fstp	dword ptr [ esp ]
pop	eax
jmp	return_abs
label0:
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
jmp	return_abs
xor	eax,	eax
return_abs:
pop	ebp
ret	
f_abs	endp






f_square_root	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	12
push	0
push	0
push	00h
push	0
push	dword ptr [ eax ]
push	1
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
jz	label3
jc	label3
mov	eax,	1
label3:
FFREE	st(0)
FINCSTP	
test	eax,	eax
jz	label2
mov	eax,	ebp
add	eax,	12
mov	ebx,	dword ptr [ eax ]
mov	eax,	ebp
sub	eax,	16
mov	dword ptr [ eax ],	ebx
jmp	label4
label2:
push	1
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
pop	ebx
mov	eax,	ebp
sub	eax,	16
mov	dword ptr [ eax ],	ebx
label4:
push	dword ptr [ ebp -12 ]
push	dword ptr [ ebp -16 ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
push	2
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fdivp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
pop	ebx
mov	eax,	ebp
sub	eax,	4
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
sub	eax,	8
mov	dword ptr [ eax ],	ebx
jmp	label5
label6:
push	dword ptr [ ebp -4 ]
push	dword ptr [ ebp -4 ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	ebp
add	eax,	12
push	dword ptr [ eax ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
ja	label9
mov	eax,	1
label9:
FFREE	st(0)
FINCSTP	
test	eax,	eax
jz	label8
mov	ebx,	dword ptr [ ebp -4 ]
mov	eax,	ebp
sub	eax,	12
mov	dword ptr [ eax ],	ebx
jmp	label10
label8:
mov	ebx,	dword ptr [ ebp -4 ]
mov	eax,	ebp
sub	eax,	16
mov	dword ptr [ eax ],	ebx
label10:
push	dword ptr [ ebp -12 ]
push	dword ptr [ ebp -16 ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
push	2
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fdivp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
pop	ebx
mov	eax,	ebp
sub	eax,	4
mov	dword ptr [ eax ],	ebx
push	dword ptr [ ebp -8 ]
push	dword ptr [ ebp -4 ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
jnz	label12
mov	eax,	1
label12:
FFREE	st(0)
FINCSTP	
test	eax,	eax
jz	label11
jmp	label7
label11:
mov	ebx,	dword ptr [ ebp -4 ]
mov	eax,	ebp
sub	eax,	8
mov	dword ptr [ eax ],	ebx
label5:
push	dword ptr [ ebp -4 ]
push	dword ptr [ ebp -4 ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	ebp
add	eax,	12
push	dword ptr [ eax ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fsubp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
call	f_abs
add	esp,	4
push	eax
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
jc	label13
mov	eax,	1
label13:
FFREE	st(0)
FINCSTP	
test	eax,	eax
jnz	label6
label7:
mov	eax,	dword ptr [ ebp -4 ]
add	esp,	16
jmp	return_square_root
add	esp,	16
xor	eax,	eax
return_square_root:
pop	ebp
ret	
f_square_root	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	0
push	0
push	0
push	offset data:str0
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
push	offset data:str1
call	_scanf
add	esp,	8
push	offset data:str2
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	12
push	eax
push	offset data:str3
call	_scanf
add	esp,	8
push	dword ptr [ ebp -4 ]
push	dword ptr [ ebp -12 ]
call	f_square_root
add	esp,	8
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	8
mov	dword ptr [ eax ],	ebx
push	dword ptr [ ebp -8 ]
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
push	offset data:str4
call	_printf
add	esp,	24
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc