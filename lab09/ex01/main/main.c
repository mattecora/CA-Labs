#include "LPC17xx.h"
#include "../led/led.h"
#include "../button/button.h"

int main() {
    SystemInit();
    LEDInit(0x80);
    ButtonInit();
    
    while (1) {
        __ASM("WFI");
    }
}
