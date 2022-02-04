/*
 * EEPROM.c
 *
 * Created: 1/26/2022
 * Author : Abdelrhman Elsawy
 */

#include "EEPROM.h"

void EEPROM_Init()
{
	I2C_Init();
}

uint8_t EEPROM_u8WriteByte ( uint8_t Addr , uint16_t location , uint8_t data )
{
	Addr = ( 0b01010000 | ( Addr << 1 )) ;
	uint8_t locationHighByte = ( location >> 8 ) ;
	uint8_t locationLowByte = (uint8_t)location ;
	uint8_t u8ErrorState = STD_TYPES_OK ;
	I2C_SendStartCondition();
	if (!I2C_u8CheckStatus(START_SENT))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendSlaveAddress(Addr,WRITE_OP);
	if (!I2C_u8CheckStatus(SLA_W_SENT_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendByte(locationHighByte);
	if (!I2C_u8CheckStatus(DATA_SENT_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendByte(locationLowByte);
	if (!I2C_u8CheckStatus(DATA_SENT_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;			
	I2C_SendByte(data);
	if (!I2C_u8CheckStatus(DATA_SENT_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendStopCondition();

	return u8ErrorState ;
}

uint8_t EEPROM_u8ReadByte( uint8_t Addr , uint16_t location , uint8_t *data )
{
	Addr = (( Addr << 1 ) | 0b01010000 ) ;
	uint8_t locationHighByte = ( location >> 8 ) ;
	uint8_t locationLowByte = (uint8_t)location ;
	uint8_t u8ErrorState = STD_TYPES_OK ;
	I2C_SendStartCondition();
	if (!I2C_u8CheckStatus(START_SENT))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendSlaveAddress(Addr,WRITE_OP);
	if (!I2C_u8CheckStatus(SLA_W_SENT_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendByte(locationHighByte);
	if (!I2C_u8CheckStatus(DATA_SENT_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendByte(locationLowByte);
	if (!I2C_u8CheckStatus(DATA_SENT_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;			
	I2C_SendStartCondition();
	if (!I2C_u8CheckStatus(REPEATED_START_SENT))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendSlaveAddress(Addr,READ_OP);
	if (!I2C_u8CheckStatus(SLA_R_RECEIVED_WITH_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_ReceiveDataWithNoAck(data);
	if (!I2C_u8CheckStatus(DATA_RECEIVED_WITHOUT_ACK))
			u8ErrorState = EEPROM_WriteByte_Error ;
	I2C_SendStopCondition();
	
	return u8ErrorState ;
}

