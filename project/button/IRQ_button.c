#include "button.h"

void EINT0_IRQHandler(void)
{
    /* Set the blind state */
    Blind_State = BLIND;
    
    /* Disable the main timer */
    Timer_Stop(TIMER0);
    
    /* Disable the maintenance timer */
    Timer_Stop(TIMER3);
    
    /* Play first sample */
    DAC_Play();
    
    /* Start the play timer */
    Timer_Start(TIMER2);
    
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 20);
    
    /* Start the RIT */
    RIT_Debounce(BUTTON_INT0);
    
    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 0);
}

void EINT1_IRQHandler(void)
{   
    /* Disable the main timer */
    Timer_Stop(TIMER0);
    
    /* Disable the maintenance timer */
    Timer_Stop(TIMER3);
    
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 22);
    
    /* Start the RIT */
    RIT_Debounce(BUTTON_KEY1);

    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 1);
}

void EINT2_IRQHandler(void)
{
    /* Disable the main timer */
    Timer_Stop(TIMER0);
    
    /* Disable the maintenance timer */
    Timer_Stop(TIMER3);
    
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 24);
    
    /* Start the RIT */
    RIT_Debounce(BUTTON_KEY2);

    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 2);
}
