#include "joystick.h"

int8_t Joystick_Get(void)
{
	int8_t i;
	
	/* Poll all the joystick directions */
    for (i = JOY_SEL; i <= JOY_UP; i++)
	{
        if (LPC_GPIO1->FIOPIN & 1 << (25 + i))
			return i;
	}
	
	return JOY_NONE;
}
