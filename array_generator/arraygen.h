#ifndef _ARRAYGEN_H
#define _ARRAYGEN_H

#include "../algorithms/xoroshiro128plus.h"

/**
 * @brief Enumeration for the order type of the elements in the array.
 *
 */
enum order_type
{
    ASC,  /**< Ascending order */
    DESC, /**< Descending order */
    UNS   /**< Unsorted order */
};

/**
 * @brief Enumeration for the sign type of the elements in the array.
 *
 */
enum sign_type
{
    POS, /**< Positive sign */
    NEG, /**< Negative sign */
    BOTH /**< Both positive and negative signs */
};

typedef int (*sign_func)(xrshr128p_state_t state);

struct array_config
{
    size_t length;
    int min;
    int max;
    enum order_type order;
    enum sign_type sign;
};

/**
 * Generates an array of integers based on the given configuration.
 *
 * @param config The configuration for the array generation.
 * @return A pointer to the generated array.
 *
 * @note The caller is responsible for freeing the memory allocated for the array.
 */
int *arraygen(struct array_config *config);

#endif
