/*-----------------------------------------------------------------------------
                 Program to demonstrate Led_Blinking
  -----------------------------------------------------------------------------
 
note: Leds can be connected to any of the ports as all the ports are blinked

------------------------------------------------------------------------------*/


/* htc.h contains the definition of all ports and SFRs */
#include <avr\io.h>
#include "stdutils.h"
#include "delay.h" //User defined library which contains the delay routines


#define LedOn 0xFF
#define LedOff 0x00

/* start the main program */
void main() 
{
  /*Configure all the ports as output */
   DDRA= C_PortOutput_U8;
   DDRB= C_PortOutput_U8;
   DDRC= C_PortOutput_U8;
   DDRD= C_PortOutput_U8;

  while(1)
    {

	 /* Turn On all the leds and wait for one second */ 
	   PORTA=LedOn;
	   PORTB=LedOn;
	   PORTC=LedOn;
	   PORTD=LedOn;
	   
	   DELAY_sec(1);


	 /* Turn off all the leds and wait for one second */
	   PORTA=LedOff;
	   PORTB=LedOff;
	   PORTC=LedOff;
	   PORTD=LedOff;           

	   DELAY_sec(1);
	  }
  }
