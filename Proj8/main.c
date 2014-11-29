//===========================================================================
// File Name : main.c
//
// Description: The main, 'while' operating system
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: volatile unsigned int Time_Sequence, volatile char one_time,
// volatile unsigned int five_msec_count, char *display_NCSU, char *display_HW3
// Functions: main
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

volatile unsigned int Time_Sequence;
volatile char one_time;
volatile unsigned int five_msec_count;
volatile unsigned int startTimer = 0;

volatile unsigned int goFor = 0;

volatile unsigned int slowDrive = 0;

unsigned int driving = 0;
unsigned int reverse = 0;
unsigned int startHalf = 0;
unsigned int halfTimer = 0;

unsigned int L_Dir;
unsigned int R_Dir;

unsigned int turnDebounce = 1;

char *display_NCSU;
char *display_HW3;

char goingRight = 0;
char goingLeft = 0;

void main(void){
//===========================================================================
// Function name: main
//
// Description: The main function.  Our 'while' OS
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: Time_Sequence, one_time, five_msec_count
// Calls: Init_Ports, Init_Clocks, Init_Conditions, Init_Timers, Init_LEDs,
//      Init_LCD, five_msec_sleep, Switch_Process
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
//===========================================================================
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  PJOUT |= LED1;                            // Turn LED 1 on to indicate boot
  Time_Sequence = RESET;                        // 
  Init_Timers();                            // Initialize Timers
  five_msec_sleep(SLEEP_50);                      // 250 msec delay for the clock to settle
  Init_LCD();                               // Initialize LCD
  five_msec_sleep(SLEEP_75);                      // 375 msec delay for the clock to settle
  Init_LEDs();                              // Initialize LEDs
  display_NCSU = "   Callibrate   ";
  display_HW3 =  "  IR Em Off  ";
  
//  lcd_command(CLEAR_DISPLAY);
  five_msec_sleep(SLEEP_10); 
  lcd_out("Make Selection",LCD_LINE_1);       // 16 characters max between quotes - line 1
  //lcd_out("LED On       ",LCD_LINE_2);
    //lcd_out(display_NCSU,LCD_LINE_1);       // 16 characters max between quotes - line 1
    //lcd_out(display_HW3,LCD_LINE_2);        // 16 characters max between quotes - line 2
    
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 ADC_Process();
 L_Dir = L_FORWARD;
 R_Dir = R_FORWARD;
 while(ALWAYS) {                            // Can the Operating system run
  if (turnAround) 
  {
    //turnDebounce = 1;
    turnAroundExp();
  }
  else{
  if ((drive) && ~(driving))
  {
      //newFM(200);
      driving = 1;
      //if (turnAround) turnAroundExp();
  }
  if (driving)
  {
    
    //newFM(2);
    //threshhold of 50 at least works!
    //100 works well
    //else if ((ADC_LD > (LED_White_LD+250)) && (ADC_RD > (LED_White_RD+250)))
    if ((ADC_LD > (LED_Black_LD-80)) && (ADC_RD > (LED_Black_RD-80)))
    {
      
      //P3OUT |= L_Dir;
      //P3OUT |= R_Dir;
      //newFM(1);
      //P3OUT &= ~L_Dir;
      //P3OUT &= ~R_Dir;
      //newFM(1);
      //goFor = 1;
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
      goingLeft = 0;
      goingRight = 0;
    }
    
    //if ((ADC_LD < (LED_White_LD+250)) && (ADC_RD > (LED_White_RD+250)))
    else if ((ADC_RD > (LED_Black_RD-80)))
    {
      goLeft();
    }
    
    //else if ((ADC_LD > (LED_White_LD+250)) && (ADC_RD < (LED_White_RD+250)))
    else if ((ADC_LD > (LED_Black_LD-80)))
    {
      goRight();
    }
    
    //else if ((turnAround) && ((ADC_LD < (LED_Black_LD-150)) && (ADC_RD < (LED_Black_RD-150))))
    //else if (turnAround)
    //{
    //  turnAroundExp();
    //}
    
    else
    {
      if (goingLeft)
      {
      goLeft();
        
      }
      
      else if (goingRight)
      {
      goRight();
      }
    }
  }
  }
 }
//------------------------------------------------------------------------------
}

void goLeft()
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
      //goRight = 1;
      goingLeft = 1;
}

void goRight()
{
      //lcd_clear();
      //lcd_out("Go Right", LCD_LINE_1);
      //newFM(5);
      //P3OUT &= ~L_FORWARD;
      //P3OUT |= R_FORWARD;
      //newFM(1);
      //P3OUT &= ~L_FORWARD;
      //P3OUT &= ~R_FORWARD;
      //newFM(3);
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
      //goRight = 1;
      goingRight = 1;
  
}

void turnAroundExp()
{
  
  if (turnDebounce)
  {
      newFM(5);
      P3OUT |= R_FORWARD;
      P3OUT |= L_REVERSE;
      newFM(50);
      P3OUT &= ~L_FORWARD;
      P3OUT &= ~R_FORWARD;
      P3OUT &= ~L_REVERSE;
      P3OUT &= ~R_REVERSE;
      newFM(5);
      turnDebounce = 0;
  }
  if (((ADC_LD < (LED_Black_LD-80)) && (ADC_RD < (LED_Black_RD-80))))
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
     turnAround = 0;
  }
  
  
}
