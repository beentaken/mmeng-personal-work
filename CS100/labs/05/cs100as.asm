; CS 100 Assignment 5
; Due Date: Friday 10/24/2008 @ 12:00 noon
; Student Name:	Marcus Meng
; Student ID#: 
; Section: 
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

start         
 NOP		

END
