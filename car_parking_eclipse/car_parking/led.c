/*
 *  File name: led.c
 *  Description: Source file for 3-LED driver
 *  Created on: Oct 5, 2024
 *  Author: Malak Waleed
 */

#include "led.h"
#include "gpio.h"
#include "common_macros.h"

LED_ID g_ledRedLed = LED_RED_ID;
LED_ID g_ledGreenLed = LED_GREEN_ID;
LED_ID g_ledBlueLed = LED_BLUE_ID;

void LEDS_init(void)
{
	/*Set the direction of all 3 LEDs to output*/
	GPIO_setupPinDirection(LED_RED_PORT, LED_RED_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_GREEN_PORT, LED_GREEN_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_BLUE_PORT, LED_BLUE_PIN, PIN_OUTPUT);

	/*Turn off all 3 LEDs*/
	/*for positive logic*/
#if(LED_CONNECTION_LOGIC == 0)
	GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_LOW);
	GPIO_writePin(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_LOW);
	GPIO_writePin(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_LOW);

	/*for negative logic*/
#elif(LED_CONNECTION_LOGIC == 1)
	GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_HIGH);
	GPIO_writePin(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_HIGH);
	GPIO_writePin(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_HIGH);
#endif

}

void LED_on(LED_ID id)
{
	/*Turn on 1 LED*/
	/*for positive logic*/
#if(LED_CONNECTION_LOGIC == 0)
	switch(id)
	{
	case LED_RED_ID:
		GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_HIGH);
		break;
	case LED_GREEN_ID:
		GPIO_writePin(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_HIGH);
		break;
	case LED_BLUE_ID:
		GPIO_writePin(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_HIGH);
		break;
	}

	/*for negative logic*/
#elif(LED_CONNECTION_LOGIC == 1)
	switch(id)
	{
	case LED_RED_ID:
		GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_LOW);
		break;
	case LED_GREEN_ID:
		GPIO_writePin(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_LOW);
		break;
	case LED_BLUE_ID:
		GPIO_writePin(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_LOW);
		break;
	}
#endif

}

void LED_off(LED_ID id)
{
	/*Turn off 1 LED*/
	/*for positive logic*/
#if(LED_CONNECTION_LOGIC == 0)
	switch(id)
	{
	case LED_RED_ID:
		GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_LOW);
		break;
	case LED_GREEN_ID:
		GPIO_writePin(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_LOW);
		break;
	case LED_BLUE_ID:
		GPIO_writePin(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_LOW);
		break;
	}

	/*for negative logic*/
#elif(LED_CONNECTION_LOGIC == 1)
	switch(id)
	{
	case LED_RED_ID:
		GPIO_writePin(LED_RED_PORT, LED_RED_PIN, LOGIC_HIGH);
		break;
	case LED_GREEN_ID:
		GPIO_writePin(LED_GREEN_PORT, LED_GREEN_PIN, LOGIC_HIGH);
		break;
	case LED_BLUE_ID:
		GPIO_writePin(LED_BLUE_PORT, LED_BLUE_PIN, LOGIC_HIGH);
		break;
	}

#endif
}











