/*
 * File:   newmain.c
 * Author: el_pa
 *
 * Created on 2 de julio de 2020, 12:17 PM
 */


#include <xc.h>
#include "..\1_libetriasYO\config.h"
#include "..\1_libetriasYO\lcd1.h"
#include <stdio.h>
#include "..\1_libetriasYO\ADClib.h"

#define Echo PORTCbits.RC1 //define RA1 como echo 
#define Trig PORTCbits.RC0 //define RA2 como trigger

void init(){
    PORTA = 0x00;
    LATA = 0x00;
    ADCON1 = 0x0F;
    CMCON = 0x07;
    //TRISA= 0b11001111
    //TRISA por bits
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 1;
    TRISAbits.RA2 = 1;
    TRISAbits.RA3 = 1;
    TRISAbits.RA4 = 0;
    TRISAbits.RA5 = 0;
    TRISAbits.RA6 = 1;
    //TRISAbits.RA7 = 1;
    
            
    PORTB = 0x00;
    LATB = 0x00;
    TRISB = 0x00;
    
    PORTD = 0x00;
    LATD = 0x00;
    TRISD = 0x00;
}


void main(void) {
    init();
    int a;
    lcd_init();
    lcd_clear();
    lcd_gotoxy(1,1);
    lcd_putc("*Hola mundo*");
    lcd_gotoxy(2,1);
    lcd_putc("*****XC8*****");
    delay_ms(800);
    T1CON = 0x10;
      while(1)
  { 
    TMR1H = 0;                //define el valor inicial del timer
    TMR1L = 0;                //lo de arribax2

    Trig = 1;                  //valor del trigger en 1 
    delay_ms(10);          
    Trig = 0;                  //trigger bajo

    while(!Echo){
     TMR1ON = 1; 
    }              //inicia echo y espera por respuesta 
                    
    while(Echo){
   TMR1ON = 0;
    }               //espera al echo para poner en bajo el timer 
                 

    a = (TMR1L | (TMR1H<<8)); //lee valores del timer 
    a = a/58.82;              //tiempo a distancia (formula)
    
    if(a>=2 && a<=400)        //revisa que este dentro del rango del sensor 
    { 
      lcd_clear();
      lcd_gotoxy (1,1);
      lcd_putc("Distancia =");

      lcd_gotoxy(1,14);
      
      sprintf( "%i",a%10 +48);

      a = a/10;
      lcd_gotoxy(1,13);
      sprintf( "%i",a%10 +48);

      a = a/10;
      lcd_gotoxy(1,12);
      sprintf( "%i",a%10 +48);

    }  
    else
    {
      lcd_clear();
      lcd_gotoxy(1,1);
      lcd_putc("Fuera de rango");
    }
    delay_ms(400);
  }
        return;
}

/*

#define V_AN 4.08

void main(void) {
    unsigned long adcv=0;
    float volt;
    char datos[20];
    PORTA = 0X00;
    LATA = 0X00;
    TRISA = 3; //RA0 ENTRADA
    adc_config(AN0_TO_AN1,VSS_VDD);
    
    PORTB = 0X00;
    LATB = 0X00;
    TRISB = 0X00;
    
    PORTD = 0X00;
    LATD = 0X00;
    TRISD = 0X00;
    lcd_init();
    lcd_putc("\f**IDE MPLAB X**");    //se muestra una cadena de caracteres en la pantalla LCD
    lcd_putc("\n******XC8****LCD4x20");  
    lcd_putc("\nuControladores"); 
    lcd_putc("\nADC: PIC18F4550");
    __delay_ms(500);
    lcd_clear();
    
    //como convertir de BDC a binario, de bianrio a BDC 
    while(1){
        adcv = adc_read(1);
        delay_ms(100);
        
        volt= (adcv*V_AN)/1023;
        lcd_gotoxy(1,1);
        sprintf(datos,"%.2f%V",volt);
        lcd_putc(datos);
        
        
        
        
        adcv = adc_read(0);
        volt= (adcv*V_AN*100.0)/1023;
        lcd_gotoxy(1,2);
        sprintf(datos,"%.2f%cC",volt,223);
        lcd_putc(datos);
        delay_ms(100);
        
    }
    return;
}
*/