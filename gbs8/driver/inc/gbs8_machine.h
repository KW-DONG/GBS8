/**
 *  state machine for a standard SSVE device
 */

#ifndef __GBS8_BUTTON_H
#define __GBS_BUTTON_H
#include <stdint.h>
#include "gbs8_gpio.h"

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
    uint8_t state;  //ON or OFF

}machine_t;


#endif