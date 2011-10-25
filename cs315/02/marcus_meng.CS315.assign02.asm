 .386
.model flat,stdcall
option casemap:none

;include     \masm32\include\masm32rt.inc
;include     \masm32\macros\macros.asm

include     \masm32\include\msvcrt.inc
includelib  \masm32\lib\msvcrt.lib

.data                                                   ; data segment

MaxElements dd      5
PrintNumber   db     'Number=%u ', 0
PrintRoot db     'Root=%u', 10, 0
ElementList DWORD      36, 169, 9801, 51984, 105625 ; roots: 6, 13, 99, 228, 325

.code                                                   ; code segment

start:

            mov     EBX, 0  ; Load index 0
            mov     ESI, offset ElementList
begin:
            mov     EAX, [ESI] ; Load current number to square root
            mov     EDX, 0  ; Iterations
            mov     ECX, 1  ; Partial square root counter
            pushad
            invoke  crt_printf,addr PrintNumber, EAX      ; printf()
            popad

root:
            sub     EAX, ECX ; Subtract current odd number from value EAX -= ECX
            inc     EDX      ; increment counter ++EDX
            add     ECX, 2   ; Next odd number ECX += 2

            cmp     ECX, EAX ; Compare odd value to current value
            jbe     root ; Jump if ECX <= EAX
            
            pushad
            invoke  crt_printf,addr PrintRoot, EDX      ; printf()
            popad

            inc     EBX ; Increment counter.
            add     ESI, 4 ; Increment ESI pointer by 4 bytes.
            
            cmp     EBX, MaxElements ; If EBX compared to MaxElements
            jne     begin ; Jump back to begin if not equal

            pushad
            invoke  crt__getch                          ; getch()
            popad
            
            nop

            ret
            
end         start