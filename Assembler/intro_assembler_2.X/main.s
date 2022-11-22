/*
 *Archivo: main.s
 *Fecha De creación: 25 feb 2022
 *Fecha de modificación: 25 - feb - 2022
 *Dispositivo: 

 *Descripción del programa: Este programa permite al microcontrolador hacer un blink en el pin RB0. 
     
 *Descripción del hardware: Un microcontrolador PIC16F84A Alimentado con 5 Vdc, al cual se conecta un 
     *led al pin RB0 en configuración. El circuito está simulado en el programa PROTEUS. 
*/
    
PROCESSOR 16F84A
#include<xc.inc>
    
    /*CONFIGURATION BITS*/
    ; CONFIG
    CONFIG  FOSC = XT             ; Oscillator Selection bits (XT oscillator)
    CONFIG  WDTE = OFF            ; Watchdog Timer (WDT disabled)
    CONFIG  PWRTE = OFF           ; Power-up Timer Enable bit (Power-up Timer is disabled)
    CONFIG  CP = OFF              ; Code Protection bit (Code protection disabled)
  

 PSECT code, delta = 2, abs
 
 ;Setup
 BEGIN: 
    bcf	    STATUS, 6
    bsf	    STATUS, 5   ; Cabia al banco 1 de memoria
    movlw   11B	    ; Mueve al registro w el valor 0b00000011
    movwf   TRISA	    ; Mueve al registro TRISA el valor 0b00000011
    movlw   000B	    ; Mueve al registro w el valor 0b00000000
    movwf   TRISB    ; Mueve al registro TRISB el valor 0b00000000
    bcf	    STATUS, 5   ; Cambia al banco 0 de memoria
    clrf    PORTA
    clrf    PORTB
  
    
    ;Programa Principal
 MAIN:
  read_1:
    btfss   PORTA, 0  ; Verifica si el pin RA0 está en 1
    goto    read_2
    bsf	    PORTA, 0
    call    SET_RB0    ; Salta a SET_RB0, cuando termine volverá a read_2
  read_2:
    btfss   PORTA, 0  ; Verifica si el pin RA1 está en 1
    goto    read_1
    bsf	    PORTA, 0
    call    SET_RB0
    goto    MAIN
    
 SET_RB0:
    btfsc   PORTB, 0
    goto    CLR_RB0
    bsf	    PORTB, 0
    return
    
 CLR_RB0:
    bcf	    PORTB, 0
    return
    

 
 


