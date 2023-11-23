#include "tm4c123gh6pm_registers.h"
#include "Leds.h"

void LEDS_PORTB_Init(void)
{
    GPIO_PORTB_AMSEL_REG = 0x00;          /* Disable Analog on PB0 ~ PB7 */
    GPIO_PORTB_PCTL_REG  = 0x00;          /* Clear PMCx bits for PB0 ~ PB7 to use it as GPIO pin */
    GPIO_PORTB_DIR_REG   = 0xFF;          /* Configure PB0 ~ PB7 as output pin */
    GPIO_PORTB_AFSEL_REG = 0x00;          /* Disable alternative function on PB0 ~ PB7 */
    GPIO_PORTB_DEN_REG   = 0xFF;          /* Enable Digital I/O on PB0 ~ PB7 */
    GPIO_PORTB_DATA_REG  = 0x00;          /* Clear bit PB0 ~ PB7 in Data register to turn off the leds */
}


void LEDS_PORTA_Init(void)
{
    GPIO_PORTA_AMSEL_REG &= 0xCF;          /* Disable Analog on PA4 , PA5*/
    GPIO_PORTA_PCTL_REG  &= 0xFF00FFFF;    /* Clear PMCx bits for PA4 , PA5 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG   |= 0x30;          /* Configure PA4 , PA5 as output pin */
    GPIO_PORTA_AFSEL_REG &= 0xCF;          /* Disable alternative function on PA4 , PA5 */
    GPIO_PORTA_DEN_REG   |= 0x30;          /* Enable Digital I/O on PA4 , PA5 */
    GPIO_PORTA_DATA_REG  &= 0xCF;          /* Clear bit PA4 , PA5 in Data register to turn off the leds */
}

void LED_ON(uint8 Led_Port , uint8 Led_Pin)
{
    switch(Led_Port)
    {
    case PORTA:
        GPIO_PORTA_DATA_REG |= (1<<Led_Pin) ;
        break ;

    case PORTB:
        GPIO_PORTB_DATA_REG |= (1<<Led_Pin);
        break;
    }
}

void LED_OFF(uint8 Led_Port , uint8 Led_Pin)
{
    switch(Led_Port)
    {
    case PORTA:
        GPIO_PORTA_DATA_REG &= ~(1<<Led_Pin) ;
        break ;

    case PORTB:
        GPIO_PORTB_DATA_REG &= ~(1<<Led_Pin);
        break;
    }
}

