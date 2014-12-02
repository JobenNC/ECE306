//===========================================================================
// File Name : drive.c
//
// Description: The code for oreintation changes
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: volatile unsigned int Time_Sequence, volatile char one_time,
// volatile unsigned int five_msec_count, char *display_NCSU, char *display_HW3
// Functions: goLeft, goRight, turnAround
//===========================================================================
#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

unsigned int L_Dir = L_FORWARD;
unsigned int R_Dir = R_FORWARD;

volatile unsigned int turnDebounce = START;


void goLeft()
//===========================================================================
// Function name: goLeft
//
// Description: Go left
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: Time_Sequence, one_time, five_msec_count
// Calls: 
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
//===========================================================================
{
   
  
      if (slowDrive)
      {
        P3OUT |= L_Dir;
        P3OUT &= ~R_Dir;
      }
      else
      {
        P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      }
      goingLeft = START;
}

void goForward()
//===========================================================================
// Function name: goForward
//
// Description: Drive car forward
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: Time_Sequence, one_time, five_msec_count
// Calls: 
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
//===========================================================================
{
  if (slowDrive)
      {
        P3OUT |= L_Dir;
        P3OUT |= R_Dir;
      }
      else
      {
        P3OUT &= ~L_Dir;
        P3OUT &= ~R_Dir;
      }
      goingLeft = RESET;
      goingRight = RESET;
}

void goRight()
//===========================================================================
// Function name: goRight
//
// Description: Turn the car around
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: Time_Sequence, one_time, five_msec_count
// Calls: 
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
//===========================================================================
{
      if (slowDrive)
      {
        P3OUT &= ~L_Dir;
        P3OUT |= R_Dir;
      }
      else
      {
        P3OUT &= ~L_Dir;
        P3OUT &= ~R_Dir;
      }
      goingRight = START;
  
}


void turnAroundExp()
//===========================================================================
// Function name: turnAroundExp
//
// Description: movements for turning around
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: Time_Sequence, one_time, five_msec_count
// Calls: 
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
//===========================================================================
{
  
  if (turnDebounce)
  {
      newFM(FIFTH);
      P3OUT |= R_FORWARD;
      P3OUT |= L_REVERSE;
      newFM(ledOffset - TENTH);
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      newFM(FIFTH);
      turnDebounce = RESET;
  }
  if (((ADC_LD < (LED_Black_LD-ledOffset)) && (ADC_RD < (LED_Black_RD-ledOffset))))
  {
    if (slowDrive)
        {
          P3OUT |= R_FORWARD;
          P3OUT &= ~L_FORWARD;
          P3OUT |= L_REVERSE;
        }
    else
      {
         P3OUT &= ~L_FORWARD;
         P3OUT &= ~R_FORWARD;
         P3OUT &= ~L_REVERSE;
         P3OUT &= ~R_REVERSE;
      }
  }
  else 
  {
     P3OUT &= ~L_FORWARD;
     P3OUT &= ~R_FORWARD;
     P3OUT &= ~L_REVERSE;
     P3OUT &= ~R_REVERSE;
     turnAround = RESET;
     drive = RESET;
  } 
}
