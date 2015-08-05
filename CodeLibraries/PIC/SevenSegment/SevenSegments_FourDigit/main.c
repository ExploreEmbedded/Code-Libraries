/*-----------------------------------------------------------------------------
   Program to demonstrate 4digit counter on 4-SevenSegment(CommonAnode) display
  -----------------------------------------------------------------------------
  note:
Code is for CommonAnode type of segment, seg_code[] must be complemented for CommonCathode
------------------------------------------------------------------------------*/

																	
/*contains the defnition of all ports and SFRs */
#include <pic16f877a.h>

#include "delay.h"	//User defined delay library which conatins the delay routines

#define SegmentValue PORTB
#define SegmentSlection PORTC

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08	 


void display_number(unsigned int number)
{
    unsigned char seg_code[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82, 0xF8,0x80,0x90};
    unsigned char temp,i;
    unsigned int num;
  
 

   for(i=0;i<200;i++)	   
   	 { 
	   num=number;
	   
	   temp = num/1000;
	   num=num%1000;  
	   SegmentSlection=SegOne;
	   SegmentValue = seg_code[temp];
	   DELAY_ms(1);

	   temp = num/100;
	   num=num%100;  
	   SegmentSlection=SegTwo;
	   SegmentValue = seg_code[temp];
	   DELAY_ms(1);

           temp = num/10;
	   SegmentSlection=SegThree;
	   SegmentValue = seg_code[temp];
	   DELAY_ms(1);

	   temp = num%10;
	   SegmentSlection=SegFour; 
	   SegmentValue = seg_code[temp];
	   DELAY_ms(1);
	  }
 }
/* start the main program */
void main() 
{
 
   unsigned int cnt=0;
 /* Configure the ports as output */
  TRISB = C_PortOutput_U8;
  TRISC = C_PortOutput_U8;
   while(1)
    {
	   
	    for(cnt=0;cnt<=9999;cnt++)	 // loop to display 0000-9999
		 {
		   display_number(cnt);  	
		 }
	}												  
																		 
  }										