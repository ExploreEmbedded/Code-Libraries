/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   uart.c (AVR controllers)
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the Library routines for UART

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


/**************************************************************************************************
                             Revision History
****************************************************************************************************
15.0: Initial version 
***************************************************************************************************/
#include <stdarg.h>
#include "uart.h"




/***************************************************************************************************
                         void UART_Init(uint32_t var_baudRate_u32)
****************************************************************************************************
 * I/P Arguments: uint32_t : Baudrate to be configured.
 * Return value	: none

 * description  :This function is used to initialize the UART at specified baud rate.
                 If the requested baud rate is not within the supported range then
                 the default baud rate of 9600 is set.


		    Refer uart.h file for Supported(range) baud rates.		
***************************************************************************************************/
void UART_Init(uint32_t var_baudRate_u32)
{	
	TMOD |= 0x20; //Timer1 in Mode2.
    SCON=0x50;    // Asynchronous mode, 8-bit data and 1-stop bit
    TR1=1;        //Turn ON the timer for Baud rate generation
	UART_SetBaudRate(var_baudRate_u32);
}






/***************************************************************************************************
                         void UART_SetBaudRate(uint32_t var_baudRate_u32)
 ***************************************************************************************************
 * I/P Arguments: uint32_t : var_baudRate_u32 to be configured.
 * Return value	: none

 * description  :This function is used to Set/Change the baudrate on the fly.
                 If the requested baud rate is not within the supported range then
                 the default baudrate of 9600 is set.

		    Refer uart.h file for Supported range of baud rates.
***************************************************************************************************/
void UART_SetBaudRate(uint32_t var_baudRate_u32)
{
	sint8_t RegValue;

	if((var_baudRate_u32 >= C_MinBaudRate_U32) && (var_baudRate_u32<=C_MaxBaudRate_U32))
	{
		/* Check if the requested baudate is within range,
	     If yes then calculate the value to be loaded into baud rate generator. */
		RegValue = M_GetBaudRateGeneratorValue(var_baudRate_u32);
	}
	else
	{
		/*	 Invalid baudrate requested, hence set it to default baudrate of 9600 */
		RegValue = M_GetBaudRateGeneratorValue(9600);
	}

	TH1 = RegValue; 
}





/***************************************************************************************************
                              char UART_RxChar()
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value	: char: Ascii value of the character received

 * description :This function is used to receive a char from UART module.
                It waits till a char is received and returns it after reception.
***************************************************************************************************/
char UART_RxChar()
{
    while(RI==0);	  // Wait till the data is received
    RI=0;             // Clear Receive Interrupt Flag for next cycle
    
	return(SBUF);	  // return the received char
}








/***************************************************************************************************
                         void UART_TxChar(char var_uartData_u8)
****************************************************************************************************
 * I/P Arguments: char--> Ascii value of the character to be transmitted.
 * Return value	: none.

 * description  :This function is used to transmit a char through UART module.
***************************************************************************************************/
void UART_TxChar(char var_uartData_u8)
{
	SBUF=var_uartData_u8; // Load the data to be transmitted
    while(TI==0);       // Wait till the data is trasmitted
    TI=0;		        //Clear the Tx flag for next cycle.
}







/***************************************************************************************************
                         void UART_TxString(char *ptr_stringPointer_u8)
****************************************************************************************************
 * I/P Arguments: String(Address of the string) to be transmitted.
 * Return value	: none

 * description :This function is used to transmit a NULL terminated string through UART.
               1.The ptr_stringPointer_u8 points to the first char of the string
                    and traverses till the end(NULL CHAR) and transmits a char each time
***************************************************************************************************/
#if (Enable_UART_TxString==1)
void UART_TxString(char *ptr_stringPointer_u8)
{
	while(*ptr_stringPointer_u8)
		UART_TxChar(*ptr_stringPointer_u8++);// Loop through the string and transmit char by char
}
#endif






/***************************************************************************************************
                         void UART_RxString(char *ptr_stringPointer_u8)
****************************************************************************************************
 * I/P Arguments: char *:  Address of the string/buffer where the received data needs to be stored
 * Return value	: none

 * description  :
              1.This function is used to receive a ASCII string through UART till the carriage_return/New_line
              2.The stream of data is copied to the buffer till carriage_return/New_line is encountered.
			  3. Once the Carriage_return/New_Line is received the string will be null terminated.

 *****NOTE*******:
  1.The received char is ECHOED back,
    if not required then comment UART_TxChar(ch) in the code.
  2.BackSlash is not taken care.
***************************************************************************************************/
#if (Enable_UART_RxString==1)
void UART_RxString(char *ptr_stringPointer_u8)
{
	char ch;
	while(1)
	{
		ch=UART_RxChar();    //Receive a char
		UART_TxChar(ch);     //Echo back the received char

		if((ch=='\r') || (ch=='\n')) //read till enter key is pressed
		{						     //once enter key is pressed null terminate the string
			*ptr_stringPointer_u8=0;           //and break the loop
			break;				  
		}
		*ptr_stringPointer_u8=ch;              //copy the char into string and increment the pointer
		ptr_stringPointer_u8++;
	}
}
#endif






/***************************************************************************************************
        void  UART_TxDecimalNumber(uint32_t var_decNumber_u32, uint8_t var_numOfDigitsToTransmit_u8 )
 ***************************************************************************************************
 * I/P Arguments: uint32_t: Number to be transmitted on UART.
                  uint8_t : Number of digits to be transmitted
 * Return value	: none

 * description  :This function is used to transmit a max of 10digit decimal number.
                2nd parameter specifies the number of digits from the right side to be transmitted
                 The output for the input combinations is as below
                1.(12345,4) then 4-digits ie. 2345 will be transmitted
				2.(12345,6) then 6-digits ie. 012345 will be transmitted
				3.(12345,C_DefaultDigitsToTransmit_U8) then 12345 will be transmitted.
***************************************************************************************************/
#if ((Enable_UART_TxDecimalNumber==1) || (Enable_UART_TxFloatNumber==1))
void UART_TxDecimalNumber(uint32_t var_decNumber_u32, uint8_t var_numOfDigitsToTransmit_u8)
{
	uint8_t i=0,a[10];

	if(var_decNumber_u32==0)
	{
		/* If the number is zero then update the array with the same for transmitting */
		for(i=0;((i<var_numOfDigitsToTransmit_u8) && (i<C_MaxDigitsToTransmit_U8)) ;i++)
		   a[i] = 0x00;
	}
	else
	{
		for(i=0;i<var_numOfDigitsToTransmit_u8;i++)
		{
			/* Continue extracting the digits from right side
			   till the Specified var_numOfDigitsToTransmit_u8 */
			if(var_decNumber_u32!=0)
			{
				/* Extract the digits from the number till it becomes zero.
			    First get the remainder and divide the number by 10 each time.
                If var_number_u32 = 123 then extracted remainder will be 3 and number will be 12.
				The process continues till it becomes zero or max digits reached*/
				a[i]=util_GetMod32(var_decNumber_u32,10);
				var_decNumber_u32=var_decNumber_u32/10;
			}
			else if( (var_numOfDigitsToTransmit_u8 == C_DefaultDigitsToTransmit_U8) ||
					(var_numOfDigitsToTransmit_u8 > C_MaxDigitsToTransmit_U8))
			{
				/* Stop the iteration if the Max number of digits are reached or
			     the user expects exact(Default) digits in the number to be transmitted */ 
				break;
			}
			else
			{
				/*In case user expects more digits to be transmitted than the actual digits in number,
  			    then update the remaining digits with zero.
                Ex: var_number_u32 is 123 and user wants five digits then 00123 has to be transmitted */
				a[i]=0;
			}
		}
	}

	while(i)
	{ 
		/* Finally get the ascii values of the digits and transmit*/
		UART_TxChar(util_Dec2Ascii(a[i-1]));
		i--;
	}
}
#endif






/***************************************************************************************************
   void  UART_TxHexNumber(uint32_t var_hexNumber_u32, uint8_t var_numOfDigitsToTransmit_u8 )
 ***************************************************************************************************
 * Function name:  UART_TxHexNumber()
 * I/P Arguments: uint32_t: Hexadecimal Number to be transmitted on UART.
                  uint8_t : Number of digits to be transmitted
 * Return value	: none

 * description  :This function is used to transmit a max of 10digit hex number.
                 2nd parameter specifies the number of digits from the right side to be transmitted
                 The output for the input combinations is as below
                1.(0x12AB,3) then 3-digits ie. 2AB will be transmitted
				2.(0x12AB,6) then 6-digits ie. 0012AB will be transmitted
				3.(0x12AB,C_DefaultDigitsToTransmit_U8) then 12AB will be transmitted.
***************************************************************************************************/
#if (Enable_UART_TxHexNumber==1)
void UART_TxHexNumber(uint32_t var_hexNumber_u32,uint8_t var_numOfDigitsToTransmit_u8)
{
	uint8_t i=0,a[10];

	if(var_hexNumber_u32==0)
	{
		/* If the number zero then update the array with the same for transmitting */
		for(i=0;((i<var_numOfDigitsToTransmit_u8) && (i<C_MaxDigitsToTransmit_U8)) ;i++)
		  a[i]=0x00;
	}
	else
	{
		for(i=0;i<var_numOfDigitsToTransmit_u8;i++)
		{
			/* Continue extracting the digits from right side till the Specified var_numOfDigitsToTransmit_u8 */
			if(var_hexNumber_u32!=0)
			{
				/* Extract the digits from the number till it becomes zero.
			    First get the lower nibble and shift the number 4 times.
			   If var_number_u32 = 0xABC then extracted digit will be 0x0C and number will become 0xAB.
			   The process continues till it becomes zero or max digits reached*/
				a[i]=(uint8_t)(var_hexNumber_u32 & 0x0f);
				var_hexNumber_u32=var_hexNumber_u32 >> 4;
			}
			else if( (var_numOfDigitsToTransmit_u8 == C_DefaultDigitsToTransmit_U8) ||
					(var_numOfDigitsToTransmit_u8 > C_MaxDigitsToTransmit_U8))
			{
				/* Stop the iteration if the Max number of digits are reached or
			     the user expects exact(Default) digits in the number to be transmitted */ 
				break;
			}
			else
			{
				/* In case user expects more digits to be transmitted than the actual digits in number,
  			           then update the remaining digits with zero.
                Ex: var_number_u32 is 0x123 and user wants five digits then 00123 has to be transmitted */
				a[i]=0x00;
			}
		}
	}

	while(i!=0)
	{
		/* Finally get the ascii values of the digits and transmit*/
		UART_TxChar(util_Hex2Ascii(a[i-1]));
		i--;
	}
}
#endif






/***************************************************************************************************
            void  UART_TxBinaryNumber(uint32_t var_binNumber_u32, uint8_t var_numOfBitsToTransmit_u8)
 ***************************************************************************************************
 * Function name:  UART_TxBinaryNumber()
 * I/P Arguments: uint32_t: Hexadecimal Number to be transmitted on UART.
                  uint8_t : Number of bits to be transmitted
 * Return value	: none

 * description  :This function is used to transmit the binary equivalent of the given number.
                 2nd parameter specifies the number of LSB to be transmitted
                 The output for the input combinations is as below
                1.(10,4) then 4-LSB will be transmitted ie. 1010
				2.(10,8) then 8-LSB will be transmitted ie. 00001010
				3.(10,2) then 2-LSB will be transmitted ie. 10
***************************************************************************************************/
#if (Enable_UART_TxBinaryNumber==1)
void UART_TxBinaryNumber(uint32_t var_binNumber_u32, uint8_t var_numOfBitsToTransmit_u8)
{
	uint8_t ch;

	while(var_numOfBitsToTransmit_u8!=0)
	{
		/* Start Extracting the bits from the specified bit positions.
	     Get the Acsii values of the bits and transmit */
		ch = util_GetBitStatus(var_binNumber_u32,(var_numOfBitsToTransmit_u8-1));
		UART_TxChar(util_Dec2Ascii(ch));
		var_numOfBitsToTransmit_u8--;
	}
}
#endif






/***************************************************************************************************
            void  UART_TxFloatNumber(float var_floatNumber_f32)
 ***************************************************************************************************
 * Function name:  UART_TxFloatNumber()
 * I/P Arguments: float: float Number to be transmitted on UART.

 * Return value	: none

 * description  :This function is used to transmit a floating point number

 * Note         :It supports 6digits of precision.  
         Float will be disabled by default as it takes huge controller resources
	     It can be enabled by changing value of Enable_UART_TxFloatNumber to 1 in uart.h	 
 ***************************************************************************************************/
#if (Enable_UART_TxFloatNumber==1)
void UART_TxFloatNumber(float var_floatNumber_f32)
{
	uint32_t var_tempNumber_u32;
	/* Dirty hack to support the floating point by extracting the integer and fractional part.
      1.Type cast the number to int to get the integer part.
	  2.transmit the extracted integer part followed by a decimal point(.).
	  3.Later the integer part is made zero by subtracting with the extracted integer value.
	  4.Finally the fractional part is multiplied by 100000 to support 6-digit precision */

	var_tempNumber_u32 = (uint32_t) var_floatNumber_f32;
	UART_TxDecimalNumber(var_tempNumber_u32,C_DefaultDigitsToTransmit_U8);

	UART_TxChar('.');

	var_floatNumber_f32 = var_floatNumber_f32 - var_tempNumber_u32;
	var_tempNumber_u32 = var_floatNumber_f32 * 1000000;
	UART_TxDecimalNumber(var_tempNumber_u32,C_DefaultDigitsToTransmit_U8);
}
#endif






/***************************************************************************************************
            void UART_Printf(const char *argList, ...)
 ***************************************************************************************************
 * Function name:  UART_Printf()
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
        setting the respective compiler switch to 1 in uart.h file.
		Ex:  setting Enable_UART_TxDecimalNumber to 1 will enable %d
		     setting Enable_UART_TxHexNumber to 1 will enable %x

  Extra feature is available to specify the number of digits to be transmitted using printf.
	 ex: %4d: will transmit the lower four digits of the decimal number.
	     %12b: will transmit the 12-LSB of the number
		 %d: Will transmit the exact digits of the number
***************************************************************************************************/
#if ( Enable_UART_Printf   == 1 ) 
void UART_Printf(const char *argList, ...)
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
	uint8_t var_numOfDigitsToTransmit_u8;

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
			   var_numOfDigitsToTransmit_u8 = 0;
			   while((ch>=0x30) && (ch<=0x39))
			    {
				   var_numOfDigitsToTransmit_u8 = (var_numOfDigitsToTransmit_u8 * 10) + (ch-0x30);
				   ptr++;
				   ch = *ptr;
				}
			}
			else
			{
			  var_numOfDigitsToTransmit_u8 = C_MaxDigitsToTransmitUsingPrintf_U8;
			}				


			switch(ch)       /* Decode the type of the argument */
			{
			case 'C':
			case 'c':     /* Argument type is of char, hence read char data from the argp */
				ch = va_arg(argp, uint16_t);
				UART_TxChar(ch);
				break;

			case 'd':    /* Argument type is of signed integer, hence read 16bit data from the argp */
				var_num_s16 = va_arg(argp, sint16_t);
#if (Enable_UART_TxDecimalNumber == 1)
				if(var_num_s16<0)
				 { /* If the number is -ve then display the 2's complement along with '-' sign */ 
				   var_num_s16 = -var_num_s16;
				   UART_TxChar('-');
				 }
				UART_TxDecimalNumber(var_num_s16,var_numOfDigitsToTransmit_u8);
#endif
				break;
				
			case 'D':    /* Argument type is of integer, hence read 16bit data from the argp */
				var_num_s32 = va_arg(argp, sint32_t);
#if (Enable_UART_TxDecimalNumber == 1)				
				if(var_num_s32<0)
				 { /* If the number is -ve then display the 2's complement along with '-' sign */
				   var_num_s32 = -var_num_s32;
				   UART_TxChar('-');
				 }
				UART_TxDecimalNumber(var_num_s32,var_numOfDigitsToTransmit_u8);
#endif				
				break;	

			case 'u':    /* Argument type is of unsigned integer, hence read 16bit unsigned data */
				var_num_u16 = va_arg(argp, uint16_t);
#if (Enable_UART_TxDecimalNumber == 1)				
				UART_TxDecimalNumber(var_num_u16,var_numOfDigitsToTransmit_u8);
#endif				
				break;
			
			case 'U':    /* Argument type is of integer, hence read 32bit unsigend data */
				var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_UART_TxDecimalNumber == 1)				
				UART_TxDecimalNumber(var_num_u32,var_numOfDigitsToTransmit_u8);
#endif				
				break;			

			case 'x':  /* Argument type is of hex, hence hexadecimal data from the argp */
				var_num_u16 = va_arg(argp, uint16_t);
#if (Enable_UART_TxHexNumber == 1)				
				UART_TxHexNumber(var_num_u16,var_numOfDigitsToTransmit_u8);
#endif				
				break;

			case 'X':  /* Argument type is of hex, hence hexadecimal data from the argp */
				var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_UART_TxHexNumber == 1)						
				UART_TxHexNumber(var_num_u32,var_numOfDigitsToTransmit_u8);
#endif				
				break;

			
			case 'b':  /* Argument type is of binary,Read int and convert to binary */
				var_num_u16 = va_arg(argp, uint16_t);
#if (Enable_UART_TxBinaryNumber == 1)						
				if(var_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
				   var_numOfDigitsToTransmit_u8 = 16;
				UART_TxBinaryNumber(var_num_u16,var_numOfDigitsToTransmit_u8);
#endif				
				break;

			case 'B':  /* Argument type is of binary,Read int and convert to binary */
				var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_UART_TxBinaryNumber == 1)				
				if(var_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
				   var_numOfDigitsToTransmit_u8 = 16;				
				UART_TxBinaryNumber(var_num_u32,var_numOfDigitsToTransmit_u8);	
#endif				
				break;


			case 'F':
			case 'f': /* Argument type is of float, hence read double data from the argp */
				var_floatNum_f32 = va_arg(argp, double);
#if (Enable_UART_TxFloatNumber == 1)				
				UART_TxFloatNumber(var_floatNum_f32);
#endif
				break;


			case 'S':
			case 's': /* Argument type is of string, hence get the pointer to sting passed */
				str = va_arg(argp, char *);
#if (Enable_UART_TxString == 1)
				UART_TxString(str);
#endif				
				break;

			case '%':
				UART_TxChar('%');
				break;
			}
		}
		else
		{
			/* As '%' is not detected display/transmit the char passed */
			UART_TxChar(ch);
		}
	}

	va_end(argp);
}
#endif
