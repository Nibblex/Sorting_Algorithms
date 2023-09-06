#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_helpers.h"
#include "sort_helpers.h"

size_t array_from_stdin(int *a[])
{
    int tmp_size;
    size_t size;

    // Read array size
    if (scanf("%d", &tmp_size) != 1)
    {
        fprintf(stderr, "Error reading size from input.\n");
        exit(EXIT_FAILURE);
    }

    // Check if size is valid
    if (tmp_size < 0)
    {
        fprintf(stderr, "Array size must be a positive integer, got %d.\n", tmp_size);
        exit(EXIT_FAILURE);
    }

    size = (size_t)tmp_size;

    // Allocate memory for array
    *a = (int *)malloc(size * sizeof(int));
    if (*a == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read array elements
    for (size_t i = 0; i < size; i++)
    {
        if (scanf("%d", &(*a)[i]) != 1)
        {
            fprintf(stderr, "Error reading element at index %ld.\n", i);
            free(*a);
            exit(EXIT_FAILURE);
        }
    }

    return size;
}

void array_dump(int a[], size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("%i", a[i]);
        printf((i < length - 1) ? " " : "\n");
    }
}

int *array_copy(int array[], size_t length)
{
    int *copy = malloc(length * sizeof(int));
    memcpy(copy, array, length * sizeof(int));
    return copy;
}

bool array_is_sorted(int a[], size_t length)
{
    size_t i = 1;
    while (i < length && cmp(a + i - 1, a + i) <= 0)
    {
        i++;
    }

    return !length || i == length;
}

bool array_is_permutation_of(int a[], int b[], size_t length)
{
    bool is_permutation;
    int *b_copy;

    b_copy = array_copy(b, length);

    qsort(b_copy, length, sizeof(int), cmp);

    is_permutation = memcmp(b_copy, a, length * sizeof(int)) == 0;

    free(b_copy);

    return is_permutation;
}
