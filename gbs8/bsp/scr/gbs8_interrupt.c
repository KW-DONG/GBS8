#include "gbs8_interrupt.h"
#include "gbs8_config.h"

/******************************************GLOBAL******************************************************/

void GBS_Interrupt_Init()
{
#if (EXTI_EN)
    GBS_EXTI_Config(1);
#endif
#if (CNIT_EN)
    GBS_CNIT_Config(1);
#endif
#if (T0I_EN)
    GBS_T0I_Config(1);
#endif
#if (T1I_EN)
    GBS_T1I_Config(1);
#endif
#if (T2I_EN)
    GBS_T2I_Config(1);
#endif
    GBS_Interrupt_Enable();
}

void GBS_Interrupt_Enable()
{
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void GBS_Interrupt_Disable()
{
    INTCONbits.GIE = 0;
}

/*****************************************CONFIG*********************************************************/

void GBS_EXTI_Config(uint8_t mode)
{
   
    //enable the external interrupt 
    INTCONbits.INTE = 1;
    
    OPTION_REGbits.INTEDG = mode;
    
    //clear exti flag
    INTCONbits.INTF = 0;
}

void GBS_CNIT_Config(uint8_t mode)
{

    //enable portb change interrupt
    INTCONbits.RBIE = mode;

    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;
    IOCBbits.IOCB3 = 1;
    IOCBbits.IOCB4 = 1;
    IOCBbits.IOCB5 = 1;
    IOCBbits.IOCB6 = 1;
    IOCBbits.IOCB7 = 1;

    //clear change interrupt
    INTCONbits.RBIF = 0;
} 

void GBS_T0I_Config(uint8_t mode)
{
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = mode;
}

void GBS_T1I_Config(uint8_t mode)
{
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = mode;
}

void GBS_T2I_Config(uint8_t mode)
{
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = mode;
}

/********************************************ISR****************************************************/

void __interrupt() ISR()
{
#if (EXTI_EN)
    if (INTCONbits.INTF)
    {
        EXTI_ISR(EXTI_MD);
        INTCONbits.INTF = 0;
    }
#endif

#if (CNIT_EN)
    if (INTCONbits.RBIF)
    {
        CNIT_ISR();
        INTCONbits.RBIF = 0;
    }
#endif
    
#if (T0I_EN)
    if (INTCONbits.T0IF)
    {
        T0I_ISR();
#if (USE_FSM)
        
#endif
        INTCONbits.T0IF = 0;
    }
#endif

#if (T1I_EN)
    if (PIR1bits.TMR1IF)
    {
        T1I_ISR();
        PIR1bits.TMR1IF = 0;
    }
#endif

#if (T2I_EN)
    if (PIR1bits.TMR2IF)
    {
        T2I_ISR();
        PIR1bits.TMR2IF = 0;
    }

#endif

#if (USART_EN)
    if (PIR1bits.TXIF)
    {
        USART_TX_ISR();
        PIR1bits.TXIF = 0;
    }
    
    if (PIR1bits.RCIF)
    {
        USART_RX_ISR();
        PIR1bits.RCIF = 0;
    }
    
#if USE_PROTOCAL
    
#endif

#endif

}


