#include "gbs8_gpio.h"
#include "gbs8_config.h"
#include "gbs8_timer.h"
#include "gbs8_relay.h"
#include "gbs8_interrupt.h"

int i;
uint8_t t;
uint8_t k;

int main()
{
    GBS_Interrupt_Init();
    GBS_Timer0_Config(TIM0_PS256, 0);
    GBS_Timer1_Config(TIM_ENABLE, TIM1_PS8, 0);
    //GBS_Timer2_Config(TIM_ENABLE, TIM2_PS16, T2OUTPS9, 0);
    //POUT_10(P_ON);
    //GBS_PWM_Config(FULL_BRIDGE_F,0);

    //RUN_BLINK(LED_ON);
    //GBS_RELAY2_SET(NO);


    while(1)
    {
        //RUN_BLINK(LED_ON);
        //GBS_RELAY1_SET(NC);
        //__delay_ms(100);
        //RUN_BLINK(LED_OFF);
        //GBS_RELAY1_SET(NO);
        //__delay_ms(100);
        
        if (i>500)
        {
            //RUN_BLINK(LED_ON);
            //__delay_ms(1);
        }
        else
        {
            //RUN_BLINK(LED_OFF);
            //__delay_ms(1);
        }

    }
}

void T0I_ISR()
{
    if (i>1)
    {
        i = 0;
        //GBS_RELAY1_SET(NC);
        RUN_BLINK(LED_ON);
        //__delay_ms(1);
    }  
    else
    {
        //GBS_RELAY1_SET(NO);
        RUN_BLINK(LED_OFF);
        //__delay_ms(1);
        i++;
    }     
}

void T1I_ISR()
{
    if (t>1)
    {
        t = 0;
        GBS_RELAY1_SET(NO);
    }
    else
    {
        GBS_RELAY1_SET(NC);
        t++;
    }
}

void T2I_ISR()
{
    
}
