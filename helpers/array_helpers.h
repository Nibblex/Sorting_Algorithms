#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include "sort_helpers.h"

int *array_from_file(unsigned int length, const char *filepath);
/*
    Each element is read from the file located at 'filepath'.
    The file must exist in disk and must have its contents in the following
    format:

    <array_length>
    <array_elem_1> <array_elem_2> <array_elem_3> ... <array_elem_N>

    In other words, the first line must be the array length, and the next line
    must contain 'length' amount of elements separated by one or more
    blank characters.

    Those elements are copied into the array 'a'.
    The array_length must be lower or equal to 'max_size'.

    Returns the length of the array.
*/

unsigned int array_length_from_file(const char *filepath);

int *array_copy(int src[], unsigned int length);

bool array_is_sorted(int a[], unsigned int length);

bool array_is_permutation_of(int a[], int other[], unsigned int length);

void array_dump(int a[], unsigned int length);

#endif
