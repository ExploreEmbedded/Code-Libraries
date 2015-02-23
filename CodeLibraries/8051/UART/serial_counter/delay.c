/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   delay.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains delay routines
 
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


#include"delay.h"
/***************************************************************************************************
                         void DELAY_us(uint16_t us_count)
****************************************************************************************************
 * I/P Arguments: uint16_t.
 * Return value	: none

 * description :
         This function is used generate delay in us.
         It generates a delay of approximate 10us for each count,
         if 5000 is passed as the argument then it generates a delay of 50ms.		  

***************************************************************************************************/
void DELAY_us(uint16_t us_count)
 {	
    while(us_count!=0)
      {
		 us_count--;
	   }
  }



/***************************************************************************************************
                         void DELAY_ms(uint16_t ms_count)
****************************************************************************************************
 * I/P Arguments: uint16_t.
 * Return value	: none

 * description:
     This function is used generate delay in ms.
     It generates a delay of 1ms for each count,
     if 1000 is passed as the argument then it generates delay of 1000ms(1sec)
***************************************************************************************************/
void DELAY_ms(uint16_t ms_count)
 {
        while(ms_count!=0)
		 {
	        DELAY_us(C_CountForOneMsDelay_U16);	 //DELAY_us is called to generate 1ms delay
			 ms_count--;
			}

   }






/***************************************************************************************************
                        void DELAY_sec(uint16_t sec_count)
****************************************************************************************************
  * I/P Arguments: uint16_t.
  * Return value	: none

  * description:
      This function is used generate delay in sec .
      It generates a approximate delay of 1sec for each count,
      if 10 is passed as the argument then it generates delay of 10sec
***************************************************************************************************/
void DELAY_sec(uint16_t sec_count)
 {


	 while(sec_count!=0)
	  {
	     DELAY_ms(1000);	//DELAY_ms is called to generate 1sec delay
		 sec_count--;
		}
  }