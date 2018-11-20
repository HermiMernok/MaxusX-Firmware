/*
 * F769_UART.h
 *
 *  Created on: 03 Sep 2018
 *      Author: NeilPretorius
 */

#ifndef F769_UART_H_
#define F769_UART_H_

#include "Global_Variables.h"

//COM port count
#define COMn			6

//Port names
typedef enum
{
	COM_EXP1		= 0,
	COM_EXP4	    = 1,
	COM_MF			= 2,
	COM_External    = 3,
	COM_EXP2  		= 4,
	COM_EXP3        = 5,

}COM_TypeDef;

/*--------------------------------
Functions made public
----------------------------------*/
void UART_Init(COM_TypeDef COMx, uint32_t BaudRate);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void USART_SendString(COM_TypeDef COM, char Data[]);
void USART_SendByte(COM_TypeDef COM, uint8_t Data);
void USART_SendArray(COM_TypeDef COM, uint8_t Data[], uint16_t Size);
void DMA_UART_RWD_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size);
uint16_t DMA_UART_Vision_Get_WRPtr(uint16_t rx_buffer_size);
uint16_t DMA_UART_Ranger_Get_WRPtr(uint16_t rx_buffer_size);
uint16_t DMA_UART_UBlock_Get_WRPtr(uint16_t rx_buffer_size);;
void DMA_UART_Pulse400_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size);
void DMA_UART_Ublock_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size);
void DMA_UART_RF_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size);
void DMA_UART_RF_TX(uint8_t tx_buffer[], uint16_t tx_buffer_size);
void DMA_UART_External_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size);

extern void _Error_Handler(char *, int);

#endif /* F769_UART_H_ */
