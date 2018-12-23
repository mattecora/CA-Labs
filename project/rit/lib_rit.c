#include "rit.h"

void RIT_Init(unsigned int rit_interval) {
    LPC_SC->PCONP       |=  (1<<16);            // Enable power for RIT
    
    LPC_RIT->RICOMPVAL   = rit_interval;        // Set match value		
    LPC_RIT->RICTRL      = (1<<1) | (1<<2);     // Enable clear on match and debug behavior

    LPC_RIT->RICOUNTER   = 0;                   // Set count value to 0
    
    NVIC_EnableIRQ(RIT_IRQn);
}

void RIT_Enable(void) {
    LPC_RIT->RICTRL |= (1<<3);
}

void RIT_Disable(void) {
    LPC_RIT->RICTRL &= !(0x3);
}

void RIT_Reset(void) {
    LPC_RIT->RICOUNTER = 0;
}
