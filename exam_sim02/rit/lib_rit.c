#include "rit.h"

void RIT_Init(uint32_t rit_interval)
{
    /* Enable power for RIT */
    LPC_SC->PCONP |= (1 << 16);

    /* Set match value */
    LPC_RIT->RICOMPVAL = rit_interval;

    /* Enable clear on match and debug behavior */
    LPC_RIT->RICTRL = (1 << 1) | (1 << 2);

    /* Set count value to 0 */
    LPC_RIT->RICOUNTER = 0;

    /* Enable the interrupt handler */
    NVIC_EnableIRQ(RIT_IRQn);
}

void RIT_Enable(void)
{
    /* Set control bit */
    LPC_RIT->RICTRL |= (1 << 3);
}

void RIT_Disable(void)
{
    /* Unset control bit */
    LPC_RIT->RICTRL &= ~(1 << 3);
}

void RIT_Reset(void)
{
    /* Reset counter */
    LPC_RIT->RICOUNTER = 0;
}
