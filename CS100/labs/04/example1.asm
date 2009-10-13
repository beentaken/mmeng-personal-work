include <p18f452.inc>

CBLOCK 0x09
 num1
 num2
ENDC 

result EQU 0x0B

ORG 0x00
GOTO start

ORG 0x08
RETFIE

ORG 0x18
RETFIE

ORG 0x050 
start 
 MOVLW  0x5
 MOVWF  num1
 MOVLW  D'3'
 MOVWF  num2  
 MOVF  num1,W
 ADDWF  num2,W
 MOVWF  result
END