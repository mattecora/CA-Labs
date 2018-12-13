#include "button.h"

void ButtonInit(void) {
    LPC_PINCON->PINSEL4    |= (1 << 20);        // External interrupt 0 pin selection
    LPC_GPIO2->FIODIR      &= ~(1 << 10);       // PORT2.10 defined as input

    LPC_PINCON->PINSEL4    |= (1 << 22);        // External interrupt 1 pin selection
    LPC_GPIO2->FIODIR      &= ~(1 << 11);       // PORT2.11 defined as input
  
    LPC_PINCON->PINSEL4    |= (1 << 24);        // External interrupt 2 pin selection
    LPC_GPIO2->FIODIR      &= ~(1 << 12);       // PORT2.12 defined as input

    LPC_SC->EXTMODE         = 0x7;

    NVIC_EnableIRQ(EINT2_IRQn);                 // Enable IRQ for EINT2 in NVIC
    NVIC_SetPriority(EINT2_IRQn, 1);            // Set the priority for EINT2
    NVIC_EnableIRQ(EINT1_IRQn);                 // Enable IRQ for EINT1 in NVIC
    NVIC_SetPriority(EINT1_IRQn, 2);            // Set the priority for EINT1
    NVIC_EnableIRQ(EINT0_IRQn);                 // Enable IRQ for EINT0 in NVIC
    NVIC_SetPriority(EINT0_IRQn, 3);            // Set the priority for EINT0
}
