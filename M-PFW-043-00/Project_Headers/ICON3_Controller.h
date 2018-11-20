/*ICON#_Controller_CAN.h
 *Created on: 11 Jul 2018
 *Company: Mernok Elektronik
 *Author: S.D. Janse van Rensburg
*/

#ifndef PROJECT_HEADERS_RBE_SYSTEM_ICON__CONTROLLER_CAN_H_
#define PROJECT_HEADERS_RBE_SYSTEM_ICON__CONTROLLER_CAN_H_

//Includes
#include "Global_Variables.h"

//Defines
#define Controller_CAN_MOB1 0x15555555 //Control/status flags
#define Controller_CAN_MOB2 0x19555555 //Filtered Analogue readings
#define Controller_CAN_MOB3 0x15955555 //Controller type, Firmware revisions and brake current limit

#define Host_CAN_MOB1 		0x1555555A //Host message to controller

#define Allowable_CAN_Loss_Count 20

//Variables made public

/*******************************************************************/
//Receive message structures from controller
/*******************************************************************/

typedef struct _CAN_MOB1_info_
{
	uint8_t Error_code;
	uint8_t Fuel_level;
	uint8_t Status_flags;
	uint8_t Parameter_index;
	uint8_t System_flags_A;
	uint8_t System_flags_B;
	uint8_t Relay_feedback;
	uint8_t Direction;

}CAN_MOB1;

typedef struct _CAN_MOB2_info_
{
	uint8_t Armature_current_LSB;
	uint8_t Armature_current_MSB;
	uint8_t Stack_voltage_LSB;
	uint8_t Stack_voltage_MSB;
	uint8_t Feedback_Current_ref_MSB;
	uint8_t Feedback_Current_ref_LSB;
	uint8_t Armature_voltage_LSB;
	uint8_t Armature_voltage_MSB;

}CAN_MOB2;

typedef struct _CAN_MOB3_info_
{
	uint8_t Firmware_revision;
	uint8_t Controller_type;
//	uint8_t;
//	uint8_t;
//	uint8_t;
//	uint8_t;
//	uint8_t;
//	uint8_t;

}CAN_MOB3;

//Structures required by CAN handler
CAN_MOB1 		MY_CAN_MOB1;
CAN_MOB2 		MY_CAN_MOB2;
CAN_MOB3 		MY_CAN_MOB3;

//One byte size
typedef struct _Controller_Status_Flags_
{
	uint8_t System_OK 					:1;	//1 = System OK, 0 = don't care
	uint8_t System_NOK 					:1;	//1 = System not OK, 0 = don't care
	uint8_t 					 		:1;	//1 = , 0 =
	uint8_t 					 		:1;	//1 = , 0 =
	uint8_t Lights_state				:1;	//1 = reverse, 0 = forward
	uint8_t 							:1; //spare bit
	uint8_t Controller_mode				:1;	//1 = Parameter transfer mode, 0 = normal operation mode
	uint8_t Cell_60_42					:1;	//1 = 60 cell, 0 = 42 cell
}Controller_Status_Flags;

//One byte size
typedef struct _System_Flags_A_
{
	uint8_t Run_state				:1;	//1 = motor control active, 0 = IGBT firing disables
	uint8_t Forward_flag			:1;	//1 = forward direction active, 0 = dont care
	uint8_t Reverse_flag			:1;	//1 = reverse direction active, 0 = dont care
	uint8_t Neutral_flag			:1;	//1 = neutral direction active, 0 = dont care
	uint8_t BrakingActive_flag		:1;	//1 = motor in braking (Neg Varma), 0 = dont care
	uint8_t NeutralBrake_flag		:1;	//1 = Neutral brake routine active, 0 = dont care
	uint8_t ForwardWithBrake_flag	:1;	//1 = Forward direction with braking active, 0 = dont care
	uint8_t ReverseWithBrake_flag	:1;	//1 = reverse direction with braking active, 0 = dont care
}System_Flags_A;

//One byte size
typedef struct _System_Flags_B_
{
	uint8_t Tandem_flag				:1;	//1 = is master, 0 = is slave (dont care)
	uint8_t EmergencyBrake_flag		:1;	//1 = controller in E-stop routine, 0 = dont care
	uint8_t Internal_EmergencyBrake_flag :1; //1 = controller internal E-stop routine, 0 = dont care
	uint8_t Error_flag				:1;	//1 = (dont care)
	uint8_t Remote_flag				:1;	//1 = (dont care)
	uint8_t KeyValid_flag			:1;	//1 = Valid Key, 0 = no key (dont care)
	uint8_t CreepActive_flag		:1;	//1 = Creep speed mode active, 0 = dont care
	uint8_t SelfTestPass_flag		:1;	//1 = Controller selftest passed, selftest fail/busy
}System_Flags_B;

//One byte size
typedef struct _Relay_Flags_
{
	uint8_t 						:1;	//1 = active , 0 = deactive
	uint8_t							:1;	//1 = active, 0 = deactive
	uint8_t Line_Contactor			:1;	//1 = active, 0 = deactive
	uint8_t Reverse_Contactor		:1;	//1 = active, 0 = deactive
	uint8_t Forward_contactor		:1;	//1 = active, 0 = deactive
	uint8_t Brake_contactor			:1;	//1 = active, 0 = deactive
	uint8_t Lights_contactor		:1;	//1 = active, 0 = deactive
	uint8_t Mechanical_brake_Contactor	:1;	//1 = active, 0 = deactive
}Relay_Flags;

//One byte size
typedef struct _status_
{
	uint8_t	COMMS_OK				:1;
	uint8_t	MOB1_received			:1;
	uint8_t	MOB2_received			:1;
	uint8_t	MOB3_received			:1;
	uint8_t							:1;
	uint8_t							:1;
	uint8_t							:1;
	uint8_t							:1;
}status;

//Info required for controller to use
typedef struct _Controller_info_
{
	//MOB1
	uint8_t 				Error_Code;
	uint8_t 				Fuel_level;
	Controller_Status_Flags	StatusFlags;
	uint8_t 				Parameter_index;
	System_Flags_A 			SystemFlagsA;
	System_Flags_B			SystemFlagsB;
	Relay_Flags 			RelayFlags;
	uint8_t 				SystemDirection;

	//MOB2
	uint16_t 				FilteredArmatureCurrent;
	uint16_t 				FilteredStackVoltage;
	uint16_t 				Feedback_current_ref;
	uint16_t  				FilteredArmatureVoltage;

	//MOB3
	uint8_t			 		Firmware_revision;
	uint8_t			 		Controller_type;


	//Variable used for communication purposes
	status					Control_status;
	uint8_t					CAN_comms_Counter;

}Controller_info;

//Declare required structures
Controller_info ControllerCANInfo;

/*******************************************************************/
//Transmitting message structures to controller
/*******************************************************************/
//one word
typedef struct _Control_Reference_
{
	//Unsigned - 16bit value (0 -> 32767)
	uint16_t Reference_LSB			:8;
	uint16_t Reference_MSB			:8;
}Control_Reference;
//one byte

typedef struct _Status_Flags_
{
	uint8_t Key						:1;	//1 = Key OK, 0 = Key not OK
	uint8_t Door_state				:1;	//1 = Panto UP, 0 = Panto DOWN
	uint8_t 						:1;	//1 = , 0 =
	uint8_t 						:1;	//1 = , 0 =
	uint8_t BrakeTestActive			:1;	//1 = mechanical brake test active, 0 = don't care
	uint8_t Selftest_Bypass			:1;	//1 = Controller self-test bypassed, 0 = Controller to perform self-test
	uint8_t 						:1; //1 = , 0 =
	uint8_t Parameter_entry_bit		:1; //1 = Parameter entry mode, 0 = Normal mode
}Status_Flags;

//Host message structure to use when sending CAN message
typedef struct _Host_Info_
{
	//Host_MOB
	Control_Reference		ControlReference; //16bit unsigned value
	uint8_t					Selected_direction;
	Status_Flags			StatusFlags;
	uint8_t					Speed_BrakeLimitLSB;
	uint8_t					BrakeLimitMSB_ParameterValueMSB;
	uint8_t					ParameterValueLSB_SpeedGoverninglimit;
	uint8_t					ParameterIndex;

}Host_Info;

//Declare required structures
Host_Info		HostCANInfo;

//Functions made public
void Init_Contoller_info(void);
void CommsLost_to_default(void);
bool Parse_Controller_CAN_message(CAN_RxHeaderTypeDef RX_HEADER, uint8_t DataBuffer[]);
void Update_all_Controller_Data(void);
void Process_ICON3_messages(void);
void Host_send_message(void);

#endif /* PROJECT_HEADERS_RBE_SYSTEM_ICON__CONTROLLER_CAN_H_ */
