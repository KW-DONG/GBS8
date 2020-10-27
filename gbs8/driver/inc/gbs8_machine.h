/**
 *  state machine for a standard SSVE device
 *  this state machine is controlled by four buttons with leds and other signals
 *  the state machine is updated by timer 0
 */

#ifndef __GBS8_BUTTON_H
#define __GBS_BUTTON_H
#include <stdint.h>
#include "gbs8_gpio.h"
#include "gbs8_timer.h"

#define BUTTON_START1   NULL
#define BUTTON_START2   NULL
#define BUTTON_STOP     NULL
#define BUTTON_LOCK     NULL

#define LED_START1      NULL
#define LED_START2      NULL
#define LED_STOP        NULL
#define LED_LOCK        NULL

#define FEEDBACK_A      NULL
#define FEEDBACK_B      NULL
#define FEEDBACK_C      NULL
#define FEEDBACK_D      NULL
#define FEEDBACK_E      NULL

#define OUTPUT_A        NULL
#define OUTPUT_B        NULL
#define OUTPUT_C        NULL
#define OUTPUT_D        NULL
#define OUTPUT_E        NULL

 
typedef struct 
{
    //states
    uint8_t enable:1;  //ON or OFF
    uint8_t machineState;

    //requestions
    uint8_t startRequest:1;
    uint8_t stopRequest:1;
    uint8_t stateChangeRequest;
    
}machine_t;

extern machine_t myMachine;

void GBS_Machine_Init();


#endif