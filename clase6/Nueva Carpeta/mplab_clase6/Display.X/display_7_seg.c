
#include "display_7_seg.h"

static uint8_t error = 0b11111010;

uint8_t hex_to_7seg_ac(uint8_t hex)
{
    if(sizeof(ac_vector)/sizeof(ac_vector[0]) >= hex)
    {
        return error;
    }
    return ac_vector[hex];
}

void print_7seg(port_7seg port, uint8_t caracter)
{
    switch(port)
    {
        case "A":
            PORTA = caracter;
            break;
        case "B":
            PORTB = caracter;
            break;
        case "C":
            PORTC = caracter;
            break;
        case "D":
            PORTD = caracter;
            break;
        case "E":
            PORTE = caracter;
            break;
        default:
            PORTA = caracter;
            
    }
    
}
