#include "LPC17xx.h"
#include "../led/led.h"
#include "../button/button.h"

int main() {
    // SystemInit() called by startup_LPC17xx.s
    LED_Init(0x01);
    Button_Init();
    
    while (1) {
        __ASM("WFI");
    }
}
