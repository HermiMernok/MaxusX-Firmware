/*
 * F769_SRAM.c
 *
 *  Created on: 03 Feb 2017
 *      Author: JacoOlivier
 */

#include "F769_SRAM.h"

SRAM_HandleTypeDef SRAM_Dev;
FMC_NORSRAM_TimingTypeDef p;
FMC_NORSRAM_TimingTypeDef ex_p;

void SRAM_Init(void)
{


	HAL_SRAM_DeInit(&SRAM_Dev);

	SRAM_Dev.Instance = FMC_NORSRAM_DEVICE;

	SRAM_Dev.Init.NSBank = FMC_NORSRAM_BANK2;
	SRAM_Dev.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
	SRAM_Dev.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
	SRAM_Dev.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
	SRAM_Dev.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
	SRAM_Dev.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
	SRAM_Dev.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
	SRAM_Dev.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
	SRAM_Dev.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
	SRAM_Dev.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
	SRAM_Dev.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
	SRAM_Dev.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
	//	SRAM_Dev.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
	//	SRAM_Dev.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;

		p.AddressSetupTime = 2;
		p.AddressHoldTime = 1;
		p.DataSetupTime = 2;
		p.BusTurnAroundDuration = 1;
		p.CLKDivision = 2;
		p.DataLatency = 1;
		p.AccessMode = FMC_ACCESS_MODE_B;
//	p.AddressSetupTime = 2;
//	p.AddressHoldTime = 5;
//	p.DataSetupTime = 3;
//	p.BusTurnAroundDuration = 1;
//	p.CLKDivision = 2;
//	p.DataLatency = 1;

	HAL_SRAM_Init(&SRAM_Dev, &p, &ex_p);


}

//void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
//{
//	GPIO_InitTypeDef gpio_init_structure;
//
//	/* Enable FMC clock */
//	__HAL_RCC_FMC_CLK_ENABLE();
//
//	/* Enable GPIOs clock */
//	__HAL_RCC_GPIOD_CLK_ENABLE();
//	__HAL_RCC_GPIOE_CLK_ENABLE();
//	__HAL_RCC_GPIOF_CLK_ENABLE();
//	__HAL_RCC_GPIOG_CLK_ENABLE();
//
//	/*
//	   +-------------------+--------------------+------------------+------------------+
//	   | PD0  <-> FMC_D2    | PD2  <-> FMC_NBL0  | PF0 <-> FMC_A0  | PG0 <-> FMC_A10  |
//	   | PD1  <-> FMC_D3    | PD3  <-> FMC_NBL1  | PF1 <-> FMC_A1  | PG1 <-> FMC_A11  |
//	   | PD4  <-> FMC_NOE   | PE2  <-> FMC_A23   | PF2 <-> FMC_A2  | PG2 <-> FMC_A12  |
//	   | PD5  <-> FMC_NWE   | PE3  <-> FMC_A19   | PF3 <-> FMC_A3  | PG3 <-> FMC_A13  |
//	   | PD8  <-> FMC_D13   | PE4  <-> FMC_A20   | PF4 <-> FMC_A4  | PG4 <-> FMC_A14  |
//	   | PD9  <-> FMC_D14   | PE5  <-> FMC_A21   | PF5 <-> FMC_A5  | PG5 <-> FMC_A15  |
//	   | PD10 <-> FMC_D15   | PE6  <-> FMC_A22   | PF12 <-> FMC_A6 | PC8 <-> FMC_NE2  |
//	   | PD11 <-> FMC_A16   | PE7  <-> FMC_D4    | PF13 <-> FMC_A7 | PG13 <-> FMC_A24 |
//	   | PD12 <-> FMC_A17   | PE8  <-> FMC_D5    | PF14 <-> FMC_A8 | PG14 <-> FMC_A25 |
//	   | PD13 <-> FMC_A18   | PE9  <-> FMC_D6    | PF15 <-> FMC_A9 |------------------+
//	   | PD14 <-> FMC_D0    | PE10 <-> FMC_D7    |------------------+
//	   | PD15 <-> FMC_D1    | PE11 <-> FMC_D8    |
//	   | PD6  <-> FMC_NWAIT | PE12 <-> FMC_D9    |
//	   | PD7  <-> FMC_NE1   | PE13 <-> FMC_D10   |
//	                        | PE14 <-> FMC_D11   |
//	                        | PE15 <-> FMC_D12   |
//	   +---------------------                    +--------------------+
//	 */
//
//	/* Common GPIO configuration */
//	gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
//	gpio_init_structure.Pull      = GPIO_PULLDOWN;
//	gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
//	gpio_init_structure.Alternate = GPIO_AF12_FMC;
//
//	/* GPIOD configuration */
//	gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |\
//			GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 |\
//			GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
//	HAL_GPIO_Init(GPIOD, &gpio_init_structure);
//
//	gpio_init_structure.Pin   = GPIO_PIN_4 ;
//	gpio_init_structure.Pull      = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOD, &gpio_init_structure);
//	/* GPIOE configuration */
//	gpio_init_structure.Pin   = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | \
//			GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |\
//			GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
//	HAL_GPIO_Init(GPIOE, &gpio_init_structure);
//
//	/* GPIOF configuration */
//	gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 |\
//			GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
//	HAL_GPIO_Init(GPIOF, &gpio_init_structure);
//
//	/* GPIOG configuration */
//	gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 |\
//			GPIO_PIN_5 | GPIO_PIN_13| GPIO_PIN_14;
//	HAL_GPIO_Init(GPIOG, &gpio_init_structure);
//
//	/* Pulled High GPIO configuration */
//	gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
//	gpio_init_structure.Pull      = GPIO_NOPULL;
//	gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
//	gpio_init_structure.Alternate = GPIO_AF12_FMC;
//
//	/* NE1 and NWAIT configuration */
//	gpio_init_structure.Pin   = GPIO_PIN_6 | GPIO_PIN_7;
//	HAL_GPIO_Init(GPIOD, &gpio_init_structure);
//
//	/* NE2 configuration */
//
//	gpio_init_structure.Pin = GPIO_PIN_8;
//	gpio_init_structure.Mode = GPIO_MODE_AF_PP;
//	gpio_init_structure.Pull = GPIO_NOPULL;
//	gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//	gpio_init_structure.Alternate = GPIO_AF9_FMC;
//
//	HAL_GPIO_Init(GPIOC, &gpio_init_structure);
//	//
//	/* USER CODE BEGIN FMC_MspInit 0 */
//
//	/* USER CODE END FMC_MspInit 0 */
//	GPIO_InitTypeDef GPIO_InitStruct;
//}
uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
	if(HAL_SRAM_Write_16b(&SRAM_Dev, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
	{
		//   return SDRAM_ERROR;
	}
	else
	{
		//  return SDRAM_OK;
	}
}

/**
 * @brief  Reads an amount of data from the SDRAM memory in polling mode.
 * @param  uwStartAddress: Read start address
 * @param  pData: Pointer to data to be read
 * @param  uwDataSize: Size of read data from the memory
 * @retval SDRAM status
 */
uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize)
{
	if(HAL_SRAM_Read_16b(&SRAM_Dev, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief  Reads an amount of data from the SDRAM memory in polling mode.
 * @param  uwStartAddress: Read start address
 * @param  pData: Pointer to data to be read
 * @param  uwDataSize: Size of read data from the memory
 * @retval SDRAM status
 */
uint8_t BSP_SRAM_ReadData32(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize)
{
	if(HAL_SRAM_Read_32b(&SRAM_Dev, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
