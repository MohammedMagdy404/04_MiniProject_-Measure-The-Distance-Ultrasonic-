/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Mohamed Magdy
 *
 *******************************************************************************/
#include "HCSR04_ultrasonic.h"
#include "gpio.h"
#include "std_types.h"
#include "util/delay.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static ICU_ConfigType ICU_Configurations = {
		F_CPU_8,
		RAISING
};

static uint8 u_edgeCount = 0;
static uint16 u_timeHigh = 0;
static uint16 u_distance = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the Ultra-sonic driver
 * 	1. Initialize the ICU driver as required.
 * 	2. Setup the ICU call back function.
 * 	3. Setup the direction for the trigger pin as output pin through the
		GPIO driver.
 */
void Ultrasonic_init(void){
	/*
	 * 1. Initialize the ICU driver as required.
	 */
	ICU_init(&ICU_Configurations);

	/*
	 * 2. Setup the ICU call back function.
	 */
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/*
	 * 3. Setup the direction for the trigger pin as output pin through the GPIO driver.
	 */
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
}

/*
 * Description: Send the Trigger pulse to the ultra-sonic.
 */
void Ultrasonic_Trigger(void){
	GPIO_writePin(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	_delay_us(14);
	GPIO_writePin(PORTB_ID, PIN5_ID, PIN_INPUT);
}

/*
 * Description:
 * Send the trigger pulse by using Ultrasonic_Trigger function.
 * Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void){
	/*
	 * Send the trigger pulse by using Ultrasonic_Trigger function.
	 */
	Ultrasonic_Trigger();
	/*
	 * Start the measurements by the ICU from this moment.
	 */
	u_distance = (u_timeHigh * 0.017);

	return u_distance;
}

/*
 * Description:
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by
 * the ultra-sonic sensor.
 */
void Ultrasonic_edgeProcessing(void){
	u_edgeCount++;
	if(u_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(u_edgeCount == 2)
	{
		/* Store the High time value */
		u_timeHigh = ICU_getInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		ICU_clearTimerValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);
		u_edgeCount = 0;
	}
}


