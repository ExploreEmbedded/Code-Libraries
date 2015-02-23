/*-----------------------------------------------------------------------------
  Program to demonstrate uart library usage at 9600 baudrate
  -----------------------------------------------------------------------------
  note:
  Refer uart.h for baud rate configuraton.
------------------------------------------------------------------------------*/

#include"uart.h"
int main()
{
  code char str_TxMsg_u8[]={"Good Morning"};
  char var_uartData_u8='A';
  uint16_t var_num_u16= 1234u;
  char str_readString_u8[10];
  char ch;
 
 
  UART_Init(9600);
  UART_TxString("\n\rProgram to illustrate the UART library usage ");
 
  UART_TxString(str_TxMsg_u8);    /* Transmit the message stored in a string */
  UART_TxString("\n\rChar:");
  UART_TxChar('X');             /* Transmit the specified Ascii character */
  UART_TxChar(var_uartData_u8);    /* Transmit the char stored in a variable */
 
  UART_TxString("\n\rDec:");
  UART_TxDecimalNumber(1234,5);  /* Transmit the specified digits of a number */
  UART_TxString(" Hex:");
  UART_TxHexNumber(0xABCD,5);    /* Note here the number of digits to transmit=5 */
  UART_TxString(" Bin:");        /* The number Transmitted on UART will be as below*/
  UART_TxBinaryNumber(0xABCD,16);/* dec=01234, hex=0ABCD, bin=1010101111001101*/
 
 
  UART_Printf("\n\rDec=%d Hex=%x Bin:%b str=%s",var_num_u16,var_num_u16,var_num_u16,str_TxMsg_u8);
  UART_Printf("\n\rDec=%d Hex=%x Bin:%b str=%s",123u,0xABCDu,0x55u,"hello,world");
 
  UART_Printf("\n\rEnter a String: ");
  UART_RxString(str_readString_u8);
  UART_Printf("\n\rEntered string is: %s",str_readString_u8);
 
  do
  {
 	UART_Printf("\n\rEnter 'E' to exit: ");
 	ch = UART_RxChar();
 	UART_Printf("\n\rYou entered: %c",ch);
  }while((ch!='E') && (ch!='e'));
 
 
  UART_Printf("\n\rEnjoy Embedded Programming");
  while(1);
 
  return 0;
}