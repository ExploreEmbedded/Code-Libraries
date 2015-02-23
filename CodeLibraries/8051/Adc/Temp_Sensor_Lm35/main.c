/*-----------------------------------------------------------------------------
 Program to demonstrate single channel ADC, 8bit(0-255) adc value is displayed on lcd
  -----------------------------------------------------------------------------
  note:
  1.Refer lcd.h file for Pin connections
  2.Refer adc.h for adc pin connection(adc_databus,A,B,C,ALE,Start,Eoc,OE)
  3.Refer the LM35 datasheet for Voltage and temp relation
------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 

#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "adc.h"   //User defined library which conatins the adc routines


/* start the main program */
void main() 
{
   unsigned char adc_result=0;
   unsigned int adc_temp=0;

  /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);

  /* Initilize the adc before starting the conversion */
    ADC_Init();



   while(1)
    {
	      /*Get the adc value of channel one or wherever the LM35 temp sensor is connected */
		 adc_result= ADC_GetAdcValue(1);
         
		 LCD_GoToLine(1);
         LCD_Printf("ADC value:%u",adc_result);
					 
		 // Convert the raw ADC value to equivalent temperature with 5v as ADC reference
		 /* Step size of AdC= (5v/255)=19.60mv = 20mv.
		    for every degree celcius the Lm35 provides 10mv voltage change.
			1 step of ADC=20mv=2'c, hence the Raw ADC value can be multiplied by 2 to get equivalent temp*/
		 adc_temp = (adc_result*2); 

	     /*Go to second line and Display the actual temp */
		 LCD_GoToNextLine();
         LCD_Printf("Temp:%u",adc_temp);
      }


  }