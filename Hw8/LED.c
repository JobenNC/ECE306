//===========================================================================
// File Name : LED.c
//
// Description: Handle initialization of LEDs
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: None
// Functions: Init_LEDs
//===========================================================================

#include  "functions.h"
#include "macros.h"
#include  "msp430.h"

void Init_LEDs(void){
//===========================================================================
// Function name: Init_LEDs
//
// Description: This function initialized the LEDs to off
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: None
// Calls: None
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on all 8 LEDs
  PJOUT &= ~LED1;
  PJOUT &= ~LED2;
  PJOUT &= ~LED3;
  PJOUT &= ~LED4;
  P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;
//------------------------------------------------------------------------------
}