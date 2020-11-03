#include "gbs8_gpio.h"
#include "gbs8_config.h"
#include "gbs8_timer.h"
#include "gbs8_relay.h"
#include "gbs8_interrupt.h"
#include "gbs8_stepper.h"
#include "pic16f887.h"
#include "gbs8_usart.h"

#define TEST_STEPPER    0
#define TEST_USART      1


int main()
{
    GBS_Interrupt_Init();
    //GBS_Stepper_Init();
    GBS_USART_Init(9600);
    
    while(1)
    {
        RUN_BLINK(LED_ON);
        //TXREG = 'G';
        __delay_ms(1000);
        RUN_BLINK(LED_OFF);
        __delay_ms(1000);
        SEND_CHAR("1234");
        GBS_USART_Send();
        
    #if (TEST_STEPPER)
        if (sBufferA.buffer[sBufferA.tail].flag == BLOCK_FREE)
        {
            sBufferA.buffer[sBufferA.tail].acc = 10;
            sBufferA.buffer[sBufferA.tail].acc_until = 50;
            sBufferA.buffer[sBufferA.tail].dec = 10;
            sBufferA.buffer[sBufferA.tail].dec_after = 50;
            sBufferA.buffer[sBufferA.tail].dec_until = 150;
            sBufferA.buffer[sBufferA.tail].dir = CLOCKWISE;
            sBufferA.buffer[sBufferA.tail].flag = BLOCK_READY;
            sBufferA.buffer[sBufferA.tail].maxSpeed = 500;
            sBufferA.tail = (sBufferA.tail+1)%STEPPER_BUFFER_SIZE;
            //if (RUN_BLINK_R==LED_ON)    RUN_BLINK(LED_OFF);
            //else                        RUN_BLINK(LED_ON);
            __delay_ms(100);
        }
    #endif
    #if (TEST_USART)
        //GBS_USART_Buffer_Write(&usartSendBuffer, 'a');
        //GBS_USART_Send(&usartSendBuffer);
    #endif
    }
}


