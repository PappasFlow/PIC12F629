#ifndef heder
#define	heder


#define NC GPIO0 //Nombre de pines debe tener coherencia con TRI
#define LED GPIO1
#define RX GPIO2
#define BOTON GPIO3
#define TX GPIO4
#define BUZZ GPIO5

#define  TRI  0b00001100  //define estado pines I/O

enum ESTADOS {ESPERA,F1K,F2K,F4K,F8K,F16K}; //Nombre de estados
enum STATES{LOW,HIGH}; //para declarar estados mas claro

#define BAUDIOS 100 //define tiempo para uart funcione de manera correcta es 1/baudios en realidad
#define BAUDIOS_R 90 // define tiempo uart para RX os 
#define _XTAL_FREQ 4000000
#define TIME_BUTTON 1  //ajuste tiempo pulsador para cambiar de estado
#define TIME_MINUTE 30 //define tiempo para reset 
#define TIME_FREC  32 //ajusta tiempo frecuencia 

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
void init (void);

void blink (void);
void button  (void);
void one_minute (void);
void loop (void);

void recieve(void);
void recieve_os(void);
void send(char);
void TX_frec(void);
char mejorBit(char,char,char);

#endif	
