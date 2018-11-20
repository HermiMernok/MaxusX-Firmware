/*
 * F769_SPI.c
 *
 *  Created on: 03 Sep 2018
 *      Author: NeilPretorius
 */

#include "F769_SPI.h"

/*-----------------------------------------
 *Function name and description
 *---------
 * Standard SPI test function
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * SPI_FailTypedef Enum
 *
 *-----------------------------------------*/

SPI_FailTypedef SPI_Test(void)
{
//	uint8_t  tested_result = 0;
//	uint8_t  RTC_Buf;
	//0 = OK
	//1 = RTC
	//2 = NVRAM time_out
	//3 = NVRAM Integrity

//	uint16_t time_out = 0;

	/*****************************************************/
	//check if RTC times out
	/*****************************************************/
	select_RTC();

	for (uint8_t k = 0; k < 5; k++)
	{
		;
	}
//
//	// Loop while DR register in not empty //
//	while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_TX);
//	{
//		// Send byte through SPI Peripheral //
//		RTC_Buf = 123;
//		if(HAL_SPI_Transmit(&hspi2, &RTC_Buf, 1, 5000) != HAL_OK)
//		{
//			return SPI_RTC_Failure;
//		}
//
//	}
//
//	// Wait to receive a byte //
//	while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_BUSY_RX);
//	{
//		// Return the result //
//		if(HAL_SPI_Receive(&hspi2,&RTC_Buf,1,5000) != HAL_OK)
//		{
//			//error with RTC
//			return SPI_RTC_Failure;
//		}
//
//	}
//
//	for (k = 0; k < 5; k++)
//	{
//		;
//	}
	release_RTC();

	return NV_RAM_SPI_Test();


}

