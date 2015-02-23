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
   ADCSRA=(1<<ADEN) | (1<<ADPS0); /* Enable ADC , sampling freq=osc_freq/2 */
   ADMUX=0x00;                    /* Result right justified, select channel zero */
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
   
   ADMUX = var_adcChannel_u8;               /* Select the required channel */
   util_BitSet(ADCSRA,ADSC);              /* Start the ADC conversion by setting ADSC bit */
   
   while(util_IsBitCleared(ADCSRA,ADIF)); /* Wait till the conversion is over */
                                          /* ADIF will be set once ADC conversion is complete */
     return(ADCW);                        /* Return the 10-bit result */
 }
       
