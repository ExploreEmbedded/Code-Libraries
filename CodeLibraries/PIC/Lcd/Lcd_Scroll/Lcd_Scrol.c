/*
 * Lcd_Scrol.c: Program to demonstrate scrolling of message on LCD
 *
 * Created: 11/6/2012 8:19:23 PM
 *  Author: exploreembedded
 *  note: Refer lcd.h file for Pin connections
 */ 




#include "lcd.h"	//User defined LCD library which contains the lcd routines



/* start the main program */
void main()
{
  char msg[]={"         hello world, welcome to PIC programming "};

/* Initialize the lcd before displaying any thing on the lcd */
LCD_Init(8,2,16);

while(1)
{
	/*scroll the message on line1 indefnitely*/
	LCD_ScrollMessage(1,msg);

	LCD_ScrollMessage(2,"          Enjoy embedded programming ");
	
}
}