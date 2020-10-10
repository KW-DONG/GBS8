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
}

void GBS_Interrupt_Disable()
{
    INTCONbits.GIE = 0;
}

/*****************************************CONFIG*********************************************************/

void GBS_EXTI_Config(uint8_t mode)
{
    //enable global interrupts
    INTCONbits.GIE = 1;
    
    //enable the external interrupt 
    INTCONbits.INTE = 1;
    
    OPTION_REGbits.INTEDG = mode;
    
    //clear exti flag
    INTCONbits.INTF = 0;
}

void GBS_CNIT_Config(uint8_t mode)
{
    //enable global interrupts
    INTCONbits.GIE = 1;
    
    //enable portb change interrupt
    INTCONbits.RBIE = mode;
    
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
        INTCONbits.T0IF = 0;
    }
#endif

#if (T1I_EN)
    if (PIR1bits.TMR1IF = 1)
    {
        T1I_ISR();
        PIR1bits.TMR1IF = 0;
    }
#endif
}


