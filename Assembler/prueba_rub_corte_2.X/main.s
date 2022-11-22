

 PROCESSOR 16F84A
	#include <xc.inc> 

; Bits de configuración
    
    CONFIG  FOSC = HS             ; Oscillator Selection bits (HS oscillator)
    CONFIG  WDTE = OFF            ; Watchdog Timer (WDT disabled)
    CONFIG  PWRTE = OFF           ; Power-up Timer Enable bit (Power-up Timer is disabled)
    CONFIG  CP = OFF              ; Code Protection bit (Code protection disabled)
    
    #include <xc.inc> 
    
    cont1 EQU 0xc
    cont2 EQU 0xd
; Declaración del sector de programa correspondiente a código
    psect code, delta = 2, abs
    org 0x00
; Configuración de los puertos como entradas o salidas
 SETUP:
    BCF	    STATUS,6	;
    BSF	    STATUS,5	;ESTAMOS EN EL BANCO 1
    movlw   00010B	;B ES BINARIO
    movwf   TRISA	;CONFIGURACION DEL PORTA RA0 Y RA1 COMO ENTRADAS
    movlw   00000000B
    movwf   TRISB	;Configuramos todo PORTB como salida
    bcf     STATUS, 5	;ESTAMOS EN EL BANCO 0
    clrf    PORTA	; LIMPIAMOS EL PUERTO A COMPLETO
    clrf    PORTB	; LIMPIAMOS EL PUERTO A COMPLETO
    
; Programa Principal
APAGADO:
    bsf     PORTB, 1	;Colocando en 1 el pin RB0 del PORTB  
    call    RETARDO	;Espero
    bcf     PORTB, 1    ;Colocando en 0 el pin RB0 del PORTB
    bsf     PORTB, 2
    call    RETARDO
    bcf     PORTB, 2
    bsf     PORTB, 3
    call    RETARDO  
    bcf     PORTB, 3
    BTFSS   PORTA, 1
    goto    APAGADO   
    goto    ENCENDIDO
ENCENDIDO:
   bsf     PORTB, 3
   call    RETARDO
   bcf     PORTB, 3
   bsf     PORTB, 2
   call    RETARDO
   bcf     PORTB, 2
   bsf     PORTB, 1 
   call    RETARDO
   bcf     PORTB, 1
   BTFSS   PORTA, 1
   goto    ENCENDIDO 
   goto    APAGADO
RETARDO:
    movlw   255
    movwf   cont1
    movlw   255
    movwf   cont2
RETARDO_1: 
    decfsz  cont1, 1  
    goto    RETARDO_1 
    decfsz  cont2, 1  
    goto    RETARDO_1 
    return
end