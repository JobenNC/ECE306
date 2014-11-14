#include "macros.h"

void Switches_Process(void){
//------------------------------------------------------------------------------
// Switch Configurations
//------------------------------------------------------------------------------
  if (!(P4IN & SW1)){
    PJOUT |= LED1;                   // Change State of LED 1
    PJOUT |= LED2;                   // Change State of LED 2
    PJOUT |= LED3;                   // Change State of LED 3
    PJOUT |= LED4;                   // Change State of LED 4
  }
  if (!(P4IN & SW2)) {
    P3OUT |= LED5;                   // Change State of LED 5
    P3OUT |= LED6;                   // Change State of LED 6
    P3OUT |= LED7;                   // Change State of LED 7
    P3OUT |= LED8;                   // Change State of LED 8
  }
}
