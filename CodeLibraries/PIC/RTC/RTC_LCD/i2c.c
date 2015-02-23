/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   i2c.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library routines for I2C read,write operation

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
***************************************************************************************************/




/***************************************************************************************************
                             Revision History
****************************************************************************************************
15.0: Initial version 
***************************************************************************************************/

#include "delay.h"
#include "i2c.h"


/***************************************************************************************************
                          Local Function declaration
***************************************************************************************************/

static void i2c_WaitForIdle();
static void i2c_Ack();
static void i2c_NoAck();
/**************************************************************************************************/





/***************************************************************************************************
                         void I2C_Restart()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :.
***************************************************************************************************/
void I2C_Restart()
{
	RSEN = 1;        /* Repeated start enabled */
	while(RSEN);     /* wait for condition to finish */
}






/***************************************************************************************************
                         void I2C_Init()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to initialize the I2C module.
***************************************************************************************************/
void I2C_Init()
{
	SCL_Direction = C_PinInput_U8;
	SDA_Direction = C_PinInput_U8;

	SSPSTAT |= 0x80;  /* Slew rate disabled */
	SSPCON = 0x28;    /* SSPEN = 1, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) */
	SSPADD = 50;      /* 100Khz @ 20Mhz Fosc */
}





/***************************************************************************************************
                         void I2C_Start()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate I2C Start Condition.
                 Start Condition: SDA goes low when SCL is High.

                               ____________
                SCL:          |            |
                      ________|            |______
                           _________
                SDA:      |         |
                      ____|         |____________

***************************************************************************************************/
void I2C_Start()
{
	SEN = 1;              /* trigger the Start condition and wait till its completed*/
	while(SEN == 1);      /* automatically cleared by hardware once start condition is completed */

}





/***************************************************************************************************
                         void I2C_Stop()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate I2C Stop Condition.
                 Stop Condition: SDA goes High when SCL is High.

                               ____________
                SCL:          |            |
                      ________|            |______
                                 _________________
                SDA:            |
                      __________|

***************************************************************************************************/

void I2C_Stop(void)
{
	PEN = 1;              /* Trigger stop condition, Wait till stop condition to finished*/
	while(PEN == 1);      /* PEN automatically cleared by hardware once stop condition is finished*/
}








/***************************************************************************************************
                         void I2C_Write(uint8_t var_i2cData_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t-->8bit data to be sent.
 * Return value  : none

 * description  :This function is used to send a byte on SDA line using I2C protocol
                 8bit data is sent bit-by-bit on each clock cycle.
                 MSB(bit) is sent first and LSB(bit) is sent at last.
                 Data is sent when SCL is low.

         ___     ___     ___     ___     ___     ___     ___     ___     ___     ___
 SCL:   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
      __|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___

 SDA:    D8       D7     D6      D5      D4       D3      D2      D1      D0     ACK


***************************************************************************************************/
void I2C_Write(uint8_t var_i2cData_u8)
{


    SSPBUF = var_i2cData_u8;  /* Copy the data to be transmitted into SSPBUF */
    while(BF==1);             /* wait till the data is transmitted */
    i2c_WaitForIdle();        /* wait till current operation is complete*/
}






/***************************************************************************************************
                         uint8_t I2C_Read(uint8_t var_ackOption_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t: Acknowledgement to be sent after data reception.
                        1:Positive acknowledgement
                        0:Negative acknowledgement						
 * Return value  : uint8_t(received byte)

 * description :This fun is used to receive a byte on SDA line using I2C protocol.
               8bit data is received bit-by-bit each clock and finally packed into Byte.
               MSB(bit) is received first and LSB(bit) is received at last.


         ___     ___     ___     ___     ___     ___     ___     ___     ___     ___
SCL:    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
      __|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |__

 SDA:    D8       D7     D6      D5       D4     D3       D2      D1     D0      ACK


***************************************************************************************************/
uint8_t I2C_Read(uint8_t var_ackOption_u8)
{
	uint8_t  var_i2cData_u8=0x00;

	RCEN = 1;                   /* Enable data reception */
	while(BF==0);               /* wait for data to be received */
	var_i2cData_u8 = SSPBUF;    /* copy the received data */
	i2c_WaitForIdle();          /* wait till current operation is complete*/
	      
	if(var_ackOption_u8==1)     /*Send the Ack/NoAck depending on the user option*/
	{
		i2c_Ack();
	}
	else
	{
		i2c_NoAck();
	}

	return var_i2cData_u8;       /* Finally return the received Byte */
}










/***************************************************************************************************
                                Local functions
***************************************************************************************************/



/***************************************************************************************************
                         void i2c_WaitForIdle()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :Waits till previous I2C communication to complete..
***************************************************************************************************/
static void i2c_WaitForIdle()
{
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    /* wait till I2C module completes previous operation and becomes idle */
}								







/***************************************************************************************************
                         static void i2c_Ack()
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate a the Positive ACK
                 pulse on SDA after receiving a byte.
***************************************************************************************************/
static void i2c_Ack()
{
	ACKDT = 0;            /* Acknowledge data bit, 0 = ACK */
	ACKEN = 1;            /* Ack data enabled */
	while(ACKEN == 1);    /* wait for ack data to send on bus */
}





/***************************************************************************************************
                        static void i2c_NoAck()
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate a the Negative/NO ACK
                 pulse on SDA after receiving all bytes.
***************************************************************************************************/
static void i2c_NoAck()
{
	ACKDT = 1;            /* Acknowledge data bit, 1 = NAK/NoAK */
	ACKEN = 1;            /* Ack data enabled */
	while(ACKEN == 1);    /* wait for ack data to send on bus */
}
