include ..\..\include\start.inc

str0	db	101, 110, 116, 101, 114, 32, 49, 48, 32, 101, 108, 101, 109, 101, 110, 116, 115, 32, 116, 111, 32, 115, 111, 114, 116, 58, 10, 0
str1	db	37, 105, 0
str2	db	101, 110, 116, 101, 114, 32, 49, 48, 32, 101, 108, 101, 109, 101, 110, 116, 115, 32, 116, 111, 32, 115, 111, 114, 116, 58, 10, 0
str3	db	37, 105, 0
str4	db	83, 111, 114, 116, 101, 100, 58, 10, 0
str5	db	37, 105, 10, 0
str6	db	83, 111, 114, 116, 101, 100, 58, 10, 0
str7	db	37, 105, 10, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_enter	proc
push	ebp
mov	ebp,	esp
push	0
push	offset data:str0
call	_printf
add	esp,	4
jmp	label0
label1:
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
push	eax
push	offset data:str1
call	_scanf
add	esp,	8
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label0:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label2
mov	edx,	1
label2:
mov	eax,	edx
test	eax,	eax
jnz	label1
push	offset data:str2
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	4
xor	ebx,	ebx
mov	dword ptr [ eax ],	ebx
jmp	label3
label4:
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	40
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
push	eax
push	offset data:str3
call	_scanf
add	esp,	8
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label3:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label5
mov	edx,	1
label5:
mov	eax,	edx
test	eax,	eax
jnz	label4
add	esp,	4
xor	eax,	eax
return_enter:
pop	ebp
ret	
f_enter	endp






f_sort	proc
push	ebp
mov	ebp,	esp
push	0
jmp	label6
label7:
push	dword ptr [ ebp -4 ]
jmp	label8
label9:
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
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
jnl	label11
mov	edx,	1
label11:
mov	eax,	edx
test	eax,	eax
jz	label10
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
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
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
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
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
push	dword ptr [ ebp -12 ]
push	0
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label10:
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label8:
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label12
mov	edx,	1
label12:
mov	eax,	edx
test	eax,	eax
jnz	label9
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label6:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label13
mov	edx,	1
label13:
mov	eax,	edx
test	eax,	eax
jnz	label7
add	esp,	4
xor	eax,	eax
return_sort:
pop	ebp
ret	
f_sort	endp






f_SortStruct	proc
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
push	eax
call	f_sort
add	esp,	4
mov	eax,	40
xor	ebx,	ebx
add	eax,	ebx
push	eax
mov	eax,	ebp
add	eax,	8
mov	eax,	dword ptr [ eax ]
pop	ebx
sub	eax,	ebx
push	eax
call	f_sort
add	esp,	4
xor	eax,	eax
return_SortStruct:
pop	ebp
ret	
f_SortStruct	endp






f_print	proc
push	ebp
mov	ebp,	esp
push	0
push	offset data:str4
call	_printf
add	esp,	4
jmp	label14
label15:
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
push	offset data:str5
call	_printf
add	esp,	8
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label14:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label16
mov	edx,	1
label16:
mov	eax,	edx
test	eax,	eax
jnz	label15
push	offset data:str6
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	4
xor	ebx,	ebx
mov	dword ptr [ eax ],	ebx
jmp	label17
label18:
push	0
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	40
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
push	offset data:str7
call	_printf
add	esp,	8
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label17:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label19
mov	edx,	1
label19:
mov	eax,	edx
test	eax,	eax
jnz	label18
add	esp,	4
xor	eax,	eax
return_print:
pop	ebp
ret	
f_print	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	80
mov	eax,	ebp
sub	eax,	4
push	eax
call	f_enter
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
call	f_SortStruct
add	esp,	4
mov	eax,	ebp
sub	eax,	4
push	eax
call	f_print
add	esp,	84
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc