/*
 * F769_SRAM.h
 *
 *  Created on: 03 Feb 2017
 *      Author: JacoOlivier
 */

#ifndef F769_SRAM_H_
#define F769_SRAM_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"



/* DMA definitions for SRAM DMA transfer */
#define __DMAx_CLK_ENABLE                 __HAL_RCC_DMA2_CLK_ENABLE
#define __DMAx_CLK_DISABLE                __HAL_RCC_DMA2_CLK_DISABLE

void SRAM_Init(void);

uint8_t BSP_SRAM_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_SRAM_ReadData32(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
#endif /* F769_SRAM_H_ */
