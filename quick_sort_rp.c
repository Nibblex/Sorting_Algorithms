#include "sort_helpers.h"


static unsigned int get_random_pivot(int a[], unsigned int izq, unsigned int der) {
    unsigned int pivot;
    srand(time(NULL));
    pivot = (rand() % (der-izq+1)) + izq;
    swap(a, izq, pivot);
    return (pivot = izq);
}

static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    unsigned int pivot, i = izq, j = der;
    pivot = get_random_pivot(a, izq, der);
    while (i <= j) {
        if (goes_before(a[i], a[pivot])) {
            i++;
        } else {
            swap(a, i, j);
            j--;
        }
    }
    swap(a, j, pivot);
    return (pivot = j);
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int pivot;
    if (izq < der+1) {
        pivot = partition(a, izq, der);
        quick_sort_rec(a, izq, pivot-1);
        quick_sort_rec(a, pivot+1, der);
    }
}

void quick_sort_rp(int a[], unsigned int length) {
    quick_sort_rec(a, 0, !length ? 0 : length - 1);
}