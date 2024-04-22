#include "header.h"


void __interrupt() ISR() { 
    if(GPIF && (RX==0) ){
        //recieve();  //no aplica sobremuestreo
        recieve_os(); //aplica sobremuestreo
        GPIF=0;
    }
    if (T0IF) { 
         static char contador = 0;
         //blink();
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
    loop ();
}

void main(void) {
    init();
    while(1){
        loop ();
    } //fin superbucle     
}
