/*
 * App_VisionControl.c
 *
 *  Created on: Apr 29, 2016
 *      Author: JacoOlivier
 */


#include "App_VisionControl.h"
#include "App_Threats.h"
#include "TagTypes.h"

_Transpondert*		TagList[PresentList_Max];

//Usable_Tag			Tags_Usable[Tag_List_Max];
_Transpondert*		PersonTagList[PresentList_Max];
_Transpondert*		RangerList[PresentList_Max];

Pulse_Tag			PresentList[PresentList_Max];
Pulse_Tag			Excluded_OwnTagList[Excluded_OwnTagList_Max];

//Externals
extern vision_device  	PULSE400_Module;
extern vision_device  	Ranging_Module;
extern vision_device* 	myReader;
extern vision_device* 	myRanger;
extern Parameter		Local_Params[];

#define (Local_Params[Local_LastLF].ParamCURRENT) 	5

/*-----------------------------------------
 *Function name and description
 *---------
 *Initialise Tag Lists
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/

void Init_VisionControl (void)
{

	//Initialise pulse tag components
	for(uint8_t i = 0; i < PresentList_Max; i++)
	{
		Vision_Clear_PulseTag (i);
//		Tags_Usable[i].Tag_Verified 	= false;
//		Tags_Usable[i].Tag_Active 		= false;
//		Tags_Usable[i].Transp_LastSeen 	= 0;
	}


	//Reset all list counters
	ControlCounters.AcceptedList_Counter = 0;
	ControlCounters.ActiveList_Counter = 0;
	ControlCounters.ExcludedList_Counter = 0;
	ControlCounters.ExcludedTag_Counter = 0;
	ControlCounters.OwnTag_Counter = 0;
	ControlCounters.PresentList_Counter = 0;
	ControlCounters.TagList_Counter = 0;
	ControlCounters.ThreatList_Counter = 0;
	ControlCounters.OnScreen_Counter = 0;
	ControlCounters.PassTags_Counter = 0; //TODO: Neil add to PRT document and new commander code
	ControlCounters.UsableTags_Counter = 0;

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

void Vision_Filter_Tags (void)
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
				TagList[ControlCounters.TagList_Counter] = Tag_Pulse;
				ControlCounters.TagList_Counter++;

			}
		}
	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 *Manage tags seen over RF
 *tags seen by RF
 *
 *Inputs:
 *---------
 * List of all tags seen over RF
 * Size of the list
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void Vision_PulseTag_Filter (void)
{
	bool InList = false;

	uint8_t Index;

	for(uint8_t i = 0; i < ControlCounters.TagList_Counter; i++)
	{
//		if(TagList[i].Tag_Verified)
		{
		if((check_bit(TagList[i]->status, 6)) || (TagList[i]->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT))
		{
			Index = Vision_FindInExcludedOwn(TagList[i]);

			if(Index == 0xFF)
				InList = false;
			else
				InList = true;

			if((InList))
			{
				Excluded_OwnTagList[Index].Tag_LastSeen = time_now();
				// FIXME : V8 create functions
//				// ---- Update LF history ----
//				Vision_Update_LF (TagList[i], Index);
//				// ---- Update RF history ----
//				Vision_Update_RF (TagList[i], Index);
				// ---- Set active flag of transponder ----

				//check if this tag is in an exclusion field
				if(check_bit(Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Transp->status, 6))
					Excluded_OwnTagList[Index].Tag_Excluded = true;
				else
					Excluded_OwnTagList[Index].Tag_Excluded = false;

				//check if this tag belongs to the system`s own tags
				if(TagList[i]->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT)
					Excluded_OwnTagList[Index].Tag_Owned = true;
				else
					Excluded_OwnTagList[Index].Tag_Owned = false;

				Excluded_OwnTagList[Index].Active = true;
			}
			else
			{
				// --- Add transponder to master threat list ----
				Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Transp = TagList[i];

				// ---- Set active flag of transponder ----
				Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Active = true;

				// ---- Update time stamps of transponder ----
				Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Tag_LastSeen = time_now();
				Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Tag_FirstSeen = time_now();

				// ---- Set first action of the transponder ----
				Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].PulseTagAction1 = Act_DisplayOnly;

				//Check if ranging
				if(Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Transp->kind == Ranging)
					Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Ranger = true;
				else
					Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Ranger = false;

				//check if this tag is in an exclusion field
				if(check_bit(Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Transp->status, 6))
					Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Tag_Excluded = true;
				else
					Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Tag_Excluded = false;

				//check if this tag belongs to the system`s own tags
				if(TagList[i]->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT)
					Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Tag_Owned = true;
				else
					Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Tag_Owned = false;

				// FIXME : V8 create functions
//				// ---- Start a LF history ----
//				Vision_Update_LF (TagList[i], ControlCounters.PresentList_Counter);
//				// ---- Start a RF history ----
//				Vision_Update_RF (TagList[i], ControlCounters.PresentList_Counter);

				Excluded_OwnTagList[ControlCounters.ExcludedOwnList_Counter].Active = true;

				//Increment list counter
				ControlCounters.ExcludedOwnList_Counter++;
			}
		}
		else
		{
			// ---- Check if tag is in Pulse400 list (updated when received from Pulse400)----
			Index = Vision_FindInPresent(TagList[i]);

			if(Index == 0xFF)
				InList = false;
			else
				InList = true;

			if((InList))
			{

				// ---- Removed for V8, populated into separate list ----
//				//check if this tag is in an exclusion field
//				if(check_bit(PresentList[Index].Transp->status, 6))
//					PresentList[Index].Tag_Excluded = true;
//				else
//					PresentList[Index].Tag_Excluded = false;
//
//				//check if this tag belongs to the system`s own tags
//				if(PresentList[Index].Transp->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT)
//					PresentList[Index].Tag_Owned = true;
//				else
//					PresentList[Index].Tag_Owned = false;

				PresentList[Index].Tag_LastSeen = time_now();
				// ---- Update LF history ----
				Vision_Update_LF (TagList[i], Index);
				// ---- Update RF history ----
				Vision_Update_RF (TagList[i], Index);
				// ---- Set active flag of transponder ----
				PresentList[Index].Active = true;
			}
			else
			{

				// --- Add transponder to master threat list ----
				PresentList[ControlCounters.PresentList_Counter].Transp = TagList[i];

				// ---- Set active flag of transponder ----
				PresentList[ControlCounters.PresentList_Counter].Active = true;

				// ---- Update time stamps of transponder ----
				PresentList[ControlCounters.PresentList_Counter].Tag_LastSeen = time_now();
				PresentList[ControlCounters.PresentList_Counter].Tag_FirstSeen = time_now();

				// ---- Set first action of the transponder ----
				PresentList[ControlCounters.PresentList_Counter].PulseTagAction1 = Act_DisplayOnly;

				//Check if ranging
				if(PresentList[ControlCounters.PresentList_Counter].Transp->kind == Ranging)
					PresentList[ControlCounters.PresentList_Counter].Ranger = true;
				else
					PresentList[ControlCounters.PresentList_Counter].Ranger = false;

				// ---- Removed for V8, populated into separate list ----
//				//check if this tag is in an exclusion field
//				if(check_bit(PresentList[ControlCounters.PresentList_Counter].Transp->status, 6))
//					PresentList[ControlCounters.PresentList_Counter].Tag_Excluded = true;
//				else
//					PresentList[ControlCounters.PresentList_Counter].Tag_Excluded = false;
//
//				//check if this tag belongs to the system`s own tags
//				if(TagList[i]->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT)
//					PresentList[ControlCounters.PresentList_Counter].Tag_Owned = true;
//				else
//					PresentList[ControlCounters.PresentList_Counter].Tag_Owned = false;

				// ---- Start a LF history ----
				Vision_Update_LF (TagList[i], ControlCounters.PresentList_Counter);
				// ---- Start a RF history ----
				Vision_Update_RF (TagList[i], ControlCounters.PresentList_Counter);

				PresentList[ControlCounters.PresentList_Counter].Active = true;

				//Increment list counter
				ControlCounters.PresentList_Counter++;
			}
		}
		}

	}

	//list sorting : based on last seen (RF), deactivate flag, remove invalid/old entries
	Vision_PulseTag_Sort ();

}

/*-----------------------------------------
 *Function name and description
 *---------
 *Manage tags seen over RF
 *tags seen by RF
 *
 *Inputs:
 *---------
 * List of all tags seen over RF
 * Size of the list
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void Vision_ExcludedOwnTag_Filter (void)
{
	bool InList = false;

	uint8_t Index;

	for(uint8_t i = 0; i < ControlCounters.ExcludedOwnList_Counter; i++)
	{
//		if(TagList[i].Tag_Verified)
		{
			// ---- Check if tag is in Pulse400 list (updated when received from Pulse400)----
			Index = Vision_FindInPresent (TagList[i]);

			if(Index == 0xFF)
				InList = false;
			else
				InList = true;

			if((InList))
			{

				// ---- Removed for V8, populated into separate list ----
//				//check if this tag is in an exclusion field
//				if(check_bit(PresentList[Index].Transp->status, 6))
//					PresentList[Index].Tag_Excluded = true;
//				else
//					PresentList[Index].Tag_Excluded = false;
//
//				//check if this tag belongs to the system`s own tags
//				if(PresentList[Index].Transp->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT)
//					PresentList[Index].Tag_Owned = true;
//				else
//					PresentList[Index].Tag_Owned = false;

				PresentList[ControlCounters.PresentList_Counter].Tag_LastSeen = time_now();
				// ---- Update LF history ----
				Vision_Update_LF (TagList[i], Index);
				// ---- Update RF history ----
				Vision_Update_RF (TagList[i], Index);
				// ---- Set active flag of transponder ----
				PresentList[Index].Active = true;
			}
			else
			{

				// --- Add transponder to master threat list ----
				PresentList[ControlCounters.PresentList_Counter].Transp = TagList[i];
				// ---- Set active flag of transponder ----
				PresentList[ControlCounters.PresentList_Counter].Active = true;

				PresentList[ControlCounters.PresentList_Counter].Tag_LastSeen = time_now();
				PresentList[ControlCounters.PresentList_Counter].Tag_FirstSeen = time_now();
				PresentList[ControlCounters.PresentList_Counter].PulseTagAction1 = Act_DisplayOnly;
				//Check if ranging
				if(PresentList[ControlCounters.PresentList_Counter].Transp->kind == Ranging)
					PresentList[ControlCounters.PresentList_Counter].Ranger = true;
				else
					PresentList[ControlCounters.PresentList_Counter].Ranger = false;

				// ---- Removed for V8, populated into separate list ----
//				//check if this tag is in an exclusion field
//				if(check_bit(PresentList[ControlCounters.PresentList_Counter].Transp->status, 6))
//					PresentList[ControlCounters.PresentList_Counter].Tag_Excluded = true;
//				else
//					PresentList[ControlCounters.PresentList_Counter].Tag_Excluded = false;
//
//				//check if this tag belongs to the system`s own tags
//				if(TagList[i]->VehicleID == (uint16_t)Local_Params[Local_VID].ParamCURRENT)
//					PresentList[ControlCounters.PresentList_Counter].Tag_Owned = true;
//				else
//					PresentList[ControlCounters.PresentList_Counter].Tag_Owned = false;

				// ---- Start a LF history ----
				Vision_Update_LF (TagList[i], ControlCounters.PresentList_Counter);
				// ---- Start a RF history ----
				Vision_Update_RF (TagList[i], ControlCounters.PresentList_Counter);

				PresentList[Index].Active = true;

				//Increment list counter
				ControlCounters.PresentList_Counter++;

			}
		}

	}

	//list sorting : based on last seen (RF), deactivate flag, remove invalid/old entries
	Vision_PulseTag_Sort ();

}

void Vision_PulseTag_Sort (void)
{

	uint8_t i, pass;
	uint8_t Removed = 0;
	Pulse_Tag hold;

	for(uint8_t j = 0; j < ControlCounters.PresentList_Counter; j++)
	{
		if(PresentList[j].Active)
		{
			PresentList[j].Active = false;	//clear active flag
			PresentList[j].Tag_LastSeen = time_now();

		}
		else
		{
			if(time_since(PresentList[j].Tag_LastSeen) > 5*Seconds)
			{
				//Clear Pulse Tag
				Vision_Clear_PulseTag(j);
				Removed++;
			}
		}

	}

	for(pass = 0; pass < ControlCounters.PresentList_Counter; pass++)
	{

		for(i = 0; i < (ControlCounters.PresentList_Counter - 1); i++)
		{
			if((PresentList[i].Transp->rssi) < (PresentList[i + 1].Transp->rssi)) //(PresentList[i].Transp->LF.RSSI) < (PresentList[i + 1].Transp->LF.RSSI) (PresentList[i].Transp->rssi) < (PresentList[i + 1].Transp->rssi)
			{
				hold = PresentList[i];

				PresentList[i] = PresentList[i + 1];

				PresentList[i + 1] = hold;
			}
		}

	}

	ControlCounters.PresentList_Counter -= Removed;

	Removed = 0;

	for(uint8_t j = 0; j < ControlCounters.ExcludedOwnList_Counter; j++)
	{
		if(Excluded_OwnTagList[j].Active)
		{
			Excluded_OwnTagList[j].Active = false;	//clear active flag
			Excluded_OwnTagList[j].Tag_LastSeen = time_now();

		}
		else
		{
			if(time_since(Excluded_OwnTagList[j].Tag_LastSeen) > 5*Seconds)
			{
				//Clear Pulse Tag
				Vision_Clear_ExcludedOwnTag(j);
				Removed++;
			}
		}

	}

	for(pass = 0; pass < ControlCounters.ExcludedOwnList_Counter; pass++)
	{

		for(i = 0; i < (ControlCounters.ExcludedOwnList_Counter - 1); i++)
		{
			if((Excluded_OwnTagList[i].Transp->rssi) < (Excluded_OwnTagList[i + 1].Transp->rssi)) //(PresentList[i].Transp->LF.RSSI) < (PresentList[i + 1].Transp->LF.RSSI) (PresentList[i].Transp->rssi) < (PresentList[i + 1].Transp->rssi)
			{
				hold = Excluded_OwnTagList[i];

				Excluded_OwnTagList[i] = Excluded_OwnTagList[i + 1];

				Excluded_OwnTagList[i + 1] = hold;
			}
		}

	}

	ControlCounters.ExcludedOwnList_Counter -= Removed;
}

void Vision_MultiTag_Handler (Pulse_Tag List[])
{

	uint8_t i, pass;

	for(pass = 0; pass < ControlCounters.PresentList_Counter; pass++)
	{

		for(i = pass+1; i < ControlCounters.PresentList_Counter; i++)
		{
			//apply only to vehicle tags
			if(List[pass].Transp->VehicleID != 0)
			{
				if((List[pass].Transp->VehicleID) == (List[i].Transp->VehicleID))
				{
					if((List[pass].Transp->LF.RSSI) >= (List[i].Transp->LF.RSSI))
					{
						//Clear Pulse Tag
						Vision_Clear_PulseTag(i);
					}
					else
					{
						//Clear Pulse Tag
						Vision_Clear_PulseTag(pass);
					}
				}
			}
		}

	}

}

void Vision_Clear_PulseTag (uint8_t Index)
{

	//Clear all transponder that are too old from transp log
	clean_transp_log(Local_Params[Local_LastRF].ParamCURRENT);

	for(uint8_t i = 0; i < TAG_System_MAX; i++)
	{
		for(uint8_t j = 0; j < Local_Params[Local_LF_Smoothing].ParamCURRENT; j++)
		{
			PresentList[Index].RSSI_Archive[i][j] = 0;
			PresentList[Index].RF_Archive[i].RSSI = 0;
			PresentList[Index].RF_Archive[i].last_RF = 0;
		}

		PresentList[Index].Archive_Count[i] = 0;

		PresentList[Index].LF_History[i].RSSI = 0;
		PresentList[Index].LF_History[i].SlaveID = 0;
		PresentList[Index].LF_History[i].VehicleID = 0;
		PresentList[Index].LF_History[i].last_LF = 0;
	}

	PresentList[Index].Tag_LastSeen = 0;
	PresentList[Index].RF_Count = 0;
	PresentList[Index].Active = false;
	PresentList[Index].Tag_Owned = false;
	PresentList[Index].Tag_Excluded = false;
	PresentList[Index].FarField = false;
	PresentList[Index].Tag_FirstSeen = 0;
	PresentList[Index].PulseTagAction1 = Act_None;
	PresentList[Index].PulseTagAction2 = Act_None;
	PresentList[Index].PulseTagAction3 = Act_None;
	PresentList[Index].PulseTagActionTime1_2 = 2000;
	PresentList[Index].PulseTagActionTime2_3 = 5000;
}

void Vision_Clear_ExcludedOwnTag (uint8_t Index)
{

	//Clear all transponder that are too old from transp log
	clean_transp_log(Local_Params[Local_LastRF].ParamCURRENT);

	for(uint8_t i = 0; i < TAG_System_MAX; i++)
	{
		for(uint8_t j = 0; j < Local_Params[Local_LF_Smoothing].ParamCURRENT; j++)
		{
			Excluded_OwnTagList[Index].RSSI_Archive[i][j] = 0;
			Excluded_OwnTagList[Index].RF_Archive[i].RSSI = 0;
			Excluded_OwnTagList[Index].RF_Archive[i].last_RF = 0;
		}

		Excluded_OwnTagList[Index].Archive_Count[i] = 0;

		Excluded_OwnTagList[Index].LF_History[i].RSSI = 0;
		Excluded_OwnTagList[Index].LF_History[i].SlaveID = 0;
		Excluded_OwnTagList[Index].LF_History[i].VehicleID = 0;
		Excluded_OwnTagList[Index].LF_History[i].last_LF = 0;
	}

	Excluded_OwnTagList[Index].Tag_LastSeen = 0;
	Excluded_OwnTagList[Index].RF_Count = 0;
	Excluded_OwnTagList[Index].Active = false;
	Excluded_OwnTagList[Index].Tag_Owned = false;
	Excluded_OwnTagList[Index].Tag_Excluded = false;
	Excluded_OwnTagList[Index].FarField = false;
	Excluded_OwnTagList[Index].Tag_FirstSeen = 0;
	Excluded_OwnTagList[Index].PulseTagAction1 = Act_None;
	Excluded_OwnTagList[Index].PulseTagAction2 = Act_None;
	Excluded_OwnTagList[Index].PulseTagAction3 = Act_None;
	Excluded_OwnTagList[Index].PulseTagActionTime1_2 = 2000;
	Excluded_OwnTagList[Index].PulseTagActionTime2_3 = 5000;
}

uint8_t Vision_FindInPresent (_Transpondert* Tag)
{
	for(uint8_t i = 0; i < ControlCounters.PresentList_Counter; i++)
	{
		if(PresentList[i].Transp->UID == Tag->UID)
		{
			return i;
			break;
		}
	}

	return 0xFF;
}

uint8_t Vision_FindInExcludedOwn (_Transpondert* Tag)
{
	for(uint8_t i = 0; i < ControlCounters.ExcludedOwnList_Counter; i++)
	{
		if(Excluded_OwnTagList[i].Transp->UID == Tag->UID)
		{
			return i;
			break;
		}
	}

	return 0xFF;
}

uint8_t Vision_FindVID (uint16_t VID)
{
	for(uint8_t i = 0; i < ControlCounters.PresentList_Counter; i++)
	{
		if(TagList[i]->VehicleID == VID)
		{
			return i;
			break;
		}
	}

	return 0xFF;
}


/*-----------------------------------------
 *Function name and description
 *---------
 *Filter RF seen tags and sort into
 *a LF list with
 *List[0]   -> Highest LF
 *List[255] -> Lowest LF
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/

void Vision_Sort_VLF (_Transpondert* RF_Tags[])
{

	uint8_t i, pass;

	_Transpondert* hold;

	for(pass = 0; pass < ControlCounters.TagList_Counter; pass++)
	{

		for(i = 0; i < (ControlCounters.TagList_Counter - 1); i++)
		{
			if((RF_Tags[i]->LF.RSSI < RF_Tags[i + 1]->LF.RSSI))
			{
				hold = RF_Tags[i];

				RF_Tags[i] = RF_Tags[i + 1];

				RF_Tags[i + 1] = hold;
			}
			else if((RF_Tags[i]->LF.RSSI == RF_Tags[i + 1]->LF.RSSI))
			{
				if(time_since((RF_Tags[i]->LF.last_LF) > time_since(RF_Tags[i + 1]->LF.last_LF)))
				{
					hold = RF_Tags[i];

					RF_Tags[i] = RF_Tags[i + 1];

					RF_Tags[i + 1] = hold;
				}
			}
		}

	}


}

/*-----------------------------------------
 *Function name and description
 *---------
 *Update VLF source information
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
void Vision_Update_GPS (_Transpondert* Tag, uint8_t Index)
{
	//	double Distance_Threat;
	//	uint16_t Distance_Actual;
	//
	//	//Only apply the GPS update to GPS capable tags
	//	if(Tag->kind == Pulse_GPS)
	//	{
	//		//Calculate direct distance from own vehicle to threat);
	//		Distance_Threat = App_GPS_ReturnDistance(OwnPosition.Own_GPS_Data.Latitude_deg, OwnPosition.Own_GPS_Data.Longitude_deg, Tag->GPS_Data.Latitude_deg, Tag->GPS_Data.Longitude_deg);
	//		if(Distance_Threat != -1)
	//		{
	//			Distance_Actual = (uint16_t)Distance_Threat;
	//
	//			if(PresentList[Index].GPS_Count < Local_Params[Local_LF_Smoothing].ParamCURRENT)
	//			{
	//				PresentList[Index].GPS_Distance[PresentList[Index].GPS_Count] = Distance_Actual;
	//				PresentList[Index].GPS_Count++;
	//			}
	//			else
	//			{
	//				PresentList[Index].GPS_Count = 0;
	//				PresentList[Index].GPS_Distance[PresentList[Index].GPS_Count] = Distance_Actual;
	//				PresentList[Index].GPS_Count++;
	//			}
	//		}
	//	}
}

/*-----------------------------------------
 *Function name and description
 *---------
 *Update VLF source information
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
void Vision_Update_RF (_Transpondert* Tag, uint8_t Index)
{
	//Update LF archive only when a newer value is received or if it is a first entry
	if((Tag->last_seen > RF_ReturnHighestTime(PresentList[Index].RF_Archive))) //PresentList[Index].RF_Archive[PresentList[Index].RF_Count].last_RF)
	{
		if(PresentList[Index].RF_Count < Local_Params[Local_LF_Smoothing].ParamCURRENT)
		{
			PresentList[Index].RF_Archive[PresentList[Index].RF_Count].RSSI = Tag->rssi;
			PresentList[Index].RF_Archive[PresentList[Index].RF_Count].last_RF = Tag->last_seen;
			PresentList[Index].RF_Count++;
		}
		else
		{
			PresentList[Index].RF_Count = 0;
			PresentList[Index].RF_Archive[PresentList[Index].RF_Count].RSSI = Tag->rssi;
			PresentList[Index].RF_Archive[PresentList[Index].RF_Count].last_RF = Tag->last_seen;
			PresentList[Index].RF_Count++;
		}
	}
}


/*-----------------------------------------
 *Function name and description
 *---------
 *Update VLF source information
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
void Vision_Update_LF (_Transpondert* Tag, uint8_t Index)
{
	uint8_t VLF_Source;
	if((Tag->LF.RSSI > Local_Params[Local_Threshold_LF].ParamCURRENT) && (Tag->LF.VehicleID == Local_Params[Local_VID].ParamCURRENT))
	{
		switch(PresentList[Index].Transp->LF.SlaveID)
		{

		case Front_Tag_SID:

			VLF_Source = Front_Tag;
			break;

		case Rear_Tag_SID:

			VLF_Source = Rear_Tag;
			break;

		case Left_Tag_SID:

			VLF_Source = Left_Tag;
			break;

		case Right_Tag_SID:

			VLF_Source = Right_Tag;
			break;

		default:

			VLF_Source = 0xFF;
			break;
		}

		if(VLF_Source != 0xFF)
		{
			//Update LF archive only when a newer value is received or if it is a first entry
			if((Tag->LF.last_LF != PresentList[Index].LF_History[VLF_Source].last_LF)) //if(((Tag->LF.RSSI != PresentList[Index].RSSI_Archive[VLF_Source][(PresentList[Index].Archive_Count[VLF_Source] - 1)])))
			{
				if(PresentList[Index].Archive_Count[VLF_Source] < Local_Params[Local_LF_Smoothing].ParamCURRENT)
				{
					PresentList[Index].RSSI_Archive[VLF_Source][PresentList[Index].Archive_Count[VLF_Source]] = Tag->LF.RSSI;
					PresentList[Index].Archive_Count[VLF_Source]++;
				}
				else
				{
					PresentList[Index].Archive_Count[VLF_Source] = 0;
					PresentList[Index].RSSI_Archive[VLF_Source][PresentList[Index].Archive_Count[VLF_Source]] = Tag->LF.RSSI;
					PresentList[Index].Archive_Count[VLF_Source]++;
				}

				PresentList[Index].LF_History[VLF_Source].RSSI = LF_ReturnHighest(PresentList[Index].RSSI_Archive[VLF_Source]);
				PresentList[Index].LF_History[VLF_Source].SlaveID = Tag->LF.SlaveID;
				PresentList[Index].LF_History[VLF_Source].last_LF = Tag->LF.last_LF;
				PresentList[Index].LF_History[VLF_Source].VehicleID = Tag->LF.VehicleID;
			}
		}

	}

	//Verify all lf entries
	for(uint8_t j = 0; j < TAG_System_MAX; j++)
	{
		PresentList[Index].LF_History[j] = Vision_LFVerify (PresentList[Index].LF_History[j]);

		if(PresentList[Index].LF_History[j].RSSI == -1)
		{
			for(uint8_t k = 0; k < Local_Params[Local_LF_Smoothing].ParamCURRENT; k++)
			{
				PresentList[Index].RSSI_Archive[j][k] = 0;
			}

			PresentList[Index].Archive_Count[j] = 0;

		}
	}

	//	//Check if this tag is seen purely over RF
	//	if((PresentList[Index].LF_History[Front_Tag].RSSI == -1) && (PresentList[Index].LF_History[Rear_Tag].RSSI == -1) && (PresentList[Index].LF_History[Right_Tag].RSSI == -1) && (PresentList[Index].LF_History[Left_Tag].RSSI == -1))
	//		PresentList[Index].FarField = true;
	//	else
	//		PresentList[Index].FarField = false;


}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function verifies an RF entry
 *
 *Inputs:
 *---------
 * RSSI Array
 *
 *Outputs:
 *---------
 * Maximum value
 *-----------------------------------------*/
uint8_t RF_ReturnHighestRSSI (RF_message_type RF_Data[])
{
	uint8_t MAX = 0;

	for(uint8_t i = 0; i < Local_Params[Local_LF_Smoothing].ParamCURRENT; i++)
	{
		if(RF_Data[i].RSSI > MAX)
			MAX = RF_Data[i].RSSI;
	}

	return MAX;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function check for the smallest distance measured
 *
 *Inputs:
 *---------
 * GPS distance array
 *
 *Outputs:
 *---------
 * Smallest distance
 *-----------------------------------------*/
uint16_t GPS_ReturnSmallestDist (uint16_t GPS_Data[])
{
	uint8_t MIN = GPS_Data[0];

	for(uint8_t i = 0; i < Local_Params[Local_LF_Smoothing].ParamCURRENT; i++)
	{
		if(GPS_Data[i] < MIN)
			MIN = GPS_Data[i];
	}

	return MIN;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function verifies an RF entry
 *
 *Inputs:
 *---------
 * RSSI Array
 *
 *Outputs:
 *---------
 * Maximum value
 *-----------------------------------------*/
uint32_t RF_ReturnHighestTime (RF_message_type RF_Data[])
{
	uint32_t MAX = 0;

	for(uint8_t i = 0; i < Local_Params[Local_LF_Smoothing].ParamCURRENT; i++)
	{
		if(RF_Data[i].last_RF > MAX)
			MAX = RF_Data[i].last_RF;
	}

	return MAX;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function verifies an LF entry
 *
 *Inputs:
 *---------
 * RSSI Array
 *
 *Outputs:
 *---------
 * Maximum value
 *-----------------------------------------*/
uint8_t LF_ReturnHighest (uint8_t RSSI[])
{
	uint8_t MAX = 0;

	for(uint8_t i = 0; i < Local_Params[Local_LF_Smoothing].ParamCURRENT; i++)
	{
		if(RSSI[i] > MAX)
			MAX = RSSI[i];
	}

	return MAX;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function verifies an LF entry
 *
 *Inputs:
 *---------
 * Pulse Tag
 *
 *Outputs:
 *---------
 * Position
 *-----------------------------------------*/
LF_message_type Vision_LFVerify (LF_message_type LF)
{
	LF_message_type LF_Checked;

	if((time_since(LF.last_LF) > Local_Params[Local_LastLF].ParamCURRENT*Seconds))
	{
		LF_Checked.RSSI = -1;	//-1 indicates seen only over RF, refer to "Vision_PulseTag_Filter"
		LF_Checked.SlaveID = 0;
		LF_Checked.VehicleID = 0;
		LF_Checked.last_LF = 0;

		return LF_Checked;
	}
	else
	{
		LF_Checked = LF;
		return LF_Checked;
	}
}

void PulseTag_Actions(void)
{
	for(int i = 0; i < ControlCounters.PresentList_Counter; i++)
	{
		if (time_since(PresentList[i].Tag_FirstSeen) > PresentList[i].PulseTagActionTime1_2)
		{
			PresentList[i].PulseTagAction2 = Act_ForceSlow;
		}
		if (time_since(PresentList[i].Tag_FirstSeen) > PresentList[i].PulseTagActionTime2_3)
		{
			PresentList[i].PulseTagAction3 = Act_ForceStop;
		}
	}
}
