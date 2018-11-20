/*S29GL01GS.c
 *Created on: Aug 24, 2012
 *Company: Mernok Elektronik
 *Author: S.D. Janse van Rensburg
 */

#include "string.h"

#include "S29GL01GS.h"
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

//Local Variables

//Global Variables
uint8_t DMAcomplete = 1 ;
/* Includes ------------------------------------------------------------------*/

/**
 * @brief  FSMC Bank 4 NOR/SRAM4 -> CS Signal on /NE4
 */
/* Delay definition */
#define BlockErase_Timeout    ((uint32_t)0x00A00000)
#define ChipErase_Timeout     ((uint32_t)0x30000000)
#define Program_Timeout       ((uint32_t)0x00001400)


NOR_HandleTypeDef S29GL01GS;
FMC_NORSRAM_TimingTypeDef p;
FMC_NORSRAM_TimingTypeDef ex_p;
/****************************************************************/
/**
 * @brief  Configures the FSMC and GPIOs to interface with the NOR memory.
 *         This function must be called before any write/read operation
 *         on the NOR.
 * @param  None
 * @retval None
 */
/****************************************************************/
void S29GL01GS_Init(uint8_t *error, char *return_message)
{
	HAL_NOR_StatusTypeDef Status;

	HAL_NOR_DeInit(&S29GL01GS);

	/* Flash Device Configuration */
	GPIO_InitTypeDef   				GPIO_InitStructure;
	S29GL01GS.Instance = FMC_NORSRAM_DEVICE;

	S29GL01GS.Init.AsynchronousWait 	= FMC_ASYNCHRONOUS_WAIT_DISABLE;
	S29GL01GS.Init.BurstAccessMode 		= FMC_BURST_ACCESS_MODE_DISABLE;
	//	S29GL01GS.Init.ContinuousClock		= FMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
	S29GL01GS.Init.DataAddressMux		= FMC_DATA_ADDRESS_MUX_DISABLE;
	S29GL01GS.Init.ExtendedMode			= FMC_EXTENDED_MODE_DISABLE;
	S29GL01GS.Init.MemoryDataWidth		= FMC_NORSRAM_MEM_BUS_WIDTH_16;
	S29GL01GS.Init.MemoryType           = FMC_MEMORY_TYPE_NOR;
	S29GL01GS.Init.NSBank               = FMC_NORSRAM_BANK1;
	S29GL01GS.Init.WaitSignal           = FMC_WAIT_SIGNAL_DISABLE;
	S29GL01GS.Init.WaitSignalActive     = FMC_WAIT_TIMING_BEFORE_WS;
	S29GL01GS.Init.WaitSignalPolarity   = FMC_WAIT_SIGNAL_POLARITY_LOW;
	S29GL01GS.Init.WriteBurst           = FMC_WRITE_BURST_DISABLE;
	//	S29GL01GS.Init.WriteFifo			= FMC_WRITE_FIFO_DISABLE;
	//	S29GL01GS.Init.PageSize				= FMC_PAGE_SIZE_NONE;
	S29GL01GS.Init.WriteOperation		= FMC_WRITE_OPERATION_ENABLE;

	p.AddressSetupTime 			= 1;
	p.AddressHoldTime 			= 1;
	p.DataSetupTime 			= 20;
	p.BusTurnAroundDuration	 	= 1;
	p.CLKDivision 				= 2;
	p.DataLatency 				= 1;
	p.AccessMode 				= FMC_ACCESS_MODE_A;

	/* Enable the NORSRAM device */
	HAL_NOR_Init(&S29GL01GS, &p, &ex_p);


	//Configure Flash Reset pin
	GPIO_InitStructure.Pin = NORFLASH_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(NORFLASH_PORT, &GPIO_InitStructure);

	//Set Reset pin high
	HAL_GPIO_WritePin(NORFLASH_PORT,NORFLASH_PIN,GPIO_PIN_SET);

	HAL_Delay(100);

	//Reset the flash device
	S29GL01GS_HW_Reset();

	HAL_Delay(100);

	//Get status of the flash device
	Status = HAL_NOR_GetStatus(&S29GL01GS, Bank1_NOR1_ADDR, 100);

	//Read NOR ID and see if it is correct. If not correct, give message
	NOR_IDTypeDef NOR_ID;
	HAL_NOR_Read_ID(&S29GL01GS, &NOR_ID);

	//Manufacturer code
	if((Expected_Manufacturer_Code != NOR_ID.Manufacturer_Code) & (Expected_Device_Code2 != NOR_ID.Device_Code2))
	{
		//Device failure or completely wrong device
		*error = 1;
		//message
		char local_string[50] = ("Internal flash failure\r\n");
		strcpy((return_message), local_string);

	}
	else if (Expected_Manufacturer_Code != NOR_ID.Manufacturer_Code)
	{
		//wrong device manufacturer
		*error = 1;
		//message
		char local_string[50] = ("Incorrect manufacturer ID for internal flash\r\n");
		strcpy((return_message), local_string);
	}
	else if(Expected_Device_Code2 != NOR_ID.Device_Code2)
	{
		//wrong specific device
		*error = 1;
		//message
		char local_string[50] = ("Incorrect internal flash memory\r\n");
		strcpy((return_message), local_string);
	}
	else
	{
		*error = 0;
		char local_string[50] = ("Flash memory confirmed\r\n");
		strcpy((return_message), local_string);
	}

	S29GL01GS_ReturnToReadMode(&S29GL01GS);
}


/****************************************************************/
//hw Reset og flash device
/****************************************************************/
void S29GL01GS_HW_Reset(void)
{
	//reset pin low
	HAL_GPIO_WritePin(NORFLASH_PORT,NORFLASH_PIN,GPIO_PIN_RESET);

	//delay
	HAL_Delay(2);

	//reset pin high
	HAL_GPIO_WritePin(NORFLASH_PORT,NORFLASH_PIN,GPIO_PIN_SET);
}



/****************************************************************/
/**
 * @brief  Reads NOR memory's Manufacturer and Device Code.
 * @param  NOR_ID: pointer to a NOR_IDTypeDef structure which will hold the
 *         Manufacturer and Device Code.
 * @retval None
 */
/****************************************************************/
void S29GL01GS_ReadID(NOR_IDTypeDef* NOR_ID)
{
	NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
	NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
	NOR_WRITE(ADDR_SHIFT(0x0555), 0x0090);

	NOR_ID->Manufacturer_Code = *(__IO uint16_t *) ADDR_SHIFT(0x0000);
	NOR_ID->Device_Code1 = *(__IO uint16_t *) ADDR_SHIFT(0x0001);
	NOR_ID->Device_Code2 = *(__IO uint16_t *) ADDR_SHIFT(0x000E);
	NOR_ID->Device_Code3 = *(__IO uint16_t *) ADDR_SHIFT(0x000F);
}



/****************************************************************/
/**
 * @brief  Erases the specified Nor memory block.
 * @param  BlockAddr: address of the block to erase.
 * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
 *         or NOR_TIMEOUT
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_EraseBlock(NOR_HandleTypeDef *hnor, uint32_t BlockAddr)
{
	HAL_NOR_Erase_Block(hnor, BlockAddr, Bank1_NOR1_ADDR);

	return (S29GL01GS_GetStatus(hnor, BlockErase_Timeout));

	//	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x0555), 0x00AA);
	//	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x02AA), 0x0055);
	//
	//	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x0555), 0x0080);
	//	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x0555), 0x00AA);
	//	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x02AA), 0x0055);
	//
	//	NOR_WRITE((Bank1_NOR1_ADDR + BlockAddr), 0x30);
	//
	//	return (S29GL01GS_GetStatus(hnor, BlockErase_Timeout));
}




/****************************************************************/
/**
 * @brief  Erases the entire chip.
 * @param  None
 * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
 *         or NOR_TIMEOUT
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_EraseChip(NOR_HandleTypeDef *hnor)
{
	NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
	NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
	NOR_WRITE(ADDR_SHIFT(0x0555), 0x0080);
	NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
	NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
	NOR_WRITE(ADDR_SHIFT(0x0555), 0x0010);

	return (S29GL01GS_GetStatus(hnor, ChipErase_Timeout));
}



/****************************************************************/
/**
 * @brief  Writes a half-word to the NOR memory.
 * @param  WriteAddr: NOR memory internal address to write to.
 * @param  Data: Data to write.
 * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
 *         or NOR_TIMEOUT
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_WriteHalfWord(NOR_HandleTypeDef *hnor, uint32_t WriteAddr, uint16_t Data)
{
	NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA);
	NOR_WRITE(ADDR_SHIFT(0x002AA), 0x0055);
	NOR_WRITE(ADDR_SHIFT(0x00555), 0x00A0);
	NOR_WRITE((Bank1_NOR1_ADDR + WriteAddr), Data);


	return (S29GL01GS_GetStatus(hnor, Program_Timeout));
}




/****************************************************************/
/**
 * @brief  Writes a half-word buffer to the FSMC NOR memory.
 * @param  pBuffer: pointer to buffer.
 * @param  WriteAddr: NOR memory internal address from which the data will be
 *         written.
 * @param  NumHalfwordToWrite: number of Half words to write.
 * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
 *         or NOR_TIMEOUT
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_WriteBuffer(NOR_HandleTypeDef *hnor, uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{

	HAL_NOR_StatusTypeDef status = NOR_ONGOING;

	do
	{
		/*!< Transfer data to the memory */
		status = S29GL01GS_WriteHalfWord(hnor, WriteAddr, *pBuffer++);
		WriteAddr = WriteAddr + 2;
		NumHalfwordToWrite--;
	}
	while((status == NOR_SUCCESS) && (NumHalfwordToWrite != 0));

	return (status);

}

/****************************************************************/
/**
 * @brief  Writes a half-word buffer to the FSMC NOR memory.
 * @param  pBuffer: pointer to buffer.
 * @param  WriteAddr: NOR memory internal address from which the data will be
 *         written.
 * @param  NumHalfwordToWrite: number of Half words to write.
 * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
 *         or NOR_TIMEOUT
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_WriteBuffer_32bit(NOR_HandleTypeDef *hnor, uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
	NumHalfwordToWrite =NumHalfwordToWrite*2;
	HAL_NOR_StatusTypeDef status = NOR_ONGOING;

	do
	{
		/*!< Transfer data to the memory */
		status = S29GL01GS_WriteHalfWord(hnor, WriteAddr, *pBuffer++);
		WriteAddr = WriteAddr + 2;
		NumHalfwordToWrite--;
	}
	while((status == NOR_SUCCESS) && (NumHalfwordToWrite != 0));

	return (status);

}


/****************************************************************/
/**
 * @brief  Writes a half-word buffer to the FSMC NOR memory. This function
 *         must be used only with S29GL128P NOR memory.
 * @param  pBuffer: pointer to buffer.
 * @param  WriteAddr: NOR memory internal address from which the data will be
 *         written.
 * @param  NumHalfwordToWrite: number of Half words to write.
 *         The maximum allowed value is 32 Half words (64 bytes).
 * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
 *         or NOR_TIMEOUT
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_ProgramBuffer(NOR_HandleTypeDef *hnor, uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
	uint32_t lastloadedaddress = 0x00;
	uint32_t currentaddress = 0x00;
	uint32_t endaddress = 0x00;

	/*!< Initialize variables */
	currentaddress = WriteAddr;
	endaddress = WriteAddr + NumHalfwordToWrite - 1;
	lastloadedaddress = WriteAddr;

	/*!< Issue unlock command sequence */
	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x00555), 0x00AA);

	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x02AA), 0x0055);

	/*!< Write Write Buffer Load Command */
	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, WriteAddr), 0x0025);
	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, WriteAddr), (NumHalfwordToWrite - 1));

	/*!< Load Data into NOR Buffer */
	while(currentaddress <= endaddress)
	{
		/*!< Store last loaded address & data value (for polling) */
		lastloadedaddress = currentaddress;

		NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, currentaddress), *pBuffer++);
		currentaddress += 1;
	}

	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, lastloadedaddress), 0x29);

	return(S29GL01GS_GetStatus(hnor, Program_Timeout));
}



/****************************************************************/
/**
 * @brief  Reads a half-word from the NOR memory.
 * @param  ReadAddr: NOR memory internal address to read from.
 * @retval Half-word read from the NOR memory
 */
/****************************************************************/
uint16_t S29GL01GS_ReadHalfWord(uint32_t ReadAddr)
{
	NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA);
	NOR_WRITE(ADDR_SHIFT(0x002AA), 0x0055);
	NOR_WRITE((Bank1_NOR1_ADDR + ReadAddr), 0x00F0 );

	return (*(__IO uint16_t *)((Bank1_NOR1_ADDR + ReadAddr)));
}




/****************************************************************/
/**
 * @brief  Reads a block of data from the FSMC NOR memory.
 * @param  pBuffer: pointer to the buffer that receives the data read from the
 *         NOR memory.
 * @param  ReadAddr: NOR memory internal address to read from.
 * @param  NumHalfwordToRead : number of Half word to read.
 * @retval None
 */
/****************************************************************/
void S29GL01GS_ReadBuffer(NOR_HandleTypeDef *hnor, uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{

//	HAL_NOR_ReadBuffer(hnor, ReadAddr, pBuffer, NumHalfwordToRead);

//	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x0555), 0x00AA);
//	NOR_WRITE(NOR_ADDR_SHIFT(Bank1_NOR1_ADDR, NOR_MEMORY_8B, 0x02AA), 0x0055);
	NOR_WRITE((Bank1_NOR1_ADDR + ReadAddr), 0x00F0);

	for(; NumHalfwordToRead != 0x00; NumHalfwordToRead--) /*!< while there is data to read */
	{
		/*!< Read a Halfword from the NOR */
		*pBuffer++ = *(__IO uint16_t *)((Bank1_NOR1_ADDR + ReadAddr));
		ReadAddr = ReadAddr + 2;
	}
}



/****************************************************************/
/**
 * @brief  Returns the NOR memory to Read mode.
 * @param  None
 * @retval HAL_NOR_StatusTypeDef
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_ReturnToReadMode(NOR_HandleTypeDef *hnor)
{
	return HAL_NOR_ReturnToReadMode(hnor);
}



/****************************************************************/
/**
 * @brief  Returns the NOR memory to Read mode and resets the errors in the NOR
 *         memory Status Register.
 * @param  None
 * @retval NOR_SUCCESS
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_Reset(void)
{
	NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA);
	NOR_WRITE(ADDR_SHIFT(0x002AA), 0x0055);
	NOR_WRITE(Bank1_NOR1_ADDR, 0x00F0);

	return (NOR_SUCCESS);
}



/****************************************************************/
/**
 * @brief  Returns the NOR operation status.
 * @param  Timeout: NOR progamming Timeout
 * @retval NOR_Status: The returned value can be: NOR_SUCCESS, NOR_ERROR
 *         or NOR_TIMEOUT
 */
/****************************************************************/
HAL_NOR_StatusTypeDef S29GL01GS_GetStatus(NOR_HandleTypeDef *hnor, uint32_t Timeout)
{
	HAL_NOR_StatusTypeDef status = HAL_NOR_GetStatus(hnor, Bank1_NOR1_ADDR, Timeout);

	/*!< Return the operation status */
	return (status);
}


///
/****************************************************************/
//Flash test
/****************************************************************/
void S29GL01GS_Test(void)
{
	//#define BUFFER_SIZE        0x400
	//#define WRITE_READ_ADDR    NOR_BLOCK_1
	NOR_IDTypeDef NOR_ID;
	uint16_t TxBuffer[1024]= {0};

	uint16_t RxBuffer1[1024];
	//uint16_t RxBuffer1[50048];
	//uint16_t RxBuffer1[130560];
	S29GL01GS_ReadID(&NOR_ID);

	S29GL01GS_ReturnToReadMode(&S29GL01GS);

	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_0);
	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_1);
	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_2);
	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_3);
	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_4);
	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_5);

	int i;
	for(i = 0; i <= 1023; i++)
	{
		TxBuffer[i] = i;
	}

	S29GL01GS_WriteBuffer(&S29GL01GS, &TxBuffer[0], NOR_BLOCK_1, 1024);

	S29GL01GS_ReadBuffer(&S29GL01GS, &RxBuffer1[0], NOR_BLOCK_1, 1024);

}

void HAL_NOR_MspWait(NOR_HandleTypeDef *hnor, uint32_t Timeout)
{
	uint32_t timeout = Timeout;

	/*!< Poll on NOR memory Ready/Busy signal ----------------------------------*/
	while((HAL_GPIO_ReadPin(FSMC_NWAIT_PORT, FSMC_NWAIT_PIN) != GPIO_PIN_RESET) && (timeout > 0))
	{
		timeout--;
	}

	timeout = Timeout;

	while((HAL_GPIO_ReadPin(FSMC_NWAIT_PORT, FSMC_NWAIT_PIN) == GPIO_PIN_RESET) && (timeout > 0))
	{
		timeout--;
	}
}
