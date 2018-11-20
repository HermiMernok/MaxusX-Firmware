/*=================================
Dev_ADPS9301.c
Created on: 	31 August, 2018
Company: 		Mernok Elektronik
Author: 		H. du Plessis
==================================*/

#ifndef MCP23S17_H_
#define MCP23S17_H_
#include "stm32f7xx_hal.h"

#include "Global_Variables.h"


//Variables made public
struct _IO_Expander_In_Flags
{
	bool Module_detect1			;	//IO_Expander Inputs : IO_Epander1 A
	bool Module_detect2			;
	bool Module_detect3			;
	bool Module_detect4			;
	bool Charge_Active			;
	bool PSU_Protect			;
	bool fbk_CAN_PWR			;	//: IO_Epander2 A
	bool fbk_V_EXT_Uart			;
	bool fbk_V_Proxy			;
	bool fbk_V_Ethernet			;
	bool fbk_V_Control			;
	bool fbk_Siren1				;
	bool fbk_Siren2				;
	bool Charge_fault			;
	bool fbk_F_Light_White     	; //: IO_Epander2 B
	bool fbk_F_Light_Red     	;
	bool fbk_F_Light_Flash_Red  ;
	bool fbk_F_Light_Dev     	;
	bool fbk_R_Light_White     	;
	bool fbk_R_Light_Red     	;
	bool fbk_R_Light_Flash_Red  ;
	bool fbk_R_Light_Dev     	;
	bool LCD_PWR_Fault			;	//: IO_Epander3 B
	bool Variant0				;
	bool Variant1				;
	bool Revision0				;
	bool Revision1				;
	bool Revision2				;
} IO_Expander_In_Flags;

bool IO_Expander_Input_Flags_Array[28];

struct _IO_Expander_Output_Flags
{
	bool Led_Status_B		;	//IO_Expander Outputs : IO_Epander1
	bool Led_Status_G		;
	bool Module_reset1		;
	bool Module_reset2		;
	bool Module_reset3		;
	bool Module_reset4		;
	bool Led_Key_R			;
	bool Led_Key_G			;
	bool Led_Key_B			;
	bool Led_Status_R		;
	bool CAN1_Term			;	//: IO_Epander3
	bool CAN2_Term			;
	bool CAN3_Term			;
	bool LCD_Power			;
} IO_Expander_Output_Flags;

bool IO_Expander_Output_Flags_Array[14];

//Functions made public
void Set_ExpanderIO_In_Flags(void);
void Get_ExpanderIO_Input_Bytes(void);

void Set_ExpanderIO_Output_Bytes(void);
void Latch_IOExpander_Outputs(void);
void MCP23S17_CS_Init(void);
void LED_TEST(uint8_t toggle);



#endif /* F769_INIT_H_ */


