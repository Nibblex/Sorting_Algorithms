#include <stdlib.h>
#include <time.h>

#include "../helpers/sort_helpers.h"
#include "../xoroshiro128plus.h"

#include "arraygen.h"

int *arraygen(unsigned long int length, long int min, long int max, int options)
{
    xrshr128p_state_t state = xrshr128p_init(time(NULL));
    int sign = (options & NEG) ? -1 : 1;

    int *array = malloc(length * sizeof(long int));
    for (unsigned long int i = 0; i < length; i++)
    {
        sign = (options & BOTH) ? (rand_pos(state, 0, 1) ? 1 : -1) : sign;
        array[i] = rand_pos(state, min, max) * sign;
    }

    if (options & ASC)
    {
        qsort(array, length, sizeof(long int), cmp);
    }
    else if (options & DESC)
    {
        qsort(array, length, sizeof(long int), cmp_desc);
    }

    return array;
}
