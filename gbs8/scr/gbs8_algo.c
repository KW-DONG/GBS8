#include "gbs8_algo.h"
#include <math.h>

uint8_t Demical_2_Binary(uint8_t dec)
{
    uint8_t temp = dec, result = 0, k = 1, i;
    while (temp)
    {
        i = temp%2;
        result = k * i + result;
        k = k * 10;
        temp = temp / 2;
    }
    return result;
}

uint8_t Read_Binary(uint8_t dec, uint8_t len, uint8_t num)
{
    uint8_t len_temp = 0;//actual length
    uint8_t pwr = 1;
    for (;dec>pwr;len_temp++)
    {
        pwr*=10;
    }
    if (len_temp < len&&num<(len-len_temp)) return 0;
    else                                    return (dec);
}