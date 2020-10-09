#include <stdlib.h>
#include "gbs8_timer.h"

void GBS_Timer0_Config(uint8_t clockSource, uint8_t sourceEdge, uint8_t assignment, uint8_t pr0, uint8_t pr1, uint8_t pr2)
{
    T0CS = clockSource;
    T0SE = sourceEdge;
    PSA = assignment;
    PS0 = pr0;
    PS1 = pr1;
    PS2 = pr2;

}

void GBS_Timer1_Config(uint8_t state, uint8_t gateEn, uint8_t gateDir, uint8_t ckPS)
{
    TMR1CS = 0; //use internal clock source
    T1OSCEN = 0;//LP oscillator is off

    TMR1ON = state;
    TMR1GE = gateEn;
    T1GINV = gateDir;
    T1CONbits.T1CKPS = ckPS;
}

void GBS_Timer2_Config(uint8_t state, uint8_t ckPS, uint8_t outPS)
{
    TMR2ON = state;
    T2CONbits.T2CKPS = ckPS;
    T2CONbits.TOUTPS = outPS;
}

void GBS_PWM_Config(uint8_t pr2, uint8_t OCfg)
{
    PR2 = pr2;
    CCP1CONbits.P1M = OCfg;
    CCP2CONbits;
    CCPR1L;
}

void GBS_ECCP_Config(uint8_t mode)
{
    CCP1CONbits.CCP1M = mode;
}