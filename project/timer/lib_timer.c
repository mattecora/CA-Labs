#include "timer.h"

void Timer_Init(unsigned char timer_num, unsigned int timer_interval, unsigned char timer_behavior) {
    if (timer_num == 0) {
        LPC_TIM0->MR0 = timer_interval;
        LPC_TIM0->MCR = timer_behavior;

        NVIC_EnableIRQ(TIMER0_IRQn);
    } else {
        LPC_TIM1->MR0 = timer_interval;
        LPC_TIM1->MCR = timer_behavior;

        NVIC_EnableIRQ(TIMER1_IRQn);
    }
}

void Timer_Start(unsigned char timer_num) {
    if (timer_num == 0) {
        LPC_TIM0->TCR = 1;
    } else {
        LPC_TIM1->TCR = 1;
    }
}

void Timer_Stop(unsigned char timer_num) {
    if (timer_num == 0) {
        LPC_TIM0->TCR = 0;
    } else {
        LPC_TIM1->TCR = 0;
    }
}

void Timer_Reset(unsigned char timer_num) {
    if (timer_num == 0) {
        LPC_TIM0->TCR |= 0x02;
    } else {
        LPC_TIM1->TCR |= 0x02;
    }
}
