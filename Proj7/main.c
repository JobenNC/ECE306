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

volatile char readyToReceive = START;
volatile char whichChar = RESET;
volatile char resetCount = RESET;

char writeOut = RESET;
char wroteFirst = RESET;
char gotBoth = RESET;

char *serial;
int counter = RESET;

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
   
   if (resetCount)
   {
     UCA1CTL1 &= ~UCSWRST; // Release from reset
     UCA1IE |= UCRXIE; // Enable RX interrup
     Init_Serial_UCA1();
     resetCount = RESET;
     ++usb_rx_ring_wr;
     ++usb_rx_ring_wr;
     USB_Char_Rx[RESET] = (char) CLEAR_REG;
     USB_Char_Rx[START] = (char) CLEAR_REG;
   }
   
   test1 = usb_rx_ring_wr;
   test2 = usb_rx_ring_rd;
   
   test = RESET;
   if ((test1 != test2) & (readyToReceive))
      {
        if ((UCTXIFG))
        {
          if (usb_rx_ring_rd > SIXTH)
          {
            usb_rx_ring_rd =RESET;
            
            if (!whichChar)
            {
              bit1 = USB_Char_Rx[EIGHTH]; //6
              //char1++;
            }
            else
            {
              bit2 = USB_Char_Rx[NINTH]; //7
              //char2++;
              gotBoth = START;
            }
            whichChar = !whichChar;
          }
          else
          {
            if (!whichChar)
            {
              test1 = usb_rx_ring_wr;
              bit1 = USB_Char_Rx[test1-START];
            }
            else
            {
              test2 = usb_rx_ring_wr;
              bit2 = USB_Char_Rx[test2];
              gotBoth = START;
            }
            whichChar = !whichChar;
            usb_rx_ring_rd++;
          }
          
          //---------------Write to LCD
          if (gotBoth)
          {
            lcd_clear();
            //newFM(HALF_SEC);
            test = (int) bit2<<EIGHTH;
            test = test | (int) bit1;
            
            testChar = (test/(numRange*numRange*numRange*numRange))%numRange+numOffset;
            serial[SEVENTH] = (char) testChar;
            testChar = (test/(numRange*numRange*numRange))%numRange + numOffset;
            serial[EIGHTH] = testChar;
            testChar = (test/(numRange*numRange))%numRange + numOffset;
            serial[NINTH] = testChar;
            testChar = (test/numRange)%numRange + numOffset;
            serial[numRange] = testChar;
            testChar = (test/START)%numRange + numOffset;
            serial[ELEVENTH] = testChar;
            lcd_out(serial, LCD_LINE_1);
            
            testChar = (test/START)%numRange + numOffset;
            test++;
            
            bit1 = (char) (test & full);
            bit2 = (char) (test>>EIGHTH);
            
            writeOut = START;
          
            newFM(ONE_SEC);
          
            //wroteFirst = 1;
            UCA1TXBUF = bit1;
            while (!UCTXIFG) {}
            UCA1TXBUF = bit2;
            while (!UCTXIFG) {}
            writeOut = RESET;
            gotBoth = RESET;
            //wroteFirst = 0;
        }
      }
}
}
}