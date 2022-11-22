/*
 * File:   main.c
 * Author: Luis Diaz
 *
 * Created on 25 de abril de 2022, 03:59 PM
 */

// Inicio bits de configuración
    #pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
    #pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
    #pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

    // CONFIG1H
    #pragma config FOSC = XTPLL_XT // Oscillator Selection bits (Internal oscillator, XT used by USB (INTXT))
    #pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
    #pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

    // CONFIG2L
    #pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
    #pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
    #pragma config BORV = 21        // Brown-out Reset Voltage bits (2.1V)
    #pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

    // CONFIG2H
    #pragma config WDT = OFF         // Watchdog Timer Enable bit (WDT enabled)
    #pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

    // CONFIG3H
    #pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
    #pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
    #pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

    // CONFIG4L
    #pragma config STVREN = OFF      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
    #pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
    #pragma config BBSIZ = BB1K     // Boot Block Size Select bit (1KW Boot block size)
    #pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

    // CONFIG5L
    #pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) or (001000-001FFFh) is not code-protected)
    #pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)

    // CONFIG5H
    #pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) or (000000-000FFFh) is not code-protected)

    // CONFIG6L
    #pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) or (001000-001FFFh) is not write-protected)
    #pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)

    // CONFIG6H
    #pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
    #pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) or (000000-000FFFh) is not write-protected)

    // CONFIG7L
    #pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) or (001000-001FFFh) is not protected from table reads executed in other blocks)
    #pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)

    // CONFIG7H
    #pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) or (000000-000FFFh) is not protected from table reads executed in other blocks)

// Fin bits de configuración


#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000

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


void main(void) {
    
    /*
     * Configura todos los pines como digitales I/O. */
    ADCON1bits.PCFG = 0b1111; 
    
    //uartInit(9600);
    
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 1;
    
    //Configuración del transmisor UART:
    TXSTA = 0b00100100;

    //Configuración del receptor UART:
    RCSTA = 0b10010000;

    //Configuración del BAUDRATE: 
    BAUDCON = 0b00000000; 
    BAUDCONbits.BRG16 = 1;
    uint16_t baud_desaired = 9600;
    uint16_t baud_rate = (_XTAL_FREQ/(baud_desaired*4))-1;
    SPBRG = baud_rate & 0x00FF; //máscara
    SPBRGH = baud_rate >> 8; //corrimiento
    
    char * caract_1 = "H";
    char * caract_2 = "O";
    char * caract_3 = "L";
    char * caract_4 = "A";
    char * caract_5 = "\n";
    char * caract_6 = "\r";
    
    while(1){
          
        while(TXSTAbits.TRMT == 0);
        TXREG = *caract_1;
        
        while(TXSTAbits.TRMT == 0);
        TXREG = *caract_2;
        
        while(TXSTAbits.TRMT == 0);
        TXREG = *caract_3;
        
        while(TXSTAbits.TRMT == 0);
        TXREG = *caract_4;
        
        while(TXSTAbits.TRMT == 0);
        TXREG = *caract_5;
        
        while(TXSTAbits.TRMT == 0);
        TXREG = *caract_6;
        
        __delay_ms(200);
        
        char * mensaje = "Hola Mundo\n\r";
        
       // while(*mensaje){
       // while(TXSTAbits.TRMT == 0);
        //TXREG = *mensaje++;
    //}
        
    }
    
}
