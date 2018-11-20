/**
 ******************************************************************************
 * @file    spi_flash.h
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    18-April-2011
 * @brief   This file contains all the functions prototypes for the spi_flash
 *          firmware driver.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Global_Variables.h"
#include "F769_SPI.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* M25P SPI Flash supported commands */  
#define MR25H40_CMD_WRITE          0x02  /* Write to Memory instruction */
#define MR25H40_CMD_WRSR           0x01  /* Write Status Register instruction */
#define MR25H40_CMD_WREN           0x06  /* Write enable instruction */
#define MR25H40_CMD_READ           0x03  /* Read from Memory instruction */
#define MR25H40_CMD_RDSR           0x05  /* Read Status Register instruction  */
#define MR25H40_CMD_RDID           0x9F  /* Read identification */
#define MR25H40_CMD_SE             0xD8  /* Sector Erase instruction */
#define MR25H40_CMD_BE             0xC7  /* Bulk Erase instruction */

#define MR25H40_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */

#define MR25H40_DUMMY_BYTE         0x55
#define MR25H40_SPI_PAGESIZE       0x100

#define MR25H40_M25P128_ID         0x202018
#define MR25H40_M25P64_ID          0x202017

///* M25P FLASH SPI Interface pins  */
#define MR25H40_CS_PIN						GPIO_PIN_1
#define MR25H40_CS_GPIO_PORT					GPIOB

#define MR25H_Size				   	1			// 0 if you only want a 16 bit address

/* Exported macro ------------------------------------------------------------*/
/* Select MR25H40: Chip Select pin low */

/* Deselect MR25H40: Chip Select pin high */
//#define MR25H40_CS_HIGH()      HAL_GPIO_WritePin(MR25H40_CS_GPIO_PORT, MR25H40_CS_PIN, GPIO_PIN_SET)


/* High layer functions  */
void MR25H40_CS_LOW(void);
void MR25H40_CS_HIGH(void);
void MR25H40_DeInit(void);
void MR25H40_Write_StatusByte(uint8_t data);
void MR25H40_Init(void);
void MR25H40_EraseSector(uint32_t SectorAddr);
void MR25H40_EraseBulk(void);
bool MR25H40_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
bool MR25H40_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void MR25H40_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t MR25H40_ReadID(void);
void MR25H40_StartReadSequence(uint32_t ReadAddr);
void MR25H40_CS_Init(void);

/* Low layer functions */
uint8_t MR25H40_ReadByte(void);
uint8_t MR25H40_SendByte(uint8_t byte);
uint16_t MR25H40_SendHalfWord(uint16_t HalfWord);
void MR25H40_WriteEnable(void);
bool MR25H40_WaitForWriteEnd(void);

uint8_t NV_RAM_SPI_Test(void);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_FLASH_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
