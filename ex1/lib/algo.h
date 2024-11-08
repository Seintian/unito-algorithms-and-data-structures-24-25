/**
 * @file algo.h
 * @brief Header file containing the declaration of the merge_sort and the quick_sort functions.
 *
 * This file provides the interface for the merge_sort and the quick_sort functions, which 
 * sort arrays of elements.
 * It does not include the auxiliary functions used by the merge_sort and the quick_sort functions.
 */

#ifndef _ALGO_H
#define _ALGO_H

#include <stdlib.h>


#define INSERTION_SORT_THRESHOLD 10

/**
 * @brief Sorts an array using the insertion sort algorithm.
 *
 * This function sorts an array of elements using the insertion sort algorithm.
 * The array is sorted in-place.
 *
 * @param base Pointer to the array to be sorted.
 * @param left Index of the first element to be sorted.
 * @param right Index of the last element to be sorted.
 * @param size Size of each element in the array.
 * @param compar Comparison function that determines the order of the elements.
 *               It should return a negative value if the first element is less
 *               than the second, zero if they are equal, and a positive value
 *               if the first element is greater than the second.
 * @param temp Temporary buffer allocated once in the caller used for swaps.
 */
void insertion_sort(void *base, size_t left, size_t right, size_t size, int (*compar)(const void*, const void*), void *temp);

/**
 * @brief Sorts an array using the merge sort algorithm.
 *
 * This function sorts an array of elements using the merge sort algorithm.
 * The array is sorted in-place.
 *
 * @param base Pointer to the array to be sorted.
 * @param nitems Number of elements in the array.
 * @param size Size of each element in the array.
 * @param compar Comparison function that determines the order of the elements.
 *               It should return a negative value if the first element is less
 *               than the second, zero if they are equal, and a positive value
 *               if the first element is greater than the second.
 */
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief Sorts an array using the quick sort algorithm.
 *
 * This function sorts an array of elements using the quicksort algorithm. The
 * array is specified by a pointer to its base, the number of elements, and the
 * size of each element. A comparison function is provided to determine the
 * order of the elements.
 *
 * @param base Pointer to the first element of the array to be sorted.
 * @param nitems Number of elements in the array.
 * @param size Size of each element in the array.
 * @param compar Comparison function that determines the order of the elements.
 *               It should return a negative value if the first argument is less
 *               than the second, zero if they are equal, and a positive value
 *               if the first argument is greater than the second.
 */
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

#endif // _ALGO_H