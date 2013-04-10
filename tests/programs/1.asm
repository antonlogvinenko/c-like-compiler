include ..\..\include\start.inc

;	STRING CONSTANTS:
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
;		-->> b
push	0
;		<<-- b
;		<<-- PUSHing local variables
;		-->> IF STATEMENT
;		-->> CONDITION
;		-->> b
push	dword ptr [ ebp -4 ]
;		<<-- b
;		<<-- CONDITION
pop	eax
test	eax,	eax
jz	label0
;		-->> TRUE BLOCK
;		-->> BLOCK STATEMENT
;		-->> PUSHing local variables
;		-->> x
push	0
;		<<-- x
;		<<-- PUSHing local variables
;		-->> RETURN
;		-->> 0
push	0
;		<<-- 0
pop	eax
add	esp,	8
jmp	return_main
;		<<-- RETURN
;		-->> POPing local variables
add	esp,	4
;		<<-- POPing local variables
;		<<-- BLOCK STATEMENT
;		<<-- TRUE BLOCK
label0:
;		<<-- IF STATEMENT
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