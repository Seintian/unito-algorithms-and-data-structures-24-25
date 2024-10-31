#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
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