#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "func.h"

long double func_sigmoid(long double x)
{
    return 1 / (1 + exp(-x));
}

long double func_derivative_sigmoid(long double x)
{
    return x / (1 - x);
}

int func_random_from_range(int min, int max)
{
    return (rand() %
            (max - min + 1)) +
           min;
}