/*
 * F769_IO.c
 *
 *  Created on: 01 Sep 2018
 *      Author: NeilPretorius
 */

#include "F769_IO.h"

//Inputs

///Inputs
GPIO_TypeDef* INS_PORT[Inputsn] = {
		Estop_Mon_GPIO_PORT		,
		Button_1_GPIO_PORT       ,
		Button_2_GPIO_PORT       ,
		Button_3_GPIO_PORT       ,
		Button_4_GPIO_PORT       ,
		Button_5_GPIO_PORT       ,
		USB_OTG_Fault_GPIO_PORT   ,
		Proxy1_PNP_GPIO_PORT      ,
		Proxy1_NPN_GPIO_PORT      ,
		Ext_In_2_GPIO_PORT        ,
		Ext_In_3_GPIO_PORT        ,
		Ext_In_4_GPIO_PORT        ,
		Ext_In_5_GPIO_PORT        ,
		Ext_In_6_GPIO_PORT        ,
		Ext_In_1_GPIO_PORT        ,
		Estop_In_Ext_GPIO_PORT    ,
		CNTRL_InEXT_GPIO_PORT     ,
		CNTRL_InFWD_GPIO_PORT     ,
		CNTRL_InREV_GPIO_PORT     ,
		CNTRL_InRES_GPIO_PORT     ,
		RWD_CTS_GPIO_PORT         ,
		Proxy2_NPN_GPIO_PORT      ,
		Expander_Int_GPIO_PORT    ,
		Estop_In_Int_GPIO_PORT    ,
};

const uint16_t Ins_PIN[Inputsn] = {
		Estop_Mon_PIN		,
		Button_1_PIN       ,
		Button_2_PIN       ,
		Button_3_PIN       ,
		Button_4_PIN       ,
		Button_5_PIN       ,
		USB_OTG_Fault_PIN   ,
		Proxy1_PNP_PIN      ,
		Proxy1_NPN_PIN      ,
		Ext_In_2_PIN        ,
		Ext_In_3_PIN        ,
		Ext_In_4_PIN        ,
		Ext_In_5_PIN        ,
		Ext_In_6_PIN        ,
		Ext_In_1_PIN        ,
		Estop_In_Ext_PIN    ,
		CNTRL_InEXT_PIN     ,
		CNTRL_InFWD_PIN     ,
		CNTRL_InREV_PIN     ,
		CNTRL_InRES_PIN     ,
		RWD_CTS_PIN         ,
		Proxy2_NPN_PIN      ,
		Expander_Int_PIN    ,
		Estop_In_Int_PIN    ,
};


//Outputs
GPIO_TypeDef* Outputs_PORT[Outputsn] = {
		RTC_CS_GPIO_PORT        		,
		NV_CS_GPIO_PORT        		,
		IO_EXP1_CS_GPIO_PORT        	,
		IO_EXP2_CS_GPIO_PORT        	,
		Estop_Relay_GPIO_PORT        	,
		But_Led_Blue_GPIO_PORT        ,
		But_Led_Red_GPIO_PORT        	,
		PSU_Prt_SDWN_GPIO_PORT        ,
		QSPI_Reset_GPIO_PORT        	,
		IO_EXP3_CS_GPIO_PORT        	,
		FSMC_BLN0_GPIO_PORT        	,
		FSMC_BLN1_GPIO_PORT        	,
		USB_OTG_EN_GPIO_PORT			,
		LCD_BL_GPIO_PORT           	,
		V_Ext_Uart_GPIO_PORT          ,
		V_Proxy_GPIO_PORT           	,
		V_Ethernet_GPIO_PORT          ,
		V_Control_GPIO_PORT           ,
		F_Light_White_GPIO_PORT     	,
		F_Light_Red_GPIO_PORT     	,
		F_Light_Flash_Red_GPIO_PORT   ,
		F_Light_Dev_GPIO_PORT     	,
		R_Light_White_GPIO_PORT     	,
		R_Light_Red_GPIO_PORT     	,
		R_Light_Flash_Red_GPIO_PORT   ,
		R_Light_Dev_GPIO_PORT     	,
		PWR_CAN2_GPIO_PORT        	,
		DSI_Reset_GPIO_PORT        	,
		PFLASH_Reset_GPIO_PORT        ,
		Siren1_GPIO_PORT			,
		Siren2_GPIO_PORT
};

const uint16_t Outputs_PIN[Outputsn] = {
		RTC_CS_PIN        		,
		NV_CS_PIN        		,
		IO_EXP1_CS_PIN        	,
		IO_EXP2_CS_PIN        	,
		Estop_Relay_PIN        	,
		But_Led_Blue_PIN        ,
		But_Led_Red_PIN        	,
		PSU_Prt_SDWN_PIN        ,
		QSPI_Reset_PIN        	,
		IO_EXP3_CS_PIN        	,
		FSMC_BLN0_PIN        	,
		FSMC_BLN1_PIN        	,
		USB_OTG_EN_PIN			,
		LCD_BL_PIN           	,
		V_Ext_Uart_PIN          ,
		V_Proxy_PIN           	,
		V_Ethernet_PIN          ,
		V_Control_PIN           ,
		F_Light_White_PIN     	,
		F_Light_Red_PIN     	,
		F_Light_Flash_Red_PIN   ,
		F_Light_Dev_PIN     	,
		R_Light_White_PIN     	,
		R_Light_Red_PIN     	,
		R_Light_Flash_Red_PIN   ,
		R_Light_Dev_PIN     	,
		PWR_CAN2_PIN        	,
		DSI_Reset_PIN        	,
		PFLASH_Reset_PIN        ,
		Siren1_PIN				,
		Siren2_PIN
};

bool IO_Input_Read(Input_Name_TypeDef Input)
{
	//Designed for active low inputs
	bool state;

	if(Input<Inputsn)
	{
		switch(HAL_GPIO_ReadPin(INS_PORT[Input], Ins_PIN[Input]))
		{
		case GPIO_PIN_SET:

			state = false;
			break;

		case GPIO_PIN_RESET:

			state = true;
			break;

		default:
			break;
		}
	}
	else
	{
		Get_ExpanderIO_Input_Bytes();
		state= IO_Expander_Input_Flags_Array[Input - Inputsn];
	}

	return state;
}

bool IO_Input_ReadNormal(Input_Name_TypeDef Input)
{
	bool state;

	//Designed for active high inputs

	switch(HAL_GPIO_ReadPin(INS_PORT[Input], Ins_PIN[Input]))
	{
	case GPIO_PIN_SET:

		state = true;
		break;

	case GPIO_PIN_RESET:

		state = false;
		break;

	default:
		break;
	}

	return state;

}

void IO_Output_control(Output_Name_TypeDef Output, bool state)
{
	if(Output<Outputsn)
	{
		if(state)
			HAL_GPIO_WritePin(Outputs_PORT[Output], Outputs_PIN[Output], GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(Outputs_PORT[Output], Outputs_PIN[Output], GPIO_PIN_SET);
	}
	else
	{
		IO_Expander_Output_Flags_Array[Output-Outputsn] = state;
		Set_ExpanderIO_Output_Bytes();
	}


}
