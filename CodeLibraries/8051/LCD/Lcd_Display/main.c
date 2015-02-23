/*-----------------------------------------------------------------------------
         Program to demonstrate displaying of message on LCD
  -----------------------------------------------------------------------------
  note:
  Refer lcd.h file for Pin connections
------------------------------------------------------------------------------*/ 

#include "lcd.h"	//User defined LCD library which contains the lcd routines
#include "delay.h" //User defined library which contains the delay routines


/* start the main program */
void main() 
{

  /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);

  /* Display "hello, world" on first line*/
  LCD_DisplayString("hello, world");

  /*Go to second line and display "good morning" */
  LCD_GoToNextLine();
  LCD_DisplayString("good morning");


  while(1);

  }