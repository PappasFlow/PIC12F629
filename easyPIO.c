/*
 * File:   easyIO.c
 * Author: joaquin and juan 
 *
 * Created on 10 de abril de 2024, 17:45
*/

#include "header.h" 

void init (void){
    TRISIO = TRI;             
}

void digitalwrite (unsigned char pin,unsigned char est){
    static unsigned char gpio = 0; //variable que almacena estado 
    (est==0) ? (gpio = gpio & ~(1<<pin)) : (gpio = gpio | 1<<pin);
    GPIO=gpio;
}

char digitalread (unsigned char pin){
    return GPIO & 1<<pin;
}