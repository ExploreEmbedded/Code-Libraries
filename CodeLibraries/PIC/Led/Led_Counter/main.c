/*-----------------------------------------------------------------------------
                 Program to demonstrate binary upcounter
  -----------------------------------------------------------------------------
 
note: Leds can be connected to any of the ports as all the ports are blinked

------------------------------------------------------------------------------*/


/*contains the defnition of all ports and SFRs */
#include <pic16f877a.h>
#include "stdutils.h"

#include "delay.h" //User defined library which conatins the delay routines




/* start the main program */
void main() 
{
   unsigned char cnt=0;
  /*Configure all the ports as output */
   TRISA= C_PortOutput_U8;
   TRISB= C_PortOutput_U8;
   TRISC= C_PortOutput_U8;
   TRISD= C_PortOutput_U8;
   TRISE= C_PortOutput_U8;
   
  while(1)
    {

	 /* Display the counter on all the ports */ 
	   PORTA=cnt;
	   PORTB=cnt;
	   PORTC=cnt;
	   PORTD=cnt;
           PORTE=cnt;

	 /* Increment the counter after 1-sec */ 
	   DELAY_sec(1);
        cnt++;
      }
  }