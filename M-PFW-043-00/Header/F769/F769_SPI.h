/*
 * F769_SPI.h
 *
 *  Created on: 03 Sep 2018
 *      Author: NeilPretorius
 */

#ifndef F769_SPI_H_
#define F769_SPI_H_

#include "Global_Variables.h"

typedef enum
{
	SPI_OK 				= 0,
	SPI_RTC_Failure 	= 1,
	SPI_NVRAM_Failure 	= 2,
	SPI_NVRAM_Integrity = 3
}SPI_FailTypedef;

SPI_FailTypedef SPI_Test(void);

struct _SPI_Status
{
	bool			SPI_OK;
}SPI_Status;

#endif /* F769_SPI_H_ */
