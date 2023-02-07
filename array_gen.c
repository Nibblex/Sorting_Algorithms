#include <stdlib.h>
#include <time.h>

#include "./helpers/sort_helpers.h"

#include "array_gen.h"
#include "xoroshiro128plus.h"

#define rand_pos(state, min, max) (xrshr128p_next(state) % ((max) - (min) + 1)) + (min)

int *array_generator(int length, int min, int max, int order_type, int sign_type)
{
    xrshr128p_state_t state = xrshr128p_init(time(NULL));
    int sign = sign_type == NEG ? -1 : 1;

    int *array = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
    {
        sign = sign_type == BOTH ? (rand_pos(state, 0, 1) ? 1 : -1) : sign;
        array[i] = rand_pos(state, min, max) * sign;
    }

    switch (order_type)
    {
    case ASC:
        qsort(array, length, sizeof(int), cmp);
        break;

    case DESC:
        qsort(array, length, sizeof(int), cmp);
        break;

    default:
        break;
    }

    return array;
}