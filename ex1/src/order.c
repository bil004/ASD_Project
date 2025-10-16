#include <stdlib.h>
#include <string.h>

#include "../include/sort.h"

int compar(const void *e1, const void *e2) { 
    const int *s1 = (const int *)e1;
    const int *s2 = (const int *)e2;
    
    if (*s1 > *s2) return 1;
    if (*s1 < *s2) return -1;
    return 0;
}

int compar_name(const void *e1, const void *e2) {
    const Records *r1 = (const Records *)e1;
    const Records *r2 = (const Records *)e2;
    return strcmp(r1->name, r2->name);
}

int compar_integerNum(const void *e1, const void *e2) {
    const Records *r1 = (const Records *)e1;
    const Records *r2 = (const Records *)e2;
    return (r1->integerNum - r2->integerNum);
}

int compar_floatNum(const void *e1, const void *e2) {
    const Records *r1 = (const Records *)e1;
    const Records *r2 = (const Records *)e2;
    if (r1->floatNum < r2->floatNum) return -1;
    if (r1->floatNum > r2->floatNum) return 1;
    return 0;
}


void swap(void *a, void *b, size_t size) {
    if (a == NULL || b == NULL) return;
    void *temp = malloc(size);
    if (temp == NULL) return;
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

int median_of_three(void *base, int low, int high, size_t size, int (*compar)(const void*, const void*)) {
    char *arr = (char *)base;
    int mid = low + (high - low) / 2;

    if (compar(arr + low * size, arr + mid * size) > 0)
        swap(arr + low * size, arr + mid * size, size);
    
    if (compar(arr + low * size, arr + high * size) > 0)
        swap(arr + low * size, arr + high * size, size);
    
    if (compar(arr + mid * size, arr + high * size) > 0)
        swap(arr + mid * size, arr + high * size, size);

    swap(arr + mid * size, arr + high * size, size);
    return high;
}

int partition(void *base, int low, int high, size_t size, int (*compar)(const void*, const void*)) {
    char *arr = (char *)base;

    int pivotIndex = median_of_three(base, low, high, size, compar);
    void *pivot = arr + pivotIndex * size;

    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (compar(arr + i * size, pivot) < 0);

        do {
            j--;
        } while (compar(arr + j * size, pivot) > 0);

        if (i >= j)
            return j;

        swap(arr + i * size, arr + j * size, size);
    }
}

void q_sort(void *base, int low, int high, size_t size, int (*compar)(const void*, const void*)) {
    if (low < high) {
        int pivot = partition(base, low, high, size, compar);

        q_sort(base, low, pivot, size, compar);     
        q_sort(base, pivot + 1, high, size, compar); 
    }
}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (nitems <= 1) return;
    q_sort(base, 0, nitems - 1, size, compar);
}

void merge(void *base, size_t size, int (*compar)(const void*, const void*), size_t left, size_t mid, size_t right) {
    size_t e1 = mid - left + 1;
    size_t e2 = right - mid;

    void *sx = (void*)malloc(e1 * size);
    void *dx = (void*)malloc(e2 * size);
    if (dx == NULL || sx == NULL) {
        free(dx);
        free(sx);
        return;
    }

    memcpy(sx, (char*)base + left * size, e1 * size);
    memcpy(dx, (char*)base + (mid + 1) * size, e2 * size);

    size_t i = 0, j = 0, k = left;
    while (i < e1 && j < e2) {
        if (compar((char*)sx + i * size, (char*)dx + j * size) <= 0) {
            memcpy((char*)base + k * size, (char*)sx + i * size, size);
            i++;
        } 
        else {
            memcpy((char*)base + k * size, (char*)dx + j * size, size);
            j++;
        }
        k++;
    }

    while (i < e1) {
        memcpy((char*)base + k * size, (char*)sx + i * size, size);
        i++;
        k++;
    }

    while (j < e2) {
        memcpy((char*)base + k * size, (char*)dx + j * size, size);
        j++;
        k++;
    }
    free(dx);
    free(sx);
}


void merge_sortR(void *base, size_t size, int (*compar)(const void*, const void*), size_t left, size_t right) {
    if (left >= right) return;
    
    size_t mid = left + (right - left) / 2;
    merge_sortR(base, size, compar, left, mid);
    merge_sortR(base, size, compar, mid + 1, right);
    merge(base, size, compar, left, mid, right);
}


void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (nitems > 1) merge_sortR(base, size, compar, 0, nitems - 1);
}