/***************************************************************************************************
                                   ExploreEmbedded	
 ****************************************************************************************************
 * File:   keypad.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains hex-keypad port configurations

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
#ifndef _KEYPAD_H
#define _KEYPAD_H

#include <reg51.h>
#include "stdutils.h"


/***************************************************************************************************
                                 Hex-Keypad PORT Configuration
 ***************************************************************************************************/
#define M_RowColDirection P1       //PORT Direction Configuration for keypad
#define M_ROW P1                 //Higher four bits of PORT are used as ROWs
#define M_COL P1                   //Lower four bits of PORT are used as COLs
#define C_RowOutputColInput_U8 0x0F	 //value to configure Rows as Output and Colums as Input
/**************************************************************************************************/




/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void KEYPAD_Init();
void KEYPAD_WaitForKeyRelease();
void KEYPAD_WaitForKeyPress();
uint8_t KEYPAD_GetKey();
/**************************************************************************************************/

#endif
