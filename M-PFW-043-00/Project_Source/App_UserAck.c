/*
 * App_UserAck.c
 *
 *  Created on: Jun 3, 2016
 *      Author: JacoOlivier
 */

#include <App_BacklightControl.h>
#include "App_UserAck.h"

ACK_Button	User_Button[Button_Count];

uint16_t	Skipper;


/*-----------------------------------------
 *Function name and description
 *---------
 * This function initialises the ACK_Button
 * machine and sets up all button references
 * to button functions as required
 *
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void App_ACK_Init (void)
{

	User_Button[ACK_Up].ACK_Flag			=	&Input_Flags.Button_1;
	User_Button[ACK_Down].ACK_Flag			=	&Input_Flags.Button_2;
	User_Button[ACK_Left].ACK_Flag			=	&Input_Flags.Button_3;
	User_Button[ACK_Right].ACK_Flag			=	&Input_Flags.Button_4;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function checks the status of a button
 * flag
 *
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
bool App_ACK_CheckFlag (User_Buttons Button)
{
	if(User_Button[Button].Button_Pressed)
	{
		return true;
	}

	return false;

}

/*-----------------------------------------
 *Function name and description
 *---------
 * This function waits until a specific
 * button has been released after initial
 * press
 *
 *Inputs:
 *---------
 * enum reference to button
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void App_ACK_ButtonReleased (uint8_t Button)
{

	//Process the event if it has not yet been processed
	if((*User_Button[Button].ACK_Flag) && (!User_Button[Button].ACK_Processed) && (User_Button[Button].ACK_Flag != NULL))
	{
		User_Button[Button].ACK_Processed = true;
	}


	//	while((*User_Button[Button].ACK_Flag) && (User_Button[Button].ACK_Flag != NULL))
	//	{
	//		/*--------------------------------
	//		 * Read All Inputs
	//		 *------------------------------*/
	//		IO_App_Read_Inputs();
	//	}
}

// === Change button handler to include time delay ===
/*-----------------------------------------
 *Function name and description
 *---------
 * This is a handler function that updates
 * all button pressed flags and time stamps
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void App_ACK_Handler (void)
{
	for(uint8_t i = 0; i < Button_Count; i++)
	{
		if((*User_Button[i].ACK_Flag) && User_Button[i].Time_Pressed == 0  && (!User_Button[i].ACK_Processed))
		{
			User_Button[i].Time_Pressed = time_now();


		}

		else if((!*User_Button[i].ACK_Flag) && (User_Button[i].ACK_Processed))
		{
			User_Button[i].Time_Pressed = 0;
			User_Button[i].ACK_Processed = false;

		}

		if(App_ACK_TimeSince_Pressed(i) > 100 && (!User_Button[i].ACK_Processed) && (*User_Button[i].ACK_Flag))
		{
			User_Button[i].Button_Pressed = true;
		}
		else
		{
			User_Button[i].Button_Pressed = false;
		}
	}
}


/*-----------------------------------------
 *Function name and description
 *---------
 * This function returns the time since
 * a button was pressed
 *
 *Inputs:
 *---------
 * enum reference of button
 *
 *Outputs:
 *---------
 *32-bit integer of time since press
 *
 *-----------------------------------------*/
uint32_t App_ACK_TimeSince_Pressed (uint8_t Button)
{
	uint32_t time_since_pressed = 0;

	if(User_Button[Button].Time_Pressed != 0)
	{
		time_since_pressed = time_since(User_Button[Button].Time_Pressed);
		return time_since_pressed;
	}
	else
		return 0;
}


