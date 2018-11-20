/*VMS_USB.h
 *Created on: Oct 11, 2013
 *Company: Mernok Elektronik
 *Author: J.C. Els
*/

#ifndef USB_H_
#define USB_H_
//Includes
#include "Global_Variables.h"

//Defines
#define	Images_Dir			"0:/MaxusX/Resources"
#define	Log_Dir				"0:/MaxusX/DataLog"
#define	Log_Root			"0:"
#define	Log_Params			"0:/MaxusX/Parameters"

#define Flash_block_Start_EV_logs	NOR_BLOCK_250

//Lcd text for USB
#define USB_Normal_Colour	WHITE
#define USB_ERROR_Colour	BRIGHTRED
#define USB_OK_Colour		BRIGHTGREEN

#define Clear_Line                "                                       "
#define LCD_USB_Message_1         "USB OTG Machine initiated              "

#define LCD_USB_Message_2         "No disk detected, please insert disk   "
#define LCD_USB_Message_3         "Disk detected                          "

#define LCD_USB_Message_4         "High speed device                      "
#define LCD_USB_Message_5         "Full speed device                      "
#define LCD_USB_Message_6         "Low speed device                       "
#define LCD_USB_Message_7         "Device Speed Error!!                   "


#define LCD_USB_Message_8         "Device Enumeration Complete            "

#define LCD_USB_Message_9         "FAT File system initialised            "
#define LCD_USB_Message_10        "USB ERROR - Initialise FAT System      "
#define LCD_USB_Message_11        "USB ERROR - Disk Write Protected       "

#define LCD_USB_Message_12        "Checking images on disk, DON'T "
#define LCD_USB_Message_13        "REMOVE USB Disk, please wait!! "

#define LCD_USB_Message_14        "Images not found, please check disk!!! "

#define LCD_USB_Message_15        "Images found, updating active, DO NOT  "
#define LCD_USB_Message_16        "remove flash disk until prompted       "
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


//Variables made public
typedef enum
{
	Read 	= 0,
	Write	= 1
}USB_Operation_TypeDef;

//Functions made public
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
