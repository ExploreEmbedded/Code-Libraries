/*
 * Lcd_Display.c : Program to demonstrate displaying of message on LCD
 *
 * Created: 11/6/2012 8:25:05 PM
 *  Author: exploreembedded
 * note: Refer lcd.h file for Pin connections
 */ 




#include "lcd.h"	//User defined LCD library which conatins the lcd routines


/* start the main program */
void main() 
{

  /* Initialize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);

  /* Display "hello, world" on first line*/
  LCD_DisplayString("hello, world");

  /*Go to second line and display "good morning" */
  LCD_GoToLine(2);
  LCD_DisplayString("good morning");


  while(1);

  }