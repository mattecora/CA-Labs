#include "button.h"

void Handle_Req(void)
{
    switch (Current_State)
    {
    case STATE_RG:
        /* Reset the main timer */
        Timer_Reset(TIMER0);
        Timer_Start(TIMER0);
        break;

    case STATE_RFG:
        /* Switch to the previous state */
        Run_State[STATE_RG]();
        break;

    case STATE_GR:
        /* Start the main timer */
        Timer_Start(TIMER0);
        break;

    case STATE_YR:
        /* Nop */
        break;
    }
}

void EINT0_IRQHandler(void)
{
    /* Set the blind state */
    Blind_State = BLIND;
    
    /* Play first sample */
    DAC_Play();
    
    /* Start the play timer */
    Timer_Start(TIMER2);
    
    /* Handle pedestrian request */
    Handle_Req();
    
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 20);
    
    /* Stop until the button is pressed */
    while (!(LPC_GPIO2->FIOPIN & (1 << 10)));
    
    /* Switch back to interrupt mode */
    LPC_PINCON->PINSEL4 |= 1 << 20;
    
    /* Reset the play timer */
    Timer_Reset(TIMER2);
    
    /* Reset the DAC output */
    DAC_Out(0);
    
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
