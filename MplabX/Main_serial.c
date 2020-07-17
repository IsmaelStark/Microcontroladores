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

#include "..\1_libetriasYO\SerialClase.h"






void main(void) {
    unsigned long adcv=0;
    float volt;
    char datos[20], c;
    PORTA = 0X00;
    LATA = 0X00;
    TRISA = 3; //RA0 ENTRADA
    adc_config(NO_ANALOGS,VSS_VDD);
    
    PORTB = 0X00;
    LATB = 0X00;
    TRISB = 0X00;
    
    PORTD = 0X00;
    LATD = 0X00;
    TRISD = 0X00;
    
    serial_config(9600);
    lcd_init();
    lcd_putc("\f**IDE MPLAB X**");    //se muestra una cadena de caracteres en la pantalla LCD
    lcd_putc("\n******XC8****LCD4x20");  
    lcd_putc("\nuControladores"); 
    lcd_putc("\nADC: PIC18F4550");
    __delay_ms(500);
    lcd_clear();
    
    //como convertir de BDC a binario, de bianrio a BDC 
    while(1){
        tx_serial_string("Tolentino va areprobar :v, es broma F");
        c = rx_serial();
        LATB = c;
        delay_ms(1000);
        
    }
    return;
}
