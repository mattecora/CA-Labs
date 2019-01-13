#include "adc.h"

void ADC_IRQHandler(void)
{
    /* Read ADC value */
    ADC_Val = ((LPC_ADC->ADGDR >> 4) & 0xFFF);
    
    /* Set the DAC volume */
    DAC_Volume = ADC_Val;
}
