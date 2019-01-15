#include "rit.h"

void RIT_IRQHandler(void)
{
    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
