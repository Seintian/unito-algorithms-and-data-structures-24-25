/**
 * @file text_io.h
 * @brief Interface for reading text files and storing words in a hash table.
 */

#ifndef _TEXT_IO_H
#define _TEXT_IO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"


#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 32

/**
 * @brief Counts the number of words in a file.
 *
 * This function reads the file line by line and splits each line into words
 * using common delimiters such as spaces, punctuation, and newline characters.
 * It returns the total word count in the file. The file pointer is reset 
 * after counting the words.
 *
 * @param file File pointer to the file.
 * @return The number of words in the file, or -1 if an error occurs.
 */
int count_words(FILE* file);

/**
 * @brief Reads a file and stores the words in a hash table.
 *
 * This function reads the file line by line and splits each line into words
 * using common delimiters such as spaces, punctuation, and newline characters.
 * It stores the words in a hash table, where the key is the word and the value
 * is the frequency of the word in the file. The hash table is returned by reference.
 *
 * @param text_fp File pointer to the file.
 * @param table Pointer to a hash table to store the words.
 * @return 0 if successful, -1 if an error occurs.
 */
int read_text(FILE* text_fp, HashTable** table);

#endif // _TEXT_IO_H