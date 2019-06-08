/*
 * File:   main.c
 * Author: ce
 *
 * Created on May 22, 2019, 7:59 PM
 */

#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 4000000

void main(void) {
    
    TRISB = 0;
    TRISD = 1;
    
    RB0 = 0;
    
    while(1){
        RB0 = RD0;
        
        /*if(RD0 == 1) {
            RB0 = 1;
        } else {
            RB0 = 0;
        }*/
    }
}
