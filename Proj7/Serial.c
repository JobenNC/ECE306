//===========================================================================
// File Name : Serial.c
//
// Description: Serial communication functions
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: buffers and sizes
// Functions: None
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

int SMALL_RING_SIZE = SMALL_RING;
int LARGE_RING_SIZE = LARGE_RING;
int BEGINNING = RESET;

//extern volatile char USB_Char_Tx[8] = {RESET};
//extern volatile char USB_Char_Rx[16] = {RESET};

extern volatile char USB_Char_Tx[SMALL_RING] = {RESET};
extern volatile char USB_Char_Rx[SMALL_RING] = {RESET};

extern volatile int usb_tx_ring_wr = RESET;
extern volatile int usb_tx_ring_rd = RESET;

extern volatile int usb_rx_ring_wr = RESET;
extern volatile int usb_rx_ring_rd = RESET;

//----------------------------------------------------------------------------
void Init_Serial_UCA1(void){
 int i;
 
 for(i=RESET; i<SMALL_RING_SIZE; i++){
 USB_Char_Rx[i] = CLEAR_REG;// USB Character
 }
 usb_rx_ring_wr = -START;
 usb_rx_ring_rd = -START;
 
 for(i=RESET; i<LARGE_RING_SIZE; i++){
 USB_Char_Tx[i] = CLEAR_REG;// USB Character
 }
 usb_tx_ring_wr = RESET;
 usb_tx_ring_rd = RESET;
 // Configure UART 0
 UCA1CTLW0 = RESET; // Use word register
 UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA1CTLW0 |= UCSWRST; // Set Software reset enable
 // 9,600 Baud Rate
// 1. Calculate N = fBRCLK/Baudrate [if N > 16 continue with step 3, otherwise with step 2]
// N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
// 2. OS16 = 0, UCBRx = INT(N) [continue with step 4]
// 3. OS16 = 1, UCx = INT(N/16), UCFx = INT([(N/16) – INT(N/16)] × 16)
// UCx = INT(N/16) = 833.333/16 => 52
// UCFx = INT([(N/16) – INT(N/16)] × 16) = ([833.333/16-INT(833.333/16)]*16) => 
// (52.08333333-52)*16=>0.083*16=1
// 4. UCSx can be found by looking up the fractional part of N ( = N - INT(N) ) in Table 18-4
// Decicmal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x25
// 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// UCA1BRW = 52 ; // 9,600 baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16; 
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1; 
// UCA1MCTLW = 0x4911 ; 
 
 UCA1BRW = BRW; // 4800 baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16; 
// UCA0MCTLW = 0x-- concatenate - concatenate -; 
 UCA1MCTLW = CTLW ; 
 
 UCA1CTL1 &= ~UCSWRST; // Release from reset
 UCA1IE |= UCRXIE; // Enable RX interrupt
}

//------------------------------------------------------------------------------
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  //===========================================================================
// ISR name: UARTA1 interrupt
//
// Description: This ISR handles UARTA1
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
 unsigned int temp;
 switch(__even_in_range(UCA1IV,UCA_RANGE)){
 case RESET: // Vector 0 - no interrupt
 break;
 case SECOND: // Vector 2 - RXIFG
 temp = ++usb_rx_ring_wr;
 
 //for prev proj
 //if (temp % SECOND) readyToReceive = START;
 //else readyToReceive = RESET;
 
 USB_Char_Rx[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
 if (usb_rx_ring_wr > (7)){
    //usb_rx_ring_wr = RESET; // Circular buffer back to beginning
   usb_rx_ring_wr = -1;
 }

 break;
 case FOURTH: // Vector 4 – TXIFG
   //write to UCAxTXBUF x=0
   
 break;
 default: break; 
 }
}
//------------------------------------------------------------------------------