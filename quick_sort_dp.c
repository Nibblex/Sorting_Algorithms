#include "sort_helpers.h"


typedef struct pivotes {
    unsigned int pivot, pivot_izq, pivot_der;
} pivotes_t;

static pivotes_t partition(int a[], unsigned int izq, unsigned int der) {
    pivotes_t p;
    p.pivot = izq;
    unsigned int i = izq+1, j = der, k = 0;
    while (i <= j) {
        if (!goes_before(a[p.pivot], a[i])) {
            swap(a, i, i-k);
            i++;
        } else if (a[i] == a[p.pivot]) {
            k++;
            i++;
        } else {
            swap(a, i, j);
            j--;
        }
    }
    swap(a, j-k, p.pivot);
    p.pivot_der = j;
    p.pivot_izq = p.pivot_der-k;
    return p;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    pivotes_t p;
    if (izq < der+1) {
        p = partition(a, izq, der);
        quick_sort_rec(a, izq, p.pivot_izq-1);
        quick_sort_rec(a, p.pivot_der+1, der);
    }
}

void quick_sort_dp(int a[], unsigned int length) {
    quick_sort_rec(a, 0, !length ? 0 : length - 1);
}