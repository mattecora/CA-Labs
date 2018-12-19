#ifndef     __LED_H
#define     __LED_H

#include    "LPC17xx.h"

#define     LED_NUM      8
#define     SHIFT_LEFT  -1
#define     SHIFT_RIGHT  1

//          lib_led.c
void        LED_Init(unsigned int initial_value);   // LEDs initialization
void        LED_Deinit(void);                       // LEDs deinitialization

//          func_led.c
void        LED_On(unsigned int num);               // Turn on a LED
void        LED_Off(unsigned int num);              // Turn off a LED
void        LED_Out(unsigned int value);            // Set a value to the LED array
void        LED_Shift(int dir);                     // Shift active LED

#endif
