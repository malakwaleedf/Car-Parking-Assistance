/*
 *  File name: icu.h
 *  Description: Header file for ICU driver
 *  Created on: Oct 14, 2024
 *  Author: Malak Waleed
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/*definitions*/
#define ICU_FALLING_EDGE 0
#define ICU_RISING_EDGE 1

/*data types declaration*/
typedef enum{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU_8,
	F_CPU_64,
	F_CPU_256,
	F_CPU_1024
}ICU_ClockType;

typedef enum{
	FALLING_EDGE,
	RISING_EDGE
}ICU_EdgeType;

typedef struct{
	ICU_ClockType clock;
	ICU_EdgeType edge;
}ICU_ConfigType;

/*function prototypes*/
void ICU_init(const ICU_ConfigType * config_ptr);
void ICU_setCallBack(void(*a_ptr)(void));
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType);
uint16 ICU_getInputCaptureValue(void);
void ICU_clearTimerValue(void);
void ICU_deInit(void);


#endif /* ICU_H_ */
