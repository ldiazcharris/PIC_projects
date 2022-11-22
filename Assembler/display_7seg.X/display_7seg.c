
#include "display_7seg.h"

static uint8_t ac_vector[] = {
    0b10000001, 0b11001111, 0b10010010, 0b10000110, 0b11001100, 0b10100100, 
    0b10100000, 0b10001111, 0b10000000, 0b10001100, 0b10001000, 0b11100000,
    0b10110001, 0b11000010, 0b10110000, 0b10111000, 0b11111010
};

static uint8_t error = 0b11111010;

static char7seg to_7seg(uint8_t hex)
{
    
    if (sizeof(ac_vector)/sizeof(ac_vector[0]) <= hex)
    {
        return error;
    }
    return ac_vector[hex];
}

void print_7seg(uint8_t port, uint8_t num)
{
    char7seg caracter = to_7seg(num);
    
    switch(port)
    {
        case 'A':
            PORTA = caracter;
            break;
        case 'B':
            PORTB = caracter;
            break;
        case 'C':
            PORTC = caracter;
            break;
        case 'D':
            //PORTD = caracter;
            break;
        case 'E':
            PORTE = caracter;
            break;
        default:
            PORTB = caracter;
    }
}