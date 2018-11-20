/*
 * M41T94.h
 * Created on: Mar 11, 2012
 * Company: Mernok Elektronik 
 * Author: S.D. Janse van Rensburg
 */

#ifndef M41T94_H_
#define M41T94_H_
//includes
#include "Global_Variables.h"


//Externals
extern uint8_t Year_bin, Month_bin, Date_bin, Hour_bin, Min_bin, Sec_bin;
extern const char* month_names[12];

//defines
/* SPI Chip Select Pin Defines */
#define CSn								2

typedef enum
{
	Second = 0,
	Minute = 1,
	Hour = 2,
	Day = 3,
	Date = 4,
	Month = 5,
	Year = 6
} RTC_Time;

struct _RTC_Flags
{
	bool		RTC_Reading;
	bool		RTC_Fail;
	bool		RTC_OK;
	bool		RTC_TimeReady;
} RTC_Flags;

//Variables made public
unsigned int time_hundreds;
unsigned int time_tenths;
unsigned int time_seconds;
unsigned int time_10seconds;
unsigned int time_minutes;
unsigned int time_10minutes;
unsigned int time_hours;
unsigned int time_10hours;
unsigned int time_day;
unsigned int time_date;
unsigned int time_10date;
unsigned int time_month;
unsigned int time_10month;
unsigned int time_year;
unsigned int time_10year;

extern uint8_t Time_Actual_Year;
extern uint8_t Time_Actual_Month;
extern uint8_t Time_Actual_Date;
extern uint8_t Time_Actual_WeekDay;
extern uint8_t Time_Actual_Hour;
extern uint8_t Time_Actual_Minute;
extern uint8_t Time_Actual_Second;
extern uint8_t DateBufEx[8];
char Text_Time[50];
char Text_Date[50];

extern uint16_t testcounter;
//Functions made public
void Init_M41T94rtc(void);
void update_time_test(void);
void update_time_Compilation(void);
void Extract_Time(void);
void Extract_Time_Converter(RTC_Time Type,uint8_t Data[]);
void update_time(uint8_t *date_time);
void ReadTime_M41T94rtc(void);
void PrintTime_M41T94rtc(void);
uint8_t ReadByte_M41T94rtc(void);
uint8_t WriteByte_M41T94rtc(uint8_t);
void Display_Time(void);
void Display_Time_New_Font(void);
void select_RTC(void);
void release_RTC(void);

bool Time_Checker_M41T94rtc(void);
bool Time_Checker_0_99(uint8_t value);
bool Time_Checker_0_59(uint8_t value);
bool Time_Checker_1_31(uint8_t value);
bool Time_Checker_0_23(uint8_t value);
bool Time_Checker_1_12(uint8_t value);


//Added for Commander1xx
void ReadBinary_M41T94rtc(void);
void SaveTime_M41T94rtc(void);
void release_RTC_all(void);
void init_RTC_CS_Rev1(void);
void init_RTC_CS_Rev3(void);
void select_RTC_Rev1(void);
void select_RTC_Rev3(void);
void release_RTC_Rev1(void);
void release_RTC_Rev3(void);
void Init_M41T94rtc_Rev1(void);
void Init_M41T94rtc_Rev3(void);
void ReadTime_M41T94rtc_Rev1(void);
void ReadTime_M41T94rtc_Rev3(void);

#endif /* M41T94_H_ */
