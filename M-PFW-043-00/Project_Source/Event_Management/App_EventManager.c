/*
 * App_EventManager.c
 *
 *  Created on: May 30, 2016
 *      Author: JacoOlivier
 */

#include "App_EventManager.h"
#include "App_Railbound_Events.h"
#include "App_Threats.h"

//#include "App_SystemControl.h"

Event 	EventList[evSize];

evList	evGroups[evGroupSize];
evList	evMessages[evGroupSize];

evList	evScreen[evScreenSize];

extern Event*	Active_Event;
extern Threat* 	Active_Threat;

void App_EventManager_Init(void)
{
	//clear all event active flags
	for(int i = 0; i < evSize; i++)
	{
		EventList[i].EventActive = false;
		EventList[i].EventLogged = false;
		EventList[i].ACKReceived = false;
		EventList[i].Processed = false;
		memset(EventList[i].EventData, 0xFF, sizeof(EventList[i].EventData));
	}

	// ---- Switch event initialize handler ----
	// ---- TODO: Insert function to get current application ----
	switch(1)
	{
		// ---- Handle the railbound system control events ----
		default:

			App_Railbound_Events_Init();

			break;
	}

	Active_Event = &EventList[EV_Empty];
}

void App_EventControl (void)
{
	// ---- Handle all event flags (set events) ----
	App_EventHandler();

	// ---- Update all events in group lists ----
	App_EventManageUpdates();

	// ---- Handle Active Events ----
	App_EventHandleActives();
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function handles all active events
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventHandleActives(void)
{
	uint8_t Most_Important = 0;
	uint16_t ApplyEventID = 0, SplashEventID = 0;

	Most_Important = App_EventDetermineMostImportantEventGroup();
	ApplyEventID 	= App_EventDetermineApplyID();
	SplashEventID	= App_EventDetermineSplashID();

	// ---- Clear active events processed flags when higher priority events occur ----
	for (uint8_t i = 0; i < evGroupSize - 1; i++)
	{
		if(evGroups[i].evCounter > 0)
			EventList[evGroups[i + 1].evIndex[0]].Processed = false;
	}

	// ---- If the most important group's action is greater than the lowest action in the enum, apply event ID ----
	if (App_EventDetermineMostImportantAction(evGroups[Most_Important].evIndex[0]) > Act_DisplayOnly)
	{
		// ---- Process event data, update active event / splash event ----
		App_EventProcess(ApplyEventID, SplashEventID);
	}
	// ----- If the most important event in each group has the display action, handle accordingly ----
	else
	{
		// ----- Apply events based on event group priority, if there are an active event in the group ----
		if (evGroups[Type_Internal].evCounter > 0)
		{
			// ---- Process event data, update active event / splash event ----
			App_EventProcess(evGroups[Type_Internal].evIndex[0], SplashEventID);
		}
		else if (evGroups[Type_System].evCounter > 0)
		{
			// ---- Process event data, update active event / splash event ----
			App_EventProcess(evGroups[Type_System].evIndex[0], SplashEventID);
		}
		else if (evGroups[Type_Operational].evCounter > 0)
		{
			// ---- Process event data, update active event / splash event ----
			App_EventProcess(evGroups[Type_Operational].evIndex[0], SplashEventID);
		}
		else if (evGroups[Type_Vehicle].evCounter > 0)
		{
			// ---- Process event data, update active event / splash event ----
			App_EventProcess(evGroups[Type_Vehicle].evIndex[0], SplashEventID);
		}
		else if (evGroups[Type_PDS].evCounter > 0)
		{
			// ---- Process event data, update active event / splash event ----
			App_EventProcess(evGroups[Type_PDS].evIndex[0], SplashEventID);
		}
		else
		{

		}
	}
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function handles all active events
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * Index of evGroup
 *-------------------------------------------------------------*/
uint8_t App_EventDetermineMostImportantEventGroup (void)
{

	uint8_t Index, Action = 0, ActionMost = 0;

	for(uint8_t i = 1; i < evGroupSize; i++)
	{
		Action = App_EventReferenceDetermineMostImportantAction(&EventList[evGroups[i].evIndex[0]]);

		if (Action > ActionMost)
		{
			ActionMost = Action;
			Index = i;
		}
	}

	return Index;

}

uint16_t App_EventDetermineApplyID (void)
{
	// ---- Create temporary variables to store values in ----
	uint8_t Action = 0, ActionMost = 0;
	uint16_t Index = 0;

	// ---- Since all the groups are prioritized so only compare the first indexes of the groups ----
	for(uint8_t i = 1; i < evGroupSize; i++)
	{
		// ---- Determine the most import action ----
		Action = App_EventReferenceDetermineMostImportantAction(&EventList[evGroups[i].evIndex[0]]);

		// ---- If the action has a greater priority ----
		if (Action > ActionMost)
		{
			// ---- Keep track of the most important action and group index ----
			ActionMost = Action;
			Index = evGroups[i].evIndex[0];
		}
	}

	// ---- Return the group with the most important action ----
	return Index;
}

uint16_t App_EventDetermineSplashID (void)
{
	for(uint8_t i = Disp_Generic_SplashScreen; i <= Disp_Dedicated_SplashScreen; i++)
	{
		for (uint8_t j = 0 ; j < evScreen[i].evCounter; j++)
		{
			if ((evScreen[i].evCounter) && (EventList[evScreen[i].evIndex[j]].SplashActive))
			{
				return evScreen[i].evIndex[j];
			}
		}
	}

	return 0;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function handles all active events
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * Index of evGroup
 *-------------------------------------------------------------*/
uint8_t App_EventDetermineMostImportantAction(uint16_t evAction)
{
	// ---- Create a temporary value to store the of the most important action in ----
	uint8_t Action = Act_None;

	// ---- Check if the acknowledgment of the event is not set ----
	if (EventList[evAction].ACKReceived == false)
	{
		// ---- Check the if action 1 has bigger priority ----
		if (EventList[evAction].EventAction1 > Action)
		{
			Action = EventList[evAction].EventAction1;
		}

		// ---- Check the if action 2 has bigger priority, and if the time have elapsed ----
		if ((EventList[evAction].EventAction2 > Action) && (time_since(EventList[evAction].TimeStampSystic) >= EventList[evAction].EventActionTime1_2))
		{
			Action = EventList[evAction].EventAction2;
		}

		// ---- Check the if action 3 has bigger priority, and if the time have elapsed ----
		if ((EventList[evAction].EventAction3 > Action) && (time_since(EventList[evAction].TimeStampSystic) >= EventList[evAction].EventActionTime2_3))
		{
			Action = EventList[evAction].EventAction3;
		}
	}
	// ---- Check if the acknowledgment of the event is set ----
	else
	{
		Action = (uint8_t) EventList[evAction].EventACKAction;
	}

	// ---- Return the biggest priority action ----
	return Action;
}

uint8_t App_EventReferenceDetermineMostImportantAction(Event* ActionEvent)
{
	// ---- Create a temporary variable to store the most important action in ----
	uint8_t Action = 0;

	// ---- Check if the acknowledgment of the event is not set ----
	if (ActionEvent->ACKReceived == false)
	{
		// ---- Check if action 1 is greater than the temporary action ----
		if (ActionEvent->EventAction1 > Action)
		{
			Action = (uint8_t) ActionEvent->EventAction1;
		}

		// ---- Check if action 2 is greater than the temporary action, and if time has elapsed ----
		if (((uint8_t) ActionEvent->EventAction2 > Action) && (time_since(ActionEvent->TimeStampSystic) >= ActionEvent->EventActionTime1_2))
		{
			Action = (uint8_t) ActionEvent->EventAction2;
		}

		// ---- Check if action 3 is greater than the temporary action, and if time has elapsed ----
		if (((uint8_t) ActionEvent->EventAction3 > Action) && (time_since(ActionEvent->TimeStampSystic) >= ActionEvent->EventActionTime2_3))
		{
			Action = (uint8_t) ActionEvent->EventAction3;
		}
	}
	// ---- Check if the acknowledgment of the event is set ----
	else
	{
		Action = (uint8_t) ActionEvent->EventACKAction;
	}

	// ---- Return the most important action (temporary value) ----
	return Action;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function processes all data of the current event
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventProcess(uint16_t ApplyEvent, uint16_t SplashEvent)
{
	// ---- Display the event, splash screen take priority over active event ----
	App_EventDisplay(ApplyEvent, SplashEvent);

	// ---- Apply the event however required ----
	App_EventApply(ApplyEvent);

	//Handle acknowledgment actions
	App_EventACK(ApplyEvent);
}

void App_EventDisplay(uint16_t ApplyEventActive, uint16_t SplashEventActive)
{
	// ---- Create static values to keep track of the current splash event is active ----
	static uint32_t SplashDuration = 0;
	static bool SplashScreenActive = false;

	// ---- Check if there are a splash event that is active in the event list, received ----
	if (SplashEventActive != EV_Empty)
	{
		// ---- Check if a splash screen has not been activated, If splash screen is not already the event displayed  ----
		if ((!SplashScreenActive) && (ActiveDisplay_Event->EventID != EventList[SplashEventActive].EventID))
		{
			// ---- Update reference to active display event ----
			ActiveDisplay_Event = &EventList[SplashEventActive];

			// ---- Update local variables to inform the function a splash screen is active ----
			SplashDuration = time_now();
			SplashScreenActive = true;
		}
		else
		{
			// ---- Check if the time since the splash screen has stared elapsed, or if the event is not active ----
			if ((time_since(SplashDuration) >= ActiveDisplay_Event->SplashTime) || (!ActiveDisplay_Event->EventActive))
			{
				// ---- De-activate the event splash screen ----
				ActiveDisplay_Event->SplashActive = false;

				// ---- Update local variables to inform the function a splash screen is not active anymore ----
				SplashDuration = 0;
				SplashScreenActive = false;
			}
		}
	}
	else
	{
		// ---- Update reference to active display event ----
		ActiveDisplay_Event = &EventList[ApplyEventActive];

		// ---- Update local variables to inform the function a splash screen is not active anymore----
		SplashDuration = 0;
		SplashScreenActive = false;
	}
}

uint16_t App_EventScreenGetContentGroup(void)
{
	// ---- Return display content group of event ----
	return ActiveDisplay_Event->EventCategory;
}

uint8_t App_EventScreenGetDsipType(void)
{
	// ---- Return display type of event ----
	return ActiveDisplay_Event->DispType;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function applies all details contained in the event
 *Inputs:
 *---------
 * Event list
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventBuzzer(uint16_t ApplyEventActive)
{

//	//Configure the buzzer
//	if((EventList[ApplyEventActive].BuzzerRequired) && (!BuzzerFlags.BuzzerActive))
//	{
//		BuzzerFlags.BuzzerActive = true;
//		BuzzerFlags.BuzzerCounter = 0;
//		BuzzerFlags.BuzzerUpdateLast = time_now();
//	}
//	else if((!EventList[ApplyEventActive].BuzzerRequired))
//	{
//		BuzzerFlags.BuzzerActive = false;
//		BuzzerFlags.BuzzerCounter = 0;
//	}
//
//	//Update only if the mode is different from before
//	if(BuzzerFlags.BuzzerMode != EventList[ApplyEventActive].BuzzerMode)
//	{
//		BuzzerFlags.BuzzerMode = EventList[ApplyEventActive].BuzzerMode;
//		BuzzerFlags.BuzzerUpdateLast = time_now();
//	}

}


/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function applies all details contained in the event
 *Inputs:
 *---------
 * Event list
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventApply(uint16_t ApplyEventActive)
{

	// ---- Check if the current event is not already processed , and that the event is not the EV_Empty (no event) ----
	if((!EventList[ApplyEventActive].Processed) && (ApplyEventActive != EV_Empty))
	{
//		//Configure the buzzer
//		if((EventList[ApplyEventActive].BuzzerRequired) && (!BuzzerFlags.BuzzerActive))
//		{
//			BuzzerFlags.BuzzerActive = true;
//			BuzzerFlags.BuzzerCounter = 0;
//			BuzzerFlags.BuzzerUpdateLast = time_now();
//		}
//		else if((!EventList[ApplyEventActive].BuzzerRequired))
//		{
//			BuzzerFlags.BuzzerActive = false;
//			BuzzerFlags.BuzzerCounter = 0;
//		}
//
//		//Update only if the mode is different from before
//		if(BuzzerFlags.BuzzerMode != EventList[ApplyEventActive].BuzzerMode)
//		{
//			BuzzerFlags.BuzzerMode = EventList[ApplyEventActive].BuzzerMode;
//			BuzzerFlags.BuzzerUpdateLast = time_now();
//		}

		// ---- Clear previous active event processed flag ----
		Active_Event->Processed = false;

		// ---- Update System State Machine ----
		//System_State_Machine();

		// ---- Set current active event processed flag ----
		EventList[ApplyEventActive].Processed = true;

		// ---- Point reference to the current active and display event -----
		Active_Event = &EventList[ApplyEventActive];

	}

	// ---- Apply active event actions (most important one) ----
	// ---- TODO: Switching from warning to critical does not clear the processed flag ----
	//App_SystemControl_ApplyAction((uint8_t*) Active_Event);
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function checks if an event that requires an
 * acknowledge is processed properly
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventACK (uint16_t AcknowledgeEventActive)
{
//	//Event Ignored and Received IDs reside at event ID + 1 and event ID + 2, respectively
//	uint8_t ACK_Ignored = AcknowledgeEventActive + 1;
//	uint8_t ACK_Received = AcknowledgeEventActive + 2;
//
//	if(EventList[AcknowledgeEventActive].ACKRequired)
//	{
//		//Required time has expired
//		if ((time_since(EventList[AcknowledgeEventActive].TimeStampSystic) > EventList[AcknowledgeEventActive].TimeRequired * Seconds))
//		{
////			//trigger acknowledge ignored event
////			App_EventSet(ACK_Ignored);
//		}
//		//Acknowledge received within required time
//		else if((((time_since(EventList[AcknowledgeEventActive].TimeStampSystic)) < (EventList[AcknowledgeEventActive].TimeRequired * Seconds)) && (App_ACK_CheckFlag (ACK_CAS))))
//		{
//			//trigger acknowledge received event
//			App_EventSetACK (AcknowledgeEventActive);
//			//App_EventSet(ACK_Received);
//		}
//		//		//Event is ignored, but still active
//		//		else if((EventList[EV_ACK_Ignored_CAS].EventActive))
//		//		{
//		//			App_EventClear(ACK_Ignored);
//		//		}
//		//		//Event has successfully been acknowledged
//		//		else if(EventList[EV_ACK_Received_CAS].EventActive)
//		//		{
//		//			App_EventClear(ACK_Received);
//		//			EventList[evGroup.evIndex[0]].ACKReceived = true;
//		//		}
//
//	}
//	else
//	{
////		//Process the event if it has not yet been processed
////		if((App_ACK_CheckFlag (ACK_CAS)) && (!User_Button[ACK_CAS].ACK_Processed))
////		{
////			EventList[AcknowledgeEventActive].ACKReceived = true;
////			User_Button[ACK_CAS].ACK_Processed = true;
////		}
////		else
////			EventList[AcknowledgeEventActive].ACKReceived = false;
//
//	}

}






/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function sets any event to be active as well as gives
 * the event a time stamp
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventSet (uint16_t Event)
{
	//First see if the event is not already active
	if((!EventList[Event].EventActive) && (!EventList[Event].EventLogged))
	{
		//If not active, make active and give a time stamp
		EventList[Event].EventActive = true;
		EventList[Event].ACKReceived = false;
		EventList[Event].Processed = false;
		EventList[Event].TimeStampSystic = time_now();

		EventList[Event].SplashActive = true;
	}
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function sets any event to be active as well as gives
 * the event a time stamp
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventSetACK (uint16_t Event)
{
	//First see if the event is not already active
	if (EventList[Event].EventActive)
	{
		EventList[Event].ACKReceived = true;
	}
}

void App_EventSetTimeStamp (uint16_t Event, uint32_t TimeStamp)
{
//	if((!EventList[Event].EventActive) && (!EventList[Event].EventLogged))
//	{
		//If not active, make active and give a time stamp
		EventList[Event].EventActive = true;
//		EventList[Event].ACKReceived = false;
//		EventList[Event].Processed = false;
		EventList[Event].TimeStampSystic = TimeStamp;

		EventList[Event].SplashActive = true;
//	}
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function clears any event to be inactive
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventClear (uint16_t Event)
{
	EventList[Event].EventActive 		= false;
	EventList[Event].Processed 			= false;
	EventList[Event].EventLogged 		= false;
	EventList[Event].TimeStampSystic	= 0;
	memset(EventList[Event].EventData, 0xFF, sizeof(EventList[Event].EventData));

	EventList[Event].SplashActive		= false;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function clears any event to be inactive
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventClearProcessed(uint16_t Event)
{
	EventList[Event].Processed 		= false;
	EventList[Event].EventLogged 	= false;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function clears any event to be inactive
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventClearLogged(uint16_t Event)
{
	EventList[Event].EventLogged 	= false;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function clears any event to be inactive
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventClearACK(uint16_t Event)
{
	EventList[Event].ACKReceived = false;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function clears any event to be inactive
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventMove (uint16_t CurrentPosition, uint16_t NewPosition)
{
	Event Temp = {0};
	Temp = EventList[NewPosition];
	EventList[NewPosition] = EventList[CurrentPosition];
	EventList[CurrentPosition] = Temp;
//	App_EventClear(CurrentPosition);
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function clears any event to be inactive
 *Inputs:
 *---------
 * Event Name
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventResetCAS (void)
{
	if(evGroups[Type_PDS].evCounter > 0)
	{
		EventList[evGroups[Type_PDS].evIndex[0]].Processed = false;
	}

}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function updates all events and sorts them into
 * relevant event lists
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventManageUpdates(void)
{
	// ---- Clear counters of event group lists ----
	for (uint8_t j = 1 ; j < evGroupSize; j++)
	{
		evGroups[j].evCounter = 0;
	}

	// ---- Clear counters of event screen lists ----
	for (uint8_t j = 1 ; j < evScreenSize; j++)
	{
		evScreen[j].evCounter = 0;
	}

	// ---- Reset all information in the lists ----
	memset(evGroups, 0, sizeof(evGroups));
	memset(evScreen, 0, sizeof(evScreen));

	// ---- Create lists of different active events displayable events ----
	for (uint16_t i = 0; i < evSize; i++)
	{
		// ---- Update event group list status ----
		evGroups[EventList[i].EventCategory] = App_EventUpdate(evGroups[EventList[i].EventCategory], i);
		evScreen[EventList[i].DispType] = App_EventUpdate(evScreen[EventList[i].DispType], i);
	}

	// ---- Rearrange event lists so that events with more important actions are handled first per event group ----
	App_EventListSort(evGroups);

	// ---- Make a copy of the active events for display purposes (avoid interrupting when counters = 0) ----
	memcpy(evMessages, evGroups, sizeof(evGroups));
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function sorts all events such that events with actions
 * take priority over those without actions (Display Only Events)
 *Inputs:
 *---------
 * evList
 *
 *Outputs:
 *---------
 * evList
 *-------------------------------------------------------------*/
void App_EventListSort (evList evGroups[])
{
	// ---- Create temporary values to sort the events in the groups ----
	uint8_t i, j, pass, hold_status = 0;
	uint16_t hold_index = 0;

	// ---- Loop through all the groups ----
	for (j = 1; j < evGroupSize; j++)
	{
		// ---- Loop through all the events in the group ----
		for (pass = 0; pass < evListSize; pass++)
		{
			// ---- Prioritize the events in the group according to the group ----
			for (i = 0; i < (evListSize - 1); i++)
			{
				// ---- Determine if the next event has a more important action than the current event ----
				if (App_EventDetermineMostImportantAction(evGroups[j].evIndex[i]) < App_EventDetermineMostImportantAction(evGroups[j].evIndex[i+1]))
				{
					// ---- Switch positions of the two current indexes ----
					hold_index = evGroups[j].evIndex[i];
					hold_status = evGroups[j].evStatus[i];

					evGroups[j].evIndex[i] = evGroups[j].evIndex[i+1];
					evGroups[j].evStatus[i] = evGroups[j].evStatus[i+1];

					evGroups[j].evIndex[i+1] = hold_index;
					evGroups[j].evStatus[i+1] = hold_status;
				}
			}
		}
	}
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function searches event lists for inactive events and
 * removes them while shifting elements around to maintain list
 * sorting
 *Inputs:
 *---------
 * evList
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
evList App_EventRemove (evList evGroup)
{

	if(evGroup.evCounter > 0)
	{
		//check status of top element in list
		evGroup.evStatus[0] = EventList[evGroup.evIndex[0]].EventActive;

		//if the top element status changed to inactive, clear the element and shift the list
		if(!evGroup.evStatus[0])
		{
			//clear index
			evGroup.evIndex[0] = 0;
			//shift the list
			for(uint8_t i = 0; i < evGroup.evCounter - 1; i++)
			{
				evGroup.evIndex[i] = evGroup.evIndex[i + 1];
				evGroup.evIndex[i + 1] = 0;
			}

			//Decrement list counter
			evGroup.evCounter--;

		}
	}
//	uint8_t ClearEntry = 0;
//
//	if(evGroup.evCounter > 0)
//	{
//		for(uint8_t t = 0; t < evGroup.evCounter - 1; t++)
//		{
//			if (!EventList[evGroup.evIndex[t]].EventActive)
//			{
//				ClearEntry++;
//			}
//
//			if (ClearEntry)
//			{
//				evGroup.evIndex[t] = evGroup.evIndex[t + ClearEntry];
//				evGroup.evIndex[t + ClearEntry] = 0;
//			}
//		}
//	}
//
//	evGroup.evCounter -= ClearEntry;
	return evGroup;


}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function updates an event list by either adding a new
 * event or by simply updating an existing event
 *Inputs:
 *---------
 * evList
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
evList App_EventUpdate (evList evGroup, uint16_t evIndex)
{
	if (EventList[Input_01_On].EventActive)
	{
		evGroup.evCounter = evGroup.evCounter;
	}
	if ((EventList[evIndex].EventActive) && (EventList[evIndex].DispType != Disp_None))
	{
		if(evGroup.evCounter == 0)
		{
			//This is the first entry
			evGroup.evIndex[evGroup.evCounter] = evIndex;
			//Pass over the status of the actual event to the list item
			evGroup.evStatus[evGroup.evCounter] = true;
			//Update list counter
			evGroup.evCounter++;
		}
		else
		{
			if(!App_EventFindInList (evGroup, evIndex))
			{
				//add to list
				evGroup.evIndex[evGroup.evCounter] = evIndex;
				//Pass over the status of the actual event to the list item
				evGroup.evStatus[evGroup.evCounter] = true;
				//Update list counter if actual event is active
				evGroup.evCounter++;
			}
		}
	}
	return evGroup;

}


/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function searches list indexes for existing events
 *Inputs:
 *---------
 * evList
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
bool App_EventFindInList (evList evGroup, uint16_t evIndex)
{

	for(uint8_t j = 1; j < evGroup.evCounter; j++)
	{
		if(evIndex == evGroup.evIndex[j])
			return true;
	}

	return false;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function clears all flags for the next round of event
 * checking
 *Inputs:
 *---------
 * evList
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
evList App_EventFlagRst (evList evGroup)
{

	for(uint8_t i = 1; i < evGroup.evCounter; i++)
	{
		evGroup.evStatus[i] = false;
	}

	return evGroup;

}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function updates the name of the event
 *Inputs:
 *---------
 * Index
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventExtractName (char Name[])
{
	char* ptr;
	uint8_t index;

	//find location of '-' in the name
	ptr = strchr((const char*)Name, '-');

	//get actual index of the '-' in the name
	index = (uint8_t)(ptr - (const char*)Name);

	char Vehicle_Name[index];

	for(uint8_t i = 0; i < index; i++)
	{
		Vehicle_Name[i] = Name[i];
	}

	sprintf(Vehicle_Name,Name);

}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function updates the Image of the event
 *Inputs:
 *---------
 * Index
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventUpdateThreatImage(uint16_t Index, uint8_t TagType)
{
	// ---- Update image from the array of threat images ----
	EventList[Index].ImageName = TagTypeImage[TagType];
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function updates the additional information of the event
 *Inputs:
 *---------
 * Index
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventUpdateAddtionalInfo (uint16_t Index, uint8_t* Info)
{
	// ---- Update reference pointer of event (pointer must exist) ----
	EventList[Index].AddtionalInfo = Info;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function updates the additional information of the event
 *Inputs:
 *---------
 * Index
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventUpdateActions(uint16_t Index, uint8_t Act1, uint8_t Act2, uint8_t Act3)
{
	// ---- Update actions of event (if actions handled not by event manager) ----
	EventList[Index].EventAction1 		= Act1;
	EventList[Index].EventAction2 		= Act2;
	EventList[Index].EventAction3 		= Act3;
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function updates the logging data of the event
 *Inputs:
 *---------
 * Index
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventUpdateData(uint16_t Index, uint8_t* EventData)
{
	if ((EventList[Index].EventActive) && (!EventList[Index].EventLogged))
	{
		memcpy(EventList[Index].EventData, EventData, sizeof(EventList[Index].EventData));
	}
}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function checks the events that should only be active for
 * a specific time (splash screen events)
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventSplashHandler (void)
{

	//License card events

//	if((EventList[EV_License_Valid].EventActive) && (time_since(EventList[EV_License_Valid].TimeInvoked) >= Card_Splash*Seconds) && (!System_Flags.System_DebugMode))
//	{
//		App_EventClear(EV_License_Valid);
//		EventList[EV_License_Valid].ACKReceived = true;
////		fill_rect(0,40,470,230,BLACK);
//	}

}

/*-------------------------------------------------------------
 *Function name and description
 *---------
 * This function checks all system flags and sets/clears corresponding
 * events to be handled
 *Inputs:
 *---------
 * evList
 *
 *Outputs:
 *---------
 * None
 *-------------------------------------------------------------*/
void App_EventHandler (void)
{
	// ---- Switch between application configured ----
	// ---- TODO: Insert function to get current application ----
	switch(1)
	{
		// ---- Handle the railbound system control events ----
		default:

			App_Railbound_Events_Handler();

			break;
	}
}
