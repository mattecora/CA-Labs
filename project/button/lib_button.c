#include "button.h"

void Button_Init(uint8_t keys)
{
    /* Set interrupt mode on selected keys (P2.10, P2.11, P2.12) */
    LPC_PINCON->PINSEL4 |= ((keys & BUTTON_INT0) | 
                           ((keys & BUTTON_KEY1) << 1) | 
                           ((keys & BUTTON_KEY2) << 2)) << 20;
    
    /* Set direction to input on selected keys (P2.10, P2.11, P2.12) */
    LPC_GPIO2->FIODIR &= ~(keys << 10);
    
    /* Enable the interrupt handlers */
    if (keys & BUTTON_INT0)
        NVIC_EnableIRQ(EINT0_IRQn);
    if (keys & BUTTON_KEY1)
        NVIC_EnableIRQ(EINT1_IRQn);
    if (keys & BUTTON_KEY2)
        NVIC_EnableIRQ(EINT2_IRQn);
}
