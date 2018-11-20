/*
 * App_EventManager.h
 *
 *  Created on: May 30, 2016
 *      Author: JacoOlivier
 */

#ifndef APP_EVENTMANAGER_H_
#define APP_EVENTMANAGER_H_

#include "Global_Variables.h"

#define	evSize					250
#define evListSize				50
#define evGroupSize				9	// ---- Total group count + 1 (Type_None) ----
#define evScreenSize			7	// ---- Total group count + 1 (Disp_None) ----

#define Card_Splash				2
#define ParameterID_Log_Start	1000

/*
 * Event Type Definition
 *
 * This is the required structure needed
 * to fully describe an event so that it
 * may be fully handled by the system
 *
 */
typedef struct _Event
{
	// ---- *Event Information* ----

	// ---- The category of the event ----
	uint16_t		EventCategory;
	// ---- The unique identifier of the event ----
	uint16_t		EventID;
	// ---- This is a flag that indicates if the event is active or inactive ----
	bool			EventActive;
	// ---- The name of the event, this will be printed on screen ----
	char			EventName[25];

	// ---- *Event Control* ----
	// ---- Systic time stamp when the event occurred ----
	uint32_t		TimeStampSystic;
	// ---- The action which will be executed as soon as the event occurred ----
	uint8_t			EventAction1;
	// ---- The action which will be executed when EventActionTime1_2 elapsed after event EventAction1 ----
	uint8_t			EventAction2;
	// ---- The action which will be executed when EventActionTime2_3 elapsed after event EventAction2 ----
	uint8_t			EventAction3;
	// ---- The time delays for the actions ----
	uint32_t		EventActionTime1_2;
	uint32_t		EventActionTime2_3;

	// ---- *Event Processing* ----
	// ---- This is a flag that indicates if the event has been processed or not ----
	bool			Processed;
	// ---- This is a flag that indicates if the event is already logged or not ----
	bool			EventLogged;

	uint8_t			TimeRequired;
	bool			ACKRequired;
	bool			ACKReceived;

	// ---- The action which will be executed when the event has been set active ----
	uint8_t			EventACKAction;

	// ---- *Event Interface* ----

	// ---- This display type will determine if the event must be displayed (only displayed events can be actioned upon) ----
	uint8_t			DispType;
	// ---- The address of the image that will be displayed if the event is applied ----
	uint8_t			ImageName;
	// ---- This display time will determine the duration the event must be displayed (only used for splash screen) ----
	uint32_t		SplashTime;
	// ---- This is a flag that indicates if the splash is active or inactive ----
	bool			SplashActive;

	// ---- The mode of the buzzer when the event is applied ----
	uint8_t			BuzzerMode;
	// ---- If the buzzer is required when the event is applied ----
	bool			BuzzerRequired;

	//Events
	//uint8_t*		EventData;
	uint8_t			EventData[8];

	// ---- The pointer to reference the information the event is based on ----
	uint8_t* 		AddtionalInfo;


}Event;

Event*	Active_Event;
Event*	ActiveDisplay_Event;

/*
 * Events Defined Enum
 *
 */
typedef enum
{
	// ---- *Start-up Events* ----
	EV_Empty										= 0,
	EV_Power_Down									= 1,
	EV_Power_Up										= 2,
	EV_Commissioning_Required						= 3,

	// ---- *Unit Health Events* ----
	EV_NVRAMSPI_Fail								= 10,
	EV_NVRAMSPI_OK									= 11,

	EV_RTCSPI_Fail									= 12,
	EV_RTCSPI_OK									= 13,

	EV_SystemTime_Fail								= 14,
	EV_SystemTime_OK								= 15,

	EV_AmbientSensor_Fail		 					= 16,
	EV_AmbientSensor_OK								= 17,

	// ---- *Parameter Events* ----
	EV_Parameter_Fail								= 20,
	EV_Parameter_OK									= 21,

	EV_Revison_Fail									= 22,
	EV_Revison_OK									= 23,

	// ---- *Expansion Module Events* ----
	EV_Exp_Mod_1_Fail								= 30,
	EV_Exp_Mod_2_Fail								= 31,
	EV_Exp_Mod_3_Fail								= 32,
	EV_Exp_Mod_4_Fail								= 33,

	EV_Exp_Mod_1_OK									= 34,
	EV_Exp_Mod_2_OK									= 35,
	EV_Exp_Mod_3_OK									= 36,
	EV_Exp_Mod_4_OK									= 37,

	// ---- *Module Antenna Events* ----
	EV_Exp_Mod_1_Ant_Fail							= 50,
	EV_Exp_Mod_2_Ant_Fail							= 51,
	EV_Exp_Mod_3_Ant_Fail							= 52,
	EV_Exp_Mod_4_Ant_Fail							= 53,

	EV_Exp_Mod_1_Ant_OK								= 54,
	EV_Exp_Mod_2_Ant_OK								= 55,
	EV_Exp_Mod_3_Ant_OK								= 56,
	EV_Exp_Mod_4_Ant_OK								= 57,

	// ---- *Device RF Monitoring Events* ----
	EV_PulseDeviceRF01_Fail							= 58,
	EV_PulseDeviceRF02_Fail							= 59,
	EV_PulseDeviceRF03_Fail							= 60,
	EV_PulseDeviceRF04_Fail							= 61,
	EV_PulseDeviceRF05_Fail							= 62,

	EV_PulseDeviceRF01_OK							= 63,
	EV_PulseDeviceRF02_OK							= 64,
	EV_PulseDeviceRF03_OK							= 65,
	EV_PulseDeviceRF04_OK							= 66,
	EV_PulseDeviceRF05_OK							= 67,

	// ---- *Device CAN Monitoring Events* ----
	EV_PulseDeviceCAN01_Fail						= 68,
	EV_PulseDeviceCAN02_Fail						= 69,
	EV_PulseDeviceCAN03_Fail						= 70,
	EV_PulseDeviceCAN04_Fail						= 71,
	EV_PulseDeviceCAN05_Fail						= 72,

	EV_PulseDeviceCAN01_OK							= 73,
	EV_PulseDeviceCAN02_OK							= 74,
	EV_PulseDeviceCAN03_OK							= 75,
	EV_PulseDeviceCAN04_OK							= 76,
	EV_PulseDeviceCAN05_OK							= 77,

	// ---- *Ancillary Monitoring Events* ----
	EV_HUB200_Failure								= 78,
	EV_HUB200_OK									= 79,

	EV_LightBar_Failure								= 80,
	EV_LightBar_OK									= 81,

	EV_FLOW_Failure									= 82,
	EV_FLOW_OK										= 83,

	EV_Remote_Failure								= 84,
	EV_Remote_OK									= 85,

	// ---- *Emergency Stop Events* ----
	EV_Estop_Latch_Int								= 90,
	EV_EStop_Release_Int							= 91,

	EV_Estop_Latch_Ext								= 92,
	EV_Estop_Release_Ext							= 93,

	// ---- *External Input Events* ----
	Input_01_On										= 94,
	Input_01_Off									= 95,
	Input_02_On										= 96,
	Input_02_Off									= 97,
	Input_03_On										= 98,
	Input_03_Off									= 99,
	Input_04_On										= 100,
	Input_04_Off									= 101,
	Input_05_On										= 102,
	Input_05_Off									= 103,
	Input_06_On										= 104,
	Input_06_Off									= 105,

	// ---- *Pre-operation Events* ----
	EV_System_Pre_Op_Pass							= 110,
	EV_System_Pre_Op_Fail							= 111,

	// ---- *License Card Events* ----
	EV_License_Required								= 112,
	EV_Admin_Required								= 113,

	// ---- Must be sequential (for loop) ----
	EV_License_Processed_01							= 114,
	EV_License_Processed_02							= 115,
	EV_License_Processed_03							= 116,
	EV_License_Processed_04							= 117,
	EV_License_Processed_05							= 118,
	EV_License_Processed_06							= 119,

	EV_License_Processing							= 120,
	EV_License_Invalid								= 121,
	EV_Licence_WarningDate							= 122,
	EV_Licence_ExpiredDate							= 123,
	EV_License_Valid								= 124,

	// ---- *Road Condition Events* ----
	// ---- Must be sequential (for loop) ----
	EV_UnknownRoad									= 125,
	EV_DryRoad										= 126,
	EV_WetRoad										= 127,
	EV_SlipRoad										= 128,

	// ---- *Speed Zone Events* ----
	// ---- Must be sequential (for loop) ----
	EV_LowSpeedZone									= 129,
	EV_MeduimSpeedZone								= 130,
	EV_HighSpeedZone								= 131,

	EV_LowSpeedZone_End								= 132,
	EV_MeduimSpeedZone_End							= 133,
	EV_HighSpeedZone_End							= 134,

	// ---- *Speed Control Events* ----
	EV_Speed_OK										= 135,
	EV_Speed_OKEnd									= 136,
	EV_Speed_Warning								= 137,
	EV_Speed_WarningEnd								= 138,
	EV_Speed_Overspeeding							= 139,
	EV_Speed_OverspeedingEnd						= 140,

	// ---- *Operational Work Zone Events* ----
	EV_Operational_WorkZone_01						= 141,
	EV_Operational_WorkZone_02						= 142,
	EV_Operational_WorkZoneEnd						= 143,
	EV_Operational_WorkZoneFail						= 144,

	// ---- *System Action Events* ----
	EV_SystemAction									= 145,

	// ---- *Proximity Detection Events* ----
	// ---- Must be sequential (for loop) ----
	EV_PDS_1										= 150,
	EV_PDS_2										= 151,
	EV_PDS_3										= 152,
	EV_PDS_4										= 153,
	EV_PDS_5										= 154,
	// ---- Logging Purposes ----
	EV_PDS_6										= 155,
	EV_PDS_7										= 156,

	EV_PDS_1_End									= 157,
	EV_PDS_2_End									= 158,
	EV_PDS_3_End									= 159,
	EV_PDS_4_End									= 160,
	EV_PDS_5_End									= 161,
	// ---- Logging Purposes ----
	EV_PDS_6_End									= 162,
	EV_PDS_7_End									= 163,

	// ---- *J1939 Engine Events* ----
	EV_J1939_Failure                                = 170,
	EV_J1939_OK		                                = 171,
	EV_J1939_Coolant_TempHigh                      	= 172,
	EV_J1939_Coolant_TempOK		                    = 173,
	EV_J1939_Coolant_PresHigh                      	= 174,
	EV_J1939_Coolant_PresOK		                    = 175,

	EV_J1939_Oil_TempHigh                           = 176,
	EV_J1939_Oil_TempOK                            	= 177,
	EV_J1939_Oil_PresHigh                           = 178,
	EV_J1939_Oil_PresOK                            	= 179,

	EV_J1939_Fuel_Error                             = 180,
	EV_J1939_Fuel_OK	                            = 181,
	EV_J1939_Rev_Error								= 182,
	EV_J1939_Rev_OK									= 183,

	// ---- *J1939 Vehicle Interface Events* ----
	EV_PDS_Fault									= 190,
	EV_PDS_OK										= 191,
	EV_Vehicle_Fault								= 192,
	EV_Vehicle_OK									= 193,
	EV_Confirm_Emergency_Stop						= 194,
	EV_Confirm_Controlled_Stop						= 195,
	EV_Confirm_SlowDown								= 196,
	EV_Confirm_Bypass								= 197,
	EV_Confirm_ApplySetPoint						= 198,
	EV_Confirm_StandDown							= 199,
	EV_Confirm_Motion_Inhibit						= 200,

	EV_Negotiation_Incomplete						= 201,
	EV_Negotiation_Complete_01						= 202,
	EV_Negotiation_Complete_02						= 203,
	EV_Negotiation_Complete_03						= 204,

	EV_PDS_1_ACK_Ignored							= 212,
	EV_PDS_2_ACK_Ignored							= 213,
	EV_PDS_3_ACK_Ignored							= 214,
	EV_PDS_4_ACK_Ignored							= 215,
	EV_PDS_5_ACK_Ignored							= 216,

	EV_PDS_1_ACK_Received							= 217,
	EV_PDS_2_ACK_Received							= 218,
	EV_PDS_3_ACK_Received							= 219,
	EV_PDS_4_ACK_Received							= 220,
	EV_PDS_5_ACK_Received							= 221,

	//Debug event
	EV_Debug_Card									= 233,

	EV_LowPressure									= 222,
	EV_ProximityError								= 223,
	EV_Remote_Tilt									= 224,

	EV_Output_01									= 225,
	EV_Output_02									= 226,
	EV_Output_03									= 227,
	EV_Idle											= 228,

	EV_Tag_Test_Passed								= 229,
	EV_Tag_Test_Failed								= 230,
	EV_Tag_Test_TimeOut								= 231,


	EV_Speedo_Op_Default							= 234,
	EV_Speedo_Brake_Test_Static_Pass                = 235,
	EV_Speedo_Brake_Test_Static_Fail                = 236,
	EV_Speedo_Brake_Test_Active                     = 237,
	EV_Dynamic_Test_Control                         = 238,
	EV_Dynamic_Test_Result                          = 239,
	EV_Wheel_Slip_Active                            = 240,
	EV_Break_Test_Failed							= 241,


	EV_Loco_Motor_Stall								= 243,

	EV_User_ACK_CAS									= 244,
}Events_Defined;

typedef struct _evList
{

	uint16_t	evIndex[evListSize];		//keep track of this with event definitions!!
	bool		evStatus[evListSize];
	uint8_t		evCounter;

}evList;


/*
 * Event Type Enum
 *
 * These are the types of event that
 * can occur and be acknowledged by
 * the system
 *
 */
typedef enum
{
	Type_None				= 0,
	Type_Internal			= 1,				//The order of these enums are defined based on importance, 0 (Most important)
	Type_System				= 2,
	Type_Operational	 	= 3,
	Type_Debug				= 4,
	Type_Vehicle			= 5,
	Type_PDS				= 6,
	Type_Init				= 7,
	Type_Idle				= 8,
	Type_Commisioning		= 9

} Event_Type;

/*
 * Event Action Enum
 *
 * These are the types of event actions
 * that can occur and be acknowledged by
 * the system
 *
 */
typedef enum
{
	Act_None				= 0,						//This has to be numbered in ascending order based on severity!!
	Act_DisplayOnly			= 1,

	Act_ForceStandDown		= 2,
	Act_ForceHigh			= 3,
	Act_ForceMeduim			= 4,
	Act_ForceSlow			= 5,
	Act_MotionInhibit		= 6,
	Act_ForceStop			= 7,

	Act_Overrule			= 8,

	Act_ForceStandDown_OVR	= 9,
	Act_ForceHigh_OVR		= 10,
	Act_ForceMeduim_OVR		= 11,
	Act_ForceSlow_OVR		= 12,
	Act_MotionInhibit_OVR	= 13,
	Act_ForceStop_OVR		= 14,

}Event_Action;


/*
 * Display Type Enum
 *
 * These are the types of displays
 * that the system is capable of handling
 *
 */
typedef enum
{
	Disp_None					= 0,
	Disp_Message				= 1,
	Disp_Icon					= 2,
	Disp_Generic_SplashScreen	= 3,
	Disp_Dedicated_SplashScreen	= 4,
	Disp_Generic_FullScreen		= 5,
	Disp_Dedicated_FullScreen	= 6

}Display_Type;

typedef enum
{
	Status_Unknown		= 0,
	Status_Inactive		= 1,
	Status_Active		= 2,
	Status_NotRequired 	= 3

} StatusFlag;



//Externals

extern evList	evGroups[evGroupSize];
extern evList	evMessages[evGroupSize];
extern Event 	EventList[evSize];
extern Event*	Active_Event;
extern uint8_t 	TagTypeImage[255];

void App_EventManager_Init(void);
void App_EventManageUpdates(void);
void App_EventControl(void);
evList App_EventUpdate(evList evGroup, uint16_t evIndex);
evList App_EventRemove(evList evGroup);
evList App_EventFlagRst(evList evGroup);
void App_EventSet(uint16_t Event);
void App_EventSetTimeStamp(uint16_t Event, uint32_t TimeStamp);
void App_EventClear(uint16_t Event);
void App_EventProcess(uint16_t ApplyEvent, uint16_t SplashEvent);
void App_EventHandleActives(void);
void App_EventHandler(void);
void App_EventListSort(evList evGroups[]);
bool App_EventFindInList(evList evGroup, uint16_t evIndex);
void App_EventApply(uint16_t Apply_EV);
void App_EventACK(uint16_t AcknowledgeEventActive);
void App_EventUpdateThreatImage(uint16_t Index, uint8_t TagType);
void App_EventUpdateAddtionalInfo(uint16_t Index, uint8_t* Info);
void App_EventResetCAS(void);
void App_EventPrioritiesFilter(void);

void App_EventClearLogged(uint16_t Event);
void App_EventClearACK(uint16_t Event);
void App_EventSetACK(uint16_t Event);

uint8_t App_EventDetermineMostImportantEventGroup (void);
uint16_t App_EventDetermineApplyID(void);
uint16_t App_EventDetermineSplashID(void);
uint8_t App_EventDetermineMostImportantAction (uint16_t evAction);
uint8_t App_EventReferenceDetermineMostImportantAction(Event* ActionEvent);

void App_EventUpdateActions(uint16_t Index, uint8_t Act1, uint8_t Act2, uint8_t Act3);
void App_EventUpdateData(uint16_t Index, uint8_t* EventData);

void App_EventSplashHandler (void);
void App_EventDisplay (uint16_t ApplyEventActive, uint16_t SplashEventActive);



#endif /* APP_EVENTMANAGER_H_ */
