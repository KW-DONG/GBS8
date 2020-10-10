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