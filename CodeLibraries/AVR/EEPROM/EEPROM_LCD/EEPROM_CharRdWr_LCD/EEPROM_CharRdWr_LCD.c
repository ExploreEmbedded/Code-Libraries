/*-----------------------------------------------------------------------------
         Program to demonstrate Eeprom char Read Write on Lcd 
  -----------------------------------------------------------------------------
  note:
  Refer lcd.h file for Pin connections
------------------------------------------------------------------------------*/



#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "eeprom.h" //User defined library which conatins eeprom(At2404) routines


/* start the main program */
void main() 
{
   unsigned char eeprom_address=0x00, write_char = 'X', read_char;

  /* Initialize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);												  
 
   while(1)
    {					
	   	   LCD_GoToLine(1);							// Move the cursor to first line
           LCD_DisplayString("Eeprom Write: ");         //Display the message on first line
		   LCD_DisplayChar(write_char);			        //Display the char to be written 
		   EEPROM_WriteByte(eeprom_address,write_char);	// Write the data at memoryLocation	0x00

		   LCD_GoToLine(2);							// Move the cursor to Second line
		   LCD_DisplayString("Eeprom Read: ");          //Display the message on first line
		   read_char = EEPROM_ReadByte(eeprom_address);	// Read the data from memoryLocation 0x00
		   LCD_DisplayChar(read_char);			        //Display the read data 

	  }		

  }