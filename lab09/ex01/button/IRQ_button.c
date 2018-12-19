#include "button.h"
#include "../led/led.h"

void EINT0_IRQHandler(void) {
    LED_Out(0x01);
	LPC_SC->EXTINT &= (1 << 0);     // Clear pending interrupt
}

void EINT1_IRQHandler(void) {
    LED_Shift(SHIFT_LEFT);
	LPC_SC->EXTINT &= (1 << 1);     // Clear pending interrupt
}

void EINT2_IRQHandler(void) {
    LED_Shift(SHIFT_RIGHT);
	LPC_SC->EXTINT &= (1 << 2);     // Clear pending interrupt
}
