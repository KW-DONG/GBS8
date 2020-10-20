#ifndef __GBS8_STEPPER_H
#define __GBS8_STEPPER_H
#include "stdint.h"

#define STEPPER_BUFFER_SIZE 5   //number of trapezoidal curves in the buffer

#define MAXIMUM_SPEED   3000    //use rpm
#define RESOLUTION      200     //steps per rotation, default rotate angle is 1.8 degree


#define MAXIMUM_FREQ    MAXIMUM_SPEED*RESOLUTION/60 //Hz




typedef struct
{
    uint32_t steps;
    uint32_t freq;
}stepperblock_t;

typedef struct 
{
    stepperblock_t buffer[STEPPER_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}stepperBuffer_t;

void GBS_Stepper_Init();

void GBS_Stepper_Planner();

/**
 * @brief write stepper buffer
 * 
 */
void GBS_Stepper_Buffer_Writer(uint32_t freq, uint32_t steps);

void GBS_Stepper_Executor();

/**
 * @brief update stepper directly
 * @param freq stepper frequency
 * @param en   enable or diable
 */
void GBS_Stepper_Config(uint32_t freq, uint8_t en);

#endif