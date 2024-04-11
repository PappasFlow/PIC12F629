/*
 * File:   PIC12F629_TDII.c
 * Author: joaqu
 *
 * Created on 9 de abril de 2024, 12:40
 */
#include "header.h"

void main(void) {
    pioinit();
    
    while(1){
         //ESTRUCTURA MAQUINA ESTADOS
        switch (state){
            case ESPERA:
                digitalwrite(BUZZ,LOW);
                digitalwrite(RX,HIGH);
                break;
            case F1K:
                digitalwrite(RX,LOW);
                break;
            case F2K:
                break;
            case F4K:
                break;
            case F8K:
                break;
            case F16K:
                digitalwrite(BUZZ,HIGH);
                break;
            default: state=ESPERA;
        }
        //estas sentancias se ejecutan siempre en el bucle
        button();
        blink();  
        one_minute();
    } //fin superbucle   
}
