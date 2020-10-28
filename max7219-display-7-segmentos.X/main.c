#include <xc.h>
#include <PIC16f877A.h>
#include "config.h"
#define _XTAL_FREQ 20000000
#include "max7219.h"

void displayNumber( int number);

void main(void) {
    TRISB = 0;
    max7219_Config();

    max7219_Clear();
   
    for(int i = 0; i < 9999; i++) {
        displayNumber(i);
        __delay_ms(2000);
    }
    return;
}

void displayNumber( int number) {
    int result;
    int pos = 0 ;
    max7219_Clear();
    while ( number > 0 ) {
        result = number % 10 ; 
        number = number / 10 ;
        max7219_WriteDigito(pos++, result);
    }
}