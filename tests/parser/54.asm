include ..\..\include\start.inc

str1 db 37, 105, 0   ;%i
i dd 777
ii dq  55


include ..\..\include\code.inc

_main proc

call f_main
ret
_main endp



f_main proc

push i
push offset data:str1
call _printf
pop i
pop i
;pop i
;pop i





ret 
f_main endp

             

include ..\..\include\end.inc