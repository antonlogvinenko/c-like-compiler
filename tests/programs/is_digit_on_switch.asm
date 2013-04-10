include ..\..\include\start.inc

;	STRING CONSTANTS:
str0	db	101, 110, 116, 101, 114, 32, 97, 32, 100, 105, 103, 105, 116, 58, 10, 0
str1	db	37, 105, 0
str2	db	122, 101, 114, 111, 0
str3	db	111, 110, 101, 0
str4	db	116, 119, 111, 0
str5	db	116, 104, 114, 101, 101, 0
str6	db	102, 111, 117, 114, 0
str7	db	110, 111, 116, 32, 97, 32, 100, 105, 103, 105, 116, 10, 0
str8	db	102, 105, 118, 101, 0
str9	db	115, 105, 120, 0
str10	db	115, 101, 118, 101, 110, 0
str11	db	101, 105, 103, 104, 116, 0
str12	db	110, 105, 110, 101, 0
;	GLOBAL VARIABLES:


include ..\..\include\code.inc



_main	proc
call	f_main
ret	
_main	endp






f_main	proc
push	ebp
mov	ebp,	esp
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		-->> digit
;		-->> 0
push	0
;		<<-- 0
;		<<-- digit
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str0
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> call scanf()
mov	eax,	ebp
sub	eax,	4
push	eax
push	offset data:str1
call	_scanf
add	esp,	8
push	eax
;		<<-- call scanf()
;	...cleaning...
add	esp,	4
;		-->> switch expression
;		-->> digit
push	dword ptr [ ebp -4 ]
;		<<-- digit
;		<<-- switch expression
;		-->> switch conditions
;		-->> 0
push	0
;		<<-- 0
pop	eax
pop	ebx
cmp	eax,	ebx
je	label2
push	ebx
;		-->> 99
push	99
;		<<-- 99
pop	eax
pop	ebx
cmp	eax,	ebx
je	label3
push	ebx
;		-->> 1
push	1
;		<<-- 1
pop	eax
pop	ebx
cmp	eax,	ebx
je	label4
push	ebx
;		-->> 2
push	2
;		<<-- 2
pop	eax
pop	ebx
cmp	eax,	ebx
je	label5
push	ebx
;		-->> 3
push	3
;		<<-- 3
pop	eax
pop	ebx
cmp	eax,	ebx
je	label6
push	ebx
;		-->> 4
push	4
;		<<-- 4
pop	eax
pop	ebx
cmp	eax,	ebx
je	label7
push	ebx
;		-->> 5
push	5
;		<<-- 5
pop	eax
pop	ebx
cmp	eax,	ebx
je	label8
push	ebx
;		-->> 6
push	6
;		<<-- 6
pop	eax
pop	ebx
cmp	eax,	ebx
je	label9
push	ebx
;		-->> 7
push	7
;		<<-- 7
pop	eax
pop	ebx
cmp	eax,	ebx
je	label10
push	ebx
;		-->> 8
push	8
;		<<-- 8
pop	eax
pop	ebx
cmp	eax,	ebx
je	label11
push	ebx
;		-->> 9
push	9
;		<<-- 9
pop	eax
pop	ebx
cmp	eax,	ebx
je	label12
push	ebx
add	esp,	4
jmp	label1
;		<<-- switch conditions
;		<<-- switch bodies
label2:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str2
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label3:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str2
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label4:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str3
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label5:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str4
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label6:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str5
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label7:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str6
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label1:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str7
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label8:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str8
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label9:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str9
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label10:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str10
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label11:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str11
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
label12:
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		<<-- PUSHing local variables
;		-->> call printf()
push	offset data:str12
call	_printf
add	esp,	4
push	eax
;		<<-- call printf()
;	...cleaning...
add	esp,	4
;		-->> BREAK
add	esp,	0
jmp	label0
;		<<-- BREAK
;		-->> POPing local variables
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
;		<<-- switch bodies
;	for breaks
label0:
;		-->> POPing local variables
add	esp,	4
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
xor	eax,	eax
return_main:
pop	ebp
ret	
f_main	endp




include ..\..\include\end.inc