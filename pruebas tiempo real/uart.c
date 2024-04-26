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



void send(char *ch){
    union CharBits datosend;
    static unsigned int count = 0;
    static unsigned int i = 0;
    datosend.byte = ch[i];
    
    if(ch[i]==0){
            tx_flag = 0;
            i = 0;
        }
    
    if( tx_flag == 1){
        switch(count) {
            case 0:TX =LOW;
                count++;
                break;
            case (BAUDIOS):
                TX  =(__bit)datosend.bit0;
                count++;
                break;
            case (BAUDIOS*2):
                TX  =(__bit)datosend.bit1;
                count++;
                break;
            case (BAUDIOS*3):
                TX  =(__bit)datosend.bit2;
                count++;
                break;
            case (BAUDIOS*4):
                TX  =(__bit)datosend.bit3;
                count++;
                break;
            case (BAUDIOS*5):
                TX  =(__bit)datosend.bit4;
                count++;
                break;
            case (BAUDIOS*6):
                TX  =(__bit)datosend.bit5;
                count++;
                break;
            case (BAUDIOS*7):
                TX  =(__bit)datosend.bit6;
                count++;
                break;
            case (BAUDIOS*8):
                TX  =(__bit)datosend.bit7;
                count++;
                break;
            case (BAUDIOS*9):
                TX  =HIGH;
                count++;
                break;
            case (BAUDIOS*30):
                count=0;
                i++;
                break;
            default:
                count++;
        }
    }
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

