/*
 * File:   PIC12F629_TDII.c
 * Author: joaquin and juan 
 *
 * Created on 9 de abril de 2024, 12:40
 */
#include "header.h"
#define _XTAL_FREQ 4000000
void __interrupt() ISR() {  
}

void main(void) {
    init();
    
    while(1){
        controlBuzz();
        button();
        blink();  
        one_minute();
    } //fin superbucle   
}