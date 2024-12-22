/**
 * @file algo.c
 * @brief Implementation file for the merge_sort and the quick_sort functions.
 */

#include "algo.h"
#include "error_logger.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


// Helper function for insertion sort for small segments
void insertion_sort(void *base, size_t left, size_t right, size_t size, int (*compar)(const void*, const void*), void *temp) {
    for (size_t i = left + 1; i <= right; i++) {
        memcpy(temp, (uint8_t*)base + i * size, size);

        size_t j = i;
        while (j > left && compar((uint8_t*)base + (j - 1) * size, temp) > 0) {
            memcpy((uint8_t*)base + j * size, (uint8_t*)base + (j - 1) * size, size);
            j--;
        }

        memcpy((uint8_t*)base + j * size, temp, size);
    }
}

// Helper function to merge two halves of the array
void merge(void *base, size_t left, size_t mid, size_t right, size_t size, int (*compar)(const void*, const void*), void *temp) {
    if (!base || !temp || !compar)
        return;

    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    // Copy the left half to temp buffer
    memcpy(temp, (uint8_t *)base + left * size, n1 * size);
    // Pointer to the beginning of the right half
    void *R = (uint8_t *)base + (mid + 1) * size;

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < n1 && j < n2) {
        if (compar((uint8_t *)temp + i * size, (uint8_t *)R + j * size) <= 0) {
            memcpy((uint8_t *)base + k * size, (uint8_t *)temp + i * size, size);
            i++;
        } 
        else {
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

    // No need to copy the remaining elements of the right half, as they are already in place
}

// Bottom-up iterative merge sort
void merge_sort(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*)) {
    if (base == NULL || n_items == 0 || size == 0 || compar == NULL) 
        return;

    // Allocate temp buffer for merging
    void *temp = malloc(n_items * size);
    if (temp == NULL) 
        raise_error("Memory allocation failed");

    // Start with subarrays of size 1 and double the size in each iteration
    for (size_t width = 1; width < n_items; width *= 2) {
        for (size_t i = 0; i < n_items; i += 2 * width) {
            size_t left = i;
            size_t mid = (i + width - 1 < n_items) ? i + width - 1 : n_items - 1;
            size_t right = (i + 2 * width - 1 < n_items) ? i + 2 * width - 1 : n_items - 1;

            if (mid < right)
                merge(base, left, mid, right, size, compar, temp);
        }
    }

    free(temp);
}


// Helper function that swaps two elements of a generic array knowing their size
void swap(void *el1, void *el2, size_t size, void *temp) {
    memcpy(temp, el1, size);
    memcpy(el1, el2, size);
    memcpy(el2, temp, size);
}

// Helper function that chooses the pivot following the "median-of-three" rule in order to avoid 
// worst-case behavior on already sorted arrays
void median_of_three(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*), void *temp) {
	void *low = base;
	void *mid = (uint8_t *)base + size * (n_items / 2);
	void *high = (uint8_t *)base + size * (n_items - 1);

	if (compar(mid, high) > 0)
		swap(mid, high, size, temp);

	if (compar(low, high) > 0)
		swap(low, high, size, temp);

	if (compar(mid, low) > 0)
		swap(mid, low, size, temp);
}

void three_way_partition(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*), void *temp, size_t *lt, size_t *gt) {
    // Choose the pivot using median_of_three and place it in base[0]
    median_of_three(base, n_items, size, compar, temp);
    
    void* pivot = base;
    size_t low = 1;
    size_t j = 1;
    size_t high = n_items - 1;

    while (j <= high) {
        int cmp = compar((uint8_t *)base + size * j, pivot);

        if (cmp < 0) {
            if (low != j) 
                swap((uint8_t *)base + size * low, (uint8_t *)base + size * j, size, temp);
    
            low++;
            j++;
        } 
        else if (cmp > 0) {
            if (high != j)
                swap((uint8_t *)base + size * j, (uint8_t *)base + size * high, size, temp);
                
            high--;
        } 
        else
            j++;
    }
    
    if (low - 1) // NB: if there are no elements in base[1 ... n_items - 1] that are smaller than the pivot the swap is not taken
        swap(pivot, (uint8_t *)base + size * (low - 1), size, temp);
    
    *lt = low; // Elements < pivot
    *gt = high; // Elements > pivot start here
}

// Recursive function that sorts the array using quick sort
void quick_sort_recursive(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*), void *temp) {
    if (n_items <= 1)
        return;
    
    if (n_items <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(base, 0, n_items - 1, size, compar, temp);
        return;
    }

    size_t lt;
    size_t gt;
    three_way_partition(base, n_items, size, compar, temp, &lt, &gt);
    
    size_t left_size = lt;
    size_t right_size = n_items - (gt + 1);

    if (left_size < right_size) {
        // recursive call on base[0 ... lt - 1] (smaller portion)
        quick_sort_recursive(base, left_size, size, compar, temp);
        // recursive call on base[gt + 1 ... n_items - 1] (bigger portion)
        quick_sort_recursive((uint8_t *)base + size * (gt + 1), right_size, size, compar, temp);
    }
    else {
        // recursive call on base[gt + 1 ... n_items - 1] (smaller portion)
        quick_sort_recursive((uint8_t *)base + size * (gt + 1), right_size, size, compar, temp);
        // recursive call on base[0 ... lt - 1] (bigger portion)
        quick_sort_recursive(base, left_size, size, compar, temp);
    }
}


void quick_sort(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*)) {
    if (base == NULL || n_items == 0 || size == 0 || compar == NULL)
        return;

    // memory allocation for temporary void pointer, used to swap array elements, and the control on malloc's outcome
    void *temp = malloc(size);
    if (!temp)
        raise_error("Memory allocation failed");

    quick_sort_recursive(base, n_items, size, compar, temp);
    free(temp);
}