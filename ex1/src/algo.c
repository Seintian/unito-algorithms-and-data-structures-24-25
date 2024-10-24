#include "algo.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>


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
        insertion_sort(base, left, right, size, compar, temp);
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
void merge_sort(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*)) {
    if (base == NULL || n_items == 0 || size == 0 || compar == NULL) 
        return;

    // Allocate half-size temporary buffer
    void *temp = malloc((n_items / 2 + 1) * size);
    if (temp == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    merge_sort_recursive(base, 0, n_items - 1, size, compar, temp);
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

// Helper function to partition the array
size_t partition(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*), void *temp) {
    // call to median_of_three in order to choose the pivot (put in base[0])
	median_of_three(base, n_items, size, compar, temp);

    size_t i = 1, j = n_items - 1;
    while (i <= j) {
        if (compar((uint8_t *)base + size * i, base) <= 0)
            i++;

        else if (compar((uint8_t *)base + size * j, base) > 0)
            j--;

        else {
            swap((uint8_t *)base + size * i, (uint8_t *)base + size * j, size, temp);

            i++;
            j--;
        }
    }

    swap(base, (uint8_t *)base + size * j, size, temp);

    // return the value of 'j' index, that is the pivot
    return j;
}

// Recursive function that sorts the array using quick sort
void quick_sort_recursive(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*), void *temp) {
    if (n_items < 1)
        return;
    
    if (n_items <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(base, 0, n_items - 1, size, compar, temp);
        return;
    }

    size_t pivot = partition(base, n_items, size, compar, temp);
    size_t right_size = n_items - (pivot + 1);

    if (pivot < right_size) {
        // recursive call on base[0 ... pivot - 1] (smaller)
        quick_sort_recursive(base, pivot, size, compar, temp);
        // recursive call on base[pivot + 1 ... n_items - 1] (bigger)
        quick_sort_recursive((uint8_t *)base + size * (pivot + 1), right_size, size, compar, temp);
    }
    else {
        // recursive call on base[pivot + 1 ... n_items - 1] (smaller)
        quick_sort_recursive((uint8_t *)base + size * (pivot + 1), right_size, size, compar, temp);
        // recursive call on base[0 ... pivot - 1] (bigger)
        quick_sort_recursive(base, pivot, size, compar, temp);
    }
}


void quick_sort(void *base, size_t n_items, size_t size, int (*compar)(const void*, const void*)) {
    if (base == NULL || n_items == 0 || size == 0 || compar == NULL)
        return;

    // memory allocation for temporary void pointer, used to swap array elements, and the control on malloc's outcome
    void *temp = malloc(size);
    if (!temp) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    quick_sort_recursive(base, n_items, size, compar, temp);
    free(temp);
}
