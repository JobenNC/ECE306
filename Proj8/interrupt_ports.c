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

volatile unsigned int drive = 0;

volatile unsigned int LED_White_LD;
volatile unsigned int LED_Black_LD;
volatile unsigned int LED_White_RD;
volatile unsigned int LED_Black_RD;

volatile unsigned int butt1 = -1;
volatile unsigned int butt2 = 0;

volatile unsigned int turnAroundCount = 0;

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
   
   switch(butt1)
   {
     
    case -1:
      lcd_clear();
      lcd_out("    Calibrate", LCD_LINE_1);
      lcd_out("LED Black",LCD_LINE_2);
      butt1++;
      
    case 0:
      lcd_clear();
      lcd_out("    Calibrate", LCD_LINE_1);
      lcd_out("LED White",LCD_LINE_2);
      butt1++;
      //P1OUT |= IR_LED;
      break;
    case 1:
      lcd_clear();
      lcd_out("    Calibrate", LCD_LINE_1);
      lcd_out("LED Black",LCD_LINE_2);
      butt1++;
      //P1OUT &= ~IR_LED;
      break;
      
    case 2:
      lcd_clear();
      lcd_out("    Drive", LCD_LINE_1);
      butt1 = 0;
      break;
      
    default: break;
   }
 }
// Switch 2 
 if (P4IFG & SW2) {
   //lcd_clear();
   //lcd_out("    Switch 2", LCD_LINE_1);
// Set a variable to identify the switch has been pressed.
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
   
   switch(butt1)
   {
    case 1:
      
      switch(butt2)
      {
        case 0:
          
          LED_White_LD = ADC_LD;
      
          nib1 = (0x0F&ADC_LD);
          if (nib1 < 10) nib1 = nib1 + 48;
          else nib1 = nib1 + 55;
      
          nib2 = (0xF0&ADC_LD)>>4;
          if (nib2 < 10) nib2 = nib2 + 48;
          else nib2 = nib2 + 55;
      
          nib3 = (0xF00&ADC_LD)>>8;
          nib3 = nib3 + 48;
      
          nib4 = 0x00 + 48;
      
          display_One="            ";
          display_One[8]=nib4;
          display_One[9]=nib3;
          display_One[10]=nib2;
          display_One[11]=nib1;
      
          lcd_clear();
          lcd_out(display_One, LCD_LINE_1);
          lcd_out("Left Detector",LCD_LINE_2);
          butt2++;
          
          break;
          
        case 1:
          
          LED_White_RD = ADC_RD;
      
          nib1 = (0x0F&ADC_RD);
          if (nib1 < 10) nib1 = nib1 + 48;
          else nib1 = nib1 + 55;
      
          nib2 = (0xF0&ADC_RD)>>4;
          if (nib2 < 10) nib2 = nib2 + 48;
          else nib2 = nib2 + 55;
      
          nib3 = (0xF00&ADC_RD)>>8;
          nib3 = nib3 + 48;
      
          nib4 = 0x00 + 48;
      
          display_One="            ";
          display_One[8]=nib4;
          display_One[9]=nib3;
          display_One[10]=nib2;
          display_One[11]=nib1;
      
          lcd_clear();
          lcd_out(display_One, LCD_LINE_1);
          lcd_out("Right Detector",LCD_LINE_2);
          butt2 = 0;
          
          break;
          
        default: break;
      }
      
      break;
      
      case 2:
        
      //newFM(100);
      
      switch(butt2)
      {
        case 0:
          LED_Black_LD = ADC_LD;
      
          nib1 = (0x0F&ADC_LD);
          if (nib1 < 10) nib1 = nib1 + 48;
          else nib1 = nib1 + 55;
      
          nib2 = (0xF0&ADC_LD)>>4;
          if (nib2 < 10) nib2 = nib2 + 48;
          else nib2 = nib2 + 55;
      
          nib3 = (0xF00&ADC_LD)>>8;
          nib3 = nib3 + 48;
      
          nib4 = 0x00 + 48;
      
          display_One="            ";
          display_One[8]=nib4;
          display_One[9]=nib3;
          display_One[10]=nib2;
          display_One[11]=nib1;
      
          lcd_clear();
          lcd_out(display_One, LCD_LINE_1);
          lcd_out("Left Detector",LCD_LINE_2);
          butt2++;
          break;
          
        case 1:
          LED_Black_RD = ADC_RD;
      
          nib1 = (0x0F&ADC_RD);
          if (nib1 < 10) nib1 = nib1 + 48;
          else nib1 = nib1 + 55;
      
          nib2 = (0xF0&ADC_RD)>>4;
          if (nib2 < 10) nib2 = nib2 + 48;
          else nib2 = nib2 + 55;
      
          nib3 = (0xF00&ADC_RD)>>8;
          nib3 = nib3 + 48;
      
          nib4 = 0x00 + 48;
      
          display_One="            ";
          display_One[8]=nib4;
          display_One[9]=nib3;
          display_One[10]=nib2;
          display_One[11]=nib1;
      
          lcd_clear();
          lcd_out(display_One, LCD_LINE_1);
          lcd_out("Right Detector",LCD_LINE_2);
          butt2 = 0;
          break;
          
        default: break;
      }
      
      break;
      
   case 0:
     
     drive = 1; 
     turnAroundCount = 0;
     
     break;
      
    default: break;  
   }
   nib1 = nib1;
 }
// Enable the Timer Interrupt for the debounce.
}
