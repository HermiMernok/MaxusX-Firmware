/*=================================
Dev_ADPS9301.c
Created on: 	31 August, 2018
Company: 		Mernok Elektronik
Author: 		H. du Plessis
==================================*/

/* Includes ------------------------------------------------------------------*/
#include "ICs/MCP23S17.h"

SPI_HandleTypeDef hspi5;


/***********************************************/
/* Private typedef -----------------------------------------------------------*/
enum IO_Expander_number
{
	IO_EXPANDER1 = 1,
	IO_EXPANDER2,
	IO_EXPANDER3,
};
/* Private define ------------------------------------------------------------*/
#define	IO_EXPANDER1_ADRR			0x4E
#define	IO_EXPANDER2_ADRR			0x4C
#define	IO_EXPANDER3_ADRR			0x48

#define IO_EXPANDER_READ			0x01
#define IO_EXPANDER_WRITE			0x00

#define	IO_EXPANDERA_INIT_ADRR		0x00
#define	IO_EXPANDERB_INIT_ADRR		0x01

#define IO_EXPANDER_A 				0x12
#define IO_EXPANDER_B 				0x13

#define IO_EXPANDER_LATCH_A 		0x14
#define IO_EXPANDER_LATCH_B 		0x15

#define IO_EXPANDER1_PIN_DEF_A		0b11111100
#define IO_EXPANDER1_PIN_DEF_B		0b00000000

#define IO_EXPANDER2_PIN_DEF_A		0b11111111
#define IO_EXPANDER2_PIN_DEF_B		0b11111111

#define IO_EXPANDER3_PIN_DEF_A		0b00000000
#define IO_EXPANDER3_PIN_DEF_B		0b00111111


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t IO_Expander1A_byte;
uint8_t IO_Expander1B_byte;

uint8_t IO_Expander2A_byte;
uint8_t IO_Expander2B_byte;

uint8_t IO_Expander3A_byte;
uint8_t IO_Expander3B_byte;

uint8_t IO_Expander1A_Output_byte;
uint8_t IO_Expander1B_Output_byte;

uint8_t IO_Expander2A_Output_byte;
uint8_t IO_Expander2B_Output_byte;

uint8_t IO_Expander3A_Output_byte;
uint8_t IO_Expander3B_Output_byte;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


///****************************************************************/
///**
// * @brief  DeInitializes the peripherals used by the SPI NVRAM driver.
// * @param  None
// * @retval None
// */
///****************************************************************/
//void MR25H256_DeInit(void)
//{
//	MR25H256_LowLevel_DeInit();
//}

void MCP23S17_CS_LOW(uint8_t IC_Number)
{
	switch(IC_Number)
	{
	case 1:

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
		break;
	}


}

void MCP23S17_CS_HIGH(uint8_t IC_Number)
{
	switch(IC_Number)
	{
	case 1:

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
		break;

	case 2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		break;

	case 3:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
		break;
	}

}

/****************************************************************/
/**
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param  byte: byte to send.
 * @retval The value of the received byte.
 */
/****************************************************************/
uint8_t MCP23S17_SendByte(uint8_t byte)
{
	uint8_t rx_byte = 0;

	//Transmit data and receive result in rx_data buffer (single byte)
	//HAL_SPI_TransmitReceive(&hspi5, &byte, &rx_byte, 1, 50);
	HAL_SPI_Transmit(&hspi5, &byte, 1, 50);
	return rx_byte;
}

/****************************************************************/
/**
 * @brief  Initialize the CS PINs, this function can be used if the spi bus was enabled already.
 * @param  None
 * @retval None
 */
/****************************************************************/
void MCP23S17_CS_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	/*!< Enable GPIO clocks */
//	RCC_AHB1PeriphClockCmd(MR25H40_CS_GPIO_CLK, ENABLE);//MR25H40_CS_GPIO_CLK

	/*!< Configure MR25H40 Card CS pin in output pushpull mode ********************/
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_7 ;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	MCP23S17_CS_HIGH(IO_EXPANDER1);
	MCP23S17_CS_HIGH(IO_EXPANDER2);
	MCP23S17_CS_HIGH(IO_EXPANDER3);

	//IO Expander 1 Init
	HAL_Delay(10);
	MCP23S17_CS_LOW(IO_EXPANDER1);
	MCP23S17_SendByte(IO_EXPANDER1_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDERB_INIT_ADRR);
	MCP23S17_SendByte(IO_EXPANDER1_PIN_DEF_B);
	MCP23S17_CS_HIGH(IO_EXPANDER1);
	HAL_Delay(10);
	MCP23S17_CS_LOW(IO_EXPANDER1);
	MCP23S17_SendByte(IO_EXPANDER1_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDERA_INIT_ADRR);
	MCP23S17_SendByte(IO_EXPANDER1_PIN_DEF_A);
	MCP23S17_CS_HIGH(IO_EXPANDER1);

	//IO Expander 2 Init
	HAL_Delay(10);
	MCP23S17_CS_LOW(IO_EXPANDER2);
	MCP23S17_SendByte(IO_EXPANDER2_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDERB_INIT_ADRR);
	MCP23S17_SendByte(IO_EXPANDER2_PIN_DEF_B);
	MCP23S17_CS_HIGH(IO_EXPANDER2);
	HAL_Delay(10);
	MCP23S17_CS_LOW(IO_EXPANDER2);
	MCP23S17_SendByte(IO_EXPANDER2_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDERA_INIT_ADRR);
	MCP23S17_SendByte(IO_EXPANDER2_PIN_DEF_A);
	MCP23S17_CS_HIGH(IO_EXPANDER2);

	//IO Expander 3 Init
	HAL_Delay(10);
	MCP23S17_CS_LOW(IO_EXPANDER3);
	MCP23S17_SendByte(IO_EXPANDER3_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDERB_INIT_ADRR);
	MCP23S17_SendByte(IO_EXPANDER3_PIN_DEF_B);
	MCP23S17_CS_HIGH(IO_EXPANDER3);
	HAL_Delay(10);
	MCP23S17_CS_LOW(IO_EXPANDER3);
	MCP23S17_SendByte(IO_EXPANDER3_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDERA_INIT_ADRR);
	MCP23S17_SendByte(IO_EXPANDER3_PIN_DEF_A);
	MCP23S17_CS_HIGH(IO_EXPANDER3);

}

uint32_t MCP23S17_ReadID(uint8_t IC_Number)
{
	//uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
	uint32_t  Temp0 = 0;
	/*!< Select the NVRAM: Chip Select low */
	MCP23S17_CS_LOW(IC_Number);

	/*!< Send "RDID " instruction */
	//MCP23S17_SendByte(IOEXPANDER_READ_ID);

	/*!< Read a byte from the NVRAM */
	//Temp1 = MR25H40_SendByte(MR25H40_DUMMY_BYTE);

	//	/*!< Read a byte from the NVRAM */
	//	Temp2 = MR25H40_SendByte(MR25H40_DUMMY_BYTE);

	/*!< Deselect the NVRAM: Chip Select high */
	MCP23S17_CS_HIGH(IC_Number);

	//Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

	return Temp0;
}

uint8_t MCP23S17_ReadByte(uint8_t byte)
{
	uint8_t rx_byte = 0;

	//Transmit data and receive result in rx_data buffer (single byte)
	HAL_SPI_TransmitReceive(&hspi5, &byte, &rx_byte, 1, 50);

	return rx_byte;
}

void Get_ExpanderIO_Input_Bytes(void)
{
	MCP23S17_CS_LOW(IO_EXPANDER1);
	MCP23S17_SendByte(IO_EXPANDER1_ADRR|IO_EXPANDER_READ);
	MCP23S17_SendByte(IO_EXPANDER_A);
	IO_Expander1A_byte = MCP23S17_ReadByte(0b11111111);
	MCP23S17_CS_HIGH(IO_EXPANDER1);

	MCP23S17_CS_LOW(IO_EXPANDER2);
	MCP23S17_SendByte(IO_EXPANDER2_ADRR|IO_EXPANDER_READ);
	MCP23S17_SendByte(IO_EXPANDER_A);
	IO_Expander2A_byte = MCP23S17_ReadByte(0b11111111);
	MCP23S17_CS_HIGH(IO_EXPANDER2);

	MCP23S17_CS_LOW(IO_EXPANDER2);
	MCP23S17_SendByte(IO_EXPANDER2_ADRR|IO_EXPANDER_READ);
	MCP23S17_SendByte(IO_EXPANDER_B);
	IO_Expander2B_byte = MCP23S17_ReadByte(0b11111111);
	MCP23S17_CS_HIGH(IO_EXPANDER2);

	MCP23S17_CS_LOW(IO_EXPANDER3);
	MCP23S17_SendByte(IO_EXPANDER3_ADRR|IO_EXPANDER_READ);
	MCP23S17_SendByte(IO_EXPANDER_B);
	IO_Expander3B_byte = MCP23S17_ReadByte(0b11111111);
	MCP23S17_CS_HIGH(IO_EXPANDER3);

	Set_ExpanderIO_In_Flags();
}

void Set_ExpanderIO_In_Flags(void)
{
	IO_Expander_Input_Flags_Array[5]  = IO_Expander_In_Flags.PSU_Protect 			 =  check_bit(IO_Expander1A_byte, 2);
	IO_Expander_Input_Flags_Array[4]  = IO_Expander_In_Flags.Charge_Active 			 =  check_bit(IO_Expander1A_byte, 3);
	IO_Expander_Input_Flags_Array[3]  = IO_Expander_In_Flags.Module_detect4 		 =  check_bit(IO_Expander1A_byte, 4);
	IO_Expander_Input_Flags_Array[2]  = IO_Expander_In_Flags.Module_detect3 		 =  check_bit(IO_Expander1A_byte, 5);
	IO_Expander_Input_Flags_Array[1]  = IO_Expander_In_Flags.Module_detect2 		 =  check_bit(IO_Expander1A_byte, 6);
	IO_Expander_Input_Flags_Array[0]  = IO_Expander_In_Flags.Module_detect1 		 =  check_bit(IO_Expander1A_byte, 7);
	IO_Expander_Input_Flags_Array[6]  = IO_Expander_In_Flags.fbk_CAN_PWR			 =  check_bit(IO_Expander2A_byte, 7);	//: IO_Epander2 A
	IO_Expander_Input_Flags_Array[7]  = IO_Expander_In_Flags.fbk_V_EXT_Uart			 =  check_bit(IO_Expander2A_byte, 6);
	IO_Expander_Input_Flags_Array[8]  = IO_Expander_In_Flags.fbk_V_Proxy			 =  check_bit(IO_Expander2A_byte, 5);
	IO_Expander_Input_Flags_Array[9]  = IO_Expander_In_Flags.fbk_V_Ethernet			 =  check_bit(IO_Expander2A_byte, 4);
	IO_Expander_Input_Flags_Array[10] = IO_Expander_In_Flags.fbk_V_Control			 =  check_bit(IO_Expander2A_byte, 3);
	IO_Expander_Input_Flags_Array[11] = IO_Expander_In_Flags.fbk_Siren1				 =  check_bit(IO_Expander2A_byte, 2);
	IO_Expander_Input_Flags_Array[12] = IO_Expander_In_Flags.fbk_Siren2				 =  check_bit(IO_Expander2A_byte, 1);
	IO_Expander_Input_Flags_Array[13] = IO_Expander_In_Flags.Charge_fault			 =  check_bit(IO_Expander2A_byte, 0);
	IO_Expander_Input_Flags_Array[14] = IO_Expander_In_Flags.fbk_F_Light_White     	 =  check_bit(IO_Expander2B_byte, 0); //: IO_Epander2 B
	IO_Expander_Input_Flags_Array[15] = IO_Expander_In_Flags.fbk_F_Light_Red     	 =  check_bit(IO_Expander2B_byte, 1);
	IO_Expander_Input_Flags_Array[16] = IO_Expander_In_Flags.fbk_F_Light_Flash_Red   =  check_bit(IO_Expander2B_byte, 2);
	IO_Expander_Input_Flags_Array[17] = IO_Expander_In_Flags.fbk_F_Light_Dev     	 =  check_bit(IO_Expander2B_byte, 3);
	IO_Expander_Input_Flags_Array[18] = IO_Expander_In_Flags.fbk_R_Light_White     	 =  check_bit(IO_Expander2B_byte, 4);
	IO_Expander_Input_Flags_Array[19] = IO_Expander_In_Flags.fbk_R_Light_Red     	 =  check_bit(IO_Expander2B_byte, 5);
	IO_Expander_Input_Flags_Array[20] = IO_Expander_In_Flags.fbk_R_Light_Flash_Red   =  check_bit(IO_Expander2B_byte, 6);
	IO_Expander_Input_Flags_Array[21] = IO_Expander_In_Flags.fbk_R_Light_Dev     	 =  check_bit(IO_Expander2B_byte, 7);
	IO_Expander_Input_Flags_Array[22] = IO_Expander_In_Flags.LCD_PWR_Fault			 =  check_bit(IO_Expander3B_byte, 0);	//: IO_Epander3 B
	IO_Expander_Input_Flags_Array[23] = IO_Expander_In_Flags.Variant0				 =  check_bit(IO_Expander3B_byte, 1);
	IO_Expander_Input_Flags_Array[24] = IO_Expander_In_Flags.Variant1				 =  check_bit(IO_Expander3B_byte, 2);
	IO_Expander_Input_Flags_Array[25] = IO_Expander_In_Flags.Revision0				 =  check_bit(IO_Expander3B_byte, 3);
	IO_Expander_Input_Flags_Array[26] = IO_Expander_In_Flags.Revision1				 =  check_bit(IO_Expander3B_byte, 4);
	IO_Expander_Input_Flags_Array[27] = IO_Expander_In_Flags.Revision2				 =  check_bit(IO_Expander3B_byte, 5);

}

void Set_ExpanderIO_Output_Bytes(void)
{
	IO_Expander1A_Output_byte = 0;
	IO_Expander1B_Output_byte = 0;

	IO_Expander2A_Output_byte = 0;
	IO_Expander2B_Output_byte = 0;

	IO_Expander3A_Output_byte = 0;
	IO_Expander3B_Output_byte = 0;

	IO_Expander_Output_Flags.Led_Status_G	 = 	IO_Expander_Output_Flags_Array[1];
	IO_Expander_Output_Flags.Led_Status_B	 = 	IO_Expander_Output_Flags_Array[0];
	IO_Expander_Output_Flags.Module_reset1   = 	IO_Expander_Output_Flags_Array[2];
	IO_Expander_Output_Flags.Module_reset2   = 	IO_Expander_Output_Flags_Array[3];
	IO_Expander_Output_Flags.Module_reset3   = 	IO_Expander_Output_Flags_Array[4];
	IO_Expander_Output_Flags.Module_reset4   = 	IO_Expander_Output_Flags_Array[5];
	IO_Expander_Output_Flags.Led_Key_R	     = 	IO_Expander_Output_Flags_Array[6];
	IO_Expander_Output_Flags.Led_Key_G	     = 	IO_Expander_Output_Flags_Array[7];
	IO_Expander_Output_Flags.Led_Key_B	     = 	IO_Expander_Output_Flags_Array[8];
	IO_Expander_Output_Flags.Led_Status_R	 = 	IO_Expander_Output_Flags_Array[9];
	IO_Expander_Output_Flags.CAN1_Term	     = 	IO_Expander_Output_Flags_Array[10];
	IO_Expander_Output_Flags.CAN2_Term	     = 	IO_Expander_Output_Flags_Array[11];
	IO_Expander_Output_Flags.CAN3_Term	     = 	IO_Expander_Output_Flags_Array[12];
	IO_Expander_Output_Flags.LCD_Power	     = 	IO_Expander_Output_Flags_Array[13];

	if(IO_Expander_Output_Flags.Led_Status_B)
		IO_Expander1A_Output_byte |= 0x01;
	if(IO_Expander_Output_Flags.Led_Status_G)
		IO_Expander1A_Output_byte |= 0x02;


	if(IO_Expander_Output_Flags.Module_reset1)
		IO_Expander1B_Output_byte |= 0x01;
	if(IO_Expander_Output_Flags.Module_reset2)
		IO_Expander1B_Output_byte |= 0x02;
	if(IO_Expander_Output_Flags.Module_reset3)
		IO_Expander1B_Output_byte |= 0x04;
	if(IO_Expander_Output_Flags.Module_reset4)
		IO_Expander1B_Output_byte |= 0x08;
	if(IO_Expander_Output_Flags.Led_Key_R)
		IO_Expander1B_Output_byte |= 0x10;
	if(IO_Expander_Output_Flags.Led_Key_G)
		IO_Expander1B_Output_byte |= 0x20;
	if(IO_Expander_Output_Flags.Led_Key_B)
		IO_Expander1B_Output_byte |= 0x40;
	if(IO_Expander_Output_Flags.Led_Status_R)
		IO_Expander1B_Output_byte |= 0x80;

	if(IO_Expander_Output_Flags.CAN1_Term)
		IO_Expander3A_Output_byte |= 0x80;
	if(IO_Expander_Output_Flags.CAN2_Term)
		IO_Expander3A_Output_byte |= 0x40;
	if(IO_Expander_Output_Flags.CAN3_Term)
		IO_Expander3A_Output_byte |= 0x20;
	if(IO_Expander_Output_Flags.LCD_Power)
		IO_Expander3A_Output_byte |= 0x10;

	Latch_IOExpander_Outputs();
}

void Latch_IOExpander_Outputs(void)
{

	MCP23S17_CS_LOW(IO_EXPANDER1);
	MCP23S17_SendByte(IO_EXPANDER1_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDER_LATCH_A);
	MCP23S17_SendByte(IO_Expander1A_Output_byte);
	MCP23S17_CS_HIGH(IO_EXPANDER1);

	MCP23S17_CS_LOW(IO_EXPANDER1);
	MCP23S17_SendByte(IO_EXPANDER1_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDER_LATCH_B);
	MCP23S17_SendByte(IO_Expander1B_Output_byte);
	MCP23S17_CS_HIGH(IO_EXPANDER1);

	MCP23S17_CS_LOW(IO_EXPANDER2);
	MCP23S17_SendByte(IO_EXPANDER2_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDER_LATCH_A);
	MCP23S17_SendByte(IO_Expander2A_Output_byte);
	MCP23S17_CS_HIGH(IO_EXPANDER2);

	MCP23S17_CS_LOW(IO_EXPANDER2);
	MCP23S17_SendByte(IO_EXPANDER2_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDER_LATCH_B);
	MCP23S17_SendByte(IO_Expander2B_Output_byte);
	MCP23S17_CS_HIGH(IO_EXPANDER2);

	MCP23S17_CS_LOW(IO_EXPANDER3);
	MCP23S17_SendByte(IO_EXPANDER3_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDER_LATCH_A);
	MCP23S17_SendByte(IO_Expander3A_Output_byte);
	MCP23S17_CS_HIGH(IO_EXPANDER3);

	MCP23S17_CS_LOW(IO_EXPANDER3);
	MCP23S17_SendByte(IO_EXPANDER3_ADRR|IO_EXPANDER_WRITE);
	MCP23S17_SendByte(IO_EXPANDER_LATCH_B);
	MCP23S17_SendByte(IO_Expander3B_Output_byte);
	MCP23S17_CS_HIGH(IO_EXPANDER3);
}

void LED_TEST(uint8_t toggle)
{
	MCP23S17_CS_LOW(1);
	MCP23S17_SendByte(0x4E);
	MCP23S17_SendByte(0x15);
	if(toggle == 1)
	{
		MCP23S17_SendByte(0xFF);
	}
	else
	{
		MCP23S17_SendByte(0b00000000);
	}
	MCP23S17_CS_HIGH(1);


	MCP23S17_CS_LOW(3);
	MCP23S17_SendByte(0x48);
	MCP23S17_SendByte(0x14);
	MCP23S17_SendByte(0xFF);
	MCP23S17_CS_HIGH(3);
	//	HAL_Delay(1);
	//	MCP23S17_CS_LOW(1);
	//	MCP23S17_SendByte(0x4F);
	//	Temp = MCP23S17_ReadByte(0x15);
	//    MCP23S17_CS_HIGH(1);
}
