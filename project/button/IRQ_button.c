#include "button.h"

void HandlePedReq(void) {
    switch (current_state) {
        case STATE_RG:
            // Reset the timer
            Timer_Reset(0);
            Timer_Start(0);
            break;
        
        case STATE_RFG:
            // Switch to the previous state
            Run_State[STATE_RG]();
            break;
        
        case STATE_GR:
            // Set a 5s timer
            Timer_Init(0, TIME_5SEC, IRS_ON_MATCH);
            Timer_Start(0);
            break;
        
        case STATE_YR:
            // Nop
            break;
    }
}

void EINT0_IRQHandler(void) {
    LPC_SC->EXTINT &= (1 << 0);     // Clear pending interrupt
}

void EINT1_IRQHandler(void) {
    HandlePedReq();
    LPC_SC->EXTINT &= (1 << 1);     // Clear pending interrupt
}

void EINT2_IRQHandler(void) {
    HandlePedReq();
    LPC_SC->EXTINT &= (1 << 2);     // Clear pending interrupt
}
