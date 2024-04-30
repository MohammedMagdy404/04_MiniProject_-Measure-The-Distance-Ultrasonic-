/*
 ================================================================================================
 Name        : buzzer.c
 Author      : Mohamed magdy
 Description : Source file for BUZZER Driver
 Date        : 21/10/2023
 ================================================================================================
 */

#include "buzzer.h"
#include "gpio.h"
#include "util/delay.h"


/*
 * Description:
 * function to initialize the buzzer pin
 */
void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
/*
 * Description:
 * function to buzz the buzzer once
 */
void Buzz(void){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
	_delay_ms(200);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

