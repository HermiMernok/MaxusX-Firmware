/*
 * USB_App.h
 *
 *  Created on: 26 May 2018
 *      Author: NeilPretorius
 */

#ifndef USB_APP_H_
#define USB_APP_H_

#include <stdbool.h>
#include "Global_Variables.h"

#define BUFFER_SIZE        ((uint16_t)(512))



typedef  void (*pFunction)(void);

bool Application_Sanity_Check(uint32_t Address);
void Delete_Sanity_Value_sector(void);
void Write_Application_Sanity(uint32_t Address, uint8_t Value);

uint8_t BootStatus;
bool Writing_file_Flash;
uint8_t Persentage_to_flash;

/////////////BOOTLOADER DEFINES (FLASH) //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
pFunction Jump_To_Application;
uint32_t JumpAddress;
uint32_t Adress_p;


typedef  void (*pFunction)(void);
#define _DF1S 0

/* Define the flash memory start address */
#define USER_FLASH_STARTADDRESS    ((uint32_t)0x08000000) /* Flash Start Address */

/* End of the Flash address */
#define USER_FLASH_END_ADDRESS     	((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */

/* Define the user application size */
#define USER_FLASH_SIZE   			(USER_FLASH_END_ADDRESS - USER_FLASH_STARTADDRESS + 1)

/* Define the address from where user application will be loaded.
   Note: the 1st sector 0x08000000-0x08007FFF is reserved for the Firmware upgrade code */

#define APPLICATION_ADDRESS        ((uint32_t)0x08020000)

#define Status_Address 				((uint32_t)0x0807FFFF)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

enum
{

	MaxusX_Firmware		= 43,		//M-PFW-043-01-00


}DeviceApplication;

enum
{
	USB_stick_OK,
	USB_File_OK,
	USB_File_error,
	USB_Error,
	USB_Error_during_Flash_program,
	Memory_busy,
	Memory_busy_erasing,
	Memory_done_erasing,
	Memory_done,
	Memory_too_small,
	Memory_erase_error,
	Memory_error,
	Busy_Programming_memory,
	Waiting_for_USB,
	Bootloading_done,
}BootloadStatus;

void UpdateBootloader(void);

bool FileName_Check(int FileName[45]);

void ProgramFlashMemory(void);

void Jump_to_application(void);

void MX_Flash_Init(void);




#endif /* USB_APP_H_ */
