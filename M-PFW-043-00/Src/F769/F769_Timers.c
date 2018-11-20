/*
 * F769_Timers.c
 *
 *  Created on: 6 Sept 2018
 *      Author: HduPlessis
 */

#include "F769_Timers.h"




extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/*-----------------------------------------
 *Function name and description
 *---------
 * Stop Timer 3
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void TIM3_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim3);
}


/*-----------------------------------------
 *Function name and description
 *---------
 * Start Timer 3
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void TIM3_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
}
/*-----------------------------------------
 *Function name and description
 *---------
 * Stop Timer 3
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void TIM4_Stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim4);
}


/*-----------------------------------------
 *Function name and description
 *---------
 * Start Timer 3
 *
 *Inputs:
 *---------
 *
 *Outputs:
 *---------
 *
 *-----------------------------------------*/
void TIM4_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim4);
}
