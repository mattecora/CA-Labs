#ifndef     __RIT_H
#define     __RIT_H

#include    "LPC17xx.h"

#include    "../led/led.h"

/*--------- RIT frequency defines ------------------------------------------*/

#define     DEBUG                                   /* Delete for real vals */

#ifdef      DEBUG
#define     FREQ_2HZ        0x001312D0              /* Divided by 10        */
#else
#define     FREQ_2HZ        0x00BEBC20              /* True value           */
#endif

/*--------- lib_rit.c ------------------------------------------------------*/

void        RIT_Init(uint32_t rit_interval);        /* Initialize the RIT   */
void        RIT_Enable(void);                       /* Enable the RIT       */
void        RIT_Disable(void);                      /* Disable the RIT      */
void        RIT_Reset(void);                        /* Reset the RIT        */

/*--------- IRQ_rit.c ------------------------------------------------------*/

void        RIT_IRQHandler(void);                   /* Handler for RIT      */

#endif
