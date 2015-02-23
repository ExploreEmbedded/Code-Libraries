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
  unsigned char eeprom_address=0x00, write_String[] = {"hello world"}, read_string[15];

  /* Initilize the Uart before Transmiting/Reaceiving any data */
    UART_Init(9600);												  
 
   while(1)
    {
	   	   UART_TxString("\n\rWr:");                      //Print the message on UART
		   UART_TxString(write_String);			         //Print the String to be written 
		   EEPROM_WriteString(eeprom_address,write_String); // Write the String at memory Location	0x00

		   
		   UART_TxString("  Rd:");                           //Print the message on UART
		   EEPROM_ReadString(eeprom_address,read_string);	// Read the String from memory Location 0x00
		   UART_TxString(read_string);			            //Print the read String

	  }		

  }