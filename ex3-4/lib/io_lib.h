#ifndef _IO_LIB_H
#define _IO_LIB_H

#include <stdlib.h>
#include <stdio.h>


#define MAX_LINE_SIZE 512
#define MAX_STRING_LENGTH 244

/**
 * Ogni record contiene i seguenti dati:
 *
 * place1: (tipo stringa) nome della località "sorgente" (la stringa può contenere spazi ma non può contenere virgole);
 * place2: (tipo stringa) nome della località "destinazione" (la stringa può contenere spazi ma non può contenere virgole);
 * distance: (tipo float) distanza in metri tra le due località.
 * 
 */
typedef struct _Record {
    char* place1;
    char* place2;
    double distance;

} Record;

// TODO: comment
extern const char* recordReadFmt;

// TODO: comment
extern const char* recordWriteFmt;

// TODO: redeclare these functions for HashTables and Graphs
/**
 * @brief Reads records from a file and stores them in an array of RecordPtr.
 *
 * This function reads a specified number of records from the given input file
 * and stores them in the provided array of RecordPtr. The function assumes that
 * the file is already opened for reading and that the array has enough space to
 * hold the specified number of records.
 *
 * Assumptions:
 * 
 * - The CSV file must contain only valid records.
 * 
 * - The CSV file must have a trailing newline at the end.
 *
 * @param infile A pointer to the input file from which records are to be read.
 * @param records A pointer to an array of RecordPtr where the read records will be stored.
 * @param n_records The number of records to read from the file.
 * @return The number of records successfully read from the file.
 * @throw `EXIT_FAILURE` if an error occurs while reading the records.
 */
size_t read_records(FILE* infile, Record* records, size_t n_records);

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
size_t write_records(FILE* outfile, Record* records, size_t n_records);

#endif // _IO_LIB_H