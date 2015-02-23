/*-----------------------------------------------------------------------------
  Program to demonstrate transmission of String at 9600 baudrate
  -----------------------------------------------------------------------------
  note:
  Refer uart.h for baud rate configuraton.
------------------------------------------------------------------------------*/

#include "uart.h"	//User defined UART library which conatins the uart routines


/* start the main program */
void main() 
{
   	 char msg[]={"hello world, "};

  /* Initilize the UART before Transmitting/Receiving any data */
    UART_Init(9600);

   while(1)
    {
	    /*Transmit a string indefinitely at 9600 baud rate */
	     UART_TxString(msg); 
         UART_TxString("welcome to 8051 programming\n\r"); 
	  }	   

  }