/***************************************************************************************************
                                   ExploreEmbedded	
 ****************************************************************************************************
 * File:   lcd.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the Library routines for Alpha Numeric LCD

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
    Copyright (C) 2012  ExploreEmbedded

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
 ***************************************************************************************************
15.0: Initial version 
***************************************************************************************************/


/***************************************************************************************************
                                   2x16 LCD internal structure
****************************************************************************************************
    
            |<--------------------16 chars on Each Line-------------------->|
    	   ____________________________________________________________________	
          |\                                                                  /|
          |	\ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___/ |
          |  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |
    Line1 |  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | |
          |  |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___| |
          |  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |
    Line2 |  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | |
          |  |___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___| |
    	  | /                                                                \ |
    	  |/__________________________________________________________________\|
    	                | D7 D6 D5 D4 D3 D2 D1 D0 |     EN   RW   RS          
    		            |<------Lcd Data Bus----->|    Lcd control Lines
    		            |	                      |	      
***************************************************************************************************/								   
#include <stdarg.h>
#include "delay.h"
#include "lcd.h"



/***************************************************************************************************
                          Global Variables and Structures
 ***************************************************************************************************/
uint8_t VAR_LcdTrackLineNum_U8;         //Variable to track the line numbers
uint8_t VAR_LcdTrackCursorPos_U8;       //Variable to track the cursor
LcdConfig_st STK_LCDConfig;             //Structure containing the selected LCD Configuration
uint8_t ARR_LcdLineNumAddress_U8[]={0x80,0x80,0xc0,0x90,0xd0};
/**************************************************************************************************/




/***************************************************************************************************
                            local function prototypes
 ***************************************************************************************************/
static void lcd_DataWrite( uint8_t dat);
static void lcd_BusyCheck();
static void lcd_Reset();
static void lcd_SendNibble(uint8_t var);
static void lcd_SendCmdSignals();
static void lcd_SendDataSignals();
/**************************************************************************************************/





/**************************************************************************************************
void LCD_Init(uint8_t var_lcdMode_u8, uint8_t var_lcdNoOfLines_u8, uint8_t var_MaxCharsPerLine_u8)
***************************************************************************************************
 * Function name:  LCD_Init()
 * I/P Arguments:  uint8_t: required Mode 4/8-bit
                   uint8_t: Number of lines of LCD
                   uint8_t: Number of Chars per line
 * Return value	: none

 * description  :This function is used to initialize the lcd.
                 *It initializes the LCD for selected mode(4/8-bit) and Type(16x2/16x1 etc)
**************************************************************************************************/
void LCD_Init(uint8_t var_lcdMode_u8, uint8_t var_lcdNoOfLines_u8, uint8_t var_MaxCharsPerLine_u8)
{


	M_LcdDataBusDirection = C_PortOutput_U8;     //Configure the Data Bus as output
	M_LcdControlBusDirection = C_PortOutput_U8;  //Configure the Control Bus as output
	STK_LCDConfig.mvar_LcdMode_U8 = var_lcdMode_u8;      // Keep the track of selected Mode(4/8 bit)
	STK_LCDConfig.mvar_MaxSupportedChars_U8 = var_MaxCharsPerLine_u8; //Keep the LCD type
	STK_LCDConfig.mvar_MaxSupportedLines_U8 = var_lcdNoOfLines_u8;
	if(var_lcdNoOfLines_u8 > mENUM_LcdLineTwo)
	{
		ARR_LcdLineNumAddress_U8[mENUM_LcdLineThree] =  0x90 + (var_MaxCharsPerLine_u8 & 0x0fu);
		ARR_LcdLineNumAddress_U8[mENUM_LcdLineFour] =  0xd0 + (var_MaxCharsPerLine_u8 & 0x0fu);
	}

	DELAY_ms(100);

	if(STK_LCDConfig.mvar_LcdMode_U8 == M_EightBitMode)
	{
		LCD_CmdWrite(CMD_LCD_EIGHT_BIT_MODE); // Initialize the LCD for 8-bit 5x7 matrix type
	}
	else if(STK_LCDConfig.mvar_LcdMode_U8 == M_FourBitMode)
	{
		lcd_Reset();
		LCD_CmdWrite(CMD_LCD_FOUR_BIT_MODE); // Initialize the LCD for 4-bit 5x7 matrix type 
	}

	LCD_CmdWrite(CMD_DISPLAY_ON_CURSOR_ON);	 // Display ON cursor ON
	LCD_Clear();	                         // Clear the LCD and go to First line First Position
}




/***************************************************************************************************
                         void LCD_Clear()
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value	: none

 * description  :This function clears the LCD and moves the cursor to beginning of first line
 ***************************************************************************************************/
void LCD_Clear()
{
	LCD_CmdWrite(CMD_LCD_CLEAR);	// Clear the LCD and go to First line First Position
	LCD_GoToLine(mENUM_LcdLineOne);
}





/***************************************************************************************************
                         void LCD_GoToLine(uint8_t var_lineNumber_u8)
 ***************************************************************************************************
 * I/P Arguments: uint8_t: Line number.
 * Return value	: none

 * description  :This function moves the Cursor to beginning of the specified line.
        If the requested line number is out of range, it will not move the cursor.

     Note: The line numbers run from 1 to Maxlines,
	 	   To avoid the confusion the below enums has to be used for selecting lines
           For four line LCD the enums are as below:
           mENUM_LcdLineOne,
           mENUM_LcdLineTwo,
           mENUM_LcdLineThree,
           mENUM_LcdLineFour,
 ***************************************************************************************************/
void LCD_GoToLine(uint8_t var_lineNumber_u8)
{
	if(var_lineNumber_u8 <= STK_LCDConfig.mvar_MaxSupportedLines_U8)
	{
		/* If the line number is within range then
	       Move the Cursor to beginning of the specified line */
		VAR_LcdTrackCursorPos_U8 = 0x00;
		VAR_LcdTrackLineNum_U8 = var_lineNumber_u8;
		LCD_CmdWrite(ARR_LcdLineNumAddress_U8[var_lineNumber_u8]);
	}
}






/***************************************************************************************************
                         void  LCD_GoToNextLine()
 ***************************************************************************************************
 * I/P Arguments: none
 * Return value	: none

 * description  :This function moves the Cursor to beginning of the next line.
        If the cursor is on last line and NextLine command is issued then 
		it will move the cursor to first line.
 ***************************************************************************************************/
void  LCD_GoToNextLine()
{
	/*Increment the current line number.
	  In case it exceeds the limit, rool it back to first line */
	VAR_LcdTrackLineNum_U8++;
	VAR_LcdTrackCursorPos_U8 = 0x00;
	if(VAR_LcdTrackLineNum_U8 > STK_LCDConfig.mvar_MaxSupportedLines_U8)
		VAR_LcdTrackLineNum_U8 = 0x01;
	LCD_CmdWrite(ARR_LcdLineNumAddress_U8[VAR_LcdTrackLineNum_U8]);
}






/***************************************************************************************************
                void LCD_SetCursor(char var_lineNumber_u8,char var_charNumber_u8)
 ***************************************************************************************************
 * I/P Arguments: char row,char col
                 row -> line number(line1=1, line2=2),
                        For 2line LCD the I/P argument should be either 1 or 2.
                 col -> char number.
                        For 16-char LCD the I/P argument should be between 0-15.
 * Return value	: none

 * description  :This function moves the Cursor to specified position

                   Note:If the Input(Line/Char number) are out of range 
				        then no action will be taken
 ***************************************************************************************************/
#if ( Enable_LCD_SetCursor    == 1 )
void LCD_SetCursor(uint8_t var_lineNumber_u8, uint8_t var_charNumber_u8)
{

	if((var_lineNumber_u8 <= STK_LCDConfig.mvar_MaxSupportedLines_U8) &&
			(var_charNumber_u8< STK_LCDConfig.mvar_MaxSupportedChars_U8))
	{
		/*If the line number and char are in range then
		   move the Cursor to specified Position*/
		VAR_LcdTrackCursorPos_U8 = var_charNumber_u8;
		VAR_LcdTrackLineNum_U8 = var_lineNumber_u8;
		LCD_CmdWrite(ARR_LcdLineNumAddress_U8[var_lineNumber_u8]+var_charNumber_u8);
	}
}
#endif









/***************************************************************************************************
                       void LCD_CmdWrite( uint8_t var_lcdCmd_u8)
 ***************************************************************************************************
 * I/P Arguments: 8-bit command supported by LCD.
 * Return value	: none

 * description :This function sends a command to LCD.
                Some of the commonly used commands are defined in lcd.h.
                For more commands refer the data sheet and send the supported command.				
				The behaviour is undefined if unsupported commands are sent.    
 ***************************************************************************************************/
void LCD_CmdWrite( uint8_t var_lcdCmd_u8)
{
	lcd_BusyCheck();
	if(STK_LCDConfig.mvar_LcdMode_U8 == M_EightBitMode)
	{

		M_LcdDataBus = var_lcdCmd_u8;     // Send the complete command if the selected mode is 8-bit
		lcd_SendCmdSignals();  // Signals for command write operation
	}
	else if(STK_LCDConfig.mvar_LcdMode_U8 == M_FourBitMode)
	{
		lcd_SendNibble(var_lcdCmd_u8);  // Send the command in two nibbles as the selected mode is 4-bit
		lcd_SendCmdSignals(); // Signals for command write operation

		lcd_SendNibble(var_lcdCmd_u8 << 4);
		lcd_SendCmdSignals();
	}
}







/***************************************************************************************************
                       void LCD_DisplayChar( char var_lcdData_u8)
 ***************************************************************************************************
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value	: none

 * description  : This function sends a character to be displayed on LCD.
                  Any valid ascii value can be passed to display respective character

 ***************************************************************************************************/
void LCD_DisplayChar(char var_lcdData_u8)
{
	if((VAR_LcdTrackCursorPos_U8>=STK_LCDConfig.mvar_MaxSupportedChars_U8) || (var_lcdData_u8=='\n'))
	{
		/* If the cursor has reached to end of line on page1
		OR NewLine command is issued Then Move the cursor to next line */
		LCD_GoToNextLine();
	}
	if(var_lcdData_u8!='\n') /* Display the character if its not newLine Char */
	{

		lcd_DataWrite(var_lcdData_u8); /* Display the data and keep track of cursor */
		VAR_LcdTrackCursorPos_U8++;
	}
}







/***************************************************************************************************
                       void LCD_DisplayString(char *ptr_stringPointer_u8)
 ***************************************************************************************************
 * I/P Arguments: String(Address of the string) to be displayed.
 * Return value	: none

 * description  :
               This function is used to display the ASCII string on the lcd.
                 1.The ptr_stringPointer_u8 points to the first char of the string
                    and traverses till the end(NULL CHAR)and displays a char each time.

 ***************************************************************************************************/
#if (Enable_LCD_DisplayString==1)
void LCD_DisplayString(char *ptr_stringPointer_u8)
{
	while((*ptr_stringPointer_u8)!=0)
		LCD_DisplayChar(*ptr_stringPointer_u8++); // Loop through the string and display char by char
}
#endif







/***************************************************************************************************
               void LCD_ScrollMessage(uint8_t var_lineNumber_u8, char *ptr_msgPointer_u8)
 ***************************************************************************************************
 * I/P Arguments: 
                  uint8_t  : Line number on which the message has to be scrolled
                  char *: pointer to the string to be scrolled					  

 * Return value	: none

 * description  :This function scrolls the given message on the specified line.
                 If the specified line number is out of range then the message
				 will be scrolled on first line
 ***************************************************************************************************/
#if ( Enable_LCD_ScrollMessage  == 1 )
void LCD_ScrollMessage(uint8_t var_lineNumber_u8, char *ptr_msgPointer_u8)
{
	unsigned char i,j;


	if(var_lineNumber_u8 > STK_LCDConfig.mvar_MaxSupportedLines_U8)
		var_lineNumber_u8 = mENUM_LcdLineOne; // Select first line if the var_lineNumber_u8 is out of range

	LCD_CmdWrite(CMD_DISPLAY_ON_CURSOR_OFF);			 //Disable the Cursor

	for(i=0;ptr_msgPointer_u8[i];i++)
	{      
		/* Loop to display the complete string,	each time 16 chars are displayed and
		pointer is incremented to point to next char */


		LCD_GoToLine(var_lineNumber_u8);     //Move the Cursor to first line

		for(j=0;j<STK_LCDConfig.mvar_MaxSupportedChars_U8 && ptr_msgPointer_u8[i+j];j++)
		{
			//Display first 16 Chars or till Null char is reached
			LCD_DisplayChar(ptr_msgPointer_u8[i+j]);
		}


		while( j<STK_LCDConfig.mvar_MaxSupportedChars_U8)
		{
			/*If the chars to be scrolled are less than MaxLcdChars,
			  then display remaining chars with blank spaces*/
			LCD_DisplayChar(' ');
			j++;
		}

		DELAY_ms(125);
	}
	LCD_CmdWrite(CMD_DISPLAY_ON_CURSOR_ON);			  // Finally enable the Cursor
}
#endif






/***************************************************************************************************
            void  LCD_DisplayNumber(uint32_t var_DecNumber_u32, uint8_t var_numOfDigitsToDisplay_u8 )
 ***************************************************************************************************
 * Function name:  LCD_DisplayNumber()
 * I/P Arguments: uint32_t: Number to be displayed on the LCD.
                  uint8_t : Number of digits to be displayed
 * Return value	: none

 * description  :This function is used to display a max of 10digit decimal number.
                2nd parameter specifies the number of digits from the right side to be displayed
                 The output for the input combinations is as below
                1.(12345,4) then 4-digits ie. 2345 will be displayed
				2.(12345,6) then 6-digits ie. 012345 will be displayed
				3.(12345,C_DisplayDefaultDigits_U8) then 12345 will be displayed.
 ***************************************************************************************************/
#if ((Enable_LCD_DisplayDecimalNumber == 1) || (Enable_LCD_DisplayFloatNumber == 1))
void LCD_DisplayDecimalNumber(uint32_t var_DecNumber_u32, uint8_t var_numOfDigitsToDisplay_u8)
{
	uint8_t i=0,a[10];

	if(var_DecNumber_u32==0)
	{
		/* If the number is zero then update the array with the same for displaying */
		for(i=0;((i<var_numOfDigitsToDisplay_u8) && (i<C_MaxDigitsToDisplay_U8));i++)
	    	a[i] = 0x00;
	}
	else
	{
		for(i=0;i<var_numOfDigitsToDisplay_u8;i++)
		{
			/* Continue extracting the digits from right side
			   till the Specified var_numOfDigitsToDisplay_u8 */
			if(var_DecNumber_u32!=0)
			{
				/* Extract the digits from the number till it becomes zero.
			    First get the remainder and divide the number by 10 each time.
                If var_num_u32 = 123 then extracted remainder will be 3 and number will be 12.
				The process continues till it becomes zero or max digits reached*/
				a[i]=util_GetMod32(var_DecNumber_u32,10);
				var_DecNumber_u32=var_DecNumber_u32/10;
			}
			else if( (var_numOfDigitsToDisplay_u8 == C_DisplayDefaultDigits_U8) ||
					 (var_numOfDigitsToDisplay_u8 > C_MaxDigitsToDisplay_U8))
			{
				/* Stop the iteration if the Max number of digits are reached or 
			     the user expects exact(Default) digits in the number to be displayed */ 
				break;
			}
			else
			{
				/* In case user expects more digits to be displayed than the actual digits in number,
  			    then update the remaining digits with zero.
               Ex: var_num_u32 is 123 and user wants five digits then 00123 has to be displayed */
				a[i]=0;
			}
		}
	}


	while(i)
	{ 
		/* Finally get the ascii values of the digits and display*/
		LCD_DisplayChar(util_Dec2Ascii(a[i-1]));
		i--;
	}
}
#endif





/***************************************************************************************************
         void  LCD_DisplayHexNumber(uint32_t var_hexNumber_u32, uint8_t var_numOfDigitsToDisplay_u8 )
 ***************************************************************************************************
 * Function name:  LCD_DisplayHexNumber()
 * I/P Arguments: uint32_t: Hexadecimal Number to be displayed on the LCD.
                  uint8_t : Number of digits to be displayed
 * Return value	: none

 * description  :This function is used to display a max of 10digit hex number.
                 2nd parameter specifies the number of digits from the right side to be displayed
                 The output for the input combinations is as below
                1.(0x12AB,3) then 3-digits ie. 2AB will be displayed
				2.(0x12AB,6) then 6-digits ie. 0012AB will be displayed
				3.(0x12AB,C_DisplayDefaultDigits_U8) then 12AB will be displayed.
 ***************************************************************************************************/
#if ( Enable_LCD_DisplayHexNumber == 1 ) 
void LCD_DisplayHexNumber(uint32_t var_hexNumber_u32,uint8_t var_numOfDigitsToDisplay_u8)
{
	uint8_t i=0,a[10];

	if(var_hexNumber_u32==0)
	{
		/* If the number zero then update the array with the same for displaying */
		for(i=0;((i<var_numOfDigitsToDisplay_u8) && (i<C_MaxDigitsToDisplay_U8));i++)
		    a[i] = 0x00;
	}
	else
	{
		for(i=0;i<var_numOfDigitsToDisplay_u8;i++)
		{
			/* Continue extracting the digits from right side
			   till the Specified var_numOfDigitsToDisplay_u8 */
			if(var_hexNumber_u32!=0)
			{
				/* Extract the digits from the number till it becomes zero.
			   First get the lower nibble and shift the number 4 times.
			   if var_num_u32 = 0xABC then extracted digit will be 0x0C and number will become 0xAB.
			   The process continues till it becomes zero or max digits reached*/
				a[i]=(uint8_t)(var_hexNumber_u32 & 0x0f);
				var_hexNumber_u32=var_hexNumber_u32 >> 4;
			}
			else if( (var_numOfDigitsToDisplay_u8 == C_DisplayDefaultDigits_U8) ||
					 (var_numOfDigitsToDisplay_u8 > C_MaxDigitsToDisplay_U8))
			{
				/* Stop the iteration if the Max number of digits are reached or 
			     the user expects exact(Default) digits in the number to be displayed */ 
				break;
			}
			else
			{
				/* In case user expects more digits to be displayed than the actual digits in number,
  			    then update the remaining digits with zero.
                Ex: var_num_u32 is 0x123 and user wants five digits then 00123 has to be displayed */
				a[i]=0x00;
			}
		}
	}

	while(i!=0)
	{
		/* Finally get the ascii values of the digits and display*/
		LCD_DisplayChar(util_Hex2Ascii(a[i-1]));
		i--;
	}
}
#endif






/*************************************************************************************************
      void  LCD_DisplayBinaryNumber(uint32_t var_binNumber_u32, uint8_t var_numOfBitsToDisplay_u8)
 *************************************************************************************************
 * Function name:  LCD_DisplayBinaryNumber()
 * I/P Arguments: uint32_t: Hexadecimal Number to be displayed on the LCD.
                  uint8_t : Number of bits to be displayed
 * Return value	: none

 * description  :This function is used to display the binary equivalent of the given number.
                 2nd parameter specifies the number of LSB to be displayed
                 The output for the input combinations is as below
                1.(10,4) then 4-LSB will be displayed ie. 1010
				2.(10,8) then 8-LSB will be displayed ie. 00001010
				3.(10,2) then 2-LSB will be displayed ie. 10
 *************************************************************************************************/
#if (Enable_LCD_DisplayBinaryNumber == 1)
void LCD_DisplayBinaryNumber(uint32_t var_binNumber_u32, uint8_t var_numOfBitsToDisplay_u8)
{
	uint8_t ch;
	  
	while(var_numOfBitsToDisplay_u8!=0)
	{
		/* Start Extracting the bits from the specified bit positions.
	     Get the Acsii values of the bits and display */
		ch = util_GetBitStatus(var_binNumber_u32,(var_numOfBitsToDisplay_u8-1));
		LCD_DisplayChar(util_Dec2Ascii(ch));
		var_numOfBitsToDisplay_u8--;
	}
}
#endif






/*************************************************************************************************
            void  LCD_DisplayFloatNumber(double var_floatNum_f32)
 *************************************************************************************************
 * Function name:  LCD_DisplayFloatNumber()
 * I/P Arguments: float: float Number to be displayed on the LCD.

 * Return value	: none

 * description  :This function is used to display a floating point number
                 It supports 6digits of precision.

    Note: Float will be disabled by default as it takes huge controller resources
	     It can be enabled by changing value of Enable_LCD_DisplayFloatNumber to 1 in lcd.h
 **************************************************************************************************/
#if (Enable_LCD_DisplayFloatNumber == 1)  
void LCD_DisplayFloatNumber(double var_floatNum_f32)
{
	uint32_t var_temp_u32;
	/* Dirty hack to support the floating point by extracting the integer and fractional part.
      1.Type cast the number to int to get the integer part.
	  2.Display the extracted integer part followed by a decimal point(.).
	  3.Later the integer part is made zero by subtracting with the extracted integer value.
	  4.Finally the fractional part is multiplied by 100000 to support 6-digit precision */

	var_temp_u32 = (uint32_t) var_floatNum_f32;
	LCD_DisplayDecimalNumber(var_temp_u32,C_DisplayDefaultDigits_U8);

	LCD_DisplayChar('.');

	var_floatNum_f32 = var_floatNum_f32 - var_temp_u32;
	var_temp_u32 = var_floatNum_f32 * 1000000;
	LCD_DisplayDecimalNumber(var_temp_u32,C_DisplayDefaultDigits_U8);
}
#endif






/*************************************************************************************************
            void LCD_Printf(const char *argList, ...)
 *************************************************************************************************
 * Function name:  LCD_Printf()
 * I/P Arguments: variable length arguments similar to printf

 * Return value	: none

 * description  :This function is similar to printf function in C.
				 It takes the arguments with specified format and prints accordingly
				 The supported format specifiers are as below.
				 1. %c: character
				 2. %d: signed 16-bit number
				 3. %D: signed 32-bit number
				 4. %u: unsigned 16-bit number
				 5. %U: unsigned 32-bit number
				 6. %b: 16-bit binary number
				 7. %B: 32-bit binary number
				 8. %f: Float number
				 9. %x: 16-bit hexadecimal number
				 10. %X: 32-bit hexadecimal number
				 11. %s: String

  Note: By default all the functions will be disabled. The required functions can be enabled by 
        setting the respective compiler switch to 1 in lcd.h file.
		Ex:  setting Enable_LCD_DisplayDecimalNumber to 1 will enable %d
		     setting Enable_LCD_DisplayHexNumber to 1 will enable %x

  Extra feature is available to specify the number of digits to be displayed using printf.
	 ex: %4d: will display the lower four digits of the decimal number.
	     %12b: will display the 12-LSB of the number
		 %d: Will display the exact digits of the number

#####: In case of printing the variables(8-bit) its recommended to type cast and promote them to uint16_t.
        uint8_t var_Num_u8;
		LCD_Printf("num1:%u",(uint16_t)var_Num_u8);
 *************************************************************************************************/
#if ( Enable_LCD_Printf   == 1 ) 
void LCD_Printf(const char *argList, ...)
{
	const char *ptr;
	double var_floatNum_f32;
	va_list argp;
	sint16_t var_num_s16;
	sint32_t var_num_s32;
	uint16_t var_num_u16;
	uint32_t var_num_u32;
	char *str;
	char  ch;
	uint8_t var_numOfDigitsToDisp_u8;

	va_start(argp, argList);

	/* Loop through the list to extract all the input arguments */
	for(ptr = argList; *ptr != '\0'; ptr++)
	{

		ch= *ptr;
		if(ch == '%')         /*Check for '%' as there will be format specifier after it */
		{
		    ptr++;
		    ch = *ptr;
		   if((ch>=0x30) && (ch<=0x39))
			{
			   var_numOfDigitsToDisp_u8 = 0;
			   while((ch>=0x30) && (ch<=0x39))
			    {
				   var_numOfDigitsToDisp_u8 = (var_numOfDigitsToDisp_u8 * 10) + (ch-0x30);
				   ptr++;
				   ch = *ptr;
				}
			}
			else
			{
			  var_numOfDigitsToDisp_u8 = C_MaxDigitsToDisplayUsingPrintf_U8;
			}				


			switch(ch)       /* Decode the type of the argument */
			{
			case 'C':
			case 'c':     /* Argument type is of char, hence read char data from the argp */
				ch = va_arg(argp, uint16_t);
				LCD_DisplayChar(ch);
				break;

			case 'd':    /* Argument type is of signed integer, hence read 16bit data from the argp */
				var_num_s16 = va_arg(argp, sint16_t);
#if (Enable_LCD_DisplayDecimalNumber == 1)
				if(var_num_s16<0)
				 { /* If the number is -ve then display the 2's complement along with '-' sign */ 
				   var_num_s16 = -var_num_s16;
				   LCD_DisplayChar('-');
				 }
				LCD_DisplayDecimalNumber(var_num_s16,var_numOfDigitsToDisp_u8);
#endif
				break;
				
			case 'D':    /* Argument type is of integer, hence read 16bit data from the argp */
				var_num_s32 = va_arg(argp, sint32_t);
#if (Enable_LCD_DisplayDecimalNumber == 1)				
				if(var_num_s32<0)
				 { /* If the number is -ve then display the 2's complement along with '-' sign */
				   var_num_s32 = -var_num_s32;
				   LCD_DisplayChar('-');
				 }
				LCD_DisplayDecimalNumber(var_num_s32,var_numOfDigitsToDisp_u8);
#endif				
				break;	

			case 'u':    /* Argument type is of unsigned integer, hence read 16bit unsigned data */
				var_num_u16 = va_arg(argp, uint16_t);
#if (Enable_LCD_DisplayDecimalNumber == 1)				
				LCD_DisplayDecimalNumber(var_num_u16,var_numOfDigitsToDisp_u8);
#endif				
				break;
			
			case 'U':    /* Argument type is of integer, hence read 32bit unsigend data */
				var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_LCD_DisplayDecimalNumber == 1)				
				LCD_DisplayDecimalNumber(var_num_u32,var_numOfDigitsToDisp_u8);
#endif				
				break;			

			case 'x':  /* Argument type is of hex, hence hexadecimal data from the argp */
				var_num_u16 = va_arg(argp, uint16_t);
#if (Enable_LCD_DisplayHexNumber == 1)				
				LCD_DisplayHexNumber(var_num_u16,var_numOfDigitsToDisp_u8);
#endif				
				break;

			case 'X':  /* Argument type is of hex, hence hexadecimal data from the argp */
				var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_LCD_DisplayHexNumber == 1)						
				LCD_DisplayHexNumber(var_num_u32,var_numOfDigitsToDisp_u8);
#endif				
				break;

			
			case 'b':  /* Argument type is of binary,Read int and convert to binary */
				var_num_u16 = va_arg(argp, uint16_t);
#if (Enable_LCD_DisplayBinaryNumber == 1)						
				if(var_numOfDigitsToDisp_u8 == C_MaxDigitsToDisplayUsingPrintf_U8)
				   var_numOfDigitsToDisp_u8 = 16;
				LCD_DisplayBinaryNumber(var_num_u16,var_numOfDigitsToDisp_u8);
#endif				
				break;

			case 'B':  /* Argument type is of binary,Read int and convert to binary */
				var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_LCD_DisplayBinaryNumber == 1)				
				if(var_numOfDigitsToDisp_u8 == C_MaxDigitsToDisplayUsingPrintf_U8)
				   var_numOfDigitsToDisp_u8 = 16;				
				LCD_DisplayBinaryNumber(var_num_u32,var_numOfDigitsToDisp_u8);	
#endif				
				break;


			case 'F':
			case 'f': /* Argument type is of float, hence read double data from the argp */
				var_floatNum_f32 = va_arg(argp, double);
#if (Enable_LCD_DisplayFloatNumber == 1)				
				LCD_DisplayFloatNumber(var_floatNum_f32);
#endif
				break;


			case 'S':
			case 's': /* Argument type is of string, hence get the pointer to sting passed */
				str = va_arg(argp, char *);
#if (Enable_LCD_DisplayString == 1)
				LCD_DisplayString(str);
#endif				
				break;

			case '%':
				LCD_DisplayChar('%');
				break;
			}
		}
		else
		{
			/* As '%' is not detected display/transmit the char passed */
			LCD_DisplayChar(ch);
		}
	}

	va_end(argp);
}
#endif






/*************************************************************************************************
                       static void lcd_DataWrite( uint8_t dat)
 *************************************************************************************************
 * I/P Arguments: uint8_t: 8-bit value to be sent to LCD.
 * Return value	: none

 * description : This functions is used to send a byte of data to LCD.                 .    
 *************************************************************************************************/
static void lcd_DataWrite( uint8_t dat)
{
	lcd_BusyCheck();
	if(STK_LCDConfig.mvar_LcdMode_U8 == M_EightBitMode)
	{
		M_LcdDataBus = dat;      // Send the complete data byte if the selected mode is 8-bit
		lcd_SendDataSignals();  // Signals for data write operation
	}
	else if(STK_LCDConfig.mvar_LcdMode_U8 == M_FourBitMode)
	{
		lcd_SendNibble(dat);    // Send the data in two nibbles as the selected mode is 4-bit
		lcd_SendDataSignals();  // Signals for data write operation

		lcd_SendNibble(dat << 4);
		lcd_SendDataSignals();
	}
}







/*************************************************************************************************
                       static void lcd_BusyCheck()
 *************************************************************************************************
 * I/P Arguments: none.
 * Return value	: none

 * description : This functions is used check whether LCD is busy.
                 It waits till the LCD is busy by polling the LCD busy flag.
				 After completing the previous operation, LCDs clears its internal busy flag.
 *************************************************************************************************/
static void lcd_BusyCheck()
{
	uint8_t busyflag;
#ifdef LCD_RW                         //Perform Busy check if LCD_RW pin is used

	util_UpdateBit(M_LcdDataBusDirection,LCD_D7,C_PinInput_U8); // Configure busy pin as input
	M_LcdClearBit(LCD_RS);           // Select the Command Register by pulling RS LOW
	M_LcdSetBit(LCD_RW);             // Select the Read Operation for busy flag by setting RW
	do
	{

		M_LcdClearBit(LCD_EN);             // Send a High-to-Low Pulse at Enable Pin
		DELAY_us(10);	
		M_LcdSetBit(LCD_EN); 
		DELAY_us(10);
		busyflag = util_GetBitStatus(M_LcdDataBusInput,LCD_D7);


		if(STK_LCDConfig.mvar_LcdMode_U8 == 4)
		{
			/* Perform extra dummy read for 4-bit */ 	   	
			M_LcdClearBit(LCD_EN);
			DELAY_us(10);
			M_LcdSetBit(LCD_EN); 
			DELAY_us(10);
		}	
	}while(busyflag);

	util_UpdateBit(M_LcdDataBusDirection,LCD_D7,C_PinOutput_U8);
#else
	/* Busy flag cannot be read as LCD_RW is not available hence Extra delay of 1ms is added 
	  to ensure the LCD completes previous operation and ready to receive new commands/data */
	DELAY_ms(1);  
#endif
}






/*************************************************************************************************
                       static void lcd_Reset()
 *************************************************************************************************
 * I/P Arguments: none.
 * Return value	: none

 * description : This functions is used to reset the LCD. 
                 This is used only in 4-bit mode as the LCD by default boots in 8-Bit mode.
----------------------------------------------------------------------------------*/
static void lcd_Reset()
{
	/* LCD reset sequence for 4-bit mode, refer data sheet for more info */
	lcd_SendNibble(0x30);
	lcd_SendCmdSignals();
	DELAY_ms(100);
	lcd_SendNibble(0x30);
	lcd_SendCmdSignals();
	DELAY_us(200);
	lcd_SendNibble(0x30);
	lcd_SendCmdSignals();
	DELAY_us(200);
	lcd_SendNibble(0x20);
	lcd_SendCmdSignals();
	DELAY_us(200);
}






/*************************************************************************************************
                       static void lcd_SendNibble(uint8_t var)
 *************************************************************************************************
 * I/P Arguments: uint8_t: Higher nibble of the data to be send on LCD4-LCD7 data lines
 * Return value	: none

 * description : This functions is used to send the higher nibble of the data to LCD in 4-bit mode
 *************************************************************************************************/
static void lcd_SendNibble(uint8_t var)
{
	util_UpdateBit(M_LcdDataBus,LCD_D4,util_GetBitStatus(var,LCD_D4));
	util_UpdateBit(M_LcdDataBus,LCD_D5,util_GetBitStatus(var,LCD_D5));
	util_UpdateBit(M_LcdDataBus,LCD_D6,util_GetBitStatus(var,LCD_D6));
	util_UpdateBit(M_LcdDataBus,LCD_D7,util_GetBitStatus(var,LCD_D7));
}




/*************************************************************************************************
                       static void lcd_SendCmdSignals()
 *************************************************************************************************
 * I/P Arguments: none
 * Return value	: none

 * description : This functions generates the signals for sending the var_lcdCmd_u8 to LCD
 *************************************************************************************************/
static void lcd_SendCmdSignals()
{
	M_LcdClearBit(LCD_RS);           // Select the Command Register by pulling RS LOW
#ifdef LCD_RW
	M_LcdClearBit(LCD_RW);           // Select the Write Operation  by pulling RW LOW
#endif
	M_LcdSetBit(LCD_EN);             // Send a High-to-Low Pusle at Enable Pin
	DELAY_us(10);
	M_LcdClearBit(LCD_EN);
}




/*************************************************************************************************
                       static void lcd_SendDataSignals()
 **************************************************************************************************
 * I/P Arguments: none
 * Return value	: none

 * description : This functions generates the signals for sending the Data to LCD
 *************************************************************************************************/
static void lcd_SendDataSignals()
{
	M_LcdSetBit(LCD_RS); 			// Select the Data Register by pulling RS HIGH
#ifdef LCD_RW
	M_LcdClearBit(LCD_RW);          // Select the Write Operation  by pulling RW LOW
#endif
	M_LcdSetBit(LCD_EN);            // Send a High-to-Low Pusle at Enable Pin
	DELAY_us(10);
	M_LcdClearBit(LCD_EN);
}
