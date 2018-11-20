/*
 * App_VisionControl.h
 *
 *  Created on: Apr 29, 2016
 *      Author: JacoOlivier
 */

#ifndef APP_VISIONCONTROL_H_
#define APP_VISIONCONTROL_H_

#include "Global_Variables.h"

#define tag_time_since_rf			20
#define	TAG_System_MAX				4
#define LF_Smoothing_Max			20
#define GPS_Smoothing_Max
#define PresentList_Max				100
#define Excluded_OwnTagList_Max		20


struct _ControlCounters
{
	uint8_t 	TagList_Counter;
	uint8_t 	RangerList_Counter;
	uint8_t		PresentList_Counter;
	uint8_t		ThreatList_Counter;
	uint8_t		ExcludedList_Counter;
	uint8_t		ExcludedOwnList_Counter;
	uint8_t		AcceptedList_Counter;
	uint8_t		ActiveList_Counter;
	uint8_t		OwnTag_Counter;
	uint8_t		ExcludedTag_Counter;
	uint8_t		OnScreen_Counter;
	uint8_t		PassTags_Counter;
	uint8_t		UsableTags_Counter;

}ControlCounters;

typedef struct _Usable_Tag
{

	_Transpondert*	Transp;												//Direct reference to the transponder in pulse400 list

	uint32_t		Transp_LastSeen;

	bool			Tag_Verified;										//Flag indicating if this tag is excluded
	bool			Tag_Active;											//Flag indicating if this tag is excluded


}Usable_Tag;

typedef enum
{
	Threat_list		= 0,
	Excluded_list	= 1,
	Accepted_list	= 2

}CAS_Lists;

typedef enum
{
	Type_Low_Speed			= 1,
	Type_High_Speed			= 2,
	Type_Medium_Speed 		= 3,
	Type_Loco				= 4,
	Type_Battery			= 5,
	Type_NoGo				= 6,
	Type_Person				= 7,
	Type_Traffic			= 9,
	Type_Explosive			= 11,
	//Type_Vehicle			= 12,
	Type_Ventdoor			= 13

}Tag_Type;


//externals
extern Pulse_Tag		PresentList[PresentList_Max];
extern Pulse_Tag		Excluded_OwnTagList[Excluded_OwnTagList_Max];
extern _Transpondert*	TagList[PresentList_Max];
extern _Transpondert*	PersonTagList[PresentList_Max];

void Init_VisionControl (void);
void Vision_Filter_Tags (void);
void Ranger_Filter_Tags (void);
void Vision_Sort_VLF (_Transpondert* RF_Tags[]);
bool Vision_Tag_Inspect (_Transpondert* Tag);
void Vision_Threat_SM (_Transpondert* Tags[]);
void Vision_Update_LF (_Transpondert* Tag, uint8_t Index);

uint8_t Vision_FindInPresent (_Transpondert* Tag);
uint8_t Vision_FindInExcludedOwn (_Transpondert* Tag);

void Vision_PulseTag_Filter (void);
bool Vision_FindOwnTags (_Transpondert* Tag);
void Vision_PulseTag_Sort (void);
void Vision_MultiTag_Handler (Pulse_Tag List[]);

void Vision_Clear_PulseTag(uint8_t Index);
void Vision_Clear_ExcludedOwnTag(uint8_t Index);

void Vision_RF_Status (void);
bool Vision_FilterOwnTags (_Transpondert* Tag);
LF_message_type Vision_LFVerify (LF_message_type LF);
uint8_t LF_ReturnHighest (uint8_t RSSI[]);
void Vision_Update_RF (_Transpondert* Tag, uint8_t Index);
uint8_t RF_ReturnHighestRSSI (RF_message_type RF_Data[]);
uint32_t RF_ReturnHighestTime (RF_message_type RF_Data[]);
uint16_t Ranger_Return_Distance (uint16_t VID);
void Tag_Test_Filter (void);
uint8_t Vision_FindVID (uint16_t VID);
void Vision_Update_GPS (_Transpondert* Tag, uint8_t Index);
uint16_t GPS_ReturnSmallestDist (uint16_t GPS_Data[]);
void Vision_Compare_Tags (void);
uint8_t Vision_Find_EntryTag (uint32_t UID);
void Vision_Recycle_EntryTag (void);
void PulseTag_Actions(void);


#endif /* APP_VISIONCONTROL_H_ */
