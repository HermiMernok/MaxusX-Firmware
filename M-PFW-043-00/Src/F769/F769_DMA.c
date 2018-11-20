/*
 * F769_DMA.c
 *
 *  Created on: 03 Sep 2018
 *      Author: NeilPretorius
 */


#include "F769_DMA.h"


DMA_HandleTypeDef hdma_uart1_rx;
DMA_HandleTypeDef hdma_uart2_rx;
DMA_HandleTypeDef hdma_uart3_rx;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart5_rx;
DMA_HandleTypeDef hdma_uart6_rx;
DMA_HandleTypeDef hdma_uart6_tx;
DMA_HandleTypeDef hdma_uart7_rx;

//uint8_t vision_inbuf[VISION_BUF_LEN] =
//{ };
//uint8_t ranger_inbuf[VISION_BUF_LEN] =
//{ };
//uint8_t uBlox_inbuf[VISION_BUF_LEN] =
//{ };
extern vision_device  Pulse400_Module;

void DMA_Init (void)
{
	DMA_UART_COM_EXP1_RX(Pulse400_Module.vision_inbuf, VISION_BUF_LEN);
//	UBLOX_Module.vision_inbuf = uBlox_inbuf;
//	DMA_UART_Ublock_RX(UBLOX_Module.vision_inbuf, VISION_BUF_LEN);
//
//	if(System_Flags.System_HW_Rev > 2)
	DMA_UART_External_RX(Config_RX_Buffer, 9);

}


