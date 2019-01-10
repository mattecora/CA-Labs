/*--------------------------------------------------------------------------*/
/*          Joystick library for LPC1768/LandTiger board                    */
/*--------------------------------------------------------------------------*/

#ifndef     __JOYSTICK_H
#define     __JOYSTICK_H

#include    "LPC17xx.h"

/*--------- Joystick-related defines ---------------------------------------*/

#define     JOY_NONE        -1
#define     JOY_SEL         0
#define     JOY_DOWN        1
#define     JOY_LEFT        2
#define     JOY_RIGHT       3
#define     JOY_UP          4

/*--------- lib_joystick.c -------------------------------------------------*/

void        Joystick_Init(void);                    /* Initialize joystick  */

/*--------- func_joystick.c ------------------------------------------------*/

int8_t      Joystick_Get(void);                     /* Get direction        */

#endif
