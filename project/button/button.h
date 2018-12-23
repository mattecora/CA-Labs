#ifndef     __BUTTON_H
#define     __BUTTON_H

#include    "LPC17xx.h"

#include    "../state/state.h"

#define     BUTTON_INT0         1
#define     BUTTON_KEY1         2
#define     BUTTON_KEY2         4
#define     BUTTON_ALL          BUTTON_INT0 | BUTTON_KEY1 | BUTTON_KEY2

//          lib_button.c
void        Button_Init         (unsigned char keys);   // Buttons initialization

//          IRQ_button.c
void        EINT1_IRQHandler    (void);                 // Handler for INT0
void        EINT2_IRQHandler    (void);                 // Handler for KEY1
void        EINT3_IRQHandler    (void);                 // Handler for KEY2

#endif
