#include <p18f452.inc>

ORG 0X00
	GOTO start

ORG 0X08
	RETFIE

ORG 0X18
	RETFIE

ORG 0X20
start:
	CLRF LATC

	; Sets RB0 and RA4 for input and CCP1 for output
	BSF TRISB, RB0
	BSF TRISA, RA4
	BCF TRISC, 2
	
	MOVLW B'00000110'
	MOVWF T2CON
	
	MOVLW B'00001100'
	MOVWF CCP1CON

; Default loop
mainloop:
	CLRWDT ; No reset kkthxbye.
	
	BTFSS PORTB, RB0
	BRA rb0notset
	
	MOVLW .155
	MOVWF PR2
	
	BTFSS PORTA, RA4
	BRA ra4notset
	
	MOVLW .16
	MOVWF CCPR1L
	BSF CCP1CON, 5
	BCF CCP1CON, 4
	BRA mainloop
; Set high frequency.
rb0notset:
	MOVLW .255
	MOVWF PR2
	
	BTFSS PORTA, RA4
	BRA ra4notset
	
	MOVLW .16
	MOVWF CCPR1L
	BSF CCP1CON, 5
	BCF CCP1CON, 4
	
	BRA mainloop
; Set large pulse width.
ra4notset:
	MOVLW .31
	MOVWF CCPR1L
	BCF CCP1CON, 5
	BSF CCP1CON, 4
	BRA mainloop
END