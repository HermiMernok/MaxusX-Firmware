/*=================================
F769_LCD.c
Created on: 	31 August, 2018
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

/*=== Define to prevent recursive inclusion ===*/
#ifndef __F769_LCD_H
#define __F769_LCD_H


//======================================
//============= Includes ===============
//======================================

#include "Global_Variables.h"
#include <string.h> /* use of memset() */
#include "USB_Image.h"
//======================================
//============= Defines ================
//======================================

#define  VSA   10  /*!< Vertical start active time in units of lines */
#define  VBP   70  /*!< Vertical Back Porch time in units of lines */
#define  VFP   70 /*!< Vertical Front Porch time in units of lines */
#define  HSA   100 /*!< Horizontal start active time in units of lcdClk */
#define  HBP   160 /*!< Horizontal Back Porch time in units of lcdClk */
#define  HFP   160  /*!< Horizontal Front Porch time in units of lcdClk */


//======================================
//============= Enums ==================
//======================================

// === Possible Display Orientations ===
 typedef enum
 {
   LCD_ORIENTATION_PORTRAIT  = 0x00, /*!< Portrait orientation choice of LCD screen  */
   LCD_ORIENTATION_LANDSCAPE = 0x01, /*!< Landscape orientation choice of LCD screen */
   LCD_ORIENTATION_INVALID   = 0x02  /*!< Invalid orientation choice of LCD screen   */
 } LCD_OrientationTypeDef;

// === LCD library state Typedef ===
 typedef enum
 {
	LCD_OK    =     0x00,
	LCD_ERROR  =    0x01,
	LCD_TIMEOUT =   0x02
 } LCD_StateTypeDef;

 //======================================
 //======== Public Functions ============
 //======================================

 uint8_t  LCD_Init(void);

 /* @brief DMA2D handle variable */
 extern DMA2D_HandleTypeDef hdma2d_discovery;

 #ifdef __cplusplus{
 }
 #endif

 #endif /* __F769_LCD_H */

 /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
