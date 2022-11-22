/*
 * File:   newmain.c
 * Author: srivera10
 *
 * Created on 5 de septiembre de 2022, 19:04
 */
// PIC16F628A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include <stdbool.h>
#define  _XTAL_FREQ 4000000

void main(void) {

    TRISA = 0b00000011; // Para Configurar los pines del PORTA como I/O
    TRISB = 0b00000000;
    
    
    PORTAbits.RA0 = 0;
    PORTBbits.RB0 = 0;
    while (true) {

        if (PORTAbits.RA0 == 1) {
            __delay_ms(40);
            if (PORTAbits.RA0 == 1) {
                PORTBbits.RB0 = 1;
            }
        }

        if (PORTAbits.RA1 == 1) {
            __delay_ms(40);
            if (PORTAbits.RA1 == 1) {
                PORTBbits.RB0 = 0;
            }
        }
    }
}