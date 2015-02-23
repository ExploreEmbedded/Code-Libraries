/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   uart.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the baudrate configurations and function prototypes for UART routines

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
#ifndef _UART_H
#define _UART_H

#include <avr\io.h>
#include "stdutils.h"

/***************************************************************************************************
                             Baudrate configurations
***************************************************************************************************/
#define C_MinBaudRate_U32 2400
#define C_MaxBaudRate_U32 115200UL

#define M_GetBaudRateGeneratorValue(baudrate)  (((F_CPU -((baudrate) * 8L)) / ((baudrate) * 16UL)))
/**************************************************************************************************/





/***************************************************************************************************
                      PreCompile configurations to enable/disable the functions
****************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring 
   its respective macros to 1/0.
 2. By default all the API's are enabled except for FLOAT transmission.
 3. Transmitting of floating number takes huge controller
    resources and need to be enabled only if required. 
	This implies for other interfaces as well. 
***************************************************************************************************/
#define    Enable_UART_TxString          0
#define    Enable_UART_RxString          0
#define    Enable_UART_TxDecimalNumber   1
#define    Enable_UART_TxHexNumber       0
#define    Enable_UART_TxBinaryNumber    0
#define    Enable_UART_TxFloatNumber     0
#define    Enable_UART_Printf            1
/**************************************************************************************************/





/***************************************************************************************************
                             Commonly used UART macros/Constants
***************************************************************************************************/
#define C_DefaultDigitsToTransmit_U8          0xffu    // Will transmit the exact digits in the number
#define C_MaxDigitsToTransmit_U8              10u      // Max decimal/hexadecimal digits to be transmitted
#define C_NumOfBinDigitsToTransmit_U8         16u      // Max bits of a binary number to be transmitted
#define C_MaxDigitsToTransmitUsingPrintf_U8   C_DefaultDigitsToTransmit_U8 /* Max dec/hexadecimal digits to be displayed using printf */
/**************************************************************************************************/





/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/

void UART_Init(uint32_t var_baudRate_u32);
void UART_SetBaudRate(uint32_t var_baudRate_u32);
void UART_TxChar(char var_uartData_u8);
char UART_RxChar();
void UART_TxString(char *ptr_stringPointer_u8);
void UART_RxString(char *ptr_stringPointer_u8);
void UART_TxDecimalNumber(uint32_t var_decNumber_u32, uint8_t var_numOfDigitsToTransmit_u8);
void UART_TxHexNumber(uint32_t var_hexNumber_u32,uint8_t var_numOfDigitsToTransmit_u8);
void UART_TxBinaryNumber(uint32_t var_binNumber_u32, uint8_t var_numOfBitsToTransmit_u8);
void UART_TxFloatNumber(float var_floatNumber_f32);
void UART_Printf(const char *argList, ...);
/**************************************************************************************************/


#endif
