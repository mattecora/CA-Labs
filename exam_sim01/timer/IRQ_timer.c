#include "timer.h"

void TIMER0_IRQHandler(void)
{
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
    int div_res;
    
    /* Call divisible */
    div_res = divisible(e1, e2);
    
    /* Output LEDs */
    LED_Out(
        (e1 & 0xF) << 4 |   /* e1 on low-index LEDs */
        (div_res & 0xF)     /* e2 on high-index LEDs */
    );
    
    /* Reset counting */
    e1 = 0;
    e2 = 0;
    
    /* Clear interrupt flags */
    LPC_TIM2->IR = 7;
}

void TIMER3_IRQHandler(void)
{
    /* Clear interrupt flags */
    LPC_TIM3->IR = 7;
}
