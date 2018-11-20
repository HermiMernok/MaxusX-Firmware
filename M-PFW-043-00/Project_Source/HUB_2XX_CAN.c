/*HUB_2XX_CAN.c
 *Created on: 27 Jul 2018
 *Company: Mernok Elektronik
 *Author: S.D. Janse van Rensburg
*/

#include "HUB_2XX_CAN.h"

/****************************************************************/
/**
 * @brief  
 * @param  
 *   This parameter can be one of following parameters:
 *     @arg 
 * @retval None
 */
/****************************************************************/
/***********************************************/
void HUB_2XX_Init(void)
{
	memset(&HUB2XX_handle,0,sizeof(HUB2XX_Handle));
	memset(&HUB2XX_IO,0,sizeof(HUB2XX_IO_message));
	memset(&HUB2XX_ADC,0,sizeof(HUB2XX_ADC_message));
}
//Function to default all HUB2XX values
void HUB_2XX_Default(void)
{
	memset(&HUB2XX_handle,0,sizeof(HUB2XX_Handle));
	memset(&HUB2XX_IO,0,sizeof(HUB2XX_IO_message));
	memset(&HUB2XX_ADC,0,sizeof(HUB2XX_ADC_message));
}

bool HUB_2XX_message_Parser(CAN_RxHeaderTypeDef RX_HEADER, uint8_t DataBuffer[])
{
	bool temp = false;
	//Test if correct Data Size and Message ID
	if(RX_HEADER.DLC == 8 && (RX_HEADER.ExtId == HUB2XX_RX_MOB1 || RX_HEADER.ExtId == HUB2XX_RX_MOB2))
	{

		switch(RX_HEADER.ExtId)
		{
		//detect 1st MOB from hub
		case HUB2XX_RX_MOB1:
			memcpy(&HUB2XX_ADC,DataBuffer,sizeof(HUB2XX_ADC_message));
			HUB2XX_handle.HUB2XX_Status.MOB1_Received = true;
			temp = true;
			break;

		//detect 2nd MOB from hub
		case HUB2XX_RX_MOB2:
			memcpy(&HUB2XX_IO,DataBuffer,sizeof(HUB2XX_IO_message));
			HUB2XX_handle.HUB2XX_Status.MOB2_Received = true;
			temp = true;
			break;
		}

	}
	return temp;
}

//NOTE: MAXUSX will not send CAN messages as
//Function to set/clear CAN IO outputs
void Transmit_HUB_2XX_messages(HUB2XX_Handle *HUB_control)
{
	/* Transmit Structure preparation */
	uint8_t Test_Buffer[8] = {0};
	CAN2_TX_HEADER.ExtId = HUB2XX_MOB;
	CAN2_TX_HEADER.DLC = 8;
	CAN2_TX_HEADER.IDE = CAN_ID_EXT;
	CAN2_TX_HEADER.RTR = CAN_RTR_DATA;
	CAN2_TX_HEADER.TransmitGlobalTime = DISABLE;

	//clear buffer before use
	//memset(&TxMessage.Data[0], 0 , sizeof(TxMessage.Data));

	switch(HUB_control->Message_index)
	{
		//TX POT ADC values request
		case 0:
			Test_Buffer[2] = 0x04;
			Test_Buffer[3] = 0x10;
			break;
		//TX POT IO status request
		case 1:
			Test_Buffer[2] = 0x08;
			break;
	}

	CAN_Send_Message(&hcan2, &CAN2_TX_HEADER, Test_Buffer, 0);
	//update index to rotate between all messages types
	if(HUB_control->Message_index++ > 0)
		HUB_control->Message_index = 0;

}

void HUB_2XX_Handler(void)
{
	//If CAN IO message detected
	if(HUB2XX_handle.HUB2XX_Status.MOB1_Received & HUB2XX_handle.HUB2XX_Status.MOB2_Received)
	{
		HUB2XX_handle.Comms_counter = 0;
		HUB2XX_handle.HUB2XX_Status.MOB1_Received = false; //restart wait
		HUB2XX_handle.HUB2XX_Status.MOB2_Received = false; //restart wait
		HUB2XX_handle.HUB2XX_Status.Connected = true;
	}
	else
	{
		if(HUB2XX_handle.Comms_counter++ > HUB_Comms_count)
		{
			HUB2XX_handle.HUB2XX_Status.Connected = false;
			HUB2XX_handle.Comms_counter = HUB_Comms_count;
			HUB_2XX_Default();
		}
	}

	/**********************************************************************************************
	 * Note- MAXUSX does not send over CAN bus only Commander200 (To send only un-comment this part)
	 **********************************************************************************************/
	//Retransmit packet to CAN IO
	//Transmit_HUB_2XX_messages(&HUB2XX_handle);
}

