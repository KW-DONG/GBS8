#ifndef __GBS8_TIMER_H
#define __GBS8_TIMER_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>

enum 
{
    TIMER_MODE,
    COUNTER_MODE,
};

/**
 * @brief Timer0 configuration
 * @param mode
 * @note when used as a timer, the Timer0 module will increment every instruction cycle (without prescaler)
 *      when used as a counter, the Timer0 module will increment on every rising or falling edge of the T0CKI pin
 */
void GBS_Timer0_Mode(uint8_t mode);

//timer 1
void GBS_Timer1_Mode(uint8_t mode);

//timer 2
void GBS_Timer2_Mode(uint8_t mode);

#endif