

#include "config_2450.h"
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000

void uartConfig(uint16_t baud_desaired);
void uart_transmit(char *message);


void main(void) {
    
    /*
     * Configura todos los pines como digitales I/O. 
     */
    ADCON1bits.PCFG = 0b1111; 
    
    uartConfig(9600);
    
    
    while(1){
          
             
        char mensaje[] = "Hola Mundo\n\r";
        uart_transmit(mensaje);
        __delay_ms(500);
    }
    
}


void uartConfig(uint16_t baud_desaired){
    

    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 1;
    
    //Configuración del transmisor UART:
    TXSTA = 0b00100100;

    //Configuración del receptor UART:
    RCSTA = 0b10010000;

    //Configuración del BAUDRATE: 
    BAUDCON = 0b00000000; 
    BAUDCONbits.BRG16 = 1; 
    uint16_t baud_rate = (_XTAL_FREQ/(baud_desaired*4))-1;
    SPBRG = baud_rate & 0x00FF; //máscara
    SPBRGH = baud_rate >> 8; //corrimiento 
    
}

void uart_transmit(char *message){
    while(*message){
        
        /*Esta instrucción Pregunta siempre si el TSR está vacío
        * Si TRMT está en 1 inidca que el TSR está lleno
        * Si TRMT está en 0 inidca que el TSR está vacío
        */
        while(TXSTAbits.TRMT == 0);
        TXREG = *message++;
    }
}
