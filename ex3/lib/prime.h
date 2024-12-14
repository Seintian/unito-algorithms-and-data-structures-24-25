/**
 * @file prime.h
 * @brief Interface for prime number functions.
 */

#ifndef _PRIME_H
#define _PRIME_H

/**
 * @brief checks if a number is prime
 * 
 * Checks if a number is prime. Returns 1 if the number is prime, 0 otherwise.
 * 
 * @param n The number to check
 * @return int
 */
int is_prime(int n);

/**
 * @brief gets the next prime number after a given number
 * 
 * Gets the next prime number after a given number, 
 * regardless of whether the number is prime.
 * 
 * @param n The number to start from
 * @return int
 */
int next_prime(int n);

#endif // _PRIME_H_