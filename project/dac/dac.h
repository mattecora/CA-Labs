/*--------------------------------------------------------------------------*/
/*          DAC library for LPC1768/LandTiger board                         */
/*--------------------------------------------------------------------------*/

#ifndef     __DAC_H
#define     __DAC_H

#include    "LPC17xx.h"

#include    "../adc/adc.h"

/*--------- DAC-related defines --------------------------------------------*/

#define     FREQ_440HZ      0x377                   /* A (440 Hz)           */

#define     VOL_MAX         ADC_MAX                 /* Maximum volume       */
#define     VOL_MIN         ADC_MIN                 /* Minimum volume       */

extern      uint16_t        DAC_Volume;             /* Output volume        */

/*--------- lib_dac.c ------------------------------------------------------*/

void        DAC_Init(void);                         /* Initialize the DAC   */

/*--------- func_dac.c -----------------------------------------------------*/

void        DAC_Out(uint16_t dac_val);              /* Output analog value  */
void        DAC_Play(void);                         /* Output next sample   */

#endif
