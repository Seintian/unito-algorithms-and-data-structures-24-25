/**
 * @file csv_operations.c
 * @brief This file contains the implementation of CSV reading, writing, and comparison functions.
 *
 * This file provides functions to read and write CSV records into an array, compare records
 * based on different fields, count lines in a file, and handle whitespace trimming.
 */

#include "csv.h"
#include <errno.h>
#include <string.h>
#include <ctype.h>


#define USE_BASE_IO_FUNCTIONS 0

const char* recordReadFmt = "%d,%239[^,],%d,%lf\n";
const char* recordWriteFmt = "%d,%s,%d,%lf\n";

int compare_field1(const void* a, const void* b) {
    const Record* recordA = (const Record*)a;
    const Record* recordB = (const Record*)b;
    
    return strcmp(recordA -> field1, recordB -> field1);
}

int compare_field2(const void* a, const void* b) {
    const Record* recordA = (const Record*)a;
    const Record* recordB = (const Record*)b;

    return recordA -> field2 - recordB -> field2;
}

int compare_field3(const void* a, const void* b) {
    const Record* recordA = (const Record*)a;
    const Record* recordB = (const Record*)b;

    double res = recordA -> field3 - recordB -> field3;

    if (res < 0)
        return -1;

    else if (res > 0)
        return 1;

    else
        return 0;
}

size_t count_lines(FILE* file) {
    size_t n_lines = 0;
    char buffer[MAX_LINE_SIZE];

    while (fgets(buffer, MAX_LINE_SIZE, file))
        n_lines++;

    rewind(file);

    return n_lines;
}

#ifdef USE_BASE_IO_FUNCTIONS
#   if USE_BASE_IO_FUNCTIONS == 0

/**
 * @brief Trims leading and trailing whitespace characters from a string.
 * 
 * This function modifies the input string by removing any leading or trailing whitespace characters.
 * It uses `isspace` to check for whitespace and adjusts the string accordingly.
 *
 * @param str The string to be trimmed.
 */
void trim_whitespace(char* str) {
    char* end;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == '\0')
        return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';
}

/**
 * @brief Parses a line from a CSV file into a record.
 * 
 * This function parses a line of CSV data into a `Record` structure. It tokenizes the line by commas,
 * trims whitespace, and assigns the values to the respective fields in the record.
 *
 * @param start The starting position of the line in the input buffer.
 * @param length The length of the line.
 * @param line A temporary buffer used to store the line.
 * @param record Pointer to the record where the parsed data will be stored.
 * @return The number of fields successfully parsed, or -1 if there was an error (e.g., line is too long).
 */
int parse_line(const char* start, size_t length, char* line, RecordPtr record) {
    if (length >= MAX_LINE_SIZE) 
        return -1;

    memcpy(line, start, length);

    line[length] = '\0';
    char* line_info;
    int fields_parsed = 0;

    char* token = strtok_r(line, ",", &line_info);
    if (token == NULL || strlen(token) == 0)
        return fields_parsed;

    trim_whitespace(token);

    record -> id = atoi(token);
    if (record -> id == 0 && errno == EINVAL)
        return fields_parsed;
    
    fields_parsed++;

    for (; fields_parsed < 4; fields_parsed++) {
        token = strtok_r(NULL, ",", &line_info);
        if (token == NULL)
            return fields_parsed;

        trim_whitespace(token);

        switch (fields_parsed) {
            case 1: {
                size_t len = strlen(token);

                record -> field1 = malloc(len + 1);
                if (record -> field1 == NULL) {
                    perror("Error allocating memory for field1");
                    exit(EXIT_FAILURE);
                }

                strcpy(record -> field1, token);

                break;
            }
            case 2: {
                record -> field2 = atoi(token);
                if (record -> field2 == 0 && errno == EINVAL)
                    return fields_parsed;

                break;
            }
            case 3: {
                record -> field3 = atof(token);
                if (record -> field3 == 0 && errno == EINVAL)
                    return fields_parsed;

                break;
            }
            default:
                break;
        }
    }

    return fields_parsed;
}

size_t read_records(FILE* infile, RecordPtr records, size_t n_records) {
    size_t read_count = 0;
    size_t bytes_read;
    size_t line_length;
    char buffer[READING_BUFFER_SIZE];
    char line[MAX_LINE_SIZE];
    const char* start;
    const char* end;
    const char* newline;
    int fields_parsed;

    while (read_count < n_records) {
        bytes_read = fread(buffer, 1, sizeof(buffer), infile);
        if (bytes_read == 0)
            break;

        start = buffer;
        end = buffer + bytes_read;

        while (start < end && read_count < n_records) {
            newline = memchr(start, '\n', end - start);
            if (!newline)
                break;

            line_length = newline - start;
            
            fields_parsed = parse_line(start, line_length, line, &records[read_count]);
            if (fields_parsed == N_FIELDS_IN_RECORD)
                read_count++;

            else if (fields_parsed == -1) {
                // line is too long to be a valid record
                fprintf(stderr, "Error: line is too long to be a valid record\n");
                exit(EXIT_FAILURE);
            }

            start = newline + 1;
        }

        // Handle any leftover data if needed.
        if (start < end)
            fseek(infile, -(end - start), SEEK_CUR);
    }

    if (ferror(infile)) {
        perror("Error reading from CSV file");
        exit(EXIT_FAILURE);
    }

    return read_count;
}

size_t write_records(FILE* outfile, RecordPtr records, size_t n_records) {
    size_t n_wrote_records = 0;
    char buffer[WRITING_BUFFER_SIZE];
    char* ptr = buffer;
    size_t buffer_left = sizeof(buffer);

    for (size_t i = 0; i < n_records; i++) {
        size_t written = snprintf(
            ptr, 
            buffer_left, 
            recordWriteFmt,
            records[i].id,
            records[i].field1,
            records[i].field2,
            records[i].field3
        );

        if (written >= buffer_left) {
            // Flush the buffer
            if (fwrite(buffer, 1, ptr - buffer, outfile) < ptr - buffer) {
                perror("Error writing to CSV file");
                exit(EXIT_FAILURE);
            }

            // Reset the buffer pointer and size
            ptr = buffer;
            buffer_left = sizeof(buffer);

            // Write the current record directly if it's still too large
            if (written >= sizeof(buffer)) {
                fprintf(
                    outfile, 
                    recordWriteFmt,
                    records[i].id,
                    records[i].field1,
                    records[i].field2,
                    records[i].field3
                );

                continue; // Skip the pointer update below for this record
            }

            // Retry writing the current record after flush
            written = snprintf(
                ptr,
                buffer_left,
                recordWriteFmt,
                records[i].id,
                records[i].field1,
                records[i].field2,
                records[i].field3
            );
        }

        // Update the buffer pointer and remaining size
        ptr += written;
        buffer_left -= written;

        n_wrote_records++;
    }

    // Flush any remaining data in the buffer
    if (ptr != buffer)
        fwrite(buffer, 1, ptr - buffer, outfile);

    return n_wrote_records;
}

#else

size_t read_records(FILE* infile, RecordPtr records, size_t n_records) {
    size_t read_count = 0;
    char* temp_buffer = malloc(MAX_FIELD1_SIZE);
    if (temp_buffer == NULL) {
        perror("Error allocating memory for temp_buffer");
        exit(EXIT_FAILURE);
    }

    for (; read_count < n_records; read_count++) {
        if (fscanf(
            infile, 
            recordReadFmt, 
            &records[read_count].id, 
            temp_buffer, 
            &records[read_count].field2, 
            &records[read_count].field3
        ) != N_FIELDS_IN_RECORD)
            break;

        records[read_count].field1 = malloc(strlen(temp_buffer) + 1);
        if (records[read_count].field1 == NULL) {
            perror("Error allocating memory for field1");
            exit(EXIT_FAILURE);
        }

        strcpy(records[read_count].field1, temp_buffer);
    }

    free(temp_buffer);

    return read_count;
}

size_t write_records(FILE* outfile, RecordPtr records, size_t n_records) {
    size_t n_wrote_records = 0;

    for (; n_wrote_records < n_records; n_wrote_records++)
        if (
            fprintf(
                outfile, 
                recordWriteFmt,
                records[n_wrote_records].id,
                records[n_wrote_records].field1,
                records[n_wrote_records].field2,
                records[n_wrote_records].field3
            ) == 0
        )
            break;

    return n_wrote_records;
}

#   endif
#endif