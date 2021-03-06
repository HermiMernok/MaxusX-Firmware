/*
 * USB_Image.c
 *
 *  Created on: Jun 24, 2015
 *      Author: JacoOlivier
 */

#include "USB_Image.h"
#include "ff_gen_drv.h"
#include "usbh_diskio.h"
#include "fatfs.h"
#include "ff.h"

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
FIL file;
DIR dir;


//Global Variables
extern USB_OTG_HCTypeDef  USB_OTG_Core;
extern USBH_HandleTypeDef hUsbHostFS;
extern ApplicationTypeDef Appli_state;
extern NOR_HandleTypeDef S29GL01GS;

char Image_number[50] 		 = {0};
/****************************************************************/

/****************************************************************/
void Check_Image_Count(void)
{
	Explore_Disk_Images("0:/", 0);


}

void Flash_Erase_Blocks (uint8_t Blocks)
{
	char Progress[50];
	uint32_t Start_Addr;

	Start_Addr = NOR_BLOCK_0;

	for(uint8_t i = 0; i < Blocks; i++)
	{

		sprintf(Progress,"Erasing Block %d / %d", i,Blocks);
		TextToScreen_SML (300, 255, Progress,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		S29GL01GS_EraseBlock(&S29GL01GS, Start_Addr);
		Start_Addr += 0x20000;

	}


}


/****************************************************************/

/****************************************************************/
/****************************************************************/
void Update_Images_Now(void)
{
	uint8_t Image_Count = 0;
	char Feedback_buf[50] = {0};

	for(int i = 1; i <= Number_Of_Images; i++)
	{
		void *Image_Location = (void*)(Bank1_NOR1_ADDR + image[i].address);

		if(BSP_LCD_ValidateBitmap(image[i].X_size, image[i].Y_size, Image_Location))
			Image_Count++;
	}

	//BSP_LCD_Clear(LCD_COLOR_BLACK);
	//
	//	sprintf(Feedback_buf, "Currently %d / %d images in flash", Image_Count, Number_Of_Images);
	//	TextToScreen(0, 160, Feedback_buf, CENTER_MODE, LCD_COLOR_WHITE, LCD_COLOR_BLACK, Text_Small);

	//if((Image_Count != Number_Of_Images) && (Image_Count != 0))
	//	{
	//TextToScreen_SML(0, 255, "Append new images, or erase and update all? ", LCD_COLOR_WHITE, LCD_COLOR_BLACK);

	//TextToScreen(1,30,"< APPEND", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);
	//	TextToScreen(360,30,"ERASE >", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);

	//wait for response
	//		while((!Input_Flags.Button_1) && (!Input_Flags.Button_3))
	//		{
	//			IO_App_Read_Inputs();
	//		}

	//	if(Input_Flags.Button_1)
	//	{
	//	TextToScreen_SML (0, 255, "Erasing flash. . .                     ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);

	//Erase blocks in flash
	//		Flash_Erase_Blocks(200);

	//		Image_Count = 0;
	//		}
	//	}
	//	else if((Image_Count == Number_Of_Images) || ((Image_Count != Number_Of_Images) && (Image_Count == 0)))
	//	{
	//		TextToScreen_SML(0, 255, "Restart, or erase and update all? ", LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	//
	//		TextToScreen(1,30,"< RESTART", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);
	//		TextToScreen(360,30,"ERASE >", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);
	//
	//		//wait for response
	//		while((!Input_Flags.Button_1) && (!Input_Flags.Button_3))
	//		{
	//		IO_App_Read_Inputs();
	//	}

	//	if(Input_Flags.Button_1)
	//	{
	//		TextToScreen_SML (0, 255, "Erasing flash. . .                     ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);

	//Erase blocks in flash
	//		Flash_Erase_Blocks(200);

	//		Image_Count = 0;
	//	}
	//	else
	//	{
	/* Software reset */
	//			NVIC_SystemReset();
	//		}
	//	}
	//	else
	//	{
	//	TextToScreen_SML (0, 255, "Erasing flash. . .                     ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);

	//Erase blocks in flash
	//Flash_Erase_Blocks(200);

	//		Image_Count = 0;
	//}

	//	BSP_LCD_Clear(LCD_COLOR_BLACK);

	//TextToScreen_SML (0, 255, "Updating Images!          ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);

	//Update images
	//	if(Image_Count == Number_Of_Images)
	//{
		Flash_Erase_Blocks(200);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_0);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_1);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_2);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_3);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_4);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_5);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_6);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_7);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_8);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_9);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_10);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_11);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_12);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_13);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_14);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_15);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_16);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_17);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_18);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_19);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_20);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_21);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_22);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_23);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_24);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_25);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_26);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_27);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_28);
//	S29GL01GS_EraseBlock(&S29GL01GS, NOR_BLOCK_29);
	Image_Browser(Images_Dir, Image_Count);
	//	}
}



/****************************************************************/
/**
 * @brief  Explore_Disk
 *         Displays disk content
 * @param  path: pointer to root path
 * @retval None
 */
/****************************************************************/
bool Explore_Disk_Images(char* path, uint8_t recu_level)
{
	FRESULT res;
	FILINFO fno;
	FATFS mynewdiskFatFs;
	char *fn;

	fn = fno.fname;

	char Number_String[4];
	Number_String[0] = 0;
	Number_String[1] = 0;
	Number_String[2] = 0;
	Number_String[3] = 0;
	int i = 0;
	int j = 0;

	uint8_t String50[] = "       ";

	j = 0;
	Flash_Disk_ImageCount = 0;

	//Mount the USB device
	res = f_mount(&mynewdiskFatFs, (TCHAR const*)path, 1);
	//Open the Images Directory
	res = f_opendir(&dir, (TCHAR const*)path);
	if (res == FR_OK)
	{
		while(hUsbHostFS.device.is_connected == 1)
		{
			//Read the Images Directory
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0)
			{
				break;
			}
			if (fno.fname[0] == '.')
			{
				continue;
			}
			//#if _USE_LFN
			//			fn = *fno.lfname ? fno.lfname : fno.fname;
			//#else
			fn = fno.fname;
			//#endif
			/* Print Image File Names (*.bmp) to screen */
			for (i = 0; i < 7; i++)	//
			{
				if (((fn[i] >= 0x2E) && (fn[i] <= 0x7A)) || (fn[i] == 0x20))		// '.' <= fn[i] <= 'z' || ' '
				{
					String50[i] = (uint8_t) fn[i];
				}
				else
				{
					String50[i] = 0x20;
				}
			}

			if((fno.fattrib & AM_MASK) == AM_DIR) {}
			else
			{
				for (i = 0; i < Number_Of_Images; i++)
				{
					if (((String50[4] == 'b') && (String50[5] == 'm') && (String50[6] == 'p')) || ((String50[4] == 'B') && (String50[5] == 'M') && (String50[6] == 'P')))
					{
						Flash_Disk_ImageCount++;
						break;
					}
					else
					{
					}
				}
			}
		}
	}
	else
	{

	}

	//now check if image count was OK
	if(Flash_Disk_ImageCount == Number_Of_Images)
		return true;
	else
		return false;
}



/****************************************************************/
/**
 * @brief  Image Browser
 *         Browse Images on disk
 * @param  path: pointer to root path
 * @retval None
 */
/****************************************************************/
uint8_t Image_Browser (char* path, uint8_t Image_Count)
{
	FRESULT res;
	uint8_t ret = 1;
	FILINFO fno;
	FATFS mynewdiskFatFs;
	char *fn;
	uint8_t my_breaker = 0;

	//#if _USE_LFN
	//	static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
	//	fno.lfname = lfn;
	//	fno.lfsize = sizeof(lfn);
	//#endif

	char test_string[5];
	uint16_t test_int = Number_Of_Images;


	//Mount the USB device
	res = f_mount(&mynewdiskFatFs, (TCHAR const*)path, 1);
	res = f_opendir(&dir, path);
	if (res == FR_OK)
	{
		for (;;)
		{
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0 || my_breaker == 1)
				break;
			if (fno.fname[0] == '.')
				continue;
			//#if _USE_LFN
			//			fn = *fno.lfname ? fno.lfname : fno.fname;
			//#else
			fn = fno.fname;
			//#endif
			if (fno.fattrib & AM_DIR)
			{
				continue;
			}
			else
			{
				char Image_name[7] = {0};

				Image_name[3] = '.';
				Image_name[4] = 'b';
				Image_name[5] = 'm';
				Image_name[6] = 'p';
				fn[3] = '.';
				fn[4] = 'b';
				fn[5] = 'm';
				fn[6] = 'p';
				fn[8] = 0x00;
				fn[9] = 0x00;
				fn[10] = 0x00;
				fn[11] = 0x00;
				fn[12] = 0x00;
				fn[13] = 0x00;
				fn[14] = 0x00;
				fn[15] = 0x00;
				fn[16] = 0x00;
				fn[17] = 0x00;
				fn[18] = 0x00;

				for(int k = Image_Count; k <= Number_Of_Images; k++)
				{
					//Convert image number to name
					Bin2BCD(k, Image_name, 3);

					//Make file name
					fn[0] = Image_name[0];
					fn[1] = Image_name[1];
					fn[2] = Image_name[2];

					sprintf(Image_number, "Loading Image %d of %d     ", k,Number_Of_Images);
					TextToScreen_SML (300, 255,Image_number,LCD_COLOR_WHITE,LCD_COLOR_BLACK);


					//Do image
					Do_Image(fn, k);
					BSP_LCD_Clear(LCD_COLOR_BLACK);
					App_printImg(0,0,k);
				}

				//Add delay so that the last loaded image can be seen
				Delay(1000);
				BSP_LCD_Clear(LCD_COLOR_BLACK); //clear last images before returning to the menu

				ret = 0;
				res = 0;
				my_breaker = 1;
			}
		}
	}

	res = f_closedir(&dir);

	return ret;
}



/****************************************************************/
/****************************************************************/
void Do_Image(char *FileName, uint16_t imagenumber)
{
	FRESULT res;
	FATFS mynewdiskFatFs;
	char FileDir[50] = {0};

	//String operations to add directory to the file name
	strcpy(FileDir, Images_Dir);
	strcat(FileDir, "/");
	strcat(FileDir,FileName);

	//Open image file
	res = f_open(&file, FileDir, FA_OPEN_EXISTING | FA_READ);

	//Load image data into internal flash memory
	Show_Image(0, 0, imagenumber);

	f_close(&file);
}



/****************************************************************/
/**
 * @brief  Show and Save Image
 *         Displays BMP image
 * @param  Address -> Block in NOR Flash to save image to
 * @retval None
 *
 */
void Show_Image(uint16_t x, uint16_t y, uint16_t index)
{

	uint16_t i = 0, j = 0;
	uint16_t numOfReadBytes = 0;
	FRESULT res;
	uint16_t dataBuf[IMAGE_BUFFER_SIZE/2] = {0};
	uint16_t dataBuf1[IMAGE_BUFFER_SIZE/2] = {0};
	uint32_t address = image[index].address;
	uint16_t WRcount = 0;
	HAL_NOR_StatusTypeDef Result;

	//LCD_SetDisplayArea(x, x + x_size, y, y + y_size);
	//LCD_WriteCommand(CMD_WR_MEMSTART);

	/* Bypass Bitmap header  - Bytes */
	res = f_lseek(&file, 0);			//66

	if(res == FR_OK)
	{
		while (hUsbHostFS.device.is_connected == 1)
		{
			res = f_read(&file, Image_Buf, IMAGE_BUFFER_SIZE, (void *)&numOfReadBytes);

			if((numOfReadBytes == 0) || (res != FR_OK)) /*EOF or Error*/

			{
				//Done loading image
				break;
			}

			for(i = 0 ; i < IMAGE_BUFFER_SIZE; i+= 2)
			{
				dataBuf[i/2] = ((uint16_t)Image_Buf[i+1] << 8) + ((uint16_t)Image_Buf[i]);
			}
			Result = S29GL01GS_WriteBuffer(&S29GL01GS, dataBuf, address, IMAGE_BUFFER_SIZE / 2);
			//			S29GL01GS_ReadBuffer(&S29GL01GS, dataBuf1, address, IMAGE_BUFFER_SIZE / 2);
			address += (IMAGE_BUFFER_SIZE); 	//NOR  note: * 2 was corrected
			j++;
			WRcount++;
		}
	}
}



