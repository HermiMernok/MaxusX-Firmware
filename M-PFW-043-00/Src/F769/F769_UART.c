/*
 * F769_UART.c
 *
 *  Created on: 03 Sep 2018
 *      Author: NeilPretorius
 */


#include "F769_UART.h"

extern UART_InitTypeDef 	USART_InitStructure;


UART_HandleTypeDef huartx[COMn];
USART_TypeDef* COM_USART[COMn] = {USART1, USART3,UART4, UART5, USART6, UART8};
const uint8_t COM_IRQ[COMn] = {USART1_IRQn, USART3_IRQn, UART4_IRQn, UART5_IRQn, USART6_IRQn, UART8_IRQn};
extern DMA_HandleTypeDef hdma_uart6_tx;
extern DMA_HandleTypeDef hdma_uart5_Rx;

/*-----------------------------------------
 *Function name and description
 *---------
 * Configures a UART
 *
 *Inputs:
 *---------
 * COM port and Baudrate
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void UART_Init(COM_TypeDef COMx, uint32_t BaudRate)
{

	HAL_UART_DeInit(&huartx[COMx]);
	huartx[COMx].Instance = COM_USART[COMx];
	huartx[COMx].Init.BaudRate = BaudRate;
	huartx[COMx].Init.WordLength = UART_WORDLENGTH_8B;
	huartx[COMx].Init.StopBits = UART_STOPBITS_1;
	huartx[COMx].Init.Parity = UART_PARITY_NONE;
	huartx[COMx].Init.Mode = UART_MODE_TX_RX;
	huartx[COMx].Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huartx[COMx].Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huartx[COMx].AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	HAL_UART_Init(&huartx[COMx]);

	__HAL_UART_ENABLE_IT(&huartx[COMx], UART_IT_RXNE);
}

/*-----------------------------------------
 *Function name and description
 *---------
 * Configures a UART for DMA operation
 *
 *Inputs:
 *---------
 * COM port and Baudrate
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void UART_DMA_Init(COM_TypeDef COMx, uint32_t BaudRate)
{

	huartx[COMx].Instance = COM_USART[COMx];
	huartx[COMx].Init.BaudRate = BaudRate;
	huartx[COMx].Init.WordLength = UART_WORDLENGTH_8B;
	huartx[COMx].Init.StopBits = UART_STOPBITS_1;
	huartx[COMx].Init.Parity = UART_PARITY_NONE;
	huartx[COMx].Init.Mode = UART_MODE_TX_RX;
	huartx[COMx].Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huartx[COMx].Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huartx[COMx].AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	HAL_UART_Init(&huartx[COMx]);

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if(uartHandle->Instance==UART4)
	{
		/* UART4 clock enable */
		__HAL_RCC_UART4_CLK_ENABLE();

		HAL_NVIC_SetPriority(UART4_IRQn, 0x0f, 0);
		HAL_NVIC_EnableIRQ(UART4_IRQn);

		/**UART4 GPIO Configuration
    PI9     ------> UART4_RX
    PH13     ------> UART4_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
		HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
		HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

		/* USER CODE BEGIN UART4_MspInit 1 */

		/* USER CODE END UART4_MspInit 1 */
	}
	else if(uartHandle->Instance==UART5)
	{
		/* UART5 clock enable */
		__HAL_RCC_UART5_CLK_ENABLE();

		HAL_NVIC_SetPriority(UART5_IRQn, 0x0f, 0);
		HAL_NVIC_EnableIRQ(UART5_IRQn);

		/**UART5 GPIO Configuration
    PC12     ------> UART5_TX
    PB8     ------> UART5_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_UART5;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN UART5_MspInit 1 */

		/* USER CODE END UART5_MspInit 1 */
	}
	else if(uartHandle->Instance==UART8)
	{

		/* UART8 clock enable */
		__HAL_RCC_UART8_CLK_ENABLE();

		HAL_NVIC_SetPriority(UART8_IRQn, 0x0f, 0);
		HAL_NVIC_EnableIRQ(UART8_IRQn);

		/**UART8 GPIO Configuration
    PE0     ------> UART8_RX
    PE1     ------> UART8_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART8;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* USER CODE BEGIN UART8_MspInit 1 */

		/* USER CODE END UART8_MspInit 1 */
	}
	else if(uartHandle->Instance==USART1)
	{

		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		HAL_NVIC_SetPriority(USART1_IRQn, 0x0F, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);

		/**USART1 GPIO Configuration
    PB14     ------> USART1_TX
    PB15     ------> USART1_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_14 | GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_USART1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
	else if(uartHandle->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspInit 0 */

		/* USER CODE END USART3_MspInit 0 */
		/* USART3 clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		HAL_NVIC_SetPriority(USART3_IRQn, 0x0f, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);

		/**USART3 GPIO Configuration
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USER CODE BEGIN USART3_MspInit 1 */

		/* USER CODE END USART3_MspInit 1 */
	}
	else if(uartHandle->Instance==USART6)
	{
		/* USER CODE BEGIN USART6_MspInit 0 */

		/* USER CODE END USART6_MspInit 0 */
		/* USART6 clock enable */
		__HAL_RCC_USART6_CLK_ENABLE();

		HAL_NVIC_SetPriority(USART6_IRQn, 0x0f, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);

		/**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USER CODE BEGIN USART6_MspInit 1 */

		/* USER CODE END USART6_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

	if(uartHandle->Instance==UART4)
	{
		/* USER CODE BEGIN UART4_MspDeInit 0 */

		/* USER CODE END UART4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART4_CLK_DISABLE();

		/**UART4 GPIO Configuration
    PI9     ------> UART4_RX
    PH13     ------> UART4_TX
		 */
		HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9);

		HAL_GPIO_DeInit(GPIOH, GPIO_PIN_13);

		/* USER CODE BEGIN UART4_MspDeInit 1 */
		HAL_NVIC_DisableIRQ(UART4_IRQn);
		/* USER CODE END UART4_MspDeInit 1 */
	}
	else if(uartHandle->Instance==UART5)
	{
		/* USER CODE BEGIN UART5_MspDeInit 0 */

		/* USER CODE END UART5_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART5_CLK_DISABLE();

		/**UART5 GPIO Configuration
    PC12     ------> UART5_TX
    PB8     ------> UART5_RX
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

		/* USER CODE BEGIN UART5_MspDeInit 1 */
		HAL_NVIC_DisableIRQ(UART5_IRQn);
		/* USER CODE END UART5_MspDeInit 1 */
	}
	else if(uartHandle->Instance==UART8)
	{
		/* USER CODE BEGIN UART8_MspDeInit 0 */

		/* USER CODE END UART8_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART8_CLK_DISABLE();

		/**UART8 GPIO Configuration
    PE0     ------> UART8_RX
    PE1     ------> UART8_TX
		 */
		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0|GPIO_PIN_1);

		/* USER CODE BEGIN UART8_MspDeInit 1 */
		HAL_NVIC_DisableIRQ(UART8_IRQn);
		/* USER CODE END UART8_MspDeInit 1 */
	}
	else if(uartHandle->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
    PB14     ------> USART1_TX
    PB15     ------> USART1_RX
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14|GPIO_PIN_15);

		/* USER CODE BEGIN USART1_MspDeInit 1 */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE END USART1_MspDeInit 1 */
	}
	else if(uartHandle->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

		/* USER CODE BEGIN USART3_MspDeInit 1 */
		HAL_NVIC_DisableIRQ(USART3_IRQn);
		/* USER CODE END USART3_MspDeInit 1 */
	}
	else if(uartHandle->Instance==USART6)
	{
		/* USER CODE BEGIN USART6_MspDeInit 0 */

		/* USER CODE END USART6_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

		/* USER CODE BEGIN USART6_MspDeInit 1 */
		HAL_NVIC_DisableIRQ(USART6_IRQn);
		/* USER CODE END USART6_MspDeInit 1 */
	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 * Configures a UART-DMA operation for the
 * Pulse400 module
 *
 *Inputs:
 *---------
 * COM port and Baudrate
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void DMA_UART_COM_EXP1_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size)
{
	//Disable Interrupt
	HAL_NVIC_DisableIRQ(COM_IRQ[COM_EXP1]);

	//Disable RX interrupt
	__HAL_UART_DISABLE_IT(&huartx[COM_EXP1], UART_IT_RXNE);

	//Reset DMA on RX pin
	HAL_DMA_DeInit(huartx[COM_EXP1].hdmarx);

	//Enable DMA1 Clock
	__HAL_RCC_DMA2_CLK_ENABLE();

	//Assign DMA mode of operation
	hdma_uart1_rx.Instance = USART1_RX_DMA_STREAM;
	hdma_uart1_rx.Init.Channel = USART1_RX_DMA_CHANNEL;
	hdma_uart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_uart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma_uart1_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
	hdma_uart1_rx.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma_uart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_uart1_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_uart1_rx.Init.Mode = DMA_CIRCULAR;
	hdma_uart1_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
	hdma_uart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_uart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_uart1_rx.Init.Priority = DMA_PRIORITY_HIGH;

	//Initialize DMA on RX pin
	HAL_DMA_Init(&hdma_uart1_rx);

	__HAL_LINKDMA(&huartx[COM_EXP1], hdmarx, hdma_uart1_rx);

	__HAL_UART_SEND_REQ(&huartx[COM_EXP1],UART_RXDATA_FLUSH_REQUEST);

	__HAL_UART_CLEAR_OREFLAG(&huartx[COM_EXP1]);

	//Set up DMA for reception
	HAL_UART_Receive_DMA(&huartx[COM_EXP1], rx_buffer, rx_buffer_size);

}

/*-----------------------------------------
 *Function name and description
 *---------
 * Configures a UART-DMA operation for the
 * UART 5 External COM
 *
 *Inputs:
 *---------
 * COM port and Baudrate
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void DMA_UART_External_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size)
{
	//Disable Interrupt
	HAL_NVIC_DisableIRQ(UART5_IRQn);

	//Disable RX interrupt
	__HAL_UART_DISABLE_IT(&huartx[COM_External], UART_IT_RXNE);

	//Reset DMA on RX pin
	HAL_DMA_DeInit(huartx[COM_External].hdmarx);

	//Enable DMA1 Clock
	__HAL_RCC_DMA1_CLK_ENABLE();

	//Assign DMA mode of operation
	hdma_uart5_rx.Instance = USART5_RX_DMA_STREAM;
	hdma_uart5_rx.Init.Channel = USART5_RX_DMA_CHANNEL;
	hdma_uart5_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_uart5_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma_uart5_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
	hdma_uart5_rx.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma_uart5_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	//hdma_uart5_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_uart5_rx.Init.Mode = DMA_CIRCULAR;
	hdma_uart5_rx.Init.Mode = DMA_NORMAL;
	hdma_uart5_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
	hdma_uart5_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_uart5_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_uart5_rx.Init.Priority = DMA_PRIORITY_HIGH;

	HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

	//Initialize DMA on RX pin

	HAL_DMA_Init(&hdma_uart5_rx);

	__HAL_LINKDMA(&huartx[COM_External], hdmarx, hdma_uart5_rx);

	__HAL_UART_SEND_REQ(&huartx[COM_External],UART_RXDATA_FLUSH_REQUEST);

	__HAL_UART_CLEAR_OREFLAG(&huartx[COM_External]);

	//Set up DMA for reception
	__HAL_UART_FLUSH_DRREGISTER(&huartx[COM_External]);
	HAL_UART_Receive_DMA(&huartx[COM_External], rx_buffer, rx_buffer_size);
}



/*-----------------------------------------
 *Function name and description
 *---------
 * Configures a UART-DMA operation for the
 * XBEE module on the RX pin
 *
 *Inputs:
 *---------
 * COM port and Baudrate
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void DMA_UART_RF_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size)
{
	Uart_Clear_DMA_RX();
	//Disable Interrupt
	HAL_NVIC_DisableIRQ(USART6_IRQn);

	//Disable RX interrupt
	__HAL_UART_DISABLE_IT(&huartx[COM_EXP2], UART_IT_RXNE);

	//Reset DMA on RX pin
	HAL_DMA_DeInit(huartx[COM_EXP2].hdmarx);

	//Enable DMA2 Clock
	__HAL_RCC_DMA2_CLK_ENABLE();

	//Assign DMA mode of operation
	hdma_uart6_rx.Instance = USART6_RX_DMA_STREAM;
	hdma_uart6_rx.Init.Channel = USART6_RX_DMA_CHANNEL;
	hdma_uart6_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_uart6_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma_uart6_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma_uart6_rx.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma_uart6_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_uart6_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_uart6_rx.Init.Mode = DMA_CIRCULAR;
	hdma_uart6_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
	hdma_uart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_uart6_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_uart6_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;


	//TODO cause problem after restart
	//HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	////HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

	//Initialize DMA on RX pin
	HAL_DMA_Init(&hdma_uart6_rx);

	__HAL_LINKDMA(&huartx[COM_EXP2], hdmarx, hdma_uart6_rx);

	__HAL_UART_SEND_REQ(&huartx[COM_EXP2],UART_RXDATA_FLUSH_REQUEST);

	__HAL_UART_CLEAR_OREFLAG(&huartx[COM_EXP2]);

	//		Set up DMA for reception
	HAL_UART_Receive_DMA(&huartx[COM_EXP2], rx_buffer, rx_buffer_size);
}

/*-----------------------------------------
 *Function name and description
 *---------
 * Configures a UART-DMA operation for the
 * XBEE module on the TX pin
 *
 *Inputs:
 *---------
 * COM port and Baudrate
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void DMA_UART_RF_TX(uint8_t tx_buffer[], uint16_t tx_buffer_size)
{
	Uart_Clear_DMA_TX();

	//TODO: This is not how one should do this coding but it makes it work
	//UART_EndTxTransfer(&huartx[COM_EXP2]);
	huartx[COM_EXP2].gState = HAL_UART_STATE_READY;

	//Disable Interrupt
	HAL_NVIC_DisableIRQ(USART6_IRQn);

	//Disable TX interrupt
	__HAL_UART_DISABLE_IT(&huartx[COM_EXP2], UART_IT_TXE);

	//Reset DMA on RX pin
	HAL_DMA_DeInit(huartx[COM_EXP2].hdmatx);

	//Enable DMA1 Clock
	__HAL_RCC_DMA2_CLK_ENABLE();

	//Assign DMA mode of operation
	hdma_uart6_tx.Instance = USART6_TX_DMA_STREAM;
	hdma_uart6_tx.Init.Channel = USART6_TX_DMA_CHANNEL;
	hdma_uart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_uart6_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	hdma_uart6_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma_uart6_tx.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma_uart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_uart6_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_uart6_tx.Init.Mode = DMA_NORMAL;
	hdma_uart6_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
	hdma_uart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_uart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_uart6_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;

	//Initialize DMA on RX pin
	HAL_DMA_Init(&hdma_uart6_tx);
	__HAL_LINKDMA(&huartx[COM_EXP2], hdmatx, hdma_uart6_tx);

	//	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
	HAL_NVIC_DisableIRQ(DMA2_Stream6_IRQn);

	//	__HAL_DMA_DISABLE_IT(&hdma_uart6_tx, DMA_IT_TC);
	//	__HAL_DMA_DISABLE_IT(&hdma_uart6_tx, DMA_IT_HT);
	//	__HAL_DMA_DISABLE_IT(&hdma_uart6_tx, DMA_IT_TE);
	//	__HAL_DMA_DISABLE_IT(&hdma_uart6_tx, DMA_IT_DME);
	//	__HAL_DMA_DISABLE_IT(&hdma_uart6_tx, DMA_IT_FE);

	__HAL_UART_SEND_REQ(&huartx[COM_EXP2],UART_TXDATA_FLUSH_REQUEST);

	__HAL_UART_CLEAR_OREFLAG(&huartx[COM_EXP2]);

	//Set up DMA for reception
	HAL_UART_Transmit_DMA(&huartx[COM_EXP2], tx_buffer, tx_buffer_size);



}

void Uart_Clear_DMA_TX(void)
{

	/* Clear all DMA Stream0 flags */
	__HAL_DMA_CLEAR_FLAG (huartx[COM_EXP2].hdmatx, __HAL_DMA_GET_TC_FLAG_INDEX(huartx[COM_EXP2].hdmatx));
	__HAL_DMA_CLEAR_FLAG (huartx[COM_EXP2].hdmatx, __HAL_DMA_GET_HT_FLAG_INDEX(huartx[COM_EXP2].hdmatx));
	__HAL_DMA_CLEAR_FLAG (huartx[COM_EXP2].hdmatx, __HAL_DMA_GET_TE_FLAG_INDEX(huartx[COM_EXP2].hdmatx));
	//__HAL_DMA_CLEAR_FLAG (Exp2_COM->hdmarx, __HAL_DMA_GET_FE_FLAG_INDEX(Exp2_COM->hdmarx));
	//__HAL_DMA_CLEAR_FLAG (Exp2_COM->hdmarx, __HAL_DMA_GET_DME_FLAG_INDEX(Exp2_COM->hdmarx));

	/* Disable the DMA Rx Stream */
	HAL_UART_DMAStop(huartx[COM_EXP2].hdmatx);

	//flush all data still in registers
	__HAL_UART_FLUSH_DRREGISTER(&huartx[COM_EXP2]);

	/* Enable the normal interrupt handler for this UART*/
	//	HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
	//	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void Uart_Clear_DMA_RX(void)
{

	/* Clear all DMA Stream0 flags */
	__HAL_DMA_CLEAR_FLAG (huartx[COM_EXP2].hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(huartx[COM_EXP2].hdmarx));
	__HAL_DMA_CLEAR_FLAG (huartx[COM_EXP2].hdmarx, __HAL_DMA_GET_HT_FLAG_INDEX(huartx[COM_EXP2].hdmarx));
	__HAL_DMA_CLEAR_FLAG (huartx[COM_EXP2].hdmarx, __HAL_DMA_GET_TE_FLAG_INDEX(huartx[COM_EXP2].hdmarx));
	//__HAL_DMA_CLEAR_FLAG (Exp2_COM->hdmarx, __HAL_DMA_GET_FE_FLAG_INDEX(Exp2_COM->hdmarx));
	//__HAL_DMA_CLEAR_FLAG (Exp2_COM->hdmarx, __HAL_DMA_GET_DME_FLAG_INDEX(Exp2_COM->hdmarx));

	/* Disable the DMA Rx Stream */
	HAL_UART_DMAStop(huartx[COM_EXP2].hdmarx);

	//flush all data still in registers
	__HAL_UART_FLUSH_DRREGISTER(&huartx[COM_EXP2]);

	/* Enable the normal interrupt handler for this UART*/
	//	HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
	//	HAL_NVIC_EnableIRQ(USART1_IRQn);
}



/*-----------------------------------------
 *Function name and description
 *---------
 * Send a string terminated with NULL
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void USART_SendString(COM_TypeDef COM, char Data[])
{
	HAL_UART_Transmit(&huartx[COM], Data, sizeof(Data)/4, 10);
}

/*-----------------------------------------
 *Function name and description
 *---------
 * Send a single byte
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void USART_SendByte(COM_TypeDef COM, uint8_t Data)
{
	HAL_UART_Transmit(&huartx[COM], &Data, 1, 10);
}

/*-----------------------------------------
 *Function name and description
 *---------
 * Send a single byte
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void USART_SendArray(COM_TypeDef COM, uint8_t* Data, uint16_t Size)
{
	HAL_UART_Transmit(&huartx[COM], Data, Size, (Size/100 + 1)*15);
}

void APP_COM_Vision_COM_TX(uint8_t COM, uint8_t* data, uint8_t length)
{
	uint8_t* data_frame;
	uint8_t data_length = 0;

	// ---- Get message frame (SOF, CRC, EOF) ----
	data_frame = get_frame(data, length, &data_length);

	USART_SendArray(COM, data_frame, data_length);
}



bool Check_TX_done(void)
{
	if(__HAL_DMA_GET_IT_SOURCE(&hdma_uart6_tx, DMA_IT_TC) != RESET)
	{
		HAL_DMA_IRQHandler(&hdma_uart6_tx);
		return true;
	}
	else
	{
		return false;
	}
}

bool Check_RX_done(void)
{
	if(__HAL_DMA_GET_IT_SOURCE(&hdma_uart6_rx, DMA_IT_TC) != RESET)
	{
		HAL_DMA_IRQHandler(&hdma_uart6_rx);
		return true;
	}
	else
	{
		return false;
	}
}
