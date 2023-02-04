#include <time.h>

#include "./helpers/sort_helpers.h"

#include "xoroshiro128plus.h"

#define rand_pos(state, izq, der) (xrshr128p_next(state) % ((der) - (izq) + 1)) + (izq)

#define pivot_selection(a, izq, der, state)             \
    ({                                                  \
        unsigned int pivot = rand_pos(state, izq, der); \
        swap(a, izq, pivot);                            \
    })

static unsigned int partition(int a[], unsigned int izq, unsigned int der, xrshr128p_state_t *state)
{
    unsigned int pivot = pivot_selection(a, izq, der, *state);
    int pivot_value = a[pivot];
    while (izq <= der)
    {
        if (cmp(a[izq], pivot_value) <= 0)
        {
            izq++;
        }
        else
        {
            swap(a, izq, der);
            der--;
        }
    }

    return swap(a, der, pivot);
}

static void quicksort_rec(int a[], unsigned int izq, unsigned int der, xrshr128p_state_t *state)
{
    unsigned int pivot, length = der - izq + 1;
    if (length < CHUNK_SIZE)
    {
        insertion_sort(a + izq, length);
        return;
    }

    if (izq < der + 1)
    {
        pivot = partition(a, izq, der, state);
        quicksort_rec(a, izq, pivot - 1, state);
        quicksort_rec(a, pivot + 1, der, state);
    }
}

void quicksort_rp(int a[], unsigned int length)
{
    xrshr128p_state_t state = xrshr128p_init(time(NULL));
    quicksort_rec(a, 0, !length ? 0 : length - 1, &state);
}
