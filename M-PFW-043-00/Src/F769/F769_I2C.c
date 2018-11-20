/*
 * F769_I2C.c
 *
 *  Created on: 30 Mar 2017
 *      Author: JacoOlivier
 */

#include "F769_I2C.h"

void I2C2_Init(void)
{
	MX_I2C2_Init();
}

bool I2C_BufferRead(I2C_HandleTypeDef *hi2c, uint8_t* data, uint8_t DeviceAddr, uint8_t ReadAddr, uint8_t len)
{
	if(HAL_I2C_Mem_Read(hi2c,DeviceAddr,ReadAddr,1,data,len,100) == HAL_OK)
		return true;
	else
		return false;
}

bool I2C_ByteWrite(I2C_HandleTypeDef *hi2c, uint8_t* data, uint8_t DeviceAddr,uint8_t WriteAddr)
{

	if(HAL_I2C_Mem_Write(hi2c,DeviceAddr,WriteAddr,1,data,1,100) == HAL_OK)
		return true;
	else
		return false;
}
