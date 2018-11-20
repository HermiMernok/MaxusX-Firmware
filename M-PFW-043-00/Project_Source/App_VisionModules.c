/*
 * App_VisionModules.c
 *
 *  Created on: 04 September 2018
 */

#include "App_VisionModules.h"
#include "App_Threats.h"

#include "F769_UART.h"

vision_device  Pulse400_Module;
uint8_t COM_EXP1_Buffer[VISION_BUF_LEN] = { };

Pulse_Tag			PresentList[PresentList_Max];
Pulse_Tag			Excluded_OwnTagList[Excluded_OwnTagList_Max];

void App_VisionModules_Init(void)
{
	// Initialize Pulse400 module
	//Pulse400_Module = {0};

	// Set COM Port Number of Pulse400 module
	Pulse400_Module.COM_Port = COM_EXP1;
	Pulse400_Module.interface = COM;
	Pulse400_Module.vision_inbuf = COM_EXP1_Buffer;
}

void App_VisionModules_Process(void)
{
	vision_process(&Pulse400_Module);
}

int Vision_GetWRptr(vision_device* reader)
{
	return DMA_UART_Vision_Get_WRPtr(VISION_BUF_LEN);
}

/*-----------------------------------------
 *Function name and description
 *---------
 *RF and LF based filters and sorting
 *
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void System_Filter_Control(void)
{

//	/*--------------------------------
//	 * Filter all tags seen over RF
//	 *------------------------------*/
//	Vision_Filter_Tags();

	//Code added when pulse threat list breaks
	//	if(System_Flags.System_Pulse400_Reset)
	//	{
	//		System_Flags.System_Pulse400_Reset = false;
	//		System_Flags.System_Pulse400_Errors++;
	//
	//		clear_transp_log();
	//
	//		VisionModule_Reset (myVisionModules[myPulse400]);
	//
	//		Vision_Filter_Tags ();
	//
	//	}

	//	sprintf(Text_Buf6, "Resets : %d ", System_Flags.System_Pulse400_Errors);

//	/*--------------------------------
//	 * Update Pulse tag list information
//	 *------------------------------*/
//	Vision_PulseTag_Filter();
//
//	/*--------------------------------
//	 * Update Threat list information
//	 *------------------------------*/
//	Threat_Management();
//
//	/*--------------------------------
//	 * Update Work Zone Status
//	 *------------------------------*/
//	Threat_WorkZoneHandler();

	/*--------------------------------
	 * Update Speed Zone
	 *------------------------------*/
//	App_Update_SpeedZone();


}

/*-----------------------------------------
 *Function name and description
 *---------
 * Gets the write pointer from the DMA to determine how many bytes have been written.
 *Inputs:
 *---------
 *	buffer size: tghe size of the buffer??
 *Outputs:
 *---------
 *	integer offset in the Rx buffer.
 *-----------------------------------------*/
uint16_t DMA_UART_Vision_Get_WRPtr(uint16_t rx_buffer_size)
{
	uint16_t bytes_left = 0;
	bytes_left = huartx[COM_EXP1].hdmarx->Instance->NDTR;

	return (rx_buffer_size-1)&(rx_buffer_size - bytes_left);
}
