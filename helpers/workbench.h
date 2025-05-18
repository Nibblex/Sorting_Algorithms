#ifndef _WORKBENCH_H
#define _WORKBENCH_H

#include <stdbool.h>

#include "../algorithms/algorithms.h" // struct algorithm

#define NUM_ALGORITHMS 10
#define NUM_TESTS 2

/**
 * @brief A struct representing a test case for sorting algorithms.
 *
 */
struct test
{
  char* name;    /**< The name of the test case. */
  enum test_type /**< The type of the test case. */
  {
    SORTED,  /**< The test case is sorted. */
    PERMUTED /**< The test case is a permutation of the original array. */
  } type;
};

/**
 * @brief A struct representing a workbench for sorting algorithms.
 *
 */
struct workbench
{
  int* array;          /**< A pointer to the array to be sorted. */
  size_t array_length; /**< The length of the array to be sorted. */

  struct algorithm
    algorithms[NUM_ALGORITHMS]; /**< An array of algorithms to be tested. */
  size_t nalgorithms;           /**< The number of algorithms to be tested. */

  struct test tests[NUM_TESTS]; /**< An array of tests to be run. */
  size_t ntests;                /**< The number of tests to be run. */

  char* format;    /**< The format in which the results should be displayed. */
  int sort_by;     /**< The column to sort the results by. */
  bool dump_array; /**< A flag indicating whether to dump the array before and after
                      sorting. */
};

/**
 * Runs the given workbench.
 *
 * @param wb The workbench to run.
 */
void
wb_run(struct workbench* wb);

/**
 * @brief Frees the memory allocated for a workbench.
 *
 * @param wb Pointer to the workbench to be freed.
 */
void
wb_free(struct workbench* wb);

#endif
