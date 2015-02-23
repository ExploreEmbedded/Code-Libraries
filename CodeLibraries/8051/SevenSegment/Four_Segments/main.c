/*-----------------------------------------------------------------------------
   Program to demonstrate 4digit counter on 4-SevenSegment(CommonAnode) display
  -----------------------------------------------------------------------------
  note:
Code is for CommonAnode type of segment, seg_code[] must be complemented for CommonCathode
------------------------------------------------------------------------------*/

																	
/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 

#include "delay.h"	//User defined delay library which conatins the delay routines

#define SegmentValue P0
#define SegmentSlection P1

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08	 
#define NoSeg	 0x00


void display_number(unsigned int number)
{
    unsigned char seg_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	unsigned char temp;
	unsigned int i,num;

   for(i=0;i<9;i++)	   
   	 { 
	   num=number;
	   
	   temp = num/1000;
	   num=num%1000;  
	   SegmentSlection=SegOne;
	   SegmentValue = seg_code[temp];
	   DELAY_us(10);

	   temp = num/100;
	   num=num%100;  
	   SegmentSlection=SegTwo;
	   SegmentValue = seg_code[temp];
	   DELAY_us(10);

       temp = num/10;  
	   SegmentSlection=SegThree;
	   SegmentValue = seg_code[temp];
	   DELAY_us(10);

	   temp = num%10;
	   SegmentSlection=SegFour; 
	   SegmentValue = seg_code[temp];
	   DELAY_us(10);  	   
	  }
	 
 }
/* start the main program */
void main() 
{
 
   unsigned int cnt=0;

   while(1)
    {
	   
	    for(cnt=0;cnt<9999;cnt++)	 // loop to display 0000-9999
		 {
		   
		   display_number(cnt);
		   DELAY_sec(1);
	    	 
			
		 }

	}												  
																		 
  }										