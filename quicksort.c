#include "./helpers/sort_helpers.h"

static unsigned int partition(int a[], unsigned int left, unsigned int right)
{
    unsigned int pivot = left;
    int pivot_value = a[pivot];
    while (left <= right)
    {
        if (cmp(a + left, &pivot_value) <= 0)
        {
            left++;
        }
        else
        {
            swap(a, left, right--);
        }
    }

    return swap(a, right, pivot);
}

static void quicksort_rec(int a[], unsigned int left, unsigned int right)
{
    unsigned int pivot, length = right - left + 1;
    if (length < CHUNK_SIZE)
    {
        insertion_sort(a + left, length);
    }
    else
    {
        pivot = partition(a, left, right);
        quicksort_rec(a, left, pivot - 1);
        quicksort_rec(a, pivot + 1, right);
    }
}

void quicksort(int a[], unsigned int length)
{
    quicksort_rec(a, 0, !length ? 0 : length - 1);
}
