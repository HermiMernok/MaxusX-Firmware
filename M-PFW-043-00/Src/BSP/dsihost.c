/**
 ******************************************************************************
 * File Name          : DSIHOST.c
 * Description        : This file provides code for the configuration
 *                      of the DSIHOST instances.
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "dsihost.h"

/* USER CODE BEGIN 0 */
  DSI_PHY_TimerTypeDef dsiPhyInit;
/* USER CODE END 0 */

DSI_HandleTypeDef hdsi;

/* DSIHOST init function */

void MX_DSIHOST_DSI_Init(void)
{
	/* USER CODE BEGIN 0 */

	/* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
	DSI_PLLInitTypeDef dsiPllInit;

	uint32_t laneByteClk_kHz = 0;

	hdsi.Instance = DSI;

	//HAL_DSI_DeInit(&(hdsi));

	dsiPllInit.PLLNDIV  = 100;
	dsiPllInit.PLLIDF   = 5;
	dsiPllInit.PLLODF  = 1;
	laneByteClk_kHz = 62500; /* 500 MHz / 8 = 62.5 MHz = 62500 kHz */

	/* Set number of Lanes */
	hdsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;

	/* TXEscapeCkdiv = f(LaneByteClk)/15.62 = 4 */
	hdsi.Init.TXEscapeCkdiv = laneByteClk_kHz/15625;

	if (HAL_DSI_Init(&(hdsi), &(dsiPllInit)))
	{
		_Error_Handler(__FILE__, __LINE__);
	}
	  /* Configure the D-PHY Timings */
	  dsiPhyInit.ClockLaneHS2LPTime = 0x14;
	  dsiPhyInit.ClockLaneLP2HSTime = 0x14;
	  dsiPhyInit.DataLaneHS2LPTime = 0x0A;
	  dsiPhyInit.DataLaneLP2HSTime = 0x0A;
	  dsiPhyInit.DataLaneMaxReadTime = 0x00;
	  dsiPhyInit.StopWaitTime = 0x0;
	  HAL_DSI_ConfigPhyTimer(&hdsi, &dsiPhyInit);
	/* USER CODE END 0 */
}

void HAL_DSI_MspInit(DSI_HandleTypeDef* dsiHandle)
{

	if(dsiHandle->Instance==DSI)
	{
		/* USER CODE BEGIN DSI_MspInit 0 */

		/* USER CODE END DSI_MspInit 0 */
		/* DSI clock enable */
		__HAL_RCC_DSI_CLK_ENABLE();
		/* USER CODE BEGIN DSI_MspInit 1 */

		/* USER CODE END DSI_MspInit 1 */
	}
}

void HAL_DSI_MspDeInit(DSI_HandleTypeDef* dsiHandle)
{

	if(dsiHandle->Instance==DSI)
	{
		/* USER CODE BEGIN DSI_MspDeInit 0 */

		/* USER CODE END DSI_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_DSI_CLK_DISABLE();
		/* USER CODE BEGIN DSI_MspDeInit 1 */

		/* USER CODE END DSI_MspDeInit 1 */
	}
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
