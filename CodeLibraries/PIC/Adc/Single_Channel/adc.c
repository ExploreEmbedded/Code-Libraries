/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   adc.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for ADC conversion
 
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
 
 
/***************************************************************************************************
                             Revision History
****************************************************************************************************				   
15.0: Initial version 
***************************************************************************************************/
#include"adc.h"
#include"delay.h"



/***************************************************************************************************
                         void ADC_Init()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value	: none

 * description :This function initializes the ADC module.

***************************************************************************************************/
void ADC_Init()
 {
   ADCON0=0x00;        // sampling freq=osc_freq/2,ADC off initially
   ADCON1=0x80;  /* All pins are configured as Analog input pins and
                          the 10-bit ADC result is right justified */  
}


  
  
  
/***************************************************************************************************
                         uint16_t ADC_GetAdcValue(uint8_t var_adcChannel_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t(channel number).
 * Return value	: uint16_t(10 bit ADC result)

 * description  :This function does the ADC conversion for the Selected Channel
                 and returns the converted 10bit result
                 The adc value per bit depends on the resolution of the ADC.
				 For AVR/PIC(10-bit adc) the adc value per lsb will be 5/1023=0048v
***************************************************************************************************/				 
uint16_t ADC_GetAdcValue(uint8_t var_adcChannel_u8)
 {
 
    ADCON0= (var_adcChannel_u8<<3);   //select particular channel and turn ON adc
	ADON = 1;
    DELAY_us(50);
   
    GO=1;                                         // Start ADC conversion
    while(GO_DONE==1);                            // Wait for the conversion to complete
	                                         // GO bit will be cleared once conversion is complete

    return((ADRESH<<8) + ADRESL);            // return right justified 10-bit result
 }
       
