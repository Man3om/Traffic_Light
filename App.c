#include "Timers.h"
#include "Leds.h"
#include "Buttons.h"
#include "tm4c123gh6pm_registers.h"
#include "App.h"

/*************************************************************************************************************************
 *                                                 GLobal Variables
 *************************************************************************************************************************/
typedef enum {A , B} Traffic_State ; /* Enumeration For Traffic States (Traffic A or traffic B) */
volatile uint8 g_flagTraffic = 0 , g_flagButton = 0 , g_countTraffic = 0 ;
volatile Traffic_State g_state = A ;
/*************************************************************************************************************************/

/*
 *Description: CallBack Function To Handle Time Of LEDs Traffic
 *Input: Void
 *Return: Void
 */
void Traffic_Timer(void)
{
    g_countTraffic++;                                 /* Increase Seconds Every ISR */

    /* Checking Flag & Seconds */
    if((g_flagTraffic == 0) && (g_countTraffic == 5)) /* After 5 Seconds */
    {
        switch(g_state)                               /* Choose Between 2 States */
        {
        case A:
            LED_OFF(Traffic_Port , TrafficA_Green);   /* Turn off Green Led For Traffic A */
            LED_OFF(Traffic_Port , TrafficB_Red);     /* Turn off Red Led For Traffic B */
            break;
        case B:
            LED_OFF(Traffic_Port , TrafficB_Green);   /* Turn off Green Led For Traffic B */
            LED_OFF(Traffic_Port , TrafficA_Red);     /* Turn off Red Led For Traffic A */
            break;
        }

        LED_ON(Traffic_Port , TrafficA_Yellow);       /* Turn on Yellow Led For Traffic A */
        LED_ON(Traffic_Port , TrafficB_Yellow);       /* Turn on Yellow Led For Traffic B */

        g_flagTraffic = 1 ;                           /* Change Flag Value for Next Period */
        g_countTraffic = 0 ;                          /* Reset Counter For Next Period of Seconds */
    }
    else if((g_flagTraffic == 1) && (g_countTraffic == 2)) /* After 2 Seconds */
    {
        switch(g_state)
        {
        case A:
            LED_OFF(Traffic_Port , TrafficA_Yellow); /* Turn off Yellow Led For Traffic A */
            LED_ON(Traffic_Port , TrafficA_Red) ;    /* Turn on Red Led For Traffic A */

            LED_OFF(ButtonA_Port , ButtonA_Red);     /* Turn off Red Led For Button A */
            LED_ON(ButtonA_Port , ButtonA_Green);    /* Turn on Green Led For Button A */
            break ;
        case B:
            LED_OFF(Traffic_Port , TrafficB_Yellow); /* Turn off Yellow Led For Traffic B */
            LED_ON(Traffic_Port , TrafficB_Red) ;    /* Turn on Red Led For Traffic B */

            LED_OFF(ButtonB_Port , ButtonB_Red);     /* Turn off Red Led For Button B */
            LED_ON(ButtonB_Port , ButtonB_Green);    /* Turn on Green Led For Button B */
            break;
        }

        g_flagTraffic = 2 ;                          /* Change Flag Value for Next Period */
        g_countTraffic = 0 ;                         /* Reset Counter For Next Period of Seconds */
    }
    else if((g_flagTraffic == 2) && (g_countTraffic == 1)) /* After 1 Second */
    {
        switch(g_state)
        {
        case A:
            LED_OFF(Traffic_Port , TrafficB_Yellow); /* Turn off Yellow Led For Traffic B */
            LED_ON(Traffic_Port , TrafficB_Green) ;  /* Turn on Green Led For Traffic B */

            LED_OFF(ButtonB_Port , ButtonB_Green);   /* Turn off Green Led For Button B */
            LED_ON(ButtonB_Port , ButtonB_Red);      /* Turn on Red Led For Button B */

            g_state = B ;                            /* Change State For Sate Traffic B */
            break ;
        case B:
            LED_OFF(Traffic_Port , TrafficA_Yellow); /* Turn off Yellow Led For Traffic A */
            LED_ON(Traffic_Port , TrafficA_Green) ;  /* Turn on Green Led For Traffic A */

            LED_OFF(ButtonA_Port , ButtonA_Green);   /* Turn off Green Led For Button A */
            LED_ON(ButtonA_Port , ButtonA_Red);      /* Turn on Red Led For Button A */

            g_state = A ;                            /* Change State For Sate Traffic A */
            break;
        }

        g_flagTraffic = 0 ;                          /* Change Flag Value for Next Period */
        g_countTraffic = 0 ;                         /* Reset Counter For Next Period of Seconds */
    }
}


/*
 *Description: CallBack Function To Handle Time Of LEDs Buttons
 *Input: Void
 *Return: Void
 */
void Button_Timer(void)
{
    switch (g_flagButton)                      /* Choose Between 2 Buttons */
    {
    case 1:
        Timers_ButtonStop() ;                  /* Stop Timer Buttons */

        LED_OFF(Traffic_Port, TrafficA_Red);   /* Turn off Red Led For Traffic A */
        LED_OFF(ButtonA_Port, ButtonA_Green);  /* Turn off Green Led For Button A */

        LED_ON(Traffic_Port, TrafficA_Green);  /* Turn on Green Led For Traffic A */
        LED_ON(ButtonA_Port, ButtonA_Red);     /* Turn on Red Led For Button A */

        Timers_TrafficResume();                /* Resume Traffic Timer */

        break;
    case 2:
        Timers_ButtonStop() ;                  /* Stop Timer Buttons */

        LED_OFF(Traffic_Port, TrafficB_Red);   /* Turn off Red Led For Traffic B */
        LED_OFF(ButtonB_Port, ButtonB_Green);  /* Turn off Green Led For Button B */

        LED_ON(Traffic_Port, TrafficB_Green);  /* Turn on Green Led For Traffic B */
        LED_ON(ButtonA_Port, ButtonB_Red);     /* Turn on Red Led For Button B */

        Timers_TrafficResume();                /* Resume Traffic Timer */

        break;
    }
}


/*
 *Description: CallBack Function To Handle Pressed Button A
 *Input: Void
 *Return: Void
 */
void ButtonA(void)
{
    /* Checking Green Led in Traffic A On Or Off */
    if(GPIO_PORTB_DATA_REG & (1<<TrafficA_Green))
    {
        Timers_TrafficStop();                   /* Stop Traffic Timers */

        LED_OFF(Traffic_Port, TrafficA_Green);  /* Turn off Green Led For Traffic A */
        LED_OFF(ButtonA_Port, ButtonA_Red);     /* Turn off Red Led For Button A */

        LED_ON(Traffic_Port, TrafficA_Red);     /* Turn on Red Led For Traffic A */
        LED_ON(ButtonA_Port, ButtonA_Green);    /* Turn on Green Led For Traffic A */

        Timers_ButtonStart();                   /* Start For 2 Seconds */

        g_flagButton = 1 ;                      /* Change Button Flag To handle which Button is Pressed */
    }
}


/*
 *Description: CallBack Function To Handle Pressed Button B
 *Input: Void
 *Return: Void
 */
void ButtonB(void)
{
    /* Checking Green Led in Traffic B On Or Off */
    if(GPIO_PORTB_DATA_REG & (1<<TrafficB_Green))
    {
        Timers_TrafficStop();                   /* Stop Traffic Timers */

        LED_OFF(Traffic_Port, TrafficB_Green);  /* Turn off Green Led For Traffic B */
        LED_OFF(ButtonB_Port, ButtonB_Red);     /* Turn off Red Led For Button B */

        LED_ON(Traffic_Port, TrafficB_Red);     /* Turn on Red Led For Traffic B */
        LED_ON(ButtonB_Port, ButtonB_Green);    /* Turn on Green Led For Button B */

        Timers_ButtonStart();                   /* Start For 2 Seconds */

        g_flagButton = 2 ;                      /* Change Button Flag To handle which Button is Pressed */
    }
}


/*
 *Description: Main Application Code
 *Input: Void
 *Return: Void
 */
void Run_APP(void)
{
    SYSCTL_RCGCGPIO_REG |= 0x23;                /* Enable PORTA & PORTB & PORTF Clocks */
    while((SYSCTL_PRGPIO_REG & 0x23) != 0x23);  /* Waiting For Clocks */

    SYSCTL_RCGCTIMER_REG |= 0x03 ;              /* Enable Timer0 & Timer1 Clock */
    while((SYSCTL_PRTIMER_REG & 0x03) != 0x03); /* Waiting For Clocks */

    Buttons_SetCallbackA(ButtonA);              /* Setup CallBack Function For Button A */
    Buttons_SetCallbackB(ButtonB);              /* Setup CallBack Function For Button B */

    Timers_ButtonCALLBACK(Button_Timer);        /* Setup CallBack Function For Button Timer */
    Timers_TrafficCALLBACK(Traffic_Timer);      /* Setup CallBack Function For Traffic Timer */

    /* Initialize All Modules */
    LEDS_PORTB_Init() ;
    LEDS_PORTA_Init() ;
    Buttons_Init();
    Timer0_Init();
    Timer1_Init();

    Timers_ButtonStop();                        /* Stop Button Timer */

    LED_ON(Traffic_Port , TrafficA_Green) ;     /* Turn on Green Led For Traffic A */
    LED_ON(Traffic_Port , TrafficB_Red) ;       /* Turn on Red Led For Traffic B */

    LED_ON(ButtonA_Port, ButtonA_Red);          /* Turn on Red Led For Button A */
    LED_ON(ButtonB_Port, ButtonB_Green);        /* Turn on Green Led For Button B */

    g_state = A ;                               /* Setup First State For Traffic */

    Enable_Exceptions();                        /* Enable Exceptions */
    Enable_Faults();                            /* Enable Faults */

    while(1)
    {
        Wait_For_Interrupt();                  /* Sleep Mode */
    }
}

