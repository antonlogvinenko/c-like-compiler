include ..\..\include\start.inc

str0	db	101, 110, 116, 101, 114, 32, 99, 111, 109, 112, 108, 101, 120, 32, 110, 117, 109, 98, 101, 114, 58, 10, 0
str1	db	37, 102, 37, 102, 0
str2	db	40, 37, 102, 41, 32, 43, 32, 40, 37, 102, 41, 32, 105, 10, 0
str3	db	101, 114, 114, 111, 114, 32, 119, 104, 101, 110, 32, 100, 105, 118, 105, 100, 105, 110, 103, 10, 0
str4	db	100, 105, 118, 58, 32, 0
str5	db	109, 111, 100, 117, 108, 101, 58, 32, 37, 102, 10, 0
str6	db	109, 117, 108, 58, 32, 0
str7	db	109, 111, 100, 117, 108, 101, 58, 32, 37, 102, 10, 0
str8	db	97, 100, 100, 58, 32, 0
str9	db	109, 111, 100, 117, 108, 101, 58, 32, 37, 102, 0


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
add	eax,	8
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
add	eax,	8
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
add	eax,	8
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
add	eax,	8
push	dword ptr [ eax ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fsubp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
call	f_abs
add	esp,	4
push	eax
push	02edbe6ffh
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






f_module	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
call	f_square_root
add	esp,	4
jmp	return_module
xor	eax,	eax
return_module:
pop	ebp
ret	
f_module	endp






f_div	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
push	0
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
jnz	label15
mov	eax,	1
label15:
FFREE	st(0)
FINCSTP	
test	eax,	eax
jz	label14
xor	eax,	eax
add	esp,	4
jmp	return_div
label14:
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fsubp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
push	dword ptr [ ebp -4 ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
fld	dword ptr [ eax ]
fld	dword ptr [ esp ]
fdivp	st(1),	st(0)
fst	dword ptr [ eax ]
fstp	dword ptr [ esp ]
add	esp,	4
push	dword ptr [ ebp -4 ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
fld	dword ptr [ eax ]
fld	dword ptr [ esp ]
fdivp	st(1),	st(0)
fst	dword ptr [ eax ]
fstp	dword ptr [ esp ]
add	esp,	4
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
call	f_module
add	esp,	8
jmp	return_div
add	esp,	4
xor	eax,	eax
return_div:
pop	ebp
ret	
f_div	endp






f_mul	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fsubp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
fmulp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
call	f_module
add	esp,	4
jmp	return_mul
xor	eax,	eax
return_mul:
pop	ebp
ret	
f_mul	endp






f_add	proc
push	ebp
mov	ebp,	esp
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp + 4 ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
add	esp,	4
fstp	dword ptr [ esp ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
add	eax,	8
push	dword ptr [ eax ]
call	f_module
add	esp,	4
jmp	return_add
xor	eax,	eax
return_add:
pop	ebp
ret	
f_add	endp






f_scanC	proc
push	ebp
mov	ebp,	esp
push	0
push	0
push	offset data:str0
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	8
push	eax
mov	eax,	ebp
sub	eax,	4
push	eax
push	offset data:str1
call	_scanf
add	esp,	12
push	dword ptr [ ebp -4 ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
push	dword ptr [ ebp -8 ]
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	8
xor	eax,	eax
return_scanC:
pop	ebp
ret	
f_scanC	endp






f_printC	proc
push	ebp
mov	ebp,	esp
mov	eax,	4
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
push	offset data:str2
call	_printf
add	esp,	20
xor	eax,	eax
return_printC:
pop	ebp
ret	
f_printC	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	24
mov	eax,	ebp
sub	eax,	4
push	0
push	eax
call	f_scanC
add	esp,	4
mov	eax,	ebp
sub	eax,	12
push	eax
call	f_scanC
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
mov	eax,	ebp
sub	eax,	12
push	eax
mov	eax,	ebp
sub	eax,	20
push	eax
call	f_div
add	esp,	12
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	28
mov	dword ptr [ eax ],	ebx
push	ebx
push	-1
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
fld	dword ptr [ esp ]
fld	dword ptr [ esp + 4 ]
add	esp,	8
xor	eax,	eax
fcomip	st,	st(1)
jnz	label17
mov	eax,	1
label17:
FFREE	st(0)
FINCSTP	
test	eax,	eax
jz	label16
push	offset data:str3
call	_printf
add	esp,	4
jmp	label18
label16:
push	offset data:str4
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	20
push	eax
call	f_printC
add	esp,	4
push	dword ptr [ ebp -28 ]
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
push	offset data:str5
call	_printf
add	esp,	12
label18:
mov	eax,	ebp
sub	eax,	4
push	eax
mov	eax,	ebp
sub	eax,	12
push	eax
mov	eax,	ebp
sub	eax,	20
push	eax
call	f_mul
add	esp,	12
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	28
mov	dword ptr [ eax ],	ebx
push	offset data:str6
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	20
push	eax
call	f_printC
add	esp,	4
push	dword ptr [ ebp -28 ]
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
push	offset data:str7
call	_printf
add	esp,	12
mov	eax,	ebp
sub	eax,	4
push	eax
mov	eax,	ebp
sub	eax,	12
push	eax
mov	eax,	ebp
sub	eax,	20
push	eax
call	f_add
add	esp,	12
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	28
mov	dword ptr [ eax ],	ebx
push	offset data:str8
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	20
push	eax
call	f_printC
add	esp,	4
push	dword ptr [ ebp -28 ]
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
push	offset data:str9
call	_printf
add	esp,	40
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc