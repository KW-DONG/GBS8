#ifndef __GBS8_RELAY_H
#define __GBS8_RELAY_H

#include <pic16f887.h>
#include <xc.h>

#define NO  0
#define NC  1

#define GBS_RELAY1_SET(X)   TRISEbits.TRISE2 = X
#define GBS_RELAY2_SET(X)   TRISEbits.TRISE1 = X

#define GBS_RELAY1_R        TRISEbits.TRISE2
#define GBS_RELAY2_R        TRISEbits.TRISE1

/**
 *  @brief relay initialization function
 *  @note use pin 27 RE2/AN7 for relay 1
 *  @note use pin 26 RE1/AN6 for relay 2
 */
void GBS_Relay_Init();

#endif
