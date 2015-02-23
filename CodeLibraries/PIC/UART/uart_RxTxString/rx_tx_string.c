/*-----------------------------------------------------------------------------
  Program to demonstrate reception & transmission of a String at 9600 baudrate
  -----------------------------------------------------------------------------
  note:
  Refer uart.h for baud rate configuraton.
------------------------------------------------------------------------------*/


#include "uart.h"	//User defined UART library which conatins the uart routines


/* start the main program */
void main() 
{
   	 char msg[50];

  /* Initialize the UART before Transmitting/Receiving any data */
    UART_Init(9600);
	
   while(1)
    {
	    /*Receive and transmit a string indefinitely at 9600 baud rate */
	     UART_TxString("\n\r\n\rEnter a new String: ");
		 UART_RxString(msg);   //Receive a string and store it in msg

		 UART_TxString("Entered String is: ");
		 UART_TxString(msg);   //Transmit the received string
	  }	   

  }