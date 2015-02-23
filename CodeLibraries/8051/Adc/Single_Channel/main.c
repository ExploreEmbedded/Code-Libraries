/*-----------------------------------------------------------------------------
 Program to demonstrate single channel ADC, 8bit(0-255) adc value is displayed on lcd
  -----------------------------------------------------------------------------
  note:
  1.Refer lcd.h file for Pin connections
  2.Refer adc.c for adc pin connection(adc_databus,A,B,C,ALE,Start,Eoc,OE)
------------------------------------------------------------------------------*/


/* Reg51.h contains the defnition of all ports and SFRs */
#include <reg51.h> 

#include "lcd.h"	//User defined LCD library which conatins the lcd routines
#include "adc.h"   //User defined library which conatins the adc routines


/* start the main program */
void main() 
{
   unsigned char adc_result;

  /* Initilize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);

  /* Initilize the adc before starting the conversion */
    ADC_Init();

  /* Display "ADC Channel zero" on first line*/
  LCD_DisplayString("ADC Channel zero");

   /* Display the adc channel zero value continously */ 
   while(1)
    {
	     /*Get the adc value of channel zero */
		 adc_result= ADC_Get(0);

        /*Go to second line and display the adc value */
         LCD_GoToLineTwo();
         LCD_DisplayDecimalNumber(adc_result,);
      }


  }