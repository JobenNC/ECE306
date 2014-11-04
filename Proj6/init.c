//===========================================================================
// File Name : init.c
//
// Description: Set up initial conditions
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: No globals defined in this file
// Functions: Init_Conditions
//===========================================================================

#include  "functions.h"
#include "macros.h"

void Init_Conditions(void){
//===========================================================================
// Function name: Init_Conditions
//
// Description: Set up intiial conditions
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: None
// Calls: enable_interrupts
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench Version (6.10.5)
// ==========================================================================
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them. 
  enable_interrupts();

//------------------------------------------------------------------------------
}