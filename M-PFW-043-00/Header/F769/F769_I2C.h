/*
 * F769_I2C.h
 *
 *  Created on: 30 Mar 2017
 *      Author: JacoOlivier
 */

#ifndef F769_I2C_H_
#define F769_I2C_H_

/*--------------------------------
Includes
----------------------------------*/
#include "Global_Variables.h"

/*--------------------------------
Functions made public
----------------------------------*/
void I2C2_Init(void);
bool I2C_BufferRead(I2C_HandleTypeDef *hi2c, uint8_t* data, uint8_t DeviceAddr, uint8_t ReadAddr, uint8_t len);
bool I2C_ByteWrite(I2C_HandleTypeDef *hi2c, uint8_t* data, uint8_t DeviceAddr,uint8_t WriteAddr);

#endif /* F769_I2C_H_ */
