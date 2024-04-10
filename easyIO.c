/*
 * File:   easyIO.c
 * Author: joaquin
 *
 * Created on 10 de abril de 2024, 17:45
 */

#include "header.h"


unsigned char gpio = 0b00000000 ; //gobierna todo el pin out 
unsigned char trisio = 0b00000000 ; //gobierna todo el modo de pin out 

void digitalwrite (int pin,int est){
    TRISIO = trisio;
    if (est)
        gpio = gpio | 1<<pin; //or
    else
        gpio = gpio & ~(1<<pin);  //and
    GPIO=gpio;
}

int digitalread (int pin){
    TRISIO = trisio;
    return GPIO & 1<<pin;
}


void pinmode (int pin,char mod []){
    if (mod=="INPUT")
        trisio = trisio | 1<<pin; //or
    else
        trisio = trisio & ~(1<<pin);  //and
    
}