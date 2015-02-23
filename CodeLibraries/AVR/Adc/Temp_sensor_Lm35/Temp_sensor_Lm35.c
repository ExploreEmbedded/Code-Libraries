/*-----------------------------------------------------------------------------
 Program to demonstrate single channel ADC, 10bit(0-1023) adc value is displayed on lcd
  -----------------------------------------------------------------------------
  note:
  1.Refer lcd.c(lcd_4_bit.c/lcd_8_bit.c) file for Pin connections
  2.Refer Atmega32 datasheet for register description.
------------------------------------------------------------------------------*/
 

#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "adc.h"   //User defined library which conatins the adc routines


/* start the main program */
void main() 
{
   unsigned int adc_result,adc_temp;

  /* Initialize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);

  /* Initialize the adc before starting the conversion */
    ADC_Init();
  

   /* Display the adc channel zero value continuously */ 
   while(1)
    {
	     /*Get the adc value of channel one or wherever the LM35 temp sensor is connected */
		 adc_result= ADC_GetAdcValue(1);
         
		 LCD_GoToLine(1);
         LCD_Printf("ADC value:%u",adc_result);
					 
		 // Convert the raw ADC value to equivalent temperature with 5v as ADC reference
		 /* Step size of AdC= (5v/1023)=4.887mv = 5mv.
		    for every degree celcius the Lm35 provides 10mv voltage change.
			1 step of ADC=5mv=0.5'c, hence the Raw ADC value can be divided by 2 to get equivalent temp*/
		 adc_temp = (adc_result/2); 

		/*Go to second line and Display the actual temp */
		 LCD_GoToNextLine();
         LCD_Printf("Temp:%u",adc_temp);
      }


  }