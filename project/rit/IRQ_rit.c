#include "rit.h"

void RIT_IRQHandler(void)
{
    /* Toggle LED state */
    if ((led_value & 0xFF) == (CAR_RED | PED_GREEN))
    {
        /* Turn off if on */
        LED_Out(CAR_RED);
    }
    else if ((led_value & 0xFF) == CAR_RED)
    {
        /* Turn on if off */
        LED_Out(CAR_RED | PED_GREEN);
    }

    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
