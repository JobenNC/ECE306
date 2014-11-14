//===========================================================================
// File Name : menus.c
//
// Description: Menu Functions
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

int i;

char* song = "           We're the Red and White from State And we know we are the best. A hand behind our back, We can take on all the rest. Come over the hill, Carolina. Devils and Deacs stand in line. The Red and White from N.C. State. Go State!";
//char* song = "abcdefghijklmnopqrstuvwxyz";
char* red = "red";
char* white = "white";
int rw = 0;
char* msg ="               ";
//char *res1[3] = {"0", "middle", "end"};
char *res1 = "Color Value";
char *res2[10] = {"Black  0", "Brown   1", "Red   2", "Orange   3", "Yellow   4", "Green   5", "Blue   6", "Violet   7", "Gray    8", "White     9"};

char *shape1[10] = {"Circle", "Square", "Triangle", "Octagon", "Pentagon", "Hexagon", "Cube", "Oval", "Sphere", "Cylinder"};
char *shape2[10] = {"Square", "Triangle", "Octagon", "Pentagon", "Hexagon", "Cube", "Oval", "Sphere", "Cylinder", "End"};

int index = 0;

void displayRes()
{
  int item = ADC_Thumb;
  i = item/100;
  if (i==10) i = 9;
  lcd_clear();
  lcd_out(res1, LCD_LINE_1);
  lcd_out(res2[i], LCD_LINE_2);
}

void displayShape()
{
  int item = ADC_Thumb;
  i = item/100;
  if (i==10) i = 9;
  lcd_clear();
  lcd_out(shape1[i], LCD_LINE_1);
  lcd_out(shape2[i], LCD_LINE_2);
}  
 
void displaySong()
{
  int item = ADC_Thumb;
  
  
  if ((item)>(lastItem+10))
  {
    if (index > 233) index = 0;
    //else index++;
    msg[2] = song[index];
    msg[3] = song[index+1];
    msg[4] = song[index+2];
    msg[5] = song[index+3];
    msg[6] = song[index+4];
    msg[7] = song[index+5];
    msg[8] = song[index+6];
    msg[9] = song[index+7];
    msg[10] = song[index+8];
    msg[11] = song[index+9];
    msg[12] = song[index+10];
    index++;
    lcd_clear();
    lcd_out(msg, LCD_LINE_1);
    
    if (!rw) lcd_out(red, LCD_LINE_2);
    else lcd_out(white, LCD_LINE_2);
    rw = ~rw;
  }
  lastItem = item;
}