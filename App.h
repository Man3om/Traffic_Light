
#ifndef APP_H_
#define APP_H_

#include "std_types.h"
/*************************************************************************************************************************/
#define Traffic_Port     PORTB

#define TrafficA_Red     PIN0
#define TrafficA_Yellow  PIN1
#define TrafficA_Green   PIN2

#define TrafficB_Red     PIN3
#define TrafficB_Yellow  PIN4
#define TrafficB_Green   PIN5

/************************************************************************************************************************/
#define ButtonA_Port     PORTB
#define ButtonA_Red      PIN6
#define ButtonA_Green    PIN7

/*************************************************************************************************************************/
#define ButtonB_Port     PORTA
#define ButtonB_Red      PIN4
#define ButtonB_Green    PIN5

/*************************************************************************************************************************/
void Run_APP(void) ;


#endif /* APP_H_ */
