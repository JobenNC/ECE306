//===========================================================================
// File Name : init_adc.c
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

void ADC_Process(void){
//===========================================================================
// function name: adc_process
//
// Description: This handles initial adc reading
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
 while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
    ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
}

void init_adc(void)
{
  //===========================================================================
// function name: init_adc
//
// Description: This ISR handles switch events
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
 //Will go to init_ADC
 //ADC10CTL0 = RESET_STATE; // Clear ADC10CTL0 
 ADC10CTL0 = RESET; // Clear ADC10CTL0 
 ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
 ADC10CTL0 &= ~ADC10MSC; // Single Sequence
 ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
 //ADC10CTL1 = RESET_STATE; // Clear ADC10CTL1 
 ADC10CTL1 = RESET; // Clear ADC10CTL1 
 ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
 ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
 ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
 ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider � Divide by 1.
 ADC10CTL1 |= ADC10SSEL_0; // MODCLK
 ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
 //ADC10CTL1 |= 1; // sequence-of-channels, single-conversion
 //ADC10CTL2 = RESET_STATE; // Clear ADC10CTL2
 ADC10CTL2 = RESET; // Clear ADC10CTL2 
 ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
 ADC10CTL2 |= ADC10RES; // 10-bit resolution
 ADC10CTL2 &= ~ADC10DF; // Binary unsigned
 ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
 
 
 //ADC10MCTL0 = RESET_STATE; // Clear ADC10MCTL0
 ADC10MCTL0 = RESET; // Clear ADC10MCTL0 
 ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
 
 //ADC10MCTL0 |= ADC10INCH_0; // Channel A1
 //ADC10MCTL0 |= ADC10INCH_1; // Channel A2
 ADC10MCTL0 |= ADC10INCH_0; // Channel A3 Thumb Wheel 

 ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt 
}