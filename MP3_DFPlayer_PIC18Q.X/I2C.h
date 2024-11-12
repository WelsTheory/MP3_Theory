
#ifndef I2C_H
#define	I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "main.h"

void I2C_Init(void);

void I2C_SendBytes(uint8_t address, uint8_t* data, uint8_t len);

void I2C_ReadBytes(uint8_t address, uint8_t* data, uint8_t len);

#endif	/* XC_HEADER_TEMPLATE_H */

