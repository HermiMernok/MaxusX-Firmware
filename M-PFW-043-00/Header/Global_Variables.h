/*
 * Global_Variables.h
 *
 *  Created on: 01 Sep 2018
 *  Author: NeilPretorius
 */

#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

//======================================
//============ Defines =================
//======================================

////////////////Product Info///////////////////

#define FIRMWARE_PROJECT_NUMBER			43
#define FIRMWARE_REVISION				1
#define FIRMWARE_SUB_REVISION			0

//////////////////////////////////////////////

#define FWConfigTimeStamp  __TIMESTAMP__
#define FWConfigDate   __DATE__
#define FWConfigTime  __TIME__

//////////////////////////////////////////////


//======================================
//============ Includes ================
//======================================

// === Standard Lib ===
#include <stdbool.h>
#include "strings.h"
#include <math.h>
#include <stdlib.h>
#include "string.h"
#include "stdio.h"
#include <stddef.h>
#include <stdarg.h>

//=== Text Fonts ===
#include "Fonts.h"

// == HAL Lib ===

#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal_dma2d.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_rcc_ex.h"
#include "stm32f7xx_ll_usb.h"
#include "stm32f7xx_hal_flash.h"
#include "stm32f7xx_hal_ltdc.h"
#include "stm32f7xx_hal_sram.h"
#include "stm32f7xx_hal_dma.h"
#include "stm32f7xx_hal_can.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_spi.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_nor.h"
#include "stm32f7xx_hal_i2c.h"
#include "stm32f7xx_hal_tim_ex.h"

#include "main.h"

// === BSP (Cube Generated) ===
#include "dsihost.h"
#include "fatfs.h"
#include "i2c.h"
#include "ltdc.h"
#include "quadspi.h"
#include "adc.h"
#include "can.h"
#include "spi.h"
#include "gpio.h"
#include "dma2d.h"
#include "usart.h"
#include "tim.h"
#include "usb_host.h"
#include "fmc.h"
//#include "ethernet.h"
//#include "ethernetif.h"

// === F769 ===
#include "F769_Init.h"
#include "F769_QSPI.h"
#include "F769_UART.h"
#include "F769_DMA.h"
#include "F769_IO.h"
#include "F769_SPI.h"
#include "F769_SRAM.h"
#include "F769_LCD.h"
#include "F769_Timers.h"

// === ICs ===

#include "MCP23S17.h"
#include "MR25H40.h"
#include "M41T94.h"
#include "MT25Q1G.h"
#include "SN65DSI83.h"
#include "S29GL01GS.h"

// === Application ===

#include "USB_App.h"
#include "App_Pins.h"
#include "App_Init.h"
#include "App_VisionModules.h"
#include "App_EventManager.h"
#include "App_Text.h"
#include <App_BacklightControl.h>
#include "App_UserAck.h"
#include "App_Debug.h"

#include "USB_Image.h"
#include "USB.h"
#include "MaxusX_Images.h"


#include "ICON3_Controller.h"
#include "HUB_2XX_CAN.h"

#include "TCP.h"

// ---- TITAN Vision Includes ----
#include "Delay.h"
#include "Vision_Parameters.h"
#include "VisionMaster.h"
#include "VisionZoneInterface.h"
#include "VisionMasterCommands.h"

//======================================
//======== Public Enumerations =========
//======================================

//Bit state
typedef enum
{
	Bit_Set 				= 0,
	Bit_Clear				= 1
} Bit_State_TypeDef;

//Output state
typedef enum
{
	Off 					= 0,
	On						= 1
} Output_State_TypeDef;

//======================================
//========== Public structs ============
//======================================

struct _IC_Flags
{
	bool		RTC_OK;
	bool		Light_Sensor_OK;
	bool 			NOR_FLASH_OK;

}IC_Flags;

//=== USB Flags  ===
struct _USB_Flags
{
	bool Image_Update_Requested;		//set when images must be updated
	bool Some_Startup_USB;				//set when ANY usb is required, so unit will not start normally but would rather start in USB mode
	bool DataLog_Requested;				//set to show data log was requested
	uint8_t USB_Operation_Type;			//can be a read or a write operation
	bool Force_Disc_Remove;				//This flag is set, to force a user to remove disk and replace
	bool Main_FW_Update_Requested;		//Set when the Main CPU FW must be updated
	bool Parameter_Update_Requested;	//Used to indicate a param update from USB flash disk
	bool Parameter_Download_Requested;	//Used to indicate a param update from USB flash disk
	bool USB_OK;						//Set this flag when the USB has been enumerated and sits in disk_explorer

}USB_Flags;

//======================================
//========= Public Variables ===========
//======================================

//======================================
//========= Public Functions ===========
//======================================



uint8_t debug;

#endif /* GLOBAL_VARIABLES_H_ */
