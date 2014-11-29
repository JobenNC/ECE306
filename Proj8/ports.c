//===========================================================================
// File Name : ports.c
//
// Description: This file contains the Initialization for all port pins
//      All bit masks are #defined in "macros.h"
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: No globals defined in this file
// Functions: Init_Ports, Init_Ports1, Init_Ports2, Init_Ports3, Init_Ports2,
//      Init_PortsJ
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

void Init_Ports1(void)
//===========================================================================
// Function name: Init_Ports1
//
// Description: Init all pins on port 1
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no globals modified
// Calls: none
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR1 capture: CCI1A input
// 0 1 1 - TA0 CCR1 compare: Out1
// 1 0 0 - External DMA trigger
// 1 0 1 - RTC clock calibration output
// 1 1 X - Analog input A0 - ADC, Comparator_D input CD0, Vref- External applied reference
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR2 capture: CCI2A input,
// 0 1 1 - TA0 CCR2 compare: Out2
// 1 0 0 - TA1 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A1 - ADC, Comparator_D input CD1, Input for an external reference voltage to the ADC
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR1 capture: CCI1A input
// 0 1 1 - TA1 CCR1 compare: Out1
// 1 0 0 - TA0 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A2 - ADC, Comparator_D input CD2
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR2 capture: CCI2A input
// 0 1 1 - TA1 CCR2 compare: Out2
// 1 0 X - Slave transmit enable - eUSCI_B0 SPI mode
// 1 1 X - Analog input A3 - ADC, Comparator_D input CD3
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCR1 capture: CCI1A input
// 0 1 1 - TB0 CCR1 compare: Out1
// 1 0 X - Slave transmit enable - eUSCI_A0 SPI mode
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCl2A
// 0 1 1 - TB0.2
// 1 0 X - UCA0CLK
// 1 1 X - A5/CD5
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1.CCl1A
// 0 1 1 - TB1.1
// 1 0 X - UCB0SIM0
// 1 1 0 - TA0.CCI0A
// 1 1 1 - TA0.0
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1.CCI2A
// 0 1 1 - TB1.2
// 1 0 X - UCB0SOMI
// 1 1 0 - TA1.CCI0A
// 1 1 1 - TA1.0
//
// Pins:
// P10 - V Detect Right
//      - ADC, Out=0
// P11 - V Detect Left
//      - ADC, Out=0
// P12 - IR LED
//      - Output, Out=0
// P13 - V Thumb
//      - ADC, Out=1
// P14 - SPI_CS_LCD
//      - Output, Out=1
// P15 - RESET LCD
//      - Output, Out=1
// P16 - SPI SIMO
//      - UCB0SIMO, Out=0
// P17 - RS LCD
//      - Output, Out=1
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version: (6.10.5)
//===========================================================================
{

 P1SELC = CLEAR_REG; // Default to I/0 
 P1DIR = DIR_INPUT; // Default to input
 
 P1SEL0 |= V_DETECT_R; // 1 V_DETECT_R selected
 P1SEL1 |= V_DETECT_R; // 1 V_DETECT_R selected
 
 P1SEL0 |= V_DETECT_L; // 1 V_DETECT_L selected
 P1SEL1 |= V_DETECT_L; // 1 V_DETECT_L selected
 
 P1SEL0 &= ~SPI_SIMO; // 0 SIMO_B selected
 P1SEL1 |= SPI_SIMO; // 1 SIMO_B selected
// P1SEL0 &= ~SOMI_B; // 0 SOMI_B is unused on the LCD
// P1SEL1 |= SOMI_B; // 1 SOMI_B is unused on the LCD
 
 P1OUT &= ~IR_LED; // 0 P1 IR_LED Port Pin set low
 P1DIR |= IR_LED; // 1 Set P1 IR_LED direction to output
 P1OUT |= IR_LED;

 P1SEL0 |= V_THUMB; // 1 V_THUMB selected
 P1SEL1 |= V_THUMB; // 1 V_THUMB selected
 
 P1OUT |= SPI_CS_LCD; // 1 P1 SPI_CS_LCD Port Pin set high
 P1DIR |= SPI_CS_LCD; // 1 Set SPI_CS_LCD output direction
 P1REN |= SPI_CS_LCD; // 1 Enable pullup resistor
 
 P1OUT &= ~RESET_LCD; // 0 P1 SPI_CS_LCD Port Pin set low
 P1DIR |= RESET_LCD; // 1 Set RESET_LCD output direction
 P1REN |= RESET_LCD; // 1 Enable pullup resistor
 
// P1DIR &= ~SOMI_B; // SOMI_B is unused on the LCD
 P1DIR |= SPI_SIMO; // 1 SIMO_B set to Output
 P1REN |= SPI_SIMO; // 1 Enable pullup resistor
 
 P1OUT |= RS_LCD; // 1 P1 RS_LCD Port Pin set high
 P1DIR |= RS_LCD; // 1 Set RS_LCD output direction
 P1REN |= RS_LCD; // 1 Enable pullup resistor
}

void Init_Ports2(void)
//===========================================================================
// Function name: Init_Ports2
//
// Description: Init all pins on port 2
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no globals modified
// Calls: none
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCI0A
// 0 1 1 - TB2.0
// 1 0 X - UCA0TXD
// 1 1 0 - TB0CLK
// 1 1 1 - ACLK
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCl1A,
// 0 1 1 - TB2.1
// 1 0 X - UCA0RXD
// 1 1 0 - TB0.CC10A
// 1 1 1 - TB0.0
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCl2A
// 0 1 1 - TB2.2
// 1 0 X - UCB0CLK
// 1 1 0 - TB1.CCl0A
// 1 1 1 - TB1.0
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0.CCl0B
// 0 1 1 - TA0.0
// 1 0 X - UCA1STE
// 1 1 X - A6/CD10
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1.CCl0B
// 0 1 1 - TA1.0
// 1 0 X - UCA1CLK
// 1 1 X - A6/CD11
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0.CCIOB
// 0 1 1 - TB0.0
// 1 0 X - UCA1TXD
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1.CCl0B
// 0 1 1 - TB1.0
// 1 0 X - UCA1RXD
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Pins:
// P20 - USB TXD
//      - UCA0TXD, Out=0
// P21 - USB RXD
//      - UCA0RXD, Out=0
// P22 - SPI_SCK
//      - UCB0CLK, Out=0
// P23 - Unused
//      - Input, no pull up/down
// P24 - Unused
//      - Input, no pull up/down
// P25 - CPU TXD
//      - UCA1TXD, Out=0
// P26 - CPU RXD
//      - UCA1RXD, Out=0
// P27 - Unknown
//      - Input, no pull up/down
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version: (6.10.5)
//===========================================================================
{
 P2SELC = CLEAR_REG; // Default to I/0 
 P2DIR = DIR_INPUT; // Default to input
 
 P2SEL1 |= USB_TXD;
 P2SEL0 &= ~USB_TXD;
 //P2DIR
 P2OUT &= ~USB_TXD;
 
 P2SEL1 |= USB_RXD;
 P2SEL0 &= ~USB_RXD;
 //P2DIR
 P2OUT &= ~USB_RXD;
 
 P2SEL1 |= SPI_SCK;
 P2SEL0 &= ~SPI_SCK;
 //P2DIR
 P2OUT |= SPI_SCK;
 P2REN |= SPI_SCK;
 
 P2DIR &= ~P_2_3;
 
 P2DIR &= ~P_2_4;

P2SEL1 |= CPU_TXD;
P2SEL0 &= ~CPU_TXD;
//P2DIR
P2OUT &= ~CPU_TXD;

P2SEL1 |= CPU_RXD;
P2SEL0 &= ~CPU_RXD;
//P2DIR
P2OUT &= ~CPU_RXD;

P2DIR &= ~P_2_7;
}

void Init_Ports3(void)
//===========================================================================
// Function name: Init_Ports3
//
// Description: Init all pins on port 3
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no globals modified
// Calls: none
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - A12/CD12
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - A13/CD13
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - A14/CD14
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 1 1 X - A15/CD15
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1.CCl1B
// 0 1 1 - TB1.1
// 1 1 0 - TB2CLK
// 1 1 1 - SMCLK
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1.CCl2B
// 0 1 1 - TB1.2
// 1 1 1 - CDOUT
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCl1B
// 0 1 1 - TB2.1
// 1 1 0 - TB1CLK
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCl2B
// 0 1 1 - TB2.2
//
// Pins:
// P30 - Var X
//      - Input, no pull-up/down res
// P31 - Var Y
//      - Input, no pull-up/down resistor
// P32 - Var Z
//      - Input, no pull-up/down resistor
// P33 - LED_BACKLITE
//      - Output, Initialized to 1
// P34 - R Forward
//      - Output, Initialzied to 0
// P35 - R Reverse
//      - Output, Initialized to 0
// P36 - L Forward
//      - Output, Initialized to 0
// P37 - L Reverse
//      - Output, Initialized to 0
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version: (6.10.5)
//===========================================================================
{
 P3SELC = CLEAR_REG; // Default to I/0 
 P3DIR = DIR_INPUT; // Default to input
 
 P3OUT &= ~VAR_X;
 P3OUT &= ~VAR_Y;
 P3OUT &= ~VAR_Z;
 
 P3DIR |= LCD_BACKLITE;
 P3OUT |= LCD_BACKLITE;
 
 P3DIR |= R_FORWARD;
 P3OUT &= ~R_FORWARD;
 
 P3DIR |= R_REVERSE;
 P3OUT &= ~R_REVERSE;
 
 P3DIR |= L_FORWARD;
 P3OUT &= ~L_FORWARD;
 
 P3DIR |= L_REVERSE;
 P3OUT &= ~L_REVERSE; 
}

void Init_Ports4(void)
{
//===========================================================================
// Function name: Init_Ports4
//
// Description: Init all pins on port 4
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no globals modified
// Calls: none
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB2.CCI0B
// 0 1 1 - TB2.0
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
//
// Pins:
// P40 - Switch 1
//      - Input, pull-up resistor
// P41 - Switch 2
//      - Input, pull-up resistor
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version: (6.10.5)
//===========================================================================
 P4SELC = CLEAR_REG; // Default all to I/0 
 P4DIR = DIR_INPUT; // Default all to input
 
 //Init switch 1
 P4DIR &= ~SW1;
 P4OUT |= SW1;
 P4REN |= SW1;
 
 //Init switch 2
 P4DIR &= ~SW2;
 P4OUT |= SW2;
 P4REN |= SW2;
 
 // Configure the interrupt
 P4IES |= SW1; // P4.0 Hi/Lo edge interrupt
 P4IES |= SW2; // P4.0 Hi/Lo edge interrupt
 P4IFG &= ~SW1; // P4 IFG SW1 cleared
 P4IFG &= ~SW2; // P4 IFG SW2 cleared
// Start / Enable Interrupt 
 P4IE |= SW1; // P4.0 SW1 interrupt Enabled
 P4IE |= SW2; // P4.0 SW2 interrupt enabled

}

void Init_PortsJ(void)
//===========================================================================
// Function name: Init_PortsJ
//
// Description: Init all pins on port J
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no globals modified
// Calls: none
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR1 capture: CCI1A input
// 0 1 1 - TA0 CCR1 compare: Out1
// 1 0 0 - External DMA trigger
// 1 0 1 - RTC clock calibration output
// 1 1 X - Analog input A0 - ADC, Comparator_D input CD0, Vref- External applied reference
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR2 capture: CCI2A input,
// 0 1 1 - TA0 CCR2 compare: Out2
// 1 0 0 - TA1 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A1 - ADC, Comparator_D input CD1, Input for an external reference voltage to 
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR1 capture: CCI1A input
// 0 1 1 - TA1 CCR1 compare: Out1
// 1 0 0 - TA0 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A2 - ADC, Comparator_D input CD2
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR2 capture: CCI2A input
// 0 1 1 - TA1 CCR2 compare: Out2
// 1 0 X - Slave transmit enable - eUSCI_B0 SPI mode
// 1 1 X - Analog input A3 - ADC, Comparator_D input CD3
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCR1 capture: CCI1A input
// 0 1 1 - TB0 CCR1 compare: Out1
// 1 0 X - Slave transmit enable - eUSCI_A0 SPI mode
//
// Pins:
// PJ0 - GPS Power
//      - Output, initially 0
// PJ1 - GPS Reset
//      - Output, initially 0
// PJ2 - GPS Power Control
//      - Output, initially 0
// PJ3 GPS Power Check
//      - Input, no pull up/down Res
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version: (6.10.5)
//===========================================================================
{
 PJSELC = CLEAR_REG; // Default to I/0 
 PJDIR = DIR_INPUT; // Default to input

 PJDIR |= GPS_PWR; //Select GPS Power
 PJOUT &= ~GPS_PWR;
 
 PJDIR |= GPS_RESET; //Select GPS Reset
 PJOUT &= ~GPS_RESET;
 
 PJDIR |= GPS_PWRCNTL; //Select GPS Power Control
 PJOUT &= ~GPS_PWRCNTL;
 
 PJDIR &= ~GPS_PWRCHK; //Select GPS Power Check
 PJREN &= ~GPS_PWRCHK;
 
 //Will go to init_ADC
 //ADC10CTL0 = RESET_STATE; // Clear ADC10CTL0 
 ADC10CTL0 = 0x00; // Clear ADC10CTL0 
 ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
 ADC10CTL0 &= ~ADC10MSC; // Single Sequence
 ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
 //ADC10CTL1 = RESET_STATE; // Clear ADC10CTL1 
 ADC10CTL1 = 0x00; // Clear ADC10CTL1 
 ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
 ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
 ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
 ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
 ADC10CTL1 |= ADC10SSEL_0; // MODCLK
 ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
 //ADC10CTL1 |= 1; // sequence-of-channels, single-conversion
 //ADC10CTL2 = RESET_STATE; // Clear ADC10CTL2
 ADC10CTL2 = 0x00; // Clear ADC10CTL2 
 ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
 ADC10CTL2 |= ADC10RES; // 10-bit resolution
 ADC10CTL2 &= ~ADC10DF; // Binary unsigned
 ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
 
 
 //ADC10MCTL0 = RESET_STATE; // Clear ADC10MCTL0
 ADC10MCTL0 = 0x00; // Clear ADC10MCTL0 
 ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
 
 //ADC10MCTL0 |= ADC10INCH_0; // Channel A1
 //ADC10MCTL0 |= ADC10INCH_1; // Channel A2
 ADC10MCTL0 |= ADC10INCH_0; // Channel A3 Thumb Wheel 

 ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}

// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal

volatile unsigned int ADC_Thumb = -1;
volatile unsigned int ADC_RD = -1;
volatile unsigned int ADC_LD = -1;
volatile unsigned int chan = 1;

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
 switch(__even_in_range(ADC10IV,12)) {
 case 0: break; // No interrupt
 case 2: break; // conversion result overflow
 case 4: break; // conversion time overflow
 case 6: break; // ADC10HI
 case 8: break; // ADC10LO
 case 10: break; // ADC10IN
 case 12: 
    //ADC_Thumb = ADC10MEM0; // Channel A3
    
    
    switch(chan)
    {
    case 0: 
      ADC_Thumb = ADC10MEM0;
      
      ADC10CTL0 &= ~ADC10ENC;
      ADC10CTL0 &= ~ADC10SC;
      ADC10MCTL0 &= ~ADC10INCH_3;
      ADC10MCTL0 |= ADC10INCH_0;
      ADC10CTL0 |= ADC10ENC;
      ADC10CTL0 |= ADC10SC;
      chan++;
      break;
    case 1: 
      ADC_LD = ADC10MEM0;
      
      ADC10CTL0 &= ~ADC10ENC;
      ADC10CTL0 &= ~ADC10SC;
      ADC10MCTL0 &= ~ADC10INCH_0;
      ADC10MCTL0 |= ADC10INCH_1;
      ADC10CTL0 |= ADC10ENC;
      ADC10CTL0 |= ADC10SC;
      chan++;
      break;
    case 2: 
      ADC_RD = ADC10MEM0;
      
      ADC10CTL0 &= ~ADC10ENC;
      ADC10CTL0 &= ~ADC10SC;
      ADC10MCTL0 &= ~ADC10INCH_1;
      ADC10MCTL0 |= ADC10INCH_3;
      ADC10CTL0 |= ADC10ENC;
      ADC10CTL0 |= ADC10SC;
      chan=0;
      break;
    default: break;
    }
    break; 
 default: break; 
 } 
}

//chan 1 is R det
//chan 2 is L det

void ADC_Process(void){
 while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
    ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
    //chan = chan;
    //newFM(100);
}

void Init_Ports(void)
//===========================================================================
// Function name: Init_Ports
//
// Description: Call init functions for each port
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
// Calls: void Init_Ports1(void), void Init_Ports2(void), void Init_Ports3(void)
// void Init_Ports4(void), void Init_PortsJ(void)
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version: (6.10.5)
//===========================================================================
{
 
 Init_Ports1();
 Init_Ports2();
 Init_Ports3();
 Init_Ports4();
 Init_PortsJ();
 
}
