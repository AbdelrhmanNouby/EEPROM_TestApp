/*
 * I2C_prv.h
 *
 * Created: 1/25/2022
 * Author : Abdelrhman Elsawy
 */



#ifndef I2C_PRV_H_
#define I2C_PRV_H_

//TWCR REG
#define TWIE_BIT     0
#define TWEN_BIT     2
#define TWWC_BIT     3
#define TWSTO_BIT    4
#define TWSTA_BIT    5
#define TWEA_BIT     6
#define TWINT_BIT    7

// Prescaler BITs
#define TWPS0_BIT    0
#define TWPS1_BIT    1

// General Call BIT
#define TWGCE_BIT    0

// Genera call cases 
#define DISABLE_GENERAL_CALL	0
#define ENABLE_GENERAL_CALL		1

// mask to can write on TWSR_REG without editing on PRESCALER BITS
#define TWSR_REG_MASK		 0xF8

//I2C Expected status
#define START_SENT                    0x08
#define REPEATED_START_SENT           0x10
#define SLA_W_SENT_WITH_ACK           0x18
#define SLA_W_SENT_WITHOUT_ACK        0x20
#define DATA_SENT_WITH_ACK            0x28
#define DATA_SENT_WITHOUT_ACK         0x30
#define ARBITRATION_LOST              0x38
#define SLA_R_RECEIVED_WITH_ACK       0x40
#define SLA_R_RECEIVED_WITHOUT_ACK    0x48
#define DATA_RECEIVED_WITH_ACK        0x50
#define DATA_RECEIVED_WITHOUT_ACK     0x58

#define MASTER			0
#define SLAVE			1

#endif /* I2C_PRV_H_ */