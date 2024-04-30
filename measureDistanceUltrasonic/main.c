/*
 ================================================================================================
 Name        : main.c
 Author      : Mohamed magdy
 Description : Measure distance from ultrasonic
 Date        : 21/10/2023
 ================================================================================================
 */

#include "std_types.h"
#include "lcd.h"
#include "HCSR04_ultrasonic.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "buzzer.h"

/*
 * Description: function to handle when object is so close
 * active the buzzer
 * And monitor on the LCD Screen
 */
void soClose(void){
	LCD_moveCursor(1, 4);
	LCD_displayString("Warning");
	LCD_moveCursor(2, 2);
	LCD_displayString("Object is so");
	LCD_moveCursor(3, 4);
	LCD_displayString("Close !");

	Buzz();
}
void notSoClose(void){
	LCD_moveCursor(1, 4);
	LCD_displayString("       ");
	LCD_moveCursor(2, 2);
	LCD_displayString("            ");
	LCD_moveCursor(3, 4);
	LCD_displayString("       ");
}


/*
 * Description: main function to handle work flow of
 * receiving the distance from ultra-sonic module
 * monitor this distance on the LCD Screen
 */

int main(void){
	uint16 distance = 0;

	Ultrasonic_init();
	LCD_init();
	Buzzer_init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);


	while(1){
		/*
		 * read the distance
		 */
		distance = Ultrasonic_readDistance();

		LCD_moveCursor(0, 0);
		LCD_displayString("Distance= ");
		LCD_intgerToString(distance);
		LCD_displayString("cm");

		if(distance == 0){
			/*will do nothing cause distance is Zero or he crashed*/
		}
		else if(distance <= 15){
			soClose();
		}else{
			notSoClose();
		}

	}
}







