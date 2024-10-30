#include "io.h"
#include <string.h>


int count_lines(FILE* file_fp) {
    if (file_fp == NULL)
        return -1;

    int lines = 0;
    int ch;

    while (!feof(file_fp)) {
        ch = fgetc(file_fp);
        if (ch == '\n')
            lines++;
    }

    rewind(file_fp);

    return lines;
}

int count_words(FILE* file) {
    if (file == NULL)
        return -1;

    int word_count = 0;
    char line[MAX_LINE_LENGTH];
    const char* delimiters = " \t\n,.!?;:\"()[]{}<>-";

    fseek(file, 0, SEEK_SET);

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

void free_matrix(char** matrix, int total_rows) {
    if (matrix == NULL)
        return;

    for (int i = 0; i < total_rows; i++)
        free(matrix[i]);

    free(matrix);
}

int read_dictionary(FILE* dictionary_fp, char*** dictionary) {
    if (dictionary_fp == NULL || dictionary == NULL)
        return -1;
    
    int total_words = count_lines(dictionary_fp);
    if (total_words < 1)
        return -1;

    *dictionary = malloc(total_words * sizeof(char*));
    if (*dictionary == NULL)
        return -1;
    
    int words_read = 0;
    char line[MAX_WORD_LENGTH];
    while (words_read < total_words && fgets(line, MAX_WORD_LENGTH, dictionary_fp)) {
        // Remove the newline character if present
        line[strcspn(line, "\n")] = '\0';

        (*dictionary)[words_read] = malloc(strlen(line) + 1);
        if ((*dictionary)[words_read] == NULL) {
            free_matrix(*dictionary, words_read);

            return -1;
        }

        strcpy((*dictionary)[words_read++], line);
    }

    return words_read;
}

int read_to_correct(FILE* to_correct_fp, char*** to_correct) {
    if (to_correct_fp == NULL || to_correct == NULL)
        return -1;
    
    int total_words = count_words(to_correct_fp);
    if (total_words < 1)
        return -1;

    *to_correct = malloc(total_words * sizeof(char*));
    if (*to_correct == NULL)
        return -1;
    
    int words_read = 0;
    char line[MAX_LINE_LENGTH];
    const char *delimiters = " \t\n,.!?;:\"()[]{}<>-";
    while (words_read < total_words && fgets(line, MAX_LINE_LENGTH, to_correct_fp)) {
        char *saveptr;
        const char *word = strtok_r(line, delimiters, &saveptr);

        while (words_read < total_words && word != NULL) {
            (*to_correct)[words_read] = malloc(strlen(word) + 1);
            if ((*to_correct)[words_read] == NULL) {
                free_matrix(*to_correct, words_read);

                return -1;
            }

            strcpy((*to_correct)[words_read++], word);

            word = strtok_r(NULL, delimiters, &saveptr);
        }
    }

    return words_read;
}