#include "header.h"


void __interrupt() ISR() { 
    if (T0IF) { 
         static char contador = 0;
         blink();
         if(contador  >= 16){//entra cada 1 seg
             TX_frec();
             contador=0;
             button();  
             one_minute();
         } else 
             contador++;
         TMR0 = 0;
         T0IF=0;
    }
    
}

void main(void) {
    init();
    while(1){
         switch(state) {
            case ESPERA:
                BUZZ = 0;
                break;
            case F1K:
                BUZZ ^= 1;
                __delay_us(TIME_FREC*16);
                break;
            case F2K:
                BUZZ ^= 1;
                __delay_us(TIME_FREC*8);
            break;
            case F4K:
                BUZZ ^= 1;
                __delay_us(TIME_FREC*4);
               break;
            case F8K:
                BUZZ ^= 1;
                __delay_us(TIME_FREC*2);
                break;
             case F16K:
                BUZZ ^= 1;
                __delay_us(TIME_FREC);
                break;
             default:state=ESPERA;}
    } //fin superbucle  
    
}
