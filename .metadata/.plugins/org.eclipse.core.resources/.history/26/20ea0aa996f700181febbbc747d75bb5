/*VMS_USB_Image.h
 *Created on: Dec 5, 2012
 *Company: Mernok Elektronik
 *Author: S.D. Janse van Rensburg
*/

#ifndef USB_IMAGE_H_
#define USB_IMAGE_H_
//Includes
#include "Global_Variables.h"

//Defines
//Variables made public

//Functions made public
void Disk_Explorer(void);
void Update_Images_Now(void);


#define AM_MASK		0x3F	/* Mask of defined bits */

bool Explore_Disk_Images(char* path);
uint8_t Image_Browser (char* path, uint8_t Image_Count);
void Show_Image(uint16_t x, uint16_t y, uint16_t index);
void WriteFile(void);
void Do_Image(char *FileName, uint16_t imagenumber);
void Flash_Erase_Blocks (uint8_t Blocks);

#endif /* USB_IMAGE_H_ */
