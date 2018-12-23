#include "button.h"

void Button_Init(unsigned char keys) {
    if (keys & BUTTON_INT0) {
        LPC_PINCON->PINSEL4    |= (1 << 20);        // External interrupt 0 pin selection
        LPC_GPIO2->FIODIR      &= ~(1 << 10);       // PORT2.10 defined as input
        
        NVIC_EnableIRQ(EINT2_IRQn);                 // Enable IRQ for EINT2 in NVIC
        NVIC_SetPriority(EINT2_IRQn, 1);            // Set the priority for EINT2
    }
    
    if (keys & BUTTON_KEY1) {
        LPC_PINCON->PINSEL4    |= (1 << 22);        // External interrupt 1 pin selection
        LPC_GPIO2->FIODIR      &= ~(1 << 11);       // PORT2.11 defined as input
        
        NVIC_EnableIRQ(EINT1_IRQn);                 // Enable IRQ for EINT1 in NVIC
        NVIC_SetPriority(EINT1_IRQn, 2);            // Set the priority for EINT1
    }
    
    if (keys & BUTTON_KEY2) {
        LPC_PINCON->PINSEL4    |= (1 << 24);        // External interrupt 2 pin selection
        LPC_GPIO2->FIODIR      &= ~(1 << 12);       // PORT2.12 defined as input
        
        NVIC_EnableIRQ(EINT0_IRQn);                 // Enable IRQ for EINT0 in NVIC
        NVIC_SetPriority(EINT0_IRQn, 3);            // Set the priority for EINT0
    }
    
    LPC_SC->EXTMODE = 0x7;    
}
