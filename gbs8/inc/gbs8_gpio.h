#ifndef __GBS8_GPIO_H
#define __GBS8_GPIO_H

#include <pic16f887.h>
#include <xc.h>

#define POUT_1(X)   PORTDbits.RD7 = X
#define POUT_2(X)   PORTDbits.RD6 = X
#define POUT_3(X)   PORTDbits.RD5 = X
#define POUT_4(X)   PORTDbits.RD4 = X
#define POUT_5(X)   PORTCbits.RC5 = X
#define POUT_6(X)   PORTDbits.RD3 = X
#define POUT_7(X)   PORTDbits.RD2 = X
#define POUT_8(X)   PORTDbits.RD1 = X
#define POUT_9(X)   PORTDbits.RD0 = X
#define POUT_10(X)  PORTCbits.RC2 = X
#define POUT_11(X)  PORTCbits.RC1 = X
#define POUT_12(X)  PORTCbits.RC0 = X

#define RUN_BLINK(X)   PORTEbits.RE0 = X

#define PIN_1       PORTAbits.RA2
#define PIN_2       PORTAbits.RA3
#define PIN_3       PORTAbits.RA4
#define PIN_4       PORTAbits.RA5
#define PIN_5       PORTBbits.RB4
#define PIN_6       PORTBbits.RB5
#define PIN_7       PORTAbits.RA0
#define PIN_8       PORTAbits.RA1
#define PIN_9       PORTBbits.RB0
#define PIN_10      PORTBbits.RB1
#define PIN_11      PORTBbits.RB2
#define PIN_12      PORTBbits.RB3

/**
 * @brief Initialize all the inputs and outputs
 */
void GBS_GPIO_Init();

#endif