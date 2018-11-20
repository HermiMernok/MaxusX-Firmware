/*
 * App_Pins.c
 *
 *  Created on: 02 Sep 2018
 *      Author: NeilPretorius
 */

#include "App_Pins.h"

void IO_App_Clear_Inputs(void)
{
	Input_Flags.Estop_Mon		             = false;
	Input_Flags.Button_1                     = false;
	Input_Flags.Button_2                     = false;
	Input_Flags.Button_3                     = false;
	Input_Flags.Button_4                     = false;
	Input_Flags.Button_5                     = false;
	Input_Flags.USB_OTG_Fault                = false;
	Input_Flags.Proxy1_PNP                   = false;
	Input_Flags.Proxy1_NPN                   = false;
	Input_Flags.Ext_In_2                     = false;
	Input_Flags.Ext_In_3                     = false;
	Input_Flags.Ext_In_4                     = false;
	Input_Flags.Ext_In_5                     = false;
	Input_Flags.Ext_In_6                     = false;
	Input_Flags.Ext_In_1                     = false;
	Input_Flags.Estop_In_Ext                 = false;
	Input_Flags.CNTRL_InEXT                  = false;
	Input_Flags.CNTRL_InFWD                  = false;
	Input_Flags.CNTRL_InREV                  = false;
	Input_Flags.CNTRL_InRES                  = false;
	Input_Flags.RWD_CTS                      = false;
	Input_Flags.Proxy2_NPN                   = false;
	Input_Flags.Expander_Int                 = false;
	Input_Flags.Estop_In_Int                 = false;
	Input_Flags.Module_detect1			     = false;
	Input_Flags.Module_detect2			     = false;
	Input_Flags.Module_detect3			     = false;
	Input_Flags.Module_detect4			     = false;
	Input_Flags.Charge_Active			     = false;
	Input_Flags.PSU_Protect			         = false;
	Input_Flags.fbk_CAN_PWR			         = false;
	Input_Flags.fbk_V_EXT_Uart			     = false;
	Input_Flags.fbk_V_Proxy			         = false;
	Input_Flags.fbk_V_Ethernet			     = false;
	Input_Flags.fbk_V_Control			     = false;
	Input_Flags.fbk_Siren1				     = false;
	Input_Flags.fbk_Siren2				     = false;
	Input_Flags.Charge_fault			     = false;
	Input_Flags.fbk_F_Light_White     	     = false;
	Input_Flags.fbk_F_Light_Red     	     = false;
	Input_Flags.fbk_F_Light_Flash_Red        = false;
	Input_Flags.fbk_F_Light_Dev     	     = false;
	Input_Flags.fbk_R_Light_White     	     = false;
	Input_Flags.fbk_R_Light_Red     	     = false;
	Input_Flags.fbk_R_Light_Flash_Red        = false;
	Input_Flags.fbk_R_Light_Dev     	     = false;
	Input_Flags.LCD_PWR_Fault			     = false;
	Input_Flags.Variant0				     = false;
	Input_Flags.Variant1				     = false;
	Input_Flags.Revision0				     = false;
	Input_Flags.Revision1				     = false;
	Input_Flags.Revision2				     = false;

}


void IO_App_Init(void)
{
	/*--------------------------------
	Set output pins to initial state
	----------------------------------*/
	IO_Output_control(RTC_CS        	 , Off);	//active low

	IO_Output_control(IO_EXP1_CS         , On);	//active low
	IO_Output_control(IO_EXP2_CS         , On);	//active low
	IO_Output_control(Estop_Relay        , On); //active low
	IO_Output_control(But_Led_Blue       , On); //active low
	IO_Output_control(But_Led_Red        , On); //active low
	IO_Output_control(PSU_Prt_SDWN       , On );//active low
	IO_Output_control(QSPI_Reset         , Off);
	IO_Output_control(IO_EXP3_CS         , On); //active low
	IO_Output_control(FSMC_BLN0        	 , Off);
	IO_Output_control(FSMC_BLN1        	 , Off);
//	IO_Output_control(USB_OTG_EN		 , Off);//controlled by USB code
	IO_Output_control(LCD_BL           	 , Off);
	IO_Output_control(V_Ext_Uart         , Off);
	IO_Output_control(V_Proxy            , Off);
	IO_Output_control(V_Ethernet         , Off);
	IO_Output_control(V_Control          , Off);
	IO_Output_control(F_Light_White      , Off);
	IO_Output_control(F_Light_Red     	 , Off);
	IO_Output_control(F_Light_Flash_Red  , Off);
	IO_Output_control(F_Light_Dev     	 , Off);
	IO_Output_control(R_Light_White      , Off);
	IO_Output_control(R_Light_Red     	 , Off);
	IO_Output_control(R_Light_Flash_Red  , Off);
	IO_Output_control(R_Light_Dev     	 , Off);
	IO_Output_control(PWR_CAN2        	 , Off);
	IO_Output_control(DSI_Reset        	 , Off);
	IO_Output_control(PFLASH_Reset       , Off);
	IO_Output_control(Siren1        	 , Off);
	IO_Output_control(Siren2        	 , Off);
	IO_Output_control(Led_Status_G		 , Off);
	IO_Output_control(Led_Status_B		 , Off);
	IO_Output_control(Module_reset1		 , Off);
	IO_Output_control(Module_reset2		 , Off);
	IO_Output_control(Module_reset3		 , Off);
	IO_Output_control(Module_reset4		 , Off);
	IO_Output_control(Led_Key_R			 , Off);
	IO_Output_control(Led_Key_G			 , Off);
	IO_Output_control(Led_Key_B			 , Off);
	IO_Output_control(Led_Status_R		 , Off);
	IO_Output_control(CAN1_Term			 , Off);
	IO_Output_control(CAN2_Term			 , Off);
	IO_Output_control(CAN3_Term			 , Off);
	IO_Output_control(LCD_Power			 , On);

	IO_Output_control(NV_CS        		 , On);	//active low

	IO_App_Clear_Inputs();

}
/*-----------------------------------------
 *Function name and description
 *---------
 * RGB LED controller
 *Inputs:
 *---------
 * LED	- Status, Key
 * Color -
 * Red
 * Green
 * Blue
 * Violet
 * Amber
 * White
 * Turquoise
 * Off
 *
 *Outputs:
 *---------
 * None
 *-----------------------------------------*/
void IO_RGB_Led(RGB_LED_TypeDef LED, RGB_State_TypeDef color)
{
	//Key LED
	if(LED == Key)
	{
		switch(color)
		{
		case Red:
			IO_Output_control(Led_Key_R,On);
			IO_Output_control(Led_Key_G,Off);
			IO_Output_control(Led_Key_B,Off);
			break;

		case Green:
			IO_Output_control(Led_Key_R,Off);
			IO_Output_control(Led_Key_G,On);
			IO_Output_control(Led_Key_B,Off);
			break;

		case Blue:
			IO_Output_control(Led_Key_R,Off);
			IO_Output_control(Led_Key_G,Off);
			IO_Output_control(Led_Key_B,On);
			break;

		case Violet:
			IO_Output_control(Led_Key_R,On);
			IO_Output_control(Led_Key_G,Off);
			IO_Output_control(Led_Key_B,On);
			break;

		case Amber:
			IO_Output_control(Led_Key_R,On);
			IO_Output_control(Led_Key_G,On);
			IO_Output_control(Led_Key_B,Off);
			break;

		case White:
			IO_Output_control(Led_Key_R,On);
			IO_Output_control(Led_Key_G,On);
			IO_Output_control(Led_Key_B,On);
			break;

		case Turquoise:
			IO_Output_control(Led_Key_R,Off);
			IO_Output_control(Led_Key_G,On);
			IO_Output_control(Led_Key_B,On);
			break;

		case LED_Off:
			IO_Output_control(Led_Key_R,Off);
			IO_Output_control(Led_Key_G,Off);
			IO_Output_control(Led_Key_B,Off);
			break;
		}
	}
	//Status LED
	else
	{
		switch(color)
		{
		case Red:
			IO_Output_control(Led_Status_R,On);
			IO_Output_control(Led_Status_G,Off);
			IO_Output_control(Led_Status_B,Off);
			break;

		case Green:
			IO_Output_control(Led_Status_R,Off);
			IO_Output_control(Led_Status_G,On);
			IO_Output_control(Led_Status_B,Off);
			break;

		case Blue:
			IO_Output_control(Led_Status_R,Off);
			IO_Output_control(Led_Status_G,Off);
			IO_Output_control(Led_Status_B,On);
			break;

		case Violet:
			IO_Output_control(Led_Status_R,On);
			IO_Output_control(Led_Status_G,Off);
			IO_Output_control(Led_Status_B,On);
			break;

		case Amber:
			IO_Output_control(Led_Status_R,On);
			IO_Output_control(Led_Status_G,On);
			IO_Output_control(Led_Status_B,Off);
			break;

		case White:
			IO_Output_control(Led_Status_R,On);
			IO_Output_control(Led_Status_G,On);
			IO_Output_control(Led_Status_B,On);
			break;

		case Turquoise:
			IO_Output_control(Led_Status_R,Off);
			IO_Output_control(Led_Status_G,On);
			IO_Output_control(Led_Status_B,On);
			break;

		case LED_Off:
			IO_Output_control(Led_Status_R,Off);
			IO_Output_control(Led_Status_G,Off);
			IO_Output_control(Led_Status_B,Off);
			break;
		}
	}
}

/*-----------------------------------------
*Function name and description
 *---------
 * Reads all inputs and store results in struct
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *
 *-----------------------------------------*/
void IO_App_Read_Inputs(void)
{
	Input_Flags.Estop_Mon 				= IO_Input_Read(Estop_Mon);
	Input_Flags.Button_1        		= IO_Input_Read(Button_1     );
	Input_Flags.Button_2        		= IO_Input_Read(Button_2     );
	Input_Flags.Button_3        		= IO_Input_Read(Button_3     );
	Input_Flags.Button_4        		= IO_Input_Read(Button_4     );
	Input_Flags.Button_5        		= IO_Input_Read(Button_5     );
	Input_Flags.USB_OTG_Fault   		= IO_Input_Read(USB_OTG_Fault);
	Input_Flags.Proxy1_PNP      		= IO_Input_Read(Proxy1_PNP   );
	Input_Flags.Proxy1_NPN      		= IO_Input_Read(Proxy1_NPN   );
	Input_Flags.Ext_In_2        		= IO_Input_Read(Ext_In_2     );
	Input_Flags.Ext_In_3        		= IO_Input_Read(Ext_In_3     );
	Input_Flags.Ext_In_4        		= IO_Input_Read(Ext_In_4     );
	Input_Flags.Ext_In_5        		= IO_Input_Read(Ext_In_5     );
	Input_Flags.Ext_In_6        		= IO_Input_Read(Ext_In_6     );
	Input_Flags.Ext_In_1        		= IO_Input_Read(Ext_In_1     );
	Input_Flags.Estop_In_Ext    		= IO_Input_Read(Estop_In_Ext );
	Input_Flags.CNTRL_InEXT     		= IO_Input_Read(CNTRL_InEXT  );
	Input_Flags.CNTRL_InFWD     		= IO_Input_Read(CNTRL_InFWD  );
	Input_Flags.CNTRL_InREV     		= IO_Input_Read(CNTRL_InREV  );
	Input_Flags.CNTRL_InRES     		= IO_Input_Read(CNTRL_InRES  );
	Input_Flags.RWD_CTS         		= IO_Input_Read(RWD_CTS      );
	Input_Flags.Proxy2_NPN      		= IO_Input_Read(Proxy2_NPN   );
	Input_Flags.Expander_Int    		= IO_Input_Read(Expander_Int );
	Input_Flags.Estop_In_Int    		= IO_Input_Read(Estop_In_Int );
	Input_Flags.Module_detect1			= IO_Input_Read(Module_detect1			);//1//IO_Expander Inputs : IO_Epander1
	Input_Flags.Module_detect2			= IO_Input_Read(Module_detect2			);//2
	Input_Flags.Module_detect3			= IO_Input_Read(Module_detect3			);//3
	Input_Flags.Module_detect4			= IO_Input_Read(Module_detect4			);//4
	Input_Flags.Charge_Active			= IO_Input_Read(Charge_Active			);//5
	Input_Flags.PSU_Protect				= IO_Input_Read(PSU_Protect				);//6
	Input_Flags.fbk_CAN_PWR				= IO_Input_Read(fbk_CAN_PWR				);//7	//: IO_Epander2
	Input_Flags.fbk_V_EXT_Uart			= IO_Input_Read(fbk_V_EXT_Uart			);//8
	Input_Flags.fbk_V_Proxy				= IO_Input_Read(fbk_V_Proxy				);//9
	Input_Flags.fbk_V_Ethernet			= IO_Input_Read(fbk_V_Ethernet			);//10
	Input_Flags.fbk_V_Control			= IO_Input_Read(fbk_V_Control			);//11
	Input_Flags.fbk_Siren1				= IO_Input_Read(fbk_Siren1				);//12
	Input_Flags.fbk_Siren2				= IO_Input_Read(fbk_Siren2				);//13
	Input_Flags.Charge_fault			= IO_Input_Read(Charge_fault			);//14
	Input_Flags.fbk_F_Light_White     	= IO_Input_Read(fbk_F_Light_White     	);//15
	Input_Flags.fbk_F_Light_Red     	= IO_Input_Read(fbk_F_Light_Red     	);//16
	Input_Flags.fbk_F_Light_Flash_Red   = IO_Input_Read(fbk_F_Light_Flash_Red   );//17
	Input_Flags.fbk_F_Light_Dev     	= IO_Input_Read(fbk_F_Light_Dev     	);//18
	Input_Flags.fbk_R_Light_White     	= IO_Input_Read(fbk_R_Light_White     	);//19
	Input_Flags.fbk_R_Light_Red     	= IO_Input_Read(fbk_R_Light_Red     	);//20
	Input_Flags.fbk_R_Light_Flash_Red   = IO_Input_Read(fbk_R_Light_Flash_Red   );//21
	Input_Flags.fbk_R_Light_Dev     	= IO_Input_Read(fbk_R_Light_Dev     	);//22
	Input_Flags.LCD_PWR_Fault			= IO_Input_Read(LCD_PWR_Fault			);//23	//: IO_Epander2
	Input_Flags.Variant0				= IO_Input_Read(Variant0				);//24
	Input_Flags.Variant1				= IO_Input_Read(Variant1				);//25
	Input_Flags.Revision0				= IO_Input_Read(Revision0				);//26
	Input_Flags.Revision1				= IO_Input_Read(Revision1				);//27
	Input_Flags.Revision2				= IO_Input_Read(Revision2				);//28

}

/*-----------------------------------------
 *Function name and description
 *---------
 * Set button on front to Blue
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *
 *-----------------------------------------*/
void IO_App_BTN_Blue(void)
{
	IO_Output_control(But_Led_Red, On);
	IO_Output_control(But_Led_Blue,Off);
}

/*-----------------------------------------
 *Function name and description
 *---------
 * Set button on front to Red
 *
 *Inputs:
 *---------
 * None
 *
 *Outputs:
 *---------
 * None
 *
 *-----------------------------------------*/
void IO_App_BTN_Red(void)
{
	IO_Output_control(But_Led_Blue,On);
	IO_Output_control(But_Led_Red, Off);
}
