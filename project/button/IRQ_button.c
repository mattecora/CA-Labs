#include "button.h"

void Handle_Req(void)
{
    switch (current_state)
    {
    case STATE_RG:
        /* Reset the timer */
        Timer_Reset(0);
        Timer_Start(0);
        break;

    case STATE_RFG:
        /* Switch to the previous state */
        Run_State[STATE_RG]();
        break;

    case STATE_GR:
        /* Start the 5s timer */
        Timer_Start(1);
        break;

    case STATE_YR:
        /* Nop */
        break;
    }
}

void EINT0_IRQHandler(void)
{
    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 0);
}

void EINT1_IRQHandler(void)
{
    /* Handle pedestrian request */
    Handle_Req();

    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 1);
}

void EINT2_IRQHandler(void)
{
    /* Handle pedestrian request */
    Handle_Req();

    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 2);
}
