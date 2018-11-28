/*=================================
F769_LCD.c
Created on: 	31 August, 2018
Company: 		Mernok Elektronik
Author: 		H. du Plessis
==================================*/

/* <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

//======================================
//============ Includes ================
//======================================

#include <F769_LCD.h>



static DSI_VidCfgTypeDef hdsivideo_handle;

DMA2D_HandleTypeDef hdma2d_discovery;
LTDC_HandleTypeDef  hltdc_discovery;

//======================================
//============ Functions ================
//======================================

LCD_StateTypeDef DSI_Init(LCD_OrientationTypeDef orientation)
{
	MX_DSIHOST_DSI_Init();

	uint32_t                   VACT; /*!< Vertical Active time in units of lines = imageSize Y in pixels to display */
	uint32_t                   HACT; /*!< Horizontal Active time in units of lcdClk = imageSize X in pixels to display */


	/* Toggle Hardware Reset of the DSI LCD using
	 * its XRES signal (active low) */

	/* Timing parameters for all Video modes
	 * Set Timing parameters of LTDC depending on its chosen orientation
	 */
	if(orientation == LCD_ORIENTATION_PORTRAIT)
	{
		BSP_LCD_X_Size = 600;  /* 480 */
		BSP_LCD_Y_Size = 1024; /* 800 */
	}
	else
	{
		/* lcd_orientation == LCD_ORIENTATION_LANDSCAPE */
		BSP_LCD_X_Size = 1024;  /* 800 */
		BSP_LCD_Y_Size = 600; /* 480 */
	}
	HACT = BSP_LCD_X_Size;
	VACT = BSP_LCD_Y_Size;

	hdsivideo_handle.VirtualChannelID = 0;
	hdsivideo_handle.ColorCoding = DSI_RGB888; //((uint32_t)0x00000005U)
	hdsivideo_handle.VSPolarity = DSI_VSYNC_ACTIVE_LOW;
	hdsivideo_handle.HSPolarity = DSI_HSYNC_ACTIVE_LOW;
	hdsivideo_handle.DEPolarity = DSI_DATA_ENABLE_ACTIVE_LOW; //TODO may cause problems
	hdsivideo_handle.Mode = DSI_VID_MODE_NB_EVENTS; /* Mode Video burst ie : one LgP per line */

	//hdsivideo_handle.NullPacketSize = 0xFFF;
	hdsivideo_handle.NullPacketSize = 0xFFF;
	hdsivideo_handle.NumberOfChunks = 0;
	hdsivideo_handle.PacketSize                = HACT; /* Value depending on display orientation choice portrait/landscape */
	hdsivideo_handle.HorizontalSyncActive      = (HSA * laneByteClk_kHz)/LcdClock;
	hdsivideo_handle.HorizontalBackPorch       = (HBP * laneByteClk_kHz)/LcdClock;
	hdsivideo_handle.HorizontalLine            = ((HACT + HSA + HBP + HFP) * laneByteClk_kHz)/LcdClock; /* Value depending on display orientation choice portrait/landscape */
	hdsivideo_handle.VerticalSyncActive        = VSA;
	hdsivideo_handle.VerticalBackPorch         = VBP;
	hdsivideo_handle.VerticalFrontPorch        = VFP;
//	hdsivideo_handle.HorizontalSyncActive      = 50;
	//hdsivideo_handle.HorizontalBackPorch       = (HBP * laneByteClk_kHz)/LcdClock;

	hdsivideo_handle.VerticalActive            = VACT; /* Value depending on display orientation choice portrait/landscape */
	/* Enable or disable sending LP command while streaming is active in video mode */
	hdsivideo_handle.LPCommandEnable = DSI_LP_COMMAND_ENABLE; /* Enable sending commands in mode LP (Low Power) */

	/* Largest packet size possible to transmit in LP mode in VSA, VBP, VFP regions */
	/* Only useful when sending LP packets is allowed while streaming is active in video mode */
	hdsivideo_handle.LPLargestPacketSize = 16;

	/* Largest packet size possible to transmit in LP mode in HFP region during VACT period */
	/* Only useful when sending LP packets is allowed while streaming is active in video mode */
	hdsivideo_handle.LPVACTLargestPacketSize = 0;

	/* Specify for each region of the video frame, if the transmission of command in LP mode is allowed in this region */
	/* while streaming is active in video mode                                                                         */
	hdsivideo_handle.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE;   /* Allow sending LP commands during HFP period */
	hdsivideo_handle.LPHorizontalBackPorchEnable  = DSI_LP_HBP_ENABLE;   /* Allow sending LP commands during HBP period */
	hdsivideo_handle.LPVerticalActiveEnable = DSI_LP_VACT_ENABLE;  /* Allow sending LP commands during VACT period */
	hdsivideo_handle.LPVerticalFrontPorchEnable = DSI_LP_VFP_ENABLE;   /* Allow sending LP commands during VFP period */
	hdsivideo_handle.LPVerticalBackPorchEnable = DSI_LP_VBP_ENABLE;   /* Allow sending LP commands during VBP period */
	hdsivideo_handle.LPVerticalSyncActiveEnable = DSI_LP_VSYNC_ENABLE; /* Allow sending LP commands during VSync = VSA period */

	/* Configure DSI Video mode timings with settings set above */
	HAL_DSI_ConfigVideoMode(&(hdsi), &(hdsivideo_handle));

	return LCD_OK;
}

LCD_StateTypeDef LTDC_Init()
{
	static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
	/* Timing Configuration */
	hltdc_discovery.Init.HorizontalSync = (HSA - 1);
	hltdc_discovery.Init.AccumulatedHBP = (HSA + HBP - 1);
	hltdc_discovery.Init.AccumulatedActiveW = (BSP_LCD_X_Size + HSA + HBP - 1);
	hltdc_discovery.Init.TotalWidth = (BSP_LCD_X_Size + HSA + HBP + HFP - 1);

	/* Initialize the LCD pixel width and pixel height */
	hltdc_discovery.LayerCfg->ImageWidth  = BSP_LCD_X_Size;
	hltdc_discovery.LayerCfg->ImageHeight = BSP_LCD_Y_Size;

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 400;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 7; //7
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

	/* Background value */
	hltdc_discovery.Init.Backcolor.Blue = 0;
	hltdc_discovery.Init.Backcolor.Green = 0;
	hltdc_discovery.Init.Backcolor.Red = 0;
	hltdc_discovery.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	hltdc_discovery.Instance = LTDC;

	/* Get LTDC Configuration from DSI Configuration */
	HAL_LTDC_StructInitFromVideoConfig(&(hltdc_discovery), &(hdsivideo_handle));

	/* Initialize the LTDC */
	HAL_LTDC_Init(&hltdc_discovery);
}

/**
 * @brief  BSP LCD Reset
 *         Hw reset the LCD DSI activating its XRES signal (active low for some time)
 *         and desactivating it later.
 */
void LCD_Reset(void)
{
	/* Activate XRES active low */
	IO_Output_control(DSI_Reset, On);

	HAL_Delay(20); /* wait 20 ms */

	/* Desactivate XRES */
	IO_Output_control(DSI_Reset, Off);

	/* Wait for 10ms after releasing XRES before sending commands */
	HAL_Delay(10);
}

LCD_StateTypeDef LCD_Init()
{
	LCD_Reset();
	BSP_LCD_MspInit();
	DSI_Init(LCD_ORIENTATION_LANDSCAPE);
	LTDC_Init();
	HAL_DSI_Start(&hdsi);
	SRAM_Init();

	/* Initialize the font */
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	BSP_LCD_LayerDefaultInit(0, LCD_FRAMEBUFFER1_ADDR);

	BSP_LCD_SetLayerVisible (0, ENABLE);
	BSP_LCD_SetLayerVisible(1, DISABLE);

	/* Select the LCD Background Layer  */
	BSP_LCD_SelectLayer(0);
	return LCD_OK;
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
