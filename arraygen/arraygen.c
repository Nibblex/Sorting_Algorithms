#include <stdlib.h>
#include <time.h>

#include "../helpers/sort_helpers.h"

#include "arraygen.h"

static inline int pos_sign(xrshr128p_state_t state)
{
    return 1;
}

static inline int neg_sign(xrshr128p_state_t state)
{
    return -1;
}

static inline int both_sign(xrshr128p_state_t state)
{
    return rand_pos(state, 0, 1) ? 1 : -1;
}

static inline sign_func sign_func_ptr(sign_type sign)
{
    switch (sign)
    {
    case POS:
        return pos_sign;
    case NEG:
        return neg_sign;
    case BOTH:
        return both_sign;
    default:
        return pos_sign;
    }
}

int *arraygen(struct array_config *config)
{
    xrshr128p_state_t state = xrshr128p_init(time(NULL));
    sign_func sign_f = sign_func_ptr(config->sign);
    int *array;
    int elem;

    array = malloc(config->length * sizeof(int));

    for (size_t i = 0; i < config->length; i++)
    {
        elem = rand_pos(state, config->min, config->max) * sign_f(state);
        array[i] = elem;
    }

    if (config->order != UNS)
    {
        qsort(array, config->length, sizeof(int), config->order == ASC ? cmp : cmp_desc);
    }

    return array;
}
