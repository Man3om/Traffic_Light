#include "tm4c123gh6pm_registers.h"
#include "Buttons.h"

/*************************************************************************************************************************
 *                                                 GLobal Variables
 *************************************************************************************************************************/
static volatile void (*g_ptra) (void) = NULL_PTR ;
static volatile void (*g_ptrb) (void) = NULL_PTR ;
/*************************************************************************************************************************/

/*
 *Description: ISR Function For GPIO PORTF IRQ
 *Input: Void
 *Return: Void
 */
void PORTF_Handler(void)
{
    /* Check Which Button is Pressed */
    if(GPIO_PORTF_RIS_REG & (1<<0))
    {
        if(g_ptrb != NULL_PTR)
        {
            g_ptrb();  /* Call Function for Button B (SW02) */

            GPIO_PORTF_ICR_REG |= (1<<0) ; /* Clear Interrupt Flag For PF0 */
        }
    }
    else if(GPIO_PORTF_RIS_REG & (1<<4))
    {
        if(g_ptra != NULL_PTR)
        {
            g_ptra();  /* Call Function for Button  (SW01) */

            GPIO_PORTF_ICR_REG |= (1<<4) ; /* Clear Interrupt Flag For PF4 */
        }
    }
}

/*
 *Description: CallBack Function To Handle Time Of LEDs Traffic
 *Input: Void
 *Return: Void
 */
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
    GPIO_PORTF_IS_REG    &= 0xEE;         /* Choosing Edge Trigger Interrupt */
    GPIO_PORTF_IBE_REG   &= 0xEE;         /* Interrupt on one Edge */
    GPIO_PORTF_IEV_REG   &= 0xEE;         /* Falling Edge */
    GPIO_PORTF_IM_REG    |= 0x11;         /* Enable Module Interrupt on PF0 , PF4 */
    NVIC_PRI7_REG = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) |           /* Setup Priority*/
            (GPIO_PORTF_INTERRUPT_PRIORITY << GPIO_PORTF_PRIORITY_BITS_POS);
    NVIC_EN0_REG |= (1<<30);              /* Enable Interrupt For GPIO PORTF */
}


/*
 *Description: Setup CallBack Function To Handle Pressed Button A
 *Input: Pointer to Function
 *Return: Void
 */
void Buttons_SetCallbackA( void (*a_ptra)(void) )
{
    g_ptra = a_ptra ;
}


/*
 *Description: Setup CallBack Function To Handle Pressed Button B
 *Input: Pointer to Function
 *Return: Void
 */
void Buttons_SetCallbackB( void (*a_ptrb)(void) )
{
    g_ptrb = a_ptrb ;
}
