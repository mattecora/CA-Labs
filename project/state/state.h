/*--------------------------------------------------------------------------*/
/*          State management library                                        */
/*--------------------------------------------------------------------------*/

#ifndef     __STATE_H
#define     __STATE_H

#include    "../led/led.h"
#include    "../timer/timer.h"
#include    "../rit/rit.h"
#include    "../adc/adc.h"
#include    "../dac/dac.h"

/*--------- State-related definitions --------------------------------------*/

enum        state           {STATE_RG, STATE_RFG, STATE_GR, STATE_YR};
typedef     enum state      state_t;                /* state_t definition   */

enum        blind           {NO_BLIND, BLIND};
typedef     enum blind      blind_t;                /* blind_t definition   */

enum        maint           {NO_MAINT, MAINT};
typedef     enum maint      maint_t;                /* maint_t definition   */

extern      state_t         Current_State;          /* Semaphore state      */
extern      blind_t         Blind_State;            /* Blind flag           */
extern      maint_t         Maint_State;            /* Maintenance flag     */

/*--------- State handlers -------------------------------------------------*/

extern      void (*Run_State[4])(void);             /* Vector of handlers   */

void        Run_State0(void);                       /* STATE_RG handler     */
void        Run_State1(void);                       /* STATE_RFG handler    */
void        Run_State2(void);                       /* STATE_GR handler     */
void        Run_State3(void);                       /* STATE_YR handler     */

void        Run_Maint(void);                        /* MAINT handler        */
void        Run_NoMaint(void);                      /* NO_MAINT handler     */

#endif
