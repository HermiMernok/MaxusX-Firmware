/*
 * Home.c
 *
 *  Created on: Jan 23, 2015
 *      Author: Jaco Olivier
 */


#include "App_Text.h"

/**
 * @brief  Writes a string to the LCD
 * @param  x: 			X position
 * @param  y: 			Y position
 * @param  textString: 	Text data
 * @param  Mode:		Text printing mode, can be variables of Text_AlignModeTypdef
 * @param  FColor:		Text Color
 * @param  BColor: 		Background Color
 * @param  Size: 		Size of text
 * @retval RGB pixel color
 */
void TextToScreen(int x, int y, char *textString ,uint8_t Mode, uint32_t FColor, uint32_t BColor, Text_SizeTypdef Size)
{
	BSP_LCD_SetBackColor(BColor);
	BSP_LCD_SetTextColor(FColor);

	switch(Size)
	{
	case Text_Extra_Small:

		BSP_LCD_SetFont(&Font12);
		break;

	case Text_Small:

		BSP_LCD_SetFont(&Font16);
		break;

	case Text_Medium:

		BSP_LCD_SetFont(&Font20);
		break;

	case Text_Large:

		BSP_LCD_SetFont(&Font24);
		break;

	default:
		break;
	}


	BSP_LCD_DisplayStringAt(x, y, textString, LEFT_MODE);
}

void TextToScreen_SML(int x, int y, char *textString, uint32_t FColor, uint32_t BColor)
{
	BSP_LCD_SetBackColor(BColor);
	BSP_LCD_SetTextColor(FColor);
	BSP_LCD_SetFont(&Font16);

	BSP_LCD_DisplayStringAt(x, y, textString, LEFT_MODE);
}

void TextToScreen_MED(int x, int y, char *textString, uint32_t FColor, uint32_t BColor)
{
	BSP_LCD_SetBackColor(BColor);
	BSP_LCD_SetTextColor(FColor);
	BSP_LCD_SetFont(&Font20);

	BSP_LCD_DisplayStringAt(x, y, textString, LEFT_MODE);
}

void TextToScreen_LRG(int x, int y, char *textString, uint32_t FColor, uint32_t BColor)
{
	BSP_LCD_SetBackColor(BColor);
	BSP_LCD_SetTextColor(FColor);
	BSP_LCD_SetFont(&Font24);

	BSP_LCD_DisplayStringAt(x, y, textString, LEFT_MODE);
}



