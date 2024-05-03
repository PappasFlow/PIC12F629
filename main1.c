#include "header.h"

char segMas1 = 0;
char flag = 0;
char sendFlag = 0;
void  __interrupt() ISR() { 
    if(GPIF && (RX==0) ){
        GPIF=0;
        IOC2 = 0;
        GIE=0;
        GIE=0;segMas1=1;
        flag = 1;
        
        //recieve();  //no aplica sobremuestreo
        recieve_os(); //aplica sobremuestreo
    }else if (T0IF) { 
         static char contador = 0;
         if(contador%4 == 0)
             sendFlag = 1;
         if(contador  >= TIME_TOIF){//entra cada 1 seg
             segMas1 = 1;
             GIE=0;
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
        if(sendFlag){
            static char cout=0;
            switch(cout){
                case 0:
            send('F');
            break;
                    case 1:
                        if(state!=5)
                            send('0');
                        else
                            send('1');
                        break;
                case 2:
                     switch(state) {
        case F1K:
            send('1');
            break;
        case F2K:
            send('2');
            break;
        case F4K:
            send('4');
            break;
        case F8K:
            send('8');
            break;
        case F16K:

            send('6');
            break;
        default:
            send('0');
    }
                    break;
            }
            if(cout<3)
                cout++;
            else
                cout=0;
            sendFlag=0;
        }
        if(segMas1 ==1 ){
             //TX_frec();
            //send('A');
             button();
             blink();
             one_minute();
             segMas1 = 0;
             GIE=1;
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

