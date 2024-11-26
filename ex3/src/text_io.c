/**
 * @file text_io.c
 * @brief Input/Output functions for reading files.
 */

#define LOWER_WORDS 0

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
#include "text_io.h"


/**
 * @brief Inserts a word into the hash table.
 *
 * This function inserts a word into the hash table. If the word is already in the hash table,
 * the frequency of the word is incremented. If the word is not in the hash table, it is added
 * with a frequency of 1.
 *
 * @param table Pointer to the hash table.
 * @param word The word to insert.
 * @return 0 if successful, -1 if an error occurs.
 */
static int insert_word(HashTable* table, const char* word) {
    if (table == NULL || word == NULL)
        return -1;

    int* freq = (int*) hash_table_get(table, word);
    if (freq)
        (*freq)++;

    else {
        const char* new_word = strdup(word);
        if (!new_word)
            return -1;

        int* new_freq = (int*) malloc(sizeof(int));
        if (!new_freq)
            return -1;

        *new_freq = 1;
        hash_table_put(table, new_word, new_freq);
    }

    return 0;
}

/**
 * @brief Trims leading and trailing whitespace from a string.
 *
 * This function modifies the original string by trimming any leading and trailing whitespace.
 *
 * @param str The string to trim.
 */
static void trim_whitespace(char* str) {
    if (str == NULL)
        return;

    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end))
        end--;

    *(end + 1) = '\0';

    while (*str && isspace(*str))
        str++;
}

int count_words(FILE* file) {
    if (file == NULL)
        return -1;

    int word_count = 0;
    char line[MAX_LINE_LENGTH];
    const char* delimiters = " \t\n,.!?;:\"()[]{}<>-“”—’";

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* saveptr;
        const char* token = strtok_r(line, delimiters, &saveptr);
        while (token != NULL) {
            word_count++;
            token = strtok_r(NULL, delimiters, &saveptr);
        }
    }

    fseek(file, 0, SEEK_SET);
    return word_count;
}

#if defined(LOWER_WORDS) && LOWER_WORDS == 1
/**
 * @brief Converts a string to lowercase.
 *
 * This function converts all the characters in the provided string to 
 * lowercase. It modifies the original string.
 *
 * @param str The string to convert to lowercase.
 */
static void to_lower(char *str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z')
            *str += 'a' - 'A';

        str++;
    }
}
#endif // LOWER_WORDS

int read_text(FILE* text_fp, HashTable** table) {
    if (text_fp == NULL || table == NULL || *table == NULL)
        return -1;

    char line[MAX_LINE_LENGTH];
    const char* delimiters = " \t\n,.!?;:\"()[]{}<>'“”—’";
    while (fgets(line, MAX_LINE_LENGTH, text_fp) != NULL) {
        char* saveptr;
        char* token = strtok_r(line, delimiters, &saveptr);
        while (token != NULL) {
#           if defined(LOWER_WORDS) && LOWER_WORDS == 1
                to_lower(token);
#           endif

            trim_whitespace(token);

            if (strlen(token) > 0)
                insert_word(*table, token);

            token = strtok_r(NULL, delimiters, &saveptr);
        }
    }

    return 0;
}