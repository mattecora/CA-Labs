#include "timer.h"

void TIMER0_IRQHandler(void)
{
    /* Toggle LED 4 */
    if (LED_Value & 0x80)
        LED_Off(7);
    else
        LED_On(7);
    
    /* Clear interrupt flags */
    LPC_TIM0->IR = 7;
}

void TIMER1_IRQHandler(void)
{   
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
