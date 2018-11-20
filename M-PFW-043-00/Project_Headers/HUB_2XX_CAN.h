/*HUB_2XX_CAN.h
 *Created on: 27 Jul 2018
 *Company: Mernok Elektronik
 *Author: S.D. Janse van Rensburg
*/

#ifndef PROJECT_HEADERS_RBE_SYSTEM_HUB_2XX_CAN_H_
#define PROJECT_HEADERS_RBE_SYSTEM_HUB_2XX_CAN_H_

//Includes
#include "Global_Variables.h"

//Defines
#define HUB2XX_MOB		 	0x17777777
#define HUB2XX_RX_MOB1	 	0x1777D777	//ADC Values
#define HUB2XX_RX_MOB2	 	0x177E7777	//Digital I/O
#define HUB_Comms_count		10
//Variables made public

typedef struct _HUB2XX_ADC_message_
{
	uint8_t					:8;
	uint8_t					:8;
	uint8_t					:8;
	uint8_t					:8;
	uint16_t	ADC_Ref		:16;
	uint8_t					:8;
	uint8_t					:8;

}HUB2XX_ADC_message;

typedef struct _POT_IO_status_
{
	uint8_t	Forward			:1;
	uint8_t	Reverse			:1;
	uint8_t	Stop_reset		:1;
	uint8_t					:1;
	uint8_t					:1;
	uint8_t					:1;
	uint8_t					:1;
	uint8_t					:1;

}POT_IO_status;

//typedef struct _Pulse_Count_
//{
//	uint8_t	LSB			:8;
//	uint8_t	MSB			:8;
//
//}Pulse_Count;

typedef struct _HUB2XX_IO_message_
{
	uint64_t					:8;
	uint64_t					:8;
	uint64_t					:8;
	POT_IO_status   POT_IO		;
	uint64_t					:8;
	uint64_t	Pulse_Count		:16; //PulseCount for 500ms at PROXY1 only- 16bit value
	uint64_t					:8;

}HUB2XX_IO_message;


//1byte
typedef struct _HUB2XX_Status_
{
	uint8_t	Connected		:1;
	uint8_t	MOB1_Received	:1;
	uint8_t	MOB2_Received	:1;
	uint8_t					:1;
	uint8_t					:1;
	uint8_t					:1;
	uint8_t					:1;
	uint8_t					:1;

}HUB2XX_Status;

typedef struct _HUB2XX_Handle_
{
	HUB2XX_Status	HUB2XX_Status;
	uint8_t 		Comms_counter;
	uint8_t			Message_index;

}HUB2XX_Handle;

//Declare required HUB structs
HUB2XX_Handle HUB2XX_handle;
HUB2XX_IO_message HUB2XX_IO;
HUB2XX_ADC_message HUB2XX_ADC;

//Functions made public

void HUB_2XX_Init(void);
void HUB_2XX_Default(void);
bool HUB_2XX_message_Parser(CAN_RxHeaderTypeDef RX_HEADER, uint8_t DataBuffer[]);
void Transmit_HUB_2XX_Control(HUB2XX_Handle *HUB_control);
void HUB_2XX_Handler(void);


#endif /* PROJECT_HEADERS_RBE_SYSTEM_HUB_2XX_CAN_H_ */
