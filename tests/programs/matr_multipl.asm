include ..\..\include\start.inc

str0	db	78, 101, 103, 97, 116, 105, 118, 101, 32, 97, 110, 100, 32, 122, 101, 114, 111, 32, 118, 97, 108, 117, 101, 115, 39, 114, 101, 32, 102, 111, 114, 98, 105, 100, 100, 101, 110, 10, 0
str1	db	84, 111, 111, 32, 98, 105, 103, 32, 118, 97, 108, 117, 101, 115, 10, 0
str2	db	37, 102, 0
str3	db	82, 101, 115, 117, 108, 116, 58, 10, 0
str4	db	37, 102, 32, 0
str5	db	10, 0
str6	db	109, 97, 116, 114, 105, 120, 32, 49, 44, 32, 114, 111, 119, 115, 32, 97, 110, 100, 32, 99, 111, 108, 117, 109, 110, 115, 58, 10, 0
str7	db	37, 105, 37, 105, 0
str8	db	109, 97, 116, 114, 105, 120, 32, 50, 44, 32, 114, 111, 119, 115, 32, 97, 110, 100, 32, 99, 111, 108, 117, 109, 110, 115, 58, 10, 0
str9	db	37, 105, 37, 105, 0
str10	db	67, 97, 110, 110, 111, 116, 32, 109, 117, 108, 116, 105, 112, 108, 121, 44, 32, 119, 114, 111, 110, 103, 32, 100, 97, 116, 97, 10, 0
str11	db	69, 110, 116, 101, 114, 32, 109, 97, 116, 114, 105, 120, 32, 65, 58, 10, 0
str12	db	69, 110, 116, 101, 114, 32, 109, 97, 116, 114, 105, 120, 32, 66, 58, 10, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_data_ok	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
xor	ebx,	ebx
xor	edx,	edx
cmp	eax,	ebx
jg	label2
mov	edx,	1
label2:
mov	eax,	edx
mov	edx,	1
test	eax,	eax
jne	label1
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
xor	ebx,	ebx
xor	edx,	edx
cmp	eax,	ebx
jg	label3
mov	edx,	1
label3:
mov	eax,	edx
test	eax,	eax
jne	label1
xor	edx,	edx
label1:
mov	eax,	edx
test	eax,	eax
jz	label0
push	offset data:str0
call	_printf
add	esp,	4
xor	eax,	eax
jmp	return_data_ok
label0:
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jng	label6
mov	edx,	1
label6:
mov	eax,	edx
mov	edx,	1
test	eax,	eax
jne	label5
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jng	label7
mov	edx,	1
label7:
mov	eax,	edx
test	eax,	eax
jne	label5
xor	edx,	edx
label5:
mov	eax,	edx
test	eax,	eax
jz	label4
push	offset data:str1
call	_printf
add	esp,	4
xor	eax,	eax
jmp	return_data_ok
label4:
mov	eax,	1
jmp	return_data_ok
xor	eax,	eax
return_data_ok:
pop	ebp
ret	
f_data_ok	endp






f_enter_matrix	proc
push	ebp
mov	ebp,	esp
push	0
jmp	label8
label9:
push	0
jmp	label10
label11:
push	0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
push	eax
push	offset data:str2
call	_scanf
add	esp,	8
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label10:
push	dword ptr [ ebp -8 ]
mov	eax,	ebp
add	eax,	8
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label12
mov	edx,	1
label12:
mov	eax,	edx
test	eax,	eax
jnz	label11
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label8:
push	dword ptr [ ebp -4 ]
mov	eax,	ebp
add	eax,	12
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label13
mov	edx,	1
label13:
mov	eax,	edx
test	eax,	eax
jnz	label9
add	esp,	4
xor	eax,	eax
return_enter_matrix:
pop	ebp
ret	
f_enter_matrix	endp






f_output	proc
push	ebp
mov	ebp,	esp
push	0
push	offset data:str3
call	_printf
add	esp,	4
jmp	label14
label15:
push	0
jmp	label16
label17:
push	0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
fld	dword ptr [ esp ]
sub	esp,	4
fstp	qword ptr [ esp ]
push	offset data:str4
call	_printf
add	esp,	12
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label16:
push	dword ptr [ ebp -8 ]
mov	eax,	ebp
add	eax,	8
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label18
mov	edx,	1
label18:
mov	eax,	edx
test	eax,	eax
jnz	label17
push	offset data:str5
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label14:
push	dword ptr [ ebp -4 ]
mov	eax,	ebp
add	eax,	12
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label19
mov	edx,	1
label19:
mov	eax,	edx
test	eax,	eax
jnz	label15
add	esp,	4
xor	eax,	eax
return_output:
pop	ebp
ret	
f_output	endp






f_multiply	proc
push	ebp
mov	ebp,	esp
push	0
jmp	label20
label21:
push	0
jmp	label22
label23:
push	0
push	0
fild	dword ptr [ esp ]
fstp	dword ptr [ esp ]
push	0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
jmp	label24
label25:
push	0
mov	eax,	dword ptr [ ebp -12 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	36
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	dword ptr [ ebp -12 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	32
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
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
fld	dword ptr [ eax ]
fld	dword ptr [ esp ]
faddp	st(1),	st(0)
fst	dword ptr [ eax ]
fstp	dword ptr [ esp ]
add	esp,	4
mov	eax,	ebp
sub	eax,	12
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label24:
push	dword ptr [ ebp -12 ]
mov	eax,	ebp
add	eax,	20
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label26
mov	edx,	1
label26:
mov	eax,	edx
test	eax,	eax
jnz	label25
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label22:
push	dword ptr [ ebp -8 ]
mov	eax,	ebp
add	eax,	24
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label27
mov	edx,	1
label27:
mov	eax,	edx
test	eax,	eax
jnz	label23
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label20:
push	dword ptr [ ebp -4 ]
mov	eax,	ebp
add	eax,	28
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label28
mov	edx,	1
label28:
mov	eax,	edx
test	eax,	eax
jnz	label21
mov	eax,	ebp
add	eax,	28
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
add	eax,	24
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
xor	eax,	eax
return_multiply:
pop	ebp
ret	
f_multiply	endp






f_main	proc
push	ebp
mov	ebp,	esp
push	0
push	0
push	0
push	0
push	0
push	0
sub	esp,	1200
push	offset data:str6
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	8
push	eax
mov	eax,	ebp
sub	eax,	4
push	eax
push	offset data:str7
call	_scanf
add	esp,	12
push	dword ptr [ ebp -4 ]
push	dword ptr [ ebp -8 ]
call	f_data_ok
add	esp,	8
test	eax,	eax
jz	label29
push	offset data:str8
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	16
push	eax
mov	eax,	ebp
sub	eax,	12
push	eax
push	offset data:str9
call	_scanf
add	esp,	12
push	dword ptr [ ebp -12 ]
push	dword ptr [ ebp -16 ]
call	f_data_ok
add	esp,	8
test	eax,	eax
jz	label30
push	dword ptr [ ebp -8 ]
mov	ebx,	dword ptr [ ebp -12 ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
je	label32
mov	edx,	1
label32:
mov	eax,	edx
test	eax,	eax
jz	label31
push	offset data:str10
call	_printf
add	esp,	4
xor	eax,	eax
add	esp,	1224
jmp	return_main
label31:
push	offset data:str11
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	28
push	eax
push	dword ptr [ ebp -4 ]
push	dword ptr [ ebp -8 ]
call	f_enter_matrix
add	esp,	12
push	offset data:str12
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	428
push	eax
push	dword ptr [ ebp -12 ]
push	dword ptr [ ebp -16 ]
call	f_enter_matrix
add	esp,	12
mov	eax,	ebp
sub	eax,	28
push	eax
mov	eax,	ebp
sub	eax,	428
push	eax
push	dword ptr [ ebp -4 ]
push	dword ptr [ ebp -16 ]
push	dword ptr [ ebp -8 ]
mov	eax,	ebp
sub	eax,	828
push	eax
mov	eax,	ebp
sub	eax,	20
push	eax
mov	eax,	ebp
sub	eax,	24
push	eax
call	f_multiply
add	esp,	32
mov	eax,	ebp
sub	eax,	828
push	eax
push	dword ptr [ ebp -20 ]
push	dword ptr [ ebp -24 ]
call	f_output
add	esp,	12
label30:
label29:
add	esp,	1224
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc