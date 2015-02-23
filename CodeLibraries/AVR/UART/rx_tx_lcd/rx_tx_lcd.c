/*-----------------------------------------------------------------------------
  Program to demonstrate serial Reception,transmission of char at 9600 baudrate
      and same to display on lcd.
  -----------------------------------------------------------------------------
  note:
  Refer uart.h for baud rate configuraton.
------------------------------------------------------------------------------*/



#include "uart.h"	//User defined UART library which contains the uart routines

#include "lcd.h"	//User defined LCD library which contains the lcd routines


/* start the main program */
void main() 
{
   	 char ch='m';

  /* Initialize the UART before Transmitting/Receiving any data */
    UART_Init(9600);

  /* Initialize the lcd before displaying any thing on the lcd */
    LCD_Init(4,2,16);

   while(1)
    {
	    /*Receive and Transmit a char indefinitely at 9600 baud rate */
	    ch=UART_RxChar(); // Receive a char and store it in "ch"
        
         UART_TxChar(ch);  //Transmit the received char

		 LCD_DisplayChar(ch); //Display the received char on LCD
	  }	   

  }