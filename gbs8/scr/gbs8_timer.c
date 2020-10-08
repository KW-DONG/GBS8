#include "gbs8_timer.h"

void GBS_Timer0_Mode(uint8_t mode)
{
    PSA = 0;
    T0SE = 0;
    switch (mode)
    {
        case TIMER_MODE:    T0CS = 0;
        case COUNTER_MODE:  T0CS = 1;
    }
}

void GBS_Timer1_Mode(uint8_t mode);

void GBS_Timer2_Mode(uint8_t mode);