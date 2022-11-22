/*
 * File:   main.c
 * Author: Luis Diaz
 *
 * Created on 29 de agosto de 2022, 07:38 PM
 */
// PIC16F84A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdbool.h>
#define _XTAL_FREQ 4000000

void main(void) {
    TRISA = 0b00000011;
    TRISB = 0b00000000;
    PORTAbits.RA0 = 0;
    PORTBbits.RB0 = 0;
    int cont = 0;
    while (true) {
        if (PORTAbits.RA0 == 1) {
            cont = 1;
        }
        while (cont == 1) {
            PORTBbits.RB0 = 1;
            __delay_ms(100);
            PORTBbits.RB0 = 0;
            __delay_ms(100);
            if (PORTAbits.RA0 == 1) {
                cont = 0;
                PORTBbits.RB0 = 0;
                cont = 0;
                __delay_ms(200);
            }
            
        }
    }
}
