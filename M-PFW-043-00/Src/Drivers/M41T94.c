/*
 * M41T94.c
 * Created on: Mar 11, 2012
 * Company: Mernok Elektronik 
 * Author: S.D. Janse van Rensburg
 */
#include "ICs/M41T94.h"
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
//global variables

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
//time used in system
uint8_t Time_Actual_Year = 0;	//year byte 0x00 - 0x99
uint8_t Time_Actual_Month = 0;	//month byte 0x00 - 0x12
uint8_t Time_Actual_Date = 0;	//Date byte 0x00 - 0x31
uint8_t Time_Actual_WeekDay = 0;	//weekday byte 0x01 - 0x07  1 = Sunday, 7 = Saturday
uint8_t Time_Actual_Hour = 0;	//Hour byte 0x00 - 0x24
uint8_t Time_Actual_Minute = 0;    //Minute byte 0x00 - 0x59
uint8_t Time_Actual_Second = 0;	//Second byte 0x00 - 0x59
//uint8_t Low_Byte_RTC;
//uint8_t High_Byte_RTC;
//uint8_t Complete_Byte_RTC;
uint8_t DateBufEx[8] = { 0 };

uint8_t Year_bin, Month_bin, Date_bin, Hour_bin, Min_bin, Sec_bin;

const char* month_names[12] =
{ "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

uint8_t Result = 0;
int ResultFlag = 0;
int k = 0;
int SPI_Tx_ResultFlag = 0;

uint16_t testcounter = 0;
/****************************************************************/
/*Initialise the CS pin of RTC
 *
 */
/****************************************************************/


/****************************************************************/
/****************************************************************/
void select_RTC(void)
{
	//HAL_GPIO_WritePin(RTC__CS_PORT[RTC_CS],RTC__CS_PIN[RTC_CS], GPIO_PIN_RESET);
	IO_Output_control(RTC_CS, On);
}



/****************************************************************/
/****************************************************************/
void release_RTC(void)
{
	//HAL_GPIO_WritePin(RTC__CS_PORT[RTC_CS],RTC__CS_PIN[RTC_CS], GPIO_PIN_SET);
	IO_Output_control(RTC_CS, Off);
}

/****************************************************************/

void release_RTC_all(void)
{

	/* Enable the GPIO Clock */ //todo
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//RCC_AHB1PeriphClockCmd(RTC__CS_CLK[Input], ENABLE);

//	/* Configure the GPIO pin */
//	GPIO_InitStructure.Pin = RTC__CS_PIN[RTC_CS];
//	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStructure.Pull = GPIO_NOPULL;
//	GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
//	HAL_GPIO_Init(RTC__CS_PORT[RTC_CS], &GPIO_InitStructure);
//
//	/* Configure the GPIO pin */
//	GPIO_InitStructure.Pin = RTC__CS_PIN[RTC_CS_Rev3];
//	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStructure.Pull = GPIO_NOPULL;
//	GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
//	HAL_GPIO_Init(RTC__CS_PORT[RTC_CS_Rev3], &GPIO_InitStructure);
//
//	HAL_GPIO_WritePin(RTC__CS_PORT[RTC_CS],RTC__CS_PIN[RTC_CS], GPIO_PIN_SET);
//	HAL_GPIO_WritePin(RTC__CS_PORT[RTC_CS_Rev3],RTC__CS_PIN[RTC_CS_Rev3], GPIO_PIN_SET);
}

/****************************************************************/
void Init_M41T94rtc(void)
{
	HAL_Delay(10);

//	if(System_Flags.System_HW_Rev > 2)
//		init_RTC_CS(RTC_CS_Rev3);
//	else
//		init_RTC_CS(RTC_CS);
//
//	init_RTC_CS(0);
	/* Setup the M41T94 RTC */
	/* Enable device */
	select_RTC();
	for (k = 0; k < 5; k++)
	{
		;
	}
	/* Reset the Control Registers */
	WriteByte_M41T94rtc(0b10001000);						// WRITE mode -> Address 0x08
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x08
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x09
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x0A
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x0B
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x0C
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x0D
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x0E
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x0F
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x10
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x11
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x12
	WriteByte_M41T94rtc(0b00000000);						// Data for Address 0x13
	for (k = 0; k < 5; k++)
	{
		;
	}
	/* Disable device */
	release_RTC();

	HAL_Delay(10);

}

void update_time_test(void)
{
	//		/* Set default time to 1 January 2011 12:00:00 */
	select_RTC();
	for (int k = 0; k < 500; k++)
	{
		;
	}

	WriteByte_M41T94rtc(0b10000000);				// WRITE mode -> Address 0x00
	WriteByte_M41T94rtc(0x00);						// ms
	WriteByte_M41T94rtc(0x00);			// second
	WriteByte_M41T94rtc(0x00);			// minute
	WriteByte_M41T94rtc(0x12);			// hour
	WriteByte_M41T94rtc(0x01);			// day
	WriteByte_M41T94rtc(0x01);			// date
	WriteByte_M41T94rtc(0x01);			// month
	WriteByte_M41T94rtc(0x11);			// year

	release_RTC();
	for (int k = 0; k < 500; k++)
	{
		;
	}

}

void update_time_Compilation(void)
{
	/* Set time to when unit FW was compiled */
	Extract_Time();

	select_RTC();
	for (int k = 0; k < 500; k++)
	{
		;
	}

	WriteByte_M41T94rtc(0b10000000);			// WRITE mode -> Address 0x00
	WriteByte_M41T94rtc(0x00);					// ms
	WriteByte_M41T94rtc(DateBufEx[0]);			// second
	WriteByte_M41T94rtc(DateBufEx[1]);			// minute
	WriteByte_M41T94rtc(DateBufEx[2]);			// hour
	WriteByte_M41T94rtc(DateBufEx[3]);			// day
	WriteByte_M41T94rtc(DateBufEx[4]);			// date
	WriteByte_M41T94rtc(DateBufEx[5]);			// month
	WriteByte_M41T94rtc(DateBufEx[6]);			// year

	release_RTC();
	for (int k = 0; k < 500; k++)
	{
		;
	}

}

void Extract_Time(void)
{
	DateBufEx[6] = 1;			//Time_Actual_Year;
	DateBufEx[5] = 1;			//Time_Actual_Month;
	DateBufEx[4] = 1;			//Time_Actual_Date;
	DateBufEx[3] = 1;			//Time_Actual_WeekDay;
	DateBufEx[2] = 1;			//Time_Actual_Hour;
	DateBufEx[1] = 1;			//Time_Actual_Minute;
	DateBufEx[0] = 1;			//Time_Actual_Second;

	char* TimeStamp;
	uint8_t temp[3] =
	{ 0 };
	TimeStamp = FWConfigTimeStamp;

	memcpy(&temp[0], &(TimeStamp[22]), 2);			//	Year
	Extract_Time_Converter(Year, temp);

	memcpy(&temp[0], &(TimeStamp[8]), 2);			//	Date
	Extract_Time_Converter(Date, temp);

	memcpy(&temp[0], &(TimeStamp[11]), 2);			//	Hour
	Extract_Time_Converter(Hour, temp);

	memcpy(&temp[0], &(TimeStamp[14]), 2);			//	Min
	Extract_Time_Converter(Minute, temp);

	memcpy(&temp[0], &(TimeStamp[17]), 2);			//	Sec
	Extract_Time_Converter(Second, temp);

	memcpy(&temp[0], &(TimeStamp[4]), 3);			//	Month
	Extract_Time_Converter(Month, temp);

	memcpy(&temp[0], &(TimeStamp[0]), 3);			//	Day
	Extract_Time_Converter(Day, temp);
}

//void Extract_Time_Converter(RTC_Time Type, uint8_t Data[3])
//{
//	switch (Type)
//	{
//	case Year:								//Time_Actual_Year;
//		High_Byte = Data[0];
//		Low_Byte = Data[1];
//		ASCIItoHex();					//convert high and low byte to hex value
//		DateBufEx[6] = Complete_Byte;	//Put this into
//		break;
//
//	case Month:								//Time_Actual_Month;
//		if  (memcmp(Data, "Dec",3) == 0)
//			DateBufEx[5] = 0x12;
//		else if (memcmp(Data, "Nov",3) == 0)
//			DateBufEx[5] = 0x11;
//		else if  (memcmp(Data, "Oct",3) == 0)
//			DateBufEx[5] = 0x10;
//		else if (memcmp(Data, "Sep",3) == 0)
//			DateBufEx[5] = 0x09;
//		else if  (memcmp(Data, "Aug",3) == 0)
//			DateBufEx[5] = 0x08;
//		else if (memcmp(Data, "Jul",3) == 0)
//			DateBufEx[5] = 0x07;
//		else if  (memcmp(Data, "Jun",3) == 0)
//			DateBufEx[5] = 0x06;
//		else if (memcmp(Data, "May",3) == 0)
//			DateBufEx[5] = 0x05;
//		else if  (memcmp(Data, "Apr",3) == 0)
//			DateBufEx[5] = 0x04;
//		else if (memcmp(Data, "Mar",3) == 0)
//			DateBufEx[5] = 0x03;
//		else if  (memcmp(Data, "Feb",3) == 0)
//			DateBufEx[5] = 0x02;
//		else if (memcmp(Data, "Jan",3) == 0)
//			DateBufEx[5] = 0x01;
//		else
//			DateBufEx[5] = 0x01;
//		break;
//
//	case Date:								//Time_Actual_Date;
//		High_Byte = Data[0];
//		Low_Byte = Data[1];
//		ASCIItoHex();					//convert high and low byte to hex value
//		DateBufEx[4] = Complete_Byte;	//Put this into
//		break;
//
//	case Day:
//		if  (memcmp(Data, "Sun",3) == 0)	//Time_Actual_WeekDay;
//			DateBufEx[3] = 0x07;
//		else if (memcmp(Data, "Sat",3) == 0)
//			DateBufEx[3] = 0x06;
//		else if  (memcmp(Data, "Fri",3) == 0)
//			DateBufEx[3] = 0x05;
//		else if (memcmp(Data, "Thu",3) == 0)
//			DateBufEx[3] = 0x04;
//		else if  (memcmp(Data, "Wed",3) == 0)
//			DateBufEx[3] = 0x03;
//		else if (memcmp(Data, "Tue",3) == 0)
//			DateBufEx[3] = 0x02;
//		else if  (memcmp(Data, "Mon",3) == 0)
//			DateBufEx[3] = 0x01;
//		else
//			DateBufEx[3] = 0x01;
//		break;
//
//	case Hour:								//Time_Actual_Hour;
//		High_Byte = Data[0];
//		Low_Byte = Data[1];
//		ASCIItoHex();					//convert high and low byte to hex value
//		DateBufEx[2] = Complete_Byte;	//Put this into
//		break;
//
//	case Minute:							//Time_Actual_Minute;
//		High_Byte = Data[0];
//		Low_Byte = Data[1];
//		ASCIItoHex();					//convert high and low byte to hex value
//		DateBufEx[1] = Complete_Byte;	//Put this into
//		break;
//
//	case Second:							//Time_Actual_Second;
//		High_Byte = Data[0];
//		Low_Byte = Data[1];
//		ASCIItoHex();					//convert high and low byte to hex value
//		DateBufEx[0] = Complete_Byte;	//Put this into
//		break;
//	}
//}

//function updates the rtc time from pc time
void update_time(uint8_t *date_time)
{

	select_RTC();
	for (int k = 0; k < 500; k++)
	{
		;
	}
	WriteByte_M41T94rtc(0b10000000);				// WRITE mode -> Address 0x00
	WriteByte_M41T94rtc(0x00);						// ms
	WriteByte_M41T94rtc(*date_time++);				// second
	WriteByte_M41T94rtc(*date_time++);				// minute
	WriteByte_M41T94rtc(*date_time++);				// hour
	WriteByte_M41T94rtc(*date_time++);				// day
	WriteByte_M41T94rtc(*date_time++);				// date
	WriteByte_M41T94rtc(*date_time++);				// month
	WriteByte_M41T94rtc(*date_time++);				// year
	release_RTC();
	for (int k = 0; k < 500; k++)
	{
		;
	}

}

/****************************************************************/
/****************************************************************/
void ReadTime_M41T94rtc(void)
{
	uint8_t temp_rtc;

	select_RTC();
	for (k = 0; k < 5; k++)
	{
		;
	}

	WriteByte_M41T94rtc(0b00000000);						// READ mode -> Address 0x00
	/* Address 0x00 */
	temp_rtc = ReadByte_M41T94rtc();
	time_hundreds = temp_rtc & 0x0F;
	time_tenths = temp_rtc >> 4;
	/* Address 0x01 */
	temp_rtc = ReadByte_M41T94rtc();
	temp_rtc = temp_rtc & 0x7F;
	time_seconds = temp_rtc & 0x0F;
	time_10seconds = temp_rtc >> 4;
	/* Address 0x02 */
	temp_rtc = ReadByte_M41T94rtc();
	time_minutes = temp_rtc & 0x0F;
	time_10minutes = temp_rtc >> 4;
	/* Address 0x03 */
	temp_rtc = ReadByte_M41T94rtc();
	temp_rtc = temp_rtc & 0x3F;
	time_hours = temp_rtc & 0x0F;
	time_10hours = temp_rtc >> 4;
	/* Address 0x04 */
	temp_rtc = ReadByte_M41T94rtc();
	time_day = temp_rtc & 0x07;
	/* Address 0x05 */
	temp_rtc = ReadByte_M41T94rtc();
	time_date = temp_rtc & 0x0F;
	time_10date = temp_rtc >> 4;
	/* Address 0x06 */
	temp_rtc = ReadByte_M41T94rtc();
	time_month = temp_rtc & 0x0F;
	time_10month = temp_rtc >> 4;
	/* Address 0x07 */
	temp_rtc = ReadByte_M41T94rtc();
	time_year = temp_rtc & 0x0F;
	time_10year = temp_rtc >> 4;

	release_RTC();
	for (k = 0; k < 5; k++)
	{
		;
	}

	Time_Actual_Year = (time_10year << 4) | time_year;
	Time_Actual_Month = (time_10month << 4) | time_month;
	Time_Actual_Date = (time_10date << 4) | time_date;
	Time_Actual_WeekDay = time_day;
	Time_Actual_Hour = (time_10hours << 4) | time_hours;
	Time_Actual_Minute = (time_10minutes << 4) | time_minutes;
	Time_Actual_Second = (time_10seconds << 4) | time_seconds;

	if (!Time_Checker_M41T94rtc())	//true if time is correct
	{
		//todo		System_Settings.Error_Code = System_Fault;
		testcounter++;
	}
	else
	{
		//todo		System_Settings.Error_Code = None;
	}
}

/****************************************************************/
/* Display time on 7" LCD
 *
 */
/****************************************************************/
void Display_Time(void)
{
	char hours[2] = {0};
	char minutes[2] = {0};
	char seconds[2] = {0};
	char date[2] = {0};
	char month[2] = {0};
	char year[2] = {0};

	if(RTC_Flags.RTC_TimeReady)
	{

		RTC_Flags.RTC_TimeReady = false;

		ReadTime_M41T94rtc();

		//display years
		year[0] = time_10year + 0x30;
		year[1] = time_year + 0x30;

		//display months
		month[0] = time_10month + 0x30;
		month[1] = time_month + 0x30;

		//display date
		date[0] = time_10date + 0x30;
		date[1] = time_date + 0x30;

		//display hours
		hours[0] = time_10hours + 0x30;
		hours[1] = time_hours + 0x30;

		//display minutes
		minutes[0] = time_10minutes + 0x30;
		minutes[1] = time_minutes + 0x30;

		//display seconds
		seconds[0] = time_10seconds + 0x30;
		seconds[1] = time_seconds + 0x30;

		if(Time_Checker_M41T94rtc())
		{
			sprintf(Text_Time,"%c%c:%c%c:%c%c", hours[0],hours[1], minutes[0], minutes[1], seconds[0], seconds[1]);
			sprintf(Text_Date,"20%c%c/%c%c/%c%c", year[0],year[1], month[0], month[1], date[0], date[1]);
		}
	}

}

/****************************************************************/
// Display time on LCD using new Font
/****************************************************************/
void Display_Time_New_Font(void)
{
	//
	//	char time_string[3];
	//	time_string[2] = 0;
	//
	//	char full_time_string[20] =
	//	{ 0 };
	//
	//	//Load Millennium
	//	full_time_string[0] = '2';
	//	full_time_string[1] = '0';
	//
	//	//Load year
	//	full_time_string[2] = time_10year + 0x30;
	//	full_time_string[3] = time_year + 0x30;
	//
	//	//Load /
	//	full_time_string[4] = '/';
	//
	//	//Load month
	//	full_time_string[5] = time_10month + 0x30;
	//	full_time_string[6] = time_month + 0x30;
	//
	//	//Load /
	//	full_time_string[7] = '/';
	//
	//	//Load Date
	//	full_time_string[8] = time_10date + 0x30;
	//	full_time_string[9] = time_date + 0x30;
	//
	//	//Load ' '
	//	full_time_string[10] = ' ';
	//
	//	//Load Hours
	//	full_time_string[11] = time_10hours + 0x30;
	//	full_time_string[12] = time_hours + 0x30;
	//
	//	//Load ':'
	//	full_time_string[13] = ':';
	//
	//	//Load Minutes
	//	full_time_string[14] = time_10minutes + 0x30;
	//	full_time_string[15] = time_minutes + 0x30;
	//
	//	//Load ':'
	//	full_time_string[16] = ':';
	//
	//	//Load Seconds
	//	full_time_string[17] = time_10seconds + 0x30;
	//	full_time_string[18] = time_seconds + 0x30;
	//
	//	//Load nul as termination
	//	full_time_string[19] = ' ';
	//
	//	//Clear MS bottom 2
	//	LCD_DrawRectangleFill(LCD_MB_Low_2_X, LCD_MB_Low_2_X + w2 - 5 - 1, LCD_MB2_Y, LCD_MB2_Y + LCD_MB2_Height - 1, Message_Box_Colour);
	//
	//	//Display the string
	//	full_time_string[19] = 0;
	//	OutTextXY(LCD_MB_Low_2_X + 5, LCD_Botton_MB_Text_Y, full_time_string);
}

/****************************************************************/
// Send time to PC
/****************************************************************/
void PrintTime_M41T94rtc(void)
{
	ReadTime_M41T94rtc();

	/* Line 1 */
	USART_SendString(0, "Time: ");
	USART_Sendbyte(0, time_10hours + 0x30);
	USART_Sendbyte(0, time_hours + 0x30);
	USART_Sendbyte(0, ':');
	USART_Sendbyte(0, time_10minutes + 0x30);
	USART_Sendbyte(0, time_minutes + 0x30);
	USART_Sendbyte(0, ':');
	USART_Sendbyte(0, time_10seconds + 0x30);
	USART_Sendbyte(0, time_seconds + 0x30);
	USART_Sendbyte(0, '\r');
	USART_Sendbyte(0, '\n');

	USART_SendString(0, "Date: ");
	USART_Sendbyte(0, time_10date + 0x30);
	USART_Sendbyte(0, time_date + 0x30);
	USART_Sendbyte(0, '/');
	USART_Sendbyte(0, time_10month + 0x30);
	USART_Sendbyte(0, time_month + 0x30);
	USART_Sendbyte(0, '/');
	USART_Sendbyte(0, '2');
	USART_Sendbyte(0, '0');
	USART_Sendbyte(0, time_10year + 0x30);
	USART_Sendbyte(0, time_year + 0x30);
	USART_Sendbyte(0, '\r');
	USART_Sendbyte(0, '\n');
}

/****************************************************************/
/**
 * @brief  Reads a byte from the RTC.
 * @note
 * @param  None
 * @retval Byte Read from the RTC.
 */
/****************************************************************/
uint8_t ReadByte_M41T94rtc(void)
{
	return (WriteByte_M41T94rtc(0x55));
}

/****************************************************************/
/**
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param  byte: byte to send.
 * @retval The value of the received byte.
 */
/****************************************************************/
uint8_t WriteByte_M41T94rtc(uint8_t Data)
{
	uint8_t rx_data = 0;

	//Transmit data and receive result in rx_data buffer (single byte)
	HAL_SPI_TransmitReceive(&hspi2, &Data, &rx_data, 1, 100);

	return rx_data;

}

bool Time_Checker_M41T94rtc(void)
{
	//Check the time stamp
	if (Time_Checker_0_99(Time_Actual_Year))							//Check Year
		if (Time_Checker_1_12(Time_Actual_Month))						//Check Month
			if (Time_Checker_1_31(Time_Actual_Date))					//Check Date
				if (Time_Checker_0_23(Time_Actual_Hour))				//Check Hour
					if (Time_Checker_0_59(Time_Actual_Minute))			//Check Minute
						if (Time_Checker_0_59(Time_Actual_Second))		//Check Second
							return true;

	//If timestamp incorrect in any way
	return false;
}

bool Time_Checker_0_99(uint8_t value)
{
	switch (value)
	{
	case 0x00 ... 0x09:
	case 0x10 ... 0x19:
	case 0x20 ... 0x29:
	case 0x30 ... 0x39:
	case 0x40 ... 0x49:
	case 0x50 ... 0x59:
	case 0x60 ... 0x69:
	case 0x70 ... 0x79:
	case 0x80 ... 0x89:
	case 0x90 ... 0x99:

	return true;
	break;

	default:
		return false;
		break;
	}
}
bool Time_Checker_0_59(uint8_t value)
{
	switch (value)
	{
	case 0x00 ... 0x09:
	case 0x10 ... 0x19:
	case 0x20 ... 0x29:
	case 0x30 ... 0x39:
	case 0x40 ... 0x49:
	case 0x50 ... 0x59:
	return true;
	break;

	default:
		return false;
		break;
	}
}
bool Time_Checker_1_31(uint8_t value)
{
	switch (value)
	{
	case 0x01 ... 0x09:
	case 0x10 ... 0x19:
	case 0x20 ... 0x29:
	case 0x30 ... 0x31:
	return true;
	break;

	default:
		return false;
		break;
	}
}
bool Time_Checker_0_23(uint8_t value)
{
	switch (value)
	{
	case 0x00 ... 0x09:
	case 0x10 ... 0x19:
	case 0x20 ... 0x23:
	return true;
	break;

	default:
		return false;
		break;
	}
}
bool Time_Checker_1_12(uint8_t value)
{
	switch (value)
	{
	case 0x01 ... 0x09:
	case 0x10 ... 0x12:
	return true;
	break;

	default:
		return false;
		break;
	}
}


/****************************************************************/
// APPLICATION CODE ADDED FOR COMMANDER1XX
/****************************************************************/

///****************************************************************/
//// save time values to device
///****************************************************************/
void WriteTime_M41T94rtc(void)
{
	select_RTC();
	for (k = 0; k < 5; k++)
		;

	WriteByte_M41T94rtc(0b10000000);							// Write mode -> Address 0x00
	/* Address 0x00 */
	WriteByte_M41T94rtc(0);
	/* Address 0x01 */
	WriteByte_M41T94rtc(0);
	/* Address 0x02 */
	WriteByte_M41T94rtc(Time_Actual_Minute);
	/* Address 0x03 */
	WriteByte_M41T94rtc(Time_Actual_Hour);
	/* Address 0x04 */
	WriteByte_M41T94rtc(Time_Actual_WeekDay);
	/* Address 0x05 */
	WriteByte_M41T94rtc(Time_Actual_Date);
	/* Address 0x06 */
	WriteByte_M41T94rtc(Time_Actual_Month);
	/* Address 0x07 */
	WriteByte_M41T94rtc(Time_Actual_Year);

	release_RTC();
}

/****************************************************************/
/*
 * helper function: converts the BCD(hex) values to binary
 */
/****************************************************************/
uint8_t BCD_to_BIN(uint8_t BCD)
{
	return ((BCD & 0x0F) + ((BCD >> 4) * 10));
}

/****************************************************************/
/*
 * helper function: converts the binary value passed to BCD
 */
/****************************************************************/
uint8_t BIN_to_BCD(uint8_t BIN)
{
	uint8_t top = 0, bot = 0;
	top = BIN / 10;
	bot = BIN % 10;
	return (bot + (top << 4));
}


/****************************************************************/
/**
 * @brief  Reads time values into binary registers.
 */
/****************************************************************/
void ReadBinary_M41T94rtc(void)
{
	ReadTime_M41T94rtc();

	Year_bin = BCD_to_BIN(Time_Actual_Year);
	Month_bin = BCD_to_BIN(Time_Actual_Month);
	Date_bin = BCD_to_BIN(Time_Actual_Date);
	Hour_bin = BCD_to_BIN(Time_Actual_Hour);
	Min_bin = BCD_to_BIN(Time_Actual_Minute);
}

/****************************************************************/
/**
 * @brief 	Write binary values to hex time registers and save them.
 * 			run after editing the time
 */
/****************************************************************/
void SaveTime_M41T94rtc(void)
{
	Time_Actual_Year = BIN_to_BCD(Year_bin);
	Time_Actual_Month = BIN_to_BCD(Month_bin);
	Time_Actual_Date = BIN_to_BCD(Date_bin);
	Time_Actual_Hour = BIN_to_BCD(Hour_bin);
	Time_Actual_Minute = BIN_to_BCD(Min_bin);
	Time_Actual_Second = BIN_to_BCD(Sec_bin);;

	WriteTime_M41T94rtc();
}
