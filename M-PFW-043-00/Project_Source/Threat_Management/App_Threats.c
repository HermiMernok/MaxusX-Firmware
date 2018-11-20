/*
 * App_Threats.c
 *
 *  Created on: Jul 9, 2016
 *      Author: Jaco-PC
 */

#include "App_Threats.h"
#include "App_EventManager.h"

Threat				ThreatList[Threat_Size];
Threat				WorkZoneList[10];
ACK_Threat			ACK_Threats[50];
Threat*				Active_Threat;
char 				ThreatInfo[50];

//Externals
extern Event		EventList[];
extern Pulse_Tag	PresentList[];
extern Pulse_Tag	Excluded_OwnTagList[];

Zone_Message_Type	Threat_Broadcast;
uint8_t				ACK_Data[8] = {0};

#define (Local_Params[Local_Ublox_Enable].ParamCURRENT) 	1

/*-----------------------------------------
 *Function name and description
 *---------
 * Initialise All Threats
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

void Threat_Init(void)
{
	for(uint8_t i = 0; i < Threat_Size; i++)
	{
		ThreatList[i].ACK_Received = false;
		ThreatList[i].ACK_Requested = false;
		ThreatList[i].ACK_Required = false;
		ThreatList[i].Event_Processed = false;
		ThreatList[i].Event_Triggered = false;
		ThreatList[i].Log_Required = false;
		ThreatList[i].Threat_Excluded = false;
		ThreatList[i].Threat_OwnTag = false;

		memset(ThreatList[i].Threat_Name,0,20);

//		ThreatList[i].Threat_Position.Direction = 0;
		ThreatList[i].Threat_Position.Width = 0;
		ThreatList[i].Threat_Position.Zone = 0;
		ThreatList[i].Threat_PrimaryID = 0;
		ThreatList[i].Threat_SecondaryID = 0;
		ThreatList[i].Threat_Tech = 0;
		ThreatList[i].Threat_Type = 0;
		ThreatList[i].TimeStamp = 0;
		ThreatList[i].LastSeen = 0;
		ThreatList[i].ThreatAction1 = Act_None;
		ThreatList[i].ThreatAction2 = Act_None;
		ThreatList[i].ThreatAction3 = Act_None;
	}

}

/*-----------------------------------------
 *Function name and description
 *---------
 *Filter Pulse400 reader taglist for
 *tags seen by RF
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void Vision_Filter_Tags(void)
{
	_Transpondert* Tag_Pulse;

	int	Restart = 0;
	bool first_entery = true;

	ControlCounters.TagList_Counter = 0;

	//Load all PULSE tags into tag list
	while((Tag_Pulse != 0) || (first_entery))
	{
		first_entery = false;

		Tag_Pulse = transp_filter(Restart,0xFFFF,Local_Params[Local_LastRF].ParamCURRENT,0,0,0);
		Restart = 0xFF;

		if((Tag_Pulse->rssi > Local_Params[Local_Threshold_RF].ParamCURRENT) && (Tag_Pulse != NULL) && (Tag_Pulse->UID != 0xFFFF))
		{
			//Only allow tags of kind pulse or pulse_gps in the tag lists
			if((Tag_Pulse->kind == Pulse) || (Tag_Pulse->kind == Pulse_GPS))
			{

				//				if(((Tag_Pulse->VehicleID != 0) && (Tag_Pulse->type == Person)))
				//				{
				//					clear_transp(Tag_Pulse);
				//				}

				switch(Local_Params[Local_Commander101_Application].ParamCURRENT)
				{
				case App_Railbound_CAS:
				case App_Trackless_CAS:

//					if((check_bit(Tag_Pulse->status, 6)) || (Tag_Pulse->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT))
//					{
//						Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter] = Tag_Pulse;
//						ControlCounters.ExcludedOwnList_Counter++;
//					}
//					else
//					{
						TagList[ControlCounters.TagList_Counter] = Tag_Pulse;
						ControlCounters.TagList_Counter++;
//					}

					break;

				case App_Tag_TestStation:

					if ((Tag_Pulse->LF.RSSI > Local_Params[Local_Threshold_LF].ParamCURRENT) && (Tag_Pulse->LF.VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT) && (time_since(Tag_Pulse->LF.last_LF)) < ((uint8_t)Local_Params[Local_LastLF].ParamCURRENT * Seconds) && (Tag_Pulse->type == Person))
					{
						TagList[ControlCounters.TagList_Counter] = Tag_Pulse;
						ControlCounters.TagList_Counter++;
					}

					break;

				default:
					break;
				}
			}
		}
	}


//	Vision_Compare_Tags ();

}

/*-----------------------------------------
 *Function name and description
 *---------
 * Management of all types of tags added to
 * a standard threat structure
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

void Threat_Management (void)
{
	// ---- Create temporary values for identifying the steps needed ----
	uint8_t	Index = 0xFF, Override = 0xFF;

	Threat temp;

	// ---- Clear counters of the excluded and own tags ----
	ThreatManagementCounters.OwnTag_Counter = 0;
	ThreatManagementCounters.ExcludedTag_Counter = 0;

	// ---- Loop through the present list to compile threat list ----
	for(uint8_t i = 0; i < ThreatManagementCounters.PresentList_Counter; i++)
	{
		// ---- First see if tag is not already in the threat list ----
		Index = Threat_SearchUID(PresentList[i].Transp->UID);

		// ---- Use this to override an existing threat with new information from a multitag threat ----
		Override = Threat_SearchVID(PresentList[i].Transp->VehicleID, PresentList[i].Transp->UID);

		if((Index == 0xFF) && (Override == 0xFF))
		{

			// ---- Tag not in list so add it to the list ----
			ThreatList[ThreatManagementCounters.ThreatList_Counter] = Threat_Add(PresentList[i]);

			// ---- Removed V8 - Not used any more
			//Check if this threat is an owned tag
//			if(PresentList[i].Tag_Owned)
//			{
//				ThreatList[ThreatManagementCounters.ThreatList_Counter].Threat_OwnTag = true;
//				ThreatManagementCounters.OwnTag_Counter++;
//			}
//			else
//				ThreatList[ThreatManagementCounters.ThreatList_Counter].Threat_OwnTag = false;
//
//			//check if this threat is excluded from CAS
//			if(check_bit(PresentList[i].Transp->status, 6))
//			{
//				ThreatList[ThreatManagementCounters.ThreatList_Counter].Threat_Excluded = true;
//				ThreatManagementCounters.ExcludedTag_Counter++;
//			}
//			else
//				ThreatList[ThreatManagementCounters.ThreatList_Counter].Threat_Excluded = false;

			// ---- Increment threat list counter ----
			ThreatManagementCounters.ThreatList_Counter++;
		}
		else
		{
			// ---- First check if this tag`s VID is already in the list ----
			if(Override != 0xFF)
			{
				// ---- Create a temporary threat of the multitag threat ----
				temp = Threat_Add(PresentList[i]);

				// ---- If the temporary threat zone is more critical than listed threat ----
				if(temp.Threat_Position.Zone > ThreatList[Override].Threat_Position.Zone)
				{
					Index = Override;
					Threat_Clear(ThreatList[Index]);
					ThreatList[Index] = temp;
				}
				// ---- If the temporary threat zone is the same than listed threat ----
				else if((temp.Threat_Position.Zone == ThreatList[Index].Threat_Position.Zone))
				{
					// ---- If the accuracy is better than the stored value ----
					if(temp.Threat_Position.Width < ThreatList[Index].Threat_Position.Width)
					{
						Index = Override;
						Threat_Clear(ThreatList[Index]);
						ThreatList[Index] = temp;
					}
				}
			}
			else
			{
				ThreatList[Index] = Threat_Update(PresentList[i], Index);
			}
			// ---- Removed V8 - Not used any more
//			//Check if this threat is an owned tag
//			if(PresentList[i].Tag_Owned)
//			{
//				ThreatList[Index].Threat_OwnTag = true;
//				ThreatManagementCounters.OwnTag_Counter++;
//			}
//			else
//				ThreatList[Index].Threat_OwnTag = false;
//
//			//check if this threat is excluded from CAS
//			if(check_bit(PresentList[i].Transp->status, 6))
//			{
//				ThreatList[Index].Threat_Excluded = true;
//				ThreatManagementCounters.ExcludedTag_Counter++;
//			}
//			else
//				ThreatList[Index].Threat_Excluded = false;
		}
	}

	// ---- Loop through the excluded and own tag list to count ----
	for (uint8_t i = 0; i < ThreatManagementCounters.ExcludedOwnList_Counter; i++)
	{
		// ---- If the fag is set to be a own tag ----
		if(Excluded_OwnTagList[i].Tag_Owned)
		{
			ThreatManagementCounters.OwnTag_Counter++;
		}

		// ---- If the fag is set to be a excluded tag ----
		if(Excluded_OwnTagList[i].Tag_Excluded)
		{
			ThreatManagementCounters.ExcludedTag_Counter++;
		}
	}

	// ---- Remove old entries ----
	Threat_RemoveOld();

	// ---- Update the pointer reference of the active threat ----
	Active_Threat = &ThreatList[0];
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function sorts the master threat list based
 * on the zones as well as last seen time stamps
 *
 *
 *Inputs:
 *---------
 * Old Threat
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void Threat_RemoveOld(void)
{
	uint8_t Removed = 0;
	uint32_t Time = 0;

	// ---- Loop through the threat list to see if the index is still valid or not ----
	for(uint8_t i = 0; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{
		// ---- Get time stamp of the threat ----
		Time = time_since(ThreatList[i].LastSeen);

		// ---- Check if time stamp is invalid ----
		if (Time > Threat_LastSeen*Seconds)
		{
			ThreatList[i] = Threat_Clear(ThreatList[i]);
			Removed++;
		}
	}

	// ---- Sort the list based on zones and last seen values ----
	Threat_Sort(ThreatList);

	// ---- Sort the list based on actions ----
	Threat_SortActions(ThreatList);

	// ---- Decrement list counter by amount of items removed ----
	ThreatManagementCounters.ThreatList_Counter -= Removed;

}

Threat Threat_Clear(Threat ThreatItem)
{
	// ---- Clear type ----
	ThreatItem.Threat_Type = 0;

	// ---- Clear technology ----
	ThreatItem.Threat_Tech = 0;

	// ---- Clear width ----
	ThreatItem.Threat_Position.Width = 0;

	// ---- Clear zone ----
	ThreatItem.Threat_Position.Zone = 0;

	// ---- Clear distance ----
	ThreatItem.Threat_Position.Distance = 0;

	// ---- Clear name ----
	memset(&ThreatItem.Threat_Name[0], 0, sizeof(ThreatItem.Threat_Name));

	// ---- Clear primaryID ----
	ThreatItem.Threat_PrimaryID = 0;

	// ---- Clear secondaryID ----
	ThreatItem.Threat_SecondaryID = 0;

	// ---- Clear time stamp ----
	ThreatItem.TimeStamp = 0;

	// ---- Clear last seen ----
	ThreatItem.LastSeen = 0;

	// ---- Clear booleans flags ----
	ThreatItem.ACK_Received 	= false;
	ThreatItem.ACK_Requested 	= false;
	ThreatItem.ACK_Required 	= false;
	ThreatItem.Log_Required 	= false;
	ThreatItem.Threat_Excluded 	= false;
	ThreatItem.Threat_OwnTag 	= false;
	ThreatItem.Event_Triggered 	= false;

	// ---- Clear threat actions -----
	ThreatItem.ThreatAction1 = Act_None;
	ThreatItem.ThreatAction2 = Act_None;
	ThreatItem.ThreatAction3 = Act_None;

	// ---- If the threat event is processed clear flag ----
	if(ThreatItem.Event_Processed)
	{
		ThreatItem.Event_Processed = false;
		ThreatManagementCounters.AcceptedList_Counter--;
	}
	else
	{
		ThreatItem.Event_Processed = false;
	}

	return ThreatItem;
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function sorts the master threat list based
 * on the zones as well as putting pedestrians above
 * other tag types
 *
 *
 *Inputs:
 *---------
 * Master Threat List
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void Threat_Sort (Threat MasterList[])
{

	uint8_t i, pass;

	Threat hold;

	for(pass = 0; pass < ThreatManagementCounters.ThreatList_Counter; pass++)
	{

		for(i = 0; i < (ThreatManagementCounters.ThreatList_Counter - 1); i++)
		{
			if((MasterList[i].Threat_Position.Zone < MasterList[i + 1].Threat_Position.Zone)) //First level look for zone priority
			{
				hold = MasterList[i];

				MasterList[i] = MasterList[i + 1];

				MasterList[i + 1] = hold;
			}
			else if((MasterList[i].Threat_Position.Zone) == (MasterList[i + 1].Threat_Position.Zone))
			{
				if((MasterList[i].Threat_Type != Person) && (MasterList[i + 1].Threat_Type == Person))	//Second level look for tag type priority
				{
					hold = MasterList[i];

					MasterList[i] = MasterList[i + 1];

					MasterList[i + 1] = hold;
				}
				//				else if(MasterList[i].Threat_Position.Width < MasterList[i + 1].Threat_Position.Width)	//Third level look for width priority
				//				{
				//					hold = MasterList[i];
				//
				//					MasterList[i] = MasterList[i + 1];
				//
				//					MasterList[i + 1] = hold;
				//				}

			}
		}
	}
}

void Threat_SortActions (Threat MasterList[])
{
	uint8_t i, pass;

	Threat hold;

	for(pass = 0; pass < ThreatManagementCounters.ThreatList_Counter; pass++)
	{
		for(i = 0; i < (ThreatManagementCounters.ThreatList_Counter - 1); i++)
		{
			if (Threat_DetermineMostImportantAction(&MasterList[i]) < Threat_DetermineMostImportantAction(&MasterList[i + 1]))
			{
				hold = MasterList[i];

				MasterList[i] = MasterList[i + 1];

				MasterList[i + 1] = hold;
			}
		}
	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function returns the most important action
 * from the pointer to a threat recieved
 *
 *Inputs:
 *---------
 * Pulse Tag
 *
 *Outputs:
 *---------
 * boolean flag
 *-----------------------------------------*/
uint8_t Threat_DetermineMostImportantAction (Threat *ActionList)
{
	// ---- Create temporarily variable to compare the actions of the threat ----
	uint8_t Action = 0;

	//	---- Check if action 1 has greater priority ----
	if (ActionList->ThreatAction1 > Action)
	{
		Action = ActionList->ThreatAction1;
	}

	//	---- Check if action 2 has greater priority ----
	if (ActionList->ThreatAction2 > Action)
	{
		Action = ActionList->ThreatAction2;
	}

	//	---- Check if action 3 has greater priority ----
	if (ActionList->ThreatAction3 > Action)
	{
		Action = ActionList->ThreatAction3;
	}

	//	---- Return most important action ----
	return Action;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function adds a pulse tag to the
 * threat list
 *
 *Inputs:
 *---------
 * Pulse Tag
 *
 *Outputs:
 *---------
 * boolean flag
 *-----------------------------------------*/
Threat Threat_Add (Pulse_Tag PulseTag)
{
	Threat ThreatTag;

	char* Tag_Name;

	Tag_Name = &PulseTag.Transp->name[0];

	// ---- Copy the name of the detected threat ----
	memset(&ThreatTag.Threat_Name[0], 0 ,20);
	memcpy(&ThreatTag.Threat_Name[0],Tag_Name,20);

	// ---- Get the primary ID of the detected threat ----
	ThreatTag.Threat_PrimaryID = PulseTag.Transp->UID;

	// ---- Get the secondary ID of the detected threat ----
	ThreatTag.Threat_SecondaryID = PulseTag.Transp->VehicleID;

	// ---- Get the type of the detected threat ----
	ThreatTag.Threat_Type = PulseTag.Transp->type;

	// ---- Get the name of the detected threat ----
	ThreatTag.Threat_Tech = PulseTag.Transp->kind;

	// ---- Determine the position of the detected threat (Low-Frequency) ----
	if(PulseTag.Transp->kind == Pulse)
	{
		// ---- Parse the received LF information ----
		ThreatTag.Threat_Position = Threat_ParseLF(PulseTag);
	}
	// ---- Determine the position of the detected threat (Low-Frequency and GPS) ----
	else if(PulseTag.Transp->kind == Pulse_GPS)
	{
		bool GPS_Capable;
		Position LF_Data;
		Position GPS_Data;

		// ---- If GPS module is enabled on the master device ----
		if (Local_Params[Local_Ublox_Enable].ParamCURRENT == 1)
		{
			GPS_Capable = true;
		}
		// ---- If GPS module is disabled on the master device ----
		else
		{
			GPS_Capable = false;
		}

		if(GPS_Capable)
		{
//			ThreatTag.Threat_GPSInfo = PulseTag.Transp->GPS_Data;

			// ---- Parse the received LF information ----
			LF_Data = Threat_ParseLF(PulseTag);	//Parse the current LF information

			// ---- Check if received GPS threat has a valid GPS fix -----
			if (App_GPS_Validate(PulseTag.Transp))
			{
				// ---- Parse the current GPS information ----
				GPS_Data = Threat_ParseGPS(PulseTag);
			}
			else
			{
				GPS_Data.Sector = Threat_Sector_12;
				GPS_Data.Distance = 0xFFFF;
				GPS_Data.Width = 360;
				GPS_Data.Zone = Presence;
				ThreatTag.Threat_Latitude = 255;
				ThreatTag.Threat_Longitude = 255;
			}

			if(GPS_Data.Zone != Zone_None)
			{
				//Compare LF and GPS position data
				if(LF_Data.Zone != GPS_Data.Zone)
				{
					if(LF_Data.Zone > GPS_Data.Zone)
						ThreatTag.Threat_Position = LF_Data;
					else
						ThreatTag.Threat_Position = GPS_Data;
				}
				else
				{
					if(LF_Data.Width < GPS_Data.Width)
						ThreatTag.Threat_Position = LF_Data;
					else
						ThreatTag.Threat_Position = GPS_Data;
				}
			}
			else
			{
				ThreatTag.Threat_Position = GPS_Data;
			}
		}
		else
		{
//			memset(&ThreatTag.Threat_GPSInfo, 0, sizeof(ThreatTag.Threat_GPSInfo));
			ThreatTag.Threat_Position = Threat_ParseLF (PulseTag);
		}

	}
	else
	{
		ThreatTag.Threat_Position.Sector = Threat_Sector_12;
		ThreatTag.Threat_Position.Distance = 0xFFFF;
		ThreatTag.Threat_Position.Width = 360;
		ThreatTag.Threat_Position.Zone = Presence;
	}

	/*Added for detecting vehicle tags using RF RSSI when a pulse tag is detected*/
	if ((ThreatTag.Threat_Position.Zone == Presence) && (ThreatTag.Threat_Type != Person) && ThreatTag.Threat_Tech == Pulse)
	{
		if (RF_ReturnHighestRSSI(PulseTag.RF_Archive) > Local_Params[Local_RF_RSSI_Zone].ParamCURRENT)
		{
			ThreatTag.Threat_Position.Zone = Warning;
			ThreatTag.Threat_Position.Width = 360;
		}
	}

	/*Last seen*/
	ThreatTag.LastSeen = time_now();

	/*Time stamp*/
	ThreatTag.TimeStamp = PulseTag.Tag_FirstSeen;

	/*Tag status*/
	ThreatTag.Threat_OwnTag = PulseTag.Tag_Owned;
	ThreatTag.Threat_Excluded = PulseTag.Tag_Excluded;

	/*Flags*/
	ThreatTag.ACK_Received = false;
	ThreatTag.ACK_Requested = false;
	ThreatTag.ACK_Required = false;
	ThreatTag.Event_Processed = false;
	ThreatTag.Event_Triggered = false;
	ThreatTag.Log_Required = false;

	if (ThreatTag.Threat_Position.Zone == Critical)
	{
		ThreatTag.ThreatAction1 = (uint8_t) Local_Params[Local_ThreatCritical_Action1].ParamCURRENT;
	}
	else if (ThreatTag.Threat_Position.Zone == Warning)
	{
		ThreatTag.ThreatAction1 = (uint8_t) Local_Params[Local_ThreatWarning_Action1].ParamCURRENT;
	}
	else if (ThreatTag.Threat_Position.Zone == Presence)
	{
		ThreatTag.ThreatAction1 = (uint8_t) Local_Params[Local_ThreatPresence_Action1].ParamCURRENT;
	}
	else
	{
		ThreatTag.ThreatAction1 = Act_None;
	}

	ThreatTag.ThreatAction2 = Act_None;
	ThreatTag.ThreatAction3 = Act_None;

	ThreatTag.Threat_Latitude = PulseTag.Transp->GPS_Data.Latitude;
	ThreatTag.Threat_Longitude = PulseTag.Transp->GPS_Data.Longitude;

	ThreatTag.Threat_HorizontalAccuracy = PulseTag.Transp->GPS_Data.HorizontalAccuracy;
	ThreatTag.Threat_Speed = PulseTag.Transp->GPS_Data.Speed;
	ThreatTag.Threat_HeadingVehicle = PulseTag.Transp->GPS_Data.HeadingVehicle;

	return ThreatTag;
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function looks if a tag is already present
 * in the threat list
 *
 *
 *Inputs:
 *---------
 * 32-bit UID
 *
 *Outputs:
 *---------
 * boolean flag
 *-----------------------------------------*/

Threat Threat_Update (Pulse_Tag PulseTag, uint8_t Index)
{
	Threat ThreatTag;

	char* Tag_Name;

	Tag_Name = &PulseTag.Transp->name[0];

	// ---- Copy the name of the detected threat ----
	memset(&ThreatTag.Threat_Name[0], 0 ,20);
	memcpy(&ThreatTag.Threat_Name[0],Tag_Name,20); //copy in the event name

	// ---- Get the primary ID of the detected threat ----
	ThreatTag.Threat_PrimaryID = PulseTag.Transp->UID;

	// ---- Get the secondary ID of the detected threat ----
	ThreatTag.Threat_SecondaryID = PulseTag.Transp->VehicleID;

	// ---- Get the type of the detected threat ----
	ThreatTag.Threat_Type = PulseTag.Transp->type;

	// ---- Get the technology of the detected threat ----
	ThreatTag.Threat_Tech = PulseTag.Transp->kind;

	// ---- Determine the position of the detected threat (Low-Frequency) ----
	if(PulseTag.Transp->kind == Pulse)
	{
		ThreatTag.Threat_Position = Threat_ParseLF(PulseTag);
	}
	// ---- Determine the position of the detected threat (Low-Frequency and GPS) ----
	else if (PulseTag.Transp->kind == Pulse_GPS)
	{
		bool GPS_Capable;
		Position LF_Data;
		Position GPS_Data;

		// ---- If GPS module is enabled on the master device ----
		if (Local_Params[Local_Ublox_Enable].ParamCURRENT == 1)
		{
			GPS_Capable = true;
		}
		// ---- If GPS module not enabled on the master device ----
		else
		{
			GPS_Capable = false;
		}

		// ---- Only calculate GPS data if the functionality is enabled on the master device ----
		if (GPS_Capable)
		{
			// ---- Parse the received LF information ----
			LF_Data = Threat_ParseLF(PulseTag);

			// ---- Check if received GPS threat has a valid GPS fix -----
			if (App_GPS_Validate(PulseTag.Transp))
			{
				GPS_Data = Threat_ParseGPS(PulseTag);	//Parse the current GPS information
			}
			// ---- If received GPS threat has no valid GPS fix, set GPS data to presence 360 -----
			else
			{
				GPS_Data = Threat_InvalidGPS();
			}

			if (GPS_Data.Zone != Zone_None)
			{
				//Compare LF and GPS position data
				if (LF_Data.Zone != GPS_Data.Zone)
				{
					if(LF_Data.Zone > GPS_Data.Zone)
						ThreatTag.Threat_Position = LF_Data;
					else
						ThreatTag.Threat_Position = GPS_Data;
				}
				else
				{
					if(LF_Data.Width < GPS_Data.Width)
						ThreatTag.Threat_Position = LF_Data;
					else
						ThreatTag.Threat_Position = GPS_Data;
				}
			}
			else
			{
				ThreatTag.Threat_Position = GPS_Data;
			}
		}
		else
		{
			ThreatTag.Threat_Position = Threat_ParseLF (PulseTag);
		}

	}
	else
	{
		ThreatTag.Threat_Position.Sector = Threat_Sector_12;
		ThreatTag.Threat_Position.Distance = 0xFFFF;
		ThreatTag.Threat_Position.Width = 360;
		ThreatTag.Threat_Position.Zone = Presence;
	}

	/*Added for detecting vehicle tags using RF RSSI when a pulse tag is detected*/
	if((ThreatTag.Threat_Position.Zone == Presence) && (ThreatTag.Threat_Type != Person) && ThreatTag.Threat_Tech == Pulse)
	{
		if (RF_ReturnHighestRSSI(PulseTag.RF_Archive) > Local_Params[Local_RF_RSSI_Zone].ParamCURRENT)
		{
//			ThreatTag.Threat_Position.Direction = Front_Tag;
			ThreatTag.Threat_Position.Zone = Warning;
			ThreatTag.Threat_Position.Width = 360;
		}
	}

	/*Time stamp*/
	ThreatTag.LastSeen = time_now();

	/*Tag status*/
	ThreatTag.Threat_OwnTag = PulseTag.Tag_Owned;
	ThreatTag.Threat_Excluded = PulseTag.Tag_Excluded;

	/*Flags*/
	ThreatTag.ACK_Received = ThreatList[Index].ACK_Received;
	ThreatTag.ACK_Requested = ThreatList[Index].ACK_Requested;
	ThreatTag.ACK_Required = ThreatList[Index].ACK_Required;
	ThreatTag.Event_Processed = ThreatList[Index].Event_Processed;
	ThreatTag.Event_Triggered = ThreatList[Index].Event_Triggered;
	ThreatTag.Log_Required = ThreatList[Index].Log_Required;

	if (ThreatTag.Threat_Position.Zone !=  ThreatList[Index].Threat_Position.Zone)
	{
		ThreatTag.TimeStamp = time_now();
	}
	else
	{
		ThreatTag.TimeStamp = ThreatList[Index].TimeStamp;
	}

	ThreatTag.ThreatAction1 = ThreatList[Index].ThreatAction1;
	ThreatTag.ThreatAction2 = ThreatList[Index].ThreatAction2;
	ThreatTag.ThreatAction3 = ThreatList[Index].ThreatAction3;

	ThreatTag.Threat_Latitude = PulseTag.Transp->GPS_Data.Latitude;
	ThreatTag.Threat_Longitude = PulseTag.Transp->GPS_Data.Longitude;

	ThreatTag.Threat_HorizontalAccuracy = PulseTag.Transp->GPS_Data.HorizontalAccuracy;
	ThreatTag.Threat_Speed = PulseTag.Transp->GPS_Data.Speed;
	ThreatTag.Threat_HeadingVehicle = PulseTag.Transp->GPS_Data.HeadingVehicle;


	//Check if this threat is an accepted threat and if the zone increased
	if(ThreatTag.Event_Processed)
	{
		//check if threat position changed
		if(Threat_DetermineUpdate(ThreatTag.Threat_Position, ThreatList[Index].Threat_Position, ThreatTag.Event_Processed))
		{
			ThreatTag.Event_Processed = false;
			ThreatManagementCounters.AcceptedList_Counter--;
		}
	}

	return ThreatTag;
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function returns the threat`s position based
 * on LF information
 *
 *Inputs:
 *---------
 * Pulse Tag
 *
 *Outputs:
 *---------
 * Position
 *-----------------------------------------*/
Position Threat_ParseLF (Pulse_Tag PulseTag)
{
	Position Threat_Pos;
	uint8_t TagZones[4];
	Local_Tag	OwnVehicleTags[4];

	Threat_Pos.kind = Pulse;

	//Return threat distance
	//Threat_Pos.Distance = Ranger_Return_Distance (PulseTag.Transp->VehicleID);

	// ---- If this tag is seen only over RF ----
	if(PulseTag.FarField)
	{
		Threat_Pos.Sector = Threat_Sector_12;
		Threat_Pos.Width = 360;
		Threat_Pos.Zone = Presence;
		Threat_Pos.Distance = 0xFFFF;

		return Threat_Pos;
	}
	else
	{

		switch (Local_Params[Local_TagCount].ParamCURRENT)
		{
			// ---- In case it is a single tag system ----
			case Single_Tag_System:

				// ---- Update vehicle's tag information ----
				OwnVehicleTags[0].Own_Tag_RSSI = PulseTag.LF_History[Front_Tag].RSSI;
				OwnVehicleTags[0].Own_Tag_SID = Front_Tag_SID;

				// ---- Determine the zone form LF Zone ----
				TagZones[Front_Tag] = Threat_DetermineZone(OwnVehicleTags[0].Own_Tag_RSSI);

				// ---- If information received is from the unit SID 12 ----
				if(OwnVehicleTags[0].Own_Tag_SID == Front_Tag_SID)
				{
					Threat_Pos.Sector = Threat_Sector_12;
					Threat_Pos.Width = 360;
					Threat_Pos.Zone = TagZones[Front_Tag];
					Threat_Pos.Distance = OwnVehicleTags[0].Own_Tag_RSSI;
				}
				// ---- If not form the front tag (useless front tag SID hardcoded) ----
				else
				{
					Threat_Pos.Sector = Threat_Sector_12;
					Threat_Pos.Width = 360;
					Threat_Pos.Zone = Presence;
					Threat_Pos.Distance = 0xFFFF;
				}

				break;

			// ---- In case it is a single tag system ----
			case Two_Tag_System:

				// ---- Update vehicle's tag information ----
				OwnVehicleTags[0].Own_Tag_RSSI = PulseTag.LF_History[Front_Tag].RSSI;
				OwnVehicleTags[0].Own_Tag_SID = Front_Tag_SID;

				OwnVehicleTags[1].Own_Tag_RSSI = PulseTag.LF_History[Rear_Tag].RSSI;
				OwnVehicleTags[1].Own_Tag_SID = Rear_Tag_SID;

				// ---- Implement LF sorting ----
				Threat_OwnedTag_Sort (OwnVehicleTags);

				// ---- Switch between the most information tag (LF) ----
				switch(OwnVehicleTags[0].Own_Tag_SID)
				{
					// ---- If it is the the front tag ----
					case Front_Tag_SID:

						// ----Get zones
						TagZones[Front_Tag] = Threat_DetermineZone(OwnVehicleTags[0].Own_Tag_RSSI);
						TagZones[Rear_Tag] = Threat_DetermineZone(OwnVehicleTags[1].Own_Tag_RSSI);

						//Check if this is a multi-zone threat
						if((OwnVehicleTags[1].Own_Tag_RSSI != 0) && (OwnVehicleTags[1].Own_Tag_SID == Rear_Tag_SID))
						{
							//Check full circle event
							if(TagZones[Front_Tag] == TagZones[Rear_Tag])
							{
								Threat_Pos.Sector = Threat_Sector_12;
								Threat_Pos.Width = 360;
								Threat_Pos.Zone = TagZones[Front_Tag];
		//						Threat_Pos.Direction = Front_Tag_Dir;
								Threat_Pos.Distance = 0xFFFF;
							}
							else
							{
								Threat_Pos.Sector = Threat_Sector_12;
								//Only apply front tag
								Threat_Pos.Width = 180;
								Threat_Pos.Zone = TagZones[Front_Tag];
		//						Threat_Pos.Direction = Front_Tag_Dir;
								Threat_Pos.Distance = OwnVehicleTags[0].Own_Tag_RSSI;
							}

						}
						else
						{
							Threat_Pos.Sector = Threat_Sector_12;
							//Only apply front tag
							Threat_Pos.Width = 360;
							Threat_Pos.Zone = TagZones[Front_Tag];
		//					Threat_Pos.Direction = Front_Tag_Dir;
							Threat_Pos.Distance = OwnVehicleTags[0].Own_Tag_RSSI;
						}

						break;
						// ---- If it is the the front tag ----
					case Rear_Tag_SID:

						//Get zones
						TagZones[Rear_Tag] = Threat_DetermineZone(OwnVehicleTags[0].Own_Tag_RSSI);
						TagZones[Front_Tag] = Threat_DetermineZone(OwnVehicleTags[1].Own_Tag_RSSI);

						//Check if this is a multi-zone threat
						if((OwnVehicleTags[1].Own_Tag_RSSI != 0) && (OwnVehicleTags[1].Own_Tag_SID == Front_Tag_SID))
						{
							//Check full circle event
							if(TagZones[Rear_Tag] == TagZones[Front_Tag])
							{
								Threat_Pos.Sector = Threat_Sector_12;
								Threat_Pos.Width = 360;
								Threat_Pos.Zone = TagZones[Rear_Tag];
		//						Threat_Pos.Direction = Front_Tag_Dir;
								Threat_Pos.Distance = 0xFFFF;
							}
							else
							{
								Threat_Pos.Sector = Threat_Sector_12;
								//Only apply rear tag
								Threat_Pos.Width = 180;
								Threat_Pos.Zone = TagZones[Rear_Tag];
		//						Threat_Pos.Direction = Rear_Tag_Dir;
								Threat_Pos.Distance = OwnVehicleTags[1].Own_Tag_RSSI;
							}

						}
						else
						{
							Threat_Pos.Sector = Threat_Sector_12;
							//Only apply Rear tag
							Threat_Pos.Width = 360;
							Threat_Pos.Zone = TagZones[Rear_Tag];
		//					Threat_Pos.Direction = Rear_Tag_Dir;
							Threat_Pos.Distance = OwnVehicleTags[1].Own_Tag_RSSI;
						}

						break;

			default:
				break;
			}

			break;

			case Four_Tag_System:

				OwnVehicleTags[0].Own_Tag_RSSI = PulseTag.LF_History[Front_Tag].RSSI;
				OwnVehicleTags[0].Own_Tag_SID = Front_Tag_SID;

				OwnVehicleTags[1].Own_Tag_RSSI = PulseTag.LF_History[Rear_Tag].RSSI;
				OwnVehicleTags[1].Own_Tag_SID = Rear_Tag_SID;

				OwnVehicleTags[2].Own_Tag_RSSI = PulseTag.LF_History[Left_Tag].RSSI;
				OwnVehicleTags[2].Own_Tag_SID = Left_Tag_SID;

				OwnVehicleTags[3].Own_Tag_RSSI = PulseTag.LF_History[Right_Tag].RSSI;
				OwnVehicleTags[3].Own_Tag_SID = Right_Tag_SID;

				//Implement LF sorting
				Threat_OwnedTag_Sort (OwnVehicleTags);

				//Determine Tag Zones
				for(uint8_t i = 0; i < 4; i++)
				{
					switch(OwnVehicleTags[i].Own_Tag_SID)
					{
					case Front_Tag_SID:

						TagZones[Front_Tag] = Threat_DetermineZone(OwnVehicleTags[i].Own_Tag_RSSI);
						break;

					case Rear_Tag_SID:

						TagZones[Rear_Tag] = Threat_DetermineZone(OwnVehicleTags[i].Own_Tag_RSSI);
						break;

					case Left_Tag_SID:

						TagZones[Left_Tag] = Threat_DetermineZone(OwnVehicleTags[i].Own_Tag_RSSI);
						break;

					case Right_Tag_SID:

						TagZones[Right_Tag] = Threat_DetermineZone(OwnVehicleTags[i].Own_Tag_RSSI);
						break;

					default:
						break;
					}
				}

				//check for full circle events

				/*FRONT == REAR*/
				if((TagZones[Front_Tag] == TagZones[Rear_Tag]) && (TagZones[Front_Tag] > TagZones[Right_Tag]) && (TagZones[Front_Tag] > TagZones[Left_Tag]))
				{
					//This is a full circle event
//					Threat_Pos.Direction = Front_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_12;
					Threat_Pos.Width = 360;
					Threat_Pos.Zone = TagZones[Front_Tag];
					Threat_Pos.Distance = 0xFFFF;
				}

				/*RIGHT == LEFT*/
				else if((TagZones[Right_Tag] == TagZones[Left_Tag]) && (TagZones[Right_Tag] > TagZones[Front_Tag]) && (TagZones[Right_Tag] > TagZones[Rear_Tag]))
				{
					//This is a full circle event
//					Threat_Pos.Direction = Right_Tag;
					Threat_Pos.Sector = Threat_Sector_03;
					Threat_Pos.Width = 360;
					Threat_Pos.Zone = TagZones[Right_Tag];
					Threat_Pos.Distance = 0xFFFF;
				}

				/*FRONT == REAR == RIGHT == LEFT*/
				else if((TagZones[Front_Tag] == TagZones[Rear_Tag]) && (TagZones[Front_Tag] == TagZones[Left_Tag]) && (TagZones[Front_Tag] == TagZones[Right_Tag]))
				{
					//This is a full circle event
//					Threat_Pos.Direction = Front_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_12;
					Threat_Pos.Width = 360;
					Threat_Pos.Zone = TagZones[Front_Tag];
					Threat_Pos.Distance = 0xFFFF;
				}


				/*FRONT HALF*/
				else if((TagZones[Front_Tag] == TagZones[Right_Tag]) && (TagZones[Front_Tag] == TagZones[Left_Tag]) && (TagZones[Front_Tag] > TagZones[Rear_Tag]))
				{
//					Threat_Pos.Direction = Front_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_12;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Front_Tag];
					Threat_Pos.Distance = OwnVehicleTags[0].Own_Tag_RSSI;
				}

				/*REAR HALF*/
				else if((TagZones[Rear_Tag] == TagZones[Right_Tag]) && (TagZones[Rear_Tag] == TagZones[Left_Tag]) && (TagZones[Rear_Tag] > TagZones[Front_Tag]))
				{
//					Threat_Pos.Direction = Rear_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_06;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Rear_Tag];
					Threat_Pos.Distance = OwnVehicleTags[1].Own_Tag_RSSI;
				}

				/*RIGHT HALF*/
				else if((TagZones[Right_Tag] == TagZones[Front_Tag]) && (TagZones[Right_Tag] == TagZones[Rear_Tag]) && (TagZones[Right_Tag] > TagZones[Left_Tag]))
				{
//					Threat_Pos.Direction = Right_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_03;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Right_Tag];
					Threat_Pos.Distance = OwnVehicleTags[3].Own_Tag_RSSI;
				}
				/*FRONT-RIGHT HALF*/
				else if((TagZones[Right_Tag] == TagZones[Front_Tag]) && (TagZones[Right_Tag] > TagZones[Rear_Tag]) && (TagZones[Right_Tag] > TagZones[Left_Tag]))
				{
//					Threat_Pos.Direction = FrontRight_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_02;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Right_Tag];
					Threat_Pos.Distance = OwnVehicleTags[0].Own_Tag_RSSI;
				}
				/*REAR-RIGHT HALF*/
				else if((TagZones[Right_Tag] == TagZones[Rear_Tag]) && (TagZones[Right_Tag] > TagZones[Front_Tag]) && (TagZones[Right_Tag] > TagZones[Left_Tag]))
				{
//					Threat_Pos.Direction = RearRight_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_04;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Right_Tag];
					Threat_Pos.Distance = OwnVehicleTags[1].Own_Tag_RSSI;
				}
				/*LEFT HALF*/
				else if((TagZones[Left_Tag] == TagZones[Front_Tag]) && (TagZones[Left_Tag] == TagZones[Rear_Tag]) && (TagZones[Left_Tag] > TagZones[Right_Tag]))
				{
//					Threat_Pos.Direction = Left_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_09;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Left_Tag];
					Threat_Pos.Distance = OwnVehicleTags[2].Own_Tag_RSSI;
				}
				/*FRONT-LEFT HALF*/
				else if((TagZones[Left_Tag] == TagZones[Front_Tag]) && (TagZones[Left_Tag] > TagZones[Rear_Tag]) && (TagZones[Left_Tag] > TagZones[Right_Tag]))
				{
//					Threat_Pos.Direction = FrontLeft_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_10;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Left_Tag];
					Threat_Pos.Distance = OwnVehicleTags[0].Own_Tag_RSSI;
				}
				/*REAR-LEFT HALF*/
				else if((TagZones[Left_Tag] == TagZones[Rear_Tag]) && (TagZones[Left_Tag] > TagZones[Front_Tag]) && (TagZones[Left_Tag] > TagZones[Right_Tag]))
				{
//					Threat_Pos.Direction = RearLeft_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_08;
					Threat_Pos.Width = 180;
					Threat_Pos.Zone = TagZones[Left_Tag];
					Threat_Pos.Distance = OwnVehicleTags[1].Own_Tag_RSSI;
				}
				/*FRONT*/
				else if ((TagZones[Front_Tag] > TagZones[Right_Tag]) && (TagZones[Front_Tag] > TagZones[Left_Tag]) && (TagZones[Front_Tag] > TagZones[Rear_Tag]))
				{
//					Threat_Pos.Direction = Front_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_12;
					Threat_Pos.Width = 90;
					Threat_Pos.Zone = TagZones[Front_Tag];
					Threat_Pos.Distance = OwnVehicleTags[0].Own_Tag_RSSI;

				}
				/*REAR*/
				else if((TagZones[Rear_Tag] > TagZones[Right_Tag]) && (TagZones[Rear_Tag] > TagZones[Left_Tag]) && (TagZones[Rear_Tag] > TagZones[Front_Tag]))
				{
//					Threat_Pos.Direction = Rear_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_06;
					Threat_Pos.Width = 90;
					Threat_Pos.Zone = TagZones[Rear_Tag];
					Threat_Pos.Distance = OwnVehicleTags[1].Own_Tag_RSSI;
				}
				/*RIGHT*/
				else if((TagZones[Right_Tag] > TagZones[Left_Tag]) && (TagZones[Right_Tag] > TagZones[Front_Tag]) && (TagZones[Right_Tag] > TagZones[Rear_Tag]))
				{
//					Threat_Pos.Direction = Right_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_03;
					Threat_Pos.Width = 90;
					Threat_Pos.Zone = TagZones[Right_Tag];
					Threat_Pos.Distance = OwnVehicleTags[2].Own_Tag_RSSI;
				}
				/*LEFT*/
				else if((TagZones[Left_Tag] > TagZones[Right_Tag]) && (TagZones[Left_Tag] > TagZones[Front_Tag]) && (TagZones[Left_Tag] > TagZones[Rear_Tag]))
				{
//					Threat_Pos.Direction = Left_Tag_Dir;
					Threat_Pos.Sector = Threat_Sector_09;
					Threat_Pos.Width = 90;
					Threat_Pos.Zone = TagZones[Left_Tag];
					Threat_Pos.Distance = OwnVehicleTags[3].Own_Tag_RSSI;
				}

				break;

			default:

				Threat_Pos.Sector = Threat_Sector_12;
				Threat_Pos.Width = 360;
				Threat_Pos.Zone = Presence;
				Threat_Pos.Distance = 0xFFFF;

				break;

		}

		return Threat_Pos;
	}

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function returns the threat`s position based
 * on GPS information
 *
 *Inputs:
 *---------
 * Pulse Tag
 *
 *Outputs:
 *---------
 * Position
 *-----------------------------------------*/
Position Threat_ParseGPS(Pulse_Tag PulseTag)
{
	Position Threat_Pos;
	double Bearing_Threat, Bearing_Relative, Heading_Vehicle, Safety_Factor;
	uint32_t H_Acc, V_Acc, Own_H_Acc = 0, Own_V_Acc = 0;
	uint16_t Display_Width, Distance_Threat = 0, Acc_Distance = 0;
	uint8_t Display_Width_Error, Safety = 0;

	//Assign Threat kind
	Threat_Pos.kind = Pulse_GPS;

	// ---- Calculate bearing from own vehicle to threat ----
	Bearing_Threat = App_GPS_ReturnBearing(OwnPosition.Own_GPS_Data.Latitude, OwnPosition.Own_GPS_Data.Longitude, PulseTag.Transp->GPS_Data.Latitude, PulseTag.Transp->GPS_Data.Longitude);

	// ---- Check if heading of vehicle is valid ----
	if (OwnPosition.Own_Heading_Valid)
	{
		// ---- Use the vehicle heading ----
		Heading_Vehicle = App_int32ToDouble(OwnPosition.Own_GPS_Data.HeadingVehicle, 5);

		// ----- Invert heading if vehicle is in reverse gear ----
		App_Invert_Heading(&Heading_Vehicle);
	}
	else
	{
		// ---- Indicate that the heading is invalid ----
		Heading_Vehicle = -1;
	}

	// ---- Calculate direct distance from own vehicle to threat ----
	Distance_Threat = (uint16_t)App_GPS_ReturnDistance(OwnPosition.Own_GPS_Data.Latitude, OwnPosition.Own_GPS_Data.Longitude, PulseTag.Transp->GPS_Data.Latitude, PulseTag.Transp->GPS_Data.Longitude);

	// ---- Condition the GPS coordinates by limiting the distance ----
	if (Distance_Threat < 500)
	{
		// ---- Convert threat GPS accuracy into meters ----
		V_Acc = PulseTag.Transp->GPS_Data.VerticalAccuracy / 1000;
		H_Acc = PulseTag.Transp->GPS_Data.HorizontalAccuracy / 1000;

		// ---- Convert vehicle GPS accuracy into meters ----
		Own_H_Acc = OwnPosition.Own_GPS_Data.HorizontalAccuracy / 1000;
		Own_V_Acc = OwnPosition.Own_GPS_Data.VerticalAccuracy / 1000;

		// ---- Apply GPS accuracies to determine worst case distance ----
		if ((H_Acc + Own_H_Acc) < Distance_Threat)
			Acc_Distance = (H_Acc + Own_H_Acc);
		else
			Acc_Distance = 0;

		// ----- Catch the event where a faulty/corrupt coordinate has been placed in threat list ----
		if (Bearing_Threat == -1)
		{
//			Threat_Pos.Direction = Dir_360;
			Threat_Pos.Width = 360;
		}
		else
		{
			// ---- Adjust the bearing with the heading offset from the vehicle ----
			Bearing_Relative = Bearing_Threat - Heading_Vehicle;

			// ---- Check that the trigonometric angle sizes will fit in a circle between 0 and 360 only ----
			while((Bearing_Relative > 360) || (Bearing_Relative < 0))
			{
				// ---- Subtract a circle (degrees) ----
				if(Bearing_Relative > 360)
					Bearing_Relative -= 360;
				// ---- Add a circle (degrees) ----
				else
					Bearing_Relative += 360;
			}

//			// ---- Load double values in 32-bit values for text functions ----
//			Bearing = (uint32_t)Bearing_Threat;
//			Relative = (uint32_t)Bearing_Threat;

			//Update tag direction relative to vehicle heading
//			Threat_Pos.Direction = (uint16_t) Bearing_Relative;

			// ---- Calculate the sector in which to draw the threat ----
			Threat_Pos.Sector = (((uint16_t) Bearing_Relative) / 15) -  (((uint16_t) Bearing_Relative) / 30);

			// ---- Condition the sector calculation for to convert 0 to sector 12 ----
			Threat_Pos.Sector = (Threat_Pos.Sector == 0 ? 12 : Threat_Pos.Sector);

			// ---- Load local parameter values ----
			Display_Width 		= (uint16_t) Local_Params[Local_DispWidth].ParamCURRENT;
			Display_Width_Error = (uint8_t) Local_Params[Local_DispWidth_Error].ParamCURRENT;

//			//Draw threat width as a function of its position accuracy and own position accuracy
//			Threat_Pos.Width = Display_Width  + (H_Acc*Display_Width_Error);

			// ---- Draw threat width as a function of its position accuracy and own position accuracy ----
			Threat_Pos.Width = Display_Width + ((H_Acc / Display_Width_Error) * Display_Width);

			// ---- Condition the calculated width value if larger than 360 ----
			Threat_Pos.Width = (Threat_Pos.Width > 360 ? 360 : Threat_Pos.Width);
		}

		Safety = (uint8_t) Local_Params[Local_GPS_SafetyFactor].ParamCURRENT;

		Safety_Factor = 0.1 * Safety;

		//Catch the event where a faulty/corrupt coordinate has been placed in threat list OR the GPS accuracies are too big to direct the threat
		if ((Distance_Threat <= ((H_Acc + Own_H_Acc)*Safety_Factor)) && (Distance_Threat >= 0))
		{
			Threat_Pos.Distance = 0xFFFF;
			Threat_Pos.Width = 360;
			Threat_Pos.Zone = Critical;
		}
		else
		{
			// ---- Check that the heading is valid ----
			if(Heading_Vehicle == -1)
			{
				Threat_Pos.Width = 360;

			}
//			if(Local_Params[Local_DynamicZone_Enable].ParamCURRENT == 1)
//			{
//				Threat_Pos.Distance = Dist;
//
//				double CalcDistance = App_SpeedControlStoppingDistance(10, 0);
//
//				Threat_Pos.DistanceCritical = App_SpeedControlZoneDistance(Critical, CalcDistance);
//				Threat_Pos.DistanceWarning = App_SpeedControlZoneDistance(Warning, CalcDistance);
//				Threat_Pos.DistancePresence = App_SpeedControlZoneDistance(Presence, CalcDistance);
//
////				//Adaptive zone formula
////				Critical_Dist = Local_Params[Local_GPS_Dist_Critical].ParamCURRENT + App_GPS_DynamicZone_Calculate(PulseTag.Transp, Bearing_Relative, Bearing_Threat);
////
////				Threat_Pos.DistanceCritical = Critical_Dist;
////				Threat_Pos.DistanceWarning = (uint16_t)(Critical_Dist*Warning_Factor);
////				Threat_Pos.DistancePresence = (uint16_t)(Warn*Presence_Factor);
//			}
//			else
//			{
//				Threat_Pos.Distance = Dist;
//
//				Threat_Pos.DistanceCritical = Local_Params[Local_GPS_Dist_Critical].ParamCURRENT;
//				Threat_Pos.DistanceWarning = Local_Params[Local_GPS_Dist_Warning].ParamCURRENT;
//				Threat_Pos.DistancePresence = Local_Params[Local_GPS_Dist_Presence].ParamCURRENT;
//			}

			Threat_Pos.Distance = Distance_Threat + Acc_Distance;

			Threat_Pos.DistanceCritical = App_Threat_GetZoneDistance(Critical, (int32_t)*SpeedBarParameters.Speedbar_Input, J1939.MachinetoPDSData.SPN_MachinePitch);
			Threat_Pos.DistanceWarning = App_Threat_GetZoneDistance(Warning, (int32_t)*SpeedBarParameters.Speedbar_Input, J1939.MachinetoPDSData.SPN_MachinePitch);
			Threat_Pos.DistancePresence = App_Threat_GetZoneDistance(Presence, (int32_t)*SpeedBarParameters.Speedbar_Input, J1939.MachinetoPDSData.SPN_MachinePitch);

			if (Threat_Pos.Distance < Threat_Pos.DistanceCritical)
			{
				Threat_Pos.Zone = Critical;
			}
			else if ((Threat_Pos.Distance >= Threat_Pos.DistanceCritical) && (Threat_Pos.Distance < Threat_Pos.DistanceWarning))
			{
				Threat_Pos.Zone = Warning;
			}
			else if ((Threat_Pos.Distance >= Threat_Pos.DistanceWarning) && (Threat_Pos.Distance < Threat_Pos.DistancePresence))
			{
				Threat_Pos.Zone = Presence;
			}
			else
			{
				Threat_Pos.Zone = Zone_None;
			}
		}
	}
	else
	{
		Threat_Pos.Zone = Zone_None;
	}

	if(Threat_Pos.Zone == Zone_None)
	{
		Threat_Pos.Sector = Threat_Sector_12;
//		Threat_Pos.Direction = Dir_360;
		Threat_Pos.Distance = 0xFFFF;
		Threat_Pos.Width = 360;
		Threat_Pos.Zone = Zone_None;
	}



//	//Add information of the primary threat in buffers for printing to the LCD
//	if(PulseTag.Transp->UID == Active_Threat->Threat_PrimaryID)
//	{
//		sprintf(Text_Buf7, "Dist : %d m  " , Dist);
//
//		if(Crit > 0)
//			sprintf(Text_Buf8, "Added : %d m  " , Crit - Local_Params[Local_GPS_Dist_Critical].ParamCURRENT);
//		else
//			sprintf(Text_Buf8, "Added : 0 m  ");
//
//		sprintf(Text_Buf9, "LAT1 : %d  +-%d ",  OwnPosition.Own_GPS_Data.Latitude, (OwnPosition.Own_GPS_Data.HorizontalAccuracy/1000));
//		sprintf(Text_Buf10, "LON1 : %d  ", OwnPosition.Own_GPS_Data.Longitude);
//
//		sprintf(Text_Buf11, "LAT2 : %d  +-%d ",PulseTag.Transp->GPS_Data.Latitude, H_Acc);
//		sprintf(Text_Buf12, "LON2 : %d  ",PulseTag.Transp->GPS_Data.Longitude);
//
//	}

	return Threat_Pos;

}

Position Threat_InvalidGPS (void)
{
	Position Invalid_Pos;

	Invalid_Pos.Sector = Threat_Sector_12;
//	Invalid_Pos.Direction = Dir_360;
	Invalid_Pos.Distance = 0xFFFF;
	Invalid_Pos.Width = 360;
	Invalid_Pos.Zone = Presence;

	Invalid_Pos.kind = Pulse_GPS;
	Invalid_Pos.DistanceCritical = 0;
	Invalid_Pos.DistanceWarning = 0;
	Invalid_Pos.DistancePresence = 0;

	return Invalid_Pos;
}

uint16_t App_Threat_GetZoneDistance(uint8_t GetZone, int32_t Speed, int8_t Pitch)
{
	uint16_t Zone_DistanceCritical = 0;
	uint16_t Zone_DistanceWarning = 0;
	uint16_t Zone_DistancePresence = 0;

	// ---- Check if the zones must be dynamically calculated or be static ----
	if (Local_Params[Local_DynamicZone_Enable].ParamCURRENT == 1)
	{
//		// ---- Calculate the stopping distance of towards the unit ----
//		uint16_t CalcDistance = App_SpeedControlStoppingDistance(Speed, Pitch);
//
//		// ---- Update distances dynamic zones -----
//		Zone_DistanceCritical = App_SpeedControlZoneDistance(Critical, CalcDistance);
//		Zone_DistanceWarning = App_SpeedControlZoneDistance(Warning, CalcDistance);
//		Zone_DistancePresence = App_SpeedControlZoneDistance(Presence, CalcDistance);

		Zone_DistanceCritical = App_SpeedControlCriticalDistance(Speed, Pitch);
		Zone_DistanceWarning = App_SpeedControlWarningDistance(Speed, Pitch);
		Zone_DistancePresence = App_SpeedControlPresenceDistance(Speed, Pitch);

	//				//Adaptive zone formula
	//				Critical_Dist = Local_Params[Local_GPS_Dist_Critical].ParamCURRENT + App_GPS_DynamicZone_Calculate(PulseTag.Transp, Bearing_Relative, Bearing_Threat);
	//
	//				Crit = Critical_Dist;
	//				Warn = (uint16_t)(Critical_Dist*Warning_Factor);
	//				Pres = (uint16_t)(Warn*Presence_Factor);
	}
	else
	{
		// ---- Update distances to the static zones (static parameters) -----
		Zone_DistanceCritical = Local_Params[Local_GPS_Dist_Critical].ParamCURRENT;
		Zone_DistanceWarning = Local_Params[Local_GPS_Dist_Warning].ParamCURRENT;
		Zone_DistancePresence = Local_Params[Local_GPS_Dist_Presence].ParamCURRENT;
	}

	if (GetZone == Critical)
	{
		return Zone_DistanceCritical;
	}
	else if (GetZone == Warning)
	{
		return Zone_DistanceWarning;
	}
	else if (GetZone == Presence)
	{
		return Zone_DistancePresence;
	}

	return 0;
}

/*-----------------------------------------
 *Function name and description
 *---------
 *
 * Sort all vehicle tags based on LF RSSI
 * First Item --> Highest RSSI
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/

Local_Tag* Threat_OwnedTag_Sort (Local_Tag OwnedTags[])
{
	uint8_t i, pass;

	Local_Tag hold;

	for (pass = 0; pass < Local_Params[Local_TagCount].ParamCURRENT; pass++)
	{
		for(i = 0; i < Local_Params[Local_TagCount].ParamCURRENT - 1; i++)
		{
			if(OwnedTags[i].Own_Tag_RSSI < OwnedTags[i+1].Own_Tag_RSSI)
			{
				hold = OwnedTags[i];

				OwnedTags[i] = OwnedTags[i + 1];

				OwnedTags[i + 1] = hold;
			}
		}
	}

	return OwnedTags;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function returns the threat`s direction based
 * on various LF information
 *
 *
 *Inputs:
 *---------
 * Pulse Tag
 * kind - pulse or GPS_pulse
 *
 *Outputs:
 *---------
 * uint8_t direction
 *-----------------------------------------*/
uint8_t Threat_DetermineDirection (Pulse_Tag PulseTag)
{
	uint8_t  Dominant;
	uint8_t Index;
	uint8_t RSSI = 0;
	uint32_t LastSeen = 0;

	//find highest RSSI value in LF History
	for(uint8_t i = 0; i < 4; i++)
	{
		if(PulseTag.LF_History[i].RSSI > RSSI)
		{
			Index = i;
			LastSeen = PulseTag.LF_History[i].last_LF;
		}
		else if(PulseTag.LF_History[i].RSSI == RSSI)
		{
			if(time_since(PulseTag.LF_History[i].last_LF) < time_since(LastSeen))
			{
				Index = i;
				LastSeen = PulseTag.LF_History[i].last_LF;
			}
		}
	}

	switch(Index)
	{
		case Front_Tag:

			Dominant = Front_Tag_SID;
			break;

		case Rear_Tag:

			Dominant = Rear_Tag_SID;
			break;

		case Left_Tag:

			Dominant = Left_Tag_SID;
			break;

		case Right_Tag:

			Dominant = Right_Tag_SID;
			break;

		default:

			break;
	}


	return Dominant;
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function determines if a threat status
 * should be updated for the user
 *
 *
 *Inputs:
 *---------
 * Current Position data
 * Previous Position data
 * Status of the threat acknowledgment
 *
 *Outputs:
 *---------
 * uint8_t direction
 *-----------------------------------------*/
bool Threat_DetermineUpdate (Position ThreatIndex, Position ThreatPrevious, bool ACK_Status)
{
	int delta = 0;

	if(!ACK_Status)
	{
//		delta = abs(ThreatIndex.Direction - ThreatPrevious.Direction);

		if ((ThreatIndex.Zone != ThreatPrevious.Zone) || (delta > Local_Params[Local_Directivity_EV_Width].ParamCURRENT) || (ThreatIndex.Width != ThreatPrevious.Width))
			return true;
		else
			return false;
	}
	else
	{
		//First see if the parameter is set to enable update events after position changed or if the threat has not been acknowledged, else only update if zone increased
		if ((Local_Params[Local_Directivity_Events].ParamCURRENT == 1))
		{
//			delta = abs(ThreatIndex.Direction - ThreatPrevious.Direction);

			if((ThreatIndex.Zone > ThreatPrevious.Zone) || (delta > Local_Params[Local_Directivity_EV_Width].ParamCURRENT) || (ThreatIndex.Width != ThreatPrevious.Width))
				return true;
			else
				return false;
		}
		else
		{
			if((ThreatIndex.Zone > ThreatPrevious.Zone))
				return true;
			else
				return false;
		}

	}
}
/*-----------------------------------------
 *Function name and description
 *---------
 * This function returns the threat zone based on
 * current LF info
 *
 *
 *Inputs:
 *---------
 * Transponder tag
 *
 *Outputs:
 *---------
 * uint8_t zone
 *-----------------------------------------*/
uint8_t Threat_DetermineZone (int8_t LF_RSSI)
{
	uint8_t Zone;

	//Determine the zone of the tag by looking at the LF data
	if(LF_RSSI == -1)
	{
		Zone = Presence;
	}
	else if((LF_RSSI >= Local_Params[Local_Threshold_Presence].ParamCURRENT) && (LF_RSSI < Local_Params[Local_Threshold_Warning].ParamCURRENT))
	{
		Zone = Presence;
	}
	else if((LF_RSSI >= Local_Params[Local_Threshold_Warning].ParamCURRENT) && (LF_RSSI < Local_Params[Local_Threshold_Critical].ParamCURRENT))
	{
		Zone = Warning;
	}
	else if(LF_RSSI >= Local_Params[Local_Threshold_Critical].ParamCURRENT)
	{
		Zone = Critical;
	}
	else
	{
		Zone = Presence;
	}

	return Zone;
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function looks if a tag is already present
 * in the threatlist
 *
 *
 *Inputs:
 *---------
 * 32-bit UID, List type
 *
 *Outputs:
 *---------
 * Index inside of threat list
 *-----------------------------------------*/
uint8_t Threat_SearchUID (uint32_t UID)
{
	for(uint8_t i = 0; i < ThreatCounters.ThreatList_Counter; i++)
	{

		if(UID == ThreatList[i].Threat_PrimaryID)
		{
			return i;
		}

	}
	return 0xFF;
}


/*-----------------------------------------
 *Function name and description
 *---------
 * This function looks if a tag is part of a
 * vehicle (same VID) already in threat list
 *
 *
 *Inputs:
 *---------
 * 16-bit VID
 * 32-bit UID
 *
 *Outputs:
 *---------
 * Index to the threat in the list
 *-----------------------------------------*/
uint8_t Threat_SearchVID (uint16_t VID, uint32_t UID)
{

	for(uint8_t i = 0; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{
		if(((ThreatList[i].Threat_SecondaryID == VID) && (VID != 0)) && (ThreatList[i].Threat_PrimaryID != UID))
		{
			if(VID != Local_Params[Local_VID].ParamCURRENT) //apply only if this multi-tag threat is not an owned tag
				return i;
		}
	}

	return 0xFF;

}


/*-----------------------------------------
 *Function name and description
 *---------
 * This function looks if a threat is already accepted
 *
 *
 *Inputs:
 *---------
 * 32-bit UID, List type
 *
 *Outputs:
 *---------
 * true or false
 *-----------------------------------------*/
bool Threat_AcceptedSearch (Threat Threat_Item)
{
	for(uint8_t i = 0; i < ThreatManagementCounters.AcceptedList_Counter; i++)
	{
		if(Threat_Item.Threat_PrimaryID == ACK_Threats[i].ACK_UID)
		{
			return true;
		}
	}

	return false;
}

void Threat_SortAccepted (void)
{
	uint8_t i, pass;

	ACK_Threat hold;

	for(pass = 0; pass < ThreatManagementCounters.AcceptedList_Counter; pass++)
	{

		for(i = 0; i < (ThreatManagementCounters.AcceptedList_Counter - 1); i++)
		{
			if((ACK_Threats[i].ACK_UID < ACK_Threats[i + 1].ACK_UID))
			{
				hold = ACK_Threats[i];

				ACK_Threats[i] = ACK_Threats[i + 1];

				ACK_Threats[i + 1] = hold;
			}
		}

	}

}

uint8_t Threat_SortEvents (void)
{
	uint8_t Index;

	//search list for first tag that is not owned or excluded
	for(uint8_t i = 0; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{

		if((!ThreatList[i].Threat_Excluded) && (!ThreatList[i].Threat_OwnTag) && (!ThreatList[i].Event_Processed) && (ThreatList[i].Threat_Type != 0) && (ThreatList[i].Threat_Position.Zone != Zone_None))
		{
			Index = i;
			return Index;
		}

	}

	return 0xFF;
}

Threat* Threat_FindNextActive(uint8_t* Index)
{

	//search list for first tag that is not owned or excluded
	for(uint8_t i = *Index; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{

		if((!ThreatList[i].Threat_Excluded) && (!ThreatList[i].Threat_OwnTag) && (!ThreatList[i].Event_Processed) && (ThreatList[i].Threat_Type != 0) && (ThreatList[i].Threat_Position.Zone != Zone_None))
		{
			(*Index) = i + 1;
			return &ThreatList[i];
		}

	}

	return NULL;
}

uint8_t App_ThreatFilter (uint8_t Restart)
{
	uint8_t Index;

	if(Restart <= ThreatManagementCounters.ThreatList_Counter)
	{
		//search list for first tag that is not owned or excluded
		for(uint8_t i = Restart; i < ThreatManagementCounters.ThreatList_Counter; i++)
		{

			if((!ThreatList[i].Threat_Excluded) && (!ThreatList[i].Threat_OwnTag) && (ThreatList[i].Threat_Type != 0) && (ThreatList[i].Threat_Position.Zone != Zone_None))
			{
				Index = i;
				return Index;
			}

		}
	}

	return 0xFF;
}

void App_ThreatResetACK (void)
{
	//search list for first tag that is not owned or excluded
	for(uint8_t i = 0; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{
		ThreatList[i].Event_Processed = false;
	}

	ThreatManagementCounters.AcceptedList_Counter = 0;
}


void Threat_HandleActive (uint8_t Index)
{
	//Remove trigger flag
	ThreatList[Index].Event_Triggered = false;

//		//Look in accepted list if item exists
//		if(!Vision_AcceptedSearch (ThreatList[Index]))
//		{
//			//ACK_Threats[ThreatManagementCounters.AcceptedList_Counter].Threat_handle = &ThreatList[Index];
//			ACK_Threats[ThreatManagementCounters.AcceptedList_Counter].ACK_UID = ThreatList[Index].Threat_PrimaryID;
//			ACK_Threats[ThreatManagementCounters.AcceptedList_Counter].Zone_Prev = ThreatList[Index].Threat_Zone;
//			App_EventClear (evGroups[Type_CAS].evIndex[0]);
//			ThreatManagementCounters.AcceptedList_Counter++;
//		}
}

void Threat_EventListMove(uint8_t CurrentIndex, uint8_t  ToIndex, Threat* NewThreat)
{
	ThreatEventList[ToIndex] = ThreatEventList[CurrentIndex];
}

void Threat_EventListSet (Threat* NewThreat, uint8_t IndexOffset)
{
	ThreatEventList[IndexOffset] = *NewThreat;
}

void Threat_EventListReset (uint8_t IndexOffset)
{
	ThreatEventList[IndexOffset].ACK_Received = false;
	ThreatEventList[IndexOffset].ACK_Requested = false;
	ThreatEventList[IndexOffset].ACK_Required = false;
	ThreatEventList[IndexOffset].Event_Processed = false;
	ThreatEventList[IndexOffset].Event_Triggered = false;
	ThreatEventList[IndexOffset].Log_Required = false;
	ThreatEventList[IndexOffset].Threat_Excluded = false;
	ThreatEventList[IndexOffset].Threat_OwnTag = false;

	memset(ThreatEventList[IndexOffset].Threat_Name,0,20);

//	ThreatEventList[IndexOffset].Threat_Position.Direction = 0;
	ThreatEventList[IndexOffset].Threat_Position.Width = 0;
	ThreatEventList[IndexOffset].Threat_Position.Zone = 0;
	ThreatEventList[IndexOffset].Threat_PrimaryID = 0;
	ThreatEventList[IndexOffset].Threat_SecondaryID = 0;
	ThreatEventList[IndexOffset].Threat_Tech = 0;
	ThreatEventList[IndexOffset].Threat_Type = 0;
	ThreatEventList[IndexOffset].TimeStamp = 0;
	ThreatEventList[IndexOffset].LastSeen = 0;
}

uint8_t Threat_EventListFind(Threat* FindThreat)
{
	// ---- Search list for specific tag to see if it is in the list ----
	// ---- FIXME: Geofences has no UID just Names, Tags don't necessarily has unique name, or any name ----
	for(uint8_t i = 0; i < MaxEventThreat; i++)
	{
		if (ThreatEventList[i].Threat_PrimaryID == FindThreat->Threat_PrimaryID)
		{
			return (i < MaxEventThreat ? i : 0xFF);
		}
	}

	return 0xFF;
}

uint8_t Threat_EventListTempFind(Threat* FindThreat)
{
	// ---- Search list for specific tag to see if it is in the list ----
	// ---- FIXME: Geofences has no UID just Names, Tags don't necessarily has unique name, or any name ----
	for(uint8_t i = 0; i < MaxEventThreat; i++)
	{
		if (ThreatEventListTemp[i].Threat_PrimaryID == FindThreat->Threat_PrimaryID)
		{
			return (i < MaxEventThreat ? i : 0xFF) ;
		}
	}

	return 0xFF;
}

void Threat_EventSet (Threat* NewThreat, uint8_t IndexOffset)
{
	uint16_t Event = 0;
	uint8_t  Event_Data[8] = {0};

	Event = (uint16_t) (EV_PDS_1 + IndexOffset);

	if (Event != 0) // && (!EventList[Event].EventActive))
	{
		Event_Data[0] = (uint8_t) (NewThreat->Threat_PrimaryID >> 24);
		Event_Data[1] = (uint8_t) (NewThreat->Threat_PrimaryID >> 16);
		Event_Data[2] = (uint8_t) (NewThreat->Threat_PrimaryID >> 8);
		Event_Data[3] = (uint8_t) (NewThreat->Threat_PrimaryID);
		Event_Data[4] = (uint8_t) (NewThreat->Threat_SecondaryID >> 8);
		Event_Data[5] = (uint8_t) (NewThreat->Threat_SecondaryID);
//		Event_Data[6] = (uint8_t) (NewThreat->Threat_Position.Direction>> 8);
//		Event_Data[7] = (uint8_t) (NewThreat->Threat_Position.Direction);

		//EventList[Event].EventData = Event_Data;
		memcpy(EventList[Event].EventData, Event_Data, 8);

		App_EventSetTimeStamp(Event, NewThreat->TimeStamp);
		App_EventClearLogged(Event);
		App_EventUpdateThreatImage(Event, NewThreat->Threat_Type);
		App_EventUpdateAddtionalInfo(Event, (uint8_t*)NewThreat);
		App_EventUpdateActions(Event, NewThreat->ThreatAction1, NewThreat->ThreatAction2, NewThreat->ThreatAction3);
	}
}

void Threat_EventUpdate(Threat* UpdateThreat, uint8_t IndexOffset)
{
	uint16_t Event = 0;
	uint8_t  Event_Data[8] = {0};

	Event = (uint16_t) (EV_PDS_1 + IndexOffset);

	Event_Data[0] = (uint8_t)(UpdateThreat->Threat_PrimaryID >> 24);
	Event_Data[1] = (uint8_t)(UpdateThreat->Threat_PrimaryID >> 16);
	Event_Data[2] = (uint8_t)(UpdateThreat->Threat_PrimaryID >> 8);
	Event_Data[3] = (uint8_t)(UpdateThreat->Threat_PrimaryID);
	Event_Data[4] = (uint8_t)(UpdateThreat->Threat_SecondaryID >> 8);
	Event_Data[5] = (uint8_t)(UpdateThreat->Threat_SecondaryID);
//	Event_Data[6] = (uint8_t)(UpdateThreat->Threat_Position.Direction>> 8);
//	Event_Data[7] = (uint8_t)(UpdateThreat->Threat_Position.Direction);

	memcpy(EventList[Event].EventData, Event_Data, 8);

	App_EventUpdateThreatImage(Event, UpdateThreat->Threat_Type);
	App_EventUpdateAddtionalInfo(Event, (uint8_t*) UpdateThreat);
	App_EventUpdateActions(Event, UpdateThreat->ThreatAction1, UpdateThreat->ThreatAction2, UpdateThreat->ThreatAction3);
}

void Threat_EventMove(Threat* MoveThreat, uint8_t IndexOffset)
{
	uint16_t Event = 0;
	uint8_t  Event_Data[8] = {0};

	Event = (uint16_t) (EV_PDS_1 + IndexOffset);

	Event_Data[0] = (uint8_t) (MoveThreat->Threat_PrimaryID >> 24);
	Event_Data[1] = (uint8_t) (MoveThreat->Threat_PrimaryID >> 16);
	Event_Data[2] = (uint8_t) (MoveThreat->Threat_PrimaryID >> 8);
	Event_Data[3] = (uint8_t) (MoveThreat->Threat_PrimaryID);
	Event_Data[4] = (uint8_t) (MoveThreat->Threat_SecondaryID >> 8);
	Event_Data[5] = (uint8_t) (MoveThreat->Threat_SecondaryID);
//	Event_Data[6] = (uint8_t) (MoveThreat->Threat_Position.Direction>> 8);
//	Event_Data[7] = (uint8_t) (MoveThreat->Threat_Position.Direction);

	memcpy(EventList[Event].EventData, Event_Data, 8);

	App_EventClearLogged(Event);
	App_EventClearACK(Event);
	App_EventUpdateThreatImage(Event, MoveThreat->Threat_Type);
	App_EventUpdateAddtionalInfo(Event, (uint8_t*) MoveThreat);
	App_EventUpdateActions(Event, MoveThreat->ThreatAction1, MoveThreat->ThreatAction2, MoveThreat->ThreatAction3);

}

void Threat_EventCheckActions(void)
{
	// ---- Loop through the threat list to determine if the action time has elapsed to set the action ----
	for(int i = 0; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{
		// ----- If the entry in the threat list has a valid time stamp ----
		if (ThreatList[i].TimeStamp != 0)
		{
			// ---- Transition between two different actions, get the most important previous action ----
			ThreatList[i].ThreatAction1 = Threat_DetermineMostImportantAction(&ThreatList[i]);

			// ---- Switch between the different zones of the threat ----
			switch (ThreatList[i].Threat_Position.Zone)
			{
				// ---- Presence Zone ----
				case Presence:

					// ---- If the time stamp has elapsed between action 1 and 2 ----
					if (time_since(ThreatList[i].TimeStamp) > Local_Params[Local_ThreatPresence_Action1_2_Time].ParamCURRENT)
					{
						ThreatList[i].ThreatAction1 = (uint8_t) Local_Params[Local_ThreatPresence_Action1].ParamCURRENT;
						ThreatList[i].ThreatAction2 = (uint8_t) Local_Params[Local_ThreatPresence_Action2].ParamCURRENT;
					}

					// ---- If the time stamp has elapsed between action 2 and 3 ----
					if (time_since(ThreatList[i].TimeStamp) > Local_Params[Local_ThreatPresence_Action2_3_Time].ParamCURRENT)
					{
						ThreatList[i].ThreatAction1 = (uint8_t) Local_Params[Local_ThreatPresence_Action1].ParamCURRENT;
						ThreatList[i].ThreatAction3 = (uint8_t) Local_Params[Local_ThreatPresence_Action3].ParamCURRENT;
					}

					break;

				// ---- Warning Zone ----
				case Warning:

					// ---- If the time stamp has elapsed between action 1 and 2 ----
					if (time_since(ThreatList[i].TimeStamp) > Local_Params[Local_ThreatWarning_Action1_2_Time].ParamCURRENT)
					{
						ThreatList[i].ThreatAction1 = (uint8_t) Local_Params[Local_ThreatWarning_Action1].ParamCURRENT;
						ThreatList[i].ThreatAction2 = (uint8_t) Local_Params[Local_ThreatWarning_Action2].ParamCURRENT;
					}

					// ---- If the time stamp has elapsed between action 2 and 3 ----
					if (time_since(ThreatList[i].TimeStamp) > Local_Params[Local_ThreatWarning_Action2_3_Time].ParamCURRENT)
					{
						ThreatList[i].ThreatAction1 = (uint8_t) Local_Params[Local_ThreatWarning_Action1].ParamCURRENT;
						ThreatList[i].ThreatAction3 = (uint8_t) Local_Params[Local_ThreatWarning_Action3].ParamCURRENT;
					}

					break;

				// ---- Critical Zone ----
				case Critical:

					// ---- If the time stamp has elapsed between action 1 and 2 ----
					if (time_since(ThreatList[i].TimeStamp) > Local_Params[Local_ThreatCritical_Action1_2_Time].ParamCURRENT)
					{
						ThreatList[i].ThreatAction1 = (uint8_t) Local_Params[Local_ThreatCritical_Action1].ParamCURRENT;
						ThreatList[i].ThreatAction2 = (uint8_t) Local_Params[Local_ThreatCritical_Action2].ParamCURRENT;
					}

					// ---- If the time stamp has elapsed between action 2 and 3 ----
					if (time_since(ThreatList[i].TimeStamp) > Local_Params[Local_ThreatCritical_Action2_3_Time].ParamCURRENT)
					{
						ThreatList[i].ThreatAction1 = (uint8_t) Local_Params[Local_ThreatCritical_Action1].ParamCURRENT;
						ThreatList[i].ThreatAction3 = (uint8_t) Local_Params[Local_ThreatCritical_Action3].ParamCURRENT;
					}

					break;

				default:

					ThreatList[i].ThreatAction2 = Act_None;
					ThreatList[i].ThreatAction3 = Act_None;

					break;
			}
		}
	}
}

void Threat_EventUpdateActions (uint16_t Index, uint8_t Act1, uint8_t Act2, uint8_t Act3)
{
	uint16_t Event = 0;

	Event = (uint16_t) EV_PDS_1 + Index ;

	App_EventUpdateActions(Event, Act1, Act2, Act3);
}

void Threat_EventReset (uint8_t IndexOffset)
{
	uint16_t Event = 0;

	Event = (uint16_t) EV_PDS_1 + IndexOffset ;

	memset(EventList[Event].EventData, 0, 8);

	App_EventClear(Event);
	App_EventUpdateActions(Event, Act_DisplayOnly, Act_DisplayOnly, Act_DisplayOnly);
	App_EventUpdateThreatImage(Event, 0);
	App_EventUpdateAddtionalInfo(Event, NULL);
}

void Threat_EventSetEnd(Threat* OldThreat, uint8_t IndexOffset)
{
	uint16_t Event = 0;
	Event = (uint16_t) (EV_PDS_1_End + IndexOffset) ;

	uint8_t Event_Data[8];
	memset(Event_Data, 0xFF, 8);
//
//	uint8_t DisplayPosition = 0;
//
//	DisplayPosition = IndexOffset + 1;
//
//	EventData[0] = DisplayPosition;
//
	App_EventSet(Event);
//	App_EventUpdateData(Event, EventData);

	if ((Event != 0)  && (OldThreat != NULL))
	{
		Event_Data[0] = (uint8_t)(OldThreat->Threat_PrimaryID >> 24);
		Event_Data[1] = (uint8_t)(OldThreat->Threat_PrimaryID >> 16);
		Event_Data[2] = (uint8_t)(OldThreat->Threat_PrimaryID >> 8);
		Event_Data[3] = (uint8_t)(OldThreat->Threat_PrimaryID);
		Event_Data[4] = (uint8_t)(OldThreat->Threat_SecondaryID >> 8);
		Event_Data[5] = (uint8_t)(OldThreat->Threat_SecondaryID);
//		Event_Data[6] = (uint8_t)(OldThreat->Threat_Position.Direction>> 8);
//		Event_Data[7] = (uint8_t)(OldThreat->Threat_Position.Direction);

		//EventList[Event].EventData = Event_Data;
		memcpy(EventList[Event].EventData,Event_Data,8);

		App_EventUpdateAddtionalInfo(Event, (uint8_t*)OldThreat);
	}
}

void Threat_EventResetEnd(uint8_t IndexOffset)
{
	uint16_t Event = 0;

	Event = (uint16_t) (EV_PDS_1_End + IndexOffset);

	uint8_t EventData[8];
	memset(EventData, 0xFF, 8);

	App_EventClear(Event);
	App_EventUpdateAddtionalInfo(Event, NULL);
	App_EventUpdateData(Event, EventData);
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function resets all trigger flags
 *
 *
 *Inputs:
 *---------
 * void
 *
 *Outputs:
 *---------
 * void
 *-----------------------------------------*/
void Threat_Events_Reset (void)
{
	// ---- Loop through the size of the threat list and reset flag ----
	for(uint8_t i = 0; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{
		ThreatList[i].Event_Triggered = false;
	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function runs through the threat list
 * and adds a vision zone msg to be sent
 * by the pulse400 module to warn all close
 * by pedestrian tags
 *
 *
 *Inputs:
 *---------
 * void
 *
 *Outputs:
 *---------
 * void
 *-----------------------------------------*/
void Threat_Warn_Pedestrian (void)
{
	// ---- Loop through threat list and send message to the pedestrian devices ----
	for (int i = 0; i < ThreatManagement.ThreatList_Counter; i++)
	{
		// ---- If the threat is a pedestrian ----
		if (ThreatList[i].Threat_Type == Person)
		{
			// ---- Update top threat position ----
			Threat_Broadcast.Zone 		= ThreatList[i].Threat_Position.Zone;
			Threat_Broadcast.Distance	= ThreatList[i].Threat_Position.Distance;
			Threat_Broadcast.Heading	= OwnPosition.Own_GPS_Data.HeadingVehicle;
			Threat_Broadcast.UID		= ThreatList[i].Threat_PrimaryID;

			// ---- Add message to zone process ----
			add_zone_message(&Threat_Broadcast);
		}
	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function handles active CAS events
 *
 *
 *Inputs:
 *---------
 * void
 *
 *Outputs:
 *---------
 * void
 *-----------------------------------------*/
void Threat_Events (void)
{
	uint8_t Index = 0;
	uint8_t* pIndex = &Index;

	uint8_t FindIndex = 0xFF;
	//Handle all threat types
	//Index = Threat_SortEvents();
	Threat* PriorityThreat;

	Threat_EventCheckActions();

	// ---- Update the previous list of the threat parsed into events ----
	memcpy(ThreatEventListTemp, ThreatEventList, (sizeof(Threat) * MaxEventThreat));

	// ---- Loop only through the max event of threats that can occur ----
	for (uint8_t i = 0 ; i < MaxEventThreat; i++)
	{
		// ---- Get the first valid threat in the list if available ----
		PriorityThreat = Threat_FindNextActive(pIndex);

		// ---- Check if a valid threat was returned ----
		if (PriorityThreat != NULL)
		{
			// ---- Check if this threat is already in the threat list (mirror the events) ----
			FindIndex = Threat_EventListTempFind(PriorityThreat);

			// ---- Update the threat list that mirrors the events ----
			Threat_EventListSet(PriorityThreat, i);

			Threat_EventResetEnd(i);

			// ---- The reference pointer must ensure that if zone none occurs it will not be drawn ---
			if (FindIndex != 0xFF)
			{
				// ---- If the threat was found in the same place as the previous time ----
				if (FindIndex == i)
				{
					if (App_Threat_DetermineUpdate( ThreatEventList[i].Threat_Position.Sector, ThreatEventList[i].Threat_Position.Zone, ThreatEventList[i].Threat_Position.Width,
													ThreatEventListTemp[FindIndex].Threat_Position.Sector, ThreatEventListTemp[FindIndex].Threat_Position.Zone, ThreatEventListTemp[FindIndex].Threat_Position.Width))
					{
						// ---- Move event with details of the threat - keep same place only clear logged flag ----
						Threat_EventMove(&ThreatEventList[i], i);
					}
					else
					{
						// ---- Update event with details of the threat ----
						Threat_EventUpdate(&ThreatEventList[i], i);
					}
				}
				else
				{
					// ---- Move event with details of the threat ----
					Threat_EventSet(&ThreatEventList[i], i);
				}
			}
			else
			{
				// ---- Set event with details of the threat ----
				Threat_EventSet(&ThreatEventList[i], i);
			}
		}
		else
		{
			Threat_EventReset(i);
			Threat_EventSetEnd(&ThreatEventListTemp[i],i);
			Threat_EventListReset(i);
		}
	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 * Function used for creating and maintaining
 * a work-zone
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

void Threat_WorkZoneHandler(void)
{
	// ---- Check if the GPS100 module is enabled, workzone only for GPS based system -----
	if(Local_Params[Local_Ublox_Enable].ParamCURRENT == 1)
	{

		//Check conditions to place the system in a work zone
		//if((App_ACK_CheckFlag (ACK_CAS)) && (time_since(User_Button[ACK_CAS].Time_Pressed) > 3*Seconds) && (!System_Flags.System_WorkZone))
		if((!(*User_Button[ACK_CAS].ACK_Flag)) && (User_Button[ACK_CAS].Press_Duration > 3*Seconds) && (System_Flags.System_WorkZoneStatus != Status_Active))
		{
			// ---- Check if the speed received from the input is lower than set in parameters, and that active threat is not a pedestrian ----
			if ((OwnPosition.Own_GPS_Speed <= Local_Params[Local_Workzone_ActivateSpeed].ParamCURRENT) && (Active_Threat->Threat_Type != Person))
			{
				// ---- Set the work zone status active (created) ----
 				System_Flags.System_WorkZoneStatus = Status_Active;

				System_Flags.System_Last_LON = OwnPosition.Own_GPS_Data.Longitude;
				System_Flags.System_Last_LAT = OwnPosition.Own_GPS_Data.Latitude;

				App_ThreatResetACK();
			}
			else
			{
				// ---- Set the work zone status to not required (failed to create) ----
				System_Flags.System_WorkZoneStatus = Status_NotRequired;
			}

			App_Button_Press_Handled(ACK_CAS);
		}

		// ---- If the workzone is still active check the conditions to see if the work zone is still valid ----
		if (System_Flags.System_WorkZoneStatus == Status_Active)
		{
			// ---- Calculate distance from point where the workzone was created ----
			System_Flags.System_Last_Distance = (uint16_t) App_GPS_ReturnDistance(OwnPosition.Own_GPS_Data.Latitude, OwnPosition.Own_GPS_Data.Longitude, System_Flags.System_Last_LAT, System_Flags.System_Last_LON);

			// ---- Compare distance with the distance store in parameters, if larger disable workzone ----
			if(System_Flags.System_Last_Distance > Local_Params[Local_Workzone_Raduis].ParamCURRENT)
			{
				System_Flags.System_WorkZoneStatus = Status_Inactive;
			}
			// ---- Check active threat is not a person, if so disable workzone ----
			if (Active_Threat->Threat_Type == Person)
			{
				System_Flags.System_WorkZoneStatus = Status_Inactive;
			}
		}
	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function inspects the threat list for
 * speed zone tags and returns the most severe
 * speed zone
 *
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * Current Speed Zone
 *-----------------------------------------*/

uint8_t Threat_ReturnSpeedZone(void)
{
	uint8_t SpeedZoneArray[20] = {0};
	uint8_t SpeedZoneTags = 0;
	uint8_t	SpeedZoneHighest = 0;

	for(int i = 0; i < ThreatManagementCounters.ThreatList_Counter; i++)
	{
		if(ThreatList[i].Threat_Type == LowSpeed)
		{
			SpeedZoneArray[SpeedZoneTags] = SpeedZone_Low;
			SpeedZoneTags++;
		}
		else if(ThreatList[i].Threat_Type == MedSpeed)
		{
			SpeedZoneArray[SpeedZoneTags] = SpeedZone_Med;
			SpeedZoneTags++;
		}
		else if(ThreatList[i].Threat_Type == highSpeed)
		{
			SpeedZoneArray[SpeedZoneTags] = SpeedZone_High;
			SpeedZoneTags++;
		}
	}

	if(SpeedZoneTags > 1)
	{
		for(uint8_t j = 0; j < SpeedZoneTags; j++)
		{
			if(SpeedZoneArray[j] < SpeedZoneHighest)
				SpeedZoneHighest = SpeedZoneArray[j];
		}

		return SpeedZoneHighest;
	}
	else if(SpeedZoneTags == 1)
		return SpeedZoneArray[0];
	else
		return SpeedZone_None;
}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function returns true or false if a threat`s
 * position should be updated on the display
 *
 *
 *Inputs:
 *---------
 * Pulse Tag
 * kind - pulse or GPS_pulse
 *
 *Outputs:
 *---------
 * uint8_t direction
 *-----------------------------------------*/
bool App_Threat_DetermineUpdate (uint8_t Sector_Now, uint8_t Zone_Now, uint16_t Width_Now, uint8_t Sector_Prev, uint8_t Zone_Prev, uint16_t Width_Prev)
{
	// ---- Check if sector, or zone or width is different than the previous if so an update occurred ----
	if ((Sector_Now != Sector_Prev) || (Zone_Now != Zone_Prev) || (Width_Now != Width_Prev))
	{
		return true;
	}
	// ---- No update occurred ----
	else
	{
		return false;
	}
}

bool App_Threat_DetermineScreenUpdate (uint8_t Sector_Now, uint8_t Zone_Now, uint16_t Width_Now, uint8_t Sector_Prev, uint8_t Zone_Prev, uint16_t Width_Prev)
{
	// ---- Check if sector (only when width is not full circle), or zone is different than the previous if so an update occurred ----
	if (((Sector_Now != Sector_Prev) && (Width_Now != 360)) || (Zone_Now != Zone_Prev))
	{
		return true;
	}
	// ---- No update occurred ----
	else
	{
		return false;
	}
}

bool App_Threat_GetPDSEventData(uint16_t PDSEventID, uint8_t* DataPointer)
{
	uint8_t PDSEventData[48];
	Threat* EventThreat = NULL;

	memset(PDSEventData, 0xFF, sizeof(PDSEventData));

	if (EventList[PDSEventID].AddtionalInfo != NULL)
	{
		EventThreat = (Threat*) EventList[PDSEventID].AddtionalInfo;
		// ---- Threat Information ----
		memcpy(PDSEventData, &EventThreat->Threat_PrimaryID, 4);
		PDSEventData[4] = EventThreat->Threat_Tech;
		PDSEventData[5] = 0xFF;
		PDSEventData[6] = EventThreat->Threat_Type;
		PDSEventData[7] = (uint8_t) (EventThreat->Threat_Position.Width / 10);

		PDSEventData[8] = EventThreat->Threat_Position.Sector;
		PDSEventData[9] = EventThreat->Threat_Position.Zone;
		memcpy((PDSEventData + 10), &EventThreat->Threat_Speed, 2);
		memcpy((PDSEventData + 12), &EventThreat->Threat_Position.Distance, 2);
		memcpy((PDSEventData + 14), &EventThreat->Threat_HeadingVehicle, 2);

		memcpy((PDSEventData + 16), &EventThreat->Threat_Latitude, 4);
		memcpy((PDSEventData + 20), &EventThreat->Threat_Longitude, 4);

		PDSEventData[24] = (uint8_t) (EventThreat->Threat_HorizontalAccuracy / 1000);
	}

	if ((PDSEventID >= EV_PDS_1_End) && (PDSEventID <= EV_PDS_7_End))
	{
		PDSEventData[28] = (uint8_t) (PDSEventID - (uint16_t) EV_PDS_1_End) + 1;
	}
	else
	{
		PDSEventData[28] = (uint8_t) (PDSEventID - (uint16_t) EV_PDS_1) + 1;
	}

	uint16_t Speed = (uint16_t) (SpeedBar_Display.Speed_Current * 10);
	memcpy((PDSEventData + 32), &Speed, 2);

	uint16_t Heading = (uint16_t) (OwnPosition.Own_GPS_Data.HeadingVehicle / ((int32_t) 1000));
	memcpy((PDSEventData + 34), &Heading, 2);

	// ---- Create temporarily value for calculations ----
	double Accuracy_Calc = 0;

	// ---- Calculate the accuracy of the fix in meters ----
	Accuracy_Calc = ((double)OwnPosition.Own_GPS_Data.HorizontalAccuracy) / (double) 1000.00;
	uint8_t H_Acc = (uint8_t) (ceil(Accuracy_Calc));

	PDSEventData[36] = H_Acc;

	memcpy((PDSEventData + 40), &OwnPosition.Own_GPS_Data.Latitude, 4);
	memcpy((PDSEventData + 44), &OwnPosition.Own_GPS_Data.Longitude, 4);
	memcpy(DataPointer, PDSEventData, sizeof(PDSEventData));

	return true;
}

bool App_Threat_GetWorkZoneEventData(uint8_t* DataPointer)
{
	// ---- Define temporarily value to store data in ----
	uint8_t WorkzoneEventData[16];

	// ---- Reset the values in the value to reserved ----
	memset(WorkzoneEventData, 0xFF, sizeof(WorkzoneEventData));

	// ---- Copy the work zone radius size in the data ----
	WorkzoneEventData[4] = (uint8_t) Local_Params[Local_Workzone_Raduis].ParamCURRENT ;

	// ---- Copy the center point longitude and latitude the data ----
	memcpy((WorkzoneEventData + 8), &System_Flags.System_Last_LAT, 4);
	memcpy((WorkzoneEventData + 12), &System_Flags.System_Last_LON, 4);

	// ---- Copy temporary data into into pointer recieved ----
	memcpy(DataPointer, WorkzoneEventData, sizeof(WorkzoneEventData));

	return true;
}
