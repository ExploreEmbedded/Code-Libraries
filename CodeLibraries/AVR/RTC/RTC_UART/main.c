/*-----------------------------------------------------------------------------
         Program to demonstrate displaying of RTC on Uart at 9600 Baud Rate
  -----------------------------------------------------------------------------
  note:
  Refer uart.h for baudrate configuration.  
  Refer i2c.h for SDA and SCL connection.
------------------------------------------------------------------------------*/


#include "uart.h"	//User defined UART library which conatins the UART routines
#include "rtc.h" //User defined library which conatins the RTC(ds1307) routines



/* start the main program */
void main() 
{
   unsigned char sec,min,hour,day,month,year;

  /* Initilize the Uart before Transmiting/Reaceiving any data */
    UART_Init(9600);

  /* Initilize the RTC(ds1307) before reading or writing time/date */
    RTC_Init();

	UART_TxString(" Testing RTC ");
 /*##### Set the time and Date only once. Once the Time and Date is set, comment these lines
         and reflash the code. Else the time will be set every time the controller is reset*/
    RTC_SetTime(0x10,0x40,0x00);  //  10:40:20 am
    RTC_SetDate(0x01,0x01,0x15);  //  1st Jan 2015



   /* Display the Time and Date continuously */ 
   while(1)
    {
	   /* Read the Time from RTC(ds1307) */ 
        RTC_GetTime(&hour,&min,&sec);      
		
	    /* Read the Date from RTC(ds1307) */ 
        RTC_GetDate(&day,&month,&year);        
	 
        UART_Printf("\n\rtime:%2x:%2x:%2x  \nDate:%2x/%2x/%2x",(uint16_t)hour,(uint16_t)min,(uint16_t)sec,(uint16_t)day,(uint16_t)month,(uint16_t)year);
	  }		

  }