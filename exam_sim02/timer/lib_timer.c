#include "timer.h"

/* Array of timer structures */
LPC_TIM_TypeDef *LPC_TIM[4] = {LPC_TIM0, LPC_TIM1, LPC_TIM2, LPC_TIM3};

/* Array of IRQ identifiers */
IRQn_Type TIMER_IRQn[4] = {TIMER0_IRQn, TIMER1_IRQn, TIMER2_IRQn, TIMER3_IRQn};

void Timer_Init(uint8_t timer_num, uint8_t match_reg, uint32_t timer_interval, uint8_t timer_behavior)
{
    /* Power on TIMER2/TIMER3 */
    if (timer_num == TIMER2 || timer_num == TIMER3)
    {
        LPC_SC->PCONP |= 1 << (20 + timer_num);
    }
    
    /* Set the match register */
    (&(LPC_TIM[timer_num]->MR0))[match_reg] = timer_interval;

    /* Set the match control register */
    LPC_TIM[timer_num]->MCR = timer_behavior << 3 * match_reg;

    /* Enable the interrupt handler */
    NVIC_EnableIRQ(TIMER_IRQn[timer_num]);
}

void Timer_SetMatch(uint8_t timer_num, uint8_t match_reg, uint8_t timer_behavior)
{
    /* Clear bits in the match control register */
    LPC_TIM[timer_num]->MCR &= ~(TIMER_IRS << 3 * match_reg);
    
    /* Set bits in the match control register */
    LPC_TIM[timer_num]->MCR |= timer_behavior << 3 * match_reg;
}

void Timer_Start(uint8_t timer_num)
{
    /* Set the timer control register */
    LPC_TIM[timer_num]->TCR = 1;
}

void Timer_Stop(uint8_t timer_num)
{
    /* Set the timer control register */
    LPC_TIM[timer_num]->TCR = 0;
}

void Timer_Reset(uint8_t timer_num)
{
    /* Set the timer control register */
    LPC_TIM[timer_num]->TCR = 2;
}
