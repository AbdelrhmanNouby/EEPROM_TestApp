/*
 * I2C_config.h
 *
 * Created: 1/25/2022
 * Author : Abdelrhman Elsawy
 */



#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

/*
                       CPU Clock frequency
SCL frequency =   ???????????????????????????
				    16 + ( 2(TWBR) * ( 4^TWPS )
 
 to set SCL = 100 KHz -> TWBR = 32 , TWPS =  0 
 or TWBR = 8, TWPS =  1 				
*/

#define TWPS_BITS_VALUE            0
#define TWBR_REG_VALUE            32

// set I2C mode
#define MODE	MASTER
#define I2C_ADDRESS			100

// Set general call mode 
#define I2C_GENERAL_CALL_MODE     DISABLE_GENERAL_CALL

//Put Micro controller slave addresses
#define I2C_SLAVE1_ADDRESS         1

#endif /* I2C_CONFIG_H_ */