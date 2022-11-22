    ; Fecha de creación: 23/09/2022
    ; Propietario: Luis Díaz
    ; Plataforma: PIC16F84A
    ; Descripición:
    ;		    Blink en el pin RB0
    ; Hardware: 
    ;		    PIC16F84A. LED contectado al Pin RB0
    ;		    Oscilador de cristal de 4MHz
    ;		    Alimentaciíon 5Vdc
    
   PROCESSOR 16F84A
	#include <xc.inc> 

; Bits de configuración
    
    CONFIG  FOSC = HS             ; Oscillator Selection bits (HS oscillator)
    CONFIG  WDTE = OFF            ; Watchdog Timer (WDT disabled)
    CONFIG  PWRTE = OFF           ; Power-up Timer Enable bit (Power-up Timer is disabled)
    CONFIG  CP = OFF              ; Code Protection bit (Code protection disabled)

; Declaración de variables
    cont1 EQU 0x4f
    cont2 EQU 0x0d
  
 
; MACROS:
 select_bank_1 macro
    bcf	    STATUS, 6
    bsf	    STATUS, 5
    endm
    
 select_bank_0 macro
    bcf	    STATUS, 6
    bcf	    STATUS, 5
    endm
    
 pin_conf_in macro r_tris, pin
    select_bank_1
    bsf	    r_tris, pin
    select_bank_0
    endm
 
 pin_conf_out macro r_tris, pin
    select_bank_1
    bsf	    r_tris, pin
    select_bank_0
    endm
 
psect udata_shr	; Almacenamiento de variables en la RAM, compartida entre bancos
			; 
var1:
    ds 1		; Variable var1 con 1 localidad en la RAM
    
var2:
    ds 2		; Variable var1 con 2 localidades en la RAM	
 
	
psect udata	; Almacenamiento de variables en la RAM, no compartida entre bancos

var3: 
    ds 1

psect udata_bank1   ; Almacenamiento de variables en la RAM, en un banco específico

var4:
    ds 1
	
 
 
; Declaración del sector de programa correspondiente a código
    psect code, delta = 2, abs
    org 0x00
    
; Configuración de los puertos GPIO
SETUP:
    bcf	    STATUS, 6
    bsf	    STATUS, 5	    ; Estoy en el banco 1 de memoria
    movlw   00011B
    movwf   TRISA	    ; Configuramos PORTA RA0 y RA1 como entradas
    movlw   00000000B
    movwf   TRISB	    ; Configuramos todo PORTB como salida
    bcf	    STATUS, 5	    ; Volví al banco 0 de memoria
    clrf    PORTA
    clrf    PORTB
    
; Programa Principal
    
BLINK:
    bsf	    PORTB, 0	; Colocando en 1 el pin 0 del PORTB
    call    DELAY	; Espero
    bcf	    PORTB, 0	; Colocando en 0 el pin 0 del PORTB
    call    DELAY	; Espero
    goto    BLINK	; Repito

DELAY:
    call C_CONT
    
DECREMENT: 
    decfsz  var4, 1  ; 1 - 1 = 0 -> cont1
    goto    DECREMENT  ; cuando cont1 - 1 = 0 entonces NOP: No Operation
    return
    
C_CONT:
    movlw   255
    movwf   var4
    movlw   255
    movwf   var1
    return

end