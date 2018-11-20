/*--------------------------------
Dev_ADPS9301.h
Created on: 	13 Oct, 2016
Company: 		Mernok Elektronik
Author: 		J. Fourie
Last Edit:		14 Oct, 2016
Last Edited by: J. Fourie
Revision:		01
----------------------------------*/
#ifndef APDS9309_H_
#define APDS9309_H_

/*--------------------------------
Includes
----------------------------------*/
#include <math.h>

#include "Global_Variables.h"
/*--------------------------------
Defines
----------------------------------*/
typedef unsigned char u8_t;
typedef unsigned short int u16_t;
typedef short int i16_t;


/**************************************************************************************************************
 *********************************************WHAT YOU NEED TO DO**********************************************
 **************************************************************************************************************
 1.  ************************Chose how the address is defined on the ADPS9301 chip***********************
	 * ADPS_ADDR_GND means the address pin is grounded resulting in an address of 0b01010010
	 * ADPS_ADDR_VCC means the address pin is grounded resulting in an address of 0b10010010
	 * Not defining either of the above means the pin is floating resulting in an address of 0b01110010
	 ************************Chose how the address is defined on the ADPS9301 chip************************
 2.  *************************Chose to which I2C channel the ADPS9301 chip connected**********************
	 * #define ADPS_I2C I2C1 -- Define that ADPS9301 is routed to first I2C
	 * #define ADPS_I2C I2C2 -- Define that ADPS9301 is routed to second I2C
	 * #define ADPS_I2C I2C3 -- Define that ADPS9301 is routed to third I2C
	 ************************Chose to which I2C channel the ADPS9301 chip connected***********************
 3.  **********************************************Initialise IC******************************************
	 * Include the "ADPS9301_Init();" function in your application initialisation
	 **********************************************Initialise IC******************************************
 4.  **********************************************Read Values********************************************
	 * Use the function ADPS9301_GetValues(Uint16_Array_of_Size_2); to get raw sensor data
	 * Use the function ADPS9301_GetLux(); to get a lux value (returns float)
	 **********************************************Read Values********************************************
 **************************************************************************************************************
 **************************************************************************************************************
 **************************************************************************************************************
 **************************************************************************************************************
 **************************************************************************************************************/

#define ADPS_ADDR_GND
#define ADPS_I2C				I2C2

typedef enum
{
	APDS9309_OK 		= 0x00,
	APDS9309_ERROR 		= 0x01,
	APDS9309_TIMEOUT	= 0x02

} APDS9301_Status_Typedef;

//Address definition
#ifdef ADPS_ADDR_GND
	#define	ADPS_I2C_ADDRESS	0b01010010				// ADDR pin grounded
#else
	#ifdef ADPS_ADDR_VCC
	#define ADPS_I2C_ADDRESS	0b10010010				// ADDR pin to VCC
#else
	#define ADPS_I2C_ADDRESS	0b01110010				// ADDR pin floating
#endif
#endif


//Read/Write Commands
#define ADPS_command_byte		0b11000000				// specifies byte read/write
#define ADPS_command_word		0b11100000				// specifies word read/write

//#define Lux_Scale				29.2727					// scale constant for 13.7ms integration
//#define Lux_Scale				3.9753					// scale constant for 101 ms integration
//#define Lux_Scale				1.0						// scale constant for 402 ms integration
//#define Lux_Scale				468.36					// scale constant for 13.7ms integration, low gain mode
#define Lux_Scale				63.605					// scale constant for 101 ms integration, low gain mode
//#define Lux_Scale				16.0					// scale constant for 402 ms integration, low gain mode

//#define timing_value			0b00000000				// timing register value. set for 13.7ms samples, continuous
#define timing_value			0b00000001				// timing register value. set for 100 ms samples, continuous
//#define timing_value			0b00000010				// timing register value. set for 400 ms samples, continuous

//Register Definition
/************** AMBIENT SENSOR REGISTERS *****************/
												// COMMAND REGISTER : | 1  |CLR |WORD|RESV|-- -- ADDRESS -- --|
#define CONTROL					0x00			// CONTROL REGISTER : | -- | -- | -- | -- | -- | -- |--POWER--|
#define TIMING					0x01			// TIMING  REGISTER : |
#define THRESHOLDLOW_L			0x02			//
#define THRESHOLDLOW_H			0x03			//
#define THRESHOLDHIGH_L			0x04			//
#define THRESHOLDHIGH_H			0x05			//
#define INTERRUPT				0x06			//
#define CHIP_ID					0x0A			// ID      REGISTER : | 0  | 1  | 0  | 1  |-- --  REVNO  -- --|
#define DATA0_L					0x0C			//
#define DATA0_H					0x0D			//
#define DATA1_L					0x0E			//
#define DATA1_H					0x0F			//
/*--------------------------------
Variables made public
----------------------------------*/

/*--------------------------------
Functions made public
----------------------------------*/
uint8_t ADPS9309_Init(void);
bool ADPS9309_GetValues(uint16_t *ADPS9301_Values);
float ADPS9309_GetLux(void);
void AmbientSens_set_tune(float f);
#endif /* APDS9309_H_ */
