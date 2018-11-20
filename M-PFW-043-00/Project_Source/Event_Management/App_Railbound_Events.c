/*
 * App_Trackless_CAS_Events.c
 *
 *  Created on: Dec 9, 2016
 *      Author: JacoOlivier
 */

#include "App_Railbound_Events.h"
#include "App_EventManager.h"

//#include "App_SpeedControl.h"
//#include "ISO_21815.h"

void App_Railbound_Events_Init(void)
{
	// ---- Index - EV_Empty - ID ----
	EventList[EV_Empty].EventCategory 					= Type_None;
	EventList[EV_Empty].EventID 						= 0;

	EventList[EV_Empty].EventActive 					= false;

	sprintf(EventList[EV_Empty].EventName, "No Event");

	EventList[EV_Empty].TimeStampSystic 					= 0;

	EventList[EV_Empty].EventAction1 					= Act_None;
	EventList[EV_Empty].EventAction2 					= Act_None;
	EventList[EV_Empty].EventAction3 					= Act_None;
	EventList[EV_Empty].EventActionTime1_2 				= 0;
	EventList[EV_Empty].EventActionTime2_3 				= 0;

	EventList[EV_Empty].Processed 						= false;
	EventList[EV_Empty].EventLogged 					= false;

	EventList[EV_Empty].DispType 						= Disp_None;
	//EventList[EV_Empty].ImageName 						= Icon_Attention;

	EventList[EV_Empty].BuzzerRequired 					= false;
	//EventList[EV_Empty].BuzzerMode 						= Buzz_Once;

	memset(EventList[EV_Empty].EventData, 0xFF, sizeof(EventList[EV_Empty].EventData));
	EventList[EV_Empty].AddtionalInfo					= NULL;

	EventList[EV_Empty].TimeRequired = 0;
	EventList[EV_Empty].ACKRequired = false;

	/*-------------------------------------------------------------------------------------------------------
	 * 										  DEBUG EVENT
	 *-------------------------------------------------------------------------------------------------------*/

	// ---- Index - EV_Debug_Card - ID ----
	EventList[EV_Debug_Card].EventCategory 				= Type_Debug;
	EventList[EV_Debug_Card].EventID 					= 300;

	EventList[EV_Debug_Card].EventActive 				= false;

	sprintf(EventList[EV_Debug_Card].EventName, "Tech Card Inserted");

	EventList[EV_Debug_Card].TimeStampSystic 			= 0;

	EventList[EV_Debug_Card].EventAction1 				= Act_None;
	EventList[EV_Debug_Card].EventAction2 				= Act_None;
	EventList[EV_Debug_Card].EventAction3 				= Act_None;
	EventList[EV_Debug_Card].EventActionTime1_2 		= 0;
	EventList[EV_Debug_Card].EventActionTime2_3 		= 0;

	EventList[EV_Debug_Card].Processed 					= false;
	EventList[EV_Debug_Card].EventLogged 				= false;

	EventList[EV_Debug_Card].DispType 					= Disp_Icon;
	//EventList[EV_Debug_Card].ImageName 					= Icon_Attention;

	EventList[EV_Debug_Card].BuzzerRequired 			= false;
	//EventList[EV_Debug_Card].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Debug_Card].EventData, 0xFF, sizeof(EventList[EV_Debug_Card].EventData));
	EventList[EV_Debug_Card].AddtionalInfo				= NULL;

	EventList[EV_Debug_Card].TimeRequired = 0;
	EventList[EV_Debug_Card].ACKRequired = false;

	/*-------------------------------------------------------------------------------------------------------
	 * 											INTERNAL EVENTS
	 *-------------------------------------------------------------------------------------------------------*/
	// ---- Index - EV_NVRAMSPI_Fail - ID ----
	EventList[EV_NVRAMSPI_Fail].EventCategory 			= Type_Internal;
	EventList[EV_NVRAMSPI_Fail].EventID 				= 10;

	EventList[EV_NVRAMSPI_Fail].EventActive 			= false;

	sprintf(EventList[EV_NVRAMSPI_Fail].EventName, "NVRAM Fail");

	EventList[EV_NVRAMSPI_Fail].EventAction1 			= Act_DisplayOnly;
	EventList[EV_NVRAMSPI_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_NVRAMSPI_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_NVRAMSPI_Fail].EventActionTime1_2 		= 0;
	EventList[EV_NVRAMSPI_Fail].EventActionTime2_3 		= 0;

	EventList[EV_NVRAMSPI_Fail].Processed				= false;
	EventList[EV_NVRAMSPI_Fail].EventLogged				= false;

	EventList[EV_NVRAMSPI_Fail].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_NVRAMSPI_Fail].ImageName 				= Icon_Attention;

	EventList[EV_NVRAMSPI_Fail].BuzzerRequired 			= true;
	//EventList[EV_NVRAMSPI_Fail].BuzzerMode 				= Buzz_Medium;

	memset(EventList[EV_NVRAMSPI_Fail].EventData, 0xFF, sizeof(EventList[EV_NVRAMSPI_Fail].EventData));
	EventList[EV_NVRAMSPI_Fail].AddtionalInfo				= NULL;

	EventList[EV_NVRAMSPI_Fail].TimeRequired = 0;
	EventList[EV_NVRAMSPI_Fail].ACKRequired = false;

	// ---- Index - EV_NVRAMSPI_OK - ID ----
	EventList[EV_NVRAMSPI_OK].EventCategory 			= Type_Internal;
	EventList[EV_NVRAMSPI_OK].EventID 					= 11;

	EventList[EV_NVRAMSPI_OK].EventActive 				= false;

	sprintf(EventList[EV_NVRAMSPI_OK].EventName, "NVRAM OK");

	EventList[EV_NVRAMSPI_OK].EventAction1 				= Act_None;
	EventList[EV_NVRAMSPI_OK].EventAction2 				= Act_None;
	EventList[EV_NVRAMSPI_OK].EventAction3 				= Act_None;
	EventList[EV_NVRAMSPI_OK].EventActionTime1_2 		= 0;
	EventList[EV_NVRAMSPI_OK].EventActionTime2_3 		= 0;

	EventList[EV_NVRAMSPI_OK].Processed					= false;
	EventList[EV_NVRAMSPI_OK].EventLogged				= false;

	EventList[EV_NVRAMSPI_OK].DispType 					= Disp_None;
	//EventList[EV_NVRAMSPI_OK].ImageName 				= Icon_Attention;

	EventList[EV_NVRAMSPI_OK].BuzzerRequired 			= false;
	//EventList[EV_NVRAMSPI_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_NVRAMSPI_OK].EventData, 0xFF, sizeof(EventList[EV_NVRAMSPI_OK].EventData));
	EventList[EV_NVRAMSPI_OK].AddtionalInfo				= NULL;

	EventList[EV_NVRAMSPI_OK].TimeRequired = 0;
	EventList[EV_NVRAMSPI_OK].ACKRequired = false;

	// ---- Index - EV_RTCSPI_Fail - ID ----
	EventList[EV_RTCSPI_Fail].EventCategory 			= Type_Internal;
	EventList[EV_RTCSPI_Fail].EventID 					= 12;

	EventList[EV_RTCSPI_Fail].EventActive 				= false;

	sprintf(EventList[EV_RTCSPI_Fail].EventName, "RTC Fail");

	EventList[EV_RTCSPI_Fail].EventAction1 				= Act_DisplayOnly;
	EventList[EV_RTCSPI_Fail].EventAction2 				= Act_ForceStop;
	EventList[EV_RTCSPI_Fail].EventAction3 				= Act_ForceStop;
	EventList[EV_RTCSPI_Fail].EventActionTime1_2 		= 0;
	EventList[EV_RTCSPI_Fail].EventActionTime2_3 		= 0;

	EventList[EV_RTCSPI_Fail].Processed					= false;
	EventList[EV_RTCSPI_Fail].EventLogged				= false;

	EventList[EV_RTCSPI_Fail].DispType 					= Disp_Generic_FullScreen;
	//EventList[EV_RTCSPI_Fail].ImageName 				= Icon_Attention;

	EventList[EV_RTCSPI_Fail].BuzzerRequired 			= true;
	//EventList[EV_RTCSPI_Fail].BuzzerMode 				= Buzz_Medium;

	memset(EventList[EV_RTCSPI_Fail].EventData, 0xFF, sizeof(EventList[EV_RTCSPI_Fail].EventData));
	EventList[EV_RTCSPI_Fail].AddtionalInfo				= NULL;

	EventList[EV_RTCSPI_Fail].TimeRequired = 0;
	EventList[EV_RTCSPI_Fail].ACKRequired = false;

	// ---- Index - EV_RTCSPI_OK - ID ----
	EventList[EV_RTCSPI_OK].EventCategory 				= Type_Internal;
	EventList[EV_RTCSPI_OK].EventID 					= 13;

	EventList[EV_RTCSPI_OK].EventActive 				= false;

	sprintf(EventList[EV_RTCSPI_OK].EventName, "RTC OK");

	EventList[EV_RTCSPI_OK].EventAction1 				= Act_None;
	EventList[EV_RTCSPI_OK].EventAction2 				= Act_None;
	EventList[EV_RTCSPI_OK].EventAction3 				= Act_None;
	EventList[EV_RTCSPI_OK].EventActionTime1_2 			= 0;
	EventList[EV_RTCSPI_OK].EventActionTime2_3 			= 0;

	EventList[EV_RTCSPI_OK].Processed					= false;
	EventList[EV_RTCSPI_OK].EventLogged					= false;

	EventList[EV_RTCSPI_OK].DispType 					= Disp_None;
	//EventList[EV_RTCSPI_OK].ImageName 					= Icon_Attention;

	EventList[EV_RTCSPI_OK].BuzzerRequired 				= false;
	//EventList[EV_RTCSPI_OK].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_RTCSPI_OK].EventData, 0xFF, sizeof(EventList[EV_RTCSPI_OK].EventData));
	EventList[EV_RTCSPI_OK].AddtionalInfo				= NULL;

	EventList[EV_RTCSPI_OK].TimeRequired = 0;
	EventList[EV_RTCSPI_OK].ACKRequired = false;

	// ---- Index - EV_SystemTime_Fail - ID ----
	EventList[EV_SystemTime_Fail].EventCategory 		= Type_Internal;
	EventList[EV_SystemTime_Fail].EventID 				= 14;

	EventList[EV_SystemTime_Fail].EventActive 			= false;

	sprintf(EventList[EV_SystemTime_Fail].EventName, "System Time Fail");

	EventList[EV_SystemTime_Fail].EventAction1 			= Act_DisplayOnly;
	EventList[EV_SystemTime_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_SystemTime_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_SystemTime_Fail].EventActionTime1_2 	= 0;
	EventList[EV_SystemTime_Fail].EventActionTime2_3 	= 0;

	EventList[EV_SystemTime_Fail].Processed				= false;
	EventList[EV_SystemTime_Fail].EventLogged			= false;

	EventList[EV_SystemTime_Fail].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_SystemTime_Fail].ImageName 			= Icon_Attention;

	EventList[EV_SystemTime_Fail].BuzzerRequired 		= true;
	//EventList[EV_SystemTime_Fail].BuzzerMode 			= Buzz_Medium;

	memset(EventList[EV_SystemTime_Fail].EventData, 0xFF, sizeof(EventList[EV_SystemTime_Fail].EventData));
	EventList[EV_SystemTime_Fail].AddtionalInfo			= NULL;

	EventList[EV_SystemTime_Fail].TimeRequired = 0;
	EventList[EV_SystemTime_Fail].ACKRequired = false;

	// ---- Index - EV_SystemTime_OK - ID ----
	EventList[EV_SystemTime_OK].EventCategory 			= Type_Internal;
	EventList[EV_SystemTime_OK].EventID 				= 15;

	EventList[EV_SystemTime_OK].EventActive 			= false;

	sprintf(EventList[EV_SystemTime_OK].EventName, "System Time OK");

	EventList[EV_SystemTime_OK].EventAction1 			= Act_None;
	EventList[EV_SystemTime_OK].EventAction2 			= Act_None;
	EventList[EV_SystemTime_OK].EventAction3 			= Act_None;
	EventList[EV_SystemTime_OK].EventActionTime1_2 		= 0;
	EventList[EV_SystemTime_OK].EventActionTime2_3 		= 0;

	EventList[EV_SystemTime_OK].Processed				= false;
	EventList[EV_SystemTime_OK].EventLogged				= false;

	EventList[EV_SystemTime_OK].DispType 				= Disp_None;
	//EventList[EV_SystemTime_OK].ImageName 				= Icon_Attention;

	EventList[EV_SystemTime_OK].BuzzerRequired 			= false;
	//EventList[EV_SystemTime_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_SystemTime_OK].EventData, 0xFF, sizeof(EventList[EV_SystemTime_OK].EventData));
	EventList[EV_SystemTime_OK].AddtionalInfo			= NULL;

	EventList[EV_SystemTime_OK].TimeRequired = 0;
	EventList[EV_SystemTime_OK].ACKRequired = false;

	// ---- Index - EV_AmbientSensor_Fail - ID ----
	EventList[EV_AmbientSensor_Fail].EventCategory 		= Type_Internal;
	EventList[EV_AmbientSensor_Fail].EventID 			= 16;

	EventList[EV_AmbientSensor_Fail].EventActive 		= false;

	sprintf(EventList[EV_AmbientSensor_Fail].EventName, "Light Sensor Fail");

	EventList[EV_AmbientSensor_Fail].EventAction1 		= Act_None;
	EventList[EV_AmbientSensor_Fail].EventAction2 		= Act_None;
	EventList[EV_AmbientSensor_Fail].EventAction3 		= Act_None;
	EventList[EV_AmbientSensor_Fail].EventActionTime1_2 = 0;
	EventList[EV_AmbientSensor_Fail].EventActionTime2_3 = 0;

	EventList[EV_AmbientSensor_Fail].Processed			= false;
	EventList[EV_AmbientSensor_Fail].EventLogged		= false;

	EventList[EV_AmbientSensor_Fail].DispType 			= Disp_Message;
	//EventList[EV_AmbientSensor_Fail].ImageName 			= Icon_Attention;

	EventList[EV_AmbientSensor_Fail].BuzzerRequired 	= false;
	//EventList[EV_AmbientSensor_Fail].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_AmbientSensor_Fail].EventData, 0xFF, sizeof(EventList[EV_AmbientSensor_Fail].EventData));
	EventList[EV_AmbientSensor_Fail].AddtionalInfo			= NULL;

	EventList[EV_AmbientSensor_Fail].TimeRequired = 0;
	EventList[EV_AmbientSensor_Fail].ACKRequired = false;

	// ---- Index - EV_AmbientSensor_OK - ID ----
	EventList[EV_AmbientSensor_OK].EventCategory 		= Type_Internal;
	EventList[EV_AmbientSensor_OK].EventID 				= 17;

	EventList[EV_AmbientSensor_OK].EventActive 			= false;

	sprintf(EventList[EV_AmbientSensor_OK].EventName, "Light Sensor OK");

	EventList[EV_AmbientSensor_OK].EventAction1 		= Act_None;
	EventList[EV_AmbientSensor_OK].EventAction2 		= Act_None;
	EventList[EV_AmbientSensor_OK].EventAction3 		= Act_None;
	EventList[EV_AmbientSensor_OK].EventActionTime1_2 	= 0;
	EventList[EV_AmbientSensor_OK].EventActionTime2_3 	= 0;

	EventList[EV_AmbientSensor_OK].Processed			= false;
	EventList[EV_AmbientSensor_OK].EventLogged			= false;

	EventList[EV_AmbientSensor_OK].DispType 			= Disp_None;
	//EventList[EV_AmbientSensor_OK].ImageName 			= Icon_Attention;
	EventList[EV_AmbientSensor_OK].SplashTime			= 0;
	EventList[EV_AmbientSensor_OK].SplashActive			= false;

	EventList[EV_AmbientSensor_OK].BuzzerRequired 		= true;
	//EventList[EV_AmbientSensor_OK].BuzzerMode 			= Buzz_Medium;

	memset(EventList[EV_AmbientSensor_OK].EventData, 0xFF, sizeof(EventList[EV_AmbientSensor_OK].EventData));
	EventList[EV_AmbientSensor_OK].AddtionalInfo		= NULL;

	EventList[EV_AmbientSensor_OK].TimeRequired = 0;
	EventList[EV_AmbientSensor_OK].ACKRequired = false;

	// ---- Index - EV_Parameter_Fail - ID ----
	EventList[EV_Parameter_Fail].EventCategory 			= Type_Internal;
	EventList[EV_Parameter_Fail].EventID 				= 20;

	EventList[EV_Parameter_Fail].EventActive 			= false;

	sprintf(EventList[EV_Parameter_Fail].EventName, "Parameters Mismatch");

	EventList[EV_Parameter_Fail].EventAction1 			= Act_None;
	EventList[EV_Parameter_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_Parameter_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_Parameter_Fail].EventActionTime1_2 	= 0;
	EventList[EV_Parameter_Fail].EventActionTime2_3 	= 0;

	EventList[EV_Parameter_Fail].Processed 				= false;
	EventList[EV_Parameter_Fail].EventLogged			= false;

	EventList[EV_Parameter_Fail].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_Parameter_Fail].ImageName 				= Icon_Attention;
	EventList[EV_Parameter_Fail].SplashTime				= 0;
	EventList[EV_Parameter_Fail].SplashActive			= false;

	EventList[EV_Parameter_Fail].BuzzerRequired 		= true;
	//EventList[EV_Parameter_Fail].BuzzerMode 			= Buzz_Fast;

	memset(EventList[EV_Parameter_Fail].EventData, 0xFF, sizeof(EventList[EV_Parameter_Fail].EventData));
	EventList[EV_Parameter_Fail].AddtionalInfo			= NULL;

	EventList[EV_Parameter_Fail].TimeRequired = 0;
	EventList[EV_Parameter_Fail].ACKRequired = false;

	// ---- Index - EV_Parameter_OK - ID ----
	EventList[EV_Parameter_OK].EventCategory 			= Type_Internal;
	EventList[EV_Parameter_OK].EventID 					= 21;

	EventList[EV_Parameter_OK].EventActive 				= false;

	sprintf(EventList[EV_Parameter_OK].EventName, "Parameters OK");

	EventList[EV_Parameter_OK].EventAction1 			= Act_None;
	EventList[EV_Parameter_OK].EventAction2 			= Act_None;
	EventList[EV_Parameter_OK].EventAction3 			= Act_None;
	EventList[EV_Parameter_OK].EventActionTime1_2 		= 0;
	EventList[EV_Parameter_OK].EventActionTime2_3 		= 0;

	EventList[EV_Parameter_OK].Processed 				= false;
	EventList[EV_Parameter_OK].EventLogged				= false;

	EventList[EV_Parameter_OK].DispType 				= Disp_None;
	//EventList[EV_Parameter_OK].ImageName 				= Icon_Attention;
	EventList[EV_Parameter_OK].SplashTime				= 0;
	EventList[EV_Parameter_OK].SplashActive				= false;

	EventList[EV_Parameter_OK].BuzzerRequired 			= false;
	//EventList[EV_Parameter_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Parameter_OK].EventData, 0xFF, sizeof(EventList[EV_Parameter_OK].EventData));
	EventList[EV_Parameter_OK].AddtionalInfo			= NULL;

	EventList[EV_Parameter_OK].TimeRequired = 0;
	EventList[EV_Parameter_OK].ACKRequired = false;

	// ---- Index - EV_Revison_Fail - ID ----
	EventList[EV_Revison_Fail].EventCategory 			= Type_Internal;
	EventList[EV_Revison_Fail].EventID 					= 22;

	EventList[EV_Revison_Fail].EventActive 				= false;

	sprintf(EventList[EV_Revison_Fail].EventName, "Revision Mismatch");

	EventList[EV_Revison_Fail].EventAction1 			= Act_None;
	EventList[EV_Revison_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_Revison_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_Revison_Fail].EventActionTime1_2 		= 0;
	EventList[EV_Revison_Fail].EventActionTime2_3 		= 0;

	EventList[EV_Revison_Fail].Processed 				= false;
	EventList[EV_Revison_Fail].EventLogged				= false;

	EventList[EV_Revison_Fail].DispType 				= Disp_Generic_FullScreen;
	EventList[EV_Revison_Fail].SplashTime				= 0;
	EventList[EV_Revison_Fail].SplashActive				= false;
	//EventList[EV_Revison_Fail].ImageName 				= Icon_Attention;

	EventList[EV_Revison_Fail].BuzzerRequired 			= true;
	//EventList[EV_Revison_Fail].BuzzerMode 				= Buzz_Fast;

	memset(EventList[EV_Revison_Fail].EventData, 0xFF, sizeof(EventList[EV_Revison_Fail].EventData));
	EventList[EV_Revison_Fail].AddtionalInfo			= NULL;

	EventList[EV_Revison_Fail].TimeRequired = 0;
	EventList[EV_Revison_Fail].ACKRequired = false;

	// ---- Index - EV_Revison_OK - ID ----
	EventList[EV_Revison_OK].EventCategory 				= Type_Internal;
	EventList[EV_Revison_OK].EventID 					= 23;

	EventList[EV_Revison_OK].EventActive 				= false;

	sprintf(EventList[EV_Revison_OK].EventName, "Revision OK");

	EventList[EV_Revison_OK].EventAction1 				= Act_None;
	EventList[EV_Revison_OK].EventAction2 				= Act_None;
	EventList[EV_Revison_OK].EventAction3 				= Act_None;
	EventList[EV_Revison_OK].EventActionTime1_2 		= 0;
	EventList[EV_Revison_OK].EventActionTime2_3 		= 0;

	EventList[EV_Revison_OK].Processed 					= false;
	EventList[EV_Revison_OK].EventLogged				= false;

	EventList[EV_Revison_OK].DispType 					= Disp_None;
	EventList[EV_Revison_OK].SplashTime					= 0;
	EventList[EV_Revison_OK].SplashActive				= false;
	//EventList[EV_Revison_OK].ImageName 					= Icon_Attention;

	EventList[EV_Revison_OK].BuzzerRequired 			= false;
	//EventList[EV_Revison_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Revison_OK].EventData, 0xFF, sizeof(EventList[EV_Revison_OK].EventData));
	EventList[EV_Revison_OK].AddtionalInfo			= NULL;

	EventList[EV_Revison_OK].TimeRequired = 0;
	EventList[EV_Revison_OK].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_1_Fail - ID ----
	EventList[EV_Exp_Mod_1_Fail].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_1_Fail].EventID 				= 30;

	EventList[EV_Exp_Mod_1_Fail].EventActive			= false;

	sprintf(EventList[EV_Exp_Mod_1_Fail].EventName, "Expansion 01 Fail");

	EventList[EV_Exp_Mod_1_Fail].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_1_Fail].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_1_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_Exp_Mod_1_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_Exp_Mod_1_Fail].EventActionTime1_2		= 0;
	EventList[EV_Exp_Mod_1_Fail].EventActionTime2_3		= 0;

	EventList[EV_Exp_Mod_1_Fail].Processed 				= false;
	EventList[EV_Exp_Mod_1_Fail].EventLogged 			= false;

	EventList[EV_Exp_Mod_1_Fail].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_Exp_Mod_1_Fail].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_1_Fail].SplashTime 			= 0;
	EventList[EV_Exp_Mod_1_Fail].SplashActive 			= false;

	EventList[EV_Exp_Mod_1_Fail].BuzzerRequired 		= true;
	//EventList[EV_Exp_Mod_1_Fail].BuzzerMode 			= Buzz_Fast;

	memset(EventList[EV_Exp_Mod_1_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_1_Fail].EventData));
	EventList[EV_Exp_Mod_1_Fail].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_1_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_1_Fail].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_2_Fail - ID ----
	EventList[EV_Exp_Mod_2_Fail].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_2_Fail].EventID 				= 31;

	EventList[EV_Exp_Mod_2_Fail].EventActive			= false;

	sprintf(EventList[EV_Exp_Mod_2_Fail].EventName, "Expansion 02 Fail");

	EventList[EV_Exp_Mod_2_Fail].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_2_Fail].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_2_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_Exp_Mod_2_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_Exp_Mod_2_Fail].EventActionTime1_2		= 0;
	EventList[EV_Exp_Mod_2_Fail].EventActionTime2_3		= 0;

	EventList[EV_Exp_Mod_2_Fail].Processed 				= false;
	EventList[EV_Exp_Mod_2_Fail].EventLogged 			= false;

	EventList[EV_Exp_Mod_2_Fail].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_Exp_Mod_2_Fail].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_2_Fail].SplashTime 			= 0;
	EventList[EV_Exp_Mod_2_Fail].SplashActive 			= false;

	EventList[EV_Exp_Mod_2_Fail].BuzzerRequired 		= true;
	//EventList[EV_Exp_Mod_2_Fail].BuzzerMode 			= Buzz_Fast;

	memset(EventList[EV_Exp_Mod_2_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_2_Fail].EventData));
	EventList[EV_Exp_Mod_2_Fail].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_2_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_2_Fail].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_3_Fail - ID ----
	EventList[EV_Exp_Mod_3_Fail].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_3_Fail].EventID 				= 32;

	EventList[EV_Exp_Mod_3_Fail].EventActive			= false;

	sprintf(EventList[EV_Exp_Mod_3_Fail].EventName, "Expansion 03 Fail");

	EventList[EV_Exp_Mod_3_Fail].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_3_Fail].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_3_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_Exp_Mod_3_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_Exp_Mod_3_Fail].EventActionTime1_2		= 0;
	EventList[EV_Exp_Mod_3_Fail].EventActionTime2_3		= 0;

	EventList[EV_Exp_Mod_3_Fail].Processed 				= false;
	EventList[EV_Exp_Mod_3_Fail].EventLogged 			= false;

	EventList[EV_Exp_Mod_3_Fail].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_Exp_Mod_3_Fail].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_3_Fail].SplashTime 			= 0;
	EventList[EV_Exp_Mod_3_Fail].SplashActive 			= false;

	EventList[EV_Exp_Mod_3_Fail].BuzzerRequired 		= true;
	//EventList[EV_Exp_Mod_3_Fail].BuzzerMode 			= Buzz_Fast;

	memset(EventList[EV_Exp_Mod_3_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_3_Fail].EventData));
	EventList[EV_Exp_Mod_3_Fail].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_3_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_3_Fail].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_4_Fail - ID ----
	EventList[EV_Exp_Mod_4_Fail].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_4_Fail].EventID 				= 33;

	EventList[EV_Exp_Mod_4_Fail].EventActive			= false;

	sprintf(EventList[EV_Exp_Mod_4_Fail].EventName, "Expansion 04 Fail");

	EventList[EV_Exp_Mod_4_Fail].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_4_Fail].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_4_Fail].EventAction2 			= Act_ForceStop;
	EventList[EV_Exp_Mod_4_Fail].EventAction3 			= Act_ForceStop;
	EventList[EV_Exp_Mod_4_Fail].EventActionTime1_2		= 0;
	EventList[EV_Exp_Mod_4_Fail].EventActionTime2_3		= 0;

	EventList[EV_Exp_Mod_4_Fail].Processed 				= false;
	EventList[EV_Exp_Mod_4_Fail].EventLogged 			= false;

	EventList[EV_Exp_Mod_4_Fail].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_Exp_Mod_4_Fail].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_4_Fail].SplashTime 			= 0;
	EventList[EV_Exp_Mod_4_Fail].SplashActive 			= false;

	EventList[EV_Exp_Mod_4_Fail].BuzzerRequired 		= true;
	//EventList[EV_Exp_Mod_4_Fail].BuzzerMode 			= Buzz_Fast;

	memset(EventList[EV_Exp_Mod_4_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_4_Fail].EventData));
	EventList[EV_Exp_Mod_4_Fail].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_4_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_4_Fail].ACKRequired = false;

	// ---- Index - EV_Expansion_Module_1_OK - ID ----
	EventList[EV_Exp_Mod_1_OK].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_1_OK].EventID 					= 34;

	EventList[EV_Exp_Mod_1_OK].EventActive 				= false;

	sprintf(EventList[EV_Exp_Mod_1_OK].EventName, "Expansion 01 OK");

	EventList[EV_Exp_Mod_1_OK].TimeStampSystic 			= 0;

	EventList[EV_Exp_Mod_1_OK].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_1_OK].EventAction2 			= Act_None;
	EventList[EV_Exp_Mod_1_OK].EventAction3 			= Act_None;
	EventList[EV_Exp_Mod_1_OK].EventActionTime1_2 		= 0;
	EventList[EV_Exp_Mod_1_OK].EventActionTime2_3 		= 0;

	EventList[EV_Exp_Mod_1_OK].Processed 				= false;
	EventList[EV_Exp_Mod_1_OK].EventLogged 				= false;

	EventList[EV_Exp_Mod_1_OK].DispType 				= Disp_None;
	//EventList[EV_Exp_Mod_1_OK].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_1_OK].SplashTime 				= 0;
	EventList[EV_Exp_Mod_1_OK].SplashActive 			= false;

	EventList[EV_Exp_Mod_1_OK].BuzzerRequired 			= false;
	//EventList[EV_Exp_Mod_1_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Exp_Mod_1_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_1_OK].EventData));
	EventList[EV_Exp_Mod_1_OK].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_1_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_1_OK].ACKRequired = false;

	// ---- Index - EV_Expansion_Module_2_OK - ID ----
	EventList[EV_Exp_Mod_2_OK].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_2_OK].EventID 					= 35;

	EventList[EV_Exp_Mod_2_OK].EventActive 				= false;

	sprintf(EventList[EV_Exp_Mod_2_OK].EventName, "Expansion 02 OK");

	EventList[EV_Exp_Mod_2_OK].TimeStampSystic 			= 0;

	EventList[EV_Exp_Mod_2_OK].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_2_OK].EventAction2 			= Act_None;
	EventList[EV_Exp_Mod_2_OK].EventAction3 			= Act_None;
	EventList[EV_Exp_Mod_2_OK].EventActionTime1_2 		= 0;
	EventList[EV_Exp_Mod_2_OK].EventActionTime2_3 		= 0;

	EventList[EV_Exp_Mod_2_OK].Processed 				= false;
	EventList[EV_Exp_Mod_2_OK].EventLogged 				= false;

	EventList[EV_Exp_Mod_2_OK].DispType 				= Disp_None;
	//EventList[EV_Exp_Mod_2_OK].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_2_OK].SplashTime 				= 0;
	EventList[EV_Exp_Mod_2_OK].SplashActive 			= false;

	EventList[EV_Exp_Mod_2_OK].BuzzerRequired 			= false;
	//EventList[EV_Exp_Mod_2_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Exp_Mod_2_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_2_OK].EventData));
	EventList[EV_Exp_Mod_2_OK].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_2_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_2_OK].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_3_OK - ID ----
	EventList[EV_Exp_Mod_3_OK].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_3_OK].EventID 					= 36;

	EventList[EV_Exp_Mod_3_OK].EventActive 				= false;

	sprintf(EventList[EV_Exp_Mod_3_OK].EventName, "Expansion 03 OK");

	EventList[EV_Exp_Mod_3_OK].TimeStampSystic 			= 0;

	EventList[EV_Exp_Mod_3_OK].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_3_OK].EventAction2 			= Act_None;
	EventList[EV_Exp_Mod_3_OK].EventAction3 			= Act_None;
	EventList[EV_Exp_Mod_3_OK].EventActionTime1_2 		= 0;
	EventList[EV_Exp_Mod_3_OK].EventActionTime2_3 		= 0;

	EventList[EV_Exp_Mod_3_OK].Processed 				= false;
	EventList[EV_Exp_Mod_3_OK].EventLogged 				= false;

	EventList[EV_Exp_Mod_3_OK].DispType 				= Disp_None;
	//EventList[EV_Exp_Mod_3_OK].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_3_OK].SplashTime 				= 0;
	EventList[EV_Exp_Mod_3_OK].SplashActive 			= false;

	EventList[EV_Exp_Mod_3_OK].BuzzerRequired 			= false;
	//EventList[EV_Exp_Mod_3_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Exp_Mod_3_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_3_OK].EventData));
	EventList[EV_Exp_Mod_3_OK].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_3_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_3_OK].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_4_OK - ID ----
	EventList[EV_Exp_Mod_4_OK].EventCategory 			= Type_Internal;
	EventList[EV_Exp_Mod_4_OK].EventID 					= 37;

	EventList[EV_Exp_Mod_4_OK].EventActive 				= false;

	sprintf(EventList[EV_Exp_Mod_4_OK].EventName, "Expansion 04 OK");

	EventList[EV_Exp_Mod_4_OK].TimeStampSystic 			= 0;

	EventList[EV_Exp_Mod_4_OK].EventAction1 			= Act_None;
	EventList[EV_Exp_Mod_4_OK].EventAction2 			= Act_None;
	EventList[EV_Exp_Mod_4_OK].EventAction3 			= Act_None;
	EventList[EV_Exp_Mod_4_OK].EventActionTime1_2 		= 0;
	EventList[EV_Exp_Mod_4_OK].EventActionTime2_3 		= 0;

	EventList[EV_Exp_Mod_4_OK].Processed 				= false;
	EventList[EV_Exp_Mod_4_OK].EventLogged 				= false;

	EventList[EV_Exp_Mod_4_OK].DispType 				= Disp_None;
	//EventList[EV_Exp_Mod_4_OK].ImageName 				= Icon_Attention;
	EventList[EV_Exp_Mod_4_OK].SplashTime 				= 0;
	EventList[EV_Exp_Mod_4_OK].SplashActive 			= false;

	EventList[EV_Exp_Mod_4_OK].BuzzerRequired 			= false;
	//EventList[EV_Exp_Mod_4_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Exp_Mod_4_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_4_OK].EventData));
	EventList[EV_Exp_Mod_4_OK].AddtionalInfo			= NULL;

	EventList[EV_Exp_Mod_4_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_4_OK].ACKRequired = false;


	/*-------------------------------------------------------------------------------------------------------
	 * 										  System Events
	 *-------------------------------------------------------------------------------------------------------*/

	// ---- Index - EV_Exp_Mod_1_Ant_Fail - ID ----
	EventList[EV_Exp_Mod_1_Ant_Fail].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_1_Ant_Fail].EventID 			= 50;

	EventList[EV_Exp_Mod_1_Ant_Fail].EventActive 		= false;

	sprintf(EventList[EV_Exp_Mod_1_Ant_Fail].EventName, "Antenna (Exp01) Fail");

	EventList[EV_Exp_Mod_1_Ant_Fail].TimeStampSystic 	= 0;

	EventList[EV_Exp_Mod_1_Ant_Fail].EventAction1 		= Act_DisplayOnly;
	EventList[EV_Exp_Mod_1_Ant_Fail].EventAction2 		= Act_ForceStop;
	EventList[EV_Exp_Mod_1_Ant_Fail].EventAction3 		= Act_ForceStop;
	EventList[EV_Exp_Mod_1_Ant_Fail].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_1_Ant_Fail].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_1_Ant_Fail].Processed 			= false;
	EventList[EV_Exp_Mod_1_Ant_Fail].EventLogged 		= false;

	EventList[EV_Exp_Mod_1_Ant_Fail].DispType 			= Disp_Generic_FullScreen;
	//EventList[EV_Exp_Mod_1_Ant_Fail].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_1_Ant_Fail].SplashTime 		= 0;
	EventList[EV_Exp_Mod_1_Ant_Fail].SplashActive 		= false;

	EventList[EV_Exp_Mod_1_Ant_Fail].BuzzerRequired 	= true;
	//EventList[EV_Exp_Mod_1_Ant_Fail].BuzzerMode 		= Buzz_Fast;

	memset(EventList[EV_Exp_Mod_1_Ant_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_1_Ant_Fail].EventData));
	EventList[EV_Exp_Mod_1_Ant_Fail].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_1_Ant_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_1_Ant_Fail].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_2_Ant_Fail - ID ----
	EventList[EV_Exp_Mod_2_Ant_Fail].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_2_Ant_Fail].EventID 			= 51;

	EventList[EV_Exp_Mod_2_Ant_Fail].EventActive 		= false;

	sprintf(EventList[EV_Exp_Mod_2_Ant_Fail].EventName, "Antenna (Exp02) Fail");

	EventList[EV_Exp_Mod_2_Ant_Fail].TimeStampSystic 	= 0;

	EventList[EV_Exp_Mod_2_Ant_Fail].EventAction1 		= Act_DisplayOnly;
	EventList[EV_Exp_Mod_2_Ant_Fail].EventAction2 		= Act_ForceStop;
	EventList[EV_Exp_Mod_2_Ant_Fail].EventAction3 		= Act_ForceStop;
	EventList[EV_Exp_Mod_2_Ant_Fail].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_2_Ant_Fail].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_2_Ant_Fail].Processed 			= false;
	EventList[EV_Exp_Mod_2_Ant_Fail].EventLogged 		= false;

	EventList[EV_Exp_Mod_2_Ant_Fail].DispType 			= Disp_Generic_FullScreen;
	//EventList[EV_Exp_Mod_2_Ant_Fail].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_2_Ant_Fail].SplashTime 		= 0;
	EventList[EV_Exp_Mod_2_Ant_Fail].SplashActive 		= false;

	EventList[EV_Exp_Mod_2_Ant_Fail].BuzzerRequired 	= true;
	//EventList[EV_Exp_Mod_2_Ant_Fail].BuzzerMode 		= Buzz_Fast;

	memset(EventList[EV_Exp_Mod_2_Ant_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_2_Ant_Fail].EventData));
	EventList[EV_Exp_Mod_2_Ant_Fail].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_2_Ant_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_2_Ant_Fail].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_3_Ant_Fail - ID ----
	EventList[EV_Exp_Mod_3_Ant_Fail].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_3_Ant_Fail].EventID 			= 52;

	EventList[EV_Exp_Mod_3_Ant_Fail].EventActive 		= false;

	sprintf(EventList[EV_Exp_Mod_3_Ant_Fail].EventName, "Antenna (Exp03) Fail");

	EventList[EV_Exp_Mod_3_Ant_Fail].TimeStampSystic 	= 0;

	EventList[EV_Exp_Mod_3_Ant_Fail].EventAction1 		= Act_None;
	EventList[EV_Exp_Mod_3_Ant_Fail].EventAction2 		= Act_None;
	EventList[EV_Exp_Mod_3_Ant_Fail].EventAction3 		= Act_None;
	EventList[EV_Exp_Mod_3_Ant_Fail].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_3_Ant_Fail].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_3_Ant_Fail].Processed 			= false;
	EventList[EV_Exp_Mod_3_Ant_Fail].EventLogged 		= false;

	EventList[EV_Exp_Mod_3_Ant_Fail].DispType 			= Disp_None;
	//EventList[EV_Exp_Mod_3_Ant_Fail].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_3_Ant_Fail].SplashTime 		= 0;
	EventList[EV_Exp_Mod_3_Ant_Fail].SplashActive 		= false;

	EventList[EV_Exp_Mod_3_Ant_Fail].BuzzerRequired 	= false;
	//EventList[EV_Exp_Mod_3_Ant_Fail].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_Exp_Mod_3_Ant_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_3_Ant_Fail].EventData));
	EventList[EV_Exp_Mod_3_Ant_Fail].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_3_Ant_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_3_Ant_Fail].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_4_Ant_Fail - ID ----
	EventList[EV_Exp_Mod_4_Ant_Fail].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_4_Ant_Fail].EventID 			= 53;

	EventList[EV_Exp_Mod_4_Ant_Fail].EventActive 		= false;

	sprintf(EventList[EV_Exp_Mod_4_Ant_Fail].EventName, "Antenna (Exp04) Fail");

	EventList[EV_Exp_Mod_4_Ant_Fail].TimeStampSystic 	= 0;

	EventList[EV_Exp_Mod_4_Ant_Fail].EventAction1 		= Act_None;
	EventList[EV_Exp_Mod_4_Ant_Fail].EventAction2 		= Act_None;
	EventList[EV_Exp_Mod_4_Ant_Fail].EventAction3 		= Act_None;
	EventList[EV_Exp_Mod_4_Ant_Fail].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_4_Ant_Fail].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_4_Ant_Fail].Processed 			= false;
	EventList[EV_Exp_Mod_4_Ant_Fail].EventLogged 		= false;

	EventList[EV_Exp_Mod_4_Ant_Fail].DispType 			= Disp_None;
	//EventList[EV_Exp_Mod_4_Ant_Fail].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_4_Ant_Fail].SplashTime 		= 0;
	EventList[EV_Exp_Mod_4_Ant_Fail].SplashActive 		= false;

	EventList[EV_Exp_Mod_4_Ant_Fail].BuzzerRequired 	= false;
	//EventList[EV_Exp_Mod_4_Ant_Fail].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_Exp_Mod_4_Ant_Fail].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_4_Ant_Fail].EventData));
	EventList[EV_Exp_Mod_4_Ant_Fail].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_4_Ant_Fail].TimeRequired = 0;
	EventList[EV_Exp_Mod_4_Ant_Fail].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_1_Ant_OK - ID ----
	EventList[EV_Exp_Mod_1_Ant_OK].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_1_Ant_OK].EventID 				= 54;

	EventList[EV_Exp_Mod_1_Ant_OK].EventActive 			= false;

	sprintf(EventList[EV_Exp_Mod_1_Ant_OK].EventName, "Antenna (Exp01) OK");

	EventList[EV_Exp_Mod_1_Ant_OK].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_1_Ant_OK].EventAction1 		= Act_None;
	EventList[EV_Exp_Mod_1_Ant_OK].EventAction2 		= Act_None;
	EventList[EV_Exp_Mod_1_Ant_OK].EventAction3 		= Act_None;
	EventList[EV_Exp_Mod_1_Ant_OK].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_1_Ant_OK].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_1_Ant_OK].Processed 			= false;
	EventList[EV_Exp_Mod_1_Ant_OK].EventLogged 			= false;

	EventList[EV_Exp_Mod_1_Ant_OK].DispType 			= Disp_None;
	//EventList[EV_Exp_Mod_1_Ant_OK].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_1_Ant_OK].SplashTime 			= 0;
	EventList[EV_Exp_Mod_1_Ant_OK].SplashActive 		= false;

	EventList[EV_Exp_Mod_1_Ant_OK].BuzzerRequired 		= false;
	//EventList[EV_Exp_Mod_1_Ant_OK].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Exp_Mod_1_Ant_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_1_Ant_OK].EventData));
	EventList[EV_Exp_Mod_1_Ant_OK].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_1_Ant_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_1_Ant_OK].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_2_Ant_OK - ID ----
	EventList[EV_Exp_Mod_2_Ant_OK].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_2_Ant_OK].EventID 				= 55;

	EventList[EV_Exp_Mod_2_Ant_OK].EventActive 			= false;

	sprintf(EventList[EV_Exp_Mod_2_Ant_OK].EventName, "Antenna (Exp02) OK");

	EventList[EV_Exp_Mod_2_Ant_OK].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_2_Ant_OK].EventAction1 		= Act_None;
	EventList[EV_Exp_Mod_2_Ant_OK].EventAction2 		= Act_None;
	EventList[EV_Exp_Mod_2_Ant_OK].EventAction3 		= Act_None;
	EventList[EV_Exp_Mod_2_Ant_OK].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_2_Ant_OK].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_2_Ant_OK].Processed 			= false;
	EventList[EV_Exp_Mod_2_Ant_OK].EventLogged 			= false;

	EventList[EV_Exp_Mod_2_Ant_OK].DispType 			= Disp_None;
	//EventList[EV_Exp_Mod_2_Ant_OK].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_2_Ant_OK].SplashTime 			= 0;
	EventList[EV_Exp_Mod_2_Ant_OK].SplashActive 		= false;

	EventList[EV_Exp_Mod_2_Ant_OK].BuzzerRequired 		= false;
	//EventList[EV_Exp_Mod_2_Ant_OK].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Exp_Mod_2_Ant_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_2_Ant_OK].EventData));
	EventList[EV_Exp_Mod_2_Ant_OK].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_2_Ant_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_2_Ant_OK].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_3_Ant_OK - ID ----
	EventList[EV_Exp_Mod_3_Ant_OK].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_3_Ant_OK].EventID 				= 56;

	EventList[EV_Exp_Mod_3_Ant_OK].EventActive 			= false;

	sprintf(EventList[EV_Exp_Mod_3_Ant_OK].EventName, "Antenna (Exp03) OK");

	EventList[EV_Exp_Mod_3_Ant_OK].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_3_Ant_OK].EventAction1 		= Act_None;
	EventList[EV_Exp_Mod_3_Ant_OK].EventAction2 		= Act_None;
	EventList[EV_Exp_Mod_3_Ant_OK].EventAction3 		= Act_None;
	EventList[EV_Exp_Mod_3_Ant_OK].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_3_Ant_OK].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_3_Ant_OK].Processed 			= false;
	EventList[EV_Exp_Mod_3_Ant_OK].EventLogged 			= false;

	EventList[EV_Exp_Mod_3_Ant_OK].DispType 			= Disp_None;
	//EventList[EV_Exp_Mod_3_Ant_OK].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_3_Ant_OK].SplashTime 			= 0;
	EventList[EV_Exp_Mod_3_Ant_OK].SplashActive 		= false;

	EventList[EV_Exp_Mod_3_Ant_OK].BuzzerRequired 		= false;
	//EventList[EV_Exp_Mod_3_Ant_OK].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Exp_Mod_3_Ant_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_3_Ant_OK].EventData));
	EventList[EV_Exp_Mod_3_Ant_OK].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_3_Ant_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_3_Ant_OK].ACKRequired = false;

	// ---- Index - EV_Exp_Mod_4_Ant_OK - ID ----
	EventList[EV_Exp_Mod_4_Ant_OK].EventCategory 		= Type_System;
	EventList[EV_Exp_Mod_4_Ant_OK].EventID 				= 57;

	EventList[EV_Exp_Mod_4_Ant_OK].EventActive 			= false;

	sprintf(EventList[EV_Exp_Mod_4_Ant_OK].EventName, "Antenna (Exp04) OK");

	EventList[EV_Exp_Mod_4_Ant_OK].TimeStampSystic 		= 0;

	EventList[EV_Exp_Mod_4_Ant_OK].EventAction1 		= Act_None;
	EventList[EV_Exp_Mod_4_Ant_OK].EventAction2 		= Act_None;
	EventList[EV_Exp_Mod_4_Ant_OK].EventAction3 		= Act_None;
	EventList[EV_Exp_Mod_4_Ant_OK].EventActionTime1_2	= 0;
	EventList[EV_Exp_Mod_4_Ant_OK].EventActionTime2_3	= 0;

	EventList[EV_Exp_Mod_4_Ant_OK].Processed 			= false;
	EventList[EV_Exp_Mod_4_Ant_OK].EventLogged 			= false;

	EventList[EV_Exp_Mod_4_Ant_OK].DispType 			= Disp_None;
	//EventList[EV_Exp_Mod_4_Ant_OK].ImageName 			= Icon_Attention;
	EventList[EV_Exp_Mod_4_Ant_OK].SplashTime 			= 0;
	EventList[EV_Exp_Mod_4_Ant_OK].SplashActive 		= false;

	EventList[EV_Exp_Mod_4_Ant_OK].BuzzerRequired 		= false;
	//EventList[EV_Exp_Mod_4_Ant_OK].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Exp_Mod_4_Ant_OK].EventData, 0xFF, sizeof(EventList[EV_Exp_Mod_4_Ant_OK].EventData));
	EventList[EV_Exp_Mod_4_Ant_OK].AddtionalInfo		= NULL;

	EventList[EV_Exp_Mod_4_Ant_OK].TimeRequired = 0;
	EventList[EV_Exp_Mod_4_Ant_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF01_Fail - ID ----
	EventList[EV_PulseDeviceRF01_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceRF01_Fail].EventID 			= 58;

	EventList[EV_PulseDeviceRF01_Fail].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF01_Fail].EventName, "RF Pulse300 Fail");

	EventList[EV_PulseDeviceRF01_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF01_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceRF01_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF01_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF01_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceRF01_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceRF01_Fail].Processed 		= false;
	EventList[EV_PulseDeviceRF01_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceRF01_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceRF01_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceRF01_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF01_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceRF01_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceRF01_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceRF01_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF01_Fail].EventData));
	EventList[EV_PulseDeviceRF01_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceRF01_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceRF01_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF02_Fail - ID ----
	EventList[EV_PulseDeviceRF02_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceRF02_Fail].EventID 			= 59;

	EventList[EV_PulseDeviceRF02_Fail].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF02_Fail].EventName, "RF Pulse500 RT Fail");

	EventList[EV_PulseDeviceRF02_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF02_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceRF02_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF02_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF02_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceRF02_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceRF02_Fail].Processed 		= false;
	EventList[EV_PulseDeviceRF02_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceRF02_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceRF02_Fail].ImageName		= Icon_Attention;
	EventList[EV_PulseDeviceRF02_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF02_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceRF02_Fail].BuzzerRequired	= true;
	//EventList[EV_PulseDeviceRF02_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceRF02_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF02_Fail].EventData));
	EventList[EV_PulseDeviceRF02_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceRF02_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceRF02_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF03_Fail - ID ----
	EventList[EV_PulseDeviceRF03_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceRF03_Fail].EventID 			= 60;

	EventList[EV_PulseDeviceRF03_Fail].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF03_Fail].EventName, "RF Pulse500 RR Fail");

	EventList[EV_PulseDeviceRF03_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF03_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceRF03_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF03_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF03_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceRF03_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceRF03_Fail].Processed 		= false;
	EventList[EV_PulseDeviceRF03_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceRF03_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceRF03_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceRF03_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF03_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceRF03_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceRF03_Fail].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceRF03_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF03_Fail].EventData));
	EventList[EV_PulseDeviceRF03_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceRF03_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceRF03_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF04_Fail - ID ----
	EventList[EV_PulseDeviceRF04_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceRF04_Fail].EventID 			= 61;

	EventList[EV_PulseDeviceRF04_Fail].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF04_Fail].EventName, "RF Pulse500 LT Fail");

	EventList[EV_PulseDeviceRF04_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF04_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceRF04_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF04_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF04_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceRF04_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceRF04_Fail].Processed 		= false;
	EventList[EV_PulseDeviceRF04_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceRF04_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceRF04_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceRF04_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF04_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceRF04_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceRF04_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceRF04_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF04_Fail].EventData));
	EventList[EV_PulseDeviceRF04_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceRF04_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceRF04_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF05_Fail - ID ----
	EventList[EV_PulseDeviceRF05_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceRF05_Fail].EventID 			= 62;

	EventList[EV_PulseDeviceRF05_Fail].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF05_Fail].EventName, "RF Pulse500 FT Fail");

	EventList[EV_PulseDeviceRF05_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF05_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceRF05_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF05_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceRF05_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceRF05_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceRF05_Fail].Processed 		= false;
	EventList[EV_PulseDeviceRF05_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceRF05_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceRF05_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceRF05_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF05_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceRF05_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceRF05_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceRF05_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF05_Fail].EventData));
	EventList[EV_PulseDeviceRF05_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceRF05_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceRF05_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF01_OK - ID ----
	EventList[EV_PulseDeviceRF01_OK].EventCategory 		= Type_System;
	EventList[EV_PulseDeviceRF01_OK].EventID 			= 63;

	EventList[EV_PulseDeviceRF01_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF01_OK].EventName, "RF Pulse300 OK");

	EventList[EV_PulseDeviceRF01_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF01_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceRF01_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceRF01_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceRF01_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceRF01_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceRF01_OK].Processed 			= false;
	EventList[EV_PulseDeviceRF01_OK].EventLogged		= false;

	EventList[EV_PulseDeviceRF01_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceRF01_OK].ImageName 			= Icon_Attention;
	EventList[EV_PulseDeviceRF01_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF01_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceRF01_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceRF01_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceRF01_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF01_OK].EventData));
	EventList[EV_PulseDeviceRF01_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceRF01_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceRF01_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF02_OK - ID ----
	EventList[EV_PulseDeviceRF02_OK].EventCategory 		= Type_System;
	EventList[EV_PulseDeviceRF02_OK].EventID 			= 64;

	EventList[EV_PulseDeviceRF02_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF02_OK].EventName, "RF Pulse500 RT OK");

	EventList[EV_PulseDeviceRF02_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF02_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceRF02_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceRF02_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceRF02_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceRF02_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceRF02_OK].Processed 			= false;
	EventList[EV_PulseDeviceRF02_OK].EventLogged		= false;

	EventList[EV_PulseDeviceRF02_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceRF02_OK].ImageName 			= Icon_Attention;
	EventList[EV_PulseDeviceRF02_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF02_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceRF02_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceRF02_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceRF02_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF02_OK].EventData));
	EventList[EV_PulseDeviceRF02_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceRF02_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceRF02_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF03_OK - ID ----
	EventList[EV_PulseDeviceRF03_OK].EventCategory 		= Type_System;
	EventList[EV_PulseDeviceRF03_OK].EventID 			= 65;

	EventList[EV_PulseDeviceRF03_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF03_OK].EventName, "RF Pulse500 RR OK");

	EventList[EV_PulseDeviceRF03_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF03_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceRF03_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceRF03_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceRF03_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceRF03_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceRF03_OK].Processed 			= false;
	EventList[EV_PulseDeviceRF03_OK].EventLogged		= false;

	EventList[EV_PulseDeviceRF03_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceRF03_OK].ImageName 			= Icon_Attention;
	EventList[EV_PulseDeviceRF03_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF03_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceRF03_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceRF03_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceRF03_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF03_OK].EventData));
	EventList[EV_PulseDeviceRF03_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceRF03_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceRF03_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF04_OK - ID ----
	EventList[EV_PulseDeviceRF04_OK].EventCategory 		= Type_System;
	EventList[EV_PulseDeviceRF04_OK].EventID 			= 66;

	EventList[EV_PulseDeviceRF04_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF04_OK].EventName, "RF Pulse500 LT OK");

	EventList[EV_PulseDeviceRF04_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF04_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceRF04_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceRF04_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceRF04_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceRF04_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceRF04_OK].Processed 			= false;
	EventList[EV_PulseDeviceRF04_OK].EventLogged		= false;

	EventList[EV_PulseDeviceRF04_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceRF04_OK].ImageName 			= Icon_Attention;
	EventList[EV_PulseDeviceRF04_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF04_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceRF04_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceRF04_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceRF04_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF04_OK].EventData));
	EventList[EV_PulseDeviceRF04_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceRF04_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceRF04_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceRF05_OK - ID ----
	EventList[EV_PulseDeviceRF05_OK].EventCategory 		= Type_System;
	EventList[EV_PulseDeviceRF05_OK].EventID 			= 67;

	EventList[EV_PulseDeviceRF05_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceRF05_OK].EventName, "RF Pulse500 FT OK");

	EventList[EV_PulseDeviceRF05_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceRF05_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceRF05_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceRF05_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceRF05_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceRF05_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceRF05_OK].Processed 			= false;
	EventList[EV_PulseDeviceRF05_OK].EventLogged			= false;

	EventList[EV_PulseDeviceRF05_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceRF05_OK].ImageName 			= Icon_Attention;
	EventList[EV_PulseDeviceRF05_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceRF05_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceRF05_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceRF05_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceRF05_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceRF05_OK].EventData));
	EventList[EV_PulseDeviceRF05_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceRF05_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceRF05_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN01_Fail - ID ----
	EventList[EV_PulseDeviceCAN01_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN01_Fail].EventID 		= 68;

	EventList[EV_PulseDeviceCAN01_Fail].EventActive 	= false;

	sprintf(EventList[EV_PulseDeviceCAN01_Fail].EventName, "CAN Pulse300 Fail");

	EventList[EV_PulseDeviceCAN01_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceCAN01_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN01_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN01_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceCAN01_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceCAN01_Fail].Processed 		= false;
	EventList[EV_PulseDeviceCAN01_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceCAN01_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceCAN01_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN01_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN01_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceCAN01_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceCAN01_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceCAN01_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN01_Fail].EventData));
	EventList[EV_PulseDeviceCAN01_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceCAN01_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN01_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN02_Fail - ID ----
	EventList[EV_PulseDeviceCAN02_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN02_Fail].EventID 		= 69;

	EventList[EV_PulseDeviceCAN02_Fail].EventActive 	= false;

	sprintf(EventList[EV_PulseDeviceCAN02_Fail].EventName, "CAN Pulse500 RT Fail");

	EventList[EV_PulseDeviceCAN02_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN02_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceCAN02_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN02_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN02_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceCAN02_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceCAN02_Fail].Processed 		= false;
	EventList[EV_PulseDeviceCAN02_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceCAN02_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceCAN02_Fail].ImageName 		= Icon_Attention;

	EventList[EV_PulseDeviceCAN02_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceCAN02_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceCAN02_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN02_Fail].EventData));
	EventList[EV_PulseDeviceCAN02_Fail].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceCAN02_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN02_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN03_Fail - ID ----
	EventList[EV_PulseDeviceCAN03_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN03_Fail].EventID 		= 70;

	EventList[EV_PulseDeviceCAN03_Fail].EventActive 	= false;

	sprintf(EventList[EV_PulseDeviceCAN03_Fail].EventName, "CAN Pulse500 RR Fail");

	EventList[EV_PulseDeviceCAN03_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN03_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceCAN03_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN03_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN03_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceCAN03_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceCAN03_Fail].Processed 		= false;
	EventList[EV_PulseDeviceCAN03_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceCAN03_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceCAN03_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN03_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN03_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceCAN03_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceCAN03_Fail].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceCAN03_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN03_Fail].EventData));
	EventList[EV_PulseDeviceCAN03_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceCAN03_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN03_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN04_Fail - ID ----
	EventList[EV_PulseDeviceCAN04_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN04_Fail].EventID 		= 71;

	EventList[EV_PulseDeviceCAN04_Fail].EventActive 	= false;

	sprintf(EventList[EV_PulseDeviceCAN04_Fail].EventName, "CAN Pulse500 LT Fail");

	EventList[EV_PulseDeviceCAN04_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN04_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceCAN04_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN04_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN04_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceCAN04_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceCAN04_Fail].Processed 		= false;
	EventList[EV_PulseDeviceCAN04_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceCAN04_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceCAN04_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN04_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN04_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceCAN04_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceCAN04_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceCAN04_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN04_Fail].EventData));
	EventList[EV_PulseDeviceCAN04_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceCAN04_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN04_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN05_Fail - ID ----
	EventList[EV_PulseDeviceCAN05_Fail].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN05_Fail].EventID 		= 72;

	EventList[EV_PulseDeviceCAN05_Fail].EventActive 	= false;

	sprintf(EventList[EV_PulseDeviceCAN05_Fail].EventName, "CAN Pulse500 FT Fail");

	EventList[EV_PulseDeviceCAN05_Fail].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN05_Fail].EventAction1 	= Act_DisplayOnly;
	EventList[EV_PulseDeviceCAN05_Fail].EventAction2 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN05_Fail].EventAction3 	= Act_ForceSlow;
	EventList[EV_PulseDeviceCAN05_Fail].EventActionTime1_2 = 1000;
	EventList[EV_PulseDeviceCAN05_Fail].EventActionTime2_3 = 1000;

	EventList[EV_PulseDeviceCAN05_Fail].Processed 		= false;
	EventList[EV_PulseDeviceCAN05_Fail].EventLogged		= false;

	EventList[EV_PulseDeviceCAN05_Fail].DispType 		= Disp_Generic_FullScreen;
	//EventList[EV_PulseDeviceCAN05_Fail].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN05_Fail].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN05_Fail].SplashActive 	= false;

	EventList[EV_PulseDeviceCAN05_Fail].BuzzerRequired 	= true;
	//EventList[EV_PulseDeviceCAN05_Fail].BuzzerMode 		= Buzz_Medium;

	memset(EventList[EV_PulseDeviceCAN05_Fail].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN05_Fail].EventData));
	EventList[EV_PulseDeviceCAN05_Fail].AddtionalInfo	= NULL;

	EventList[EV_PulseDeviceCAN05_Fail].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN05_Fail].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN01_OK - ID ----
	EventList[EV_PulseDeviceCAN01_OK].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN01_OK].EventID 			= 73;

	EventList[EV_PulseDeviceCAN01_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceCAN01_OK].EventName, "CAN Pulse300 OK");

	EventList[EV_PulseDeviceCAN01_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN01_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceCAN01_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceCAN01_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceCAN01_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceCAN01_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceCAN01_OK].Processed 		= false;
	EventList[EV_PulseDeviceCAN01_OK].EventLogged		= false;

	EventList[EV_PulseDeviceCAN01_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceCAN01_OK].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN01_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN01_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceCAN01_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceCAN01_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceCAN01_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN01_OK].EventData));
	EventList[EV_PulseDeviceCAN01_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceCAN01_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN01_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN02_OK - ID ----
	EventList[EV_PulseDeviceCAN02_OK].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN02_OK].EventID 			= 74;

	EventList[EV_PulseDeviceCAN02_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceCAN02_OK].EventName, "CAN Pulse500 RT OK");

	EventList[EV_PulseDeviceCAN02_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN02_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceCAN02_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceCAN02_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceCAN02_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceCAN02_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceCAN02_OK].Processed 		= false;
	EventList[EV_PulseDeviceCAN02_OK].EventLogged		= false;

	EventList[EV_PulseDeviceCAN02_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceCAN02_OK].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN02_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN02_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceCAN02_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceCAN02_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceCAN02_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN02_OK].EventData));
	EventList[EV_PulseDeviceCAN02_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceCAN02_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN02_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN03_OK - ID ----
	EventList[EV_PulseDeviceCAN03_OK].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN03_OK].EventID 			= 75;

	EventList[EV_PulseDeviceCAN03_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceCAN03_OK].EventName, "CAN Pulse500 RT OK");

	EventList[EV_PulseDeviceCAN03_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN03_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceCAN03_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceCAN03_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceCAN03_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceCAN03_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceCAN03_OK].Processed 		= false;
	EventList[EV_PulseDeviceCAN03_OK].EventLogged		= false;

	EventList[EV_PulseDeviceCAN03_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceCAN03_OK].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN03_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN03_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceCAN03_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceCAN03_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceCAN03_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN03_OK].EventData));
	EventList[EV_PulseDeviceCAN03_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceCAN03_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN03_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN04_OK - ID ----
	EventList[EV_PulseDeviceCAN04_OK].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN04_OK].EventID 			= 76;

	EventList[EV_PulseDeviceCAN04_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceCAN04_OK].EventName, "CAN Pulse500 RR OK");

	EventList[EV_PulseDeviceCAN04_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN04_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceCAN04_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceCAN04_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceCAN04_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceCAN04_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceCAN04_OK].Processed 		= false;
	EventList[EV_PulseDeviceCAN04_OK].EventLogged		= false;

	EventList[EV_PulseDeviceCAN04_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceCAN04_OK].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN04_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN04_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceCAN04_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceCAN04_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceCAN04_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN04_OK].EventData));
	EventList[EV_PulseDeviceCAN04_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceCAN04_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN04_OK].ACKRequired = false;

	// ---- Index - EV_PulseDeviceCAN05_OK - ID ----
	EventList[EV_PulseDeviceCAN05_OK].EventCategory 	= Type_System;
	EventList[EV_PulseDeviceCAN05_OK].EventID 			= 77;

	EventList[EV_PulseDeviceCAN05_OK].EventActive 		= false;

	sprintf(EventList[EV_PulseDeviceCAN05_OK].EventName, "CAN Pulse500 FT OK");

	EventList[EV_PulseDeviceCAN05_OK].TimeStampSystic	= 0;

	EventList[EV_PulseDeviceCAN05_OK].EventAction1 		= Act_None;
	EventList[EV_PulseDeviceCAN05_OK].EventAction2 		= Act_None;
	EventList[EV_PulseDeviceCAN05_OK].EventAction3 		= Act_None;
	EventList[EV_PulseDeviceCAN05_OK].EventActionTime1_2 = 0;
	EventList[EV_PulseDeviceCAN05_OK].EventActionTime2_3 = 0;

	EventList[EV_PulseDeviceCAN05_OK].Processed 		= false;
	EventList[EV_PulseDeviceCAN05_OK].EventLogged		= false;

	EventList[EV_PulseDeviceCAN05_OK].DispType 			= Disp_None;
	//EventList[EV_PulseDeviceCAN05_OK].ImageName 		= Icon_Attention;
	EventList[EV_PulseDeviceCAN05_OK].SplashTime 		= 0;
	EventList[EV_PulseDeviceCAN05_OK].SplashActive 		= false;

	EventList[EV_PulseDeviceCAN05_OK].BuzzerRequired 	= false;
	//EventList[EV_PulseDeviceCAN05_OK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_PulseDeviceCAN05_OK].EventData, 0xFF, sizeof(EventList[EV_PulseDeviceCAN05_OK].EventData));
	EventList[EV_PulseDeviceCAN05_OK].AddtionalInfo		= NULL;

	EventList[EV_PulseDeviceCAN05_OK].TimeRequired = 0;
	EventList[EV_PulseDeviceCAN05_OK].ACKRequired = false;

	// ---- Index - EV_HUB200_Failure - ID ----
	EventList[EV_HUB200_Failure].EventCategory 			= Type_System;
	EventList[EV_HUB200_Failure].EventID 				= 78;

	EventList[EV_HUB200_Failure].EventActive 			= false;

	sprintf(EventList[EV_HUB200_Failure].EventName, "HUB200 Failure");

	EventList[EV_HUB200_Failure].TimeStampSystic		= 0;

	EventList[EV_HUB200_Failure].EventAction1 			= Act_DisplayOnly;
	EventList[EV_HUB200_Failure].EventAction2 			= Act_ForceSlow;
	EventList[EV_HUB200_Failure].EventAction3 			= Act_ForceSlow;
	EventList[EV_HUB200_Failure].EventActionTime1_2		= 1000;
	EventList[EV_HUB200_Failure].EventActionTime2_3 	= 1000;

	EventList[EV_HUB200_Failure].Processed 				= false;
	EventList[EV_HUB200_Failure].EventLogged			= false;

	EventList[EV_HUB200_Failure].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_HUB200_Failure].ImageName 				= Icon_Attention;
	EventList[EV_HUB200_Failure].SplashTime 			= 0;
	EventList[EV_HUB200_Failure].SplashActive 			= false;

	EventList[EV_HUB200_Failure].BuzzerRequired 		= true;
	//EventList[EV_HUB200_Failure].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_HUB200_Failure].EventData, 0xFF, sizeof(EventList[EV_HUB200_Failure].EventData));
	EventList[EV_HUB200_Failure].AddtionalInfo		= NULL;

	EventList[EV_HUB200_Failure].TimeRequired = 0;
	EventList[EV_HUB200_Failure].ACKRequired = false;

	// ---- Index - EV_HUB200_OK - ID ----
	EventList[EV_HUB200_OK].EventCategory 				= Type_System;
	EventList[EV_HUB200_OK].EventID 					= 79;

	EventList[EV_HUB200_OK].EventActive 				= false;

	sprintf(EventList[EV_HUB200_OK].EventName, "HUB200 OK");

	EventList[EV_HUB200_OK].TimeStampSystic				= 0;

	EventList[EV_HUB200_OK].EventAction1 				= Act_None;
	EventList[EV_HUB200_OK].EventAction2 				= Act_None;
	EventList[EV_HUB200_OK].EventAction3 				= Act_None;
	EventList[EV_HUB200_OK].EventActionTime1_2			= 0;
	EventList[EV_HUB200_OK].EventActionTime2_3 			= 0;

	EventList[EV_HUB200_OK].Processed 					= false;
	EventList[EV_HUB200_OK].EventLogged					= false;

	EventList[EV_HUB200_OK].DispType 					= Disp_None;
	//EventList[EV_HUB200_OK].ImageName 					= Icon_Attention;
	EventList[EV_HUB200_OK].SplashTime 					= 0;
	EventList[EV_HUB200_OK].SplashActive 				= false;

	EventList[EV_HUB200_OK].BuzzerRequired 				= false;
	//EventList[EV_HUB200_OK].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_HUB200_OK].EventData, 0xFF, sizeof(EventList[EV_HUB200_OK].EventData));
	EventList[EV_HUB200_OK].AddtionalInfo				= NULL;

	EventList[EV_HUB200_OK].TimeRequired = 0;
	EventList[EV_HUB200_OK].ACKRequired = false;

	// ---- Index - EV_LightBar_Failure - ID ----
	EventList[EV_LightBar_Failure].EventCategory 		= Type_System;
	EventList[EV_LightBar_Failure].EventID 				= 80;

	EventList[EV_LightBar_Failure].EventActive 			= false;

	sprintf(EventList[EV_LightBar_Failure].EventName, "LightBar Failure");

	EventList[EV_LightBar_Failure].TimeStampSystic		= 0;

	EventList[EV_LightBar_Failure].EventAction1 		= Act_DisplayOnly;
	EventList[EV_LightBar_Failure].EventAction2 		= Act_ForceSlow;
	EventList[EV_LightBar_Failure].EventAction3 		= Act_ForceSlow;
	EventList[EV_LightBar_Failure].EventActionTime1_2	= 1000;
	EventList[EV_LightBar_Failure].EventActionTime2_3 	= 1000;

	EventList[EV_LightBar_Failure].Processed 			= false;
	EventList[EV_LightBar_Failure].EventLogged			= false;

	EventList[EV_LightBar_Failure].DispType 			= Disp_Generic_FullScreen;
	//EventList[EV_LightBar_Failure].ImageName 			= Icon_Attention;
	EventList[EV_LightBar_Failure].SplashTime 			= 0;
	EventList[EV_LightBar_Failure].SplashActive 		= false;

	EventList[EV_LightBar_Failure].BuzzerRequired 		= true;
	//EventList[EV_LightBar_Failure].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_LightBar_Failure].EventData, 0xFF, sizeof(EventList[EV_LightBar_Failure].EventData));
	EventList[EV_LightBar_Failure].AddtionalInfo		= NULL;

	EventList[EV_LightBar_Failure].TimeRequired = 0;
	EventList[EV_LightBar_Failure].ACKRequired = false;

	// ---- Index - EV_LightBar_OK - ID ----
	EventList[EV_LightBar_OK].EventCategory 			= Type_System;
	EventList[EV_LightBar_OK].EventID 					= 81;

	EventList[EV_LightBar_OK].EventActive 				= false;

	sprintf(EventList[EV_LightBar_OK].EventName, "LightBar OK");

	EventList[EV_LightBar_OK].TimeStampSystic				= 0;

	EventList[EV_LightBar_OK].EventAction1 				= Act_None;
	EventList[EV_LightBar_OK].EventAction2 				= Act_None;
	EventList[EV_LightBar_OK].EventAction3 				= Act_None;
	EventList[EV_LightBar_OK].EventActionTime1_2		= 0;
	EventList[EV_LightBar_OK].EventActionTime2_3 		= 0;

	EventList[EV_LightBar_OK].Processed 				= false;
	EventList[EV_LightBar_OK].EventLogged				= false;

	EventList[EV_LightBar_OK].DispType 					= Disp_None;
	//EventList[EV_LightBar_OK].ImageName 				= Icon_Attention;
	EventList[EV_LightBar_OK].SplashTime 				= 0;
	EventList[EV_LightBar_OK].SplashActive 				= false;

	EventList[EV_LightBar_OK].BuzzerRequired 			= false;
	//EventList[EV_LightBar_OK].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_LightBar_OK].EventData, 0xFF, sizeof(EventList[EV_LightBar_OK].EventData));
	EventList[EV_LightBar_OK].AddtionalInfo				= NULL;

	EventList[EV_LightBar_OK].TimeRequired = 0;
	EventList[EV_LightBar_OK].ACKRequired = false;

	// ---- Index - EV_LightBar_Failure - ID ----
	EventList[EV_FLOW_Failure].EventCategory 			= Type_System;
	EventList[EV_FLOW_Failure].EventID 					= 82;

	EventList[EV_FLOW_Failure].EventActive 				= false;

	sprintf(EventList[EV_FLOW_Failure].EventName, "FLOW Failure");

	EventList[EV_FLOW_Failure].TimeStampSystic			= 0;

	EventList[EV_FLOW_Failure].EventAction1 			= Act_DisplayOnly;
	EventList[EV_FLOW_Failure].EventAction2 			= Act_ForceSlow;
	EventList[EV_FLOW_Failure].EventAction3 			= Act_ForceSlow;
	EventList[EV_FLOW_Failure].EventActionTime1_2		= 1000;
	EventList[EV_FLOW_Failure].EventActionTime2_3 		= 1000;

	EventList[EV_FLOW_Failure].Processed 				= false;
	EventList[EV_FLOW_Failure].EventLogged				= false;

	EventList[EV_FLOW_Failure].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_FLOW_Failure].ImageName 				= Icon_Attention;
	EventList[EV_FLOW_Failure].SplashTime 				= 0;
	EventList[EV_FLOW_Failure].SplashActive 			= false;

	EventList[EV_FLOW_Failure].BuzzerRequired 			= true;
	//EventList[EV_FLOW_Failure].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_FLOW_Failure].EventData, 0xFF, sizeof(EventList[EV_FLOW_Failure].EventData));
	EventList[EV_FLOW_Failure].AddtionalInfo			= NULL;

	EventList[EV_FLOW_Failure].TimeRequired = 0;
	EventList[EV_FLOW_Failure].ACKRequired = false;

	// ---- Index - EV_FLOW_OK - ID ----
	EventList[EV_FLOW_OK].EventCategory 				= Type_System;
	EventList[EV_FLOW_OK].EventID 						= 83;

	EventList[EV_FLOW_OK].EventActive 					= false;

	sprintf(EventList[EV_FLOW_OK].EventName, "FLOW OK");

	EventList[EV_FLOW_OK].TimeStampSystic				= 0;

	EventList[EV_FLOW_OK].EventAction1 					= Act_None;
	EventList[EV_FLOW_OK].EventAction2 					= Act_None;
	EventList[EV_FLOW_OK].EventAction3 					= Act_None;
	EventList[EV_FLOW_OK].EventActionTime1_2			= 0;
	EventList[EV_FLOW_OK].EventActionTime2_3 			= 0;

	EventList[EV_FLOW_OK].Processed 					= false;
	EventList[EV_FLOW_OK].EventLogged					= false;

	EventList[EV_FLOW_OK].DispType 						= Disp_None;
	//EventList[EV_FLOW_OK].ImageName 					= Icon_Attention;
	EventList[EV_FLOW_OK].SplashTime 					= 0;
	EventList[EV_FLOW_OK].SplashActive 					= false;

	EventList[EV_FLOW_OK].BuzzerRequired 				= false;
	//EventList[EV_FLOW_OK].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_FLOW_OK].EventData, 0xFF, sizeof(EventList[EV_FLOW_OK].EventData));
	EventList[EV_FLOW_OK].AddtionalInfo					= NULL;

	EventList[EV_FLOW_OK].TimeRequired = 0;
	EventList[EV_FLOW_OK].ACKRequired = false;

	// ---- Index - EV_Estop_Latch_Int - ID ----
	EventList[EV_Estop_Latch_Int].EventCategory 		= Type_System;
	EventList[EV_Estop_Latch_Int].EventID				= 90;

	EventList[EV_Estop_Latch_Int].EventActive 			= false;

	sprintf(EventList[EV_Estop_Latch_Int].EventName, "Internal E-Stop Pressed");

	EventList[EV_Estop_Latch_Int].TimeStampSystic		= 0;

	EventList[EV_Estop_Latch_Int].EventAction1			= Act_ForceStop;
	EventList[EV_Estop_Latch_Int].EventAction2 			= Act_ForceStop;
	EventList[EV_Estop_Latch_Int].EventAction3 			= Act_ForceStop;
	EventList[EV_Estop_Latch_Int].EventActionTime1_2 	= 0;
	EventList[EV_Estop_Latch_Int].EventActionTime2_3 	= 0;

	EventList[EV_Estop_Latch_Int].Processed				= false;
	EventList[EV_Estop_Latch_Int].EventLogged			= false;

	EventList[EV_Estop_Latch_Int].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_Estop_Latch_Int].ImageName 			= Icon_MED_EStopWithArrows;
	EventList[EV_Estop_Latch_Int].SplashTime 			= 0;
	EventList[EV_Estop_Latch_Int].SplashActive 			= false;

	EventList[EV_Estop_Latch_Int].BuzzerRequired 		= true;
	//EventList[EV_Estop_Latch_Int].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Estop_Latch_Int].EventData, 0xFF, sizeof(EventList[EV_Estop_Latch_Int].EventData));
	EventList[EV_Estop_Latch_Int].AddtionalInfo			= NULL;

	EventList[EV_Estop_Latch_Int].TimeRequired = 0;
	EventList[EV_Estop_Latch_Int].ACKRequired = false;

	// ---- Index - EV_EStop_Release_Int - ID ----
	EventList[EV_EStop_Release_Int].EventCategory 		= Type_System;
	EventList[EV_EStop_Release_Int].EventID				= 91;

	EventList[EV_EStop_Release_Int].EventActive 		= false;

	sprintf(EventList[EV_EStop_Release_Int].EventName, "Internal E-Stop Release");

	EventList[EV_EStop_Release_Int].TimeStampSystic		= 0;

	EventList[EV_EStop_Release_Int].EventAction1		= Act_None;
	EventList[EV_EStop_Release_Int].EventAction2 		= Act_None;
	EventList[EV_EStop_Release_Int].EventAction3 		= Act_None;
	EventList[EV_EStop_Release_Int].EventActionTime1_2 	= 0;
	EventList[EV_EStop_Release_Int].EventActionTime2_3 	= 0;

	EventList[EV_EStop_Release_Int].Processed			= false;
	EventList[EV_EStop_Release_Int].EventLogged			= false;

	EventList[EV_EStop_Release_Int].DispType 			= Disp_None;
	//EventList[EV_EStop_Release_Int].ImageName 			= Icon_MED_EStopWithArrows;
	EventList[EV_EStop_Release_Int].SplashTime 			= 0;
	EventList[EV_EStop_Release_Int].SplashActive 		= false;

	EventList[EV_EStop_Release_Int].BuzzerRequired 		= false;
	//EventList[EV_EStop_Release_Int].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_EStop_Release_Int].EventData, 0xFF, sizeof(EventList[EV_EStop_Release_Int].EventData));
	EventList[EV_EStop_Release_Int].AddtionalInfo		= NULL;

	EventList[EV_EStop_Release_Int].TimeRequired = 0;
	EventList[EV_EStop_Release_Int].ACKRequired = false;

	// ---- Index - EV_Estop_Latch_Ext - ID ----
	EventList[EV_Estop_Latch_Ext].EventCategory 		= Type_System;
	EventList[EV_Estop_Latch_Ext].EventID				= 92;

	EventList[EV_Estop_Latch_Ext].EventActive 			= false;

	sprintf(EventList[EV_Estop_Latch_Ext].EventName, "External E-Stop Pressed");

	EventList[EV_Estop_Latch_Ext].TimeStampSystic		= 0;

	EventList[EV_Estop_Latch_Ext].EventAction1			= Act_ForceStop;
	EventList[EV_Estop_Latch_Ext].EventAction2 			= Act_ForceStop;
	EventList[EV_Estop_Latch_Ext].EventAction3 			= Act_ForceStop;
	EventList[EV_Estop_Latch_Ext].EventActionTime1_2 	= 0;
	EventList[EV_Estop_Latch_Ext].EventActionTime2_3 	= 0;

	EventList[EV_Estop_Latch_Ext].Processed				= false;
	EventList[EV_Estop_Latch_Ext].EventLogged			= false;

	EventList[EV_Estop_Latch_Ext].DispType 				= Disp_Generic_FullScreen;
	//EventList[EV_Estop_Latch_Ext].ImageName 			= Icon_MED_EStopWithArrows;
	EventList[EV_Estop_Latch_Ext].SplashTime 			= 0;
	EventList[EV_Estop_Latch_Ext].SplashActive 			= false;

	EventList[EV_Estop_Latch_Ext].BuzzerRequired 		= true;
	//EventList[EV_Estop_Latch_Ext].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Estop_Latch_Ext].EventData, 0xFF, sizeof(EventList[EV_Estop_Latch_Ext].EventData));
	EventList[EV_Estop_Latch_Ext].AddtionalInfo			= NULL;

	EventList[EV_Estop_Latch_Ext].TimeRequired = 0;
	EventList[EV_Estop_Latch_Ext].ACKRequired = false;

	// ---- Index - EV_Estop_Release_Ext - ID ----
	EventList[EV_Estop_Release_Ext].EventCategory 		= Type_System;
	EventList[EV_Estop_Release_Ext].EventID				= 93;

	EventList[EV_Estop_Release_Ext].EventActive 		= false;

	sprintf(EventList[EV_Estop_Release_Ext].EventName, "External E-Stop Release");

	EventList[EV_Estop_Release_Ext].TimeStampSystic		= 0;

	EventList[EV_Estop_Release_Ext].EventAction1		= Act_None;
	EventList[EV_Estop_Release_Ext].EventAction2 		= Act_None;
	EventList[EV_Estop_Release_Ext].EventAction3 		= Act_None;
	EventList[EV_Estop_Release_Ext].EventActionTime1_2 	= 0;
	EventList[EV_Estop_Release_Ext].EventActionTime2_3 	= 0;

	EventList[EV_Estop_Release_Ext].Processed			= false;
	EventList[EV_Estop_Release_Ext].EventLogged			= false;

	EventList[EV_Estop_Release_Ext].DispType 			= Disp_None;
	//EventList[EV_Estop_Release_Ext].ImageName 			= Icon_MED_EStopWithArrows;
	EventList[EV_Estop_Release_Ext].SplashTime 			= 0;
	EventList[EV_Estop_Release_Ext].SplashActive 		= false;

	EventList[EV_Estop_Release_Ext].BuzzerRequired 		= false;
	//EventList[EV_Estop_Release_Ext].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Estop_Release_Ext].EventData, 0xFF, sizeof(EventList[EV_Estop_Release_Ext].EventData));
	EventList[EV_Estop_Release_Ext].AddtionalInfo		= NULL;

	EventList[EV_Estop_Release_Ext].TimeRequired = 0;
	EventList[EV_Estop_Release_Ext].ACKRequired = false;

	// ---- Index - Input_01_On - ID ----
	EventList[Input_01_On].EventCategory 				= Type_System;
	EventList[Input_01_On].EventID						= 94;

	EventList[Input_01_On].EventActive 					= false;

	sprintf(EventList[Input_01_On].EventName, "External Input 01 On");

	EventList[Input_01_On].TimeStampSystic				= 0;

	EventList[Input_01_On].EventAction1					= Act_None;
	EventList[Input_01_On].EventAction2 				= Act_None;
	EventList[Input_01_On].EventAction3 				= Act_MotionInhibit;
	EventList[Input_01_On].EventActionTime1_2 			= 0;
	EventList[Input_01_On].EventActionTime2_3 			= 0;

	EventList[Input_01_On].Processed					= false;
	EventList[Input_01_On].EventLogged					= false;

	EventList[Input_01_On].DispType 					= Disp_Message;
	//EventList[Input_01_On].ImageName 					= Icon_Attention;
	EventList[Input_01_On].SplashTime 					= 500;
	EventList[Input_01_On].SplashActive 				= false;

	EventList[Input_01_On].BuzzerRequired 				= false;
	//EventList[Input_01_On].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_01_On].EventData, 0xFF, sizeof(EventList[Input_01_On].EventData));
	EventList[Input_01_On].AddtionalInfo				= NULL;

	EventList[Input_01_On].TimeRequired = 0;
	EventList[Input_01_On].ACKRequired = false;

	// ---- Index - Input_01_Off - ID ----
	EventList[Input_01_Off].EventCategory 				= Type_System;
	EventList[Input_01_Off].EventID						= 95;

	EventList[Input_01_Off].EventActive 				= false;

	sprintf(EventList[Input_01_Off].EventName, "External Input 01 Off");

	EventList[Input_01_Off].TimeStampSystic				= 0;

	EventList[Input_01_Off].EventAction1				= Act_None;
	EventList[Input_01_Off].EventAction2 				= Act_None;
	EventList[Input_01_Off].EventAction3 				= Act_None;
	EventList[Input_01_Off].EventActionTime1_2 			= 0;
	EventList[Input_01_Off].EventActionTime2_3 			= 0;

	EventList[Input_01_Off].Processed					= false;
	EventList[Input_01_Off].EventLogged					= false;

	EventList[Input_01_Off].DispType 					= Disp_None;
	//EventList[Input_01_Off].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_01_Off].SplashTime 					= 0;
	EventList[Input_01_Off].SplashActive 				= false;

	EventList[Input_01_Off].BuzzerRequired 				= false;
	//EventList[Input_01_Off].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_01_Off].EventData, 0xFF, sizeof(EventList[Input_01_Off].EventData));
	EventList[Input_01_Off].AddtionalInfo				= NULL;

	EventList[Input_01_Off].TimeRequired = 0;
	EventList[Input_01_Off].ACKRequired = false;

	// ---- Index - Input_02_On - ID ----
	EventList[Input_02_On].EventCategory 				= Type_System;
	EventList[Input_02_On].EventID						= 96;

	EventList[Input_02_On].EventActive 					= false;

	sprintf(EventList[Input_02_On].EventName, "External Input 02 On");

	EventList[Input_02_On].TimeStampSystic				= 0;

	EventList[Input_02_On].EventAction1					= Act_None;
	EventList[Input_02_On].EventAction2 				= Act_None;
	EventList[Input_02_On].EventAction3 				= Act_ForceStandDown_OVR;
	EventList[Input_02_On].EventActionTime1_2 			= 0;
	EventList[Input_02_On].EventActionTime2_3 			= 0;

	EventList[Input_02_On].Processed					= false;
	EventList[Input_02_On].EventLogged					= false;

	EventList[Input_02_On].DispType 					= Disp_Message;
	//EventList[Input_02_On].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_02_On].SplashTime 					= 0;
	EventList[Input_02_On].SplashActive 				= false;

	EventList[Input_02_On].BuzzerRequired 				= false;
	//EventList[Input_02_On].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_02_On].EventData, 0xFF, sizeof(EventList[Input_02_On].EventData));
	EventList[Input_02_On].AddtionalInfo				= NULL;

	EventList[Input_02_On].TimeRequired = 0;
	EventList[Input_02_On].ACKRequired = false;

	// ---- Index - Input_02_Off - ID ----
	EventList[Input_02_Off].EventCategory 				= Type_System;
	EventList[Input_02_Off].EventID						= 97;

	EventList[Input_02_Off].EventActive 				= false;

	sprintf(EventList[Input_02_Off].EventName, "External Input 02 Off");

	EventList[Input_02_Off].TimeStampSystic				= 0;

	EventList[Input_02_Off].EventAction1				= Act_None;
	EventList[Input_02_Off].EventAction2 				= Act_None;
	EventList[Input_02_Off].EventAction3 				= Act_None;
	EventList[Input_02_Off].EventActionTime1_2 			= 0;
	EventList[Input_02_Off].EventActionTime2_3 			= 0;

	EventList[Input_02_Off].Processed					= false;
	EventList[Input_02_Off].EventLogged					= false;

	EventList[Input_02_Off].DispType 					= Disp_None;
	//EventList[Input_02_Off].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_02_Off].SplashTime 					= 0;
	EventList[Input_02_Off].SplashActive 				= false;

	EventList[Input_02_Off].BuzzerRequired 				= false;
	//EventList[Input_02_Off].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_02_Off].EventData, 0xFF, sizeof(EventList[Input_02_Off].EventData));
	EventList[Input_02_Off].AddtionalInfo				= NULL;

	EventList[Input_02_Off].TimeRequired = 0;
	EventList[Input_02_Off].ACKRequired = false;

	// ---- Index - Input_03_On - ID ----
	EventList[Input_03_On].EventCategory 				= Type_System;
	EventList[Input_03_On].EventID						= 98;

	EventList[Input_03_On].EventActive 					= false;

	sprintf(EventList[Input_03_On].EventName, "External Input 03 On");

	EventList[Input_03_On].TimeStampSystic				= 0;

	EventList[Input_03_On].EventAction1					= Act_None;
	EventList[Input_03_On].EventAction2 				= Act_None;
	EventList[Input_03_On].EventAction3 				= Act_Overrule;
	EventList[Input_03_On].EventActionTime1_2 			= 0;
	EventList[Input_03_On].EventActionTime2_3 			= 0;

	EventList[Input_03_On].Processed					= false;
	EventList[Input_03_On].EventLogged					= false;

	EventList[Input_03_On].DispType 					= Disp_Message;
	//EventList[Input_03_On].ImageName 					= Icon_MenAtWork;
	EventList[Input_03_On].SplashTime 					= 0;
	EventList[Input_03_On].SplashActive 				= false;

	EventList[Input_03_On].BuzzerRequired 				= false;
	//EventList[Input_03_On].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_03_On].EventData, 0xFF, sizeof(EventList[Input_03_On].EventData));
	EventList[Input_03_On].AddtionalInfo				= NULL;

	EventList[Input_03_On].TimeRequired = 0;
	EventList[Input_03_On].ACKRequired = false;

	// ---- Index - Input_03_Off - ID ----
	EventList[Input_03_Off].EventCategory 				= Type_System;
	EventList[Input_03_Off].EventID						= 99;

	EventList[Input_03_Off].EventActive 				= false;

	sprintf(EventList[Input_03_Off].EventName, "External Input 03 Off");

	EventList[Input_03_Off].TimeStampSystic				= 0;

	EventList[Input_03_Off].EventAction1				= Act_None;
	EventList[Input_03_Off].EventAction2 				= Act_None;
	EventList[Input_03_Off].EventAction3 				= Act_None;
	EventList[Input_03_Off].EventActionTime1_2 			= 0;
	EventList[Input_03_Off].EventActionTime2_3 			= 0;

	EventList[Input_03_Off].Processed					= false;
	EventList[Input_03_Off].EventLogged					= false;

	EventList[Input_03_Off].DispType 					= Disp_None;
	//EventList[Input_03_Off].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_03_Off].SplashTime 					= 0;
	EventList[Input_03_Off].SplashActive 				= false;

	EventList[Input_03_Off].BuzzerRequired 				= false;
	//EventList[Input_03_Off].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_03_Off].EventData, 0xFF, sizeof(EventList[Input_03_Off].EventData));
	EventList[Input_03_Off].AddtionalInfo				= NULL;

	EventList[Input_03_Off].TimeRequired = 0;
	EventList[Input_03_Off].ACKRequired = false;

	// ---- Index - Input_04_On - ID ----
	EventList[Input_04_On].EventCategory 				= Type_System;
	EventList[Input_04_On].EventID						= 100;

	EventList[Input_04_On].EventActive 					= false;

	sprintf(EventList[Input_04_On].EventName, "External Input 04 On");

	EventList[Input_04_On].TimeStampSystic				= 0;

	EventList[Input_04_On].EventAction1					= Act_None;
	EventList[Input_04_On].EventAction2 				= Act_ForceSlow_OVR;
	EventList[Input_04_On].EventAction3 				= Act_None;
	EventList[Input_04_On].EventActionTime1_2 			= 0;
	EventList[Input_04_On].EventActionTime2_3 			= 0;

	EventList[Input_04_On].Processed					= false;
	EventList[Input_04_On].EventLogged					= false;

	EventList[Input_04_On].DispType 					= Disp_Message;
	//EventList[Input_04_On].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_04_On].SplashTime 					= 0;
	EventList[Input_04_On].SplashActive 				= false;

	EventList[Input_04_On].BuzzerRequired 				= false;
	//EventList[Input_04_On].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_04_On].EventData, 0xFF, sizeof(EventList[Input_04_On].EventData));
	EventList[Input_04_On].AddtionalInfo				= NULL;

	EventList[Input_04_On].TimeRequired = 0;
	EventList[Input_04_On].ACKRequired = false;

	// ---- Index - Input_01_Off - ID ----
	EventList[Input_04_Off].EventCategory 				= Type_System;
	EventList[Input_04_Off].EventID						= 101;

	EventList[Input_04_Off].EventActive 				= false;

	sprintf(EventList[Input_04_Off].EventName, "External Input 04 Off");

	EventList[Input_04_Off].TimeStampSystic				= 0;

	EventList[Input_04_Off].EventAction1				= Act_None;
	EventList[Input_04_Off].EventAction2 				= Act_None;
	EventList[Input_04_Off].EventAction3 				= Act_None;
	EventList[Input_04_Off].EventActionTime1_2 			= 0;
	EventList[Input_04_Off].EventActionTime2_3 			= 0;

	EventList[Input_04_Off].Processed					= false;
	EventList[Input_04_Off].EventLogged					= false;

	EventList[Input_04_Off].DispType 					= Disp_None;
	//EventList[Input_04_Off].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_04_Off].SplashTime 					= 0;
	EventList[Input_04_Off].SplashActive 				= false;

	EventList[Input_04_Off].BuzzerRequired 				= false;
	//EventList[Input_04_Off].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_04_Off].EventData, 0xFF, sizeof(EventList[Input_04_Off].EventData));
	EventList[Input_04_Off].AddtionalInfo				= NULL;

	EventList[Input_04_Off].TimeRequired = 0;
	EventList[Input_04_Off].ACKRequired = false;

	// ---- Index - Input_05_On - ID ----
	EventList[Input_05_On].EventCategory 				= Type_System;
	EventList[Input_05_On].EventID						= 102;

	EventList[Input_05_On].EventActive 					= false;

	sprintf(EventList[Input_05_On].EventName, "External Input 05 On");

	EventList[Input_05_On].TimeStampSystic				= 0;

	EventList[Input_05_On].EventAction1					= Act_None;
	EventList[Input_05_On].EventAction2 				= Act_None;
	EventList[Input_05_On].EventAction3 				= Act_ForceMeduim_OVR;
	EventList[Input_05_On].EventActionTime1_2 			= 0;
	EventList[Input_05_On].EventActionTime2_3 			= 0;

	EventList[Input_05_On].Processed					= false;
	EventList[Input_05_On].EventLogged					= false;

	EventList[Input_05_On].DispType 					= Disp_Message;
	//EventList[Input_05_On].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_05_On].SplashTime 					= 0;
	EventList[Input_05_On].SplashActive 				= false;

	EventList[Input_05_On].BuzzerRequired 				= false;
	//EventList[Input_05_On].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_05_On].EventData, 0xFF, sizeof(EventList[Input_05_On].EventData));
	EventList[Input_05_On].AddtionalInfo				= NULL;

	EventList[Input_05_On].TimeRequired = 0;
	EventList[Input_05_On].ACKRequired = false;

	// ---- Index - Input_05_Off - ID ----
	EventList[Input_05_Off].EventCategory 				= Type_System;
	EventList[Input_05_Off].EventID						= 103;

	EventList[Input_05_Off].EventActive 				= false;

	sprintf(EventList[Input_05_Off].EventName, "External Input 05 Off");

	EventList[Input_05_Off].TimeStampSystic				= 0;

	EventList[Input_05_Off].EventAction1				= Act_None;
	EventList[Input_05_Off].EventAction2 				= Act_None;
	EventList[Input_05_Off].EventAction3 				= Act_None;
	EventList[Input_05_Off].EventActionTime1_2 			= 0;
	EventList[Input_05_Off].EventActionTime2_3 			= 0;

	EventList[Input_05_Off].Processed					= false;
	EventList[Input_05_Off].EventLogged					= false;

	EventList[Input_05_Off].DispType 					= Disp_None;
	//EventList[Input_05_Off].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_05_Off].SplashTime 					= 0;
	EventList[Input_05_Off].SplashActive 				= false;

	EventList[Input_05_Off].BuzzerRequired 				= false;
	//EventList[Input_05_Off].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_05_Off].EventData, 0xFF, sizeof(EventList[Input_05_Off].EventData));
	EventList[Input_05_Off].AddtionalInfo				= NULL;

	EventList[Input_05_Off].TimeRequired = 0;
	EventList[Input_05_Off].ACKRequired = false;

	// ---- Index - Input_06_On - ID ----
	EventList[Input_06_On].EventCategory 				= Type_System;
	EventList[Input_06_On].EventID						= 104;

	EventList[Input_06_On].EventActive 					= false;

	sprintf(EventList[Input_06_On].EventName, "External Input 06 On");

	EventList[Input_06_On].TimeStampSystic				= 0;

	EventList[Input_06_On].EventAction1					= Act_None;
	EventList[Input_06_On].EventAction2 				= Act_None;
	EventList[Input_06_On].EventAction3 				= Act_ForceHigh_OVR;
	EventList[Input_06_On].EventActionTime1_2 			= 0;
	EventList[Input_06_On].EventActionTime2_3 			= 0;

	EventList[Input_06_On].Processed					= false;
	EventList[Input_06_On].EventLogged					= false;

	EventList[Input_06_On].DispType 					= Disp_Message;
	//EventList[Input_06_On].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_06_On].SplashTime 					= 0;
	EventList[Input_06_On].SplashActive 				= false;

	EventList[Input_06_On].BuzzerRequired 				= false;
	//EventList[Input_06_On].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_06_On].EventData, 0xFF, sizeof(EventList[Input_06_On].EventData));
	EventList[Input_06_On].AddtionalInfo				= NULL;

	EventList[Input_06_On].TimeRequired = 0;
	EventList[Input_06_On].ACKRequired = false;

	// ---- Index - Input_06_Off - ID ----
	EventList[Input_06_Off].EventCategory 				= Type_System;
	EventList[Input_06_Off].EventID						= 105;

	EventList[Input_06_Off].EventActive 				= false;

	sprintf(EventList[Input_06_Off].EventName, "External Input 06 Off");

	EventList[Input_06_Off].TimeStampSystic				= 0;

	EventList[Input_06_Off].EventAction1				= Act_None;
	EventList[Input_06_Off].EventAction2 				= Act_None;
	EventList[Input_06_Off].EventAction3 				= Act_None;
	EventList[Input_06_Off].EventActionTime1_2 			= 0;
	EventList[Input_06_Off].EventActionTime2_3 			= 0;

	EventList[Input_06_Off].Processed					= false;
	EventList[Input_06_Off].EventLogged					= false;

	EventList[Input_06_Off].DispType 					= Disp_None;
	//EventList[Input_06_Off].ImageName 					= Icon_MED_EStopWithArrows;
	EventList[Input_06_Off].SplashTime 					= 0;
	EventList[Input_06_Off].SplashActive 				= false;

	EventList[Input_06_Off].BuzzerRequired 				= false;
	//EventList[Input_06_Off].BuzzerMode 					= Buzz_Once;

	memset(EventList[Input_06_Off].EventData, 0xFF, sizeof(EventList[Input_06_Off].EventData));
	EventList[Input_06_Off].AddtionalInfo				= NULL;

	EventList[Input_06_Off].TimeRequired = 0;
	EventList[Input_06_Off].ACKRequired = false;

	/*-------------------------------------------------------------------------------------------------------
	 * 										   Operational Events
	 *-------------------------------------------------------------------------------------------------------*/
	// ---- Index - EV_System_Pre_Op_Fail - ID ----
	EventList[EV_System_Pre_Op_Fail].EventCategory 		= Type_Operational;
	EventList[EV_System_Pre_Op_Fail].EventID 			= 100;

	EventList[EV_System_Pre_Op_Fail].EventActive 		= false;

	sprintf(EventList[EV_System_Pre_Op_Fail].EventName, "Pre-Op Failed");

	EventList[EV_System_Pre_Op_Fail].TimeStampSystic	= 0;

	EventList[EV_System_Pre_Op_Fail].EventAction1		= Act_DisplayOnly;
	EventList[EV_System_Pre_Op_Fail].EventAction2 		= Act_DisplayOnly;
	EventList[EV_System_Pre_Op_Fail].EventAction3 		= Act_DisplayOnly;
	EventList[EV_System_Pre_Op_Fail].EventActionTime1_2 = 0;
	EventList[EV_System_Pre_Op_Fail].EventActionTime2_3 = 0;

	EventList[EV_System_Pre_Op_Fail].Processed			= false;
	EventList[EV_System_Pre_Op_Fail].EventLogged		= false;

	//EventList[EV_System_Pre_Op_Fail].ImageName 			= Icon_Attention;
	EventList[EV_System_Pre_Op_Fail].DispType 			= Disp_Generic_FullScreen;
	EventList[EV_System_Pre_Op_Fail].SplashTime 		= 0;
	EventList[EV_System_Pre_Op_Fail].SplashActive 		= false;

	EventList[EV_System_Pre_Op_Fail].BuzzerRequired 	= true;
	//EventList[EV_System_Pre_Op_Fail].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_System_Pre_Op_Fail].EventData, 0xFF, sizeof(EventList[EV_System_Pre_Op_Fail].EventData));
	EventList[EV_System_Pre_Op_Fail].AddtionalInfo = NULL;

	EventList[EV_System_Pre_Op_Fail].TimeRequired = 0;
	EventList[EV_System_Pre_Op_Fail].ACKRequired = false;

	// ---- Index - EV_System_Pre_Op_Fail - ID ----
	EventList[EV_System_Pre_Op_Pass].EventCategory 		= Type_Operational;
	EventList[EV_System_Pre_Op_Pass].EventID 			= 100;

	EventList[EV_System_Pre_Op_Pass].EventActive 		= false;

	sprintf(EventList[EV_System_Pre_Op_Pass].EventName, "Pre-Op Passed");

	EventList[EV_System_Pre_Op_Pass].TimeStampSystic	= 0;

	EventList[EV_System_Pre_Op_Pass].EventAction1		= Act_None;
	EventList[EV_System_Pre_Op_Pass].EventAction2 		= Act_None;
	EventList[EV_System_Pre_Op_Pass].EventAction3 		= Act_None;
	EventList[EV_System_Pre_Op_Pass].EventActionTime1_2 = 0;
	EventList[EV_System_Pre_Op_Pass].EventActionTime2_3 = 0;

	EventList[EV_System_Pre_Op_Pass].Processed			= false;
	EventList[EV_System_Pre_Op_Pass].EventLogged		= false;

	//EventList[EV_System_Pre_Op_Pass].ImageName 			= Icon_Attention;
	EventList[EV_System_Pre_Op_Pass].DispType 			= Disp_Icon;
	EventList[EV_System_Pre_Op_Pass].SplashTime 		= 0;
	EventList[EV_System_Pre_Op_Pass].SplashActive 		= false;

	EventList[EV_System_Pre_Op_Pass].BuzzerRequired 	= true;
	//EventList[EV_System_Pre_Op_Pass].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_System_Pre_Op_Pass].EventData, 0xFF, sizeof(EventList[EV_System_Pre_Op_Pass].EventData));
	EventList[EV_System_Pre_Op_Pass].AddtionalInfo 		= NULL;

	EventList[EV_System_Pre_Op_Pass].TimeRequired = 0;
	EventList[EV_System_Pre_Op_Pass].ACKRequired = false;

	// ---- Index - EV_License_Required - ID ----
	EventList[EV_License_Required].EventCategory 		= Type_Operational;
	EventList[EV_License_Required].EventID 				= 112;

	EventList[EV_License_Required].EventActive = false;

	sprintf(EventList[EV_License_Required].EventName, "Insert License Card");

	EventList[EV_License_Required].TimeStampSystic		= 0;

	EventList[EV_License_Required].EventAction1			= Act_ForceStop;
	EventList[EV_License_Required].EventAction2 		= Act_ForceStop;
	EventList[EV_License_Required].EventAction3 		= Act_ForceStop;
	EventList[EV_License_Required].EventActionTime1_2 	= 0;
	EventList[EV_License_Required].EventActionTime2_3 	= 0;

	EventList[EV_License_Required].Processed			= false;
	EventList[EV_License_Required].EventLogged			= false;

	EventList[EV_License_Required].DispType 			= Disp_Generic_FullScreen;
	EventList[EV_License_Required].SplashTime			= 0;
	EventList[EV_License_Required].SplashActive			= false;
	//EventList[EV_License_Required].ImageName 			= Icon_MED_InsertLicence;

	EventList[EV_License_Required].BuzzerRequired 		= true;
	//EventList[EV_License_Required].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_License_Required].EventData, 0xFF, sizeof(EventList[EV_License_Required].EventData));
	EventList[EV_License_Required].AddtionalInfo		= NULL;

	EventList[EV_License_Required].TimeRequired = 0;
	EventList[EV_License_Required].ACKRequired = false;

	// ---- Index - EV_License_Processed_01 - ID ----
	EventList[EV_License_Processed_01].EventCategory 	= Type_Operational;
	EventList[EV_License_Processed_01].EventID 			= 114;

	EventList[EV_License_Processed_01].EventActive 		= false;

	sprintf(EventList[EV_License_Processed_01].EventName, "License Card Processed");

	EventList[EV_License_Processed_01].TimeStampSystic	= 0;

	EventList[EV_License_Processed_01].EventAction1 	= Act_None;
	EventList[EV_License_Processed_01].EventAction2 	= Act_None;
	EventList[EV_License_Processed_01].EventAction3 	= Act_None;
	EventList[EV_License_Processed_01].EventActionTime1_2 = 0;
	EventList[EV_License_Processed_01].EventActionTime2_3 = 0;

	EventList[EV_License_Processed_01].Processed 		= false;
	EventList[EV_License_Processed_01].EventLogged 		= false;

	EventList[EV_License_Processed_01].DispType 		= Disp_None;
	EventList[EV_License_Processed_01].SplashTime		= 0;
	EventList[EV_License_Processed_01].SplashActive		= false;
	//EventList[EV_License_Processed_01].ImageName 		= Icon_CardRequested;

	EventList[EV_License_Processed_01].BuzzerRequired 	= true;
	//EventList[EV_License_Processed_01].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_License_Processed_01].EventData, 0xFF, sizeof(EventList[EV_License_Processed_01].EventData));
	EventList[EV_License_Processed_01].AddtionalInfo	= NULL;

	EventList[EV_License_Processed_01].TimeRequired = 0;
	EventList[EV_License_Processed_01].ACKRequired = false;

	// ---- Index - EV_License_Processed_02 - ID ----
	EventList[EV_License_Processed_02].EventCategory 	= Type_Operational;
	EventList[EV_License_Processed_02].EventID 			= 115;

	EventList[EV_License_Processed_02].EventActive 		= false;

	sprintf(EventList[EV_License_Processed_02].EventName, "License Card Processed");

	EventList[EV_License_Processed_02].TimeStampSystic	= 0;

	EventList[EV_License_Processed_02].EventAction1 	= Act_None;
	EventList[EV_License_Processed_02].EventAction2 	= Act_None;
	EventList[EV_License_Processed_02].EventAction3 	= Act_None;
	EventList[EV_License_Processed_02].EventActionTime1_2 = 0;
	EventList[EV_License_Processed_02].EventActionTime2_3 = 0;

	EventList[EV_License_Processed_02].Processed 		= false;
	EventList[EV_License_Processed_02].EventLogged 		= false;

	EventList[EV_License_Processed_02].DispType 		= Disp_None;
	EventList[EV_License_Processed_02].SplashTime		= 0;
	EventList[EV_License_Processed_02].SplashActive		= false;
	//EventList[EV_License_Processed_02].ImageName 		= Icon_CardRequested;

	EventList[EV_License_Processed_02].BuzzerRequired 	= false;
	//EventList[EV_License_Processed_02].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_License_Processed_02].EventData, 0xFF, sizeof(EventList[EV_License_Processed_02].EventData));
	EventList[EV_License_Processed_02].AddtionalInfo	= NULL;

	EventList[EV_License_Processed_02].TimeRequired = 0;
	EventList[EV_License_Processed_02].ACKRequired = false;

	// ---- Index - EV_License_Processed_03 - ID ----
	EventList[EV_License_Processed_03].EventCategory 	= Type_Operational;
	EventList[EV_License_Processed_03].EventID 			= 116;

	EventList[EV_License_Processed_03].EventActive 		= false;

	sprintf(EventList[EV_License_Processed_03].EventName, "License Card Processed");

	EventList[EV_License_Processed_03].TimeStampSystic	= 0;

	EventList[EV_License_Processed_03].EventAction1 	= Act_None;
	EventList[EV_License_Processed_03].EventAction2 	= Act_None;
	EventList[EV_License_Processed_03].EventAction3 	= Act_None;
	EventList[EV_License_Processed_03].EventActionTime1_2 = 0;
	EventList[EV_License_Processed_03].EventActionTime2_3 = 0;

	EventList[EV_License_Processed_03].Processed 		= false;
	EventList[EV_License_Processed_03].EventLogged 		= false;

	EventList[EV_License_Processed_03].DispType 		= Disp_None;
	EventList[EV_License_Processed_03].SplashTime		= 0;
	EventList[EV_License_Processed_03].SplashActive		= false;
	//EventList[EV_License_Processed_03].ImageName 		= Icon_CardRequested;

	EventList[EV_License_Processed_03].BuzzerRequired 	= false;
	//EventList[EV_License_Processed_03].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_License_Processed_03].EventData, 0xFF, sizeof(EventList[EV_License_Processed_03].EventData));
	EventList[EV_License_Processed_03].AddtionalInfo	= NULL;

	EventList[EV_License_Processed_03].TimeRequired = 0;
	EventList[EV_License_Processed_03].ACKRequired = false;

	// ---- Index - EV_License_Processed_04 - ID ----
	EventList[EV_License_Processed_04].EventCategory 	= Type_Operational;
	EventList[EV_License_Processed_04].EventID 			= 117;

	EventList[EV_License_Processed_04].EventActive 		= false;

	sprintf(EventList[EV_License_Processed_04].EventName, "License Card Processed");

	EventList[EV_License_Processed_04].TimeStampSystic	= 0;

	EventList[EV_License_Processed_04].EventAction1 	= Act_None;
	EventList[EV_License_Processed_04].EventAction2 	= Act_None;
	EventList[EV_License_Processed_04].EventAction3 	= Act_None;
	EventList[EV_License_Processed_04].EventActionTime1_2 = 0;
	EventList[EV_License_Processed_04].EventActionTime2_3 = 0;

	EventList[EV_License_Processed_04].Processed 		= false;
	EventList[EV_License_Processed_04].EventLogged 		= false;

	EventList[EV_License_Processed_04].DispType 		= Disp_None;
	EventList[EV_License_Processed_04].SplashTime		= 0;
	EventList[EV_License_Processed_04].SplashActive		= false;
	//EventList[EV_License_Processed_04].ImageName 		= Icon_CardRequested;

	EventList[EV_License_Processed_04].BuzzerRequired 	= false;
	//EventList[EV_License_Processed_04].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_License_Processed_04].EventData, 0xFF, sizeof(EventList[EV_License_Processed_04].EventData));
	EventList[EV_License_Processed_04].AddtionalInfo	= NULL;

	EventList[EV_License_Processed_04].TimeRequired = 0;
	EventList[EV_License_Processed_04].ACKRequired = false;

	// ---- Index - EV_License_Processed_05 - ID ----
	EventList[EV_License_Processed_05].EventCategory 	= Type_Operational;
	EventList[EV_License_Processed_05].EventID 			= 118;

	EventList[EV_License_Processed_05].EventActive 		= false;

	sprintf(EventList[EV_License_Processed_05].EventName, "License Card Processed");

	EventList[EV_License_Processed_05].TimeStampSystic	= 0;

	EventList[EV_License_Processed_05].EventAction1 	= Act_None;
	EventList[EV_License_Processed_05].EventAction2 	= Act_None;
	EventList[EV_License_Processed_05].EventAction3 	= Act_None;
	EventList[EV_License_Processed_05].EventActionTime1_2 = 0;
	EventList[EV_License_Processed_05].EventActionTime2_3 = 0;

	EventList[EV_License_Processed_05].Processed 		= false;
	EventList[EV_License_Processed_05].EventLogged 		= false;

	EventList[EV_License_Processed_05].DispType 		= Disp_None;
	EventList[EV_License_Processed_05].SplashTime		= 0;
	EventList[EV_License_Processed_05].SplashActive		= false;
	//EventList[EV_License_Processed_05].ImageName 		= Icon_CardRequested;

	EventList[EV_License_Processed_05].BuzzerRequired 	= false;
	//EventList[EV_License_Processed_05].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_License_Processed_05].EventData, 0xFF, sizeof(EventList[EV_License_Processed_05].EventData));
	EventList[EV_License_Processed_05].AddtionalInfo	= NULL;

	EventList[EV_License_Processed_05].TimeRequired = 0;
	EventList[EV_License_Processed_05].ACKRequired = false;

	// ---- Index - EV_License_Processed_06 - ID ----
	EventList[EV_License_Processed_06].EventCategory 	= Type_Operational;
	EventList[EV_License_Processed_06].EventID 			= 119;

	EventList[EV_License_Processed_06].EventActive 		= false;

	sprintf(EventList[EV_License_Processed_06].EventName, "License Card Processed");

	EventList[EV_License_Processed_06].TimeStampSystic	= 0;

	EventList[EV_License_Processed_06].EventAction1 	= Act_None;
	EventList[EV_License_Processed_06].EventAction2 	= Act_None;
	EventList[EV_License_Processed_06].EventAction3 	= Act_None;
	EventList[EV_License_Processed_06].EventActionTime1_2 = 0;
	EventList[EV_License_Processed_06].EventActionTime2_3 = 0;

	EventList[EV_License_Processed_06].Processed 		= false;
	EventList[EV_License_Processed_06].EventLogged 		= false;

	EventList[EV_License_Processed_06].DispType 		= Disp_None;
	EventList[EV_License_Processed_06].SplashTime		= 0;
	EventList[EV_License_Processed_06].SplashActive		= false;
	//EventList[EV_License_Processed_06].ImageName 		= Icon_CardRequested;

	EventList[EV_License_Processed_06].BuzzerRequired 	= false;
	//EventList[EV_License_Processed_06].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_License_Processed_06].EventData, 0xFF, sizeof(EventList[EV_License_Processed_06].EventData));
	EventList[EV_License_Processed_06].AddtionalInfo	= NULL;

	EventList[EV_License_Processed_06].TimeRequired = 0;
	EventList[EV_License_Processed_06].ACKRequired = false;

	// ---- Index - EV_License_Processing - ID ----
	EventList[EV_License_Processing].EventCategory 		= Type_Operational;
	EventList[EV_License_Processing].EventID 			= 120;

	EventList[EV_License_Processing].EventActive 		= false;

	sprintf(EventList[EV_License_Processing].EventName, "Processing License Card");

	EventList[EV_License_Processing].TimeStampSystic	= 0;

	EventList[EV_License_Processing].EventAction1 		= Act_DisplayOnly;
	EventList[EV_License_Processing].EventAction2 		= Act_ForceStop;
	EventList[EV_License_Processing].EventAction3 		= Act_ForceStop;
	EventList[EV_License_Processing].EventActionTime1_2 = 0;
	EventList[EV_License_Processing].EventActionTime2_3 = 0;

	EventList[EV_License_Processing].Processed 			= false;
	EventList[EV_License_Processing].EventLogged 		= false;

	EventList[EV_License_Processing].DispType 			= Disp_Generic_SplashScreen;
	EventList[EV_License_Processing].SplashTime			= 5000;
	EventList[EV_License_Processing].SplashActive		= false;
	//EventList[EV_License_Processing].ImageName 			= Icon_MED_ProcessingLicence;

	EventList[EV_License_Processing].BuzzerRequired 	= true;
	//EventList[EV_License_Processing].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_License_Processing].EventData, 0xFF, sizeof(EventList[EV_License_Processing].EventData));
	EventList[EV_License_Processing].AddtionalInfo		= NULL;

	EventList[EV_License_Processing].TimeRequired = 0;
	EventList[EV_License_Processing].ACKRequired = false;

	// ---- Index - EV_License_Invalid - ID ----
	EventList[EV_License_Invalid].EventCategory 		= Type_Operational;
	EventList[EV_License_Invalid].EventID 				= 121;

	EventList[EV_License_Invalid].EventActive 			= false;

	sprintf(EventList[EV_License_Invalid].EventName, "Invalid License Card");

	EventList[EV_License_Invalid].TimeStampSystic		= 0;

	EventList[EV_License_Invalid].EventAction1			= Act_ForceStop;
	EventList[EV_License_Invalid].EventAction2 			= Act_ForceStop;
	EventList[EV_License_Invalid].EventAction3 			= Act_ForceStop;
	EventList[EV_License_Invalid].EventActionTime1_2	= 0;
	EventList[EV_License_Invalid].EventActionTime2_3 	= 0;

	EventList[EV_License_Invalid].Processed				= false;
	EventList[EV_License_Invalid].EventLogged			= false;

	EventList[EV_License_Invalid].DispType 				= Disp_Generic_FullScreen;
	EventList[EV_License_Invalid].SplashTime			= 0;
	EventList[EV_License_Invalid].SplashActive			= false;
	//EventList[EV_License_Invalid].ImageName 			= Icon_MED_InvaidLicence;

	EventList[EV_License_Invalid].BuzzerRequired 		= true;
	//EventList[EV_License_Invalid].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_License_Invalid].EventData, 0xFF, sizeof(EventList[EV_License_Invalid].EventData));
	EventList[EV_License_Invalid].AddtionalInfo			= NULL;

	EventList[EV_License_Invalid].TimeRequired = 0;
	EventList[EV_License_Invalid].ACKRequired = false;

	// ---- Index - EV_Licence_WarningDate - ID ----
	EventList[EV_Licence_WarningDate].EventCategory 	= Type_Operational;
	EventList[EV_Licence_WarningDate].EventID 			= 122;

	EventList[EV_Licence_WarningDate].EventActive 		= false;

	sprintf(EventList[EV_Licence_WarningDate].EventName, "Card Warning Date");

	EventList[EV_Licence_WarningDate].TimeStampSystic	= 0;

	EventList[EV_Licence_WarningDate].EventAction1		= Act_None;
	EventList[EV_Licence_WarningDate].EventAction2 		= Act_None;
	EventList[EV_Licence_WarningDate].EventAction3 		= Act_None;
	EventList[EV_Licence_WarningDate].EventActionTime1_2 = 0;
	EventList[EV_Licence_WarningDate].EventActionTime2_3 = 0;

	EventList[EV_Licence_WarningDate].Processed			= false;
	EventList[EV_Licence_WarningDate].EventLogged		= false;

	EventList[EV_Licence_WarningDate].DispType 			= Disp_Generic_SplashScreen;
	EventList[EV_Licence_WarningDate].SplashTime		= 2000;
	EventList[EV_Licence_WarningDate].SplashActive		= false;
	//EventList[EV_Licence_WarningDate].ImageName 		= Icon_CardRequested;

	EventList[EV_Licence_WarningDate].BuzzerRequired 	= true;
	//EventList[EV_Licence_WarningDate].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_Licence_WarningDate].EventData, 0xFF, sizeof(EventList[EV_Licence_WarningDate].EventData));
	EventList[EV_Licence_WarningDate].AddtionalInfo		= NULL;

	EventList[EV_Licence_WarningDate].TimeRequired = 0;
	EventList[EV_Licence_WarningDate].ACKRequired = false;

	// ---- Index - EV_Licence_ExpiredDate - ID ----
	EventList[EV_Licence_ExpiredDate].EventCategory 	= Type_Operational;
	EventList[EV_Licence_ExpiredDate].EventID 			= 123;

	EventList[EV_Licence_ExpiredDate].EventActive 		= false;

	sprintf(EventList[EV_Licence_ExpiredDate].EventName, "Expired License Card");

	EventList[EV_Licence_ExpiredDate].TimeStampSystic	= 0;

	EventList[EV_Licence_ExpiredDate].EventAction1		= Act_None;
	EventList[EV_Licence_ExpiredDate].EventAction2 		= Act_None;
	EventList[EV_Licence_ExpiredDate].EventAction3 		= Act_None;
	EventList[EV_Licence_ExpiredDate].EventActionTime1_2 = 0;
	EventList[EV_Licence_ExpiredDate].EventActionTime2_3 = 0;

	EventList[EV_Licence_ExpiredDate].Processed			= false;
	EventList[EV_Licence_ExpiredDate].EventLogged		= false;

	EventList[EV_Licence_ExpiredDate].DispType 			= Disp_Generic_SplashScreen;
	EventList[EV_Licence_ExpiredDate].SplashTime		= 2000;
	EventList[EV_Licence_ExpiredDate].SplashActive		= false;
	//EventList[EV_Licence_ExpiredDate].ImageName 		= Icon_CardRequested;

	EventList[EV_Licence_ExpiredDate].BuzzerRequired 	= true;
	//EventList[EV_Licence_ExpiredDate].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_Licence_ExpiredDate].EventData, 0xFF, sizeof(EventList[EV_Licence_ExpiredDate].EventData));
	EventList[EV_Licence_ExpiredDate].AddtionalInfo		= NULL;

	EventList[EV_Licence_ExpiredDate].TimeRequired = 0;
	EventList[EV_Licence_ExpiredDate].ACKRequired = false;

	// ---- Index - EV_License_Valid - ID ----
	EventList[EV_License_Valid].EventCategory 			= Type_Operational;
	EventList[EV_License_Valid].EventID 				= 124;

	EventList[EV_License_Valid].EventActive 			= false;

	sprintf(EventList[EV_License_Valid].EventName, "Valid License Card");

	EventList[EV_License_Valid].TimeStampSystic			= 0;

	EventList[EV_License_Valid].EventAction1			= Act_None;
	EventList[EV_License_Valid].EventAction2 			= Act_None;
	EventList[EV_License_Valid].EventAction3 			= Act_None;
	EventList[EV_License_Valid].EventActionTime1_2 		= 0;
	EventList[EV_License_Valid].EventActionTime2_3 		= 0;

	EventList[EV_License_Valid].Processed 				= false;
	EventList[EV_License_Valid].EventLogged				= false;

	EventList[EV_License_Valid].DispType 				= Disp_Generic_SplashScreen;
	EventList[EV_License_Valid].SplashTime				= 2000;
	EventList[EV_License_Valid].SplashActive			= false;
	//EventList[EV_License_Valid].ImageName 				= Icon_MED_ValidLicence;

	EventList[EV_License_Valid].BuzzerRequired 			= true;
	//EventList[EV_License_Valid].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_License_Invalid].EventData, 0xFF, sizeof(EventList[EV_License_Invalid].EventData));
	EventList[EV_License_Invalid].AddtionalInfo			= NULL;

	EventList[EV_License_Valid].TimeRequired = 0;
	EventList[EV_License_Valid].ACKRequired = false;

	// ---- Index - EV_UnknownRoad - ID ----
	EventList[EV_UnknownRoad].EventCategory 			= Type_Operational;
	EventList[EV_UnknownRoad].EventID 					= 125;

	EventList[EV_UnknownRoad].EventActive 				= false;

	sprintf(EventList[EV_UnknownRoad].EventName, "Select Road Condition");

	EventList[EV_UnknownRoad].TimeStampSystic			= 0;

	EventList[EV_UnknownRoad].EventAction1 				= Act_DisplayOnly;
	EventList[EV_UnknownRoad].EventAction2 				= Act_ForceStop;
	EventList[EV_UnknownRoad].EventAction3 				= Act_ForceStop;
	EventList[EV_UnknownRoad].EventActionTime1_2 		= 0;
	EventList[EV_UnknownRoad].EventActionTime2_3 		= 0;

	EventList[EV_UnknownRoad].Processed 				= false;
	EventList[EV_UnknownRoad].EventLogged				= false;

	EventList[EV_UnknownRoad].DispType 					= Disp_Generic_FullScreen;
	//EventList[EV_UnknownRoad].ImageName 				= Icon_SML_UnkwounRoad;
	EventList[EV_UnknownRoad].SplashTime				= 0;
	EventList[EV_UnknownRoad].SplashActive				= false;

	EventList[EV_UnknownRoad].BuzzerRequired 			= true;
	//EventList[EV_UnknownRoad].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_UnknownRoad].EventData, 0xFF, sizeof(EventList[EV_UnknownRoad].EventData));
	EventList[EV_UnknownRoad].AddtionalInfo				= NULL;

	EventList[EV_UnknownRoad].TimeRequired = 0;
	EventList[EV_UnknownRoad].ACKRequired = false;

	// ---- Index - EV_DryRoad - ID ----
	EventList[EV_DryRoad].EventCategory 				= Type_Operational;
	EventList[EV_DryRoad].EventID 						= 126;

	EventList[EV_DryRoad].EventActive 					= false;

	sprintf(EventList[EV_DryRoad].EventName, "Road Condition - Dry");

	EventList[EV_DryRoad].TimeStampSystic				= 0;

	EventList[EV_DryRoad].EventAction1 					= Act_None;
	EventList[EV_DryRoad].EventAction2 					= Act_None;
	EventList[EV_DryRoad].EventAction3 					= Act_None;
	EventList[EV_DryRoad].EventActionTime1_2 			= 0;
	EventList[EV_DryRoad].EventActionTime2_3 			= 0;

	EventList[EV_DryRoad].Processed 					= false;
	EventList[EV_DryRoad].EventLogged					= false;

	EventList[EV_DryRoad].DispType 						= Disp_Generic_SplashScreen;
	//EventList[EV_DryRoad].ImageName 					= Icon_SML_DryRoad;
	EventList[EV_DryRoad].SplashTime					= 1500;
	EventList[EV_DryRoad].SplashActive					= false;

	EventList[EV_DryRoad].BuzzerRequired 				= true;
	//EventList[EV_DryRoad].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_DryRoad].EventData, 0xFF, sizeof(EventList[EV_DryRoad].EventData));
	EventList[EV_DryRoad].AddtionalInfo					= NULL;

	EventList[EV_DryRoad].TimeRequired = 0;
	EventList[EV_DryRoad].ACKRequired = false;

	// ---- Index - EV_WetRoad - ID ----
	EventList[EV_WetRoad].EventCategory 				= Type_Operational;
	EventList[EV_WetRoad].EventID 						= 127;

	EventList[EV_WetRoad].EventActive 					= false;

	sprintf(EventList[EV_WetRoad].EventName, "Road Condition - Wet");

	EventList[EV_WetRoad].TimeStampSystic				= 0;

	EventList[EV_WetRoad].EventAction1 					= Act_None;
	EventList[EV_WetRoad].EventAction2 					= Act_None;
	EventList[EV_WetRoad].EventAction3 					= Act_None;
	EventList[EV_WetRoad].EventActionTime1_2 			= 0;
	EventList[EV_WetRoad].EventActionTime2_3 			= 0;

	EventList[EV_WetRoad].Processed 					= false;
	EventList[EV_WetRoad].EventLogged					= false;

	EventList[EV_WetRoad].DispType 						= Disp_Generic_SplashScreen;
	//EventList[EV_WetRoad].ImageName 					= Icon_SML_WetRoad;
	EventList[EV_WetRoad].SplashTime					= 1500;
	EventList[EV_WetRoad].SplashActive					= false;

	EventList[EV_WetRoad].BuzzerRequired 				= true;
	//EventList[EV_WetRoad].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_WetRoad].EventData, 0xFF, sizeof(EventList[EV_WetRoad].EventData));
	EventList[EV_WetRoad].AddtionalInfo					= NULL;

	EventList[EV_WetRoad].TimeRequired = 0;
	EventList[EV_WetRoad].ACKRequired = false;

	// ---- Index - EV_WetRoad - ID ----
	EventList[EV_SlipRoad].EventCategory 				= Type_Operational;
	EventList[EV_SlipRoad].EventID 						= 128;

	EventList[EV_SlipRoad].EventActive 					= false;

	sprintf(EventList[EV_SlipRoad].EventName, "Road Condition - Slip");

	EventList[EV_SlipRoad].TimeStampSystic				= 0;

	EventList[EV_SlipRoad].EventAction1 				= Act_None;
	EventList[EV_SlipRoad].EventAction2 				= Act_None;
	EventList[EV_SlipRoad].EventAction3 				= Act_None;
	EventList[EV_SlipRoad].EventActionTime1_2 			= 0;
	EventList[EV_SlipRoad].EventActionTime2_3 			= 0;

	EventList[EV_SlipRoad].Processed 					= false;
	EventList[EV_SlipRoad].EventLogged					= false;

	EventList[EV_SlipRoad].DispType 					= Disp_Generic_SplashScreen;
	//EventList[EV_SlipRoad].ImageName 					= Icon_SML_SlipperyRoad;
	EventList[EV_SlipRoad].SplashTime					= 1500;
	EventList[EV_SlipRoad].SplashActive					= false;

	EventList[EV_SlipRoad].BuzzerRequired 				= true;
	//EventList[EV_SlipRoad].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_SlipRoad].EventData, 0xFF, sizeof(EventList[EV_SlipRoad].EventData));
	EventList[EV_SlipRoad].AddtionalInfo				= NULL;

	EventList[EV_SlipRoad].TimeRequired = 0;
	EventList[EV_SlipRoad].ACKRequired = false;

	// ---- Index - EV_LowSpeedActive - ID ----
	EventList[EV_LowSpeedZone].EventCategory 			= Type_Operational;
	EventList[EV_LowSpeedZone].EventID 					= 129;

	EventList[EV_LowSpeedZone].EventActive				= false;

	sprintf(EventList[EV_LowSpeedZone].EventName, "Low Speed Zone");

	EventList[EV_LowSpeedZone].TimeStampSystic			= 0;

	EventList[EV_LowSpeedZone].EventAction1 			= Act_DisplayOnly;
	EventList[EV_LowSpeedZone].EventAction2 			= Act_ForceSlow;
	EventList[EV_LowSpeedZone].EventAction3 			= Act_ForceSlow;
	EventList[EV_LowSpeedZone].EventActionTime1_2 		= 1000;
	EventList[EV_LowSpeedZone].EventActionTime2_3 		= 1000;

	EventList[EV_LowSpeedZone].Processed				= false;
	EventList[EV_LowSpeedZone].EventLogged				= false;

	EventList[EV_LowSpeedZone].DispType 				= Disp_Icon;
	//EventList[EV_LowSpeedZone].ImageName 				= Icon_Tortoise;
	EventList[EV_LowSpeedZone].SplashTime				= 0;
	EventList[EV_LowSpeedZone].SplashActive				= false;

	EventList[EV_LowSpeedZone].BuzzerRequired			= true;
	//EventList[EV_LowSpeedZone].BuzzerMode				= Buzz_Once;

	memset(EventList[EV_LowSpeedZone].EventData, 0xFF, sizeof(EventList[EV_LowSpeedZone].EventData));
	EventList[EV_LowSpeedZone].AddtionalInfo			= NULL;

	EventList[EV_LowSpeedZone].TimeRequired = 0;
	EventList[EV_LowSpeedZone].ACKRequired = false;

	// ---- Index - EV_MeduimSpeedZone - ID ----
	EventList[EV_MeduimSpeedZone].EventCategory 		= Type_Operational;
	EventList[EV_MeduimSpeedZone].EventID 				= 130;

	EventList[EV_MeduimSpeedZone].EventActive			= false;

	sprintf(EventList[EV_MeduimSpeedZone].EventName, "Medium Speed Zone");

	EventList[EV_MeduimSpeedZone].TimeStampSystic		= 0;

	EventList[EV_MeduimSpeedZone].EventAction1 			= Act_DisplayOnly;
	EventList[EV_MeduimSpeedZone].EventAction2 			= Act_ForceMeduim;
	EventList[EV_MeduimSpeedZone].EventAction3 			= Act_ForceMeduim;
	EventList[EV_MeduimSpeedZone].EventActionTime1_2 	= 1000;
	EventList[EV_MeduimSpeedZone].EventActionTime2_3 	= 1000;

	EventList[EV_MeduimSpeedZone].DispType 				= Disp_Icon;
	//EventList[EV_MeduimSpeedZone].ImageName 			= Icon_WalkingMan;
	EventList[EV_MeduimSpeedZone].SplashTime			= 0;
	EventList[EV_MeduimSpeedZone].SplashActive			= false;

	EventList[EV_MeduimSpeedZone].BuzzerRequired		= true;
	//EventList[EV_MeduimSpeedZone].BuzzerMode			= Buzz_Once;

	memset(EventList[EV_MeduimSpeedZone].EventData, 0xFF, sizeof(EventList[EV_MeduimSpeedZone].EventData));
	EventList[EV_MeduimSpeedZone].AddtionalInfo		= NULL;

	EventList[EV_MeduimSpeedZone].TimeRequired = 0;
	EventList[EV_MeduimSpeedZone].ACKRequired = false;

	// ---- Index - EV_HighSpeedZone - ID ----
	EventList[EV_HighSpeedZone].EventCategory 			= Type_Operational;
	EventList[EV_HighSpeedZone].EventID 				= 131;

	EventList[EV_HighSpeedZone].EventActive 			= false;

	sprintf(EventList[EV_HighSpeedZone].EventName, "High Speed Zone");

	EventList[EV_HighSpeedZone].TimeStampSystic			= 0;

	EventList[EV_HighSpeedZone].EventAction1 			= Act_DisplayOnly;
	EventList[EV_HighSpeedZone].EventAction2 			= Act_ForceHigh;
	EventList[EV_HighSpeedZone].EventAction3 			= Act_ForceHigh;
	EventList[EV_HighSpeedZone].EventActionTime1_2 		= 0;
	EventList[EV_HighSpeedZone].EventActionTime2_3 		= 0;

	EventList[EV_HighSpeedZone].DispType 				= Disp_Icon;
	//EventList[EV_HighSpeedZone].ImageName 				= Icon_Rabbit;
	EventList[EV_HighSpeedZone].SplashTime				= 0;
	EventList[EV_HighSpeedZone].SplashActive			= false;

	EventList[EV_HighSpeedZone].BuzzerRequired			= true;
	//EventList[EV_HighSpeedZone].BuzzerMode				= Buzz_Once;

	memset(EventList[EV_HighSpeedZone].EventData, 0xFF, sizeof(EventList[EV_HighSpeedZone].EventData));
	EventList[EV_HighSpeedZone].AddtionalInfo			= NULL;

	EventList[EV_HighSpeedZone].TimeRequired 			= 0;
	EventList[EV_HighSpeedZone].ACKRequired 			= false;

	// ---- Index - EV_LowSpeedZone_End - ID ----
	EventList[EV_LowSpeedZone_End].EventCategory 		= Type_Operational;
	EventList[EV_LowSpeedZone_End].EventID 				= 132;

	EventList[EV_LowSpeedZone_End].EventActive			= false;

	sprintf(EventList[EV_LowSpeedZone_End].EventName, "Low Speed Zone End");

	EventList[EV_LowSpeedZone_End].TimeStampSystic			= 0;

	EventList[EV_LowSpeedZone_End].EventAction1 		= Act_None;
	EventList[EV_LowSpeedZone_End].EventAction2 		= Act_None;
	EventList[EV_LowSpeedZone_End].EventAction3 		= Act_None;
	EventList[EV_LowSpeedZone_End].EventActionTime1_2 	= 0;
	EventList[EV_LowSpeedZone_End].EventActionTime2_3 	= 0;

	EventList[EV_LowSpeedZone_End].Processed			= false;
	EventList[EV_LowSpeedZone_End].EventLogged			= false;

	EventList[EV_LowSpeedZone_End].DispType 			= Disp_Message;
	//EventList[EV_LowSpeedZone_End].ImageName 			= Icon_Tortoise;
	EventList[EV_LowSpeedZone_End].SplashTime			= 0;
	EventList[EV_LowSpeedZone_End].SplashActive			= false;

	EventList[EV_LowSpeedZone_End].BuzzerRequired		= false;
	//EventList[EV_LowSpeedZone_End].BuzzerMode			= Buzz_Once;

	memset(EventList[EV_LowSpeedZone_End].EventData, 0xFF, sizeof(EventList[EV_LowSpeedZone_End].EventData));
	EventList[EV_LowSpeedZone_End].AddtionalInfo		= NULL;

	EventList[EV_LowSpeedZone_End].TimeRequired = 0;
	EventList[EV_LowSpeedZone_End].ACKRequired = false;

	// ---- Index - EV_MeduimSpeedZone_End - ID ----
	EventList[EV_MeduimSpeedZone_End].EventCategory 	= Type_Operational;
	EventList[EV_MeduimSpeedZone_End].EventID 			= 133;

	EventList[EV_MeduimSpeedZone_End].EventActive		= false;

	sprintf(EventList[EV_MeduimSpeedZone_End].EventName, "Medium Speed Zone End");

	EventList[EV_MeduimSpeedZone_End].TimeStampSystic	= 0;

	EventList[EV_MeduimSpeedZone_End].EventAction1 		= Act_None;
	EventList[EV_MeduimSpeedZone_End].EventAction2 		= Act_None;
	EventList[EV_MeduimSpeedZone_End].EventAction3 		= Act_None;
	EventList[EV_MeduimSpeedZone_End].EventActionTime1_2 = 0;
	EventList[EV_MeduimSpeedZone_End].EventActionTime2_3 = 0;

	EventList[EV_MeduimSpeedZone_End].DispType 			= Disp_Message;
	//EventList[EV_MeduimSpeedZone_End].ImageName 		= Icon_WalkingMan;
	EventList[EV_MeduimSpeedZone_End].SplashTime		= 0;
	EventList[EV_MeduimSpeedZone_End].SplashActive		= false;

	EventList[EV_MeduimSpeedZone_End].BuzzerRequired	= false	;
	//EventList[EV_MeduimSpeedZone_End].BuzzerMode		= Buzz_Once;

	memset(EventList[EV_MeduimSpeedZone_End].EventData, 0xFF, sizeof(EventList[EV_MeduimSpeedZone_End].EventData));
	EventList[EV_MeduimSpeedZone_End].AddtionalInfo		= NULL;

	EventList[EV_MeduimSpeedZone_End].TimeRequired = 0;
	EventList[EV_MeduimSpeedZone_End].ACKRequired = false;

	// ---- Index - EV_HighSpeedZone_End - ID ----
	EventList[EV_HighSpeedZone_End].EventCategory 		= Type_Operational;
	EventList[EV_HighSpeedZone_End].EventID 			= 134;

	EventList[EV_HighSpeedZone_End].EventActive 		= false;

	sprintf(EventList[EV_HighSpeedZone_End].EventName, "High Speed Zone End");

	EventList[EV_HighSpeedZone_End].TimeStampSystic		= 0;

	EventList[EV_HighSpeedZone_End].EventAction1 		= Act_None;
	EventList[EV_HighSpeedZone_End].EventAction2 		= Act_None;
	EventList[EV_HighSpeedZone_End].EventAction3 		= Act_None;
	EventList[EV_HighSpeedZone_End].EventActionTime1_2 	= 0;
	EventList[EV_HighSpeedZone_End].EventActionTime2_3 	= 0;

	EventList[EV_HighSpeedZone_End].DispType 			= Disp_Message;
	//EventList[EV_HighSpeedZone_End].ImageName 			= Icon_Rabbit;
	EventList[EV_HighSpeedZone_End].SplashTime			= 0;
	EventList[EV_HighSpeedZone_End].SplashActive		= false;

	EventList[EV_HighSpeedZone_End].BuzzerRequired		= false;
	//EventList[EV_HighSpeedZone_End].BuzzerMode			= Buzz_Once;

	memset(EventList[EV_HighSpeedZone_End].EventData, 0xFF, sizeof(EventList[EV_HighSpeedZone_End].EventData));
	EventList[EV_HighSpeedZone_End].AddtionalInfo		= NULL;

	EventList[EV_HighSpeedZone_End].TimeRequired = 0;
	EventList[EV_HighSpeedZone_End].ACKRequired = false;

	// ---- Index - EV_Speed_OK - ID ----
	EventList[EV_Speed_OK].EventCategory 				= Type_Operational;
	EventList[EV_Speed_OK].EventID 						= 135;

	EventList[EV_Speed_OK].EventActive 					= false;

	sprintf(EventList[EV_Speed_OK].EventName, "Speed - OK");

	EventList[EV_Speed_OK].TimeStampSystic				= 0;

	EventList[EV_Speed_OK].EventAction1 				= Act_None;
	EventList[EV_Speed_OK].EventAction2 				= Act_None;
	EventList[EV_Speed_OK].EventAction3 				= Act_None;
	EventList[EV_Speed_OK].EventActionTime1_2 			= 0;
	EventList[EV_Speed_OK].EventActionTime2_3 			= 0;

	EventList[EV_Speed_OK].Processed 					= false;
	EventList[EV_Speed_OK].EventLogged					= false;

	EventList[EV_Speed_OK].DispType 					= Disp_None;
	//EventList[EV_Speed_OK].ImageName 					= Icon_Attention;
	EventList[EV_Speed_OK].SplashTime					= 0;
	EventList[EV_Speed_OK].SplashActive					= false;

	EventList[EV_Speed_OK].BuzzerRequired 				= false;
	//EventList[EV_Speed_OK].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_Speed_OK].EventData, 0xFF, sizeof(EventList[EV_Speed_OK].EventData));
	EventList[EV_Speed_OK].AddtionalInfo				= NULL;

	EventList[EV_Speed_OK].TimeRequired = 0;
	EventList[EV_Speed_OK].ACKRequired = false;

	// ---- Index - EV_Speed_OKEnd - ID ----
	EventList[EV_Speed_OKEnd].EventCategory 			= Type_Operational;
	EventList[EV_Speed_OKEnd].EventID 					= 136;

	EventList[EV_Speed_OKEnd].EventActive 				= false;

	sprintf(EventList[EV_Speed_OKEnd].EventName, "Speed - OK End");

	EventList[EV_Speed_OKEnd].TimeStampSystic			= 0;

	EventList[EV_Speed_OKEnd].EventAction1 				= Act_None;
	EventList[EV_Speed_OKEnd].EventAction2 				= Act_None;
	EventList[EV_Speed_OKEnd].EventAction3 				= Act_None;
	EventList[EV_Speed_OKEnd].EventActionTime1_2 		= 0;
	EventList[EV_Speed_OKEnd].EventActionTime2_3 		= 0;

	EventList[EV_Speed_OKEnd].Processed 				= false;
	EventList[EV_Speed_OKEnd].EventLogged				= false;

	EventList[EV_Speed_OKEnd].DispType 					= Disp_None;
	//EventList[EV_Speed_OKEnd].ImageName 				= Icon_Attention;
	EventList[EV_Speed_OKEnd].SplashTime				= 0;
	EventList[EV_Speed_OKEnd].SplashActive				= false;

	EventList[EV_Speed_OKEnd].BuzzerRequired 			= false;
	//EventList[EV_Speed_OKEnd].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Speed_OKEnd].EventData, 0xFF, sizeof(EventList[EV_Speed_OKEnd].EventData));
	EventList[EV_Speed_OKEnd].AddtionalInfo				= NULL;

	EventList[EV_Speed_OKEnd].TimeRequired = 0;
	EventList[EV_Speed_OKEnd].ACKRequired = false;

	// ---- Index - EV_Speedo_Warning - ID ----
	EventList[EV_Speed_Warning].EventCategory 			= Type_Operational;
	EventList[EV_Speed_Warning].EventID 				= 137;

	EventList[EV_Speed_Warning].EventActive 			= false;

	sprintf(EventList[EV_Speed_Warning].EventName, "Speed - Warn Limit");

	EventList[EV_Speed_Warning].TimeStampSystic 		= 0;

	EventList[EV_Speed_Warning].EventAction1 			= Act_None;
	EventList[EV_Speed_Warning].EventAction2 			= Act_None;
	EventList[EV_Speed_Warning].EventAction3 			= Act_None;
	EventList[EV_Speed_Warning].EventActionTime1_2 		= 0;
	EventList[EV_Speed_Warning].EventActionTime2_3 		= 0;

	EventList[EV_Speed_Warning].Processed 				= false;
	EventList[EV_Speed_Warning].EventLogged				= false;

	EventList[EV_Speed_Warning].DispType 				= Disp_Generic_SplashScreen;
	//EventList[EV_Speed_Warning].ImageName 				= Icon_Attention;
	EventList[EV_Speed_Warning].SplashTime 				= 1500;
	EventList[EV_Speed_Warning].SplashActive			= false;

	EventList[EV_Speed_Warning].BuzzerRequired 			= true;
	//EventList[EV_Speed_Warning].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_Speed_Warning].EventData, 0xFF, sizeof(EventList[EV_Speed_Warning].EventData));
	EventList[EV_Speed_Warning].AddtionalInfo			= NULL;

	EventList[EV_Speed_Warning].TimeRequired = 0;
	EventList[EV_Speed_Warning].ACKRequired = false;

	// ---- Index - EV_Speed_WarningEnd - ID ----
	EventList[EV_Speed_WarningEnd].EventCategory 		= Type_Operational;
	EventList[EV_Speed_WarningEnd].EventID 				= 138;

	EventList[EV_Speed_WarningEnd].EventActive 			= false;

	sprintf(EventList[EV_Speed_WarningEnd].EventName, "Speed - Warn Limit End");

	EventList[EV_Speed_WarningEnd].TimeStampSystic 		= 0;

	EventList[EV_Speed_WarningEnd].EventAction1 		= Act_None;
	EventList[EV_Speed_WarningEnd].EventAction2 		= Act_None;
	EventList[EV_Speed_WarningEnd].EventAction3 		= Act_None;
	EventList[EV_Speed_WarningEnd].EventActionTime1_2 	= 0;
	EventList[EV_Speed_WarningEnd].EventActionTime2_3 	= 0;

	EventList[EV_Speed_WarningEnd].Processed 			= false;
	EventList[EV_Speed_WarningEnd].EventLogged			= false;

	EventList[EV_Speed_WarningEnd].DispType 			= Disp_None;
	//EventList[EV_Speed_WarningEnd].ImageName 			= Icon_Attention;
	EventList[EV_Speed_WarningEnd].SplashTime 			= 0;
	EventList[EV_Speed_WarningEnd].SplashActive			= false;

	EventList[EV_Speed_WarningEnd].BuzzerRequired 		= false;
	//EventList[EV_Speed_WarningEnd].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Speed_WarningEnd].EventData, 0xFF, sizeof(EventList[EV_Speed_WarningEnd].EventData));
	EventList[EV_Speed_WarningEnd].AddtionalInfo		= NULL;

	EventList[EV_Speed_WarningEnd].TimeRequired = 0;
	EventList[EV_Speed_WarningEnd].ACKRequired = false;

	// ---- Index - EV_Speedo_Overspeeding - ID ----
	EventList[EV_Speed_Overspeeding].EventCategory 		= Type_Operational;
	EventList[EV_Speed_Overspeeding].EventID 			= 139;

	EventList[EV_Speed_Overspeeding].EventActive 		= false;

	sprintf(EventList[EV_Speed_Overspeeding].EventName, "Speed - Over Limit");

	EventList[EV_Speed_Overspeeding].TimeStampSystic 	= 0;

	EventList[EV_Speed_Overspeeding].EventAction1 		= Act_None;
	EventList[EV_Speed_Overspeeding].EventAction2 		= Act_None;
	EventList[EV_Speed_Overspeeding].EventAction3 		= Act_None;
	EventList[EV_Speed_Overspeeding].EventActionTime1_2 = 0;
	EventList[EV_Speed_Overspeeding].EventActionTime2_3 = 0;

	EventList[EV_Speed_Overspeeding].Processed 			= false;
	EventList[EV_Speed_Overspeeding].EventLogged		= false;

	EventList[EV_Speed_Overspeeding].DispType 			= Disp_Generic_SplashScreen;
	//EventList[EV_Speed_Overspeeding].ImageName 			= Icon_Attention;
	EventList[EV_Speed_Overspeeding].SplashTime 		= 1500;
	EventList[EV_Speed_Overspeeding].SplashActive		= false;

	EventList[EV_Speed_Overspeeding].BuzzerRequired 	= true;
	//EventList[EV_Speed_Overspeeding].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_Speed_Overspeeding].EventData, 0xFF, sizeof(EventList[EV_Speed_Overspeeding].EventData));
	EventList[EV_Speed_Overspeeding].AddtionalInfo		= NULL;

	EventList[EV_Speed_Overspeeding].TimeRequired = 0;
	EventList[EV_Speed_Overspeeding].ACKRequired = false;

	// ---- Index - EV_Speed_OverspeedingEnd - ID ----
	EventList[EV_Speed_OverspeedingEnd].EventCategory 	= Type_Operational;
	EventList[EV_Speed_OverspeedingEnd].EventID 		= 140;

	EventList[EV_Speed_OverspeedingEnd].EventActive 	= false;

	sprintf(EventList[EV_Speed_OverspeedingEnd].EventName, "Speed - Over Limit End");

	EventList[EV_Speed_OverspeedingEnd].TimeStampSystic = 0;

	EventList[EV_Speed_OverspeedingEnd].EventAction1 	= Act_None;
	EventList[EV_Speed_OverspeedingEnd].EventAction2 	= Act_None;
	EventList[EV_Speed_OverspeedingEnd].EventAction3 	= Act_None;
	EventList[EV_Speed_OverspeedingEnd].EventActionTime1_2 = 0;
	EventList[EV_Speed_OverspeedingEnd].EventActionTime2_3 = 0;

	EventList[EV_Speed_OverspeedingEnd].Processed 		= false;
	EventList[EV_Speed_OverspeedingEnd].EventLogged		= false;

	EventList[EV_Speed_OverspeedingEnd].DispType 		= Disp_None;
	//EventList[EV_Speed_OverspeedingEnd].ImageName 		= Icon_Attention;
	EventList[EV_Speed_OverspeedingEnd].SplashTime 		= 0;
	EventList[EV_Speed_OverspeedingEnd].SplashActive	= false;

	EventList[EV_Speed_OverspeedingEnd].BuzzerRequired 	= false;
	//EventList[EV_Speed_OverspeedingEnd].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_Speed_OverspeedingEnd].EventData, 0xFF, sizeof(EventList[EV_Speed_OverspeedingEnd].EventData));
	EventList[EV_Speed_OverspeedingEnd].AddtionalInfo		= NULL;

	EventList[EV_Speed_OverspeedingEnd].TimeRequired = 0;
	EventList[EV_Speed_OverspeedingEnd].ACKRequired = false;

	// ---- Index - EV_Operational_WorkZone - ID ----
	EventList[EV_Operational_WorkZone_01].EventCategory = Type_Operational;
	EventList[EV_Operational_WorkZone_01].EventID 		= 141;

	EventList[EV_Operational_WorkZone_01].EventActive 	= false;

	sprintf(EventList[EV_Operational_WorkZone_01].EventName, "Work Zone Operation");

	EventList[EV_Operational_WorkZone_01].TimeStampSystic = 0;

	EventList[EV_Operational_WorkZone_01].EventAction1 	= Act_Overrule;
	EventList[EV_Operational_WorkZone_01].EventAction2 	= Act_Overrule;
	EventList[EV_Operational_WorkZone_01].EventAction3 	= Act_Overrule;
	EventList[EV_Operational_WorkZone_01].EventActionTime1_2 = 0;
	EventList[EV_Operational_WorkZone_01].EventActionTime2_3 = 0;

	EventList[EV_Operational_WorkZone_01].Processed 	= false;
	EventList[EV_Operational_WorkZone_01].EventLogged	= false;

	EventList[EV_Operational_WorkZone_01].DispType 		= Disp_Icon;
	//EventList[EV_Operational_WorkZone_01].ImageName 	= Icon_Tram;
	EventList[EV_Operational_WorkZone_01].SplashTime 	= 0;
	EventList[EV_Operational_WorkZone_01].SplashActive	= false;

	EventList[EV_Operational_WorkZone_01].BuzzerRequired = true;
	//EventList[EV_Operational_WorkZone_01].BuzzerMode 	= Buzz_Once;

	memset(EventList[EV_Operational_WorkZone_01].EventData, 0xFF, sizeof(EventList[EV_Operational_WorkZone_01].EventData));
	EventList[EV_Operational_WorkZone_01].AddtionalInfo	= NULL;

	EventList[EV_Operational_WorkZone_01].TimeRequired = 0;
	EventList[EV_Operational_WorkZone_01].ACKRequired = false;

	// ---- Index - EV_Operational_WorkZone_02 - ID ----
	EventList[EV_Operational_WorkZone_02].EventCategory	= Type_Operational;
	EventList[EV_Operational_WorkZone_02].EventID 		= 141;

	EventList[EV_Operational_WorkZone_02].EventActive 	= false;

	sprintf(EventList[EV_Operational_WorkZone_02].EventName, "Work Zone Operation");

	EventList[EV_Operational_WorkZone_02].TimeStampSystic = 0;

	EventList[EV_Operational_WorkZone_02].EventAction1 	= Act_Overrule;
	EventList[EV_Operational_WorkZone_02].EventAction2 	= Act_Overrule;
	EventList[EV_Operational_WorkZone_02].EventAction3 	= Act_Overrule;
	EventList[EV_Operational_WorkZone_02].EventActionTime1_2 = 0;
	EventList[EV_Operational_WorkZone_02].EventActionTime2_3 = 0;

	EventList[EV_Operational_WorkZone_02].Processed 	= false;
	EventList[EV_Operational_WorkZone_02].EventLogged	= false;

	EventList[EV_Operational_WorkZone_02].DispType 		= Disp_None;
	//EventList[EV_Operational_WorkZone_02].ImageName 	= Icon_Tram;
	EventList[EV_Operational_WorkZone_02].SplashTime 	= 0;
	EventList[EV_Operational_WorkZone_02].SplashActive	= false;

	EventList[EV_Operational_WorkZone_02].BuzzerRequired = false;
	//EventList[EV_Operational_WorkZone_02].BuzzerMode 	= Buzz_Once;

	memset(EventList[EV_Operational_WorkZone_02].EventData, 0xFF, sizeof(EventList[EV_Operational_WorkZone_02].EventData));
	EventList[EV_Operational_WorkZone_02].AddtionalInfo	= NULL;

	EventList[EV_Operational_WorkZone_02].TimeRequired = 0;
	EventList[EV_Operational_WorkZone_02].ACKRequired = false;

	// ---- Index - EV_Operational_WorkZoneEnd - ID ----
	EventList[EV_Operational_WorkZoneEnd].EventCategory = Type_Operational;
	EventList[EV_Operational_WorkZoneEnd].EventID 		= 143;

	EventList[EV_Operational_WorkZoneEnd].EventActive 	= false;

	sprintf(EventList[EV_Operational_WorkZoneEnd].EventName, "Work Zone Operation End");

	EventList[EV_Operational_WorkZoneEnd].TimeStampSystic = 0;

	EventList[EV_Operational_WorkZoneEnd].EventAction1 	= Act_None;
	EventList[EV_Operational_WorkZoneEnd].EventAction2 	= Act_None;
	EventList[EV_Operational_WorkZoneEnd].EventAction3 	= Act_None;
	EventList[EV_Operational_WorkZoneEnd].EventActionTime1_2 	= 0;
	EventList[EV_Operational_WorkZoneEnd].EventActionTime2_3 	= 0;

	EventList[EV_Operational_WorkZoneEnd].Processed 	= false;
	EventList[EV_Operational_WorkZoneEnd].EventLogged	= false;

	EventList[EV_Operational_WorkZoneEnd].DispType 		= Disp_None;
	//EventList[EV_Operational_WorkZoneEnd].ImageName 	= Icon_Tram;
	EventList[EV_Operational_WorkZoneEnd].SplashTime 	= 0;
	EventList[EV_Operational_WorkZoneEnd].SplashActive	= false;

	EventList[EV_Operational_WorkZoneEnd].BuzzerRequired= false;
	//EventList[EV_Operational_WorkZoneEnd].BuzzerMode 	= Buzz_Once;

	memset(EventList[EV_Operational_WorkZoneEnd].EventData, 0xFF, sizeof(EventList[EV_Operational_WorkZoneEnd].EventData));
	EventList[EV_Operational_WorkZoneEnd].AddtionalInfo	= NULL;

	EventList[EV_Operational_WorkZoneEnd].TimeRequired = 0;
	EventList[EV_Operational_WorkZoneEnd].ACKRequired = false;

	// ---- Index - EV_Operational_WorkZoneFail - ID ----
	EventList[EV_Operational_WorkZoneFail].EventCategory= Type_Operational;
	EventList[EV_Operational_WorkZoneFail].EventID 		= 144;

	EventList[EV_Operational_WorkZoneFail].EventActive 	= false;

	sprintf(EventList[EV_Operational_WorkZoneFail].EventName, "Work Zone Activate Fail");

	EventList[EV_Operational_WorkZoneFail].TimeStampSystic = 0;

	EventList[EV_Operational_WorkZoneFail].EventAction1 = Act_None;
	EventList[EV_Operational_WorkZoneFail].EventAction2	= Act_None;
	EventList[EV_Operational_WorkZoneFail].EventAction3	= Act_None;
	EventList[EV_Operational_WorkZoneFail].EventActionTime1_2 = 0;
	EventList[EV_Operational_WorkZoneFail].EventActionTime2_3 = 0;

	EventList[EV_Operational_WorkZoneFail].Processed 	= false;
	EventList[EV_Operational_WorkZoneFail].EventLogged	= false;

	EventList[EV_Operational_WorkZoneFail].DispType 	= Disp_Icon;
	//EventList[EV_Operational_WorkZoneFail].ImageName 	= Icon_Tram;
	EventList[EV_Operational_WorkZoneFail].SplashTime 	= 0;
	EventList[EV_Operational_WorkZoneFail].SplashActive	= false;

	EventList[EV_Operational_WorkZoneFail].BuzzerRequired = true;
	//EventList[EV_Operational_WorkZoneFail].BuzzerMode 	= Buzz_Once;

	memset(EventList[EV_Operational_WorkZoneFail].EventData, 0xFF, sizeof(EventList[EV_Operational_WorkZoneFail].EventData));

	EventList[EV_Operational_WorkZoneFail].TimeRequired = 0;
	EventList[EV_Operational_WorkZoneFail].ACKRequired = false;

	// ---- Index - EV_SystemAction - ID ----
	EventList[EV_SystemAction].EventCategory 			= Type_Operational;
	EventList[EV_SystemAction].EventID					= 145;

	EventList[EV_SystemAction].EventActive 				= false;

	sprintf(EventList[EV_SystemAction].EventName, "System Action");

	EventList[EV_SystemAction].TimeStampSystic 			= 0;

	EventList[EV_SystemAction].EventAction1				= Act_None;
	EventList[EV_SystemAction].EventAction2 			= Act_None;
	EventList[EV_SystemAction].EventAction3 			= Act_None;
	EventList[EV_SystemAction].EventActionTime1_2 		= 0;
	EventList[EV_SystemAction].EventActionTime2_3 		= 0;

	EventList[EV_SystemAction].Processed				= false;
	EventList[EV_SystemAction].EventLogged				= false;

	EventList[EV_SystemAction].DispType 				= Disp_None;
	//EventList[EV_SystemAction].ImageName 				= Icon_Attention;
	EventList[EV_SystemAction].SplashTime 				= 0;
	EventList[EV_SystemAction].SplashActive				= false;

	EventList[EV_SystemAction].BuzzerRequired 			= false;
	//EventList[EV_SystemAction].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_SystemAction].EventData, 0xFF, sizeof(EventList[EV_SystemAction].EventData));
	EventList[EV_SystemAction].AddtionalInfo			= NULL;

	EventList[EV_SystemAction].TimeRequired = 0;
	EventList[EV_SystemAction].ACKRequired = false;

	/*-------------------------------------------------------------------------------------------------------
	 * 								  Proximity Detection Events
	 *-------------------------------------------------------------------------------------------------------*/
	// ---- Index - EV_PDS_1 - ID ----
	EventList[EV_PDS_1].EventCategory 					= Type_PDS;
	EventList[EV_PDS_1].EventID 						= 150;

	EventList[EV_PDS_1].EventActive 					= false;

	sprintf(EventList[EV_PDS_1].EventName, "Proximity Detection 01");

	EventList[EV_PDS_1].TimeStampSystic					= 0;

	EventList[EV_PDS_1].EventAction1					= Act_None;
	EventList[EV_PDS_1].EventAction2 					= Act_None;
	EventList[EV_PDS_1].EventAction3 					= Act_None;
	EventList[EV_PDS_1].EventActionTime1_2 				= 0;
	EventList[EV_PDS_1].EventActionTime2_3 				= 0;

	EventList[EV_PDS_1].Processed						= false;
	EventList[EV_PDS_1].EventLogged						= false;

	EventList[EV_PDS_1].DispType 						= Disp_Dedicated_FullScreen;
	//EventList[EV_PDS_1].ImageName 						= Icon_LowSpeed;
	EventList[EV_PDS_1].SplashTime 						= 0;
	EventList[EV_PDS_1].SplashActive					= false;

	EventList[EV_PDS_1].BuzzerRequired 					= true;
	//EventList[EV_PDS_1].BuzzerMode 						= Buzz_Fast;

	memset(EventList[EV_PDS_1].EventData, 0xFF, sizeof(EventList[EV_PDS_1].EventData));
	EventList[EV_PDS_1].AddtionalInfo					= NULL;

	//EventList[EV_PDS_1].TimeRequired 					= Local_Params[Local_ProcessingTime_OPE].ParamCURRENT;
	EventList[EV_PDS_1].ACKRequired 					= true;
	EventList[EV_PDS_1].EventACKAction					= Act_DisplayOnly;

	// ---- Index - EV_PDS_2 - ID ----
	EventList[EV_PDS_2].EventCategory 					= Type_PDS;
	EventList[EV_PDS_2].EventID 						= 151;

	EventList[EV_PDS_2].EventActive 					= false;

	sprintf(EventList[EV_PDS_2].EventName, "Proximity Detection 02");

	EventList[EV_PDS_2].EventAction1 					= Act_None;
	EventList[EV_PDS_2].EventAction2 					= Act_None;
	EventList[EV_PDS_2].EventAction3 					= Act_None;
	EventList[EV_PDS_2].EventActionTime1_2 				= 0;
	EventList[EV_PDS_2].EventActionTime2_3 				= 0;

	EventList[EV_PDS_2].Processed						= false;
	EventList[EV_PDS_2].EventLogged						= false;

	EventList[EV_PDS_2].DispType 						= Disp_Dedicated_FullScreen;
	//EventList[EV_PDS_2].ImageName 						= Icon_LowSpeed;
	EventList[EV_PDS_2].SplashTime 						= 0;
	EventList[EV_PDS_2].SplashActive					= false;

	EventList[EV_PDS_2].BuzzerRequired 					= false;
	//EventList[EV_PDS_2].BuzzerMode 						= Buzz_Fast;

	memset(EventList[EV_PDS_2].EventData, 0xFF, sizeof(EventList[EV_PDS_2].EventData));
	EventList[EV_PDS_2].AddtionalInfo					= NULL;

	//EventList[EV_PDS_2].TimeRequired 					= Local_Params[Local_ProcessingTime_OPE].ParamCURRENT;
	EventList[EV_PDS_2].ACKRequired 					= true;

	// ---- Index - EV_PDS_3 - ID ----
	EventList[EV_PDS_3].EventCategory 					= Type_PDS;
	EventList[EV_PDS_3].EventID 						= 152;

	EventList[EV_PDS_3].EventActive 					= false;

	sprintf(EventList[EV_PDS_3].EventName, "Proximity Detection 03");

	EventList[EV_PDS_3].TimeStampSystic					= 0;

	EventList[EV_PDS_3].EventAction1 					= Act_None;
	EventList[EV_PDS_3].EventAction2 					= Act_None;
	EventList[EV_PDS_3].EventAction3 					= Act_None;
	EventList[EV_PDS_3].EventActionTime1_2 				= 0;
	EventList[EV_PDS_3].EventActionTime2_3 				= 0;

	EventList[EV_PDS_3].Processed						= false;
	EventList[EV_PDS_3].EventLogged						= false;

	EventList[EV_PDS_3].DispType 						= Disp_Dedicated_FullScreen;
	//EventList[EV_PDS_3].ImageName 						= Icon_LowSpeed;
	EventList[EV_PDS_3].SplashTime 						= 0;
	EventList[EV_PDS_3].SplashActive					= false;

	EventList[EV_PDS_3].BuzzerRequired					= false;
	//EventList[EV_PDS_3].BuzzerMode 						= Buzz_Fast;

	memset(EventList[EV_PDS_3].EventData, 0xFF, sizeof(EventList[EV_PDS_3].EventData));
	EventList[EV_PDS_3].AddtionalInfo					= NULL;

	//EventList[EV_PDS_3].TimeRequired 					= Local_Params[Local_ProcessingTime_OPE].ParamCURRENT;
	EventList[EV_PDS_3].ACKRequired 					= true;

	// ---- Index - EV_PDS_4 - ID ----
	EventList[EV_PDS_4].EventCategory 					= Type_PDS;
	EventList[EV_PDS_4].EventID 						= 153;

	EventList[EV_PDS_4].EventActive 					= false;

	sprintf(EventList[EV_PDS_4].EventName, "Proximity Detection 04");

	EventList[EV_PDS_4].TimeStampSystic					= 0;

	EventList[EV_PDS_4].EventAction1 					= Act_None;
	EventList[EV_PDS_4].EventAction2 					= Act_None;
	EventList[EV_PDS_4].EventAction3 					= Act_None;
	EventList[EV_PDS_4].EventActionTime1_2 				= 0;
	EventList[EV_PDS_4].EventActionTime2_3 				= 0;

	EventList[EV_PDS_4].Processed						= false;
	EventList[EV_PDS_4].EventLogged						= false;

	EventList[EV_PDS_4].DispType 						= Disp_Dedicated_FullScreen;
	//EventList[EV_PDS_4].ImageName 						= Icon_LowSpeed;
	EventList[EV_PDS_4].SplashTime 						= 0;
	EventList[EV_PDS_4].SplashActive					= false;

	EventList[EV_PDS_4].BuzzerRequired 					= false;
	//EventList[EV_PDS_4].BuzzerMode 						= Buzz_Fast;

	memset(EventList[EV_PDS_4].EventData, 0xFF, sizeof(EventList[EV_PDS_4].EventData));
	EventList[EV_PDS_4].AddtionalInfo					= NULL;

	//EventList[EV_PDS_4].TimeRequired 					= Local_Params[Local_ProcessingTime_OPE].ParamCURRENT;
	EventList[EV_PDS_4].ACKRequired 					= true;

	// ---- Index - EV_PDS_5 - ID ----
	EventList[EV_PDS_5].EventCategory 					= Type_PDS;
	EventList[EV_PDS_5].EventID 						= 154;

	EventList[EV_PDS_5].EventActive 					= false;

	sprintf(EventList[EV_PDS_5].EventName, "Proximity Detection 05");

	EventList[EV_PDS_5].TimeStampSystic					= 0;

	EventList[EV_PDS_5].EventAction1					= Act_None;
	EventList[EV_PDS_5].EventAction2 					= Act_None;
	EventList[EV_PDS_5].EventAction3 					= Act_None;
	EventList[EV_PDS_5].EventActionTime1_2 				= 0;
	EventList[EV_PDS_5].EventActionTime2_3 				= 0;

	EventList[EV_PDS_5].Processed						= false;
	EventList[EV_PDS_5].EventLogged						= false;

	EventList[EV_PDS_5].DispType 						= Disp_Dedicated_FullScreen;
	//EventList[EV_PDS_5].ImageName 						= Icon_LowSpeed;
	EventList[EV_PDS_5].SplashTime 						= 0;
	EventList[EV_PDS_5].SplashActive					= false;

	EventList[EV_PDS_5].BuzzerRequired 					= false;
	//EventList[EV_PDS_5].BuzzerMode 						= Buzz_Fast;

	memset(EventList[EV_PDS_5].EventData, 0xFF, sizeof(EventList[EV_PDS_5].EventData));
	EventList[EV_PDS_5].AddtionalInfo					= NULL;

	//EventList[EV_PDS_5].TimeRequired 					= Local_Params[Local_ProcessingTime_OPE].ParamCURRENT;
	EventList[EV_PDS_5].ACKRequired 					= true;

	// ---- Index - EV_PDS_6 - ID ----
	EventList[EV_PDS_6].EventCategory 					= Type_PDS;
	EventList[EV_PDS_6].EventID 						= 155;

	EventList[EV_PDS_6].EventActive 					= false;

	sprintf(EventList[EV_PDS_6].EventName, "Proximity Detection 05");

	EventList[EV_PDS_6].TimeStampSystic					= 0;

	EventList[EV_PDS_6].EventAction1					= Act_None;
	EventList[EV_PDS_6].EventAction2 					= Act_None;
	EventList[EV_PDS_6].EventAction3 					= Act_None;
	EventList[EV_PDS_6].EventActionTime1_2 				= 0;
	EventList[EV_PDS_6].EventActionTime2_3 				= 0;

	EventList[EV_PDS_6].Processed						= false;
	EventList[EV_PDS_6].EventLogged						= false;

	EventList[EV_PDS_6].DispType 						= Disp_Dedicated_FullScreen;
	//EventList[EV_PDS_6].ImageName 						= Icon_LowSpeed;
	EventList[EV_PDS_6].SplashTime 						= 0;
	EventList[EV_PDS_6].SplashActive					= false;

	EventList[EV_PDS_6].BuzzerRequired 					= false;
	//EventList[EV_PDS_6].BuzzerMode 						= Buzz_Fast;

	memset(EventList[EV_PDS_6].EventData, 0xFF, sizeof(EventList[EV_PDS_6].EventData));
	EventList[EV_PDS_6].AddtionalInfo					= NULL;

	EventList[EV_PDS_6].TimeRequired					= 0;
	EventList[EV_PDS_6].ACKRequired 					= false;

	// ---- Index - EV_PDS_7 - ID ----
	EventList[EV_PDS_7].EventCategory 					= Type_PDS;
	EventList[EV_PDS_7].EventID 						= 156;

	EventList[EV_PDS_7].EventActive 					= false;

	sprintf(EventList[EV_PDS_7].EventName, "Proximity Detection 05");

	EventList[EV_PDS_7].TimeStampSystic					= 0;

	EventList[EV_PDS_7].EventAction1					= Act_None;
	EventList[EV_PDS_7].EventAction2 					= Act_None;
	EventList[EV_PDS_7].EventAction3 					= Act_None;
	EventList[EV_PDS_7].EventActionTime1_2 				= 0;
	EventList[EV_PDS_7].EventActionTime2_3 				= 0;

	EventList[EV_PDS_7].Processed						= false;
	EventList[EV_PDS_7].EventLogged						= false;

	EventList[EV_PDS_7].DispType 						= Disp_Dedicated_FullScreen;
	//EventList[EV_PDS_7].ImageName 						= Icon_LowSpeed;
	EventList[EV_PDS_7].SplashTime 						= 0;
	EventList[EV_PDS_7].SplashActive					= false;

	EventList[EV_PDS_7].BuzzerRequired 					= false;
	//EventList[EV_PDS_7].BuzzerMode 						= Buzz_Fast;

	memset(EventList[EV_PDS_7].EventData, 0xFF, sizeof(EventList[EV_PDS_7].EventData));
	EventList[EV_PDS_7].AddtionalInfo					= NULL;

	EventList[EV_PDS_7].TimeRequired 					= 0;
	EventList[EV_PDS_7].ACKRequired 					= false;

	// ---- Index - EV_PDS_1_End - ID ----
	EventList[EV_PDS_1_End].EventCategory 				= Type_PDS;
	EventList[EV_PDS_1_End].EventID 					= 157;

	EventList[EV_PDS_1_End].EventActive 				= false;

	sprintf(EventList[EV_PDS_1_End].EventName, "Proximity Detection 01 E");

	EventList[EV_PDS_1_End].TimeStampSystic				= 0;

	EventList[EV_PDS_1_End].EventAction1				= Act_None;
	EventList[EV_PDS_1_End].EventAction2 				= Act_None;
	EventList[EV_PDS_1_End].EventAction3 				= Act_None;
	EventList[EV_PDS_1_End].EventActionTime1_2 			= 0;
	EventList[EV_PDS_1_End].EventActionTime2_3 			= 0;

	EventList[EV_PDS_1_End].Processed					= false;
	EventList[EV_PDS_1_End].EventLogged					= false;

	EventList[EV_PDS_1_End].DispType 					= Disp_None;
	//EventList[EV_PDS_1_End].ImageName 					= Icon_LowSpeed;
	EventList[EV_PDS_1_End].SplashTime 					= 0;
	EventList[EV_PDS_1_End].SplashActive				= false;

	EventList[EV_PDS_1_End].BuzzerRequired 				= false;
	//EventList[EV_PDS_1_End].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_PDS_1_End].EventData, 0xFF, sizeof(EventList[EV_PDS_1_End].EventData));
	EventList[EV_PDS_1_End].AddtionalInfo					= NULL;

	EventList[EV_PDS_1_End].TimeRequired = 0;
	EventList[EV_PDS_1_End].ACKRequired = false;

	// ---- Index - EV_PDS_2_End - ID ----
	EventList[EV_PDS_2_End].EventCategory 				= Type_PDS;
	EventList[EV_PDS_2_End].EventID 					= 158;

	EventList[EV_PDS_2_End].EventActive 				= false;

	sprintf(EventList[EV_PDS_2_End].EventName, "Proximity Detection 02 E");

	EventList[EV_PDS_2_End].TimeStampSystic 			= 0;

	EventList[EV_PDS_2_End].EventAction1 				= Act_None;
	EventList[EV_PDS_2_End].EventAction2 				= Act_None;
	EventList[EV_PDS_2_End].EventAction3 				= Act_None;
	EventList[EV_PDS_2_End].EventActionTime1_2 			= 0;
	EventList[EV_PDS_2_End].EventActionTime2_3 			= 0;

	EventList[EV_PDS_2_End].Processed					= false;
	EventList[EV_PDS_2_End].EventLogged					= false;

	EventList[EV_PDS_2_End].DispType 					= Disp_None;
	//EventList[EV_PDS_2_End].ImageName 					= Icon_LowSpeed;
	EventList[EV_PDS_2_End].SplashTime 					= 0;
	EventList[EV_PDS_2_End].SplashActive				= false;

	EventList[EV_PDS_2_End].BuzzerRequired 				= false;
	//EventList[EV_PDS_2_End].BuzzerMode 					= Buzz_Fast;

	memset(EventList[EV_PDS_2_End].EventData, 0xFF, sizeof(EventList[EV_PDS_2_End].EventData));
	EventList[EV_PDS_2_End].AddtionalInfo				= NULL;

	EventList[EV_PDS_2_End].TimeRequired = 0;
	EventList[EV_PDS_2_End].ACKRequired = false;

	// ---- Index - EV_PDS_3 - ID ----
	EventList[EV_PDS_3_End].EventCategory 				= Type_PDS;
	EventList[EV_PDS_3_End].EventID 					= 159;

	EventList[EV_PDS_3_End].EventActive 				= false;

	sprintf(EventList[EV_PDS_3_End].EventName, "Proximity Detection 03 E");

	EventList[EV_PDS_3_End].TimeStampSystic 			= 0;

	EventList[EV_PDS_3_End].EventAction1 				= Act_None;
	EventList[EV_PDS_3_End].EventAction2 				= Act_None;
	EventList[EV_PDS_3_End].EventAction3 				= Act_None;
	EventList[EV_PDS_3_End].EventActionTime1_2 			= 0;
	EventList[EV_PDS_3_End].EventActionTime2_3 			= 0;

	EventList[EV_PDS_3_End].Processed					= false;
	EventList[EV_PDS_3_End].EventLogged					= false;

	EventList[EV_PDS_3_End].DispType 					= Disp_None;
	//EventList[EV_PDS_3_End].ImageName 					= Icon_LowSpeed;
	EventList[EV_PDS_3_End].SplashTime 					= 0;
	EventList[EV_PDS_3_End].SplashActive				= false;

	EventList[EV_PDS_3_End].BuzzerRequired				= false;
	//EventList[EV_PDS_3_End].BuzzerMode 					= Buzz_Fast;

	memset(EventList[EV_PDS_3_End].EventData, 0xFF, sizeof(EventList[EV_PDS_3_End].EventData));
	EventList[EV_PDS_3_End].AddtionalInfo				= NULL;

	EventList[EV_PDS_3_End].TimeRequired = 0;
	EventList[EV_PDS_3_End].ACKRequired = false;

	// ---- Index - EV_PDS_4_End - ID ----
	EventList[EV_PDS_4_End].EventCategory 				= Type_PDS;
	EventList[EV_PDS_4_End].EventID 					= 160;

	EventList[EV_PDS_4_End].EventActive 				= false;

	sprintf(EventList[EV_PDS_4_End].EventName, "Proximity Detection 04 E");

	EventList[EV_PDS_4_End].TimeStampSystic 			= 0;

	EventList[EV_PDS_4_End].EventAction1 				= Act_None;
	EventList[EV_PDS_4_End].EventAction2 				= Act_None;
	EventList[EV_PDS_4_End].EventAction3 				= Act_None;
	EventList[EV_PDS_4_End].EventActionTime1_2 			= 0;
	EventList[EV_PDS_4_End].EventActionTime2_3 			= 0;

	EventList[EV_PDS_4_End].Processed					= false;
	EventList[EV_PDS_4_End].EventLogged					= false;

	EventList[EV_PDS_4_End].DispType 					= Disp_None;
	//EventList[EV_PDS_4_End].ImageName 					= Icon_LowSpeed;
	EventList[EV_PDS_4_End].SplashTime 					= 0;
	EventList[EV_PDS_4_End].SplashActive				= false;

	EventList[EV_PDS_4_End].BuzzerRequired 				= false;
	//EventList[EV_PDS_4_End].BuzzerMode 					= Buzz_Fast;

	memset(EventList[EV_PDS_4_End].EventData, 0xFF, sizeof(EventList[EV_PDS_4_End].EventData));
	EventList[EV_PDS_4_End].AddtionalInfo				= NULL;

	EventList[EV_PDS_4_End].TimeRequired = 0;
	EventList[EV_PDS_4_End].ACKRequired = false;

	// ---- Index - EV_PDS_5_End - ID ----
	EventList[EV_PDS_5_End].EventCategory 				= Type_PDS;
	EventList[EV_PDS_5_End].EventID 					= 161;

	EventList[EV_PDS_5_End].EventActive 				= false;

	sprintf(EventList[EV_PDS_5_End].EventName, "Proximity Detection 05 E");

	EventList[EV_PDS_5_End].TimeStampSystic 			= 0;

	EventList[EV_PDS_5_End].EventAction1				= Act_None;
	EventList[EV_PDS_5_End].EventAction2 				= Act_None;
	EventList[EV_PDS_5_End].EventAction3 				= Act_None;
	EventList[EV_PDS_5_End].EventActionTime1_2 			= 0;
	EventList[EV_PDS_5_End].EventActionTime2_3 			= 0;

	EventList[EV_PDS_5_End].Processed					= false;
	EventList[EV_PDS_5_End].EventLogged					= false;

	EventList[EV_PDS_5_End].DispType 					= Disp_None;
	//EventList[EV_PDS_5_End].ImageName 					= Icon_LowSpeed;
	EventList[EV_PDS_5_End].SplashTime 					= 0;
	EventList[EV_PDS_5_End].SplashActive				= false;

	EventList[EV_PDS_5_End].BuzzerRequired 				= false;
	//EventList[EV_PDS_5_End].BuzzerMode 					= Buzz_Fast;

	memset(EventList[EV_PDS_5_End].EventData, 0xFF, sizeof(EventList[EV_PDS_5_End].EventData));
	EventList[EV_PDS_5_End].AddtionalInfo				= NULL;

	EventList[EV_PDS_5_End].TimeRequired = 0;
	EventList[EV_PDS_5_End].ACKRequired = false;

	// ---- Index - EV_PDS_6_End - ID ----
	EventList[EV_PDS_6_End].EventCategory 				= Type_PDS;
	EventList[EV_PDS_6_End].EventID 					= 162;

	EventList[EV_PDS_6_End].EventActive 				= false;

	sprintf(EventList[EV_PDS_6_End].EventName, "Proximity Detection 06 E");

	EventList[EV_PDS_7_End].TimeStampSystic 			= 0;

	EventList[EV_PDS_6_End].EventAction1				= Act_None;
	EventList[EV_PDS_6_End].EventAction2 				= Act_None;
	EventList[EV_PDS_6_End].EventAction3 				= Act_None;
	EventList[EV_PDS_6_End].EventActionTime1_2 			= 0;
	EventList[EV_PDS_6_End].EventActionTime2_3 			= 0;

	EventList[EV_PDS_6_End].Processed					= false;
	EventList[EV_PDS_6_End].EventLogged					= false;

	EventList[EV_PDS_6_End].DispType 					= Disp_None;
	//EventList[EV_PDS_6_End].ImageName 					= Icon_LowSpeed;
	EventList[EV_PDS_6_End].SplashTime 					= 0;
	EventList[EV_PDS_6_End].SplashActive				= false;

	EventList[EV_PDS_6_End].BuzzerRequired 				= false;
	//EventList[EV_PDS_6_End].BuzzerMode 					= Buzz_Fast;

	memset(EventList[EV_PDS_6_End].EventData, 0xFF, sizeof(EventList[EV_PDS_6_End].EventData));
	EventList[EV_PDS_6_End].AddtionalInfo				= NULL;

	EventList[EV_PDS_6_End].TimeRequired = 0;
	EventList[EV_PDS_6_End].ACKRequired = false;

	// ---- Index - EV_PDS_7_End - ID ----
	EventList[EV_PDS_7_End].EventCategory 				= Type_PDS;
	EventList[EV_PDS_7_End].EventID 					= 163;

	EventList[EV_PDS_7_End].EventActive 				= false;

	sprintf(EventList[EV_PDS_7_End].EventName, "Proximity Detection 07 E");

	EventList[EV_PDS_7_End].TimeStampSystic 			= 0;

	EventList[EV_PDS_7_End].EventAction1				= Act_None;
	EventList[EV_PDS_7_End].EventAction2 				= Act_None;
	EventList[EV_PDS_7_End].EventAction3 				= Act_None;
	EventList[EV_PDS_7_End].EventActionTime1_2 			= 0;
	EventList[EV_PDS_7_End].EventActionTime2_3 			= 0;

	EventList[EV_PDS_7_End].Processed					= false;
	EventList[EV_PDS_7_End].EventLogged					= false;

	EventList[EV_PDS_7_End].DispType 					= Disp_None;
	//EventList[EV_PDS_7_End].ImageName 					= Icon_LowSpeed;
	EventList[EV_PDS_7_End].SplashTime 					= 0;
	EventList[EV_PDS_7_End].SplashActive				= false;

	EventList[EV_PDS_7_End].BuzzerRequired 				= false;
	//EventList[EV_PDS_7_End].BuzzerMode 					= Buzz_Fast;

	memset(EventList[EV_PDS_7_End].EventData, 0xFF, sizeof(EventList[EV_PDS_7_End].EventData));
	EventList[EV_PDS_7_End].AddtionalInfo				= NULL;

	EventList[EV_PDS_7_End].TimeRequired = 0;
	EventList[EV_PDS_7_End].ACKRequired = false;

	/*-------------------------------------------------------------------------------------------------------
	 * 										  Vehicle Events
	 *-------------------------------------------------------------------------------------------------------*/
	// ---- Index - EV_J1939_Failure - ID ----
	EventList[EV_J1939_Failure].EventCategory 			= Type_Vehicle;
	EventList[EV_J1939_Failure].EventID 				= 170;

	EventList[EV_J1939_Failure].EventActive 			= false;

	sprintf(EventList[EV_J1939_Failure].EventName, "J1939 Failure");

	EventList[EV_J1939_Failure].TimeStampSystic 		= 0;

	EventList[EV_J1939_Failure].EventAction1			= Act_None;
	EventList[EV_J1939_Failure].EventAction2 			= Act_None;
	EventList[EV_J1939_Failure].EventAction3 			= Act_None;
	EventList[EV_J1939_Failure].EventActionTime1_2 		= 0;
	EventList[EV_J1939_Failure].EventActionTime2_3 		= 0;

	EventList[EV_J1939_Failure].Processed 				= false;
	EventList[EV_J1939_Failure].EventLogged				= false;

	//EventList[EV_J1939_Failure].ImageName 				= Icon_Attention;
	EventList[EV_J1939_Failure].DispType 				= Disp_Icon;
	EventList[EV_J1939_Failure].SplashTime 				= 0;
	EventList[EV_J1939_Failure].SplashActive			= false;

	EventList[EV_J1939_Failure].BuzzerRequired 			= false;
	//EventList[EV_J1939_Failure].BuzzerMode 				= Buzz_Once;

	memset(EventList[EV_J1939_Failure].EventData, 0xFF, sizeof(EventList[EV_J1939_Failure].EventData));
	EventList[EV_J1939_Failure].AddtionalInfo			= NULL;

	EventList[EV_J1939_Failure].TimeRequired = 0;
	EventList[EV_J1939_Failure].ACKRequired = false;

	// ---- Index - EV_J1939_OK - ID ----
	EventList[EV_J1939_OK].EventCategory 				= Type_Vehicle;
	EventList[EV_J1939_OK].EventID 						= 171;

	EventList[EV_J1939_OK].EventActive		 			= false;

	sprintf(EventList[EV_J1939_OK].EventName, "J1939 OK");

	EventList[EV_J1939_OK].TimeStampSystic 				= 0;

	EventList[EV_J1939_OK].EventAction1					= Act_None;
	EventList[EV_J1939_OK].EventAction2 				= Act_None;
	EventList[EV_J1939_OK].EventAction3 				= Act_None;
	EventList[EV_J1939_OK].EventActionTime1_2 			= 0;
	EventList[EV_J1939_OK].EventActionTime2_3 			= 0;

	EventList[EV_J1939_OK].Processed 					= false;
	EventList[EV_J1939_OK].EventLogged					= false;

	EventList[EV_J1939_OK].DispType 					= Disp_Icon;
	//EventList[EV_J1939_OK].ImageName 					= Icon_Attention;
	EventList[EV_J1939_OK].SplashTime 					= 0;
	EventList[EV_J1939_OK].SplashActive					= false;

	EventList[EV_J1939_OK].BuzzerRequired 				= false;
	//EventList[EV_J1939_OK].BuzzerMode 					= Buzz_Once;

	memset(EventList[EV_J1939_OK].EventData, 0xFF, sizeof(EventList[EV_J1939_OK].EventData));
	EventList[EV_J1939_OK].AddtionalInfo				= NULL;

	EventList[EV_J1939_OK].TimeRequired = 0;
	EventList[EV_J1939_OK].ACKRequired = false;

	// ---- Index - EV_J1939_Coolant_TempHigh - ID ----
	EventList[EV_J1939_Coolant_TempHigh].EventCategory 	= Type_Vehicle;
	EventList[EV_J1939_Coolant_TempHigh].EventID 		= 172;

	EventList[EV_J1939_Coolant_TempHigh].EventActive 	= false;

	sprintf(EventList[EV_J1939_Coolant_TempHigh].EventName, "Coolant Temp High");

	EventList[EV_J1939_Coolant_TempHigh].TimeStampSystic = 0;

	EventList[EV_J1939_Coolant_TempHigh].EventAction1	= Act_None;
	EventList[EV_J1939_Coolant_TempHigh].EventAction2 	= Act_None;
	EventList[EV_J1939_Coolant_TempHigh].EventAction3 	= Act_None;
	EventList[EV_J1939_Coolant_TempHigh].EventActionTime1_2 = 0;
	EventList[EV_J1939_Coolant_TempHigh].EventActionTime2_3 = 0;

	EventList[EV_J1939_Coolant_TempHigh].Processed 		= false;
	EventList[EV_J1939_Coolant_TempHigh].EventLogged	= false;

	EventList[EV_J1939_Coolant_TempHigh].DispType 		= Disp_Icon;
	//EventList[EV_J1939_Coolant_TempHigh].ImageName 		= Icon_Attention;
	EventList[EV_J1939_Coolant_TempHigh].SplashTime 	= 0;
	EventList[EV_J1939_Coolant_TempHigh].SplashActive	= false;

	EventList[EV_J1939_Coolant_TempHigh].BuzzerRequired = false;
	//EventList[EV_J1939_Coolant_TempHigh].BuzzerMode 	= Buzz_Once;

	memset(EventList[EV_J1939_Coolant_TempHigh].EventData, 0xFF, sizeof(EventList[EV_J1939_Coolant_TempHigh].EventData));
	EventList[EV_J1939_Coolant_TempHigh].AddtionalInfo	= NULL;

	EventList[EV_J1939_Coolant_TempHigh].TimeRequired = 0;
	EventList[EV_J1939_Coolant_TempHigh].ACKRequired = false;

	// ---- Index - EV_J1939_Coolant_TempOK - ID ----
	EventList[EV_J1939_Coolant_TempOK].EventCategory 	= Type_Vehicle;
	EventList[EV_J1939_Coolant_TempOK].EventID 			= 173;

	EventList[EV_J1939_Coolant_TempOK].EventActive 	= false;

	sprintf(EventList[EV_J1939_Coolant_TempOK].EventName, "Coolant Temp OK");

	EventList[EV_J1939_Coolant_TempOK].TimeStampSystic = 0;

	EventList[EV_J1939_Coolant_TempOK].EventAction1		= Act_None;
	EventList[EV_J1939_Coolant_TempOK].EventAction2 	= Act_None;
	EventList[EV_J1939_Coolant_TempOK].EventAction3 	= Act_None;
	EventList[EV_J1939_Coolant_TempOK].EventActionTime1_2 = 0;
	EventList[EV_J1939_Coolant_TempOK].EventActionTime2_3 = 0;

	EventList[EV_J1939_Coolant_TempOK].Processed 		= false;
	EventList[EV_J1939_Coolant_TempOK].EventLogged		= false;

	EventList[EV_J1939_Coolant_TempOK].DispType 		= Disp_Icon;
	//EventList[EV_J1939_Coolant_TempOK].ImageName 		= Icon_Attention;
	EventList[EV_J1939_Coolant_TempOK].SplashTime 		= 0;
	EventList[EV_J1939_Coolant_TempOK].SplashActive		= false;

	EventList[EV_J1939_Coolant_TempOK].BuzzerRequired 	= false;
	//EventList[EV_J1939_Coolant_TempOK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_J1939_Coolant_TempOK].EventData, 0xFF, sizeof(EventList[EV_J1939_Coolant_TempOK].EventData));
	EventList[EV_J1939_Coolant_TempOK].AddtionalInfo	= NULL;

	EventList[EV_J1939_Coolant_TempOK].TimeRequired = 0;
	EventList[EV_J1939_Coolant_TempOK].ACKRequired = false;

	// ---- Index - EV_J1939_Coolant_PresHigh - ID ----
	EventList[EV_J1939_Coolant_PresHigh].EventCategory 	= Type_Vehicle;
	EventList[EV_J1939_Coolant_PresHigh].EventID 		= 174;

	EventList[EV_J1939_Coolant_PresHigh].EventActive 	= false;

	sprintf(EventList[EV_J1939_Coolant_PresHigh].EventName, "Coolant Pres High");

	EventList[EV_J1939_Coolant_PresHigh].TimeStampSystic = 0;

	EventList[EV_J1939_Coolant_PresHigh].EventAction1	= Act_None;
	EventList[EV_J1939_Coolant_PresHigh].EventAction2 	= Act_None;
	EventList[EV_J1939_Coolant_PresHigh].EventAction3 	= Act_None;
	EventList[EV_J1939_Coolant_PresHigh].EventActionTime1_2 = 0;
	EventList[EV_J1939_Coolant_PresHigh].EventActionTime2_3 = 0;

	EventList[EV_J1939_Coolant_PresHigh].Processed 		= false;
	EventList[EV_J1939_Coolant_PresHigh].EventLogged	= false;

	EventList[EV_J1939_Coolant_PresHigh].DispType 		= Disp_Icon;
	//EventList[EV_J1939_Coolant_PresHigh].ImageName 		= Icon_Attention;
	EventList[EV_J1939_Coolant_PresHigh].SplashTime 	= 0;
	EventList[EV_J1939_Coolant_PresHigh].SplashActive	= false;

	EventList[EV_J1939_Coolant_PresHigh].BuzzerRequired = false;
	//EventList[EV_J1939_Coolant_PresHigh].BuzzerMode 	= Buzz_Once;

	memset(EventList[EV_J1939_Coolant_PresHigh].EventData, 0xFF, sizeof(EventList[EV_J1939_Coolant_PresHigh].EventData));
	EventList[EV_J1939_Coolant_PresHigh].AddtionalInfo	= NULL;

	EventList[EV_J1939_Coolant_PresHigh].TimeRequired = 0;
	EventList[EV_J1939_Coolant_PresHigh].ACKRequired = false;

	// ---- Index - EV_J1939_Coolant_PresOK - ID ----
	EventList[EV_J1939_Coolant_PresOK].EventCategory 	= Type_Vehicle;
	EventList[EV_J1939_Coolant_PresOK].EventID 			= 175;

	EventList[EV_J1939_Coolant_PresOK].EventActive 	= false;

	sprintf(EventList[EV_J1939_Coolant_PresOK].EventName, "Coolant Pres OK");

	EventList[EV_J1939_Coolant_PresOK].TimeStampSystic = 0;

	EventList[EV_J1939_Coolant_PresOK].EventAction1		= Act_None;
	EventList[EV_J1939_Coolant_PresOK].EventAction2 	= Act_None;
	EventList[EV_J1939_Coolant_PresOK].EventAction3 	= Act_None;
	EventList[EV_J1939_Coolant_PresOK].EventActionTime1_2 = 0;
	EventList[EV_J1939_Coolant_PresOK].EventActionTime2_3 = 0;

	EventList[EV_J1939_Coolant_PresOK].Processed 		= false;
	EventList[EV_J1939_Coolant_PresOK].EventLogged		= false;

	EventList[EV_J1939_Coolant_PresOK].DispType 		= Disp_Icon;
	//EventList[EV_J1939_Coolant_PresOK].ImageName 		= Icon_Attention;
	EventList[EV_J1939_Coolant_PresOK].SplashTime 		= 0;
	EventList[EV_J1939_Coolant_PresOK].SplashActive		= false;

	EventList[EV_J1939_Coolant_PresOK].BuzzerRequired 	= false;
	//EventList[EV_J1939_Coolant_PresOK].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_J1939_Coolant_PresOK].EventData, 0xFF, sizeof(EventList[EV_J1939_Coolant_PresOK].EventData));
	EventList[EV_J1939_Coolant_PresOK].AddtionalInfo	= NULL;

	EventList[EV_J1939_Coolant_PresOK].TimeRequired = 0;
	EventList[EV_J1939_Coolant_PresOK].ACKRequired = false;

	// ---- Index - EV_J1939_Oil_TempHigh - ID ----
	EventList[EV_J1939_Oil_TempHigh].EventCategory 		= Type_Vehicle;
	EventList[EV_J1939_Oil_TempHigh].EventID 			= 174;

	EventList[EV_J1939_Oil_TempHigh].EventActive 		= false;

	sprintf(EventList[EV_J1939_Oil_TempHigh].EventName, "Coolant Pres High");

	EventList[EV_J1939_Oil_TempHigh].TimeStampSystic 	= 0;

	EventList[EV_J1939_Oil_TempHigh].EventAction1		= Act_None;
	EventList[EV_J1939_Oil_TempHigh].EventAction2 		= Act_None;
	EventList[EV_J1939_Oil_TempHigh].EventAction3 		= Act_None;
	EventList[EV_J1939_Oil_TempHigh].EventActionTime1_2 = 0;
	EventList[EV_J1939_Oil_TempHigh].EventActionTime2_3 = 0;

	EventList[EV_J1939_Oil_TempHigh].Processed 			= false;
	EventList[EV_J1939_Oil_TempHigh].EventLogged		= false;

	EventList[EV_J1939_Oil_TempHigh].DispType 			= Disp_Icon;
	//EventList[EV_J1939_Oil_TempHigh].ImageName 			= Icon_Attention;
	EventList[EV_J1939_Oil_TempHigh].SplashTime 		= 0;
	EventList[EV_J1939_Oil_TempHigh].SplashActive		= false;

	EventList[EV_J1939_Oil_TempHigh].BuzzerRequired 	= false;
	//EventList[EV_J1939_Oil_TempHigh].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_J1939_Oil_TempHigh].EventData, 0xFF, sizeof(EventList[EV_J1939_Oil_TempHigh].EventData));
	EventList[EV_J1939_Oil_TempHigh].AddtionalInfo		= NULL;

	EventList[EV_J1939_Oil_TempHigh].TimeRequired = 0;
	EventList[EV_J1939_Oil_TempHigh].ACKRequired = false;

	// ---- Index - EV_J1939_Oil_TempOK - ID ----
	EventList[EV_J1939_Oil_TempOK].EventCategory 		= Type_Vehicle;
	EventList[EV_J1939_Oil_TempOK].EventID 				= 175;

	EventList[EV_J1939_Oil_TempOK].EventActive 			= false;

	sprintf(EventList[EV_J1939_Oil_TempOK].EventName, "Coolant Pres OK");

	EventList[EV_J1939_Oil_TempOK].TimeStampSystic 		= 0;

	EventList[EV_J1939_Oil_TempOK].EventAction1			= Act_None;
	EventList[EV_J1939_Oil_TempOK].EventAction2 		= Act_None;
	EventList[EV_J1939_Oil_TempOK].EventAction3 		= Act_None;
	EventList[EV_J1939_Oil_TempOK].EventActionTime1_2 	= 0;
	EventList[EV_J1939_Oil_TempOK].EventActionTime2_3 	= 0;

	EventList[EV_J1939_Oil_TempOK].Processed 			= false;
	EventList[EV_J1939_Oil_TempOK].EventLogged			= false;

	EventList[EV_J1939_Oil_TempOK].DispType 			= Disp_Icon;
	//EventList[EV_J1939_Oil_TempOK].ImageName 			= Icon_Attention;
	EventList[EV_J1939_Oil_TempOK].SplashTime 			= 0;
	EventList[EV_J1939_Oil_TempOK].SplashActive			= false;

	EventList[EV_J1939_Oil_TempOK].BuzzerRequired 		= false;
	//EventList[EV_J1939_Oil_TempOK].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_J1939_Oil_TempOK].EventData, 0xFF, sizeof(EventList[EV_J1939_Oil_TempOK].EventData));
	EventList[EV_J1939_Oil_TempOK].AddtionalInfo		= NULL;

	EventList[EV_J1939_Oil_TempOK].TimeRequired = 0;
	EventList[EV_J1939_Oil_TempOK].ACKRequired = false;

	// ---- Index - EV_J1939_Oil_TempHigh - ID ----
	EventList[EV_J1939_Oil_TempHigh].EventCategory 		= Type_Vehicle;
	EventList[EV_J1939_Oil_TempHigh].EventID 			= 176;

	EventList[EV_J1939_Oil_TempHigh].EventActive 		= false;

	sprintf(EventList[EV_J1939_Oil_TempHigh].EventName, "Oil Temp High");

	EventList[EV_J1939_Oil_TempHigh].TimeStampSystic 	= 0;

	EventList[EV_J1939_Oil_TempHigh].EventAction1		= Act_None;
	EventList[EV_J1939_Oil_TempHigh].EventAction2 		= Act_None;
	EventList[EV_J1939_Oil_TempHigh].EventAction3 		= Act_None;
	EventList[EV_J1939_Oil_TempHigh].EventActionTime1_2 = 0;
	EventList[EV_J1939_Oil_TempHigh].EventActionTime2_3 = 0;

	EventList[EV_J1939_Oil_TempHigh].Processed 			= false;
	EventList[EV_J1939_Oil_TempHigh].EventLogged		= false;

	EventList[EV_J1939_Oil_TempHigh].DispType 			= Disp_Icon;
	//EventList[EV_J1939_Oil_TempHigh].ImageName 			= Icon_Attention;
	EventList[EV_J1939_Oil_TempHigh].SplashTime 		= 0;
	EventList[EV_J1939_Oil_TempHigh].SplashActive		= false;

	EventList[EV_J1939_Oil_TempHigh].BuzzerRequired 	= false;
	//EventList[EV_J1939_Oil_TempHigh].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_J1939_Oil_TempHigh].EventData, 0xFF, sizeof(EventList[EV_J1939_Oil_TempHigh].EventData));
	EventList[EV_J1939_Oil_TempHigh].AddtionalInfo		= NULL;

	EventList[EV_J1939_Oil_TempHigh].TimeRequired = 0;
	EventList[EV_J1939_Oil_TempHigh].ACKRequired = false;

	// ---- Index - EV_J1939_Oil_TempOK - ID ----
	EventList[EV_J1939_Oil_TempOK].EventCategory 		= Type_Vehicle;
	EventList[EV_J1939_Oil_TempOK].EventID 				= 177;

	EventList[EV_J1939_Oil_TempOK].EventActive 			= false;

	sprintf(EventList[EV_J1939_Oil_TempOK].EventName, "Oil Temp OK");

	EventList[EV_J1939_Oil_TempOK].TimeStampSystic 		= 0;

	EventList[EV_J1939_Oil_TempOK].EventAction1			= Act_None;
	EventList[EV_J1939_Oil_TempOK].EventAction2 		= Act_None;
	EventList[EV_J1939_Oil_TempOK].EventAction3 		= Act_None;
	EventList[EV_J1939_Oil_TempOK].EventActionTime1_2 	= 0;
	EventList[EV_J1939_Oil_TempOK].EventActionTime2_3 	= 0;

	EventList[EV_J1939_Oil_TempOK].Processed 			= false;
	EventList[EV_J1939_Oil_TempOK].EventLogged			= false;

	EventList[EV_J1939_Oil_TempOK].DispType 			= Disp_Icon;
	//EventList[EV_J1939_Oil_TempOK].ImageName 			= Icon_Attention;
	EventList[EV_J1939_Oil_TempOK].SplashTime 			= 0;
	EventList[EV_J1939_Oil_TempOK].SplashActive			= false;

	EventList[EV_J1939_Oil_TempOK].BuzzerRequired 		= false;
	//EventList[EV_J1939_Oil_TempOK].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_J1939_Oil_TempOK].EventData, 0xFF, sizeof(EventList[EV_J1939_Oil_TempOK].EventData));
	EventList[EV_J1939_Oil_TempOK].AddtionalInfo		= NULL;

	EventList[EV_J1939_Oil_TempOK].TimeRequired = 0;
	EventList[EV_J1939_Oil_TempOK].ACKRequired = false;

	// ---- Index - EV_J1939_Oil_PresHigh - ID ----
	EventList[EV_J1939_Oil_PresHigh].EventCategory 		= Type_Vehicle;
	EventList[EV_J1939_Oil_PresHigh].EventID 			= 178;

	EventList[EV_J1939_Oil_PresHigh].EventActive 		= false;

	sprintf(EventList[EV_J1939_Oil_PresHigh].EventName, "Oil Pres High");

	EventList[EV_J1939_Oil_PresHigh].TimeStampSystic 	= 0;

	EventList[EV_J1939_Oil_PresHigh].EventAction1		= Act_None;
	EventList[EV_J1939_Oil_PresHigh].EventAction2 		= Act_None;
	EventList[EV_J1939_Oil_PresHigh].EventAction3 		= Act_None;
	EventList[EV_J1939_Oil_PresHigh].EventActionTime1_2 = 0;
	EventList[EV_J1939_Oil_PresHigh].EventActionTime2_3 = 0;

	EventList[EV_J1939_Oil_PresHigh].Processed 			= false;
	EventList[EV_J1939_Oil_PresHigh].EventLogged		= false;

	EventList[EV_J1939_Oil_PresHigh].DispType 			= Disp_Icon;
	//EventList[EV_J1939_Oil_PresHigh].ImageName 			= Icon_Attention;
	EventList[EV_J1939_Oil_PresHigh].SplashTime 		= 0;
	EventList[EV_J1939_Oil_PresHigh].SplashActive		= false;

	EventList[EV_J1939_Oil_PresHigh].BuzzerRequired 	= false;
	//EventList[EV_J1939_Oil_PresHigh].BuzzerMode 		= Buzz_Once;

	memset(EventList[EV_J1939_Oil_PresHigh].EventData, 0xFF, sizeof(EventList[EV_J1939_Oil_PresHigh].EventData));
	EventList[EV_J1939_Oil_PresHigh].AddtionalInfo		= NULL;

	EventList[EV_J1939_Oil_PresHigh].TimeRequired = 0;
	EventList[EV_J1939_Oil_PresHigh].ACKRequired = false;

	// ---- Index - EV_J1939_Oil_PresOK - ID ----
	EventList[EV_J1939_Oil_PresOK].EventCategory 		= Type_Vehicle;
	EventList[EV_J1939_Oil_PresOK].EventID 				= 179;

	EventList[EV_J1939_Oil_PresOK].EventActive 			= false;

	sprintf(EventList[EV_J1939_Oil_PresOK].EventName, "Oil Pres OK");

	EventList[EV_J1939_Oil_PresOK].TimeStampSystic 		= 0;

	EventList[EV_J1939_Oil_PresOK].EventAction1			= Act_None;
	EventList[EV_J1939_Oil_PresOK].EventAction2 		= Act_None;
	EventList[EV_J1939_Oil_PresOK].EventAction3 		= Act_None;
	EventList[EV_J1939_Oil_PresOK].EventActionTime1_2 	= 0;
	EventList[EV_J1939_Oil_PresOK].EventActionTime2_3 	= 0;

	EventList[EV_J1939_Oil_PresOK].Processed 			= false;
	EventList[EV_J1939_Oil_PresOK].EventLogged			= false;

	EventList[EV_J1939_Oil_PresOK].DispType 			= Disp_Icon;
	//EventList[EV_J1939_Oil_PresOK].ImageName 			= Icon_Attention;
	EventList[EV_J1939_Oil_PresOK].SplashTime 			= 0;
	EventList[EV_J1939_Oil_PresOK].SplashActive			= false;

	EventList[EV_J1939_Oil_PresOK].BuzzerRequired 		= false;
	//EventList[EV_J1939_Oil_PresOK].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_J1939_Oil_PresOK].EventData, 0xFF, sizeof(EventList[EV_J1939_Oil_PresOK].EventData));
	EventList[EV_J1939_Oil_PresOK].AddtionalInfo		= NULL;

	EventList[EV_J1939_Oil_PresOK].TimeRequired = 0;
	EventList[EV_J1939_Oil_PresOK].ACKRequired = false;

	/*J1939 Fuel Error*/
	sprintf(EventList[EV_J1939_Fuel_Error].EventName, "Fuel Error");
	EventList[EV_J1939_Fuel_Error].EventID = 444;
	EventList[EV_J1939_Fuel_Error].EventActive = false;

	EventList[EV_J1939_Fuel_Error].TimeRequired = 0;
	EventList[EV_J1939_Fuel_Error].ACKRequired = false;
	EventList[EV_J1939_Fuel_Error].EventCategory = Type_System;
	EventList[EV_J1939_Fuel_Error].Processed = false;

	//EventList[EV_J1939_Fuel_Error].ImageName = Icon_Attention;
	EventList[EV_J1939_Fuel_Error].DispType = Disp_Icon;

	EventList[EV_J1939_Fuel_Error].BuzzerRequired = true;
	//EventList[EV_J1939_Fuel_Error].BuzzerMode = Buzz_Fast;

	/*J1939 Revs Error*/
	sprintf(EventList[EV_J1939_Rev_Error].EventName, "Revolutions Error");
	EventList[EV_J1939_Rev_Error].EventID = 445;
	EventList[EV_J1939_Rev_Error].EventActive = false;

	EventList[EV_J1939_Rev_Error].TimeRequired = 0;
	EventList[EV_J1939_Rev_Error].ACKRequired = false;
	EventList[EV_J1939_Rev_Error].EventCategory = Type_System;
	EventList[EV_J1939_Rev_Error].Processed = false;

	//EventList[EV_J1939_Rev_Error].ImageName = Icon_Attention;
	EventList[EV_J1939_Rev_Error].DispType = Disp_Icon;

	EventList[EV_J1939_Rev_Error].BuzzerRequired = true;
	//EventList[EV_J1939_Rev_Error].BuzzerMode = Buzz_Fast;

	// ---- Index - EV_Confirm_Emergency_Stop - ID ----
	EventList[EV_Confirm_Emergency_Stop].EventCategory 	= Type_Vehicle;
	EventList[EV_Confirm_Emergency_Stop].EventID 		= 194;

	EventList[EV_Confirm_Emergency_Stop].EventActive 	= false;

	sprintf(EventList[EV_Confirm_Emergency_Stop].EventName, "Emergency Stop Message");

	EventList[EV_Confirm_Emergency_Stop].TimeStampSystic = 0;

	EventList[EV_Confirm_Emergency_Stop].EventAction1	= Act_None;
	EventList[EV_Confirm_Emergency_Stop].EventAction2 	= Act_None;
	EventList[EV_Confirm_Emergency_Stop].EventAction3 	= Act_None;
	EventList[EV_Confirm_Emergency_Stop].EventActionTime1_2 = 0;
	EventList[EV_Confirm_Emergency_Stop].EventActionTime2_3 = 0;

	EventList[EV_Confirm_Emergency_Stop].Processed		= false;
	EventList[EV_Confirm_Emergency_Stop].EventLogged	= false;

	EventList[EV_Confirm_Emergency_Stop].DispType 		= Disp_None;
	//EventList[EV_Confirm_Emergency_Stop].ImageName 		= Icon_LowSpeed;
	EventList[EV_Confirm_Emergency_Stop].SplashTime 	= 0;
	EventList[EV_Confirm_Emergency_Stop].SplashActive	= false;

	EventList[EV_Confirm_Emergency_Stop].BuzzerRequired = false;
	//EventList[EV_Confirm_Emergency_Stop].BuzzerMode 	= Buzz_Once;

	memset(EventList[EV_Confirm_Emergency_Stop].EventData, 0xFF, sizeof(EventList[EV_Confirm_Emergency_Stop].EventData));
	EventList[EV_Confirm_Emergency_Stop].AddtionalInfo	= NULL;

	EventList[EV_Confirm_Emergency_Stop].TimeRequired = 0;
	EventList[EV_Confirm_Emergency_Stop].ACKRequired = false;

	// ---- Index - EV_Confirm_Controlled_Stop - ID ----
	EventList[EV_Confirm_Controlled_Stop].EventCategory = Type_Vehicle;
	EventList[EV_Confirm_Controlled_Stop].EventID 		= 195;

	EventList[EV_Confirm_Controlled_Stop].EventActive 	= false;

	sprintf(EventList[EV_Confirm_Controlled_Stop].EventName, "Controlled Stop Message");

	EventList[EV_Confirm_Controlled_Stop].TimeStampSystic = 0;

	EventList[EV_Confirm_Controlled_Stop].EventAction1	= Act_None;
	EventList[EV_Confirm_Controlled_Stop].EventAction2 	= Act_None;
	EventList[EV_Confirm_Controlled_Stop].EventAction3 	= Act_None;
	EventList[EV_Confirm_Controlled_Stop].EventActionTime1_2 = 0;
	EventList[EV_Confirm_Controlled_Stop].EventActionTime2_3 = 0;

	EventList[EV_Confirm_Controlled_Stop].Processed		= false;
	EventList[EV_Confirm_Controlled_Stop].EventLogged	= false;

	EventList[EV_Confirm_Controlled_Stop].DispType 		= Disp_None;
	//EventList[EV_Confirm_Controlled_Stop].ImageName 	= Icon_LowSpeed;
	EventList[EV_Confirm_Controlled_Stop].SplashTime 	= 0;
	EventList[EV_Confirm_Controlled_Stop].SplashActive	= false;

	EventList[EV_Confirm_Controlled_Stop].BuzzerRequired = false;
	//EventList[EV_Confirm_Controlled_Stop].BuzzerMode 	= Buzz_Fast;

	memset(EventList[EV_Confirm_Controlled_Stop].EventData, 0xFF, sizeof(EventList[EV_Confirm_Controlled_Stop].EventData));
	EventList[EV_Confirm_Controlled_Stop].AddtionalInfo	= NULL;

	EventList[EV_Confirm_Controlled_Stop].TimeRequired = 0;
	EventList[EV_Confirm_Controlled_Stop].ACKRequired = false;

	// ---- Index - EV_Confirm_SlowDown - ID ----
	EventList[EV_Confirm_SlowDown].EventCategory 		= Type_Vehicle;
	EventList[EV_Confirm_SlowDown].EventID 				= 196;

	EventList[EV_Confirm_SlowDown].EventActive 			= false;

	sprintf(EventList[EV_Confirm_SlowDown].EventName, "Slow Down Message");

	EventList[EV_Confirm_SlowDown].TimeStampSystic 		= 0;

	EventList[EV_Confirm_SlowDown].EventAction1			= Act_None;
	EventList[EV_Confirm_SlowDown].EventAction2 		= Act_None;
	EventList[EV_Confirm_SlowDown].EventAction3 		= Act_None;
	EventList[EV_Confirm_SlowDown].EventActionTime1_2 	= 0;
	EventList[EV_Confirm_SlowDown].EventActionTime2_3 	= 0;

	EventList[EV_Confirm_SlowDown].Processed			= false;
	EventList[EV_Confirm_SlowDown].EventLogged			= false;

	EventList[EV_Confirm_SlowDown].DispType 			= Disp_None;
	//EventList[EV_Confirm_SlowDown].ImageName 			= Icon_LowSpeed;
	EventList[EV_Confirm_SlowDown].SplashTime 			= 0;
	EventList[EV_Confirm_SlowDown].SplashActive			= false;

	EventList[EV_Confirm_SlowDown].BuzzerRequired 		= false;
	//EventList[EV_Confirm_SlowDown].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Confirm_SlowDown].EventData, 0xFF, sizeof(EventList[EV_Confirm_SlowDown].EventData));
	EventList[EV_Confirm_SlowDown].AddtionalInfo		= NULL;

	EventList[EV_Confirm_SlowDown].TimeRequired = 0;
	EventList[EV_Confirm_SlowDown].ACKRequired = false;

	// ---- Index - EV_Confirm_Bypass - ID ----
	EventList[EV_Confirm_Bypass].EventCategory 			= Type_Vehicle;
	EventList[EV_Confirm_Bypass].EventID 				= 197;

	EventList[EV_Confirm_Bypass].EventActive 			= false;

	sprintf(EventList[EV_Confirm_Bypass].EventName, "Bypass Message");

	EventList[EV_Confirm_Bypass].TimeStampSystic 		= 0;

	EventList[EV_Confirm_Bypass].EventAction1			= Act_None;
	EventList[EV_Confirm_Bypass].EventAction2 			= Act_None;
	EventList[EV_Confirm_Bypass].EventAction3 			= Act_None;
	EventList[EV_Confirm_Bypass].EventActionTime1_2 	= 0;
	EventList[EV_Confirm_Bypass].EventActionTime2_3 	= 0;

	EventList[EV_Confirm_Bypass].Processed				= false;
	EventList[EV_Confirm_Bypass].EventLogged			= false;

	EventList[EV_Confirm_Bypass].DispType 				= Disp_None;
	//EventList[EV_Confirm_Bypass].ImageName 				= Icon_LowSpeed;
	EventList[EV_Confirm_Bypass].SplashTime 			= 0;
	EventList[EV_Confirm_Bypass].SplashActive			= false;

	EventList[EV_Confirm_Bypass].BuzzerRequired 		= false;
	//EventList[EV_Confirm_Bypass].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Confirm_Bypass].EventData, 0xFF, sizeof(EventList[EV_Confirm_Bypass].EventData));
	EventList[EV_Confirm_Bypass].AddtionalInfo			= NULL;

	EventList[EV_Confirm_Bypass].TimeRequired = 0;
	EventList[EV_Confirm_Bypass].ACKRequired = false;

	// ---- Index - EV_Confirm_ApplySetPoint - ID ----
	EventList[EV_Confirm_ApplySetPoint].EventCategory 	= Type_Vehicle;
	EventList[EV_Confirm_ApplySetPoint].EventID 		= 198;

	EventList[EV_Confirm_ApplySetPoint].EventActive 	= false;

	sprintf(EventList[EV_Confirm_ApplySetPoint].EventName, "Set Point Message");

	EventList[EV_Confirm_ApplySetPoint].TimeStampSystic = 0;

	EventList[EV_Confirm_ApplySetPoint].EventAction1	= Act_None;
	EventList[EV_Confirm_ApplySetPoint].EventAction2 	= Act_None;
	EventList[EV_Confirm_ApplySetPoint].EventAction3 	= Act_None;
	EventList[EV_Confirm_ApplySetPoint].EventActionTime1_2 = 0;
	EventList[EV_Confirm_ApplySetPoint].EventActionTime2_3 = 0;

	EventList[EV_Confirm_ApplySetPoint].Processed		= false;
	EventList[EV_Confirm_ApplySetPoint].EventLogged		= false;

	EventList[EV_Confirm_ApplySetPoint].DispType 		= Disp_None;
	//EventList[EV_Confirm_ApplySetPoint].ImageName 		= Icon_LowSpeed;
	EventList[EV_Confirm_ApplySetPoint].SplashTime 		= 0;
	EventList[EV_Confirm_ApplySetPoint].SplashActive	= false;

	EventList[EV_Confirm_ApplySetPoint].BuzzerRequired 	= false;
	//EventList[EV_Confirm_ApplySetPoint].BuzzerMode 		= Buzz_Fast;

	memset(EventList[EV_Confirm_ApplySetPoint].EventData, 0xFF, sizeof(EventList[EV_Confirm_ApplySetPoint].EventData));
	EventList[EV_Confirm_ApplySetPoint].AddtionalInfo	= NULL;

	EventList[EV_Confirm_ApplySetPoint].TimeRequired = 0;
	EventList[EV_Confirm_ApplySetPoint].ACKRequired = false;

	// ---- Index - EV_Confirm_StandDown - ID ----
	EventList[EV_Confirm_StandDown].EventCategory 		= Type_Vehicle;
	EventList[EV_Confirm_StandDown].EventID 			= 199;

	EventList[EV_Confirm_StandDown].EventActive 		= false;

	sprintf(EventList[EV_Confirm_StandDown].EventName, "Stand Down Message");

	EventList[EV_Confirm_StandDown].TimeStampSystic 	= 0;

	EventList[EV_Confirm_StandDown].EventAction1		= Act_None;
	EventList[EV_Confirm_StandDown].EventAction2 		= Act_None;
	EventList[EV_Confirm_StandDown].EventAction3 		= Act_None;
	EventList[EV_Confirm_StandDown].EventActionTime1_2 	= 0;
	EventList[EV_Confirm_StandDown].EventActionTime2_3 	= 0;

	EventList[EV_Confirm_StandDown].Processed			= false;
	EventList[EV_Confirm_StandDown].EventLogged			= false;

	EventList[EV_Confirm_StandDown].DispType 			= Disp_None;
	//EventList[EV_Confirm_StandDown].ImageName 			= Icon_LowSpeed;
	EventList[EV_Confirm_StandDown].SplashTime 			= 0;
	EventList[EV_Confirm_StandDown].SplashActive		= false;

	EventList[EV_Confirm_StandDown].BuzzerRequired 		= false;
	//EventList[EV_Confirm_StandDown].BuzzerMode 			= Buzz_Once;

	memset(EventList[EV_Confirm_StandDown].EventData, 0xFF, sizeof(EventList[EV_Confirm_StandDown].EventData));
	EventList[EV_Confirm_StandDown].AddtionalInfo		= NULL;

	EventList[EV_Confirm_StandDown].TimeRequired = 0;
	EventList[EV_Confirm_StandDown].ACKRequired = false;

	// ---- Index - EV_Confirm_Motion_Inhibit - ID ----
	EventList[EV_Confirm_Motion_Inhibit].EventCategory 	= Type_Vehicle;
	EventList[EV_Confirm_Motion_Inhibit].EventID 		= 200;

	EventList[EV_Confirm_Motion_Inhibit].EventActive 	= false;

	sprintf(EventList[EV_Confirm_Motion_Inhibit].EventName, "Motion Inhibit Message");

	EventList[EV_Confirm_StandDown].TimeStampSystic 	= 0;

	EventList[EV_Confirm_Motion_Inhibit].EventAction1	= Act_None;
	EventList[EV_Confirm_Motion_Inhibit].EventAction2 	= Act_None;
	EventList[EV_Confirm_Motion_Inhibit].EventAction3 	= Act_None;
	EventList[EV_Confirm_Motion_Inhibit].EventActionTime1_2 = 0;
	EventList[EV_Confirm_Motion_Inhibit].EventActionTime2_3 = 0;

	EventList[EV_Confirm_Motion_Inhibit].Processed		= false;
	EventList[EV_Confirm_Motion_Inhibit].EventLogged	= false;

	EventList[EV_Confirm_Motion_Inhibit].DispType 		= Disp_None;
	//EventList[EV_Confirm_Motion_Inhibit].ImageName 		= Icon_LowSpeed;
	EventList[EV_Confirm_Motion_Inhibit].SplashTime 	= 0;
	EventList[EV_Confirm_Motion_Inhibit].SplashActive	= false;

	EventList[EV_Confirm_Motion_Inhibit].BuzzerRequired = false;
	//EventList[EV_Confirm_Motion_Inhibit].BuzzerMode 	= Buzz_Fast;

	memset(EventList[EV_Confirm_Motion_Inhibit].EventData, 0xFF, sizeof(EventList[EV_Confirm_Motion_Inhibit].EventData));
	EventList[EV_Confirm_Motion_Inhibit].AddtionalInfo	= NULL;

	EventList[EV_Confirm_Motion_Inhibit].TimeRequired = 0;
	EventList[EV_Confirm_Motion_Inhibit].ACKRequired = false;

	// ---- Index - EV_Negotiation_Incomplete - ID ----
	EventList[EV_Negotiation_Incomplete].EventCategory 	= Type_Vehicle;
	EventList[EV_Negotiation_Incomplete].EventID 		= 201;

	EventList[EV_Negotiation_Incomplete].EventActive 	= false;

	sprintf(EventList[EV_Negotiation_Incomplete].EventName, "Negotiation Incomplete");

	EventList[EV_Negotiation_Incomplete].TimeStampSystic 	= 0;

	EventList[EV_Negotiation_Incomplete].EventAction1	= Act_None;
	EventList[EV_Negotiation_Incomplete].EventAction2 	= Act_None;
	EventList[EV_Negotiation_Incomplete].EventAction3 	= Act_None;
	EventList[EV_Negotiation_Incomplete].EventActionTime1_2 = 0;
	EventList[EV_Negotiation_Incomplete].EventActionTime2_3 = 0;

	EventList[EV_Negotiation_Incomplete].Processed		= false;
	EventList[EV_Negotiation_Incomplete].EventLogged	= false;

	EventList[EV_Negotiation_Incomplete].DispType 		= Disp_None;
	//EventList[EV_Negotiation_Incomplete].ImageName 		= Icon_LowSpeed;
	EventList[EV_Negotiation_Incomplete].SplashTime 	= 0;
	EventList[EV_Negotiation_Incomplete].SplashActive	= false;

	EventList[EV_Negotiation_Incomplete].BuzzerRequired = false;
	//EventList[EV_Negotiation_Incomplete].BuzzerMode 	= Buzz_Fast;

	memset(EventList[EV_Negotiation_Incomplete].EventData, 0xFF, sizeof(EventList[EV_Negotiation_Incomplete].EventData));
	EventList[EV_Negotiation_Incomplete].AddtionalInfo	= NULL;

	EventList[EV_Negotiation_Incomplete].TimeRequired = 0;
	EventList[EV_Negotiation_Incomplete].ACKRequired = false;

	// ---- Index - EV_Negotiation_Complete_01 - ID ----
	EventList[EV_Negotiation_Complete_01].EventCategory 	= Type_Vehicle;
	EventList[EV_Negotiation_Complete_01].EventID 			= 202;

	EventList[EV_Negotiation_Complete_01].EventActive 		= false;

	sprintf(EventList[EV_Negotiation_Complete_01].EventName, "Negotiation Completed");

	EventList[EV_Negotiation_Complete_01].TimeStampSystic 	= 0;

	EventList[EV_Negotiation_Complete_01].EventAction1		= Act_None;
	EventList[EV_Negotiation_Complete_01].EventAction2 		= Act_None;
	EventList[EV_Negotiation_Complete_01].EventAction3 		= Act_None;
	EventList[EV_Negotiation_Complete_01].EventActionTime1_2 = 0;
	EventList[EV_Negotiation_Complete_01].EventActionTime2_3 = 0;

	EventList[EV_Negotiation_Complete_01].Processed			= false;
	EventList[EV_Negotiation_Complete_01].EventLogged		= false;

	EventList[EV_Negotiation_Complete_01].DispType 			= Disp_None;
	//EventList[EV_Negotiation_Complete_01].ImageName 		= Icon_LowSpeed;
	EventList[EV_Negotiation_Complete_01].SplashTime 		= 0;
	EventList[EV_Negotiation_Complete_01].SplashActive		= false;

	EventList[EV_Negotiation_Complete_01].BuzzerRequired 	= false;
	//EventList[EV_Negotiation_Complete_01].BuzzerMode 		= Buzz_Fast;

	memset(EventList[EV_Negotiation_Complete_01].EventData, 0xFF, sizeof(EventList[EV_Negotiation_Complete_01].EventData));
	EventList[EV_Negotiation_Complete_01].AddtionalInfo		= NULL;

	EventList[EV_Negotiation_Complete_01].TimeRequired = 0;
	EventList[EV_Negotiation_Complete_01].ACKRequired = false;

	// ---- Index - EV_Negotiation_Complete_02 - ID ----
	EventList[EV_Negotiation_Complete_02].EventCategory 	= Type_Vehicle;
	EventList[EV_Negotiation_Complete_02].EventID 			= 202;

	EventList[EV_Negotiation_Complete_02].EventActive 		= false;

	sprintf(EventList[EV_Negotiation_Complete_02].EventName, "Negotiation Completed");

	EventList[EV_Negotiation_Complete_02].TimeStampSystic 	= 0;

	EventList[EV_Negotiation_Complete_02].EventAction1		= Act_None;
	EventList[EV_Negotiation_Complete_02].EventAction2 		= Act_None;
	EventList[EV_Negotiation_Complete_02].EventAction3 		= Act_None;
	EventList[EV_Negotiation_Complete_02].EventActionTime1_2 = 0;
	EventList[EV_Negotiation_Complete_02].EventActionTime2_3 = 0;

	EventList[EV_Negotiation_Complete_02].Processed			= false;
	EventList[EV_Negotiation_Complete_02].EventLogged		= false;

	EventList[EV_Negotiation_Complete_02].DispType 			= Disp_None;
	//EventList[EV_Negotiation_Complete_02].ImageName 		= Icon_LowSpeed;
	EventList[EV_Negotiation_Complete_02].SplashTime 		= 0;
	EventList[EV_Negotiation_Complete_02].SplashActive		= false;

	EventList[EV_Negotiation_Complete_02].BuzzerRequired 	= false;
	//EventList[EV_Negotiation_Complete_02].BuzzerMode 		= Buzz_Fast;

	memset(EventList[EV_Negotiation_Complete_02].EventData, 0xFF, sizeof(EventList[EV_Negotiation_Complete_02].EventData));
	EventList[EV_Negotiation_Complete_02].AddtionalInfo		= NULL;

	EventList[EV_Negotiation_Complete_02].TimeRequired = 0;
	EventList[EV_Negotiation_Complete_02].ACKRequired = false;

	// ---- Index - EV_Negotiation_Complete_03 - ID ----
	EventList[EV_Negotiation_Complete_03].EventCategory 	= Type_Vehicle;
	EventList[EV_Negotiation_Complete_03].EventID 			= 202;

	EventList[EV_Negotiation_Complete_03].EventActive 		= false;

	sprintf(EventList[EV_Negotiation_Complete_03].EventName, "Negotiation Completed");

	EventList[EV_Negotiation_Complete_03].TimeStampSystic 	= 0;

	EventList[EV_Negotiation_Complete_03].EventAction1		= Act_None;
	EventList[EV_Negotiation_Complete_03].EventAction2 		= Act_None;
	EventList[EV_Negotiation_Complete_03].EventAction3 		= Act_None;
	EventList[EV_Negotiation_Complete_03].EventActionTime1_2 = 0;
	EventList[EV_Negotiation_Complete_03].EventActionTime2_3 = 0;

	EventList[EV_Negotiation_Complete_03].Processed			= false;
	EventList[EV_Negotiation_Complete_03].EventLogged		= false;

	EventList[EV_Negotiation_Complete_03].DispType 			= Disp_None;
	//EventList[EV_Negotiation_Complete_03].ImageName 		= Icon_LowSpeed;
	EventList[EV_Negotiation_Complete_03].SplashTime 		= 0;
	EventList[EV_Negotiation_Complete_03].SplashActive		= false;

	EventList[EV_Negotiation_Complete_03].BuzzerRequired 	= false;
	//EventList[EV_Negotiation_Complete_03].BuzzerMode 		= Buzz_Fast;

	memset(EventList[EV_Negotiation_Complete_03].EventData, 0xFF, sizeof(EventList[EV_Negotiation_Complete_03].EventData));
	EventList[EV_Negotiation_Complete_03].AddtionalInfo		= NULL;

	EventList[EV_Negotiation_Complete_03].TimeRequired = 0;
	EventList[EV_Negotiation_Complete_03].ACKRequired = false;

	// ---- Index - EV_Idle - ID ----
	EventList[EV_Idle].EventCategory 					= Type_System;
	EventList[EV_Idle].EventID 							= 423;

	EventList[EV_Idle].EventActive 						= false;

	sprintf(EventList[EV_Idle].EventName, "System Idle");

	EventList[EV_Idle].TimeStampSystic 					= 0;

	EventList[EV_Idle].EventAction1 					= Act_None;
	EventList[EV_Idle].EventAction2 					= Act_None;
	EventList[EV_Idle].EventAction3 					= Act_None;
	EventList[EV_Idle].EventActionTime1_2 				= 0;
	EventList[EV_Idle].EventActionTime2_3 				= 0;

	EventList[EV_Idle].Processed 						= false;
	EventList[EV_Idle].EventLogged 						= false;

	EventList[EV_Idle].DispType 						= Disp_None;
	//EventList[EV_Idle].ImageName 						= Icon_Attention;

	EventList[EV_Idle].BuzzerRequired 					= false;
	//EventList[EV_Idle].BuzzerMode 						= Buzz_Once;

	memset(EventList[EV_Idle].EventData, 0xFF, sizeof(EventList[EV_Idle].EventData));
	EventList[EV_Idle].AddtionalInfo					= NULL;

	EventList[EV_Idle].TimeRequired = 0;
	EventList[EV_Idle].ACKRequired = false;

	/*User Acknowledge Event*/
	sprintf(EventList[EV_User_ACK_CAS].EventName, "ACK Received");
	EventList[EV_User_ACK_CAS].EventID = 389;
	EventList[EV_User_ACK_CAS].EventActive = false;


	EventList[EV_User_ACK_CAS].TimeRequired = 0;
	EventList[EV_User_ACK_CAS].ACKRequired = false;
	EventList[EV_User_ACK_CAS].EventCategory = Type_PDS;

	//EventList[EV_User_ACK_CAS].ImageName = Icon_ACK;
	EventList[EV_User_ACK_CAS].DispType = Disp_Icon;

	EventList[EV_User_ACK_CAS].BuzzerRequired = false;
	//EventList[EV_User_ACK_CAS].BuzzerMode = Buzz_Medium;
}

void App_Railbound_Events_Handler(void)
{
	uint8_t GenericEventData[8] = {0};

	if (Input_Flags.Button_1 == true)
	{
		App_EventSet(Input_01_On);
		App_EventClear(Input_01_Off);
	}
	else
	{
		App_EventSet(Input_01_Off);
		App_EventClear(Input_01_On);
	}

	if (Input_Flags.Button_2 == true)
	{
		App_EventSet(Input_02_On);
		App_EventClear(Input_02_Off);
	}
	else
	{
		App_EventSet(Input_02_Off);
		App_EventClear(Input_02_On);
	}
//	/*System Idle Event*/
//	if(System_Flags.System_Status == Type_Idle)
//		App_EventSet(EV_Idle);
//	else
//		App_EventClear(EV_Idle);
//
//	// ---- Check if expansion module is enabled ----
//	if (myVisionModules[myPulse400].Module_Enabled)
//	{
//		// ---- Check if the module in expansion bay 1 is faulty ----
//		if((!myVisionModules[myPulse400].Module_OK))
//		{
//			App_EventSet(EV_Exp_Mod_1_Fail);
//			App_VisionModules_GetModuleData(myVisionModules[myPulse400], GenericEventData);
//			App_EventUpdateData(EV_Exp_Mod_1_Fail, GenericEventData);
//			App_EventClear(EV_Exp_Mod_1_OK);
//		}
//		// ---- If expansion bay 1 is healthy ----
//		else
//		{
//			App_EventSet(EV_Exp_Mod_1_OK);
//			App_VisionModules_GetModuleData(myVisionModules[myPulse400], GenericEventData);
//			App_EventUpdateData(EV_Exp_Mod_1_OK, GenericEventData);
//			App_EventClear(EV_Exp_Mod_1_Fail);
//		}
//	}
//
//	// ---- Check if expansion module is enabled ----
//	if (myVisionModules[myUbloxGPS].Module_Enabled)
//	{
//		// ---- Check if the module in expansion bay 2 is faulty ----
//		if ((!myVisionModules[myUbloxGPS].Module_OK) || ((!OwnPosition.Own_Position_Ready) && (Local_Params[Local_Antenna_Sense].ParamCURRENT == 0)))
//		{
//			App_EventSet(EV_Exp_Mod_2_Fail);
//			App_VisionModules_GetModuleData(myVisionModules[myUbloxGPS], GenericEventData);
//			App_EventUpdateData(EV_Exp_Mod_2_Fail, GenericEventData);
//			App_EventClear(EV_Exp_Mod_2_OK);
//		}
//		// ---- If expansion bay 2 is healthy ----
//		else
//		{
//			App_EventSet(EV_Exp_Mod_2_OK);
//			App_VisionModules_GetModuleData(myVisionModules[myUbloxGPS], GenericEventData);
//			App_EventUpdateData(EV_Exp_Mod_2_OK, GenericEventData);
//			App_EventClear(EV_Exp_Mod_2_Fail);
//		}
//	}
//
//	// ---- Check if the antenna sense parameter is set ----
//	if(Local_Params[Local_Antenna_Sense].ParamCURRENT == 1)
//	{
//		// ---- Check connection of PDS antenna (not connected) ----
//		if(!PULSE400_Module.stat.Antenna_connected)
//		{
//			App_EventSet(EV_Exp_Mod_1_Ant_Fail);
//			App_EventClear(EV_Exp_Mod_1_Ant_OK);
//		}
//		// ---- Connection of PDS antenna (connected) ----
//		else
//		{
//			App_EventSet(EV_Exp_Mod_1_Ant_OK);
//			App_EventClear(EV_Exp_Mod_1_Ant_Fail);
//		}
//
//		// ---- Check connection of GPS antenna, since the system initializes and wait for GPS fix ----
//		if (!OwnPosition.Own_Position_Ready)
//		{
//			App_EventSet(EV_Exp_Mod_2_Ant_Fail);
//			App_EventClear(EV_Exp_Mod_2_Ant_OK);
//		}
//		// ---- No GPS fix make assumption antenna is damaged ----
//		else
//		{
//			App_EventSet(EV_Exp_Mod_2_Ant_OK);
//			App_EventClear(EV_Exp_Mod_2_Ant_Fail);
//		}
//	}
//
//	// ---- Check if the parameters revision are a match set events accordingly ----
//	if(!Param_Status.RevisionOK)
//	{
//		App_EventSet(EV_Revison_Fail);
//		App_Parameters_GetParameterData(GenericEventData);
//		App_EventUpdateData(EV_Revison_Fail, GenericEventData);
//		App_EventClear(EV_Revison_OK);
//	}
//	// ---- If the parameters revision are not a match set events accordingly ----
//	else
//	{
//		App_EventSet(EV_Revison_OK);
//		App_Parameters_GetParameterData(GenericEventData);
//		App_EventUpdateData(EV_Revison_OK, GenericEventData);
//		App_EventClear(EV_Revison_Fail);
//	}
//
//	// ---- Check if ambient light sensor has passed set event active ----
//	if (System_HealthFlags.HealthFlag_AmbientLight)
//	{
//		App_EventSet(EV_AmbientSensor_OK);
//		App_Init_GetAmbientData(GenericEventData);
//		App_EventUpdateData(EV_AmbientSensor_OK, GenericEventData);
//		App_EventClear(EV_AmbientSensor_Fail);
//	}
//	// ---- If ambient light sensor has failed set event active ----
//	else
//	{
//		App_EventSet(EV_AmbientSensor_Fail);
//		App_EventClear(EV_AmbientSensor_OK);
//	}
//
//	// ---- Check if NVRAM has passed set event active ----
//	if (System_HealthFlags.HealthFlag_NVRAM)
//	{
//		App_EventSet(EV_NVRAMSPI_OK);
//		App_EventClear(EV_NVRAMSPI_Fail);
//	}
//	// ---- If NVRAM has failed set event active ----
//	else
//	{
//		App_EventSet(EV_NVRAMSPI_Fail);
//		App_EventClear(EV_NVRAMSPI_OK);
//	}
//
//	// ---- Check if RTC has passed set event active ----
//	if (System_HealthFlags.HealthFlag_RTC)
//	{
//		App_EventSet(EV_RTCSPI_OK);
//		App_EventClear(EV_RTCSPI_Fail);
//	}
//	// ---- If RTC has failed set event active ----
//	else
//	{
//		App_EventSet(EV_RTCSPI_Fail);
//		App_EventClear(EV_RTCSPI_OK);
//	}
//
//	// ---- Check if System Time has passed set event active ----
//	if (System_HealthFlags.HealthFlag_SystemTime)
//	{
//		App_EventSet(EV_SystemTime_OK);
//		App_EventClear(EV_SystemTime_Fail);
//	}
//	// ---- If System Time has failed set event active ----
//	else
//	{
//		App_EventSet(EV_SystemTime_Fail);
//		App_Init_GetSystemTimeData(GenericEventData);
//		App_EventUpdateData(EV_SystemTime_Fail, GenericEventData);
//		App_EventClear(EV_SystemTime_OK);
//	}
//
//	// ---- Check if the EStop is in the latched state (Internal EStop Button) ----
//	if(Input_Flags.Estop_In_Int)
//	{
//		App_EventSet(EV_Estop_Latch_Int);
//		App_SpeedControl_GetEStopData(EV_Estop_Latch_Int, GenericEventData);
//		App_EventUpdateData(EV_Estop_Latch_Int, GenericEventData);
//		App_EventClear(EV_EStop_Release_Int);
//	}
//	// ---- If the EStop is in the released state (Internal EStop Button) ----
//	else
//	{
//		App_EventSet(EV_EStop_Release_Int);
//		App_SpeedControl_GetEStopData(EV_EStop_Release_Int, GenericEventData);
//		App_EventUpdateData(EV_EStop_Release_Int, GenericEventData);
//		App_EventClear(EV_Estop_Latch_Int);
//	}
//
//	// ---- Check if the EStop is in the latched state (External EStop Button) ----
//	if(Input_Flags.Estop_In_Ext)
//	{
//		App_EventSet(EV_Estop_Latch_Ext);
//		App_SpeedControl_GetEStopData(EV_Estop_Latch_Ext, GenericEventData);
//		App_EventUpdateData(EV_Estop_Latch_Ext, GenericEventData);
//		App_EventClear(EV_Estop_Release_Ext);
//	}
//	// ---- If the EStop is in the released state (External EStop Button) ----
//	else
//	{
//		App_EventSet(EV_Estop_Release_Ext);
//		App_SpeedControl_GetEStopData(EV_Estop_Release_Ext, GenericEventData);
//		App_EventUpdateData(EV_Estop_Release_Ext, GenericEventData);
//		App_EventClear(EV_Estop_Latch_Ext);
//	}
//
//	// ---- Check if input flag of external input 1 is set (active high) ----
//	if (Input_Flags.Ext_In_1)
//	{
//		App_EventSet(Input_01_On);
//		App_EventClear(Input_01_Off);
//	}
//	// ---- Input flag of external input 1 is not set (active high) ----
//	else
//	{
//		App_EventSet(Input_01_Off);
//		App_EventClear(Input_01_On);
//	}
//
//	// ---- Check if input flag of external input 2 is set (active high) ----
//	if (Input_Flags.Ext_In_2)
//	{
//		App_EventSet(Input_02_On);
//		App_EventClear(Input_02_Off);
//	}
//	// ---- Input flag of external input 2 is not set (active high) ----
//	else
//	{
//		App_EventSet(Input_02_Off);
//		App_EventClear(Input_02_On);
//	}
//
//	// ---- Check if input flag of external input 3 is set (active high) ----
//	if (Input_Flags.Ext_In_3)
//	{
//		App_EventSet(Input_03_On);
//		App_EventClear(Input_03_Off);
//	}
//	// ---- Input flag of external input 3 is not set (active high) ----
//	else
//	{
//		App_EventSet(Input_03_Off);
//		App_EventClear(Input_03_On);
//	}
//
//	// ---- Check if input flag of external input 4 is not set (active low) ----
//	if (Input_Flags.Ext_In_4)
//	{
//		App_EventSet(Input_04_On);
//		App_EventClear(Input_04_Off);
//	}
//	// ---- Input flag of external input 4 is set (active low) ----
//	else
//	{
//		App_EventSet(Input_04_Off);
//		App_EventClear(Input_04_On);
//	}
//
//	// ---- Check if input flag of external input 5 is not set (active low) ----
//	if (Input_Flags.Ext_In_5)
//	{
//		App_EventSet(Input_05_On);
//		App_EventClear(Input_05_Off);
//	}
//	// ---- Input flag of external input 5 is set (active low) ----
//	else
//	{
//		App_EventSet(Input_05_Off);
//		App_EventClear(Input_05_On);
//	}
//
//	// ---- Check if input flag of external input 6 is not set (active low) ----
//	if (Input_Flags.Ext_In_6)
//	{
//		App_EventSet(Input_06_On);
//		App_EventClear(Input_06_Off);
//	}
//	// ---- Input flag of external input 6 is set (active low) ----
//	else
//	{
//		App_EventSet(Input_06_Off);
//		App_EventClear(Input_06_On);
//	}
//
//	// ---- Check if global device RF monitoring is active ----
//	if (Local_Params[Local_RF_Required].ParamCURRENT == 1)
//	{
//		// ---- Request specific unit connection status ----
//		uint8_t	MonitorResult = App_Monitoring_GetRFStatus(Pulse300_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Pulse300_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceRF01_OK);
//			App_EventUpdateData(EV_PulseDeviceRF01_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF01_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceRF01_Fail);
//			App_EventUpdateData(EV_PulseDeviceRF01_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF01_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetRFStatus(Right_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Right_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceRF02_OK);
//			App_EventUpdateData(EV_PulseDeviceRF02_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF02_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceRF02_Fail);
//			App_EventUpdateData(EV_PulseDeviceRF02_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF02_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetRFStatus(Rear_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Rear_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceRF03_OK);
//			App_EventUpdateData(EV_PulseDeviceRF03_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF03_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceRF03_Fail);
//			App_EventUpdateData(EV_PulseDeviceRF03_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF03_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetRFStatus(Left_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Left_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceRF04_OK);
//			App_EventUpdateData(EV_PulseDeviceRF04_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF04_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceRF04_Fail);
//			App_EventUpdateData(EV_PulseDeviceRF04_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF04_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetRFStatus(Front_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Front_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceRF05_OK);
//			App_EventUpdateData(EV_PulseDeviceRF05_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF05_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceRF05_Fail);
//			App_EventUpdateData(EV_PulseDeviceRF05_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceRF05_OK);
//		}
//	}
//
//	// ---- Check if global device CAN monitoring is active ----
//	if (Local_Params[Local_CAN_Required].ParamCURRENT == 1)
//	{
//		// ---- Request specific unit connection status ----
//		uint8_t	MonitorResult = App_Monitoring_GetCANStatus(Pulse300_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Pulse300_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceCAN01_OK);
//			App_EventUpdateData(EV_PulseDeviceCAN01_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN01_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceCAN01_Fail);
//			App_EventUpdateData(EV_PulseDeviceCAN01_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN01_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetCANStatus(Right_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Right_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceCAN02_OK);
//			App_EventUpdateData(EV_PulseDeviceCAN02_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN02_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceCAN02_Fail);
//			App_EventUpdateData(EV_PulseDeviceCAN02_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN02_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetCANStatus(Rear_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Rear_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceCAN03_OK);
//			App_EventUpdateData(EV_PulseDeviceCAN03_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN03_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceCAN03_Fail);
//			App_EventUpdateData(EV_PulseDeviceCAN03_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN03_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetCANStatus(Left_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Left_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceCAN04_OK);
//			App_EventUpdateData(EV_PulseDeviceCAN04_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN04_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceCAN04_Fail);
//			App_EventUpdateData(EV_PulseDeviceCAN04_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN04_OK);
//		}
//
//		// ---- Request specific unit connection status ----
//		MonitorResult = App_Monitoring_GetCANStatus(Front_Tag_Monitor);
//		App_Monitoring_GetMonitoringData(Front_Tag_Monitor, GenericEventData);
//
//		// ---- If the result of the monitoring is Active, set OK event ----
//		if (MonitorResult == Monitor_Active)
//		{
//			App_EventSet(EV_PulseDeviceCAN05_OK);
//			App_EventUpdateData(EV_PulseDeviceCAN05_OK, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN05_Fail);
//		}
//		// ---- If the result of the monitoring is Failed, set Fail event ----
//		else if (MonitorResult == Monitor_Failed)
//		{
//			App_EventSet(EV_PulseDeviceCAN05_Fail);
//			App_EventUpdateData(EV_PulseDeviceCAN05_Fail, GenericEventData);
//			App_EventClear(EV_PulseDeviceCAN05_OK);
//		}
//	}
//
//	// ---- Check if the HUB 200 is enabled ----
//	if (Local_Params[Local_HUB200_Enable].ParamCURRENT == 1)
//	{
//		// ---- Check the status and set events accordingly (HUB200 Failure) ----
//		if (!System_Flags.System_HUB200)
//		{
//			App_EventSet(EV_HUB200_Failure);
//			App_EventClear(EV_HUB200_OK);
//		}
//		// ---- Check the status and set events accordingly (HUB200 Failure) ----
//		else
//		{
//			App_EventSet(EV_HUB200_OK);
//			App_EventClear(EV_HUB200_Failure);
//		}
//	}
//
//	// ---- Check if the HUB 200 is enabled ----
//	if (Local_Params[Local_Lightbar_Enable].ParamCURRENT == 1)
//	{
//		// ---- Check the status and set events accordingly (HUB200 Failure) ----
//		if (!APP_CAN_LightPro.LightProConnected[0])
//		{
//			App_EventSet(EV_LightBar_Failure);
//			App_EventClear(EV_LightBar_OK);
//		}
//		// ---- Check the status and set events accordingly (HUB200 Failure) ----
//		else
//		{
//			App_EventSet(EV_LightBar_OK);
//			App_EventClear(EV_LightBar_Failure);
//		}
//	}
//
//	// ---- Check the status of work zone if it has ended set end event ----
//	if (System_Flags.System_WorkZoneStatus == Status_Inactive)
//	{
//		App_EventSet(EV_Operational_WorkZoneEnd);
//		App_EventClear(EV_Operational_WorkZone_01);
//		App_EventClear(EV_Operational_WorkZoneFail);
//	}
//	// ---- Check the status of work zone if it is set active set event ----
//	else if (System_Flags.System_WorkZoneStatus == Status_Active)
//	{
//		App_EventSet(EV_Operational_WorkZone_01);
//		App_EventClear(EV_Operational_WorkZoneEnd);
//		App_EventClear(EV_Operational_WorkZoneFail);
//	}
//	// ---- Check the status of work zone if it has failed set event ----
//	else if (System_Flags.System_WorkZoneStatus == Status_NotRequired)
//	{
//		App_EventSet(EV_Operational_WorkZoneFail);
//		App_EventClear(EV_Operational_WorkZone_01);
//		App_EventClear(EV_Operational_WorkZoneEnd);
//	}
//
//	// ---- Check current speed zone set events accordingly (Speed Zone Low) ----
//	if (SpeedControlParameters.SpeedZone_Current == SpeedZone_Low)
//	{
//		App_EventSet(EV_LowSpeedZone);
//		App_SpeedControl_GetZoneChangeData(EV_LowSpeedZone, GenericEventData);
//		App_EventUpdateData(EV_LowSpeedZone, GenericEventData);
//		App_EventClear(EV_MeduimSpeedZone);
//		App_EventClear(EV_HighSpeedZone);
//	}
//	// ---- Check current speed zone set events accordingly (Speed Zone Medium) ----
//	else if (SpeedControlParameters.SpeedZone_Current == SpeedZone_Med)
//	{
//		App_EventSet(EV_MeduimSpeedZone);
//		App_SpeedControl_GetZoneChangeData(EV_MeduimSpeedZone, GenericEventData);
//		App_EventUpdateData(EV_MeduimSpeedZone, GenericEventData);
//		App_EventClear(EV_LowSpeedZone);
//		App_EventClear(EV_HighSpeedZone);
//	}
//	// ---- Check current speed zone set events accordingly (Speed Zone High) ----
//	else if (SpeedControlParameters.SpeedZone_Current == SpeedZone_High)
//	{
//		App_EventSet(EV_HighSpeedZone);
//		App_SpeedControl_GetZoneChangeData(EV_HighSpeedZone, GenericEventData);
//		App_EventUpdateData(EV_HighSpeedZone, GenericEventData);
//		App_EventClear(EV_LowSpeedZone);
//		App_EventClear(EV_MeduimSpeedZone);
//	}
//	// ---- Check current speed zone set events accordingly (Speed Zone None) ----
//	else
//	{
//		App_EventClear(EV_LowSpeedZone);
//		App_EventClear(EV_MeduimSpeedZone);
//		App_EventClear(EV_HighSpeedZone);
//	}
//
//	// ---- Check previous speed zone set events accordingly (Speed Zone Low) ----
//	if (SpeedControlParameters.SpeedZone_Previous == SpeedZone_Low)
//	{
//		App_EventSet(EV_LowSpeedZone_End);
//		App_EventClear(EV_MeduimSpeedZone_End);
//		App_EventClear(EV_HighSpeedZone_End);
//	}
//	// ---- Check previous speed zone set events accordingly (Speed Zone Medium) ----
//	else if (SpeedControlParameters.SpeedZone_Previous == SpeedZone_Med)
//	{
//		App_EventSet(EV_MeduimSpeedZone_End);
//		App_EventClear(EV_LowSpeedZone_End);
//		App_EventClear(EV_HighSpeedZone_End);
//	}
//	// ---- Check previous speed zone set events accordingly (Speed Zone High) ----
//	else if (SpeedControlParameters.SpeedZone_Previous == SpeedZone_High)
//	{
//		App_EventSet(EV_HighSpeedZone_End);
//		App_EventClear(EV_LowSpeedZone_End);
//		App_EventClear(EV_MeduimSpeedZone_End);
//	}
//	// ---- Check previous speed zone set events accordingly (Speed Zone None) ----
//	else
//	{
//		App_EventClear(EV_LowSpeedZone_End);
//		App_EventClear(EV_MeduimSpeedZone_End);
//		App_EventClear(EV_HighSpeedZone_End);
//	}
//
//	// ---- Check if the speed bar is enabled ----
//	if (Local_Params[Local_Speedbar_Enable].ParamCURRENT == 1)
//	{
//		// ---- Check the status and set events accordingly (Speed Over) ----
//		if(SpeedBarParameters.Indicator_SpeedOverSpeed == Status_Active)
//		{
//			App_EventSet(EV_Speed_Overspeeding);
//			App_SpeedBar_GetSpeedData(GenericEventData);
//			App_EventUpdateData(EV_Speed_Overspeeding, GenericEventData);
//			App_EventClear(EV_Speed_OverspeedingEnd);
//		}
//		// ---- Check the status and set events accordingly (Speed Over End) ----
//		else if (SpeedBarParameters.Indicator_SpeedOverSpeed == Status_Inactive)
//		{
//			App_EventSet(EV_Speed_OverspeedingEnd);
//			App_SpeedBar_GetSpeedData(GenericEventData);
//			App_EventUpdateData(EV_Speed_OverspeedingEnd, GenericEventData);
//			App_EventClear(EV_Speed_Overspeeding);
//		}
//
//		// ---- Check the status and set events accordingly (Speed Warning) ----
//		if(SpeedBarParameters.Indicator_SpeedWarning == Status_Active)
//		{
//			App_EventSet(EV_Speed_Warning);
//			App_SpeedBar_GetSpeedData(GenericEventData);
//			App_EventUpdateData(EV_Speed_Warning, GenericEventData);
//			App_EventClear(EV_Speed_WarningEnd);
//		}
//		// ---- Check the status and set events accordingly (Speed Warning End) ----
//		else if (SpeedBarParameters.Indicator_SpeedWarning == Status_Inactive)
//		{
//			App_EventSet(EV_Speed_WarningEnd);
//			App_SpeedBar_GetSpeedData(GenericEventData);
//			App_EventUpdateData(EV_Speed_WarningEnd, GenericEventData);
//			App_EventClear(EV_Speed_Warning);
//		}
//
//		// ---- Check the status and set events accordingly (Speed OK) ----
//		if (SpeedBarParameters.Indicator_SpeedOK == Status_Active)
//		{
//			App_EventSet(EV_Speed_OK);
//			App_SpeedBar_GetSpeedData(GenericEventData);
//			App_EventUpdateData(EV_Speed_OK, GenericEventData);
//			App_EventClear(EV_Speed_OKEnd);
//		}
//		// ---- Check the status and set events accordingly (Speed OK End) ----
//		else if (SpeedBarParameters.Indicator_SpeedOK == Status_Inactive)
//		{
//			App_EventSet(EV_Speed_OKEnd);
//			App_SpeedBar_GetSpeedData(GenericEventData);
//			App_EventUpdateData(EV_Speed_OKEnd, GenericEventData);
//			App_EventClear(EV_Speed_OK);
//		}
//	}
//
//	// ---- Check the status and set events accordingly (Dry Road) ----
//	if (RoadConditionParameters.RoadCondition_Current == Condition_Dry)
//	{
//		App_EventSet(EV_DryRoad);
//		App_EventClear(EV_UnknownRoad);
//		App_EventClear(EV_WetRoad);
//		App_EventClear(EV_SlipRoad);
//
//	}
//	// ---- Check the status and set events accordingly (Wet Road) ----
//	else if (RoadConditionParameters.RoadCondition_Current == Condition_Wet)
//	{
//		App_EventSet(EV_WetRoad);
//		App_EventClear(EV_UnknownRoad);
//		App_EventClear(EV_DryRoad);
//		App_EventClear(EV_SlipRoad);
//	}
//	// ---- Check the status and set events accordingly (Slippery Road) ----
//	else if (RoadConditionParameters.RoadCondition_Current == Condition_Slip)
//	{
//		App_EventSet(EV_SlipRoad);
//		App_EventClear(EV_UnknownRoad);
//		App_EventClear(EV_DryRoad);
//		App_EventClear(EV_WetRoad);
//	}
//	// ---- Instruct the operator to select a road condition ----
//	else
//	{
//		App_EventSet(EV_UnknownRoad);
//		App_EventClear(EV_DryRoad);
//		App_EventClear(EV_WetRoad);
//		App_EventClear(EV_SlipRoad);
//	}
//
//	// ---- Run the PDS Events update them from the threat list ----
//	Threat_Events();
//
//	// ---- Check if the pre-operation is enabled ----
//	if (Local_Params[Local_PreOp_Required].ParamCURRENT == 1)
//	{
//		// ---- Check if the pre-operation test has timed-out ----
//		if(System_Pre_Op_Flags.Pre_Op_Timeout)
//		{
//			App_EventSet(EV_System_Pre_Op_Fail);
//		}
//		// ---- If the pre-operation test has not timed-out ----
//		else
//		{
//			App_EventClear(EV_System_Pre_Op_Fail);
//		}
//	}
//
//	// ---- Check if license card is needed for the operation of the vehicle ----
//	if (Local_Params[Local_License_Required].ParamCURRENT == 1)
//	{
//		// ---- If there are a license card detected ----
//		if (RWD_Flags.Card_In_Field)
//		{
//			// ---- Clear the license required event ----
//			App_EventClear(EV_License_Required);
//
//			// ---- If the license card is being read ----
//			if (RWD_Flags.processing)
//			{
//				// ---- Set the event that the system is busy processing the license card ----
//				App_EventSet(EV_License_Processing);
//			}
//			// ---- If the license card is fully read ----
//			else
//			{
//				// ---- Clear the license processing event ----
//				App_EventClear(EV_License_Processing);
//
//				if ((RWD_Flags.Card_All_Blocks_Read) && (RWD_Flags.Card_Blocks_Processed))
//				{
//					// ---- Set the event that the license card is processed ----
//					App_EventSet(EV_License_Processed_01);
//					App_Licensing_GetLicenceGenericEventData(EV_License_Processed_01, GenericEventData);
//					App_EventUpdateData(EV_License_Processed_01, GenericEventData);
//
//					// ---- If the license card is valid ----
//					if (Local_license_Flags.valid)
//					{
//						// ---- Set the event that the license card is valid ----
//						App_EventSet(EV_License_Valid);
//						App_Licensing_GetLicenceGenericEventData(EV_License_Valid, GenericEventData);
//						App_EventUpdateData(EV_License_Valid, GenericEventData);
//						App_EventClear(EV_License_Invalid);
//
//						// ---- If the warning date of the license card has been reached set event ----
//						if (Local_license_Flags.warning)
//						{
//							App_EventSet(EV_Licence_WarningDate);
//							App_Licensing_GetLicenceGenericEventData(EV_Licence_WarningDate, GenericEventData);
//							App_EventUpdateData(EV_Licence_WarningDate, GenericEventData);
//						}
//						// ---- Clear the warning date license card event ----
//						else
//						{
//							App_EventClear(EV_Licence_WarningDate);
//						}
//					}
//					// ---- The license card is invalid ----
//					else
//					{
//						// ---- Set the event that the license card is invalid ----
//						App_EventSet(EV_License_Invalid);
//						App_Licensing_GetLicenceInvalidEventData(GenericEventData);
//						App_EventUpdateData(EV_License_Invalid, GenericEventData);
//						App_EventClear(EV_License_Valid);
//					}
//				}
//			}
//		}
//		else
//		{
//			App_EventSet(EV_License_Required);
//			App_EventClear(EV_License_Processing);
//			App_EventClear(EV_License_Processed_01);
//			App_EventClear(EV_License_Invalid);
//			App_EventClear(EV_License_Valid);
//			App_EventClear(EV_Licence_WarningDate);
//		}
//	}
//	// ---- If there are a license card detected but the license card control is disabled ----
//	else
//	{
//		// ---- If there are a license card detected, and the license card is fully read ----
//		if((RWD_Flags.Card_In_Field) && (RWD_Flags.Card_All_Blocks_Read) && (RWD_Flags.Card_Blocks_Processed))
//		{
//			App_EventSet(EV_License_Processed_01);
//		}
//		// ---- If the license card is removed clear the processed event ----
//		else
//		{
//			App_EventClear(EV_License_Processed_01);
//		}
//	}
//
//	// ---- Technician card present ----
//	if(App_LicenseCheck(Priv_Debug))
//	{
//		App_EventSet(EV_Debug_Card);
//	}
//	// ---- Technician card not present ----
//	else
//	{
//		App_EventClear(EV_Debug_Card);
//	}
//
//	// ---- Request specific message confirmation status ----
//	if (ISO_21815_CheckPropulsionActionConfirm(RPY_EmergencyStopConfirm))
//	{
//		App_EventSet(EV_Confirm_Emergency_Stop);
//		ISO_21815_PropulsionActionEventData(RPY_EmergencyStopConfirm, GenericEventData);
//		App_EventUpdateData(EV_Confirm_Emergency_Stop, GenericEventData);
//	}
//	// ---- No message confirmation status received ----
//	else
//	{
//		App_EventClear(EV_Confirm_Emergency_Stop);
//	}
//
//	// ---- Request specific message confirmation status ----
//	if (ISO_21815_CheckPropulsionActionConfirm(RPY_ControlledStopConfirm))
//	{
//		App_EventSet(EV_Confirm_Controlled_Stop);
//		ISO_21815_PropulsionActionEventData(RPY_ControlledStopConfirm, GenericEventData);
//		App_EventUpdateData(EV_Confirm_Controlled_Stop, GenericEventData);
//	}
//	// ---- No message confirmation status received ----
//	else
//	{
//		App_EventClear(EV_Confirm_Controlled_Stop);
//	}
//
//	// ---- Request specific message confirmation status ----
//	if (ISO_21815_CheckPropulsionActionConfirm(RPY_SlowDownConfirm))
//	{
//		App_EventSet(EV_Confirm_SlowDown);
//		ISO_21815_PropulsionActionEventData(RPY_SlowDownConfirm, GenericEventData);
//		App_EventUpdateData(EV_Confirm_SlowDown, GenericEventData);
//	}
//	// ---- No message confirmation status received ----
//	else
//	{
//		App_EventClear(EV_Confirm_SlowDown);
//	}
//
//	// ---- Request specific message confirmation status ----
//	if (ISO_21815_CheckPropulsionActionConfirm(RPY_BypassConfirm))
//	{
//		App_EventSet(EV_Confirm_Bypass);
//		ISO_21815_PropulsionActionEventData(RPY_BypassConfirm, GenericEventData);
//		App_EventUpdateData(EV_Confirm_Bypass, GenericEventData);
//	}
//	// ---- No message confirmation status received ----
//	else
//	{
//		App_EventClear(EV_Confirm_Bypass);
//	}
//
//	// ---- Request specific message confirmation status ----
//	if (ISO_21815_CheckPropulsionActionConfirm(RPY_ApplySetPointConfirm))
//	{
//		App_EventSet(EV_Confirm_ApplySetPoint);
//		ISO_21815_PropulsionActionEventData(RPY_ApplySetPointConfirm, GenericEventData);
//		App_EventUpdateData(EV_Confirm_ApplySetPoint, GenericEventData);
//	}
//	// ---- No message confirmation status received ----
//	else
//	{
//		App_EventClear(EV_Confirm_ApplySetPoint);
//	}
//
//	// ---- Request specific message confirmation status ----
//	if (ISO_21815_CheckPropulsionActionConfirm(RPY_StandDownConfirm))
//	{
//		App_EventSet(EV_Confirm_StandDown);
//		ISO_21815_PropulsionActionEventData(RPY_StandDownConfirm, GenericEventData);
//		App_EventUpdateData(EV_Confirm_StandDown, GenericEventData);
//	}
//	// ---- No message confirmation status received ----
//	else
//	{
//		App_EventClear(EV_Confirm_StandDown);
//	}
//
//	// ---- Request Motion Inhibit Confirm message confirmation status ----
//	if (ISO_21815_CheckPropulsionMotionInhibitConfirm())
//	{
//		App_EventSet(EV_Confirm_Motion_Inhibit);
//	}
//	// ---- No message confirmation status received ----
//	else
//	{
//		App_EventClear(EV_Confirm_Motion_Inhibit);
//	}
//
//
//	if (ISO_21815_CheckNegotationComplete())
//	{
//		App_EventSet(EV_Negotiation_Complete_01);
//	}
//	else
//	{
//		App_EventSet(EV_Negotiation_Incomplete);
//	}
//	/*J1939 Events*/
//	if(Local_Params[Local_J1939_Enable].ParamCURRENT == 1)
//	{
//		//Check global connection state
//		if(!APP_CAN_J1939.Connected)
//		{
//			sprintf(System_Info, "J1939 Communication Failure ");
//			App_EventSet(EV_J1939_Failure);
//		}
//		else
//		{
//			App_EventClear(EV_J1939_Failure);
//
//			if(Own_Vehicle[Engine_Revolutions].Data_CURRENT > 500)
//			{
//				if((Local_Params[Local_J1939_Coolant_Temp_Enable].ParamCURRENT == 1) || (Local_Params[Local_J1939_Coolant_Pres_Enable].ParamCURRENT == 1))
//				{
//					if((Own_Vehicle[Coolant_Temperature].Data_Status != Param_OK) && (Local_Params[Local_J1939_Coolant_Temp_Enable].ParamCURRENT == 1))
//					{
//						//EventList[EV_J1939_Coolant_Error].EventData = App_ReturnErrorMsg (Coolant_Temperature);
//						memcpy(EventList[EV_J1939_Coolant_TempHigh].EventData,App_ReturnErrorMsg (Coolant_Temperature),8);
//
//						App_EventSet(EV_J1939_Coolant_TempHigh);
//					}
//					else if((Own_Vehicle[Coolant_Pressure].Data_Status != Param_OK) && (Local_Params[Local_J1939_Coolant_Pres_Enable].ParamCURRENT == 1))
//					{
//						//EventList[EV_J1939_Coolant_Error].EventData = App_ReturnErrorMsg (Coolant_Pressure);
//						memcpy(EventList[EV_J1939_Coolant_PresHigh].EventData,App_ReturnErrorMsg (Coolant_Pressure),8);
//
//						App_EventSet(EV_J1939_Coolant_PresHigh);
//					}
//					else
//						App_EventClear(EV_J1939_Coolant_PresOK);
//				}
//
//				if((Local_Params[Local_J1939_Oil_Temp_Enable].ParamCURRENT == 1) || (Local_Params[Local_J1939_Oil_Pres_Enable].ParamCURRENT == 1))
//				{
//					if((Own_Vehicle[Oil_Temperature].Data_Status != Param_OK) && (Local_Params[Local_J1939_Oil_Temp_Enable].ParamCURRENT == 1))
//					{
//						//EventList[EV_J1939_Oil_Error].EventData = App_ReturnErrorMsg (Oil_Temperature);
//						memcpy(EventList[EV_J1939_Oil_TempHigh].EventData,App_ReturnErrorMsg (Oil_Temperature),8);
//
//						App_EventSet(EV_J1939_Oil_TempHigh);
//					}
//					else if((Own_Vehicle[Oil_Pressure].Data_Status != Param_OK) && (Local_Params[Local_J1939_Oil_Pres_Enable].ParamCURRENT == 1))
//					{
//						//EventList[EV_J1939_Oil_Error].EventData = App_ReturnErrorMsg (Oil_Pressure);
//						memcpy(EventList[EV_J1939_Oil_PresHigh].EventData,App_ReturnErrorMsg (Oil_Pressure),8);
//
//						App_EventSet(EV_J1939_Oil_PresHigh);
//					}
//					else
//						App_EventClear(EV_J1939_Oil_PresOK);
//
//				}
//
//				if(Local_Params[Local_J1939_Fuel_Temp_Enable].ParamCURRENT == 1)
//				{
//					if(Own_Vehicle[Fuel_Temperature].Data_Status != Param_OK)
//					{
//						//EventList[EV_J1939_Fuel_Error].EventData = App_ReturnErrorMsg (Fuel_Temperature);
//						memcpy(EventList[EV_J1939_Fuel_Error].EventData,App_ReturnErrorMsg (Fuel_Temperature),8);
//
//						App_EventSet(EV_J1939_Fuel_Error);
//					}
//					else
//						App_EventClear(EV_J1939_Fuel_Error);
//				}
//
//				if(Local_Params[Local_J1939_Engine_Rev_Enable].ParamCURRENT == 1)
//				{
//					if(Own_Vehicle[Engine_Revolutions].Data_Status != Param_OK)
//					{
//						//EventList[EV_J1939_Rev_Error].EventData = App_ReturnErrorMsg (Engine_Revolutions);
//						memcpy(EventList[EV_J1939_Rev_Error].EventData,App_ReturnErrorMsg (Engine_Revolutions),8);
//
//						App_EventSet(EV_J1939_Rev_Error);
//					}
//					else
//						App_EventClear(EV_J1939_Rev_Error);
//				}
//			}
//		}
//	}
//
//
//
//	/*CAS ACK Event*/
//	if((EventList[EV_User_ACK_CAS].ACKRequired) && (!EventList[EV_User_ACK_CAS].EventLogged))
//	{
//		App_EventSet(EV_User_ACK_CAS);
//	}
//	else if(EventList[EV_User_ACK_CAS].EventLogged)
//	{
//		EventList[EV_User_ACK_CAS].ACKRequired = false;
//		App_EventClear(EV_User_ACK_CAS);
//	}
//	else
//	{
//		App_EventClear(EV_User_ACK_CAS);
//	}

}


