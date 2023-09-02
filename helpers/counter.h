#ifndef _COUNTER_H
#define _COUNTER_H

#include <stdlib.h>

/**
 * @brief A struct that holds counters for various operations in sorting algorithms.
 */
struct counter
{
    size_t cmp_counter;            /**< Counter for number of comparisons */
    size_t swap_counter;           /**< Counter for number of swaps */
    size_t recursion_counter;      /**< Counter for number of recursive calls */
    size_t insertion_sort_counter; /**< Counter for number of times insertion sort is used */
    size_t heapsort_counter;       /**< Counter for number of times heapsort is used */
};

/**
 * @brief Initializes the counters in the given counter struct.
 *
 * @param c Pointer to the counter struct to be initialized.
 */
void counter_init(struct counter *c);

#endif
