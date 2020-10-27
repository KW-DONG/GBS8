#include "gbs8_gpio.h"

void GBS_GPIO_Init()
{
    //Inputs
    //RAs
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;
    
    //RBs
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB5 = 1;
 
    //Outputs
    POUT_1(P_OFF);
    POUT_2(P_OFF);
    POUT_3(P_OFF);
    POUT_4(P_OFF);
    POUT_5(P_OFF);
    POUT_6(P_OFF);
    POUT_7(P_OFF);
    POUT_8(P_OFF);
    POUT_9(P_OFF);
    POUT_10(P_OFF);
    POUT_11(P_OFF);
    POUT_12(P_OFF);
    
    //Input mode
    //all digital inputs
    ANSEL = DIGITAL;
    ANSELH = DIGITAL;
}