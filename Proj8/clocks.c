//===========================================================================
// File Name : clocks.c
//
// Description: Clock initializations
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: None
// Functions: Init_Clocks
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_Clocks(void){
//===========================================================================
// Function name: Init_Clocks
//
// Description: Initialize clocks
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
//------------------------------------------------------------------------------
// Clock Configurtaions
// This is the clock initialization for the program.
//
// Initial clock configuration, runs immediately after boot.
// Disables 1ms watchdog timer, 
//      configure MCLK to 8MHz
//      configure SMCLK to 8MHz.  
// Since the X1 oscillator is not currently connected, 
// X1CLK is an unknown speed (probably ~10kHz).
//------------------------------------------------------------------------------
// ==========================================================================
  WDTCTL = WDTPW | WDTHOLD;            // Disable watchdog
// Clocks:
  CSCTL0 = CSKEY;                      // Unlock register
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;       // Set max. DCO setting [8MHz]
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;   // set ACLK = vlo; SMCLK = DCO; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_0 + DIVM_0;   // set all dividers /1
  CSCTL0_H = CSLOCK;                   // Lock registers
//------------------------------------------------------------------------------
}

