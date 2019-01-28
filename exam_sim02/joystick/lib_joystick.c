#include "joystick.h"

void Joystick_Init(void)
{
	/* Set GPIO PIN mode on P1.25 - P1.29 */
    LPC_PINCON->PINSEL3 &= ~(0x3FF << 18);
	
	/* Set direction to input in P1.25 - P1.29 */
    LPC_GPIO1->FIODIR &= ~(0x1F << 25);
}
