#include "led.h"

const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };
extern unsigned char led_value;

void LED_On(unsigned int num) {
    LPC_GPIO2->FIOPIN   |= led_mask[num];
	led_value            = LPC_GPIO2->FIOPIN;
}

void LED_Off(unsigned int num) {
    LPC_GPIO2->FIOPIN   &= ~led_mask[num];
	led_value            = LPC_GPIO2->FIOPIN;
}

void LED_Out(unsigned int value) {
    int i;

    for (i = 0; i < LED_NUM; i++) {
        if (value & (1<<i)) {
            LED_On(i);
        } else {
            LED_Off(i);
        }
    }
	led_value = value;
}

void LED_Shift(int dir) {
    unsigned int new_value;
    
    if (dir == SHIFT_LEFT) {
        new_value = (led_value << 1) != 0x100 ? (led_value << 1) : 0x01;
        LED_Out(new_value);
    } else if (dir == SHIFT_RIGHT) {
        new_value = (led_value >> 1) != 0x000 ? (led_value >> 1) : 0x80;
        LED_Out(new_value);
    }
}
