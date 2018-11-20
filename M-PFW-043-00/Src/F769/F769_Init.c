/*
 * F769_Init.c
 *
 *  Created on: 01 Sep 2018
 *      Author: NeilPretorius
 */

#include "F769_Init.h"

void Init_769(void)
{
	/* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();



	/*==============================
	 *Start up delay
	 *-=============================-*/
	HAL_Delay(100);

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */

	MX_GPIO_Init();

	UART_Init(COM_EXP1, 115200);


	//UART_Init(COM_EXP4,115200);

	//UART_Init(COM_External,115200);

	//=== Board support package (BSP) setup ===
	MX_FMC_Init();
	DMA_Init ();


	MX_CAN1_Init();
	MX_CAN2_Init();
	MX_I2C2_Init();
	MX_SPI2_Init();
	MX_SPI5_Init();

	MX_TIM3_Init();
	MX_TIM5_Init(10);


	UART_Init(COM_EXP2,115200);
	DMA_Init();

	/****************************************************************/
	//Initialise USB-OTG
	/****************************************************************/
	MX_USB_HOST_Init();
	MX_FATFS_Init();

	/*==============================
	 *Ethernet LWIP Setup
	 *-=============================-*/
	//MX_LWIP_Init();


	//MX_LWIP_Init();
	MCP23S17_CS_Init();

	//=== FMC Initialise ===


}


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_USART1
			|RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_USART6
			|RCC_PERIPHCLK_UART4|RCC_PERIPHCLK_UART5
			|RCC_PERIPHCLK_UART8|RCC_PERIPHCLK_I2C2
			|RCC_PERIPHCLK_CLK48;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 394;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 7;
	PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
	PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
	PeriphClkInitStruct.PLLSAIDivQ = 1;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
	PeriphClkInitStruct.Uart8ClockSelection = RCC_UART8CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
