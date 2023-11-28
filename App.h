
#ifndef APP_H_
#define APP_H_

#include "std_types.h"

/*************************************************************************************************************************
 *                                               Private Macros
 *************************************************************************************************************************/
/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm(" WFI ")

/*************************************************************************************************************************
 *                                               2 Traffic LEDs Macros
 *************************************************************************************************************************/
#define Traffic_Port     PORTB

#define TrafficA_Red     PIN0
#define TrafficA_Yellow  PIN1
#define TrafficA_Green   PIN2

#define TrafficB_Red     PIN3
#define TrafficB_Yellow  PIN4
#define TrafficB_Green   PIN5

/*************************************************************************************************************************
 *                                                 Button 1 LEDs Macros
 *************************************************************************************************************************/
#define ButtonA_Port     PORTB
#define ButtonA_Red      PIN6
#define ButtonA_Green    PIN7

/*************************************************************************************************************************
 *                                                 Button 2 LEDs Macros
 *************************************************************************************************************************/
#define ButtonB_Port     PORTA
#define ButtonB_Red      PIN4
#define ButtonB_Green    PIN5

/*************************************************************************************************************************
 *                                                 Functions Prototype
 *************************************************************************************************************************/
void Run_APP(void) ;


#endif /* APP_H_ */
