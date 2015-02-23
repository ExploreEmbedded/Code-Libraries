/*-----------------------------------------------------------------------------
                 Program to demonstrate Switches and Leds
  -----------------------------------------------------------------------------
 
note: 
1.Leds are  connected to PORTD
2.Switches are connected to PORTB

------------------------------------------------------------------------------*/


/*contains the definition of all ports and SFRs */
#include <avr\io.h>
#include "stdutils.h"

#define Switches PINB
#define LEDs PORTD

/* start the main program */
void main() 
{
   unsigned char SwitchData;

  /*Configure the PORTB as I/p to read the switch data */ 
   DDRD = C_PortOutput_U8;
   DDRB = C_PortInput_U8;

  while(1)
    {
	  
	  /*Read the switch position */ 
	   SwitchData =  Switches; 
	 
	 /*Turn on the respective led depending on Switch position */ 
	   LEDs=SwitchData;
	  }
  }