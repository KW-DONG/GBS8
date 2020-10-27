#include "gbs8_gpio.h"
#include "gbs8_config.h"
#include "gbs8_timer.h"
#include "gbs8_relay.h"
#include "gbs8_interrupt.h"

uint32_t i;

int main()
{
    GBS_Interrupt_Init();
    GBS_Timer0_Config(TIM0_PS2, 0);
    RUN_BLINK(LED_ON);
    GBS_RELAY2_SET(NO);
    while(1);
}

void T0I_ISR()
{
    if (i>10)
    {
        i = 0;
        GBS_RELAY1_SET(NC);
    }  
    else
    {
        GBS_RELAY1_SET(NO);
        i++;
    }     
}

