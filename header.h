#ifndef header
#define	header

//Define (no tocar nombres)
#define  TRI  0b00001010  //define estado pines I/O
enum PINS {RX,TX,NC,BOTON,LED,BUZZ}; //Nombre de pines debe tener coherencia con TRI
enum ESTADOS {ESPERA,F1K,F2K,F4K,F8K,F16K}; //Nombre de estados
enum STATES{LOW,HIGH}; //para declarar estados mas claro

#define TIME_BLINK  1000  //define tiempo parpadeo led
#define TIME_BUTTON 7000  //define tiempo pulsador para cambiar de estado
#define TIME_MINUTE 30000 //define tiempo para reset 

//varibles globales
char state = ESPERA;  //estado maquina


// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


//LIBS
#include <xc.h> // include processor files - each processor file is guarded.  


//My HEDERS
void digitalwrite (unsigned char,unsigned char);
char digitalread (unsigned char);
void init (void);
void controlBuzz(void);

void blink (void);
void button  (void);
void one_minute (void);




#endif	
