/*
 *  File name: icu.c
 *  Description: Source file for ICU driver
 *  Created on: Oct 14, 2024
 *  Author: Malak Waleed
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
#include "icu.h"

/*Global variable to hold the address of the call back func*/
static volatile void (*g_callBackFuncPtr)(void) = NULL_PTR;

/*Interrupt service routine for ICU*/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackFuncPtr != NULL_PTR)
	{
		(*g_callBackFuncPtr)();
	}
}

void ICU_init(const ICU_ConfigType * config_ptr)
{
	/*Timer1 is set to normal mode*/
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);

	/*set the direction of PD6 pin to input*/
	SET_BIT(DDRD,PD6);

	/*set ICU initial triggering edge*/
	if(config_ptr ->edge == ICU_FALLING_EDGE)
	{
		CLEAR_BIT(TCCR1B,ICES1);
	}
	else if(config_ptr ->edge == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,ICES1);
	}

	/*set the clock prescaler*/
	TCCR1B = (TCCR1B & 0xF8) | ((config_ptr ->clock) & 0x03);

	/*initialize TCNT1 register to 0*/
	TCNT1 = 0;

	/*initialize ICR1 register to 0*/
	ICR1 = 0;

	/*enable ICU interrupt*/
	SET_BIT(TIMSK,TICIE1);
}

void ICU_setCallBack(void(*a_ptr)(void))
{
	/*save the address of the call back func in a priv global variable*/
	g_callBackFuncPtr = a_ptr;
}

void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	/*set ICU triggering edge as required*/
	if(a_edgeType == ICU_FALLING_EDGE)
	{
		CLEAR_BIT(TCCR1B,ICES1);
	}
	else if(a_edgeType == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,ICES1);
	}
}

uint16 ICU_getInputCaptureValue(void)
{
	/*read the ICR1 register*/
	return ICR1;
}

void ICU_clearTimerValue(void)
{
	/*clear TCNT1 register*/
	TCNT1 = 0;
}

void ICU_deInit(void)
{
	/*disable ICU*/
	/*clear all Timer1/ICU registers*/
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/*disable ICU interrupt*/
	CLEAR_BIT(TIMSK,TICIE1);

	/*reset priv global variable holding call back func address*/
	g_callBackFuncPtr = NULL_PTR;
}












