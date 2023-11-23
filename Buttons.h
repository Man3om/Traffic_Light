#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "std_types.h"


/*************************************************************************************************************************
 *                                                 Functions Prototype
 *************************************************************************************************************************/
void Buttons_Init(void);
void Buttons_SetCallbackA( void (*a_ptra)(void) );
void Buttons_SetCallbackB( void (*a_ptrb)(void) );



#endif /* BUTTONS_H_ */
