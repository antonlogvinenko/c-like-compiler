.686
.model flat

includelib ..\..\lib\libc
includelib ..\..\lib\kernel32
EXTRN	_printf:NEAR
EXTRN	__fltused:NEAR
EXTRN	_scanf:NEAR

data  segment