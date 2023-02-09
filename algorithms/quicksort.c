#include <time.h>

#include "../helpers/sort_helpers.h"

void quicksort(int a[], unsigned int length)
{
    if (length < 2)
        return;

    xrshr128p_state_t state = xrshr128p_init(time(NULL));

    int top = -1;
    unsigned int stack[length];
    unsigned int pivot, left = 0, right = length - 1;

    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0)
    {
        right = stack[top--];
        left = stack[top--];

        if (right - left < MAX_THRESH)
        {
            insertion_sort(a + left, right - left + 1);
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
