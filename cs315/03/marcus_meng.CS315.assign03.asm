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
            
            pushad
            invoke  crt_printf,addr PrintNumber, EAX      ; printf()
            popad

            push    16 ; Space for return value.
            push    EAX ; Parameter for function call.
            call    SQRT
            pop     EDX ; Return value

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

SQRT        PROC NEAR
            SQRT_RET EQU 12[EBP]
            SQRT_ARG EQU 8[EBP]

            ; Save registers
            push EBP
            mov EBP, ESP
            push EAX
            push EDX
            push ECX

            mov EAX, SQRT_ARG ; Get first argument
            
            mov     EDX, 0  ; Iterations
            mov     ECX, 1  ; Partial square root counter
root:
            sub     EAX, ECX ; Subtract current odd number from value EAX -= ECX
            inc     EDX      ; increment counter ++EDX
            add     ECX, 2   ; Next odd number ECX += 2

            cmp     ECX, EAX ; Compare odd value to current value
            jbe     root ; Jump if ECX <= EAX

            mov SQRT_RET, EDX ; Put return value on to stack.
            ; Restore registers
            pop ECX
            pop EDX
            pop EAX
            pop EBP

            ret 4
SQRT        ENDP
            
end         start