/*ICON#_Controller_CAN.c
 *Created on: 11 Jul 2018
 *Company: Mernok Elektronik
 *Author: S.D. Janse van Rensburg
*/

#include "ICON3_Controller.h"

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
//Local Variables

//Global Variables

//Init Controller_CAN_INFO
void Init_Contoller_info(void)
{
	memset(&ControllerCANInfo,0,sizeof(ControllerCANInfo));
	memset(&HostCANInfo,0,sizeof(HostCANInfo));
	memset(&MY_CAN_MOB1,0,sizeof(MY_CAN_MOB1));
	memset(&MY_CAN_MOB2,0,sizeof(MY_CAN_MOB2));
	memset(&MY_CAN_MOB3,0,sizeof(MY_CAN_MOB3));
}

void CommsLost_to_default(void)
{
	memset(&ControllerCANInfo,0,sizeof(ControllerCANInfo));
	memset(&HostCANInfo,0,sizeof(HostCANInfo));
	memset(&MY_CAN_MOB1,0,sizeof(MY_CAN_MOB1));
	memset(&MY_CAN_MOB2,0,sizeof(MY_CAN_MOB2));
	memset(&MY_CAN_MOB3,0,sizeof(MY_CAN_MOB3));
}

bool Parse_Controller_CAN_message(CAN_RxHeaderTypeDef RX_HEADER, uint8_t DataBuffer[])
{
	bool Message_used = false;
	//Step1 - Determine valid CAN message by checking data size and CAN ID
	if((RX_HEADER.DLC == 8) && (RX_HEADER.ExtId == Controller_CAN_MOB1||RX_HEADER.ExtId == Controller_CAN_MOB2||RX_HEADER.ExtId == Controller_CAN_MOB3))
	{
		//step2 - Determine the specific MOB received and store data
		switch(RX_HEADER.ExtId)
		{
		case Controller_CAN_MOB1:
			memcpy(&MY_CAN_MOB1, DataBuffer, sizeof(MY_CAN_MOB1));
			ControllerCANInfo.Control_status.MOB1_received = true;
			Message_used = true; //indicate message used
			break;

		case Controller_CAN_MOB2:
			memcpy(&MY_CAN_MOB2,DataBuffer, sizeof(MY_CAN_MOB2));
			ControllerCANInfo.Control_status.MOB2_received = true;
			Message_used = true; //indicate message used
			break;

		case Controller_CAN_MOB3:
			memcpy(&MY_CAN_MOB3, DataBuffer, sizeof(MY_CAN_MOB3));
			ControllerCANInfo.Control_status.MOB3_received = true;
			Message_used = true; //indicate message used
			break;

		default:
				//Do nothing let it only pass
			break;
		}
	}
	return Message_used;
}
//Function to update CAN buffer to Controller variables
void Update_all_Controller_Data(void)
{
	//Update data from controller
	//MOB1
	ControllerCANInfo.Error_Code 					= MY_CAN_MOB1.Error_code;
	ControllerCANInfo.Fuel_level					= MY_CAN_MOB1.Fuel_level;
	memcpy(&ControllerCANInfo.StatusFlags,			&MY_CAN_MOB1.Status_flags,sizeof(ControllerCANInfo.StatusFlags));
	ControllerCANInfo.Parameter_index 				= MY_CAN_MOB1.Parameter_index;
	memcpy(&ControllerCANInfo.SystemFlagsA,	 		&MY_CAN_MOB1.System_flags_A,sizeof(ControllerCANInfo.SystemFlagsA));
	memcpy(&ControllerCANInfo.SystemFlagsB, 		&MY_CAN_MOB1.System_flags_B,sizeof(ControllerCANInfo.SystemFlagsB));
	memcpy(&ControllerCANInfo.RelayFlags, 			&MY_CAN_MOB1.Relay_feedback,sizeof(ControllerCANInfo.RelayFlags));
	ControllerCANInfo.SystemDirection 				= MY_CAN_MOB1.Direction;

	//MOB2
	ControllerCANInfo.FilteredArmatureCurrent 		= Byte2Int(MY_CAN_MOB2.Armature_current_MSB,MY_CAN_MOB2.Armature_current_LSB);
	ControllerCANInfo.FilteredStackVoltage 			= Byte2Int(MY_CAN_MOB2.Stack_voltage_MSB,MY_CAN_MOB2.Stack_voltage_LSB);
	ControllerCANInfo.Feedback_current_ref			= Byte2Int(MY_CAN_MOB2.Feedback_Current_ref_MSB,MY_CAN_MOB2.Feedback_Current_ref_LSB);
	ControllerCANInfo.FilteredArmatureVoltage 		= Byte2Int(MY_CAN_MOB2.Armature_voltage_MSB,MY_CAN_MOB2.Armature_voltage_LSB);

	//MOB3
	ControllerCANInfo.Firmware_revision				= MY_CAN_MOB3.Firmware_revision;
	ControllerCANInfo.Controller_type				= MY_CAN_MOB3.Controller_type;

}

void Process_ICON3_messages(void)
{
	//Test if all 3 CAN MODS were received
	if(ControllerCANInfo.Control_status.MOB1_received && ControllerCANInfo.Control_status.MOB2_received && ControllerCANInfo.Control_status.MOB3_received)
	{
		//Update all controller variables on the system
		Update_all_Controller_Data();
		//Clear all flags
		ControllerCANInfo.Control_status.COMMS_OK = true;
		ControllerCANInfo.Control_status.MOB1_received = false;
		ControllerCANInfo.Control_status.MOB2_received = false;
		ControllerCANInfo.Control_status.MOB3_received = false;
		ControllerCANInfo.CAN_comms_Counter = 0;
	}
	else
	{
		if(ControllerCANInfo.CAN_comms_Counter++ >= Allowable_CAN_Loss_Count)
		{
			ControllerCANInfo.Control_status.COMMS_OK = false;
			ControllerCANInfo.CAN_comms_Counter = Allowable_CAN_Loss_Count;
			CommsLost_to_default();		//clear all data of controller
		}
	}
}

/**********************************************************************************************
 * Note- MAXUSX does not send over CAN bus only Commander200 (To send only un-comment this part)
 **********************************************************************************************/
//void Host_send_message(void)
//{
//	//Only connect if controller present
//	TxMessage.ExtId = 0x1555555A;
//	TxMessage.IDE = CAN_ID_EXT;
//	//Indicate 8 data bytes
//	TxMessage.DLC = 8;
//	//Load all 8 data bytes
//	TxMessage.Data[0] = HostCANInfo.ControlReference.Reference_LSB;
//	TxMessage.Data[1] = HostCANInfo.ControlReference.Reference_MSB;
//	TxMessage.Data[2] = HostCANInfo.Selected_direction;
//	TxMessage.Data[3] = *(uint32_t*)&HostCANInfo.StatusFlags;
//	TxMessage.Data[4] = HostCANInfo.Speed_BrakeLimitLSB;
//	TxMessage.Data[5] = HostCANInfo.BrakeLimitMSB_ParameterValueMSB;
//	TxMessage.Data[6] = HostCANInfo.ParameterValueLSB_SpeedGoverninglimit;
//	TxMessage.Data[7] = HostCANInfo.ParameterIndex;
//
//	//Only send when instructed
//	if(Tramminginfo.Tramming_Status.Start_Transmission)
//		CAN_Transmit(CAN1, &TxMessage);
//
//}

//void Key_message(void)
//{
//#define ICON3_CAN_Response_ID 0x1A555555
//
//	TxMessage.ExtId = ICON3_CAN_Response_ID;
//	TxMessage.IDE = CAN_ID_EXT;
//	TxMessage.DLC = 8;
//	TxMessage.Data[0] = 0x55;
//	TxMessage.Data[1] = 0x55;
//	TxMessage.Data[2] = 0x55;
//	TxMessage.Data[3] = 0x00;
//	TxMessage.Data[4] = 0x55;
//	TxMessage.Data[5] = 0x55;
//	TxMessage.Data[6] = 0x55;
//	TxMessage.Data[7] = 0x55;
//	//Only send when instructed
//	if(Tramminginfo.Tramming_Status.Start_Transmission)
//		CAN_Transmit(CAN1, &TxMessage);
//}

