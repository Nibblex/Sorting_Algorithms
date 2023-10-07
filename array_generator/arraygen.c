#include <stdlib.h>
#include <time.h>

#include "../helpers/sort_helpers.h"

#include "arraygen.h"

static inline int pos_sign(xrshr128p_state_t state)
{
    state = state;
    return 1;
}

static inline int neg_sign(xrshr128p_state_t state)
{
    state = state;
    return -1;
}

static inline int both_sign(xrshr128p_state_t state)
{
    return rand_pos(state, 0, 1) ? 1 : -1;
}

static sign_func sign_func_ptr(enum sign_type sign)
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

static inline int cmp_desc(const void *a, const void *b)
{
    return cmp(b, a);
}

int *arraygen(struct array_config *config)
{
    int *array;
    sign_func sign;
    xrshr128p_state_t state;

    array = malloc(config->length * sizeof(int));
    sign = sign_func_ptr(config->sign);
    state = xrshr128p_init(time(NULL));

    for (size_t i = 0; i < config->length; ++i)
    {
        array[i] = sign(state) * rand_pos(state, config->min, config->max);
    }

    if (config->order != UNS)
    {
        qsort(array, config->length, sizeof(int), config->order == ASC ? cmp : cmp_desc);
    }

    return array;
}
