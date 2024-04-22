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



void send(char ch){
    union CharBits datosend;
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


void recieve(void){           //sin sobremuestreo
    union CharBits dato;
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
    if(dato.byte == 'x') //tecla de escape
        state = ESPERA;
}



void recieve_os(void){                    //con sobremuestreo
    union CharBits dato0,dato1,dato2;
    
    __delay_us(BAUDIOS_R);
    dato0.bit0= RX;
    __delay_us(10);
     dato1.bit0= RX;
    __delay_us(10);
     dato2.bit0= RX;
     
    __delay_us(BAUDIOS_R - 20);
    dato0.bit1= RX;
    __delay_us(10);
     dato1.bit1= RX;
    __delay_us(10);
     dato2.bit1= RX;
    
    __delay_us(BAUDIOS_R - 20);
    dato0.bit2= RX;
    __delay_us(10);
     dato1.bit2= RX;
    __delay_us(10);
     dato2.bit2= RX;
     
    __delay_us(BAUDIOS_R - 20);
    dato0.bit3= RX;
    __delay_us(10);
     dato1.bit3= RX;
    __delay_us(10);
     dato2.bit3= RX;
     
    __delay_us(BAUDIOS_R - 20);
    dato0.bit4= RX;
    __delay_us(10);
     dato1.bit4= RX;
    __delay_us(10);
     dato2.bit4= RX;
             
    __delay_us(BAUDIOS_R - 20);
    dato0.bit5= RX;
    __delay_us(10);
     dato1.bit5= RX;
    __delay_us(10);
     dato2.bit5= RX;
     
    __delay_us(BAUDIOS_R - 20);
    dato0.bit6= RX;
    __delay_us(10);
     dato1.bit6= RX;
    __delay_us(10);
     dato2.bit6= RX;
     
    __delay_us(BAUDIOS_R - 20);
    dato0.bit7= RX;
    __delay_us(10);
     dato1.bit7= RX;
    __delay_us(10);
     dato2.bit7= RX;
     
    if( mejorBit(dato0.byte,dato1.byte,dato2.byte) == 'x') //tecla de escape
        state = ESPERA;

}


char mejorBit(char a, char b, char c) {
    char resultado = 0;
    
    // Comprobar cada bit y seleccionar el mejor
    for (int i = 0; i < 8; i++) {
        // Obtener el i-ésimo bit de cada caracter
        char bitA = (a >> i) & 1;
        char bitB = (b >> i) & 1;
        char bitC = (c >> i) & 1;

        // Calcular el bit mejor de los tres
        char mejorBit = (bitA & bitB) | (bitA & bitC) | (bitB & bitC);

        // Establecer el bit en el resultado
        resultado |= (mejorBit << i);
    }

    return resultado;
}
