/**
 ******************************************************************************
 * @file    SPI/MR25H40/MR25H40.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    18-April-2011
 * @brief   This file provides a set of functions needed to manage the SPI MR25H40
 *          NVRAM memory.
 *
 */

//  Simple example to write a buffer and read a buffer
//	MR25H40_WriteBuffer(local_byte, 100, 20);
//  MR25H40_ReadBuffer(RX_Buffer, 100, 20);

/* Includes ------------------------------------------------------------------*/
#include "MR25H40.h"

#include "Global_Variables.h"

extern SPI_HandleTypeDef hspi2;
/****************************************************************/
/**
 * @brief
 * @param
 *   This parameter can be one of following parameters:
 *     @arg
 * @retval None
 */
/****************************************************************/
/***********************************************/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void MR25H40_LowLevel_DeInit(void);
void MR25H40_LowLevel_Init(void); 

/* Private functions ---------------------------------------------------------*/

/****************************************************************/
/**
 * @brief  Initialize the CS PIN of the MR25H40, this function can be used if the spi bus was enabled already.
 * @param  None
 * @retval None
 */
/****************************************************************/
void MR25H40_CS_Init(void) //not needed for this application (Pin already defined)
{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	/*!< Enable GPIO clocks */
//	//	RCC_AHB1PeriphClockCmd(MR25H40_CS_GPIO_CLK, ENABLE);//MR25H40_CS_GPIO_CLK
//	__HAL_RCC_GPIOC_CLK_ENABLE();
//	/*!< Configure MR25H40 Card CS pin in output pushpull mode ********************/
//	GPIO_InitStruct.Pin = MR25H40_CS_PIN;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(MR25H40_CS_GPIO_PORT, &GPIO_InitStruct);
//	MR25H40_CS_HIGH();
}


void MR25H40_CS_LOW(void)
{
	//HAL_GPIO_WritePin(MR25H40_CS_GPIO_PORT, MR25H40_CS_PIN, GPIO_PIN_RESET);
	IO_Output_control(NV_CS, On);
}

void MR25H40_CS_HIGH(void)
{
	//HAL_GPIO_WritePin(MR25H40_CS_GPIO_PORT, MR25H40_CS_PIN, GPIO_PIN_SET);
	IO_Output_control(NV_CS, Off);
}

/****************************************************************/
/**
 * @brief  DeInitializes the peripherals used by the SPI NVRAM driver.
 * @param  None
 * @retval None
 */
/****************************************************************/
void MR25H40_DeInit(void)
{
	MR25H40_LowLevel_DeInit();
}


/****************************************************************/
/**
 * @brief  Enables the write access to the NVRAM.
 * @param  None
 * @retval None
 */
/****************************************************************/
void MR25H40_Write_StatusByte(uint8_t data)
{
	/// enable writing
	MR25H40_WriteEnable();

	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_HIGH();

	MR25H40_CS_HIGH();

	MR25H40_CS_LOW();

	/*!< Send "Write Status byte" instruction */
	MR25H40_SendByte(MR25H40_CMD_WRSR);
	/*!< Send data to be written */
	MR25H40_SendByte(data);

	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();
}



/****************************************************************/
/**
 * @brief  Erases the specified NVRAM sector.
 * @param  SectorAddr: address of the sector to erase.
 * @retval None
 */
/****************************************************************/
void MR25H40_EraseSector(uint32_t SectorAddr)
{
	/*!< Send write enable instruction */
	MR25H40_WriteEnable();

	/*!< Sector Erase */
	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();
	/*!< Send Sector Erase instruction */
	//  MR25H40_SendByte(MR25H40_CMD_SE);
	/*!< Send SectorAddr high nibble address byte */
	if (MR25H_Size) MR25H40_SendByte((SectorAddr & 0xFF0000) >> 16);
	/*!< Send SectorAddr medium nibble address byte */
	MR25H40_SendByte((SectorAddr & 0xFF00) >> 8);
	/*!< Send SectorAddr low nibble address byte */
	MR25H40_SendByte(SectorAddr & 0xFF);
	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();

	/*!< Wait the end of NVRAM writing */
	MR25H40_WaitForWriteEnd();
}



/****************************************************************/
/**
 * @brief  Erases the entire NVRAM.
 * @param  None
 * @retval None
 */
/****************************************************************/
void MR25H40_EraseBulk(void)
{
	/*!< Send write enable instruction */
	MR25H40_WriteEnable();

	/*!< Bulk Erase */
	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();
	/*!< Send Bulk Erase instruction  */
	//  MR25H40_SendByte(MR25H40_CMD_BE);
	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();

	/*!< Wait the end of NVRAM writing */
	MR25H40_WaitForWriteEnd();
}




/****************************************************************/
/**
 * @brief  Writes more than one byte to the NVRAM with a single WRITE cycle
 *         (Page WRITE sequence).
 * @note   The number of byte can't exceed the NVRAM page size.
 * @param  pBuffer: pointer to the buffer  containing the data to be written
 *         to the NVRAM.
 * @param  WriteAddr: NVRAM's internal address to write to.
 * @param  NumByteToWrite: number of bytes to write to the NVRAM, must be equal
 *         or less than "MR25H40_PAGESIZE" value.
 * @retval None
 */
/****************************************************************/
bool MR25H40_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	/*!< Enable the write access to the NVRAM */
	MR25H40_WriteEnable();

	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();

	/*!< Send "Write to Memory " instruction */
	MR25H40_SendByte(MR25H40_CMD_WRITE);
	/*!< Send WriteAddr high nibble address byte to write to */
	if (MR25H_Size) MR25H40_SendByte((WriteAddr & 0xFF0000) >> 16);
	/*!< Send WriteAddr medium nibble address byte to write to */
	MR25H40_SendByte((WriteAddr & 0xFF00) >> 8);
	/*!< Send WriteAddr low nibble address byte to write to */
	MR25H40_SendByte(WriteAddr & 0xFF);

	/*!< while there is data to be written on the NVRAM */
	while (NumByteToWrite--)
	{
		/*!< Send the current byte */
		MR25H40_SendByte(*pBuffer);
		/*!< Point on the next byte to be written */
		pBuffer++;
	}

	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();

	/*!< Wait the end of NVRAM writing */
	if(MR25H40_WaitForWriteEnd() == false)
		return false;
	else
		return true;
}



/****************************************************************/
/**
 * @brief  Writes block of data to the NVRAM. In this function, the number of
 *         WRITE cycles are reduced, using Page WRITE sequence.
 * @param  pBuffer: pointer to the buffer  containing the data to be written
 *         to the NVRAM.
 * @param  WriteAddr: NVRAM's internal address to write to.
 * @param  NumByteToWrite: number of bytes to write to the NVRAM.
 * @retval None
 */
/****************************************************************/
bool MR25H40_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

	Addr = WriteAddr % MR25H40_SPI_PAGESIZE;
	count = MR25H40_SPI_PAGESIZE - Addr;
	NumOfPage =  NumByteToWrite / MR25H40_SPI_PAGESIZE;
	NumOfSingle = NumByteToWrite % MR25H40_SPI_PAGESIZE;

	if (Addr == 0) /*!< WriteAddr is MR25H40_PAGESIZE aligned  */
	{
		if (NumOfPage == 0) /*!< NumByteToWrite < MR25H40_PAGESIZE */
		{
			if(MR25H40_WritePage(pBuffer, WriteAddr, NumByteToWrite) == false)
				return false;
		}
		else /*!< NumByteToWrite > MR25H40_PAGESIZE */
		{
			while (NumOfPage--)
			{
				if(MR25H40_WritePage(pBuffer, WriteAddr, MR25H40_SPI_PAGESIZE) == false)
					return false;
				WriteAddr +=  MR25H40_SPI_PAGESIZE;
				pBuffer += MR25H40_SPI_PAGESIZE;
			}

			if(MR25H40_WritePage(pBuffer, WriteAddr, NumOfSingle) == false)
				return false;
		}
	}
	else /*!< WriteAddr is not MR25H40_PAGESIZE aligned  */
	{
		if (NumOfPage == 0) /*!< NumByteToWrite < MR25H40_PAGESIZE */
		{
			if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > MR25H40_PAGESIZE */
			{
				temp = NumOfSingle - count;

				if(MR25H40_WritePage(pBuffer, WriteAddr, count) == false)
					return false;
				WriteAddr +=  count;
				pBuffer += count;

				if(MR25H40_WritePage(pBuffer, WriteAddr, temp) == false)
					return false;
			}
			else
			{
				if(MR25H40_WritePage(pBuffer, WriteAddr, NumByteToWrite) == false)
					return false;
			}
		}
		else /*!< NumByteToWrite > MR25H40_PAGESIZE */
		{
			NumByteToWrite -= count;
			NumOfPage =  NumByteToWrite / MR25H40_SPI_PAGESIZE;
			NumOfSingle = NumByteToWrite % MR25H40_SPI_PAGESIZE;

			if(MR25H40_WritePage(pBuffer, WriteAddr, count) == false)
				return false;
			WriteAddr +=  count;
			pBuffer += count;

			while (NumOfPage--)
			{
				if(MR25H40_WritePage(pBuffer, WriteAddr, MR25H40_SPI_PAGESIZE) == false)
					return false;
				WriteAddr +=  MR25H40_SPI_PAGESIZE;
				pBuffer += MR25H40_SPI_PAGESIZE;
			}

			if (NumOfSingle != 0)
			{
				if(MR25H40_WritePage(pBuffer, WriteAddr, NumOfSingle) == false)
					return false;
			}
		}
	}

	return true;
}



/****************************************************************/
/**
 * @brief  Reads a block of data from the NVRAM.
 * @param  pBuffer: pointer to the buffer that receives the data read from the NVRAM.
 * @param  ReadAddr: NVRAM's internal address to read from.
 * @param  NumByteToRead: number of bytes to read from the NVRAM.
 * @retval None
 */
/****************************************************************/
void MR25H40_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();

	/*!< Send "Read from Memory " instruction */
	MR25H40_SendByte(MR25H40_CMD_READ);

	/*!< Send ReadAddr high nibble address byte to read from */
	if (MR25H_Size) MR25H40_SendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte to read from */
	MR25H40_SendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte to read from */
	MR25H40_SendByte(ReadAddr & 0xFF);

	HAL_SPI_Receive(&hspi2, pBuffer,NumByteToRead, 10);
	//	while (NumByteToRead--) /*!< while there is data to be read */
	//	{
	//		/*!< Read a byte from the NVRAM */
	//		*pBuffer = MR25H40_SendByte(MR25H40_DUMMY_BYTE);
	//		/*!< Point to the next location where the byte read will be saved */
	//		pBuffer++;
	//	}


	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();
}



/****************************************************************/
/**
 * @brief  Reads NVRAM identification.
 * @param  None
 * @retval NVRAM identification
 */
/****************************************************************/
uint32_t MR25H40_ReadID(void)
{
	uint32_t  Temp0 = 0; //Temp = 0,, Temp1 = 0, Temp2 = 0

	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();

	/*!< Send "RDID " instruction */
	MR25H40_SendByte(0x05);

	/*!< Read a byte from the NVRAM */
	Temp0 = MR25H40_SendByte(MR25H40_DUMMY_BYTE);

	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();


	return Temp0;
}




/****************************************************************/
/**
 * @brief  Initiates a read data byte (READ) sequence from the NVRAM.
 *   This is done by driving the /CS line low to select the device, then the READ
 *   instruction is transmitted followed by 3 bytes address. This function exit
 *   and keep the /CS line low, so the NVRAM still being selected. With this
 *   technique the whole content of the NVRAM is read with a single READ instruction.
 * @param  ReadAddr: NVRAM's internal address to read from.
 * @retval None
 */
/****************************************************************/
void MR25H40_StartReadSequence(uint32_t ReadAddr)
{
	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();

	/*!< Send "Read from Memory " instruction */
	MR25H40_SendByte(MR25H40_CMD_READ);

	/*!< Send the 24-bit address of the address to read from -------------------*/
	/*!< Send ReadAddr high nibble address byte */
	if (MR25H_Size) MR25H40_SendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte */
	MR25H40_SendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte */
	MR25H40_SendByte(ReadAddr & 0xFF);
}



/****************************************************************/
/**
 * @brief  Reads a byte from the SPI NVRAM.
 * @note   This function must be used only if the Start_Read_Sequence function
 *         has been previously called.
 * @param  None
 * @retval Byte Read from the SPI NVRAM.
 */
/****************************************************************/
uint8_t MR25H40_ReadByte(void)
{
	return (MR25H40_SendByte(MR25H40_DUMMY_BYTE));
}




/****************************************************************/
/**
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param  byte: byte to send.
 * @retval The value of the received byte.
 */
/****************************************************************/
uint8_t MR25H40_SendByte(uint8_t byte)
{
	uint8_t rx_byte = 0;

	//Transmit data and receive result in rx_data buffer (single byte)
	HAL_SPI_TransmitReceive(&hspi2, &byte, &rx_byte, 1, 10);

	return rx_byte;
}




/****************************************************************/
/**
 * @brief  Sends a Half Word through the SPI interface and return the Half Word
 *         received from the SPI bus.
 * @param  HalfWord: Half Word to send.
 * @retval The value of the received Half Word.
 */
/****************************************************************/
uint16_t MR25H40_SendHalfWord(uint16_t HalfWord)
{
	//	/*!< Loop while DR register in not emplty */
	//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	//
	//	/*!< Send Half Word through the MR25H40 peripheral */
	//	SPI_I2S_SendData(SPI1, HalfWord);
	//
	//	/*!< Wait to receive a Half Word */
	//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//
	//	/*!< Return the Half Word read from the SPI bus */
	//	return SPI_I2S_ReceiveData(SPI1);
	return 0;
}



/****************************************************************/
/**
 * @brief  Enables the write access to the NVRAM.
 * @param  None
 * @retval None
 */
/****************************************************************/
void MR25H40_WriteEnable(void)
{//MR25H40_CS_HIGH();
	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();

	/*!< Send "Write Enable" instruction */
	MR25H40_SendByte(MR25H40_CMD_WREN);

	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();
}

/****************************************************************/
/**
 * @brief  Polls the status of the Write In Progress (WIP) flag in the NVRAM's
 *         status register and loop until write opertaion has completed.
 * @param  None
 * @retval None
 */
/****************************************************************/
bool MR25H40_WaitForWriteEnd(void)
{
	uint8_t NVRAMstatus = 0;
	uint16_t time_cntr = 0;

	/*!< Select the NVRAM: Chip Select low */
	MR25H40_CS_LOW();

	/*!< Send "Read Status Register" instruction */
	MR25H40_SendByte(MR25H40_CMD_RDSR);

	/*!< Loop as long as the memory is busy with a write cycle */
	do
	{
		/*!< Send a dummy byte to generate the clock needed by the NVRAM
    and put the value of the status register in NVRAM_Status variable */
		NVRAMstatus = MR25H40_SendByte(MR25H40_DUMMY_BYTE);

		if(time_cntr++ > 50000)
		{
			//error with NVRAM
			return false;
		}
	}
	while ((NVRAMstatus & MR25H40_WIP_FLAG) == SET); /* Write in progress */

	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();

	//passed
	return true;
}


uint8_t NV_RAM_SPI_Test(void)
{
	uint16_t time_out = 0;
	/*****************************************************/
	//check if NVRAM times out
	/*****************************************************/
	/*!< Select the NVRAM: Chip Select low */
	uint8_t NVRAMstatus = SPI_NVRAM_Failure;

	MR25H40_CS_LOW();
	time_out = 0;

	/*!< Send "Read Status Register" instruction */
	MR25H40_SendByte(MR25H40_CMD_RDSR);

	/*!< Loop as long as the memory is busy with a write cycle */
	do
	{
		/*!< Send a dummy byte to generate the clock needed by the NVRAM
     and put the value of the status register in NVRAM_Status variable */
		NVRAMstatus = MR25H40_SendByte(MR25H40_DUMMY_BYTE);

		if(time_out++ > 50000)
		{
			//error with NVRAM
			return SPI_NVRAM_Failure;
		}

	}
	while ((NVRAMstatus & MR25H40_WIP_FLAG) == SET); // Write in progress //

	/*!< Deselect the NVRAM: Chip Select high */
	MR25H40_CS_HIGH();


	/*****************************************************/
	//Version 12
	//Clear the status register
	/*****************************************************/
	MR25H40_Write_StatusByte(0);

	HAL_Delay(100);

	/*****************************************************/
	//check NVRAM integrity
	/*****************************************************/
	bool local_out = true;

	//Test buffers
	uint8_t TX_Buffer[100] = {0};
	uint8_t RX_Buffer[100] = {0};

	for(uint8_t i = 0; i <= 99; i++)
	{
		RX_Buffer[i] = 0;
	}

	//generate test data
	for(uint8_t i = 0; i <= 99; i++)
	{
		TX_Buffer[i] = i;
	}

	//write data to NVRAM scratch pad
	if (MR25H40_WriteBuffer(TX_Buffer, 0, 100) == false)
		return SPI_NVRAM_Failure;

	//read data back
	MR25H40_ReadBuffer(RX_Buffer, 0, 100);

	//compare, if not correct, show error
	for(uint8_t i = 0; i <= 99; i++)
	{
		if((TX_Buffer[i]) != (RX_Buffer[i]))
			local_out = false;
	}

	//check if data was the same
	if(local_out == false)
	{
		//There is an integrity issue
		return SPI_NVRAM_Integrity;
	}

	//all OK
	return SPI_OK;
}


/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
