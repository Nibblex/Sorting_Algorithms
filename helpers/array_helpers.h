#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>

typedef int (*compare_func)(const void*, const void*, void*);

/**
 * Each element is read from stdin and stored in the array 'a'.
 * The array is dynamically allocated, so it must be freed after use.
 *
 * input format:
 *
 * <array_length>
 * <array_elem_1> <array_elem_2> <array_elem_3> ... <array_elem_N>
 *
 * In other words, the first line must be the array length, and the next line
 * must contain 'length' amount of elements separated by one or more
 * blank characters.
 *
 * Those elements are copied into the array 'a'.
 * The array_length must be lower or equal to the quantity of elements
 *
 * Returns the length of the array.
 *
 * @param a The array to store the elements in.
 * @return The length of the array.
 */
size_t
array_from_stdin(int* a[]);

/**
 * Prints the contents of an integer array to the console.
 *
 * @param a The integer array to be printed.
 * @param length The length of the integer array.
 */
void
array_dump(int a[], size_t length);

/**
 * Creates a copy of an integer array.
 *
 * @param src The source array to copy.
 * @param length The length of the source array.
 * @return A pointer to the newly created copy of the source array.
 */
int*
array_copy(int src[], size_t length);

/**
 * Checks if an array is sorted in ascending order.
 *
 * @param a The array to check.
 * @param length The length of the array.
 * @return true if the array is sorted in ascending order, false otherwise.
 */
bool
array_is_sorted(int a[], size_t length, compare_func cmp);

/**
 * Checks if an array is a permutation of another array.
 *
 * @param a The first array to compare.
 * @param b The second array to compare.
 * @param length The length of the arrays.
 * @return true if the arrays are permutations of each other, false otherwise.
 */
bool
array_is_permutation_of(int a[], int b[], size_t length, compare_func cmp);

#endif
