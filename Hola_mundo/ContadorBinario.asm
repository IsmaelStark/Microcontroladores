; PIC18F4550 Configuration Bit Settings

; Assembly source line config statements

#include "p18f4550.inc"

; CONFIG1L
  CONFIG  PLLDIV = 2            ; PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
  CONFIG  CPUDIV = OSC1_PLL2    ; System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
  CONFIG  USBDIV = 2            ; USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

; CONFIG1H
  CONFIG  FOSC = HSPLL_HS       ; Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

; CONFIG2L
  CONFIG  PWRT = OFF            ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  BOR = ON              ; Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
  CONFIG  BORV = 3              ; Brown-out Reset Voltage bits (Minimum setting 2.05V)
  CONFIG  VREGEN = OFF          ; USB Voltage Regulator Enable bit (USB voltage regulator disabled)

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = ON           ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
  CONFIG  PBADEN = ON           ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = ON              ; Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
  CONFIG  ICPRT = OFF           ; Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

    CBLOCK	0X00
      W_TEMP
      STATUS_TEMP
      BSR_TEMP
      
	d1
	d2
	d3

	CONTADOR
    ENDC

	ORG 0X00
	GOTO INICIO
	ORG 0X008
	GOTO BAJA_PRIORIDAD
	ORG 0X018
BAJA_PRIORIDAD
	MOVWF W_TEMP
	MOVFF STATUS,STATUS_TEMP
	MOVFF BSR,BSR_TEMP
	RETURN
FIN_INTER
	MOVWF W_TEMP
	MOVFF STATUS,STATUS_TEMP
	MOVFF BSR,BSR_TEMP
	RETURN
ALTA_PRIORIDAD
	GOTO FIN_INTER
	
INICIO
	CLRF PORTA ;  Initialize PORTA by
		; clearing output
		; data latches
	CLRF LATA ; Alternate method
		; to clear output
		; data latches
	MOVLW 0Fh ; Configure A/D 
	MOVWF ADCON1 ; for digital inputs
	MOVLW 07h ; Configure comparators
	MOVWF CMCON ; for digital input
	MOVLW b'11001111'; 0CFh ;b'11001111'  ;d'207' ; Value used to 
	; initialize data 
	; direction
	MOVWF  TRISA ;  Set RA<3:0> as inputs
	;  RA<5:4> as outputs


	CLRF PORTB
	CLRF LATB
	MOVLW 0h
	MOVWF  TRISB

	CLRF PORTD
	CLRF LATD
	MOVLW 0FFh
	MOVWF  TRISD
	
	MOVLW	.240
	MOVWF	CONTADOR
	
PRINCIPAL
	MOVF	CONTADOR,W	;CONTADOR A W
	MOVWF	LATB	    ;LO QUE HAY EN W A PORTB
	CALL	RETARDO_100MS
	INCF	CONTADOR,F  ;INCREMENTO EN 1 Y GUARDO
	BTFSS	STATUS,0
	GOTO	PRINCIPAL
	
	BSF PORTA,5
	CALL	RETARDO_100MS
	BCF PORTA,5
	
	
RETARDO_500MS
	;#INCLUDE <RETARDOS.INC>
	movlw	0x36
	movwf	d1
	movlw	0x15
	movwf	d2
	movlw	0x07; OX0E ORIGINAL, 0X07 100ms, 0X1F 500ms
	movwf	d3
Delay_0
	decfsz	d1, f
	goto	Delay_0
	decfsz	d2, f
	goto	Delay_0
	decfsz	d3, f
	goto	Delay_0
			;1 cycle
	nop
	RETURN
	
	
	
END