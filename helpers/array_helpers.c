#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_helpers.h"
#include "sort_helpers.h"

unsigned long int array_from_stdin(int *a[])
{
    long int tmp_size;
    unsigned long int size;

    // Read array size
    if (scanf("%ld", &tmp_size) != 1)
    {
        fprintf(stderr, "Error reading size from input.\n");
        exit(EXIT_FAILURE);
    }

    // Check if size is valid
    if (tmp_size < 0)
    {
        fprintf(stderr, "Array size must be a positive integer, got %ld.\n", tmp_size);
        exit(EXIT_FAILURE);
    }

    size = (unsigned long int)tmp_size;

    // Allocate memory for array
    *a = (int *)malloc(size * sizeof(int));
    if (*a == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read array elements
    for (unsigned long int i = 0; i < size; i++)
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

void array_dump(int a[], unsigned int length)
{
    for (unsigned int i = 0; i < length; i++)
    {
        printf("%i", a[i]);
        printf((i < length - 1) ? " " : "\n");
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int *array_copy(int array[], unsigned int length)
{
    int *copy = malloc(length * sizeof(int));
    memcpy(copy, array, length * sizeof(int));
    return copy;
}

bool array_is_sorted(int a[], unsigned int length)
{
    unsigned int i = 1;
    while (i < length && cmp(a + i - 1, a + i) <= 0)
    {
        i++;
    }

    return !length || i == length;
}

static unsigned int array_value_count(int a[], unsigned int length, int value)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        if (a[i] == value)
        {
            count++;
        }
    }
    return count;
}

bool array_is_permutation_of(int a[], int b[], unsigned int length)
{
    unsigned int i = 0;
    bool result = true;
    while (i < length && result)
    {
        unsigned int a_count = array_value_count(a, length, a[i]);
        unsigned int b_count = array_value_count(b, length, a[i]);
        result = (a_count == b_count);
        i++;
    }
    return result;
}
