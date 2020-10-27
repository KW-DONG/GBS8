#include "gbs8_fsm.h"
#include "gbs8_interrupt.h"

#if (USE_FSM)

void GBS_Machine_Start()
{
    switch (myFsm.state)
    {
    case SAFE_STATE:
        GBS_Safe_Mode();
        break;
    case WORK_STATE:
        GBS_Work_Mode();
        break;
    case IDLE_STATE:
        GBS_Idle_Mode();
    default:
        GBS_Idle_Mode();
        break;
    } 
}

void GBS_Safe_Mode()
{
    LED_START1(LED_OFF);
    LED_START2(LED_OFF);
    LED_STOP(LED_OFF);
    LED_LOCK(LED_ON);
}

void GBS_Work_Mode()
{
    LED_START1(LED_OFF);
    LED_START2(LED_OFF);
    LED_STOP(LED_ON);
    LED_LOCK(LED_ON);
}

void GBS_Idle_Mode()
{
    LED_START1(LED_ON);
    LED_START2(LED_ON);
    LED_STOP(LED_OFF);
    LED_LOCK(LED_ON);
}

#endif


