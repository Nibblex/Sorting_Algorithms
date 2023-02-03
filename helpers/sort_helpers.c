#include "sort_helpers.h"

void reset_counters(void)
{
    swap_counter = 0;
    goesb_counter = 0;
}

bool goes_before(int x, int y)
{
    goesb_counter++;

    return abs(x) <= abs(y);
}

unsigned int swap(int a[], unsigned int i, unsigned int j)
{
    swap_counter++;

    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;

    return i;
}
