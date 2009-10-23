; CS 100 Assignment 5
; Due Date: Friday 10/24/2008 @ 12:00 noon
; Student Name:	Marcus Meng
; Student ID#: 80009207
; Section: A
; 
TITLE 		"CS 100 Assignment 5"
LIST		P=18F452
#include 	<p18f452.inc>
#include 	<cs100as5data.inc>	; DO NOT remove the data file included here
								; You might edit the file and choose your own numbers for testing

;--------------- DATA DEFINITION ---------------
CBLOCK 0x20
 NUM1:2
 NUM2:2
 RESULT:4
ENDC

; ****** RESET VECTOR SERVICE ROUTINE ******
ORG 0x00    ; Set program memory base at reset vector 0x00 
 GOTO start  ; Go to start of the main program

; ****** HIGH-PRIORITY INTERRUPT VECTOR SERVICE ROUTINE ******
ORG	0x08
 RETFIE

; ****** LOW-PRIORITY INTERRUPT VECTOR SERVICE ROUTINE ******
ORG	0x18
 RETFIE
 

; ****** MAIN PROGRAM SHOULD START AT ANY LOCATION FAR ENOUGH FROM BOTH INTERRUPT VECTORS ****** 
;         
ORG	0x040   ; Set program memory at any address beyond the needs of interrupt service routines  

; NOTES

; RESULT 	+1		+2	 	+3
; L*L:L		L*L:H	H*H:L	H*H:H
;			H*L:L	Carry	Carry
;					H*L:H	Carry
;			L*H:L	Carry	Carry
;					L*H:H	Carry

start         
 MOVLW num1_h ; Set up NUM1 to represent the full number.
 MOVWF NUM1+1
 MOVLW num1_l
 MOVWF NUM1

 MOVLW num2_h ; Set up NUM2 to represent the full number.
 MOVWF NUM2+1
 MOVLW num2_l
 MOVWF NUM2

 MOVF NUM1, W			; Multiply high bits and store into upper result.
 MULWF NUM2
 MOVFF PRODL, RESULT
 MOVFF PRODH, RESULT+1		

 MOVF NUM1+1, W			; Multiply low bits and store into lower registers.
 MULWF NUM2+1
 MOVFF PRODL, RESULT+2
 MOVFF PRODH, RESULT+3

 MOVF NUM1+1, W			; First take care of HxL * 10^8
 MULWF NUM2
 MOVF PRODL, W
 ADDWF RESULT+1, F		; Add to lower middle.
 MOVF PRODH, W
 ADDWFC RESULT+2, F		; Add to upper middle and take care of the carry.
 CLRF WREG
 ADDWFC RESULT+3, F		; Just in case upper add also carried.

 MOVF NUM1, W			; Now to deal with LxH * 10^8
 MULWF NUM2+1
 MOVF PRODL, W
 ADDWF RESULT+1, F		; Lower middle.
 MOVF PRODH, W
 ADDWFC RESULT+2, F		; Upper middle, with carry.
 CLRF WREG
 ADDWFC RESULT+3, F		; Fix carry.

END
