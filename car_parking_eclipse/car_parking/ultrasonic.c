/*
 *  File name: ultrasonic.c
 *  Description: Source file for Ultrasonic Sensor driver
 *  Created on: Oct 14, 2024
 *  Author: Malak Waleed
 */

//#define F_CPU 16000000UL
#include <util/delay.h>
#include "common_macros.h"
#include "gpio.h"
#include "icu.h"
#include "ultrasonic.h"
#include <avr/io.h>

/*Global variavles*/
uint8 g_ultrasonic_EdgesNUMBER = 0;
uint8 g_ultrasonic_ReadDistance = 0;
uint16 g_ultrasonic_HighTime = 0;

void Ultrasonic_edgeProcessing(void)
{
	if(g_ultrasonic_EdgesNUMBER == 0)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING_EDGE);
		g_ultrasonic_EdgesNUMBER++;
	}
	else if(g_ultrasonic_EdgesNUMBER == 1)
	{
		g_ultrasonic_HighTime = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RISING_EDGE);
		g_ultrasonic_ReadDistance = 1;
		g_ultrasonic_EdgesNUMBER = 0;
	}

}

void Ultrasonic_init(void)
{
	/*initialize ICU*/
	ICU_ConfigType g_ultrasonic_ICU_InitConfig = {F_CPU_8, RISING_EDGE};
	ICU_init(&g_ultrasonic_ICU_InitConfig);

	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/*set the direction of trigger pin to output*/
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, PIN_OUTPUT);

	/*initialize trigger pin to logic low */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_LOW);
}

void Ultrasonic_Trigger(void)
{
	/*send a pulse on the trigger pin*/
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_LOW);

}

uint16 Ultrasonic_readDistance(void)
{
	uint16 distance = 0;

	Ultrasonic_Trigger();

	while(g_ultrasonic_ReadDistance != 1){

	}

	if(g_ultrasonic_ReadDistance == 1)
	{
		distance = (g_ultrasonic_HighTime / 117.6 )+1;
		g_ultrasonic_ReadDistance = 0;
	}
	if(distance>66)
	{
		distance=distance+1;
		if(distance>140)
		{
			distance=distance+1;
			if(distance>213)
			{
				distance=distance+1;
			}
		}
	}


	return distance;
}








