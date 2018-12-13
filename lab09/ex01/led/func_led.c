#include "led.h"

const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };
extern unsigned char led_value;

void LEDOn(unsigned int num) {
    LPC_GPIO2->FIOPIN   |= led_mask[num];
	led_value            = LPC_GPIO2->FIOPIN;
}

void LEDOff(unsigned int num) {
    LPC_GPIO2->FIOPIN   &= ~led_mask[num];
	led_value            = LPC_GPIO2->FIOPIN;
}

void LEDOut(unsigned int value) {
    int i;

    for (i = 0; i < LED_NUM; i++) {
        if (value & (1<<i)) {
            LEDOn(i);
        } else {
            LEDOff(i);
        }
    }
	led_value = value;
}

void LEDShift(int dir) {
    unsigned int new_value;
    
    if (dir == SHIFT_LEFT) {
        new_value = (led_value << 1) != 0x100 ? (led_value << 1) : 0x01;
        LEDOut(new_value);
    } else if (dir == SHIFT_RIGHT) {
        new_value = (led_value >> 1) != 0x000 ? (led_value >> 1) : 0x80;
        LEDOut(new_value);
    }
}
