#include "timer.h"

void TIMER0_IRQHandler(void)
{
    /* Switch to the next state */
    Run_State[(current_state + 1) % (STATE_YR + 1)]();

    /* Clear interrupt flags */
    LPC_TIM0->IR = 7;
}

void TIMER1_IRQHandler(void)
{
    /* Toggle LED state */
    if (led_value == (CAR_RED | PED_GREEN))
    {
        /* Turn off if on */
        LED_Out(CAR_RED);
    }
    else if (led_value == CAR_RED)
    {
        /* Turn on if off */
        LED_Out(CAR_RED | PED_GREEN);
    }

    /* Clear interrupt flags */
    LPC_TIM1->IR = 7;
}

void TIMER2_IRQHandler(void)
{
    /* Clear interrupt flags */
    LPC_TIM2->IR = 7;
}

void TIMER3_IRQHandler(void)
{
    /* Clear interrupt flags */
    LPC_TIM3->IR = 7;
}
