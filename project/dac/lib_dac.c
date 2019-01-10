#include "dac.h"

void DAC_Init(void)
{
    /* Set pin 0.26 to analog out */
    LPC_PINCON->PINSEL1 |= 1 << 21;
	LPC_PINCON->PINSEL1 &= ~(1 << 20);
    
    /* Set pin direction to output */
	LPC_GPIO0->FIODIR |= 1 << 26;
}
