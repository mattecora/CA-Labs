#include "dac.h"

/* Sampled sine wave on 10 bits */
uint16_t Sin_Wave[64] = 
{
     512,  562,  612,  661,  708,  753,  796,  837,
     874,  908,  938,  964,  985, 1002, 1014, 1022,
    1023, 1022, 1014, 1002,  985,  964,  938,  908,
     874,  837,  796,  753,  708,  661,  612,  562,
     512,  462,  412,  363,  316,  271,  228,  187,
     150,  116,   86,   60,   39,   22,   10,    2,
       0,    2,   10,   22,   39,   60,   86,  116,
     150,  187,  228,  271,  316,  363,  412,  462
};

/* Sample to output */
uint8_t Sample_Num = 0;

/* Volume for output */
uint16_t DAC_Volume = VOL_MAX;

void DAC_Out(uint16_t dac_val)
{
    /* Clear DAC output */
    LPC_DAC->DACR &= ~(0x3FF << 6);
    
    /* Set DAC output */
    LPC_DAC->DACR |= (dac_val & 0x3FF) << 6;
}

void DAC_Play(void)
{
    /* Output the scaled sample */
    DAC_Out(Sin_Wave[Sample_Num] * DAC_Volume/VOL_MAX);
    
    /* Compute next sample */
    Sample_Num = (Sample_Num + 1) % 64;
}
