/*-----------------------------------------------------------------------------
         Program to demonstrate Number(16-bit, 32bit) read write 
  -----------------------------------------------------------------------------
  note:
  Refer lcd.h file for Pin connections
  Refer i2c.c for SDA and SCL connection.
------------------------------------------------------------------------------*/


#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "eeprom.h" //User defined library which conatins eeprom(At2404) routines
#include "delay.h"


/* start the main program */
void main() 
{
   uint16_t var_writeNumber_u16=12345, var_readNumber_u16;
   uint32_t var_writeNumber_u32=123456789, var_readNumber_u32; 

   /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);												  
 
   	LCD_DisplayString("16-bit Number   read write");
    DELAY_sec(2);

   	LCD_Clear();				             
	LCD_Printf("Wr:%u",var_writeNumber_u16);  //Dispaly the 16-bit String to be written 
	EEPROM_WriteNBytes(50,&var_writeNumber_u16,sizeof(var_writeNumber_u16)); // Write the 16-bit number into eeprom

	LCD_GoToLine(2);				   
	EEPROM_ReadNBytes(50,&var_readNumber_u16,sizeof(var_readNumber_u16));  // Read the 16-bit number from eeprom
    LCD_Printf("Rd:%u",var_writeNumber_u16);  //Dispaly the 16-bit number read from eeprom

	DELAY_sec(2);
	LCD_Clear();
	
	LCD_DisplayString("32-bit Number   read write");
    DELAY_sec(2);

   	LCD_Clear();				             
	LCD_Printf("Wr:%U",var_writeNumber_u32);  //Dispaly the 32-bit String to be written 
	EEPROM_WriteNBytes(100,&var_writeNumber_u32,sizeof(var_writeNumber_u32)); // Write the 32-bit number into eeprom

	LCD_GoToLine(2);				   
	EEPROM_ReadNBytes(100,&var_readNumber_u32,sizeof(var_readNumber_u32));  // Read the 32-bit number from eeprom
    LCD_Printf("Rd:%U",var_writeNumber_u32);  //Dispaly the 32-bit number read from eeprom

	 		
	while(1);
}