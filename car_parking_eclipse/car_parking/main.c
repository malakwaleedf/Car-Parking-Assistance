/*
 * File name: main.c
 * Description: Source file for application main func
 * Created on: Oct 14, 2024
 * Author: Malak Waleed
 */

//#define F_CPU 16000000UL
#include <util/delay.h>
#include "lcd.h"
#include "buzzer.h"
#include "led.h"
#include "ultrasonic.h"
#include <avr/io.h>
#include "common_macros.h"

int main(void)
{
	SET_BIT(SREG,7);

	uint16 distance_measured = 0;
	/*devices initialization*/
	LCD_init();
	Buzzer_init();
	LEDS_init();
	Ultrasonic_init();

	LCD_displayString("Distance=");
	LCD_moveCursor(0,13);
	LCD_displayString("cm");

	while(1)
	{
		distance_measured = Ultrasonic_readDistance();

		LCD_moveCursor(0,10);
		LCD_intgerToString(distance_measured);

		if(distance_measured < 10)
		{
			LCD_moveCursor(0,11);
			LCD_displayString("  ");
		}

		if(distance_measured <= 5)
		{
			LCD_moveCursor(1,5);
			LCD_displayString("STOP");
			LED_on(g_ledRedLed);
			LED_on(g_ledGreenLed);
			LED_on(g_ledBlueLed);
			Buzzer_on();
			_delay_ms(150);
			LED_off(g_ledRedLed);
			LED_off(g_ledGreenLed);
			LED_off(g_ledBlueLed);
			Buzzer_off();
			_delay_ms(150);
		}
		else if((distance_measured > 5) && (distance_measured <= 10))
		{
			LCD_moveCursor(1,5);
			LCD_displayString("     ");
			LED_on(g_ledRedLed);
			LED_on(g_ledGreenLed);
			LED_on(g_ledBlueLed);
			Buzzer_off();
		}
		else if((distance_measured > 10) && (distance_measured <= 15))
		{
			LCD_moveCursor(1,5);
			LCD_displayString("     ");
			LED_on(g_ledRedLed);
			LED_on(g_ledGreenLed);
			LED_off(g_ledBlueLed);
			Buzzer_off();
		}
		else if((distance_measured > 10) && (distance_measured <= 20))
		{
			LCD_moveCursor(1,5);
			LCD_displayString("     ");
			LED_on(g_ledRedLed);
			LED_off(g_ledGreenLed);
			LED_off(g_ledBlueLed);
			Buzzer_off();
		}
		else if(distance_measured > 20)
		{
			LCD_moveCursor(1,5);
			LCD_displayString("     ");
			LED_off(g_ledRedLed);
			LED_off(g_ledGreenLed);
			LED_off(g_ledBlueLed);
			Buzzer_off();
		}
	}
}
