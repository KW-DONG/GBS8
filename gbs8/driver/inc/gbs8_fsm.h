/**
 *  finit state machine for a standard SSVE device
 *  this state machine is controlled by four buttons with leds and other signals
 *  the state machine is updated by timer 0
 *  please do not write ISR for timer 0 if you would like to use the state machine
 * 
 * 
 *  Benefits of using fsm
 *  1. All the SSVE equipments use the same user interface 
 *  2. New delay function saves CPU resource
 */

#ifndef __GBS8_FSM_H
#define __GBS8_FSM_H
#include <stdint.h>
#include "gbs8_gpio.h"
#include "gbs8_timer.h"
#include "gbs8_config.h"

#define SAFE_STATE      0
#define WORK_STATE      1
#define IDLE_STATE      2

 
typedef struct 
{
    //states
    uint8_t state;
    
}fsm_t;

typedef struct
{
    uint8_t currentState;
    uint8_t nextState;
    uint8_t condition;

}task_t;

typedef struct 
{
    uint8_t total
}state_t;


task_t taskList[TASK_NUM];

fsm_t myFsm;

void GBS_Delay_Ms(uint64_t t);

void GBS_Machine_Init();

void GBS_Machine_Start();

void GBS_Safe_Mode();

void GBS_Idle_Mode();

void GBS_Task_Scheduler();

#endif