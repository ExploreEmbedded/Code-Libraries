/***************************************************************************************************
                                   ExploreEmbedded	
 ****************************************************************************************************
 * File:   lcd.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the LCD port configurations, CMD list, function prototypes

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


#ifndef _LCD_H_
#define _LCD_H_

#include <avr/io.h>
#include "stdutils.h"


/***************************************************************************************************
                               LCD PORT Configuration 
 ***************************************************************************************************/
#define M_LcdDataBus PORTB
#define M_LcdDataBusDirection DDRB
#define M_LcdDataBusInput PINB

#define M_LcdControlBus PORTD
#define M_LcdControlBusDirection DDRD


#define LCD_D4  4
#define LCD_D5  5
#define LCD_D6  6
#define LCD_D7  7

#define LCD_RS  5
#define LCD_RW  6  /* Comment this line if RW pin is not used(grounded) */
#define LCD_EN  7
/**************************************************************************************************/






/***************************************************************************************************
                 PreCompile configurations to enable/disable the functions
 ***************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
 2. By default all the API's are disabled.
 3. Displaying of floating number takes huge controller resources and need to be enabled only 
    if required. This implies for other interfaces as well. 
 ***************************************************************************************************/
#define    Enable_LCD_SetCursor              0
#define    Enable_LCD_DisplayString          0
#define    Enable_LCD_ScrollMessage          0
#define    Enable_LCD_DisplayDecimalNumber   0
#define    Enable_LCD_DisplayHexNumber       1
#define    Enable_LCD_DisplayBinaryNumber    0
#define    Enable_LCD_DisplayFloatNumber     0
#define    Enable_LCD_Printf                 1
/**************************************************************************************************/







/***************************************************************************************************
                        List of commonly used LCD Commands 
 ***************************************************************************************************/
#define CMD_LCD_CLEAR                0x01u
#define CMD_LCD_RETURN_HOME          0x02u
#define CMD_DISPLAY_ON_CURSOR_OFF    0x0Cu
#define CMD_DISPLAY_ON_CURSOR_ON     0x0Eu
#define CMD_DISPLAY_ON_CURSOR_BLINK  0x0Fu
#define CMD_LCD_FOUR_BIT_MODE        0x28u
#define CMD_LCD_EIGHT_BIT_MODE       0x38u
/**************************************************************************************************/







/***************************************************************************************************
                             Commonly used LCD macros/Constants
**************************************************************************************************/
#define M_EightBitMode 8u
#define M_FourBitMode  4u


#define C_DisplayDefaultDigits_U8            0xffu // Will display the exact digits in the number
#define C_MaxDigitsToDisplay_U8              10u   // Max decimal/hexadecimal digits to be displayed
#define C_NumOfBinDigitsToDisplay_U8         16u   // Max bits of a binary number to be displayed
#define C_MaxDigitsToDisplayUsingPrintf_U8   C_DisplayDefaultDigits_U8 /* Max dec/hexadecimal digits to be displayed using printf */


#define M_LcdClearBit(x)   util_BitClear((M_LcdControlBus),(x))
#define M_LcdSetBit(x)     util_BitSet((M_LcdControlBus),(x))
/**************************************************************************************************/







/***************************************************************************************************
                                 Struct/Enums used
 ***************************************************************************************************/

typedef enum{
	mENUM_LcdDummy,
	mENUM_LcdLineOne,
	mENUM_LcdLineTwo,
	mENUM_LcdLineThree,
	mENUM_LcdLineFour,
	mENUM_LcdMaxLines
}LCD_Lines;


typedef struct{
	uint8_t mvar_MaxSupportedLines_U8;
	uint8_t mvar_MaxSupportedChars_U8;
	uint8_t mvar_LcdMode_U8;
}LcdConfig_st;

/**************************************************************************************************/





/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void LCD_Init(uint8_t var_lcdMode_u8, uint8_t var_lcdNoOfLines_u8, uint8_t var_MaxCharsPerLine_u8);
void LCD_CmdWrite( uint8_t var_lcdCmd_u8);
void LCD_DisplayChar( char var_lcdData_u8);
void LCD_Clear();
void LCD_GoToLine(uint8_t var_lineNumber_u8);
void LCD_GoToNextLine();
void LCD_SetCursor(uint8_t var_lineNumber_u8, uint8_t var_charNumber_u8);
void LCD_DisplayString(char *ptr_stringPointer_u8);
void LCD_ScrollMessage(uint8_t var_lineNumber_u8, char *ptr_msgPointer_u8);
void LCD_DisplayDecimalNumber(uint32_t var_DecNumber_u32, uint8_t var_numOfDigitsToDisplay_u8);
void LCD_DisplayHexNumber(uint32_t var_hexNumber_u32,uint8_t var_numOfDigitsToDisplay_u8);
void LCD_DisplayBinaryNumber(uint32_t var_binNumber_u32, uint8_t var_numOfBitsToDisplay_u8);
void LCD_DisplayFloatNumber(float var_floatNum_f32);
void LCD_Printf(const char *argList, ...);
/**************************************************************************************************/

#endif
