#ifndef _WORKBENCH_H
#define _WORKBENCH_H

#include <stdbool.h>

#include "../algorithms/algorithms.h"

#define NUM_ALGORITHMS 9
#define NUM_TESTS 2

/**
 * @brief A struct representing a test case for sorting algorithms.
 *
 */
struct test
{
    char *name;    /**< The name of the test case. */
    enum test_type /**< The type of the test case. */
    {
        SORTED,  /**< The test case is sorted. */
        PERMUTED /**< The test case is a permutation of the original array. */
    } type;
    bool enabled; /**< A flag indicating whether the test case is enabled. */
};

/**
 * @brief A struct that holds the results of a sorting algorithm run.
 *
 * This struct contains the name of the algorithm, the elapsed time, the counters used during the run,
 * and the results of the tests.
 */
struct run
{
    char *algorithm_name;    /**< The name of the sorting algorithm used. */
    double elapsed;          /**< The elapsed time of the sorting algorithm run. */
    struct counter counters; /**< The counters used during the sorting algorithm run. */
    char *sorted;            /**< The result of testing if the array is sorted. */
    char *permuted;          /**< The result of testing if the array is a permutation of the original array. */
};

/**
 * @brief A struct representing a workbench for sorting algorithms.
 *
 */
struct workbench
{
    int *array;                                  /**< A pointer to the array to be sorted. */
    size_t array_length;                         /**< The length of the array to be sorted. */
    struct algorithm algorithms[NUM_ALGORITHMS]; /**< An array of algorithms to be tested. */
    struct test tests[NUM_TESTS];                /**< An array of tests to be run. */
    struct run runs[NUM_ALGORITHMS];             /**< An array of runs for each algorithm. */
    char *format;                                /**< The format in which the results should be displayed. */
    int sort_by;                                 /**< The column to sort the results by. */
    bool dump_array;                             /**< A flag indicating whether to dump the array before and after sorting. */
};

/**
 * Runs the given workbench.
 *
 * @param wb The workbench to run.
 */
void workbench_run(struct workbench *wb);

/**
 * @brief Frees the memory allocated for a workbench.
 *
 * @param wb Pointer to the workbench to be freed.
 */
void workbench_free(struct workbench *wb);

#endif
