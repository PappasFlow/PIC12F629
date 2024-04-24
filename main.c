#include "header.h"

char segMas1 = 0;
char flag = 0;
void __interrupt() ISR() { 
    if(GPIF && (RX==0) ){
        GPIF=0;
        IOC2 = 0;
        GIE=0;
        segMas1=1;
        flag = 1;
        
        //recieve();  //no aplica sobremuestreo
        recieve_os(); //aplica sobremuestreo
    }else if (T0IF) { 
         static char contador = 0;
         if(contador  >= TIME_TOIF){//entra cada 1 seg
             segMas1 = 1;
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
        if(segMas1 ==1 ){
             TX_frec();
             button();
             blink();
             one_minute();
             segMas1 = 0;
        }
        if(flag ==1 ){
            IOC2=1;
             GIE=1;
             flag = 0;
             segMas1=0;
        }
        loop ();
        
    }
}

