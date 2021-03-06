#include "led.h"

uint8_t LED_Value;

void LED_Init(uint8_t initial_value)
{
    /* Set GPIO mode on P2.0 to P2.7 */
    LPC_PINCON->PINSEL4 &= 0xFFFF0000;

    /* Set direction to output on P2.0 to P2.7 */
    LPC_GPIO2->FIODIR |= 0x000000FF;

    /* Set the LEDs initial value */
    LPC_GPIO2->FIOSET = initial_value;
    LED_Value = initial_value;
}
