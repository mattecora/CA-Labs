#include "led.h"

unsigned char led_value;

void LEDInit(unsigned int initial_value) {
    LPC_PINCON->PINSEL4 &= 0xFFFF0000;      // PIN mode GPIO (00b value per P2.0 to P2.7)
	LPC_GPIO2->FIODIR   |= 0x000000FF;      // P2.0...P2.7 Output (LEDs on PORT2 defined as Output)
    LPC_GPIO2->FIOSET    = initial_value;   // Set the LEDs initial value
    led_value            = initial_value;
}

void LEDDeinit(void) {
    LPC_GPIO2->FIODIR   &= 0xFFFFFF00;
}
