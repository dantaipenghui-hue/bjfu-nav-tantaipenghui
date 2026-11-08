#include "swap.hpp"

void swapByValue(int a, int b)
{
    int t = a;
    a = b;
    b = t;
}

void swapByPointer(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void swapByReference(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
