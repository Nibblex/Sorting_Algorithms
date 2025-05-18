#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#define MAX_THRESH 15

#include <stdbool.h>

#include "../helpers/sort_helpers.h"

#define NUM_COUNTERS 6

/**
 * @brief Typedef for a function pointer that takes an integer array and its length as
 * input and sorts the array.
 *
 */
typedef void (*sorting_func)(int a[], size_t length, double* counters);

/**
 * @brief A struct that holds the results of a sorting algorithm run.
 *
 * This struct contains the counters used during the run and the results of the tests.
 */
struct run
{
  double counters[NUM_COUNTERS]; /**< The counters used during the run. */
  char* sorted;                  /**< The result of testing if the array is sorted. */
  char* permuted; /**< The result of testing if the array is a permutation of the
                     original array. */
};

/**
 * @brief A struct representing a sorting algorithm.
 *
 */
struct algorithm
{
  char* name;     /**< Name of the algorithm */
  sorting_func f; /**< Function pointer to the algorithm */
  struct run run; /**< The results of running the algorithm */
};

/* Sorting algorithms */

void
binsort(int a[], size_t length, double* counters);

void
heapsort(int a[], size_t length, double* counters);

void
introsort(int a[], size_t length, double* counters);

void
isort(int a[], size_t length, double* counters);

void
mergesort(int a[], size_t length, double* counters);

void
quicksort(int a[], size_t length, double* counters);

void
quicksort_std(int a[], size_t length, double* counters);

void
selection_sort(int a[], size_t length, double* counters);

void
shellsort(int a[], size_t length, double* counters);

void
timsort(int a[], size_t length, double* counters);

#endif
