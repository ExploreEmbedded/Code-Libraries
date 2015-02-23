/*-----------------------------------------------------------------------------
         Program to demonstrate serial transmission of char at 9600 baudrate
  -----------------------------------------------------------------------------
  note:
  Refer uart.h for baud rate configuration.
------------------------------------------------------------------------------*/



#include "uart.h"	//User defined UART library which contains the uart routines


/* start the main program */
void main() 
{
 
 /* Initialize the UART before Transmitting/Receiving any data */
    UART_Init(9600);

   while(1)
    {
        /*Transmit a char indefinitely at 9600 baud rate */
         UART_TxChar('a');
	  }
  }