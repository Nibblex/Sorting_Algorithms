#include <time.h>

#include "../helpers/sort_helpers.h"
#include "algorithms.h"

void quicksort(int a[], size_t length)
{
    if (length < 2)
        return;

    xrshr128p_state_t state = xrshr128p_init(time(NULL));

    int top = -1;
    size_t stack[length];
    size_t pivot, left = 0, right = length - 1;
    size_t segment_length;

    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0)
    {
        right = stack[top--];
        left = stack[top--];

        segment_length = right - left + 1;
        if (segment_length < MAX_THRESH)
        {
            insertion_sort(a + left, segment_length);
            continue;
        }

        pivot = partition(a, left, right, MID, &state);

        if (pivot > left + 1)
        {
            stack[++top] = left;
            stack[++top] = pivot;
        }

        if (pivot < right - 1)
        {
            stack[++top] = pivot + 1;
            stack[++top] = right;
        }
    }
}
