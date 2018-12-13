#ifndef     __LED_H
#define     __LED_H

#include    "LPC17xx.h"

#define     LED_NUM      8
#define     SHIFT_LEFT  -1
#define     SHIFT_RIGHT  1

//          lib_led.c
void        LEDInit(unsigned int initial_value);    // LEDs initialization
void        LEDDeinit(void);                        // LEDs deinitialization

//          func_led.c
void        LEDOn(unsigned int num);                // Turn on a LED
void        LEDOff(unsigned int num);               // Turn off a LED
void        LEDOut(unsigned int value);             // Set a value to the LED array
void        LEDShift(int dir);                      // Shift active LED

#endif
