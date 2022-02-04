/*
 * I2C.c
 *
 * Created: 1/25/2022
 * Author : Abdelrhman Elsawy
 */

#include "I2C.h"

void I2C_Init(void)
{
	SET_BIT(TWCR_REG,TWEN_BIT);				  //Enable I2C
	TWBR_REG = TWBR_REG_VALUE;				  //Set TWBR = value selected in config file 
	
	//Prepare TWSR for masking TWPS0,TWPS1
	SET_BIT(TWSR_REG,TWPS0_BIT);
	SET_BIT(TWSR_REG,TWPS1_BIT);
	
	//Put I2C TWPS Value in TWSR_REG
	TWSR_REG &= ((TWPS_BITS_VALUE)|(TWSR_REG_MASK)) ;
	
	//general call
	if (I2C_GENERAL_CALL_MODE == ENABLE_GENERAL_CALL)
	{
		SET_BIT(TWAR_REG,TWGCE_BIT);
	}
	
	if ( MODE == SLAVE )	
	{
		TWAR_REG = ( I2C_ADDRESS << 1);
	}
	SET_BIT(TWCR_REG,TWINT_BIT);
	SET_BIT(TWCR_REG,TWEN_BIT);
}

void I2C_SendStartCondition(void)
{
    //Send Start condition + clear TWINT flag to start TWI operation
	SET_BIT(TWCR_REG,TWSTA_BIT);
	
	while(GET_BIT(TWCR_REG,TWINT_BIT)==0);           //wait until start is transmitted
	TWCR_REG = ( 1 << TWEN_BIT ) ;                   //clear start bit and all bits except enable	
}

void I2C_SendStopCondition(void)
{
	//Send Stop condition + clear TWINT flag to start TWI operation
	SET_BIT(TWCR_REG,TWINT_BIT);
	SET_BIT(TWCR_REG,TWSTO_BIT);
	SET_BIT(TWCR_REG,TWEN_BIT);
}

uint8_t I2C_u8CheckStatus(uint8_t u8ExpectedStatus)
{
	uint8_t u8State = STATUS_AS_EXPECTED ;
	if ((TWSR_REG & TWSR_REG_MASK) == u8ExpectedStatus)
		u8State = STATUS_AS_EXPECTED ;
	else
		u8State = STATUS_NOT_AS_EXPECTED ;	
	
	return u8State ;
}

void I2C_SendSlaveAddress(uint8_t u8SlaveAdd,uint8_t u8Operation)
{
	TWDR_REG = (u8SlaveAdd<<1)|(u8Operation);				//Put address and operation in TWDR Reg
	// reset flag Start sending address and operation
	SET_BIT(TWCR_REG,TWINT_BIT);
	SET_BIT(TWCR_REG,TWEN_BIT);  
	while((GET_BIT(TWCR_REG,TWINT_BIT))==0);	        //wait until operation complete	
}

void I2C_SendByte(uint8_t u8Data)
{
	TWDR_REG = u8Data;				// assign the character to data REG
	// reset flag Start sending address and operation
	SET_BIT(TWCR_REG,TWINT_BIT);
	SET_BIT(TWCR_REG,TWEA_BIT);
	SET_BIT(TWCR_REG,TWEN_BIT);
	while((GET_BIT(TWCR_REG,TWINT_BIT))==0);        //wait until operation complete	
}

void I2C_ReceiveDataWithNoAck(uint8_t * u8Data)
{
	// reset flag Start sending address and operation
/*
	SET_BIT(TWCR_REG,TWINT_BIT);
	CLR_BIT(TWCR_REG,TWSTO_BIT);*/
	SET_BIT(TWCR_REG,TWEN_BIT);
	while((GET_BIT(TWCR_REG,TWINT_BIT))==0);        //wait until operation complete
	*u8Data	= TWDR_REG ;
}

void I2C_ReceiveDataWithAck(uint8_t * u8Data)
{	
	// reset flag Start sending address and operation and enable ACK BIT
	SET_BIT(TWCR_REG,TWINT_BIT);
	SET_BIT(TWCR_REG,TWEA_BIT);
	CLR_BIT(TWCR_REG,TWSTO_BIT);
	SET_BIT(TWCR_REG,TWEN_BIT);
	
	while((GET_BIT(TWCR_REG,TWINT_BIT))==0);        //wait until operation complete
	*u8Data	= TWDR_REG ;
}

void I2C_SendString(uint8_t * str )
{
	while(*str != '\0')
	{
		// send character by character
		I2C_SendByte(*str);
		str++;
	}
}