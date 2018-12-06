/*
 * USB.c
 *
 *  Created on: 20 November, 2018
 *      Author: Hermi du Plessis
 */


#ifndef USB_H_
#define USB_H_

//=== Includes ===

#include "Global_Variables.h"

//=== Defines ===
#define	Images_Dir			"0:/MaxusX/Resources"
#define	Log_Dir				"0:/MaxusX/DataLog"
#define	Log_Root			"0:"
#define	Log_Params			"0:/MaxusX/Parameters"

#define Flash_block_Start_EV_logs	NOR_BLOCK_250


// === USB Status Message ==
#define USB_CLEAR_LINE               "                                       "

#define USB_STATUS_MESSAGE_1         "USB OTG initiated                      "
#define USB_STATUS_MESSAGE_2         "Device Enumeration Complete            "
#define USB_STATUS_MESSAGE_3         "Disk detected                          "
#define USB_STATUS_MESSAGE_4		 "USB Device Disconnected                "

#define USB_SPEED_MESSAGE_1          "High speed device                      "
#define USB_SPEED_MESSAGE_2          "Full speed device                      "
#define USB_SPEED_MESSAGE_3          "Low speed device                       "
#define USB_SPEED_MESSAGE_4          "Device Speed Error!!                   "

#define USB_ERROR_MESSAGE_1			 "Device Not Supported                   "
#define USB_ERROR_MESSAGE_2			 "FAT File system initialised            "
#define USB_ERROR_MESSAGE_3			 "USB ERROR - Initialise FAT System      "
#define USB_ERROR_MESSAGE_4			 "USB ERROR - Disk Write Protected       "
#define USB_ERROR_MESSAGE_5			 "USB ERROR                              "




#define USB_ERROR_MESSAGE_7 	"USB OTG non-recovered error            "
#define USB_ERROR_MESSAGE_8 	"No disk detected, please insert disk   "


#define LCD_USB_Message_13        "Checking images on disk, DON'T "
#define LCD_USB_Message_14        "REMOVE USB Disk, please wait!! "

#define LCD_USB_Message_15        "Images not found, please check disk!!! "

#define LCD_USB_Message_16        "Images found, updating active, DO NOT  "
#define LCD_USB_Message_17        "remove flash disk until prompted       "
#define LCD_USB_Message_18        "Erasing flash....                      "

#define LCD_USB_Message_19        "Total images to be updated:            "
#define LCD_USB_Message_20        "Currently updating image:              "

#define LCD_USB_Message_21        "Image update complete. Press accept to "
#define LCD_USB_Message_22        "restart the system....                 "

#define LCD_USB_Message_23        "Parameter file not found or file not in"
#define LCD_USB_Message_24        "correct directory, check disk!!        "

#define LCD_USB_Message_25        "Parameter file downloaded successfully "
#define LCD_USB_Message_26        "Please remove USB disk!!               "

#define LCD_USB_Message_27        "Parameter file corrupt!!               "

#define LCD_USB_Message_28        "Datalog file transfer started          "
#define LCD_USB_Message_29        "Please DO NOT remove USB disk!!        "

#define LCD_USB_Message_30        "Data log file uploaded successfully    "
#define LCD_USB_Message_31        "Please remove USB disk!!               "

#define LCD_USB_Message_32        "Data log file upload failed            "
#define LCD_USB_Message_33        "Please remove USB disk!!               "


//=== Public Variables ===
typedef enum
{
	Read 	= 0,
	Write	= 1
}USB_Operation_TypeDef;

//=== Public Functions ===
void Main_USB_Handler(void);
void USB_Screen_Init(void);
void USB_Core_Init(void);
void USB_Core_New_Device(void);
void USB_Core_Unrecovered_Error(void);
void USB_Core_Disconnected(void);
void USB_Core_Reset(void);
void USB_Core_Enum_Done(void);
void USB_Core_Unsupported_Device(void);
void USB_Core_Speed_Detected(uint8_t DeviceSpeed);
void USB_Core_Waiting(void);
void USB_Core_FAT_Error(void);
void USB_Core_FAT_Disk_Protected(void);
void USB_Core_FAT_OK(void);
void USB_User_File_Reader(void);
void USB_User_File_Explorer(void);
void USB_User_File_Writer(void);
void App_USB_SM(void);
void User_DataLog_Extraction_USB(void);
void User_Parameter_Upload_USB(void);
void User_Parameter_Extraction_USB(void);
void USB_Param_Parse(uint8_t Source_Bytes[]);

#endif /* USB_H_ */
