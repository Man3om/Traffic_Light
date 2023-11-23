#include "Timers.h"
#include "Leds.h"
#include "Buttons.h"
#include "tm4c123gh6pm_registers.h"
#include "App.h"

typedef enum {A , B} Traffic_State ;
volatile uint8 g_flagTraffic = 0 , g_flagButton = 0 , g_countTraffic = 0 , g_countButton = 0 ;
volatile Traffic_State g_state = A ;

void Traffic_Timer(void)
{
    if((g_flagTraffic == 0) && (g_countTraffic == 5))
    {
        switch(g_state)
        {
        case A:
            LED_OFF(Traffic_Port , TrafficA_Green);
            LED_OFF(Traffic_Port , TrafficB_Red);
            break;
        case B:
            LED_OFF(Traffic_Port , TrafficB_Green);
            LED_OFF(Traffic_Port , TrafficA_Red);
            break;
        }

        LED_ON(Traffic_Port , TrafficA_Yellow);
        LED_ON(Traffic_Port , TrafficB_Yellow);

        g_flagTraffic = 1 ;
        g_countTraffic = 0 ;
    }
    else if((g_flagTraffic == 1) && (g_countTraffic == 2))
    {
        switch(g_state)
        {
        case A:
            LED_OFF(Traffic_Port , TrafficA_Yellow);
            LED_ON(Traffic_Port , TrafficA_Red) ;

            LED_OFF(ButtonA_Port , ButtonA_Red);
            LED_ON(ButtonA_Port , ButtonA_Green);
            break ;
        case B:
            LED_OFF(Traffic_Port , TrafficB_Yellow);
            LED_ON(Traffic_Port , TrafficB_Red) ;

            LED_OFF(ButtonB_Port , ButtonB_Red);
            LED_ON(ButtonB_Port , ButtonB_Green);
            break;
        }

        g_flagTraffic = 2 ;
        g_countTraffic = 0 ;
    }
    else if((g_flagTraffic == 2) && (g_countTraffic == 1))
    {
        switch(g_state)
        {
        case A:
            LED_OFF(Traffic_Port , TrafficB_Yellow);
            LED_ON(Traffic_Port , TrafficB_Green) ;

            LED_OFF(ButtonB_Port , ButtonB_Green);
            LED_ON(ButtonB_Port , ButtonB_Red);

            g_state = B ;
            break ;
        case B:
            LED_OFF(Traffic_Port , TrafficA_Yellow);
            LED_ON(Traffic_Port , TrafficA_Green) ;

            LED_OFF(ButtonA_Port , ButtonA_Green);
            LED_ON(ButtonA_Port , ButtonA_Red);

            g_state = A ;
            break;
        }

        g_flagTraffic = 0 ;
        g_countTraffic = 0 ;
    }
}

void Button_Timer(void)
{
    if(g_countButton == 2)
    {
        switch (g_flagButton) {
        case 1:
            Timers_ButtonStop() ; /* Stop Timer Buttons */

            LED_OFF(Traffic_Port, TrafficA_Red);
            LED_OFF(ButtonA_Port, ButtonA_Green);

            LED_ON(Traffic_Port, TrafficA_Green);
            LED_ON(ButtonA_Port, ButtonA_Red);

            Timers_TrafficResume();

            break;
        case 2:
            Timers_ButtonStop() ; /* Stop Timer Buttons */

            LED_OFF(Traffic_Port, TrafficB_Red);
            LED_OFF(ButtonB_Port, ButtonB_Green);

            LED_ON(Traffic_Port, TrafficA_Green);
            LED_ON(ButtonA_Port, ButtonA_Red);

            Timers_TrafficResume();

            break;
        }

        g_countButton = 0 ;
    }
}

void ButtonA(void)
{
    if(GPIO_PORTB_DATA_REG & (1<<TrafficA_Green))
    {
        Timers_TrafficStop(); /* Stop Traffic Timers */

        LED_OFF(Traffic_Port, TrafficA_Green);
        LED_OFF(ButtonA_Port, ButtonA_Red);

        LED_ON(Traffic_Port, TrafficA_Red);
        LED_ON(ButtonA_Port, ButtonA_Green);

        Timers_ButtonStart(); /* Start For 2 Seconds */

        g_flagButton = 1 ;

    }
}

void ButtonB(void)
{
    if(GPIO_PORTB_DATA_REG & (1<<TrafficB_Green))
    {
        Timers_TrafficStop(); /* Stop Traffic Timers */

        LED_OFF(Traffic_Port, TrafficB_Green);
        LED_OFF(ButtonB_Port, ButtonB_Red);

        LED_ON(Traffic_Port, TrafficB_Red);
        LED_ON(ButtonB_Port, ButtonB_Green);

        Timers_ButtonStart(); /* Start For 2 Seconds */

        g_flagButton = 2 ;
    }

}

void Run_APP(void)
{
    SYSCTL_RCGCGPIO_REG |= 0x23;  /* Enable PORTA & PORTB & PORTF Clocks */
    while((SYSCTL_PRGPIO_REG & 0x23) != 0x23); /* Waiting For Clocks */

    Buttons_SetCallbackA(ButtonA);
    Buttons_SetCallbackB(ButtonB);

    Timers_ButtonCALLBACK(Button_Timer);
    Timers_TrafficCALLBACK(Traffic_Timer);

    LEDS_PORTB_Init() ;
    LEDS_PORTA_Init() ;
    Buttons_Init();
    Timers_TrafficInit();
    Timers_ButtonInit();

    Timers_ButtonStop();

    LED_ON(Traffic_Port , TrafficA_Green) ;
    LED_ON(Traffic_Port , TrafficB_Red) ;

    LED_ON(ButtonA_Port, ButtonA_Red);
    LED_ON(ButtonB_Port, ButtonB_Green);

    g_state = A ;

    while(1)
    {

    }
}




