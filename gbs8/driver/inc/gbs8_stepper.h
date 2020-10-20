#ifndef __GBS8_STEPPER_H
#define __GBS8_STEPPER_H
#include "stdint.h"
#include <stdint.h>
#include "gbs8_gpio.h"

/****************************CONFIGURATION***********************************/

#define STEPPER_BUFFER_SIZE 5   //number of trapezoidal curves in the buffer

#define MAXIMUM_SPEED   3000    //use rpm
#define RESOLUTION      200     //steps per rotation, default rotate angle is 1.8 degree

#define P_DIR(X)    POUT_1(X)
#define P_STP(X)    POUT_2(X)

#define TMR 2                   //timer selected

/*****************************************************************************/

#define MAXIMUM_FREQ    MAXIMUM_SPEED*RESOLUTION/60 //Hz

#if (TMR==0)
#define TMR_ISR T0I_ISR
#elif (TMR==1)
#define TMR_ISR T1I_ISR
#elif (TMR==2)
#define TMR_ISR T2I_ISR
#endif

/*********************************TYPES*************************************/

typedef struct
{
    uint8_t dir;
    uint32_t freq_in;
    uint32_t acc_until;
    uint32_t dec_after;
    uint32_t max_freq;
}trapblock_t;

typedef struct 
{
    trapblock_t buffer[STEPPER_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}stepperBuffer_t;

void GBS_Stepper_Init();

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

/************************GLOBAL_VARIABLES************************************/
stepperBuffer_t stepperBuffer;

uint64_t stepperCnts = 0;

uint64_t stepperFreq = 0;

uint8_t  stepperDir = 0;



#endif