/*--------------------------------------------------------------------------*/
/*          Button library for LPC1768/LandTiger board                      */
/*--------------------------------------------------------------------------*/

#ifndef     __BUTTON_H
#define     __BUTTON_H

#include    "LPC17xx.h"

#include    "../rit/rit.h"

/*--------- Button keys defines --------------------------------------------*/

#define     BUTTON_NONE     0
#define     BUTTON_INT0     1
#define     BUTTON_KEY1     2
#define     BUTTON_KEY2     4
#define     BUTTON_ALL      7

/*--------- Button press count variables -----------------------------------*/

extern      int             e1;
extern      int             e2;

/*--------- lib_button.c ---------------------------------------------------*/

void        Button_Init(uint8_t keys);              /* Initialize buttons   */

/*--------- IRQ_button.c ---------------------------------------------------*/

void        EINT1_IRQHandler(void);                 /* Handler for INT0     */
void        EINT2_IRQHandler(void);                 /* Handler for KEY1     */
void        EINT3_IRQHandler(void);                 /* Handler for KEY2     */

#endif
