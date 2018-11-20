/* App_Text.h
 *
 *  Created on: Jan 23, 2015
 *      Author: JacoOlivier
 */

#ifndef APP_TEXT_H_
#define APP_TEXT_H_

//Includes
#include "Global_Variables.h"

#define SPACE	32

//Defines


typedef enum
{
	Text_Extra_Small 	= 0,
	Text_Small 			= 1,
	Text_Medium 		= 2,
	Text_Large			= 3

}Text_SizeTypdef;


//Variables made public

//Functions made public
void TextToScreen(int x, int y, char *textString ,uint8_t Mode, uint32_t FColor, uint32_t BColor, Text_SizeTypdef Size);
void TextToScreen_SML(int x, int y, char *textString, uint32_t FColor, uint32_t BColor);
void TextToScreen_MED(int x, int y, char *textString, uint32_t FColor, uint32_t BColor);
void TextToScreen_LRG(int x, int y, char *textString, uint32_t FColor, uint32_t BColor);
void TextToScreen_TITLE(int x, int y, char *textString, uint32_t FColor, uint32_t BColor);




#endif /* APP_TEXT_H_ */
