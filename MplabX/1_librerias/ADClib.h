  
#ifndef XC_adc_H
#define	XC_adc_H

#include <xc.h>
#include "config.h"

#define VSS_VDD     0x00
#define VSS_VREFP   0x01
#define VREFN_VDD   0x02
#define VREFN_VREFP 0x03

#define NO_ANALOGS   0x0F   // None
#define ALL_ANALOG   0x00   // A0 A1 A2 A3 A5 E0 E1 E2 B2 B3 B1 B4 B0     
#define AN0_TO_AN11  0x03   // A0 A1 A2 A3 A5 E0 E1 E2 B2 B3 B1 B4       
#define AN0_TO_AN10  0x04   // A0 A1 A2 A3 A5 E0 E1 E2 B2 B3 B1          
#define AN0_TO_AN9   0x05   // A0 A1 A2 A3 A5 E0 E1 E2 B2 B3             
#define AN0_TO_AN8   0x06   // A0 A1 A2 A3 A5 E0 E1 E2 B2                
#define AN0_TO_AN7   0x07   // A0 A1 A2 A3 A5 E0 E1 E2                   
#define AN0_TO_AN6   0x08   // A0 A1 A2 A3 A5 E0 E1                      
#define AN0_TO_AN5   0x09   // A0 A1 A2 A3 A5 E0                         
#define AN0_TO_AN4   0x0A   // A0 A1 A2 A3 A5
#define AN0_TO_AN3   0x0B   // A0 A1 A2 A3
#define AN0_TO_AN2   0x0C   // A0 A1 A2
#define AN0_TO_AN1   0x0D   // A0 A1
#define AN0          0x0E   // A0

void adc_config(unsigned char pinesAN, unsigned char vref){
    if (pinesAN == NO_ANALOGS){
        ADCON1bits.PCFG= NO_ANALOGS;   //no analogicos
        CMCON = 0X07;           //desactivo comparadores
        return;
    }
    CMCON = 0X07;           //desactivo comparadores
    ADCON1bits.PCFG= pinesAN; //TODOS LOS PINES ANALOGICOS
    ADCON1bits.VCFG =vref;  //voltaje referencia VDD_VSS
    ADCON0 = 0;             //canal 0, go/done=0(idle), ADON = ad disabled
    ADCON2bits.ACQT = 1;    //2*TAD
    //ADCON2bits.ACQT = 2; //4*TAD
    ADCON2bits.ADCS = 6; //FOSC/64
    ADCON2bits.ADFM = 1; //Right justified 
}

int adc_read(unsigned char ch){
    if(ch>12){return 0;}
        ADCON0bits.CHS = ch;//selecciono canal
        __delay_us(100);
        ADCON0bits.ADON = 1;//habilitamos ADC
        ADCON0bits.GO_DONE = 1;//comenzamos conversion
        while(ADCON0bits.GO_DONE == 1);//mientras este haciendo la conversion
        ADCON0bits.ADON = 0;//habilitamos ADC
        return ADRES; //aqui manda los 10bit enteros leidos por el ADC
}


#endif	/* XC_HEADER_TEMPLATE_H */

