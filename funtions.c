#include "header.h"


void init (void){
    TRISIO = TRI;
    GPIO = 0; //inicia todos los gpio a cero
    GPIO0 =1;
    T0CS = 0;         // Timer0 Clock Source Select bit: Internal instruction cycle clock (CLKOUT)
    PSA = 0;          // Prescaler Assignment bit: Prescaler is assigned to the Timer0 module
    PS2 =1;          // Prescaler Rate Select bits: 1:128 Prescaler value
    PS1 = 1;
    PS0 = 1;
    
    // Calcular el valor de TMR0 para una interrupción cada 32 kHz
    TMR0 =0;// Prescaler 1:128, Frecuencia deseada = 32000 Hz (32 kHz)
    
    T0IE = 1;         // Enable Timer0 overflow interrupt
    GIE = 0;          // Enable Global Interrupt Enable bit
}

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
union CharBits datosend[6];
union CharBits dato;
void carga(void){
    char aux = '0';
    for(char i=0;i<6;i++){
        datosend[i].byte = aux + i;
    }
}

void send(void){
     GPIO0 =LOW;
     __delay_us(100);
     GPIO0  =(__bit)datosend[state].bit0;
     __delay_us(90);
     GPIO0 =(__bit)datosend[state].bit1;
     __delay_us(90);
    GPIO0  =(__bit)datosend[state].bit2;
     __delay_us(90);
     GPIO0  =(__bit)datosend[state].bit3;
     __delay_us(90);
     GPIO0 =(__bit)datosend[state].bit4;
     __delay_us(90);
     GPIO0  =(__bit)datosend[state].bit5;
     __delay_us(90);
     GPIO0  =(__bit)datosend[state].bit6;
     __delay_us(90);
     GPIO0 =(__bit)datosend[state].bit7;
     __delay_us(90);
     GPIO0  =HIGH;
}
void recieve(void){
    __delay_us(90);
    dato.bit0= GPIO1;
    __delay_us(100);
    dato.bit1= GPIO1;
    __delay_us(100);
    dato.bit2= GPIO1;
    __delay_us(100);
    dato.bit3= GPIO1;
    __delay_us(100);
    dato.bit4=GPIO1;
    __delay_us(100);
    dato.bit5= GPIO1;
    __delay_us(100);
    dato.bit6= GPIO1;
    __delay_us(100);
    dato.bit7= GPIO1;
    if(dato.byte == 0x1b)
        state = 0;
}
void button  (void){
    static unsigned int count = 0;
    static unsigned int flag = 0;
    if(count==0 && state==ESPERA && (BOTON==1) ){ //inicia cuenta si esta en inicio
        //state=F1K; //opcional inicia al momento del click en el estado F1K
        count=1;}
    
    if(count==0 && (state!=ESPERA) && (BOTON==1) ){ //reinicia estado 0 si se preciona en funcionamiento
        state=ESPERA;}
    
    if((count!=0) && (BOTON==1) ) //cuenta mientras se precione o reinicia al soltar
        count++;
    else{
       count=0; 
       flag =1;
    }
    if(flag){
        (count==60) ? state=0 : count++;
    }
if ((count >= state) && !flag) {
    if(state >= 5)
    state = 1;
    else
    state = (char)count;
    GPIO4 = 1;
    count = 1;
}}
void one_Second(void){
    button(); 
    send();
    GPIO4=0;
}
