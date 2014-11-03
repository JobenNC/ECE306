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
volatile unsigned int startTimer = RESET;

unsigned int driving = RESET;
unsigned int reverse = RESET;
unsigned int startHalf = RESET;
unsigned int halfTimer = RESET;

unsigned int L_Dir;
unsigned int R_Dir;

char *display_NCSU;
char *display_HW3;

int test1=0;
int test2=0;

extern volatile int writeNext = 0;

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
  init_adc();
  Init_Serial_UCA1();                        // Initialize Serial Comms
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
 while(ALWAYS) {    
   
   // Can the Operating system run
   newFM(20);
   
   UCA1TXBUF = 'U';
   
   //if (writeNext)
   //{
      //UCA1TXBUF = 'u';
      //writeNext = 0;
      
      //while (!UCTXIFG)
      //{
      //}
      //UCA1TXBUF = 'u';
      
      //while (1)
      //{
      //  test1 = usb_rx_ring_wr;
      //  test2 = usb_rx_ring_rd;
      //  if (test1 != test2) break;
      //}
      
      /////while (!UCTXIFG)
      ////{
      ////}
      ////UCA1TXBUF = 'u';
      
      //usb_rx_ring_rd++;
      //char test = USB_Char_Rx[usb_rx_ring_wr];
   //}
    //Code for tx rx

    //

 // //switch(Time_Sequence){
 // //  case TSEQ_250:                               // 1000 msec  
 // //    if(one_time){
 // //      //Init_LEDs();                      // Initialize LEDs
 // //      one_time = RESET;
 // //    }
 // //    Time_Sequence = RESET;                    // 
 // //  case TSEQ_200:                               // 1000 msec  
 // //    if(one_time){
 // //      //PJOUT |= LED4;                      // Change State of LED 4
 // //      //P3OUT |= LED5;                      // Change State of LED 5
 // //      one_time = RESET;
 // //    }
 // //  case TSEQ_150:                               // 750 msec  
 // //    if(one_time){
 // //      //PJOUT |= LED3;                      // Change State of LED 3
 // //      //P3OUT |= LED6;                      // Change State of LED 6
 // //      one_time = RESET;
 // //    }
 // //  case TSEQ_100:                               // 500 msec  
 // //    if(one_time){
 // //      //PJOUT |= LED2;                      // Change State of LED 2
 // //      //P3OUT |= LED7;                      // Change State of LED 7
 // //      one_time = RESET;
 // //    }
 // //  case  TSEQ_50:                               // 250 msec  
 // //    if(one_time){
 //  //     //PJOUT |= LED1;                      // Change State of LED 1
 //  //     //P3OUT |= LED8;                      // Change State of LED 8
 // //      one_time = RESET;
 // //    }
 // //    break;                                // 
 // //  default: break; 
 // //}
 // //Switches_Process();                       // Check for switch state change
 // 
 // if (starting)
 // {
 //   newFM(HALF_SEC);
 //   starting = RESET;
 // }
 // 
 // if ((drive) && ~(driving))
 // {
 //     //newFM(200);
 //     driving = START;
 // }
 // if (driving)
 // {
 //   
 //   //if ((ADC_LD > (LED_Black_LD-350)) && (ADC_RD < (LED_Black_RD-350)))
 //   //{
 //   //  P3OUT &= ~L_FORWARD;
 //   //  P3OUT |= R_FORWARD;
 //   //  newFM(20);
 //   //  P3OUT &= ~L_FORWARD;
 //   //  P3OUT &= ~R_FORWARD;
 //   //}
 //   
 //   //else if ((ADC_LD < (LED_Black_LD-350)) && (ADC_RD > (LED_Black_RD-350)))
 //   //{
 //   //  P3OUT |= L_FORWARD;
 //   //  P3OUT &= ~R_FORWARD;
 //   //  newFM(20);
 //   //  P3OUT &= ~L_FORWARD;
 //   //  P3OUT &= ~R_FORWARD;
 //   //}
 //   
 //   if ((ADC_LD < (LED_Black_LD - offLine)) && (ADC_RD < (LED_Black_RD - offLine)))
 //   {
 //     P3OUT |= L_Dir;
 //     P3OUT |= R_Dir;
 //     newFM(SEVENTH);
 //     P3OUT &= ~L_Dir;
 //     P3OUT &= ~R_Dir;
 //   }
 //   
 //   else
 //   {
 //     P3OUT &= ~L_Dir;
 //     P3OUT &= ~R_Dir;
 //     if (reverse == RESET)
 //     {
 //       newFM(HALF_SEC);
 //       L_Dir = L_REVERSE;
 //       R_Dir = R_REVERSE;
 //       
 //       startTimer = START;
 //       P3OUT |= L_Dir;
 //       P3OUT |= R_Dir;
 //       newFM(seventy);
 //       P3OUT &= ~L_Dir;
 //       P3OUT &= ~R_Dir;
 //       
 //       reverse++;
 //     }
 //     else if (reverse == START)
 //     {
 //       
 //       startTimer = RESET;
 //       P3OUT &= ~L_Dir;
 //       P3OUT &= ~R_Dir;
 //       
 //       L_Dir = L_FORWARD;
 //       R_Dir = R_FORWARD;
 //       
 //       newFM(HALF_SEC);
 //       
 //       P3OUT |= L_Dir;
 //       P3OUT |= R_Dir;
 //       newFM(timerCount/HALF);
 //       P3OUT &= ~L_Dir;
 //       P3OUT &= ~R_Dir;
 //       
 //       newFM(ONE_SEC);
 //       
 //       L_Dir = R_FORWARD;
 //       R_Dir = L_REVERSE;
 //       P3OUT |= L_Dir;
 //       P3OUT |= R_Dir;
 //       newFM(twoLoop);
 //       P3OUT &= ~L_Dir;
 //       P3OUT &= ~R_Dir;
 //       
 //       newFM(ONE_SEC);
 //       
 //       L_Dir = R_REVERSE;
 //       R_Dir = L_FORWARD;
 //       P3OUT |= L_Dir;
 //       P3OUT |= R_Dir;
 //       newFM(twoLoop);
 //       P3OUT &= ~L_Dir;
 //       P3OUT &= ~R_Dir;
 //       
 //       
 //       reverse++;
 //       driving = RESET;
 //       drive = RESET;
 //     }
 //     
 //     else
 //     {
 //       P3OUT &= ~L_Dir;
 //       P3OUT &= ~R_Dir;
 //     }
 //   }
 // }
 // //ADC_Process();
 // //if(Time_Sequence > TSEQ_250){
 // //  Time_Sequence = RESET;
 // //}
 }
//------------------------------------------------------------------------------
}
