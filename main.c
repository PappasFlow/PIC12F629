/*
 * File:   PIC12F629_TDII.c
 * Author: joaqu
 *
 * Created on 9 de abril de 2024, 12:40
 */


#include "header.h"

void main(void) {
     
    pinmode(2,"OUPUT");
    pinmode(1,"OUPUT");
    pinmode(3,"INPUT");
    
     digitalwrite(2, 1 );
     while(1){
        digitalwrite(1, digitalread(3) );
     }
}



