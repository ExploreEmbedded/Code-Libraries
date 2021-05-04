/***************************************************************************************************
                                   ExploreEmbedded	
 ****************************************************************************************************
 * File:   keypad.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library routines for 4x4 Hex-Keypad

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


/***************************************************************************************************
                             PORT configurations/Connections
 ****************************************************************************************************
 Note:
  1.Rows should be connected to lower 4-bits of PORTx
  1.Cols should be connected to higher 4-bits of PORTx
  The Row/Col information has to be updated in keypad.h
            ___________________
           |    |    |    |    |
           | 0  | 1  | 2  | 3  |--------- R0
           |____|____|____|____|
           |    |    |    |    |
           | 4  | 5  | 6  | 7  |--------- R1
           |____|____|____|____|
           |    |    |    |    |
	   | 8  | 9  | A  | B  |--------- R2
           |____|____|____|____|
           |    |    |    |    |
           | C  | D  | E  | F  |--------- R3
           |____|____|____|____|
             |    |    |    |
             |    |    |    |____________ C3
             |    |    |
             |    |    |_________________ C2
             |    |
             |    |______________________ C1
             |
             |___________________________ C0

 ****************************************************************************************************/


#include "keypad.h"
#include "delay.h"




/***************************************************************************************************
                           local function prototypes
 ***************************************************************************************************/
static uint8_t keypad_ScanKey();
/**************************************************************************************************/





/***************************************************************************************************
                   void KEYPAD_Init()
 ***************************************************************************************************
 * I/P Arguments:none
 * Return value : none

 * description  : This function configures the rows and columns for keypad scan
        1.ROW lines are configured as Output.
        2.Column Lines are configured as Input.
 ***************************************************************************************************/
void KEYPAD_Init()
{
	M_RowColDirection= C_RowOutputColInput_U8; // Configure Row lines as O/P and Column lines as I/P
}




/***************************************************************************************************
                   void KEYPAD_WaitForKeyRelease()
 ***************************************************************************************************
 * I/P Arguments:none

 * Return value	: none

 * description  : This function waits till the previous key is released.
 ***************************************************************************************************/
void KEYPAD_WaitForKeyRelease()
{
	uint8_t key;
	do
	{
		do
		{
			M_ROW=0x0F;           // Pull the ROW lines to low and Column lines high.
			key=M_COL & 0x0F;     // Read the Columns, to check the key press
		}while(key!=0x0F);

		DELAY_ms(1);

		M_ROW=0x0F;           // Pull the ROW lines to low and Column lines high.
		key=M_COL & 0x0F;     // Read the Columns, to check the key press
	}while(key!=0x0F);   // Wait till the Key is released,
	                     // If no Key is pressed, Column lines will be High(0x0F)
}





/***************************************************************************************************
                   void KEYPAD_WaitForKeyPress()
 ***************************************************************************************************
 * I/P Arguments:none

 * Return value	: none

 * description  : This function waits till a new key is pressed.
                  The new Key pressed can be decoded by the function KEYPAD_GetKey.
 ***************************************************************************************************/
void KEYPAD_WaitForKeyPress()
{
	uint8_t var_keyPress_u8;
	do
	{
		do
		{
			M_ROW=0x0F;		  // Pull the ROW lines to low and Column lines high.
			var_keyPress_u8=M_COL & 0x0F;	  // Read the Columns, to check the key press
		}while(var_keyPress_u8==0x0F); // Wait till the Key is pressed,
		// if a Key is pressed the corresponding Column line go low

		DELAY_ms(1);		  // Wait for some time(debounce Time);

		M_ROW=0x0F;		  // After debounce time, perform the above operation
		var_keyPress_u8=M_COL & 0x0F;	  // to ensure the Key press.

	}while(var_keyPress_u8==0x0F);
}









/***************************************************************************************************
                   unsigned char KEYPAD_GetKey()
 ***************************************************************************************************
 * I/P Arguments:none

 * Return value	: uint8_t--> ASCII value of the Key Pressed

 * description: This function waits till a key is pressed and returns its ASCII Value
                It follows the following sequences to decode the key pressed:
				1.Wait till the previous key is released..
				2.Wait for the new key press.
				3.Scan all the rows one at a time for the pressed key.
				4.Decodes the key pressed depending on ROW-COL combination and returns its
				  ASCII value.
 ***************************************************************************************************/
uint8_t KEYPAD_GetKey()
{
	uint8_t var_keyPress_u8;

	KEYPAD_WaitForKeyRelease();    // Wait for the previous key release
	DELAY_ms(1);

	KEYPAD_WaitForKeyPress();      // Wait for the new key press
	var_keyPress_u8 = keypad_ScanKey();        // Scan for the key pressed.

	switch(var_keyPress_u8)                       // Decode the key
	{
	case 0xe7: var_keyPress_u8='0'; break;
	case 0xeb: var_keyPress_u8='1'; break;
	case 0xed: var_keyPress_u8='2'; break;
	case 0xee: var_keyPress_u8='3'; break;
	case 0xd7: var_keyPress_u8='4'; break;
	case 0xdb: var_keyPress_u8='5'; break;
	case 0xdd: var_keyPress_u8='6'; break;
	case 0xde: var_keyPress_u8='7'; break;
	case 0xb7: var_keyPress_u8='8'; break;
	case 0xbb: var_keyPress_u8='9'; break;
	case 0xbd: var_keyPress_u8='A'; break;
	case 0xbe: var_keyPress_u8='B'; break;
	case 0x77: var_keyPress_u8='C'; break;
	case 0x7b: var_keyPress_u8='D'; break;
	case 0x7d: var_keyPress_u8='E'; break;
	case 0x7e: var_keyPress_u8='F'; break;
	default  : var_keyPress_u8='z'; break;
	}
	return(var_keyPress_u8);                      // Return the key
}






/***************************************************************************************************
                     static uint8_t keypad_ScanKey()
 ***************************************************************************************************
 * I/P Arguments:none

 * Return value	: uint8_t--> Scancode of the Key Pressed

 * description  : This function scans all the rows to decode the key pressed.
        1.Each time a ROW line is pulled low to detect the KEY.
        2.Column Lines are read to check the key press.
        3.If any Key is pressed then corresponding Column Line goes low.

        4.Return the ScanCode(Combination of ROW & COL) for decoding the key.
 ***************************************************************************************************/
static uint8_t keypad_ScanKey()
{

	uint8_t var_keyScanCode_u8 = 0xEF,i, var_keyPress_u8;

	for(i=0;i<0x04;i++)                // Scan All the 4-Rows for key press
	{
		M_ROW=var_keyScanCode_u8;        // Select 1-Row at a time for Scanning the Key
		DELAY_ms(1);
		var_keyPress_u8=M_COL & 0x0F;    // Read the Column, for key press

		if(var_keyPress_u8!=0x0F)        // If the KEY press is detected for the selected
			break;                     // ROW then stop Scanning,

		var_keyScanCode_u8=((var_keyScanCode_u8<<1)+0x01); // Rotate the ScanKey to SCAN the remaining Rows
	}
	var_keyPress_u8 = var_keyPress_u8 + (var_keyScanCode_u8 & 0xf0); // Return the row and COL status to decode the key
	return(var_keyPress_u8);
}
