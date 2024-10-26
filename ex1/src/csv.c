#include "csv.h"
#include <errno.h>


const char* recordReadFmt = "%d,%99[^,],%d,%lf\n";
const char* recordWriteFmt = "%d,%s,%d,%lf\n";

int compare_field1(const void* a, const void* b) {
    return strcmp(((RecordPtr) a) -> field1, ((RecordPtr) b) -> field1);
}

int compare_field2(const void* a, const void* b) {
    return ((RecordPtr) a) -> field2 - ((RecordPtr) b) -> field2;
}

int compare_field3(const void* a, const void* b) {
    double res = (((RecordPtr) a) -> field3 - ((RecordPtr) b) -> field3);

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

// size_t read_records(FILE* infile, RecordPtr records, size_t n_records) {
//     size_t n_read_records = 0;

//     for (size_t i = 0; i < n_records; i++) {
//         size_t fields_read = fscanf(
//             infile, 
//             "%d,%99[^,],%d,%lf\n", 
//             &(records[i].id), 
//             records[i].field1, 
//             &(records[i].field2), 
//             &(records[i].field3)
//         );

//         if (fields_read != N_FIELDS_IN_RECORD) {
//             fprintf(stderr, "Error reading record from CSV file: %zu fields read instead of %zu\n", fields_read, N_FIELDS_IN_RECORD);
//             fprintf(stderr, "Aborting reading. Read %zu records.\n", n_read_records);
//             exit(EXIT_FAILURE);
//         }

//         n_read_records++;
//     }

//     return n_read_records;
// }
size_t read_records(FILE* infile, RecordPtr records, size_t n_records) {
    char line[MAX_LINE_SIZE];
    size_t read_count = 0;

    while (read_count < n_records && fgets(line, sizeof(line), infile)) {
        int parsed_fields = sscanf(line, recordReadFmt,
                                   &records[read_count].id,
                                   records[read_count].field1,
                                   &records[read_count].field2,
                                   &records[read_count].field3);
        
        if (parsed_fields != N_FIELDS_IN_RECORD) {
            errno = EINVAL;

            // fprintf(stderr, "Error reading record from CSV file: %d fields read instead of %d\n", parsed_fields, N_FIELDS_IN_RECORD);
            // fprintf(stderr, "Line causing error: '%s'\n", line);
            return read_count;
        }
        
        read_count++;
    }

    if (ferror(infile)) {
        perror("Error reading from CSV file");
        exit(EXIT_FAILURE);
    }

    return read_count;
}

// size_t write_records(FILE* outfile, RecordPtr records, size_t n_records) {
//     size_t n_wrote_records = 0;

//     for (size_t i = 0; i < n_records; i++) {
//         fprintf(
//             outfile, 
//             "%d,%s,%d,%lf\n", 
//             records[i].id, 
//             records[i].field1, 
//             records[i].field2, 
//             records[i].field3
//         );

//         n_wrote_records++;
//     }

//     return n_wrote_records;
// }
size_t write_records(FILE* outfile, RecordPtr records, size_t n_records) {
    size_t n_wrote_records;

    for (n_wrote_records = 0; n_wrote_records < n_records; n_wrote_records++) {
        int result = fprintf(
            outfile, 
            recordWriteFmt, 
            records[n_wrote_records].id, 
            records[n_wrote_records].field1, 
            records[n_wrote_records].field2, 
            records[n_wrote_records].field3
        );

        if (result < 0) {
            perror("Error writing to CSV file");
            exit(EXIT_FAILURE);
        }
    }

    return n_wrote_records;
}
