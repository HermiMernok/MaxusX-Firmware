

#include "App_Debug.h"

void Startup_Debug(uint16_t Height)
{

	TextToScreen_LRG(10,Height,"Tests",LCD_COLOR_WHITE, LCD_BLACK);

	if(IC_Flags.RTC_OK )
	{
		TextToScreen_MED(10,Height+LINE_HEIGHT,"NVRAM Ok",LCD_YELLOW, LCD_BLACK);
	}
	else
	{
		TextToScreen_MED(10,Height+LINE_HEIGHT,"NVRAM Failed",LCD_YELLOW, LCD_BLACK);
	}

	if(IC_Flags.Light_Sensor_OK)
	{
		TextToScreen_MED(10,Height+LINE_HEIGHT*2,"Light Sensor OK",LCD_YELLOW, LCD_BLACK);
	}
	else
	{
		TextToScreen_MED(10,Height+LINE_HEIGHT*2,"Light Sensor Failed",LCD_WHITE, LCD_BLACK);
	}

	if(IC_Flags.NOR_FLASH_OK)
	{
		TextToScreen_MED(10,Height+LINE_HEIGHT*3,"NOR FLASH OK",LCD_WHITE, LCD_BLACK);
	}
	else
	{
		TextToScreen_MED(10,Height+LINE_HEIGHT*3,"NOR FLASH Failed",LCD_WHITE, LCD_BLACK);
	}

}

void Operational_Debug(uint16_t Height)
{

	TextToScreen_MED(750,10, Text_Date,LCD_WHITE, LCD_BLACK);
	TextToScreen_MED(750,40,Text_Time,LCD_WHITE, LCD_BLACK);

	TextToScreen_LRG(10,Height,"CAN",LCD_WHITE, LCD_BLACK);

	if(NV_RAM_SPI_Test() != SPI_OK)
	{
		TextToScreen_MED(10,Height+40,"NVRAM Failed",LCD_WHITE, LCD_BLACK);
	}
	else
	{
		TextToScreen_MED(10,Height+40,"NVRAM Ok",LCD_WHITE, LCD_BLACK);
	}



	//	if(RTC)
	//	{
	//		TextToScreen_LRG(10,40,"RTC Failed",LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	//	}
	//	else
	//	{
	//		TextToScreen_LRG(10,40,"RTC Ok",LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	//	}


}
