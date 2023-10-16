#include <time.h>

#include "algorithms.h"

typedef struct
{
    int *lo;
    int *hi;
} stack_node;

#define PUSH(low, high) ((top->lo = (low)), (top->hi = (high)), ++top)
#define POP(low, high) (--top, (low = top->lo), (high = top->hi))
#define STACK_NOT_EMPTY (stack < top)

void quicksort(int a[], size_t length, struct counter *counters)
{
    xrshr128p_state_t state = xrshr128p_init(time(NULL));

    stack_node stack[2 * log2(length)];
    stack_node *top = stack;

    int *pivot, *lo = a, *hi = a + length - 1;
    size_t segment_length;

    PUSH(lo, hi);

    while (STACK_NOT_EMPTY)
    {
        POP(lo, hi);

        segment_length = (size_t)(hi - lo + 1);
        if (segment_length < MAX_THRESH)
        {
            isort(lo, segment_length, counters);
            continue;
        }

        pivot = partition(lo, hi, MID, &state, counters);

        if (pivot > lo + 1)
        {
            PUSH(lo, pivot);
        }

        if (pivot < hi - 1)
        {
            PUSH(pivot + 1, hi);
        }
    }
}
