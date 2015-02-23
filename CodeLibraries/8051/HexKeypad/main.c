/*-----------------------------------------------------------------------------
                    Program to demonstrate 4*4-Matrix Keypad
  -----------------------------------------------------------------------------
  note:
  1.Refer lcd.c(lcd_4_bit.c/lcd_8_bit.c) file for Pin connections
  2.Refer keypad.c for Keypad(Row/Col) connections.
------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include"keypad.h"
#include"lcd.h"
#include "delay.h"


/* Program to demonstrate the hex-Keypad interface*/
int  main()
{
  uint8_t key;
  LCD_Init(8,2,16);            /*Initialize the 2x16 LCD in 8-bit mode */
  KEYPAD_Init();               /*Configure the ROWs and COLUMNs for keypad scanning*/

	while(1)
	{
		key = KEYPAD_GetKey(); /*Get the Ascii value of the key Pressed */
		LCD_DisplayChar(key);  /*Display the key pressed */
	}

	return 0;
}