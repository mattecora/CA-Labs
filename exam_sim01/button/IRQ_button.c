#include "button.h"

int e1 = 0;
int e2 = 0;

void EINT0_IRQHandler(void)
{
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 20);
    
    /* Start the RIT */
    RIT_Debounce(BUTTON_INT0);
    
    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 0);
}

void EINT1_IRQHandler(void)
{
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 22);
    
    /* Start the RIT */
    RIT_Debounce(BUTTON_KEY1);
    
    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 1);
}

void EINT2_IRQHandler(void)
{
    /* Switch to GPIO mode */
    LPC_PINCON->PINSEL4 &= ~(1 << 24);
    
    /* Start the RIT */
    RIT_Debounce(BUTTON_KEY2);
    
    /* Clear pending interrupt */
    LPC_SC->EXTINT &= (1 << 2);
}
