/*--------------------------------------------------------------------------*/
/*          RIT library for LPC1768/LandTiger board                         */
/*--------------------------------------------------------------------------*/

#ifndef     __RIT_H
#define     __RIT_H

#include    "LPC17xx.h"

#include    "../button/button.h"
#include    "../timer/timer.h"
#include    "../dac/dac.h"
#include    "../state/state.h"

/*--------- RIT defines ----------------------------------------------------*/

extern      uint8_t         Debounce_Key;           /* Button to debounce   */

/*--------- lib_rit.c ------------------------------------------------------*/

void        RIT_Init(uint32_t rit_interval);        /* Initialize the RIT   */
void        RIT_Enable(void);                       /* Enable the RIT       */
void        RIT_Disable(void);                      /* Disable the RIT      */
void        RIT_Reset(void);                        /* Reset the RIT        */
void        RIT_Debounce(uint8_t key);              /* Debounce with RIT    */

/*--------- IRQ_rit.c ------------------------------------------------------*/

void        RIT_IRQHandler(void);                   /* Handler for RIT      */

#endif
