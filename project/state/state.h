#ifndef     __STATE_H
#define     __STATE_H

#include    "../led/led.h"
#include    "../timer/timer.h"
#include    "../rit/rit.h"

/*--------- State-related definitions --------------------------------------*/

enum        state           {STATE_RG, STATE_RFG, STATE_GR, STATE_YR};
typedef     enum state      state_t;                /* state_t definition   */

extern      state_t         current_state;          /* Semaphore state      */

/*--------- State handlers -------------------------------------------------*/

extern      void (*Run_State[4])(void);             /* Vector of handlers   */

void        Run_State0(void);                       /* STATE_RG handler     */
void        Run_State1(void);                       /* STATE_RFG handler    */
void        Run_State2(void);                       /* STATE_GR handler     */
void        Run_State3(void);                       /* STATE_YR handler     */

#endif
