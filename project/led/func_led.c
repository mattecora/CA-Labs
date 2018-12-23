#include "led.h"

const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };

void LED_On(unsigned char num) {
    LPC_GPIO2->FIOPIN   |= led_mask[num];
	led_value            = LPC_GPIO2->FIOPIN;
}

void LED_Off(unsigned char num) {
    LPC_GPIO2->FIOPIN   &= ~led_mask[num];
	led_value            = LPC_GPIO2->FIOPIN;
}

void LED_Out(unsigned char value) {
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
