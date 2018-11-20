/*
 * App_UserAck.h
 *
 *  Created on: Jun 3, 2016
 *      Author: JacoOlivier
 */

#ifndef APP_USERACK_H_
#define APP_USERACK_H_

#include "Global_Variables.h"
#include "Delay.h"

#define	Button_Count		4
#define	Button_Threshold	2


struct _ACK_Flags
{
	bool		ACK_EditMode;
}ACK_Flags;


typedef enum
{

	ACK_Up					=	0,
	ACK_Down				=	1,
	ACK_Left				=	2,
	ACK_Right				= 	3,

}User_Buttons;

typedef struct _ACK_Button
{
	bool*		ACK_Flag;
	bool		Button_Pressed;
	bool		ACK_Processed;

uint32_t	Time_Pressed;

}ACK_Button;


/*--------------------------------
Externals
----------------------------------*/
extern ACK_Button	User_Button[Button_Count];
extern uint16_t	Skipper;


/*--------------------------------
Functions made public
----------------------------------*/
void App_ACK_Init (void);
void App_ACK_ButtonReleased (uint8_t Button);
void App_ACK_Handler (void);
uint32_t App_ACK_TimeSince_Pressed (uint8_t Button);
void App_ACK_UpdateSkippper (uint32_t	time_stamp);
void App_ACK_DebugAssign (void);
bool App_ACK_CheckFlag (User_Buttons Button);

#endif /* APP_USERACK_H_ */
