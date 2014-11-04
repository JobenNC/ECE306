//===========================================================================
// File Name : interrupts_adc.c
//
// Description: function declarations
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: None
// Functions: None defined
//===========================================================================


#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

volatile unsigned int ADC_Thumb = BEFORE_START;
volatile unsigned int ADC_RD = BEFORE_START;
volatile unsigned int ADC_LD = BEFORE_START;
volatile unsigned int chan = START;

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  
//===========================================================================
// ISR name: adc interrupt
//
// Description: This ISR handles adc
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: switchPress, isDebounce, bounceCount
// Calls: lcd_out, lcd_clear
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
 switch(__even_in_range(ADC10IV,TWELFTH)) {
 case RESET: break; // No interrupt
 case SECOND: break; // conversion result overflow
 case FOURTH: break; // conversion time overflow
 case SIXTH: break; // ADC10HI
 case EIGHTH: break; // ADC10LO
 case TENTH: break; // ADC10IN
 case TWELFTH: 
    //ADC_Thumb = ADC10MEM0; // Channel A3
    
    
    switch(chan)
    {
    case RESET: 
      ADC_Thumb = ADC10MEM0;
      
      ADC10CTL0 &= ~ADC10ENC;
      ADC10CTL0 &= ~ADC10SC;
      ADC10MCTL0 &= ~ADC10INCH_3;
      ADC10MCTL0 |= ADC10INCH_0;
      ADC10CTL0 |= ADC10ENC;
      ADC10CTL0 |= ADC10SC;
      chan++;
      break;
    case START: 
      ADC_LD = ADC10MEM0;
      
      ADC10CTL0 &= ~ADC10ENC;
      ADC10CTL0 &= ~ADC10SC;
      ADC10MCTL0 &= ~ADC10INCH_0;
      ADC10MCTL0 |= ADC10INCH_1;
      ADC10CTL0 |= ADC10ENC;
      ADC10CTL0 |= ADC10SC;
      chan++;
      break;
    case SECOND: 
      ADC_RD = ADC10MEM0;
      
      ADC10CTL0 &= ~ADC10ENC;
      ADC10CTL0 &= ~ADC10SC;
      ADC10MCTL0 &= ~ADC10INCH_1;
      ADC10MCTL0 |= ADC10INCH_3;
      ADC10CTL0 |= ADC10ENC;
      ADC10CTL0 |= ADC10SC;
      chan=RESET;
      break;
    default: break;
    }
    break; 
 default: break; 
 } 
}

//chan 1 is R det
//chan 2 is L det