
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "lwip.h"
#include "tcp_echoclient.h"
#include "Global_Variables.h"

//#include "049.h"

//struct netif gnetif;
/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern ApplicationTypeDef Appli_state;


/* System variables------------------------------------------------------------*/
uint8_t HW_Rev = 0;
#include "iwdg.h"

/* Private function prototypes -----------------------------------------------*/
void MX_USB_HOST_Process(void);
static void Netif_Config(void);
extern vision_device Pulse400_Module;

uint32_t Color_Wheel_Array[] =
{
		LCD_COLOR_DARKRED,		//0 *
		LCD_COLOR_RED,			//1
		LCD_COLOR_LIGHTRED,     //2 *
		LCD_COLOR_ORANGE,       //3 *
		LCD_COLOR_DARKYELLOW,   //4 *
		LCD_COLOR_YELLOW,       //5
		LCD_COLOR_LIGHTYELLOW,  //6
		LCD_COLOR_DARKGREEN,    //7 *
		LCD_COLOR_GREEN,        //8
		LCD_COLOR_LIGHTGREEN,   //9
		LCD_COLOR_DARKCYAN,     //10 *
		LCD_COLOR_CYAN,         //11
		LCD_COLOR_LIGHTCYAN,    //12
		LCD_COLOR_DARKBLUE,     //13 *
		LCD_COLOR_BLUE,         //14
		LCD_COLOR_LIGHTBLUE,    //15 *
		LCD_COLOR_DARKMAGENTA,  //16 *
		LCD_COLOR_MAGENTA,      //17
		LCD_COLOR_LIGHTMAGENTA, //18 *
		LCD_COLOR_BLACK,        //19
		LCD_COLOR_DARKGRAY,     //20 *
		LCD_COLOR_LIGHTGRAY,    //21 *
		LCD_COLOR_WHITE,        //22


};

uint8_t Index = 0;
uint8_t Prev_value = 0;
void Color_Line_test()
{

	for(int i = 0 ; i < 9 ; i++)
	{
		BSP_LCD_SetTextColor(Color_Wheel_Array[Index]);
		BSP_LCD_FillRect(i*50,0,100,600);
		Index++;

		if(Index == 22)
		{
			Index = 0;
		}

	}

	Index = Index - 8;

	if(Index > 23)
	{
		Index = 22+Index;
	}
}



int main(void)
{
	Init_769();
	Application_Init();

	//
	//	uint8_t RxBuffer1[6400] = {0};
	//
	//	//S29GL01GS_ReadBuffer(&S29GL01GS, &RxBuffer1[0], NOR_BLOCK_0, 6400);
	//
	//	/* Configure the Network interface */
	//	//  Netif_Config();
	//	  /* Notify user about the network interface config */
	//	 // User_notification(&gnetif);
	//
	//
	//	//S29GL01GS_WriteBuffer_32bit(&S29GL01GS, &image_data_049[0], IMG_03_Addr			+      	 IMG_03_Size, 6400);
	//	//S29GL01GS_ReadBuffer(&S29GL01GS, &RxBuffer1[0], NOR_BLOCK_0, 6400);

	//Power CAN bus //Note State is swapped, true = off and false = on
	IO_Output_control(PWR_CAN2, false);

	//Init dummy DMA setup
	uint8_t Buffer[10] = {0};
	uint8_t Buffertx[6] = {'1','2','3','4','5','6'};

	DMA_UART_RF_RX(Buffer, 10);
	DMA_UART_RF_TX(Buffertx, 6);
	extern uint8_t RF_RX_OK;
	extern UART_HandleTypeDef huartx[COMn];
	uint8_t QSPI_BUFFER[1024] = {0};
	uint8_t QSPI_READBUFFER[1024] = {0};

	for(int i =0; i < 1024 ; i++)
	{
		QSPI_BUFFER[i] = i;
	}
	BSP_QSPI_Write(QSPI_BUFFER,0x077FFFF ,1024);
	BSP_QSPI_Read(QSPI_READBUFFER,0x077FFFF ,1024);
	BSP_QSPI_Erase_Block(0x0780000);

	BSP_QSPI_Read(QSPI_READBUFFER,0x077FFFF ,1024);
	uint8_t text_buffer[5] = {0};
	uint8_t feedback = BSP_QSPI_GetStatus();
	//sprintf(text_buffer, "%d", feedback);
	//TextToScreen_SML(100,0,text_buffer, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
//	while (1)
//	{
//		BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
//		BSP_LCD_FillRect(10,580,2,2);
//		__HAL_IWDG_RELOAD_COUNTER(&hiwdg); //Reload Watchdog -- Feed the dog
//
//		//TextToScreen_MED(10,10,"Light Sensor OK",LCD_COLOR_BLUE,LCD_COLOR_GRAY );
//		Delay(10);
////		Color_Line_test();
//
//
//		BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//
//			//	BSP_LCD_FillRect(924,50,100,50);
//
//		//TextToScreen_SML(10,10, "o", LCD_COLOR_BROWN,LCD_COLOR_BLACK);
//
//		uint8_t text_buffer[100];
//
////		for(int i =0 ; i <23 ; i++)
////		{
////			sprintf(text_buffer, "%d Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod", i);
////			TextToScreen_SML(10,i*24,text_buffer, Color_Wheel_Array[i], LCD_COLOR_BLACK);
////		}
//		//App_printImg(0,0, image[1].index);
//
////		uint8_t Data;
////		SN65DSI83_ReadRegs(&hi2c2, 0xE5, &Data, 1);
////
////		for(int i =0 ; i <23 ; i++)
////			{
////				sprintf(text_buffer, "%d Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod", i);
////
////				TextToScreen_SML(10,i*24,text_buffer, LCD_COLOR_WHITE, Color_Wheel_Array[i]);
////			}
//
//	}


	//Init_Ethernet();

//	while (1)
//	{
//
//
//		/*=================================
//		 * Read all Inputs
//		 *================================*/
//		IO_App_Read_Inputs();
//
//		/*=================================
//		 * Handle User Inputs
//		 *================================*/
//		App_ACK_Handler();
//		if(App_ACK_CheckFlag(ACK_Down))
//		{

//			tcp_echoclient_connect();
//
//		}
//		else
//		{
//
//		}
//
//		/*=================================
//		 *
//		 *================================*/
//		Ethernet_Handler();
App_printImg(0,0, IMG_BUTTON_UP);
BSP_LCD_Clear(LCD_COLOR_BLUE);
TextToScreen_SML(10,0,"Startup", LCD_COLOR_WHITE, LCD_COLOR_BLACK);
USB_Flags.Image_Update_Requested = true;
//	}
	while (1)
	{
		/*=================================
		 * Read all Inputs
		 *================================*/
		IO_App_Read_Inputs();

		/*=================================
		 * Handle User Inputs
		 *================================*/
		App_ACK_Handler();

		/*--------------------------------
		 * Process Vision Module Messages
		 *------------------------------*/
		App_VisionModules_Process();

		/*--------------------------------
		 * Manage and Control Events
		 *------------------------------*/
		App_EventControl();


		/*===============================
		 * USB Host Process
		 *==============================*/
		MX_USB_HOST_Process();


		/*--------------------------------
		 * Filter all tags seen over RF
		 *------------------------------*/
		System_Filter_Control();

		//if(Check_TX_done())
		//	{
		//		DMA_UART_RF_TX(Buffertx, 6);
		//	}

		/*=================================
		 * Update Display Time
		 *===============================*/
		Display_Time();

		/*=================================
		 * Adjust Brightness
		 *===============================*/
		LCD_Brightness_Control();


		// Process ICON3 CAN Messages
		Process_ICON3_messages();

		HUB_2XX_Handler();

		/*=================================
		 * Display Operational Information
		 *================================*/
		//	Operational_Debug(300);

		/*=================================
		 * Button Press example
		 *================================*/
		if(App_ACK_CheckFlag(ACK_Down))
		{

			// === use App_ACK_ButtonReleased to process button press ===
			//App_ACK_ButtonReleased (ACK_Up);
			IO_Output_control(Led_Key_B, true);
		}
		else
		{
			IO_Output_control(Led_Key_B, false);
		}

		/*================================
		 * USB Application Handler
		 *==============================*/
		App_USB_SM();

	}

}


/**
 * @brief  This function is executed in case of error occurrence.
 * @param  file: The file name as string.
 * @param  line: The line in file as a number.
 * @retval None
 */
void _Error_Handler(char *file, int line)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while(1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
