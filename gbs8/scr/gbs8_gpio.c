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
    POUT_1(OFF);
    POUT_2(OFF);
    POUT_3(OFF);
    POUT_4(OFF);
    POUT_5(OFF);
    POUT_6(OFF);
    POUT_7(OFF);
    POUT_8(OFF);
    POUT_9(OFF);
    POUT_10(OFF);
    POUT_11(OFF);
    POUT_12(OFF);
    
    //Input mode
    //all digital inputs
    ANSEL = DIGITAL;
    ANSELH = DIGITAL;
}