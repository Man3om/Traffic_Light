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
 *                                                 Functions Prototype
 *************************************************************************************************************************/
void Timers_TrafficInit(void);
void Timers_ButtonInit(void);
void Timers_ButtonStart(void);
void Timers_ButtonStop(void);
void Timers_TrafficStop(void);
void Timers_TrafficResume(void);
void Timers_TrafficCALLBACK(void (*a_ptrTraffic) (void));
void Timers_ButtonCALLBACK(void (*a_ptrButtons) (void));




#endif /* TIMERS_H_ */
