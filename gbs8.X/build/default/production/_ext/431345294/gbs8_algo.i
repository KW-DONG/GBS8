# 1 "../gbs8/bsp/scr/gbs8_algo.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "../gbs8/bsp/scr/gbs8_algo.c" 2
# 1 "../gbs8/bsp/inc\\gbs8_algo.h" 1



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 1 3
# 13 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed char int8_t;






typedef signed int int16_t;







typedef __int24 int24_t;







typedef signed long int int32_t;
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint8_t;





typedef unsigned int uint16_t;






typedef __uint24 uint24_t;






typedef unsigned long int uint32_t;
# 88 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed char int_least8_t;







typedef signed int int_least16_t;
# 109 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __int24 int_least24_t;
# 118 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed long int int_least32_t;
# 136 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint_least8_t;






typedef unsigned int uint_least16_t;
# 154 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __uint24 uint_least24_t;







typedef unsigned long int uint_least32_t;
# 181 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef signed char int_fast8_t;






typedef signed int int_fast16_t;
# 200 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __int24 int_fast24_t;







typedef signed long int int_fast32_t;
# 224 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
# 240 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef __uint24 uint_fast24_t;






typedef unsigned long int uint_fast32_t;
# 268 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef int32_t intmax_t;
# 282 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\stdint.h" 3
typedef uint32_t uintmax_t;






typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 4 "../gbs8/bsp/inc\\gbs8_algo.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\math.h" 1 3



# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\__unsupported.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\math.h" 2 3
# 30 "C:\\Program Files\\Microchip\\xc8\\v2.20\\pic\\include\\c90\\math.h" 3
extern double fabs(double);
extern double floor(double);
extern double ceil(double);
extern double modf(double, double *);
extern double sqrt(double);
extern double atof(const char *);
extern double sin(double) ;
extern double cos(double) ;
extern double tan(double) ;
extern double asin(double) ;
extern double acos(double) ;
extern double atan(double);
extern double atan2(double, double) ;
extern double log(double);
extern double log10(double);
extern double pow(double, double) ;
extern double exp(double) ;
extern double sinh(double) ;
extern double cosh(double) ;
extern double tanh(double);
extern double eval_poly(double, const double *, int);
extern double frexp(double, int *);
extern double ldexp(double, int);
extern double fmod(double, double);
extern double trunc(double);
extern double round(double);
# 5 "../gbs8/bsp/inc\\gbs8_algo.h" 2
# 16 "../gbs8/bsp/inc\\gbs8_algo.h"
uint8_t Read_Binary(uint8_t dec, uint8_t num);


uint16_t Register_Joint(uint8_t regH, uint8_t regL);







void Reg10_Decouple(uint8_t* regH, uint8_t* regL, uint16_t reg);
# 1 "../gbs8/bsp/scr/gbs8_algo.c" 2




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
