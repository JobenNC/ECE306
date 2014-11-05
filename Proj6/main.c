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
char test;
char *serial;
int counter = 0;

char *display_NCSU;
char *display_HW3;

char toWrite;

int test1=RESET;
int test2=RESET;

int timeOut = RESET;
int dontWrite = RESET;


extern volatile int writeNext = RESET;

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
  lcd_out("1-Display 2-Clr",LCD_LINE_1);       // 16 characters max between quotes - line 1
  //lcd_out("LED On       ",LCD_LINE_2);
    //lcd_out(display_NCSU,LCD_LINE_1);       // 16 characters max between quotes - line 1
    //lcd_out(display_HW3,LCD_LINE_2);        // 16 characters max between quotes - line 2
    
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 ADC_Process();
 L_Dir = L_FORWARD;
 R_Dir = R_FORWARD;
 serial="               ";
 while(ALWAYS) {    
   
   //UCA1TXBUF = 'U';
   //if (nib2 < numRange) nib2 = nib2 + numOffset;
   //       else nib2 = nib2 + charOffset;
   test1 = usb_rx_ring_wr;
   test2 = usb_rx_ring_rd;
   if (test1 != test2)
      {
        if ((UCTXIFG))
        {
          if (usb_rx_ring_rd > 6)
          {
            usb_rx_ring_rd =0;
            test = USB_Char_Rx[7];
            test++;
          }
          else
          {
            usb_rx_ring_rd++;
            test = USB_Char_Rx[usb_rx_ring_wr];
          }
          
          //test = test + numOffset;
          
          lcd_clear();
          
          //test = test + 48;
          toWrite = test/10;
          serial[char1]=toWrite + 48;
          
          toWrite = test % 10;
          
          serial[char2] = toWrite + 48;
          //if ((int) test < 10)
          //{
          //    toWrite = test + 48;
          //}     
          //serial[char1]=toWrite;
          
          lcd_out(serial, LCD_LINE_1);
          
          test++;
          //test = test - 48;
          
          newFM(200);
          UCA1TXBUF = test;
        }
   //     nib1 = (nib1Mask&ADC_RD);
   //       nib1 = (nib1Mask&ADC_RD);
   //       if (nib1 < numRange) nib1 = nib1 + numOffset;
   //       else nib1 = nib1 + charOffset;
   //   
   //       nib2 = (nib2Mask&ADC_RD)>>shift4;
   //       if (nib2 < numRange) nib2 = nib2 + numOffset;
   //       else nib2 = nib2 + charOffset;
   //   
   //       nib3 = (nib3Mask&ADC_RD)>>shift8;
   //       nib3 = nib3 + numOffset;
   //   
   //       nib4 = RESET + numOffset;
   //   
   //       display_One="            ";
   //       display_One[char1]=nib4;
   //       display_One[char2]=nib3;
   //       display_One[char3]=nib2;
   //       display_One[char4]=nib1;
      }
   
   
   
   //-------------------------------------------------------
   //if (writeNext)
   //{
  
   //   if ((UCTXIFG))
   //   {
   //     timeOut = RESET;
   //     
   //     //
   //     //
   //     UCA1TXBUF = toWrite;
   //   
   //     newFM(HUNDRED_MIL);
   //     if (usb_rx_ring_wr == RESET)
   //     {
   //       dontWrite = START;
   //       break;
   //     }
   //
   //   
   //     while (START)
   //     {
   //       newFM(START);
   //       test1 = usb_rx_ring_wr;
   //       test2 = usb_rx_ring_rd;
   //       if (test1 != test2) break;
   //     }
   //   
   //     usb_rx_ring_rd++;
   //     test = USB_Char_Rx[usb_rx_ring_wr];
   //   
   //     serial[char1-1+j]=test;
   //     }
   //
   // lcd_clear();
   // if (!dontWrite) lcd_out(serial, LCD_LINE_1);
   // else dontWrite = RESET;
   // //else dontWrite = 0;
   // usb_rx_ring_wr = RESET;
   // usb_rx_ring_rd = RESET;
   // usb_tx_ring_wr = RESET;
   // usb_tx_ring_rd = RESET;
   // 
   // if (i >= 100) writeNext = 0;
   //}
   //}
 }
}
