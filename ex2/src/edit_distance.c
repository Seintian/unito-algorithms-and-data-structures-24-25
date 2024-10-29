#include "edit_distance.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>


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
int edit_distance(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL)
        return -1;

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 == 0)
        return (int)len2;

    if (len2 == 0)
        return (int)len1;

    int d_no_op = (s1[0] == s2[0])
        ? edit_distance(s1 + 1, s2 + 1)
        : INT_MAX;

    int d_canc = 1 + edit_distance(s1, s2 + 1);

    int d_ins = 1 + edit_distance(s1 + 1, s2);

    return min3(d_no_op, d_canc, d_ins);
}

// TODO:
int edit_distance_dyn(const char *s1, const char *s2) {
    return 0;
}