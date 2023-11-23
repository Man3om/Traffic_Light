#include "tm4c123gh6pm_registers.h"
#include "Buttons.h"

static volatile void (*g_ptra) (void) = NULL_PTR ;
static volatile void (*g_ptrb) (void) = NULL_PTR ;


void Buttons_Init(void)
{
    GPIO_PORTF_LOCK_REG   = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG    |= 0x11;         /* Enable changes on PF0 */
    GPIO_PORTF_AMSEL_REG &= 0xEE;         /* Disable Analog on PF0 , PF4 */
    GPIO_PORTF_PCTL_REG  &= 0xFFF0FFF0;   /* Clear PMCx bits for PF0 , PF4 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   &= 0xEE;         /* Configure PF0 , PF4 as input pin */
    GPIO_PORTF_AFSEL_REG &= 0xEE;         /* Disable alternative function on PF0 , PF4 */
    GPIO_PORTF_PUR_REG   |= 0x11;         /* Enable pull-up on PF0 , PF4 */
    GPIO_PORTF_DEN_REG   |= 0x11;         /* Enable Digital I/O on PF0 , PF4 */
}

void Buttons_SetCallbackA( void (*a_ptra)(void) )
{
    g_ptra = a_ptra ;
}

void Buttons_SetCallbackB( void (*a_ptrb)(void) )
{
    g_ptrb = a_ptrb ;
}



