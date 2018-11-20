/*=================================
Dev_ADPS9301.c
Created on: 	5 Sept, 2018
Company: 		Mernok Elektronik
Author: 		H. du Plessis
==================================*/

#ifndef APP_DEBUG_H_
#define APP_DEBUG_H_


/**

/*--------------------------------
Includes
----------------------------------*/
#include "stm32f7xx_hal.h"

#include "Global_Variables.h"

/*--------------------------------
Defines
----------------------------------*/
#define LINE_HEIGHT 40


/*--------------------------------
Variables made public
----------------------------------*/
void Startup_Debug(uint16_t Height);

void Operational_Debug(uint16_t Height);
/*--------------------------------
Functions made public
----------------------------------*/


#endif /* APP_DEBUG_H_ */
