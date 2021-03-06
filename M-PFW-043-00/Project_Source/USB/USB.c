/*
 * USB.c
 *
 *  Created on: Jun 24, 2015
 *      Author: JacoOlivier
 */

#include "USB.h"
#include "ff_gen_drv.h"
#include "usbh_diskio.h"
#include "fatfs.h"
#include "ff.h"
#include <stdio.h>
#include <stdint.h>
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
extern ApplicationTypeDef Appli_state;
extern NOR_HandleTypeDef S29GL01GS;
extern USBH_HandleTypeDef hUsbHostFS;
//extern Parameter Temp_Params[Parameters_Size];

//Test Variables
//short int F_WriteFile = 0;
//short int F_ReadList = 0;
//short int F_ReadFile = 0;


/****************************************************************/
/*This is the main state machine for the FlexiDisplay USB
 */
/****************************************************************/
void Main_USB_Handler(void)
{

}



/****************************************************************/
//USB Core functions -- these are automatically entered by the
//USB controller
/****************************************************************/

/****************************************************************/
//this always runs for any USB_OTG at system startup
/****************************************************************/
void USB_Core_Init(void)
{
	//display on lcd
	//	OutTextXY(LCD_Setup_Text_X, Line4_y_Position, LCD_USB_Message_1);

#ifdef USB_Debug
	USART_SendString(COM_PC,"USB OTG Initialised\n\r");
#endif
}


/****************************************************************/
//display device attached, clear device disconnected
/****************************************************************/
void USB_Core_New_Device(void)
{
	//display on lcd
	//	OutTextXY(LCD_Setup_Text_X, Line5_y_Position, LCD_USB_Message_3);

#ifdef USB_Debug
	USART_SendString(COM_PC,"USB Device detected\n\r");
#endif
}

/****************************************************************/
//Some error occurred, not sure yest what this is??
/****************************************************************/
void USB_Core_Unrecovered_Error(void)
{
#ifdef USB_Debug
	USART_SendString(COM_PC,"USB OTG non-recovered error\n\r");
#endif
}

/****************************************************************/
//Called when the flash disc is disconnected
/****************************************************************/
void USB_Core_Disconnected(void)
{
	//	//display on lcd
	//	OutTextXY(LCD_Setup_Text_X, Line5_y_Position, LCD_USB_Message_2);
	//	//clear other lines
	//	OutTextXY(LCD_Setup_Text_X, Line6_y_Position, Clear_Line);
	//	OutTextXY(LCD_Setup_Text_X, Line7_y_Position, Clear_Line);
	//	OutTextXY(LCD_Setup_Text_X, Line8_y_Position, Clear_Line);
	//	OutTextXY(LCD_Setup_Text_X, Line9_y_Position, Clear_Line);
	//	OutTextXY(LCD_Setup_Text_X, Line10_y_Position, Clear_Line);
	//	OutTextXY(LCD_Setup_Text_X, Line11_y_Position, Clear_Line);


	//allow reset of error flag
	//USB_Flags.Force_Disc_Remove = false;

#ifdef USB_Debug
	USART_SendString(COM_PC,"USB Device disconnected\n\r");
#endif
}

/****************************************************************/
//Not sure when this is called
/****************************************************************/
void USB_Core_Reset(void)
{

}

/****************************************************************/
//Called when new device is in and enumeration is done.
/****************************************************************/
void USB_Core_Enum_Done(void)
{
	//display on lcd
	//	OutTextXY(LCD_Setup_Text_X, Line6_y_Position, LCD_USB_Message_8);
#ifdef USB_Debug
	USART_SendString(COM_PC,"USB Device Enumeration Complete\n\r");
#endif
}

/****************************************************************/
//Called for unsupported devices
/****************************************************************/
void USB_Core_Unsupported_Device(void)
{

#ifdef USB_Debug
	USART_SendString(COM_PC,"USB ERROR - Device NOT Supported\n\r");
#endif

}

/****************************************************************/
//Entered once USB device speed is detected
/****************************************************************/
void USB_Core_Speed_Detected(uint8_t DeviceSpeed)
{
	if(DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
	{
		//display on lcd
		//		OutTextXY(LCD_Setup_Text_X, Line6_y_Position, LCD_USB_Message_4);
#ifdef USB_Debug
		USART_SendString(COM_PC,"USB High Speed Device\n\r");
#endif
	}
	else if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
	{
		//display on lcd
		//		OutTextXY(LCD_Setup_Text_X, Line6_y_Position, LCD_USB_Message_5);
#ifdef USB_Debug
		USART_SendString(COM_PC,"USB Full Speed Device\n\r");
#endif
	}
	else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
	{
		//display on lcd
		//	OutTextXY(LCD_Setup_Text_X, Line6_y_Position, LCD_USB_Message_6);
#ifdef USB_Debug
		USART_SendString(COM_PC,"USB Low Speed Device\n\r");
#endif
	}
	else
	{
		//display on lcd
		//	OutTextXY(LCD_Setup_Text_X, Line6_y_Position, LCD_USB_Message_7);
#ifdef USB_Debug
		USART_SendString(COM_PC,"ERROR - Speed Detect Error\n\r");
#endif
	}
}


/****************************************************************/
//Fat Init error
/****************************************************************/
void USB_Core_FAT_Error(void)
{
	;//display on lcd
	//OutTextXY(LCD_Setup_Text_X, Line7_y_Position, LCD_USB_Message_10);

#ifdef USB_Debug
	USART_SendString(COM_PC,"USB ERROR - Cannot Init FAT FS\n\r");
#endif
}

/****************************************************************/
//Fat Init error, disk protected
/****************************************************************/
void USB_Core_FAT_Disk_Protected(void)
{
	//display on lcd
	//OutTextXY(LCD_Setup_Text_X, Line7_y_Position, LCD_USB_Message_11);

#ifdef USB_Debug
	USART_SendString(COM_PC,"USB ERROR - Disk Write Protected\n\r");
#endif
}

///****************************************************************/
////Fat Init OK
///****************************************************************/
//void USB_Core_FAT_OK(void)
//{
//	//display on lcd
////	OutTextXY(LCD_Setup_Text_X, Line7_y_Position, LCD_USB_Message_9);
//
//	//Fat init was OK, go to state machine wait.
//	USBH_USR_ApplicationState = USH_USR_FS_WAITCOMMAND;
//
//#ifdef USB_Debug
//	USART_SendString(COM_PC,"USB FAT FS Initialisation Complete\n\r");
//#endif
//}


///****************************************************************/
////Called when Init is done and disc is in, here the correct
////USB handler must be called.
///****************************************************************/
//void USB_Core_Waiting(void)
//{
//	//If an error flag is set, don't allow entry here
//	if(USB_Flags.Force_Disc_Remove == false)
//	{
//		//Ok check what user wanted, read or write
//		if(USB_Flags.USB_Operation_Type == Write)
//		{
//			//some write function
//			USBH_USR_ApplicationState = USH_USR_FS_WRITEFILE;
//		}
//		else
//		{
//			//some read function
//			USBH_USR_ApplicationState = USH_USR_FS_READLIST;
//		}
//	}
//
//
//#ifdef USB_Debug
//	USART_SendString(COM_PC,"USB SM Waiting\n\r");
//#endif
//}




/****************************************************************/
//This function is called if the disc is in, all is started.
//Function will now check what type of USB read is required
//and call the correct function from here.
/****************************************************************/
void USB_User_File_Reader(void)
{



}


/****************************************************************/
//This function is called to check if there are the required images
//on the disc
/****************************************************************/
void USB_User_File_Explorer(void)
{
	//Now check what type of file scan is required.


	/*UPDATE IMAGES*/
//	if(USB_Flags.Image_Update_Requested)
//	{

		TIM3_Stop();
		TIM4_Stop();


		//Link the latest attached USB device
		FATFS_LinkDriver(&USBH_Driver, Images_Dir);

		//check images, if count is OK, allow update, else show message and stop
		if(Explore_Disk_Images(Images_Dir, 0))
		{
			Update_Images_Now();
			USB_Flags.Force_Disc_Remove = true;
			USB_Flags.Image_Update_Requested = false;

			//Unlink the USB device associated with the latest used directory
			FATFS_UnLinkDriver(Images_Dir);

			TIM3_Start();
			TIM4_Start();


		}
	//	else
	//	{
			USB_Flags.Image_Update_Requested = false;
			TIM3_Start();
			TIM4_Start();

			USB_Flags.Force_Disc_Remove = true;
	//	}


//	}
//	else if(USB_Flags.DataLog_Requested)
//	{
//		USB_Flags.DataLog_Requested = false;
//
//		TIM3_Stop();
//		TIM4_Stop();
//		TIM5_Stop();
//
//		//Link the latest attached USB device
//		FATFS_LinkDriver(&USBH_Driver, Log_Dir);
//
//	//	BSP_LCD_Clear(LCD_COLOR_BLACK);
//	//	TextToScreen_TITLE(0,Title_Y,"Downloading Logs",RGBConvert(255, 38, 0),LCD_COLOR_BLACK);
//
//	//	TextToScreen_MED(65,140,"*Do Not Remove Flashdrive*", LCD_COLOR_WHITE,LCD_COLOR_BLACK);
//
//		if (check_if_block_ready())
//		{
//			check_and_move_block_ready();
//		}
//
//		datalog_req_move_block();
//
//		//this function will get datalog and store on USB flash disk
//		User_DataLog_Extraction_USB();
//
//		//Unlink the USB device associated with the latest used directory
//		FATFS_UnLinkDriver(Log_Dir);
//
//
//		TIM3_Start();
//		TIM4_Start();
//		TIM5_Start();

//	}
//	else if(USB_Flags.Parameter_Update_Requested)
//	{
//
//		TIM3_Stop();
//		TIM4_Stop();
//	//	TIM5_Stop();
//
//		BSP_LCD_Clear(LCD_COLOR_BLACK);
//		User_Parameter_Upload_USB();
//
//		TIM3_Start();
//		TIM4_Start();
//	//	TIM5_Start();
//
//		USB_Flags.Parameter_Update_Requested = false;
//
//	}
//	else if(USB_Flags.Parameter_Download_Requested)
//	{
//
//		TIM3_Stop();
//		TIM4_Stop();
//		//TIM5_Stop();
//
//		BSP_LCD_Clear(LCD_COLOR_BLACK);
//		User_Parameter_Extraction_USB();
//
//		TIM3_Start();
//		TIM4_Start();
//		//TIM5_Start();
//
//		USB_Flags.Parameter_Download_Requested = false;
//
//	}

}

//User requested datalog extraction via the USB
void User_DataLog_Extraction_USB(void)
{
//	FRESULT res;
//	FIL file;
//	FATFS mynewdiskFatFs;
//
//	char data_block1[512];
//	char data_block2[512];
//	uint32_t i,j, bytes_writen=0;
//
//	char file_string[20];
//
//	//EV_log_flags.ev_usb_download_prog = 0;
//
//	//extract the date and time for file header
//	ReadTime_M41T94rtc();
//
//	file_string[0] = time_10date + 0x30;
//	file_string[1] = time_date + 0x30;
//	file_string[2] = '-';
//	file_string[3] = time_10month + 0x30;
//	file_string[4] = time_month + 0x30;
//	file_string[5] = '-';
//	file_string[6] = '2';
//	file_string[7] = '0';
//	file_string[8] = time_10year + 0x30;
//	file_string[9] = time_year + 0x30;
//	file_string[10] = '_';
//	file_string[11] = time_10hours + 0x30;
//	file_string[12] = time_hours + 0x30;
//	file_string[13] = '-';
//	file_string[14] = time_10minutes + 0x30;
//	file_string[15] = time_minutes + 0x30;
//	file_string[16] = '-';
//	file_string[17] = time_10seconds + 0x30;
//	file_string[18] = time_seconds + 0x30;
//	file_string[19] = 0;
//
//	char filename[100];
//	sprintf(filename, "0:/Commander101/DataLog/DataLog_UnitID-%d_%s.txt", (int)Local_Params[Local_VID].ParamCURRENT, file_string);
//
//	//Mount the USB device
//	res = f_mount(&mynewdiskFatFs, Log_Dir, 0);
//	//create or open directory file and save data
//	res = f_mkdir("0:/Commander101");
//	res = f_mkdir("0:/Commander101/DataLog");
//	res = f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
//	if (res == FR_OK)
//	{
//		Delay(1000);
//
//		res = f_lseek(&file, file.fsize);
//
//		//EV_log_flags.ev_log_download_active = true;
//
//		//Total number of event logs available
//		for (i = 0; i < Num_Flash_blocks_EV_Logs; i++)
//		{
//
//			EV_log_flags.ev_usb_download_prog++;
//			App_UpdateProgBars();
//
//			//Total of 128 blocks in a sector
//			for(j=0; j<128; j++)
//			{
//				//write first 512 bytes to the flash
//				S29GL01GS_ReadBuffer(&S29GL01GS, data_block1, Flash_block_Start_EV_logs + Flash_block_size * i + j*1024, 256*2);
//				f_write(&file,data_block1, 512, bytes_writen);
//				//write second 512 bytes to the flash
//				S29GL01GS_ReadBuffer(&S29GL01GS, data_block2, Flash_block_Start_EV_logs + 512 + Flash_block_size * i + j*1024, 256*2);
//				f_write(&file,data_block2, 512, bytes_writen);
//				//if usb is extracted then reset
//				if(hUsbHostFS.device.is_connected != 1)
//				{
//					NVIC_SystemReset();
//				}
//			}
//		}
//
//		res = f_close(&file);
//
//		EV_log_flags.ev_log_download_active = false;
//
//		//Upload success
//		TextToScreen(0,100,"Complete!", CENTER_MODE,LCD_COLOR_GREEN, LCD_COLOR_BLACK, Text_Large);
//
//	}
//	if ((res != FR_OK) || (file.fsize == 0))
//	{
//		TextToScreen(0,100,"- USB Failed -", CENTER_MODE, LCD_COLOR_RED, LCD_COLOR_BLACK, Text_Large);
//
//	}
//
//	//Clear text area
//	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//	BSP_LCD_FillRect(0,120,480,40);
//
//	TextToScreen(0,140,"Please Remove Flashdrive", CENTER_MODE, LCD_COLOR_WHITE, LCD_COLOR_BLACK, Text_Medium);
//
//
//	//Unlink the USB device associated with the latest used directory
//	FATFS_UnLinkDriver(Log_Dir);
//
//	//wait for disk to be removed then reset
//	while(hUsbHostFS.device.is_connected == 1)
//	{
//	}
//	NVIC_SystemReset();
}

//User requested parameter upload via the USB
void User_Parameter_Upload_USB(void)
{

//	FRESULT res;
//	FIL file;
//	FATFS mynewdiskFatFs;
//	char  Feedback[100] = {0};
//
//	uint8_t Param_buf[Param_Len] = {0};
//	bool	Result = false;
//
//	uint32_t i,j, bytes_writen=0;
//
//	char filename[100];
//	sprintf(filename, "%s/Commander1xx_params.mer", Log_Params);
//
//	//Link the latest attached USB device
//	FATFS_LinkDriver(&USBH_Driver, Log_Params);
//
//	//Mount the USB device
//	res = f_mount(&mynewdiskFatFs, Log_Params, 0);
//
//	//Open file
//	res = f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
//
//	if (res == FR_OK)
//	{
//		f_read(&file,Param_buf, Param_Len, bytes_writen);
//	}
//
//	res = f_close(&file);
//
//	/* === Check data framing === */
//	if((Param_buf[0] == RS232_SOF1) && (Param_buf[1] == RS232_SOF2) && (Param_buf[Param_Len - 1] == RS232_EOF))
//	{
//		Parse_Param_Message(Param_buf);
//		Result = true;
//	}
//
//
//	//Unlink the USB device associated with the latest used directory
//	FATFS_UnLinkDriver(Log_Params);
//
//	if(Result)
//	{
//
//		Param_Status.FW_Version_Read 	= Temp_Params[Local_FW_Rev].ParamCURRENT;
//		Param_Status.FW_Subversion_Read	= Temp_Params[Local_FW_SubRev].ParamCURRENT;
//
//		if((Param_Status.FW_Version_Read == Firmware_Revision) && (Param_Status.FW_Subversion_Read == Firmware_SubRevision))
//		{
//			//Write parameters to NVRAM
//			App_WriteParameters (Temp_Params);
//			//Log parameters
//			App_LogParameters (Temp_Params, Source_USB);
//
//			Sys_ptrs.System_Commisioning = 1;
//			log_write_system_pointers();
//
//			TextToScreen(0,130,"Parameter Upload Complete!",CENTER_MODE,LCD_COLOR_GREEN,LCD_COLOR_BLACK,Text_Medium);
//
//		}
//		else
//		{
//			sprintf(Feedback, "V%d.%d Parameters not Compatible with V%d.%d Firmware!", Param_Status.FW_Version_Read, Param_Status.FW_Subversion_Read, Firmware_Revision, Firmware_SubRevision);
//			TextToScreen(0,130,Feedback,CENTER_MODE,LCD_COLOR_RED,LCD_COLOR_BLACK,Text_Small);
//		}
//
//
//	}
//	else
//		TextToScreen(0,130,"Parameter File Corrupt!",CENTER_MODE,LCD_COLOR_RED,LCD_COLOR_BLACK,Text_Medium);
//
//
//
//	TextToScreen(0,255,"Please remove flash drive",CENTER_MODE,LCD_COLOR_WHITE,LCD_COLOR_BLACK,Text_Small);
//
//	//wait for disk to be removed then reset
//	while(hUsbHostFS.device.is_connected == 1)
//	{
//	}
//	NVIC_SystemReset();


}


//User requested parameter download via the USB
void User_Parameter_Extraction_USB(void)
{

//	FRESULT res;
//	FIL file;
//	FATFS mynewdiskFatFs;
//
//	uint8_t Param_buf[Param_Len] = {0};
//
//	uint32_t i,j, bytes_writen=0;
//
//	char filename[100];
//	sprintf(filename, "%s/Commander1xx_params.mer", Log_Params);
//
//	Construct_Param_Message(Param_buf, 'N');
//
//	//Link the latest attached USB device
//	FATFS_LinkDriver(&USBH_Driver, Log_Params);
//
//	//Mount the USB device
//	res = f_mount(&mynewdiskFatFs, Log_Params, 0);
//	//create or open directory file and save data
//	res = f_mkdir("0:/Commander101");
//	res = f_mkdir("0:/Commander101/Parameters");
//	res = f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
//
//	if (res == FR_OK)
//	{
//		f_write(&file,Param_buf, Param_Len, bytes_writen);
//	}
//	res = f_close(&file);
//
//
//	//Unlink the USB device associated with the latest used directory
//	FATFS_UnLinkDriver(Log_Params);
//
//
//	TextToScreen(0,130,"Parameter Extraction Complete!",CENTER_MODE,LCD_COLOR_GREEN,LCD_COLOR_BLACK,Text_Medium);
//
//	TextToScreen(0,255,"Please remove flash drive",CENTER_MODE,LCD_COLOR_WHITE,LCD_COLOR_BLACK,Text_Small);
//
//	//wait for disk to be removed then reset
//	while(hUsbHostFS.device.is_connected == 1)
//	{
//	}
//	NVIC_SystemReset();

}


/****************************************************************/
//This function is called when data must be written to the Flash
//Disk, check which function to call from here
/****************************************************************/
void USB_User_File_Writer(void)
{
	//Datalog Requested
	if(USB_Flags.DataLog_Requested == true)
	{
		USB_Flags.DataLog_Requested = false;

		//todo
		//		if (check_if_block_ready())
		//		{
		//			check_and_move_block_ready();
		//		}
		//		datalog_req_move_block();
		//
		//		//this function will get datalog and store on USB flash disk
		//		User_DataLog_Extraction_USB();
	}

}

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
