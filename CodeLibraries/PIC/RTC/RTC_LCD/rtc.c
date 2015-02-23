/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   rtc.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library functions for RTC-Ds1307 date and time read write

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

#include "rtc.h"
#include "i2c.h"





/***************************************************************************************************
                         void RTC_Init()
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value	: none

 * description :This function is used to Initialize the Ds1307 RTC.
***************************************************************************************************/
void RTC_Init()
{
	I2C_Init();                             // Initialize the I2c module.
	I2C_Start();                            // Start I2C communication

	I2C_Write(C_Ds1307WriteMode_U8);        // Connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(C_Ds1307ControlRegAddress_U8);// Select the Ds1307 ControlRegister to configure Ds1307

	I2C_Write(0x00);                        // Write 0x00 to Control register to disable SQW-Out

	I2C_Stop();                             // Stop I2C communication after initializing DS1307
}






/***************************************************************************************************
        void RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t,uint8_t,uint8_t-->hh,mm,ss to Initialize the time into DS1307.
 * Return value	: none

 * description  :This function is used to update the Time(hh,mm,ss) of Ds1307 RTC.
                 The new time is updated into the non volatile memory of Ds1307.
	Note: The I/P arguments should of BCD, 
	      like 0x12,0x39,0x26 for 12hr,39min and 26sec.			 
***************************************************************************************************/
void RTC_SetTime(uint8_t var_hour_u8, uint8_t var_min_u8, uint8_t var_sec_u8)
{
	I2C_Start();                            // Start I2C communication

	I2C_Write(C_Ds1307WriteMode_U8);        // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(C_Ds1307SecondRegAddress_U8); // Select the SEC RAM address

	I2C_Write(var_sec_u8);			        // Write sec from RAM address 00H
	I2C_Write(var_min_u8);			        // Write min from RAM address 01H
	I2C_Write(var_hour_u8);			        // Write hour from RAM address 02H

	I2C_Stop();           	                // Stop I2C communication after Setting the Time
}







/***************************************************************************************************
          void RTC_SetDate(uint8_t var_day_u8, uint8_t var_month_u8, uint8_t var_year_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t,uint8_t,uint8_t-->day,month,year to Initialize the Date into DS1307.
 * Return value	: none

 * description  :This function is used to set Date(dd,mm,yy) into the Ds1307 RTC.
                 The new Date is updated into the non volatile memory of Ds1307.
		Note: The I/P arguments should of BCD, 
	      like 0x15,0x08,0x47 for 15th day,8th month and 47th year.				 
***************************************************************************************************/
void RTC_SetDate(uint8_t var_day_u8, uint8_t var_month_u8, uint8_t var_year_u8)
{
	I2C_Start();                          // Start I2C communication

	I2C_Write(C_Ds1307WriteMode_U8);	  // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(C_Ds1307DateRegAddress_U8); // Request DAY RAM address at 04H

	I2C_Write(var_day_u8);			      // Write date on RAM address 04H
	I2C_Write(var_month_u8);			      // Write month on RAM address 05H
	I2C_Write(var_year_u8);			      // Write year on RAM address 06h

	I2C_Stop();				              // Stop I2C communication after Setting the Date
}






/***************************************************************************************************
      void RTC_GetTime(uint8_t *ptr_hour_u8,uint8_t *ptr_min_u8,uint8_t *ptr_sec_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t *,uint8_t *,uint8_t *-->pointers to get the hh,mm,ss.
 * Return value	: none

 * description  :This function is used to get the Time(hh,mm,ss) from Ds1307 RTC.

	Note: The time read from Ds1307 will be of BCD format, 
	      like 0x12,0x39,0x26 for 12hr,39min and 26sec.	
***************************************************************************************************/
void RTC_GetTime(uint8_t *ptr_hour_u8,uint8_t *ptr_min_u8,uint8_t *ptr_sec_u8)
{
	I2C_Start();                            // Start I2C communication

	I2C_Write(C_Ds1307WriteMode_U8);	    // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(C_Ds1307SecondRegAddress_U8); // Request Sec RAM address at 00H

	I2C_Stop();			                    // Stop I2C communication after selecting Sec Register

	I2C_Start();		                    // Start I2C communication
	I2C_Write(C_Ds1307ReadMode_U8);	        // connect to DS1307(Read mode) by sending its ID

	*ptr_sec_u8 = I2C_Read(1);                // read second and return Positive ACK
	*ptr_min_u8 = I2C_Read(1); 	            // read minute and return Positive ACK
	*ptr_hour_u8 = I2C_Read(0);               // read hour and return Negative/No ACK

	I2C_Stop();		                        // Stop I2C communication after reading the Time
}







/***************************************************************************************************
      void RTC_GetDate(uint8_t *ptr_day_u8,uint8_t *ptr_month_u8,uint8_t *ptr_year_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t *,uint8_t *,uint8_t *-->pointers to get the y,m,d.
 * Return value	: none

 * description  :This function is used to get the Date(d,m,y) from Ds1307 RTC.

	Note: The date read from Ds1307 will be of BCD format, 
	      like 0x15,0x08,0x47 for 15th day,8th month and 47th year.			  
***************************************************************************************************/
void RTC_GetDate(uint8_t *ptr_day_u8,uint8_t *ptr_month_u8,uint8_t *ptr_year_u8)
{
	I2C_Start();                          // Start I2C communication

	I2C_Write(C_Ds1307WriteMode_U8);	      // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(C_Ds1307DateRegAddress_U8); // Request DAY RAM address at 04H

	I2C_Stop();			                  // Stop I2C communication after selecting DAY Register


	I2C_Start();		                  // Start I2C communication
	I2C_Write(C_Ds1307ReadMode_U8);	      // connect to DS1307(Read mode) by sending its ID

	*ptr_day_u8 = I2C_Read(1);              // read Day and return Positive ACK
	*ptr_month_u8 = I2C_Read(1);            // read Month and return Positive ACK
	*ptr_year_u8 = I2C_Read(0);             // read Year and return Negative/No ACK

	I2C_Stop();		                      // Stop I2C communication after reading the Date
}
