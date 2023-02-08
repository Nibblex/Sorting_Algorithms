#include <time.h>

#include "../helpers/sort_helpers.h"

#include "../xoroshiro128plus.h"

enum
{
    LEFT_MOST,
    RANDOM,
    MED3,
    MID,
} pivot_type;

#define med3(arr, a, b, c)                                                                                                              \
    ({                                                                                                                                  \
        int _a = arr[a], _b = arr[b], _c = arr[c];                                                                                      \
        (_cmp(_a, _b) > 0 ? (_cmp(_b, _c) > 0 ? b : (_cmp(_a, _c) > 0 ? c : a)) : (_cmp(_a, _c) > 0 ? a : (_cmp(_b, _c) > 0 ? c : b))); \
    })

#define rand_pos(state, left, right) (xrshr128p_next(state) % ((right) - (left) + 1)) + (left)

#define pivot(a, left, right, state, type)         \
    ({                                             \
        unsigned int pivot, mid;                   \
        switch (type)                              \
        {                                          \
        case LEFT_MOST:                            \
            pivot = left;                          \
            break;                                 \
        case MID:                                  \
            pivot = left + ((right - left) >> 1);  \
            break;                                 \
        case RANDOM:                               \
            pivot = rand_pos(*state, left, right); \
            break;                                 \
        case MED3:                                 \
            mid = left + ((right - left) >> 1);    \
            pivot = med3(a, left, mid, right);     \
            break;                                 \
        }                                          \
        pivot;                                     \
    })

static unsigned int partition(int a[], unsigned int left, unsigned int right, xrshr128p_state_t *state)
{
    unsigned int pivot = pivot(a, left, right, state, MID);
    int pivot_value = a[pivot];

    unsigned int i = left - 1;
    unsigned int j = right + 1;

    while (1)
    {
        do
            i++;
        while (cmp(a + i, &pivot_value) < 0);

        do
            j--;
        while (cmp(a + j, &pivot_value) > 0);

        if (i >= j)
        {
            return j;
        }

        swap(a, i, j);
    }
}

static void quicksort_it(int a[], unsigned int length)
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

        pivot = partition(a, left, right, &state);

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

void quicksort(int a[], unsigned int length)
{
    quicksort_it(a, length);
}
