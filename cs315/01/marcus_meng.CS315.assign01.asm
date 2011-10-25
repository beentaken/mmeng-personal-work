 .386
.model flat,stdcall
option casemap:none

;include     \masm32\include\masm32rt.inc
;include     \masm32\macros\macros.asm

include     \masm32\include\msvcrt.inc
includelib  \masm32\lib\msvcrt.lib

.data                                                   ; data segment

MaxElements dd      13
PrintCount   db     'Count=%d ', 0
PrintElement db     'Element=%d', 10, 0
ElementList dd      18, 28, 30, 42, 54, 79, 93, 888, 1000, 2000, 5354, 8866

.code                                                   ; code segment

start:

            mov     EBX, 1  ; Load index 1
            mov     ESI, offset ElementList
begin:
            pushad
            invoke  crt_printf,addr PrintCount, EBX      ; printf()
            popad

            mov     EAX, [ESI]
            
            pushad
            invoke  crt_printf,addr PrintElement, EAX      ; printf()
            popad

            inc     EBX
            add     ESI, 4
            
            cmp     EBX, MaxElements
            jne     begin

            pushad
            invoke  crt__getch                          ; getch()
            popad
            
            nop

            ret
            
end         start