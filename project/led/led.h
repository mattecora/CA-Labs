#ifndef     __LED_H
#define     __LED_H

#include    "LPC17xx.h"

#define     LED_NUM         8
#define     LED_ALL         0xFF
#define     LED_NONE        0x00

#define     PED_RED         0x80
#define     PED_GREEN       0x40
#define     CAR_RED         0x20
#define     CAR_YELLOW      0x10
#define     CAR_GREEN       0x08

extern      unsigned char   led_value;                      // Current LED value

//          lib_led.c
void        LED_Init        (unsigned char initial_value);  // LEDs initialization
void        LED_Deinit      (void);                         // LEDs deinitialization

//          func_led.c
void        LED_On          (unsigned char num);            // Turn on a LED
void        LED_Off         (unsigned char num);            // Turn off a LED
void        LED_Out         (unsigned char value);          // Set a value to the LED array

#endif
