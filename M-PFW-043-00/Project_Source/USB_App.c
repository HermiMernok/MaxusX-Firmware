/*
 * USB_App.c
 *
 *  Created on: 26 May 2018
 *      Author: NeilPretorius
 */
#include "USB_App.h"

extern USBH_HandleTypeDef hUsbHostFS;
FLASH_EraseInitTypeDef STM32FLASH;


/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
static uint8_t RAM_Buf[BUFFER_SIZE] =
{
		0x00
};
static uint32_t TmpProgramCounter = 0x00, TmpReadSize = 0x00 , RamAddress = 0x00 , FileCount = 0x00, FilePercent = 0x00, TempCounter = 0x00;
static uint32_t LastPGAddress = APPLICATION_ADDRESS;
static uint16_t Progress_Bar_Ptr = 0x00;

FRESULT res;

FIL fileR;
FILINFO fno;
DIR dir;
FATFS mynewdiskFatFs;
char *fn;

void Jump_to_application()
{
	Adress_p = 0;
	Adress_p = (*(__IO uint32_t*)APPLICATION_ADDRESS);

	if (Application_Sanity_Check(Status_Address))
	{
		HAL_FLASH_Lock();
		USBH_Stop(&hUsbHostFS);
		USBH_DeInit(&hUsbHostFS);
		//Jump to user application
		JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
		Jump_To_Application = (pFunction) JumpAddress;

		//Initialize user application's Stack Pointer
		__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
		Jump_To_Application();
	}
}

void UpdateBootloader(void)
{
	MX_Flash_Init();
	bool FileOK = false;
	bool DeviceOK = false;

	int FileName[45] = {0};

	int i = 0;

	//			newVersion = 0;

	const TCHAR* mynewdiskPath = "0:/";
	res = f_mount(&mynewdiskFatFs, (TCHAR const*)mynewdiskPath, 0);
	res = f_opendir(&dir,"0:/");
	if (res == FR_OK)
	{
		DeviceOK = true;

		while(hUsbHostFS.device.is_connected == 1)	//check usb connection here
		{
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0)
			{
				break;
			}

			fn = fno.fname;

			/*MAXUS X hand-held Application Firmware File*/

			if ((strstr(fn,".txt") != NULL))		//look in the file name if it is a binary file
			{
				for (i = 0; i < 25; i++)
				{
					FileName[i] = (uint8_t) fn[i];
				}

				FileOK = FileName_Check(FileName);
				break;
			}
			else
			{
				/*No valid file detected*/
				FileOK = false;
			}
		}

		//Handle invalid files here
		if (!FileOK)
		{
			while(hUsbHostFS.device.is_connected == 1)
			{
				//No valid file on flash drive, please remove flash drive
				BootStatus = USB_File_error;
			}

			//Reset system after USB has been removed
			NVIC_SystemReset();
		}
		else
		{
			char actual_file_name[50] = {0};
			strcpy(actual_file_name, "0:");
			strncat(actual_file_name, (char*)&fn[0], 48);

			/* Open the binary file to be downloaded */
			if (f_open(&fileR, actual_file_name, FA_READ) == FR_OK)
			{

//				while (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13))
//				{
//					NVIC_SystemReset();
//				}

				if (fno.fsize > USER_FLASH_SIZE)
				{
					/* Toggle Red LED in infinite loop: No available Flash memory size for
								 the binary file */
					while(hUsbHostFS.device.is_connected == 1)
					{
						//Stay here until flash drive is removed
						BootStatus = Memory_too_small;
					}
					NVIC_SystemReset();
				}
				else
				{

					uint32_t erase_error = 0;
					/* Erase Flash Memory */

					HAL_FLASH_Unlock();
					BootStatus = Memory_busy_erasing;

					HAL_FLASHEx_Erase(&STM32FLASH, &erase_error);
					//Check for erase errors
					if(erase_error != 0xFFFFFFFF)
					{
						while(hUsbHostFS.device.is_connected == 1)
						{
							//Stay here until flash drive is removed
							BootStatus = Memory_erase_error;
						}
						//Reset system
						NVIC_SystemReset();
					}

					if(hUsbHostFS.device.is_connected == 1)
					{
						BootStatus = Memory_done_erasing;
						ProgramFlashMemory();
					}
					else
					{
						BootStatus = USB_Error_during_Flash_program;
						DeviceOK = false;
					}
				}
			}
			else
			{
				while(hUsbHostFS.device.is_connected == 1)
				{
					//The file has a valid name, but is corrupted and cannot be accessed
					BootStatus = USB_File_error;
				}
				//Reset system after USB has been removed
				NVIC_SystemReset();
			}

		}
	}
	else
	{
		if(!DeviceOK)
		{
			while(hUsbHostFS.device.is_connected == 1)
			{
				//Invalid directory or faulty USB device
				BootStatus = USB_Error;
			}
		}
		//Reset system after USB has been removed
		NVIC_SystemReset();
	}

	//Reset system after programming is completed
	while(hUsbHostFS.device.is_connected == 1)
	{
		int temp = temp +1;
		BootStatus = Bootloading_done;
	}

	NVIC_SystemReset();
	i++;
}

bool FileName_Check(int FileName[45])
{
	bool FileNameOk = false;
	char NewApplication[3] = {0};
	uint16_t App_Detected = 0;

	char NewVersion[3] = {0};
	uint16_t Ver_Detected = 0;
	char NewSubVersion[3] = {0};
	uint16_t SubVer_Detected = 0;

	//Load application number into array
	NewApplication[0] = FileName[6];
	NewApplication[1] = FileName[7];
	NewApplication[2] = FileName[8];

	//convert string to decimal
	App_Detected = atoi(NewApplication);

	//determine firmware version size
	if(FileName[12] != '-')  					//Check if firmware version is more than 99
	{
		NewVersion[0] = FileName[10];
		NewVersion[1] = FileName[11];
		NewVersion[2] = FileName[12];
	}
	else
	{
		NewVersion[0] = '0';
		NewVersion[1] = FileName[10];
		NewVersion[2] = FileName[11];
	}

	//convert string to decimal
	Ver_Detected = atoi(NewVersion);

	//Check if firmware revision size shifted the subversion position
	if(Ver_Detected < 100)
	{
		//determine firmware subversion size
		if(FileName[15] != '.')  					//Check if firmware subversion is more than 99
		{
			NewSubVersion[0] = FileName[13];
			NewSubVersion[1] = FileName[14];
			NewSubVersion[2] = FileName[15];
		}
		else
		{
			NewSubVersion[0] = '0';
			NewSubVersion[1] = FileName[13];
			NewSubVersion[2] = FileName[14];
		}
	}
	else
	{
		//determine firmware subversion size
		if(FileName[16] != '.')  					//Check if firmware subversion is more than 99
		{
			NewSubVersion[0] = FileName[14];
			NewSubVersion[1] = FileName[15];
			NewSubVersion[2] = FileName[16];
		}
		else
		{
			NewSubVersion[0] = '0';
			NewSubVersion[1] = FileName[15];
			NewSubVersion[2] = FileName[16];
		}
	}

	//convert string to decimal
	SubVer_Detected = atoi(NewSubVersion);

	//Do a quick out of bounds check on firmware version and subversion
	if((Ver_Detected > 999) || (SubVer_Detected > 999))
	{
		FileNameOk = false;
		BootStatus = USB_File_error;
	}

	//Load correct application name to be displayed
	switch(App_Detected)
	{

	case MaxusX_Firmware:

		FileNameOk = true;
		BootStatus = USB_File_OK;
		break;

	default:

		FileNameOk = false;
		break;

	}

	return FileNameOk;

}

void MX_Flash_Init(void)
{
	STM32FLASH.VoltageRange = VOLTAGE_RANGE_3; //Votage range between 2.7 and 3.6 V
	STM32FLASH.TypeErase = FLASH_TYPEERASE_SECTORS;//FLASH_TYPEERASE_MASSERASE
	STM32FLASH.Banks = FLASH_BANK_1; //Single bank
	STM32FLASH.Sector = FLASH_SECTOR_4; //Starting sector to erase
	STM32FLASH.NbSectors = FLASH_SECTOR_11 - FLASH_SECTOR_5; // diiference between last sector and starting sector addresses.
}

void ProgramFlashMemory(void)
{
	__IO uint32_t programcounter = 0x00;
	uint8_t readflag = TRUE;
	uint16_t BytesRead;

	BootStatus = Busy_Programming_memory;
	/* Program flash memory */
	RamAddress = (uint32_t) & RAM_Buf;

	/* Erase address init */
	LastPGAddress = APPLICATION_ADDRESS;

	/* Set Progress Bar Pointers */
	Progress_Bar_Ptr = Progress_Bar_Ptr + 150;
	TempCounter = 1;
	FileCount = 0;
	FilePercent = 0;

	while (readflag == TRUE)
	{
		/* Read maximum 512 Kbyte from the selected file */
		res = f_read (&fileR, (void *)&RAM_Buf, BUFFER_SIZE, (UINT *)&BytesRead);
		Writing_file_Flash = true;

		/* Progress bar */
		FilePercent = (FileCount * 100) / fno.fsize;

		/* Increment number of bytes read */
		FileCount = FileCount + BytesRead;

		/* Temp variable */
		TmpReadSize = BytesRead;

		/* The read data < "BUFFER_SIZE" Kbyte */
		if (TmpReadSize < BUFFER_SIZE)
		{
			readflag = FALSE;
		}

		/* Program flash memory */
		HAL_FLASH_Unlock();
		for (programcounter = TmpReadSize; programcounter != 0; programcounter -= 1)
		{
			TmpProgramCounter = programcounter;
			/* Write word into flash memory */
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,(LastPGAddress - TmpProgramCounter + TmpReadSize), *(__IO uint32_t *)(RamAddress - programcounter + TmpReadSize));
		}

		/* Update last programmed address value */
		LastPGAddress = LastPGAddress + TmpReadSize;
	}

	//Save sanity value if image successfully loaded
	if(FileCount  == fno.fsize)
	{
		//Update sanity value to indicate update was successful
		HAL_FLASH_Unlock();
		Write_Application_Sanity(Status_Address,0x55);
	}
	/* Close file and filesystem */
	Application_Sanity_Check(Status_Address);
	f_close (&fileR);

}

//Function that will update value to Application OK
void Write_Application_Sanity(uint32_t Address, uint8_t Value)
{
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, Address, Value);
}

bool Application_Sanity_Check(uint32_t Address)
{
	uint32_t Temp_value = 0;
	//	Step1 - read address value
	Temp_value = *(uint8_t*)Address;

	//	Step2 - Determine Status
	if(Temp_value == 0x55)
		return true;
	else
		return false;

}

