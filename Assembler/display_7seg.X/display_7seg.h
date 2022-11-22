/* 
 * File:   disply_7seg.h
 * Author: Luis Diaz
 *
 * Created on 28 de octubre de 2022, 08:02 PM
 */

#ifndef DISPLY_7SEG_H
#define	DISPLY_7SEG_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
    
typedef uint8_t char7seg;


void print_7seg(uint8_t port, char7seg caracter);



#ifdef	__cplusplus
}
#endif

#endif	/* DISPLY_7SEG_H */

