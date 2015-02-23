/*-----------------------------------------------------------------------------
  Program to demonstrate a 5 digit counter at 9600 baudrate
  -----------------------------------------------------------------------------
  note:
  Refer uart.h for baud rate configuration.
------------------------------------------------------------------------------*/

#include "uart.h"	//User defined UART library which contains the uart routines

#include "delay.h" //library which contains the delay routines


/* start the main program */
void main()
{
	uint16_t cnt=0;

	/* Initialize the UART before Transmitting/Receiving any data */
	UART_Init(9600);
	UART_Printf("5digit decimal counter: ");

	/* Transmit the counter till 9999 */
	while(cnt < 9999)
	{
		
		/* Transmit the 4-digit counter value and go to next line */
		UART_Printf("\n\r%4u",cnt);
		
		/* Increment the counter value after 1-sec */
		DELAY_sec(1);
		cnt++;
	}
	while(1);

}