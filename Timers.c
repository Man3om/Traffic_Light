#include "tm4c123gh6pm_registers.h"
#include "Timers.h"

/*************************************************************************************************************************
 *                                                 GLobal Variables
 *************************************************************************************************************************/
static volatile void (*g_ptrTraffic) (void) = NULL_PTR ;
static volatile void (*g_ptrButtons) (void) = NULL_PTR ;
/*************************************************************************************************************************/

/*
 *Description: ISR Function For Timer0B IRQ
 *Input: Void
 *Return: Void
 */
void Timer0B_Handler(void)
{
    if(g_ptrButtons != NULL_PTR)
    {
        g_ptrButtons();  /* Call Function for Buttons Timer */
    }
}

/*
 *Description: ISR Function For Timer0A IRQ
 *Input: Void
 *Return: Void
 */
void Timer0A_Handler(void)
{
    if(g_ptrTraffic != NULL_PTR)
    {
        g_ptrTraffic();  /* Call Function for Traffic Timer */
    }
}

/*
 *Description: Initialize Timer 0 For Traffics
 *Input: Void
 *Return: Void
 */
void Timers_TrafficInit(void)
{

}

/*
 *Description: Initialize Timer 1 For Buttons
 *Input: Void
 *Return: Void
 */
void Timers_ButtonInit(void)
{

}


/*
 *Description: Function To Start Timer Of LEDs Button
 *Input: Void
 *Return: Void
 */
void Timers_ButtonStart(void)
{

}


/*
 *Description: Function To Stop Timer Of LEDs Button
 *Input: Void
 *Return: Void
 */
void Timers_ButtonStop(void)
{

}


/*
 *Description: Function To Resume Timer Of LEDs Traffic
 *Input: Void
 *Return: Void
 */
void Timers_TrafficResume(void)
{


}


/*
 *Description: Function To Stop Timer Of LEDs Traffic
 *Input: Void
 *Return: Void
 */
void Timers_TrafficStop(void)
{

}

/*
 *Description: Setup CallBack Function To Handle Time Of LEDs Traffic
 *Input: Pointer to Function
 *Return: Void
 */
void Timers_TrafficCALLBACK(void (*a_ptrTraffic) (void))
{
    g_ptrTraffic = a_ptrTraffic ;
}


/*
 *Description: Setup CallBack Function To Handle Time Of LEDs Button
 *Input: Pointer to Function
 *Return: Void
 */
void Timers_ButtonCALLBACK(void (*a_ptrButtons) (void))
{
    g_ptrButtons = a_ptrButtons ;
}
