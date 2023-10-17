#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#define MAX_THRESH 15

#include <stdbool.h>

#include "../helpers/sort_helpers.h"

/**
 * @brief Typedef for a function pointer that takes an integer array and its length as input and sorts the array.
 *
 */
typedef void (*sorting_func)(int a[], size_t length, double *counters);

/**
 * @brief A struct representing a sorting algorithm.
 *
 */
struct algorithm
{
    char *name;     /**< Name of the algorithm */
    sorting_func f; /**< Function pointer to the algorithm */
};

/* Sorting algorithms */

void binsort(int a[], size_t length, double *counters);

void heapsort(int a[], size_t length, double *counters);

void introsort(int a[], size_t length, double *counters);

void isort(int a[], size_t length, double *counters);

void mergesort(int a[], size_t length, double *counters);

void quicksort(int a[], size_t length, double *counters);

void quicksort_std(int a[], size_t length, double *counters);

void selection_sort(int a[], size_t length, double *counters);

void shellsort(int a[], size_t length, double *counters);

void timsort(int a[], size_t length, double *counters);

#endif
