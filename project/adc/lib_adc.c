#include "adc.h"

/* Current ADC value */
uint16_t ADC_Val = 0xFFFF;

void ADC_Init(uint8_t adc_channel)
{
    /* Power on the ADC */
    LPC_SC->PCONP |= 1 << 12;
    
    /* Set pins for channels 0-3*/
    LPC_PINCON->PINSEL1 |= (adc_channel & 0x1) << 14 |
                           (adc_channel & 0x2) << 15 |
                           (adc_channel & 0x4) << 16 |
                           (adc_channel & 0x8) << 17;
    
    /* Set pins for channels 4-5 */
    LPC_PINCON->PINSEL3 |= (adc_channel & 0x10) << 24 |
                           (adc_channel & 0x10) << 25 |
                           (adc_channel & 0x20) << 25 |
                           (adc_channel & 0x20) << 26;
    
    /* Set pins for channels 6-7 */
    LPC_PINCON->PINSEL0 |= (adc_channel & 0x40) << 1 |
                           (adc_channel & 0x80) >> 2;

    /* Set the control register */
    LPC_ADC->ADCR = (adc_channel) | /* Set ADC channel */
                    (4 << 8) |      /* Set clock divider */
                    (1 << 21);      /* Set enable bit */ 

    /* Enable global interrupt */
    LPC_ADC->ADINTEN = 1 << 8;

    /* Enable interrupt in the NVIC */
    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_Start(void)
{
    /* Set conversion mode to now */
    LPC_ADC->ADCR |= 1 << 24;
}

void ADC_Stop(void)
{
    /* Set conversion mode to none */
    LPC_ADC->ADCR &= ~(7 << 24);
}
