/*
 * General_Functions.h
 * Created on: Mar 10, 2012
 * Company: Mernok Elektronik
 * Author: S.D. Janse van Rensburg
 */

#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_
#include "Global_Variables.h"

#define 	BCD2BIN(n)   ( ((n) >> 4) * 10 + ((n) & 0x0F) )
#define 	BIN2BCD(n)   ( (((n) / 10) << 4) + ((n) % 10) )


extern uint8_t High_Byte;
extern uint8_t Low_Byte;
extern uint8_t Complete_Byte;

void Bin2BCD(uint16_t bin_inp, char *buffer, uint8_t digits);
uint16_t BCD2Bin(uint8_t *buffer);
uint8_t BCD2Bin1(uint8_t *buffer);
uint8_t BCD2Bin2(uint8_t *buffer);
uint8_t BCD2Bin3(uint8_t *buffer);

void Int2Byte(uint16_t value, uint8_t *array_to_store);
uint16_t Byte2Int(uint8_t high_byte, uint8_t low_byte);
void HextoASCII(unsigned char hex);
void ASCIItoHex(void);
bool check_bit(uint8_t byte_to_check, uint8_t bit_to_check);
void handle_bit(uint8_t *byte_to_control, uint8_t bit_to_control, bool state);
void handle_bit32(uint32_t *byte_to_control, uint8_t bit_to_control, bool state);
void Copy_Array(unsigned char *Destination_Array, uint16_t Destintation_Start_position ,unsigned char *Source_Array, uint16_t Source_Start_position, uint16_t Bytes_to_Copy);
bool Toggle_Bool(bool BoolValue);

#endif /* GENERAL_FUNCTIONS_H_ */
