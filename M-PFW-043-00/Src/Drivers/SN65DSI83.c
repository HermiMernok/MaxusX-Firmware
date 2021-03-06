/*=================================
Dev_ADPS9301.c
Created on: 	31 August, 2018
Company: 		Mernok Elektronik
Author: 		H. du Plessis
==================================*/
#include "SN65DSI83.h"
#include "F769_LCD.h"
#include "stdbool.h"

/*--------------------------------
 *Local Variables
 *------------------------------*/


/*--------------------------------
 *Global Variables
 *------------------------------*/


uint8_t SN65DSI83_ReadRegs(I2C_HandleTypeDef *hi2c, uint8_t deviceAddr, uint8_t Reg, uint8_t* Data, uint8_t len)
{

	if(!I2C_BufferRead(hi2c, &Data, deviceAddr, len));
	{
		return true;
	}

}

uint8_t SN65DSI83_WriteReg(I2C_HandleTypeDef *hi2c, uint8_t deviceAddr, uint8_t WriteAddr, uint8_t Data)
{
	// Write using I2C bus. This is implemented in external source.
	Delay(1);
	return I2C_ByteWrite(hi2c,&Data, deviceAddr,  WriteAddr);
}


void SN65DSI83_Send_Settings()
{
	uint8_t VSA_Low = VSA; //VerticalSyncActive
	uint8_t VSA_High = VSA<<8;
	uint8_t	HSA_Low = (HSA * laneByteClk_kHz)/LcdClock; //HorizontalSyncActive
	uint8_t	HSA_High = (HSA * laneByteClk_kHz)/LcdClock<<8;
	uint8_t	HBP_Low = (HBP * laneByteClk_kHz)/LcdClock;
	uint8_t	HBP_High = (HBP * laneByteClk_kHz)/LcdClock<<8;

	uint8_t HorizontalLine_Low            = 0; /* Value depending on display orientation choice portrait/landscape */
	uint8_t HorizontalLine_High            =4; /* Value depending on display orientation choice portrait/landscape */



			// === Reset and Clock Registers ===
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x09, 0);			// SOFT_RESET
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x0A, 0x3);		// 3 PLL_EN_STAT & LVDS_CLK_RANGE & HS_CLK_SRC
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x0B, 0x20);		// 20 DSI_CLK_DIVIDER & REFCLK_MULTIPLIER
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x0D, 0);			// PLL_EN

	// === DSI Registers ===
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x10, 0x30);		// 36 CHA_DSI_LANES & SOT_ERR_TOL_DIS
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x11, 0x10);			// CHA_DSI_DATA_EQ & CHA_DSI_CLK_EQ
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x12, 0x31);		// CHA_DSI_CLK_RANGE

	//=== LVDS Registers ===
	//SN65DSI83_WriteReg(&hi2c2, 0x58, 0x18, 0x7A);		//RGB888  DE_POS_POLARITY & HS_NEG_POLARITY & VS_NEG_POLARITY & CHA_24BPP_MODE & CHA_24BPP_FORMAT1
	//SN65DSI83_WriteReg(&hi2c2, 0x58, 0x18, 0x70);		//RGB666  DE_POS_POLARITY & HS_NEG_POLARITY & VS_NEG_POLARITY & CHA_24BPP_MODE & CHA_24BPP_FORMAT1
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x18, 0x78);		// DE_NEG_POLARITY & HS_NEG_POLARITY & VS_NEG_POLARITY & CHA_24BPP_MODE & CHA_24BPP_FORMAT1

	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x19, 0x3);		// CHA_LVDS_VOCM & CHA_LVDS_VOD_SWING
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x1A, 0x1);		// CHA_REVERSE_LVDS & CHA_LVDS_TERM
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x1B, 0x10);		// CHA_LVDS_CM_ADJUST

	//=== � Video Registers ===
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x20, HorizontalLine_Low);			// CHA_ACTIVE_LINE_LENGTH_LOW -- Screen width
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x21, HorizontalLine_High);		// CHA_ACTIVE_LINE_LENGTH_HIGH
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x22, 0);			//
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x24, 0x58);		// CHA_VERTICAL_DISPLAY_SIZE_LOW 	// Test Pattern Generation Purpose Only
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x25, 0x2);		// CHA_VERTICAL_DISPLAY_SIZE_HIGH 	// Test Pattern Generation Purpose Only
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x28, 0x50);		// CHA_SYNC_DELAY_LOW
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x29, 0);			// CHA_SYNC_DELAY_HIGH
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x2C, 0x64);		// 0x64 CHA_HSYNC_PULSE_WIDTH_LOW
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x2D, 0);			// CHA_HSYNC_PULSE_WIDTH_HIGH
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x30, 0x64);		// CHA_VSYNC_PULSE_WIDTH_LOW
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x31, 0);			// CHA_VSYNC_PULSE_WIDTH_HIGH
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x34, HBP_Low);		// CHA_HORIZONTAL_BACK_PORCH
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x36, 0x0E);		// CHA_VERTICAL_BACK_PORCH			// Test Pattern Generation Purpose Only
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x38, 0x87);		// CHA_HORIZONTAL_FRONT_PORCH		// Test Pattern Generation Purpose Only
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x3A, 0x0E);		// CHA_VERTICAL_FRONT_PORCH			// Test Pattern Generation Purpose Only
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x3C, 0x0);			// CHA_TEST_PATTERN				// Test Pattern Generation Purpose Only
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x3E, 0);
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0xD, 0x1);
	SN65DSI83_WriteReg(&hi2c2, 0x58, 0x09, 0);
}


