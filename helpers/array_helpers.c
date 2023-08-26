#include <string.h>

#include "array_helpers.h"

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

int *array_copy(int array[], unsigned int length)
{
    int *copy = malloc(length * sizeof(int));
    memcpy(copy, array, length * sizeof(int));
    return copy;
}

void array_dump(int a[], unsigned int length)
{
    fprintf(stdout, "Input length: %u\n", length);
    for (unsigned int i = 0; i < length; i++)
    {
        fprintf(stdout, "%i", a[i]);
        fprintf(stdout, (i < length - 1) ? " " : "\n");
    }
    fprintf(stdout, "\n");
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

int *array_from_file(unsigned int length, const char *filepath)
{
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    int res;
    int *array = malloc(length * sizeof(int));
    unsigned int i = 0;
    while (i < length + 1)
    {
        res = fscanf(file, " %u ", array + i - (i != 0));
        if (res != 1)
        {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    fclose(file);
    return array;
}

unsigned int array_length_from_file(const char *filepath)
{
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int size = 0;
    int res = fscanf(file, " %u ", &size);
    if (res != 1)
    {
        fprintf(stderr, "Invalid array.\n");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return size;
}
