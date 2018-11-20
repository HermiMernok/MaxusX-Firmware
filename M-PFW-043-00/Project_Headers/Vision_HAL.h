/*
 * Vision_HAL.h
 *
 *  Created on: Jul 27, 2015
 *      Author: Kobus
 */

#ifndef VISION_HAL_H_
#define VISION_HAL_H_

#include <stdint.h>

#ifdef STM32F10X_CL

#endif
#ifdef STM32F4XX

#endif

#ifndef MAX
#define MIN(a,b)	((a) < (b) ? (a) : (b))
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#endif

//FIXME #define LF_TX_Capable

//#define FILTER_LF				// experimental

#define num_transp_total 100

#define Reader_input_buffer_size 32		//added CANTag
#define Pulse500_Readers 4				//added CANTag
#define Pulse300_Readers 1				//added CANTag

// define how long a microsecond is
#define UsBase	72
#define USE_TAG_NAME


////////////////////////////////////////////////////////////
// CAN port interface
// this function gets called by Vision Libs to send a can message out.
void APP_CAN_Vision_CAN_TX(uint32_t ID, uint8_t data[], uint8_t packet_length);
#define VisionSendCAN_message(ID, data, len) APP_CAN_Vision_CAN_TX(ID, data, len)
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// COM port interface
// this function gets called by Vision Libs to send a UART message out to a PULSE400 module.
// Todo: add a prototype here for a function to send UART data to a PULSE device.
void APP_COM_Vision_COM_TX(uint8_t COM, uint8_t* data, uint8_t length);
#define VisionSendCOM_message(COM, data, len) APP_COM_Vision_COM_TX(COM, data, len)
////////////////////////////////////////////////////////////


#endif /* VISION_HAL_H_ */
