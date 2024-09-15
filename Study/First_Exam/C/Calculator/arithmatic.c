#include "arithmatic.h"

float add(float a, float b) 
{
    return a + b;
}

float subtract(float a, float b)
{
    return a - b;
}

float multiply(float a, float b)
{
    return a * b;
}

float divide(float a, float b)
{
    if (b == 0)
    {
        printf("Cannot divide by 0");
        exit(1);
    }

    return a / b;
}
