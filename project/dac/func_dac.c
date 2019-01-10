#include "dac.h"

void DAC_Out(uint16_t dac_val)
{
    /* Clear DAC output */
    LPC_DAC->DACR &= ~(0x3FF << 6);
    
    /* Set DAC output */
    LPC_DAC->DACR |= (dac_val & 0x3FF) << 6;
}
