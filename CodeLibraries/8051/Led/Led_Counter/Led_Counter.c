/*-----------------------------------------------------------------------------
                 Program to demonstrate binary upcounter
  -----------------------------------------------------------------------------
 
note: Leds can be connected to any of the ports as all the ports are blinked

------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 


#include "delay.h" //User defined library which conatins the delay routines




/* start the main program */
void main() 
{
   unsigned char cnt=0;
  while(1)
    {

	 /* Display the counter on all the ports */ 
	   P0=cnt;
	   P1=cnt;
	   P2=cnt;
	   P3=cnt;

	 /* Increment the counter after 1-sec */ 
	   DELAY_sec(1);
        cnt++;
      }
  }