//===========================================================================
// File Name : interrupts_timers.c
//
// Description: timer interrupts
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: None
// Functions: Timer0_A0_ISR
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

int lcdCount = RESET;
int incr = 0;

volatile unsigned int fMCount = RESET;
volatile unsigned int timerCount = 0;
//******************************************************************************
//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler 
#pragma vector = TIMER0_A0_VECTOR 
__interrupt void Timer0_A0_ISR(void){
//===========================================================================
// ISR name: Timer0_A0_ISR
//
// Description: This ISR handles the A0 timer
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: fMCount, TA0CCR0
// Calls: void Init_Timer_B2(void)
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
 
 //if (count > 500)
 //{
 //   P3OUT ^= LCD_BACKLITE;
 //   count = 0;
 //}
 //else
 //{
 //   count++;
 //}
 
 //P3DIR |= LCD_BACKLITE; 
 fMCount = ~fMCount;
 incr++;
 slowDrive = 0;
 if (incr == 5) 
 {
   slowDrive = 1;
   incr = 0;
 }
 
 //if (lcdCount < lcdCountFin) lcdCount++;
 //else
 //{
 //  P3OUT ^= LCD_BACKLITE;
 //  lcdCount = RESET;
 //}
 
 if (isDebounce)
 {
   if (bounceCount > bounceCountFin)
   {
     //Clear
     P4IFG &= ~SW1; // P4 IFG SW1 cleared
     P4IFG &= ~SW2; // P4 IFG SW2 cleared
     // Start / Enable Interrupt 
     P4IE |= SW1; // P4.0 SW1 interrupt Enabled
     P4IE |= SW2; // P4.0 SW2 interrupt enabled
     
     isDebounce = RESET;
     bounceCount = RESET;
     
     //lcd_clear();
     //lcd_out("    Done Debouncing", LCD_LINE_1);
     
     PJOUT &= ~LED1; // Turn off debounce LED
   }
   else
   {
     bounceCount++;
   }
 }
 
 if (startTimer) timerCount++;
 TA0CCR0 += FIVE_MSEC_OFFSET; // Add Offset to TACCR0 
} 
//------------------------------------------------------------------------------
/*
//------------------------------------------------------------------------------
// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
 switch(__even_in_range(TA0IV,14)){
 case 0: break; // No interrupt
 case 2: // CCR1 not used
// Put code here for CCR1 
 TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
 break;
 case 4: // CCR2 not used
// Put code here for CCR2 
 TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
 break;
 case 6: break; // reserved
 case 8: break; // reserved
 case 10: break; // reserved
 case 12: break; // reserved
 case 14: // overflow
// Put code here for overflow
 break;
 default: break; 
 }
}
//------------------------------------------------------------------------------
*/
//*************************************************************