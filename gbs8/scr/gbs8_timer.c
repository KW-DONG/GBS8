#include "gbs8_timer.h"

void GBS_Timer0_Config(uint8_t clockSoure, uint8_t sourceEdge, uint8_t assignment, uint8_t prescaler);
{
    T0CS = clockSource;
    T0SE = sourceEdge;
    PSA = assignment;
    PS = prescaler;
}

void GBS_Timer1_Mode(uint8_t mode);

void GBS_Timer2_Mode(uint8_t mode);