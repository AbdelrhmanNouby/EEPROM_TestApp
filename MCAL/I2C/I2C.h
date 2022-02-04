/*
 * I2C.h
 *
 * Created: 1/25/2022
 * Author : Abdelrhman Elsawy
 */



#ifndef I2C_H_
#define I2C_H_

#include "I2C_config.h"
#include "I2C_prv.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"

// output check status function 
#define STATUS_AS_EXPECTED				1
#define STATUS_NOT_AS_EXPECTED			0

// select mode of operation
#define WRITE_OP    0
#define READ_OP     1

void I2C_Init(void);
void I2C_SendStartCondition(void);
void I2C_SendStopCondition(void);
uint8_t I2C_u8CheckStatus(uint8_t u8ExpectedStatus);
void I2C_SendSlaveAddress(uint8_t u8SlaveAdd,uint8_t u8Operation);
void I2C_SendByte(uint8_t u8Data);
void I2C_ReceiveDataWithNoAck(uint8_t * u8Data);
void I2C_ReceiveDataWithAck(uint8_t * u8Data);
void I2C_SendString(uint8_t * str );


#endif /* I2C_H_ */