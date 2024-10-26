#ifndef _CSV_H
#define _CSV_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define MAX_LINE_SIZE 128

/**
 * @brief Structure representing a record with four fields.
 * 
 * This structure represents a record with four fields: an integer ID, a string field1,
 * an integer field2, and a double field3. The structure is used to store the records
 * read from the input file.
 * 
 * This executable can only accept CSV files with the following format:
 * 
 *    ID,field1,field2,field3
 * 
 * where ID is an integer, field1 is a string with at most 99 characters, field2 is an integer,
 * and field3 is a double.
 */
typedef struct _Record {
    int id;
    char field1[100];
    int field2;
    double field3;

} Record, *RecordPtr;

extern const char* recordReadFmt;
extern const char* recordWriteFmt;

#define N_FIELDS_IN_RECORD 4
#define READING_BUFFER_SIZE (64 * 1024) // 64 KB
#define WRITING_BUFFER_SIZE (64 * 1024) // 64 KB

/**
 * @brief Compares two records based on the field1 field.
 *
 * This function compares two records based on the field1 field. It is used as a comparison
 * function for the quick_sort and merge_sort functions.
 * 
 * This definition is common to all the compare_fieldX functions.
 *
 * @param a Pointer to the first record.
 * @param b Pointer to the second record.
 * @return A negative value if the first record is less than the second, zero if they are equal,
 *         and a positive value if the first record is greater than the second.
 */
int compare_field1(const void* a, const void* b);
/**
 * @brief Compares two records based on the field1 field.
 *
 * This function compares two records based on the field1 field. It is used as a comparison
 * function for the quick_sort and merge_sort functions.
 * 
 * This definition is common to all the compare_fieldX functions.
 *
 * @param a Pointer to the first record.
 * @param b Pointer to the second record.
 * @return A negative value if the first record is less than the second, zero if they are equal,
 *         and a positive value if the first record is greater than the second.
 */
int compare_field2(const void* a, const void* b);
/**
 * @brief Compares two records based on the field1 field.
 *
 * This function compares two records based on the field1 field. It is used as a comparison
 * function for the quick_sort and merge_sort functions.
 * 
 * This definition is common to all the compare_fieldX functions.
 *
 * @param a Pointer to the first record.
 * @param b Pointer to the second record.
 * @return A negative value if the first record is less than the second, zero if they are equal,
 *         and a positive value if the first record is greater than the second.
 */
int compare_field3(const void* a, const void* b);


/**
 * @brief Counts the number of lines in a file.
 *
 * @param file Pointer to the file.
 * @return Number of lines in the file.
 */
size_t count_lines(FILE* file);

/**
 * @brief Reads records from a file and stores them in an array of RecordPtr.
 *
 * This function reads a specified number of records from the given input file
 * and stores them in the provided array of RecordPtr. The function assumes that
 * the file is already opened for reading and that the array has enough space to
 * hold the specified number of records.
 *
 * @param infile A pointer to the input file from which records are to be read.
 * @param records A pointer to an array of RecordPtr where the read records will be stored.
 * @param n_records The number of records to read from the file.
 * @return The number of records successfully read from the file.
 * @throw `EXIT_FAILURE` if an error occurs while reading the records.
 */
size_t read_records(FILE* infile, RecordPtr records, size_t n_records);

/**
 * @brief Writes records to a file.
 *
 * This function writes the records to the output file in CSV format.
 *
 * @param outfile Pointer to the output file.
 * @param records Pointer to the array of sorted records.
 * @param n_records Number of records to write.
 * @return The number of records successfully written to the file.
 * @throw `EXIT_FAILURE` if an error occurs while writing the records.
 */
size_t write_records(FILE* outfile, RecordPtr records, size_t n_records);

#endif // _CSV_H