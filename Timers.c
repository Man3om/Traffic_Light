#include "tm4c123gh6pm_registers.h"
#include "Timers.h"


static volatile void (*g_ptrTraffic) (void) = NULL_PTR ;
static volatile void (*g_ptrButtons) (void) = NULL_PTR ;

void Timers_TrafficInit(void)
{

}

void Timers_ButtonInit(void)
{

}

void Timers_ButtonStart(void)
{

}

void Timers_ButtonStop(void)
{

}

void Timers_TrafficResume(void)
{


}

void Timers_TrafficStop(void)
{

}

void Timers_TrafficCALLBACK(void (*a_ptrTraffic) (void))
{
    g_ptrTraffic = a_ptrTraffic ;
}


void Timers_ButtonCALLBACK(void (*a_ptrButtons) (void))
{
    g_ptrButtons = a_ptrButtons ;
}
