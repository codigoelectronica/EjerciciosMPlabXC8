/*
 * File:   main.c
 * Author: ce
 *
 * Created on May 25, 2019, 10:07 AM
 */

#include "config.h"
#include <xc.h>

#define _XTAL_FREQ 4000000

void main(void) {
    TRISD = 0;
    
    unsigned char digits[] = {
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4F, // 3
        0x66, // 4
        0x6D, // 5
        0x7D, // 6
        0x07, // 7
        0x7F, // 8
        0x6F, // 9
    };
    while(1) {
        for(int i = 0; i <= 9; i++) {
            PORTD = ~digits[i];
            __delay_ms(1000);
        }
    }
    
}