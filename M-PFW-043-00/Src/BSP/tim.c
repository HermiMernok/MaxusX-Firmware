/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim2);

}

void MX_TIM3_Init(void)
{

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	//TIM3 runs on APB1 source which clocks at 42 MHz: 42000000/42000 --> 1000 Hz ticking clock

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 42000;					//Divide clock to 1 kHz, 1ms running timer
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 500 - 1;					//Interrupt every 2ms *(Period - 1) --> 1000 ms
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.RepetitionCounter = 0x0;

	if (HAL_TIM_Base_Init(&htim3)!= HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	 if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)!= HAL_OK)
	 {
		 _Error_Handler(__FILE__, __LINE__);
	 }
}


/*-----------------------------------------
 *Function name and description
 *---------
 * Configure Timer 4
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void MX_TIM4_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	//TIM4 runs on APB1 source which clocks at 42 MHz: 42000000/42000 --> 1000 Hz ticking clock

	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 42000;						//Divide clock to 1 kHz, 1ms running timer
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 2000 - 1;					    //Interrupt every 1s *(Period + 1) --> 2000 ms
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.RepetitionCounter = 0x0;
	HAL_TIM_Base_Init(&htim4);


	//Configure the clock source
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig);

	//Output trigger initialsation
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);

}

TIM_HandleTypeDef htim5;

/* TIM5 init function */
void MX_TIM5_Init(uint32_t duty_cycle)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  uint32_t pulse = 1390*duty_cycle/100;

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 1390;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = pulse;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;


  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim5);

 	 HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  if(tim_pwmHandle->Instance==TIM5)
   {
   /* USER CODE BEGIN tim5_MspInit 0 */

   /* USER CODE END tim5_MspInit 0 */
     /* tim5 clock enable */
     __HAL_RCC_TIM5_CLK_ENABLE();
    // HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
     //			HAL_NVIC_EnableIRQ(TIM5_IRQn);
   /* USER CODE BEGIN tim5_MspInit 1 */

   /* USER CODE END tim5_MspInit 1 */
   }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(timHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspPostInit 0 */

  /* USER CODE END TIM2_MspPostInit 0 */
  
    /**TIM2 GPIO Configuration    
    PA0/WKUP     ------> TIM2_CH1
    PB11     ------> TIM2_CH4
    PB3     ------> TIM2_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM2_MspPostInit 1 */

  /* USER CODE END TIM2_MspPostInit 1 */
  }
  if(timHandle->Instance==TIM5)
    {
    /* USER CODE BEGIN TIM5_MspPostInit 0 */

    /* USER CODE END TIM5_MspPostInit 0 */

      /**TIM5 GPIO Configuration
      PA0/WKUP     ------> TIM5_CH4
      __TIM3_CLK_ENABLE();
      */

      GPIO_InitStruct.Pin = GPIO_PIN_0;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
      HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* USER CODE BEGIN TIM5_MspPostInit 1 */

    /* USER CODE END TIM5_MspPostInit 1 */
    }

}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  if(tim_pwmHandle->Instance==TIM5)
    {
    /* USER CODE BEGIN TIM5_MspDeInit 0 */

    /* USER CODE END TIM5_MspDeInit 0 */
      /* Peripheral clock disable */
      __HAL_RCC_TIM5_CLK_DISABLE();
  //   	HAL_NVIC_DisableIRQIRQ(TIM5_IRQn);
    /* USER CODE BEGIN TIM5_MspDeInit 1 */

    /* USER CODE END TIM5_MspDeInit 1 */
    }
} 



/*-----------------------------------------
 *Function name and description
 *---------
 * HAL pin init for base timer setup
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

	if(htim_base->Instance == TIM3)
	{
		/* Peripheral clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();
		/* Peripheral interrupt init */
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}

	if(htim_base->Instance == TIM4)
	{
		/* Peripheral clock enable */
		__HAL_RCC_TIM4_CLK_ENABLE();
		/* Peripheral interrupt init */
		HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
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
