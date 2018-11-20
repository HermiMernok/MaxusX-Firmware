/*
 * App_Threats.h
 *
 *  Created on: Jul 9, 2016
 *      Author: Jaco-PC
 */

#ifndef APP_THREATS_H_
#define APP_THREATS_H_

#include "Global_Variables.h"
//#include "App_Geofence.h"
//#include "J1939_Interface.h"

//#define Threat_Size				128
#define Threat_Size				50
#define MaxEventThreat			5

#define Threat_LastSeen			5

#define Seconds					1000
#define	Minutes					Seconds*60
#define Hours					Minutes*60

typedef enum
{
	Front_Tag_Dir				= 0,
	FrontRight_Tag_Dir			= 45,
	FrontLeft_Tag_Dir			= 315,

	Rear_Tag_Dir				= 180,
	RearRight_Tag_Dir			= 135,
	RearLeft_Tag_Dir			= 225,

	Left_Tag_Dir				= 270,
	Right_Tag_Dir				= 90,

}Tag_Directions;

typedef enum
{
	Threat_Sector_None			= 0,
	Threat_Sector_01			= 1,
	Threat_Sector_02			= 2,
	Threat_Sector_03			= 3,
	Threat_Sector_04			= 4,
	Threat_Sector_05			= 5,
	Threat_Sector_06			= 6,
	Threat_Sector_07			= 7,
	Threat_Sector_08			= 8,
	Threat_Sector_09			= 9,
	Threat_Sector_10			= 10,
	Threat_Sector_11			= 11,
	Threat_Sector_12			= 12
} Threat_Sector;

typedef enum
{
	GPS_Only_System         = 0,
	Single_Tag_System		= 1,
	Two_Tag_System			= 2,
	Four_Tag_System			= 4

} Tag_System;

typedef enum
{
	PulseRF_Tag_SID				= 50,
	Front_Tag_SID				= 12,
	Rear_Tag_SID				= 6,
	Left_Tag_SID				= 9,
	Right_Tag_SID				= 3,
	Global_Tag_SID				= 0

} Tag_SID;

typedef enum
{
	Front_Tag				= 0,
	Rear_Tag				= 1,
	Left_Tag				= 2,
	Right_Tag				= 3

} Tag_Identifiers;

typedef struct _Local_Tag
{

	uint8_t	 	Own_Tag_SID;		//SID of the Owned Tag
	int8_t		Own_Tag_RSSI;		//Seen LF RSSI Value of the Owned Tag

}Local_Tag;

typedef struct _Position
{

	//uint16_t	Direction;		//Dominant SID of the tag detecting the threat, in degrees
	uint16_t	Sector;
	uint8_t	 	Zone;			//CAS zone
	uint16_t	Width;			//Spread of the detection
	uint16_t	Distance;		//Distance of the detection
	uint8_t		kind;			//Kind of technology used for this position

	uint16_t	DistanceCritical;
	uint16_t	DistanceWarning;
	uint16_t	DistancePresence;

}Position;

typedef struct _Threat
{
	uint32_t		Threat_PrimaryID;					//UID of the transmitter that detects the threat
	uint16_t		Threat_SecondaryID;					//VID of the system that detects the threat

	uint8_t			Threat_Tech;						//Technology that threat was detected on i.e. Pulse, Ranging. . .
	uint8_t 		Threat_Group;						//
	uint8_t			Threat_Type;						//Type of threat i.e. Dump Truck or Pedestrian

	int32_t 		Threat_Longitude;					// Unit : decimal degrees, Scaling: 10^(-7)
	int32_t 		Threat_Latitude;					// Unit : decimal degrees, Scaling: 10^(-7)

	uint32_t 		Threat_HorizontalAccuracy;			// Unit : millimeters, Scaling: -
//	uint32_t 		Threat_VerticalAccuracy;			// Unit : millimeters, Scaling: -

	int32_t 		Threat_Speed;						// Unit : millimeters/second, Scaling: -
	int32_t 		Threat_HeadingVehicle;				// Unit : degrees, Scaling: 10^(-5)

	uint32_t		TimeStamp;
	// ---- Last seen activity of the threat ----
	uint32_t 		LastSeen;

	// ---- The indicates the action will be set as soon as the time elapsed occurred ----
	uint8_t			ThreatAction1;
	// ---- The indicates the action will be set as soon as the time elapsed occurred ----
	uint8_t			ThreatAction2;
	// ---- The indicates the action will be set as soon as the time elapsed occurred ----
	uint8_t			ThreatAction3;

	Position		Threat_Position;					//Information regarding where the threat is

	char 			Threat_Name[20];					//Threat name if available **Consider using reverse referencing to get the name and string values**

	bool 			ACK_Required;						//Acknowledgment flag if required
	bool			ACK_Requested;						//This shows which threat is active on the screen
	bool			ACK_Received;						//This shows that acknowledgement has been handled by event manager
	bool			Log_Required;						//Does this threat require to be logged?

	bool			Event_Triggered;					//Check this flag to see which threat is currently displayed
	bool			Event_Processed;					//Check this flag to see if threat has been handled

	bool			Threat_OwnTag;						//This threat needs to be treated as an own vehicle tag
	bool			Threat_Excluded;					//This threat is currently excluded from CAS


}Threat;

typedef struct _ACK_Threat
{

	uint32_t	ACK_UID;
	uint8_t		Zone_Prev;

}ACK_Threat;

struct _ThreatManagementCounters
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

} ThreatManagementCounters;

extern Threat ThreatList[Threat_Size];
Threat ThreatEventList[MaxEventThreat];
Threat ThreatEventListTemp[MaxEventThreat];
//extern Zone_Message_Type	Threat_Broadcast;

void Threat_Init(void);

void Vision_Filter_Tags(void);

void Threat_Management (void);
void Threat_RemoveOld (void);
Threat Threat_Clear(Threat ThreatItem);
void Threat_Sort (Threat MasterList[]);
void Threat_SortActions (Threat MasterList[]);
Threat Threat_Add (Pulse_Tag PulseTag);
Threat Threat_Update (Pulse_Tag PulseTag, uint8_t Index);
Position Threat_ParseLF (Pulse_Tag PulseTag);
Position Threat_ParseGPS (Pulse_Tag PulseTag);
uint8_t Threat_DetermineDirection (Pulse_Tag PulseTag);
bool Threat_DetermineUpdate (Position ThreatIndex, Position ThreatPrevious, bool ACK_Status);
uint16_t Threat_DetermineWidth(Pulse_Tag PulseTag);
uint8_t Threat_DetermineZone(int8_t LF_RSSI);
uint8_t Threat_SearchUID(uint32_t UID);
uint8_t Threat_SearchVID(uint16_t VID, uint32_t UID);
bool Threat_AcceptedSearch(Threat Threat_Item);
void Threat_SortAccepted(void);
uint8_t Threat_SortEvents(void);
Threat* Threat_FindNextActive(uint8_t* Index);
uint8_t App_ThreatFilter(uint8_t Restart);
void Threat_HandleActive(uint8_t Index);
void Threat_EventSet(Threat* NewThreat, uint8_t IndexOffset);
void Threat_Warn_Pedestrian(void);
void Threat_Events(void);
Local_Tag* Threat_OwnedTag_Sort (Local_Tag OwnedTags[]);
void App_ThreatResetACK (void);
void Threat_WorkZoneHandler(void);
uint8_t Threat_ReturnSpeedZone(void);
uint8_t Threat_DetermineMostImportantAction (Threat* ActionList);

void Threat_EventSetEnd(Threat* OldThreat, uint8_t IndexOffset);
void Threat_EventResetEnd(uint8_t IndexOffset);

Position Threat_InvalidGPS (void);
uint16_t App_Threat_GetZoneDistance(uint8_t GetZone, int32_t Speed, int8_t Pitch);

bool App_Threat_DetermineUpdate (uint8_t Sector_Now, uint8_t Zone_Now, uint16_t Width_Now, uint8_t SectorPrev, uint8_t Zone_Prev, uint16_t Width_Prev);
bool App_Threat_DetermineScreenUpdate (uint8_t Sector_Now, uint8_t Zone_Now, uint16_t Width_Now, uint8_t Sector_Prev, uint8_t Zone_Prev, uint16_t Width_Prev);
bool App_Threat_GetPDSEventData(uint16_t PDSEventID, uint8_t* DataPointer);
bool App_Threat_GetWorkZoneEventData(uint8_t* DataPointer);

#endif /* APP_THREATS_H_ */
