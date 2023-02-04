#include <time.h>

#include "./helpers/sort_helpers.h"

#include "xoroshiro128plus.h"

#define rand_pos(state, left, right) (xrshr128p_next(state) % ((right) - (left) + 1)) + (left)

#define pivot_selection(a, left, right, state)             \
    ({                                                  \
        unsigned int pivot = rand_pos(state, left, right); \
        swap(a, left, pivot);                            \
    })

static unsigned int partition(int a[], unsigned int left, unsigned int right, xrshr128p_state_t *state)
{
    unsigned int pivot = pivot_selection(a, left, right, *state);
    int pivot_value = a[pivot];
    while (left <= right)
    {
        if (cmp(a[left], pivot_value) <= 0)
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
        pivot = partition(a, left, right, state);
        quicksort_rec(a, left, pivot - 1, state);
        quicksort_rec(a, pivot + 1, right, state);
    }
}

void quicksort_rp(int a[], unsigned int length)
{
    xrshr128p_state_t state = xrshr128p_init(time(NULL));
    quicksort_rec(a, 0, !length ? 0 : length - 1, &state);
}
