/**
 * @file prime.c
 * @brief Implementation of functions for prime number operations.
 */

#include "prime.h"


int is_prime(int n) {
    if (n <= 1)
        return 0;

    if (n <= 3)
        return 1;

    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }

    return 1;
}

int next_prime(int n) {
    if (n <= 1)
        return 2;

    int prime = n;
    int found = 0;

    while (!found) {
        prime++;

        if (is_prime(prime))
            found = 1;
    }

    return prime;
}