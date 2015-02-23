/*-----------------------------------------------------------------------------
         Program to demonstrate Eeprom char Read Write on Lcd 
  -----------------------------------------------------------------------------
  note:
  Refer lcd.c(lcd_4_bit.c/lcd_8_bit.c) file for Pin connections
  Refer i2c.c for SDA and SCL connection.
------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 

#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "eeprom.h" //User defined library which conatins eeprom(At2404) routines


/* start the main program */
void main() 
{
   unsigned char eeprom_address=0x00, write_String[] = {"123456789"}, read_string[15];

  /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);												  
 
   while(1)
    {
	   	LCD_GoToLine(1);				  // Move the cursor to first line
        LCD_DisplayString("Wr:");         //Display the message on first line
		LCD_DisplayString(write_String);  //Dispaly the String to be written 
		EEPROM_WriteString(eeprom_address,write_String); // Write the String at memory Location	0x00

		LCD_GoToLine(2);				   // Move the cursor to Second line
		LCD_DisplayString("Rd:");          //Display the message on Second line
		EEPROM_ReadString(eeprom_address,read_string);	// Read the String from memory Location 0x00
		LCD_DisplayString(read_string);			        //Display the read String

	  }		

  }