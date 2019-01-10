/*--------------------------------------------------------------------------*/
/*          DAC library for LPC1768/LandTiger board                         */
/*--------------------------------------------------------------------------*/

#ifndef     __DAC_H
#define     __DAC_H

#include    "LPC17xx.h"

/*--------- lib_dac.c ------------------------------------------------------*/

void        DAC_Init(void);                         /* Initialize the DAC   */

/*--------- func_dac.c -----------------------------------------------------*/

void        DAC_Out(uint16_t dac_val);              /* Output analog value  */

#endif
