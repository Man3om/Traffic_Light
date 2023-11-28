/*
 * Timers.h
 *
 *  Created on: Nov 22, 2023
 *      Author: Abdelmonem Magdi
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_types.h"


/*************************************************************************************************************************
 *                                                 Private Macros
 *************************************************************************************************************************/
#define Timer0_PRIORITY_MASK      0x1FFFFFFF
#define Timer0_PRIORITY_BITS_POS      29
#define Timer0_INTERRUPT_PRIORITY     3

#define Timer1_PRIORITY_MASK      0xFFFF1FFF
#define Timer1_PRIORITY_BITS_POS      13
#define Timer1_INTERRUPT_PRIORITY     3

/*************************************************************************************************************************
 *                                                 Functions Prototype
 *************************************************************************************************************************/
void Timer0_Init(void);
void Timer1_Init(void);
void Timers_ButtonStart(void);
void Timers_ButtonStop(void);
void Timers_TrafficStop(void);
void Timers_TrafficResume(void);
void Timers_TrafficCALLBACK(void (*a_ptrTraffic) (void));
void Timers_ButtonCALLBACK(void (*a_ptrButtons) (void));




#endif /* TIMERS_H_ */
