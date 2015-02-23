/*-----------------------------------------------------------------------------
                 Program to demonstrate Switches and Leds
  -----------------------------------------------------------------------------
 
note: 
1.Leds are  connected to PORT2
2.Switches are connected to PORT0

------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 

#define Switches P0
#define LEDs P2

/* start the main program */
void main() 
{
   unsigned char SwitchData;

  /*Configure the P0 as I/p to read the switch data */ 
   Switches=0xff;

  while(1)
    {
	  
	  /*Read the switch position */ 
	   SwitchData =  Switches; 
	 
	 /*Turn on the respective led depending on Switch position */ 
	   LEDs=SwitchData;
	  }
  }