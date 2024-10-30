#include "edit_distance.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>


#define min(a, b) ((a) < (b) ? (a) : (b))
#define min3(a, b, c) min(a, min(b, c))

/**
 * If the length of s1 is 0, then edit_distance(s1, s2) = length of s2;
 * If the length of s2 is 0, then edit_distance(s1, s2) = length of s1;
 * Otherwise, let:
 * 
 * - `d_no_op = edit_distance(rest(s1), rest(s2))` if s1[0] == s2[0],
 *   otherwise `d_no_op = infinity;` (i.e., `INT_MAX`)
 * 
 * - `d_canc = 1 + edit_distance(s1, rest(s2));`
 * 
 * - `d_ins = 1 + edit_distance(rest(s1), s2);`
 * 
 * Therefore, `edit_distance(s1, s2)` is given by the minimum of
 * {d_no_op, d_canc, d_ins}.
 */
int edit_distance_recursive(const char *s1, const char *s2) {
    int len_s1 = (int)strlen(s1);
    int len_s2 = (int)strlen(s2);

    if (*s1 == '\0')
        return len_s2;

    if (*s2 == '\0')
        return len_s1;

    int d_no_op = (s1[0] == s2[0])
        ? edit_distance(s1 + 1, s2 + 1)
        : INT_MAX;

    int d_canc = 1 + edit_distance(s1, s2 + 1);

    int d_ins = 1 + edit_distance(s1 + 1, s2);

    return min3(d_no_op, d_canc, d_ins);
}

int edit_distance(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL)
        return -1;

    return edit_distance_recursive(s1, s2);
}

int** init_edit_distance_dyn_memo(size_t len_s1, size_t len_s2) {
    if (len_s1 == 0 || len_s2 == 0)
        return NULL;

    int** memo = (int**)malloc((len_s1 + 1) * sizeof(int*));

    for (size_t i = 0; i < len_s1 + 1; i++) {
        memo[i] = (int*)malloc((len_s2 + 1) * sizeof(int));

        memset(memo[i], -1, (len_s2 + 1) * sizeof(int));
    }

    return memo;
}

int edit_distance_dyn_recursive(const char *s1, const char* s2, int **memo, size_t i, size_t j) {
    if (*s1 == '\0')
        return (int)strlen(s2);

    if (*s2 == '\0')
        return (int)strlen(s1);
    
    if (memo == NULL)
        return -1;

    int d_no_op;
    if (*s1 == *s2) {
        d_no_op = (memo[i+1][j+1] == -1)
            ? edit_distance_dyn_recursive(s1 + 1, s2 + 1, memo, i + 1, j + 1)
            : memo[i+1][j+1];

    } else
        d_no_op = INT_MAX;

    int d_canc = 1 + \
    (
        memo[i][j+1] == -1
            ? edit_distance_dyn_recursive(s1, s2 + 1, memo, i, j + 1)
            : memo[i][j+1]
    );

    int d_ins = 1 + \
    (
        memo[i+1][j] == -1
            ? edit_distance_dyn_recursive(s1 + 1, s2, memo, i + 1, j)
            : memo[i+1][j]
    );

    memo[i][j] = min3(d_no_op, d_canc, d_ins);

    return memo[i][j];
}

int edit_distance_dyn(const char *s1, const char* s2) {
    if (s1 == NULL || s2 == NULL)
        return -1;

    size_t len_s1 = strlen(s1);
    size_t len_s2 = strlen(s2);

    if (len_s1 == 0 || len_s2 == 0)
        return edit_distance_dyn_recursive(s1, s2, NULL, 0, 0);

    int** memo = init_edit_distance_dyn_memo(len_s1, len_s2);
    if (memo == NULL)
        return -1;

    int distance = edit_distance_dyn_recursive(s1, s2, memo, 0, 0);

    for (size_t i = 0; i < len_s1; i++)
        free(memo[i]);
    
    free(memo);

    return distance;
}