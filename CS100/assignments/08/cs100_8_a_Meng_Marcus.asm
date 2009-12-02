#include <p18f452.inc>

	CBLOCK 0x20
		iterator
		previous
	ENDC

	ORG 0X00
	GOTO start

	ORG 0X08
	RETFIE

	ORG 0X18
	RETFIE

	ORG 0X40
start:
	LFSR FSR0, 0x100	; Load bank 1.
	MOVLW 0
	MOVWF iterator
	MOVWF previous

SET_BANK:
	; Add the previous value to the iterator,
	; store in working register.
	MOVFF previous, W
	ADDWF iterator, W

	; Stick the new value into the current bank
	; address and increment our FSR0 pointer.
	MOVFF W, POSTINC0

	; Increment the iterator.
	INCF iterator
	; Store the previous value.
	MOVWF previous
	
	; Should we keep looping? Stop once we're
	; done setting all 3 memory banks.
	BTFSS FSR0H, 2
		BRA SET_BANK

	END

