#include "header.h"


void init (void){
    TRISIO = TRI;
    GPIO = 0; //inicia todos los gpio a cero
    TX = HIGH;
    
    T0CS = 0;         // Timer0 Clock Source Select bit: Internal instruction cycle clock (CLKOUT)
    PSA = 0;          // Prescaler Assignment bit: Prescaler is assigned to the Timer0 module
    PS2 =1;          // Prescaler Rate Select bits: 1:128 Prescaler value
    PS1 = 1;
    PS0 = 1;
    // Calcular el valor de TMR0 para una interrupción cada 32 kHz
    TMR0 =0;// Prescaler 1:128, Frecuencia deseada = 32000 Hz (32 kHz)
    T0IE = 1;         // Enable Timer0 overflow interrupt
    
    GIE = 1;          // Enable Global Interrupt Enable bit
    
}


//hace parpadear el led cada ves que state crese
void blink  (void){     
    static unsigned char sp = ESPERA;
    if (sp != state){
        sp=state;
        LED=HIGH;}
    else
        LED=LOW;
}

void button  (void){
    static unsigned int count = 0;
    
    if(BOTON==1){
        __delay_us(20);//evita efecto rebote
    
        if(count==0 && state==ESPERA && (BOTON==1) ){ //inicia cuenta si esta en inicio
            state=F1K; //opcional inicia al momento del click en el estado F1K
            count=1;}

        if(count==0 && (state!=ESPERA) && (BOTON==1) ){ //reinicia estado 0 si se preciona en funcionamiento
            BUZZ=LOW; //apaga el buzzer
            while( BOTON==1 ){}
                state=ESPERA;}

        if((count!=0) && (BOTON==1) ) //cuenta mientras se precione
            count++;

        if(count >= TIME_BUTTON){ //aumenta el estado
            (state>F16K) ? state=F1K : state++;
            count=1;}
    } else
        count=0;  //reinicia al soltar
}


// cuenta un tiempo desde que se suelta el boton y si se cumple vuelve a estado espera
void one_minute (void){
    static unsigned int count = 0;
    count++;
    if (count >= TIME_MINUTE)
        state=ESPERA;
    if ( BOTON==1 )
        count=0;
}
