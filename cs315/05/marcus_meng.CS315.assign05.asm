 .386
.model flat,stdcall
option casemap:none

;include     \masm32\include\masm32rt.inc
;include     \masm32\macros\macros.asm

include     \masm32\include\msvcrt.inc
includelib  \masm32\lib\msvcrt.lib

.data                                                   ; data segment

NumberArray    dd  9, 1, 1618, 88, 25, 5340, 23, 7540, 46709394, 425
PrintNumber   db     '%u ', 0

.code                                                   ; code segment

start:

begin:
            call PRINTARRAY

; Sort setup begins here
pushad
            lea EDX, offset NumberArray
            mov ECX, [EDX] ; Load number of items into ECX
            dec ECX ; 8 iterations for 9 items!

            add EDX, 4 ; First item.
bubble_sort:
            
            xor EBX, EBX ; Zero out EBX
sort_iteration:
            
            mov EAX, DWORD PTR [EDX+EBX*4+4]    ; Successor item
            cmp DWORD PTR [edx+EBX*4], eax      ; Compare current to successor
            jb dont_swap ; If we're already in order...
            ; else
            xchg eax, DWORD PTR [EDX+EBX*4]     ; Swap current with successor (eax) intermediate
            mov DWORD ptr [EDX+EBX*4+4], eax    ; Plug successor (eax) into current.
        dont_swap:
            inc EBX
            cmp EBX, ECX ; After each round, we the largest items are shoved to the back
                         ; tl;dr: no need to sort up the whole array every round.
            jb sort_iteration
            loop bubble_sort
popad
; Done with sort
            call PRINTARRAY

            pushad
            invoke  crt__getch                          ; getch()
            popad
            
            nop

            ret

PRINTARRAY  PROC NEAR
            pushad
            lea EDX, offset NumberArray
            mov ECX, [EDX]

            add EDX, 4 ; Step to first item.

print_element:            
            mov EBX, [EDX] ; Load number to print
            
            pushad
            invoke crt_printf, addr PrintNumber, EBX
            popad
            
            add EDX, 4 ; Step to next item
            
            loop print_element

            pushad
            invoke crt__putch, 10 ; Put a newline in
            popad
            
            popad
            ret
PRINTARRAY  ENDP
            
end         start