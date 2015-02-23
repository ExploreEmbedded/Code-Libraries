/*-----------------------------------------------------------------------------
Program to demonstrate displaying of 5-digit LCD_Connter
-----------------------------------------------------------------------------
note:
Refer lcd.c(lcd_4_bit.c/lcd_8_bit.c) file for Pin connections
------------------------------------------------------------------------------*/


#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "delay.h" //User defined library which conatins the delay routines


int main()
{
	char a_displayMsg_u8[]={"Good Morning"};
	char var_lcdData_u8='A';
	uint16_t var_number_u16= 1234u;


	LCD_Init(8,2,16);
	LCD_ScrollMessage(0,"            Program to illustrate the lcd library usage ");


	LCD_Clear();
	LCD_DisplayString("Hello, world");    /* Display the specified Message */
	LCD_GoToNextLine();
	LCD_DisplayString(a_displayMsg_u8);   /* Display the message stored in a string */

	DELAY_sec(2);
	LCD_Clear();
	LCD_DisplayString("Display Char\n");
	LCD_DisplayChar('X');             /* Display the specified Ascii character */
	LCD_DisplayChar(var_lcdData_u8);    /* Display the char stored in a variable */


	DELAY_sec(2);
	LCD_Clear();
	LCD_DisplayString("D:");
	LCD_DisplayDecimalNumber(1234,5);   /* Display the specified digits of a number */
	LCD_DisplayString(" H:");
	LCD_DisplayHexNumber(0xABCD,5);     /* Note here the num=1234, and digitsToDisplay=5 */
	LCD_GoToNextLine();                 /* The number displayed on LCD will be as below*/
	LCD_DisplayBinaryNumber(0xABCD,16); /* dec=01234, hex=0ABCD,
                               bin=1010101111001101*/



	DELAY_sec(2);
	LCD_Clear();
	LCD_Printf("D=%3d H=%3x \n%8b",var_number_u16,var_number_u16,var_number_u16);



	DELAY_sec(2);
	LCD_Clear();
	LCD_Printf("Enjoy Embedded \nProgramming");

	while(1);

	return 0;
}