/*--------------------------------------------------------------------------*/
/*          ADC library for LPC1768/LandTiger board                         */
/*--------------------------------------------------------------------------*/

#ifndef     __ADC_H
#define     __ADC_H

#include    "LPC17xx.h"

#include    "../dac/dac.h"

/*--------- ADC-related defines --------------------------------------------*/

#define     ADC_POTM        1 << 5                  /* Potmeter port        */

#define     ADC_MIN         0                       /* Minimum ADC value    */
#define     ADC_MAX         0xFFF                   /* Maximum ADC value    */

extern      uint16_t        ADC_Val;                /* Current ADC value    */

/*--------- lib_adc.c ------------------------------------------------------*/

void        ADC_Init(uint8_t adc_channel);          /* Initialize the ADC   */
void        ADC_Start(void);                        /* Start the ADC        */
void        ADC_Stop(void);                         /* Stop the ADC         */

/*--------- IRQ_adc.c ------------------------------------------------------*/

void        ADC_IRQHandler(void);                   /* Handler for ADC      */

#endif
