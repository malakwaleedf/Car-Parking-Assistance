/*
 *  File name: ultrasonic.h
 *  Description: Header file for Ultrasonic Sensor driver
 *  Created on: Oct 14, 2024
 *  Author: Malak Waleed
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

#define ULTRASONIC_TRIGGER_PORT PORTD_ID
#define ULTRASONIC_TRIGGER_PIN PIN7_ID

/*function prototypes*/
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
