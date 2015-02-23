/*-----------------------------------------------------------------------------
                 Program to demonstrate Led_Blinging
  -----------------------------------------------------------------------------
 
note: Leds can be connected to any of the ports as all the ports are blinked

------------------------------------------------------------------------------*/


/* htc.h contains the defnition of all ports and SFRs */
#include <pic16f877a.h>
#include "stdutils.h"
#include "delay.h" //User defined library which conatins the delay routines


#define LedOn 0xFF
#define LedOff 0x00

/* start the main program */
void main() 
{
  /*Configure all the ports as output */
   TRISA= C_PortOutput_U8;
   TRISB= C_PortOutput_U8;
   TRISC= C_PortOutput_U8;
   TRISD= C_PortOutput_U8;
   TRISE= C_PortOutput_U8;

  while(1)
    {

	 /* Turn On all the leds and wait for one second */ 
	   PORTA=LedOn;
	   PORTB=LedOn;
	   PORTC=LedOn;
	   PORTD=LedOn;
           PORTE=LedOn;

	   DELAY_sec(1);


	 /* Turn off all the leds and wait for one second */
	   PORTA=LedOff;
	   PORTB=LedOff;
	   PORTC=LedOff;
	   PORTD=LedOff;
           PORTE=LedOff;

	   DELAY_sec(1);
	  }
  }