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

void GBS_Timer1_Config(uint8_t state, uint8_t gateEn, uint8_t gateDir, uint8_t pr0, uint8_t pr1)
{
    TMR1CS = 0; //use internal clock source
    T1OSCEN = 0;//LP oscillator is off

    TMR1ON = state;
    TMR1GE = gateEn;
    T1GINV = gateDir;
    T1CKPS0 = pr0;
    T1CKPS1 = pr1;
}

void GBS_Timer2_Config(uint8_t state, uint8_t pr0, uint8_t pr1, uint8_t po0, uint8_t po1, uint8_t po2, uint8_t po3)
{
    TMR2ON = state;
    T2CKPS0 = pr0;
    T2CKPS1 = pr1;
    TOUTPS0 = po0;
    TOUTPS1 = po1;
    TOUTPS2 = po2;
    TOUTPS3 = po3;
}