/*
 * F769_IO.h
 *
 *  Created on: 01 Sep 2018
 *      Author: NeilPretorius
 */

#ifndef F769_IO_H_
#define F769_IO_H_


#include "Global_Variables.h"
/*--------------------------------
Defines
----------------------------------*/
#define Inputsn			24
#define Outputsn		31

/*
 *
 * Defining Inputs
 *
 */


//Inputs
//Port A

//PORTB

//PortC
/*Configure GPIO PIN : PC14 */
#define Estop_Mon_PIN				GPIO_PIN_14
#define Estop_Mon_GPIO_PORT		  	GPIOC

//PortG
/*Configure GPIO PINs : PG6 PG7 PG8 PG9 PG10 PG15 */
#define Button_1_PIN        		GPIO_PIN_6
#define Button_1_GPIO_PORT   		GPIOG

#define Button_2_PIN        		GPIO_PIN_7
#define Button_2_GPIO_PORT   		GPIOG

#define Button_3_PIN        		GPIO_PIN_8
#define Button_3_GPIO_PORT   		GPIOG

#define Button_4_PIN        		GPIO_PIN_9
#define Button_4_GPIO_PORT   		GPIOG

#define Button_5_PIN        		GPIO_PIN_10
#define Button_5_GPIO_PORT   		GPIOG

#define USB_OTG_Fault_PIN        	GPIO_PIN_15
#define USB_OTG_Fault_GPIO_PORT  	GPIOG

//PortH
/*Configure GPIO PINs : PH2 PH3 PH8 PH9 PH10 PH11 PH12 PH15 */
#define Proxy1_PNP_PIN        			GPIO_PIN_2
#define Proxy1_PNP_GPIO_PORT   			GPIOH
#define Proxy1_NPN_PIN        			GPIO_PIN_3
#define Proxy1_NPN_GPIO_PORT   			GPIOH
#define Ext_In_2_PIN        			GPIO_PIN_8
#define Ext_In_2_GPIO_PORT   			GPIOH
#define Ext_In_3_PIN        			GPIO_PIN_9
#define Ext_In_3_GPIO_PORT   			GPIOH
#define Ext_In_4_PIN        			GPIO_PIN_10
#define Ext_In_4_GPIO_PORT   			GPIOH
#define Ext_In_5_PIN        			GPIO_PIN_11
#define Ext_In_5_GPIO_PORT   			GPIOH
#define Ext_In_6_PIN        			GPIO_PIN_12
#define Ext_In_6_GPIO_PORT   			GPIOH
#define Ext_In_1_PIN        			GPIO_PIN_15
#define Ext_In_1_GPIO_PORT   			GPIOH

//PortI
/*Configure GPIO PINs : PI8 PI10 PI11 PI4 PI5 PI6 PI7 */
#define Estop_In_Ext_PIN        		GPIO_PIN_4
#define Estop_In_Ext_GPIO_PORT   		GPIOI

#define CNTRL_InEXT_PIN        			GPIO_PIN_5
#define CNTRL_InEXT_GPIO_PORT   		GPIOI

#define CNTRL_InFWD_PIN        			GPIO_PIN_6
#define CNTRL_InFWD_GPIO_PORT   		GPIOI

#define CNTRL_InREV_PIN        			GPIO_PIN_7
#define CNTRL_InREV_GPIO_PORT   		GPIOI

#define CNTRL_InRES_PIN        			GPIO_PIN_8
#define CNTRL_InRES_GPIO_PORT   		GPIOI

#define RWD_CTS_PIN        				GPIO_PIN_10
#define RWD_CTS_GPIO_PORT   			GPIOI

#define Proxy2_NPN_PIN        			GPIO_PIN_11
#define Proxy2_NPN_GPIO_PORT   			GPIOH

//PortK
/*Configure GPIO PINs : PK3 PK4 */
#define Expander_Int_PIN        		GPIO_PIN_3
#define Expander_Int_GPIO_PORT   		GPIOK

#define Estop_In_Int_PIN        		GPIO_PIN_4
#define Estop_In_Int_GPIO_PORT   		GPIOK



/*
 *
 * Defining Outputs
 *
 */

//Outputs
//PortA


//PortB
/*Configure GPIO PINs : PB0 PB1 PB2 */
#define RTC_CS_PIN        				GPIO_PIN_0
#define RTC_CS_GPIO_PORT   				GPIOB

#define NV_CS_PIN        				GPIO_PIN_1
#define NV_CS_GPIO_PORT   				GPIOB

#define IO_EXP1_CS_PIN        			GPIO_PIN_2
#define IO_EXP1_CS_GPIO_PORT   			GPIOB

#define IO_EXP2_CS_PIN        			GPIO_PIN_7
#define IO_EXP2_CS_GPIO_PORT   			GPIOB

//PortC
/*Configure GPIO PINs : PC13 PC15 PC0 PC2 PC3 PC9 */
#define Estop_Relay_PIN        			GPIO_PIN_0
#define Estop_Relay_GPIO_PORT   		GPIOC

#define But_Led_Blue_PIN        		GPIO_PIN_2
#define But_Led_Blue_GPIO_PORT   		GPIOC

#define But_Led_Red_PIN        			GPIO_PIN_3
#define But_Led_Red_GPIO_PORT   		GPIOC

#define PSU_Prt_SDWN_PIN        		GPIO_PIN_9
#define PSU_Prt_SDWN_GPIO_PORT   		GPIOC

#define QSPI_Reset_PIN        			GPIO_PIN_13
#define QSPI_Reset_GPIO_PORT   			GPIOC

#define IO_EXP3_CS_PIN        			GPIO_PIN_15
#define IO_EXP3_CS_GPIO_PORT   			GPIOC

//PortD
/*Configure GPIO PINs : PD2 PD3 */
#define FSMC_BLN0_PIN        			GPIO_PIN_2
#define FSMC_BLN0_GPIO_PORT   			GPIOD

#define FSMC_BLN1_PIN        			GPIO_PIN_3
#define FSMC_BLN1_GPIO_PORT   			GPIOD

//PortG
/*Configure GPIO PIN : PG12 */
#define USB_OTG_EN_PIN					GPIO_PIN_12
#define USB_OTG_EN_GPIO_PORT			GPIOG


//PortI
/*Configure GPIO PINs : PI12 PI13 PI14 PI15 PI0 */
#define LCD_BL_PIN           			GPIO_PIN_0
#define LCD_BL_GPIO_PORT          		GPIOI

#define V_Ext_Uart_PIN           		GPIO_PIN_12
#define V_Ext_Uart_GPIO_PORT        	GPIOI

#define V_Proxy_PIN           			GPIO_PIN_13
#define V_Proxy_GPIO_PORT          		GPIOI

#define V_Ethernet_PIN           		GPIO_PIN_14
#define V_Ethernet_GPIO_PORT          	GPIOI

#define V_Control_PIN           		GPIO_PIN_15
#define V_Control_GPIO_PORT          	GPIOI

//PortJ
/*Configure GPIO PINs : PJ0 PJ1 PJ2 PJ3 PJ4 PJ5 PJ12 PJ13 PJ14 PJ15 */
#define F_Light_White_PIN     			GPIO_PIN_0
#define F_Light_White_GPIO_PORT         GPIOJ

#define F_Light_Red_PIN     			GPIO_PIN_1
#define F_Light_Red_GPIO_PORT         	GPIOJ

#define F_Light_Flash_Red_PIN     		GPIO_PIN_2
#define F_Light_Flash_Red_GPIO_PORT     GPIOJ

#define F_Light_Dev_PIN     			GPIO_PIN_3
#define F_Light_Dev_GPIO_PORT         	GPIOJ

#define R_Light_White_PIN     			GPIO_PIN_4
#define R_Light_White_GPIO_PORT         GPIOJ

#define R_Light_Red_PIN     			GPIO_PIN_5
#define R_Light_Red_GPIO_PORT         	GPIOJ

#define R_Light_Flash_Red_PIN     		GPIO_PIN_12
#define R_Light_Flash_Red_GPIO_PORT     GPIOJ

#define R_Light_Dev_PIN     			GPIO_PIN_13
#define R_Light_Dev_GPIO_PORT         	GPIOJ

#define PWR_CAN2_PIN        			GPIO_PIN_14
#define PWR_CAN2_GPIO_PORT   			GPIOJ

#define DSI_Reset_PIN        			GPIO_PIN_15
#define DSI_Reset_GPIO_PORT   			GPIOJ

//PortK
/*Configure GPIO PINs : PK5 PK6 PK7 */
#define PFLASH_Reset_PIN        		GPIO_PIN_5
#define PFLASH_Reset_GPIO_PORT   		GPIOK

#define Siren1_PIN        				GPIO_PIN_6
#define Siren1_GPIO_PORT   				GPIOK

#define Siren2_PIN        				GPIO_PIN_7
#define Siren2_GPIO_PORT   				GPIOK

//Outputs
typedef enum
{
	RTC_CS        		, 	//outputs connected to uC
	NV_CS        		,
	IO_EXP1_CS        	,
	IO_EXP2_CS        	,
	Estop_Relay        	,
	But_Led_Blue        ,
	But_Led_Red        	,
	PSU_Prt_SDWN        ,
	QSPI_Reset        	,
	IO_EXP3_CS        	,
	FSMC_BLN0        	,
	FSMC_BLN1        	,
	USB_OTG_EN			,
	LCD_BL           	,
	V_Ext_Uart          ,
	V_Proxy           	,
	V_Ethernet          ,
	V_Control           ,
	F_Light_White     	,
	F_Light_Red     	,
	F_Light_Flash_Red   ,
	F_Light_Dev     	,
	R_Light_White     	,
	R_Light_Red     	,
	R_Light_Flash_Red   ,
	R_Light_Dev     	,
	PWR_CAN2        	,
	DSI_Reset        	,
	PFLASH_Reset        ,
	Siren1        		,
	Siren2        		,
	Led_Status_B		,	//IO_Expander Outputs : IO_Epander1
	Led_Status_G		,
	Module_reset1		,
	Module_reset2		,
	Module_reset3		,
	Module_reset4		,
	Led_Key_R			,
	Led_Key_G			,
	Led_Key_B			,
	Led_Status_R		,
	CAN1_Term			,	//: IO_Epander3
	CAN2_Term			,
	CAN3_Term			,
	LCD_Power			,

} Output_Name_TypeDef;


//Inputs
typedef enum
{
	Estop_Mon		,
	Button_1       ,
	Button_2       ,
	Button_3       ,
	Button_4       ,
	Button_5       ,
	USB_OTG_Fault   ,
	Proxy1_PNP      ,
	Proxy1_NPN      ,
	Ext_In_2        ,
	Ext_In_3        ,
	Ext_In_4        ,
	Ext_In_5        ,
	Ext_In_6        ,
	Ext_In_1        ,
	Estop_In_Ext    ,
	CNTRL_InEXT     ,
	CNTRL_InFWD     ,
	CNTRL_InREV     ,
	CNTRL_InRES     ,
	RWD_CTS         ,
	Proxy2_NPN      ,
	Expander_Int    ,
	Estop_In_Int    ,
	Module_detect1			,//1//IO_Expander Inputs : IO_Epander1
	Module_detect2			,//2
	Module_detect3			,//3
	Module_detect4			,//4
	Charge_Active			,//5
	PSU_Protect				,//6
	fbk_CAN_PWR				,//7	//: IO_Epander2
	fbk_V_EXT_Uart			,//8
	fbk_V_Proxy				,//9
	fbk_V_Ethernet			,//10
	fbk_V_Control			,//11
	fbk_Siren1				,//12
	fbk_Siren2				,//13
	Charge_fault			,//14
	fbk_F_Light_White     	,//15
	fbk_F_Light_Red     	,//16
	fbk_F_Light_Flash_Red   ,//17
	fbk_F_Light_Dev     	,//18
	fbk_R_Light_White     	,//19
	fbk_R_Light_Red     	,//20
	fbk_R_Light_Flash_Red   ,//21
	fbk_R_Light_Dev     	,//22
	LCD_PWR_Fault			,//23	//: IO_Epander2
	Variant0				,//24
	Variant1				,//25
	Revision0				,//26
	Revision1				,//27
	Revision2				,//28

} Input_Name_TypeDef;

bool IO_Input_Read(Input_Name_TypeDef Input);
bool IO_Input_ReadNormal(Input_Name_TypeDef Input);

void IO_Output_control(Output_Name_TypeDef Output, bool state);


#endif /* F769_IO_H_ */
