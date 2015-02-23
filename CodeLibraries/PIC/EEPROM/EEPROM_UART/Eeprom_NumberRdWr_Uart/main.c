/*-----------------------------------------------------------------------------
         Program to demonstrate Number(16-bit, 32bit) read write 
  -----------------------------------------------------------------------------
  note:
  Refer uart.h file for baud rate configuration
  Refer i2c.c for SDA and SCL connection.
------------------------------------------------------------------------------*/


#include "uart.h"	
#include "eeprom.h" //User defined library which conatins eeprom(At2404) routines


/* start the main program */
void main() 
{
   uint16_t var_writeNumber_u16=12345, var_readNumber_u16;
   uint32_t var_writeNumber_u32=123456789, var_readNumber_u32; 

   /* Initilize the lcd before displaying any thing on the lcd */
    UART_Init(9600);												  
 
   	UART_TxString("\n\r16-bit Number   read write");
    
				             
	UART_Printf("\n\rWr:%u",var_writeNumber_u16);  //Dispaly the 16-bit String to be written 
	EEPROM_WriteNBytes(50,&var_writeNumber_u16,sizeof(var_writeNumber_u16)); // Write the 16-bit number into eeprom

					   
	EEPROM_ReadNBytes(50,&var_readNumber_u16,sizeof(var_readNumber_u16));  // Read the 16-bit number from eeprom
    UART_Printf("\n\rRd:%u",var_writeNumber_u16);  //Dispaly the 16-bit number read from eeprom

	
	UART_TxString("\n\r32-bit Number   read write");
    

   					             
	UART_Printf("\n\rWr:%U",var_writeNumber_u32);  //Dispaly the 32-bit String to be written 
	EEPROM_WriteNBytes(100,&var_writeNumber_u32,sizeof(var_writeNumber_u32)); // Write the 32-bit number into eeprom

					   
	EEPROM_ReadNBytes(100,&var_readNumber_u32,sizeof(var_readNumber_u32));  // Read the 32-bit number from eeprom
    UART_Printf("\n\rRd:%U",var_writeNumber_u32);  //Dispaly the 32-bit number read from eeprom

	 		
	while(1);
}