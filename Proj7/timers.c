//===========================================================================
// File Name : timers.c
//
// Description: This file contains initialization functions and interrupt
//      handlers for the time functions
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: No globals defined in this file
// Functions: Init_Timers
//===========================================================================

#include  "functions.h"
#include "macros.h"
#include "msp430.h"

void Init_Timers(void){
//===========================================================================
// Function name: Init_Timers
//
// Description: This function initialized the timers
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: None
// Calls: void Init_Timer_B2(void)
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
  
  Init_Timer_B2();   //  Required for provided compiled code to work
  Init_Timer_A0();
//------------------------------------------------------------------------------
//******************************************************************************
}

void usleep10(unsigned int usec){
//===========================================================================
// Function name: usleep10
//
// Description: a sleep function
// 
// Passed : int usec: a 10us multiplier
// Locals: int i, int j
// Returned: no values returned
// Globals: None
// Calls: None
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
  
//******************************************************************************
//------------------------------------------------------------------------------
// At the current clock rate this yields about 10usec per value passed
// A value of  0 yields 1.37 uSec
// A value of  1 yields 1.87 uSec
// A value of  2 yields 2.36 uSec
// A value of  3 yields 2.86 uSec
// A value of  4 yields 3.36 uSec
// A value of  5 yields 3.86 uSec
// A value of  6 yields 4.36 uSec
// A value of  7 yields 4.85 uSec
// A value of  8 yields 5.354 uSec
// A value of  9 yields 5.854 uSec
// A value of 10 yields 6.353 uSec
// A value of 11 yields 6.851 uSec
// A value of 12 yields 7.351 uSec
// A value of 13 yields 7.849 uSec
// A value of 14 yields 8.350 uSec
// A value of 15 yields 8.849 uSec
// A value of 16 yields 9.342 uSec
// A value of 17 yields 9.84 uSec
// A value of 18 yields 10.34 uSec
// A value of 19 yields 10.84 uSec
  int i,j;
  for(j=RESET;j<usec;j++){
    for(i=RESET;i<USLEEP_10_FIN;i++);
  }
//------------------------------------------------------------------------------
//******************************************************************************
}

void five_msec_sleep(unsigned int fivemsec){
//===========================================================================
// Function name: five_msec_sleep
//
// Description: a 5msec sleep function
// 
// Passed : unsigned int fivemsec
// Locals: no variables declared
// Returned: no values returned
// Globals: five_msec_count
// Calls: None
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
//------------------------------------------------------------------------------
//Each count passed is at least x times 5 milliseconds
  five_msec_count = RESET;
  while(fivemsec > (five_msec_count+ONE));
//------------------------------------------------------------------------------
}

void TimerB0code(void){
//------------------------------------------------------------------------------
// Timer B0 interrupt code
//------------------------------------------------------------------------------
  Time_Sequence++;
  if (waitCount <= TIME_UP) waitCount ++;
  one_time = START;
  if (five_msec_count < FIVE_MSEC_FIN){
    five_msec_count++;
  }
//------------------------------------------------------------------------------
}

void Init_Timer_A0(void)
{
//===========================================================================
// Function name: Init_Timer_A0
//
// Description: This function initializes Timer A0
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: None
// Calls: void Init_Timer_B2(void)
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
  //select src w/ tassel bits
  // set divider w/ taidex bits
  //then set taclr bit
  //starts counting as soon as taclr bit is clears.
  
  //taxccr0 stops clock when 0 written, restarts w/ nonzero
  //in scen, stars incr up from zero
  
  //op mode selected w/ mc bits
  //00 stop - halt
  //01 up - from zero to val of ta0ccr0
  //10 cont - rep counts from zero to 0fffh
  //11 up/down - rep counts from 0 to val of ta0ccr0 and back to 0
  
  //# timer cnts in period is ta0ccr0 + 1
  
  //ta0ccr0 ccifg intrpt flag is set when timer hits ta0ccr0 val
  //taifg is set when timer counts from ta0ccr0 to 0
  TA0CTL = TASSEL__SMCLK;
  //TA0CTL |= 0x
  TA0CTL |= TACLR;
  TA0CTL |= MC__CONTINUOUS;
  TA0CTL |= ID__2;
  TA0EX0 = TAIDEX_7;
  
  //disable and reset overflow intrpt
  TA0CTL &= ~TAIE;
  TA0CTL &= ~TAIFG;
  
  //int INTERVAL = 5;
  TA0CCR0 = FIVE_MSEC_OFFSET; //8,000,000/8/2/2500 = 200Hz = 5msec
  
  TA0CCTL0 |= CCIE; //enable caputre compare control reg 1
  
  //&= ~CCIE to disable
  
  //TA0R is the count reg
  //TA0CLR clears TA0R, clock div and count dir
}

void newFM(int count)
//===========================================================================
// Function name: newFM
//
// Description: My five msec sleep funct
// 
// Passed : iter count
// Locals: no variables declared
// Returned: no values returned
// Globals: fMCount
// Calls: None
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
{
  int i;
  for (i=RESET; i < count; i++)
  {
    int oldVal = fMCount;
    while (fMCount != ~oldVal)
    {
    }
  }
  return;
}
