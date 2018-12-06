/*
 * USB_Image.c
 *
 *  Created on: 20 November, 2018
 *      Author: Hermi du Plessis
 */

//=== Includes ===
#include "USB_Image.h"
#include "ff_gen_drv.h"
#include "usbh_diskio.h"
#include "fatfs.h"
#include "ff.h"

//=== Local Variables ===
FIL file;
DIR dir;

//=== Global Variables ===
extern USB_OTG_HCTypeDef  USB_OTG_Core;
extern USBH_HandleTypeDef hUsbHostFS;
extern ApplicationTypeDef Appli_state;
extern NOR_HandleTypeDef S29GL01GS;

//=== Private Variables ===

char _image_Number[50] 		 = {0};

//=== Function Prototypes ===

void Image_to_Flash(uint16_t image_index);
void Store_Image(char *FileName, uint16_t imagenumber);
void Disk_Explorer(void);
bool Explore_Disk_Images(char* path);
uint8_t Image_Browser (char* path, uint8_t Image_Count);
void WriteFile(void);
void Flash_Erase_Blocks (uint8_t Blocks);

//=== Functions ===

void Wait_Response_than_Restart(void)
{
	while((!Input_Flags.Button_1) && (!Input_Flags.Button_2)&& (!Input_Flags.Button_3)&& (!Input_Flags.Button_4))
	{
		IO_App_Read_Inputs();
	}

	NVIC_SystemReset();
}

/**===============================================
 * @brief  Check the number of images
 * @param  None
 * @retval None
 ===============================================*/
void Check_Image_Count(void)
{
	Explore_Disk_Images("0:/");
}

/**===============================================
 * @brief  Erase blocks in Flash
 * @param  Blocks - number of blocks to be erased starting from block 0.
 * @retval None
  ===============================================*/
void Flash_Erase_Blocks (uint8_t blocks)
{
	char progress[50];
	uint32_t start_Addr;

	start_Addr = NOR_BLOCK_0;

	for(uint8_t i = 0; i < blocks; i++)
	{

		sprintf(progress,"             Erasing Block %d / %d              ", i,blocks);
		TextToScreen(0, 255, progress,CENTER_MODE , LCD_COLOR_WHITE,LCD_COLOR_BLACK,Text_Small);
		S29GL01GS_EraseBlock(&S29GL01GS, start_Addr);
		start_Addr += 0x20000;
	}
}

/**===============================================
 * @brief  Statemachine to update images. Determine if number of image are
 * correct and wait for user input.
 * @param  None
 * @retval None
  ===============================================*/
void Update_Images_SM(void)
{
	uint8_t image_Count = 0;
	char Feedback_buf[30] = {0};

	// === Validate and count number of images on Flash ===

	for(int i = 1; i <= Number_Of_Images; i++)
	{
		void *Image_Location = (void*)(Bank1_NOR1_ADDR + image[i].address);

		if(BSP_LCD_ValidateBitmap(image[i].X_size, image[i].Y_size, Image_Location))
		{
			image_Count++;
		}
	}

	BSP_LCD_Clear(LCD_COLOR_BLACK);
	HAL_Delay(1);

	sprintf(Feedback_buf, "%d / %d images in flash", image_Count, Number_Of_Images);
	TextToScreen(0, 165, Feedback_buf, CENTER_MODE, LCD_COLOR_WHITE, LCD_COLOR_BLACK, Text_Small);

	/* =================================================
	 * if flash image count is less than the total number
	 * image required on the unit and not equal to zero
	 * ask if the user wants to append the new images,
	 * erase and update all or restart.
	 * ================================================*/
	if((image_Count != Number_Of_Images) && (image_Count != 0))
	{
		TextToScreen_SML(0, 255, "Append new images, or erase and update all? ", LCD_COLOR_WHITE, LCD_COLOR_BLACK);

		TextToScreen(BSP_LCD_X_Size-200,BSP_LCD_Y_Size-100,"APPEND >", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);
		TextToScreen(BSP_LCD_X_Size-150,100,"ERASE >", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);

		//wait for response
		while((!Input_Flags.Button_1) && (!Input_Flags.Button_3))
		{
			IO_App_Read_Inputs();
		}

		if(Input_Flags.Button_1)
		{
			TextToScreen(0, 225, "Erasing flash. . .", CENTER_MODE, LCD_COLOR_WHITE,LCD_COLOR_BLACK,Text_Small);

			//Erase blocks in flash
			Flash_Erase_Blocks(200);
			image_Count = 0;
		}
	}
	/* =================================================
	 * if flash image count is less than the total number
	 * image required on the unit and equal to zero
	 * ask if the user erase and update all or restart.
	 * ================================================*/
	else if((image_Count != Number_Of_Images) && (image_Count == 0))
	{
		TextToScreen(0, 255, "Restart, or erase and update all? ",CENTER_MODE, LCD_COLOR_WHITE, LCD_COLOR_BLACK, Text_Small);


		TextToScreen(BSP_LCD_X_Size-200,BSP_LCD_Y_Size-100," RESTART >", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);
		TextToScreen(BSP_LCD_X_Size-150,100,"ERASE >", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);

		//wait for response
		while((!Input_Flags.Button_1) && (!Input_Flags.Button_4))
		{
			IO_App_Read_Inputs();
		}

		if(Input_Flags.Button_1)
		{
			TextToScreen_SML (0, 225, "Erasing flash. . .                     ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);

			//Erase blocks in flash
			Flash_Erase_Blocks(200);
			Image_Browser(Images_Dir, image_Count);
			image_Count = 0;
		}
		else
		{
			/* Software reset */
			NVIC_SystemReset();
		}
	}

	/* =================================================
	 * if flash image count is equal to the total number
	 * image required on the unit and equal to zero no
	 * images are required.
	 * ================================================*/
	else
	{
		TextToScreen_SML (0, 195, "No images are required                 ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		TextToScreen_SML (0, 225, "Erasing flash. . .                     ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);

		//Erase blocks in flash
		Flash_Erase_Blocks(200);
		image_Count = 0;
		Wait_Response_than_Restart();
	}



	BSP_LCD_Clear(LCD_COLOR_BLACK);

	TextToScreen_SML (0, 255, "Updating Images!          ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);


	if(image_Count == Number_Of_Images)
	{
		TextToScreen_SML(0, 255, "Restart, or erase and update all? ", LCD_COLOR_WHITE, LCD_COLOR_BLACK);

		TextToScreen(1,30,"< RESTART", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);
		TextToScreen(360,30,"ERASE >", LEFT_MODE, LCD_COLOR_BLACK, LCD_COLOR_WHITE, Text_Large);

		//wait for response
		while((!Input_Flags.Button_1) && (!Input_Flags.Button_3))
		{
			IO_App_Read_Inputs();
		}

		if(Input_Flags.Button_1)
		{
			TextToScreen_SML (0, 255, "Erasing flash. . .                     ",LCD_COLOR_WHITE,LCD_COLOR_BLACK);

			//Erase blocks in flash
			Flash_Erase_Blocks(200);

			image_Count = 0;
		}
		else
		{
			/* Software reset */
			NVIC_SystemReset();
		}
		Image_Browser(Images_Dir, image_Count);

		TextToScreen(0, 255, "Press any key to restart the unit. ",CENTER_MODE, LCD_COLOR_WHITE, LCD_COLOR_BLACK, Text_Large);

		while((!Input_Flags.Button_1) && (!Input_Flags.Button_4))
		{
			IO_App_Read_Inputs();
		}

	}
	else
	{

	}
}

/**===============================================
 * @brief  explore disk content
 * @param  path: pointer to root path
 * @retval None
  ===============================================*/
bool Explore_Disk_Images(char* path)
{
	FRESULT res;
	FILINFO fno;
	FATFS mynewdiskFatFs;
	char *fn;

	fn = fno.fname;

	int i = 0;

	uint8_t String50[] = "       ";


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

/**===============================================
 * @brief  Browse Images on disk
 * @param  path: pointer to root path
 * @retval None
  ===============================================*/
uint8_t Image_Browser (char* path, uint8_t image_Count)
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

				for(int k = image_Count; k <= Number_Of_Images; k++)
				{
					//Convert image number to name
					Bin2BCD(k, Image_name, 3);

					//Make file name
					fn[0] = Image_name[0];
					fn[1] = Image_name[1];
					fn[2] = Image_name[2];

					sprintf(_image_Number, "Loading Image %d of %d     ", k,Number_Of_Images);
					TextToScreen_SML (300, 255,_image_Number,LCD_COLOR_WHITE,LCD_COLOR_BLACK);


					//Do image
					Store_Image(fn, k);
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

/**===============================================
 * @brief Store a image onto the flash and display
 * @param fileName: File name of image
 * @param imageNumber: Number of image to be display
 * @retval None
  ===============================================*/
void Store_Image(char *fileName, uint16_t imageNumber)
{

	char fileDir[50] = {0};

	//String operations to add directory to the file name
	strcpy(fileDir, Images_Dir);
	strcat(fileDir, "/");
	strcat(fileDir,fileName);

	//Open image file
	if(f_open(&file, fileDir, FA_OPEN_EXISTING | FA_READ) == FR_OK)
	{
		//Load image data into internal flash memory
		Image_to_Flash(imageNumber);
	}

	f_close(&file);
}


/**===============================================
 * @brief Store and Display BMP image
 * @param Address: Block in NOR Flash to save image to
 * @retval None
  ===============================================*/
void Image_to_Flash(uint16_t image_index)
{

	uint16_t i = 0, j = 0;
	uint16_t numOfReadBytes = 0;
	FRESULT res;
	uint16_t dataBuf[IMAGE_BUFFER_SIZE/2] = {0};

	uint32_t address = image[image_index].address;
	uint16_t WRcount = 0;

	int Total_Count = image[image_index].size/IMAGE_BUFFER_SIZE;
	char Feedback_buf[50] = {0};
	sprintf(Feedback_buf, "Number: %d Width: %d pixels Height: %d pixels)",image_index ,image[image_index].X_size , image[image_index].Y_size);
	TextToScreen(0, 100, Feedback_buf, CENTER_MODE, LCD_COLOR_WHITE, LCD_COLOR_BLACK, Text_Small);

	/* Bypass Bitmap header  - Bytes */
	res = f_lseek(&file, 0);			//66
	int count = 0;
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

			char Count_buf[50] = {0};

			for(i = 0 ; i < IMAGE_BUFFER_SIZE; i+= 2)
			{
				dataBuf[i/2] = ((uint16_t)Image_Buf[i+1] << 8) + ((uint16_t)Image_Buf[i]);
			}


			sprintf(Count_buf, "(%d / %d)", (int)((float)count/(float)Total_Count*100), 100);
			TextToScreen(0, 160, Count_buf, CENTER_MODE, LCD_COLOR_WHITE, LCD_COLOR_BLACK, Text_Small);

			count ++;
			S29GL01GS_WriteBuffer(&S29GL01GS, dataBuf, address, IMAGE_BUFFER_SIZE / 2);
			address += (IMAGE_BUFFER_SIZE); 	//NOR  note: * 2 was corrected
			j++;
			WRcount++;
		}
	}
}



