/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   main.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Program to demonstrate multi(4) channel ADC, 8bit(0-255) adc value is displayed on lcd
 
The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 
 
 
GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 
Errors and omissions should be reported to codelibraries@exploreembedded.com
 **************************************************************************************************/





#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "adc.h"   //User defined library which conatins the adc routines


/* start the main program */
void main() 
{
   uint16_t adc_result0,adc_result1,adc_result2,adc_result3;		

    LCD_Init(8,2,16);	   /* Initialize 2x16lcd in 8-bit mode */    
    ADC_Init();			   /* Initialize the adc module*/	 
    
   while(1)
    {
       	/* Get the adc value of first four channels */
		 adc_result0= ADC_GetAdcValue(0);
		 adc_result1= ADC_GetAdcValue(1);
		 adc_result2= ADC_GetAdcValue(2);
		 adc_result3= ADC_GetAdcValue(3);		  
	
		 LCD_GoToLine(1);
         LCD_Printf("C0:%d C1:%d \nC2:%d C3:%d ",adc_result0,adc_result1,adc_result2,adc_result3);         	     
    }			 
}