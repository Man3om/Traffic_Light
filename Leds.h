/*
 * Leds.h
 *
 *  Created on: Nov 22, 2023
 *      Author: Abdelmonem Magdi
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "std_types.h"

/*************************************************************************************************************************
 *                                                Ports & Pins Macros
 *************************************************************************************************************************/
#define PORTA    1
#define PORTB    2

#define PIN0     0
#define PIN1     1
#define PIN2     2
#define PIN3     3
#define PIN4     4
#define PIN5     5
#define PIN6     6
#define PIN7     7

/*************************************************************************************************************************
 *                                                 Functions Prototype
 *************************************************************************************************************************/void LEDS_PORTB_Init(void);
void LEDS_PORTA_Init(void);
void LED_ON(uint8 Led_Port , uint8 Led_Pin);
void LED_OFF(uint8 Led_Port , uint8 Led_Pin);



#endif /* LEDS_H_ */
