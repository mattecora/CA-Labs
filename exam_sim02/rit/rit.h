/*--------------------------------------------------------------------------*/
/*          RIT library for LPC1768/LandTiger board                         */
/*--------------------------------------------------------------------------*/

#ifndef     __RIT_H
#define     __RIT_H

#include    "LPC17xx.h"

#include    "../joystick/joystick.h"
#include    "../led/led.h"
#include    "../overflow/overflow.h"
#include    "../timer/timer.h"

/*--------- RIT defines ----------------------------------------------------*/

#ifdef      DEBUG
#define     TIME_50MS       0x0001E848              /* Divided by 10        */
#else
#define     TIME_50MS       0x001312D0              /* True value           */
#endif

#define     N               10

/*--------- lib_rit.c ------------------------------------------------------*/

void        RIT_Init(uint32_t rit_interval);        /* Initialize the RIT   */
void        RIT_Enable(void);                       /* Enable the RIT       */
void        RIT_Disable(void);                      /* Disable the RIT      */
void        RIT_Reset(void);                        /* Reset the RIT        */

/*--------- IRQ_rit.c ------------------------------------------------------*/

void        RIT_IRQHandler(void);                   /* Handler for RIT      */

#endif
