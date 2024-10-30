#ifndef _IO_H
#define _IO_H

#include <stdlib.h>
#include <stdio.h>


#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 32

int count_lines(FILE* file);

int count_words(FILE* file);

int read_dictionary(FILE* dictionary_fp, char*** dictionary);

int read_to_correct(FILE* to_correct_fp, char*** to_correct);

#endif // _IO_H