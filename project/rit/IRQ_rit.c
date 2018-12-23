#include "rit.h"

void RIT_IRQHandler(void) {
    if ((led_value & 0xFF) == (CAR_RED | PED_GREEN))
        LED_Off(6);             // Turn off if on
    else
        LED_On(6);              // Turn on if off
    
    LPC_RIT->RICTRL |= 0x1;     // Clear interrupt flag
}
