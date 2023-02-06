#include <time.h>

#include "./helpers/sort_helpers.h"

#include "xoroshiro128plus.h"

enum
{
    LEFT_MOST,
    RANDOM,
    MED3,
} pivot_type;

#define med3(arr, a, b, c)                                                                                                              \
    ({                                                                                                                                  \
        int _a = arr[a], _b = arr[b], _c = arr[c];                                                                                      \
        (_cmp(_a, _b) > 0 ? (_cmp(_b, _c) > 0 ? b : (_cmp(_a, _c) > 0 ? c : a)) : (_cmp(_a, _c) > 0 ? a : (_cmp(_b, _c) > 0 ? c : b))); \
    })

#define rand_pos(state, left, right) (xrshr128p_next(state) % ((right) - (left) + 1)) + (left)

#define pivot(a, left, right, state, type)         \
    ({                                             \
        unsigned int mid, pivot;                   \
        switch (type)                              \
        {                                          \
        case LEFT_MOST:                            \
            pivot = left;                          \
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

static unsigned int partition(int a[], unsigned int left, unsigned int right, unsigned int pivot)
{
    pivot = swap(a, left, pivot);
    int pivot_value = a[pivot];
    while (left <= right)
    {
        if (cmp(a + left, &pivot_value) <= 0)
        {
            left++;
        }
        else
        {
            swap(a, left, right--);
        }
    }

    return swap(a, right, pivot);
}

static void quicksort_rec(int a[], unsigned int left, unsigned int right, xrshr128p_state_t *state)
{
    unsigned int pivot, length = right - left + 1;
    if (length < CHUNK_SIZE)
    {
        insertion_sort(a + left, length);
    }
    else
    {
        pivot = pivot(a, left, right, state, MED3);
        pivot = partition(a, left, right, pivot);
        quicksort_rec(a, left, pivot - 1, state);
        quicksort_rec(a, pivot + 1, right, state);
    }
}

void quicksort(int a[], unsigned int length)
{
    xrshr128p_state_t state = xrshr128p_init(time(NULL));
    quicksort_rec(a, 0, !length ? 0 : length - 1, &state);
}
