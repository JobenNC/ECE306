//******************************************************************************
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define LED1                 (0x01) // LED 1
#define BLINK_LED            (0x01) // Allow LED to Blink
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2
#define GPS_ONOFF            (0x08) //
#define USE_LED5             (0x40)  //
#define USE_SMCLK            (0x00)  //
#define USE_NFETS            (0xA0)  //
#define CLEAR_DISPLAY        (0x01)

#define CSLOCK               (0x01) // Any incorrect password locks registers

// Display Modes
#define ORIGINAL             (0x00) //

// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile char slow_input_down;
extern char display_line_1[17];
extern char display_line_2[17];
extern char *display_1;
extern char *display_2;
char led_smclk;
unsigned char display_mode;

//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
void main(void){
//  led_smclk = USE_LED5;
//  led_smclk = USE_SMCLK;
  led_smclk = USE_NFETS;
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();                        // Initialize Variables and Initial Conditions
  Init_Timers();                            // Initialize Timers
  five_msec_sleep(50);                      // 250 msec delay for the clock to settle
  Init_ADC();                               // Initialize Analog-to-Digital Converter
  Init_Serial_UCA0();                       // Initialize Serial Port for USB 
  Init_Serial_UCA1();                       // Initialize Serial Port for GPS
  Init_SPI_B0();                            // Initialize SPI Bus
  Init_LEDs();                              // Initialize LEDs
  Init_LCD();                               // Initialize LCD
  five_msec_sleep(75);                      // 375 msec delay for the clock to settle
  Init_Switches();                          // Initialize Switches

  lcd_command(CLEAR_DISPLAY);
// Place the contents of what you want on the display, in between the quotes
// Limited to 16 characters per line  
//
  five_msec_sleep(10); 
  display_mode = ORIGINAL;
  control_state[0] |= GPS_ONOFF;
  
  display_1 = "   N.C. State   ";
  display_2 = "ECE-306  HW Test";
//             1234567890123456
  Display_Process();                      // Update Display 
//------------------------------------------------------------------------------

// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
    if(slow_input_down){
      slow_input_down = 0;                  // No need to check for changes in commands
      menu();                               // Check for user commands
      Display_Process();                    // Update Display 
    }
    Switches_Process();                     // Check for switch state change 
    ADC_Process();                          // Update based on change in ADC variable
  }
}
//------------------------------------------------------------------------------
