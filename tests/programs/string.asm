include ..\..\include\start.inc

str0	db	37, 99, 0
str1	db	37, 99, 0
str2	db	69, 110, 116, 101, 114, 32, 116, 104, 101, 32, 102, 105, 114, 115, 116, 32, 115, 116, 114, 105, 110, 103, 58, 10, 0
str3	db	69, 110, 116, 101, 114, 32, 116, 104, 101, 32, 115, 101, 99, 111, 110, 100, 32, 115, 116, 114, 105, 110, 103, 58, 10, 0
str4	db	84, 104, 101, 32, 99, 111, 110, 99, 97, 116, 101, 110, 97, 116, 105, 111, 110, 32, 0
str5	db	32, 105, 115, 32, 115, 101, 108, 102, 32, 109, 105, 114, 114, 111, 114, 101, 100, 10, 0
str6	db	32, 105, 115, 32, 110, 111, 116, 32, 115, 101, 108, 102, 32, 109, 105, 114, 114, 111, 114, 101, 100, 10, 0
str7	db	69, 110, 116, 101, 114, 32, 101, 100, 103, 101, 115, 32, 102, 111, 114, 32, 116, 104, 101, 32, 115, 117, 98, 115, 116, 114, 105, 110, 103, 58, 0
str8	db	37, 105, 37, 105, 0
str9	db	69, 120, 116, 114, 97, 99, 116, 101, 100, 32, 115, 117, 98, 115, 116, 114, 105, 110, 103, 58, 32, 0
str10	db	66, 97, 100, 32, 101, 100, 103, 101, 115, 46, 46, 46, 10, 0


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
mov	eax,	dword ptr [ eax ]
xor	ebx,	ebx
xor	edx,	edx
cmp	eax,	ebx
jnl	label1
mov	edx,	1
label1:
mov	eax,	edx
test	eax,	eax
jz	label0
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
neg	eax
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






f_max	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	12
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	8
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jng	label3
mov	edx,	1
label3:
mov	eax,	edx
test	eax,	eax
jz	label2
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
jmp	return_max
label2:
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
jmp	return_max
xor	eax,	eax
return_max:
pop	ebp
ret	
f_max	endp






f_min	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	12
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	8
mov	ebx,	dword ptr [ eax ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label5
mov	edx,	1
label5:
mov	eax,	edx
test	eax,	eax
jz	label4
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
jmp	return_min
label4:
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
jmp	return_min
xor	eax,	eax
return_min:
pop	ebp
ret	
f_min	endp






f_scans	proc
push	ebp
mov	ebp,	esp
push	0
push	0
jmp	label6
label7:
mov	eax,	ebp
sub	eax,	4
push	eax
push	offset data:str0
call	_scanf
add	esp,	8
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jne	label10
mov	edx,	1
label10:
mov	eax,	edx
test	eax,	eax
jz	label9
jmp	label8
jmp	label11
label9:
push	dword ptr [ ebp -4 ]
push	0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
label11:
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label6:
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	50
xor	edx,	edx
cmp	eax,	ebx
jnl	label12
mov	edx,	1
label12:
mov	eax,	edx
test	eax,	eax
jnz	label7
label8:
push	dword ptr [ ebp -8 ]
mov	eax,	200
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
mov	eax,	dword ptr [ ebp -8 ]
add	esp,	8
jmp	return_scans
add	esp,	8
xor	eax,	eax
return_scans:
pop	ebp
ret	
f_scans	endp






f_prints	proc
push	ebp
mov	ebp,	esp
push	0
jmp	label13
label14:
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	offset data:str1
call	_printf
add	esp,	8
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label13:
push	dword ptr [ ebp -4 ]
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	eax
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label15
mov	edx,	1
label15:
mov	eax,	edx
test	eax,	eax
jnz	label14
add	esp,	4
xor	eax,	eax
return_prints:
pop	ebp
ret	
f_prints	endp






f_concat	proc
push	ebp
mov	ebp,	esp
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	0
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	eax
pop	eax
add	eax,	ebx
push	eax
mov	eax,	200
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
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	50
xor	edx,	edx
cmp	eax,	ebx
jng	label17
mov	edx,	1
label17:
mov	eax,	edx
test	eax,	eax
jz	label16
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	50
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
label16:
jmp	label18
label19:
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
xor	eax,	eax
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label18:
push	dword ptr [ ebp -4 ]
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	eax
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label20
mov	edx,	1
label20:
mov	eax,	edx
test	eax,	eax
jnz	label19
mov	eax,	ebp
sub	eax,	4
xor	ebx,	ebx
mov	dword ptr [ eax ],	ebx
jmp	label21
label22:
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	0
push	eax
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	ebx,	dword ptr [ ebp -4 ]
pop	eax
add	eax,	ebx
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label21:
push	dword ptr [ ebp -4 ]
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	eax
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label23
mov	edx,	1
label23:
mov	eax,	edx
test	eax,	eax
jnz	label22
add	esp,	4
xor	eax,	eax
return_concat:
pop	ebp
ret	
f_concat	endp






f_GetSubstring	proc
push	ebp
mov	ebp,	esp
mov	eax,	ebp
add	eax,	20
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	16
push	dword ptr [ eax ]
call	f_max
add	esp,	8
push	eax
mov	eax,	ebp
add	eax,	20
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	16
push	dword ptr [ eax ]
call	f_min
add	esp,	8
push	eax
push	dword ptr [ ebp -8 ]
mov	eax,	ebp
add	eax,	20
mov	eax,	dword ptr [ eax ]
xor	ebx,	ebx
xor	edx,	edx
cmp	eax,	ebx
jnl	label26
mov	edx,	1
label26:
mov	eax,	edx
mov	edx,	1
test	eax,	eax
jne	label25
mov	eax,	ebp
add	eax,	16
mov	eax,	dword ptr [ eax ]
xor	ebx,	ebx
xor	edx,	edx
cmp	eax,	ebx
jnl	label27
mov	edx,	1
label27:
mov	eax,	edx
test	eax,	eax
jne	label25
xor	edx,	edx
label25:
mov	eax,	edx
test	eax,	eax
jz	label24
xor	eax,	eax
add	esp,	12
jmp	return_GetSubstring
label24:
mov	eax,	ebp
add	eax,	20
push	dword ptr [ eax ]
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	eax
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jl	label30
mov	edx,	1
label30:
mov	eax,	edx
mov	edx,	1
test	eax,	eax
jne	label29
mov	eax,	ebp
add	eax,	16
push	dword ptr [ eax ]
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	12
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	eax
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jl	label31
mov	edx,	1
label31:
mov	eax,	edx
test	eax,	eax
jne	label29
xor	edx,	edx
label29:
mov	eax,	edx
test	eax,	eax
jz	label28
xor	eax,	eax
add	esp,	12
jmp	return_GetSubstring
label28:
mov	eax,	ebp
add	eax,	16
push	dword ptr [ eax ]
mov	eax,	ebp
add	eax,	20
mov	ebx,	dword ptr [ eax ]
pop	eax
sub	eax,	ebx
push	eax
call	f_abs
add	esp,	4
mov	ebx,	1
add	eax,	ebx
push	eax
mov	eax,	200
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
jmp	label32
label33:
push	0
mov	eax,	dword ptr [ ebp -12 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
push	0
push	dword ptr [ ebp -12 ]
mov	ebx,	dword ptr [ ebp -8 ]
pop	eax
sub	eax,	ebx
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
sub	eax,	12
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label32:
push	dword ptr [ ebp -12 ]
mov	ebx,	dword ptr [ ebp -4 ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jg	label34
mov	edx,	1
label34:
mov	eax,	edx
test	eax,	eax
jnz	label33
mov	eax,	1
add	esp,	12
jmp	return_GetSubstring
add	esp,	12
xor	eax,	eax
return_GetSubstring:
pop	ebp
ret	
f_GetSubstring	endp






f_SelfMirrored	proc
push	ebp
mov	ebp,	esp
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	2
xor	edx,	edx
div	ebx
push	eax
push	0
jmp	label35
label36:
push	0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	eax,	200
xor	ebx,	ebx
add	eax,	ebx
push	0
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
push	eax
mov	ebx,	dword ptr [ ebp -8 ]
pop	eax
sub	eax,	ebx
mov	ebx,	1
sub	eax,	ebx
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
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
pop	ebx
sub	eax,	ebx
mov	eax,	dword ptr [ eax ]
mov	ebx,	eax
pop	eax
xor	edx,	edx
cmp	eax,	ebx
je	label38
mov	edx,	1
label38:
mov	eax,	edx
test	eax,	eax
jz	label37
xor	eax,	eax
add	esp,	8
jmp	return_SelfMirrored
label37:
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label35:
push	dword ptr [ ebp -8 ]
mov	ebx,	dword ptr [ ebp -4 ]
pop	eax
xor	edx,	edx
cmp	eax,	ebx
jnl	label39
mov	edx,	1
label39:
mov	eax,	edx
test	eax,	eax
jnz	label36
mov	eax,	1
add	esp,	8
jmp	return_SelfMirrored
add	esp,	8
xor	eax,	eax
return_SelfMirrored:
pop	ebp
ret	
f_SelfMirrored	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	816
push	0
push	0
sub	esp,	204
push	offset data:str2
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
call	f_scans
add	esp,	4
push	offset data:str3
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	208
push	eax
call	f_scans
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
mov	eax,	ebp
sub	eax,	208
push	eax
mov	eax,	ebp
sub	eax,	412
push	eax
call	f_concat
add	esp,	12
push	offset data:str4
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	412
push	eax
call	f_prints
add	esp,	4
mov	eax,	ebp
sub	eax,	412
push	eax
call	f_SelfMirrored
add	esp,	4
test	eax,	eax
jz	label40
push	offset data:str5
call	_printf
add	esp,	4
jmp	label41
label40:
push	offset data:str6
call	_printf
add	esp,	4
label41:
push	offset data:str7
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	824
push	eax
mov	eax,	ebp
sub	eax,	820
push	eax
push	offset data:str8
call	_scanf
add	esp,	12
push	dword ptr [ ebp -820 ]
push	dword ptr [ ebp -824 ]
mov	eax,	ebp
sub	eax,	412
push	eax
mov	eax,	ebp
sub	eax,	828
push	eax
call	f_GetSubstring
add	esp,	16
test	eax,	eax
jz	label42
push	offset data:str9
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	828
push	eax
call	f_prints
add	esp,	4
jmp	label43
label42:
push	offset data:str10
call	_printf
add	esp,	4
label43:
add	esp,	1028
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc