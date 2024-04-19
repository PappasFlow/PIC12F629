/*
 * File:   PIC12F629_TDII.c
 * Author: joaquin and juan 
 *
 * Created on 9 de abril de 2024, 12:40
 */
#include "header.h"
void __interrupt() ISR() { 
     if (T0IF) { 
         static char contador = 0;
         if(contador  >= 16){
             one_Second();
             contador=0;
         } else 
             contador++;
         TMR0 = 0;
         T0IF=0;
    }
    
}

void main(void) {
    init();
    carga();
    while(1){
     if(state >= 5)
    state = 0;
    else
    state++;
     send();
     __delay_ms(500);
        /*
        switch(state) {
            case 0:
                GPIO5 = 0;
                break;
            case 1:
                GPIO4 ^= 1;
                __delay_us(500);
                break;
            case 2:
              GPIO4 ^= 1;
              __delay_us(250);
            break;
            case 3:
               GPIO4 ^= 1;
               __delay_us(128);
               break;
            case 4:
            GPIO4 ^= 1;
            __delay_us(64);
             break;
             case 5:
                GPIO4 ^= 1;
                __delay_us(32);
            break;
         }    */
    }
}