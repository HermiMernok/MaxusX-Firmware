/*
 * VisionModules.h
 *
 *  Created on: 04 September
 */

#ifndef APP_VISIONMODULES_H_
#define APP_VISIONMODULES_H_

#include "LF_APL.h"
#include "Transponders.h"
#include "Global_Variables.h"

#define LF_Smoothing_Max			20
#define	TAG_System_MAX				4

#define PresentList_Max				100
#define Excluded_OwnTagList_Max		20

extern UART_HandleTypeDef huartx[];


typedef enum
{
	Zone_None		= 0,
	Presence		= 1,
	Warning			= 2,
	Critical		= 3
} PDS_Zones;

typedef struct RF_message_type
{
    uint8_t RSSI;
    uint32_t last_RF;
} RF_message_type;

typedef struct _Pulse_Tag
{
	_Transpondert*	Transp;												//Direct reference to the transponder in pulse400 list

	uint32_t		Tag_LastSeen;										// Last Time Stamp
	uint32_t		Tag_FirstSeen;										// First Seen Time

	// ---- The indicates the action will be set as soon as the time elapsed occurred ----
	uint8_t			PulseTagAction1;

	// ---- The indicates the action will be set as soon as the time elapsed occurred ----
	uint8_t			PulseTagAction2;

	// ---- The indicates the action will be set as soon as the time elapsed occurred ----
	uint8_t			PulseTagAction3;

	// ---- The time delays for the actions ----
	uint32_t		PulseTagActionTime1_2;
	uint32_t		PulseTagActionTime2_3;

	LF_message_type LF_History[TAG_System_MAX];							//Latest LF Data

	uint8_t 		RSSI_Archive[TAG_System_MAX][LF_Smoothing_Max];		//2-D Array containing list of history RSSI Values for each transmitter on vehicle

	RF_message_type	RF_Archive[20];						//Archive of RF RSSI values
	uint8_t			RF_Count;											//Counter used to keep track of RF RSSI_Archive positions

	uint8_t			Archive_Count[TAG_System_MAX];						//Counter used to keep track of LF RSSI_Archive positions

	bool			Tag_Excluded;										//Flag indicating if this tag is excluded
	bool			Tag_Owned;											//Flag indicating if this tag is part of the local vehicle
	bool			Active;												//Flag indicating tag status
	bool			FarField;											//Flag indicating if this tag is seen only over RF
	bool			Ranger;

}Pulse_Tag;

void App_VisionModules_Process(void);
void System_Filter_Control(void);

#endif /* CONTROL_APP_VISIONMODULES_H_ */
