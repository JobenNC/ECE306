//===========================================================================
// File Name : gps.c
//
// Description: gps functions
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

//pin 6 high, gps is on!

char *display_line1 = "    ";
char *display_line2 = "    ";

void GPS_Init()
{
  // GPS Initialization
 //time_pass_by = 0;
 PJOUT &= ~GPS_RESET; // GPS_RESET = GPS in Reset;
 //time_pass_by = 0;
 //while (time_pass_by <= 200);
 newFM(200);
 //time_pass_by = 0;
 PJOUT |= GPS_RESET; // GPS_RESET = GPS NOT Reset;
 newFM(200);
 //while (time_pass_by <= 200);
 //PJOUT &= ~GPS_PWRCNTL;
 newFM(20);
 PJOUT |= GPS_PWRCNTL;
 newFM(40);
 if (PJIN & GPS_PWRCHK) 
 {
   PJOUT &= ~GPS_PWRCNTL;
 }
 
 //PJOUT |= GPS_PWRCNTL;
 //newFM(210);
 //PJOUT &= ~GPS_PWRCNTL;
 
 //I commented this out
 return;
 gps_wakeup();
 while(!(PJIN & GPS_PWRCHK)){
    if (!(PJIN & GPS_PWRCHK)){
        newFM(210);
        //while (time_pass_by <= 210);
        gps_wakeup();
    }
 }
 lcd_clear();
 lcd_out("GPS_UP", LCD_LINE_1);
}

void gps_wakeup(void){
 int kick_out = 1;
 //time_pass_by = 0;
 //while (time_pass_by <= 10);
 newFM(10);
 PJOUT |= GPS_PWRCNTL; // GPS_PWRCNTL = GPS_ON;
 //time_pass_by = 0;
 newFM(20);
 //while ((time_pass_by <= 20) & kick_out){
 
 //this is where carlson set trace to show me working gps
 while (kick_out){
    if (PJIN & GPS_PWRCHK){
        kick_out = 0;
    }
 }
 //commented this out to get this working!
 PJOUT &= ~GPS_PWRCNTL; // GPS_PWRCNTL = GPS_Off;
 //gps_out_once();
}

void gps_out_once(void){
 display_line1[0] = 'L';
 display_line1[1] = 'A';
 display_line1[2] = 'T';
 display_line1[3] = ' ';
 display_line2[0] = 'L';
 display_line2[1] = 'O';
 display_line2[2] = 'N';
 display_line2[3] = ' ';
 lcd_clear();
 newFM(50);
 lcd_out(display_line1,LCD_LINE_1); // 16 characters max between quotes - line 1
 newFM(50);
 lcd_out(display_line2,LCD_LINE_2); // 16 characters max between quotes - line 2
}