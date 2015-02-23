/*-----------------------------------------------------------------------------
         Program to demonstrate displaying of 5-digit LCD_Connter
  -----------------------------------------------------------------------------
  note:
  Refer lcd.c(lcd_4_bit.c/lcd_8_bit.c) file for Pin connections
------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 

#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "delay.h" //User defined library which conatins the delay routines


/* start the main program */
void main() 
{
   unsigned int counter=0;

  /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);

  /* Display "Lcd_Counter" on first line*/
    LCD_DisplayString("Lcd_Counter");

   /* Display the counter till 9999 */ 
   while(counter < 9999)
    {
        /*Go to second line and display counter value */
         LCD_GoToLine(2);
         LCD_DisplayDecimalNumber(counter,4);

		 /*Wait for 1sec after displaying the count */
		 DELAY_sec(1);
		 		 
		 /* Increment the counter till it reaches 9999*/
		 counter++;
	  }


  while(1);

  }