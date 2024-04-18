#include "header.h"

//hace parpadear el led cada ves que state crese
void blink  (void){     
    static unsigned int count = 0;
    if (count > state)
        count++;
    else
        digitalwrite(LED,LOW);
    
    if(count < state){
        digitalwrite(LED,HIGH);
        count = state + 1;}
    
    if (count >= TIME_BLINK)
        count=state;
}

void button  (void){
    static unsigned int count = 0;
    if(count==0 && state==ESPERA && digitalread(BOTON)){ //inicia cuenta si esta en inicio
        //state=F1K; //opcional inicia al momento del click en el estado F1K
        count=1;}
    
    if(count==0 && (state!=ESPERA) && digitalread(BOTON)){ //reinicia estado 0 si se preciona en funcionamiento
        digitalwrite(BUZZ,LOW); //apaga el buzzer
        while(digitalread(BOTON)){}
        state=ESPERA;}
    
    if((count!=0) && digitalread(BOTON)) //cuenta mientras se precione o reinicia al soltar
        count++;
    else
       count=0; 
    
    if(count >= TIME_BUTTON){ //aumenta el estado
        (state>=F16K) ? state=F16K : state++;
        count=1;}
        
}
void controlBuzz(void){
    char frec[6]={0,16,8,4,2,1};
    static char toogle =0;
    static char contador =0;
    contador =+1; 
    
        if(contador >= frec[state]){
        toogle= !toogle;
        GPIO5 =(__bit)toogle;
        contador=0;
        }else if(state==0){
        GPIO5 =0;
        contador=0;
       }
}


// cuenta un tiempo desde que se suelta el boton y si se cumple vuelve a estado espera
void one_minute (void){
    static unsigned int count = 0;
    count++;
    if (count >= TIME_MINUTE)
        state=ESPERA;
    if ( digitalread(BOTON) )
        count=0;
}
