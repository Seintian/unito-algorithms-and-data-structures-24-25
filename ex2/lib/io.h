#ifndef _IO_H
#define _IO_H

#include <stdlib.h>
#include <stdio.h>


#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 32

/**
 * @brief Counts the number of lines in a file.
 *
 * This function counts the number of lines in a dictionary file.
 * It is used to determine the number of words in the dictionary.
 * Each line in the dictionary file is a word.
 *
 * @param file File pointer.
 * @return Number of lines in the file.
 */
int count_lines(FILE* file);

/**
 * @brief Counts the number of words in a file.
 *
 * This function counts the number of words in a to_correct file.
 * This file contains only one line with the words to compare with the dictionary's ones.
 * The words are separated by spaces and punctuation characters.
 *
 * @param file File pointer.
 * @return Number of words in the file.
 */
int count_words(FILE* file);

/**
 * @brief Reads the dictionary file.
 *
 * This function reads the dictionary file and stores the words in a matrix.
 * Each line in the dictionary file is a word.
 *
 * @param dictionary_fp File pointer to the dictionary file.
 * @param dictionary Pointer to the matrix that will store the words.
 * @return Number of words read from the dictionary file.
 */
int read_dictionary(FILE* dictionary_fp, char*** dictionary);

/**
 * @brief Reads the to_correct file.
 *
 * This function reads the to_correct file and stores the words in a matrix.
 * This file contains only one line with the words to compare with the dictionary's ones.
 * The words are separated by spaces and punctuation characters.
 *
 * @param to_correct_fp File pointer to the to_correct file.
 * @param to_correct Pointer to the matrix that will store the words.
 * @return Number of words read from the to_correct file.
 */
int read_to_correct(FILE* to_correct_fp, char*** to_correct);

#endif // _IO_H