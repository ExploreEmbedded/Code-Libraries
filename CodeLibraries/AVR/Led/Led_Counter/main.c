/*-----------------------------------------------------------------------------
                 Program to demonstrate binary upcounter
  -----------------------------------------------------------------------------
 
note: Leds can be connected to any of the ports as all the ports are blinked

------------------------------------------------------------------------------*/


/*contains the definition of all ports and SFRs */
#include <avr/io.h>
#include "stdutils.h"

#include "delay.h" //User defined library which contains the delay routines




/* start the main program */
void main() 
{
   unsigned char cnt=0;
  /*Configure all the ports as output */
   DDRA= C_PortOutput_U8;
   DDRB= C_PortOutput_U8;
   DDRC= C_PortOutput_U8;
   DDRD= C_PortOutput_U8;
   
  while(1)
    {

	 /* Display the counter on all the ports */ 
	   PORTA=cnt;
	   PORTB=cnt;
	   PORTC=cnt;
	   PORTD=cnt;

	 /* Increment the counter after 1-sec */ 
	   DELAY_sec(1);
        cnt++;
      }
  }