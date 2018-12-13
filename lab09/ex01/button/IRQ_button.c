#include "button.h"
#include "../led/led.h"

void EINT0_IRQHandler(void) {
    LEDOut(0x80);
	LPC_SC->EXTINT &= (1 << 0);     // Clear pending interrupt
}

void EINT1_IRQHandler(void) {
    LEDShift(SHIFT_LEFT);
	LPC_SC->EXTINT &= (1 << 1);     // Clear pending interrupt
}

void EINT2_IRQHandler(void) {
    LEDShift(SHIFT_RIGHT);
	LPC_SC->EXTINT &= (1 << 2);     // Clear pending interrupt
}
