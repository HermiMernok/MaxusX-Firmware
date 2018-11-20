/*
 * App_Init.c
 *
 *  Created on: 01 Sep 2018
 *      Author: NeilPretorius
 */

#include "App_Init.h"

#include "main.h"
#include "APDS9309.h"

void Application_Init(void)
{

	/*--------------------------------
	 *Delay startup
	 *------------------------------*/
	HAL_Delay(100);

	/****************************************************************/
	//Configure peripherals
	/***************************************************************/

	//IO_App_Init();

	SPI_Test();

	Init_M41T94rtc();

	DMA_Init();

	// TODO  App_VisionModules_Init();

	//TODO  App_EventManager_Init();

	if(NV_RAM_SPI_Test() == SPI_OK)
	{
		IC_Flags.RTC_OK = true;
	}
	else
	{
		IC_Flags.RTC_OK = false;
	}

	if(ADPS9309_Init() == APDS9309_OK)
	{
		IC_Flags.Light_Sensor_OK = true;
	}
	else
	{
		IC_Flags.Light_Sensor_OK = false;
	}

	/*===============================
	 * Initialise ACK flag
	 *==============================*/
	App_ACK_Init ();

	//=== Initialise LCD ===
	LCD_Init();
	uint8_t NOR_STATUS = 0;
	char NOR_Msg[50] = {0};
	/****************************************************************/
	//Configure External NORFLASH Device
	/***************************************************************/
	S29GL01GS_Init(&NOR_STATUS, &NOR_Msg[0]);

	if(NOR_STATUS == 0)
	{
		IC_Flags.NOR_FLASH_OK = true;
	}
	else
	{
		IC_Flags.NOR_FLASH_OK = false;
	}
//	S29GL01GS_Test();

	//=== SN65DSI83_Send_Settings();
	SN65DSI83_Send_Settings();



	TIM3_Start();

	// === Turn on Display ===
	BSP_LCD_DisplayOn();

	// === Clear Screen Black ===
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	//	IO_Output_control(LCD_Power, On);
	//	IO_Output_control(LCD_BL, On);
}
