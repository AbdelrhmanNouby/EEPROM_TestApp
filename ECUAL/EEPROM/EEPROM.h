/*
 * EEPROM.h
 *
 * Created: 1/26/2022
 * Author : Abdelrhman Elsawy
 */


#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../MCAL/I2C/I2C.h"
#include "EEPROM_ERR_HANDLE.h"

#define EEPROM_ADDRESS		0x00

void EEPROM_Init();
uint8_t EEPROM_u8WriteByte ( uint8_t Addr , uint16_t location , uint8_t data );
uint8_t EEPROM_u8ReadByte( uint8_t Addr , uint16_t location , uint8_t *data );

#endif /* EEPROM_H_ */