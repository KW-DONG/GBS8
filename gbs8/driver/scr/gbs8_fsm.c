#include "gbs8_fsm.h"
#include "gbs8_interrupt.h"

void GBS_Machine_Init()
{
    myMachine.enable = 0;
    myMachine.safety = 0;
    myMachine.startRequest = 0;
}

void GBS_Machine_Start()
{
    while (myMachine.safety)
    {
        GBS_Safe_Mode();
    }
    if (myMachine.machineState==0)
    {
        GBS_Idle_Mode();
    }
    else if (myMachine.machineState==1)
    {
        GBS_Work_Mode();
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
    if (myMachine.startRequest == 1)
    {
        myMachine.enable = 1;
        myMachine.startRequest = 0;
    }
    else if (myMachine.stopRequest == 1)
    {
        myMachine.enable = 0;
        myMachine.stopRequest = 0;
    }
     
}

