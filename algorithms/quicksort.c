#include <time.h>

#include "../helpers/sort_helpers.h"
#include "algorithms.h"

void quicksort(int a[], size_t length)
{
    if (length == 0)
        return;

    xrshr128p_state_t state = xrshr128p_init(time(NULL));

    int top = -1;
    size_t stack[length];
    size_t pivot, lo = 0, hi = length - 1;
    size_t segment_length;

    stack[++top] = lo;
    stack[++top] = hi;

    while (top >= 0)
    {
        hi = stack[top--];
        lo = stack[top--];

        segment_length = hi - lo + 1;
        if (segment_length < MAX_THRESH)
        {
            insertion_sort(a + lo, segment_length);
            continue;
        }

        pivot = partition(a, lo, hi, MID, &state);

        if (pivot > lo + 1)
        {
            stack[++top] = lo;
            stack[++top] = pivot;
        }

        if (pivot < hi - 1)
        {
            stack[++top] = pivot + 1;
            stack[++top] = hi;
        }
    }
}
