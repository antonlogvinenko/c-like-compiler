include ..\..\include\start.inc

str0	db	37, 105, 32, 0
str1	db	83, 111, 114, 116, 101, 100, 58, 10, 0
str2	db	10, 0


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_print	proc
push	ebp
mov	ebp,	esp
push	0
jmp	label0
label1:
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
push	offset data:str0
call	_printf
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
add	esp,	4
xor	eax,	eax
return_print:
pop	ebp
ret	
f_print	endp






f_sort	proc
push	ebp
mov	ebp,	esp
push	0
jmp	label3
label4:
push	dword ptr [ ebp -4 ]
jmp	label5
label6:
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
jng	label8
mov	edx,	1
label8:
mov	eax,	edx
test	eax,	eax
jz	label7
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
label7:
mov	eax,	ebp
sub	eax,	8
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label5:
mov	eax,	dword ptr [ ebp -8 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label9
mov	edx,	1
label9:
mov	eax,	edx
test	eax,	eax
jnz	label6
mov	eax,	ebp
sub	eax,	4
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label3:
mov	eax,	dword ptr [ ebp -4 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label10
mov	edx,	1
label10:
mov	eax,	edx
test	eax,	eax
jnz	label4
add	esp,	4
xor	eax,	eax
return_sort:
pop	ebp
ret	
f_sort	endp






f_main	proc
push	ebp
mov	ebp,	esp
sub	esp,	800
push	0
jmp	label11
label12:
push	0
jmp	label13
label14:
push	100
push	dword ptr [ ebp -804 ]
mov	ebx,	dword ptr [ ebp -808 ]
pop	eax
imul	ebx
mov	ebx,	eax
pop	eax
sub	eax,	ebx
push	eax
push	0
mov	eax,	dword ptr [ ebp -808 ]
mov	ebx,	4
mul	ebx
pop	ebx
add	eax,	ebx
push	eax
mov	eax,	dword ptr [ ebp -804 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
pop	ebx
mov	dword ptr [ eax ],	ebx
mov	eax,	ebp
sub	eax,	808
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label13:
mov	eax,	dword ptr [ ebp -808 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label15
mov	edx,	1
label15:
mov	eax,	edx
test	eax,	eax
jnz	label14
mov	eax,	ebp
sub	eax,	804
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
add	esp,	4
label11:
mov	eax,	dword ptr [ ebp -804 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label16
mov	edx,	1
label16:
mov	eax,	edx
test	eax,	eax
jnz	label12
mov	eax,	ebp
sub	eax,	804
xor	ebx,	ebx
mov	dword ptr [ eax ],	ebx
jmp	label17
label18:
push	0
mov	eax,	dword ptr [ ebp -804 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
push	eax
call	f_sort
add	esp,	4
mov	eax,	ebp
sub	eax,	804
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label17:
mov	eax,	dword ptr [ ebp -804 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label19
mov	edx,	1
label19:
mov	eax,	edx
test	eax,	eax
jnz	label18
push	offset data:str1
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	804
xor	ebx,	ebx
mov	dword ptr [ eax ],	ebx
jmp	label20
label21:
push	0
mov	eax,	dword ptr [ ebp -804 ]
mov	ebx,	40
mul	ebx
pop	ebx
add	eax,	ebx
mov	ebx,	eax
mov	eax,	ebp
sub	eax,	4
sub	eax,	ebx
push	eax
call	f_print
add	esp,	4
push	offset data:str2
call	_printf
add	esp,	4
mov	eax,	ebp
sub	eax,	804
mov	ebx,	dword ptr [ eax ]
inc	ebx
mov	dword ptr [ eax ],	ebx
label20:
mov	eax,	dword ptr [ ebp -804 ]
mov	ebx,	10
xor	edx,	edx
cmp	eax,	ebx
jnl	label22
mov	edx,	1
label22:
mov	eax,	edx
test	eax,	eax
jnz	label21
add	esp,	804
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc