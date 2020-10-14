#include "gbs8_algo.h"
#include <math.h>


uint8_t Read_Binary(uint8_t dec, uint8_t num)
{
    uint8_t bit;
    while (num>=0)
    {
        bit = dec%2;
        num--;
    }
    return bit;  
}

uint16_t Register_Joint(uint8_t regH, uint8_t regL)
{
    uint16_t result = 0;
    result = result ^ regH;
    result = result << 8;
    result = result ^ regL;
    return result;
}

void Reg10_Decouple(uint8_t* regH, uint8_t* regL, uint16_t reg)
{
    uint8_t regL_temp = 0b0000000011;
    regL = reg & regL_temp;
    regH = reg >> 2;
}