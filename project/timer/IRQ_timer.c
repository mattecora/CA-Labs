#include "timer.h"

void TIMER0_IRQHandler(void) {
    // Switch to the next state
    Run_State[(current_state + 1) % (STATE_YR + 1)]();
    
    // Clear interrupt flag
    LPC_TIM0->IR = 1;
}

void TIMER1_IRQHandler(void) {
    LPC_TIM1->IR = 1;       // Clear interrupt flag
}
