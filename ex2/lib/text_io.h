/**
 * @file text_io.h
 * @brief Input/Output functions for reading files.
 */

#ifndef _TEXT_IO_H
#define _TEXT_IO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 32

/**
 * @brief Counts the number of lines in a file.
 *
 * This function reads a file character by character to count how many lines
 * it contains. It assumes that the file pointer is already opened and 
 * passed as an argument. The function resets the file pointer back to 
 * the beginning after counting.
 *
 * @param file_fp File pointer to the file.
 * @return The number of lines in the file, or -1 if an error occurs.
 */
int count_lines(FILE* file);

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
 * @brief Reads a dictionary file into memory.
 *
 * This function reads words from a dictionary file and stores them in
 * a dynamically allocated array. Each word is stored as a separate string
 * in the array. The dictionary file is assumed to be plain text with one
 * word per line.
 *
 * @param dictionary_fp File pointer to the dictionary file.
 * @param dictionary A pointer to a pointer where the array of words will be stored.
 * @return The number of words successfully read, or -1 if an error occurs.
 */
int read_dictionary(FILE* dictionary_fp, char*** dictionary);

/**
 * @brief Reads a file to correct into memory.
 *
 * This function reads a file containing text to correct and stores the words
 * in a dynamically allocated array. It assumes that the file is a plain text
 * file and separates words using common delimiters such as spaces and punctuation.
 *
 * @param to_correct_fp File pointer to the file to correct.
 * @param to_correct A pointer to a pointer where the array of words will be stored.
 * @return The number of words successfully read, or -1 if an error occurs.
 */
int read_to_correct(FILE* to_correct_fp, char*** to_correct);

#endif // _TEXT_IO_H