#include "timer.h"

/* Array of timer structures */
LPC_TIM_TypeDef *LPC_TIM[4] = {LPC_TIM0, LPC_TIM1, LPC_TIM2, LPC_TIM3};

/* Array of IRQ identifiers */
IRQn_Type TIMER_IRQn[4] = {TIMER0_IRQn, TIMER1_IRQn, TIMER2_IRQn, TIMER3_IRQn};

void Timer_Init(unsigned char timer_num, unsigned char match_reg, unsigned int timer_interval, unsigned char timer_behavior)
{
    /* Set the match register */
    (&(LPC_TIM[timer_num]->MR0))[match_reg] = timer_interval;

    /* Set the match control register */
    LPC_TIM[timer_num]->MCR |= timer_behavior << 3 * match_reg;

    /* Enable the interrupt handler */
    NVIC_EnableIRQ(TIMER_IRQn[timer_num]);
}

void Timer_Start(unsigned char timer_num)
{
    /* Set the timer control register */
    LPC_TIM[timer_num]->TCR = 1;
}

void Timer_Stop(unsigned char timer_num)
{
    /* Set the timer control register */
    LPC_TIM[timer_num]->TCR = 0;
}

void Timer_Reset(unsigned char timer_num)
{
    /* Set the timer control register */
    LPC_TIM[timer_num]->TCR = 2;
}
