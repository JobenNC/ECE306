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
unsigned int test;

char bit1;
char bit2;

char testChar;

volatile char readyToReceive = 1;

char whichChar = 0;
char writeOut = 0;
char wroteFirst = 0;
char gotBoth = 0;

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
   
   test1 = usb_rx_ring_wr;
   test2 = usb_rx_ring_rd;
   
   test = 0;
   if ((test1 != test2) & (readyToReceive))
      {
        if ((UCTXIFG))
        {
          if (usb_rx_ring_rd > 6)
          {
            usb_rx_ring_rd =0;
            
            if (!whichChar)
            {
              bit1 = USB_Char_Rx[6];
              //char1++;
            }
            else
            {
              bit2 = USB_Char_Rx[7];
              //char2++;
              gotBoth = 1;
            }
            whichChar = !whichChar;
          }
          else
          {
            if (!whichChar)
            {
              test1 = usb_rx_ring_wr;
              bit1 = USB_Char_Rx[test1-1];
            }
            else
            {
              test2 = usb_rx_ring_wr;
              bit2 = USB_Char_Rx[test2];
              gotBoth = 1;
            }
            whichChar = !whichChar;
            usb_rx_ring_rd++;
          }
          
          //---------------Write to LCD
          if (gotBoth)
          {
            lcd_clear();
            test = (int) bit2<<8;
            test = test | (int) bit1;
            
            if (test==255)
            {
              driving = 1;
            }
            
            testChar = (test/10000)%10+48;
            serial[7] = (char) testChar;
            testChar = (test/1000)%10 + 48;
            serial[8] = testChar;
            testChar = (test/100)%10 + 48;
            serial[9] = testChar;
            testChar = (test/10)%10 + 48;
            serial[10] = testChar;
            testChar = (test/1)%10 + 48;
            serial[11] = testChar;
            lcd_out(serial, LCD_LINE_1);
            
            testChar = (test/1)%10 + 48;
            test++;
            
            bit1 = (char) (test & 0xFF);
            bit2 = (char) (test>>8);
            
            writeOut = 1;
          
            newFM(60);
          
            //wroteFirst = 1;
            UCA1TXBUF = bit1;
            while (!UCTXIFG) {}
            UCA1TXBUF = bit2;
            while (!UCTXIFG) {}
            writeOut = 0;
            gotBoth = 0;
            //wroteFirst = 0;
        }
      }
}
}
}