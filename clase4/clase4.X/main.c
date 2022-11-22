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
    #pragma config FOSC = INTOSC_XT // Oscillator Selection bits (Internal oscillator, XT used by USB (INTXT))
    #pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
    #pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

    // CONFIG2L
    #pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
    #pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
    #pragma config BORV = 21        // Brown-out Reset Voltage bits (2.1V)
    #pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

    // CONFIG2H
    #pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
    #pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

    // CONFIG3H
    #pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
    #pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
    #pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

    // CONFIG4L
    #pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
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
#define _XTAL_FREQ 40000000

void display7(uint8_t n){ 
    
    switch (n){
        case 0:
            LATB = 0b00111111;
                    //gfedcba
        case 1:
            LATB = 0b00000110; 
                    //gfedcba
        case 2:
            LATB = 0b01011011; 
                    //gfedcba
        case 3:
            LATB = 0b01001111; 
                    //gfedcba
        
    }
    
}

void main(void) {
    
    LATA = 0b00000000; 
    LATB = 0b00000000;
    ADCON1bits.PCFG = 0b1111; //Se puede usar 0x0f. Habilita todos los pines como Digital I/O
    TRISA = 0b00000011; //se configura RA0 como entrada y los demás pines como salida
    TRISB = 0b00000000;
    uint8_t cont = 0;
    while(1){
      if(PORTAbits.RA0 == 1){
        while(PORTAbits.RA0 == 1);
        __delay_ms(20);
        
        if(cont >= 0xf){ //15
            cont = 0x0;
        }else if(cont <= 0x0){
            cont = 0xf;
        }else{
            cont = cont++;
        }
        
       
        }else if(PORTAbits.RA0 == 0){
        while(PORTAbits.RA0 == 0);
        __delay_ms(20);
        
        display7(cont);

        }
    }
    
}
