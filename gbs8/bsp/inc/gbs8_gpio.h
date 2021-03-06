#ifndef __GBS8_GPIO_H
#define __GBS8_GPIO_H

#include <pic16f887.h>
#include <xc.h>


//POUT_X
#define INPUT   1
#define OUTPUT  0

#define P_ON    OUTPUT
#define P_OFF   INPUT

#define LED_ON  INPUT
#define LED_OFF OUTPUT

//PIN_X_MODE
#define ANALOG  1
#define DIGITAL 0

#define POUT_1(X)   TRISDbits.TRISD7 = X
#define POUT_2(X)   TRISDbits.TRISD6 = X
#define POUT_3(X)   TRISDbits.TRISD5 = X
#define POUT_4(X)   TRISDbits.TRISD4 = X
#define POUT_5(X)   TRISCbits.TRISC5 = X
#define POUT_6(X)   TRISDbits.TRISD3 = X
#define POUT_7(X)   TRISDbits.TRISD2 = X
#define POUT_8(X)   TRISDbits.TRISD1 = X
#define POUT_9(X)   TRISDbits.TRISD0 = X
#define POUT_10(X)  TRISCbits.TRISC2 = X
#define POUT_11(X)  TRISCbits.TRISC1 = X
#define POUT_12(X)  TRISCbits.TRISC0 = X

#define POUT_1_R    TRISDbits.TRISD7
#define POUT_2_R    TRISDbits.TRISD6
#define POUT_3_R    TRISDbits.TRISD5
#define POUT_4_R    TRISDbits.TRISD4
#define POUT_5_R    TRISCbits.TRISC5
#define POUT_6_R    TRISDbits.TRISD3
#define POUT_7_R    TRISDbits.TRISD2
#define POUT_8_R    TRISDbits.TRISD1
#define POUT_9_R    TRISDbits.TRISD0
#define POUT_10_R   TRISCbits.TRISC2
#define POUT_11_R   TRISCbits.TRISC1
#define POUT_12_R   TRISCbits.TRISC0

#define RUN_BLINK(X)    TRISEbits.TRISE0 = X
#define RUN_BLINK_R     TRISEbits.TRISE0

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

#define PIN_1_MODE(X)   ANSELbits.ANS2 = X
#define PIN_2_MODE(X)   ANSELbits.ANS3 = X
#define PIN_3_MODE(X)   ANSELbits.ANS4 = X
#define PIN_4_MODE(X)   ANSELbits.ANS5 = X
#define PIN_7_MODE(X)   ANSELbits.ANS0 = X
#define PIN_8_MODE(X)   ANSELbits.ANS1 = X

/**
 * @brief Initialize all the inputs and outputs
 */
void GBS_GPIO_Init();

#endif