/*--------------------------------------------------------------------------*/
/*          LED library for LPC1768/LandTiger board                         */
/*--------------------------------------------------------------------------*/

#ifndef     __LED_H
#define     __LED_H

#include    "LPC17xx.h"

/*--------- LED-related defines --------------------------------------------*/
#define     LED_NUM         8
#define     LED_ALL         0xFF
#define     LED_NONE        0x00

#define     PED_RED         0x80
#define     PED_GREEN       0x40
#define     CAR_RED         0x20
#define     CAR_YELLOW      0x10
#define     CAR_GREEN       0x08

extern      uint8_t         LED_Value;              /* Current LED value    */

/*--------- lib_led.c ------------------------------------------------------*/

void        LED_Init(uint8_t initial_value);        /* Initialize LEDs      */
void        LED_Deinit(void);                       /* Deinitialize LEDs    */

/*--------- func_led.c -----------------------------------------------------*/

void        LED_On(uint8_t num);                    /* Turn on a LED        */
void        LED_Off(uint8_t num);                   /* Turn off a LED       */
void        LED_Out(uint8_t value);                 /* Output value on LEDs */

#endif
