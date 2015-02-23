/*-----------------------------------------------------------------------------
         Program to demonstrate displaying of RTC on LCD
  -----------------------------------------------------------------------------
  note:
  Refer lcd.h file for Pin connections
  Refer Atmega32 DataSheet for register descriptions.
  ------------------------------------------------------------------------------*/



#include "lcd.h"	//User defined LCD library which contains the lcd routines
#include "rtc.h" //User defined library which contains the RTC(ds1307) routines


/* start the main program */
void main() 
{
   unsigned char sec,min,hour,day,month,year;

  /* Initialize the lcd before displaying any thing on the lcd */
    LCD_Init(8,2,16);

  /* Initialize the RTC(ds1307) before reading or writing time/date */
    RTC_Init();


  /*$$$$ Set the time and Date only once. Once the Time and Date is comment these lines
         and reflash the code. Else the time will be reset every time the controller is reset*/
    RTC_SetTime(0x10,0x40,0x20);  //  10:40:20 am
    RTC_SetDate(0x01,0x01,0x15);  //  1st Jan 2015



   /* Display the Time and Date continuously */ 
   while(1)
    {
        LCD_GoToLine(1);

        /* Read the Time from RTC(ds1307) */
        RTC_GetTime(&hour,&min,&sec);        		 
        LCD_Printf("time:%2x:%2x:%2x",hour,min,sec);

	
	/* Read the Date from RTC(ds1307) */ 
        RTC_GetDate(&day,&month,&year);        

	LCD_Printf("\nDate:%2x/%2x/%2x",day,month,year);
    }
}