/*-----------------------------------------------------------------------------
                 Program to demonstrate Switches and Leds
  -----------------------------------------------------------------------------
 
note: 
1.Leds are  connected to PORTC
2.Switches are connected to PORTA

------------------------------------------------------------------------------*/


/*contains the defnition of all ports and SFRs */
#include <pic16f877a.h>
#include "stdutils.h"

#define Switches PORTB
#define LEDs PORTD

/* start the main program */
void main() 
{
   unsigned char SwitchData;

  /*Configure the PORTB as I/p to read the switch data */ 
   TRISD = C_PortOutput_U8;
   TRISB = C_PortInput_U8;

  while(1)
    {
	  
	  /*Read the switch position */ 
	   SwitchData =  Switches; 
	 
	 /*Turn on the respective led depending on Switch position */ 
	   LEDs=SwitchData;
	  }
  }