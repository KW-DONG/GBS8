#include "gbs8_fsm.h"
#include "gbs8_interrupt.h"

void GBS_Machine_Init()
{

}

void GBS_Machine_Start()
{
    switch (myMachine.state)
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

}

void GBS_Work_Mode()
{

}

void GBS_Idle_Mode();


void T0I_ISR()
{
    switch (myMachine.state)
    {

    }

     
}

