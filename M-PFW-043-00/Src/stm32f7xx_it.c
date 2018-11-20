/**
 ******************************************************************************
 * @file    stm32f7xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 *
 * COPYRIGHT(c) 2018 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_it.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "F769_UART.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern HCD_HandleTypeDef hhcd_USB_OTG_FS;
extern UART_HandleTypeDef huartx[];
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern DMA_HandleTypeDef hdma_uart5_rx;
extern DMA_HandleTypeDef hdma_uart6_tx;
extern DMA_HandleTypeDef hdma_uart6_rx;
extern uint8_t RF_RX_OK;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart8;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* Private variables ---------------------------------------------------------*/
extern LTDC_HandleTypeDef hltdc_discovery;

/******************************************************************************/
/*            Cortex-M7 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/


/**
  * @brief  This function handles LTDC interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
  HAL_LTDC_IRQHandler(&hltdc_discovery);
}

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
	/* USER CODE BEGIN HardFault_IRQn 1 */

	/* USER CODE END HardFault_IRQn 1 */
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void)
{
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
		/* USER CODE END W1_MemoryManagement_IRQn 0 */
	}
	/* USER CODE BEGIN MemoryManagement_IRQn 1 */

	/* USER CODE END MemoryManagement_IRQn 1 */
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void)
{
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_BusFault_IRQn 0 */
		/* USER CODE END W1_BusFault_IRQn 0 */
	}
	/* USER CODE BEGIN BusFault_IRQn 1 */

	/* USER CODE END BusFault_IRQn 1 */
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void)
{
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_UsageFault_IRQn 0 */
		/* USER CODE END W1_UsageFault_IRQn 0 */
	}
	/* USER CODE BEGIN UsageFault_IRQn 1 */

	/* USER CODE END UsageFault_IRQn 1 */
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{

	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();

	//Systic function required for vision libs
	TimingDelay_Decrement();

}


/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles USB On The Go FS global interrupt.
 */
void OTG_FS_IRQHandler(void)
{
	/* USER CODE BEGIN OTG_FS_IRQn 0 */

	/* USER CODE END OTG_FS_IRQn 0 */
	HAL_HCD_IRQHandler(&hhcd_USB_OTG_FS);
	/* USER CODE BEGIN OTG_FS_IRQn 1 */

	/* USER CODE END OTG_FS_IRQn 1 */
}

void USART1_IRQHandler(void)
{
	/* USER CODE BEGIN USART3_IRQn 0 */

	//Check if the RX interrupt is the reason for entering this IRQ
	if(__HAL_UART_GET_FLAG(&huartx[COM_EXP1], UART_FLAG_RXNE) == true)
	{
		uint8_t rx_byte = huartx[COM_EXP1].Instance->RDR;		//Load received byte into temporary buffer

 		__HAL_UART_FLUSH_DRREGISTER(&huartx[COM_EXP1]); 		// Clear the buffer to prevent overrun
	}

	HAL_UART_IRQHandler(&huartx[COM_EXP1]);

	/* USER CODE END USART3_IRQn 0 */

	/* USER CODE BEGIN USART3_IRQn 1 */

	/* USER CODE END USART3_IRQn 1 */
}

void USART3_IRQHandler(void)
{
	/* USER CODE BEGIN USART3_IRQn 0 */

	/* USER CODE END USART3_IRQn 0 */
	HAL_UART_IRQHandler(&huartx[COM_EXP1]);
	/* USER CODE BEGIN USART3_IRQn 1 */

	/* USER CODE END USART3_IRQn 1 */
}

void UART5_IRQHandler(void)
{
	HAL_NVIC_ClearPendingIRQ(UART5_IRQn);

	//Check if the RX interrupt is the reason for entering this IRQ
	if(__HAL_UART_GET_FLAG(&huartx[COM_External], UART_FLAG_RXNE) == true)
	{
		uint8_t rx_byte = huartx[COM_External].Instance->RDR;		//Load received byte into temporary buffer

		__HAL_UART_FLUSH_DRREGISTER(&huartx[COM_External]); // Clear the buffer to prevent overrun

	}

	//Handle UART service
	HAL_UART_IRQHandler(&huartx[COM_External]);
}

void DMA1_Stream0_IRQHandler(void)
{
	//Check if DMA got expected bytes, if not then assume no card
//	if(__HAL_DMA_GET_FLAG(&hdma_uart5_rx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_uart5_rx)) != RESET)
//	{
//		HAL_NVIC_ClearPendingIRQ(DMA1_Stream0_IRQn);
		HAL_DMA_IRQHandler(&hdma_uart5_rx);
//	}
}


/*
* @brief This function handles CAN1 RX0 interrupt.
*/
void CAN1_RX0_IRQHandler(void)
{
	//Receive CAN message from CAN1 and process
	HAL_CAN_IRQHandler(&hcan1);
}

/*
* @brief This function handles CAN2 RX0 interrupt.
*/
void CAN2_RX0_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&hcan2);
}

void USART6_IRQHandler(void)
{

	HAL_NVIC_ClearPendingIRQ(USART6_IRQn);
	if(__HAL_UART_GET_FLAG(&huartx[4], UART_FLAG_RXNE) == 1)
	{
		uint8_t rx_byte = huartx[4].Instance->RDR;		//Load received byte into temporary buffer

		__HAL_UART_FLUSH_DRREGISTER(&huartx[4]); // Clear the buffer to prevent overrun

	}
	HAL_UART_IRQHandler(&huartx[4]);
}

void DMA2_Stream6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_uart6_tx);
}


void DMA2_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_uart6_rx);
}

/**
 * @brief This function handles Timer 3 global interrupt.
 */
void TIM3_IRQHandler (void)
{

	HAL_TIM_IRQHandler(&htim3);
	TIM3_Stop();

	/* === Set flag to allow time update === */
	RTC_Flags.RTC_TimeReady=true;

	/* === Statemachine for displaying information on LCD === */

	TIM3_Start();
}

/**
 * @brief This function handles Timer 4 global interrupt.
 */
void TIM4_IRQHandler (void)
{

	HAL_TIM_IRQHandler(&htim3);
	TIM4_Stop();

	/* === Set flag to allow time update === */
	RTC_Flags.RTC_TimeReady=true;

	/* === Statemachine for displaying information on LCD === */

	TIM4_Start();
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART5)
	{
		//debug = Config_RX_Buffer[0];

	}

	__HAL_UART_FLUSH_DRREGISTER(huart); // Clear the buffer to prevent overrun
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
