#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#define MAX_THRESH 15

#include <stdbool.h>

/**
 * @brief A struct that holds counters for various operations in sorting algorithms.
 */
struct counter
{
    size_t cmp_counter;       /**< Counter for number of comparisons */
    size_t swap_counter;      /**< Counter for number of swaps */
    size_t recursion_counter; /**< Counter for number of recursive calls */
    size_t isort_counter;     /**< Counter for number of times insertion sort is used */
    size_t heapsort_counter;  /**< Counter for number of times heapsort is used */
};

/**
 * @brief Typedef for a function pointer that takes an integer array and its length as input and sorts the array.
 *
 */
typedef void (*sorting_func)(int a[], size_t length);

/**
 * @brief A struct representing a sorting algorithm.
 *
 */
struct algorithm
{
    char *name;     /**< Name of the algorithm */
    sorting_func f; /**< Function pointer to the algorithm */
    bool enabled;   /**< Flag to indicate if the algorithm is enabled */
};

/* Sorting algorithms */

void binsort(int a[], size_t length);

void heapsort(int a[], size_t length);

void introsort(int a[], size_t length);

void isort(int a[], size_t length);

void mergesort(int a[], size_t length);

void quicksort(int a[], size_t length);

void quicksort_std(int a[], size_t length);

void selection_sort(int a[], size_t length);

void shellsort(int a[], size_t length);

void timsort(int a[], size_t length);

#endif
