#include "header.h"


union CharBits {
    char byte;
    struct {
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    };
};
union CharBits datosend;
union CharBits dato;

void send(char ch){
    datosend.byte = ch;
     TX =LOW;
     __delay_us(BAUDIOS);
     TX  =(__bit)datosend.bit0;
     __delay_us(BAUDIOS);
     TX =(__bit)datosend.bit1;
     __delay_us(BAUDIOS);
     TX  =(__bit)datosend.bit2;
     __delay_us(BAUDIOS);
     TX  =(__bit)datosend.bit3;
     __delay_us(BAUDIOS);
     TX =(__bit)datosend.bit4;
     __delay_us(BAUDIOS);
     TX  =(__bit)datosend.bit5;
     __delay_us(BAUDIOS);
     TX  =(__bit)datosend.bit6;
     __delay_us(BAUDIOS);
     TX =(__bit)datosend.bit7;
     __delay_us(BAUDIOS);
     TX  =HIGH;
}

void recieve(void){
    __delay_us(BAUDIOS);
    dato.bit0= RX;
    __delay_us(BAUDIOS);
    dato.bit1= RX;
    __delay_us(BAUDIOS);
    dato.bit2= RX;
    __delay_us(BAUDIOS);
    dato.bit3= RX;
    __delay_us(BAUDIOS);
    dato.bit4= RX;
    __delay_us(BAUDIOS);
    dato.bit5= RX;
    __delay_us(BAUDIOS);
    dato.bit6= RX;
    __delay_us(BAUDIOS);
    dato.bit7= RX;
    if(dato.byte == 'c')  // Tecla de escape
        state = ESPERA;
        

}


void TX_frec(void){
    send('F');
    send('=');
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
            send('1');
            send('6');
            break;
        default:
            send('0');
    }
    send('K');
    send('H');
    send('z');
    send(13);//enter
}