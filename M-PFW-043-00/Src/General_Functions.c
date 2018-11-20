/*
 * General_Functions.c
 * Created on: Mar 10, 2012
 * Company: Mernok Elektronik
 * Author: S.D. Janse van Rensburg
 */

#include "General_Functions.h"
/****************************************************************/
/**
 * @brief
 * @param
 *   This parameter can be one of following parameters:
 *     @arg
 * @retval None
 */
/****************************************************************/
/***********************************************/

//local variables
uint8_t Low_Byte;
uint8_t High_Byte;
uint8_t Complete_Byte;

/****************************************************************/
/**
 * @brief  converts bcd(char buffer) to 16 bit value .
 * @param1 Value to be converted
 * @retval 16 bit result
 */
/****************************************************************/
uint16_t BCD2Bin(uint8_t *buffer)
{
	uint16_t Result = 0;
	uint8_t t = 0x30;
	Result += ((*buffer++) - t) * 10000;
	Result += ((*buffer++) - t) * 1000;
	Result += ((*buffer++) - t) * 100;
	Result += ((*buffer++) - t) * 10;
	Result += ((*buffer++) - t) * 1;

	return Result;
}

/****************************************************************/
/**
 * @brief  converts bcd(char buffer) to 8 bit value .
 * @param1 Value to be converted
 * @retval 8 bit result
 */
/****************************************************************/
uint8_t BCD2Bin1(uint8_t *buffer)
{
	uint8_t Result = 0;
	uint8_t t = 0x30;
	//Result += ((*buffer++) - t) * 100;
	//Result += ((*buffer++) - t) * 10;
	Result += ((*buffer++) - t) * 1;

	return Result;
}

/****************************************************************/
/**
 * @brief  converts bcd(char buffer) to 8 bit value .
 * @param1 Value to be converted
 * @retval 8 bit result
 */
/****************************************************************/
uint8_t BCD2Bin2(uint8_t *buffer)
{
	uint8_t Result = 0;
	uint8_t t = 0x30;
	//Result += ((*buffer++) - t) * 100;
	Result += ((*buffer++) - t) * 10;
	Result += ((*buffer++) - t) * 1;

	return Result;
}

/****************************************************************/
/**
 * @brief  converts bcd(char buffer) to 8 bit value .
 * @param1 Value to be converted
 * @retval 8 bit result
 */
/****************************************************************/
uint8_t BCD2Bin3(uint8_t *buffer)
{
	uint8_t Result = 0;
	uint8_t t = 0x30;
	Result += ((*buffer++) - t) * 100;
	Result += ((*buffer++) - t) * 10;
	Result += ((*buffer++) - t) * 1;

	return Result;
}
/****************************************************************/
/**
 * @brief  converts 16 bit value to bcd (char buffer) .
 * @param1 Value to be converted
 * @param2 pointer to char buffer where results will be saved
 * @param3 amount of digits to convert, will convert lower bytes
 * @retval None
 */
/****************************************************************/
void Bin2BCD(uint16_t bin_inp, char *buffer, uint8_t digits)
{
	uint16_t Dig_1, Dig_2, Dig_3, Dig_4;
	uint16_t temp;

	temp  = bin_inp;
	if(digits >= 5)
	{
		*buffer++ = temp/10000 + 0x30;
	}

	Dig_4 = temp/10000;
	temp  = temp - (Dig_4 * 10000);
	if(digits >= 4)
	{
		*buffer++ = temp/1000 + 0x30;
	}

	Dig_3 = temp/1000;
	temp  = temp - (Dig_3 * 1000);
	if(digits >= 3)
	{
		*buffer++ = temp/100 + 0x30;
	}

	Dig_2 = temp/100;
	temp  = temp - (Dig_2 * 100);
	if(digits >= 2)
	{
		*buffer++ = temp/10 + 0x30;
	}

	Dig_1 = temp/10;
	temp  = temp - (Dig_1 * 10);
	if(digits >=1)
	{
		*buffer++ = temp + 0x30;
	}
	//	Dig_0 = temp;
}



/****************************************************************/
/*
 *Function takes a 16 bit value and splits it into high and low byte
 */
/****************************************************************/
void Int2Byte(uint16_t value, uint8_t *array_to_store)
{
	for (int i=0; i < 2; i++)
	{
		array_to_store[i] = value & 0xFF;
		value >>= 8;
	}
}




/****************************************************************/
/*Function takes 2 bytes and creates a INT
 *
 */
/****************************************************************/
uint16_t Byte2Int(uint8_t high_byte, uint8_t low_byte)
{
	//method 1
	uint16_t k = 0;
	k = (high_byte) * (256);
	uint16_t i = 0;
	i = k + low_byte;

	//method 2
	//uint16_t i = 0;
	//i = ((high_byte) << 8) | low_byte;

	return i;
}

/****************************************************************/
//This function converts hex to ascii for displaying on lcd
//
/****************************************************************/
void HextoASCII(unsigned char hex)
{
	unsigned char temp_L;           // dummy variable that will hold LSBs of Hex number
	unsigned char temp_H;           // dummy variable that will hold MSBs of Hex number

	temp_H = hex & 0xF0;            // Obtain the upper 4 bits (MSBs) of hex number
	temp_H = temp_H >> 4;           //
	if(temp_H >9)                   // Check if the number is a letter
		temp_H += 0x37;             // Convert the number to a letter in ASCII
	else
		temp_H += 0x30;             // Convert the number to ASCII number
	High_Byte = temp_H;
	temp_L = hex & 0x0F;            // Obtain the lower 4 bits (LSBs) of hex number
	if(temp_L >9)                   // Check if the the number is a letter
		temp_L += 0x37;             // Convert the number to a letter in ASCII
	else
		temp_L += 0x30;             // Convert the number to ASCII number
	Low_Byte = temp_L;
}

/****************************************************************/
//This function converts ascii to hex
//
/****************************************************************/
void ASCIItoHex(void)
{


	if(High_Byte > 0x40)             		// Check if the number is a letter
		High_Byte -= 0x37;           		// Convert the number to a ascii
	else
		High_Byte -= 0x30;           		// Convert the number to ASCII number
	High_Byte = High_Byte << 4;

	if(Low_Byte > 0x40)                  	// Check if the the number is a letter
		Low_Byte -= 0x37;              		// Convert the number to a ascii
	else
		Low_Byte -= 0x30;
	Complete_Byte = Low_Byte + High_Byte;	// Convert ascii to hex
}


/****************************************************************/
//This function will check if a specific bit is set or not
//bit order: 7,6,5,4,3,2,1,0
/****************************************************************/
bool check_bit(uint8_t byte_to_check, uint8_t bit_to_check)
{
	//check which bit to check
	switch(bit_to_check)
	{

	//bit 0
	case 0:
		if(((byte_to_check & 0b00000001) & (0b00000001)) == 0b00000001)
			return true;
		else
			return false;
		break;

		//bit 1
	case 1:
		if(((byte_to_check & 0b00000010) & (0b00000010)) == 0b00000010)
			return true;
		else
			return false;
		break;

		//bit 2
	case 2:
		if(((byte_to_check & 0b00000100) & (0b00000100)) == 0b00000100)
			return true;
		else
			return false;
		break;

		//bit 3
	case 3:
		if(((byte_to_check & 0b00001000) & (0b00001000)) == 0b00001000)
			return true;
		else
			return false;
		break;

		//bit 4
	case 4:
		if(((byte_to_check & 0b00010000) & (0b00010000)) == 0b00010000)
			return true;
		else
			return false;
		break;

		//bit 5
	case 5:
		if(((byte_to_check & 0b00100000) & (0b00100000)) == 0b00100000)
			return true;
		else
			return false;
		break;

		//bit 6
	case 6:
		if(((byte_to_check & 0b01000000) & (0b01000000)) == 0b01000000)
			return true;
		else
			return false;
		break;

		//bit 7
	case 7:
		if(((byte_to_check & 0b10000000) & (0b10000000)) == 0b10000000)
			return true;
		else
			return false;
		break;

	default:
		return false;
		break;
	}
}



/****************************************************************/
//This function will set or clear a bit
//bit order: 7,6,5,4,3,2,1,0
/****************************************************************/
void handle_bit(uint8_t *byte_to_control, uint8_t bit_to_control, bool state)
{
	//check which bit to check
	switch(bit_to_control)
	{

	//bit 0
	case 0:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000001);
		else
			*byte_to_control = (*byte_to_control & 0b11111110);
		break;

		//bit 1
	case 1:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000010);
		else
			*byte_to_control = (*byte_to_control & 0b11111101);
		break;

		//bit 2
	case 2:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000100);
		else
			*byte_to_control = (*byte_to_control & 0b11111011);
		break;

		//bit 3
	case 3:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00001000);
		else
			*byte_to_control = (*byte_to_control & 0b11110111);
		break;

		//bit 4
	case 4:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00010000);
		else
			*byte_to_control = (*byte_to_control & 0b11101111);
		break;

		//bit 5
	case 5:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00100000);
		else
			*byte_to_control = (*byte_to_control & 0b11011111);
		break;

		//bit 6
	case 6:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b01000000);
		else
			*byte_to_control = (*byte_to_control & 0b10111111);
		break;

		//bit 7
	case 7:
		if(state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b10000000);
		else
			*byte_to_control = (*byte_to_control & 0b01111111);
		break;

	default:
		break;
	}
}


void handle_bit32(uint32_t *byte_to_control, uint8_t bit_to_control, bool state)
{
//check which bit to check
	switch (bit_to_control)
	{

//bit 0
	case 0:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000000000001);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111111111110);
		break;

		//bit 1
	case 1:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000000000010);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111111111101);
		break;

		//bit 2
	case 2:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000000000100);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111111111011);
		break;

		//bit 3
	case 3:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000000001000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111111110111);
		break;

		//bit 4
	case 4:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000000010000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111111101111);
		break;

		//bit 5
	case 5:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000000100000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111111011111);
		break;

		//bit 6
	case 6:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000001000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111110111111);
		break;

		//bit 7
	case 7:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000010000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111101111111);
		break;

		//bit 8
	case 8:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000000100000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111111011111111);
		break;

		//bit 9
	case 9:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000001000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111110111111111);
		break;

		//bit 10
	case 10:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000010000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111101111111111);
		break;

		//bit 11
	case 11:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000000100000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111111011111111111);
		break;

		//bit 12
	case 12:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000001000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111110111111111111);
		break;

		//bit 13
	case 13:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000010000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111101111111111111);
		break;

		//bit 14
	case 14:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000000100000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111111011111111111111);
		break;

		//bit 15
	case 15:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000001000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111110111111111111111);
		break;

		//bit 16
	case 16:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000010000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111101111111111111111);
		break;

		//bit 17
	case 17:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000000100000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111111011111111111111111);
		break;

		//bit 18
	case 18:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000001000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111110111111111111111111);
		break;

		//bit 19
	case 19:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000010000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111101111111111111111111);
		break;

		//bit 20
	case 20:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000000100000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111111011111111111111111111);
		break;

		//bit 21
	case 21:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000001000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111110111111111111111111111);
		break;

		//bit 22
	case 22:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000010000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111101111111111111111111111);
		break;

		//bit 23
	case 23:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000000100000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111111011111111111111111111111);
		break;

		//bit 24
	case 24:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000001000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111110111111111111111111111111);
		break;

		//bit 25
	case 25:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000010000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111101111111111111111111111111);
		break;

		//bit 26
	case 26:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00000100000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11111011111111111111111111111111);
		break;

		//bit 27
	case 27:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00001000000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11110111111111111111111111111111);
		break;
		//bit 28
	case 28:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00010000000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11101111111111111111111111111111);
		break;
		//bit 29
	case 29:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b00100000000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b11011111111111111111111111111111);
		break;

		//bit 30
	case 30:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b01000000000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b10111111111111111111111111111111);
		break;
		//bit 31
	case 31:
		if (state == Bit_Set)
			*byte_to_control = (*byte_to_control | 0b10000000000000000000000000000000);
		else
			*byte_to_control = (*byte_to_control & 0b01111111111111111111111111111111);
		break;
	default:
		break;
	}
}



/****************************************************************/
/*Function copies from one array, to another from a certain point
 * and copies a certain amount of bytes
 *
 */
/****************************************************************/
void Copy_Array(unsigned char *Destination_Array, uint16_t Destintation_Start_position ,unsigned char *Source_Array, uint16_t Source_Start_position, uint16_t Bytes_to_Copy)
{

	//offset the destination array
	Destination_Array += Destintation_Start_position;

	//Offset the source array
	Source_Array += Source_Start_position;

	//copy from source to destination
	for(uint16_t i = Source_Start_position; i < (Source_Start_position + Bytes_to_Copy); i++)
	{
		*Destination_Array++ = *Source_Array++;
	}


	//	for(uint8_t i = 0; i < System_Message_Length; i++)
	//	{
	//	//	*Destination_message++ = *This_Message++;
	//	}
}


/****************************************************************/
/*Function Toggles a Binary bool from current value to inverse value
 *
 */
/****************************************************************/
bool Toggle_Bool(bool BoolValue)
{

	if(BoolValue == true)
		return false;
	else
		return true;

}
