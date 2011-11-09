 .386
.model flat,stdcall
option casemap:none

;include     \masm32\include\masm32rt.inc
;include     \masm32\macros\macros.asm

include     \masm32\include\msvcrt.inc
includelib  \masm32\lib\msvcrt.lib

.data                                                   ; data segment

Str1Len        dd 0
Str2Len        dd 0
String1      db "This is a string.", 0
String2      db "This is a not a string.", 0
PrintNumber   db     'String length=%u', 10, 0

NotEqualMessage db "Strings are not equal.", 10, 0
EqualMessage db "Strings are equal.", 10, 0

.code                                                   ; code segment

start:

            mov     EBX, 0  ; Load index 0
            ;mov     ESI, offset ElementList
begin:
            ;mov     EAX, [ESI] ; Load current number to square root

            lea EDI, String1
            call MYSTRLEN
            mov Str1Len, EBX

            lea EDI, String2
            call MYSTRLEN
            mov Str2Len, EBX
            
            pushad
            invoke  crt_printf,addr PrintNumber, Str1Len      ; printf()
            popad

            pushad
            invoke crt_printf, addr PrintNumber, Str2Len
            popad

            lea ESI, String1
            lea EDI, String2

            ; Now, load shorter length of the two string.
            mov EAX, Str1Len
            mov ECX, Str2Len
            cmp EAX, ECX

            call LOADSHORTER
            
            call MYSTRCMP

            ; Test equals: compare a string to itself, always equal
            lea ESI, String1
            lea EDI, String1

            mov ECX, Str1Len
            call MYSTRCMP

            pushad
            invoke  crt__getch                          ; getch()
            popad
            
            nop

            ret

LOADSHORTER PROC NEAR
; Loads the smaller value of EAX and ECX into ECX.
            cmp EAX, ECX
            ja INORDER ; In order
            xchg EAX, ECX
 INORDER:
            ret
LOADSHORTER ENDP

MYSTRLEN    PROC NEAR
            ; This proc returns the length in EBX.
            push EAX
            push ECX
            mov ECX, 0 ; Check no more than 20 chars
            dec ECX
            mov EBX, EDI ; Store DI for length calc later.
            mov EAX, 0 ; We want to find the first 0
                      ; Searches string in DI
            REPNE scasb ; Sets DI to the location of the found value
            ;mov EBX, EDI ; Find out how far DI moved.
            inc ECX
            not ECX
            mov EBX, ECX
            pop ECX
            pop EAX
            ret
MYSTRLEN    ENDP

MYSTRCMP    PROC NEAR
            REPE cmpsb  ; Compare them!
            jne NOTEQUAL
            pushad
            invoke crt_printf, addr EqualMessage, 0
            popad
            ret
NOTEQUAL:
            pushad
            invoke crt_printf, addr NotEqualMessage, 0
            popad
            ret
MYSTRCMP    ENDP
            
end         start