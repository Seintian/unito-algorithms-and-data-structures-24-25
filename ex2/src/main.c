#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    const FILE* dictionary_fp = fopen(dictionary, "r");
    if (!dictionary_fp) {
        printf("Error: dictionary file does not exist -> %s\n", dictionary);
        exit(EXIT_FAILURE);
    }

    const FILE* to_correct_fp = fopen(to_correct, "w");
    if (!to_correct_fp) {
        fclose(dictionary);

        printf("Error: to_correct file cannot be created " \
               "-> dictionary: %s, to_correct: %s\n", dictionary, to_correct);
        exit(EXIT_FAILURE);
    }

    fclose(dictionary_fp);
    fclose(to_correct_fp);
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

    // TODO: use the edit_distance algorithm to correct the text in the to_correct file 
    // (print the corrected words with infos)

    return EXIT_SUCCESS;
}