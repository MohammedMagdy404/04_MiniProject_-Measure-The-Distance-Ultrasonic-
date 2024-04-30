/*/*
 ================================================================================================
 Name        : buzzer.h
 Author      : Mohamed magdy
 Description : Header file for BUZZER Driver
 Date        : 21/10/2023
 ================================================================================================
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"


#define BUZZER_PORT PORTD_ID
#define BUZZER_PIN  PIN0_ID

/**********************************************************************************************
 *                                function declarations                                       *
 **********************************************************************************************/

/*
 * Description:
 * function to initialize the buzzer pin
 */
void Buzzer_init(void);


/*
 * Description:
 * function to handle when object is so close
 * active the buzzer
 */
void Buzz(void);


#endif /* BUZZER_H_ */
