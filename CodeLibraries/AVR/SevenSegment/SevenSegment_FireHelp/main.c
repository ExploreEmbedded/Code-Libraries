/*-----------------------------------------------------------------------------
   Program to demonstrate 4digit counter on 4-SevenSegment(CommonAnode) display
  -----------------------------------------------------------------------------
  note:
Code is for CommonAnode type of segment, fire_code[] and help_code[] must be complemented for CommonCathode
------------------------------------------------------------------------------*/

																	
/*contains the definition of all ports and SFRs */
#include <avr\io.h>
#include "stdutils.h"
#include "delay.h"	//User defined delay library which contains the delay routines

#define SegmentValue PORTB
#define SegmentSlection PORTC

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08
#define NoSeg    0x00	 	 


void display(unsigned char seg_code[])
{						   
	unsigned char i;
								  
   for(i=0;i<200;i++)	   
   	 { 
	   SegmentSlection=SegOne;
	   SegmentValue = seg_code[0];
	   DELAY_ms(1);
   
	   SegmentSlection=SegTwo;
	   SegmentValue = seg_code[1];
	   DELAY_ms(1);
 
	   SegmentSlection=SegThree;
	   SegmentValue = seg_code[2];
	   DELAY_ms(1);

	   SegmentSlection=SegFour; 
	   SegmentValue = seg_code[3];
	   DELAY_ms(1);
	  }
  SegmentSlection=NoSeg;
  SegmentValue = 0x00;
}
/* start the main program */
void main() 
{
    unsigned char fire_code[]={0x71,0x06,0x50,0x79},help_code[]={0x76,0x79,0x38,0x73};
  
/* Configure the ports as output */  
  DDRB = C_PortOutput_U8;
  DDRC = C_PortOutput_U8;
 
  while(1)
    {
          display(fire_code);
	     DELAY_sec(1);

          display(help_code);
	    DELAY_sec(1);
	    
    }
  }										