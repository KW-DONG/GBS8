#ifndef __GBS8_STEPPER_H
#define __GBS8_STEPPER_H
#include "stdint.h"

#define STEPPER_BUFFER_SIZE 5

typedef struct
{
    uint32_t steps;
    uint32_t freq;
}stepperCtrl_t;

typedef struct 
{
    stepperCtrl_t buffer[STEPPER_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}stepperBuffer_t;

void GBS8_Stepper_Init();

void GBS8_Stepper_Planner();

void GBS8_Stepper_Config(uint8_t freq, uint8_t en);

#endif