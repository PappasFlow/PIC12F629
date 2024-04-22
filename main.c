#include "header.h"

char segMas1 = 0;
char flag = 0;
void __interrupt() ISR() { 
    if(GPIF && (RX==0) ){
        
        //recieve();  //no aplica sobremuestreo
        recieve_os(); //aplica sobremuestreo
        GPIF=0;
        IOC2 = 0;
        GIE=0;
        segMas1=1;
        //__delay_us(100);

        flag = 1;
    }
    if (T0IF) { 
         static char contador = 0;
         //blink();
         if(contador  >= 16){//entra cada 1 seg
             segMas1 = 1;
             contador=0;
         } else 
             contador++;
         TMR0 = 0;
         T0IF=0;
    }
    //loop ();
}

void main(void) {
    init();
    LED=1;
    while(1){
        if(segMas1 ==1 ){
             TX_frec();
             button();  
             one_minute();
             //blink();
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
