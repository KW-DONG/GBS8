#ifndef __GBS8_STEPPER_H
#define __GBS8_STEPPER_H
#include "stdint.h"
#include <stdint.h>
#include "gbs8_gpio.h"
#include "gbs8_algo.h"

/****************************CONFIGURATION***********************************/

#define STEPPER_BUFFER_SIZE     3       //number of trapezoidal curves in the buffer

#define MAXIMUM_SPEED           3000    //use rpm
#define MAXIMUM_ACCELERATION    1000    //rpm^2
#define JERK_SPEED              20      //rpm, speed difference that does not need an acceleration
#define RESOLUTION              200     //steps per rotation, default rotate angle is 1.8 degree
#define TIMER_FREQ              10000   //10000 counts per second

#define STEPPER_A   1
#define STEPPER_B   0
#define STEPPER_C   0
#define STEPPER_D   0
#define STEPPER_E   0

#if (STEPPER_A) 
#define A_DIR_W(dir)    POUT_1(dir)
#define A_DIR_R         POUT_1_R
#define A_STEP_W(state) RUN_BLINK(state)
#define A_STEP_R        RUN_BLINK_R
#endif

#if (STEPPER_B)
#define B_DIR_W(dir)
#define B_DIR_R
#define B_STEP_W(state)
#define B_STEP_R
#endif

#if (STEPPER_C)
#define C_DIR_W(dir)
#define C_DIR_R
#define C_STEP_W(state)
#define C_STEP_R
#endif

#if (STEPPER_D)
#define D_DIR_W(dir)
#define D_DIR_R
#define D_STEP_W(state)
#define D_STEP_R
#endif

#if (STEPPER_E)
#define E_DIR_W(dir)
#define E_DIR_R
#define E_STEP_W(state)
#define E_STEP_R
#endif


#define TMR 2                   //timer selected

#define STEPPER_ON  1
#define STEPPER_OFF 0

/*****************************************************************************/

/**
 * 
 * ^
 * |
 * |           +---------+
 * |          /|         |
 * |         / |         |
 * |        /  |         |
 * |f_jerk +   |         |
 * |       |   |         |
 * +-------+---+---------+------->
 *        t0   t1        t2
 * 
 * f_jerk is the minimal frequency that depends on the counter variable
 * 
 */


#define MAXIMUM_FREQ    MAXIMUM_SPEED*RESOLUTION/60 //Hz
#define JERK_FREQ       JERK_FREQ*RESOLUTION/60     //Hz

#define IDLE_CNT        

#if (TMR==1)
#define TMR_ISR T1I_ISR
#elif (TMR==2)
#define TMR_ISR T2I_ISR
#endif

/*********************************TYPES*************************************/

#define BLOCK_BUSY  0
#define BLOCK_FREE  1
#define BLOCK_READY 2
#define BLOCK_EXE   3

#define CLOCKWISE       0
#define ANTICLOCKWISE   1

typedef uint8_t dir_t;          //direction

typedef float accRm_t;          //rotations per minute per minute
typedef float speedRm_t;        //rotations per minute
typedef float rotate_t;         //rotations

typedef uint32_t accSec_t;      //steps per second per second
typedef uint32_t speedSec_t;    //steps per second
typedef uint32_t steps_t;       //steps

typedef uint32_t accCnt_t;      //Counts increasement per step
typedef uint32_t cnt_t;         //Counts per step

typedef struct
{
    dir_t dir;

    steps_t acc_until;     
    steps_t dec_after;
    steps_t dec_until;
    
    accCnt_t acc;
    accCnt_t dec;

    cnt_t maxSpeed;

    uint8_t  flag;
}trapblock_t;

typedef struct 
{
    trapblock_t buffer[STEPPER_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
}sBuffer_t;

typedef struct 
{
    uint8_t state;          //ON or OFF
    uint8_t lock;           //manual lock
    uint8_t dir;            //stepper direction
    uint32_t cnts;          //used for iteration
    uint32_t cntsLast;      //represents current frequency
    uint8_t pinState;       //ON or OFF
}stepper_t;

/*******************************Declaration***************************************/

/**
 * @brief stepper motor initialization
 */
void GBS_Stepper_Init(void);

/**
 * @brief stepper motor buffer initialization
 */
void GBS_Stepper_Buffer_Init(sBuffer_t* sBufferX);

/**
 * @brief enable or diable stepper motor
 * @param state ON or OFF
 */
void GBS_Stepper_Config(stepper_t* stepperX, uint8_t state);

/**
 * @brief trapezoidal curve planner
 * @param sBufferX stepper motor buffer
 * @param dir clockwise or anticlockwise
 * @param rotation  rotation number (float)
 * @param v_i entry speed
 * @param v_m maximum speed allowed
 * @param v_o leave speed
 * @param a_i acceleration
 * @param a_o deceleration
 */
uint8_t GBS_Stepper_Planner(sBuffer_t* sBufferX, dir_t dir, rotate_t rotation, speedRm_t v_i, speedRm_t v_m, speedRm_t v_o, accRm_t a_i, accRm_t a_o);

/**
 * @brief stepper execution
 * @param stepperX stepper motor id
 * @param sBufferX stepper buffer
 * @note only called by ISR
 */
void GBS_Stepper_Exe(stepper_t* stepperX, sBuffer_t* sBufferX);

/**
 * @brief update the pins for all stepper motrs 
 * @note only called by ISR
 */
void GBS_Stepper_Update(void);

/*****************************GLOBAL_VARIABLES************************************/

#if (STEPPER_A)
sBuffer_t sBufferA;
stepper_t stepperA;
#endif

#if (STEPPER_B)
sBuffer_t sBufferB;
stepper_t stepperB;
#endif

#if (STEPPER_C)
sBuffer_t sBufferC;
stepper_t stepperC;
#endif

#if (STEPPER_D)
sBuffer_t sBufferD;
stepper_t stepperD;
#endif

#if (STEPPER_E)
sBuffer_t sBufferE;
stepper_t stepperE;
#endif

#define PORT_FLAG_UP    0
#define PORT_FLAG_FALL  1

/*****************************ALGORITHMN****************************************/

#define STEPPER_ACC     1
#define STEPPER_CST     0
#define STEPPER_DEC     -1

/**The LeibRamp Algorithmn
 * 
 * The given parameters are:
 * v0 - base speed (steps per second)
 * v - slew speed
 * a - acceleration (steps per second per second)
 * F - timer frequency (counts of timer tickes per second)
 * 
 * and calculated parameters are:
 * S - acceleration/deceleration distance
 *          S = (v^2 - v0^2) / (2a)
 * p1 - delay period for initial steps
 *          p1 = F / (v0^2 + 2a)^0.5
 * ps - delay period for the slew speed steps
 *          ps = F / v
 * R - constant multiplier
 *          R = a / F^2
 * 
 * p - the variable delay period
 *          p = p*(1 + m*p*p)
 * 
 * where 
 * m = -R during acceleration phase
 * m = 0 between acceleration and deceleration phases
 * m = R during deceleration phase
 * 
 * with better precision
 * p = p * (1 + q + q^2)
 * where
 * q = m*p*p
 * 
 */

#define FIRST_STEP_CAL(v, a) TIMER_FREQ / SQRT(SQ(v) + 2*a)

#define NEXT_STEP_CAL(dir,cnt,a)  cnt + dir*CUBE(cnt)*a/SQ(TIMER_FREQ) + CUBE(cnt)*SQ(cnt)*SQ(a/SQ(TIMER_FREQ))


#endif