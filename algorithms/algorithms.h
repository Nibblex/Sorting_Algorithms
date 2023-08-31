#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

typedef void (*sorting_func)(int a[], size_t length);

struct algorithm
{
    char *name;
    sorting_func f;
};

#define PRINT_ALGORITHMS                       \
    do                                         \
    {                                          \
        struct algorithm *alg = algorithms;    \
        printf("\tAvailable algorithms:\n\t"); \
        while (alg->name != NULL)              \
        {                                      \
            printf("%s", alg->name);           \
            alg++;                             \
            if (alg->name != NULL)             \
            {                                  \
                printf(", ");                  \
            }                                  \
        }                                      \
        printf("\n");                          \
    } while (0)

#define SET_FIRST_ALGORITHM(algorithm_name)             \
    do                                                  \
    {                                                   \
        struct algorithm *alg = algorithms;             \
        while (alg->name != NULL)                       \
        {                                               \
            if (strcmp(alg->name, algorithm_name) == 0) \
            {                                           \
                algorithms[0] = *alg;                   \
                algorithms[1].name = NULL;              \
                break;                                  \
            }                                           \
            alg++;                                      \
        }                                               \
    } while (0)

/* Sorting algorithms */

void insertion_sort(int a[], size_t length);

void selection_sort(int a[], size_t length);

void quicksort(int a[], size_t length);

void quicksort_std(int a[], size_t length);

void mergesort(int a[], size_t length);

void timsort(int a[], size_t length);

void shellsort(int a[], size_t length);

void heapsort(int a[], size_t length);

void introsort(int a[], size_t length);

#endif
