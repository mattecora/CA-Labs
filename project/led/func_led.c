#include "led.h"

void LED_On(uint8_t num)
{
    /* Set the corresponding bit to 1 */
    LPC_GPIO2->FIOPIN |= 1 << num;

    /* Update led_value */
    led_value = LPC_GPIO2->FIOPIN;
}

void LED_Off(uint8_t num)
{
    /* Set the corresponding bit to 0 */
    LPC_GPIO2->FIOPIN &= ~(1 << num);

    /* Update led_value */
    led_value = LPC_GPIO2->FIOPIN;
}

void LED_Out(uint8_t value)
{
    int i;

    /* Set the LEDs */
    for (i = 0; i < LED_NUM; i++)
    {
        if (value & (1 << i))
            LED_On(i);
        else
            LED_Off(i);
    }

    /* Update led_value */
    led_value = value;
}
