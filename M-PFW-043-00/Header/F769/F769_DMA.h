/*
 * F769_DMA.h
 *
 *  Created on: 03 Sep 2018
 *      Author: NeilPretorius
 */

#ifndef F769_DMA_H_
#define F769_DMA_H_

#include "Global_Variables.h"


uint8_t Config_RX_Buffer[10];

/*-------------------
UARTS
---------------------*/
//Uart 1 - RX
//DMA2_Channel4_Stream5
//Uart 2 - TX
//DMA2_Channel4_Stream7
#define USART1_DMA                       DMA2

#define USART1_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define USART1_TX_DMA_STREAM             DMA2_Stream7

#define USART1_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define USART1_RX_DMA_STREAM             DMA2_Stream5

//Uart 2 - RX
//DMA1_Channel4_Stream5
//Uart 2 - TX
//DMA1_Channel4_Stream6
#define USART2_DMA                       DMA1

#define USART2_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define USART2_TX_DMA_STREAM             DMA1_Stream6

#define USART2_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define USART2_RX_DMA_STREAM             DMA1_Stream5

//Uart 4 - RX
//DMA1_Channel4_Stream2
//Uart 4 - TX
//DMA1_Channel4_Stream4
#define UART4_DMA                       DMA1

#define UART4_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define UART4_TX_DMA_STREAM             DMA1_Stream4

#define UART4_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define UART4_RX_DMA_STREAM             DMA1_Stream2


//Uart 5 - RX
//DMA1_Channel4_Stream0
//Uart 5 - TX
//DMA1_Channel4_Stream7
#define USART5_DMA                       DMA1

#define USART5_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define USART5_TX_DMA_STREAM             DMA1_Stream7

#define USART5_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define USART5_RX_DMA_STREAM             DMA1_Stream0

//Uart 6 - RX
//DMA2_Channel5_Stream2			// stream 1 interferes with something...
//Uart 6 - TX
//DMA2_Channel5_Stream7
#define USART6_DMA                       DMA2

#define USART6_TX_DMA_CHANNEL            DMA_CHANNEL_5
#define USART6_TX_DMA_STREAM             DMA2_Stream7

#define USART6_RX_DMA_CHANNEL            DMA_CHANNEL_5
#define USART6_RX_DMA_STREAM             DMA2_Stream2

//Uart 7 - RX
//DMA2_Channel5_Stream2
//Uart 7 - TX
//DMA2_Channel5_Stream7
#define UART7_DMA                       DMA1

#define UART7_TX_DMA_CHANNEL            DMA_CHANNEL_5
#define UART7_TX_DMA_STREAM             DMA1_Stream1

#define UART7_RX_DMA_CHANNEL            DMA_CHANNEL_5
#define UART7_RX_DMA_STREAM             DMA1_Stream3

//Uart 8 - RX
//DMA1_Channel5_Stream6
//Uart 3 - TX
//DMA1_Channel5_Stream0
#define UART8_DMA                       DMA1

#define UART8_TX_DMA_CHANNEL            DMA_CHANNEL_5
#define UART8_TX_DMA_STREAM             DMA1_Stream0

#define UART8_RX_DMA_CHANNEL            DMA_CHANNEL_5
#define UART8_RX_DMA_STREAM             DMA1_Stream6

extern DMA_HandleTypeDef hdma_uart1_rx;
extern DMA_HandleTypeDef hdma_uart2_rx;
extern DMA_HandleTypeDef hdma_uart3_rx;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart5_rx;
extern DMA_HandleTypeDef hdma_uart6_rx;
extern DMA_HandleTypeDef hdma_uart7_rx;

void DMA_Init (void);
void DMA_UART_COM_EXP1_RX(uint8_t rx_buffer[], uint16_t rx_buffer_size);

//extern uint8_t vision_inbuf[];
//extern uint8_t ranger_inbuf[];
//extern uint8_t uBlock_inbuf[];


#endif /* F769_DMA_H_ */
