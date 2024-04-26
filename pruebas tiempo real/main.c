#include "header.h"


void __interrupt() ISR() { 
    if(GPIF && (RX==0) ){
        GPIF=0;
        IOC2 = 0;
        GIE=0;
        flag = 1;
    
        recieve_os(); //aplica sobremuestreo
    }else if (T0IF) { 
         static char contador = 0;
         if(contador  >= TIME_TOIF){//entra cada 1 seg
             flag = 2;
             contador=0;
         } else 
             contador++;
         TMR0 = 0;
         T0IF=0;
    }
}

void main(void) {
    init();
    while(1){

        if(flag ==1 ){
            IOC2=1;
            GIE=1;
            flag = 0;
        }else if(flag == 2){
             blink();
             button();
             one_minute();
             flag = 0;
             tx_flag=1;
        }
        
        loop ();
    }
}

