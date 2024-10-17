#include "algo.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>


// Helper function to merge two halves of the array
void merge(void *base, size_t left, size_t mid, size_t right, size_t size, int (*compar)(const void*, const void*)) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    // Allocate memory for temporary arrays
    void *L = malloc(n1 * size);
    void *R = malloc(n2 * size);
    
    if (L == NULL || R == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Copy data to temporary arrays L[] and R[]
    memcpy(L, (uint8_t *)base + left * size, n1 * size);
    memcpy(R, (uint8_t *)base + (mid + 1) * size, n2 * size);
    
    // Merge the temporary arrays back into base[]
    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compar((uint8_t *)L + i * size, (uint8_t *)R + j * size) <= 0) {
            memcpy((uint8_t *)base + k * size, (uint8_t *)L + i * size, size);
            i++;
        } else {
            memcpy((uint8_t *)base + k * size, (uint8_t *)R + j * size, size);
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        memcpy((uint8_t *)base + k * size, (uint8_t *)L + i * size, size);
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        memcpy((uint8_t *)base + k * size, (uint8_t *)R + j * size, size);
        j++;
        k++;
    }

    // Free the temporary arrays
    free(L);
    free(R);
}

// Recursive function to divide and merge
void merge_sort_recursive(void *base, size_t left, size_t right, size_t size, int (*compar)(const void*, const void*)) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        // Recursively sort the two halves
        merge_sort_recursive(base, left, mid, size, compar);
        merge_sort_recursive(base, mid + 1, right, size, compar);

        // Merge the sorted halves
        merge(base, left, mid, right, size, compar);
    }
}

// Public function to initiate merge sort
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (base == NULL || nitems == 0 || size == 0 || compar == NULL) 
        return;

    merge_sort_recursive(base, 0, nitems - 1, size, compar);
}



void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {

}
