#include "button.h"

void EINT0_IRQHandler(void)
{
    /* Set the blind state */
    Blind_State = BLIND;
    
    /* Play first sample */
    DAC_Play();
    
    /* Start the play timer */
    Timer_Start(TIMER2);
    
    /* Disable active timers */
    Timer_Stop(TIMER0);
    Timer_Stop(TIMER1);
    
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 20);
    
    /* Start the RIT */
    Pressed_Button = 0;
    RIT_Enable();
    
    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 0);
}

void EINT1_IRQHandler(void)
{
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 22);
    
    /* Disable active timers */
    Timer_Stop(TIMER0);
    Timer_Stop(TIMER1);
    
    /* Start the RIT */
    Pressed_Button = 1;
    RIT_Enable();

    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 1);
}

void EINT2_IRQHandler(void)
{
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 24);
    
    /* Disable active timers */
    Timer_Stop(TIMER0);
    Timer_Stop(TIMER1);
    
    /* Start the RIT */
    Pressed_Button = 2;
    RIT_Enable();

    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 2);
}
