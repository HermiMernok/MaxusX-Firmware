/*
 * App_Pins.h
 *
 *  Created on: 02 Sep 2018
 *      Author: NeilPretorius
 */

#ifndef APP_PINS_H_
#define APP_PINS_H_

#include "Global_Variables.h"

//Flags defined for the general inputs
struct _Input_Flags
{
	bool Estop_Mon		 ;
	bool Button_1        ;
	bool Button_2        ;
	bool Button_3        ;
	bool Button_4        ;
	bool Button_5        ;
	bool USB_OTG_Fault   ;
	bool Proxy1_PNP      ;
	bool Proxy1_NPN      ;
	bool Ext_In_2        ;
	bool Ext_In_3        ;
	bool Ext_In_4        ;
	bool Ext_In_5        ;
	bool Ext_In_6        ;
	bool Ext_In_1        ;
	bool Estop_In_Ext    ;
	bool CNTRL_InEXT     ;
	bool CNTRL_InFWD     ;
	bool CNTRL_InREV     ;
	bool CNTRL_InRES     ;
	bool RWD_CTS         ;
	bool Proxy2_NPN      ;
	bool Expander_Int    ;
	bool Estop_In_Int    ;
	bool Module_detect1			;//1//IO_Expander Inputs : IO_Epander1
	bool Module_detect2			;//2
	bool Module_detect3			;//3
	bool Module_detect4			;//4
	bool Charge_Active			;//5
	bool PSU_Protect			;//6
	bool fbk_CAN_PWR			;//7	//: IO_Epander2
	bool fbk_V_EXT_Uart			;//8
	bool fbk_V_Proxy			;//9
	bool fbk_V_Ethernet			;//10
	bool fbk_V_Control			;//11
	bool fbk_Siren1				;//12
	bool fbk_Siren2				;//13
	bool Charge_fault			;//14
	bool fbk_F_Light_White     	;//15
	bool fbk_F_Light_Red     	;//16
	bool fbk_F_Light_Flash_Red  ;//17
	bool fbk_F_Light_Dev     	;//18
	bool fbk_R_Light_White     	;//19
	bool fbk_R_Light_Red     	;//20
	bool fbk_R_Light_Flash_Red  ;//21
	bool fbk_R_Light_Dev     	;//22
	bool LCD_PWR_Fault			;//23	//: IO_Epander2
	bool Variant0				;//24
	bool Variant1				;//25
	bool Revision0				;//26
	bool Revision1				;//27
	bool Revision2				;//28
}Input_Flags;



//Led colors
typedef enum
{
	Red 		= 1,
	Green 		= 2,
	Blue 		= 3,
	Violet		= 4,
	Amber 		= 5,
	White		= 6,
	Turquoise	= 7,
	LED_Off,
} RGB_State_TypeDef;

//RGB Led's
typedef enum
{
	Status 		= 0,
	Key 		= 1,
} RGB_LED_TypeDef;

void IO_App_Init(void);
void IO_App_Read_Inputs(void);
void IO_App_Clear_Inputs(void);
void IO_RGB_Led(RGB_LED_TypeDef LED, RGB_State_TypeDef color);
void IO_App_BTN_Blue(void);
void IO_App_BTN_Red(void);


#endif /* APP_PINS_H_ */
