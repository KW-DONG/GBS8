#ifndef __GBS8_RELAY_H
#define __GBS8_RELAY_H

#include <pic16f887.h>
#include <xc.h>

#define RELAY1_STATE  PORTEbits.RE2
#define RELAY2_STATE  PORTEbits.RE1

/**
 *  @brief relay 1 initialization function
 *  @note use pin 27 RE2/AN7
 */
void GBS_Relay1_Init();

/**
 *  @brief relay 1 set
 *  @note Pin NC connects Pin COM
 */
void GBS_Relay1_Set();

/**
 *  @brief relay 1 reset
 *  @note Pin NO connects Pin COM
 */
void GBS_Relay1_Reset();

/**
 *  @brief relay 2 initialization function
 *  @note use pin 26 RE1/AN6
 */
void GBS_Relay2_Init();

/**
 *  @brief relay 2 reset
 *  @note Pin NC connects Pin COM
 */
void GBS_Relay2_Set();

/**
 *  @brief relay 2 reset
 *  @note Pin NO connects Pin COM
 */
void GBS_Relay2_Reset();

#endif
