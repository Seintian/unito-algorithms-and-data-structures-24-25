/**
 * @file main.c
 * @brief Command Line Interface (CLI) application for text correction using edit distance.
 *
 * @mainpage Text Correction CLI Application
 *
 * @section overview Overview
 * This project is a Command Line Interface (CLI) application designed for correcting text by finding the closest word from a dictionary using the edit distance algorithm. The user provides a dictionary file and a text file to be corrected. The program suggests the closest matches for misspelled words by calculating the edit distance between the words in the text and the dictionary.
 *
 * @section usage Usage
 * The application is executed with the following command:
 * ```
 * ./bin/main_ex2(.exe) <dictionary_path> <to_correct_path>
 * ```
 * - `<dictionary_path>`: Path to the dictionary file containing valid words.
 * - `<to_correct_path>`: Path to the file containing the words that need correction.
 *
 * Example:
 * ```
 * ./bin/main_ex2(.exe) data/dictionary.txt data/correctme.txt
 * ```
 *
 * @section file_structure File Structure
 *
 * - **main.c**: Contains the main entry point of the application, which validates input arguments, reads dictionary and to-correct files, and performs the word correction using the edit distance algorithm.
 * - **text_io.h**: Provides functions for reading files, such as reading the dictionary and the words to be corrected, as well as counting lines in a file and reading words.
 * - **edit_distance.h**: Declares the `edit_distance_dyn` function used to compute the edit distance between two words.
 *
 * @section modules Modules and Functions
 *
 * - **Input Validation**: The function `validate_input` checks the validity of the input files, ensuring that the dictionary and to-correct files are different and can be opened.
 * - **Word Correction**:
 *   - `find_closest_word`: Uses the `edit_distance_dyn` algorithm to find the closest word from the dictionary for a given word.
 * - **File Operations**:
 *   - `count_lines`: Counts the number of lines (words) in a file.
 *   - `read_dictionary`: Reads words from the dictionary file into an array.
 *   - `read_to_correct`: Reads words from the file to be corrected.
 * - **Edit Distance Algorithm**: The `edit_distance_dyn` function is used to compute the distance between two words, guiding the correction process.
 *
 * @section error_handling Error Handling
 *
 * The application validates:
 * - The dictionary and to-correct files are not the same.
 * - The dictionary file exists and can be read.
 * - The to-correct file exists and can be read.
 * - The dictionary and to-correct files contain words.
 *
 * If any validation fails, the application prints an error message and exits with `EXIT_FAILURE`.
 *
 * @section performance Performance
 * The edit distance algorithm has a time complexity of O(m * n), where `m` is the length of the first word and `n` is the length of the second word. This means that the algorithm performs efficiently on words of average length but may experience slower performance on longer words.
 *
 * @section compilation Compilation Instructions
 * To compile the application, use:
 * ```
 * make all
 * ```
 * To compile and execute the tests, use:
 * ```
 * make test
 * ```
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_io.h"
#include "edit_distance.h"


/**
 * @brief Validates the input arguments.
 *
 * This function validates the input arguments of the program.
 * It checks if the dictionary and to_correct files are different,
 * if the dictionary file exists and if the to_correct file can be created.
 *
 * @param dictionary Path to the dictionary file.
 * @param to_correct Path to the to_correct file.
 * @throw `EXIT_FAILURE` if any of the input arguments is invalid.
 */
void validate_input(const char* dictionary, const char* to_correct) {
    if (strcmp(dictionary, to_correct) == 0) {
        printf("Error: dictionary and to_correct cannot be the same " \
               "-> dictionary: %s, to_correct: %s\n", dictionary, to_correct);
        exit(EXIT_FAILURE);
    }

    FILE* dictionary_fp = fopen(dictionary, "r");
    if (!dictionary_fp) {
        printf("Error: dictionary file does not exist -> %s\n", dictionary);
        exit(EXIT_FAILURE);
    }

    FILE* to_correct_fp = fopen(to_correct, "r");
    if (!to_correct_fp) {
        fclose(dictionary_fp);

        printf("Error: to_correct file does not exist -> %s\n", to_correct);
        exit(EXIT_FAILURE);
    }

    fclose(dictionary_fp);
    fclose(to_correct_fp);
}

void find_closest_word(const char* word, char** dictionary, int words_in_dictionary, const char** closest_word, int* min_distance) {
    for (int i = 0; i < words_in_dictionary; i++) {
        const char* dict_word = dictionary[i];
        int distance = edit_distance_dyn(word, dict_word);

        if (*min_distance == -1 || distance < *min_distance) {
            *min_distance = distance;
            *closest_word = dict_word;

            if (distance == 0)
                break;
        }
    }
}

/**
 * @brief Main function.
 *
 * This function is the entry point of the program. It validates the input arguments,
 * uses the edit_distance algorithm to correct the text in the to_correct file,
 * and prints in the console the corrected words with infos.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return `EXIT_SUCCESS` if the program executed successfully,
 *         `EXIT_FAILURE` if the input arguments are invalid.
 */
int main(int argc, const char * argv[]) {
    if (argc < 3) {
        printf("Usage:\n");
        printf("  %s <dictionary_path> <to_correct_path>\n", argv[0]);
        printf("Options:\n");
        printf("  <dictionary_path> Path to the dictionary file.\n");
        printf("  <to_correct_path> Path to the file containing the text to correct.\n");
        printf("Example:\n");
        printf("  %s data/dictionary.txt data/correctme.txt\n", argv[0]);

        return EXIT_FAILURE;
    }

    validate_input(argv[1], argv[2]);

    FILE* dictionary_fp = fopen(argv[1], "r");
    if (dictionary_fp == NULL) {
        perror("Unable to open dictionary file");
        return EXIT_FAILURE;
    }

    // Determine number of words in dictionary for memory allocation
    int word_count = count_lines(dictionary_fp);
    if (word_count < 1) {
        fclose(dictionary_fp);
        fprintf(stderr, "Error: No words in dictionary.\n");

        return EXIT_FAILURE;
    }

    char** dictionary = malloc(sizeof(char*) * word_count);
    int words_in_dictionary = read_dictionary(dictionary_fp, &dictionary);
    if (words_in_dictionary < 1)
        return EXIT_FAILURE;
    
    FILE* to_correct_fp = fopen(argv[2], "r");
    if (to_correct_fp == NULL) {
        perror("Unable to open to_correct file");
        return EXIT_FAILURE;
    }

    int words_in_to_correct = count_words(to_correct_fp);
    if (words_in_to_correct < 1) {
        fclose(dictionary_fp);
        fclose(to_correct_fp);
        fprintf(stderr, "Error: No words in to_correct file.\n");

        return EXIT_FAILURE;
    }

    char** to_correct = malloc(sizeof(char*) * words_in_to_correct);
    int words_read = read_to_correct(to_correct_fp, &to_correct);
    if (words_read < 1)
        return EXIT_FAILURE;
    
    const char* word;
    int min_distance;
    const char* closest_word;
    for (int i = 0; i < words_in_to_correct; i++) {
        word = to_correct[i];
        min_distance = -1;
        closest_word = NULL;

        find_closest_word(word, dictionary, words_in_dictionary, &closest_word, &min_distance);

        printf(
            "Word: \"%s\", closest word: \"%s\", distance: %d (%s)\n", 
            word, 
            closest_word, 
            min_distance,
            min_distance == 0 ? "exact match" : "approximate match"
        );
    }

    fclose(to_correct_fp);
    fclose(dictionary_fp);

    return EXIT_SUCCESS;
}