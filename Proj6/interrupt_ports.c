//===========================================================================
// File Name : functions.h
//
// Description: function declarations
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: None
// Functions: None defined
//===========================================================================

#include  "functions.h"
#include "macros.h"
#include  "msp430.h"

volatile unsigned int isDebounce;
volatile unsigned int bounceCount;
volatile unsigned int switchPress;

volatile unsigned int drive = RESET;

volatile unsigned int LED_White_LD;
volatile unsigned int LED_Black_LD;
volatile unsigned int LED_White_RD;
volatile unsigned int LED_Black_RD;
volatile unsigned int LED_Off_RD;
volatile unsigned int LED_Off_LD;

volatile unsigned int butt1 = BEFORE_START;
volatile unsigned int butt2 = RESET;

extern volatile unsigned int starting = RESET;

char nib1;
char nib2;
char nib3;
char nib4;

char* outP;

char *display_One;


#pragma vector=PORT4_VECTOR

__interrupt void switch_interrupt(void) {
//===========================================================================
// ISR name: switch_interrupt
//
// Description: This ISR handles switch events
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: switchPress, isDebounce, bounceCount
// Calls: lcd_out, lcd_clear
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
// Switch 1 
 if (P4IFG & SW1) {
    Init_Serial_UCA1();
    writeNext = START;
   //lcd_clear();
   //lcd_out("    Switch 1", LCD_LINE_1);
// Set a variable to identify the switch has been pressed.
   switchPress = START;
// Set a variable to identify the switch is being debounced.
   isDebounce = START;
// Reset the count required of the debounce.
   bounceCount = RESET;
// Disable the Switch Interrupt.
   P4IE &= ~SW1; // P4.0 SW1 interrupt Disabled
   P4IE &= ~SW2; // P4.0 SW2 interrupt Disabled
// Clear any current timer interrupt.
   P4IFG &= ~SW1; // P4 IFG SW1 cleared
   P4IFG &= ~SW2; // P4 IFG SW2 cleared
   PJOUT |= LED1; // Toggle LED 1 on to indicate boot ISR working
   
   //-----Setup up first fake receive
   ++usb_rx_ring_wr;
   USB_Char_Rx[0] = (char) 0;
 }
// Switch 2 
 if (P4IFG & SW2) {

   lcd_clear();
// t a variable to identify the switch has been pressed.
   switchPress = START;
// Set a variable to identify the switch is being debounced.
   isDebounce = START;
// Reset the count required of the debounce.
   bounceCount = RESET;
// Disable the Switch Interrupt.
   P4IE &= ~SW2; // P4.0 SW2 interrupt Disabled
   P4IE &= ~SW1; // P4.0 SW1 interrupt Disabled
// Clear any current timer interrupt.
   P4IFG &= ~SW2; // P4 IFG SW2 cleared
   P4IFG &= ~SW1; // P4 IFG SW1 cleared
   PJOUT |= LED1; // Toggle LED 1 on to indicate boot ISR working
 }
// Enable the Timer Interrupt for the debounce.
}
