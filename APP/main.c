/*
 * EEPROM_I2C.c
 *
 * Created: 1/26/2022
 * Author : Abdelrhman Elsawy
 */ 

#include "../ECUAL/EEPROM/EEPROM.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/TIMER0/TIMER0.h"
#include "../LIB/STRING.h"

int main(void)
{
	UART_u8Init();
	EEPROM_Init();
	TIMER0_u8Init();
	uint8_t WRITE_str[] = {"WRITE"};
	uint8_t READ_str[] = {"READ"};
	uint8_t OK_str[] = {"OK"};
	uint8_t NOTOK_str[] = {"NOTOK"};
	uint8_t R_str[] = {"WRITE"};
	uint8_t add_str[10] ;
	//uint8_t data_str[9] ;
	uint8_t stored_str[] = {"the data stored is : "};	
	uint8_t data = 99 ;
	uint16_t Recieved_add = 0x08 ;
		
    while (1) 
    {
		//UART_u8SendByte((uint8_t)data);	
		UART_u8ReceiveString(R_str);
		if (Compare_Str(R_str,WRITE_str))
		{
			UART_u8ReceiveString(add_str);
			Recieved_add = StringToInt(add_str);
			UART_u8SendString(OK_str);			
			UART_u8SendByte(NEWLINE);
			
			UART_u8ReceiveByte(&data);
			UART_u8SendByte(NEWLINE);
			if ( EEPROM_u8WriteByte(EEPROM_ADDRESS,Recieved_add,data) != STD_TYPES_OK )
					 UART_u8SendString(NOTOK_str);
			TIMER0_u8PollingDelay_ms(1000);			
			UART_u8SendString(OK_str);				
			UART_u8SendByte(NEWLINE);
		}
		else if (Compare_Str(R_str,READ_str))
		{
			UART_u8ReceiveString(add_str);
			Recieved_add = StringToInt(add_str);
			UART_u8SendString(OK_str);
			UART_u8SendByte(NEWLINE);

			UART_u8SendString(stored_str);
			if ( EEPROM_u8ReadByte(EEPROM_ADDRESS,Recieved_add,(uint8_t*)&data) != STD_TYPES_OK )
					UART_u8SendString(NOTOK_str);
			TIMER0_u8PollingDelay_ms(1000);
			UART_u8SendByte(data);
			UART_u8SendByte(NEWLINE);
		}
		else
		{
			UART_u8SendString(NOTOK_str);
			UART_u8SendByte(NEWLINE);			
		}
	}
}




