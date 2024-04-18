#include "header.h"


void init (void){
    TRISIO = TRI;
    GPIO = 0; //inicia todos los gpio a cero
}


//hace parpadear el led cada ves que state crese
void blink  (void){     
    static unsigned int count = 0;
    if (count > state)
        count++;
    else
        LED=LOW;
    
    if(count < state){
        LED=HIGH;
        count = state + 1;}
    
    if (count >= TIME_BLINK)
        count=state;
}

void button  (void){
    static unsigned int count = 0;
    if(count==0 && state==ESPERA && (BOTON==1) ){ //inicia cuenta si esta en inicio
        //state=F1K; //opcional inicia al momento del click en el estado F1K
        count=1;}
    
    if(count==0 && (state!=ESPERA) && (BOTON==1) ){ //reinicia estado 0 si se preciona en funcionamiento
        BUZZ==LOW; //apaga el buzzer
        while( (BOTON==1) ){}
        state=ESPERA;}
    
    if((count!=0) && (BOTON==1) ) //cuenta mientras se precione o reinicia al soltar
        count++;
    else
       count=0; 
    
    if(count >= TIME_BUTTON){ //aumenta el estado
        (state>=F16K) ? state=F16K : state++;
        count=1;}
        
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


void controlBuzz(void){
    unsigned char frec[6]={0,16,8,4,2,1};
    static unsigned int contador =0;
    contador++; 
    
        if(contador >= (frec[state]*TIME_FREC) && (state!=ESPERA) ){
            BUZZ= !(BUZZ==1); //toogle
            contador=0;
        }else if(state==ESPERA){
            BUZZ =0;
            contador=0;
       }
}
