/*-----------------------------------------------------------------------------
         Program to demonstrate Eeprom char Read Write on UART 
  -----------------------------------------------------------------------------
  note:
  Refer Uart.c for baudrate configuration.
  Refer i2c.c for SDA and SCL connection.
------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 

#include "uart.h"	//User defined UART library which conatins the UART routines
#include "eeprom.h" //User defined library which conatins eeprom(At2404) routines


/* start the main program */
void main() 
{
   unsigned char eeprom_address=0x00, write_char = 'X', read_char;

  /* Initilize the Uart before Transmiting/Reaceiving any data */
    UART_Init(9600);												  
 
   while(1)
    {
	   	   UART_TxString("\n\rEeprom Write: ");      //Print the message on UART
		   UART_TxChar(write_char);			         //Print the char to be written 
		   EEPROM_WriteByte(eeprom_address,write_char);	// Write the data at memoryLocation	0x00

		   
		   UART_TxString("  Eeprom Read: ");            //Print the message on UART
		   read_char = EEPROM_ReadByte(eeprom_address);	// Read the data from memoryLocation 0x00
		   UART_TxChar(read_char);			            //Print the read data 

	  }		

  }