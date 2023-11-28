#include "tm4c123gh6pm_registers.h"
#include "Timers.h"

/*************************************************************************************************************************
 *                                                 GLobal Variables
 *************************************************************************************************************************/
static volatile void (*g_ptrTraffic) (void) = NULL_PTR ;
static volatile void (*g_ptrButtons) (void) = NULL_PTR ;
/*************************************************************************************************************************/

/*
 *Description: ISR Function For Timer0 IRQ
 *Input: Void
 *Return: Void
 */
void Timer0_Handler(void)
{
    if(g_ptrTraffic != NULL_PTR)
    {
        g_ptrTraffic();                    /* Call Function for Buttons Timer Every 2 Seconds */
    }

    TIMER0_ICR_REG  |= (1<<0) ;            /* Timer0 timeout flag bit clears */
}

/*
 *Description: ISR Function For Timer1 IRQ
 *Input: Void
 *Return: Void
 */
void Timer1_Handler(void)
{
    if(g_ptrButtons != NULL_PTR)
    {
        g_ptrButtons();                   /* Call Function for Traffic Timer Every 1 Second */
    }

    TIMER1_ICR_REG  |= (1<<0) ;           /* Timer1 timeout flag bit clears */
}

/*
 *Description: Initialize Timer 0 For Traffic
 *Input: Void
 *Return: Void
 */
void Timer0_Init(void)
{
    TIMER0_CTL_REG   = 0 ;                 /* Disable Timer 0 */
    TIMER0_CFG_REG   = 0x00 ;              /* Select Timer 32 Bits Mode */
    TIMER0_TAMR_REG  = 0x02;               /* Select Periodic Timer For Timer0 */
    TIMER0_SYNC_REG  = 0 ;                 /* All Timers Not Affected */
    TIMER0_TAILR_REG = 15999999 ;          /* Set Initial Value For Timer0 For 1 Second */
    TIMER0_IMR_REG  |= (1<<0) ;            /* Enable Interrupt Level For Timer0 */
    TIMER0_ICR_REG  |= (1<<0) ;            /* Timer0 timeout flag bit clears */
    NVIC_EN0_REG    |= (1<<19);            /* Enable NVIC Interrupt For Timer 0 */
    NVIC_PRI4_REG    = (NVIC_PRI4_REG & Timer0_PRIORITY_MASK ) |
            (Timer0_INTERRUPT_PRIORITY << Timer0_PRIORITY_BITS_POS);  /* Setup Priority */
    TIMER0_CTL_REG  |= (1<<0) ;            /* Enable Timer0 */
}

/*
 *Description: Initialize Timer 1 For Buttons
 *Input: Void
 *Return: Void
 */
void Timer1_Init(void)
{
    TIMER1_CTL_REG   = 0 ;                /* Disable Timer 1 */
    TIMER1_CFG_REG   = 0x00 ;             /* Select Timer 32 Bits Mode */
    TIMER1_TAMR_REG  = 0x02;              /* Select Periodic Timer For Timer1 */
    TIMER1_TAILR_REG = 31999999 ;         /* Set Initial Value For Timer1 For 2 Second */
    TIMER1_IMR_REG  |= (1<<0) ;           /* Enable Interrupt Level For Timer1*/
    TIMER1_ICR_REG  |= (1<<0) ;           /* Timer1 timeout flag bit clears */
    NVIC_EN0_REG    |= (1<<21);           /* Enable NVIC Interrupt For Timer 1 */
    NVIC_PRI5_REG    = (NVIC_PRI5_REG & Timer1_PRIORITY_MASK ) |
            (Timer1_INTERRUPT_PRIORITY << Timer1_PRIORITY_BITS_POS);  /* Setup Priority */
    TIMER1_CTL_REG  |= (1<<0) ;           /* Enable Timer1 */
}

/*
 *Description: Function To Start Timer Of LEDs Button
 *Input: Void
 *Return: Void
 */
void Timers_ButtonStart(void)
{
    __asm(" CPSID I ") ;                          /* Disable Exceptions */
    TIMER1_TAILR_REG = 31999999 ;                 /* Set Initial Value For Timer1 For 2 Second */
    __asm(" CPSIE I ") ;                          /* Enable Exceptions */

    SYSCTL_RCGCTIMER_REG |= (1<<1) ;              /* Enable Timer1 Clock */
    while(!(SYSCTL_PRTIMER_REG & 0x02));          /* Waiting For Clock */
}


/*
 *Description: Function To Stop Timer Of LEDs Button
 *Input: Void
 *Return: Void
 */
void Timers_ButtonStop(void)
{
    SYSCTL_RCGCTIMER_REG &= ~(1<<1) ;              /* Disable Timer1 Clock */
}


/*
 *Description: Function To Resume Timer Of LEDs Traffic
 *Input: Void
 *Return: Void
 */
void Timers_TrafficResume(void)
{
    SYSCTL_RCGCTIMER_REG |= (1<<0) ;              /* Enable Timer0 Clock */
    while(!(SYSCTL_PRTIMER_REG & 0x01));          /* Waiting For Clock */
}


/*
 *Description: Function To Stop Timer Of LEDs Traffic
 *Input: Void
 *Return: Void
 */
void Timers_TrafficStop(void)
{
    SYSCTL_RCGCTIMER_REG &= ~(1<<0) ;              /* Disable Timer0 Clock */
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
