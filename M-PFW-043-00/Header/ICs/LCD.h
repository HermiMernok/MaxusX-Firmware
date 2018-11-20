/*=================================
LCD.h
Created on: 	20 November, 2018
Company: 		Mernok Elektronik
Author: 		H. du Plessis
==================================*/


/**
 ******************************************************************************
 * @file    stm32f769i_discovery_lcd.h
 * @author  MCD Application Team
 * @version V2.0.0
 * @date    30-December-2016
 * @brief   This file contains the common defines and functions prototypes for
 *          the stm32469i_discovery_lcd.c driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Include LCD component Driver */

/* Include OTM8009A LCD Driver IC driver code */
//#include "../Components/otm8009a/otm8009a.h"
/* Include ADV7533 HDMI Driver IC driver code */
//#include "../Components/adv7533/adv7533.h"

/* Include SDRAM Driver */
//#include "stm32f769i_discovery_sdram.h"
//#include "stm32f769i_discovery.h"

// === Includes ===
#include "Global_Variables.h"


#include <string.h> /* use of memset() */


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Include LCD component Driver */


#include <string.h> /* use of memset() */

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32F769I_DISCOVERY
 * @{
 */

/** @addtogroup STM32F769I_DISCOVERY_LCD
 * @{
 */

/** @defgroup STM32F769I_DISCOVERY_LCD_Exported_Constants STM32F769I DISCOVERY LCD Exported Constants
 * @{
 */
#define BSP_LCD_DMA2D_IRQHandler        DMA2D_IRQHandler
#define BSP_LCD_DSI_IRQHandler          DSI_IRQHandler
#define BSP_LCD_LTDC_IRQHandler         LTDC_IRQHandler
#define BSP_LCD_LTDC_ER_IRQHandler      LTDC_ER_IRQHandler

extern DSI_HandleTypeDef hdsi;


#define LCD_LayerCfgTypeDef    LTDC_LayerCfgTypeDef
/**
 * @brief  LCD FB_StartAddress
 */
// #define LCD_FB_START_ADDRESS       ((uint32_t)0xC0000000)

#define SRAM_ADDR					((uint32_t)0x64000000)
#define FRAMEBUFFER_SIZE  			((uint32_t)0x00200000) // The size of data stored in SRAM 02457600
#define LCD_FRAMEBUFFER1_ADDR         (SRAM_ADDR) //This is the start address of FMC_NORSRAM_BANK2 --> SRAM
#define LCD_FRAMEBUFFER2_ADDR         (SRAM_ADDR+FRAMEBUFFER_SIZE) //This is the start address of FMC_NORSRAM_BANK2 --> SRAM

enum framebuffer
{
	FRAMEBUFFER1,
	FRAMEBUFFER2
};

/** @brief Maximum number of LTDC layers
 */
#define LTDC_MAX_LAYER_NUMBER             ((uint32_t) 2)

/** @brief LTDC Background layer index
 */
#define LTDC_ACTIVE_LAYER_BACKGROUND      ((uint32_t) 0)

/** @brief LTDC Foreground layer index
 */
#define LTDC_ACTIVE_LAYER_FOREGROUND      ((uint32_t) 1)

/** @brief Number of LTDC layers
 */
#define LTDC_NB_OF_LAYERS                 ((uint32_t) 2)

/** @brief LTDC Default used layer index
 */
#define LTDC_DEFAULT_ACTIVE_LAYER         LTDC_ACTIVE_LAYER_FOREGROUND

/**
 * @brief  LCD status structure definition
 */

/** @brief Blue value in ARGB8888 format
 */
#define LCD_COLOR_BLUE          ((uint32_t) 0xFF0000FF)

/** @brief Green value in ARGB8888 format
 */
#define LCD_COLOR_GREEN         ((uint32_t) 0xFF00FF00)

/** @brief Red value in ARGB8888 format
 */
#define LCD_COLOR_RED           ((uint32_t) 0xFFFF0000)

/** @brief Cyan value in ARGB8888 format
 */
#define LCD_COLOR_CYAN          ((uint32_t) 0xFF00FFFF)

/** @brief Magenta value in ARGB8888 format
 */
#define LCD_COLOR_MAGENTA       ((uint32_t) 0xFFFF00FF)

/** @brief Yellow value in ARGB8888 format
 */
#define LCD_COLOR_YELLOW        ((uint32_t) 0xFFFFFF00)

/** @brief Light Blue value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTBLUE     ((uint32_t) 0xFF8080FF)

/** @brief Light Green value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTGREEN    ((uint32_t) 0xFF80FF80)

/** @brief Light Red value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTRED      ((uint32_t) 0xFFFF8080)

/** @brief Light Cyan value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTCYAN     ((uint32_t) 0xFF80FFFF)

/** @brief Light Magenta value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTMAGENTA  ((uint32_t) 0xFFFF80FF)

/** @brief Light Yellow value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTYELLOW   ((uint32_t) 0xFFFFFF80)

/** @brief Dark Blue value in ARGB8888 format
 */
#define LCD_COLOR_DARKBLUE      ((uint32_t) 0xFF000080)

/** @brief Light Dark Green value in ARGB8888 format
 */
#define LCD_COLOR_DARKGREEN     ((uint32_t) 0xFF008000)

/** @brief Light Dark Red value in ARGB8888 format
 */
#define LCD_COLOR_DARKRED       ((uint32_t) 0xFF800000)

/** @brief Dark Cyan value in ARGB8888 format
 */
#define LCD_COLOR_DARKCYAN      ((uint32_t) 0xFF008080)

/** @brief Dark Magenta value in ARGB8888 format
 */
#define LCD_COLOR_DARKMAGENTA   ((uint32_t) 0xFF800080)

/** @brief Dark Yellow value in ARGB8888 format
 */
#define LCD_COLOR_DARKYELLOW    ((uint32_t) 0xFF808000)

/** @brief White value in ARGB8888 format
 */
#define LCD_COLOR_WHITE         ((uint32_t) 0xFFFFFFFF)

/** @brief Light Gray value in ARGB8888 format
 */
#define LCD_COLOR_LIGHTGRAY     ((uint32_t) 0xFFD3D3D3)

/** @brief Gray value in ARGB8888 format
 */
#define LCD_COLOR_GRAY          ((uint32_t) 0xFF808080)

/** @brief Dark Gray value in ARGB8888 format
 */
#define LCD_COLOR_DARKGRAY      ((uint32_t) 0xFF404040)

/** @brief Black value in ARGB8888 format
 */
#define LCD_COLOR_BLACK         ((uint32_t) 0xFF000000)

/** @brief Brown value in ARGB8888 format
 */
#define LCD_COLOR_BROWN         ((uint32_t) 0xFFA52A2A)

/** @brief Orange value in ARGB8888 format
 */
#define LCD_COLOR_ORANGE        ((uint32_t) 0xFFFFA500)

/** @brief Transparent value in ARGB8888 format
 */
#define LCD_COLOR_TRANSPARENT   ((uint32_t) 0xFF000000)

/**
 * @brief LCD default font
 */
#define LCD_DEFAULT_FONT        Font24

#define RGBConvert(red, green, blue)    (GFX_COLOR) ((((GFX_COLOR)(red) & 0xF8) << 8) | (((GFX_COLOR)(green) & 0xFC) << 3) | ((GFX_COLOR)(blue) >> 3))

#define LCD_YELLOW          RGBConvert(255, 255, 128)
#define LCD_BLACK           RGBConvert(0, 0, 0)
#define LCD_BRIGHTBLUE      RGBConvert(0, 0, 255)
#define LCD_BRIGHTGREEN     RGBConvert(0, 255, 0)
#define LCD_BRIGHTCYAN      RGBConvert(0, 255, 255)
#define LCD_BRIGHTRED       RGBConvert(255, 0, 0)
#define LCD_BRIGHTMAGENTA   RGBConvert(255, 0, 255)
#define LCD_YELLOW          RGBConvert(255, 255, 128)
#define LCD_BRIGHTYELLOW    RGBConvert(255, 255, 0)
#define LCD_LIGHTYELLOW     RGBConvert(255, 255, 150)
#define LCD_GOLD            RGBConvert(255, 215, 0)
#define LCD_BLUE            RGBConvert(0, 0, 128)
#define LCD_GREEN           RGBConvert(0, 128, 0)
#define LCD_CYAN            RGBConvert(0, 128, 128)
#define LCD_RED             RGBConvert(128, 0, 0)
#define LCD_MAGENTA         RGBConvert(128, 0, 128)
#define LCD_BROWN           RGBConvert(255, 128, 0)
#define LCD_LIGHTGRAY       RGBConvert(128, 128, 128)
#define LCD_DARKGRAY        RGBConvert(64, 64, 64)
#define LCD_LIGHTBLUE       RGBConvert(128, 128, 255)
#define LCD_LIGHTGREEN      RGBConvert(128, 255, 128)
#define LCD_LIGHTCYAN       RGBConvert(128, 255, 255)
#define LCD_LIGHTRED        RGBConvert(255, 128, 128)
#define LCD_LIGHTMAGENTA    RGBConvert(255, 128, 255)
#define LCD_WHITE           RGBConvert(255, 255, 255)
#define LCD_SADDLEBROWN 	RGBConvert(139, 69, 19)
#define LCD_SIENNA      	RGBConvert(160, 82, 45)
#define LCD_PERU        	RGBConvert(205, 133, 63)
#define LCD_BURLYWOOD  	 	RGBConvert(222, 184, 135)
#define LCD_WHEAT       	RGBConvert(245, 245, 220)
#define LCD_TAN         	RGBConvert(210, 180, 140)
#define LCD_ORANGE         	RGBConvert(255, 187, 76)
#define LCD_DARKORANGE      RGBConvert(255, 140, 0)
#define LCD_LIGHTORANGE     RGBConvert(255, 200, 0)
#define LCD_GRAY242      	RGBConvert(242, 242, 242)
#define LCD_GRAY229      	RGBConvert(229, 229, 229)
#define LCD_GRAY224         RGBConvert(224, 224, 224)
#define LCD_GRAY204      	RGBConvert(204, 204, 204)
#define LCD_GRAY192         RGBConvert(192, 192, 192)
#define LCD_GRAY160         RGBConvert(160, 160, 160)
#define LCD_GRAY128         RGBConvert(128, 128, 128)
#define LCD_GRAY096         RGBConvert(96, 96, 96)
#define LCD_GRAY032         RGBConvert(32, 32, 32)
#define LCD_GRAY010         RGBConvert(10, 10, 10)
typedef unsigned short int GFX_COLOR;


//#define LcdClock   27429 /*!< LcdClk = 27429 kHz */
#define LcdClock   27429 /*!< LcdClk = 27429 kHz */
#define laneByteClk_kHz  62500 /* 500 MHz / 8 = 62.5 MHz = 62500 kHz */
/**
 *  @brief  Possible values of
 *  pixel data format (ie color coding) transmitted on DSI Data lane in DSI packets
 */

#define   LCD_DSI_PIXEL_DATA_FMT_RBG888  DSI_RGB888 /*!< DSI packet pixel format chosen is RGB888 : 24 bpp */
#define   LCD_DSI_PIXEL_DATA_FMT_RBG565  DSI_RGB565 /*!< DSI packet pixel format chosen is RGB565 : 16 bpp */
#define   LCD_DSI_PIXEL_DATA_FMT_RBG666 DSI_RGB666 /*!< DSI packet pixel format chosen is RGB666 : 18 bpp */
/**
 * @}
 */

/** @defgroup STM32F769I_DISCOVERY_LCD_Exported_Types STM32F769I DISCOVERY LCD Exported Types
 * @{
 *
 */

/**
 * @brief  LCD Drawing main properties
 */
typedef struct
{
	uint32_t TextColor; /*!< Specifies the color of text */
	uint32_t BackColor; /*!< Specifies the background color below the text */
	sFONT    *pFont;    /*!< Specifies the font used for the text */

} LCD_DrawPropTypeDef;

/**
 * @brief  LCD Drawing point (pixel) geometric definition
 */
typedef struct
{
	int16_t X; /*!< geometric X position of drawing */
	int16_t Y; /*!< geometric Y position of drawing */

} Point;

/**
 * @brief  Pointer on LCD Drawing point (pixel) geometric definition
 */
typedef Point * pPoint;

/**
 * @brief  LCD drawing Line alignment mode definitions
 */
typedef enum
{
	CENTER_MODE             = 0x01,    /*!< Center mode */
	RIGHT_MODE              = 0x02,    /*!< Right mode  */
	LEFT_MODE               = 0x03     /*!< Left mode   */

} Text_AlignModeTypdef;

uint32_t BSP_LCD_X_Size;
uint32_t BSP_LCD_Y_Size;


uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);
void     BSP_LCD_SetXSize(uint32_t imageWidthPixels);
void     BSP_LCD_SetYSize(uint32_t imageHeightPixels);

void     BSP_LCD_LayerDefaultInit(uint16_t LayerIndex, uint32_t FB_Address);
void     BSP_LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency);
void     BSP_LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address);
void     BSP_LCD_SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue);
void     BSP_LCD_ResetColorKeying(uint32_t LayerIndex);
void     BSP_LCD_SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

void     BSP_LCD_SelectLayer(uint32_t LayerIndex);
void     BSP_LCD_SetLayerVisible(uint32_t LayerIndex, FunctionalState State);
bool 	 BSP_LCD_ValidateBitmap(uint32_t Width, uint32_t Height, uint8_t *pbmp);
void     BSP_LCD_SetTextColor(uint32_t Color);
uint32_t BSP_LCD_GetTextColor(void);
void     BSP_LCD_SetBackColor(uint32_t Color);
uint32_t BSP_LCD_GetBackColor(void);
void     BSP_LCD_SetFont(sFONT *fonts);
sFONT    *BSP_LCD_GetFont(void);
void App_printImg(uint32_t x, uint32_t y, uint16_t Index);

uint32_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos);
void     BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t pixel);
void     BSP_LCD_Clear(uint32_t Color);
void     BSP_LCD_ClearStringLine(uint32_t Line);
void     BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
void     BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode);
void     BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

void     BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void     BSP_LCD_DrawBitmap(uint32_t Xpos, uint32_t Ypos,  uint8_t* pbmp);

void     BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

void 	  BSP_LCD_DrawBitmap_NoHeader(uint32_t Xpos, uint32_t Ypos, uint32_t *pbmp,uint32_t width,uint32_t height);
void     BSP_LCD_DisplayOn(void);
void     BSP_LCD_DisplayOff(void);
void     BSP_LCD_SetBrightness(uint8_t BrightnessValue);
uint8_t  BSP_LCD_ActiveLayer();


/* @brief DMA2D handle variable */
extern DMA2D_HandleTypeDef hdma2d_discovery;

#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
