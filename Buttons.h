#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "std_types.h"

/*************************************************************************************************************************
 *                                                 Private Macros
 *************************************************************************************************************************/
#define GPIO_PORTF_PRIORITY_MASK      0xFF1FFFFF
#define GPIO_PORTF_PRIORITY_BITS_POS      21
#define GPIO_PORTF_INTERRUPT_PRIORITY     2

/*************************************************************************************************************************
 *                                                 Functions Prototype
 *************************************************************************************************************************/
void Buttons_Init(void);
void Buttons_SetCallbackA( void (*a_ptra)(void) );
void Buttons_SetCallbackB( void (*a_ptrb)(void) );



#endif /* BUTTONS_H_ */
