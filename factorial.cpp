#include "factorial.h"

int factorial(const int val)
{
    if(val < 0)
        return 0; // TODO: is it valid??
    if(val == 0)
        return 1;
    return val * factorial(val - 1);
}