//===========================================================================
// File Name : switch.c
//
// Description: Handle switch 1 & 2 presses and debouncing, also handle
//      events on swtich presses
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: int buttOne, int buttTwo, volatile int waitCount
// Functions: changeDisplay, Switch_Process
//===========================================================================

#include  "functions.h"
#include "macros.h"
#include  "msp430.h"

int buttOne = OFF;
int buttTwo = OFF;
volatile int waitCount = TIME_START;

void move(int count)
//===========================================================================
// Function name: move
//
// Description: This function handles car movement shapes
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
{
    int i;
    if (buttOne == START)
    {
      newFM(ONE_SEC);
      
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      
      P3OUT |= L_FORWARD;
      P3OUT |= R_FORWARD;
      newFM(ONE_SEC);
      
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      
      newFM(ONE_SEC);
      
      P3OUT |= L_REVERSE;
      P3OUT |= R_REVERSE;
      newFM(TWO_SEC);
      
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      
      newFM(ONE_SEC);
      
      P3OUT |= L_FORWARD;
      P3OUT |= R_FORWARD;
      newFM(ONE_SEC);
      
      
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      
      newFM(ONE_SEC);
      
      P3OUT |= L_FORWARD;
      P3OUT |= R_REVERSE;
      newFM(ONE_SEC);
      
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      
      newFM(ONE_SEC);
      
      P3OUT |= R_FORWARD;
      P3OUT |= L_REVERSE;
      newFM(ONE_SEC);
      
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      /*
      //straight line
      //five_msec_sleep(100);
      newFM(100);
      for (i=0; i<count; i++)
      {
        P3OUT |= L_FORWARD;
        P3OUT |= R_FORWARD;
        //five_msec_sleep(65);
        newFM(65);
        P3OUT &= ~L_FORWARD;
        //five_msec_sleep(35);
        newFM(35);
          //P3OUT &= ~R_FORWARD
      }
      */
    }
    else if (buttOne == 2)
    {
      //Two Left circles
      //five_msec_sleep(100);
      newFM(100);
      for (i=0; i<62; i++)
      {
        P3OUT |= L_FORWARD;
        P3OUT |= R_FORWARD;
        //five_msec_sleep(2);
        newFM(2);
        P3OUT &= ~L_FORWARD;
        //five_msec_sleep(12);
        newFM(12);
          //P3OUT &= ~R_FORWARD
      }
    }
    else if (buttOne == 3)
    {
      //Right circle
      //five_msec_sleep(100);
      newFM(100);
      //Right circle
      for (i=0; i<38; i++)
      {
        P3OUT |= L_FORWARD;
        P3OUT |= R_FORWARD;
        //five_msec_sleep(2);
        newFM(2);
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(12);
        newFM(12);
        //P3OUT &= ~R_FORWARD
      }
    }
    else if (buttOne == 4)
    {
        //Figure 8
      //Left Circle
      //five_msec_sleep(100);
      newFM(100);
      //Left circles
      //five_msec_sleep(100);
      for (i=0; i<37; i++)
      {
        P3OUT |= L_FORWARD;
        P3OUT |= R_FORWARD;
        //five_msec_sleep(2);
        newFM(2);
        P3OUT &= ~L_FORWARD;
        //five_msec_sleep(12);
        newFM(12);
          //P3OUT &= ~R_FORWARD
      }
      //for (i=0; i<count; i++)
      //{
      //  P3OUT |= L_FORWARD;
      //  P3OUT |= R_FORWARD;
      //  five_msec_sleep(10);
      //  P3OUT &= ~L_FORWARD;
      //  five_msec_sleep(90);
          //P3OUT &= ~R_FORWARD
      //}
      //Right circle
      for (i=0; i<38; i++)
      {
        P3OUT |= L_FORWARD;
        P3OUT |= R_FORWARD;
        //five_msec_sleep(2);
        newFM(2);
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(14);
        newFM(14);
        //P3OUT &= ~R_FORWARD
      }
      for (i=0; i<40; i++)
      {
        P3OUT |= L_FORWARD;
        P3OUT |= R_FORWARD;
        //five_msec_sleep(2);
        newFM(2);
        P3OUT &= ~L_FORWARD;
        //five_msec_sleep(12);
        newFM(12);
          //P3OUT &= ~R_FORWARD
      }
      //for (i=0; i<count; i++)
      //{
      //  P3OUT |= L_FORWARD;
      //  P3OUT |= R_FORWARD;
      //  five_msec_sleep(10);
      //  P3OUT &= ~L_FORWARD;
      //  five_msec_sleep(90);
          //P3OUT &= ~R_FORWARD
      //}
      //Right circle
      for (i=0; i<38; i++)
      {
        P3OUT |= L_FORWARD;
        P3OUT |= R_FORWARD;
        //five_msec_sleep(2);
        newFM(2);
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(14);
        newFM(14);
        //P3OUT &= ~R_FORWARD
      }
      
    }
    else if (buttOne == -1)
    {
        //Triangle
        //five_msec_sleep(100);
        newFM(100);
        
        for (i=2; i<count; i++)
        {
          P3OUT |= L_FORWARD;
          P3OUT |= R_FORWARD;
          //five_msec_sleep(40);
          newFM(40);
          //P3OUT &= ~L_FORWARD;
          //five_msec_sleep(5);
        }
        
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(110);
        newFM(110);
        
        for (i=2; i<count; i++)
        {
          P3OUT |= L_FORWARD;
          P3OUT |= R_FORWARD;
          //five_msec_sleep(30);
          newFM(30);
          P3OUT &= ~L_FORWARD;
          //five_msec_sleep(10);
          newFM(10);
        }
        
        P3OUT |= L_FORWARD;
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(110);
        newFM(110);
        
        for (i=2; i<count; i++)
        {
          P3OUT |= L_FORWARD;
          P3OUT |= R_FORWARD;
          //five_msec_sleep(40);
          //P3OUT &= ~L_FORWARD;
          //five_msec_sleep(5);
          //five_msec_sleep(30);
          newFM(30);
          P3OUT &= ~L_FORWARD;
          //five_msec_sleep(10);
          newFM(10);
        }
        
        P3OUT |= L_FORWARD;
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(110);
        newFM(110);
        //Triangle
        //five_msec_sleep(100);
        
        for (i=2; i<count; i++)
        {
          P3OUT |= L_FORWARD;
          P3OUT |= R_FORWARD;
          //five_msec_sleep(40);
          //P3OUT &= ~L_FORWARD;
          //five_msec_sleep(5);
          //five_msec_sleep(30);
          newFM(30);
          P3OUT &= ~L_FORWARD;
          //five_msec_sleep(10);
          newFM(10);
        }
        
        P3OUT |= L_FORWARD;
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(110);
        newFM(110);
        
        for (i=2; i<count; i++)
        {
          P3OUT |= L_FORWARD;
          P3OUT |= R_FORWARD;
          //five_msec_sleep(40);
          //P3OUT &= ~L_FORWARD;
          //five_msec_sleep(5);
          //five_msec_sleep(30);
          newFM(30);
          P3OUT &= ~L_FORWARD;
          //five_msec_sleep(10);
          newFM(10);
        }
        
        P3OUT |= L_FORWARD;
        P3OUT &= ~R_FORWARD;
        //five_msec_sleep(110);
        newFM(110);
        
        for (i=2; i<count; i++)
        {
          P3OUT |= L_FORWARD;
          P3OUT |= R_FORWARD;
          //five_msec_sleep(40);
          //P3OUT &= ~L_FORWARD;
          //five_msec_sleep(5);
          //five_msec_sleep(30);
          newFM(30);
          P3OUT &= ~L_FORWARD;
          //five_msec_sleep(10);
          newFM(10);
        }
    }
    P3OUT &= ~R_FORWARD;
    P3OUT &= ~L_FORWARD;
}

void changeDisplay(void)
//===========================================================================
// Function name: changeDisplay
//
// Description: This function manages altering the LCD display
// based on the current values of buttOne and buttTwo
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: int buttOne, int buttTwo, volatile int waitCount
// Calls: lcd_out(char *s, char line)
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
//===========================================================================
{
    if (buttOne == 0)
    {
        lcd_out("     Make Selection", LCD_LINE_1);
    }
    if (buttOne == 1)
    {
         lcd_out("    Straight Line", LCD_LINE_1);
    }
    if (buttOne == 2)
    {
         lcd_out("    Two Circles", LCD_LINE_1);
    }
    if (buttOne == 3)
    {
         lcd_out("    Right Circle", LCD_LINE_1);
    }
    if (buttOne == 4)
    {
         lcd_out("    Figure 8", LCD_LINE_1);
         
    }
    if (buttOne == 5)
    {
        lcd_out("    Triangle", LCD_LINE_1);
        buttOne = -1;
    }
  
    //if ((buttOne == OFF) && (buttTwo == OFF))
    //{
    //   lcd_out("    Lt Forward Rt   ",LCD_LINE_1);       // 16 characters max between quotes - line 1
    //   lcd_out("Off       Off",LCD_LINE_2);
    //   P3OUT &= ~L_FORWARD;
    //   P3OUT &= ~R_FORWARD;
    //}

    //if ((buttOne == OFF) && (buttTwo == ON))
    //{
    //   lcd_out("    Lt Forward Rt   ",LCD_LINE_1);       // 16 characters max between quotes - line 1
    //   lcd_out("Off       On",LCD_LINE_2);
    //   P3OUT &= ~L_FORWARD;
    //   P3OUT |= R_FORWARD;
    //}

    //if ((buttOne == ON) && (buttTwo == OFF))
    //{
    //   lcd_out("    Lt Forward Rt   ",LCD_LINE_1);       // 16 characters max between quotes - line 1
    //   lcd_out("On        Off",LCD_LINE_2);
    //   P3OUT |= L_FORWARD;
    //   P3OUT &= ~R_FORWARD;
    //}

    //if ((buttOne == ON) && (buttTwo == ON))
    //{
    //   lcd_out("    Lt Forward Rt   ",LCD_LINE_1);       // 16 characters max between quotes - line 1
    //   lcd_out("On        On",LCD_LINE_2);
    //   P3OUT |= L_FORWARD;
    //   P3OUT |= R_FORWARD;
    //}
}

void Switches_Process(void){
//------------------------------------------------------------------------------
//===========================================================================
// Function name: Switches_Process
//
// Description: Handle and debounce switch 1 and 2
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: waitCount, buttOne, buttTwo
// Calls: lcd_clear, changeDisplay
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
//------------------------------------------------------------------------------
  if ((!(P4IN & SW1)) && (waitCount > TIME_UP)){
    waitCount = RESTART;
    lcd_clear();
    //buttOne = !buttOne;
    buttOne++;
    changeDisplay();
  }
  if ((!(P4IN & SW2)) && (waitCount > TIME_UP)) {
    waitCount = RESTART;
    //lcd_clear();
    //buttTwo = !buttTwo;
    move(5);
  }
//------------------------------------------------------------------------------
}
