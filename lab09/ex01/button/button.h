#ifndef     __BUTTON_H
#define     __BUTTON_H

#include    "LPC17xx.h"

//          lib_button.c
void        ButtonInit(void);           // Buttons initialization

//          IRQ_button.c
void        EINT1_IRQHandler(void);     // Handler for INT0
void        EINT2_IRQHandler(void);     // Handler for KEY1
void        EINT3_IRQHandler(void);     // Handler for KEY2

#endif
