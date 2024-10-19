#include "algo.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>


// Helper function for insertion sort for small segments
void insertion_sort(void *base, size_t left, size_t right, size_t size, int (*compar)(const void*, const void*)) {
    for (size_t i = left + 1; i <= right; i++) {
        void *key = malloc(size);
        memcpy(key, (uint8_t*)base + i * size, size);

        size_t j = i;
        while (j > left && compar((uint8_t*)base + (j - 1) * size, key) > 0) {
            memcpy((uint8_t*)base + j * size, (uint8_t*)base + (j - 1) * size, size);
            j--;
        }

        memcpy((uint8_t*)base + j * size, key, size);
        free(key);
    }
}

// Helper function to merge two halves of the array
void merge(void *base, size_t left, size_t mid, size_t right, size_t size, int (*compar)(const void*, const void*), void *temp) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    // Copy the left half to temp buffer
    memcpy(temp, (uint8_t *)base + left * size, n1 * size);

    // Pointer to the beginning of the right half
    void *R = (uint8_t *)base + (mid + 1) * size;

    size_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (compar((uint8_t *)temp + i * size, (uint8_t *)R + j * size) <= 0) {
            memcpy((uint8_t *)base + k * size, (uint8_t *)temp + i * size, size);
            i++;
        } else {
            memcpy((uint8_t *)base + k * size, (uint8_t *)R + j * size, size);
            j++;
        }
        k++;
    }

    // Copy any remaining elements of the left half
    while (i < n1) {
        memcpy((uint8_t *)base + k * size, (uint8_t *)temp + i * size, size);
        i++;
        k++;
    }

    // Copy any remaining elements of the right half (already in place)
    while (j < n2) {
        memcpy((uint8_t *)base + k * size, (uint8_t *)R + j * size, size);
        j++;
        k++;
    }
}

// Recursive function to divide and merge
void merge_sort_recursive(void *base, size_t left, size_t right, size_t size, int (*compar)(const void*, const void*), void *temp) {
    if (right - left <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(base, left, right, size, compar);
        return;
    }

    if (left < right) {
        size_t mid = left + (right - left) / 2;

        merge_sort_recursive(base, left, mid, size, compar, temp);
        merge_sort_recursive(base, mid + 1, right, size, compar, temp);

        merge(base, left, mid, right, size, compar, temp);
    }
}

// Merge sort function
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (base == NULL || nitems == 0 || size == 0 || compar == NULL) 
        return;

    void *temp = malloc((nitems / 2 + 1) * size); // Allocate half-size temporary buffer
    if (temp == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    merge_sort_recursive(base, 0, nitems - 1, size, compar, temp);
    free(temp);
}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {

}
