/***************************************************************************************************
                                   ExploreEmbedded	
 ****************************************************************************************************
 * File:   eeprom.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library routines for Eeprom Read-Write

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

#include "eeprom.h"
#include "delay.h"



/***************************************************************************************************
  void EEPROM_WriteByte(uint16_t var_eepromAddress_u16, uint8_t var_eepromData_u8)
 ***************************************************************************************************
 * I/P Arguments: uint16_t: eeprom_address at which eeprom_data is to be written
                  uint8_t: byte of data to be to be written in eeprom.
 * Return value	: none

 * description: This function is used to write the data at specified EEPROM_address..

 **************************************************************************************************/
void EEPROM_WriteByte(uint16_t var_eepromAddress_u16, uint8_t var_eepromData_u8)
{
    while(RD || WR);           // check the WR&RD bit to see if a RD/WR is in progress
	EEADR=var_eepromAddress_u16; // Write the address to EEADR.
                               // Make sure that the address is not larger than the memory size 
	EEDATA=var_eepromData_u8;    // load the 8-bit data value to be written in the EEDATA register.
	WREN=1;                    // Set the WREN bit to enable eeprom operation.
    EECON2=0x55;               //Execute the special instruction sequence
	EECON2=0xaa;               //Refer the datasheet for more info
	WR=1;                      // Set the WR bit to trigger the eeprom write operation.
    DELAY_us(10);             
    WREN=0;                    // Disable eeprom operation.
}






/***************************************************************************************************
               uint8_t EEPROM_ReadByte(uint16_t var_eepromAddress_u16)
 ***************************************************************************************************
 * I/P Arguments: uint16_t: eeprom_address from where eeprom_data is to be read.
 * Return value	: uint8_t: data read from Eeprom.

 * description: This function is used to read the data from specified EEPROM_address.        
 ***************************************************************************************************/
uint8_t EEPROM_ReadByte(uint16_t var_eepromAddress_u16)
{
    while(RD || WR);           // check the WR&RD bit to see if a RD/WR is in progress
	EEADR=var_eepromAddress_u16; // Write the address to EEADR.
                               // Make sure that the address is not larger than the memory size 
	RD = 1;                    // Set the WR bit to trigger the eeprom read operation.
    DELAY_us(50);
    return(EEDATA);            // Return the data read form eeprom.
}





/***************************************************************************************************
void EEPROM_WriteNBytes(uint16_t var_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t var_numOfBytes_u16)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the N-bytes are to be written.
                  uint8_t*: Buffer(Pointer) containing the N-Bytes of data to be written in Eeprom.
                  uint16_t :  Number of bytes to be written

 * Return value	: none

 * description:
            This function is used to write N-bytes of data at specified EEPROM_address.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_WriteNBytes == 1)
void EEPROM_WriteNBytes(uint16_t var_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t var_numOfBytes_u16)
{
	while(var_numOfBytes_u16 !=  0)
	{
		EEPROM_WriteByte(var_eepromAddress_u16,*ptr_ramAddress_u8); //Write a byte from RAM to EEPROM
		var_eepromAddress_u16++;					   //Increment the Eeprom Address
		ptr_ramAddress_u8++;						   //Increment the RAM Address
		var_numOfBytes_u16--;					   //Decrement NoOfBytes after writing each Byte
	}
}
#endif



/***************************************************************************************************
void EEPROM_ReadNBytes(uint16_t EepromAddr, uint8_t *RamAddr, uint16_t NoOfBytes)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the N-bytes is to be read.
                  uint8_t*: Pointer to copy the N-bytes read from Eeprom.
                  uint16_t :  Number of bytes to be Read

 * Return value	: none

 * description:
            This function is used to Read N-bytes of data from specified EEPROM_address.
            The data read from the eeprom will be copied into the specified RamAddress.

	##Note:	Care should be taken to allocate enough buffer to read the data.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_ReadNBytes == 1)
void EEPROM_ReadNBytes(uint16_t var_eepromAddress_16, uint8_t *ptr_ramAddress_u8, uint16_t var_numOfBytes_u16)
{
	while(var_numOfBytes_u16 !=  0)
	{
		*ptr_ramAddress_u8 = EEPROM_ReadByte(var_eepromAddress_16);//Read a byte from EEPROM to RAM
		var_eepromAddress_16++;						//Increment the EEPROM Address
		ptr_ramAddress_u8++;							//Increment the RAM Address
		var_numOfBytes_u16--;						//Decrement NoOfBytes after Reading each Byte

	}
}
#endif







/***************************************************************************************************
 void EEPROM_WriteString(uint16_t var_eepromAddress_u16, char *ptr_stringPointer_u8)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address where the String is to be written.
                  char*: Pointer to String which has to be written.

 * Return value	: none

 * description:This function is used to Write a String at specified EEPROM_address.

   NOTE: Null char is also written into the eeprom.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_WriteString == 1)
void EEPROM_WriteString(uint16_t var_eepromAddress_u16, char *ptr_stringPointer_u8)
{

	do
	{
		EEPROM_WriteByte(var_eepromAddress_u16,*ptr_stringPointer_u8); //Write a byte from RAM to EEPROM
		ptr_stringPointer_u8++;								//Increment the RAM Address
		var_eepromAddress_u16++;								//Increment the Eeprom Address
	}while(*(ptr_stringPointer_u8-1) !=0);
}
#endif




/***************************************************************************************************
void EEPROM_ReadString(uint16_t var_eepromAddress_u16, char *ptr_destStringAddress_u8)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the String is to be read.
                  char*: Pointer into which the String is to be read.

 * Return value	: none

 * description:This function is used to Read a String from specified EEPROM_address.
           The string read from eeprom will be copied to specified buffer along with NULL character
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_ReadString == 1)
void EEPROM_ReadString(uint16_t var_eepromAddress_u16, char *ptr_destStringAddress_u8)
{
	char eeprom_data;

	do
	{
		eeprom_data = EEPROM_ReadByte(var_eepromAddress_u16); //Read a byte from EEPROM to RAM
		*ptr_destStringAddress_u8 = eeprom_data;			 //Copy the data into String Buffer
		ptr_destStringAddress_u8++;						 //Increment the RAM Address
		var_eepromAddress_u16++;							 //Increment the Eeprom Address
	}while(eeprom_data!=0);
}
#endif





/***************************************************************************************************
                                   void EEPROM_Erase()
 ***************************************************************************************************
 * I/P Arguments: none

 * Return value	: none

 * description: This function is used to erase the entire Eeprom memory.
               Complete Eeprom(C_MaxEepromSize_U16) is filled with 0xFF to accomplish the Eeprom Erase.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_Erase == 1)
void EEPROM_Erase()
{
	uint16_t var_eepromAddress_u16;

	for(var_eepromAddress_u16=0;var_eepromAddress_u16<C_MaxEepromSize_U16;var_eepromAddress_u16++)
	{
		EEPROM_WriteByte(var_eepromAddress_u16,0xffu); // Write Each memory location with OxFF
	}
}
#endif
