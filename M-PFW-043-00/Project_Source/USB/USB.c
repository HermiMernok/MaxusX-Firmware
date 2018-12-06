/*
 * USB.c
 *
 *  Created on: 20 November, 2018
 *      Author: Hermi du Plessis
 */

//=== Includes ===
#include "USB.h"
#include "ff_gen_drv.h"
#include "usbh_diskio.h"
#include "fatfs.h"
#include "ff.h"
#include <stdio.h>
#include <stdint.h>

//=== Defines ====

//=== Global Variables ===
extern ApplicationTypeDef Appli_state;
extern NOR_HandleTypeDef S29GL01GS;
extern USBH_HandleTypeDef hUsbHostFS;


//=== Local Variables ===

//=== Functions ===


/*================================================
 *USB Core functions -- these are automatically
 *USB entered by the USB controller
=================================================*/

/**===============================================
 * @brief USB Core init is required at system
 * startup for USB_OTG.
 * @param  None
 * @retval None
 ===============================================*/

void USB_Core_Init(void)
{
	TextToScreen_SML(0,0,USB_STATUS_MESSAGE_1,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug

#endif
}

/**===============================================
 * @brief Display device attached, clear device
 * disconnected
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_New_Device(void)
{
#ifdef USB_Debug

#endif
}

/**===============================================
 * @brief Some error occurred.
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_Unrecovered_Error(void)
{
	TextToScreen_SML(0,30,USB_ERROR_MESSAGE_5,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug

#endif
}

/**===============================================
 * @brief Called when the flash disc is disconnected
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_Disconnected(void)
{
	TextToScreen_SML(0,0,USB_STATUS_MESSAGE_4,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug

#endif
}

/**===============================================
 * @brief
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_Reset(void)
{

}

/**===============================================
 * @brief Called when new device is in and enumeration
 * is done.
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_Enum_Done(void)
{
	TextToScreen_SML(0,0,USB_STATUS_MESSAGE_2,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug

#endif
}

/**===============================================
 * @brief Called for unsupported device
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_Unsupported_Device(void)
{
	TextToScreen_SML(0,30,USB_ERROR_MESSAGE_1,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug

#endif

}

/**===============================================
 * @brief Entered once USB device speed is detected
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_Speed_Detected(uint8_t DeviceSpeed)
{
	if(DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
	{
		TextToScreen_SML(0,60,USB_SPEED_MESSAGE_1,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug
		USART_SendString(COM_PC,"USB High Speed Device\n\r");
#endif
	}
	else if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
	{

		TextToScreen_SML(0,60,USB_SPEED_MESSAGE_2,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug
		USART_SendString(COM_PC,"USB Full Speed Device\n\r");
#endif
	}
	else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
	{
		TextToScreen_SML(0,60,USB_SPEED_MESSAGE_3,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug
		USART_SendString(COM_PC,"USB Low Speed Device\n\r");
#endif
	}
	else
	{
		TextToScreen_SML(0,60,USB_SPEED_MESSAGE_4,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug
		USART_SendString(COM_PC,"ERROR - Speed Detect Error\n\r");
#endif
	}
}

/**===============================================
 * @brief FAT init Error
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_FAT_Error(void)
{
	TextToScreen_SML(0,30,USB_ERROR_MESSAGE_3,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug

#endif
}

/**===============================================
 * @brief Fat Init Error, disk protected
 * @param  None
 * @retval None
 * ===============================================*/
void USB_Core_FAT_Disk_Protected(void)
{
	TextToScreen_SML(0,30,USB_ERROR_MESSAGE_4,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
#ifdef USB_Debug

#endif
}

/**===============================================
 * @brief This function is called if the disk is in,
 * all is started. Function will now check what type
 * of USB read is required and call the correct function
 * from here.
 * @param  None
 * @retval None
 * ===============================================*/
void USB_User_File_Reader(void)
{
}


/**===============================================
 * @brief This function is called to check if there
 * are the required images on the disc.
 * @param  None
 * @retval None
 * ===============================================*/
void USB_User_File_Explorer(void)
{
	//Now check what type of file scan is required.


	/*UPDATE IMAGES*/
	if(USB_Flags.Image_Update_Requested)
	{

		TIM3_Stop();
		TIM4_Stop();


		//Link the latest attached USB device
		FATFS_LinkDriver(&USBH_Driver, Images_Dir);

		//check images, if count is OK, allow update, else show message and stop
		if(Explore_Disk_Images(Images_Dir))
		{
			Update_Images_SM();
			USB_Flags.Force_Disc_Remove = true;
			USB_Flags.Image_Update_Requested = false;

			//Unlink the USB device associated with the latest used directory
			FATFS_UnLinkDriver(Images_Dir);

			TextToScreen_SML(0, 255, "Press any button to restart and continue.", LCD_COLOR_WHITE, LCD_COLOR_BLACK);

			IO_App_Read_Inputs();

			while((!Input_Flags.Button_1) && (!Input_Flags.Button_2)&& (!Input_Flags.Button_3)&& (!Input_Flags.Button_4))
			{
				IO_App_Read_Inputs();
			}
NVIC_SystemReset();

		}
		else
		{
			USB_Flags.Image_Update_Requested = false;
			USB_Flags.Force_Disc_Remove = true;
			TIM3_Start();
			TIM4_Start();
		}
	}
}



/**===============================================
 * @brief This function is called when data must
 * be written to the Flash Disk, check which function
 * to call from here
 *
 * @param  None
 * @retval None
 * ===============================================*/

void USB_User_File_Writer(void)
{
	//Datalog Requested
	if(USB_Flags.DataLog_Requested == true)
	{
		USB_Flags.DataLog_Requested = false;

	}

}


/**===============================================
 * @brief USB Application statemachine. Check if
 * Flash Disk is ready, start exploring Flash Disk.
 * @param  None
 * @retval None
 * ===============================================*/
void App_USB_SM(void)
{
	if(Appli_state == APPLICATION_READY)
	{
		USB_Flags.USB_OK = true;
		USB_User_File_Explorer();
	}
	else
		USB_Flags.USB_OK = false;
}
