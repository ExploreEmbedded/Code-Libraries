/***************************************************************************************************
                                   ExploreEmbedded	
 ****************************************************************************************************
 * File:   eeprom.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the function prototypes for Eeprom Read-Write routines

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
#ifndef _EEPROM_H
#define _EEPROM_H

#include <pic16f877a.h>
#include "stdutils.h"


/***************************************************************************************************
                             Commonly used Eeprom macros/Constants
***************************************************************************************************
The below value should be set referring the respective controller data sheet*/
#define C_MaxEepromSize_U16 256
/**************************************************************************************************/


/***************************************************************************************************
                 PreCompile configurations to enable/disable the functions
 ***************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
 2. By default all the API's are disabled. 
***************************************************************************************************/
#define    ENABLE_EEPROM_WriteNBytes   1
#define    ENABLE_EEPROM_ReadNBytes    1
#define    ENABLE_EEPROM_WriteString   0
#define    ENABLE_EEPROM_ReadString    0
#define    ENABLE_EEPROM_Erase         0
/**************************************************************************************************/


/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void EEPROM_WriteByte(uint16_t var_eepromAddress_u16, uint8_t var_eepromData_u8);
uint8_t EEPROM_ReadByte(uint16_t var_eepromAddress_u16);
void EEPROM_WriteNBytes(uint16_t var_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t var_numOfBytes_u16);
void EEPROM_ReadNBytes(uint16_t var_eepromAddress_16, uint8_t *ptr_ramAddress_u8, uint16_t var_numOfBytes_u16);
void EEPROM_WriteString(uint16_t var_eepromAddress_u16, char *ptr_stringPointer_u8);
void EEPROM_ReadString(uint16_t var_eepromAddress_u16, char *ptr_destStringAddress_u8);
void EEPROM_Erase();
/**************************************************************************************************/

#endif







