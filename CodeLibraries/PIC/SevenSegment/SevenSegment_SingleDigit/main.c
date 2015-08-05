/*-----------------------------------------------------------------------------
   Program to demonstrate Hex counter on signle SevenSegment(CommonAnode) display
  -----------------------------------------------------------------------------
  note:
Code is for CommonAnode type of segment, 
seg_code[] must be complemented for CommonCathode
------------------------------------------------------------------------------*/

																	
/* htc.h contains the defnition of all ports and SFRs */
#include <pic16f877a.h>

#include "delay.h"	//User defined delay library which conatins the delay routines

#define SegmentValue PORTB
#define SegmentSlection PORTC

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08

/* start the main program */
void main() 
{
   unsigned char seg_code[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82, 0xF8,0x80,0x90};
   unsigned char cnt=0;

 /* Configure the ports as output */
  TRISB = C_PortOutput_U8;
  TRISC = C_PortOutput_U8;
 
   while(1)
    {
	   
	    for(cnt=0x00;cnt<=0x0f;cnt++)	 // loop to display 0-F
		 {
		   	SegmentSlection = SegOne;	 // Select the segment
			SegmentValue= seg_code[cnt];	 // Send the segment_code of number to be displayed
			DELAY_sec(1);
		   }

	  }												  

  }
          