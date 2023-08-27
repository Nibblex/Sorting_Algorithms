#ifndef COUNTER_H
#define COUNTER_H

/**
 * @brief A struct that holds counters for various operations in sorting algorithms.
 */
struct counter
{
    long unsigned int cmp_counter;            /**< Counter for number of comparisons */
    long unsigned int swap_counter;           /**< Counter for number of swaps */
    long unsigned int recursion_counter;      /**< Counter for number of recursive calls */
    long unsigned int insertion_sort_counter; /**< Counter for number of times insertion sort is used */
    long unsigned int heapsort_counter;       /**< Counter for number of times heapsort is used */
};

/**
 * @brief Initializes the counters in the given counter struct.
 *
 * @param c Pointer to the counter struct to be initialized.
 */
void counter_init(struct counter *c);

/**
 * @brief Prints the values of the counters in the given counter struct.
 *
 * @param c Pointer to the counter struct to be printed.
 */
void counter_print(struct counter *c);

#endif
