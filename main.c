//*
 * File:   PIC12F629_TDII.c
 * Author: joaquin and juan 
 *
 * Created on 9 de abril de 2024, 12:40
 */
#include "header.h"
#define _XTAL_FREQ 4000000
char contador =0;
char frec=0;
void __interrupt() ISR() {
    if (T0IF) { // Verificar si la interrupción es causada por Timer1
        static char toogle =0;
        contador +=1;
        if(contador == frec){
        toogle= !toogle;
        GPIO5 =(__bit)toogle;
        contador=0;
        }else if(frec==0){
             GPIO5 =0;
             contador=0;
        }
         T0IF = 0;
    }
}
void main(void) {
    init();
    
    while(1){
         //ESTRUCTURA MAQUINA ESTADOSsss
        switch (state){
            case ESPERA:
                digitalwrite(RX,HIGH);
                frec=0;
                break;
            case F1K:
                digitalwrite(RX,LOW);
                frec=16;
               
                break;
            case F2K:
                frec=8;
                
                break;
            case F4K:
                frec=4;
                
                break;
            case F8K:
                frec=2;
               
                break;
            case F16K:
                frec=1;
              
                break;
            default: state=ESPERA;
        }
        //estas sentancias se ejecutan siempre en el bucle
        button();
        blink();  
        one_minute();
    } //fin superbucle   
}
