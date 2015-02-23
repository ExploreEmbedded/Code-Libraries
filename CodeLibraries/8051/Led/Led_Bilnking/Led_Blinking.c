/*-----------------------------------------------------------------------------
                 Program to demonstrate Led_Blinging
  -----------------------------------------------------------------------------
 
note: Leds can be connected to any of the ports as all the ports are blinked

------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 
  #pragma OT(9)       /* Selcet highest level of optimization */

#include "delay.h" //User defined library which conatins the delay routines


#define LedOn 0xFF
#define LedOff 0x00

/* start the main program */
void main() 
{

  while(1)
    {

	 /* Turn On all the leds and wait for one second */ 
	   P0=LedOn;
	   P1=LedOn;
	   P2=LedOn;
	   P3=LedOn;

	   DELAY_sec(1);


	 /* Turn off all the leds and wait for one second */
	   P0=LedOff;
	   P1=LedOff;
	   P2=LedOff;
	   P3=LedOff;				   

	   DELAY_sec(1);
	  }
  }