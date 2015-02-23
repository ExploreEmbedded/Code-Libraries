/*-----------------------------------------------------------------------------
         Program to demonstrate scrolling of message on LCD
  -----------------------------------------------------------------------------
  note:
  Refer lcd.h file for Pin connections
------------------------------------------------------------------------------*/


#include "lcd.h"	//User defined LCD library which conatins the lcd routines



/* start the main program */
void main() 
{
   	code char msg[]={"         hello world, welcome to 8051 programming "};

  /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);
  
   while(1)
    {
       /*scroll the message on line1 indefnitely*/ 
         LCD_ScrollMessage(1,msg);

		 LCD_ScrollMessage(2,"          Enjoy embedded programming ");
	
	}	 
}