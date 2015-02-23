/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   stdutils.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains function prototypes for I2c routines.

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

#ifndef _I2C_H
#define _I2C_H

#include <pic16f877a.h>
#include "stdutils.h"


/***************************************************************************************************
                               SCL and SDA pin configuration
***************************************************************************************************/							   
#define SCL RC3		//SCL Connected to PORTC.3
#define SDA RC4 	//SDA Connected to PORTC.4

#define SCL_Direction TRISC3
#define SDA_Direction TRISC4
/**************************************************************************************************/






/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/
void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t );
uint8_t I2C_Read(uint8_t);
/**************************************************************************************************/

#endif
