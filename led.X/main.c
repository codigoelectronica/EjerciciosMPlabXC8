/**
 * Ejemplo de blink usando mplabx y xc8
 * @author Oscar Fernandez @OscarDevOps
 */
#include "config.h"
#include <xc.h>
#include <PIC16f877A.h>

#define _XTAL_FREQ 4000000

void main(void) {
    TRISB = 0;
    while(1){
        PORTBbits.RB0 = 1;
        __delay_ms(1000);
        PORTBbits.RB0 = 0;
        __delay_ms(1000);
    }
}