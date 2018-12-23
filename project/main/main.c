#include "lpc17xx.h"

#include "../led/led.h"
#include "../button/button.h"
#include "../rit/rit.h"

#include "../state/state.h"

int main(void) {
    // SystemInit();
    
    LED_Init(LED_ALL);
    Button_Init(BUTTON_ALL);
    RIT_Init(TIME_2HZ);
    
    Run_State[current_state]();
    
    while (1) {
        __ASM("WFI");
    }
}
