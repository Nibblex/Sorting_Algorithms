#include "sort_helpers.h"


static void merge(int a[], unsigned int izq, unsigned int med, unsigned int der) {
    int tmp[der+1];
    unsigned int j = izq, k = med+1;
    for (unsigned int i = izq; i <= med; i++)
        tmp[i] = a[i];

    for (unsigned int i = izq; i <= der; i++) {
        if (j <= med && (k > der || goes_before(tmp[j], a[k]))) {
            a[i] = tmp[j];
            j++;
        } else {
            a[i] = a[k];
            k++;
        }
    }
}

static void merge_sort_rec(int a[], unsigned int izq,unsigned int der) {
    unsigned int med;
    if (der > izq) {
        med = (izq + der)/2;
        merge_sort_rec(a, izq, med);
        merge_sort_rec(a, med+1, der);
        merge(a, izq, med, der);
    }
}

void merge_sort(int a[], unsigned int length) {
    merge_sort_rec(a, 0, !length ? 0 : length - 1);
}