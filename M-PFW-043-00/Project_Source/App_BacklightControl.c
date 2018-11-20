/*=================================
App_Display.c
Created on: 	6 Sept, 2018
Company: 		Mernok Elektronik
Author: 		H. du Plessis
==================================*/

#include <App_BacklightControl.h>

uint16_t Light_Sensor_Values[2];

void Adjust_Brightness(uint16_t value)
{
	if(value > 100)
	{
		MX_TIM5_Init(10);
	}
	else if(value > 50)
	{
		MX_TIM5_Init(10);
	}
	else
	{
		MX_TIM5_Init(10);
	}
}

void LCD_Brightness_Control()
{
	ADPS9309_GetValues(Light_Sensor_Values);
	Adjust_Brightness(Light_Sensor_Values[0]);
}
