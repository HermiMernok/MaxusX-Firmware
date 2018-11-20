/*--------------------------------
Dev_ADPS9301.c
Created on: 	13 Oct, 2016
Company: 		Mernok Elektronik
Author: 		J. Fourie
Last Edit:		14 Oct, 2016
Last Edited by: J. Fourie
Revision:		01
----------------------------------*/
#include "APDS9309.h"


/*--------------------------------
 *Local Variables
 *------------------------------*/


/*--------------------------------
 *Global Variables
 *------------------------------*/
float Ambient_tune = 1.0;
/*******************************************************************************
* Function Name		: ReadReg
* Description		: Generic Reading function. It must be fullfilled with
* 					: I2C reading functions
* Input				: Register Address
* Output			: Data Read
* Return			: None
*******************************************************************************/
u8_t ADPS9309_ReadRegs(I2C_HandleTypeDef *hi2c, u8_t deviceAddr, u8_t Reg, u8_t* Data, u8_t len)
{

  // Read using I2C bus. This is implemented in external source.
  if(!I2C_BufferRead(hi2c, Data, deviceAddr, Reg|ADPS_command_byte, len))
  return false;
  else
  return true;
}
/*******************************************************************************
* Function Name		: WriteReg
* Description		: Generic Writing function. It must be fulfilled with
*					: I2C writing function
* Input				: Register Address, Data to be written
* Output			: None
* Return			: None
*******************************************************************************/
u8_t ADPS9309_WriteReg(I2C_HandleTypeDef *hi2c, u8_t deviceAddress, u8_t WriteAddr, u8_t Data) {

	// Write using I2C bus. This is implemented in external source.
  I2C_ByteWrite(hi2c, &Data,  deviceAddress,  WriteAddr|ADPS_command_byte);
  return true;
}

/*******************************************************************************
* Function Name  : Initialises device
* Description    : Sets control registers for ADPS-9301 to run
* Input          : None
* Return         : None
*******************************************************************************/
uint8_t ADPS9309_Init(void)
{
	uint16_t s;
	HAL_StatusTypeDef RES;
	u8_t Device_ID = 0;
	float Test;

	RES = HAL_I2C_IsDeviceReady(&hi2c2,ADPS_I2C_ADDRESS,20,200);	//Check if device is ready for communication, 20 attempts, 200 ms timeout

	ADPS9309_WriteReg(&hi2c2, ADPS_I2C_ADDRESS, CONTROL, 3);						// power device on
	ADPS9309_WriteReg(&hi2c2, ADPS_I2C_ADDRESS, TIMING, timing_value);			// set auto-sample interval

	ADPS9309_ReadRegs(&hi2c2, ADPS_I2C_ADDRESS, CHIP_ID, &Device_ID, 1);

	if ((Device_ID & 0xF0) != 0b01110000)		//expect a device ID of 80 (decimal)
	{
		Delay(50);
		return (uint8_t) APDS9309_ERROR;
	}
	else
	{
		return (uint8_t) APDS9309_OK;
	}
}
/*-----------------------------------------
 *Function name and description
 *---------
 * ADPS9301_GetValues
 * Reads the values from the sensor
 *Inputs:
 *---------
 * User should supply uint16_t[2] array in arguments
 *Outputs:
 *---------
 * Populates argument array as follow:
 * ADPS9301_Values[0] = Light + IR Reading
 * ADPS9301_Values[1] = IR Reading
 *-----------------------------------------*/
bool ADPS9309_GetValues(uint16_t *ADPS9301_Values)
{
	u8_t raw_values[4];

	if (!ADPS9309_ReadRegs(&hi2c2, ADPS_I2C_ADDRESS, DATA0_L, raw_values, 4) )
	{
		return false;
	}
	else
	{
		ADPS9301_Values[0] = (((u16_t)raw_values[0]) | ((u16_t)raw_values[1]<<8));
		ADPS9301_Values[1] = (((u16_t)raw_values[2]) | ((u16_t)raw_values[3]<<8));
		return true;
	}
}
/*-----------------------------------------
 *Function name and description
 *---------
 * ADPS9301_GetLux
 * Converts Sensor values to Lux value
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 * Return lux value in type float
 *-----------------------------------------*/
float ADPS9309_GetLux(void)
{
	uint16_t ADPS9301_Values[2];
	float lux;

	//Get raw sensor value
	ADPS9301_GetValues(ADPS9301_Values);

	// Math starts here. see ADPS-9301 datasheet for empirical formula.
	// get ratio IR/(light+IR)
	// ADPS9301_Values[1] -> IR value
	// ADPS9301_Values[1] -> IR + Light value
	lux = ((float)ADPS9301_Values[1])/((float)ADPS9301_Values[0]);
	if 		(lux < 0.5 )
	{
		lux = (0.0304 * ADPS9301_Values[0]) - (0.062 * ADPS9301_Values[0] * pow((ADPS9301_Values[1]/ADPS9301_Values[0]),1.4));
	}
	else if (lux < 0.61)
	{
		lux = (0.0224 * ADPS9301_Values[0]) - (0.031 * ADPS9301_Values[1]);
	}
	else if (lux < 0.8)
	{
		lux = (0.0128 * ADPS9301_Values[0]) - (0.0153 * ADPS9301_Values[1]);
	}
	else if (lux < 1.3)
	{
		lux = (0.00146 * ADPS9301_Values[0]) - (0.00112 * ADPS9301_Values[1]);
	}
	else
	{
		lux = 0;
	}

	return lux * Lux_Scale * Ambient_tune *2.8;				// 2.8 was found to be the ideal calibration value by Max (MAE Manufacturing). 17/07/2013 (phone call)
}
/*-----------------------------------------
 *Function name and description
 *---------
 * AmbientSens_set_tune
 * Used to set the tuning factor of the lux value
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void AmbientSens_set_tune(float f)
{
	Ambient_tune = f;
}





