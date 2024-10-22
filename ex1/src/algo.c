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

// Helper function that swaps two elements of a generic array knowing their size
void swap(void *el1, void *el2, size_t size, void *tmp) {
    memcpy(tmp, el1, size);
    memcpy(el1, el2, size);
    memcpy(el2, tmp, size);
}

/* Helper function that chooses the pivot following the "median-of-three" rule in order to avoid 
 * worst-case behavior on already sorted arrays*/
void median_of_three(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*), void *tmp) {
	void *lo = base;
	void *mid = (uint8_t *)base + size * (nitems / 2);
	void *hi = (uint8_t *)base + size * (nitems - 1);
	if (compar(mid, hi) > 0) {
		swap(mid, hi, size, tmp);
	}
	if (compar(lo, hi) > 0) {
		swap(lo, hi, size, tmp);
	}
	if (compar(mid, lo) > 0) {
		swap(mid, lo, size, tmp);
	}
}

// Helper function to partition the array
size_t partition(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*), void *tmp) {
	// call to median_of_three in order to choose the pivot (it is put in base[0])
	median_of_three(base, nitems, size, compar, tmp);
    // 'i' and 'j' indexes initialization
    size_t i = 1, j = nitems - 1;
    // invariant: 
    while(i <= j) {
        if (compar((uint8_t *)base + size * i, base) <= 0) { // case: base[i] <= *base  ->  extension of interval [1 ... i-1]
            i++;
        }
        else {
            if (compar((uint8_t *)base + size * j, base) > 0) { // case: base[j] > *base  ->  extension of interval [j+1 ... nitems-1]
                j--;
            }
            else { // case: base[j] <= *base &&  base[i] > *base  ->  swap of base[i] and base[j],
            // extension of intervals [j+1 ... nitems-1] and [1 ... i-1]
                swap((uint8_t *)base + size * i, (uint8_t *)base + size * j, size, tmp);
                i++;
                j--;
            }
        }
    }
    // swap of base[0] and base[j],
    swap(base, (uint8_t *)base + size * j, size, tmp);
    // return the value of 'j' index, that is the pivot
    return j;
}

// Recursive function that sorts the array using quick sort
void quick_sort_recursive(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*), void *tmp) {
    // switch to insertion sort as number of elements is below threshold 
    if (nitems <= INSERTION_SORT_THRESHOLD) {
        insertion_sort(base, 0, nitems-1, size, compar);
        return;
    }
    if (nitems > 1) {
        // pivot assignement
        size_t pivot = partition(base, nitems, size, compar, tmp);
        // Recur first on the smaller partition to optimize stack usage
        size_t r_size = nitems - (pivot + 1);
        if (pivot < r_size) {
			// recursive call on base[0 ... pivot-1] (smaller)
			quick_sort_recursive(base, pivot, size, compar, tmp);
			// recursive call on base[pivot+1 ... nitems-1] (bigger)
			quick_sort_recursive((uint8_t *)base + size * (pivot + 1), r_size, size, compar, tmp);
		}
		else {
			// recursive call on base[pivot+1 ... nitems-1] (smaller)
			quick_sort_recursive((uint8_t *)base + size * (pivot + 1), r_size, size, compar, tmp);
			// recursive call on base[0 ... pivot-1] (bigger)
			quick_sort_recursive(base, pivot, size, compar, tmp);
		}
        
    }
}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    // controls on arguments
    if (base == NULL || nitems == 0 || size == 0 || compar == NULL) {
        perror("The function has received invalid arguments");
        return;
    }
    // memory allocation for temporary void pointer, used to swap array elements, and the control on malloc's outcome
    void *tmp = malloc(size);
    if (!tmp) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    quick_sort_recursive(base, nitems, size, compar, tmp);
    // de-allocation of memory referenced by tmp
    free(tmp);
}
