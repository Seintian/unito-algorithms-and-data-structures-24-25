/**
 * @file edit_distance.h
 * @brief Header file for edit distance algorithms.
 */

#ifndef _EDIT_DISTANCE_H
#define _EDIT_DISTANCE_H

/**
 * @brief Computes the edit distance between two strings using a recursive approach.
 * 
 * The edit distance is the minimum number of operations (insertions, deletions, or substitutions)
 * required to transform one string into another.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The edit distance between the two strings.
 */
int edit_distance(const char *s1, const char* s2);

/**
 * @brief Computes the edit distance between two strings using a dynamic programming approach.
 * 
 * The edit distance is the minimum number of operations (insertions, deletions, or substitutions)
 * required to transform one string into another. This implementation uses dynamic programming
 * to improve efficiency.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The edit distance between the two strings.
 */
int edit_distance_dyn(const char *s1, const char* s2);


#endif // _EDIT_DISTANCE_H