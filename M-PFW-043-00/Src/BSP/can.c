/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
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
#include "can.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* CAN1 init function */
void MX_CAN1_Init(void)
{
  HAL_CAN_DeInit(&hcan1);
  //HAL_CAN_MspInit(&hcan1);

  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 14;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  //Deactivate Filter
  CAN1_Filters.FilterIdHigh = 0x0000;
  CAN1_Filters.FilterIdLow = 0x0000;
  CAN1_Filters.FilterMaskIdHigh = 0x0000;
  CAN1_Filters.FilterMaskIdLow = 0x0000;
  CAN1_Filters.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN1_Filters.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN1_Filters.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN1_Filters.FilterBank = 0;
  CAN1_Filters.FilterActivation = ENABLE;

  HAL_CAN_ConfigFilter(&hcan1, &CAN1_Filters);
  //Activate CAN1 RX interrupt
  HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
  //Start CAN1
  HAL_CAN_Start(&hcan1);

}

/* CAN2 init function */
void MX_CAN2_Init(void)
{

  HAL_CAN_DeInit(&hcan2);

  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 14;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  //Set filter
  CAN2_Filters.FilterIdHigh = 0x0000;
  CAN2_Filters.FilterIdLow = 0x0000;
  CAN2_Filters.FilterMaskIdHigh = 0x0000;
  CAN2_Filters.FilterMaskIdLow = 0x0000;
  CAN2_Filters.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN2_Filters.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN2_Filters.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN2_Filters.FilterBank = 7;
  CAN2_Filters.FilterActivation = ENABLE;
  HAL_CAN_ConfigFilter(&hcan2, &CAN2_Filters);
  //Activate CAN2 RX interrupt
  HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
  //Start CAN2
  HAL_CAN_Start(&hcan2);
}

///* CAN2 init function */
//void MX_CAN3_Init(void)
//{
//
//  HAL_CAN_DeInit(&hcan3);
//  HAL_CAN_MspInit(&hcan3);
//
//  hcan2.Instance = CAN3;
//  hcan2.Init.Prescaler = 14;
//  hcan2.Init.Mode = CAN_MODE_NORMAL;
//  hcan2.Init.SyncJumpWidth = CAN_SJW_2TQ;
//  hcan2.Init.TimeSeg1 = CAN_BS1_9TQ;
//  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
//  hcan2.Init.TimeTriggeredMode = DISABLE;
//  hcan2.Init.AutoBusOff = ENABLE;
//  hcan2.Init.AutoWakeUp = DISABLE;
//  hcan2.Init.AutoRetransmission = DISABLE;
//  hcan2.Init.ReceiveFifoLocked = DISABLE;
//  hcan2.Init.TransmitFifoPriority = ENABLE;
//  if (HAL_CAN_Init(&hcan3) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }
//  //Set filter
//  CAN3_Filters.FilterIdHigh = 0x0000;
//  CAN3_Filters.FilterIdLow = 0x0000;
//  CAN3_Filters.FilterMaskIdHigh = 0x0000;
//  CAN3_Filters.FilterMaskIdLow = 0x0000;
//  CAN3_Filters.FilterFIFOAssignment = CAN_FILTER_FIFO0;
//  CAN3_Filters.FilterMode = CAN_FILTERMODE_IDMASK;
//  CAN3_Filters.FilterScale = CAN_FILTERSCALE_32BIT;
//  CAN3_Filters.FilterBank = 7;
//  CAN3_Filters.FilterActivation = ENABLE;
//  HAL_CAN_ConfigFilter(&hcan3, &CAN3_Filters);
//  //Activate CAN2 RX interrupt
//  HAL_NVIC_SetPriority(CAN3_RX0_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(CAN3_RX0_IRQn);
//  HAL_CAN_ActivateNotification(&hcan3, CAN_IT_RX_FIFO1_MSG_PENDING);
//  //Start CAN2
//  HAL_CAN_Start(&hcan3);
//}

void CAN_Send_Message(CAN_HandleTypeDef *Selected_CAN, CAN_TxHeaderTypeDef *TX_HEADER, uint8_t TX_Message[], uint32_t *TXMAILBOX)
{
		//Select relevant CAN BUS
	  if(Selected_CAN->Instance==CAN1)
				HAL_CAN_AddTxMessage(Selected_CAN, TX_HEADER, TX_Message, TXMAILBOX);
	  else if(Selected_CAN->Instance==CAN2)
				HAL_CAN_AddTxMessage(Selected_CAN, TX_HEADER, TX_Message, TXMAILBOX);
	  else if(Selected_CAN->Instance==CAN3)
				HAL_CAN_AddTxMessage(Selected_CAN, TX_HEADER, TX_Message, TXMAILBOX);

}
//static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;
//static uint32_t HAL_RCC_CAN3_CLK_ENABLED=0;
//static uint32_t HAL_RCC_CAN2_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
//    HAL_RCC_CAN1_CLK_ENABLED++;
//    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
//    }
  
    /**CAN1 GPIO Configuration    
    PH14     ------> CAN1_RX
    PB9     ------> CAN1_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
//    HAL_RCC_CAN2_CLK_ENABLED++;
//    if(HAL_RCC_CAN2_CLK_ENABLED==1){
      __HAL_RCC_CAN2_CLK_ENABLE();
//    }

  
    /**CAN2 GPIO Configuration    
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
  else if(canHandle->Instance==CAN3)
  {
  /* USER CODE BEGIN CAN3_MspInit 0 */

  /* USER CODE END CAN3_MspInit 0 */
    /* CAN3 clock enable */
//    HAL_RCC_CAN3_CLK_ENABLED++;
//    if(HAL_RCC_CAN3_CLK_ENABLED==1){
      __HAL_RCC_CAN3_CLK_ENABLE();
//    }
//    HAL_RCC_CAN2_CLK_ENABLED++;
//    if(HAL_RCC_CAN2_CLK_ENABLED==1){
//      __HAL_RCC_CAN2_CLK_ENABLE();
//    }
//    HAL_RCC_CAN1_CLK_ENABLED++;
//    if(HAL_RCC_CAN1_CLK_ENABLED==1){
//      __HAL_RCC_CAN1_CLK_ENABLE();
//    }
  
    /**CAN3 GPIO Configuration    
    PA8     ------> CAN3_RX
    PA15     ------> CAN3_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_CAN3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN3_MspInit 1 */

  /* USER CODE END CAN3_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN1 GPIO Configuration    
    PH14     ------> CAN1_RX
    PB9     ------> CAN1_TX 
    */
    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_14);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
//    HAL_RCC_CAN3_CLK_ENABLED--;
//    if(HAL_RCC_CAN3_CLK_ENABLED==0){
//      __HAL_RCC_CAN3_CLK_DISABLE();
//    }
//    HAL_RCC_CAN2_CLK_ENABLED--;
//    if(HAL_RCC_CAN2_CLK_ENABLED==0){
      __HAL_RCC_CAN2_CLK_DISABLE();
//    }
//    HAL_RCC_CAN1_CLK_ENABLED--;
//    if(HAL_RCC_CAN1_CLK_ENABLED==0){
//      __HAL_RCC_CAN1_CLK_DISABLE();
//    }
  
    /**CAN2 GPIO Configuration    
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_6);

  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN3)
  {
  /* USER CODE BEGIN CAN3_MspDeInit 0 */

  /* USER CODE END CAN3_MspDeInit 0 */
    /* Peripheral clock disable */
//    HAL_RCC_CAN3_CLK_ENABLED--;
//    if(HAL_RCC_CAN3_CLK_ENABLED==0){
      __HAL_RCC_CAN3_CLK_DISABLE();
//    }
//    HAL_RCC_CAN2_CLK_ENABLED--;
//    if(HAL_RCC_CAN2_CLK_ENABLED==0){
//      __HAL_RCC_CAN2_CLK_DISABLE();
//    }
//    HAL_RCC_CAN1_CLK_ENABLED--;
//    if(HAL_RCC_CAN1_CLK_ENABLED==0){
//      __HAL_RCC_CAN1_CLK_DISABLE();
//    }
  
    /**CAN3 GPIO Configuration    
    PA8     ------> CAN3_RX
    PA15     ------> CAN3_TX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_15);

  /* USER CODE BEGIN CAN3_MspDeInit 1 */

  /* USER CODE END CAN3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

void HANDLE_CAN_FIFO0(CAN_HandleTypeDef *hcan)
{

	uint8_t Receive_Buffer[8] = {0};
	if(hcan->Instance == CAN1)
	{
		HAL_CAN_GetRxMessage(hcan, 0, &CAN1_RX_HEADER, Receive_Buffer);
		//Run Controller_Parser
		if(Parse_Controller_CAN_message(CAN1_RX_HEADER, Receive_Buffer))
		{}

	}
	else if(hcan->Instance == CAN2)
	{
		HAL_CAN_GetRxMessage(hcan, 0, &CAN2_RX_HEADER, Receive_Buffer);
		//Run HUB200 parser
		if(HUB_2XX_message_Parser(CAN2_RX_HEADER, Receive_Buffer))
		{}
	}

}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
